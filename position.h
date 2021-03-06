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
   Position();
   explicit Position(const std::vector<Piece>& pieces);
   explicit Position(const std::string& notation);

   bool isOccupied(Square loc) const;
   bool isOccupiedBy(Square loc, Color bySide) const;
   std::optional<Piece> operator[](Square loc) const;
   std::vector<Piece> pieces(Color side) const;
   void makeMove(const Move& move);

 private:
   using Iter = std::vector<Piece>::iterator;
   using Citer = std::vector<Piece>::const_iterator;

   Iter at(Square loc);
   Citer at(Square loc) const;
   double calcScore() const;

 private:
   std::vector<Piece> m_pieces;
   Record m_record;
   double m_score = 0.;
};
