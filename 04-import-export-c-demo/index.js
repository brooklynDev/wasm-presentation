import loadWasm from './wasm-loader.js';
/*
import getStringFromPointer from './c_str.js';
*/

const wasmIntCallback = num => {
    console.log(`Got the following num from WASM: ${num}`);
}

const wasmStringCallback = str => {
    console.log(`Got the following string from WASM: ${str}`);
    /* 
    const string = getStringFromPointer(instance, str);
     console.log(`Got the following string from WASM: ${string}`);
     */
}

const instance = await loadWasm({
    js_func_with_int: wasmIntCallback,
    js_func_with_string: wasmStringCallback
});

const { add, func_that_will_call_js_with_int, func_that_will_call_js_with_string } = instance.exports;

document.getElementById('add').onclick = () => {
    const num1 = document.getElementById('num1').value;
    const num2 = document.getElementById('num2').value;
    const sum = add(+num1, +num2);
    console.log(sum);
}

document.getElementById('call-with-int').onclick = () => {
    func_that_will_call_js_with_int();
}

document.getElementById('call-with-string').onclick = () => {
    func_that_will_call_js_with_string();
}

