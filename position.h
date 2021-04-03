//
// Feb-2021, Michael Lindner
// MIT license
//
#pragma once
#include "piece.h"
#include "record.h"
#include <string>
#include <vector>


///////////////////

class Position
{
   friend bool operator==(const Position&, const Position&);

 public:
   Position() = default;
   explicit Position(const std::vector<Piece>& pieces);
   explicit Position(std::string_view notation);

   float score() const { return m_score; } 
   bool isOccupiedBy(Square coord, Color bySide) const;
   std::optional<Piece> operator[](Square coord) const;
   std::vector<Piece> pieces(Color side) const;
   std::string notate() const;
   Position makeMove(const Move& move) const;

 private:
   using Iter = std::vector<Piece>::iterator;
   using Citer = std::vector<Piece>::const_iterator;

   Iter at(Square coord);
   Citer at(Square coord) const;
   float calcScore() const;
   float calcValue(const std::vector<Piece>& pieces) const;

 private:
   std::vector<Piece> m_pieces;
   Record m_record;
   float m_score = 0.f;
};


///////////////////

bool operator==(const Position& a, const Position& b);

inline bool operator!=(const Position& a, const Position& b)
{
   return !(a == b);
}


extern const Position StartPos;