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

      const std::vector<Piece> pieces{"Kwe1"_pc, "Kbe8"_pc};
      const Position pos{pieces};
      VERIFY(pos.pieces(Color::Black).size() == 1, caseLabel);
      VERIFY(pos.pieces(Color::White).size() == 1, caseLabel);
      VERIFY(pos["e1"_sq] == "Kwe1"_pc, caseLabel);
      VERIFY(pos["e8"_sq] == "Kbe8"_pc, caseLabel);
   }
}


void testPositionNotationCtor()
{
   {
      const std::string caseLabel = "Position notation ctor";

      const Position pos{"Kwe1 Kbe8"};
      VERIFY(pos.pieces(Color::Black).size() == 1, caseLabel);
      VERIFY(pos.pieces(Color::White).size() == 1, caseLabel);
      VERIFY(pos[Square("e1")] == "Kwe1"_pc, caseLabel);
      VERIFY(pos[Square("e8")] == "Kbe8"_pc, caseLabel);
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
      VERIFY(pos.isOccupiedBy("e1"_sq, Color::White), caseLabel);
      VERIFY(!pos.isOccupiedBy("e1"_sq, Color::Black), caseLabel);
      VERIFY(pos.isOccupiedBy("e8"_sq, Color::Black), caseLabel);
      VERIFY(!pos.isOccupiedBy("e8"_sq, Color::White), caseLabel);
   }
   {
      const std::string caseLabel = "Position::isOccupiedBy for unoccupied square";

      const Position pos{"Kwe1 Kbe8"};
      VERIFY(!pos.isOccupiedBy("a1"_sq, Color::White), caseLabel);
      VERIFY(!pos.isOccupiedBy("g6"_sq, Color::Black), caseLabel);
   }
}


void testPositionIndexOperator()
{
   {
      const std::string caseLabel = "Position::operator[] for occupied square";

      const Position pos{"Kwe1 Kbe8"};
      VERIFY(pos["e1"_sq] == "Kwe1"_pc, caseLabel);
      VERIFY(pos["e8"_sq] == "Kbe8"_pc, caseLabel);
   }
   {
      const std::string caseLabel = "Position::operator[] for unoccupied square";

      const Position pos{"Kwe1 Kbe8"};
      VERIFY(pos["a1"_sq] == std::nullopt, caseLabel);
      VERIFY(pos["g5"_sq] == std::nullopt, caseLabel);
   }
}


void testPositionPieces()
{
   {
      const std::string caseLabel = "Position::pieces";

      const Position pos{"Kwe1 wg2 Kbe8 Bbf8"};

      const auto black = pos.pieces(Color::Black);
      VERIFY(black.size() == 2, caseLabel);
      VERIFY(std::find(begin(black), end(black), "Bbf8"_pc) != end(black), caseLabel);
      VERIFY(std::find(begin(black), end(black), "Kbe8"_pc) != end(black), caseLabel);

      const auto white = pos.pieces(Color::White);
      VERIFY(white.size() == 2, caseLabel);
      VERIFY(std::find(begin(white), end(white), "Kwe1"_pc) != end(white), caseLabel);
      VERIFY(std::find(begin(white), end(white), "wg2"_pc) != end(white), caseLabel);
   }
   {
      const std::string caseLabel = "Position::pieces for one piece";

      const Position pos{"Kwe1 Kbe8"};

      const auto black = pos.pieces(Color::Black);
      VERIFY(black.size() == 1, caseLabel);
      VERIFY(std::find(begin(black), end(black), "Kbe8"_pc) != end(black), caseLabel);

      const auto white = pos.pieces(Color::White);
      VERIFY(white.size() == 1, caseLabel);
      VERIFY(std::find(begin(white), end(white), "Kwe1"_pc) != end(white), caseLabel);
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
      VERIFY(pos.makeMove(Move("wg2"_pc, "g3"_sq, pos)) == Position("Kwe1 wg3 Kbe8 Bbf8"),
             caseLabel);
      VERIFY(pos.makeMove(Move("Kbe8"_pc, "d7"_sq, pos)) ==
                Position("Kwe1 wg2 Kbd7 Bbf8"),
             caseLabel);
   }
   {
      const std::string caseLabel = "Position::makeMove for capturing move";

      const Position pos("Kwe1 wg2 Kbe8 Bbf3");
      VERIFY(pos.makeMove(Move("wg2"_pc, "f3"_sq, pos)) == Position("Kwe1 wf3 Kbe8"),
             caseLabel);
      VERIFY(pos.makeMove(Move("Bbf3"_pc, "g2"_sq, pos)) == Position("Kwe1 Kbe8 Bbg2"),
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
