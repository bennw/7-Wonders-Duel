// 7 Wonders Duel
// Player Class header

#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include "Game_Constants.h"
#include "Card.h"
#include "ProgressToken.h"
#include <map>
#include <vector>
using namespace std;

namespace Seven_Wonders {

	class Player
	{
	public:
		Player(int playerNumber);
		~Player();
		void constructorDebug();
		int getPlayerNumber() const;
		void setGoesFirst(bool goesfirst);
		bool getGoesFirst() const;
		int getCoins() const;
		void setCoins(int changeInCoins);
		int getWood() const;
		void setWood(int changeInWood);
		int getStone() const;
		void setStone(int changeInStone);
		int getClay() const;
		void setClay(int changeInClay);
		int getPapyrus() const;
		void setPapyrus(int changeInPapyrus);
		int getGlass() const;
		void setGlass(int changeInGlass);
		int getWildBasic() const;
		int getWildAdv() const;
		int getDiscardGoldValue();
		void resetResources();
		bool hasUnbuiltMausoleum();
		bool hasUnbuiltLibrary();
		vector<Card*> playerCity;
		vector<Card*> playerWonderDeck;
		//vector<ProgressToken*> playerPTDeck;
		ProgressToken* playerPT1=nullptr;
		ProgressToken* playerPT2=nullptr;
		ProgressToken* playerPT3=nullptr;
		ProgressToken* playerPT4=nullptr;
		ProgressToken* playerPT5=nullptr;
		vector <ProgressToken*> playerPT = { playerPT1, playerPT2, playerPT3, playerPT4, playerPT5 };

		struct scienceSymbols
		{
			int arch = 0;
			int mortar = 0;
			int quill = 0;
			int wheel = 0;
			int sundial = 0;
			int globe = 0;
			int balance = 0;
		};

		struct flags
		{
			bool woodTradeFlag = false;
			bool stoneTradeFlag = false;
			bool clayTradeFlag = false;
			bool papyrusTradeFlag = false;
			bool glassTradeFlag = false;
			bool architecturePTFlag = false;
			bool economyPTFlag = false;
			bool masonryPTFlag = false;
			bool mathematicsPTFlag = false;
			bool philsophyPTFlag = false;
			bool strategyPTFlag = false;
			bool theologyPTFlag = false;
			bool ubanismPTFlag = false;
			bool forumResourcesFlag = false;
			bool caravenseryResourcesFlag = false;
			bool theGreatLighthouseResourcesFlag = false;
			bool piraeusResourcesFlag = false;
			bool merchantsGuildFlag = false;
			bool shipownersGuildFlag = false;
			bool buildersGuildFlag = false;
			bool magistratesGuildFlag = false;
			bool scientistsGuildFlag = false;
			bool moneylendersGuildFlag = false;
			bool tacticiansGuildFlag = false;
		};

		scienceSymbols scienceSymbols;
		flags flags;
	private:
		int mPlayerNumber;
		bool mGoesFirst;
		int mCoins = 7;
		int mWood = 0;
		int mStone = 0;
		int mClay = 0;
		int mPapyrus = 0;
		int mGlass = 0;
		bool mStrategyFlag = false;
		
		static const int STARTING_COINS = 7;
		static const int STARTING_ALL_OTHERS = 0;

	};

}

#endif // PLAYER_H
