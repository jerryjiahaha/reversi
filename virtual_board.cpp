#include <iostream>
#include <vector>
#include <assert.h>

enum nodeColor { none, black, white };

class vBoard;
class vBoardNode {
//	friend class vBoard;
	public:
		vBoardNode() { color = none; }
		void setColor(nodeColor _color);
		int getColor() const { return color; }
		int availability;
	private:
		nodeColor color;
};

void vBoardNode::setColor(nodeColor _color) {
	color = _color;
}

//################################################
class vBoard {
	public:
		vBoard();
		~vBoard();
		void init();
		void print();
		int setPos(int x, int y, nodeColor state, bool update = true);
		int setNext(int x, int y);
		int getNext() const { return next; }
		void checkAvailability();
		int isAvailible(int x, int y) const;
	private:
		int height;
		int width;
		vBoardNode **nodes;
		vBoardNode **line;
		vBoardNode **line2;
		nodeColor next;
		void validateLine(vBoardNode **_line, int length);
		void resetAvailability();
		void updateBoard(int x, int y, int direction);
		enum stateMachine_state { start, head, body, stop };
		struct vec{
			int i;
			int j;
		};
		stateMachine_state stateMachine(vBoardNode *node, stateMachine_state currentState, int nextColor);
};

/*
 * (0,0) (1,0)
 * (0,1) (1,1)
 */
vBoard::vBoard() : height(8), width(8) {
	nodes = new vBoardNode*[height];
	int i;
	for ( i = 0; i < height; ++i ) {
		nodes[i] = new vBoardNode[width];
	}
	line = new vBoardNode*[width > height ? width : height];
	line2 = new vBoardNode*[width > height ? width : height];
}

void vBoard::init() {
	/*
	 * ....................
	 * ...<black><white>...
	 * ...<white><black>...
	 * ....................
	 */
	int middle_pos_x = width/2;
	int middle_pos_y = height/2;
	this->setPos(middle_pos_x, middle_pos_y, white, false);
	this->setPos(middle_pos_x+1, middle_pos_y, black, false);
	this->setPos(middle_pos_x+1, middle_pos_y+1, white, false);
	this->setPos(middle_pos_x, middle_pos_y+1, black, false);
	this->next = black;
	this->checkAvailability();
}

void vBoard::print() {
	int i, j;
	if ( next == white ) {
		std::cout << "\033[1;36m" << "o" << "\033[0m";
	}
	else {
		std::cout << "\033[1;32m" << "x" << "\033[0m";
	}
	for ( j = 0; j < width; ++j ) {
		std::cout << j+1 << " ";
	}
	std::cout << "\n";
	for ( i = 0; i < height; ++i ) {
		std::cout << i+1;
		for ( j = 0; j < width; ++j ) {
			switch (this->nodes[i][j].getColor()) {
				case none:
					if ( this->nodes[i][j].availability ) {
						std::cout << "\033[5;37m" << "#" << "\033[0m";
					}
					else {
						std::cout << "#";
					}
					break;
				case white:
					std::cout << "\033[1;36m" << "o" << "\033[0m";
					break;
				case black:
					std::cout << "\033[1;32m" << "x" << "\033[0m";
					break;
				default:
					std::cout << "?";
			}
			std::cout << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "----------------" << std::endl;
}

vBoard::~vBoard() {
	int i;
	for ( i = 0; i < height; ++i ) {
		delete[] nodes[i];
	}
	delete[] nodes;
	delete[] line;
	delete[] line2;
}

// TODO optimize
void vBoard::checkAvailability() {
	int i, j;
	this->resetAvailability();
	for ( i = 0 ; i < height; i++ ) {
		for ( j = 0; j < width; j++ ) {
			this->line[j] = &this->nodes[i][j];
			this->line2[width-j-1] = &this->nodes[i][j];
		}
		this->validateLine(this->line, this->width);
		this->validateLine(this->line2, this->width);
	}
	for ( j = 0 ; j < width; j++ ) {
		for ( i = 0; i < height; i++ ) {
			this->line[i] = &this->nodes[i][j];
			this->line2[height-i-1] = &this->nodes[i][j];
		}
		this->validateLine(this->line, this->height);
		this->validateLine(this->line2, this->height);
	}
	int length, counter;
	for ( i = 0; i < height; i++ ) {
		counter = 0;
		length = i+1 > width ? width : i+1;
		for ( j = 0; j < width && i-counter >= 0; j++, counter++ ) { // in fact, j=counter
			this->line[counter] = &this->nodes[i-counter][j];
			this->line2[length-counter-1] = &this->nodes[i-counter][j];
			//std::cout << length << "(" << i-counter << ", " << j << ")\t";
		}
		//std::cout << std::endl;
		this->validateLine(this->line, length);
		this->validateLine(this->line2, length);
	}
	for ( j = 1; j < width; j++ ) {
		i = height-1;
		length = width-j > height ? height : width-j;
		for ( counter = 0; j + counter < width && i-counter >=0; counter++ ) {
			this->line[counter] = &this->nodes[i-counter][j+counter];
			this->line2[length-counter-1] = &this->nodes[i-counter][j+counter];
//			std::cout << length << "(" << i-counter << ", " << j+counter << ")\t";
		}
//		std::cout << "\n";
		this->validateLine(this->line, length);
		this->validateLine(this->line2, length);
	}
	for ( i = height-1; i >= 0; i-- ) {
		counter = 0;
		length = width > height-i ? height-i : width;
		for ( j = 0; j < width && i+counter < height; j++, counter++ ) {
			//std::cout << length << "(" << i+counter << ", " << j << ")\t";
			this->line[counter] = &this->nodes[i+counter][j];
			this->line2[length-counter-1] = &this->nodes[i+counter][j];
		}
		//std::cout << "\n";
		this->validateLine(this->line, length);
		this->validateLine(this->line2, length);
	}
	for ( j = 1; j < width; j++ ) {
		counter = 0;
		length = width-j > height ? height : width-j;
		for ( ; counter < length ; counter++ ) {
			this->line[counter] = &this->nodes[counter][j+counter];
			this->line2[length-counter-1] = &this->nodes[counter][j+counter];
			//std::cout << length << "(" << counter << ", " << j+counter << ")\t";
		}
		//std::cout << "\n";
		this->validateLine(this->line, length);
		this->validateLine(this->line2, length);
	}
}

vBoard::stateMachine_state vBoard::stateMachine(vBoardNode *node, vBoard::stateMachine_state currentState, int nextColor) {
	nodeColor other = ( nextColor == black ? white : black );
	switch (currentState) {
		case stop:
			currentState = start;
		case start:
			if ( node->getColor() == nextColor ) {
				currentState = head;
			}
			break;
		case head:
			if ( node->getColor() == none ) {
				currentState = start;
			}
			else if ( node->getColor() == other ) {
				currentState = body;
			}
			break;
		case body:
			if ( node->getColor() == nextColor ) {
				currentState = head;
			}
			else if ( node->getColor() == none ) {
				currentState = stop;
			}
			break;
		default:
			assert(0);
	}
	return currentState;
}

void vBoard::validateLine(vBoardNode **_line, int length) {
	int i = 0;
	stateMachine_state current = start;
	while ( i < length ) {
		//std::cout << _line[i]->getColor();
		current = this->stateMachine(_line[i], current, next);
		if ( current == stop ) {
			_line[i]->availability = 1;
		}
		++i;
	}
	//std::cout << std::endl;
}

void vBoard::resetAvailability() {
	int i, j;
	for ( i = 0; i < height; ++i ) {
		for ( j = 0; j < width; ++j ) {
			nodes[i][j].availability = 0;
		}
	}
}

int vBoard::setPos(int x, int y, nodeColor state, bool update) {
	if ( this->nodes[y-1][x-1].getColor() != none ) {
		std::cerr << "already have one" << std::endl;
		return -2;
	}
	this->nodes[y-1][x-1].setColor(state);
	if ( update ) {
		this->checkAvailability();
	}
	return 0;
}

int vBoard::isAvailible(int x, int y) const{
	if ( this->nodes[y-1][x-1].availability ) {
		return 1;
	}
	return 0;
}

int vBoard::setNext(int x, int y) {
	//assert( x>=1 && x<=width && y>=1 && y<=height );
	 if ( x<1 || x>width || y<1 || y>height ) {
		 throw "out of range";
	 }
	// validate
	if ( ! this->isAvailible(x, y) ) {
		std::cerr << "this position is not availible!" << std::endl;
		return -2;
	}
	// END validate
	if ( this->setPos(x, y, next, false) < 0) {
		return -1;
	}
	this->updateBoard(x, y, 0x11);
	this->updateBoard(x, y, 0x12);
	this->updateBoard(x, y, 0x21);
	this->updateBoard(x, y, 0x22);
	this->updateBoard(x, y, 0x10);
	this->updateBoard(x, y, 0x01);
	this->updateBoard(x, y, 0x20);
	this->updateBoard(x, y, 0x02);
	next = ( next == white ? black : white );
	this->checkAvailability();
	return 0;
}

void vBoard::updateBoard(int x, int y, int direction) {
	int dir[2];
	switch (direction>>4 & 0x3) {
		case 1:
			dir[1] = 1;
			break;
		case 2:
			dir[1] = -1;
			break;
		default:
			dir[1] = 0;
	}
	switch (direction & 0x3 ) {
		case 1:
			dir[0] = 1;
			break;
		case 2:
			dir[0] = -1;
			break;
		default:
			dir[0] = 0;
	}
	assert(dir[0]!=0 || dir[1]!=0);

	int counter;
	std::vector<struct vec> body_to_change;
	std::vector<struct vec>::iterator it;
	stateMachine_state current = head;
	struct vec pos;
	pos.i = y-1+dir[0];
	pos.j = x-1+dir[1];
	for ( counter = 0; pos.i < height && pos.i >= 0 && pos.j < width && pos.j >= 0; counter++ ) {
		current = this->stateMachine(&this->nodes[pos.i][pos.j], current, next);
		if ( current == start || current == stop) break;
		if ( current == head ) {
			for ( it = body_to_change.begin(); it != body_to_change.end(); ++it ) {
				this->nodes[it->i][it->j].setColor(next);
			}
			break;
		}
		body_to_change.push_back(pos);
		pos.i = pos.i + dir[0];
		pos.j = pos.j + dir[1];
	}
}

// check
int main(void) {
	vBoard board;
	board.init();
	board.print();
	int x, y;
	board.setNext(3, 4);
	board.print();
	board.setNext(3, 3);
	board.print();
	board.setNext(3, 2);
	board.print();
	board.setNext(6, 4);
	board.print();
	while (1) {
		std::cout << "next: " << board.getNext() << ", input position: " << std::flush;
		try {
			std::cin >> x >> y;
			if ( x == -1 ) break;
			board.setNext(x, y);
			board.print();
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
 * 3 2
 * 6 4
 * 6 6
 * 3 6
 * 7 3
 * 2 3
 * 3 5
 */
