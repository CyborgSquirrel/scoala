import { GoogleMap } from "@capacitor/google-maps";
import { useEffect, useRef, useState } from "react";

interface MapProps {
  apiKey: string,

  markerLat: number,
  markerLng: number,
}

export const ShowMap: React.FC<MapProps> = ({ apiKey, markerLat, markerLng }) => {
  const mapRef = useRef<HTMLElement>();

  const [newMap, setNewMap] = useState<undefined|GoogleMap>();

  useEffect(() => {
    (async () => {
      if (!mapRef.current) return;

      const newMap = await GoogleMap.create({
        id: "show-map",
        element: mapRef.current,
        apiKey: apiKey,
        forceCreate: true,
        config: {
          center: {
            lat: markerLat,
            lng: markerLng
          },
          zoom: 8,
        }
      });
      setNewMap(newMap);
      newMap.addMarker({
        coordinate: {
          lat: markerLat,
          lng: markerLng,
        }
      })
    })();
  }, [apiKey]);

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

export default ShowMap;
