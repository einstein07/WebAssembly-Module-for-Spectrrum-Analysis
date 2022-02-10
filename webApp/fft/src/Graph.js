import React from "react";
import Plot from "react-plotly.js";

function makeArr(startValue, stopValue, cardinality) {
  var arr = [];
  var step = (stopValue - startValue) / (cardinality - 1);
  for (var i = 0; i < cardinality; i++) {
    arr.push(startValue + (step * i));
  }
  return arr;
}
function Graph (props) {
  var x_axis = new Array(2048/**100000*/);
  var y_axis = new Array(2048/**100000*/);
  console.log("Processing data. . .")
  if (props.Type == 'Time domain'){
    for ( var i = 0 ; i < 2048/**100000*/ ; i++ ) {
        x_axis[i] = i;
        y_axis[i] = props.Data[i];
    }
    console.log("Plotting data. . .");
      return (
        <Plot
          data={[
            {
              x: x_axis,
              y: y_axis,
              type: "scatter",
              mode: "lines+markers",
              marker: { color: "blue" },
            }
          ]}
          layout={
            {
              width: 1000,
              height: 800,
              title: {
                text: props.plotTitle,
                font: {color:'blue', family: 'Courier New, monospace', size: 24}
              },
              xaxis: {
                title:{
                  text: 'Samples used to estimate power',
                  font: {
                    family: 'Courier New, monospace',
                    size: 18,
                    color: 'blue'
                  }
                }
              },
              yaxis: {
                title:{
                  text: 'Magnitude',
                  font: {
                    family: 'Courier New, monospace',
                    size: 18,
                    color: 'blue'
                  }
                }
              }
            }
          }
        />
      );
  }
  else if (props.Type == 'Frequency domain'){
    var linspace = makeArr(0, 1, 2048/**props.Count*/);
    for ( var i = 0 ; i < 2048/**100000*/ ; i++ ) {
        x_axis[i] = (props.IQrate/2) * linspace[i];
        y_axis[i] = props.Data[i];
    }
    console.log(props.IQrate);
    console.log("Plotting data. . .");
      return (
        <Plot
          data={[
            {
              x: x_axis,
              y: y_axis,
              type: "scatter",
              mode: "lines+markers",
              marker: { color: "red" },
            }
          ]}
          layout={
            {
              width: 1000,
              height: 800,
              title: {
                text: props.plotTitle,
                font: {color:'red', family: 'Courier New, monospace', size: 24}
              },
              xaxis: {
                title:{
                  text: 'Frequency (Hz)',
                  font: {
                    family: 'Courier New, monospace',
                    size: 18,
                    color: 'red'
                  }
                }
              },
              yaxis: {
                title:{
                  text: 'Magnitude',
                  font: {
                    family: 'Courier New, monospace',
                    size: 18,
                    color: 'red'
                  }
                }
              }
            }
          }
            //{yaxis: {
            //  title: {
            //    text: 'y Axis',
            //    font: {
            //      family: 'Courier New, monospace',
            //      size: 18,
            //      color: '#7f7f7f'
            //    }
            //  }
            //}
            //},
            //{xaxis: {
            //    title: {
            //      text: 'Frequency (Hz)',
            //      font: {
            //        family: 'Courier New, monospace',
            //        size: 18,
            //        color: 'blue'
            //      }
            //    }
            //  }
            //},
            //{title: {
            //  text: props.plotTitle,
            //  font: {
            //    color:'red',
            //    family: 'Courier New, monospace',
            //    size: 24
            //  }
            //}
            //}
            //}
        />
      );
  }

}

export default Graph;
