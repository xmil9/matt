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

      const Piece piece("Bwe5");
      const Square to("c3");
      const std::string notation{"Bc3"};
      const Move m{piece, to, notation};
      VERIFY(m.piece() == piece, caseLabel);
      VERIFY(m.from() == "e5"_sq, caseLabel);
      VERIFY(m.to() == to, caseLabel);
      VERIFY(m.notate() == notation, caseLabel);
   }
}


void testMoveCtorWithPosition()
{
   {
      const std::string caseLabel = "Move ctor with position";

      const Piece piece("Bwe5");
      const Square to("c3");
      const Position pos{std::vector<Piece>{piece}};
      const Move m{piece, to, pos};
      VERIFY(m.piece() == piece, caseLabel);
      VERIFY(m.from() == "e5"_sq, caseLabel);
      VERIFY(m.to() == to, caseLabel);
      VERIFY(m.notate() == "Bc3", caseLabel);
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

      const Move m{Piece("Bwh4"), "e7"_sq, "Be7"};
      VERIFY(m.from() == "h4"_sq, caseLabel);
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

      const Move m{Piece("Bwh4"), "e7"_sq, "Be7"};
      VERIFY(m.movedPiece() == Piece("Bwe7"), caseLabel);
   }
}


void testMoveSwap()
{
   {
      const std::string caseLabel = "swap Move";

      Move a{Piece("Bwh4"), "e7"_sq, "Be7"};
      Move b{Piece("bb7"), "b6"_sq, "b6"};
      swap(a, b);
      VERIFY(a.piece() == Piece("bb7"), caseLabel);
      VERIFY(a.to() == "b6"_sq, caseLabel);
      VERIFY(a.notate() == "b6", caseLabel);
      VERIFY(b.piece() == Piece("Bwh4"), caseLabel);
      VERIFY(b.to() == "e7"_sq, caseLabel);
      VERIFY(b.notate() == "Be7", caseLabel);
   }
}


void testMoveEquality()
{
   {
      const std::string caseLabel = "Move equality for equal moves";

      const Move a{Piece("Bwh4"), "e7"_sq, "Be7"};
      const Move b{Piece("Bwh4"), "e7"_sq, "Be7"};
      VERIFY(a == b, caseLabel);
   }
   {
      const std::string caseLabel = "Move equality for unequal moves";

      const Move a{Piece("Rwh4"), "e4"_sq, "Re4"};
      const Move b{Piece("Rwh4"), "h1"_sq, "Rh1"};
      const Move c{Piece("Qwh4"), "e4"_sq, "Qe4"};
      VERIFY(!(a == b), caseLabel);
      VERIFY(!(a == c), caseLabel);
   }
}


void testMoveInequality()
{
   {
      const std::string caseLabel = "Move inequality for equal moves";

      const Move a{Piece("Bwh4"), "e7"_sq, "Be7"};
      const Move b{Piece("Bwh4"), "e7"_sq, "Be7"};
      VERIFY(!(a != b), caseLabel);
   }
   {
      const std::string caseLabel = "Move inequality for unequal moves";

      const Move a{Piece("Rwh4"), "e4"_sq, "Re4"};
      const Move b{Piece("Rwh4"), "h1"_sq, "Rh1"};
      const Move c{Piece("Qwh4"), "e4"_sq, "Qe4"};
      VERIFY(a != b, caseLabel);
      VERIFY(a != c, caseLabel);
   }
}


void testNotateMove()
{
   {
      const std::string caseLabel = "notateMove for non-capturing moves";

      VERIFY(notateMove(Piece("Qbd8"), "d5"_sq, Position("Qbd8")) == "Qd5", caseLabel);
      VERIFY(notateMove(Piece("Kwe1"), "d2"_sq, Position("Kwe1")) == "Kd2", caseLabel);
      VERIFY(notateMove(Piece("bf5"), "f4"_sq, Position("bf5")) == "f4", caseLabel);
   }
   {
      const std::string caseLabel = "notateMove for capturing moves";

      VERIFY(notateMove(Piece("Qbd8"), "d5"_sq, Position("Qbd8 Bwd5")) == "Qxd5",
             caseLabel);
      VERIFY(notateMove(Piece("Kwe1"), "d2"_sq, Position("Kwe1 bd2")) == "Kxd2",
             caseLabel);
      VERIFY(notateMove(Piece("bf5"), "e4"_sq, Position("bf5 Nwe4")) == "fxe4",
             caseLabel);
   }
}

} // namespace


///////////////////

void testMove()
{
   testMoveDefaultCtor();
   testMoveFullCtor();
   testMoveCtorWithPosition();
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
