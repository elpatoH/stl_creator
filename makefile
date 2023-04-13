generator: generator.c 3d.o 3d.h
	gcc -Wall -Werror -std=c11 -g generator.c 3d.o -o generator
3d.o: 3d.c 3d.h
	gcc -Wall -Werror -std=c11 -g -c 3d.c -o 3d.o
clean:
	rm -rf generator 3d.o ahi.stl ahi2.stl ahi3.stl ahi4.stl ahi5.stl perro