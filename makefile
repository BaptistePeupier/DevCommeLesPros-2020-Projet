CC = g++ -Wall -pedantic -Werror

.DEFAULT_GOAL := check

.PHONY: clean

# Efface tout les fichiers temporaires et les produits finaux.
clean:
	rm -rf build

# Crée le répertoire qui acceuille les fichiers temporaires et les produits finaux.
build:
	mkdir -p build

# Crée ...
libEntreprise.a: Entreprise/entreprise.cpp Entreprise/entreprise.h | build
	${CC} -g -c Entreprise/entreprise.cpp -o build/entreprise.o
	ar crs build/libEntreprise.a build/entreprise.o

libPersonne.a: libEntreprise.a Entreprise/entreprise.h Personne/personne.cpp | build
	${CC} -g -c Personne/personne.cpp -I ./Entreprise -o build/personne.o
	ar crs build/libPersonne.a build/personne.o

libGeneral.a: libEntreprise.a libPersonne.a General/general.h General/general.cpp | build
	${CC} -g -c General/general.cpp -I ./Entreprise -I ./Personne -o build/general.o
	ar crs build/libGeneral.a build/general.o

tests.o: test/tests.cpp test/tests.h | build
	${CC} -g -c test/tests.cpp -I ./Entreprise -I ./Personne -I ./General -o build/tests.o

main.o: main.cpp tests.o | build
	${CC} -g -c main.cpp -I ./Entreprise -I ./Personne -I ./General -I ./test -o build/main.o

# S'assure de l'existence tout les programmes finaux (application, test, etc.)
# Par exemple : all: build/test build/appli
all: libGeneral.a main.o
	${CC} build/main.o build/tests.o -Lbuild/ -lEntreprise -lPersonne -lGeneral -o build/LuminIn

# Lance le programme de test.
check: all
	./build/LuminIn

