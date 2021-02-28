//
// Feb-2021, Michael Lindner
// MIT license
//
#include "notation.h"
#include "move.h"


///////////////////

std::string noteMove(const Piece& piece, Square to, const Position& /*pos*/)
{
   // todo - check for ambiguities
   return notation(piece) + to.notation();
}


std::string noteCapture(const Piece& piece, Square to, const Position& /*pos*/)
{
   // todo - check for ambiguities
   return notation(piece) + std::string("x") + to.notation();
}


///////////////////

Record::Record(std::string pos)
   : m_initialPos{std::move(pos)}
{
}
