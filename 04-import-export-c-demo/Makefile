CC=clang

clean:
	rm -f main.wasm

build:
	$(CC) \
		--target=wasm32 \
		-std=c99 \
		-Wall \
		-nostdlib \
		-Wl,--export-dynamic \
		-Wl,--no-entry \
		-o main.wasm \
		main.c \
		-Wl,--allow-undefined
serve: clean build
	cd web; python3 -m http.server 8181
