generator: generator.c 3d.o 3d.h
	gcc -Wall -Werror -std=c11 -g generator.c 3d.o -o generator
3d.o: 3d.c 3d.h
	gcc -Wall -Werror -std=c11 -g -c 3d.c
clean:
	rm -rf generator 3d.o output.stl chetos.stl perro.exe sphere.stl