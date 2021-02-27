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

template <typename DerivedPiece> class PieceBase
{
 public:
   Square location() const { return m_loc; }
   bool isLegalMove(const Position& pos, Square loc) const;
   bool isLegalMove(const Position& pos, std::optional<Square> loc) const;

 private:
   const DerivedPiece& derived() const { return static_cast<const DerivedPiece&>(*this); }
   DerivedPiece& derived() { return static_cast<DerivedPiece&>(*this); }

private:
   Square m_loc;
};


template <typename DerivedPiece>
bool PieceBase<DerivedPiece>::isLegalMove(const Position& pos, Square loc) const
{
   return derived().isLegalMove_(pos, loc);
}


template <typename DerivedPiece>
bool PieceBase<DerivedPiece>::isLegalMove(const Position& pos,
                                          std::optional<Square> loc) const
{
   if (loc.has_value())
      return isLegalMove(pos, *loc);
   return false;
}


template <typename DerivedPiece>
bool operator==(const DerivedPiece& a, const DerivedPiece& b)
{
   return a.location() == b.location();
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
   std::vector<Square> moves(const Position& pos) const;

 private:
   bool isLegalMove_(const Position& pos, Square loc) const;
};

struct Queen : public PieceBase<Queen>
{
   std::vector<Square> moves(const Position& pos) const;
};

struct Rook : public PieceBase<Rook>
{
   std::vector<Square> moves(const Position& pos) const;
};

struct Bishop : public PieceBase<Bishop>
{
   std::vector<Square> moves(const Position& pos) const;
};

struct Knight : public PieceBase<Knight>
{
   std::vector<Square> moves(const Position& pos) const;
};

struct Pawn : public PieceBase<Pawn>
{
   std::vector<Square> moves(const Position& pos) const;
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

inline bool isOnSquare(const Piece& piece, Square loc)
{
   return std::visit([&loc](const auto& elem) { return elem.location() == loc; }, piece);
}
