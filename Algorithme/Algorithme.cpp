// Algorithme.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <fstream>

using namespace std;

const unsigned HEURE_ARRIVE = 8 * 60 + 30;
const unsigned HEURE_DEPART = 10*18 * 60 + 30;

const unsigned TEMPS_PRATIQUE = 25;
const unsigned TEMPS_SCENE = 15;



class Block {
	public:
		unsigned start;
		unsigned end;
		unsigned deltaT;
		Block(const unsigned Cstart, const unsigned Cend) {
			start = Cstart;
			end = Cend;
			deltaT = Cend - Cstart;
		}

		void updateDeltaT() {
			deltaT = end - start;
		}
};

class PlageTemps : public Block {
	public:
		unsigned nBlocks = 0;
		Block* blocks[256];
		PlageTemps(char* = nullptr) : Block(NULL,NULL) {};

		PlageTemps(const unsigned Cstart, const unsigned Cend) : Block(Cstart, Cend) {
			blocks[0] = new Block(Cstart, Cend);
			nBlocks++;
		}
	
		void afficher() {
			if (nBlocks==0) {
				cout << "VIDE" << endl;
			}
			else {
				if (nBlocks > 1) {
					sortStartOrder();
				}
				for (unsigned i = 0; i < nBlocks; i++) {
					cout << blocks[i]->start << endl << blocks[i]->end << endl;
				}
			}
		}
	
		bool removeBlock(Block block) {
			bool canRemoveBlock = false;
	
			if ((block.deltaT <= deltaT) && (nBlocks > 0)) {
				if (nBlocks > 1) {
					sortDeltaTOrder();
				}
				for (unsigned i = 0; i < nBlocks; i++) {
					if (block.deltaT < blocks[i]->deltaT) {
						if (block.start > blocks[i]->start && block.end < blocks[i]->end) {
							blocks[nBlocks] = new Block(block.end, blocks[i]->end);
							blocks[i]->end = block.start;
							blocks[i]->updateDeltaT();
							nBlocks++;
							canRemoveBlock = true;
						}
						if (block.start == blocks[i]->start) {
							blocks[i]->start = block.end;
							blocks[i]->updateDeltaT();
							canRemoveBlock = true;
						}
						if (block.end == blocks[i]->end) {
							blocks[i]->end = block.start;
							blocks[i]->updateDeltaT();
							canRemoveBlock = true;
						}
						break;
					}
	
					if (block.deltaT == blocks[i]->deltaT) {
						canRemoveBlock = true;
						delete blocks[i];
						Block* a;
						Block* b;
						for (unsigned j = i; j < nBlocks - 1 - i; j++) {
							a = blocks[j];
							b = blocks[j + 1];
							blocks[j] = b;
							blocks[j + 1] = a;;
						}
						nBlocks--;
						break;
					}
				}
				sortStartOrder();
			}
			return canRemoveBlock;
		}
	
	private:
		void sortStartOrder() {
			for (unsigned i = 0; i < nBlocks; i++) {
				for (unsigned j = 0; j < nBlocks - 1 - i; j++) {
					if (blocks[j]->start > blocks[j + 1]->start) {
						Block* a = blocks[j];
						Block* b = blocks[j + 1];
						blocks[j] = b;
						blocks[j + 1] = a;
					}
				}
			}
		}
	
		void sortDeltaTOrder() {
			for (unsigned i = 0; i < nBlocks; i++) {
				for (unsigned j = 0; j < nBlocks - 1 - i; j++) {
					if (blocks[j]->deltaT > blocks[j + 1]->deltaT) {
						Block* a = blocks[j];
						Block* b = blocks[j + 1];
						blocks[j] = b;
						blocks[j + 1] = a;;
					}
				}
			}
		}
};

class Numero {
	public:
		string titre;
		unsigned nContraintes = 0;
		Numero* contraintes[30];
		PlageTemps dispo; //Manque utilisation et enlever plagebloc de la plage de temps et retirer dispo au contraintes
		
		Numero(string Ctitre) {
			titre = Ctitre;
			dispo = *(new PlageTemps(HEURE_ARRIVE, HEURE_DEPART));
		}
		
		void afficher() {
			cout << titre << " Contraintes : ";
			for (unsigned i = 0; i < nContraintes; i++) {
				cout << contraintes[i] << ", ";
			}
			cout << "\b\b" << endl;
		}

		void addContrainte(Numero* numero) {
			contraintes[nContraintes] = numero;
			nContraintes++;
		}
};

class ListeNumero {
public:
	Numero* numero[30] = {};
	unsigned nNumero = 0;
	
	Numero* searchAdress(const string& titre) {
		Numero* ptrNumero = 0;
		bool notFound = true;
		for (unsigned i = 0; i < nNumero && notFound; i++) {
			if (numero[i]->titre == titre) {
				notFound = false;
				ptrNumero = numero[i];
			}
		}
		return ptrNumero;
	}

	void addContrainte(const string& titre, Numero* numero) {
		numero->addContrainte(searchAdress(titre));
	}
	
	void loadFrom(const string& fileName) {
		ifstream file(fileName);
		file >> nNumero;
		for (unsigned i = 0; i < nNumero; i++) {
			string titre;
			file >> titre;
			Numero* ptrNum = new Numero(titre);
			numero[i] = ptrNum;
		}

		for (unsigned i = 0; i < nNumero; i++) {
			unsigned nContraintes;
			file >> nContraintes;
			for (unsigned j = 0; j < nContraintes; j++) {
				string contrainte;
				file >> contrainte;

				addContrainte(contrainte, numero[i]);
			}
		}
	}

	void afficher() {
		for (unsigned i = 0; i < nNumero; i++) {
			cout << numero[i]->titre << " contraintes : ";
			for (unsigned j = 0; j < numero[i]->nContraintes; j++) {
				cout << numero[i]->contraintes[j]->titre << ", ";
			}
			cout << "\b\b" << endl;
		}
	}
};

class Pratique : public Block {
public:
	Numero* numero;
	Pratique(unsigned cStart, unsigned cEnd, Numero* cNumero)
		: Block(cStart, cEnd)
	{
		numero = cNumero;
	}

	void afficher() {
		cout << start << endl << numero->titre << endl << end << endl;
	}

	unsigned getStart() {
		return start;
	}

	unsigned getEnd() {
		return end;
	}
};

class Salle {
public:
	string nom;
	PlageTemps dispo;
	unsigned nPratiques = 0;
	Pratique* pratiques[30];

	Salle(const unsigned ouverture, const unsigned fermeture, string cNom) {
		nom = cNom;
		dispo = *new PlageTemps(ouverture, fermeture);
	}

	void afficherDispo() {
		dispo.afficher();
	}

	void afficherPratique(){
		for (unsigned i = 0; i < nPratiques; i++) {
			pratiques[i]->afficher();
		}
	}

	bool addPratique(Pratique *ptrPratique) {
		bool canAddPratique = false;
		if (dispo.removeBlock(Block(ptrPratique->getStart(), ptrPratique->getEnd()))) {
			pratiques[nPratiques] = ptrPratique;
			nPratiques++;
			canAddPratique = true;
		}
		return canAddPratique;
	}	
};

class Horraire {
public:
	Horraire() {
		listNumero.loadFrom("save.txt");
		for (unsigned i = 0; i < 3; i++) {
			salles[i] = new Salle(HEURE_ARRIVE, HEURE_DEPART, to_string(i));
		}
	}
	
	void afficher(){
		cout << "\t";
		for(Salle* salle : salles){
			cout << setw(10) <<  salle->nom << " ";
		}
		cout << endl;
		
		unsigned P[] = { 0,0,0 };
		for (unsigned i = HEURE_ARRIVE; i <= HEURE_DEPART; i += 5) {
			cout << i;
			for (unsigned i = 0; i < 3; i++) {
				if (P[i]<salles[i]->nPratiques) {
					if (salles[i]->pratiques[P[i]]->getStart() >= i) {
						cout << setw(10) << salles[i]->pratiques[P[i]]->numero->titre;
					}
					if (salles[i]->pratiques[P[i]]->getEnd() == i) {
						P[i]++;
					}
				}
			}
			cout << endl;
		}
	}

	void organize() {

	}

private:
	ListeNumero listNumero;
	Salle* salles[3] = {};
};


int main()
{
	
	/*PlageTemps horaire(480, 1140);
	horaire.afficher();
	cout << endl << endl;
	if (!horaire.removeBlock(Block(490, 900))) {
		cout << "Impossible de retirer ce block de temps a l'horaire" << endl;
	};
	horaire.afficher();
	cout << endl << endl;
	horaire.removeBlock(Block(480, 490));
	horaire.afficher();
	cout << endl << endl;
	horaire.removeBlock(Block(900, 1140));
	horaire.afficher();*/

	/*ListeNumero listeNumero;
	listeNumero.loadFrom("save.txt");
	listeNumero.afficher();*/

	Horraire horraire;
	horraire.organize();
	horraire.afficher();


}

