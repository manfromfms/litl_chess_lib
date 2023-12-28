#pragma once

#include <string>
using std::string;

#include "position.h"

#include "move.h"

namespace litl {
	class antichess
	{
	public:
		litl::position position;

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
	};
}