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

void AI::updateEV()
{
	int EV = 0;
	int conflict;
	int sciSymbol, blueVP, redSwords;
	int age = 1;
	int opponentEV[2][2] = { -100 }; // [h][p], where h = 0/1: 1st and 2nd highest opponent EVs, p = 0/1: player 1/2
	ResourceType resource;
	vector<int> idxCardExposed;

	for (int p = 0; p < 2; ++p)
	{
		updateRequiredOwnedResources(p);

		for (int c = 0; c < 20; ++c)
		{
			if (bstate->board[c] == nullptr)
			{
				bstate->cardEV[c][p] = -101;
				continue;
			}

			if (bstate->board[c]->getIndex() <= IdxSawmill) age = 1;
			else if (bstate->board[c]->getIndex() <= IdxBrewery) age = 2;
			else age = 3;

			// Age 1-3: establish baseline play EV for all cards
			EV = 0;
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
				// AGE 2
			case IdxLaboratory:
				sciSymbol = 0; // arch
				goto green_card_age_2;
			case IdxDispensary:
				sciSymbol = 1; // mortar
				goto green_card_age_2;
			case IdxLibrary:
				sciSymbol = 2; // quill
				goto green_card_age_2;
			case IdxSchool:
				sciSymbol = 4; // wheel
			green_card_age_2:
				EV = 98;
				if (bstate->sciOwned[sciSymbol][p] == 1) EV = 100;
				break;
			case IdxBrewery:
				EV = 95;
				break;
			case IdxCustomsHouse:
				EV = 94 - 10 * (ownedGlass[p] + ownedPaper[p] + ownedWildAdv[p]);
				break;
			case IdxCaravansery:
				EV = 93;
				if (hasAllBasic[p]) EV -= 20;
				break;
			case IdxForum:
				EV = 92;
				if (hasAllAdv[p]) EV -= 20;
				break;
			case IdxSawmill:
				if (ownedWood[p] == 0 && ownedWildBasic[p] == 0) EV = 89;
				break;
			case IdxBrickyard:
				if (ownedClay[p] == 0 && ownedWildBasic[p] == 0) EV = 89;
				break;
			case IdxShelfQuarry:
				if (ownedStone[p] == 0 && ownedWildBasic[p] == 0) EV = 89;
				break;
			case IdxDryingRoom:
				if (ownedPaper[p] == 0 && ownedWildAdv[p] == 0) EV = 88;
				break;
			case IdxGlassBlower:
				if (ownedGlass[p] == 0 && ownedWildAdv[p] == 0) EV = 88;
				break;

			case IdxTribunal:
			case IdxAqueduct:
			case IdxTemple:
				blueVP = 5;
				goto blue_card_age_2;
			case IdxStatue:
			case IdxRostrum:
				blueVP = 4;
			blue_card_age_2:
				EV = 77 - 10 * (6 - blueVP) - 7 * bstate->cardCost[c][p];
				break;

			case IdxHorseBreeders:
			case IdxBarracks:
				redSwords = 1;
				goto red_card_age_2;
			case IdxArcheryRange:
			case IdxParadeGround:
			case IdxWalls:
				redSwords = 2;
			red_card_age_2:
				EV = 78 - 20 * (2 - redSwords) - 7 * bstate->cardCost[c][p];
				break;
			default:
				EV = 0;
				break;
			}

			// Age 2: reduce play EV if it triggers exposes for currently exposed cards
			int l, r;
			if (age == 2)
			{
				if (bstate->cardState[c] == 3)
				{
					l = cardTriggerExpose[c][0];
					r = cardTriggerExpose[c][1];
					if (l != -1 && bstate->cardState[l] == 2 && bstate->cardEV[l][1] >= 90) {
						bstate->cardEV[l][1] -= 90;
					}
					if (r != -1 && bstate->cardState[r] == 2 && bstate->cardEV[r][1] >= 90) {
						bstate->cardEV[l][1] -= 90;
					}
				}
			}
			bstate->cardEV[c][p] = EV;
		}
	}

	// Age 1-3: establish discard EV for exposed cards
	for (int c = 0; c < 20; ++c)
	{
		if (bstate->board[c] == nullptr || bstate->cardState[c] != 3)
		{
			bstate->cardDiscardEV[c][0] = -1;
			bstate->cardDiscardEV[c][1] = -1;
			continue;
		}
		else
		{
			idxCardExposed.push_back(c);
			for (int p = 0; p < 2; ++p)
			{
				if (bstate->cardEV[c][1-p] > opponentEV[0][p])
				{
					opponentEV[1][p] = opponentEV[0][p];
					opponentEV[0][p] = bstate->cardEV[c][1 - p];
				}
				else if (bstate->cardEV[c][1] > opponentEV[1][p])
				{
					opponentEV[1][p] = bstate->cardEV[c][1 - p];
				}
			}
		}
	}
	for (int& c : idxCardExposed)
	{
		for (int p = 0; p < 2; ++p)
		{
			// max opponent EV of all exposed cards sans card idx
			int l = cardTriggerExpose[c][0];
			int r = cardTriggerExpose[c][1];
			int maxOpponentEVAfterDiscard = opponentEV[0][p];
			if (bstate->cardEV[c][1-p] == opponentEV[0][p]) maxOpponentEVAfterDiscard = opponentEV[1][p];

			// now factor in cards newly exposed if card idx is discarded; facedowns have an opponent EV of 91
			if (l != -1)
			{
				if (bstate->cardState[l] == 1) maxOpponentEVAfterDiscard = max(91, maxOpponentEVAfterDiscard);
				else maxOpponentEVAfterDiscard = max(bstate->cardEV[l][1-p], maxOpponentEVAfterDiscard);
			}
			if (r != -1)
			{
				if (bstate->cardState[r] == 1) maxOpponentEVAfterDiscard = max(91, maxOpponentEVAfterDiscard);
				else maxOpponentEVAfterDiscard = max(bstate->cardEV[r][1-p], maxOpponentEVAfterDiscard);
			}

			bstate->cardDiscardEV[c][p] = 100 - maxOpponentEVAfterDiscard;
			if (bstate->cardDiscardEV[c][p] > 100) bstate->cardDiscardEV[c][p] = 100;
			if (bstate->cardDiscardEV[c][p] < 0) bstate->cardDiscardEV[c][p] = 0;
		}
	}

	updateDiscardEV(age);
}

void AI::updateDiscardEV(int age)
{
	// TODO: ideally this shouldn't be based on age
	for (int p = 0; p < 2; ++p)
	{
		if (bstate->playerCoins[p] > 2)
		{
			if (age == 1) bstate->discardEV[p] = 30;
			else bstate->discardEV[p] = 0;
		}
		else
		{
			if (age == 1) bstate->discardEV[p] = 50 - 10 * bstate->playerCoins[p];
			else bstate->discardEV[p] = 20 - 10 * bstate->playerCoins[p];
		}
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

vector<int> AI::wonderSelectAI(const vector<Card*> &wonderList)
{
	vector<int> result;
	vector<int> wonderEV;
	int EV;

	for (const Card* c : wonderList)
	{
		switch (c->getIndex())
		{
		case IdxPiraeus:
			EV = 100;
			break;
		case IdxArtemis:
			EV = 99;
			break;
		case IdxHangingGardens:
			EV = 98;
			break;
		case IdxAppianWay:
			EV = 97;
			break;
		case IdxSphinx:
			EV = 90;
			break;
		case IdxMausoleum:
			EV = 89;
			break;
		case IdxGreatLibrary:
			EV = 88;
			break;
		case IdxGreatLighthouse:
			EV = 87;
			break;
		case IdxColossus:
			EV = 86;
			break;
		case IdxZeus:
			EV = 85;
			break;
		case IdxCircusMaximus:
			EV = 84;
			break;
		case IdxPyramids:
			EV = 70;
			break;
		}
		wonderEV.push_back(EV);
	}

	for (int i = 0; i < 8; i += 4)
	{
		for (int jj = 0; jj < 4; ++jj)
		{
			int maxEV = 0;
			int maxIdx = -1;
			for (int j = 0; j < 4; ++j)
			{
				if (wonderEV[i + j] > maxEV)
				{
					maxEV = wonderEV[i + j];
					maxIdx = i + j;
				}
			}
			// push best EV wonder into result
			result.push_back(maxIdx);
			wonderEV[maxIdx] = -1;
		}
	}
	return result;
}