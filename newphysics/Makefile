all: compile link
compile:
	g++ -c -O3 main.cpp -lsfml-window -lsfml-graphics -lsfml-system -DSFML_STATIC
	g++ -c -O3 mainphysics.cpp
	g++ -c -O3 broadet.cpp
	g++ -c -O3 constraints.cpp
	g++ -c -O3 render.cpp -lsfml-window -lsfml-graphics -lsfml-system -DSFML_STATIC
	g++ -c -O3 solving.cpp
	g++ -c -O3 vectors.cpp
	g++ -c -O3 config.cpp
link:
	g++ main.o -o teststststsz.exe  mainphysics.o broadet.o constraints.o config.o render.o solving.o structs.hpp vectors.o -lsfml-window-s -lsfml-graphics-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -static-libgcc -static-libstdc++ -static