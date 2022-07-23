#include "AI.h"
#include "CardDefine.h"

enum class ResourceType
{
	Wood,
	Clay,
	Stone,
	Paper,
	Glass
};

AI::AI() 
{
	bstate = nullptr;
}
AI::~AI() {}

void AI::attachBoardState(BoardState* bs)
{
	bstate = bs;
}

void AI::updateEV(int p)
{
	int EV = 0;
	int conflict;
	ResourceType resource;

	updateRequiredOwnedResources(p);

	for (int c = 0; c < 20; ++c)
	{
		if (bstate->board[c] == nullptr)
		{
			bstate->cardEV[c][p] = -101;
			continue;
		}

		switch (bstate->board[c]->getIndex())
		{
		case IdxTavern:
			EV = 100;
			break;
		case IdxLoggingCamp:
		case IdxLumberYard:
			resource = ResourceType::Wood;
			goto brown_card_ev;
		case IdxClayPool:
		case IdxClayPit:
			resource = ResourceType::Clay;
			goto brown_card_ev;
		case IdxQuarry:
		case IdxStonePit:
			resource = ResourceType::Stone;
brown_card_ev:
			EV = 95;
			// -10 if not critical
			// -70 if dupe
			if (resource == ResourceType::Wood)
			{
				if (requiredWood[p] < 1) EV -= 10;
				if (ownedWood[p] >= 1) EV -= 70;
			}
			else if (resource == ResourceType::Clay)
			{
				if (requiredClay[p] < 1) EV -= 10;
				if (ownedClay[p] >= 1) EV -= 70;
			}
			else if (resource == ResourceType::Stone)
			{
				if (requiredStone[p] < 1) EV -= 10;
				if (ownedStone[p] >= 1) EV -= 70;
			}
			// -10 if wonder 
			if (wonderHasBasic[p]) EV -= 10;
			// -20 if 1 cost
			if (bstate->cardCost[c][p] > 0) EV -= 20;
			break;
		case IdxGlassworks:
			resource = ResourceType::Glass;
			goto silver_card_ev;
		case IdxPress:
			resource = ResourceType::Paper;
silver_card_ev:
			EV = 93;
			// -10 if not critical
			// -70 if dupe
			if (resource == ResourceType::Paper)
			{
				if (requiredPaper[p] < 1) EV -= 10;
				if (ownedPaper[p] >= 1) EV -= 70;
			}
			else if (resource == ResourceType::Glass)
			{
				if (requiredGlass[p] < 1) EV -= 10;
				if (ownedGlass[p] >= 1) EV -= 70;
			}
			// -10 if wonder
			if (wonderHasAdv[p]) EV -= 10;
			break;
		case IdxStoneReserve:
			resource = ResourceType::Stone;
			goto reserve_card_ev;
		case IdxClayReserve:
			resource = ResourceType::Clay;
			goto reserve_card_ev;
		case IdxWoodReserve:
			resource = ResourceType::Wood;
		reserve_card_ev:
			EV = 97;
			// -10 per already owned yellow
			EV -= 10 * (discardGoldValue[p] - 2);
			// -70 if not multicritical
			if (resource == ResourceType::Wood)
			{
				// no law
				if (bstate->sciUnavailable[6][p] == 1 && bstate->sciOwned[6][p] == 0) {
					if (requiredWood[p] - ownedWood[p] < 1) EV -= 70;
				}
			}
			else if (resource == ResourceType::Clay)
			{
				if (requiredClay[p] - ownedClay[p] < 1) EV -= 70;
			}
			else if (resource == ResourceType::Stone)
			{
				if (requiredStone[p] - ownedStone[p] < 1) EV -= 70;
			}
			break;
		case IdxScriptorium:
		case IdxPharmacist:
			EV = 91;
			break;
		case IdxWorkshop:
		case IdxApothecary:
			EV = 90;
			break;
		case IdxGuardTower:
		case IdxStable:
		case IdxGarrison:
		case IdxPalisade:
			EV = 0;
			conflict = bstate->conflict;
			if (p == 1) conflict *= -1;
			if (conflict <= -2 && bstate->cardCost[c][p] == 0 && bstate->playerCoins[p] > 2) EV = 59;
			break;
		case IdxTheater:
		case IdxAltar:
		case IdxBaths:
			EV = 0;
			if ((bstate->sciUnavailable[6][p] == 1 && bstate->sciOwned[6][p] == 0) && bstate->cardCost[c][p] == 0 && bstate->playerCoins[p] > 2) EV = 57;
			break;
		default:
			EV = 0;
			break;
		}
		bstate->cardEV[c][p] = EV;
	}

	updateDiscardEV(p);
}

void AI::updateDiscardEV(int p)
{
	if (bstate->playerCoins[p] > 2)
	{
		bstate->discardEV[p] = 30;
	}
	else
	{
		bstate->discardEV[p] = 50 - 10 * bstate->playerCoins[p];
	}
}

void AI::updateRequiredOwnedResources(int p)
{
	for (int w = 0; w < 4; ++w)
	{
		requiredWood[p] = max(requiredWood[p], bstate->wonder[w][p]->getWoodCost());
		requiredClay[p] = max(requiredClay[p], bstate->wonder[w][p]->getClayCost());
		requiredStone[p] = max(requiredStone[p], bstate->wonder[w][p]->getStoneCost());
		requiredPaper[p] = max(requiredPaper[p], bstate->wonder[w][p]->getPapyrusCost());
		requiredGlass[p] = max(requiredGlass[p], bstate->wonder[w][p]->getGlassCost());
		if (bstate->wonder[w][p]->getIndex() == 80) // piraeus
			wonderHasAdv[p] = 1;
		if (bstate->wonder[w][p]->getIndex() == 77) // great lighthouse
			wonderHasBasic[p] = 1;
	}
}