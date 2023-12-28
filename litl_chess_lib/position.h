#pragma once

#define ull unsigned long long

#include "useful_ull.h"
#include "move.h"

#include <vector>

#include <string>
using std::string;

#include <iostream>

namespace litl {
	class position
	{
	public:
		// All bitboards
		ull wp = 0;
		ull bp = 0;
		ull wb = 0;
		ull bb = 0;
		ull wn = 0;
		ull bn = 0;
		ull wr = 0;
		ull br = 0;
		ull wq = 0;
		ull bq = 0;
		ull wk = 0;
		ull bk = 0;

		
		// Additional position info
		bool isWhitesTurn = true;
		

		// Push pieces
		void push(char type) {
			this->push(1);

			if (type == 'p') bp += 1;
			if (type == 'P') wp += 1;

			if (type == 'b') bb += 1;
			if (type == 'B') wb += 1;

			if (type == 'n') bn += 1;
			if (type == 'N') wn += 1;

			if (type == 'r') br += 1;
			if (type == 'R') wr += 1;

			if (type == 'q') bq += 1;
			if (type == 'Q') wq += 1;

			if (type == 'k') bk += 1;
			if (type == 'K') wk += 1;
		}
		void push(int num) {
			wp <<= num;
			bp <<= num;
			wb <<= num;
			bb <<= num;
			wn <<= num;
			bn <<= num;
			wr <<= num;
			br <<= num;
			wq <<= num;
			bq <<= num;
			wk <<= num;
			bk <<= num;
		}


		// Convert ull number into string
		string longLongToBinary(long long num, bool doNewLines) {
			string binary;
			for (int i = 63; i >= 0; --i) {
				binary += ((num >> i) & 1) ? '1' : '.';

				if (i % 8 == 0 && doNewLines) binary += '\n';
			}
			return binary;
		}


		// Combine bitboards
		ull getBlackBitboard() {
			return bp | bb | bn | br | bq | bk;
		}
		ull getWhiteBitboard() {
			return wp | wb | wn | wr | wq | wk;
		}
		ull getAllBitboard() {
			return getBlackBitboard() | getWhiteBitboard();
		}


		// Additional functions
		char getPieceType(int num) {
			if (setBitOnEmptyBoard(num) & (wp | bp)) return 'p';
			if (setBitOnEmptyBoard(num) & (wb | bb)) return 'b';
			if (setBitOnEmptyBoard(num) & (wn | bn)) return 'n';
			if (setBitOnEmptyBoard(num) & (wr | br)) return 'r';
			if (setBitOnEmptyBoard(num) & (wq | bq)) return 'q';
			if (setBitOnEmptyBoard(num) & (wk | bk)) return 'k';

			return '-';
		}


		// Returns a bitboard with only one piece on given square
		ull setBitOnEmptyBoard(int num) {
			return 1LL << (63 - num);
		}


		// All this functions were used to generate possible moves for non sliding pieces
		std::vector<ull> generateAllKnightMoves() {
			std::vector<ull> result;

			for (int i = 0; i < 64; i++) {
				ull knight = setBitOnEmptyBoard(i);

				ull moves = (knight & ~litl::col_gh & ~litl::row_8) << 6 |
							(knight & ~litl::col_ab & ~litl::row_8) << 10 |
							(knight & ~litl::col_h & ~litl::row_78) << 15 |
							(knight & ~litl::col_a & ~litl::row_78) << 17 |
							(knight & ~litl::col_ab & ~litl::row_1) >> 6 |
							(knight & ~litl::col_gh & ~litl::row_1) >> 10 |
							(knight & ~litl::col_a & ~litl::row_12) >> 15 |
							(knight & ~litl::col_h & ~litl::row_12) >> 17;

				result.push_back(moves);
			}

			return result;
		}
		std::vector<ull> generateAllKingMoves() {
			std::vector<ull> result;

			for (int i = 0; i < 64; i++) {
				ull king = setBitOnEmptyBoard(i);

				ull moves = (king & ~litl::col_a) << 1 |
							(king & ~litl::col_h & ~litl::row_8) << 7 |
							(king & ~litl::row_8) << 8 |
							(king & ~litl::col_a & ~litl::row_8) << 9 |
							(king & ~litl::col_h) >> 1 |
							(king & ~litl::col_a & ~litl::row_1) >> 7 |
							(king & ~litl::row_1) >> 8 |
							(king & ~litl::col_h & ~litl::row_1) >> 9;

				result.push_back(moves);
			}

			return result;
		}
		std::vector<ull> generateAllWhitePawnsMoves() {
			std::vector<ull> result;

			for (int i = 0; i < 64; i++) {
				ull pawn = setBitOnEmptyBoard(i);

				ull moves = pawn << 8 | (pawn & row_2) << 16;

				result.push_back(moves);
			}

			return result;
		}
		std::vector<ull> generateAllBlackPawnsMoves() {
			std::vector<ull> result;

			for (int i = 0; i < 64; i++) {
				ull pawn = setBitOnEmptyBoard(i);

				ull moves = pawn >> 8 | (pawn & row_7) >> 16;

				result.push_back(moves);
			}

			return result;
		}
		std::vector<ull> generateAllWhitePawnsCaptures() {
			std::vector<ull> result;

			for (int i = 0; i < 64; i++) {
				ull pawn = setBitOnEmptyBoard(i);

				ull moves = (pawn & ~col_h) << 7 | (pawn & ~col_a) << 9;

				result.push_back(moves);
			}

			return result;
		}
		std::vector<ull> generateAllBlackPawnsCaptures() {
			std::vector<ull> result;

			for (int i = 0; i < 64; i++) {
				ull pawn = setBitOnEmptyBoard(i);

				ull moves = (pawn & ~col_a) >> 7 | (pawn & ~col_h) >> 9;

				result.push_back(moves);
			}

			return result;
		}


		// Sliding pieces bitboards generation (afaik magic bitboards will be >800 kib which is bigger than esp32 is available to store)
		ull getRookMovesBitboard(int num, ull pieces) {
			ull result = 0;

			pieces = setBitOnEmptyBoard(num) ^ pieces;

			ull startingPosition = setBitOnEmptyBoard(num);

			ull down = startingPosition;
			while (true) {
				down >>= 8;
				if (down) result |= down;
				else break;

				if (down & pieces) break;
			}

			ull up = startingPosition;
			while (true) {
				up <<= 8;
				if (up) result |= up;
				else break;

				if (up & pieces) break;
			}

			ull right = startingPosition;
			while (true) {
				right &= ~col_h;
				right >>= 1;

				if (right) result |= right;
				else break;

				if (right & pieces) break;
			}

			ull left = startingPosition;
			while (true) {
				left &= ~col_a;
				left <<= 1;

				if (left) result |= left;
				else break;

				if (left & pieces) break;
			}

			return result & ~startingPosition;
		}
		ull getBishopMovesBitboard(int num, ull pieces) {
			ull result = 0;

			pieces = setBitOnEmptyBoard(num) ^ pieces;
			ull startingPosition = setBitOnEmptyBoard(num);

			ull dl = startingPosition;
			while (true) {
				dl &= ~col_a;
				dl >>= 7;

				if (dl) result |= dl;
				else break;

				if (dl & pieces) break;
			}

			ull ul = startingPosition;
			while (true) {
				ul &= ~col_a;
				ul <<= 9;

				if (ul) result |= ul;
				else break;

				if (ul & pieces) break;
			}

			ull dr = startingPosition;
			while (true) {
				dr &= ~col_h;
				dr >>= 9;

				if (dr) result |= dr;
				else break;

				if (dr & pieces) break;
			}

			ull ur = startingPosition;
			while (true) {
				ur &= ~col_h;
				ur <<= 7;

				if (ur) result |= ur;
				else break;

				if (ur & pieces) break;
			}

			return result & ~startingPosition;
		}
		ull getQueenMovesBitboard(int num, ull pieces) {
			return getRookMovesBitboard(num, pieces) | getBishopMovesBitboard(num, pieces);
		}


		// Just a set of functions to get data from premade moves bitboards
		ull getKnightMovesBitboard(int num) {
			return knightMoves[num];
		}
		ull getKingMovesBitboard(int num) {
			return knightMoves[num];
		}
		ull getPawnMovesBitboard(int num, bool isWhite) {
			if (isWhite) return wpMoves[num];
			return bpMoves[num];
		}
		ull getPawnCapturesBitboard(int num, bool isWhite) {
			if (isWhite) return wpCaptures[num];
			return bpCaptures[num];
		}


		// Pieces logic is done here
		std::vector<litl::move> getRookMoves(int num, bool isWhite) {
			std::vector<litl::move> result;

			ull teamBitboard = isWhite ? getWhiteBitboard() : getBlackBitboard();
			ull oppoBitboard = isWhite ? getBlackBitboard() : getWhiteBitboard();

			ull bitboard = getRookMovesBitboard(num, getAllBitboard());
			bitboard &= ~teamBitboard;

			bool isCapture = false;

			if (bitboard & oppoBitboard) {
				bitboard &= oppoBitboard;
				isCapture = true;
			}

			int i = 0;
			while (bitboard) {
				if(bitboard & 1LL) result.push_back(move(num, 63 - i, isCapture));

				bitboard >>= 1;
				i++;
			}

			return result;
		}
		std::vector<litl::move> getBishopMoves(int num, bool isWhite) {
			std::vector<litl::move> result;

			ull teamBitboard = isWhite ? getWhiteBitboard() : getBlackBitboard();
			ull oppoBitboard = isWhite ? getBlackBitboard() : getWhiteBitboard();

			ull bitboard = getBishopMovesBitboard(num, getAllBitboard());
			bitboard &= ~teamBitboard;

			bool isCapture = false;

			if (bitboard & oppoBitboard) {
				bitboard &= oppoBitboard;
				isCapture = true;
			}

			int i = 0;
			while (bitboard) {
				if (bitboard & 1LL) result.push_back(move(num, 63 - i, isCapture));

				bitboard >>= 1;
				i++;
			}

			return result;
		}
		std::vector<litl::move> getKnightMoves(int num, bool isWhite) {
			std::vector<litl::move> result;

			ull teamBitboard = isWhite ? getWhiteBitboard() : getBlackBitboard();
			ull oppoBitboard = isWhite ? getBlackBitboard() : getWhiteBitboard();

			ull bitboard = getKnightMovesBitboard(num);
			bitboard &= ~teamBitboard;

			bool isCapture = false;

			if (bitboard & oppoBitboard) {
				bitboard &= oppoBitboard;
				isCapture = true;
			}

			int i = 0;
			while (bitboard) {
				if (bitboard & 1LL) result.push_back(move(num, 63 - i, isCapture));

				bitboard >>= 1;
				i++;
			}

			return result;
		}
		std::vector<litl::move> getQueenMoves(int num, bool isWhite) {
			std::vector<litl::move> result;

			ull teamBitboard = isWhite ? getWhiteBitboard() : getBlackBitboard();
			ull oppoBitboard = isWhite ? getBlackBitboard() : getWhiteBitboard();

			ull bitboard = getQueenMovesBitboard(num, getAllBitboard());
			bitboard &= ~teamBitboard;

			bool isCapture = false;

			if (bitboard & oppoBitboard) {
				bitboard &= oppoBitboard;
				isCapture = true;
			}

			int i = 0;
			while (bitboard) {
				if (bitboard & 1LL) result.push_back(move(num, 63 - i, isCapture));

				bitboard >>= 1;
				i++;
			}

			return result;
		}
		std::vector<litl::move> getKingMoves(int num, bool isWhite) {
			std::vector<litl::move> result;

			ull teamBitboard = isWhite ? getWhiteBitboard() : getBlackBitboard();
			ull oppoBitboard = isWhite ? getBlackBitboard() : getWhiteBitboard();

			ull bitboard = getKingMovesBitboard(num);
			bitboard &= ~teamBitboard;

			bool isCapture = false;

			if (bitboard & oppoBitboard) {
				bitboard &= oppoBitboard;
				isCapture = true;
			}

			int i = 0;
			while (bitboard) {
				if (bitboard & 1LL) result.push_back(move(num, 63 - i, isCapture));

				bitboard >>= 1;
				i++;
			}

			return result;
		}
		std::vector<litl::move> getPawnMoves(int num, bool isWhite) {
			std::vector<litl::move> result;

			ull any = getAllBitboard();

			ull teamBitboard = isWhite ? getWhiteBitboard() : getBlackBitboard();
			ull oppoBitboard = isWhite ? getBlackBitboard() : getWhiteBitboard();

			ull moves = getPawnMovesBitboard(num, isWhite);
			ull captures = getPawnCapturesBitboard(num, isWhite);

			if (moves & any) {
				moves &= ~row_5;
				moves &= ~row_4;
			}

			moves &= ~any;

			if (captures & oppoBitboard) {
				captures &= oppoBitboard;

				int i = 0;
				while (captures) {
					if (captures & 1LL) result.push_back(litl::move(num, 63 - i, true));

					captures >>= 1;
					i++;
				}
			}
			else {
				int i = 0;
				while (moves) {
					if (moves & 1LL) result.push_back(litl::move(num, 63 - i, false));

					moves >>= 1;
					i++;
				}
			}

			return result;
		}


		// Generate legal move for given position
		std::vector<litl::move> getLegalMoves() {
			std::vector<litl::move> result;

			ull self = isWhitesTurn ? getWhiteBitboard() : getBlackBitboard();

			int i = 0;
			while (self) {
				if (self & 1LL) {
					char type = getPieceType(63 - i);

					std::vector<litl::move> temp;

					if (type == 'b') {
						temp = getBishopMoves(63 - i, isWhitesTurn);
					} 
					else if (type == 'n') {
						temp = getKnightMoves(63 - i, isWhitesTurn);
					}
					else if (type == 'r') {
						temp = getRookMoves(63 - i, isWhitesTurn);
					}
					else if (type == 'q') {
						temp = getQueenMoves(63 - i, isWhitesTurn);
					}
					else if (type == 'k') {
						temp = getKingMoves(63 - i, isWhitesTurn);
					}
					else if (type == 'p') {
						temp = getPawnMoves(63 - i, isWhitesTurn);
					}

					if (temp.size() == 0) {
						i++;
						self >>= 1;
						continue;
					}

					if (result.size() == 0) result = temp;
					else if (result[0].isCapture && temp[0].isCapture) result.insert(result.end(), temp.begin(), temp.end());
					else if (!result[0].isCapture) {
						if (temp[0].isCapture) result = temp;
						else result.insert(result.end(), temp.begin(), temp.end());
					}
				}

				i++;
				self >>= 1;
			}

			return result;
		}
	};

	static position buildPosition(string fen) {
		position result;

		int i = 0;
		while (true) {
			char c = fen[i];

			if (isdigit(c)) {
				int num = c - '0';

				result.push(num);
			}
			else if (c == '/') {

			}
			else if (c == ' ') {
				break;
			}
			else {
				result.push(c);
			}

			i++;
		}

		i += 2;

		result.isWhitesTurn = fen[i] == 'w';

		return result;
	}
}