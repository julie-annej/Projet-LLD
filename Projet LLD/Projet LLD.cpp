// Projet LLD.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include "Source.cpp"

struct Danseur;
struct Numero;
struct ListDanseurs;
struct ListNumero;

struct ListNumero {
	unsigned nNumero = 0;
	Numero* ptrNumero[60];
};

struct Numero {
	string titre;
	unsigned nDanseurs = 0;
	Danseur *ptrDanseurs[80];
	ListNumero contraintes = { 0,{} };
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
	
	setContraintes(listeDeNumeros);
	sortFromMostconstraint(listeDeNumeros);

	for (unsigned i = 0; i < listeDeNumeros.nNumero; i++) {
		cout << listeDeNumeros.ptrNumero[i]->titre << " contraintes : ";
		for (unsigned j = 0; j <  listeDeNumeros.ptrNumero[i]->contraintes.nNumero; j++) {
			cout << listeDeNumeros.ptrNumero[i]->contraintes.ptrNumero[j]->titre <<  " ";
		}
		cout << endl;
	}
}

