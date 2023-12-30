#pragma once

#include <string>

namespace litl {
	class move
	{
	public:
		int from = -1;
		int to = -1;

		bool isCapture = false;
		char capturedPiece = '-';

		bool isEnPassant = false;
		int enPassantSquare = -1;

		bool isPromotion = false;
		char promotionTo = '-';

		int oldEnPassantSquare = -1;

		int order = 0;

		move() {

		}

		move(int oldEnPassant, int f, int t) {
			from = f;
			to = t;

			oldEnPassantSquare = oldEnPassant;
		}

		move(int oldEnPassant, int f, int t, bool isC, char type) {
			from = f;
			to = t;

			if(isC) capturedPiece = type;

			isCapture = isC;

			oldEnPassantSquare = oldEnPassant;
		}

		move(int oldEnPassant, int f, int t, bool isC, int enPassant) {
			from = f;
			to = t;

			isCapture = isC;

			if (enPassant >= 0) {
				enPassantSquare = enPassant;
				isEnPassant = true;
			}

			oldEnPassantSquare = oldEnPassant;
		}

		move(int oldEnPassant, int f, int t, char promo) {
			from = f;
			to = t;

			promotionTo = promo;
			isPromotion = true;

			oldEnPassantSquare = oldEnPassant;
		}

		std::string uci() {
			std::string cols = "hgfedcba";
			std::string rows = "12345678";

			if (from < 0 || to < 0) return "a1a1";

			if (isPromotion) {
				return std::string() + cols[(63 - from) % 8] + rows[(63 - from) / 8] + cols[(63 - to) % 8] + rows[(63 - to) / 8] + promotionTo;
			}
			else {
				return std::string() + cols[(63 - from) % 8] + rows[(63 - from) / 8] + cols[(63 - to) % 8] + rows[(63 - to) / 8];
			}
		}
	};
};