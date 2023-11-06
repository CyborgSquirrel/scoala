import { IonButton, IonButtons, IonCheckbox, IonContent, IonFab, IonFabButton, IonFooter, IonHeader, IonIcon, IonInfiniteScroll, IonInfiniteScrollContent, IonInput, IonItem, IonLabel, IonList, IonModal, IonPage, IonSearchbar, IonSelect, IonSelectOption, IonSpinner, IonTitle, IonToolbar } from '@ionic/react';
import BookList from '../components/BookList';
import './Home.css';
import { useEffect, useState } from 'react';
import { add, filterOutline, settings } from 'ionicons/icons';
import BookItem, { Book, ServerBook, bookFromServer, bookToServer } from '../components/BookItem';
import { io, Socket } from "socket.io-client";
import Settings from '../components/Settings';
import SharedToolbar from '../components/SharedToolbar';
import { makeBooksToPost, makeIsConnected, makeJwt, makeJwtHeaders, makeServerHost, postBook } from '../common';

const BOOKS_REQUEST_SIZE = 10;

const Home: React.FC = () => {
  const [serverHost, setServerHost] = makeServerHost();
  const [jwt, setJwt] = makeJwt();
  const isConnected = makeIsConnected();

  const [isAddOpen, setIsAddOpen] = useState(false);
  const [books, setBooks] = useState<{[key: number]: Book}>({});
  
  const [isSettingsOpen, setIsSettingsOpen] = useState(false);

  const [bookTitle, setBookTitle] = useState("");
  const [bookRating, setBookRating]: [number|undefined, any] = useState();
  const [bookRead, setBookRead] = useState(false);

  const [socket, setSocket] = useState(() => {
    return io(serverHost, { transports: ["websocket"] });
  });
  const [isSockConnected, setIsSockConnected] = useState(false);

  const [offset, setOffset] = useState(0);
  const [queryFilter, setQueryFilter] = useState<undefined|string>();
  const [queryIsRead, setQueryIsRead] = useState<undefined|boolean>();

  const [infinite, setInfinite] = useState<HTMLIonInfiniteScrollElement|undefined>();

  // const [booksToPost, setBooksToPost] = useState<Book[]>([]);
  const [isBooksToPostReady, booksToPost, setBooksToPost] = makeBooksToPost();

  // socket
  useEffect(() => {
    setSocket(io(serverHost, { transports: ["websocket"] }));
  }, [serverHost]);

  // socket post book
  useEffect(() => {
    const onPostBook = (serverBook: ServerBook) => {
      let book = bookFromServer(serverBook)
      if (book.id === undefined) return;
      setBooks({...books, [book.id]: book});
    };

    socket.on("post_book", onPostBook);

    return () => {
      socket.off("post_book", onPostBook);
    };
  }, [socket, books]);

  // socket connection state
  useEffect(() => {
    function onConnect() {
      setIsSockConnected(true);
    }

    function onDisconnect() {
      setIsSockConnected(false);
    }

    socket.on("connect", onConnect);
    socket.on("disconnect", onDisconnect);

    return () => {
      socket.off("connect", onConnect);
      socket.off("disconnect", onDisconnect);
    };
  }, [socket]);

  // socket jwt authentication
  useEffect(() => {
    if (jwt === null) return;

    socket.emit("auth", { jwt_token: jwt });
  }, [socket]);

  useEffect(() => {
    if (booksToPost === undefined) return;
    if (!isBooksToPostReady) return;
    
    if (!isConnected) return;
    if (booksToPost.length < 1) return;
    if (jwt === null) return;

    const book = booksToPost[0];
    postBook(serverHost, jwt, book)?.then(
      () => {
        setBooksToPost(booksToPost.slice(1));
      },
      (reason) => {
        console.error(`Couldn't post book, due to ${reason}`);
      },
    );
  }, [booksToPost, isConnected, isBooksToPostReady]);

  interface GetBooksProps {
    offset: number,
    size: number,
    filter?: string,
    is_read?: boolean,
  }

  const getBooks = async ({offset, size, filter, is_read}: GetBooksProps): Promise<Book[]|null> => {
    if (serverHost === "") return null;
    if (jwt === null) return null;

    let searchParamsDict: any = {
      offset: offset.toString(),
      size: size.toString(),
    };
    if (filter !== undefined) {
      searchParamsDict.filter = filter;
    }
    if (is_read !== undefined) {
      searchParamsDict.is_read = is_read ? 1 : 0;
    }

    const searchParams = new URLSearchParams(searchParamsDict);
    const response = await fetch(
      `${serverHost}/book?` + searchParams.toString(),
      {
        method: "GET",
        headers: {
          ...makeJwtHeaders(jwt),
        },
      }
    );
    const books = (await response.json()).map(bookFromServer);
    return books;
  };

  const booksListToDict = (books: Book[]) => {
    return Object.fromEntries(books.map((book) => [book.id, book]));
  };

  useEffect(() => {
    setOffset(0);
    setBooks({});
  }, [serverHost, queryFilter, queryIsRead]);

  useEffect(() => {
    (
      getBooks({
        offset: offset,
        size: BOOKS_REQUEST_SIZE,
        filter: queryFilter,
        is_read: queryIsRead,
      })
      .then((newBooks) => {
        if (infinite !== undefined) {
          infinite.complete();
        }

        if (newBooks === null) return;
        setBooks((books) => ({
          ...books,
          ...booksListToDict(newBooks),
        }));
      })
    );
  }, [offset, queryFilter, queryIsRead]);

  const onInfinite = (event: Event) => {
    let target = event.target as HTMLIonInfiniteScrollElement;
    setOffset(offset + BOOKS_REQUEST_SIZE);
    setInfinite(target);
  };

  const onAddDismiss = () => {
    setIsAddOpen(false);
  };

  const onSearchbarInput = (event: Event) => {
    let target = event.target as HTMLIonSearchbarElement;
    let value = target.value!.trim();
    if (value === "") {
      setQueryFilter(undefined);
    } else {
      setQueryFilter(value);
    }
  };

  const onReadSelectChange = (event: Event) => {
    let target = event.target as HTMLIonSelectElement;
    if (target.value === null) {
      setQueryIsRead(undefined);
    } else {
      setQueryIsRead(target.value);
    }
  }
  
  return (
    <IonPage>
      <IonHeader>
        <SharedToolbar
          setIsSettingsOpen={setIsSettingsOpen}
          jwt={jwt}
          setJwt={setJwt}
          isConnected={isConnected}
        />
        <IonToolbar>
          <IonSearchbar debounce={500} onIonInput={onSearchbarInput} value={queryFilter} />
          <IonSelect slot="end" onIonChange={onReadSelectChange}>
            <IonSelectOption value={null}>Any</IonSelectOption>
            <IonSelectOption value={true}>Read</IonSelectOption>
            <IonSelectOption value={false}>Unread</IonSelectOption>
          </IonSelect>
        </IonToolbar>
      </IonHeader>
      <IonContent fullscreen>
        <IonList>
          {Object.values(books).map(
            (book) => BookItem(book)
          )}
        </IonList>
        <IonInfiniteScroll onIonInfinite={onInfinite}>
          <IonInfiniteScrollContent></IonInfiniteScrollContent>
        </IonInfiniteScroll>

        <Settings
          isOpen={isSettingsOpen}
          setIsOpen={setIsSettingsOpen}
          serverHost={serverHost}
          setServerHost={setServerHost}
          booksToPost={booksToPost}
        />

        <IonModal isOpen={isAddOpen} onWillDismiss={onAddDismiss}>
          <IonHeader>
            <IonToolbar>
              <IonTitle>Add Book</IonTitle>
              <IonButtons slot="end">
                <IonButton onClick={() => setIsAddOpen(false)}>Close</IonButton>
              </IonButtons>
            </IonToolbar>
          </IonHeader>
          <IonContent>
            <IonItem>
              <IonInput
                labelPlacement="stacked"
                label="Title"
                value={bookTitle}
                onIonInput={(event) => {
                  let value = event.target.value;
                  if (typeof value !== "string") return;
                  setBookTitle(value);
                }}
              />
            </IonItem>
            <IonItem>
              <IonInput
                labelPlacement="stacked"
                label="Rating"
                type="number"
                value={bookRating}
                onIonInput={(event) => {
                  let value = event.target.value;
                  if (typeof value !== "string") return;
                  let valueInt = parseInt(value);
                  if (typeof valueInt !== "number") return;
                  setBookRating(valueInt);
                }}
              />
            </IonItem>
            <IonItem>
              <IonCheckbox
                slot="end"
                value={bookRead}
                onIonChange={(event) => {
                  let value = event.detail.checked;
                  if (typeof value !== "boolean") return;
                  setBookRead(value);
                }}
              />
              <IonLabel>Read</IonLabel>
            </IonItem>
          </IonContent>
          <IonFooter>
            <IonToolbar>
              <IonButton
                expand="full"
                onClick={() => {
                  if (bookRating === undefined) return;

                  const book = {
                    title: bookTitle,
                    rating: bookRating,
                    read: bookRead,
                    dateAdded: Math.trunc(Date.now() / 1_000),
                  };

                  if (booksToPost === undefined) {
                    // NOTE: 💀
                    console.error("God stays in heaven, because He is afraid of what He has created...");
                    return;
                  }

                  setBooksToPost([...booksToPost, book]);

                  setIsAddOpen(false);
                }}
              >
                Submit
              </IonButton>
            </IonToolbar>
          </IonFooter>
        </IonModal>

        <IonFab slot="fixed" vertical="bottom" horizontal="end">
          <IonFabButton onClick={() => setIsAddOpen(true)}>
            <IonIcon icon={add}></IonIcon>
          </IonFabButton>
        </IonFab>

      </IonContent>
    </IonPage>
  );
};

export default Home;
