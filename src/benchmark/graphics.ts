import { DOMParser } from "npm:linkedom";
import * as Plot from "npm:@observablehq/plot"
import benchmark from "../../benchmark.json" with { type: "json" }

const document = new DOMParser().parseFromString("<!DOCTYPE html><html><head></head><body></body></html>", "text/html")

interface BenchmarkData {
      name: String,
      family_index: Number,
      per_family_instance_index: Number,
      run_name: String,
      run_type: String,
      repetitions: Number,
      threads: Number,
      aggregate_name: "mean" | "median" | "stddev" | "cv",
      aggregate_unit: String,
      iterations: Number,
      real_time: Number,
      cpu_time: Number,
      time_unit: String,
      label: String
}

interface Type {
  mean: BenchmarkData | undefined,
  median: BenchmarkData | undefined ,
  stddev: BenchmarkData | undefined,
  cv: BenchmarkData| undefined
}

const plot = await Plot.plot({
    document,
    width: 1920,
    height: 1080,
    marginTop: 70,

    x: { axis: null},// padding: 0.4
    y: { tickFormat: "s", grid: true, padding: 0.4},
    fx: { padding: 0.1 },
    color: { type: "categorical", scheme: "spectral" },
    marks: [
      Plot.barY(benchmark.benchmarks, {
        x: "aggregate_name",
        y: "real_time",
        fx: (m:BenchmarkData)=>`${m.run_name.split("_").at(1)}${m.run_name.split("_").at(-1)}`,
        fill: "aggregate_name",
        insertLeft: 4
       // sort: {x: null, color: null, fx: {value: "-y", reduce: "sum"}}
      }),
      Plot.text(benchmark.benchmarks, Plot.groupX({y: "sum", text: "first"}, {
         x: "aggregate_name",
         y: 1000,
         fx: (m:BenchmarkData)=>`${m.run_name.split("_").at(1)}${m.run_name.split("_").at(-1)}`,
         text: "aggregate_name",
         anchor: "bottom",
         dy: -6,
         rotate: -45,
         lineWidth: 20
      })),
      Plot.ruleY([0])
    ],

    style: {
        background: "white",
        color: "black",
        fontFamily: "system-ui, sans-serif",
        fontSize: "14px",
    },
})

plot.setAttribute("xmlns", "http://www.w3.org/2000/svg");
plot.setAttribute("xmlns:xlink", "http://www.w3.org/1999/xlink");

// Write only the clean SVG markup to file
Deno.writeTextFileSync("bar_chart.svg", plot.outerHTML);


//console.log(aggrated.map((m:Type)=>m.median?.real_time));
//console.log(aggrated.slice(0, 5));


// (m : Type)=>{m.mean?.real_time}