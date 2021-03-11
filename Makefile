
# code details

EXE_DIR = .
EXE = $(EXE_DIR)/path
SRC= main.c readding.c SDLFunctions.c Dijkstra.c globalFunctions.c

# generic build details

CC =     gcc
CFLAGS = -Wall -O
LIBS =   -lSDL2 -lSDL2_image

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

main.o readding.o SDLFunctions.o Dijkstra.o globalFunctions.o :  main.c readding.c SDLFunctions.c Dijkstra.c globalFunctions.c 

