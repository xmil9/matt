//
// Feb-2021, Michael Lindner
// MIT license
//
#include "matt.h"
#include "position.h"


Position makeMove(const Position& pos, Color side)
{
   const auto pieces = pos.pieces(side);
   for (const auto& piece : pieces)
   {
      const auto positions = piece.nextPositions(pos);
   }
   return pos;
}


Position makeMove(const Position& pos, const Piece& piece)
{
   // just depth one for now
   const auto positions = piece.nextPositions(pos);
   // find best and return
   assert(false && "todo");
   return {};
}
