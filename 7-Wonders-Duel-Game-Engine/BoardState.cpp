#include "BoardState.h"

using namespace std;
using namespace Seven_Wonders;

BoardState::BoardState()
{
}
BoardState::~BoardState() {}

void BoardState::attachWonders(int p, vector<Card*>& wonders)
{
	for (int i = 0; i < 4; ++i)
	{
		wonder[i][p] = wonders[i];
	}
}

void BoardState::attachBoard(Card** _board)
{
	board = _board;
}