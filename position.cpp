//
// Feb-2021, Michael Lindner
// MIT license
//
#include "position.h"
#include <algorithm>


///////////////////

bool Position::isOccupied(Square loc) const
{
   return (*this)[loc].has_value();
}


bool Position::isOccupiedBy(Square loc, Color bySide) const
{
   const auto piece = (*this)[loc];
   return piece.has_value() && hasColor(*piece, bySide);
}


std::optional<Piece> Position::operator[](Square loc) const
{
   const auto it = std::find_if(begin(pieces), end(pieces), [&loc](const Piece& piece) {
      return isOnSquare(piece, loc);
   });
   if (it != end(pieces))
      return *it;
   return std::nullopt;
}
