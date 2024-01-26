import { IonButton, IonContent, IonHeader, IonIcon, IonInput, IonItem, IonLabel, IonList, IonPage, IonText, IonTitle, IonToolbar } from "@ionic/react";
import { useEffect, useRef, useState } from "react";
import { makeAuthResponse, makeAxiosInstance, makeIsConnected, makeJwt } from "../common";
import { warning, warningOutline } from "ionicons/icons";
import { useHistory } from "react-router";
import { AxiosError } from "axios";

const LogIn: React.FC = () => {
  let history = useHistory();

  const [jwt, setJwt] = makeJwt();

  const [inputError, setInputError] = useState("")
  const [authResponse, setAuthResponse] = makeAuthResponse();

  const idRef = useRef<HTMLIonInputElement>(null);

  const axiosInstance = makeAxiosInstance({});

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
        }
      </IonHeader>
      <IonContent fullscreen>
        <IonList>
          <IonItem>
            <IonInput
              ref={idRef}
              labelPlacement="stacked"
              label="Id"
            />
          </IonItem>

          <IonButton
            expand="full"
            onClick={async () => {
              let id = idRef.current?.value;
              if (id === undefined) return;
              if (typeof id === "string") id = parseInt(id);
              // if (id === NaN) return;
              
              const response = await axiosInstance.post("/auth", {id: id});
              setAuthResponse(response.data);
              // history.push("/");
              history.go(0);
            }}
          >Log In</IonButton>
        </IonList>
      </IonContent>
    </IonPage>
  );
};

export default LogIn;
