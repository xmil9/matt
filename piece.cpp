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

std::vector<Square> King::moves_(const Position& pos) const
{
   assert(pos[location()] == Piece{*this});

   std::vector<Square> result;

   static const std::array<Offset, 8> Directions{
      Offset{1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}};
   for (const auto& dir : Directions)
   {
      const auto to = location() + dir;
      if (canOccupy_(pos, to))
         result.push_back(*to);
   }

   return result;
}


bool King::canOccupy_(const Position& pos, Square loc) const
{
   // todo - check if king would be in check on square.
   return !pos.isOccupied(loc);
}


bool King::canOccupy_(const Position& pos, std::optional<Square> loc) const
{
   if (loc.has_value())
      return canOccupy_(pos, *loc);
   return false;
}


///////////////////

std::vector<Square> Queen::moves_(const Position& pos) const
{
   assert(pos[location()] == Piece{*this});

   std::vector<Square> result;

   static const std::array<Offset, 8> Directions{
      Offset{1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}};
   for (const auto& dir : Directions)
   {
      std::optional<Square> to = location() + dir;
      while (to.has_value())
      {
         if (!pos.isOccupied(*to))
         {
            result.push_back(*to);
            to = to + dir;
         }
         else
         {
            to = std::nullopt;
         }
      }
   }

   return result;
}
