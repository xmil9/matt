//
// Mar-2021, Michael Lindner
// MIT license
//
#include "position_tests.h"
#include "move.h"
#include "position.h"
#include "test_util.h"
#include <vector>


namespace
{
///////////////////

void testPositionDefaultCtor()
{
   {
      const std::string caseLabel = "Position default ctor";

      const Position pos;
      VERIFY(pos.score() == 0.f, caseLabel);
      VERIFY(pos.notate() == "", caseLabel);
      VERIFY(pos.pieces(Color::Black).empty(), caseLabel);
      VERIFY(pos.pieces(Color::White).empty(), caseLabel);
   }
}


void testPositionPiecesCtor()
{
   {
      const std::string caseLabel = "Position pieces ctor";

      const std::vector<Piece> pieces{Piece{"Kwe1"}, Piece{"Kbe8"}};
      const Position pos{pieces};
      VERIFY(pos.pieces(Color::Black).size() == 1, caseLabel);
      VERIFY(pos.pieces(Color::White).size() == 1, caseLabel);
      VERIFY(pos[Square("e1")] == Piece{"Kwe1"}, caseLabel);
      VERIFY(pos[Square("e8")] == Piece{"Kbe8"}, caseLabel);
   }
}


void testPositionNotationCtor()
{
   {
      const std::string caseLabel = "Position notation ctor";

      const Position pos{"Kwe1 Kbe8"};
      VERIFY(pos.pieces(Color::Black).size() == 1, caseLabel);
      VERIFY(pos.pieces(Color::White).size() == 1, caseLabel);
      VERIFY(pos[Square("e1")] == Piece{"Kwe1"}, caseLabel);
      VERIFY(pos[Square("e8")] == Piece{"Kbe8"}, caseLabel);
   }
}


void testPositionScore()
{
   // todo
}


void testPositionIsOccupiedBy()
{
   {
      const std::string caseLabel = "Position::isOccupiedBy for occupied square";

      const Position pos{"Kwe1 Kbe8"};
      VERIFY(pos.isOccupiedBy(Square("e1"), Color::White), caseLabel);
      VERIFY(!pos.isOccupiedBy(Square("e1"), Color::Black), caseLabel);
      VERIFY(pos.isOccupiedBy(Square("e8"), Color::Black), caseLabel);
      VERIFY(!pos.isOccupiedBy(Square("e8"), Color::White), caseLabel);
   }
   {
      const std::string caseLabel = "Position::isOccupiedBy for unoccupied square";

      const Position pos{"Kwe1 Kbe8"};
      VERIFY(!pos.isOccupiedBy(Square("a1"), Color::White), caseLabel);
      VERIFY(!pos.isOccupiedBy(Square("g6"), Color::Black), caseLabel);
   }
}


void testPositionIndexOperator()
{
   {
      const std::string caseLabel = "Position::operator[] for occupied square";

      const Position pos{"Kwe1 Kbe8"};
      VERIFY(pos[Square("e1")] == Piece{"Kwe1"}, caseLabel);
      VERIFY(pos[Square("e8")] == Piece{"Kbe8"}, caseLabel);
   }
   {
      const std::string caseLabel = "Position::operator[] for unoccupied square";

      const Position pos{"Kwe1 Kbe8"};
      VERIFY(pos[Square("a1")] == std::nullopt, caseLabel);
      VERIFY(pos[Square("g5")] == std::nullopt, caseLabel);
   }
}


void testPositionPieces()
{
   {
      const std::string caseLabel = "Position::pieces";

      const Position pos{"Kwe1 wg2 Kbe8 Bbf8"};

      const auto black = pos.pieces(Color::Black);
      VERIFY(black.size() == 2, caseLabel);
      VERIFY(std::find(begin(black), end(black), Piece("Bbf8")) != end(black), caseLabel);
      VERIFY(std::find(begin(black), end(black), Piece("Kbe8")) != end(black), caseLabel);

      const auto white = pos.pieces(Color::White);
      VERIFY(white.size() == 2, caseLabel);
      VERIFY(std::find(begin(white), end(white), Piece("Kwe1")) != end(white), caseLabel);
      VERIFY(std::find(begin(white), end(white), Piece("wg2")) != end(white), caseLabel);
   }
   {
      const std::string caseLabel = "Position::pieces for one piece";

      const Position pos{"Kwe1 Kbe8"};

      const auto black = pos.pieces(Color::Black);
      VERIFY(black.size() == 1, caseLabel);
      VERIFY(std::find(begin(black), end(black), Piece("Kbe8")) != end(black), caseLabel);

      const auto white = pos.pieces(Color::White);
      VERIFY(white.size() == 1, caseLabel);
      VERIFY(std::find(begin(white), end(white), Piece("Kwe1")) != end(white), caseLabel);
   }
   {
      const std::string caseLabel = "Position::pieces for no piece";

      const Position pos;
      VERIFY(pos.pieces(Color::Black).empty(), caseLabel);
      VERIFY(pos.pieces(Color::White).empty(), caseLabel);
   }
}


void testPositionNotate()
{
   {
      const std::string caseLabel = "Position::notate";

      VERIFY(Position("Kwe1 wg2 Kbe8 Bbf8").notate() == "Kwe1 wg2 Kbe8 Bbf8", caseLabel);
      VERIFY(Position("Qbf3").notate() == "Qbf3", caseLabel);
      VERIFY(Position().notate() == "", caseLabel);
   }
}


void testPositionMakeMove()
{
   {
      const std::string caseLabel = "Position::makeMove for non-capturing move";

      const Position pos("Kwe1 wg2 Kbe8 Bbf8");
      VERIFY(pos.makeMove(Move(Piece("wg2"), Square("g3"), pos)) ==
                Position("Kwe1 wg3 Kbe8 Bbf8"),
             caseLabel);
      VERIFY(pos.makeMove(Move(Piece("Kbe8"), Square("d7"), pos)) ==
                Position("Kwe1 wg2 Kbd7 Bbf8"),
             caseLabel);
   }
   {
      const std::string caseLabel = "Position::makeMove for capturing move";

      const Position pos("Kwe1 wg2 Kbe8 Bbf3");
      VERIFY(pos.makeMove(Move(Piece("wg2"), Square("f3"), pos)) ==
                Position("Kwe1 wf3 Kbe8"),
             caseLabel);
      VERIFY(pos.makeMove(Move(Piece("Bbf3"), Square("g2"), pos)) ==
                Position("Kwe1 Kbe8 Bbg2"),
             caseLabel);
   }
}


void testPositionEquality()
{
   {
      const std::string caseLabel = "Position equality for equal positions";

      VERIFY(Position("Kwe1 wg2 Kbe8 Bbf8") == Position("Kwe1 wg2 Kbe8 Bbf8"), caseLabel);
      VERIFY(Position("Bbf8 Kwe1 Kbe8 wg2") == Position("Kwe1 wg2 Kbe8 Bbf8"), caseLabel);
   }
   {
      const std::string caseLabel = "Position equality for unequal positions";

      // Other figure.
      VERIFY(!(Position("Kwe1 wg2 Kbe8 Rbf8") == Position("Kwe1 wg2 Kbe8 Bbf8")),
             caseLabel);
      // Other color.
      VERIFY(!(Position("Kwe1 wg2 Kbe8 Bwf8") == Position("Kwe1 wg2 Kbe8 Bbf8")),
             caseLabel);
      // Other coordinate.
      VERIFY(!(Position("Kwe2 wg2 Kbe8 Bbf8") == Position("Kwe1 wg2 Kbe8 Bbf8")),
             caseLabel);
      // Different numer of pieces.
      VERIFY(!(Position("Kwe2 wg2 Bbf8") == Position("Kwe1 wg2 Kbe8 Bbf8")), caseLabel);
   }
}


void testPositionInequality()
{
   {
      const std::string caseLabel = "Position inequality for equal positions";

      VERIFY(!(Position("Kwe1 wg2 Kbe8 Bbf8") != Position("Kwe1 wg2 Kbe8 Bbf8")),
             caseLabel);
      VERIFY(!(Position("Bbf8 Kwe1 Kbe8 wg2") != Position("Kwe1 wg2 Kbe8 Bbf8")),
             caseLabel);
   }
   {
      const std::string caseLabel = "Position inequality for unequal positions";

      // Other figure.
      VERIFY(Position("Kwe1 wg2 Kbe8 Rbf8") != Position("Kwe1 wg2 Kbe8 Bbf8"), caseLabel);
      // Other color.
      VERIFY(Position("Kwe1 wg2 Kbe8 Bwf8") != Position("Kwe1 wg2 Kbe8 Bbf8"), caseLabel);
      // Other coordinate.
      VERIFY(Position("Kwe2 wg2 Kbe8 Bbf8") != Position("Kwe1 wg2 Kbe8 Bbf8"), caseLabel);
      // Different numer of pieces.
      VERIFY(Position("Kwe2 wg2 Bbf8") != Position("Kwe1 wg2 Kbe8 Bbf8"), caseLabel);
   }
}

} // namespace


///////////////////

void testPosition()
{
   testPositionDefaultCtor();
   testPositionPiecesCtor();
   testPositionNotationCtor();
   testPositionScore();
   testPositionIsOccupiedBy();
   testPositionIndexOperator();
   testPositionPieces();
   testPositionNotate();
   testPositionMakeMove();
   testPositionEquality();
   testPositionInequality();
}
