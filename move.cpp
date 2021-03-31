//
// Mar-2021, Michael Lindner
// MIT license
//
#include "move.h"
#include "position.h"


///////////////////

Move::Move(const Piece& piece, Square to, const Position& pos)
   : Move{piece, to, notateMove(piece, to, pos)}
{
}


std::string notateMove(const Piece& piece, Square to, const Position& pos)
{
   // todo - check for ambiguities
   pos;

   std::string notation = piece.notate();

   const bool isCapture = pos.isOccupiedBy(to, !piece.color());
   if (isCapture)
   {
      // For capturing pawn moves the departing file is notated.
      if (piece.figure() == Figure::Pawn)
         notation += piece.coord().file();
      notation += "x";
   }
   
   notation += to.notate();
   return notation;
}
