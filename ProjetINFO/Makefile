CC = gcc
EXEC = EFSoft
DOXYGEN = doxygen
DOCHTML = ./doc/html
DOCCONF = ./doc/Doxyfile
DOCINDEX = $(DOCHTML)/index.html
WEBNAV = firefox

MATRIXSRC = ./src/Matrix/$(wildcard *.c)
MATRIXOBJ = $(MATRIXSRC:.c=.o)
MATRIXLIB = ./lib/matrix.a

all :

lib : matrix.a


matrix.o :
	$(CC) -c $(MATRIXSRC) -o $(MATRIXOBJ)

matrix.a : $(MATRIXOBJ)
	ar -cr $(MATRIXLIB) $(MATRIXOBJ)
	

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
