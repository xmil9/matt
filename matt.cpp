//
// Feb-2021, Michael Lindner
// MIT license
//
#include "matt.h"
#include "position.h"
#include <algorithm>
#include <iterator>


static std::optional<Position> bestPosition(const std::vector<Position>& positions,
                                            Color side)
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


std::optional<Position> makeMove(const Position& pos, Color side)
{
   // Collect best moves for each piece.
   std::vector<Position> bestByPieces;
   const auto pieces = pos.pieces(side);
   for (const auto& piece : pieces)
      if (const auto best = makeMove(pos, piece); best.has_value())
         bestByPieces.push_back(*best);

   // Find best move of of those.
   return bestPosition(bestByPieces, side);
}


std::optional<Position> makeMove(const Position& pos, const Piece& piece)
{
   return bestPosition(piece.nextPositions(pos), piece.color());
}
