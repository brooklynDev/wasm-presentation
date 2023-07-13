.PHONY: all run clean

all: clean main.wasm run

main.wasm: main.c
	@clang --target=wasm32 -nostdlib -Wl,--no-entry -Wl,--export-dynamic -Wl,--allow-undefined -o main.wasm main.c

run: main.wasm
	@wasmtime main.wasm --invoke hello_world

clean:
	@rm -f main.wasm
