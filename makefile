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

test.o: test/main.c | build
	${CC} -g -c test/main.c -I ./Entreprise -o build/test.o

# S'assure de l'existence tout les programmes finaux (application, test, etc.)
# Par exemple : all: build/test build/appli
all: libEntreprise.a test.o
	${CC} build/test.o -Lbuild/ -lEntreprise -o build/LuminIn

# Lance le programme de test.
check: all
	./build/LuminIn

clean:
	rm build/*