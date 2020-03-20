#include "Projet LLD.cpp"

#include <iostream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <algorithm>    // std::set_union, std::sort
#include <vector>


using namespace std;

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

bool numeroDansList(Numero* ptrNumero, ListNumero& listNumero) {
	bool resultat = false;
	for (unsigned i = 0; i < listNumero.nNumero; i++) {
		if (ptrNumero == listNumero.ptrNumero[i]) {
			resultat = true;
			break;
		}
	}
	return resultat;
}

//ListNumero unionOfNumero(ListDanseurs& listDanseurs) {
//	ListNumero unionOfNumero;
//	for (unsigned i = 0; i < listDanseurs.nDanseurs; i++) {
//		for (unsigned j = 0; j < listDanseurs.ptrDanseurs[i]->nNumero; j++) {
//			if (!numeroDansList(listDanseurs.ptrDanseurs[i]->ptrNumero[j], unionOfNumero)) {
//				ajouterNumero(listDanseurs.ptrDanseurs[i]->ptrNumero[j], unionOfNumero);
//			}
//		}
//	}
//	return unionOfNumero;
//}

void getContraintesNumero(Numero* ptrNum1, Numero* ptrNum2) {
	bool trouver = false;
	for (unsigned i = 0; (i < ptrNum1->nDanseurs) && (!trouver); i++) {
		for (unsigned j = 0; (j < ptrNum2->nDanseurs) && (!trouver); j++) {
			if (ptrNum1->ptrDanseurs[i]->nom == ptrNum2->ptrDanseurs[j]->nom) {
				ptrNum1->contraintes.ptrNumero[ptrNum1->contraintes.nNumero] = ptrNum2;
				ptrNum2->contraintes.ptrNumero[ptrNum2->contraintes.nNumero] = ptrNum1;
				ptrNum1->contraintes.nNumero++;
				ptrNum2->contraintes.nNumero++;
				trouver = true;
			}
		}
	}
}

void setContraintes(ListNumero& listNumero) {
	for (unsigned i = 0; i < listNumero.nNumero; i++) {
		for (unsigned j = i + 1; j < listNumero.nNumero; j++) {
			getContraintesNumero(listNumero.ptrNumero[i], listNumero.ptrNumero[j]);
		}
	}
}

void sortFromMostconstraint(ListNumero& listNumero) {
	for (unsigned i = 0; i < listNumero.nNumero; i++) {
		for (unsigned j = 0; j < listNumero.nNumero - 1 - i; j++) {
			if (listNumero.ptrNumero[j]->contraintes.nNumero < listNumero.ptrNumero[j + 1]->contraintes.nNumero) {
				Numero* a = listNumero.ptrNumero[j];
				Numero* b = listNumero.ptrNumero[j + 1];
				listNumero.ptrNumero[j] = b;
				listNumero.ptrNumero[j + 1] = a;
			}
		}
	}
}

void afficherUnNumero(Numero* ptrnumero) {
	for (unsigned i = 0; i < ptrnumero->nDanseurs; i++) {
		cout << ptrnumero->ptrDanseurs[i]->nom << ", ";
	}
}

void eraselistDanseur(ListDanseurs& listDanseurs) {
	for (unsigned i = 0; i < listDanseurs.nDanseurs; i++) {
		delete listDanseurs.ptrDanseurs[i];
	}
}
