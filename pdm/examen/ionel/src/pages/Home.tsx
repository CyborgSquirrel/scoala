import { IonButton, IonButtons, IonCheckbox, IonContent, IonFab, IonFabButton, IonHeader, IonIcon, IonImg, IonInfiniteScrollContent, IonInput, IonItem, IonLabel, IonList, IonLoading, IonModal, IonPage, IonRadio, IonSearchbar, IonSelect, IonSelectOption, IonSpinner, IonText, IonTitle, IonToolbar, useIonToast } from '@ionic/react';
import './Home.css';
import { useEffect, useMemo, useRef, useState } from 'react';
import { add } from 'ionicons/icons';
import SharedToolbar from '../components/SharedToolbar';
import { delay, makeAxiosInstance, makeItemQuantities, makeMenu, makePreferenceable, queryClient, useSocket } from '../common';
import { defineCustomElements } from '@ionic/pwa-elements/loader'
import { useQuery } from '@tanstack/react-query';
import { AxiosError } from 'axios';
import { useHistory } from 'react-router';

defineCustomElements(window);

const Home: React.FC = () => {
  const [presentToast] = useIonToast();
  const reportError = (message: string) => {
    presentToast(
      message,
      2000,
    );
  }

  let history = useHistory();
  // const [jwt, setJwt] = makeJwt();
  // const isConnected = makeIsConnected();

  const axiosInstance = makeAxiosInstance({});
  const [menu, setMenu] = makeMenu();
  const [fetchingMenu, setFetchingMenu] = useState(false);

  const loadingMenu = menu === null;

  useEffect(() => {
    (async () => {
      try {
        const response_ = await axiosInstance.get("/");
      } catch (err_) {
        const err = err_ as AxiosError;
        if (err.code === "ERR_NETWORK") {
          reportError("Can't connect to server.");
        }
      }
    })();
  }, []);
  
  useEffect(() => {
    if (menu !== null) return;
    if (fetchingMenu) return;

    setFetchingMenu(true);

    // fetch menu from websocket
    {
      const socket = new WebSocket("ws://localhost:3000");
      socket.addEventListener("message", (message) => {
        setMenu(JSON.parse(message.data));
        socket.close();
        setFetchingMenu(false);
      });
    };
  }, [menu]);

  const [itemQuantities, setItemQuantities] = makeItemQuantities();
  const [selectedItem, setSelectedItem] = useState<null|number>(null);

  const [filterComandate, setFilterComandate] = useState(false);

  const [postRequests, setPostRequests] = useState<{ [code: number]: null }>({});
  const [postErrors, setPostErrors] = useState<{ [code: number]: null }>({});

  // const [downloadingState, setDownloadingState] = useState(DownloadingState.Downloading);
  // const [questionIndex, setQuestionIndex] = useState(0);
  // const [tmpQuestions, setTmpQuestions] = useState<Question[]>([]);
  // const [questions, setQuestions] = makeQuestions();
  // const [getting, setGetting] = useState(false);

  // const questionIndexClamped = Math.min(questionIndex, authResponse!.questionIds.length-1);

  // useEffect(() => {
  //   if (questions !== null) return;
  //   if (getting) return;
  //   if (downloadingState !== DownloadingState.Downloading) return;
  //   if (questionIndex >= authResponse!.questionIds.length) {
  //     setQuestions(tmpQuestions);
  //     return;
  //   }

  //   setGetting(true);
  //   const id = authResponse!.questionIds[questionIndex];
  //   (async () => {
  //     try {
  //       const response = await axiosInstance.get(`/question/${id}`);
  //       setTmpQuestions([...tmpQuestions, response.data]);
  //       setQuestionIndex(questionIndex+1);
  //     } catch {
  //       setDownloadingState(DownloadingState.Failed);
  //     }
  //     setGetting(false);
  //   })();
  // }, [downloadingState, questionIndex, getting])

  // useEffect(() => {
  //   if (questions === null) return;

  //   setDownloadingState(DownloadingState.Finished);
  //   // history.push("/");
  //   history.go(0);
  // }, [questions])

  return (
    <IonPage>
      <IonHeader>
        
        {
          // <SharedToolbar
          //   setIsSettingsOpen={setIsSettingsOpen}
          //   jwt={jwt}
          //   setJwt={setJwt}
          //   isConnected={isConnected}
          // />
          // <IonToolbar>
          //   <IonSearchbar debounce={500} onIonInput={onSearchbarInput} value={queryFilter} />
          //   <IonSelect slot="end" onIonChange={onReadSelectChange}>
          //     <IonSelectOption value={null}>Any</IonSelectOption>
          //     <IonSelectOption value={true}>Read</IonSelectOption>
          //     <IonSelectOption value={false}>Unread</IonSelectOption>
          //   </IonSelect>
          // </IonToolbar>
        }
      </IonHeader>
      <IonContent fullscreen>
        {
          loadingMenu ? (<IonSpinner />)
          : (
            <>
              <IonCheckbox
                value={filterComandate}
                onClick={(event) => {
                  const target = event.target as HTMLIonCheckboxElement;
                  setFilterComandate(target.checked);
                }}
              >Comandate</IonCheckbox>
              <IonList>
                {
                  menu!
                  .filter((item) => {
                    if (filterComandate) {
                      return item.code in itemQuantities;
                    }
                    return true;
                  })
                  .map((item) => (
                    <IonItem
                      key={item.code}
                      onClick={() => {
                        if (selectedItem !== null) return;
                        setSelectedItem(item.code);
                      }}
                    >
                      <IonText>{item.name}</IonText><br/>
                      <IonInput
                        labelPlacement="stacked"
                        label="Quantity"
                        type="number"
                        class={item.code in postErrors ? "error" : undefined}
                        // style={{
                        //   "--color": item.code in postErrors ? "danger" : undefined,
                        // }}
                        value={item.code in itemQuantities ? itemQuantities[item.code] : undefined}
                        onKeyUp={(event) => {
                          if (event.code !== "Enter") return;

                          setSelectedItem(null);
                      
                          const target = event.target as HTMLIonInputElement;
                          let value = target.value;
                          if (value === undefined || value === null) {
                            var newItemQuantities = {...itemQuantities};
                            delete newItemQuantities[item.code];
                          } else {
                            if (typeof value === "string") value = parseInt(value);
                            var newItemQuantities = {...itemQuantities, ...{[item.code]: value}};
                          }

                          setItemQuantities(newItemQuantities);
                        }}
                        readonly={selectedItem !== item.code}
                      />
                      {
                        !(item.code in postRequests) ? null : (
                          <IonSpinner/>
                        )
                      }
                    </IonItem>
                  ))
                }
              </IonList>
              <IonButton
                disabled={Object.keys(postRequests).length !== 0}
                onClick={() => {
                  // only active if not order in progress?
                  // run a bunch of async posts
                  // set up each post in a map
                  let newPostRequests: any = {};
                  for (const [code_, quantity] of Object.entries(itemQuantities)) {
                    const code = parseInt(code_);
                    newPostRequests[code] = null;
                    (async () => {
                      try {
                        const response = await axiosInstance.post("/item", { code: code, quantity: quantity });
                        setPostErrors((postErrors) => {
                          let newPostErrors = {...postErrors};
                          delete newPostErrors[code];
                          return newPostErrors;
                        });
                      } catch (err_) {
                        const err = err_ as AxiosError;
                        console.error(err);
                        setPostErrors((postErrors) => ({...postErrors, [code]: null}));
                      }
                      setPostRequests((postRequests) => {
                        let newPostRequests = {...postRequests};
                        delete newPostRequests[code];
                        return newPostRequests;
                      });
                    })();
                  }
                  setPostRequests(newPostRequests);
                }}
              >Submit</IonButton>
            </>
          )
        }
      </IonContent>
    </IonPage>
  );
};

export default Home;
