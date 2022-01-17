# WebAssembly-Module-for-Spectrrum-Analysis

## Background
WebAssembly (WASM) is an exciting new technology which aims to bring secure, portable and perfomant code to modern web-browsers. Being a low-level assembly-like language, WASM is not designed to be written by hand, but rather provides a compilation target for languages such as C, C++, and Rust. WASM code is loaded as modules into a JavaScript application, and accessed via the WebAssembly JavaScript API, which enables developers to use the flexibility of JavaScript and efficiency of WASM side-by-side.

The WASM module performs spectral analysis on satelite data. The WASM module is generated from MATLAB code (via a few transformation steps). A web-app is created to demonstrate the WASM module.
