//
// Feb-2021, Michael Lindner
// MIT license
//
#include "matt.h"
#include "position.h"
#include <algorithm>
#include <iterator>


std::optional<Position> makeMove(const Position& pos, Color side)
{
   std::vector<Position> bestByPieces;
   const auto pieces = pos.pieces(side);
   for (const auto& piece : pieces)
      if (const auto best = makeMove(pos, piece); best.has_value())
         bestByPieces.push_back(*best);

   const auto it = std::max_element(
      begin(bestByPieces), end(bestByPieces),
      [](const auto& a, const auto& b) { return a.score() < b.score(); });
   if (it == end(bestByPieces))
      return std::nullopt;
   return *it;
}


std::optional<Position> makeMove(const Position& pos, const Piece& piece)
{
   const auto positions = piece.nextPositions(pos);
   const auto it = std::max_element(
      begin(positions), end(positions),
      [](const auto& a, const auto& b) { return a.score() < b.score(); });
   if (it == end(positions))
      return std::nullopt;
   return *it;
}
