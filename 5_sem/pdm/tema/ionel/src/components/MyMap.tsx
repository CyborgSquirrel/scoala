import { GoogleMap } from "@capacitor/google-maps";
import { useEffect, useRef, useState } from "react";
import { Geolocation } from "@capacitor/geolocation";

interface MapProps {
  apiKey: string,

  markerLat: undefined|number,
  setMarkerLat: React.Dispatch<React.SetStateAction<undefined|number>>,

  markerLng: undefined|number,
  setMarkerLng: React.Dispatch<React.SetStateAction<undefined|number>>,
}

export const MyMap: React.FC<MapProps> = ({ apiKey, markerLat, setMarkerLat, markerLng, setMarkerLng }) => {
  const mapRef = useRef<HTMLElement>();

  const [newMap, setNewMap] = useState<undefined|GoogleMap>();

  useEffect(() => {
    (async () => {
      if (!mapRef.current) return;

      const position = await Geolocation.getCurrentPosition();
      setMarkerLat(position.coords.latitude);
      setMarkerLng(position.coords.longitude);

      const newMap = await GoogleMap.create({
        id: "my-cool-map",
        element: mapRef.current,
        apiKey: apiKey,
        forceCreate: true,
        config: {
          center: {
            lat: position.coords.latitude,
            lng: position.coords.longitude
          },
          zoom: 8,
        }
      });
      setNewMap(newMap);
      newMap.setOnMapClickListener((data) => {
        setMarkerLat(data.latitude);
        setMarkerLng(data.longitude);
      });
    })();
  }, [apiKey]);

  useEffect(() => {
    if (markerLat === undefined) return;
    if (markerLng === undefined) return;
    if (newMap === undefined) return;
    
    const markerIdPromise = newMap.addMarker({
      coordinate: { lat: markerLat, lng: markerLng },
    });

    return async () => {
      if (newMap === undefined) return;

      const markerId = await markerIdPromise;
      newMap.removeMarker(markerId);
    };
  }, [newMap, markerLat, markerLng])

  return (
    <div className="component-wrapper">
      <capacitor-google-map ref={mapRef} style={{
        display: "block",
        width: 300,
        height: 400
      }}></capacitor-google-map>
    </div>
  )
}

export default MyMap;
