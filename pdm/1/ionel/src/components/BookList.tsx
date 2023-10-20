import { IonCol, IonGrid, IonItem, IonLabel, IonList, IonRow } from "@ionic/react";
import BookItem, { Book } from "./BookItem";

interface BookListProps {
  books: Book[],
}

const BookList: React.FC<BookListProps> = ({ books }) => {
  return (
    <IonGrid>
      <IonRow>
        <IonCol><IonLabel>Title</IonLabel></IonCol>
        <IonCol><IonLabel>Rating</IonLabel></IonCol>
        <IonCol><IonLabel>Date Added</IonLabel></IonCol>
        <IonCol><IonLabel>Read</IonLabel></IonCol>
      </IonRow>
      {books.map(
        (book) => BookItem(book)
      )}
    </IonGrid>
  );
};

export default BookList;
