#pragma once

#include <string>
using std::string;

#include "position.h"

#include "move.h"

#include <iostream>

namespace litl {
	class antichess
	{
	public:
		litl::position position;
		litl::move bestMove;
		int lastEval = 0;

		antichess(string fen) {
			this->position = litl::buildPosition(fen);
		}

		string getMovesStringFromVector(std::vector<litl::move> moves) {
			string result = "Moves: ";

			for (auto move : moves) {
				result += move.uci() + " ";
			}

			return result;
		}

		int eval() {
			ull team = position.isWhitesTurn ? position.getWhiteBitboard() : position.getWhiteBitboard();
			ull oppo = position.isWhitesTurn ? position.getBlackBitboard() : position.getWhiteBitboard();

			int counter = 0;

			while (team | oppo) {
				if (team & 1LL) counter -= 1;
				if (oppo & 1LL) counter += 1;

				team >>= 1;
				oppo >>= 1;
			}

			return counter;
		}

		int calc(bool isTop, int depth) {
			std::vector<litl::move> moves = position.getLegalMoves();

			if (moves.size() == 0) return 1000000;

			if (depth == 0) return eval();

			int bestEval = -1000001;

			if (isTop) bestMove = moves[0];

			for (auto move : moves) {
				position.makeMove(move);

				int temp = -calc(false, depth - 1);
				std::cout << bestMove.uci() << std::endl;

				position.undoMove(move);

				if (temp > bestEval) {
					bestEval = temp;

					if (isTop) {
						this->bestMove = move;
					}
				}
			}

			return bestEval;
		}
	};
}