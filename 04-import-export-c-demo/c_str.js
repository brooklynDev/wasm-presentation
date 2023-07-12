const cstrlen = (mem, ptr) => {
    let len = 0;
    while (mem[ptr] != 0) {
        len++;
        ptr++;
    }
    return len;
}

const cStringByPointer = (mem_buffer, ptr) => {
    const mem = new Uint8Array(mem_buffer);
    const len = cstrlen(mem, ptr);
    const bytes = new Uint8Array(mem_buffer, ptr, len);
    return new TextDecoder().decode(bytes);
}

const getStringFromPointer = (instance, ptr) => {
    const {buffer} = instance.exports.memory;
    return cStringByPointer(buffer, ptr);
}

export default getStringFromPointer;