// import './ExploreContainer.css';

import { IonCol, IonIcon, IonItem, IonLabel, IonRow } from "@ionic/react";
import { checkmark, close } from "ionicons/icons";

export interface Book {
  id?: number,
  title: string,
  rating: number,
  dateAdded: number,
  read: boolean,
}

export interface ServerBook {
  id?: number,
  title: string,
  rating: number,
  date_added: number,
  read: boolean,
}

export const bookFromServer = (
  book: ServerBook,
): Book => {
  return {
    "id": book.id,
    "title": book.title,
    "rating": book.rating,
    "dateAdded": book.date_added,
    "read": book.read,
  };
};

export const bookToServer = (
  book: Book
): ServerBook => {
  return {
    "title": book.title,
    "rating": book.rating,
    "date_added": book.dateAdded,
    "read": book.read,
  };
}

const BookItem: React.FC<Book> = ({ id, title, rating, dateAdded, read }) => {
  let dateAddedDate = new Date(dateAdded);
  return (
    <IonRow key={id}>
      <IonCol><IonLabel>{title}</IonLabel></IonCol>
      <IonCol><IonLabel>{rating}/5</IonLabel></IonCol>
      <IonCol><IonLabel>{dateAddedDate.toLocaleDateString()}</IonLabel></IonCol>
      <IonCol><IonIcon icon={read ? checkmark : close} /></IonCol>
    </IonRow>
  );
};

export default BookItem;
