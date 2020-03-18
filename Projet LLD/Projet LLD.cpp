// Projet LLD.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <algorithm>    // std::set_union, std::sort
#include <vector>

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
	if (!danseurDansList(ptrDanseur,listDanseurs)) {
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
		while (!ws(fichier).eof()) {
			unsigned nbDanseurs = 0;
			fichier >> nbDanseurs;
			Numero* ptrNumero = new Numero;
			getline(fichier, ptrNumero->titre, '\n');
			ajouterNumero(ptrNumero, listNumero);
			
			for (unsigned i = 0; i < nbDanseurs; i++) {
				Danseur* ptrDanseur = new Danseur{};
				getline(fichier, ptrDanseur->nom, '\n');
				ajouterDanseur(ptrDanseur, ptrNumero, listDanseurs);
			}
		}
	}
}

unsigned cardIntersectionNumero(Numero *ptrNum1, Numero *ptrNum2) {
	ListDanseurs inter;
	for (unsigned i = 0; i < ptrNum1->nDanseurs; i++) {
		for (unsigned j = 0; j < ptrNum1->nDanseurs; j++) {
			if (ptrNum1->ptrDanseurs[i] == ptrNum2->ptrDanseurs[j]) {
				inter.ptrDanseurs[inter.nDanseurs] = ptrNum1->ptrDanseurs[i];
				inter.nDanseurs++;
			}
		}
	}
	return inter.nDanseurs;
}


void afficherUnNumero(Numero* ptrnumero) {
	for (unsigned i = 0; i < ptrnumero->nDanseurs; i++) {
		cout << ptrnumero->ptrDanseurs[i]->nom << " ";
	}
}

int main()
{
	string nomFichier = "Test_LLD3.txt";
	ListDanseurs listeDeDanseurs = {};
	ListNumero listeDeNumeros = {};
	lireFichier(nomFichier, listeDeNumeros, listeDeDanseurs);
	cout << listeDeNumeros.nNumero << " "
		<< listeDeDanseurs.nDanseurs << " " << endl;
	cout << " Titre " << endl;
	for (unsigned i = 0; i < listeDeNumeros.nNumero; i++) {
		cout << listeDeNumeros.ptrNumero[i]->titre << ": ";
		afficherUnNumero(listeDeNumeros.ptrNumero[i]);
		cout << endl;
	}
}

