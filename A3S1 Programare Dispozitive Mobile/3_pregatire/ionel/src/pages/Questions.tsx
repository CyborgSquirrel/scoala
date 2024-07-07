import { IonButton, IonButtons, IonCheckbox, IonContent, IonFab, IonFabButton, IonHeader, IonIcon, IonImg, IonInfiniteScrollContent, IonInput, IonItem, IonLabel, IonList, IonModal, IonPage, IonRadio, IonRadioGroup, IonSearchbar, IonSelect, IonSelectOption, IonSpinner, IonText, IonTitle, IonToolbar } from '@ionic/react';
import './Home.css';
import { Fragment, useEffect, useMemo, useRef, useState } from 'react';
import { add } from 'ionicons/icons';
import SharedToolbar from '../components/SharedToolbar';
import { Question, delay, makeAuthResponse, makeAxiosInstance, makePreferenceable, makeQuestions, makeStorable, queryClient, useSocket } from '../common';
import { defineCustomElements } from '@ionic/pwa-elements/loader'
import { useQuery } from '@tanstack/react-query';
import { AxiosError } from 'axios';

defineCustomElements(window);

enum DownloadingState {
  Downloading,
  Finished,
  Failed,
}

const Questions: React.FC = () => {
  // const [jwt, setJwt] = makeJwt();
  // const isConnected = makeIsConnected();

  const axiosInstance = makeAxiosInstance({});
  // const socket = useSocket();

  const [authResponse, _] = makeAuthResponse();

  const [questions, setQuestions] = makeQuestions();

  const [answers, setAnswers] = makeStorable<(number|undefined)[]>(
    "answers",
    [],
    window.localStorage,
  );

  let [correctQuestions, setCorrectQuestions] = useState(0);

  useEffect(() => {
    let newCorrectQuestions = 0;
    for (let i = 0; i < Math.min(questions!.length, answers.length); ++i) {
      if (questions![i].indexCorrectOption === answers[i]) {
        newCorrectQuestions += 1;
      }
    }
    setCorrectQuestions(newCorrectQuestions);
  }, [questions, answers]);

  const answerRef = useRef<HTMLIonRadioGroupElement>(null);

  const question = questions![answers.length];

  const answerQuestion = () => {
    if (question === undefined) return;
    
    const value = answerRef.current?.value;
    if (value === question.indexCorrectOption) {
      setCorrectQuestions(correctQuestions + 1);
    }
    setAnswers([...answers, value])
  }

  useEffect(() => {
    const id = setTimeout(() => {
      answerQuestion();
    }, 5000);
    return () => {
      clearInterval(id);
    }
  }, [answers]);

  const [socket, setSocket] = useState(() => new WebSocket("ws://localhost:3000"));

  useEffect(() => {
    const onMessage = (event: any) => {
      const data = JSON.parse(event.data);
      setQuestions([...questions!, data]);
    };
    socket.addEventListener("message", onMessage);

    return () => {
      socket.removeEventListener("message", onMessage);
    }
  }, [socket]);

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
          Correct {correctQuestions}/{questions!.length}
        </IonText>
        <br/>

        {
          question === undefined ? null : (
            <Fragment>
              <IonText>
                {question.text}
              </IonText>
              <br/>
              <IonRadioGroup ref={answerRef}>{
                question.options.map((answer, index) => (
                  <IonRadio key={index} labelPlacement="end" value={index}>{answer}</IonRadio>
                ))
              }</IonRadioGroup>
              <IonButton
                onClick={() => {
                  answerQuestion();
                }}
              >Next</IonButton>
            </Fragment>
          )
        }

      </IonContent>
    </IonPage>
  );
};

export default Questions;

