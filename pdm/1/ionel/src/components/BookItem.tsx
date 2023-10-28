import { IonCol, IonIcon, IonItem, IonLabel, IonRow, IonText } from "@ionic/react";
import { checkmark, close, star, starOutline } from "ionicons/icons";

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
  let dateAddedDate = new Date(dateAdded * 1000);

  const stars = (amount: number, maxAmount: number) => {
    let icons = [];
    for (let i = 0; i < maxAmount; ++i) {
      let icon;
      if (i < amount) {
        icon = star;
      } else {
        icon = starOutline;
      }
      icons.push(
        <IonIcon key={i} icon={icon}></IonIcon>
      );
    }
    return icons;
  };

  return (
    <IonItem key={id}>
      <IonLabel>
        <strong>{title}</strong>
        <br />
        {stars(rating, 5)}
        <br />
        {dateAddedDate.toLocaleDateString()}
        <br />
        Read: <IonIcon icon={read ? checkmark : close} />
      </IonLabel>
    </IonItem>
  );
};

export default BookItem;
