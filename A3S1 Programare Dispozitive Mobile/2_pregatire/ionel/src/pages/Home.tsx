import { IonButton, IonButtons, IonCheckbox, IonContent, IonFab, IonFabButton, IonHeader, IonIcon, IonImg, IonInfiniteScrollContent, IonInput, IonItem, IonLabel, IonList, IonModal, IonPage, IonRadio, IonSearchbar, IonSelect, IonSelectOption, IonSpinner, IonText, IonTitle, IonToolbar } from '@ionic/react';
import './Home.css';
import { useEffect, useMemo, useRef, useState } from 'react';
import { add } from 'ionicons/icons';
import SharedToolbar from '../components/SharedToolbar';
import { Message, delay, makeAxiosInstance, makePreferenceable, queryClient, useSocket } from '../common';
import { defineCustomElements } from '@ionic/pwa-elements/loader'
import { useQuery } from '@tanstack/react-query';
import { AxiosError } from 'axios';

defineCustomElements(window);

interface User {
  unreadMessagesNo: number,
  lastUnreadMessageTimestamp?: number,
}

const Home: React.FC = () => {
  // const [jwt, setJwt] = makeJwt();
  // const isConnected = makeIsConnected();

  const axiosInstance = makeAxiosInstance({});
  const socket = useSocket();

  const messagesQuery = useQuery<Message[]>({
    queryKey: ["message"],
    initialData: [],
    queryFn: async () => {
      const response = await axiosInstance.get("/message");
      return response.data;
    },
  }, queryClient);

  const [messagesIsReady, messages, setMessages] = makePreferenceable<{ [id: number]: Message; }>("messages", {});
  const [putMessagesIsReady, putMessages, setPutMessages] = makePreferenceable<Message[]>("putMessages", []);

  const [isPutting, setIsPutting] = useState(false);

  useEffect(() => {
    if (putMessages === undefined) return;
    if (putMessages.length === 0) {
      if (putMessagesIsReady && !isPutting) {
        queryClient.invalidateQueries({queryKey: ["message"]});
      }
      return;
    }
    if (isPutting) return;

    const putMessage = putMessages[0];
    setIsPutting(true);
    (async () => {
      while (true) {
        try {
          await axiosInstance.put(
            `/message/${putMessage.id}`,
            putMessage,
          );
          break;
        } catch (err_) {
          // try again
          await delay(1000);
        }
      }
      
      setIsPutting(false);
      setPutMessages(putMessages.slice(1));
    })();
  }, [isPutting, putMessages]);
  
  useEffect(() => {
    if (!putMessagesIsReady) return;
    if (putMessages!.length > 0) return;
    if (isPutting) return;

    let newMessages: { [name: string]: Message; } = {};
    for (const message of messagesQuery.data) {
      newMessages[message.id] = message;
    }
    setMessages(newMessages);
  }, [messagesQuery.data, putMessages, putMessagesIsReady, isPutting]);

  let users: { [name: string]: User; } = {};
  for (const message of Object.values(messages!)) {
    if (!(message.sender in users)) {
      users[message.sender] = {
        unreadMessagesNo: 0,
      };
    }

    let user = users[message.sender];
    if (!message.read) {
      user.unreadMessagesNo += 1;
      if (user.lastUnreadMessageTimestamp === undefined) {
        user.lastUnreadMessageTimestamp = message.created;
      }
      user.lastUnreadMessageTimestamp = Math.max(user.lastUnreadMessageTimestamp, message.created);
    }
  }

  // NOTE: Seems kinda sus but don't have time to look into this further...
  const orderedUsers = (
    Object.entries(users).toSorted((a, b) => (Number(a[1].unreadMessagesNo <= 0) - Number(b[1].unreadMessagesNo <= 0)) || (b[1].lastUnreadMessageTimestamp! - a[1].lastUnreadMessageTimestamp!))
  );

  const messagesModal = useRef<HTMLIonModalElement>(null);
  const [selectedUser, setSelectedUser] = useState<null|string>(null);

  const selectedUserMessages = (
    selectedUser === null ? null :
    Object.values(messages!)
      .filter((message) => message.sender === selectedUser)
      .toSorted((a, b) => b.created - a.created)
  );

  useEffect(() => {
    if (selectedUser === null) {
      messagesModal.current?.dismiss();
    } else {
      messagesModal.current?.present();
    }
  }, [selectedUser]);

  // socket messages changed
  useEffect(() => {
    const handler = (message: Message) => {
      setMessages((messages) => ({...messages, ...{[message.id]: message}}));
    };

    socket.on("messages_changed", handler);

    return () => {
      socket.off("messages_changed", handler);
    };
  }, [socket, messages]);

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

        <IonList>
          {
            orderedUsers
              .map((user) => (
                <IonItem
                  key={user[0]}
                  onClick={() => {
                    setSelectedUser(user[0]);
                  }}
                >
                  <IonLabel>{user[0]} [{user[1].unreadMessagesNo}]</IonLabel>
                </IonItem>
              ))
          }
        </IonList>

        <IonModal
          ref={messagesModal}
          onWillPresent={() => {
            (async () => {
              if (selectedUserMessages === null) return;
              if (putMessages === undefined) return;
              await delay(1000);

              const newPutMessages = [...putMessages];
              const newMessages = {...messages};
              for (const message of selectedUserMessages) {
                if (!message.read) {
                  const newMessage = {...message, read: true};
                  newMessages[message.id] = newMessage;
                  newPutMessages.push(newMessage);
                }
              }
              setMessages(newMessages);
              setPutMessages(newPutMessages);
            })();
          }}
          onWillDismiss={() => {
            setSelectedUser(null);
          }}
        >
          <IonContent>
            <IonList>
              {
                selectedUserMessages?.map((message) => (
                  <IonItem key={message.id}>
                    {
                      message.read ? message.text :
                      (
                        <b>{message.text}</b>
                      )
                    }
                  </IonItem>
                ))
              }
            </IonList>
          </IonContent>
        </IonModal>

      </IonContent>
    </IonPage>
  );
};

export default Home;
