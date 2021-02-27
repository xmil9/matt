//
// Feb-2021, Michael Lindner
// MIT license
//
#include "piece.h"
#include "position.h"
#include <algorithm>
#include <array>
#include <iterator>


///////////////////

std::vector<Square> King::moves(const Position& pos) const
{
   assert(pos[location()] == Piece{*this});

   std::vector<Square> result;

   static const std::array<Offset, 8> Moves{Offset{1, 1}, {1, 0},  {1, -1}, {0, 1},
                                            {0, -1},      {-1, 1}, {-1, 0}, {-1, -1}};
   for (const auto& off : Moves)
   {
      const auto to = location() + off;
      if (isLegalMove(pos, to))
         result.push_back(*to);
   }

   return result;
}


bool King::isLegalMove_(const Position& pos, Square loc) const
{
   return !pos.isOccupied(loc);
}
