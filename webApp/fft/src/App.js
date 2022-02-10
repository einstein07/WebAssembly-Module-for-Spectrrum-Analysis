import React, { useState, useEffect, useRef } from "react";
import Graph from './Graph';
import Wasm from "react-wasm";
import createModule from "./getFreqRep.mjs";
import logo from './logo.svg';
import './App.css';
import './IniFileConfig';
import {IniFileConfig, parseINIString} from './IniFileConfig'

/**
* @param {Module}
* @return {Array} - an array of fft values
**/
function wrapGetFreqRep(Module) {
  // JS-friendly wrapper around the WASM call
  return function (inputData) {
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
    for (let i = 0; i < length; i++) {
      result.push(
        Module.HEAPF32[resultPointer / Float32Array.BYTES_PER_ELEMENT + i]
      );
    }
    // Release memory
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

function App() {

  //////////////////////////////////////////////////////////////////////////////
  // States and variables
  //////////////////////////////////////////////////////////////////////////////
  const [processingState, setProcessingState] = useState(true);

  const CHUNK_SAMPLE_SIZE = 4096; // number of samples per chunk
  const [iniConfig, setIniConfig] = useState(new IniFileConfig);

  const [getFreqRep, setGetFreqRep] = useState();

  const [graphState, setGraphState] = useState(false);
  const [graphData, setGraphData] = useState([]);
  const [graphLen, setGraphLen] = useState(0);

  const [fftGraphState, setfftGraphState] = useState(false);
  const [fftGraphData, setfftGraphData] = useState([]);
  const [fftGraphLen, setfftGraphLen] = useState(0);

  const [iqRate, setIQRate] = useState(0);

  var file;
  var clean_data;
  var dataCount = 0;

  var fileChunks;
  // Holds time domain power densities for all chuncks
  var timeChunckDensities = new Array(2048).fill(0);
  // Holds frequency power densities for all chuncks
  var chuncksDensities = new Array(2048).fill(0);
  //////////////////////////////////////////////////////////////////////////////
  useEffect(
    // useEffect here is roughly equivalent to putting this in componentDidMount
    // for a class component
    () => {
      createModule().then((Module) => {
        // need to use callback form (() => function) to ensure that `add` is
        // set to the function if you use setX(myModule.cwrap(...)) then React
        // will try to set newX = myModule.cwrap(currentX), which is wrong
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
    ////////////////////////////////////////////////////////////////////////////
    // Process satallite data and plot signal power graphs - i.e. time and
    // frequency domains
    ////////////////////////////////////////////////////////////////////////////
    setProcessingState(false);
    var Ts = 1/iqRate;
    for (let k = 0; k < 1000 /**Limit number of chuncks to 1000 for testing purposes*/; k++){

      const slicesReader = new FileReader();
      slicesReader.readAsArrayBuffer(fileChunks[k]);

      slicesReader.onload = function() {
        var buffer = slicesReader.result;
        var raw_data = new Int16Array(buffer);
        var raw_arr_size = raw_data.length;
        var clean_arr_size = 2048;
        clean_data = new Float32Array(clean_arr_size);
        /*********************************************
          Remove quadrature components
        *********************************************/
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
        /*********************************************
          Call wasm - compute fft
        *********************************************/
        var twasm0 = performance.now();
        var freq = getFreqRep( clean_data );
        var twasm1 = performance.now();
        console.log("Call to fft wasm module took " + (twasm1 - twasm0) + " milliseconds.");
        var fft = require('fft-js').fft;
        var t0 = performance.now();
        var phasors = fft(clean_data);
        var t1 = performance.now();
        console.log("Call to fft javascript module took " + (t1 - t0) + " milliseconds.");

        /*********************************************
          Estimate power density
        *********************************************/
        let timePowDensity = clean_data.map(x => (((x** 2) * Ts)));

        let Sxx = freq.map(x => ((x ** 2)));
        var Px = 0;

        let Px_n = 0;
        for (let i = 0; i < Sxx.length; i++){
          Px += Sxx[i]/2048;

          let n = 1;
          Px_n += timePowDensity[i];
          n = n + i;
          timeChunckDensities[i] += Px_n/(n * Ts);
        }
        let normalized = Sxx.map(x => (x/Px));

        for (let i = 0; i < normalized.length; i++){
          chuncksDensities[i] += normalized[i];
        }

        if ( k == (/**fileChunks.length*/1000-1)){
          setProcessingState(true);
          /*********************************************
            Find the average
          *********************************************/
          for (let i = 0; i < 2048; i++){
            let sum = chuncksDensities[i];
            chuncksDensities[i] = sum / /**fileChunks.length*/1000;
            timeChunckDensities[i] = timeChunckDensities[i]/1000/*fileChunks.length*/;
          }

          /*********************************************
            Set data to graph signal power in time domain
          *********************************************/
          setGraphLen(timeChunckDensities.length);
          setGraphData(timeChunckDensities);
          setGraphState(true);
          /*********************************************
            Set data to graph signal power in frequency domain
          *********************************************/
          setfftGraphLen(chuncksDensities.length);
          setfftGraphData(chuncksDensities);
          setfftGraphState(true);
        }
      }
    }
  };


  const onChangeConfigFile = (e) => {
    // `current` points to the mounted file input element

    var file = e.target.files[0];
    const reader = new FileReader();

    reader.readAsText(file);

    reader.onload = function() {
      var buffer = reader.result;
      var lineWords;
      // By lines
      const allLines = buffer.split(/\r\n|\n/);
      // Reading line by line
      allLines.forEach((line) => {
          lineWords = line.split(' ');
          if (lineWords[0] == 'IQ'){
            setIQRate(parseInt(lineWords[3]));
          }
      });
      setIniConfig(parseINIString(buffer));
      alert("Config file read successfully!");
    };

    };



  const onChangeDataFile = (e) => {
    ////////////////////////////////////////////////////////////////////////////
    // Read file slices
    ////////////////////////////////////////////////////////////////////////////

    file = e.target.files[0];
    const reader = new FileReader();

    fileChunks = sliceFile(file);

    alert("Satellite data read successfully!");
    ////////////////////////////////////////////////////////////////////////////
    // End of file slicing
    ////////////////////////////////////////////////////////////////////////////

  };


  if (!processingState) {
    return (
      <div className="App">
        <header className="App-header">
          <h1> WebAssembly Module for Spectrum Analysis</h1>
          <h4> Processing data. . . </h4>
        </header>
      </div>
      );
  }
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

            <Graph Type = "Time domain" Data={graphData} Count={graphLen} plotTitle="Signal power in time domain (averaged across all chunks)"/>

            <Graph Type = "Frequency domain" Data={fftGraphData} Count={graphLen} IQrate={iqRate} plotTitle="Signal power in frequency domain (averaged acrosss all chunks)"/>

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
