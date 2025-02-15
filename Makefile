main: scripts/main.cpp
	g++ scripts/main.cpp scripts/map.cpp -o game.exe -O1 -Wall -Wno-missing-braces -Iinclude/ -Llib/ -lraylib -lopengl32 -lgdi32 -lwinmm