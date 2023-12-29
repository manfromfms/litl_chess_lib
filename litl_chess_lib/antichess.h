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

		int eval(bool isCapture) {
			int counter = 0;

			// Count all pieces
			ull team = position.isWhitesTurn ? position.getWhiteBitboard() : position.getWhiteBitboard();
			ull oppo = position.isWhitesTurn ? position.getBlackBitboard() : position.getWhiteBitboard();
			while (team | oppo) {
				if (team & 1LL) counter -= 10;
				if (oppo & 1LL) counter += 10;

				team >>= 1;
				oppo >>= 1;
			}

			// Count pawns
			ull tp = position.isWhitesTurn ? position.wp : position.bp;
			ull op = position.isWhitesTurn ? position.bp : position.wp;
			while (tp | op) {
				if (tp & 1LL) counter -= 80;
				if (op & 1LL) counter += 80;

				tp >>= 1;
				op >>= 1;
			}

			// Count kings
			ull tk = position.isWhitesTurn ? position.wk : position.bk;
			ull ok = position.isWhitesTurn ? position.bk : position.wk;
			while (tk | ok) {
				if (tk & 1LL) counter -= 60;
				if (ok & 1LL) counter += 60;

				tk >>= 1;
				ok >>= 1;
			}

			// Count bishops
			ull tb = position.isWhitesTurn ? position.wb : position.bb;
			ull ob = position.isWhitesTurn ? position.bb : position.wb;
			while (tb | ob) {
				if (tb & 1LL) counter -= 60;
				if (ob & 1LL) counter += 60;

				tb >>= 1;
				ob >>= 1;
			}

			// Count knights
			ull tn = position.isWhitesTurn ? position.wn : position.bn;
			ull on = position.isWhitesTurn ? position.bn : position.wn;
			while (tn | on) {
				if (tn & 1LL) counter -= 60;
				if (on & 1LL) counter += 60;

				tn >>= 1;
				on >>= 1;
			}

			// Count rooks
			ull tr = position.isWhitesTurn ? position.wr : position.bn;
			ull or_ = position.isWhitesTurn ? position.br : position.wn;
			while (tr | or_) {
				if (tr & 1LL) counter -= 60;
				if (or_ & 1LL) counter += 60;

				tr >>= 1;
				or_ >>= 1;
			}

			// Count queens
			ull tq = position.isWhitesTurn ? position.wq : position.bq;
			ull oq = position.isWhitesTurn ? position.bq : position.wq;
			while (tq | oq) {
				if (tq & 1LL) counter -= 180;
				if (oq & 1LL) counter += 180;

				tq >>= 1;
				oq >>= 1;
			}

			// Check if has a capture
			counter += isCapture ? -80 : 80;

			return counter;
		}

		int calc(bool isTop, int depth, int alpha, int beta) {
			std::vector<litl::move> moves = position.getLegalMoves();

			if (moves.size() == 0) return 1000000;

			if (depth <= 0) return eval(moves[0].isCapture);

			if (isTop) this->bestMove = moves[0];

			for (auto& move : moves) {
				position.makeMove(move);

				int temp = -calc(false, depth - 1, -beta, -alpha);
				//std::cout << bestMove.uci() << std::endl;

				position.undoMove(move);

				if (temp >= beta) {
					return beta;
				}

				if (temp >= alpha) {
					alpha = temp;

					if (isTop) {
						this->bestMove = move;
						std::cout << "Changed best move to: " << move.uci() << " " << alpha << std::endl;
					}
				}
			}

			return alpha;
		}
	};
}