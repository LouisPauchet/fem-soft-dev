CC = gcc
EXEC = EFSoft
SRC = 	$(wildcard /src/*.c) \
		$(wildcard src/Matrix/*.c)\
		$(wildcard src/List/*.c) \
		$(wildcard src/EF/*.c)
OBJ = $(SRV:.c:.o)

DOXYGEN = doxygen
DOCHTML = ./doc/html
DOCCONF = ./doc/Doxyfile
DOCINDEX = $(DOCHTML)/index.html
WEBNAV = firefox

SRC_MATRIX = ./src/Matrix/wildcard *.c
SRC_LIST = ./src/List/wildcard *.c
SRC_TEST = ./src/test/wildcard *.c

OBJ_MATRIX = $(SRC_MATRIX:.c=.o)
OBJ_LIST = $(SRC_LIST:.c=.o)
OBJ_TEST = $(SRC_TEST:.c=.o)

all :

matrix :


liste :

clean :
	rm -rf *.o
	rm -rf $(DOCHTML)


docs :
	echo "Suppression de l'ancienne documentation"
	@ rm -rf $(DOCHTML)
	echo "Génération de la documentation"
	@ $(DOXYGEN) $(DOCCONF)
	echo "Ouverture de la documentation"
	@ $(WEBNAV) $(DOCINDEX) &
