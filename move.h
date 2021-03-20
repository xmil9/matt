//
// Feb-2021, Michael Lindner
// MIT license
//
#pragma once
#include "piece.h"
#include "square.h"
#include <string>

class Position;


///////////////////

class Move
{
 public:
   Move() = default;
   Move(const Piece& piece, Square to, std::string notation);

   const Piece& piece() const { return m_piece; }
   Square from() const { return m_piece.location(); }
   Square to() const { return m_to; }
   const std::string& notate() const { return m_notation; }
   Piece movedPiece() const { return m_piece.move(m_to); }

   friend void swap(Move& a, Move& b) noexcept
   {
      using std::swap;
      swap(a.m_piece, b.m_piece);
      swap(a.m_to, b.m_to);
      swap(a.m_notation, b.m_notation);
   }

 private:
   Piece m_piece;
   Square m_to;
   // Need to store the move's notation because to resolve ambiguities the position from
   // which the move was made is needed to generate the notation.
   std::string m_notation;
};


inline Move::Move(const Piece& piece, Square to, std::string notation)
: m_piece{piece}, m_to{to}, m_notation{std::move(notation)}
{
}

inline bool operator==(const Move& a, const Move& b)
{
   return a.piece() == b.piece() && a.to() == b.to() && a.notate() == b.notate();
}


///////////////////

std::string notateMove(const Piece& piece, Square to, const Position& pos);
