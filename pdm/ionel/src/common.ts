import { ConnectionStatus, Network } from "@capacitor/network";
import { Dispatch, SetStateAction, useEffect, useMemo, useState } from "react";
import { Book, bookToServer } from "./components/BookItem";
import { Preferences } from "@capacitor/preferences";

/*

=============================================
            THE REACT MANIFESTO             
=============================================

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
<<< EMBRACE THE PROP DRILLING <<<<<<<<<<<<<<<
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
>>>>>>>>>>>>>>>>>>>> CEASE RESISTING >>>>>>>>
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
<<<<<< SUCCUMB TO THE MACHINE <<<<<<<<<<<<<<<
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

*/

export class Fetcher {
  host: string;
  jwt: string;

  constructor(host: string, jwt: string) {
    this.host = host;
    this.jwt = jwt;
  }

  fetch(path: string, init?: RequestInit): Promise<Response> {
    return fetch(
      this.host + path,
      {
        ...init,
        ...{
          headers: {
            ...init?.headers,
            ...makeJwtHeaders(this.jwt),
          }
        }
      }
    )
  }
}

export const delay = (delay_ms: number) => new Promise(resolve => setTimeout(resolve, delay_ms));

export const postBook = (serverHost: string, jwt: string, book: Book): undefined|Promise<Response> => {
  if (serverHost === "") return;

  return fetch(
    `${serverHost}/book`,
    {
      method: "POST",
      body: JSON.stringify(bookToServer(book)),
      headers: {
        ...makeJwtHeaders(jwt),
      },
    },
  );
};

export const putBookImage = async (serverHost: string, jwt: string, bookId: number, image: string): Promise<undefined|Response> => {
  if (serverHost === "") return;

  const imageResponse = await fetch(
    image,
    {
      method: "GET",
    }
  );
  const imageBlob = await imageResponse.blob();

  const formData = new FormData();
  formData.append("image", imageBlob);

  return fetch(
    `${serverHost}/book/image/${bookId}`,
    {
      method: "PUT",
      body: formData,
      headers: {
        ...makeJwtHeaders(jwt),
      },
    }
  );
};

const makeStorable = <T>(
  name: string,
  defaultValue: T,
  storage: Storage,
): [T, Dispatch<SetStateAction<T>>] => {
  const [value, setValue] = useState<T>(() => {
    let storageValue = storage.getItem(name);
    if (storageValue === null || storageValue === undefined) {
      return defaultValue;
    }
    
    try {
      return JSON.parse(storageValue);
    } catch {
      // if it gets here, that means something really went south...
      return defaultValue;
    }
  });

  useEffect(() => {
    storage.setItem(name, JSON.stringify(value));
  }, [value]);

  return [value, setValue];
};

export const makePreferenceable = <T>(
  name: string,
  defaultValue?: T,
): [boolean, undefined|T, Dispatch<SetStateAction<undefined|T>>] => {
  const [value, setValue] = useState<undefined|T>(defaultValue);
  const [isReady, setIsReady] = useState(false);
    
  useEffect(() => {
    (async () => {
      const storageValue = (await Preferences.get({ key: name })).value;
      if (storageValue === null) {
        setIsReady(true);
        return;
      }

      try {
        setValue(JSON.parse(storageValue));
      } catch {
        // if it gets here, that means something really went south...
        console.error("Couldn't parse preferences");
      }
      setIsReady(true);
    })();
  }, []);

  useEffect(() => {
    if (isReady) {
      (async () => {
        await Preferences.set({ key: name, value: JSON.stringify(value) })
      })();
    }
  }, [value]);

  return [isReady, value, setValue];
};

export const makeServerHost = (): [string, Dispatch<SetStateAction<string>>] => {
  return makeStorable(
    "serverHost",
    "",
    window.localStorage,
  );
};

export const makeMapsApiKey = (): [string, Dispatch<SetStateAction<string>>] => {
  return makeStorable(
    "mapsApiKey",
    "",
    window.localStorage,
  );
};

export const makeJwt = (): [string|null, Dispatch<SetStateAction<string|null>>] => {
  return makeStorable<string|null>(
    "jwt",
    null,
    window.sessionStorage,
  );
};

export const makeJwtHeaders = (jwt: string): any => {
  return {
    "Authorization": " Bearer " + jwt,
  };
}

export const makeIsConnected = () => {
  const [networkStatus, setNetworkStatus] = useState<null|ConnectionStatus>(null);

  useEffect(() => {(
    Network.getStatus()
    .then((status) => {
      setNetworkStatus(status);
    })
  )}, []);

  useEffect(() => {
    let handle = Network.addListener("networkStatusChange", (status) => {
      setNetworkStatus(status);
    });
    return () => {
      handle.then((handle) => {
        handle.remove();
      });
    };
  }, []);

  const isConnected = useMemo(() => {
    if (networkStatus === null) return false;
    return networkStatus.connected;
  }, [networkStatus]);

  return isConnected
};
