//
// Mar-2021, Michael Lindner
// MIT license
//
#include "position_tests.h"
#include "move.h"
#include "position.h"
#include "square.h"
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
   {
      const std::string caseLabel =
         "Score for king is larger than all other pieces combined";

      VERIFY(
         std::abs(Position("Kwe1").score()) >
            std::abs(
               Position(
                  "Rwa1 Nwb1 Bwc1 Qwd1 Bwf1 Nwg1 Rwh1 wa2 wb2 wc2 wd2 we2 wf2 wg2 wh2")
                  .score()),
         caseLabel);
      VERIFY(
         std::abs(Position("Kwe8").score()) >
            std::abs(
               Position(
                  "Rwa8 Nwb8 Bwc8 Qwd8 Bwf8 Nwg8 Rwh8 ba7 bb7 bc7 bd7 be7 bf7 bg7 bh7")
                  .score()),
         caseLabel);
   }
   {
      const std::string caseLabel = "Ordering of piece values";

      VERIFY(std::abs(Position("Qwd1").score()) > std::abs(Position("Rwa1").score()),
             caseLabel);
      VERIFY(std::abs(Position("Rwa1").score()) > std::abs(Position("Bwc1").score()),
             caseLabel);
      VERIFY(std::abs(Position("Bwc1").score()) >= std::abs(Position("Nwb1").score()),
             caseLabel);
      VERIFY(std::abs(Position("Nwb1").score()) > std::abs(Position("wa2").score()),
             caseLabel);
      VERIFY(std::abs(Position("Qbd8").score()) > std::abs(Position("Rba8").score()),
             caseLabel);
      VERIFY(std::abs(Position("Rba8").score()) > std::abs(Position("Bbc8").score()),
             caseLabel);
      VERIFY(std::abs(Position("Bbc8").score()) >= std::abs(Position("Nbb8").score()),
             caseLabel);
      VERIFY(std::abs(Position("Nbb8").score()) > std::abs(Position("ba7").score()),
             caseLabel);
   }
   {
      const std::string caseLabel = "White pieces are positive";

      VERIFY(Position("Qwd1").score() > 0.f, caseLabel);
      VERIFY(Position("Rwa1").score() > 0.f, caseLabel);
      VERIFY(Position("Bwc1").score() > 0.f, caseLabel);
      VERIFY(Position("Nwb1").score() > 0.f, caseLabel);
      VERIFY(Position("wa2").score() > 0.f, caseLabel);
      VERIFY(Position("Qbd8").score() < 0.f, caseLabel);
      VERIFY(Position("Rba8").score() < 0.f, caseLabel);
      VERIFY(Position("Bbc8").score() < 0.f, caseLabel);
      VERIFY(Position("Nbb8").score() < 0.f, caseLabel);
      VERIFY(Position("ba7").score() < 0.f, caseLabel);
   }
   {
      const std::string caseLabel = "Score is zero for starting position";

      VERIFY(StartPos.score() == 0.f, caseLabel);
   }
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


void testPositionNotate()
{
   {
      const std::string caseLabel = "Position::notate";

      VERIFY(Position("Kwe1 wg2 Kbe8 Bbf8").notate() == "Kwe1 wg2 Kbe8 Bbf8", caseLabel);
      VERIFY(Position("Qbf3").notate() == "Qbf3", caseLabel);
      VERIFY(Position().notate() == "", caseLabel);
   }
}


void testPositionRecordedMoves()
{
   {
      const std::string caseLabel = "Position::moves before any moves";

      const Position pos{"Kwe1 Kbe8"};
      VERIFY(pos.recordedMoves().empty(), caseLabel);
   }
   {
      const std::string caseLabel = "Position::moves after a move";

      const Position pos{"Kwe1 Kbe8"};
      const Position next = pos.makeMove(Move{*pos["e1"_sq], "e2"_sq, pos});
      VERIFY(next.recordedMoves() == "Ke2", caseLabel);
   }
}


void testPositionInitialPosition()
{
   {
      const std::string caseLabel = "Position::initialPosition";

      const std::string initialPos = "Kwe1 Kbe8";
      const Position pos{initialPos};
      VERIFY(pos.initialPosition() == initialPos, caseLabel);
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


void testPositionLess()
{
   {
      const std::string caseLabel = "Position less-than operator";

      const Position a{"Kwe1"};
      const Position b{"Kbe8"};

      VERIFY(b < a, caseLabel);
      VERIFY(!(a < b), caseLabel);
      VERIFY(!(a < a), caseLabel);
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
   testPositionMakeMove();
   testPositionNotate();
   testPositionInitialPosition();
   testPositionRecordedMoves();
   testPositionEquality();
   testPositionInequality();
   testPositionLess();
}
