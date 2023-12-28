#pragma once

#include <string>
using std::string;

#include "position.h"

namespace litl {
	class antichess
	{
	public:
		litl::position position;

		antichess(string fen) {
			this->position = litl::buildPosition(fen);
		}
	};
}