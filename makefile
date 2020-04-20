CC = g++ -Wall -pedantic -Werror

.DEFAULT_GOAL := check

.PHONY: clean

# Efface tout les fichiers temporaires et les produits finaux.
clean:
	rm -rf build

# Crée le répertoire qui acceuille les fichiers temporaires et les produits finaux.
build:
	mkdir -p build

libEntreprise.a: Entreprise/entreprise.cpp Entreprise/entreprise.h | build
	${CC} -g -c Entreprise/entreprise.cpp -o build/entreprise.o
	ar crs build/libEntreprise.a build/entreprise.o

libPersonne.a: libEntreprise.a Entreprise/entreprise.h Personne/personne.cpp | build
	${CC} -g -c Personne/personne.cpp -I ./Entreprise -o build/personne.o
	ar crs build/libPersonne.a build/personne.o

libGeneral.a: libEntreprise.a libPersonne.a General/general.h General/general.cpp | build
	${CC} -g -c General/general.cpp -I ./Entreprise -I ./Personne -o build/general.o
	ar crs build/libGeneral.a build/general.o

test.o: test/main.cpp | build
	${CC} -g -c test/main.cpp -I ./Entreprise -I ./Personne -I ./General -o build/test.o

# S'assure de l'existence tout les programmes finaux (application, test, etc.)
# Par exemple : all: build/test build/appli
all: libGeneral.a test.o
	${CC} build/test.o -Lbuild/ -lEntreprise -lPersonne -lGeneral -o build/LuminIn

# Lance le programme de test.
check: all
	./build/LuminIn