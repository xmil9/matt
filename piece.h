//
// Feb-2021, Michael Lindner
// MIT license
//
#pragma once
#include "square.h"
#include <optional>
#include <string>
#include <vector>

class Move;
class Position;


///////////////////

enum class Color
{
   White,
   Black
};

inline Color operator!(Color c)
{
   return c == Color::White ? Color::Black : Color::White;
}

inline std::string notateColor(Color c)
{
   switch (c)
   {
   case Color::White:
      return "w";
   case Color::Black:
      return "b";
   default:
      return "";
   }
}

inline Color makeColor(char notation)
{
   switch (notation)
   {
   case 'w':
      return Color::White;
   case 'b':
      return Color::Black;
   default:
      return Color::White;
   }
}

inline Color makeColor(std::string_view notation)
{
   if (notation.empty())
      return Color::White;
   return makeColor(notation[0]);
}


///////////////////

enum class Figure
{
   King,
   Queen,
   Rook,
   Bishop,
   Knight,
   Pawn
};

inline std::string notateFigure(Figure f)
{
   switch (f)
   {
   case Figure::King:
      return "K";
   case Figure::Queen:
      return "Q";
   case Figure::Rook:
      return "R";
   case Figure::Bishop:
      return "B";
   case Figure::Knight:
      return "N";
   case Figure::Pawn:
      return "";
   default:
      return "";
   }
}

inline Figure makeFigure(char notation)
{
   switch (notation)
   {
   case 'K':
      return Figure::King;
   case 'Q':
      return Figure::Queen;
   case 'R':
      return Figure::Rook;
   case 'B':
      return Figure::Bishop;
   case 'N':
      return Figure::Knight;
   default:
      return Figure::Pawn;
   }
}

inline Figure makeFigure(std::string_view notation)
{
   if (notation == "")
      return Figure::Pawn;
   return makeFigure(notation[0]);
}


///////////////////

class Piece
{
 public:
   Piece() = default;
   Piece(Figure figure, Color color, Square coord);
   Piece(Figure figure, Color color, std::string_view coord);
   Piece(std::string_view notation);
   Piece(std::string_view notation, Color side);

   Color color() const { return m_color; }
   Square coord() const { return m_coord; }
   Figure figure() const { return m_figure; }
   // Does not prevent moves that are illegal for the piece.
   Piece move(Square to) const;
   std::vector<Square> reachableSquares(const Position& pos) const;
   std::vector<Move> nextMoves(const Position& pos) const;
   std::vector<Position> nextPositions(const Position& pos) const;

   bool operator==(const Piece& other) const;

   friend void swap(Piece& a, Piece& b) noexcept
   {
      using std::swap;
      swap(a.m_figure, b.m_figure);
      swap(a.m_color, b.m_color);
      swap(a.m_coord, b.m_coord);
   }

   // Notation formats:
   // F = figure
   // C = color
   // L = location coordinate
   enum class Notation
   {
      F,
      FL,
      FC,
      FCL
   };
   std::string notate(Notation format = Notation::F) const;

 private:
   Figure m_figure = Figure::Pawn;
   Color m_color = Color::White;
   Square m_coord;
};


inline Piece::Piece(Figure figure, Color color, Square coord)
: m_figure{figure}, m_color{color}, m_coord{coord}
{
}

inline Piece Piece::move(Square to) const
{
   return Piece{m_figure, m_color, to};
}

inline bool Piece::operator==(const Piece& other) const
{
   return m_figure == other.m_figure && m_color == other.m_color &&
          m_coord == other.m_coord;
}

inline bool operator!=(const Piece& a, const Piece& b)
{
   return !(a == b);
}

inline bool operator==(const Piece& a, const std::optional<Piece>& b)
{
   return b.has_value() && a == *b;
}

inline bool operator==(const std::optional<Piece>& a, const Piece& b)
{
   return b == a;
}

inline Piece operator"" _pc(const char* str, std::size_t)
{
   return Piece{str};
}


///////////////////

bool isPawnOnInitialRank(const Piece& pawn);
Offset pawnDirection(const Piece& pawn);
