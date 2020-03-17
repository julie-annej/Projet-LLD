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

struct ListDanseurs {
	unsigned nDanseurs = 0;
	Danseur* ptrDanseurs[450];
};

struct ListNumero {
	unsigned nNumeros = 0;
	Numero* ptrNumeros[30];
};

void ajouterDanseur(Danseur *ptrDanseur, Numero* ptrNumero, ListDanseurs& listDanseurs) {
	ptrNumero->ptrDanseurs[ptrNumero->nDanseurs] = ptrDanseur;
	ptrNumero->nDanseurs++;
	
	ptrDanseur->ptrNumeros[ptrDanseur->nNumeros] = ptrNumero;
	ptrDanseur->nNumeros++;

	listDanseurs.ptrDanseurs[listDanseurs.nDanseurs] = ptrDanseur;
	listDanseurs.nDanseurs++;
}

void ajouterNumero(const Numero* ptrNumero, ListNumero& ListNumero) {
	
}

bool danseurDansList(Danseur *danseur, ListDanseurs& listDanseurs) {
	bool resultat = false;
	for (unsigned i = 0; i < listDanseurs.nDanseurs; i++) {
		if (danseur->nom == listDanseurs.ptrDanseurs[i]->nom) {
			resultat = true;
			break;
		}
	}
	return resultat;
}

void lireFichier(string nomFichier) {
	ifstream fichier(nomFichier);
	if (fichier.fail()) {
		cout << "Erreur lors de l'ouverture du fichier" << endl;
	}
	else {
		ListNumero listNumero;
		ListDanseurs listDanseurs;
		
		while (!ws(fichier).eof()) {
			unsigned nbDanseur = 0;
			Numero* ptrNumero = new Numero;
			getline(fichier, ptrNumero->titre, '\t');
			ajouterNumero(ptrNumero, listNumero);

			for (unsigned i = 0; i < nbDanseur; i++) {
				Danseur* ptrDanseur = new Danseur{};
				getline(fichier, ptrDanseur->nom, '\t');
				ajouterDanseur(ptrDanseur, )
			}

		}
	}
}

int main()
{
	string nomFichier = "Test_LLD";
	
}

