#include <iostream>
#include <vector>

#include "antichess.h"

#include "utils.h"

int main()
{
	litl::antichess anti = litl::antichess("1rb1N3/pp3p1p/8/8/8/3P4/P1P1PPBP/3QK1NR b - - 0 11");

	//std::cout << anti.position.longLongToBinary(anti.position.getAllBitboard(), true) << std::endl << (anti.position.isWhitesTurn ? "White to move" : "Black to move") << std::endl;

	std::cout << anti.getMovesStringFromVector(anti.orderMoves(anti.position.getLegalMoves())) << std::endl;

	for (int i = 4; i < 1000; i++) {
		anti.position.clearPositions();

		std::cout << "Calculating into " << i << " plys" << std::endl;
		std::cout << anti.calc(true, i, -1000000, 1000000) << std::endl;
		std::cout << "Best move: " << anti.bestMove.uci() << std::endl << "Checked " << anti.position.counter << " positions" << std::endl;
	}

	//std::cout << anti.position.longLongToBinary(anti.position.getAllBitboard(), true) << std::endl << (anti.position.isWhitesTurn ? "White to move" : "Black to move") << std::endl;

	//std::cout << anti.position.longLongToBinary(anti.position.getQueenMovesBitboard(43, anti.position.getAllBitboard()), true) << std::endl;

	

	std::cin.get();
}