#ifndef SMART_GECKO_H_
#define SMART_GECKO_H_

#include "reversi_ai.h"
#include <stack>
#include <iostream>

/*
 * ref: STM32Cube_FW_F7_V1.3.0/Projects/STM32746G-Discovery/Demonstration/Modules/games
 */

#define NUM_CELL_X        8
#define NUM_CELL_Y        8

#define AA_USE_HIRES      0
#define AA_FACTOR         1

#if AA_USE_HIRES
#define AA_CALCFACTOR   AA_FACTOR
#else
#define AA_CALCFACTOR   1
#endif



class SmartGecko : public ReversiAI {
	public:
		SmartGecko();
		~SmartGecko();
		//void setNodes(const vBoardNode **_n) { nodes = _n; }
		void setBoard(const vBoard &_board);
		int testMe(int height, int width) {
			if ( height > NUM_CELL_Y || width > NUM_CELL_X ) {
				return -1;
			}
			return 0;
		}
		int nextStep(int& x, int& y, const vBoard &_board);
		int nextStep(int& x, int& y);
	private:
		int DEPTH;
		int END_GAME_DEPTH;
		int NOLIMIT;
		int WINNING_BONUS;
		int VALUE_OF_A_MOVE_POSSIBILITY;
		int VALUE_OF_AN_UNSAFE_PIECE;
		int VALUE_OF_A_SAFE_PIECE;
		int VALUE_OF_A_CORNER;
		//const vBoardNode **nodes;
		//vBoard *gameBoard;
		int _Eval(vBoard *board);
		int _Descend(int depth, int alpha, int beta, int firstMove); // XXX optimize recursive?
		int _valuePieces(const vBoard *board, int playerColor);
		//char _PlayerAI_SmartGecko(const vBoard *pBoard, int * px, int * py);
		char _PlayerAI_SmartGecko();
		int myColor;
		int otherColor;
		int _aaSafe[10][10];
		int _px;
		int _py;
		std::stack<vBoard *> _aBoardStack; // XXX vector is better?
		static const int _xs[60];
		static const int _ys[60];
		static const int _aaValues[8][8];
};

#endif
