import { IonButton, IonHeader, IonIcon, IonTitle, IonToolbar } from "@ionic/react";
import { cloud, cloudCircle, logOut as logOutIcon, settings } from "ionicons/icons";
import { Dispatch, SetStateAction, useMemo } from "react";
import { useHistory } from "react-router";

interface HeaderProps {
  setIsSettingsOpen: React.Dispatch<React.SetStateAction<boolean>>,
  jwt: string|null,
  setJwt: Dispatch<SetStateAction<string|null>>,
  isConnected: boolean,
}

const SharedToolbar: React.FC<HeaderProps> = ({setIsSettingsOpen, jwt, setJwt, isConnected}: HeaderProps) => {
  let history = useHistory();
  let loggedIn = jwt !== null;
  
  const logOut = () => {
    setJwt(null);
    history.go(0);
  };
  
  return (
    <IonToolbar>

      <IonTitle>Library</IonTitle>

      {loggedIn ? (
        <IonButton
          slot="end" fill="clear"
          onClick={logOut}
        >
          <IonIcon slot="icon-only" icon={logOutIcon} />
        </IonButton>
      ) : null}

      <IonButton
        slot="end" fill="clear"
        onClick={() => {setIsSettingsOpen(true)}}
      >
        <IonIcon slot="icon-only" icon={settings} />
      </IonButton>

      <IonButton
        slot="end" fill="clear" color={isConnected ? "success" : "danger"}
      >
        <IonIcon slot="icon-only" icon={cloud} />
      </IonButton>

    </IonToolbar>
  );
};

export default SharedToolbar;
