#include <iostream>

#include "antichess.h"

#include "utils.h"

int main()
{
	litl::antichess anti = litl::antichess("1n2b3/5p1p/8/p7/4p3/8/P1PN2PP/Rr4NR b - - 1 14");

	std::cout << anti.position.longLongToBinary(anti.position.getAllBitboard(), true) << std::endl;

	//std::cout << anti.position.longLongToBinary(anti.position.getQueenMovesBitboard(43, anti.position.getAllBitboard()), true) << std::endl;

	std::cout << "Started to calculate moves" << std::endl;
	std::cout << anti.getMovesStringFromVector(anti.position.getLegalMoves()) << std::endl;
	std::cout << "Ended successfuly" << std::endl;

	std::cin.get();
}