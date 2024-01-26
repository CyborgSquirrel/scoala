import { ConnectionStatus, Network } from "@capacitor/network";
import { Dispatch, SetStateAction, useEffect, useMemo, useState } from "react";
import { Preferences } from "@capacitor/preferences";
import axios, { AxiosInstance } from "axios";
import { Socket, io } from "socket.io-client";
import { QueryClient } from "@tanstack/react-query";

export const serverHost = "http://localhost:3000";
export const queryClient = new QueryClient()

export interface MenuItem {
  code: number,
  name: string,
  // price: number,
}

export interface OrderItem {
  code: number,
  quantity: number,
}

export interface AxiosInstanceProps {
  baseUrl?: string,
  jwt?: string,
}

export const makeAxiosInstance = (props: AxiosInstanceProps): AxiosInstance => {
  let config: any = {
    baseURL: serverHost,
    headers: {},
  };

  // just in case let it get overwritten by the props here
  if (props.baseUrl !== undefined) {
    config.baseUrl = props.baseUrl;
  }

  if (props.jwt !== undefined) {
    config.headers = {
      "Authorization": " Bearer " + props.jwt,
      ...config.headers
    };
  }

  return axios.create(config);
}

export const delay = (delay_ms: number) => new Promise(resolve => setTimeout(resolve, delay_ms));

export const makeStorable = <T>(
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

// export const makeMapsApiKey = (): [string, Dispatch<SetStateAction<string>>] => {
//   return makeStorable(
//     "mapsApiKey",
//     "",
//     window.localStorage,
//   );
// };

export const makeJwt = (): [string|null, Dispatch<SetStateAction<string|null>>] => {
  return makeStorable<string|null>(
    "jwt",
    null,
    window.sessionStorage,
  );
};

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

export const useSocket = (): Socket => {
  // socket
  const [isSockConnected, setIsSockConnected] = useState(false);
  const [socket, setSocket] = useState(() => {
    return io(serverHost, { transports: ["websocket"] });
  });

  // socket update
  // useEffect(() => {
  //   setSocket(io(serverHost, { transports: ["websocket"] }));
  // }, [serverHost]);

  // socket connection state
  useEffect(() => {
    function onConnect() {
      setIsSockConnected(true);
    }

    function onDisconnect() {
      setIsSockConnected(false);
    }

    socket.on("connect", onConnect);
    socket.on("disconnect", onDisconnect);

    return () => {
      socket.off("connect", onConnect);
      socket.off("disconnect", onDisconnect);
    };
  }, [socket]);

  // socket jwt authentication
  // useEffect(() => {
  //   if (jwt === null) return;

  //   socket.emit("auth", { jwt_token: jwt });
  // }, [socket]);

  return socket;
};

export const makeMenu = (): [null|MenuItem[], Dispatch<SetStateAction<null|MenuItem[]>>] => {
  return makeStorable<null|MenuItem[]>(
    "menu",
    null,
    window.localStorage,
  );
};

export const makeItemQuantities = (): [{ [code: number]: number }, Dispatch<SetStateAction<{ [code: number]: number }>>] => {
  return makeStorable<{ [code: number]: number }>(
    "itemQuantities",
    {},
    window.localStorage,
  );
};
