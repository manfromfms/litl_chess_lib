#include <iostream>
#include <vector>

#include "antichess.h"

#include "utils.h"

int main()
{
	litl::antichess anti = litl::antichess("8/3P1p2/8/8/8/4P2r/2P1PP2/2BQKBN1 w - - 1 20");

	std::cout << anti.position.longLongToBinary(anti.position.getAllBitboard(), true) << std::endl << (anti.position.isWhitesTurn ? "White to move" : "Black to move") << std::endl;

	for (int i = 4; i < 1000; i++) {
		std::cout << "Calculating into " << i << " plys" << std::endl;
		std::cout << anti.calc(true, i, -1000000, 1000000) << std::endl;
		std::cout << "Best move: " << anti.bestMove.uci() << std::endl << std::endl;
	}

	std::cout << anti.position.longLongToBinary(anti.position.getAllBitboard(), true) << std::endl << (anti.position.isWhitesTurn ? "White to move" : "Black to move") << std::endl;

	//std::cout << anti.position.longLongToBinary(anti.position.getQueenMovesBitboard(43, anti.position.getAllBitboard()), true) << std::endl;

	

	std::cin.get();
}