// Algorithme.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iostream>
#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

const unsigned HEURE_ARRIVE = 8 * 60 + 30;
const unsigned HEURE_DEPART = 6 * 60 + 30;

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
};

class PlageTemps : public Block {
	public:
		unsigned nBlocks = 0;
		Block* blocks[256];
		PlageTemps();
		
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
						canRemoveBlock = true;
						if (block.start > blocks[i]->start && block.end < blocks[i]->end) {
							blocks[nBlocks] = new Block(block.end, blocks[i]->end);
							blocks[i]->end = block.start;
							nBlocks++;
						}
						if (block.start == blocks[i]->start) {
							blocks[i]->start = block.end;
						}
						if (block.end == blocks[i]->end) {
							blocks[i]->end = block.start;
						}
						break;
					}
	
					if (block.deltaT == blocks[i]->deltaT) {
						canRemoveBlock = true;
						delete blocks[i];
						nBlocks--;
						break;
					}
				}
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
						blocks[j + 1] = a;;
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

class Pratique : Block {
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

	private:
		unsigned nPratiques = 0;
		Pratique* pratiques[30];

};




int main()
{
	PlageTemps horraire(480, 1140);
	horraire.afficher();
	cout << endl << endl;
	if (!horraire.removeBlock(Block(480, 900))) {
		cout << "Impossible de retirer ce block de temps a l'horraire" << endl;
	};
	horraire.afficher();
}

