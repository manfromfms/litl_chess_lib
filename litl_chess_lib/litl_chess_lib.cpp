#include <iostream>

#include "antichess.h"

#include "utils.h"

int main()
{
	litl::antichess anti = litl::antichess("q3nr1k/4bppp/3p4/rB2nPP1/3BP2P/Np2Q3/1P6/1K1R3R w - - 7 26");

	std::cout << anti.position.longLongToBinary(anti.position.getAllBitboard(), true) << std::endl;

	std::vector<ull> data = anti.position.generateAllBlackPawnsCaptures();
	for (int i = 0; i < data.size(); i++) {
		std::cout << data[i] << std::endl;
	}

	std::cin.get();
}