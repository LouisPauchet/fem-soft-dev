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

test :

clean :
	rm -rf *.o
	rm -rf $(DOCHTML)


docs: $(DOCINDEX)
	rm -rf $(DOCHTML)
	$(DOXYGEN) $(DOCCONF)
	$(WEBNAV) $(DOCINDEX)