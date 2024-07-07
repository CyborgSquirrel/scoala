import { IonButton, IonButtons, IonCheckbox, IonContent, IonFab, IonFabButton, IonHeader, IonIcon, IonImg, IonInfiniteScrollContent, IonInput, IonItem, IonLabel, IonList, IonModal, IonPage, IonRadio, IonSearchbar, IonSelect, IonSelectOption, IonSpinner, IonText, IonTitle, IonToolbar } from '@ionic/react';
import './Home.css';
import { useEffect, useMemo, useRef, useState } from 'react';
import { add } from 'ionicons/icons';
import SharedToolbar from '../components/SharedToolbar';
import { Question, delay, makeAuthResponse, makeAxiosInstance, makePreferenceable, makeQuestions, queryClient, useSocket } from '../common';
import { defineCustomElements } from '@ionic/pwa-elements/loader'
import { useQuery } from '@tanstack/react-query';
import { AxiosError } from 'axios';
import { useHistory } from 'react-router';

defineCustomElements(window);

enum DownloadingState {
  Downloading,
  Finished,
  Failed,
}

const Home: React.FC = () => {
  let history = useHistory();
  // const [jwt, setJwt] = makeJwt();
  // const isConnected = makeIsConnected();

  const axiosInstance = makeAxiosInstance({});
  // const socket = useSocket();

  const [authResponse, _] = makeAuthResponse();

  const [downloadingState, setDownloadingState] = useState(DownloadingState.Downloading);
  const [questionIndex, setQuestionIndex] = useState(0);
  const [tmpQuestions, setTmpQuestions] = useState<Question[]>([]);
  const [questions, setQuestions] = makeQuestions();
  const [getting, setGetting] = useState(false);

  const questionIndexClamped = Math.min(questionIndex, authResponse!.questionIds.length-1);

  useEffect(() => {
    if (questions !== null) return;
    if (getting) return;
    if (downloadingState !== DownloadingState.Downloading) return;
    if (questionIndex >= authResponse!.questionIds.length) {
      setQuestions(tmpQuestions);
      return;
    }

    setGetting(true);
    const id = authResponse!.questionIds[questionIndex];
    (async () => {
      try {
        const response = await axiosInstance.get(`/question/${id}`);
        setTmpQuestions([...tmpQuestions, response.data]);
        setQuestionIndex(questionIndex+1);
      } catch {
        setDownloadingState(DownloadingState.Failed);
      }
      setGetting(false);
    })();
  }, [downloadingState, questionIndex, getting])

  useEffect(() => {
    if (questions === null) return;

    setDownloadingState(DownloadingState.Finished);
    // history.push("/");
    history.go(0);
  }, [questions])

  // socket messages changed
  // useEffect(() => {
  //   const handler = (message: Message) => {
  //     setMessages((messages) => ({...messages, ...{[message.id]: message}}));
  //   };

  //   socket.on("messages_changed", handler);

  //   return () => {
  //     socket.off("messages_changed", handler);
  //   };
  // }, [socket, messages]);

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

        <IonText>
          Downloading {questionIndexClamped+1}/{authResponse?.questionIds.length}
        </IonText>

        {
          downloadingState !== DownloadingState.Failed
          ? null
          : (
            <IonButton
              onClick={() => {
                setDownloadingState(DownloadingState.Downloading);
              }}
            >Retry</IonButton>
          )
        }

      </IonContent>
    </IonPage>
  );
};

export default Home;
