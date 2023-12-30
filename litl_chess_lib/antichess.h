#pragma once

#include <string>
using std::string;

#include "position.h"
#include "SearchData.h"
#include <algorithm>

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


		// Sort move for better AB prefomance
		std::vector<litl::move> orderMoves(std::vector<litl::move> moves) {
			// Loop through all the moves
			for (auto& move : moves) {
				position.makeMove(move);

				if (position.checkIfHasToCapture()) {
					move.order = 1;
				}
				else {
					move.order = -1;
				}

				/*position.changeTurn();
				if (position.checkIfHasToCapture()) {
					move.order -= 1;
				}
				else {
					move.order -= -1;
				}
				position.changeTurn();*/

				position.undoMove(move);
			}


			// Sort and return moves array
			std::sort(moves.begin(), moves.end(), CompareByOrder());
			return moves;
		}


		// Evaluation function
		int eval(bool isCapture) {
			int counter = 0;

			ull pieces = position.getAllBitboard();

			// Get piece value from database
			int num = 0;
			while (pieces) {
				counter += getPieceValue(position.getFullPieceType(63 - num), 63 - num, position.moveNumber) * (position.isWhitesTurn ? 1 : -1);
				pieces >>= 1;
				num += 1;
			}

			// Check if has a capture
			counter += isCapture ? -80 : 80;

			return counter;
		}


		// Find evaluation for given position
		int calc(bool isTop, int depth, int alpha, int beta) {
			// Get all legal moves
			std::vector<litl::move> generated = position.getLegalMoves();

			// Check for variant game end rule
			if (generated.size() == 0) return 1000000;

			// Order moves
			std::vector<litl::move> moves = orderMoves(generated);

			// Check for depth
			if (depth <= 0) return eval(moves[0].isCapture);

			if (isTop) this->bestMove = moves[0];

			// Go through all the moves
			for (auto& move : moves) {
				position.makeMove(move);

				int temp = -calc(false, depth - 1, -beta, -alpha);
				//std::cout << bestMove.uci() << std::endl;

				position.undoMove(move);

				// Do alpha-beta pruning
				if (temp >= beta) {
					return beta;
				}

				// Update best move if found
				if (temp > alpha) {
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