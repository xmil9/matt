//
// Feb-2021, Michael Lindner
// MIT license
//
#pragma once
#include "piece.h"
#include "record.h"
#include "dscpp/SboVector.h"
#include <array>
#include <string>
#include <vector>


///////////////////

class Position
{
   friend bool operator==(const Position&, const Position&);

 public:
   Position() = default;
   explicit Position(const std::vector<Piece>& pieces);
   explicit Position(ds::SboVector<Piece, 32>&& pieces, Record&& record);
   explicit Position(std::string_view notation);

   float score() const { return m_score; }
   bool isOccupiedBy(Square coord, Color side) const;
   bool isThreatenedBy(Square coord, Color side) const;
   std::optional<Piece> operator[](Square coord) const;
   std::vector<Piece> pieces(Color side) const;
   Position makeMove(const Move& move) const;
   std::string notate() const;
   std::string initialPosition() const { return m_record.initialPosition(); }
   std::string recordedMoves() const { return m_record.moves(); }
 private:
   using Iter = ds::SboVector<Piece, 32>::iterator;
   using Citer = ds::SboVector<Piece, 32>::const_iterator;

   void populateBoard();
   Iter at(Square coord);
   Citer at(Square coord) const;
   float calcScore() const;
   float calcValue(const std::vector<Piece>& pieces) const;

 private:
   ds::SboVector<Piece, 32> m_pieces;
   std::array<unsigned char, 64> m_board;
   Record m_record;
   float m_score = 0.f;
};


///////////////////

bool operator==(const Position& a, const Position& b);

inline bool operator!=(const Position& a, const Position& b)
{
   return !(a == b);
}

inline bool operator<(const Position& a, const Position& b)
{
   return a.score() < b.score();
}


extern const Position StartPos;