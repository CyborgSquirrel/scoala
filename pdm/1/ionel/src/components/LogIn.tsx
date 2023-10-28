import { IonButton, IonContent, IonHeader, IonIcon, IonInput, IonItem, IonLabel, IonList, IonPage, IonText, IonTitle, IonToolbar } from "@ionic/react";
import { useEffect, useState } from "react";
import SharedToolbar from "./SharedToolbar";
import Settings from "./Settings";
import { makeIsConnected, makeJwt, makeServerHost } from "../common";
import { warning, warningOutline } from "ionicons/icons";
import { useHistory } from "react-router";

const LogIn: React.FC = () => {
  let history = useHistory();

  const [serverHost, setServerHost] = makeServerHost();

  const [jwt, setJwt] = makeJwt();
  const isConnected = makeIsConnected();

  const [inputError, setInputError] = useState("");

  const [isSettingsOpen, setIsSettingsOpen] = useState(false);
  
  const [name, setName] = useState("");
  const [password, setPassword] = useState("");

  const logInRequest = () => {
    fetch(
      `${serverHost}/user/login`,
      {
        method: "POST",
        body: JSON.stringify({name: name, password: password}),
      },
    ).then((response) => {
      setInputError("");
      if (response.status !== 200) {
        console.error(response);
        setInputError("Invalid credentials");
      } else {
        response.json().then((response) => {
          if (typeof response.access_token !== "string") return;
          setJwt(response.access_token);
          history.go(0);
        });
      }
    });
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

  const onLogInClicked = () => {
    logInRequest();
  };
  
  return (
    <IonPage>
      <IonHeader>
        <SharedToolbar
          setIsSettingsOpen={setIsSettingsOpen}
          jwt={jwt}
          setJwt={setJwt}
          isConnected={isConnected}
        />
      </IonHeader>
      <IonContent fullscreen>
        <Settings
          isOpen={isSettingsOpen}
          setIsOpen={setIsSettingsOpen}
          serverHost={serverHost}
          setServerHost={setServerHost}
        />

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

          <IonButton expand="full" onClick={onLogInClicked}>Log In</IonButton>
        </IonList>
      </IonContent>
    </IonPage>
  );
};

export default LogIn;
