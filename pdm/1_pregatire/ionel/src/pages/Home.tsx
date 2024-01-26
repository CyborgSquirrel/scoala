import { IonButton, IonButtons, IonCheckbox, IonContent, IonFab, IonFabButton, IonHeader, IonIcon, IonImg, IonInfiniteScrollContent, IonInput, IonItem, IonLabel, IonList, IonModal, IonPage, IonRadio, IonSearchbar, IonSelect, IonSelectOption, IonSpinner, IonText, IonTitle, IonToolbar } from '@ionic/react';
import './Home.css';
import { useEffect, useMemo, useRef, useState } from 'react';
import { add } from 'ionicons/icons';
import SharedToolbar from '../components/SharedToolbar';
import { Item, Product, delay, makeAxiosInstance, makePreferenceable, useSocket } from '../common';
import { defineCustomElements } from '@ionic/pwa-elements/loader'

defineCustomElements(window);

enum DownloadingState {
  Downloading,
  Finished,
  Outdated,
}

const Home: React.FC = () => {
  // const [jwt, setJwt] = makeJwt();
  // const isConnected = makeIsConnected();

  const axiosInstance = makeAxiosInstance({});
  const socket = useSocket();

  const [downloadingState, setDownloadingState] = useState(DownloadingState.Downloading);

  const [products, setProducts] = useState<Product[]>([]);
  const [filteredProducts, setFilteredProducts] = useState<Product[]>([]);

  const [pageIndex, setPageIndex] = useState(0);
  const [total, setTotal] = useState<null|number>(null);
  useEffect(() => {
    if (downloadingState !== DownloadingState.Downloading) return;

    axiosInstance.get("/product", {params: {page: pageIndex}})
      .then((response) => {
        const data = response.data;
        const totalPagesArgh = Math.ceil(data.total / 10);
        setTotal(data.total);
        setProducts(products.concat(data.products));
        if (pageIndex >= totalPagesArgh-1) {
          setDownloadingState(DownloadingState.Finished);
        } else {
          setPageIndex(pageIndex + 1);
        }
      })
      .catch((err) => {
        setDownloadingState(DownloadingState.Outdated);
        console.error(err);
      })
    ;
  }, [pageIndex, downloadingState]);

  useEffect(() => {
    if (downloadingState === DownloadingState.Outdated) {
      setProducts([]);
    }
  }, [downloadingState]);

  const totalPages = total !== null ? Math.ceil(total / 10) : null;
  const pageIndexClamped = totalPages !== null ? Math.min(pageIndex, totalPages-1) : 0;

  const addModal = useRef<HTMLIonModalElement>(null);
  const inputQuantity = useRef<HTMLIonInputElement>(null);
  const [modalProductCode, setModalProductCode] = useState<null|number>(null);

  const [itemsIsReady, items, setItems] = makePreferenceable<Item[]>("items", []);
  const [toUploadIndices, setToUploadIndices] = useState<null|number[]>(null);
  const [toUploadIndex, setToUploadIndex] = useState<null|number>(null);

  useEffect(() => {
    (async () => {
      if (toUploadIndices === null) return;
      if (toUploadIndex === null) return;
    
      const finished = () => {
        const newToUploadIndex = toUploadIndex+1;
        setToUploadIndex(newToUploadIndex);
        if (newToUploadIndex >= toUploadIndices.length) {
          setToUploadIndex(null);
          setToUploadIndices(null);
        }
      };

      await delay(1000);

      const itemIndex = toUploadIndices[toUploadIndex];
      const item = items![toUploadIndices[toUploadIndex]];
      axiosInstance.post(
        "/item",
        {
          product_code: item.product_code,
          quantity: item.quantity,
        }
      ).then(() => {
        setItems(items!.toSpliced(itemIndex, 1, {...item, uploaded: true}));
        finished();
      }).catch(() => {
        finished();
      });
    })();
  }, [toUploadIndices, toUploadIndex]);

  // socket post book
  useEffect(() => {
    const handler = () => {
      setDownloadingState(DownloadingState.Outdated);
    };

    socket.on("products_changed", handler);

    return () => {
      socket.off("products_changed", handler);
    };
  }, [socket]);

  return (
    <IonPage>
      <IonHeader>
        {
          // <SharedToolbar
          //   setIsSettingsOpen={setIsSettingsOpen}
          //   jwt={jwt}
          //   setJwt={setJwt}
          //   isConnected={isConnected}
          // />
          // <IonToolbar>
          //   <IonSearchbar debounce={500} onIonInput={onSearchbarInput} value={queryFilter} />
          //   <IonSelect slot="end" onIonChange={onReadSelectChange}>
          //     <IonSelectOption value={null}>Any</IonSelectOption>
          //     <IonSelectOption value={true}>Read</IonSelectOption>
          //     <IonSelectOption value={false}>Unread</IonSelectOption>
          //   </IonSelect>
          // </IonToolbar>
        }
      </IonHeader>
      <IonContent fullscreen>

        <IonText>{
          "Downloading..."
            + (totalPages !== null ? (" " + (pageIndexClamped+1).toString() + "/" + totalPages.toString()) : "")}
        </IonText>

        <IonButton
          disabled={downloadingState !== DownloadingState.Outdated}
          onClick={() => {setPageIndex(0); setDownloadingState(DownloadingState.Downloading);}}
        >
          Download
        </IonButton>

        <IonSearchbar
          // debounce={10}
          debounce={2000}
          onIonInput={(event) => {
            let filter = event.target.value;
            if (typeof filter !== "string" || filter === "") {
              setFilteredProducts([]);
              return;
            }
            filter = filter.toLowerCase();

            // idiot typescript complaining if I don't do this
            const filterString: string = filter;
            const filteredProducts = (
              products.filter((product) => product.name.toLowerCase().includes(filterString))
              .slice(0, 5)
            );

            setFilteredProducts(filteredProducts);
          }}
        />

        <IonList>
          {
            filteredProducts.map((product) => (
              <IonItem
                key={product.code}
                onClick={() => {
                  addModal.current?.present();
                  setModalProductCode(product.code);
                }}
              >
                <IonLabel>
                  {product.name}
                </IonLabel>
              </IonItem>
            ))
          }
        </IonList>

        <IonModal
          ref={addModal}
          onWillDismiss={() => {
            setModalProductCode(null);
          }}
        >
          <IonInput ref={inputQuantity} type="number" />
          <IonButton onClick={() => {
            let value = inputQuantity.current?.value;
            if (typeof value === "string") {
              value = parseInt(value);
            }
            if (typeof value !== "number") return;
            if (value <= 0) return;

            if (modalProductCode === null) return;
            
            setItems(items!.concat([{product_code: modalProductCode, quantity: value, uploaded: false}]))
            
            addModal.current?.dismiss();
          }}>Add</IonButton>
        </IonModal>

        <IonFab slot="fixed" vertical="bottom" horizontal="end">
          <IonFabButton onClick={() => {}}>
            <IonIcon icon={add}></IonIcon>
          </IonFabButton>
        </IonFab>

        <IonButton
          onClick={() => {
            if (toUploadIndices !== null) return;
            if (toUploadIndex !== null) return;

            let newToUploadIndices = [];
            for (let i = 0; i < items!.length; ++i) {
              if (!items![i].uploaded) {
                newToUploadIndices.push(i);
              }
            }
            if (newToUploadIndices.length > 0) {
              setToUploadIndices(newToUploadIndices);
              setToUploadIndex(0);
            }
          }}
        >
          Upload
        </IonButton>

        {
          toUploadIndices === null || toUploadIndex === null ? null
          : (
            <IonText>{
              "Uploading... " + (toUploadIndex+1).toString() + "/" + toUploadIndices.length.toString()
            }</IonText>
          )
        }
        
        <IonList>
          {
            items!.map((item, index) => (
              <IonItem
                // key={item.code}
                key={index}
                onClick={() => {
                  
                }}
              >
                <IonLabel>
                  Code: {item.product_code}
                  <br/>Quantity: {item.quantity}
                  <br/>Uploaded: {item.uploaded ? "yes" : "no"}
                </IonLabel>
              </IonItem>
            ))
          }
        </IonList>

      </IonContent>
    </IonPage>
  );
};

export default Home;
