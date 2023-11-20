import { IonButton, IonButtons, IonCheckbox, IonContent, IonFab, IonFabButton, IonFooter, IonHeader, IonIcon, IonInput, IonItem, IonLabel, IonModal, IonPage, IonSpinner, IonTitle, IonToolbar, createAnimation } from '@ionic/react';
import { close } from 'ionicons/icons';
import { useEffect, useState } from 'react';
import { makeServerHost } from '../common';
import { Book } from './BookItem';

interface SettingsProps {
  isOpen: boolean,
  setIsOpen: React.Dispatch<React.SetStateAction<boolean>>,

  serverHost: string,
  setServerHost: React.Dispatch<React.SetStateAction<string>>,

  mapsApiKey: string,
  setMapsApiKey: React.Dispatch<React.SetStateAction<string>>,

  booksToPost?: number,
}

const Settings: React.FC<SettingsProps> = (p: SettingsProps) => {
  const [innerServerHost, setInnerServerHost] = useState(p.serverHost);
  const [innerMapsApiKey, setInnerMapsApiKey] = useState(p.mapsApiKey);
  
  const enterAnimation = (baseEl: HTMLElement) => {
    const root = baseEl.shadowRoot!;

    const wrapperAnimation = createAnimation()
      .addElement(root.querySelector('.modal-wrapper')!)
      .keyframes([
        { offset: 0, opacity: '0', transform: 'rotate(0)' },
        { offset: 1, opacity: '0.99', transform: 'rotate(2turn)' },
      ]);

    return createAnimation()
      .addElement(baseEl)
      .easing('ease-out')
      .duration(500)
      .addAnimation(wrapperAnimation);
  };

  const leaveAnimation = (baseEl: HTMLElement) => {
    const root = baseEl.shadowRoot!;

    const wrapperAnimation = createAnimation()
      .addElement(root.querySelector('.modal-wrapper')!)
      .keyframes([
        { offset: 0, opacity: '0.99', transform: 'rotate(2turn)' },
        { offset: 1, opacity: '0', transform: 'rotate(0turn)' },
      ]);

    return createAnimation()
      .addElement(baseEl)
      .easing('ease-out')
      .duration(500)
      .addAnimation(wrapperAnimation);
  };

  const onSettingsDismiss = () => {
    p.setServerHost(innerServerHost);
    p.setMapsApiKey(innerMapsApiKey);
    p.setIsOpen(false);
  };

  let booksToPost = 0;
  if (p.booksToPost !== undefined) {
    booksToPost = p.booksToPost;
  }

  return (
    <IonModal
      isOpen={p.isOpen}
      onWillDismiss={onSettingsDismiss}
      enterAnimation={enterAnimation}
      leaveAnimation={leaveAnimation}
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
            label="Maps API Key"
            value={innerMapsApiKey}
            onIonInput={(event) => {
              let value = event.target.value;
              if (typeof value !== "string") return;
              setInnerMapsApiKey(value);
            }}
          />
        </IonItem>

        <IonItem>
          <IonInput
            labelPlacement="stacked"
            label="Books to be posted"
            value={booksToPost}
            readonly={true}
          />
        </IonItem>
        
      </IonContent>
    </IonModal>
  );
};

export default Settings;
