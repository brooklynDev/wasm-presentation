all: clean main run

main:
	wat2wasm ./add.wat

run:
	python3 -m http.server 8181

clean:
	rm -f add.wasm