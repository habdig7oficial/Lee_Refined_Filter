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
      label: String,

      index: number,
      rotation: 1 | 0;
      seed: number,
      res: number
}

let data = benchmark.benchmarks.filter((m)=>{return m.aggregate_name != "stddev" &&  m.aggregate_name != "cv"}) 


let mean = benchmark.benchmarks.filter((m)=>{return m.aggregate_name == "mean"}) 
let stddev = benchmark.benchmarks.filter((m)=>{return m.aggregate_name == "stddev"}) 

type Bound = {
  upper: number,
  name: string,
  lower: number,
  aggregate_name: "mean" | "median" | "stddev" | "cv",
}

let bounds : Bound[] = Array.from({length: mean.length}, ()=>({aggregate_name: "mean"} as Bound))

for (let i = 0; i < bounds.length; i++) {
  let ix = stddev.findIndex((n)=> n.run_name == mean[i].run_name)
  bounds[i].lower = mean[i].real_time - stddev[ix].real_time
  bounds[i].upper = mean[i].real_time + stddev[ix].real_time

  bounds[i].name = `window ${mean[i].index} ${mean[i].rotation == 1? "" : "(R)"}`;
}

//domain: ["median", "mean", "lorem"]
const plot = await Plot.plot({
    document,
    width: 1920,
    height: 1080,
    marginTop: 50,
    marginBottom: 80,
    columns: ["median", "mean"],
    x: { padding: 0.1, align: 0.6, tickRotate: -45, },// padding: 0.4
    y: { tickFormat: "s", grid: true, padding: 0.4, label: "Seconds (ns)"},
    fx: { padding: 0.1, label: "", align: 0.5 },
    color: { type: "categorical", scheme: "observable10"},
    marks: [
      Plot.barY(data, {
        x: "aggregate_name",
        y1: 0,
        y2: "real_time",
        fx: (m:BenchmarkData)=>`window ${m.index} ${m.rotation == 1? "" : "(R)"}`,
        fill: "label",
        sort: { channel: "y2", order: "descending" },
       // sort: {x: null, color: null, fx: {value: "-y", reduce: "sum"}}
      }),
      /*Plot.text(data, Plot.groupX({y: "sum", text: "first"}, {
         x: "aggregate_name",
         y: "real_time",
         fx: (m:BenchmarkData)=>`window ${m.index} ${m.rotation == 1? "" : "(R)"}`,
         text: "aggregate_name",
         anchor: "bottom",
         rotate: -45,
         lineWidth: 20, 
      })),*/
      Plot.ruleX(["lorem"], bounds, {
          x: "aggregate_name",
          y1: "lower",
          y2: "upper",
          fx: "name",
          stroke: "black",
          dx: 30
      }),
      Plot.ruleY(bounds, {
          x: "aggregate_name",
          y: "lower",
          fx: "name",
          stroke: "black"
      }),
      Plot.ruleY(bounds, {
          x: "aggregate_name",
          y: "upper",
          fx: "name",
          stroke: "black"
      }),
      Plot.ruleY(bounds, {
          x: "aggregate_name",
          y: "upper",
          fx: "name",
          stroke: "black"
      }),
      Plot.ruleY([0])
    ],

    style: {
        background: "white",
        color: "black",
        fontFamily: "system-ui, sans-serif",
        fontSize: "14px",
        margin: "20px"
    },
})

plot.setAttribute("xmlns", "http://www.w3.org/2000/svg");
plot.setAttribute("xmlns:xlink", "http://www.w3.org/1999/xlink");

// Write only the clean SVG markup to file
Deno.writeTextFileSync("bar_chart.svg", plot.outerHTML);

// (m : Type)=>{m.mean?.real_time}

data.filter((m)=> console.log(m.aggregate_name));
