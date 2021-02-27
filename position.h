//
// Feb-2021, Michael Lindner
// MIT license
//
#pragma once
#include "piece.h"
#include <vector>


///////////////////

struct Position
{
   std::vector<Piece> pieces;

   bool isOccupied(Square loc) const;
   bool isOccupiedBy(Square loc, Color bySide) const;
   std::optional<Piece> operator[](Square loc) const;
};
