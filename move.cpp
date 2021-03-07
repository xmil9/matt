//
// Mar-2021, Michael Lindner
// MIT license
//
#include "move.h"
#include "position.h"


///////////////////

std::string notateMove(const Piece& piece, Square to, const Position& pos)
{
   // todo - check for ambiguities
   pos;

   const bool isCapture = pos.isOccupiedBy(to, !piece.color());

   std::string notation = piece.notate();
   if (isCapture)
      notation += "x";
   notation += to.notate();
   return notation;
}
