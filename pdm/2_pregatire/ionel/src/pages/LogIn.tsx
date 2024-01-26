import { IonButton, IonContent, IonHeader, IonIcon, IonInput, IonItem, IonLabel, IonList, IonPage, IonText, IonTitle, IonToolbar } from "@ionic/react";
import { useEffect, useState } from "react";
import { makeAxiosInstance, makeIsConnected, makeJwt } from "../common";
import { warning, warningOutline } from "ionicons/icons";
import { useHistory } from "react-router";
import { AxiosError } from "axios";

const LogIn: React.FC = () => {
  let history = useHistory();

  const [jwt, setJwt] = makeJwt();

  const [inputError, setInputError] = useState("");

  const [name, setName] = useState("");
  const [password, setPassword] = useState("");

  const axiosInstance = makeAxiosInstance({});

  const logInRequest = async () => {
    setInputError("");
    axiosInstance.post("/user/login", {name: name, password: password})
      .then((response) => {
        setJwt(response.data.access_token);
        history.go(0);
      })
      .catch((err: AxiosError) => {
        setInputError("Invalid credentials");
      })
    ;
  };

  const InputError = () => {
    if (inputError === "") return null;
    
    return (
      <IonItem>
        <IonIcon slot="start" color="danger" icon={warningOutline}></IonIcon>
        <IonLabel color="danger">{inputError}</IonLabel>
      </IonItem>
    );
  };

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
          <InputError></InputError>

          <IonItem>
            <IonInput
              labelPlacement="stacked"
              label="Name"
              value={name}
              onIonInput={(event) => {
                let value = event.target.value;
                if (typeof value !== "string") return;
                setName(value);
              }}
            />
          </IonItem>

          <IonItem>
            <IonInput
              labelPlacement="stacked"
              label="Password"
              type="password"
              value={password}
              onIonInput={(event) => {
                let value = event.target.value;
                if (typeof value !== "string") return;
                setPassword(value);
              }}
            />
          </IonItem>

          <IonButton expand="full" onClick={() => {logInRequest();}}>Log In</IonButton>
        </IonList>
      </IonContent>
    </IonPage>
  );
};

export default LogIn;
