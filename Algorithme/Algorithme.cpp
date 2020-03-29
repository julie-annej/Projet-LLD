// Algorithme.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <fstream>

using namespace std;

const unsigned HEURE_ARRIVE = 8 * 60 + 30;
const unsigned HEURE_DEPART = 960;

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

		Block interBlock(Block* block2) {
			unsigned newStart = 0, newEnd = 0;
			if (end >= block2->start && block2->end >= start) {
				if (start <= block2->start) {
					newStart = block2->start;
				}
				if (block2->start < start) {
					newStart = start;
				}

				if (end <= block2->end) {
					newEnd = end;
				}
				if (block2->end < end) {
					newEnd = block2->end;
				}
			}
			return Block(newStart, newEnd);
		}
};

class PlageTemps : public Block {
	public:
		const unsigned nBlockMax = 256;
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
	
		bool removeBlock(const Block block) {
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
		
		void removeWOSecu(Block block) {
			if (nBlocks > 0) {
				if (nBlocks > 1) {
					sortStartOrder();
				}

				for (unsigned i = 0; i < nBlocks; i++) {
					if (blocks[i]->end >= block.start && block.end >= blocks[i]->start) {
						if (block.start > blocks[i]->start && block.end < blocks[i]->end) {
							blocks[nBlocks] = new Block(block.end, blocks[i]->end);
							blocks[i]->end = block.start;
							blocks[i]->updateDeltaT();
							nBlocks++;
						}

						if (block.start <= blocks[i]->start && block.end < blocks[i]->end) {
							blocks[i]->start = block.end;
							blocks[i]->updateDeltaT();
						}
						if (blocks[i]->end <= block.end && blocks[i]->start < block.start) {
							blocks[i]->end = block.start;
							blocks[i]->updateDeltaT();
						}


						if (blocks[i]->start >= block.start && blocks[i]->end <= block.end) {
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
				}
				sortStartOrder();
			}
		}

		PlageTemps reverse() { // a verifier
			PlageTemps reverse(start,end);
			for (unsigned i = 0; i < nBlocks; i++) {
				reverse.removeWOSecu(*blocks[i]);
			}
			return reverse;
		}

		PlageTemps interPlage(PlageTemps& plageTemps1) {
			Block interPlageBlock = this->interBlock(&plageTemps1);
			PlageTemps plageCommuneReverse = PlageTemps(interPlageBlock.start, interPlageBlock.end);
			
			/*cout << "Plage commune : ";
			plageCommune.afficher();*/
			//if (end >= plageTemps1.start && plageTemps1.end >= start) {
			
			if (interPlageBlock.deltaT > 0) {
				for (unsigned i = 0; i < nBlocks; i++) {
					for (unsigned j = 0; j < plageTemps1.nBlocks; j++) {
						Block inter = blocks[i]->interBlock(plageTemps1.blocks[j]);
						//cout << inter.start << " " << inter.end << endl;
						if (inter.deltaT > 0) {
							plageCommuneReverse.removeWOSecu(inter);
						}
					}
				}
			}
			PlageTemps plageCommuneVrai = plageCommuneReverse.reverse();
			/*cout << "Plage commune : ";
			plageCommune.afficher();*/
			return plageCommuneVrai;
		}	
};

class Numero {
	public:
		string titre;
		unsigned nContraintes = 0;
		Numero* contraintes[30];
		unsigned nContraintesAPlacer = 0;
		PlageTemps *dispo;

		Numero(string Ctitre) {
			titre = Ctitre;
			dispo = new PlageTemps(HEURE_ARRIVE, HEURE_DEPART);
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
			nContraintesAPlacer++;
		}

		void removeBlockDispo(Block block) {
			dispo->removeBlock(block);
			
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

	void sortbyNContraintesAPlacer(unsigned from) {
		for (unsigned i = from; i < nNumero; i++) {
			for (unsigned j = from; j < nNumero - 1 - i; j++) {
				if (numero[j]->nContraintesAPlacer < numero[j + 1]->nContraintesAPlacer) {
					Numero* a = numero[j];
					Numero* b = numero[j + 1];
					numero[j] = b;
					numero[j + 1] = a;
				}
			}
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
		numero->removeBlockDispo(Block(cStart, cEnd));
		for (unsigned i = 0; i < numero->nContraintes; i++) {
			numero->contraintes[i]->removeBlockDispo(Block(cStart, cEnd));
			numero->contraintes[i]->nContraintesAPlacer--;
		}

	}

	void afficher() {
		cout << start << endl << numero->titre << endl << end << endl << endl;
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
	PlageTemps * dispo;
	unsigned nPratiques = 0;
	Pratique* pratiques[30];

	Salle(const unsigned ouverture, const unsigned fermeture, const string cNom) {
		nom = cNom;
		dispo = new PlageTemps(ouverture, fermeture);
	}

	void afficherDispo() {
		dispo->afficher();
	}

	void afficherPratiques(){
		for (unsigned i = 0; i < nPratiques; i++) {
			pratiques[i]->afficher();
		}
	}

	bool addPratique(Pratique* pratique) {
		bool canAddPratique = false;
		
		if (dispo->removeBlock(Block(pratique->getStart(), pratique->getEnd()))) {
			pratiques[nPratiques] = pratique;
			nPratiques++;
			canAddPratique = true;
		}

		return canAddPratique;
	}

	void sortPratiquesStartOrder() {
		for (unsigned i = 0; i < nPratiques; i++) {
			for (unsigned j = 0; j < nPratiques - 1 - i; j++) {
				if (pratiques[j]->start > pratiques[j + 1]->start) {
					Pratique* a = pratiques[j];
					Pratique* b = pratiques[j + 1];
					pratiques[j] = b;
					pratiques[j + 1] = a;
				}
			}
		}
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
		
		for(Salle* salle : salles){
			cout << setw(20) <<  salle->nom << " ";
			salle->sortPratiquesStartOrder();
		}
		cout << endl;
		
		unsigned P[] = { 0, 0, 0 };
		for (unsigned t = HEURE_ARRIVE; t <= HEURE_DEPART; t += 5) {
			cout << t;
			for (unsigned i = 0; i < 3; ++i) {
				if (P[i]<salles[i]->nPratiques) {
					if (salles[i]->pratiques[P[i]]->getStart() <= t) {
						cout << setw(25) << salles[i]->pratiques[P[i]]->numero->titre;
					}
					if (salles[i]->pratiques[P[i]]->getEnd() == t+5) {
						P[i]++;
					}
				}
			}
			cout << endl;
		}
	}

	//void afficher() {
	//	for (Salle* salle : salles) {
	//		cout << setw(10) << salle->nom << " ";
	//	}
	//	for (Salle* salle : salles) {
	//		salle->afficherPratiques();
	//	}
	//}
	
	Block bestBlockInBestSalle(unsigned& bestSalle, Numero* numero, const unsigned duree) {
		unsigned startMin = 10000000;
		for (unsigned i = 0; i < 2; i++) {
			PlageTemps interDispo = salles[i]->dispo->interPlage(*numero->dispo);
			
			interDispo.sortStartOrder();
			/*cout << numero->titre << " Reeldispo : ";
			interDispo.afficher();*/
			for (unsigned j = 0; j < interDispo.nBlocks; j++) {
				
				if (interDispo.blocks[j]->start < startMin &&
					interDispo.blocks[j]->deltaT >= TEMPS_PRATIQUE)
				{
					bestSalle = i;
					startMin = interDispo.blocks[j]->start;
				}
			}
		}
		return Block(startMin, startMin + duree);
	}

	Block bestBlockInScene(Numero* numero, const unsigned duree) {
		PlageTemps interDispo = salles[2]->dispo->interPlage(*numero->dispo);
		interDispo.sortStartOrder();
		
		unsigned startMin = 10000000;

		for (unsigned i = 0; i < interDispo.nBlocks; i++) {
			if (interDispo.blocks[i]->start < startMin &&
				interDispo.blocks[i]->deltaT >= TEMPS_PRATIQUE)
			{
				startMin = interDispo.blocks[i]->start;
			}
		}
		
		return Block(startMin, startMin + duree);
	}

	void organize() {
		for (unsigned i = 0; i < listNumero.nNumero; i++) {
			listNumero.sortbyNContraintesAPlacer(i);
			unsigned bestSalle = 0;
			Block bestSalleBlock = bestBlockInBestSalle(bestSalle, listNumero.numero[i], TEMPS_PRATIQUE);
			Pratique* pratiqueSalle = new Pratique(bestSalleBlock.start, bestSalleBlock.end, listNumero.numero[i]);
			cout << "Salle : " << bestSalle << endl;
			pratiqueSalle->afficher();
			
			salles[bestSalle]->addPratique(pratiqueSalle);
			
			Block bestSceneBlock = bestBlockInScene(listNumero.numero[i], TEMPS_SCENE);
			Pratique* pratiqueScene = new Pratique(bestSceneBlock.start, bestSceneBlock.end, listNumero.numero[i]);
			cout << "Scene : " << endl;
			pratiqueScene->afficher();
			salles[2]->addPratique(pratiqueScene);
		}
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

	//PlageTemps p1(480, 1140);
	//PlageTemps p2(600, 900);
	//p2.removeWOSecu(Block(700, 800));
	//PlageTemps interP = p1.interPlage(p2); //marche pour tout les cas
	//interP.afficher();

	//cout << endl;

	//p1.removeWOSecu(Block(700, 1000));//marche
	//p1.afficher();

	/*Block b1(480, 900);
	Block b2(901, 1000);

	Block interB = b1.interBlock(&b2);
	cout << interB.start << " " << interB.end << endl;*/ // working 


	Horraire horraire;
	horraire.organize();
	horraire.afficher();


}

