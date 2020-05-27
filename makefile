CC = g++ -Wall -pedantic -Werror

.DEFAULT_GOAL := check

.PHONY: clean

# Efface tout les fichiers temporaires et les produits finaux.
clean:
	rm -rf build

# Crée le répertoire qui acceuille les fichiers temporaires et les produits finaux.
build:
	mkdir -p build

# Bibliothèque des fonctions pour les Entreprises
libEntreprise.a: Entreprise/entreprise.cpp Entreprise/entreprise.h | build
	${CC} -g -c Entreprise/entreprise.cpp -o build/entreprise.o
	ar crs build/libEntreprise.a build/entreprise.o

# Bibliothèque des fonctions pour les Personnes
# Liée avec la bibliothèque des fonctions pour les Entreprises
libPersonne.a: libEntreprise.a Entreprise/entreprise.h Personne/personne.cpp | build
	${CC} -g -c Personne/personne.cpp -I ./Entreprise -o build/personne.o
	ar crs build/libPersonne.a build/personne.o

# Bibliothèque des fonctions générales (création, suppression, ... des listes de données)
# Compile également les bibliothèques des Entreprises et des Personnes
# Liée avec les bibliothèques des fonctions pour les Entreprises et les Personnes
libGeneral.a: libEntreprise.a libPersonne.a General/general.h General/general.cpp | build
	${CC} -g -c General/general.cpp -I ./Entreprise -I ./Personne -o build/general.o
	ar crs build/libGeneral.a build/general.o

# Programme de test
# Compile également la biliothèque Général et donc les autres
tests.o: libGeneral.a test/tests.cpp test/tests.h | build
	${CC} -g -c test/tests.cpp -I ./Entreprise -I ./Personne -I ./General -o build/tests.o

# Interface du programme
# Compile également la biliothèque Général et donc les autres
interface.o: libGeneral.a interface/interface.cpp interface/interface.h | build
	${CC} -g -c interface/interface.cpp -I ./Entreprise -I ./Personne -I ./General -o build/interface.o

# Menu principal de l'application
# On peut ainsi choisir de lancer les batteries de tests ou l'application en elle-même
main.o: main.cpp tests.o interface.o | build
	${CC} -g -c main.cpp -I ./Entreprise -I ./Personne -I ./General -I ./test -I ./interface -o build/main.o

# S'assure de l'existence tout les programmes finaux (application, test, etc.)
# Par exemple : all: build/test build/appli
all: libGeneral.a main.o
	${CC} build/main.o build/tests.o build/interface.o -Lbuild/ -lEntreprise -lPersonne -lGeneral -o build/LuminIn

# Lance l'application.
check: all
	./build/LuminIn

# Restaure les DB à partir des backups
RestoreDB:
	cp test/db_backup/chercheurEmploi.csv test/FichiersDeTests/chercheurEmploi.csv
	cp test/db_backup/employes.csv test/FichiersDeTests/employes.csv
	cp test/db_backup/entreprise.csv test/FichiersDeTests/entreprise.csv
	cp test/db_backup/poste.csv test/FichiersDeTests/poste.csv

