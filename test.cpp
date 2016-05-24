#include <iostream>
#include "virtual_board.h"

static void fuck_board(vBoard &board);

// check
int main(void) {
	vBoard board;
	board.init();
	fuck_board(board);
	board.print();
	if ( board.checkNext() == SWITCH_USER_ ) {
		board.print();
	}
	if ( board.checkNext() == END_OF_GAME_ ) {
		return 0;
	}
	board.print();
	int x, y;
	while (1) {
		std::cout << "next: " << board.getNext() << ", input position: " << std::flush;
		try {
			std::cin >> x >> y;
			if ( x == -1 ) break;
			board.setNext(x, y);
			board.print();
			if ( board.checkNext() == SWITCH_USER_ ) {
				board.print();
			}
			if ( board.checkNext() == END_OF_GAME_ ) {
				break;
			}
		}
		catch (const char* e) {
			std::cout << x << " " << y << "\nerror: " << e << std::endl;
			std::cin.clear();
			std::cin.ignore(100000,'\n');
		}
	}
	return 0;
}

/*
 * 3 4
 * 3 3
 * 3 2
 * 6 4
 * 6 6
 * 3 6
 * 7 3
 * 2 3
 * 3 5
 */

static void fuck_board(vBoard &board) {
	board.setNext( 3, 4 );
	board.setNext( 3, 3 );
	board.setNext( 6, 5 );
	board.setNext( 6, 6 );
	board.setNext( 5, 6 );
	board.setNext( 6, 4 );
	board.setNext( 4, 3 );
	board.setNext( 4, 6 );
	board.setNext( 4, 7 );
	board.setNext( 3, 5 );
	board.setNext( 2, 4 );
	board.setNext( 3, 6 );
	board.setNext( 4, 2 );
	board.setNext( 3, 2 );
	board.setNext( 7, 4 );
	board.setNext( 5, 3 );
	board.setNext( 2, 1 );
	board.setNext( 5, 2 );
	board.setNext( 5, 1 );
	board.setNext( 6, 3 );
	board.setNext( 2, 5 );
	board.setNext( 5, 7 );
	board.setNext( 5, 8 );
	board.setNext( 6, 2 );
	board.setNext( 7, 6 );
	board.setNext( 2, 3 );
	board.setNext( 1, 4 );
	board.setNext( 7, 5 );
	board.setNext( 8, 5 );
	board.setNext( 6, 7 );
	board.setNext( 7, 3 );
	board.setNext( 1, 6 );
	board.setNext( 6, 8 );
	board.setNext( 8, 6 );
	board.setNext( 8, 7 );
	board.setNext( 3, 1 );
	board.setNext( 4, 1 );
	board.setNext( 2, 6 );
	board.setNext( 2, 2 );
	board.setNext( 1, 1 );
	board.setNext( 1, 2 );
	board.setNext( 7, 1 );
	board.setNext( 1, 5 );
	board.setNext( 7, 8 );
	board.setNext( 8, 8 );
	board.setNext( 3, 8 );
	board.setNext( 7, 2 );
	board.setNext( 8, 1 );
	board.setNext( 1, 7 );
	board.setNext( 1, 3 );
	board.setNext( 8, 2 );
	board.setNext( 1, 8 );
	board.setNext( 4, 8 );
	board.setNext( 6, 1 );
	board.setNext( 2, 8 );
	board.setNext( 8, 3 );
	board.setNext( 8, 4 );
	board.setNext( 3, 7 );
	board.setNext( 7, 7 );
}
