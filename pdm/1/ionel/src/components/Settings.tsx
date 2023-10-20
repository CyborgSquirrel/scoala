import { IonButton, IonButtons, IonCheckbox, IonContent, IonFab, IonFabButton, IonFooter, IonHeader, IonIcon, IonInput, IonItem, IonLabel, IonModal, IonPage, IonSpinner, IonTitle, IonToolbar } from '@ionic/react';
import { close } from 'ionicons/icons';
import { useEffect, useState } from 'react';

interface SettingsProps {
  isOpen: boolean,
  setIsOpen: React.Dispatch<React.SetStateAction<boolean>>,
}

const Settings: React.FC<SettingsProps> = ({isOpen, setIsOpen}: SettingsProps) => {
  const [serverHost, setServerHost] = useState("");

  useEffect(() => {
    let serverHost = window.localStorage.getItem("serverHost");
    if (serverHost === null) {
      serverHost = "";
      window.localStorage.setItem("serverHost", serverHost);
    }
    setServerHost(serverHost);
  }, []);

  const onSettingsDismiss = () => {
    window.localStorage.setItem("serverHost", serverHost);
    setIsOpen(false);
  };

  return (
    <IonModal
      isOpen={isOpen}
      onWillDismiss={onSettingsDismiss}
    >
      <IonHeader>
        <IonToolbar>
          <IonTitle>Settings</IonTitle>
          <IonButton
            slot="end" fill="clear"
            onClick={() => {setIsOpen(false)}}
          >
            <IonIcon slot="icon-only" icon={close}></IonIcon>
          </IonButton>
        </IonToolbar>
      </IonHeader>
      <IonContent>
        <IonItem>
          <IonInput
            labelPlacement="stacked"
            label="Server Host"
            value={serverHost}
            onIonInput={(event) => {
              let value = event.target.value;
              if (typeof value !== "string") return;
              setServerHost(value);
            }}
          />
        </IonItem>
      </IonContent>
    </IonModal>
  );
};

export default Settings;
