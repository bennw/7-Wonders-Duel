// 7 Wonders Duel
// World class header

#pragma once
#ifndef WORLD_H
#define WORLD_H
#include <string>
#include "Player.h"
#include "MilitaryToken.h"
#include "ProgressToken.h"
#include "Card.h"
#include "Game_Constants.h"

using namespace std;
using namespace Seven_Wonders;

namespace Seven_Wonders {
	
	class World
	{
	public:
		World();
		int getAge();
		void setAge(int age);
		void buildCard(int clickedCardIndex);
		void buildProgressToken(int progressTokenNumber);
		void discardCard(int clickedCardIndex);
		void buildWonder(int wonderNumber, int clickCardIndex);
		void exposeCards();
		vector<Card> age1Deck;
		vector<Card*> wonderCardDeck;
		vector<Card> age2Deck;
		vector<Card> age3Deck;
		vector<Card> guildDeck;
		vector<Card*> discardDeck;
		vector<ProgressToken*> progressTokenDeck;
		vector <ProgressToken*> progressTokenDiscardDeck;

		Card * board[20];

		void Setup();
		int mCurrentPlayer;


		void ExitGame();
		bool checkForNewAge();
		bool checkForScienceVictory(Player & currentPlayer);
		bool canBuild(Player & currentPlayer, Card & card);
		void runCivilianVictory();
		void doEffect(Player & currentPlayer, Card & card);
		int goldCost(Player & currentPlayer, Card & card);

		bool repeatTurn = false;
		bool progressTokenState = false;


		int mAge = 1;
		int mConflict = 0;

		// All game objects
		Player * currentPlayer = nullptr;
		Player player1;
		Player player2;
		MilitaryToken militaryTokenP12;
		MilitaryToken militaryTokenP15;
		MilitaryToken militaryTokenP22;
		MilitaryToken militaryTokenP25;
		ProgressToken progressTokenAgriculture;
		ProgressToken progressTokenArchitecture;
		ProgressToken progressTokenEconomy;
		ProgressToken progressTokenLaw;
		ProgressToken progressTokenMasonry;
		ProgressToken progressTokenMathematics;
		ProgressToken progressTokenPhilosophy;
		ProgressToken progressTokenStrategy;
		ProgressToken progressTokenTheology;
		ProgressToken progressTokenUrbanism;
		Card cardLumberYard;
		Card cardLoggingCamp;
		Card cardClayPool;
		Card cardClayPit;
		Card cardQuarry;
		Card cardStonePit;
		Card cardGlassworks;
		Card cardPress;
		Card cardGuardTower;
		Card cardWorkshop;
		Card cardApothecary;
		Card cardStoneReserve;
		Card cardClayReserve;
		Card cardWoodReserve;
		Card cardStable;
		Card cardGarrison;
		Card cardPalisade;
		Card cardScriptorium;
		Card cardPharmacist;
		Card cardTheater;
		Card cardAltar;
		Card cardBaths;
		Card cardTavern;
		Card cardSawmill;
		Card cardBrickyard;
		Card cardShelfQuarry;
		Card cardGlassBlower;
		Card cardDryingRoom;
		Card cardWalls;
		Card cardForum;
		Card cardCaravansery;
		Card cardCustomsHouse;
		Card cardTribunal;
		Card cardHorseBreeders;
		Card cardBarracks;
		Card cardArcheryRange;
		Card cardParadeGround;
		Card cardLibrary;
		Card cardDispensary;
		Card cardSchool;
		Card cardLaboratory;
		Card cardStatue;
		Card cardTemple;
		Card cardAqueduct;
		Card cardRostrum;
		Card cardBrewery;
		Card cardArsenal;
		Card cardCourthouse;
		Card cardAcademy;
		Card cardStudy;
		Card cardChamberOfCommerce;
		Card cardPort;
		Card cardArmory;
		Card cardPalace;
		Card cardTownHall;
		Card cardObelisk;
		Card cardFortifications;
		Card cardSiegeWorkshop;
		Card cardCircus;
		Card cardUniversity;
		Card cardObservatory;
		Card cardGardens;
		Card cardPantheon;
		Card cardSenate;
		Card cardLighthouse;
		Card cardArena;
		Card cardMerchantsGuild;
		Card cardShipownersGuild;
		Card cardBuildersGuild;
		Card cardMagistratesGuild;
		Card cardScientistsGuild;
		Card cardMoneylendersGuild;
		Card cardTacticiansGuild;
		Card cardTheAppianWay;
		Card cardCircusMaximus;
		Card cardTheColossus;
		Card cardTheGreatLibrary;
		Card cardTheGreatLighthouse;
		Card cardTheHangingGardens;
		Card cardTheMausoleum;
		Card cardPiraeus;
		Card cardThePyramids;
		Card cardTheSphinx;
		Card cardTheStatueOfZeus;
		Card cardTheTempleOfArtemis;

	private:

	};
}

#endif // WORLD_H
