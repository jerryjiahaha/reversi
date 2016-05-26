#ifndef VIRTUAL_BOARD_H_
#define VIRTUAL_BOARD_H_

#include <assert.h>

#define END_OF_GAME_ 0x233
#define SWITCH_USER_ 0x666

enum nodeColor { none=-1, black=0, white=1 };
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

class vBoard {
	public:
		vBoard();
		vBoard& operator=(const vBoard& origin);
//		vBoard(const vBoard& origin);
		~vBoard();
		static void copyNodes(const vBoard& origin, vBoardNode** dst);
		static vBoardNode** dupNodes(const vBoard& origin);
		void init();
		void reset();
		void print();
		int setNext(int x, int y);
		int checkNext(bool change = true);
		int getNext() const { return next; }
		void checkAvailability();
		int getAvailableCount() const { return availableCount; }
		int isAvailible(int x, int y) const;
		int getHeight() const { return height; }
		int getWidth() const { return width; }
		int getScore() const { return blackCount - whiteCount; }
		int getBlack() const { return blackCount; }
		int getWhite() const { return whiteCount; }
		int getRestCount() const { assert(blackCount+whiteCount+restCount==width*height); return restCount; }
		int switchPlayer();
		const vBoardNode** getNodes() const {
			return const_cast<const vBoardNode**>(nodes);
		}
	private:
		int height;
		int width;
		int availableCount;
		vBoardNode **nodes;
		vBoardNode **line;
		vBoardNode **line2;
		nodeColor next;
		int setPos(int x, int y, nodeColor state, bool update = true);
		void validateLine(vBoardNode **_line, int length);
		void incAvailableCount() { ++availableCount; }
		void clrAvailableCount() { availableCount = 0; }
		int blackCount;
		int whiteCount;
		int restCount;
		int setNodeAvailable(vBoardNode *node);
		void resetAvailability();
		void updateBoard(int x, int y, int direction);
		enum stateMachine_state { start, head, body, stop };
		struct vec{
			int i;
			int j;
		};
		stateMachine_state stateMachine(vBoardNode *node, stateMachine_state currentState, int nextColor);
		int endCheck() const;
};


#endif
