//
// Feb-2021, Michael Lindner
// MIT license
//
#pragma once
#include "notation.h"
#include "piece.h"
#include <vector>


///////////////////

class Position
{
 public:
   bool isOccupied(Square loc) const;
   bool isOccupiedBy(Square loc, Color bySide) const;
   std::optional<Piece> operator[](Square loc) const;

 private:
   std::vector<Piece> pieces;
   Record m_record;
};
