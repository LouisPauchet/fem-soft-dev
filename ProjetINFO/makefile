CC = gcc
AR = ar
CFFLAGS = -g -I$(INCLUDEDIR)
LDFLAGS = -lm

EXEC = EFSoft
DOCWIZARD = doxygen
DOCCONF = ./config/Doxyfile
DOCINDEX = $(DOCDIR)/html/index.html
WEBNAV = firefox
LEAKSOFT = valgrind

DOCDIR = ./doc
SRCDIR = ./src
LIBDIR = ./lib
BINDIR = ./bin
INCLUDEDIR = ./include

MATRIXSUBDIR = Matrix
EFSUBDIR = EF
LISTSUBDIR = List
MAINSUBDIR = main

launch : $(BINDIR)/$(EXEC)
	$(BINDIR)/$(EXEC)

all : Unit $(BINDIR)/$(EXEC)

Unit : listUnit matrixUnit EFUnit
#
# Création de l'unité EF
EFUnit : $(SRCDIR)/$(EFSUBDIR)/EFElementStruct.o $(SRCDIR)/$(EFSUBDIR)/EFNodeStruct.o $(SRCDIR)/$(EFSUBDIR)/EFMathematics.o $(SRCDIR)/$(EFSUBDIR)/EFIHM.o
	$(AR) -cr $(LIBDIR)/EFUnit.a $^


# Compilation de fichiers sources de l'unité EF

$(SRCDIR)/$(EFSUBDIR)/%.o : $(SRCDIR)/$(EFSUBDIR)/%.c
	$(CC) -o $@ -c $< $(CFFLAGS)


# Compilation de fichiers sources de main

$(SRCDIR)/$(MAINSUBDIR)/%.o : $(SRCDIR)/$(MAINSUBDIR)/%.c
	$(CC) -o $@ -c $< $(CFFLAGS)




#Lancement du fichier de test manuel pour l'unité matrice

listTest : $(BINDIR)/$(LISTSUBDIR)/test
	$(BINDIR)/$(LISTSUBDIR)/test
	
#Création du fichier de test manuel pour les matrices

$(BINDIR)/$(LISTSUBDIR)/test : $(SRCDIR)/$(LISTSUBDIR)/ListStruct.o $(SRCDIR)/$(LISTSUBDIR)/ListTest.o
	mkdir -p $(BINDIR)/$(LISTSUBDIR)
	$(CC) -o $@ $^ $(LDFLAGS)



# Création de l'unité List
listUnit : $(SRCDIR)/$(LISTSUBDIR)/ListStruct.o
	$(AR) -cr $(LIBDIR)/listUnit.a $^

# Compilation de fichiers sources de l'unité list

$(SRCDIR)/$(LISTSUBDIR)/%.o : $(SRCDIR)/$(LISTSUBDIR)/%.c
	$(CC) -o $@ -c $< $(CFFLAGS)

# Création de l'unité Matrice
matrixUnit : $(SRCDIR)/$(MATRIXSUBDIR)/MatrixStruct.o $(SRCDIR)/$(MATRIXSUBDIR)/MatrixIHM.o $(SRCDIR)/$(MATRIXSUBDIR)/MatrixCalc.o $(SRCDIR)/$(MATRIXSUBDIR)/MatrixList.o
	$(AR) -cr $(LIBDIR)/matrixUnit.a $^

#Création de l'executable général

$(BINDIR)/$(EXEC) : $(SRCDIR)/$(LISTSUBDIR)/ListStruct.o $(SRCDIR)/$(EFSUBDIR)/EFElementStruct.o $(SRCDIR)/$(EFSUBDIR)/EFNodeStruct.o $(SRCDIR)/$(EFSUBDIR)/EFMathematics.o $(SRCDIR)/$(EFSUBDIR)/EFIHM.o $(SRCDIR)/$(MAINSUBDIR)/main.o $(SRCDIR)/$(MATRIXSUBDIR)/MatrixStruct.o $(SRCDIR)/$(MATRIXSUBDIR)/MatrixIHM.o $(SRCDIR)/$(MATRIXSUBDIR)/MatrixCalc.o $(SRCDIR)/$(MATRIXSUBDIR)/MatrixList.o
	$(CC) -o $@ $^ $(LDFLAGS)

#Lancement du fichier de test manuel pour l'unité matrice

matrixTest : $(BINDIR)/$(MATRIXSUBDIR)/test
	$(BINDIR)/$(MATRIXSUBDIR)/test
	
#Création du fichier de test manuel pour les matrices

$(BINDIR)/$(MATRIXSUBDIR)/test : $(SRCDIR)/$(MATRIXSUBDIR)/MatrixStruct.o $(SRCDIR)/$(MATRIXSUBDIR)/MatrixIHM.o $(SRCDIR)/$(MATRIXSUBDIR)/MatrixCalc.o $(SRCDIR)/$(MATRIXSUBDIR)/MatrixTest.o
	mkdir -p $(BINDIR)/$(MATRIXSUBDIR)
	$(CC) -o $@ $^ $(LDFLAGS)

# Compilation de fichiers sources de l'unité matrice

$(SRCDIR)/$(MATRIXSUBDIR)/%.o : $(SRCDIR)/$(MATRIXSUBDIR)/%.c
	$(CC) -o $@ -c $< $(CFFLAGS)

#Suppression des fichiers objets, des unités, de la documentation et des executables.

clean :
	rm -rf $(DOCDIR)/*
	rm -rf $(BINDIR)/*
	rm -rf $(LIBDIR)/*
	rm -rf $(SRCDIR)/*.o
	rm -rf $(SRCDIR)/$(MATRIXSUBDIR)/*.o
	rm -rf $(SRCDIR)/$(EFSUBDIR)/*.o
	rm -rf $(SRCDIR)/$(LISTSUBDIR)/*.o

#Suppression des repertoires inutiles

cleanProject : clean
	rm -rf $(DOCDIR)
	rm -rf $(BINDIR)
	rm -rf $(LIBDIR)

#Création des répertoires

directory :
	mkdir -p $(DOCDIR)
	mkdir -p $(BINDIR)
	mkdir -p $(LIBDIR)

#Création de la documentation

docs :
	echo "Suppression de l'ancienne documentation"
	@ rm -rf $(DOCDIR)
	echo "Génération de la documentation"
	@ $(DOCWIZARD) $(DOCCONF)
	echo "Ouverture de la documentation"
	@ $(WEBNAV) $(DOCINDEX) &

#Création d'une archive à envoyer

sendAr : cleanProject
	rm -f ./ProjetArchive.tar.gz
	mkdir -p ./ProjetArchive
	cp -r ./src ./ProjetArchive
	cp -r ./include ./ProjetArchive
	cp -r ./config ./ProjetArchive
	cp ./makefile ./ProjetArchive
	tar zcvf ProjetArchive.tar.gz ./ProjetArchive
	rm -rf ./ProjetArchive

delSendAr :
	rm -f ./ProjetArchive.tar.gz

valgrind : $(BINDIR)/$(EXEC)
	$(LEAKSOFT) $(BINDIR)/$(EXEC)

