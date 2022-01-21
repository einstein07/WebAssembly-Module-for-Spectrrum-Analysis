import React, { useState, useEffect, useRef } from "react";
import Graph from './Graph';
import logo from './logo.svg';
import './App.css';



function App() {

  const [graphState, setGraphState] = useState(false);
  const [graphData, setGraphData] = useState([]);
  const [graphLen, setGraphLen] = useState(0);



  const dataInputFile = useRef(null);
  const onDataButtonClick = () => {
    // `current` points to the mounted file input element
   dataInputFile.current.click();
  };

  const configInputFile = useRef(null);
  const onConfigButtonClick = () => {
    // `current` points to the mounted file input element
   configInputFile.current.click();
  };

  const onProcessButtonClick = () => {
    // `current` points to the mounted file input element


  };


  const onChangeConfigFile = (e) => {
    // `current` points to the mounted file input element
    var file = e.target.files[0];
    const reader = new FileReader();

    reader.readAsText(file);

    reader.onload = function() {
      //console.log(reader.result);
      var buffer = reader.result;
      console.log(buffer);
    };
  }
  var clean_data;
  var dataCount = 0;
  const onChangeDataFile = (e) => {
    // `current` points to the mounted file input element
    var file = e.target.files[0];
    const reader = new FileReader();

    reader.readAsArrayBuffer(file);

    reader.onload = function() {
      //console.log(reader.result);
      var buffer = reader.result;
      var raw_data = new Int16Array(buffer);
      //console.log(raw_data);
      var raw_arr_size = raw_data.length;
      var clean_arr_size = raw_arr_size/2;
      clean_data = new Int16Array(clean_arr_size);
      /***
        Remove quadrature components
      */
      let i_val = 0;
      let index = 0;
      for (let i = 0; i < raw_arr_size; i++) {
        if (i_val == 0 && index < clean_arr_size ){
          clean_data[index] = raw_data[i];
          index += 1;
          i_val = 1;
        }
        else{
          i_val = 0;
        }
      }
      dataCount = clean_data.length;
      setGraphLen(dataCount);
      setGraphData(clean_data);
      setGraphState(true);
    };

    reader.onerror = function() {
      console.log(reader.error);
    };


  };


  if (graphState){
    return (
      <div className="App">
        <header className="App-header">
          <h1> WebAssembly Module for Spectrum Analysis</h1>
        </header>

        <div className="App-content">

          < input type="file"
            id="dataFileElem"
            ref={dataInputFile}
            onChange={onChangeDataFile}
            accept=".bin"
            style={{display:'none'}}
            />

          < input type="file"
            id="configFileElem"
            ref={configInputFile}
            onChange={onChangeConfigFile}
            accept=".ini"
            style={{display:'none'}}
            />

          <div className="App-button-container">
            <button className="App-button" onClick={onConfigButtonClick}>Open configuration file</button>
            <button className="App-button" onClick={onDataButtonClick}>Open satellite data file</button>
            <button className="App-button" onClick={onProcessButtonClick}>Process data</button>
          </div>

          <Graph Data={graphData} Count={graphLen}/>

        </div>
      </div>
    );
  }
  else{
    return (
      <div className="App">
        <header className="App-header">
          <h1> WebAssembly Module for Spectrum Analysis</h1>
        </header>

        <div className="App-content">

          < input type="file"
            id="dataFileElem"
            ref={dataInputFile}
            onChange={onChangeDataFile}
            accept=".bin"
            style={{display:'none'}}
            />

          < input type="file"
            id="configFileElem"
            ref={configInputFile}
            onChange={onChangeConfigFile}
            accept=".ini"
            style={{display:'none'}}
            />

          <div className="App-button-container">
            <button className="App-button" onClick={onConfigButtonClick}>Open configuration file</button>
            <button className="App-button" onClick={onDataButtonClick}>Open satellite data file</button>
            <button className="App-button" onClick={onProcessButtonClick}>Process data</button>
          </div>

          {graphState}

        </div>
      </div>
    );
  }

}

export default App;
