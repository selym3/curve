# all:
	# clang++ src/curve.cpp -c -o bin/curve.o
	# clang++ src/vec2.cpp -c -o bin/vec2.o
	# clang++ main.cpp bin/curve.o bin/vec2.o -lm -o main

compile:
	clang++ src/curve.cpp -c -o bin/curve.o
	clang++ src/vec2.cpp -c -o bin/vec2.o

main: compile
	clang++ main.cpp bin/curve.o bin/vec2.o -lm -o main

gui: compile
	clang++ gui.cpp bin/curve.o bin/vec2.o -lm -lSDL2 -o gui