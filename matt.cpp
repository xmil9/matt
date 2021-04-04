//
// Feb-2021, Michael Lindner
// MIT license
//
#include "matt.h"
#include "position.h"
#include <algorithm>
#include <iterator>


namespace
{
///////////////////

std::optional<Position> bestPosition(const std::vector<Position>& positions, Color side)
{
   // Use best scoring next position depending on the piece's color.
   const auto endPos = end(positions);
   auto bestPos = endPos;
   if (side == Color::White)
      bestPos = std::max_element(begin(positions), endPos);
   else
      bestPos = std::min_element(begin(positions), endPos);

   if (bestPos == endPos)
      return std::nullopt;
   return *bestPos;
}


std::vector<Position> allMoves(const Position& pos, Color side)
{
   std::vector<Position> allMoves;
   const auto pieces = pos.pieces(side);
   for (const auto& piece : pieces)
   {
      const auto pieceMoves = piece.nextPositions(pos);
      allMoves.insert(std::end(allMoves), std::begin(pieceMoves), std::end(pieceMoves));
   }

   return allMoves;
}


std::optional<Position> makeMove_(const Position& pos, Color side, std::size_t plies)
{
   const auto moves = allMoves(pos, side);

   const std::vector<Position>* bestMoves = &moves;
   std::vector<Position> bestNextMoves;
   bestNextMoves.reserve(moves.size());

   if (plies > 1)
   {
      for (const auto& move : moves)
      {
         if (const auto nextMove = makeMove_(move, !side, plies - 1);
             nextMove.has_value())
         {
            bestNextMoves.push_back(*nextMove);
         }
      }

      bestMoves = &bestNextMoves;
   }

   return bestPosition(*bestMoves, side);
}

} // namespace


///////////////////

std::optional<Position> makeMove(const Position& pos, Color side, std::size_t turns)
{
   // Convert turns (one move of each player) to plies (one move of one player).
   return makeMove_(pos, side, 2 * turns);
}
