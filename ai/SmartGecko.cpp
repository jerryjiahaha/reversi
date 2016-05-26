#include <iostream>

#include "reversi_ai.h"

#define NUM_CELL_X        8
#define NUM_CELL_Y        8

#define AA_USE_HIRES      0
#define AA_FACTOR         1

#if AA_USE_HIRES
#define AA_CALCFACTOR   AA_FACTOR
#else
#define AA_CALCFACTOR   1
#endif

static const int _xs[60] = {
	7, 7, 0, 0, 7, 7, 5, 5, 2, 2,
	0, 0, 5, 5, 2, 2, 5, 5, 4, 4,
	3, 3, 2, 2, 7, 7, 4, 4, 3, 3,
	0, 0, 6, 6, 6, 6, 5, 5, 4, 4,
	3, 3, 2, 2, 1, 1, 1, 1, 7, 7,
	6, 6, 1, 1, 0, 0, 6, 6, 1, 1
};

static const int _ys[60] = {
	7, 0, 7, 0, 5, 2, 7, 0, 7, 0,
	5, 2, 5, 2, 5, 2, 4, 3, 5, 2,
	5, 2, 4, 3, 4, 3, 7, 0, 7, 0,
	4, 3, 5, 4, 3, 2, 6, 1, 6, 1,
	6, 1, 6, 1, 5, 4, 3, 2, 6, 1,
	7, 0, 7, 0, 6, 1, 6, 1, 6, 1
};

static const int _aaValues[8][8] = {
	{ 1000, -100, 25,  0,  0, 25, -100, 1000 },
	{ -100, -400, -5, -5, -5, -5, -400, -100 },
	{   25,   -5, 12,  2,  2, 12,   -5,   25 },
	{    0,   -5,  2,  2,  2,  2,   -5,    0 },
	{    0,   -5,  2,  2,  2,  2,   -5,    0 },
	{   25,   -5, 12,  2,  2, 12,   -5,   25 },
	{ -100, -400, -5, -5, -5, -5, -400, -100 },
	{ 1000, -100, 25,  0,  0, 25, -100, 1000 }
};


class SmartGecko : public ReversiAI {
	public:
		SmartGecko();
		void setNodes(const vBoardNode **_n) { nodes = _n; }
		int testMe(int height, int width) {
			if ( height > NUM_CELL_Y || width > NUM_CELL_X ) {
				return -1;
			}
			return 0;
		}
	private:
		int DEPTH;
		int END_GAME_DEPTH;
		int NOLIMIT;
		int winning_bonus;
		int VALUE_OF_A_MOVE_POSSIBILITY;
		int VALUE_OF_AN_UNSAFE_PIECE;
		int VALUE_OF_A_SAFE_PIECE;
		int VALUE_OF_A_CORNER;
		const vBoardNode **nodes;
		nodeColor myColor;
		//static const int xs[60];
};

SmartGecko::SmartGecko() : ReversiAI(), \
		DEPTH(4), \
		END_GAME_DEPTH(9), \
		NOLIMIT(1000000), \
		winning_bonus(100000), \
		VALUE_OF_A_MOVE_POSSIBILITY(15), \
		VALUE_OF_AN_UNSAFE_PIECE(8), \
		VALUE_OF_A_SAFE_PIECE(20), \
		VALUE_OF_A_CORNER(1000) {
			nodes = NULL;
}
