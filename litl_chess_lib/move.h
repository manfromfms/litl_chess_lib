#pragma once

#include <string>

namespace litl {
	class move
	{
	public:
		int from = -1;
		int to = -1;

		bool isCapture = true;

		move(int f, int t) {
			from = f;
			to = t;
		}

		move(int f, int t, bool isC) {
			from = f;
			to = t;

			isCapture = isC;
		}

		std::string uci() {
			std::string cols = "hgfedcba";
			std::string rows = "12345678";

			if (from < 0 || to < 0) return "a1a1";

			return std::string() + cols[(63 - from) % 8] + rows[(63 - from) / 8] + cols[(63 - to) % 8] + rows[(63 - to) / 8];
		}
	};
};