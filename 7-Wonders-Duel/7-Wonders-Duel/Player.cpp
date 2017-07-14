// 7 Wonders Duel 
// Player class functions
// Playing with pointers

#include "Player.h"
#include <stdarg.h>
#include <iostream>
using namespace std;

Player::Player(int playerNumber) // constructor will need to set all starting resource values
{
	if (playerNumber == PLAYER_1) 
	{
		mPlayerNumber = PLAYER_1;
		setGoesFirst(true); // for now Player 1 will go first
	}
	else if (playerNumber == PLAYER_2)
	{
		mPlayerNumber = PLAYER_2;
		setGoesFirst(false);
	}

	int * p_startingResources; // pointer to integer array for starting resources
	p_startingResources = new (nothrow) int[6]; // pointer to integer array for starting resources
	if (p_startingResources == nullptr) // error-handling
	{
		cout << "Could not allocate memory for player creation...exiting..." << endl;
		system("pause");
		EXIT_FAILURE;
	}
	p_startingResources[0] = STARTING_COINS; // starting gold
	for (int i = 0; i < 5; i++) // assigning zero to each other resource
	{
		p_startingResources[1 + i] = STARTING_ALL_OTHERS;
	}

	setCoins(p_startingResources[0]);
	setWood(p_startingResources[1]);
	setStone(p_startingResources[2]);
	setClay(p_startingResources[3]);
	setPapyrus(p_startingResources[4]);
	setGlass(p_startingResources[5]);

	constructorDebug();
	system("pause");

	delete [] p_startingResources;
	p_startingResources = nullptr;
}

Player::~Player()
{
	cout << "Player destroyed"; // for debugging
}

void Player::constructorDebug()
{
	cout << "Created Player, #" << getPlayerNumber() << ", with the following starting resources:" << endl <<
		"Coins: " << getCoins() << endl <<
		"Wood: " << getWood() << endl <<
		"Stone: " << getStone() << endl <<
		"Clay: " << getClay() << endl <<
		"Papyrus: " << getPapyrus() << endl <<
		"Glass: " << getGlass() << endl << endl;
}

int Player::getPlayerNumber()
{
	return mPlayerNumber;
}

void Player::setGoesFirst(bool goesfirst)
{
	mGoesFirst = goesfirst;
}

bool Player::getGoesFirst()
{
	return mGoesFirst;
}

int Player::getCoins()
{
	return mCoins;
}

void Player::setCoins(int changeInCoins)
{
	mCoins = mCoins + changeInCoins;
}

int Player::getWood()
{
	return mWood;
}

void Player::setWood(int changeInWood)
{
	mWood = mWood + changeInWood;
}

int Player::getStone()
{
	return mStone;
}

void Player::setStone(int changeInStone)
{
	mStone = mStone + changeInStone;
}

int Player::getClay()
{
	return mClay;
}

void Player::setClay(int changeInClay)
{
	mClay = mClay + changeInClay;
}

int Player::getPapyrus()
{
	return mPapyrus;
}

void Player::setPapyrus(int changeInPapyrus)
{
	mPapyrus = mPapyrus + changeInPapyrus;
}

int Player::getGlass()
{
	return mGlass;
}

void Player::setGlass(int changeInGlass)
{
	mGlass = mGlass + changeInGlass;
}


