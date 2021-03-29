
# code details

EXE_DIR = .
EXE = $(EXE_DIR)/CyberRoads
SRC= main.c reading.c sdl_functions.c dijkstra.c bellman_ford.c globalFunctions.c 

# generic build details

CC =     gcc
CFLAGS = -Wall -O
LIBS =   -lSDL2 -lSDL2_image -lSDL2_ttf

# compile to  object code

OBJ= $(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< 

# build executable

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(LIBS)

# clean up compilation

clean:
	rm -f $(OBJ) $(EXE)

# dependencies

main.o reading.o sdl_functions.o dijkstra.o bellman_ford.o globalFunctions.o :  main.c reading.c sdl_functions.c dijkstra.c bellman_ford.c globalFunctions.c 
