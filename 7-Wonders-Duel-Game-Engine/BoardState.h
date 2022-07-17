#pragma once
#include "Card.h"

using namespace std;
using namespace Seven_Wonders;

namespace Seven_Wonders {

	class BoardState
	{
	public:
		BoardState();
		~BoardState();

		void attachBoard(Card** _board);
		void attachWonders(int p, vector<Card*>& wonders); // Player1/2: p=0/1

		Card** board; // size 20
		Card* wonder[4][2] = { nullptr };

		int playerCoins[2] = { 0 };
		int cardCost[20][2] = { 0 };
		bool cardAfford[20][2] = { 0 };
		bool cardLinked[20][2] = { 0 };
		int cardEV[20][2] = { 0 }; // AI, max 100
		short cardState[20][2] = { 0 }; // 0 = NULL, 1 = facedown, 2 = faceup, 3 = exposed
		int wonderCost[4][2] = { 0 };
		int wonderAfford[4][2] = { 0 };
		short wonderBuilt[4][2] = { 0 }; // 0 = unbuilt, 1 = built
	private:
	};

}