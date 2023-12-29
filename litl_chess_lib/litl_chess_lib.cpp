#include <iostream>
#include <vector>

#include "antichess.h"

#include "utils.h"

int main()
{
	litl::antichess anti = litl::antichess("rnbqkbnr/ppp2p1p/4p3/8/8/8/PPPPPPPP/RNBQKB1R w - - 0 4");

	std::cout << anti.position.longLongToBinary(anti.position.getAllBitboard(), true) << std::endl << (anti.position.isWhitesTurn ? "White to move" : "Black to move") << std::endl;

	std::cout << anti.calc(true, 3) << std::endl << "Best move: " << anti.bestMove.uci() << std::endl << std::endl;

	std::cout << anti.position.longLongToBinary(anti.position.getAllBitboard(), true) << std::endl << (anti.position.isWhitesTurn ? "White to move" : "Black to move") << std::endl;

	//std::cout << anti.position.longLongToBinary(anti.position.getQueenMovesBitboard(43, anti.position.getAllBitboard()), true) << std::endl;

	

	std::cin.get();
}