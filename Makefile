
# code details

EXE_DIR = .
EXE = $(EXE_DIR)/rendering

SRC= 07_texture_loading_and_rendering.c

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

07_texture_loading_and_rendering.o:  07_texture_loading_and_rendering.c  

