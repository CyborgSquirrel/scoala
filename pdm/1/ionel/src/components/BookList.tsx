import { IonCol, IonGrid, IonInfiniteScroll, IonInfiniteScrollContent, IonItem, IonLabel, IonList, IonRow } from "@ionic/react";
import BookItem, { Book } from "./BookItem";

interface BookListProps {
  books: Book[],
}

const BookList: React.FC<BookListProps> = ({ books }) => {
  const loadMore = () => {
    
  };
  
  return (
    <div>
      <IonList>
        {books.map(
          (book) => BookItem(book)
        )}
      </IonList>
      <IonInfiniteScroll onIonInfinite={loadMore}>
        <IonInfiniteScrollContent></IonInfiniteScrollContent>
      </IonInfiniteScroll>
    </div>
  );
};

export default BookList;
