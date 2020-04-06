CC = g++ -Wall -pedantic -Werror

.DEFAULT_GOAL := check

.PHONY: clean

# Efface tout les fichiers temporaires et les produits finaux.
clean:
	rm -rf build

# Crée le répertoire qui acceuille les fichiers temporaires et les produits finaux.
build:
	mkdir -p Entreprise/build

libEntreprise.a: Entreprise/lib/entreprise.cxx Entreprise/lib/entreprise.h | build
	${CC} -c Entreprise/lib/entreprise.cxx -o Entreprise/build/entreprise.o
	ar crs Entreprise/lib/libEntreprise.a Entreprise/build/entreprise.o

# S'assure de l'existence tout les programmes finaux (application, test, etc.)
# Par exemple : all: build/test build/appli
all: libEntreprise.a

# Lance le programme de test.
check:
	false
