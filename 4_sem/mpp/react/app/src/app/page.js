'use client';

import Image from 'next/image'
import styles from './page.module.css'
import {useState, useEffect, Component} from 'react'

const meciFieldNames = ['id', 'echipa1Id', 'echipa2Id', 'tip', 'numarLocuri', 'pretBilet'];
const meciTipOptions = ['Simplu', 'Semifinala1', 'Semifinala2', 'Finala'];

function MeciDelete({ meciuri, setMeciuri, getMeciuri, index }) {
  async function onDeleteClick() {
    const delete_ = async () => {
      const response = await fetch(
        `http://localhost:8080/app/meci/${meciuri[index]['id']}`,
        {
          method: 'DELETE',
          headers: {
            'Content-Type': 'application/json',
          }
        }
      );
    };
    await delete_();
    getMeciuri();
  }

  return (
    <div>
      <input type="button" value="Delete" onClick={onDeleteClick}/>
    </div>
  );
}

function MeciSelectField({ meciuri, setMeciuri, getMeciuri, index, fieldName, options }) {
  const [isEditing, setIsEditing] = useState(false);
  const [inputValue, setInputValue] = useState(meciuri[index][fieldName]);

  useEffect(() => {
    let newFieldValue = {
      ...meciuri[index]
    };

    const put = async () => {
      const response = await fetch(
        `http://localhost:8080/app/meci/${newFieldValue['id']}`,
        {
          method: 'PUT',
          body: JSON.stringify(newFieldValue),
          headers: {
            'Content-Type': 'application/json',
          }
        }
      ).then((response) => response.json());
    };
    
    if (isEditing) {
      setInputValue(meciuri[index][fieldName]);
    } else {
      if (inputValue !== meciuri[index][fieldName]) {
        setMeciuri(prevState => {
          newFieldValue[fieldName] = inputValue;
          let newMeciuri = meciuri.slice(0, index).concat([newFieldValue]).concat(meciuri.slice(index+1));
          return newMeciuri;
        });
        put(newFieldValue);
        getMeciuri();
      }
    }
  }, [isEditing]);

  function onInputChange(event) {
    setInputValue(event.target.value);
    setIsEditing(false);
  }

  const optionTags = options.map(option => <option key={option} value={option}>{option}</option>);
  
  return (
    <div>
      {
        !isEditing
        ?
        <div onDoubleClick={() => setIsEditing(true)}>{meciuri[index][fieldName]}</div>
        :
        <select value={inputValue} onChange={onInputChange}>{optionTags}</select>
      }
    </div>
  )
}

function MeciTextField({ meciuri, setMeciuri, getMeciuri, index, fieldName }) {
  const [isEditing, setIsEditing] = useState(false);
  const [inputValue, setInputValue] = useState(meciuri[index][fieldName]);

  useEffect(() => {
    let newFieldValue = {
      ...meciuri[index]
    };

    const put = async () => {
      const response = await fetch(
        `http://localhost:8080/app/meci/${newFieldValue['id']}`,
        {
          method: 'PUT',
          body: JSON.stringify(newFieldValue),
          headers: {
            'Content-Type': 'application/json',
          }
        }
      ).then((response) => response.json());
    };
    
    if (isEditing) {
      setInputValue(meciuri[index][fieldName]);
    } else {
      if (inputValue !== meciuri[index][fieldName]) {
        setMeciuri(prevState => {
          newFieldValue[fieldName] = inputValue;
          let newMeciuri = meciuri.slice(0, index).concat([newFieldValue]).concat(meciuri.slice(index+1));
          return newMeciuri;
        });
        put(newFieldValue);
        getMeciuri();
      }
    }
  }, [isEditing]);

  function onInputKeyPress(event) {
    if (event.code === 'Enter') {
      setIsEditing(false);
    }
  }

  function onInputChange(event) {
    setInputValue(event.target.value);
  }
  
  return (
    <div>
      {
        !isEditing
        ?
        <div onDoubleClick={() => setIsEditing(true)}>{meciuri[index][fieldName]}</div>
        :
        <input type="text" value={inputValue} onKeyPress={onInputKeyPress} onChange={onInputChange} />
      }
    </div>
  )
}

function Meci({ meciuri, setMeciuri, index, getMeciuri }) {
  return [
    <div key="id">{meciuri[index]["id"]}</div>,
    <div key="echipa1Id">{meciuri[index]["echipa1Id"]}</div>,
    <div key="echipa2Id">{meciuri[index]["echipa2Id"]}</div>,
    <MeciSelectField key="tip" meciuri={meciuri} setMeciuri={setMeciuri} getMeciuri={getMeciuri} index={index} fieldName="tip" options={meciTipOptions}></MeciSelectField>,
    <MeciTextField key="numarLocuri" meciuri={meciuri} setMeciuri={setMeciuri} getMeciuri={getMeciuri} index={index} fieldName="numarLocuri"></MeciTextField>,
    <MeciTextField key="pretBilet" meciuri={meciuri} setMeciuri={setMeciuri} getMeciuri={getMeciuri} index={index} fieldName="pretBilet"></MeciTextField>,
    <MeciDelete key="delete" meciuri={meciuri} setMeciuri={setMeciuri} getMeciuri={getMeciuri} index={index}></MeciDelete>,
  ];
}

function MeciTable({ meciuri, setMeciuri, getMeciuri }) {
  const style = {
    display: 'grid',
    'grid-template-columns': 'auto auto auto auto auto auto auto',
  };

  const header = meciFieldNames.concat("").map(fieldName => <div>{fieldName}</div>);
  const items = meciuri.map((meci, index) => {
    return <Meci key={meci.id} meciuri={meciuri} setMeciuri={setMeciuri} getMeciuri={getMeciuri} index={index}></Meci>;
  });

  return (
    <div style={style}>
      {header}
      {items}
    </div>
  );
}

function MeciCreate({ getMeciuri }) {
  const [echipa1Id, setEchipa1Id] = useState(0);
  const [echipa2Id, setEchipa2Id] = useState(0);
  const [tip, setTip] = useState(meciTipOptions[0]);
  const [numarLocuri, setNumarLocuri] = useState(10);
  const [pretBilet, setPretBilet] = useState(2.5);
  
  const optionTags = meciTipOptions.map(option => <option key={option} value={option}>{option}</option>);

  const style = {
    display: 'grid',
    width: '40ch', 'grid-template-columns': 'auto',
    'grid-template-rows': 'auto auto auto auto auto',
  };

  async function onSubmitClick(event) {
    const meci = {
      echipa1Id: echipa1Id,
      echipa2Id: echipa2Id,
      tip: tip,
      numarLocuri: numarLocuri,
      pretBilet: pretBilet,
    };
    
    const post = async () => {
      const response = await fetch(
        'http://localhost:8080/app/meci/',
        {
          method: 'POST',
          body: JSON.stringify(meci),
          headers: {
            'Content-Type': 'application/json',
          }
        }
      ).then((response) => response.json());
      getMeciuri();
    };

    await post();
  }

  return (
    <div style={style}>
      <label>
        Echipa 1 Id
        <input type="number" value={echipa1Id} onChange={(event) => setEchipa1Id(event.target.value)}/>
      </label>
      <label>
        Echipa 2 Id
        <input type="number" value={echipa2Id} onChange={(event) => setEchipa2Id(event.target.value)}/>
      </label>
      <label>
        Tip
        <select value={tip} onChange={(event) => setTip(event.target.value)}>{optionTags}</select>
      </label>
      <label>
        Numar Locuri
        <input type="number" value={numarLocuri} onChange={(event) => setNumarLocuri(event.target.value)}/>
      </label>
      <label>
        Pret Bilet
        <input type="number" value={pretBilet} onChange={(event) => setPretBilet(event.target.value)}/>
      </label>
      <input type="button" value="Submit" onClick={onSubmitClick}/>
    </div>
  );
}

export default function Home() {
  const [meciuri, setMeciuri] = useState([]);

  const getMeciuri = async () => {
    const response = await fetch(
      'http://localhost:8080/app/meci'
    ).then((response) => response.json());

    setMeciuri(response);
  };

  useEffect(() => {
    getMeciuri ();
  }, []);

  return (
    <main>
      <MeciCreate getMeciuri={getMeciuri}></MeciCreate>
      <MeciTable meciuri={meciuri} setMeciuri={setMeciuri} getMeciuri={getMeciuri}></MeciTable>
    </main>
  )
}
