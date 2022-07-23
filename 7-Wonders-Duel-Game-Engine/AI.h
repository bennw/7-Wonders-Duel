#pragma once
#include "BoardState.h"

class AI
{
public:
	AI();
	~AI();

	void attachBoardState(BoardState* bs);
	void updateEV();
	void updateDiscardEV(int age);
	void updateRequiredOwnedResources(int p);

	// internal state variables, used in AI computation
	int requiredWood[2] = { 0 };
	int requiredStone[2] = { 0 };
	int requiredClay[2] = { 0 };
	int requiredPaper[2] = { 0 };
	int requiredGlass[2] = { 0 };
	int ownedWood[2] = { 0 };
	int ownedStone[2] = { 0 };
	int ownedClay[2] = { 0 };
	int ownedPaper[2] = { 0 };
	int ownedGlass[2] = { 0 };
	int ownedWildBasic[2] = { 0 };
	int ownedWildAdv[2] = { 0 };
	bool wonderHasBasic[2] = { 0 };
	bool wonderHasAdv[2] = { 0 };
	int discardGoldValue[2] = { 2 };
	bool hasAllBasic[2] = { 0 };
	bool hasAllAdv[2] = { 0 };

	int cardTriggerExpose[20][2] = { -1 }; // [c][0] = left card, [c][1] = right card, -1 = no trigger
private:
	BoardState* bstate;
};