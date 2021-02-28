//
// Feb-2021, Michael Lindner
// MIT license
//
#pragma once
#include "square.h"
#include <optional>
#include <variant>
#include <vector>

struct Position;


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

template <typename DerivedPiece> class PieceBase
{
 public:
   PieceBase(Color color, Square loc);

   // Common interface for all pieces.
   Square location() const { return m_loc; }
   Color color() const { return m_color; }
   std::string notation() const { return derived().notation_(); }
   std::vector<Square> moves(const Position& pos) const { return derived().moves_(pos); }

 private:
   const DerivedPiece& derived() const { return static_cast<const DerivedPiece&>(*this); }
   DerivedPiece& derived() { return static_cast<DerivedPiece&>(*this); }

 private:
   Color m_color = Color::White;
   Square m_loc;
};


template <typename DerivedPiece>
PieceBase<DerivedPiece>::PieceBase(Color color, Square loc) : m_color{color}, m_loc{loc}
{
}


template <typename DerivedPiece>
bool operator==(const DerivedPiece& a, const DerivedPiece& b)
{
   return a.color() == b.color() && a.location() == b.location();
}


template <typename DerivedPiece>
bool operator==(const std::optional<DerivedPiece>& a,
                const std::optional<DerivedPiece>& b)
{
   if (a.has_value() && b.has_value())
      return *a == *b;
   return a.has_value() == b.has_value();
}


///////////////////

class King : public PieceBase<King>
{
   friend class PieceBase<King>;

 public:
   using PieceBase<King>::PieceBase;

 private:
   std::string notation_() const { return "K"; }
   std::vector<Square> moves_(const Position& pos) const;
};

class Queen : public PieceBase<Queen>
{
   friend class PieceBase<Queen>;

 public:
   using PieceBase<Queen>::PieceBase;

 private:
   std::string notation_() const { return "Q"; }
   std::vector<Square> moves_(const Position& pos) const;
};

class Rook : public PieceBase<Rook>
{
   friend class PieceBase<Rook>;

 public:
   using PieceBase<Rook>::PieceBase;

 private:
   std::string notation_() const { return "R"; }
   std::vector<Square> moves_(const Position& pos) const;
};

class Bishop : public PieceBase<Bishop>
{
   friend class PieceBase<Bishop>;

 public:
   using PieceBase<Bishop>::PieceBase;

 private:
   std::string notation_() const { return "B"; }
   std::vector<Square> moves_(const Position& pos) const;
};

class Knight : public PieceBase<Knight>
{
   friend class PieceBase<Knight>;

 public:
   std::string notation_() const { return "N"; }
   using PieceBase<Knight>::PieceBase;

 private:
   std::vector<Square> moves_(const Position& pos) const;
};

class Pawn : public PieceBase<Pawn>
{
   friend class PieceBase<Pawn>;

 public:
   using PieceBase<Pawn>::PieceBase;

 private:
   std::string notation_() const { return ""; }
   std::vector<Square> moves_(const Position& pos) const;
};


///////////////////

using Piece = std::variant<King, Queen, Rook, Bishop, Knight, Pawn>;


inline bool operator==(const Piece& a, const std::optional<Piece>& b)
{
   return b.has_value() && a == *b;
}

inline bool operator==(const std::optional<Piece>& a, const Piece& b)
{
   return b == a;
}

inline bool hasColor(const Piece& piece, Color color)
{
   return std::visit([&color](const auto& elem) { return elem.color() == color; }, piece);
}

inline std::string notation(const Piece& piece)
{
   return std::visit([](const auto& elem) { return elem.notation(); }, piece);
}

inline bool isOnSquare(const Piece& piece, Square loc)
{
   return std::visit([&loc](const auto& elem) { return elem.location() == loc; }, piece);
}
