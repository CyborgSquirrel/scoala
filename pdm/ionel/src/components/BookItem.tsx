import { IonAvatar, IonCol, IonIcon, IonItem, IonLabel, IonRow, IonText, createAnimation } from "@ionic/react";
import { checkmark, close, star, starOutline } from "ionicons/icons";
import { useEffect, useRef, useState } from "react";
import { Fetcher } from "../common";

export interface Book {
  id?: number,
  title: string,
  rating: number,
  dateAdded: number,
  read: boolean,
  lat: number,
  lng: number,
}

export interface ServerBook {
  id?: number,
  title: string,
  rating: number,
  date_added: number,
  read: boolean,
  lat: number,
  lng: number,
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
    "lat": book.lat,
    "lng": book.lng,
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
    "lat": book.lat,
    "lng": book.lng,
  };
};

export interface BookItemProps {
  fetcher: Fetcher,
  book: Book,
  onClick?: (book: Book) => void,
}

const BookItem: React.FC<BookItemProps> = ({ fetcher, book: { id, title, rating, dateAdded, read, lat, lng }, onClick }) => {
  const [image, setImage] = useState<undefined|string>()
  useEffect(() => {
    (async () => {
      const response = await fetcher.fetch(
        `/book/image/${id}`,
        {
          method: "GET",
        }
      );
      const responseBlob = await response.blob();
      setImage(URL.createObjectURL(responseBlob));
    })();
  }, [fetcher]);

  let dateAddedDate = new Date(dateAdded * 1000);

  const stars = (amount: number, maxAmount: number) => {
    let icons = [];
    for (let i = 0; i < maxAmount; ++i) {
      const iconRef = useRef<null|HTMLIonIconElement>(null);
      const animationRef = useRef<null|Animation>(null);

      useEffect(() => {
        if (animationRef.current === null) {
          console.log("jo");
          const animation =  createAnimation()
            .addElement(iconRef.current!)
            .duration(2000)
            .iterations(Infinity)
            .keyframes([
              { offset: 0/6 , color: "red"    },
              { offset: 1/6 , color: "orange" },
              { offset: 2/6 , color: "yellow" },
              { offset: 3/6 , color: "green"  },
              { offset: 4/6 , color: "blue"   },
              { offset: 5/6 , color: "indigo" },
              { offset: 6/6 , color: "red"    },
            ])
          ;
          animationRef.current = animation;
          animation.play();
        }
      }, [iconRef]);

      let icon;
      if (i < amount) {
        icon = star;
      } else {
        icon = starOutline;
      }
      icons.push(
        <IonIcon ref={iconRef} key={i} icon={icon}></IonIcon>
      );
    }
    return icons;
  };

  let onClickInner = undefined;
  if (onClick !== undefined) {
    onClickInner = () => {
      onClick({ id, title, rating, dateAdded, read, lat, lng });
    };
  }

  return (
    <IonItem key={id} button onClick={onClickInner}>
      <IonAvatar aria-hidden="true" slot="start">
        <img alt="" src={image} />
      </IonAvatar>      
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
