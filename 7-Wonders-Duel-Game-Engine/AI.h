#pragma once
#include "BoardState.h"

class AI
{
public:
	AI();
	~AI();

	void attachBoardState(BoardState* bs);
	void updateEV(int p); // p: player1/2 = 0/1
	void updateDiscardEV(int p);
	void updateRequiredOwnedResources(int p);

	// internal state variables, used in AI computation
	int requiredWood[2] = { 0 };
	int requiredClay[2] = { 0 };
	int requiredStone[2] = { 0 };
	int requiredPaper[2] = { 0 };
	int requiredGlass[2] = { 0 };
	int ownedWood[2] = { 0 };
	int ownedClay[2] = { 0 };
	int ownedStone[2] = { 0 };
	int ownedPaper[2] = { 0 };
	int ownedGlass[2] = { 0 };
	bool wonderHasBasic[2] = { 0 };
	bool wonderHasAdv[2] = { 0 };
	int discardGoldValue[2] = { 2 };
	bool hasAllBasic = false;
	bool hasAllAdv = false;

private:
	BoardState* bstate;
};