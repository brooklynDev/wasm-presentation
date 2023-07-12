const loadWasm = async (env) => {
    const { instance } = await WebAssembly.instantiateStreaming(
        fetch("/main.wasm"),
        {
            env
        }
    );

    return instance;
}

export default loadWasm;