import { IonButton, IonButtons, IonCheckbox, IonContent, IonFab, IonFabButton, IonFooter, IonHeader, IonIcon, IonInput, IonItem, IonLabel, IonModal, IonPage, IonSpinner, IonTitle, IonToolbar } from '@ionic/react';
import BookList from '../components/BookList';
import './Home.css';
import { useEffect, useState } from 'react';
import { add, settings } from 'ionicons/icons';
import { Book, ServerBook, bookFromServer, bookToServer } from '../components/BookItem';
import { io, Socket } from "socket.io-client";
import Settings from '../components/Settings';

const Home: React.FC = () => {
  const getServerHost = (): string => {
    let serverHost = window.localStorage.getItem("serverHost");
    if (serverHost === null) {
      serverHost = "";
    }
    return serverHost;
  };

  const [isAddOpen, setIsAddOpen] = useState(false);
  const [books, setBooks] = useState<{[key: number]: Book}>({});
  
  const [isSettingsOpen, setIsSettingsOpen] = useState(false);

  const [bookTitle, setBookTitle] = useState("");
  const [bookRating, setBookRating]: [number|undefined, any] = useState();
  const [bookRead, setBookRead] = useState(false);

  // const HOST = "http://localhost:5000";

  const [serverHost, setServerHost] = useState("");

  const socket = io(serverHost);
  const [isConnected, setIsConnected] = useState(false);

  useEffect(() => {
    setServerHost(getServerHost());

    const eventListener = (_event) => {
      setServerHost(getServerHost());
    };

    document.addEventListener("storage", eventListener);

    return () => {
      document.removeEventListener("storage", eventListener);
    };
  }, []);

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
  }, [serverHost, books]);

  useEffect(() => {
    function onConnect() {
      setIsConnected(true);
    }

    function onDisconnect() {
      setIsConnected(false);
    }

    socket.on("connect", onConnect);
    socket.on("disconnect", onDisconnect);

    return () => {
      socket.off("connect", onConnect);
      socket.off("disconnect", onDisconnect);
    };
  }, [serverHost]);

  const postBook = (book: Book) => {
    if (serverHost === "") return;

    fetch(
      `${serverHost}/book`,
      {
        method: "POST",
        body: JSON.stringify(bookToServer(book)),
      },
    );
  };

  const getBooks = () => {
    if (serverHost === "") return;

    fetch(
      `${serverHost}/book`,
      {
        method: "GET",
      }
    )
    .then((response) => response.json())
    .then((response: any[]) => response.map(bookFromServer))
    .then((books) => Object.fromEntries(
      books.map((book) => [book.id, book])
    ))
    .then((books) => {
      setBooks(books);
    })
    ;
  };

  const renderSpinner = () => {
    // if (booksBeingAdded > 0) {
    //   return (
    //     <IonSpinner slot="secondary" />
    //   );
    // }
    return null;
  };

  useEffect(() => {
    getBooks();
  }, [serverHost]);

  const onAddDismiss = () => {
    setIsAddOpen(false);
  };
  
  return (
    <IonPage>
      <IonHeader>
        <IonToolbar>
          <IonTitle>Library</IonTitle>
          {renderSpinner()}
          <IonButton
            slot="end" fill="clear"
            onClick={() => {setIsSettingsOpen(true)}}
          >
            <IonIcon slot="icon-only" icon={settings}></IonIcon>
          </IonButton>
        </IonToolbar>
      </IonHeader>
      <IonContent fullscreen>
        <BookList books={Object.values(books)} />

        <Settings
          isOpen={isSettingsOpen}
          setIsOpen={setIsSettingsOpen}
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
                  postBook({
                    title: bookTitle,
                    rating: bookRating,
                    read: bookRead,
                    dateAdded: Date.now(),
                  });
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
