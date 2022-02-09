import React, { useState, useEffect, useRef } from "react";
import Graph from './Graph';
import Wasm from "react-wasm";
import createModule from "./getFreqRep.mjs";
import logo from './logo.svg';
import './App.css';


function wrapGetFreqRep(Module) {
  // JS-friendly wrapper around the WASM call
  return function (inputData) {
    // multiplies two square matrices (as 2-D arrays) of the same size and returns the result
    const length = inputData.length;

    // set up input arrays with the input data -- remove holes if any
    const flatInputData = new Float32Array(inputData);

    const buffer = Module._malloc(
      flatInputData.length * flatInputData.BYTES_PER_ELEMENT
    );
    Module.HEAPF32.set(flatInputData, buffer >> 2);

    // allocate memory for the result array
    const resultBuffer = Module._malloc(
      flatInputData.length * flatInputData.BYTES_PER_ELEMENT
    );

    // make the call
    const resultPointer = Module.ccall(
      "getFreqRep",
      "number",
      ["number", "number"],
      [buffer, resultBuffer]
    );

    // get the data from the returned pointer into an flat array
    const result = [];
    for (let i = 0; i < length /** 2*/; i++) {
      result.push(
        Module.HEAPF32[resultPointer / Float32Array.BYTES_PER_ELEMENT + i]
      );
      //console.log(result[i]);
    }
    /**console.log('result pointer: ');
    console.log(resultPointer.length);
    console.log('result buffer: ');
    console.log(resultBuffer.length);*/
    Module._free(buffer);
    Module._free(resultBuffer);
    return result;
  };
}


/**
* @param {File|Blob} - file to slice
* @param {Number} - chunksAmount
* @return {Array} - an array of Blobs
**/
function sliceFile(file) {
  var byteIndex = 0;
  var chunks = [];

  var chunksAmount = file.size/(2048 * 4);

  for (var i = 0; i < chunksAmount; i += 1) {
    var byteEnd = Math.ceil((file.size / chunksAmount) * (i + 1));
    chunks.push(file.slice(byteIndex, byteEnd));
    byteIndex += (byteEnd - byteIndex);
  }

  return chunks;
}

function sqrtArr (arr) {
  return arr.map(function (x) {
    return Math.pow(x, 2);
  });
}

function App() {

  //var express = require('express');
  //console.log('***Express version: ', require('express/package').version);

  const [getFreqRep, setGetFreqRep] = useState();

  const [graphState, setGraphState] = useState(false);
  const [graphData, setGraphData] = useState([]);
  const [graphLen, setGraphLen] = useState(0);

  const [fftGraphState, setfftGraphState] = useState(false);
  const [fftGraphData, setfftGraphData] = useState([]);
  const [fftGraphLen, setfftGraphLen] = useState(0);

  const [iqRate, setIQRate] = useState(0);

  useEffect(
    // useEffect here is roughly equivalent to putting this in componentDidMount for a class component
    () => {
      createModule().then((Module) => {
        // need to use callback form (() => function) to ensure that `add` is set to the function
        // if you use setX(myModule.cwrap(...)) then React will try to set newX = myModule.cwrap(currentX), which is wrong
        setGetFreqRep(() => wrapGetFreqRep(Module));
      });
    },
    []
  );


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
      var lineWords;
      // By lines
      const allLines = buffer.split(/\r\n|\n/);
      // Reading line by line
      allLines.forEach((line) => {
          console.log(line);
          lineWords = line.split(' ');
          if (lineWords[0] == 'IQ'){
            setIQRate(parseInt(lineWords[3]));
          }
      });

    };

    reader.onerror = function() {
      console.log(reader.error);
      alert(reader.error);
    };
  }
  var clean_data;
  var dataCount = 0;
  const onChangeDataFile = (e) => {
    // `current` points to the mounted file input element
    var file = e.target.files[0];
    const reader = new FileReader();

    ////////////////////////////////////////////////////////////////////////////
    // Read file slices
    ////////////////////////////////////////////////////////////////////////////
    var fileChunks = sliceFile(file);
    var chuncksDensities = new Array(2048).fill(0);
    console.log(chuncksDensities);
    for (let k = 0; k < fileChunks.length; k++){
      const slicesReader = new FileReader();
      slicesReader.readAsArrayBuffer(fileChunks[k]);

      slicesReader.onload = function() {
        //console.log(reader.result);
        var buffer = slicesReader.result;
        var raw_data = new Int16Array(buffer);
        console.log("raw data length: " + raw_data.length);
        var raw_arr_size = raw_data.length;
        var clean_arr_size = 2048;//raw_arr_size/2;
        clean_data = new Float32Array/**Int16Array*/(clean_arr_size);
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
        var freq = getFreqRep( clean_data );

        //console.log("Chuck: " + k);
        let res = freq.map(x => ((x ** 2)/*/2048*/));
        var p = 0;
        for (let i = 0; i < res.length; i++){
          p += res[i]/2048;
        }
        //console.log(res);
        let normalized = res.map(x => (x/p));

        for (let i = 0; i < normalized.length; i++){
          chuncksDensities[i] += normalized[i];
        }
        //console.log(normalized);
      }
    }

/**
* Find the average
*/
    for (let i = 0; i < 2048; i++){
      let sum = chuncksDensities[i];
      chuncksDensities[i] = sum / fileChunks.length;
    }
////////////////////////////////////////////////////////////////////////////////
// End of file slicing
////////////////////////////////////////////////////////////////////////////////

    reader.readAsArrayBuffer(file);

    reader.onload = function() {
      //console.log(reader.result);
      var buffer = reader.result;
      var raw_data = new Int16Array(buffer);
      //console.log("raw data length: " + raw_data.length);
      var raw_arr_size = raw_data.length;
      var clean_arr_size = 2048;//raw_arr_size/2;
      clean_data = new Float32Array/**Int16Array*/(clean_arr_size);
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
      console.log('Clean data: ');
      console.log(clean_data);
      dataCount = clean_data.length;
      setGraphLen(dataCount);
      setGraphData(clean_data);
      setGraphState(true);
      //console.log(graphLen);


      const result = getFreqRep( clean_data );

      console.log('Chuckdensities data: ');
      console.log(/*result*/ chuncksDensities);

      setfftGraphLen(/**result*/chuncksDensities.length);
      setfftGraphData(/*result*/ chuncksDensities);
      setfftGraphState(true);


    };

    reader.onerror = function() {
      //console.log(reader.error);
      alert(reader.error);
    };


  };

/**
  if (!getFreqRep) {
    return "Loading webassembly...";
  }*/
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
            <button
              className="App-button"
              onClick={onConfigButtonClick}>
                Open configuration file
            </button>
            <button className="App-button" onClick={onDataButtonClick}>Open satellite data file</button>
            <button className="App-button" onClick={onProcessButtonClick}>Process data</button>
          </div>

            <Graph Type = "Time domain" Data={graphData} Count={graphLen} plotTitle="Real time signal"/>

            <Graph Type = "Frequency domain" Data={fftGraphData} Count={graphLen} IQrate={iqRate} plotTitle="Frequency representation of signal"/>

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
