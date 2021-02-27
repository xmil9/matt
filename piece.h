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
   // Common interface for all pieces.
   Square location() const { return m_loc; }
   std::vector<Square> moves(const Position& pos) const { return derived().moves_(pos); }

 private:
   const DerivedPiece& derived() const { return static_cast<const DerivedPiece&>(*this); }
   DerivedPiece& derived() { return static_cast<DerivedPiece&>(*this); }

 private:
   Square m_loc;
};


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

 private:
   std::vector<Square> moves_(const Position& pos) const;
   // Checks if piece can occupy the location regardless of whether it can get there.
   bool canOccupy_(const Position& pos, Square loc) const;
   bool canOccupy_(const Position& pos, std::optional<Square> loc) const;
};

class Queen : public PieceBase<Queen>
{
   friend class PieceBase<Queen>;

 private:
   std::vector<Square> moves_(const Position& pos) const;
};

class Rook : public PieceBase<Rook>
{
   friend class PieceBase<Rook>;

 private:
   std::vector<Square> moves_(const Position& pos) const;
};

class Bishop : public PieceBase<Bishop>
{
   friend class PieceBase<Bishop>;

 private:
   std::vector<Square> moves_(const Position& pos) const;
};

class Knight : public PieceBase<Knight>
{
   friend class PieceBase<Knight>;

 private:
   std::vector<Square> moves_(const Position& pos) const;
};

class Pawn : public PieceBase<Pawn>
{
   friend class PieceBase<Pawn>;

 private:
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

inline bool isOnSquare(const Piece& piece, Square loc)
{
   return std::visit([&loc](const auto& elem) { return elem.location() == loc; }, piece);
}
