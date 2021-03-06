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
   return piece.notation() + to.notation();
}


std::string noteCapture(const Piece& piece, Square to, const Position& /*pos*/)
{
   // todo - check for ambiguities
   return piece.notation() + std::string("x") + to.notation();
}


///////////////////

std::vector<Piece> parsePositionNotation(const std::string& notation)
{
   notation;
   assert(false && "todo");
   return {};
}


///////////////////

Record::Record(std::string pos)
   : m_initialPos{std::move(pos)}
{
}
