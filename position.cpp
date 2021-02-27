//
// Feb-2021, Michael Lindner
// MIT license
//
#include "position.h"
#include <algorithm>


///////////////////

bool Position::isOccupied(Square loc) const
{
   return std::find_if(begin(pieces), end(pieces), [&loc](const Piece& piece) {
             return isOnSquare(piece, loc);
          }) != end(pieces);
}
