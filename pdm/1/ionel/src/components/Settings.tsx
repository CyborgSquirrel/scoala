import { IonButton, IonButtons, IonCheckbox, IonContent, IonFab, IonFabButton, IonFooter, IonHeader, IonIcon, IonInput, IonItem, IonLabel, IonModal, IonPage, IonSpinner, IonTitle, IonToolbar } from '@ionic/react';
import { close } from 'ionicons/icons';
import { useEffect, useState } from 'react';
import { makeServerHost } from '../common';
import { Book } from './BookItem';

interface SettingsProps {
  isOpen: boolean,
  setIsOpen: React.Dispatch<React.SetStateAction<boolean>>,

  serverHost: string,
  setServerHost: React.Dispatch<React.SetStateAction<string>>,

  booksToPost?: Book[],
}

const Settings: React.FC<SettingsProps> = (p: SettingsProps) => {
  const [innerServerHost, setInnerServerHost] = useState(() => {
    return p.serverHost;
  });

  const onSettingsDismiss = () => {
    p.setServerHost(innerServerHost);
    p.setIsOpen(false);
  };

  let booksToPostLength = 0;
  if (p.booksToPost !== undefined) {
    booksToPostLength = p.booksToPost.length;
  }

  return (
    <IonModal
      isOpen={p.isOpen}
      onWillDismiss={onSettingsDismiss}
    >
      <IonHeader>
        <IonToolbar>
          <IonTitle>Settings</IonTitle>
          <IonButton
            slot="end" fill="clear"
            onClick={() => {p.setIsOpen(false)}}
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
            value={innerServerHost}
            onIonInput={(event) => {
              let value = event.target.value;
              if (typeof value !== "string") return;
              setInnerServerHost(value);
            }}
          />
        </IonItem>

        <IonItem>
          <IonInput
            labelPlacement="stacked"
            label="Books to be posted"
            value={booksToPostLength}
            readonly={true}
          />
        </IonItem>
        
      </IonContent>
    </IonModal>
  );
};

export default Settings;
