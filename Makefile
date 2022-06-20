all:
	mkdir -p build
	mkdir -p bin
	gcc -o build/panel.o src/panel.c -c -Wall
	gcc -o build/rsa_module.o src/rsa_module.c -c -Wall
	gcc -o build/md_module.o src/md_module.c -c -Wall
	gcc -o bin/mdrsa build/panel.o build/md_module.o build/rsa_module.o -lm -Wall
	rm -r build

clean:
	rm -r bin
