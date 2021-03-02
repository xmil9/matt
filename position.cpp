//
// Feb-2021, Michael Lindner
// MIT license
//
#include "position.h"
#include "move.h"
#include <algorithm>


///////////////////

bool Position::isOccupied(Square loc) const
{
   return (*this)[loc].has_value();
}


bool Position::isOccupiedBy(Square loc, Color byColor) const
{
   const auto piece = (*this)[loc];
   return piece.has_value() && piece->color() == byColor;
}


std::optional<Piece> Position::operator[](Square loc) const
{
   const auto it = std::find_if(begin(pieces), end(pieces), [&loc](const Piece& piece) {
      return piece.location() == loc;
   });
   if (it != end(pieces))
      return *it;
   return std::nullopt;
}
