CC = gcc
AR = ar
CFFLAGS = -g -I$(INCLUDEDIR) -std=c99
LDFLAGS = -lm -no-pie

MAKE = make
MAKEFLAGS = all

EXEC = EFSoft
TEST_EXEC = EFSoft_CUNIT_Test
DOCWIZARD = doxygen
DOCCONF = ./config/Doxyfile
DOCPDFNAME = Documentation_Detaille.pdf
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
TESTSUBDIR = tests

launch : $(BINDIR)/$(EXEC)
	$(BINDIR)/$(EXEC)

all : Unit $(BINDIR)/$(EXEC)

Unit : listUnit matrixUnit EFUnit

tests : $(BINDIR)/$(TEST_EXEC)
	$(BINDIR)/$(TEST_EXEC)

# Création de l'unité EF
EFUnit : $(SRCDIR)/$(EFSUBDIR)/EFElementStruct.o $(SRCDIR)/$(EFSUBDIR)/EFNodeStruct.o $(SRCDIR)/$(EFSUBDIR)/EFMathematics.o $(SRCDIR)/$(EFSUBDIR)/EFIHM.o $(SRCDIR)/$(EFSUBDIR)/EFMecanicalSystemStruct.o
	$(AR) -cr $(LIBDIR)/EFUnit.a $^


# Compilation de fichiers sources de l'unité EF

$(SRCDIR)/$(EFSUBDIR)/%.o : $(SRCDIR)/$(EFSUBDIR)/%.c
	make directory
	$(CC) -o $@ -c $< $(CFFLAGS)


# Compilation de fichiers sources de main

$(SRCDIR)/$(MAINSUBDIR)/%.o : $(SRCDIR)/$(MAINSUBDIR)/%.c
	make directory
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
	make directory
	$(CC) -o $@ -c $< $(CFFLAGS)

# Création de l'unité Matrice
matrixUnit : $(SRCDIR)/$(MATRIXSUBDIR)/MatrixStruct.o $(SRCDIR)/$(MATRIXSUBDIR)/MatrixIHM.o $(SRCDIR)/$(MATRIXSUBDIR)/MatrixCalc.o $(SRCDIR)/$(MATRIXSUBDIR)/MatrixList.o
	$(AR) -cr $(LIBDIR)/matrixUnit.a $^





#Création de l'executable de test automatiques

$(BINDIR)/$(TEST_EXEC) : $(SRCDIR)/$(LISTSUBDIR)/ListStruct.o $(SRCDIR)/$(EFSUBDIR)/EFElementStruct.o $(SRCDIR)/$(EFSUBDIR)/EFNodeStruct.o $(SRCDIR)/$(EFSUBDIR)/EFMathematics.o $(SRCDIR)/$(EFSUBDIR)/EFIHM.o $(SRCDIR)/$(MATRIXSUBDIR)/MatrixStruct.o $(SRCDIR)/$(MATRIXSUBDIR)/MatrixIHM.o $(SRCDIR)/$(MATRIXSUBDIR)/MatrixCalc.o $(SRCDIR)/$(MATRIXSUBDIR)/MatrixList.o $(SRCDIR)/$(TESTSUBDIR)/testMain.o $(SRCDIR)/$(TESTSUBDIR)/testMatrixStruct.o $(SRCDIR)/$(TESTSUBDIR)/testEFMathematics.o $(SRCDIR)/$(TESTSUBDIR)/testMatrixCalc.o $(SRCDIR)/$(EFSUBDIR)/EFMecanicalSystemStruct.o
	#$(CC) -o $@ $^ $(LDFLAGS) -lcunit
	$(CC) -o $@ $^ ./lib_external/libmat.a $(LDFLAGS) -lcunit
	

#Compilation des fichiers de test automatique.

$(SRCDIR)/$(TESTSUBDIR)/%.o : $(SRCDIR)/$(TESTSUBDIR)/%.c
	make directory
	$(CC) -o $@ -c $< $(CFFLAGS)


#Création de l'executable général

$(BINDIR)/$(EXEC) : $(SRCDIR)/$(LISTSUBDIR)/ListStruct.o $(SRCDIR)/$(EFSUBDIR)/EFElementStruct.o $(SRCDIR)/$(EFSUBDIR)/EFNodeStruct.o $(SRCDIR)/$(EFSUBDIR)/EFMathematics.o $(SRCDIR)/$(EFSUBDIR)/EFIHM.o $(SRCDIR)/$(MAINSUBDIR)/main.o $(SRCDIR)/$(MATRIXSUBDIR)/MatrixStruct.o $(SRCDIR)/$(MATRIXSUBDIR)/MatrixIHM.o $(SRCDIR)/$(MATRIXSUBDIR)/MatrixCalc.o $(SRCDIR)/$(MATRIXSUBDIR)/MatrixList.o $(SRCDIR)/$(EFSUBDIR)/EFMecanicalSystemStruct.o
	#$(CC) -o $@ $^ $(LDFLAGS)
	$(CC) -o $@ $^ ./lib_external/libmat.a $(LDFLAGS)

#Lancement du fichier de test manuel pour l'unité matrice

matrixTest : $(BINDIR)/$(MATRIXSUBDIR)/test
	$(BINDIR)/$(MATRIXSUBDIR)/test
	
#Création du fichier de test manuel pour les matrices

$(BINDIR)/$(MATRIXSUBDIR)/test : $(SRCDIR)/$(MATRIXSUBDIR)/MatrixStruct.o $(SRCDIR)/$(MATRIXSUBDIR)/MatrixIHM.o $(SRCDIR)/$(MATRIXSUBDIR)/MatrixCalc.o $(SRCDIR)/$(MATRIXSUBDIR)/MatrixTest.o
	mkdir -p $(BINDIR)/$(MATRIXSUBDIR)
	$(CC) -o $@ $^ $(LDFLAGS)

# Compilation de fichiers sources de l'unité matrice

$(SRCDIR)/$(MATRIXSUBDIR)/%.o : $(SRCDIR)/$(MATRIXSUBDIR)/%.c
	make directory
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
	rm -rf $(SRCDIR)/$(MAINSUBDIR)/*.o
	rm -rf $(SRCDIR)/$(TESTSUBDIR)/*.o
	rm -rf ./$(DOCPDFNAME)


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
	make -C $(DOCDIR)/latex/ all
	mv $(DOCDIR)/latex/refman.pdf ./$(DOCPDFNAME)
	@ $(WEBNAV) $(DOCINDEX) &
	@ $(WEBNAV) ./$(DOCPDFNAME) &

#Création d'une archive à envoyer

sendAr : cleanProject
	rm -f ./ProjetArchive.tar.gz
	mkdir -p ./ProjetArchive
	cp -r ./src ./ProjetArchive
	cp -r ./include ./ProjetArchive
	cp -r ./config ./ProjetArchive
	cp -r ./lib_external ./ProjetArchive
	cp ./makefile ./ProjetArchive
	tar zcvf ProjetArchive.tar.gz ./ProjetArchive
	rm -rf ./ProjetArchive

delSendAr :
	rm -f ./ProjetArchive.tar.gz

valgrind : $(BINDIR)/$(EXEC)
	$(LEAKSOFT)  --leak-check=full -s $(BINDIR)/$(EXEC) 

#Suppression des fichiers de stockage des matrices.

data_clean : 
	rm -rf data/*.cMat
	rm -rf *.cMat
