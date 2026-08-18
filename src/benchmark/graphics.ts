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

let data = [{"state":"CA","key":"Under 5 Years","population":2704659},{"state":"CA","key":"5 to 13 Years","population":4499890},{"state":"CA","key":"14 to 17 Years","population":2159981},{"state":"CA","key":"18 to 24 Years","population":3853788},{"state":"CA","key":"25 to 44 Years","population":10604510},{"state":"CA","key":"45 to 64 Years","population":8819342},{"state":"CA","key":"65 Years and Over","population":4114496},{"state":"TX","key":"Under 5 Years","population":2027307},{"state":"TX","key":"5 to 13 Years","population":3277946},{"state":"TX","key":"14 to 17 Years","population":1420518},{"state":"TX","key":"18 to 24 Years","population":2454721},{"state":"TX","key":"25 to 44 Years","population":7017731},{"state":"TX","key":"45 to 64 Years","population":5656528},{"state":"TX","key":"65 Years and Over","population":2472223},{"state":"NY","key":"Under 5 Years","population":1208495},{"state":"NY","key":"5 to 13 Years","population":2141490},{"state":"NY","key":"14 to 17 Years","population":1058031},{"state":"NY","key":"18 to 24 Years","population":1999120},{"state":"NY","key":"25 to 44 Years","population":5355235},{"state":"NY","key":"45 to 64 Years","population":5120254},{"state":"NY","key":"65 Years and Over","population":2607672},{"state":"FL","key":"Under 5 Years","population":1140516},{"state":"FL","key":"5 to 13 Years","population":1938695},{"state":"FL","key":"14 to 17 Years","population":925060},{"state":"FL","key":"18 to 24 Years","population":1607297},{"state":"FL","key":"25 to 44 Years","population":4782119},{"state":"FL","key":"45 to 64 Years","population":4746856},{"state":"FL","key":"65 Years and Over","population":3187797},{"state":"IL","key":"Under 5 Years","population":894368},{"state":"IL","key":"5 to 13 Years","population":1558919},{"state":"IL","key":"14 to 17 Years","population":725973},{"state":"IL","key":"18 to 24 Years","population":1311479},{"state":"IL","key":"25 to 44 Years","population":3596343},{"state":"IL","key":"45 to 64 Years","population":3239173},{"state":"IL","key":"65 Years and Over","population":1575308},{"state":"PA","key":"Under 5 Years","population":737462},{"state":"PA","key":"5 to 13 Years","population":1345341},{"state":"PA","key":"14 to 17 Years","population":679201},{"state":"PA","key":"18 to 24 Years","population":1203944},{"state":"PA","key":"25 to 44 Years","population":3157759},{"state":"PA","key":"45 to 64 Years","population":3414001},{"state":"PA","key":"65 Years and Over","population":1910571}]

const plot = await Plot.plot({
    document,
    width: 1920,
    height: 1080,

    x: { axis: null },
    y: { tickFormat: "s", grid: true },
    //fx: {label: "name"},
    color: { type: "categorical", scheme: "spectral" },
    marks: [
      Plot.barY(benchmark.benchmarks, {
        x: "aggregate_name",
        y: "real_time",
        fx: (m:BenchmarkData)=>`Window ${m.run_name.split("_").at(-1)}`,
        fill: "category",
       // sort: {x: null, color: null, fx: {value: "-y", reduce: "sum"}}
      }),

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