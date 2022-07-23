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
		short cardState[20] = { 0 }; // 0 = NULL, 1 = facedown, 2 = faceup, 3 = exposed
		int cardNumBlocked[20] = { 0 }; // number of cards directly blocking it, possible defined values = 0-2
		int wonderCost[4][2] = { 0 };
		int wonderAfford[4][2] = { 0 };
		short wonderBuilt[4][2] = { 0 }; // 0 = unbuilt, 1 = built
		int conflict; // negative = P2 winning, positive = P1 winning
		int discardEV[2] = { 0 };

		int sciDiscarded[7] = { 0 };
		int sciOwned[7][2] = { 0 };
		bool sciUnavailable[7][2] = {0};
	private:
	};

}