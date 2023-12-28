#include <iostream>

#include "antichess.h"

#include "utils.h"

int main()
{
	litl::antichess anti = litl::antichess("1n2b3/r4p1p/8/p7/8/2p5/P1PN2PP/R5NR b - - 1 14");

	std::cout << anti.position.longLongToBinary(anti.position.getAllBitboard(), true) << std::endl;

	//std::cout << anti.position.longLongToBinary(anti.position.getQueenMovesBitboard(43, anti.position.getAllBitboard()), true) << std::endl;

	std::cout << "Started to calculate moves" << std::endl;
	std::cout << anti.getMovesStringFromVector(anti.position.getLegalMoves()) << std::endl;
	std::cout << "Ended successfuly" << std::endl;

	std::cin.get();
}