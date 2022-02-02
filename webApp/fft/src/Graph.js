import React from "react";
import Plot from "react-plotly.js";

function Graph (props) {
  var x_axis = new Array(2048/**100000*/);
  var y_axis = new Array(2048/**100000*/);
  console.log("Processing data. . .")
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
            marker: { color: "red" },
          }
        ]}
        layout={{ width: 1500, height: 800, title: props.plotTitle }}
      />
    );
}

export default Graph;
