#include <iostream>
#include <algorithm>

#include "SmartGecko.h"

const int SmartGecko::_xs[60] = {
	7, 7, 0, 0, 7, 7, 5, 5, 2, 2,
	0, 0, 5, 5, 2, 2, 5, 5, 4, 4,
	3, 3, 2, 2, 7, 7, 4, 4, 3, 3,
	0, 0, 6, 6, 6, 6, 5, 5, 4, 4,
	3, 3, 2, 2, 1, 1, 1, 1, 7, 7,
	6, 6, 1, 1, 0, 0, 6, 6, 1, 1
};


const int SmartGecko::_ys[60] = {
	7, 0, 7, 0, 5, 2, 7, 0, 7, 0,
	5, 2, 5, 2, 5, 2, 4, 3, 5, 2,
	5, 2, 4, 3, 4, 3, 7, 0, 7, 0,
	4, 3, 5, 4, 3, 2, 6, 1, 6, 1,
	6, 1, 6, 1, 5, 4, 3, 2, 6, 1,
	7, 0, 7, 0, 6, 1, 6, 1, 6, 1
};

const int SmartGecko::_aaValues[8][8] = {
	{ 1000, -100, 25,  0,  0, 25, -100, 1000 },
	{ -100, -400, -5, -5, -5, -5, -400, -100 },
	{   25,   -5, 12,  2,  2, 12,   -5,   25 },
	{    0,   -5,  2,  2,  2,  2,   -5,    0 },
	{    0,   -5,  2,  2,  2,  2,   -5,    0 },
	{   25,   -5, 12,  2,  2, 12,   -5,   25 },
	{ -100, -400, -5, -5, -5, -5, -400, -100 },
	{ 1000, -100, 25,  0,  0, 25, -100, 1000 }
};

SmartGecko::SmartGecko() : ReversiAI(), \
		DEPTH(4), \
		END_GAME_DEPTH(9), \
		NOLIMIT(1000000), \
		WINNING_BONUS(100000), \
		VALUE_OF_A_MOVE_POSSIBILITY(15), \
		VALUE_OF_AN_UNSAFE_PIECE(8), \
		VALUE_OF_A_SAFE_PIECE(20), \
		VALUE_OF_A_CORNER(1000) {
			//nodes = NULL;
			//gameBoard = new vBoard();
			// XXX should I use memcpy ?
			std::fill_n((int*)_aaSafe, sizeof(_aaSafe)/sizeof(int), 1);
}

SmartGecko::~SmartGecko() {
	while ( !_aBoardStack.empty() ) {
		delete _aBoardStack.top();
		_aBoardStack.pop();
	}
}

/**
  * @brief Evaluation function for Reversi board.
  * @note  Positive value means player `other` is in the lead,
  *        negative value means player `me` is in the lead.
  * @param  *board: current board used
  * @retval value
  */
int SmartGecko::_Eval(vBoard *board) {
	int movesMe, movesOther;
	int score;
	movesMe = board->getAvailableCount();
	board->switchPlayer();
	movesOther = board->getAvailableCount();
	if ( movesMe == movesOther && movesMe == 0 ) { // end of game
		score = board->getScore();
		score = ( otherColor == black ? score : -score );
		if ( score == 0 ) {
			return 0;
		}
		if ( score > 0 ) {
			return score + WINNING_BONUS;
		}
		return score - WINNING_BONUS; // XXX
	}
	score = VALUE_OF_A_MOVE_POSSIBILITY * ( movesOther - movesMe );
	score -= _valuePieces(board, myColor);
	score += _valuePieces(board, otherColor);
	return score;
}


/**
 * @brief Minimax search for the best possible move with alpha-beta pruning
 * @param  depth: board depth
 * @param  alpha: current Move
 * @param  beta:  previous Move
 * @param  firstMove: first Move index
 * @retval best move
 */ 
int SmartGecko::_Descend(int depth, int alpha, int beta, int firstMove) {
	//BOARD * pBoard;
	//BOARD * nextBoard;
	vBoard *pBoard;
	vBoard *nextBoard;
	int x, y, i, alt, maximize;

	//pBoard    = _aBoardStack + depth;
	//nextBoard = _aBoardStack + depth - 1;
	pBoard = _aBoardStack.top();
	if (depth == 0) {
		return _Eval(pBoard);
	}
	//moves = _CalcValidMoves(pBoard);
	if ( pBoard->checkNext() == END_OF_GAME_ ) {
		return _Eval(pBoard);
	}
	//if (moves == 0) {
	//	/* The player has to pass */
	//	pBoard->ActPlayer = 3 - pBoard->ActPlayer;
	//	moves = _CalcValidMoves(pBoard);
	//	if (moves == 0) {
	//		/* The game is over */
	//		return _Eval(pBoard);
	//	}
	//}
	//maximize = pBoard->ActPlayer == 1;
	maximize = pBoard->getNext() == otherColor;
	nextBoard = new vBoard();
	_aBoardStack.push( nextBoard );
	for (i = 0; i < 60; ++i) {
		/* Try the possible moves in order from most attractive to least attractive
		   position, to maximize the effect of the alpha-beta pruning. */
		x = _xs[i];
		y = _ys[i];
		//std::cout << i << ", " << x << ", " << y << std::endl;
		//if (pBoard->aMoves[x][y]) 
		if (pBoard->isAvailible(x, y)) {
			//std::cout << "depth: " << depth << std::endl;
			//pBoard->print();
			*nextBoard = *pBoard;
			//nextBoard->print();
			//_MakeMove(nextBoard, x, y);
			//std::cout << "in _Descend, test " << x << ", " << y << std::endl;
			nextBoard->setNext(x, y);
			//nextBoard->ActPlayer = 3 - pBoard->ActPlayer;
			/* Recursively evaluate the board resulting from this move. */
			alt = _Descend(depth - 1, alpha, beta, 0);
			//std::cout << "depth: " << depth << ", alt: " << alt << ", alpha: " << alpha << ", beta: " << beta << std::endl;
			if (maximize) {
				if (alt > alpha) {
					alpha = alt;
					if (firstMove) {
						_px = x;
						_py = y;
					}
				}
			} else {
				if (alt < beta) {
					beta = alt;
					if (firstMove) {
						_px = x;
						_py = y;
					}
				}
			}
			if (beta <= alpha) {
				/* This is the alpha-beta pruning terminal condition. */
				goto end;
			}
		}
	}
end:
	delete _aBoardStack.top();
	_aBoardStack.pop();
	return maximize ? alpha : beta;
}



/**
  * @brief Find the value of all the pieces belonging to the given player.
  * @note  Positive value is good for this player.
  *        The value can also be negative, if the player occupies tiles
  *        next to free corner, which makes it easier for the opponent
  *        to get to this corner.
  * @param  board: pointer to the board stack
  * @param  playerColor: player index
  * @retval value
  */
int SmartGecko::_valuePieces(const vBoard *board, int playerColor) {
	int sum;
	int x, y, corners, changed, s, xCorner, yCorner, numberOfSafe;
	const vBoardNode **nodes = board->getNodes();

	sum = 0;
	for ( y = 1; y <= 8; y++ ) {
		for ( x = 1; x <= 8; x++ ) {
			_aaSafe[x][y] = 0;
		}
	}
	corners = 0;
	corners += ( nodes[0][0].getColor() == playerColor );
	corners += ( nodes[7][0].getColor() == playerColor );
	corners += ( nodes[0][7].getColor() == playerColor );
	corners += ( nodes[7][7].getColor() == playerColor );
	if ( corners ) {
		/* Corners are the most valuable asset of the position. */
		sum += corners * VALUE_OF_A_CORNER;
		/* Calculate how many pieces are safe,
		 *        meaning they can never be taken back
		 *               by the opponent. */
		while (1) {
			/* Repeatedly swipe the board looking for safe pieces,
			 *          until no more safe pieces are found. */
			changed = 0;
			numberOfSafe = 0;
			for (y = 1; y <= 8; y++) {
				for (x = 1; x <= 8; x++) {
					//if (!_aaSafe[x][y] && pBoard->aCells[x - 1][y - 1] == player) 
					if (!_aaSafe[x][y] && ( nodes[x - 1][y - 1].getColor() == playerColor) ) {
						/* A piece can never be taken back if in each of the four directions,
						 *                one of the two neighboring tiles are safe. */
						s = (_aaSafe[x - 1][y    ] || _aaSafe[x + 1][y    ])  /* West  - East  */
							&& (_aaSafe[x    ][y - 1] || _aaSafe[x    ][y + 1])  /* North - South */
							&& (_aaSafe[x - 1][y - 1] || _aaSafe[x + 1][y + 1])  /* NW    - SE    */
							&& (_aaSafe[x - 1][y + 1] || _aaSafe[x + 1][y - 1]); /* SW    - NE    */
						if (s) {
							_aaSafe[x][y] = 1;
							changed = 1;
							++numberOfSafe;
						}
					}
				}
				sum += numberOfSafe * VALUE_OF_A_SAFE_PIECE;
			}
			if (!changed) {
				break;
			}
		}
	}
	/* Now add the value of the unsafe pieces. */
	for (y = 0; y < 8; y++) {
		yCorner = (y < 4) ? 0 : 7;
		for (x = 0; x < 8; x++) {
			//if (pBoard->aCells[x][y] == player && !_aaSafe[x + 1][y + 1]) 
			if ( nodes[x][y].getColor() == playerColor && !_aaSafe[x + 1][y + 1]) {
				xCorner = x<4 ? 0 : 7;
				//if (pBoard->aCells[xCorner][yCorner]) 
				if ( nodes[xCorner][yCorner].getColor() != none ) { // XXX
					/* If the corner is taken, we value each position in
					   the quadrant the same. */
					sum += VALUE_OF_AN_UNSAFE_PIECE;
				} else {
					/* If the corner is still free, we use a lookup table
					   to find the value of each position. */
					sum += _aaValues[x][y];
				}
			}
		}
	}
	return sum;
}


/**
 * @brief _PlayerAI_SmartGecko
 * @param  pBoard: pointer to the board stack
 * @param  x: X position
 * @param  y: Y position
 * @retval char
 */ 
//char SmartGecko::_PlayerAI_SmartGecko(const vBoard * pBoard, int * px, int * py) 
char SmartGecko::_PlayerAI_SmartGecko() {
	int x, y, depth;
	int freeTiles = _aBoardStack.top()->getRestCount();

	/* Initialize the safe board to true to get the edges right */
	for (y = 0; y < 10; y++) {
		for (x = 0; x < 10; x++) {
			_aaSafe[x][y] = 1;
		}
	}
	//*px = -1;
	//*py = -1;
	//_px = px;
	//_py = py;
	_px = _py = -1;
//	freeTiles = 0;
//	for (y = 0; y < 8; y++) {
//		for (x = 0; x < 8; x++) {
//			//if (!pBoard->aCells[x][y]) 
//			if (!pBoard->getNodes()[x][y]) {
//				++freeTiles;
//			}
//		}
//	}
	depth = DEPTH;
	if (freeTiles <= END_GAME_DEPTH) {
		//std::cout << "freeTiles: " << freeTiles << std::endl;
		/* In the end game, we expand the search depth. */
		depth = freeTiles;
	}
//	_aBoardStack[depth] = *pBoard;
	_Descend(depth, -NOLIMIT, NOLIMIT, 1);
	if (_px == -1) {
		return 0;
	}
	return 1;
}

void SmartGecko::setBoard(const vBoard &_board) {
	vBoard *gameBoard;
	while ( !_aBoardStack.empty() ) {
		delete _aBoardStack.top();
		_aBoardStack.pop();
	}
	gameBoard = new vBoard;
	*gameBoard = _board;
	_aBoardStack.push(gameBoard);
}

int SmartGecko::nextStep(int& x, int& y, const vBoard &_board) {
	setBoard(_board);
	return nextStep(x, y);
}

int SmartGecko::nextStep(int& x, int& y) {
	//std::cout << "in AI nextStep" << std::endl;
	//_aBoardStack.top()->print();
	myColor = _aBoardStack.top()->getNext();
	otherColor = ( myColor == black ? white : black );
	int DoMove = _PlayerAI_SmartGecko();
	x = _px;
	y = _py;
	std::cout << "x, y: " << x << ", " << y << " . DoMove: " << DoMove << std::endl;
	return DoMove;
}
