CC=clang

clean:
	rm -f public/main.wasm

build:
	$(CC) \
		--target=wasm32 \
		-std=c99 \
		-Wall \
		-nostdlib \
		-Wl,--export-dynamic \
		-Wl,--no-entry \
		-o web/main.wasm \
		wasm/main.c \
		-Wl,--allow-undefined
serve: clean build
	cd web; python3 -m http.server 8181
