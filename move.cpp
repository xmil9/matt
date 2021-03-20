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

   std::string notation = piece.notate();

   const bool isCapture = pos.isOccupiedBy(to, !piece.color());
   if (isCapture)
   {
      // For capturing pawn moves the departing file is notated.
      if (piece.isFigure(Figure::Pawn))
         notation += piece.location().file();
      notation += "x";
   }
   
   notation += to.notate();
   return notation;
}
