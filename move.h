//
// Feb-2021, Michael Lindner
// MIT license
//
#pragma once
#include "piece.h"
#include "square.h"
#include <string>


///////////////////

class Move
{
public:
   Move() = default;
   Move(const Piece& piece, Square to, const std::string& notation);

private:
   Piece m_piece;
   Square m_to;
   std::string m_notation;
};


inline Move::Move(const Piece& piece, Square to, const std::string& notation)
   : m_piece{piece}, m_to{to}, m_notation{notation}
{
}
