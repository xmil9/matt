//
// Mar-2021, Michael Lindner
// MIT license
//
#include "move_tests.h"
#include "move.h"
#include "test_util.h"


namespace
{
///////////////////

void testMoveDefaultCtor()
{
   {
      const std::string caseLabel = "Move default ctor";

      const Move m;
      VERIFY(m.piece() == Piece(), caseLabel);
      VERIFY(m.from() == Square(), caseLabel);
      VERIFY(m.to() == Square(), caseLabel);
      VERIFY(m.notate() == "", caseLabel);
   }
}


void testMoveFullCtor()
{
   {
      const std::string caseLabel = "Move full ctor";

      const Piece piece = makePiece("Bwe5");
      const Square to = makeSquare("c3");
      const std::string notation{"Bc3"};
      const Move m{piece, to, notation};
      VERIFY(m.piece() == piece, caseLabel);
      VERIFY(m.from() == makeSquare("e5"), caseLabel);
      VERIFY(m.to() == to, caseLabel);
      VERIFY(m.notate() == notation, caseLabel);
   }
}


void testMovePieceAccessor()
{
   // Skip - It's trivial.
}


void testMoveFromAccessor()
{
   {
      const std::string caseLabel = "Move::from";

      const Move m{makePiece("Bwh4"), makeSquare("e7"), "Be7"};
      VERIFY(m.from() == makeSquare("h4"), caseLabel);
   }
}


void testMoveToAccessor()
{
   // Skip - It's trivial.
}


void testMoveNotate()
{
   // Skip - It's trivial.
}


void testMoveMovedPiece()
{
   {
      const std::string caseLabel = "Move::movedPiece";

      const Move m{makePiece("Bwh4"), makeSquare("e7"), "Be7"};
      VERIFY(m.movedPiece() == makePiece("Bwe7"), caseLabel);
   }
}


void testMoveSwap()
{
   {
      const std::string caseLabel = "swap Move";

      Move a{makePiece("Bwh4"), makeSquare("e7"), "Be7"};
      Move b{makePiece("bb7"), makeSquare("b6"), "b6"};
      swap(a, b);
      VERIFY(a.piece() == makePiece("bb7"), caseLabel);
      VERIFY(a.to() == makeSquare("b6"), caseLabel);
      VERIFY(a.notate() == "b6", caseLabel);
      VERIFY(b.piece() == makePiece("Bwh4"), caseLabel);
      VERIFY(b.to() == makeSquare("e7"), caseLabel);
      VERIFY(b.notate() == "Be7", caseLabel);
   }
}

} // namespace


///////////////////

void testMove()
{
   testMoveDefaultCtor();
   testMoveFullCtor();
   testMovePieceAccessor();
   testMoveFromAccessor();
   testMoveToAccessor();
   testMoveNotate();
   testMoveMovedPiece();
   testMoveSwap();
}
