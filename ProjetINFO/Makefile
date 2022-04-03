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



clean :
	rm -rf *.o


docs: $(DOCINDEX)
	rm -rf $(DOCHTML)
	$(DOXYGEN) $(DOCCONF)
	$(WEBNAV) $(DOCINDEX)