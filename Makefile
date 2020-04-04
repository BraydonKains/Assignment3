C=g++
CFLAGS=
LDFLAGS=-L/usr/lib -lallegro -lallegro_font -lallegro_image -lallegro_acodec -lallegro_audio -lallegro_primitives
INCLUDE=-I. -I/usr/include/allegro5

OBJS=main.o
SCREEN_OBJS=start_screen.o game_screen.o help_screen.o result_screen.o
G_OBJS=game.o cursor.o ship.o object_manager.o star.o bullet.o
OUT=main

all: main_game

clean:
	rm -rf *.o $(OUT)

main_game: $(OBJS) $(G_OBJS) $(SCREEN_OBJS)
	$(C) $(OBJS) $(G_OBJS) $(SCREEN_OBJS) -o $(OUT) $(INCLUDE) $(CFLAGS) $(LDFLAGS)

main.o: main.cpp
	$(C) -c main.cpp

#################
# Game Objects
#################
game.o: game.cpp game.h
	$(C) -c game.cpp game.h

cursor.o: cursor.cpp cursor.h
	$(C) -c cursor.cpp cursor.h

ship.o: ship.cpp ship.h
	$(C) -c ship.cpp ship.h

object_manager.o: object_manager.cpp object_manager.h
	$(C) -c object_manager.cpp object_manager.h

star.o: star.cpp star.h
	$(C) -c star.cpp star.h

bullet.o: bullet.cpp bullet.h
	$(C) -c bullet.cpp bullet.h

#################
# Screen Objects 
#################
start_screen.o: start_screen.cpp start_screen.h screen.h
	$(C) -c start_screen.cpp start_screen.h

game_screen.o: game_screen.cpp game_screen.h screen.h
	$(C) -c game_screen.cpp game_screen.h

help_screen.o: help_screen.cpp help_screen.h screen.h 
	$(C) -c help_screen.cpp help_screen.h 

result_screen.o: result_screen.cpp result_screen.h screen.h
	$(C) -c result_screen.cpp result_screen.h 
