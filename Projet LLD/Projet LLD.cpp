// Projet LLD.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>

using namespace std;

struct Numero {
	string titre;
	unsigned nDanseurs = 0;
	Danseur *ptrDanseurs[80];
};

struct Danseur {
	string nom;
	unsigned nNumeros = 0;
	Numero *ptrNumeros[30];
};

void ajouterDanseur(Numero& numero, Danseur* listPtrDanseurs[]) {
	
}

void lireFichier(string nomFichier) {
	ifstream fichier(nomFichier);
	if (fichier.fail()) {
		cout << "Erreur lors de l'ouverture du fichier" << endl;
	}
	else {
		while (!ws(fichier).eof()) {

		}
	}
}

int main()
{
	string nomFichier = "Test_LLD";
	
}

