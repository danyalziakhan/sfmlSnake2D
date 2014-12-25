#pragma once

struct Block {
	Block() {
	}
	
	Block(int x, int y) {
		this->x = x;
		this->y = y;
	}
	
	int x;
	int y;
};
