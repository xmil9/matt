//
// Mar-2021, Michael Lindner
// MIT license
//
#include "move_tests.h"
#include "move.h"
#include "position.h"
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
      const Square to("c3");
      const std::string notation{"Bc3"};
      const Move m{piece, to, notation};
      VERIFY(m.piece() == piece, caseLabel);
      VERIFY(m.from() == Square("e5"), caseLabel);
      VERIFY(m.to() == to, caseLabel);
      VERIFY(m.notate() == notation, caseLabel);
   }
}


void testMovePieceAccessor()
{
   // Trivial - skip.
}


void testMoveFromAccessor()
{
   {
      const std::string caseLabel = "Move::from";

      const Move m{makePiece("Bwh4"), Square("e7"), "Be7"};
      VERIFY(m.from() == Square("h4"), caseLabel);
   }
}


void testMoveToAccessor()
{
   // Trivial - skip.
}


void testMoveNotate()
{
   // Trivial - skip.
}


void testMoveMovedPiece()
{
   {
      const std::string caseLabel = "Move::movedPiece";

      const Move m{makePiece("Bwh4"), Square("e7"), "Be7"};
      VERIFY(m.movedPiece() == makePiece("Bwe7"), caseLabel);
   }
}


void testMoveSwap()
{
   {
      const std::string caseLabel = "swap Move";

      Move a{makePiece("Bwh4"), Square("e7"), "Be7"};
      Move b{makePiece("bb7"), Square("b6"), "b6"};
      swap(a, b);
      VERIFY(a.piece() == makePiece("bb7"), caseLabel);
      VERIFY(a.to() == Square("b6"), caseLabel);
      VERIFY(a.notate() == "b6", caseLabel);
      VERIFY(b.piece() == makePiece("Bwh4"), caseLabel);
      VERIFY(b.to() == Square("e7"), caseLabel);
      VERIFY(b.notate() == "Be7", caseLabel);
   }
}


void testMoveEquality()
{
   {
      const std::string caseLabel = "Move equality for equal moves";

      const Move a{makePiece("Bwh4"), Square("e7"), "Be7"};
      const Move b{makePiece("Bwh4"), Square("e7"), "Be7"};
      VERIFY(a == b, caseLabel);
   }
   {
      const std::string caseLabel = "Move equality for unequal moves";

      const Move a{makePiece("Rwh4"), Square("e4"), "Re4"};
      const Move b{makePiece("Rwh4"), Square("h1"), "Rh1"};
      const Move c{makePiece("Qwh4"), Square("e4"), "Qe4"};
      VERIFY(!(a == b), caseLabel);
      VERIFY(!(a == c), caseLabel);
   }
}


void testMoveInequality()
{
   {
      const std::string caseLabel = "Move inequality for equal moves";

      const Move a{makePiece("Bwh4"), Square("e7"), "Be7"};
      const Move b{makePiece("Bwh4"), Square("e7"), "Be7"};
      VERIFY(!(a != b), caseLabel);
   }
   {
      const std::string caseLabel = "Move inequality for unequal moves";

      const Move a{makePiece("Rwh4"), Square("e4"), "Re4"};
      const Move b{makePiece("Rwh4"), Square("h1"), "Rh1"};
      const Move c{makePiece("Qwh4"), Square("e4"), "Qe4"};
      VERIFY(a != b, caseLabel);
      VERIFY(a != c, caseLabel);
   }
}


void testNotateMove()
{
   {
      const std::string caseLabel = "notateMove for non-capturing moves";

      VERIFY(notateMove(makePiece("Qbd8"), Square("d5"), makePosition("Qbd8")) == "Qd5",
             caseLabel);
      VERIFY(notateMove(makePiece("Kwe1"), Square("d2"), makePosition("Kwe1")) == "Kd2",
             caseLabel);
      VERIFY(notateMove(makePiece("bf5"), Square("f4"), makePosition("bf5")) == "f4",
             caseLabel);
   }
   {
      const std::string caseLabel = "notateMove for capturing moves";

      VERIFY(notateMove(makePiece("Qbd8"), Square("d5"), makePosition("Qbd8 Bwd5")) ==
                "Qxd5",
             caseLabel);
      VERIFY(notateMove(makePiece("Kwe1"), Square("d2"), makePosition("Kwe1 bd2")) ==
                "Kxd2",
             caseLabel);
      VERIFY(notateMove(makePiece("bf5"), Square("e4"), makePosition("bf5 Nwe4")) ==
                "fxe4",
             caseLabel);
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
   testMoveEquality();
   testMoveInequality();
   testNotateMove();
}
