//
// Feb-2021, Michael Lindner
// MIT license
//
#pragma once
#include "square.h"
#include <optional>
#include <variant>
#include <vector>

class Move;
class Position;


///////////////////

enum class Color
{
   White,
   Black
};

inline Color operator!(Color color)
{
   return color == Color::White ? Color::Black : Color::White;
}


///////////////////

class Piece
{
 public:
   enum class Type
   {
      King,
      Queen,
      Rook,
      Bishop,
      Knight,
      Pawn
   };

   Piece() = default;
   Piece(Type type, Color color, Square loc);

   Square location() const { return m_loc; }
   Color color() const { return m_color; }
   std::string notation() const;
   std::vector<Move> nextMoves(const Position& pos) const;
   std::vector<Position> nextPositions(const Position& pos) const;

   bool operator==(const Piece& other) const;

 private:
   Type m_type = Type::Pawn;
   Color m_color = Color::White;
   Square m_loc;
};


inline Piece::Piece(Type type, Color color, Square loc)
: m_type{type}, m_color{color}, m_loc{loc}
{
}

inline bool Piece::operator==(const Piece& other) const
{
   return m_type == other.m_type && m_color == other.color() && m_loc == other.location();
}

inline bool operator==(const Piece& a, const std::optional<Piece>& b)
{
   return b.has_value() && a == *b;
}

inline bool operator==(const std::optional<Piece>& a, const Piece& b)
{
   return b == a;
}
