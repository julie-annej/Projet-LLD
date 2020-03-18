// Projet LLD.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>

using namespace std;

struct Danseur;
struct ListDanseurs;
struct ListNumero;

struct Numero {
	string titre;
	unsigned nDanseurs = 0;
	Danseur *ptrDanseurs[80];
};

struct Danseur {
	string nom;
	unsigned nNumero = 0;
	Numero* ptrNumero[30];
};

struct ListDanseurs {
	unsigned nDanseurs = 0;
	Danseur* ptrDanseurs[450];
};

struct ListNumero {
	unsigned nNumero = 0;
	Numero* ptrNumero[30];
};

bool danseurDansList(Danseur* ptrDanseur, ListDanseurs& listDanseurs) {
	bool resultat = false;
	for (unsigned i = 0; i < listDanseurs.nDanseurs; i++) {
		if (ptrDanseur->nom == listDanseurs.ptrDanseurs[i]->nom) {
			ptrDanseur = listDanseurs.ptrDanseurs[i];
			resultat = true;
			break;
		}
	}
	return resultat;
}

void ajouterDanseur(Danseur* ptrDanseur, Numero* ptrNumero, ListDanseurs& listDanseurs) {
	if (!danseurDansList(ptrDanseur, listDanseurs)) {
		listDanseurs.ptrDanseurs[listDanseurs.nDanseurs] = ptrDanseur;
		listDanseurs.nDanseurs++;
	}

	ptrNumero->ptrDanseurs[ptrNumero->nDanseurs] = ptrDanseur;
	ptrNumero->nDanseurs++;

	ptrDanseur->ptrNumero[ptrDanseur->nNumero] = ptrNumero;
	ptrDanseur->nNumero++;
}

void ajouterNumero(Numero* ptrNumero, ListNumero& listNumero) {
	listNumero.ptrNumero[listNumero.nNumero] = ptrNumero;
	listNumero.nNumero++;
}

void lireFichier(string nomFichier, ListNumero& listNumero, ListDanseurs& listDanseurs) {
	ifstream fichier(nomFichier);
	if (fichier.fail()) {
		cout << "Erreur lors de l'ouverture du fichier" << endl;
	}
	else {
		ListNumero listNumero;
		ListDanseurs listDanseurs;
		
		while (!ws(fichier).eof()) {
			unsigned nbDanseurs = 0;
			fichier >> nbDanseurs;

			Numero* ptrNumero = new Numero;
			getline(fichier, ptrNumero->titre, '\t');
			ajouterNumero(ptrNumero, listNumero);

			for (unsigned i = 0; i < nbDanseurs; i++) {
				Danseur* ptrDanseur = new Danseur{};
				getline(fichier, ptrDanseur->nom, '\t');
				ajouterDanseur(ptrDanseur, ptrNumero, listDanseurs);
			}
		}
	}
}

void cardIntersectionNumero(Numero *ptrNum1, Numero *ptrNum2) {
	ListDanseurs interDanseurs;
	ListNumero interNumero;
	for (unsigned i = 0; i < ptrNum1->nDanseurs; i++) {
		for (unsigned j = 0; j < ptrNum1->nDanseurs; j++) {
			if (ptrNum1->ptrDanseurs[i] == ptrNum2->ptrDanseurs[j]) {
				interDanseurs.ptrDanseurs[interDanseurs.nDanseurs] = ptrNum1->ptrDanseurs[i];
				interDanseurs.nDanseurs++;


			}

		}
	}
	
}

void afficherUnNumero(Numero* numero) {
	cout << "Titre: " << numero->titre;
	for (unsigned i = 0; i < numero->nDanseurs; i++) {
		cout << numero->ptrDanseurs[i]->nom << " ";
	}
}

int main()
{
	string nomFichier = "Test_LLD3.txt";
	ListDanseurs listeDeDanseurs;
	ListNumero listeDeNumeros;
	lireFichier(nomFichier, listeDeNumeros, listeDeDanseurs);
	for (unsigned i = 0; i < listeDeNumeros.nNumero; i++) {
		afficherUnNumero(listeDeNumeros.ptrNumero[i]);
	}
}