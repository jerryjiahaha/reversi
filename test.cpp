#include <iostream>
#include <stack>
#include "virtual_board.h"

static void fuck_board(vBoard &board);

static int test_stack() {
	std::cout << "test_stack" << std::endl;
	std::stack<vBoard*> bstack;
	vBoard *a = new vBoard;
	bstack.push(a);
	delete bstack.top();
	bstack.pop();
	std::cout << "test_stack end" << std::endl;
	return 0;
}

static void test_assign() {
	std::cout << "test_assign" << std::endl;
	std::cout << "a" << std::endl;
	vBoard a;
	std::cout << "a end" << std::endl;
	std::cout << "b" << std::endl;
	vBoard b;
	std::cout << "b end" << std::endl;
	std::cout << "a=b" << std::endl;
	a = b;
	std::cout << "a=b end" << std::endl;
	//std::cout << "c(a)" << std::endl;
	//vBoard c = a;
	//std::cout << "c(a) end" << std::endl;
	std::cout << "test_assign end" << std::endl;
}

// check
int main(void) {

	//test_assign();
	//return test_stack();

	vBoard board;
	board.init();
	//fuck_board(board);
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
	board.setNext( 2, 3 );
	board.setNext( 2, 2 );
	board.setNext( 5, 4 );
	board.setNext( 5, 5 );
	board.setNext( 4, 5 );
	board.setNext( 5, 3 );
	board.setNext( 3, 2 );
	board.setNext( 3, 5 );
	board.setNext( 3, 6 );
	board.setNext( 2, 4 );
	board.setNext( 1, 3 );
	board.setNext( 2, 5 );
	board.setNext( 3, 1 );
	board.setNext( 2, 1 );
	board.setNext( 6, 3 );
	board.setNext( 4, 2 );
	board.setNext( 1, 0 );
	board.setNext( 4, 1 );
	board.setNext( 4, 0 );
	board.setNext( 5, 2 );
	board.setNext( 1, 4 );
	board.setNext( 4, 6 );
	board.setNext( 4, 7 );
	board.setNext( 5, 1 );
	board.setNext( 6, 5 );
	board.setNext( 1, 2 );
	board.setNext( 0, 3 );
	board.setNext( 6, 4 );
	board.setNext( 7, 4 );
	board.setNext( 5, 6 );
	board.setNext( 6, 2 );
	board.setNext( 0, 5 );
	board.setNext( 5, 7 );
	board.setNext( 7, 5 );
	board.setNext( 7, 6 );
	board.setNext( 2, 0 );
	board.setNext( 3, 0 );
	board.setNext( 1, 5 );
	board.setNext( 1, 1 );
	board.setNext( 0, 0 );
	board.setNext( 0, 1 );
	board.setNext( 6, 0 );
	board.setNext( 0, 4 );
	board.setNext( 6, 7 );
	board.setNext( 7, 7 );
	board.setNext( 2, 7 );
	board.setNext( 6, 1 );
	board.setNext( 7, 0 );
	board.setNext( 0, 6 );
	board.setNext( 0, 2 );
	board.setNext( 7, 1 );
	board.setNext( 0, 7 );
	board.setNext( 3, 7 );
	board.setNext( 5, 0 );
	board.setNext( 1, 7 );
	board.setNext( 7, 2 );
	board.setNext( 7, 3 );
	board.setNext( 2, 6 );
	board.setNext( 6, 6 );
}
