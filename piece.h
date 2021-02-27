//
// Feb-2021, Michael Lindner
// MIT license
//
#pragma once
#include "square.h"
#include <variant>
#include <vector>

struct Position;


///////////////////

template <typename DerivedPiece> struct PieceBase
{
   Square loc;
};

struct King : public PieceBase<King>
{
   std::vector<Square> moves(const Position& pos) const;
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

inline bool isOnSquare(const Piece& piece, Square loc)
{
   return std::visit([&loc](const auto& elem) { return elem.loc == loc; }, piece);
}
