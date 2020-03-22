// Algorithme.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iostream>
#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

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
	PlageTemps(const unsigned Cstart, const unsigned Cend) : Block(Cstart, Cend) {
		blocks[0] = new Block(Cstart, Cend);
		nBlocks++;
	}

	void afficher() {
		if (nBlocks > 1) {
			sortStartOrder();
		}

		for (unsigned i = 0; i < nBlocks; i++) {
			cout << blocks[i]->start << endl << blocks[i]->end << endl;
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


int main()
{
	PlageTemps horraire(480, 1140);
	horraire.afficher();
	cout << endl << endl;
	if (!horraire.removeBlock(Block(490, 900))) {
		cout << "Impossible de retirer ce block de temps a l'horraire" << endl;
	};
	horraire.afficher();
}

