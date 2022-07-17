// 7 Wonders Duel 
// Card Properties arrays
// This may not be the best way to do this but it should work for now

#pragma once
#include <iostream>
#include <string>

namespace Seven_Wonders {

	// Order is by index of cards, found in Game_Constants.h

	extern const std::string cardName[85];

	extern const int cardAge[85];

	extern const int cardType[85];

	extern const int coinCost[85];

	extern const int woodCost[85];

	extern const int stoneCost[85];

	extern const int clayCost[85];

	extern const int papyrusCost[85];

	extern const int glassCost[85];

	extern const int linkValues[85];

	//created for those cards that have two linkers statue and temple double linking abilities.
	extern const int linkValues2[85];

}







