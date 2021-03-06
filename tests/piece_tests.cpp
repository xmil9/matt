//
// Mar-2021, Michael Lindner
// MIT license
//
#include "piece_tests.h"
#include "move.h"
#include "piece.h"
#include "position.h"
#include "square.h"
#include "test_util.h"
#include <algorithm>
#include <array>
#include <iterator>
#include <vector>


namespace
{
///////////////////

bool verifyNextMoves(const std::vector<Move>& moves, const Piece& piece,
                     const Position& pos,
                     const std::vector<std::string>& expectedLocations)
{
   if (moves.size() != expectedLocations.size())
      return false;

   std::vector<Move> expectedMoves;
   expectedMoves.reserve(expectedLocations.size());
   std::transform(begin(expectedLocations), end(expectedLocations),
                  std::back_inserter(expectedMoves),
                  [&piece, &pos](const std::string& coord) {
                     const Square to{coord};
                     return Move{piece, to, notateMove(piece, to, pos)};
                  });

   const auto endExpected = end(expectedMoves);
   for (const Move& move : moves)
   {
      // Verify move is expected.
      if (std::find(begin(expectedMoves), endExpected, move) == endExpected)
         return false;
      // Verify move is unique.
      if (std::count(begin(moves), end(moves), move) != 1)
         return false;
   }

   return true;
}


bool verifySquares(const std::vector<Square>& squares, const Piece& piece,
                   const Position& pos, const std::vector<std::string>& expectedLocations)
{
   if (squares.size() != expectedLocations.size())
      return false;

   std::vector<Square> expectedSquares;
   expectedSquares.reserve(expectedLocations.size());
   std::transform(begin(expectedLocations), end(expectedLocations),
                  std::back_inserter(expectedSquares),
                  [&piece, &pos](const std::string& coord) { return Square{coord}; });

   const auto endExpected = end(expectedSquares);
   for (const Square& coord : squares)
   {
      // Verify square is expected.
      if (std::find(begin(expectedSquares), endExpected, coord) == endExpected)
         return false;
      // Verify square is unique.
      if (std::count(begin(squares), end(squares), coord) != 1)
         return false;
   }

   return true;
}


///////////////////

void testColorNegation()
{
   {
      const std::string caseLabel = "Color negation";

      VERIFY(!Color::Black == Color::White, caseLabel);
      VERIFY(!Color::White == Color::Black, caseLabel);
   }
}


void testNotateColor()
{
   {
      const std::string caseLabel = "notateColor";

      VERIFY(notateColor(Color::White) == "w", caseLabel);
      VERIFY(notateColor(Color::Black) == "b", caseLabel);
   }
}


void testMakeColor()
{
   {
      const std::string caseLabel = "makeColor from char";

      VERIFY(makeColor('w') == Color::White, caseLabel);
      VERIFY(makeColor('b') == Color::Black, caseLabel);
      // Invalid chars.
      VERIFY(makeColor('a') == Color::White, caseLabel);
      VERIFY(makeColor(' ') == Color::White, caseLabel);
   }
   {
      const std::string caseLabel = "makeColor from string";

      VERIFY(makeColor("w") == Color::White, caseLabel);
      VERIFY(makeColor("b") == Color::Black, caseLabel);
      // At beginning.
      VERIFY(makeColor("we5") == Color::White, caseLabel);
      VERIFY(makeColor("bg8") == Color::Black, caseLabel);
      // Invalid strings.
      VERIFY(makeColor(" ") == Color::White, caseLabel);
      VERIFY(makeColor("aaaa") == Color::White, caseLabel);
      // Empty string.
      VERIFY(makeColor("") == Color::White, caseLabel);
   }
}


void testNotateFigure()
{
   {
      const std::string caseLabel = "notateFigure";

      VERIFY(notateFigure(Figure::King) == "K", caseLabel);
      VERIFY(notateFigure(Figure::Queen) == "Q", caseLabel);
      VERIFY(notateFigure(Figure::Rook) == "R", caseLabel);
      VERIFY(notateFigure(Figure::Bishop) == "B", caseLabel);
      VERIFY(notateFigure(Figure::Knight) == "N", caseLabel);
      VERIFY(notateFigure(Figure::Pawn) == "", caseLabel);
   }
}


void testMakeFigure()
{
   {
      const std::string caseLabel = "makeFigure from char";

      VERIFY(makeFigure('K') == Figure::King, caseLabel);
      VERIFY(makeFigure('Q') == Figure::Queen, caseLabel);
      VERIFY(makeFigure('R') == Figure::Rook, caseLabel);
      VERIFY(makeFigure('B') == Figure::Bishop, caseLabel);
      VERIFY(makeFigure('N') == Figure::Knight, caseLabel);
      // Invalid chars.
      VERIFY(makeFigure('a') == Figure::Pawn, caseLabel);
      VERIFY(makeFigure(' ') == Figure::Pawn, caseLabel);
   }
   {
      const std::string caseLabel = "makeFigure from string";

      VERIFY(makeFigure("K") == Figure::King, caseLabel);
      VERIFY(makeFigure("Q") == Figure::Queen, caseLabel);
      VERIFY(makeFigure("R") == Figure::Rook, caseLabel);
      VERIFY(makeFigure("B") == Figure::Bishop, caseLabel);
      VERIFY(makeFigure("N") == Figure::Knight, caseLabel);
      VERIFY(makeFigure("") == Figure::Pawn, caseLabel);
      // At beginning.
      VERIFY(makeFigure("Kwe5") == Figure::King, caseLabel);
      VERIFY(makeFigure("Rbg8") == Figure::Rook, caseLabel);
      // Invalid strings.
      VERIFY(makeFigure(" ") == Figure::Pawn, caseLabel);
      VERIFY(makeFigure("aaaa") == Figure::Pawn, caseLabel);
      // Empty string.
      VERIFY(makeFigure("") == Figure::Pawn, caseLabel);
   }
}


void testPieceDefaultCtor()
{
   {
      const std::string caseLabel = "Piece default ctor";

      const Piece p;
      VERIFY(p.figure() == Figure::Pawn, caseLabel);
      VERIFY(p.color() == Color::White, caseLabel);
      VERIFY(p.coord() == Square(), caseLabel);
   }
}


void testPieceCtor()
{
   {
      const std::string caseLabel = "Piece ctor";

      const Piece p{Figure::King, Color::Black, Square{"c5"}};
      VERIFY(p.figure() == Figure::King, caseLabel);
      VERIFY(p.color() == Color::Black, caseLabel);
      VERIFY(p.coord() == Square("c5"), caseLabel);
   }
}


void testPieceCtorWithLocationString()
{
   {
      const std::string caseLabel = "Piece ctor with coordinate string";

      const Piece p{Figure::King, Color::Black, "c5"};
      VERIFY(p.figure() == Figure::King, caseLabel);
      VERIFY(p.color() == Color::Black, caseLabel);
      VERIFY(p.coord() == Square("c5"), caseLabel);
   }
}


void testPieceCtorWithNotation()
{
   {
      const std::string caseLabel = "Piece ctor with notation";

      VERIFY(Piece("Bbg4") == Piece(Figure::Bishop, Color::Black, "g4"), caseLabel);
      VERIFY(Piece("Kwh8") == Piece(Figure::King, Color::White, "h8"), caseLabel);
      VERIFY(Piece("wh8") == Piece(Figure::Pawn, Color::White, "h8"), caseLabel);
      VERIFY(Piece("bc4") == Piece(Figure::Pawn, Color::Black, "c4"), caseLabel);
   }
   {
      const std::string caseLabel = "Piece ctor with notation for invalid notation";

      VERIFY(Piece("Tbg4") == Piece(Figure::Pawn, Color::White, Square()), caseLabel);
      VERIFY(Piece("Kqh8") == Piece(Figure::King, Color::White, "h8"), caseLabel);
      VERIFY(Piece("Rwr0") == Piece(Figure::Rook, Color::White, Square()), caseLabel);
   }
}


void testPieceCtorWithNotationAndColor()
{
   {
      const std::string caseLabel = "Piece ctor with notation and color";

      VERIFY(Piece("Bg4", Color::Black) == Piece(Figure::Bishop, Color::Black, "g4"),
             caseLabel);
      VERIFY(Piece("Kh8", Color::White) == Piece(Figure::King, Color::White, "h8"),
             caseLabel);
      VERIFY(Piece("h8", Color::White) == Piece(Figure::Pawn, Color::White, "h8"),
             caseLabel);
      VERIFY(Piece("c4", Color::Black) == Piece(Figure::Pawn, Color::Black, "c4"),
             caseLabel);
   }
   {
      const std::string caseLabel =
         "Piece ctor with notation and color for invalid notation";

      VERIFY(Piece("Tg4", Color::White) == Piece(Figure::Pawn, Color::White, Square()),
             caseLabel);
      VERIFY(Piece("Rr0", Color::Black) == Piece(Figure::Rook, Color::Black, Square()),
             caseLabel);
   }
}


void testPieceColor()
{
   {
      const std::string caseLabel = "Piece::color";

      VERIFY(Piece(Figure::King, Color::Black, "f4").color() == Color::Black, caseLabel);
      VERIFY(Piece(Figure::Pawn, Color::White, "a1").color() == Color::White, caseLabel);
   }
}


void testPieceCoordinate()
{
   {
      const std::string caseLabel = "Piece::coord";

      VERIFY(Piece(Figure::King, Color::Black, "f4").coord() == Square("f4"), caseLabel);
      VERIFY(Piece(Figure::Pawn, Color::White, "a1").coord() == Square("a1"), caseLabel);
   }
}


void testPieceIsFigure()
{
   {
      const std::string caseLabel = "Piece::isFigure";

      VERIFY(Piece(Figure::King, Color::Black, "f4").figure() == Figure::King, caseLabel);
      VERIFY(Piece(Figure::King, Color::Black, "f4").figure() != Figure::Queen,
             caseLabel);
      VERIFY(Piece(Figure::Pawn, Color::White, "h1").figure() == Figure::Pawn, caseLabel);
      VERIFY(Piece(Figure::Pawn, Color::White, "b7").figure() != Figure::Rook, caseLabel);
   }
}


void testPieceNotate()
{
   {
      const std::string caseLabel = "Piece::notate for figure only";

      VERIFY(Piece(Figure::King, Color::Black, "f4").notate(Piece::Notation::F) == "K",
             caseLabel);
      VERIFY(Piece(Figure::Queen, Color::Black, "a2").notate(Piece::Notation::F) == "Q",
             caseLabel);
      VERIFY(Piece(Figure::Rook, Color::White, "h8").notate(Piece::Notation::F) == "R",
             caseLabel);
      VERIFY(Piece(Figure::Bishop, Color::White, "c6").notate(Piece::Notation::F) == "B",
             caseLabel);
      VERIFY(Piece(Figure::Knight, Color::Black, "b8").notate(Piece::Notation::F) == "N",
             caseLabel);
      VERIFY(Piece(Figure::Pawn, Color::White, "b7").notate(Piece::Notation::F) == "",
             caseLabel);
   }
   {
      const std::string caseLabel = "Piece::notate for figure and coordinate";

      VERIFY(Piece(Figure::King, Color::Black, "f4").notate(Piece::Notation::FL) == "Kf4",
             caseLabel);
      VERIFY(Piece(Figure::Queen, Color::Black, "a2").notate(Piece::Notation::FL) ==
                "Qa2",
             caseLabel);
      VERIFY(Piece(Figure::Rook, Color::White, "h8").notate(Piece::Notation::FL) == "Rh8",
             caseLabel);
      VERIFY(Piece(Figure::Bishop, Color::White, "c6").notate(Piece::Notation::FL) ==
                "Bc6",
             caseLabel);
      VERIFY(Piece(Figure::Knight, Color::Black, "b8").notate(Piece::Notation::FL) ==
                "Nb8",
             caseLabel);
      VERIFY(Piece(Figure::Pawn, Color::White, "b7").notate(Piece::Notation::FL) == "b7",
             caseLabel);
   }
   {
      const std::string caseLabel = "Piece::notate for figure and color";

      VERIFY(Piece(Figure::King, Color::Black, "f4").notate(Piece::Notation::FC) == "Kb",
             caseLabel);
      VERIFY(Piece(Figure::Queen, Color::Black, "a2").notate(Piece::Notation::FC) == "Qb",
             caseLabel);
      VERIFY(Piece(Figure::Rook, Color::White, "h8").notate(Piece::Notation::FC) == "Rw",
             caseLabel);
      VERIFY(Piece(Figure::Bishop, Color::White, "c6").notate(Piece::Notation::FC) ==
                "Bw",
             caseLabel);
      VERIFY(Piece(Figure::Knight, Color::Black, "b8").notate(Piece::Notation::FC) ==
                "Nb",
             caseLabel);
      VERIFY(Piece(Figure::Pawn, Color::White, "b7").notate(Piece::Notation::FC) == "w",
             caseLabel);
   }
   {
      const std::string caseLabel = "Piece::notate for figure, color, and coordinate";

      VERIFY(Piece(Figure::King, Color::Black, "f4").notate(Piece::Notation::FCL) ==
                "Kbf4",
             caseLabel);
      VERIFY(Piece(Figure::Queen, Color::Black, "a2").notate(Piece::Notation::FCL) ==
                "Qba2",
             caseLabel);
      VERIFY(Piece(Figure::Rook, Color::White, "h8").notate(Piece::Notation::FCL) ==
                "Rwh8",
             caseLabel);
      VERIFY(Piece(Figure::Bishop, Color::White, "c6").notate(Piece::Notation::FCL) ==
                "Bwc6",
             caseLabel);
      VERIFY(Piece(Figure::Knight, Color::Black, "b8").notate(Piece::Notation::FCL) ==
                "Nbb8",
             caseLabel);
      VERIFY(Piece(Figure::Pawn, Color::White, "b7").notate(Piece::Notation::FCL) ==
                "wb7",
             caseLabel);
   }
}


void testPieceMove()
{
   {
      const std::string caseLabel = "Piece::move";

      VERIFY(Piece(Figure::King, Color::Black, "f4").move("g3"_sq).coord() ==
                Square("g3"),
             caseLabel);
   }
   {
      const std::string caseLabel = "Piece::move to invalid field";

      VERIFY(Piece(Figure::King, Color::Black, "f4").move("k3"_sq).coord() == Square(),
             caseLabel);
   }
   {
      const std::string caseLabel = "Piece::move that is invalid for piece";

      // No checking for illegal moves.
      VERIFY(Piece(Figure::King, Color::Black, "f4").move("a1"_sq).coord() ==
                Square("a1"),
             caseLabel);
   }
}


void testPieceThreatenedSquaresForKing()
{
   {
      const std::string caseLabel =
         "Piece::threatenedSquares for king without other pieces";

      struct
      {
         std::string piece;
         std::vector<std::string> nextLocations;
      } testCases[] = {
         {"Kwd4", {"c3", "c4", "c5", "d3", "d5", "e3", "e4", "e5"}},
         // On first file
         {"Kba3", {"a2", "a4", "b2", "b3", "b4"}},
         // On last file
         {"Kwh7", {"g6", "g7", "g8", "h6", "h8"}},
         // On first rank
         {"Kbe1", {"d1", "d2", "e2", "f1", "f2"}},
         // On last rank
         {"Kbb8", {"a7", "a8", "b7", "c7", "c8"}},
         // In corners
         {"Kwa1", {"a2", "b2", "b1"}},
         {"Kwa8", {"a7", "b8", "b7"}},
         {"Kbh1", {"h2", "g1", "g2"}},
         {"Kbh8", {"h7", "g7", "g8"}},
      };
      for (const auto& test : testCases)
      {
         Piece piece(test.piece);
         Position pos({piece});
         VERIFY(
            verifySquares(piece.threatenedSquares(pos), piece, pos, test.nextLocations),
            caseLabel);
      }
   }
   {
      const std::string caseLabel =
         "Piece::nextSquares for king with pieces of same color";

      struct
      {
         std::string piece;
         std::vector<std::string> otherPieces;
         std::vector<std::string> nextLocations;
      } testCases[] = {
         // Not blocking.
         {"Kwd4", {"Bwg4", "wc2"}, {"c3", "c4", "c5", "d3", "d5", "e3", "e4", "e5"}},
         // Blocking some squares.
         {"Kwd4", {"Bwc4", "we3"}, {"c3", "c5", "d3", "d5", "e4", "e5"}},
         // Blocking all squares.
         {"Kba1", {"ba2", "Rbb2", "Qbb1"}, {}},
      };
      for (const auto& test : testCases)
      {
         Piece piece(test.piece);
         std::vector<Piece> all{piece};
         std::transform(begin(test.otherPieces), end(test.otherPieces),
                        std::back_inserter(all),
                        [](const std::string& notation) { return Piece(notation); });
         Position pos(all);
         VERIFY(
            verifySquares(piece.threatenedSquares(pos), piece, pos, test.nextLocations),
            caseLabel);
      }
   }
   {
      const std::string caseLabel =
         "Piece::nextSquares for king with pieces of other color";

      struct
      {
         std::string piece;
         std::vector<std::string> otherPieces;
         std::vector<std::string> nextLocations;
      } testCases[] = {
         // Not blocking.
         {"Kwd4", {"Bbd8", "bc2"}, {"c3", "c4", "c5", "d3", "d5", "e3", "e4", "e5"}},
         // Blocking some squares.
         {"Kwd4", {"bc3", "be3"}, {"c3", "c4", "c5", "d3", "d5", "e3", "e4", "e5"}},
         // Squares included even though the king would be in check.
         {"Kbc4", {"Rwd5", "wh3"}, {"d5", "d4", "d3", "c5", "c3", "b5", "b4", "b3"}},
      };
      for (const auto& test : testCases)
      {
         Piece piece(test.piece);
         std::vector<Piece> all{piece};
         std::transform(begin(test.otherPieces), end(test.otherPieces),
                        std::back_inserter(all),
                        [](const std::string& notation) { return Piece(notation); });
         Position pos(all);
         VERIFY(
            verifySquares(piece.threatenedSquares(pos), piece, pos, test.nextLocations),
            caseLabel);
      }
   }
}


void testPieceThreatenedSquaresForQueen()
{
   {
      const std::string caseLabel =
         "Piece::threatenedSquares for queen without other pieces";

      struct
      {
         std::string piece;
         std::vector<std::string> nextLocations;
      } testCases[] = {
         {"Qwd4", {"c3", "b2", "a1", "d3", "d2", "d1", "e3", "f2", "g1",
                   "c4", "b4", "a4", "e4", "f4", "g4", "h4", "c5", "b6",
                   "a7", "d5", "d6", "d7", "d8", "e5", "f6", "g7", "h8"}},
         // On first file
         {"Qba3", {"a2", "a1", "a4", "a5", "a6", "a7", "a8", "b2", "c1", "b3", "c3",
                   "d3", "e3", "f3", "g3", "h3", "b4", "c5", "d6", "e7", "f8"}},
         // On last file
         {"Qwh7", {"h1", "h2", "h3", "h4", "h5", "h6", "h8", "a7", "b7", "c7", "d7",
                   "e7", "f7", "g7", "g8", "g6", "f5", "e4", "d3", "c2", "b1"}},
         // On first rank
         {"Qbe1", {"e2", "e3", "e4", "e5", "e6", "e7", "e8", "a1", "b1", "c1", "d1",
                   "f1", "g1", "h1", "d2", "c3", "b4", "a5", "f2", "g3", "h4"}},
         // On last rank
         {"Qbb8", {"b1", "b2", "b3", "b4", "b5", "b6", "b7", "a8", "c8", "d8", "e8",
                   "f8", "g8", "h8", "a7", "c7", "d6", "e5", "f4", "g3", "h2"}},
         // In corners
         {"Qwa1", {"a2", "a3", "a4", "a5", "a6", "a7", "a8", "b1", "c1", "d1", "e1",
                   "f1", "g1", "h1", "b2", "c3", "d4", "e5", "f6", "g7", "h8"}},
         {"Qwa8", {"a1", "a2", "a3", "a4", "a5", "a6", "a7", "b8", "c8", "d8", "e8",
                   "f8", "g8", "h8", "b7", "c6", "d5", "e4", "f3", "g2", "h1"}},
         {"Qbh1", {"h2", "h3", "h4", "h5", "h6", "h7", "h8", "g1", "f1", "e1", "d1",
                   "c1", "b1", "a1", "g2", "f3", "e4", "d5", "c6", "b7", "a8"}},
         {"Qbh8", {"h7", "h6", "h5", "h4", "h3", "h2", "h1", "g8", "f8", "e8", "d8",
                   "c8", "b8", "a8", "g7", "f6", "e5", "d4", "c3", "b2", "a1"}},
      };
      for (const auto& test : testCases)
      {
         Piece piece(test.piece);
         Position pos({piece});
         VERIFY(
            verifySquares(piece.threatenedSquares(pos), piece, pos, test.nextLocations),
            caseLabel);
      }
   }
   {
      const std::string caseLabel =
         "Piece::threatenedSquares for queen with pieces of same color";

      struct
      {
         std::string piece;
         std::vector<std::string> otherPieces;
         std::vector<std::string> nextLocations;
      } testCases[] = {
         // Not blocking.
         {"Qwd4", {"Bwa5", "wc2"}, {"c3", "b2", "a1", "d3", "d2", "d1", "e3",
                                    "f2", "g1", "c4", "b4", "a4", "e4", "f4",
                                    "g4", "h4", "c5", "b6", "a7", "d5", "d6",
                                    "d7", "d8", "e5", "f6", "g7", "h8"}},
         // Blocking squares along diagonal.
         {"Qwd4", {"Bwc5"}, {"c3", "b2", "a1", "d3", "d2", "d1", "e3", "f2",
                             "g1", "c4", "b4", "a4", "e4", "f4", "g4", "h4",
                             "d5", "d6", "d7", "d8", "e5", "f6", "g7", "h8"}},
         // Blocking squares along rank.
         {"Qwd4", {"wf4"}, {"c3", "b2", "a1", "d3", "d2", "d1", "e3", "f2",
                            "g1", "c4", "b4", "a4", "e4", "c5", "b6", "a7",
                            "d5", "d6", "d7", "d8", "e5", "f6", "g7", "h8"}},
         // Blocking squares along file.
         {"Qbd4", {"Rbd6"}, {"c3", "b2", "a1", "d3", "d2", "d1", "e3", "f2",
                             "g1", "c4", "b4", "a4", "e4", "f4", "g4", "h4",
                             "c5", "b6", "a7", "d5", "e5", "f6", "g7", "h8"}},
         // Blocking all squares.
         {"Qba1", {"ba2", "Rbb2", "Kbb1"}, {}},
      };
      for (const auto& test : testCases)
      {
         Piece piece(test.piece);
         std::vector<Piece> all{piece};
         std::transform(begin(test.otherPieces), end(test.otherPieces),
                        std::back_inserter(all),
                        [](const std::string& notation) { return Piece(notation); });
         Position pos(all);
         VERIFY(
            verifySquares(piece.threatenedSquares(pos), piece, pos, test.nextLocations),
            caseLabel);
      }
   }
   {
      const std::string caseLabel =
         "Piece::threatenedSquares for queen with pieces of other color";

      struct
      {
         std::string piece;
         std::vector<std::string> otherPieces;
         std::vector<std::string> nextLocations;
      } testCases[] = {
         // Not blocking.
         {"Qwd4", {"Bba5", "bc2"}, {"c3", "b2", "a1", "d3", "d2", "d1", "e3",
                                    "f2", "g1", "c4", "b4", "a4", "e4", "f4",
                                    "g4", "h4", "c5", "b6", "a7", "d5", "d6",
                                    "d7", "d8", "e5", "f6", "g7", "h8"}},
         // Blocking squares along diagonal.
         {"Qwd4", {"Bbc5"}, {"c3", "b2", "a1", "d3", "d2", "d1", "e3", "f2", "g1",
                             "c4", "b4", "a4", "e4", "f4", "g4", "h4", "c5", "d5",
                             "d6", "d7", "d8", "e5", "f6", "g7", "h8"}},
         // Blocking squares along rank.
         {"Qwd4", {"bf4"}, {"c3", "b2", "a1", "d3", "d2", "d1", "e3", "f2", "g1",
                            "c4", "b4", "a4", "e4", "f4", "c5", "b6", "a7", "d5",
                            "d6", "d7", "d8", "e5", "f6", "g7", "h8"}},
         // Blocking squares along file.
         {"Qbd4", {"Rwd6"}, {"c3", "b2", "a1", "d3", "d2", "d1", "e3", "f2", "g1",
                             "c4", "b4", "a4", "e4", "f4", "g4", "h4", "c5", "b6",
                             "a7", "d5", "d6", "e5", "f6", "g7", "h8"}},
         // Blocking all squares.
         {"Qba1", {"wa2", "Rwb2", "Kwb1"}, {"a2", "b2", "b1"}},
      };
      for (const auto& test : testCases)
      {
         Piece piece(test.piece);
         std::vector<Piece> all{piece};
         std::transform(begin(test.otherPieces), end(test.otherPieces),
                        std::back_inserter(all),
                        [](const std::string& notation) { return Piece(notation); });
         Position pos(all);
         VERIFY(
            verifySquares(piece.threatenedSquares(pos), piece, pos, test.nextLocations),
            caseLabel);
      }
   }
}


void testPieceThreatenedSquaresForRook()
{
   {
      const std::string caseLabel =
         "Piece::threatenedSquares for rook without other pieces";

      struct
      {
         std::string piece;
         std::vector<std::string> nextLocations;
      } testCases[] = {
         {"Rwd4",
          {"d3", "d2", "d1", "c4", "b4", "a4", "e4", "f4", "g4", "h4", "d5", "d6", "d7",
           "d8"}},
         // On first file
         {"Rba3",
          {"a2", "a1", "a4", "a5", "a6", "a7", "a8", "b3", "c3", "d3", "e3", "f3", "g3",
           "h3"}},
         // On last file
         {"Rwh7",
          {"h1", "h2", "h3", "h4", "h5", "h6", "h8", "a7", "b7", "c7", "d7", "e7", "f7",
           "g7"}},
         // On first rank
         {"Rbe1",
          {"e2", "e3", "e4", "e5", "e6", "e7", "e8", "a1", "b1", "c1", "d1", "f1", "g1",
           "h1"}},
         // On last rank
         {"Rbb8",
          {"b1", "b2", "b3", "b4", "b5", "b6", "b7", "a8", "c8", "d8", "e8", "f8", "g8",
           "h8"}},
         // In corners
         {"Rwa1",
          {"a2", "a3", "a4", "a5", "a6", "a7", "a8", "b1", "c1", "d1", "e1", "f1", "g1",
           "h1"}},
         {"Rwa8",
          {"a1", "a2", "a3", "a4", "a5", "a6", "a7", "b8", "c8", "d8", "e8", "f8", "g8",
           "h8"}},
         {"Rbh1",
          {"h2", "h3", "h4", "h5", "h6", "h7", "h8", "g1", "f1", "e1", "d1", "c1", "b1",
           "a1"}},
         {"Rbh8",
          {"h7", "h6", "h5", "h4", "h3", "h2", "h1", "g8", "f8", "e8", "d8", "c8", "b8",
           "a8"}},
      };
      for (const auto& test : testCases)
      {
         Piece piece(test.piece);
         Position pos({piece});
         VERIFY(
            verifySquares(piece.threatenedSquares(pos), piece, pos, test.nextLocations),
            caseLabel);
      }
   }
   {
      const std::string caseLabel =
         "Piece::threatenedSquares for rook with pieces of same color";

      struct
      {
         std::string piece;
         std::vector<std::string> otherPieces;
         std::vector<std::string> nextLocations;
      } testCases[] = {
         // Not blocking.
         {"Rwd4",
          {"Bwa5", "wc2"},
          {"d3", "d2", "d1", "c4", "b4", "a4", "e4", "f4", "g4", "h4", "d5", "d6", "d7",
           "d8"}},
         // Blocking squares along rank.
         {"Rwd4",
          {"wf4"},
          {"d3", "d2", "d1", "c4", "b4", "a4", "e4", "d5", "d6", "d7", "d8"}},
         // Blocking squares along file.
         {"Rbd4",
          {"Rbd6"},
          {"d3", "d2", "d1", "c4", "b4", "a4", "e4", "f4", "g4", "h4", "d5"}},
         // Blocking all squares.
         {"Rba1", {"ba2", "Kbb1"}, {}},
      };
      for (const auto& test : testCases)
      {
         Piece piece(test.piece);
         std::vector<Piece> all{piece};
         std::transform(begin(test.otherPieces), end(test.otherPieces),
                        std::back_inserter(all),
                        [](const std::string& notation) { return Piece(notation); });
         Position pos(all);
         VERIFY(
            verifySquares(piece.threatenedSquares(pos), piece, pos, test.nextLocations),
            caseLabel);
      }
   }
   {
      const std::string caseLabel =
         "Piece::threatenedSquares for rook with pieces of other color";

      struct
      {
         std::string piece;
         std::vector<std::string> otherPieces;
         std::vector<std::string> nextLocations;
      } testCases[] = {
         // Not blocking.
         {"Rwd4",
          {"Bba5", "bc2"},
          {"d3", "d2", "d1", "c4", "b4", "a4", "e4", "f4", "g4", "h4", "d5", "d6", "d7",
           "d8"}},
         // Blocking squares along rank.
         {"Rwd4",
          {"bf4"},
          {"d3", "d2", "d1", "c4", "b4", "a4", "e4", "f4", "d5", "d6", "d7", "d8"}},
         // Blocking squares along file.
         {"Rbd4",
          {"Rwd6"},
          {"d3", "d2", "d1", "c4", "b4", "a4", "e4", "f4", "g4", "h4", "d5", "d6"}},
         // Blocking all squares.
         {"Rba1", {"wa2", "Kwb1"}, {"a2", "b1"}},
      };
      for (const auto& test : testCases)
      {
         Piece piece(test.piece);
         std::vector<Piece> all{piece};
         std::transform(begin(test.otherPieces), end(test.otherPieces),
                        std::back_inserter(all),
                        [](const std::string& notation) { return Piece(notation); });
         Position pos(all);
         VERIFY(
            verifySquares(piece.threatenedSquares(pos), piece, pos, test.nextLocations),
            caseLabel);
      }
   }
}


void testPieceThreatenedSquaresForBishop()
{
   {
      const std::string caseLabel =
         "Piece::threatenedSquares for bishop without other pieces";

      struct
      {
         std::string piece;
         std::vector<std::string> nextLocations;
      } testCases[] = {
         {"Bwd4",
          {"c3", "b2", "a1", "e3", "f2", "g1", "c5", "b6", "a7", "e5", "f6", "g7", "h8"}},
         // On first file
         {"Bba3", {"b2", "c1", "b4", "c5", "d6", "e7", "f8"}},
         // On last file
         {"Bwh7", {"g8", "g6", "f5", "e4", "d3", "c2", "b1"}},
         // On first rank
         {"Bbe1", {"d2", "c3", "b4", "a5", "f2", "g3", "h4"}},
         // On last rank
         {"Bbb8", {"a7", "c7", "d6", "e5", "f4", "g3", "h2"}},
         // In corners
         {"Bwa1", {"b2", "c3", "d4", "e5", "f6", "g7", "h8"}},
         {"Bwa8", {"b7", "c6", "d5", "e4", "f3", "g2", "h1"}},
         {"Bbh1", {"g2", "f3", "e4", "d5", "c6", "b7", "a8"}},
         {"Bbh8", {"g7", "f6", "e5", "d4", "c3", "b2", "a1"}},
      };
      for (const auto& test : testCases)
      {
         Piece piece(test.piece);
         Position pos({piece});
         VERIFY(
            verifySquares(piece.threatenedSquares(pos), piece, pos, test.nextLocations),
            caseLabel);
      }
   }
   {
      const std::string caseLabel =
         "Piece::threatenedSquares for bishop with pieces of same color";

      struct
      {
         std::string piece;
         std::vector<std::string> otherPieces;
         std::vector<std::string> nextLocations;
      } testCases[] = {
         // Not blocking.
         {"Bwd4",
          {"Nwa5", "wc2"},
          {"c3", "b2", "a1", "e3", "f2", "g1", "c5", "b6", "a7", "e5", "f6", "g7", "h8"}},
         // Blocking squares along diagonal.
         {"Bwd4", {"Nwc5"}, {"c3", "b2", "a1", "e3", "f2", "g1", "e5", "f6", "g7", "h8"}},
         // Blocking all squares.
         {"Bba1", {"Rbb2"}, {}},
      };
      for (const auto& test : testCases)
      {
         Piece piece(test.piece);
         std::vector<Piece> all{piece};
         std::transform(begin(test.otherPieces), end(test.otherPieces),
                        std::back_inserter(all),
                        [](const std::string& notation) { return Piece(notation); });
         Position pos(all);
         VERIFY(
            verifySquares(piece.threatenedSquares(pos), piece, pos, test.nextLocations),
            caseLabel);
      }
   }
   {
      const std::string caseLabel =
         "Piece::threatenedSquares for bishop with pieces of other color";

      struct
      {
         std::string piece;
         std::vector<std::string> otherPieces;
         std::vector<std::string> nextLocations;
      } testCases[] = {
         // Not blocking.
         {"Bwd4",
          {"Nba5", "bc2"},
          {"c3", "b2", "a1", "e3", "f2", "g1", "c5", "b6", "a7", "e5", "f6", "g7", "h8"}},
         // Blocking squares along diagonal.
         {"Bwd4",
          {"Nbc5"},
          {"c3", "b2", "a1", "e3", "f2", "g1", "e5", "f6", "g7", "h8", "c5"}},
         // Blocking all squares.
         {"Bba1", {"Rwb2"}, {"b2"}},
      };
      for (const auto& test : testCases)
      {
         Piece piece(test.piece);
         std::vector<Piece> all{piece};
         std::transform(begin(test.otherPieces), end(test.otherPieces),
                        std::back_inserter(all),
                        [](const std::string& notation) { return Piece(notation); });
         Position pos(all);
         VERIFY(
            verifySquares(piece.threatenedSquares(pos), piece, pos, test.nextLocations),
            caseLabel);
      }
   }
}


void testPieceThreatenedSquaresForKnight()
{
   {
      const std::string caseLabel =
         "Piece::threatenedSquares for knight without other pieces";

      struct
      {
         std::string piece;
         std::vector<std::string> nextLocations;
      } testCases[] = {
         {"Nwd4", {"c2", "e2", "c6", "e6", "b3", "b5", "f3", "f5"}},
         // On first file
         {"Nba3", {"b1", "b5", "c2", "c4"}},
         // On last file
         {"Nwh7", {"g5", "f8", "f6"}},
         // On first rank
         {"Nbe1", {"c2", "g2", "d3", "f3"}},
         // On last rank
         {"Nbb8", {"d7", "a6", "c6"}},
         // In corners
         {"Nwa1", {"c2", "b3"}},
         {"Nwa8", {"b6", "c7"}},
         {"Nbh1", {"f2", "g3"}},
         {"Nbh8", {"g6", "f7"}},
      };
      for (const auto& test : testCases)
      {
         Piece piece(test.piece);
         Position pos({piece});
         VERIFY(
            verifySquares(piece.threatenedSquares(pos), piece, pos, test.nextLocations),
            caseLabel);
      }
   }
   {
      const std::string caseLabel =
         "Piece::threatenedSquares for knight with pieces of same color";

      struct
      {
         std::string piece;
         std::vector<std::string> otherPieces;
         std::vector<std::string> nextLocations;
      } testCases[] = {
         // Not blocking.
         {"Nwd4", {"Bwa5", "wd2"}, {"c2", "e2", "c6", "e6", "b3", "b5", "f3", "f5"}},
         // Blocking a square.
         {"Nwd4", {"Bwc2"}, {"e2", "c6", "e6", "b3", "b5", "f3", "f5"}},
         // Blocking all squares.
         {"Nba1", {"bc2", "Rbb3"}, {}},
         // Jumps over pieces.
         {"Nwa1", {"wa2", "Rwb1"}, {"c2", "b3"}},
      };
      for (const auto& test : testCases)
      {
         Piece piece(test.piece);
         std::vector<Piece> all{piece};
         std::transform(begin(test.otherPieces), end(test.otherPieces),
                        std::back_inserter(all),
                        [](const std::string& notation) { return Piece(notation); });
         Position pos(all);
         VERIFY(
            verifySquares(piece.threatenedSquares(pos), piece, pos, test.nextLocations),
            caseLabel);
      }
   }
   {
      const std::string caseLabel =
         "Piece::threatenedSquares for knight with pieces of other color";

      struct
      {
         std::string piece;
         std::vector<std::string> otherPieces;
         std::vector<std::string> nextLocations;
      } testCases[] = {
         // Not blocking.
         {"Nwd4", {"Bba5", "bd2"}, {"c2", "e2", "c6", "e6", "b3", "b5", "f3", "f5"}},
         // Blocking a square.
         {"Nwd4", {"Bbc2"}, {"c2", "e2", "c6", "e6", "b3", "b5", "f3", "f5"}},
         // Blocking all squares.
         {"Nba1", {"wc2", "Rwb3"}, {"c2", "b3"}},
         // Jumps over pieces.
         {"Nwa1", {"ba2", "Rbb1"}, {"c2", "b3"}},
      };
      for (const auto& test : testCases)
      {
         Piece piece(test.piece);
         std::vector<Piece> all{piece};
         std::transform(begin(test.otherPieces), end(test.otherPieces),
                        std::back_inserter(all),
                        [](const std::string& notation) { return Piece(notation); });
         Position pos(all);
         VERIFY(
            verifySquares(piece.threatenedSquares(pos), piece, pos, test.nextLocations),
            caseLabel);
      }
   }
}


void testPieceThreatenedSquaresForPawn()
{
   {
      const std::string caseLabel =
         "Piece::threatenedSquares for pawn without other pieces";

      struct
      {
         std::string piece;
         std::vector<std::string> nextLocations;
      } testCases[] = {
         {"ba5", {"b4"}},
         {"wg3", {"f4", "h4"}},
      };
      for (const auto& test : testCases)
      {
         Piece piece(test.piece);
         Position pos({piece});
         VERIFY(
            verifySquares(piece.threatenedSquares(pos), piece, pos, test.nextLocations),
            caseLabel);
      }
   }
   {
      const std::string caseLabel =
         "Piece::threatenedSquares for pawn with pieces of same color";

      struct
      {
         std::string piece;
         std::vector<std::string> otherPieces;
         std::vector<std::string> nextLocations;
      } testCases[] = {
         // Not on squares that pawn threatens.
         {"wd2", {"Bwa5", "wc2"}, {"c3", "e3"}},
         {"ba5", {"Bba3", "Qbc2"}, {"b4"}},
         // On squares that pawn threatens.
         {"wd2", {"Bwc3"}, {"e3"}},
         {"bf5", {"Bbe4", "bg4"}, {}},
      };
      for (const auto& test : testCases)
      {
         Piece piece(test.piece);
         std::vector<Piece> all{piece};
         std::transform(begin(test.otherPieces), end(test.otherPieces),
                        std::back_inserter(all),
                        [](const std::string& notation) { return Piece(notation); });
         Position pos(all);
         VERIFY(
            verifySquares(piece.threatenedSquares(pos), piece, pos, test.nextLocations),
            caseLabel);
      }
   }
   {
      const std::string caseLabel =
         "Piece::threatenedSquares for pawn with pieces of other color";

      struct
      {
         std::string piece;
         std::vector<std::string> otherPieces;
         std::vector<std::string> nextLocations;
      } testCases[] = {
         // Not on squares that pawn threatens.
         {"wd2", {"Bba5", "bc7"}, {"c3", "e3"}},
         {"ba5", {"Bwa3", "Qwc2"}, {"b4"}},
         // On squares that pawn threatens.
         {"wd2", {"Bbc3"}, {"c3", "e3"}},
         {"ba5", {"Bwb4"}, {"b4"}},
         {"wd2", {"Bbc3", "be3"}, {"c3", "e3"}},
         {"bf6", {"Bwg5", "Qwe5"}, {"g5", "e5"}},
      };
      for (const auto& test : testCases)
      {
         Piece piece(test.piece);
         std::vector<Piece> all{piece};
         std::transform(begin(test.otherPieces), end(test.otherPieces),
                        std::back_inserter(all),
                        [](const std::string& notation) { return Piece(notation); });
         Position pos(all);
         VERIFY(
            verifySquares(piece.threatenedSquares(pos), piece, pos, test.nextLocations),
            caseLabel);
      }
   }
}


void testPieceNextMovesForKing()
{
   {
      const std::string caseLabel = "Piece::nextMoves for king without other pieces";

      struct
      {
         std::string piece;
         std::vector<std::string> nextLocations;
      } testCases[] = {
         {"Kwd4", {"c3", "c4", "c5", "d3", "d5", "e3", "e4", "e5"}},
         // On first file
         {"Kba3", {"a2", "a4", "b2", "b3", "b4"}},
         // On last file
         {"Kwh7", {"g6", "g7", "g8", "h6", "h8"}},
         // On first rank
         {"Kbe1", {"d1", "d2", "e2", "f1", "f2"}},
         // On last rank
         {"Kbb8", {"a7", "a8", "b7", "c7", "c8"}},
         // In corners
         {"Kwa1", {"a2", "b2", "b1"}},
         {"Kwa8", {"a7", "b8", "b7"}},
         {"Kbh1", {"h2", "g1", "g2"}},
         {"Kbh8", {"h7", "g7", "g8"}},
      };
      for (const auto& test : testCases)
      {
         Piece piece(test.piece);
         Position pos({piece});
         VERIFY(verifyNextMoves(piece.nextMoves(pos), piece, pos, test.nextLocations),
                caseLabel);
      }
   }
   {
      const std::string caseLabel = "Piece::nextMoves for king with pieces of same color";

      struct
      {
         std::string piece;
         std::vector<std::string> otherPieces;
         std::vector<std::string> nextLocations;
      } testCases[] = {
         // Not blocking.
         {"Kwd4", {"Bwg4", "wc2"}, {"c3", "c4", "c5", "d3", "d5", "e3", "e4", "e5"}},
         // Blocking some squares.
         {"Kwd4", {"Bwc4", "we3"}, {"c3", "c5", "d3", "d5", "e4", "e5"}},
         // Blocking all squares.
         {"Kba1", {"ba2", "Rbb2", "Qbb1"}, {}},
      };
      for (const auto& test : testCases)
      {
         Piece piece(test.piece);
         std::vector<Piece> all{piece};
         std::transform(begin(test.otherPieces), end(test.otherPieces),
                        std::back_inserter(all),
                        [](const std::string& notation) { return Piece(notation); });
         Position pos(all);
         VERIFY(verifyNextMoves(piece.nextMoves(pos), piece, pos, test.nextLocations),
                caseLabel);
      }
   }
   {
      const std::string caseLabel =
         "Piece::nextMoves for king with pieces of other color";

      struct
      {
         std::string piece;
         std::vector<std::string> otherPieces;
         std::vector<std::string> nextLocations;
      } testCases[] = {
         // Not blocking.
         {"Kwd4", {"Bbd8", "bc2"}, {"c3", "c4", "c5", "d3", "d5", "e3", "e4", "e5"}},
         // Blocking some squares.
         {"Kwd4", {"bc3", "be3"}, {"c3", "c4", "c5", "d3", "d5", "e3", "e4", "e5"}},
         // Moves excludes because the king would be in check.
         {"Kbc4", {"Rwd5", "wh3"}, {"d5", "c3", "b4", "b3"}},
      };
      for (const auto& test : testCases)
      {
         Piece piece(test.piece);
         std::vector<Piece> all{piece};
         std::transform(begin(test.otherPieces), end(test.otherPieces),
                        std::back_inserter(all),
                        [](const std::string& notation) { return Piece(notation); });
         Position pos(all);
         VERIFY(verifyNextMoves(piece.nextMoves(pos), piece, pos, test.nextLocations),
                caseLabel);
      }
   }
   {
      const std::string caseLabel =
         "Piece::nextMoves for king that would lead to check by pawn";

      struct
      {
         std::string piece;
         std::vector<std::string> otherPieces;
         std::vector<std::string> nextLocations;
      } testCases[] = {
         {"Kwd4", {"bd5"}, {"c5", "d5", "e5", "c3", "d3", "e3"}},
      };
      for (const auto& test : testCases)
      {
         Piece piece(test.piece);
         std::vector<Piece> all{piece};
         std::transform(begin(test.otherPieces), end(test.otherPieces),
                        std::back_inserter(all),
                        [](const std::string& notation) { return Piece(notation); });
         Position pos(all);
         VERIFY(verifyNextMoves(piece.nextMoves(pos), piece, pos, test.nextLocations),
                caseLabel);
      }
   }
}


void testPieceNextMovesForQueen()
{
   {
      const std::string caseLabel = "Piece::nextMoves for queen without other pieces";

      struct
      {
         std::string piece;
         std::vector<std::string> nextLocations;
      } testCases[] = {
         {"Qwd4", {"c3", "b2", "a1", "d3", "d2", "d1", "e3", "f2", "g1",
                   "c4", "b4", "a4", "e4", "f4", "g4", "h4", "c5", "b6",
                   "a7", "d5", "d6", "d7", "d8", "e5", "f6", "g7", "h8"}},
         // On first file
         {"Qba3", {"a2", "a1", "a4", "a5", "a6", "a7", "a8", "b2", "c1", "b3", "c3",
                   "d3", "e3", "f3", "g3", "h3", "b4", "c5", "d6", "e7", "f8"}},
         // On last file
         {"Qwh7", {"h1", "h2", "h3", "h4", "h5", "h6", "h8", "a7", "b7", "c7", "d7",
                   "e7", "f7", "g7", "g8", "g6", "f5", "e4", "d3", "c2", "b1"}},
         // On first rank
         {"Qbe1", {"e2", "e3", "e4", "e5", "e6", "e7", "e8", "a1", "b1", "c1", "d1",
                   "f1", "g1", "h1", "d2", "c3", "b4", "a5", "f2", "g3", "h4"}},
         // On last rank
         {"Qbb8", {"b1", "b2", "b3", "b4", "b5", "b6", "b7", "a8", "c8", "d8", "e8",
                   "f8", "g8", "h8", "a7", "c7", "d6", "e5", "f4", "g3", "h2"}},
         // In corners
         {"Qwa1", {"a2", "a3", "a4", "a5", "a6", "a7", "a8", "b1", "c1", "d1", "e1",
                   "f1", "g1", "h1", "b2", "c3", "d4", "e5", "f6", "g7", "h8"}},
         {"Qwa8", {"a1", "a2", "a3", "a4", "a5", "a6", "a7", "b8", "c8", "d8", "e8",
                   "f8", "g8", "h8", "b7", "c6", "d5", "e4", "f3", "g2", "h1"}},
         {"Qbh1", {"h2", "h3", "h4", "h5", "h6", "h7", "h8", "g1", "f1", "e1", "d1",
                   "c1", "b1", "a1", "g2", "f3", "e4", "d5", "c6", "b7", "a8"}},
         {"Qbh8", {"h7", "h6", "h5", "h4", "h3", "h2", "h1", "g8", "f8", "e8", "d8",
                   "c8", "b8", "a8", "g7", "f6", "e5", "d4", "c3", "b2", "a1"}},
      };
      for (const auto& test : testCases)
      {
         Piece piece(test.piece);
         Position pos({piece});
         VERIFY(verifyNextMoves(piece.nextMoves(pos), piece, pos, test.nextLocations),
                caseLabel);
      }
   }
   {
      const std::string caseLabel =
         "Piece::nextMoves for queen with pieces of same color";

      struct
      {
         std::string piece;
         std::vector<std::string> otherPieces;
         std::vector<std::string> nextLocations;
      } testCases[] = {
         // Not blocking.
         {"Qwd4", {"Bwa5", "wc2"}, {"c3", "b2", "a1", "d3", "d2", "d1", "e3",
                                    "f2", "g1", "c4", "b4", "a4", "e4", "f4",
                                    "g4", "h4", "c5", "b6", "a7", "d5", "d6",
                                    "d7", "d8", "e5", "f6", "g7", "h8"}},
         // Blocking squares along diagonal.
         {"Qwd4", {"Bwc5"}, {"c3", "b2", "a1", "d3", "d2", "d1", "e3", "f2",
                             "g1", "c4", "b4", "a4", "e4", "f4", "g4", "h4",
                             "d5", "d6", "d7", "d8", "e5", "f6", "g7", "h8"}},
         // Blocking squares along rank.
         {"Qwd4", {"wf4"}, {"c3", "b2", "a1", "d3", "d2", "d1", "e3", "f2",
                            "g1", "c4", "b4", "a4", "e4", "c5", "b6", "a7",
                            "d5", "d6", "d7", "d8", "e5", "f6", "g7", "h8"}},
         // Blocking squares along file.
         {"Qbd4", {"Rbd6"}, {"c3", "b2", "a1", "d3", "d2", "d1", "e3", "f2",
                             "g1", "c4", "b4", "a4", "e4", "f4", "g4", "h4",
                             "c5", "b6", "a7", "d5", "e5", "f6", "g7", "h8"}},
         // Blocking all squares.
         {"Qba1", {"ba2", "Rbb2", "Kbb1"}, {}},
      };
      for (const auto& test : testCases)
      {
         Piece piece(test.piece);
         std::vector<Piece> all{piece};
         std::transform(begin(test.otherPieces), end(test.otherPieces),
                        std::back_inserter(all),
                        [](const std::string& notation) { return Piece(notation); });
         Position pos(all);
         VERIFY(verifyNextMoves(piece.nextMoves(pos), piece, pos, test.nextLocations),
                caseLabel);
      }
   }
   {
      const std::string caseLabel =
         "Piece::nextMoves for queen with pieces of other color";

      struct
      {
         std::string piece;
         std::vector<std::string> otherPieces;
         std::vector<std::string> nextLocations;
      } testCases[] = {
         // Not blocking.
         {"Qwd4", {"Bba5", "bc2"}, {"c3", "b2", "a1", "d3", "d2", "d1", "e3",
                                    "f2", "g1", "c4", "b4", "a4", "e4", "f4",
                                    "g4", "h4", "c5", "b6", "a7", "d5", "d6",
                                    "d7", "d8", "e5", "f6", "g7", "h8"}},
         // Blocking squares along diagonal.
         {"Qwd4", {"Bbc5"}, {"c3", "b2", "a1", "d3", "d2", "d1", "e3", "f2", "g1",
                             "c4", "b4", "a4", "e4", "f4", "g4", "h4", "c5", "d5",
                             "d6", "d7", "d8", "e5", "f6", "g7", "h8"}},
         // Blocking squares along rank.
         {"Qwd4", {"bf4"}, {"c3", "b2", "a1", "d3", "d2", "d1", "e3", "f2", "g1",
                            "c4", "b4", "a4", "e4", "f4", "c5", "b6", "a7", "d5",
                            "d6", "d7", "d8", "e5", "f6", "g7", "h8"}},
         // Blocking squares along file.
         {"Qbd4", {"Rwd6"}, {"c3", "b2", "a1", "d3", "d2", "d1", "e3", "f2", "g1",
                             "c4", "b4", "a4", "e4", "f4", "g4", "h4", "c5", "b6",
                             "a7", "d5", "d6", "e5", "f6", "g7", "h8"}},
         // Blocking all squares.
         {"Qba1", {"wa2", "Rwb2", "Kwb1"}, {"a2", "b2", "b1"}},
      };
      for (const auto& test : testCases)
      {
         Piece piece(test.piece);
         std::vector<Piece> all{piece};
         std::transform(begin(test.otherPieces), end(test.otherPieces),
                        std::back_inserter(all),
                        [](const std::string& notation) { return Piece(notation); });
         Position pos(all);
         VERIFY(verifyNextMoves(piece.nextMoves(pos), piece, pos, test.nextLocations),
                caseLabel);
      }
   }
}


void testPieceNextMovesForRook()
{
   {
      const std::string caseLabel = "Piece::nextMoves for rook without other pieces";

      struct
      {
         std::string piece;
         std::vector<std::string> nextLocations;
      } testCases[] = {
         {"Rwd4",
          {"d3", "d2", "d1", "c4", "b4", "a4", "e4", "f4", "g4", "h4", "d5", "d6", "d7",
           "d8"}},
         // On first file
         {"Rba3",
          {"a2", "a1", "a4", "a5", "a6", "a7", "a8", "b3", "c3", "d3", "e3", "f3", "g3",
           "h3"}},
         // On last file
         {"Rwh7",
          {"h1", "h2", "h3", "h4", "h5", "h6", "h8", "a7", "b7", "c7", "d7", "e7", "f7",
           "g7"}},
         // On first rank
         {"Rbe1",
          {"e2", "e3", "e4", "e5", "e6", "e7", "e8", "a1", "b1", "c1", "d1", "f1", "g1",
           "h1"}},
         // On last rank
         {"Rbb8",
          {"b1", "b2", "b3", "b4", "b5", "b6", "b7", "a8", "c8", "d8", "e8", "f8", "g8",
           "h8"}},
         // In corners
         {"Rwa1",
          {"a2", "a3", "a4", "a5", "a6", "a7", "a8", "b1", "c1", "d1", "e1", "f1", "g1",
           "h1"}},
         {"Rwa8",
          {"a1", "a2", "a3", "a4", "a5", "a6", "a7", "b8", "c8", "d8", "e8", "f8", "g8",
           "h8"}},
         {"Rbh1",
          {"h2", "h3", "h4", "h5", "h6", "h7", "h8", "g1", "f1", "e1", "d1", "c1", "b1",
           "a1"}},
         {"Rbh8",
          {"h7", "h6", "h5", "h4", "h3", "h2", "h1", "g8", "f8", "e8", "d8", "c8", "b8",
           "a8"}},
      };
      for (const auto& test : testCases)
      {
         Piece piece(test.piece);
         Position pos({piece});
         VERIFY(verifyNextMoves(piece.nextMoves(pos), piece, pos, test.nextLocations),
                caseLabel);
      }
   }
   {
      const std::string caseLabel = "Piece::nextMoves for rook with pieces of same color";

      struct
      {
         std::string piece;
         std::vector<std::string> otherPieces;
         std::vector<std::string> nextLocations;
      } testCases[] = {
         // Not blocking.
         {"Rwd4",
          {"Bwa5", "wc2"},
          {"d3", "d2", "d1", "c4", "b4", "a4", "e4", "f4", "g4", "h4", "d5", "d6", "d7",
           "d8"}},
         // Blocking squares along rank.
         {"Rwd4",
          {"wf4"},
          {"d3", "d2", "d1", "c4", "b4", "a4", "e4", "d5", "d6", "d7", "d8"}},
         // Blocking squares along file.
         {"Rbd4",
          {"Rbd6"},
          {"d3", "d2", "d1", "c4", "b4", "a4", "e4", "f4", "g4", "h4", "d5"}},
         // Blocking all squares.
         {"Rba1", {"ba2", "Kbb1"}, {}},
      };
      for (const auto& test : testCases)
      {
         Piece piece(test.piece);
         std::vector<Piece> all{piece};
         std::transform(begin(test.otherPieces), end(test.otherPieces),
                        std::back_inserter(all),
                        [](const std::string& notation) { return Piece(notation); });
         Position pos(all);
         VERIFY(verifyNextMoves(piece.nextMoves(pos), piece, pos, test.nextLocations),
                caseLabel);
      }
   }
   {
      const std::string caseLabel =
         "Piece::nextMoves for rook with pieces of other color";

      struct
      {
         std::string piece;
         std::vector<std::string> otherPieces;
         std::vector<std::string> nextLocations;
      } testCases[] = {
         // Not blocking.
         {"Rwd4",
          {"Bba5", "bc2"},
          {"d3", "d2", "d1", "c4", "b4", "a4", "e4", "f4", "g4", "h4", "d5", "d6", "d7",
           "d8"}},
         // Blocking squares along rank.
         {"Rwd4",
          {"bf4"},
          {"d3", "d2", "d1", "c4", "b4", "a4", "e4", "f4", "d5", "d6", "d7", "d8"}},
         // Blocking squares along file.
         {"Rbd4",
          {"Rwd6"},
          {"d3", "d2", "d1", "c4", "b4", "a4", "e4", "f4", "g4", "h4", "d5", "d6"}},
         // Blocking all squares.
         {"Rba1", {"wa2", "Kwb1"}, {"a2", "b1"}},
      };
      for (const auto& test : testCases)
      {
         Piece piece(test.piece);
         std::vector<Piece> all{piece};
         std::transform(begin(test.otherPieces), end(test.otherPieces),
                        std::back_inserter(all),
                        [](const std::string& notation) { return Piece(notation); });
         Position pos(all);
         VERIFY(verifyNextMoves(piece.nextMoves(pos), piece, pos, test.nextLocations),
                caseLabel);
      }
   }
}


void testPieceNextMovesForBishop()
{
   {
      const std::string caseLabel = "Piece::nextMoves for bishop without other pieces";

      struct
      {
         std::string piece;
         std::vector<std::string> nextLocations;
      } testCases[] = {
         {"Bwd4",
          {"c3", "b2", "a1", "e3", "f2", "g1", "c5", "b6", "a7", "e5", "f6", "g7", "h8"}},
         // On first file
         {"Bba3", {"b2", "c1", "b4", "c5", "d6", "e7", "f8"}},
         // On last file
         {"Bwh7", {"g8", "g6", "f5", "e4", "d3", "c2", "b1"}},
         // On first rank
         {"Bbe1", {"d2", "c3", "b4", "a5", "f2", "g3", "h4"}},
         // On last rank
         {"Bbb8", {"a7", "c7", "d6", "e5", "f4", "g3", "h2"}},
         // In corners
         {"Bwa1", {"b2", "c3", "d4", "e5", "f6", "g7", "h8"}},
         {"Bwa8", {"b7", "c6", "d5", "e4", "f3", "g2", "h1"}},
         {"Bbh1", {"g2", "f3", "e4", "d5", "c6", "b7", "a8"}},
         {"Bbh8", {"g7", "f6", "e5", "d4", "c3", "b2", "a1"}},
      };
      for (const auto& test : testCases)
      {
         Piece piece(test.piece);
         Position pos({piece});
         VERIFY(verifyNextMoves(piece.nextMoves(pos), piece, pos, test.nextLocations),
                caseLabel);
      }
   }
   {
      const std::string caseLabel =
         "Piece::nextMoves for bishop with pieces of same color";

      struct
      {
         std::string piece;
         std::vector<std::string> otherPieces;
         std::vector<std::string> nextLocations;
      } testCases[] = {
         // Not blocking.
         {"Bwd4",
          {"Nwa5", "wc2"},
          {"c3", "b2", "a1", "e3", "f2", "g1", "c5", "b6", "a7", "e5", "f6", "g7", "h8"}},
         // Blocking squares along diagonal.
         {"Bwd4", {"Nwc5"}, {"c3", "b2", "a1", "e3", "f2", "g1", "e5", "f6", "g7", "h8"}},
         // Blocking all squares.
         {"Bba1", {"Rbb2"}, {}},
      };
      for (const auto& test : testCases)
      {
         Piece piece(test.piece);
         std::vector<Piece> all{piece};
         std::transform(begin(test.otherPieces), end(test.otherPieces),
                        std::back_inserter(all),
                        [](const std::string& notation) { return Piece(notation); });
         Position pos(all);
         VERIFY(verifyNextMoves(piece.nextMoves(pos), piece, pos, test.nextLocations),
                caseLabel);
      }
   }
   {
      const std::string caseLabel =
         "Piece::nextMoves for bishop with pieces of other color";

      struct
      {
         std::string piece;
         std::vector<std::string> otherPieces;
         std::vector<std::string> nextLocations;
      } testCases[] = {
         // Not blocking.
         {"Bwd4",
          {"Nba5", "bc2"},
          {"c3", "b2", "a1", "e3", "f2", "g1", "c5", "b6", "a7", "e5", "f6", "g7", "h8"}},
         // Blocking squares along diagonal.
         {"Bwd4",
          {"Nbc5"},
          {"c3", "b2", "a1", "e3", "f2", "g1", "e5", "f6", "g7", "h8", "c5"}},
         // Blocking all squares.
         {"Bba1", {"Rwb2"}, {"b2"}},
      };
      for (const auto& test : testCases)
      {
         Piece piece(test.piece);
         std::vector<Piece> all{piece};
         std::transform(begin(test.otherPieces), end(test.otherPieces),
                        std::back_inserter(all),
                        [](const std::string& notation) { return Piece(notation); });
         Position pos(all);
         VERIFY(verifyNextMoves(piece.nextMoves(pos), piece, pos, test.nextLocations),
                caseLabel);
      }
   }
}


void testPieceNextMovesForKnight()
{
   {
      const std::string caseLabel = "Piece::nextMoves for knight without other pieces";

      struct
      {
         std::string piece;
         std::vector<std::string> nextLocations;
      } testCases[] = {
         {"Nwd4", {"c2", "e2", "c6", "e6", "b3", "b5", "f3", "f5"}},
         // On first file
         {"Nba3", {"b1", "b5", "c2", "c4"}},
         // On last file
         {"Nwh7", {"g5", "f8", "f6"}},
         // On first rank
         {"Nbe1", {"c2", "g2", "d3", "f3"}},
         // On last rank
         {"Nbb8", {"d7", "a6", "c6"}},
         // In corners
         {"Nwa1", {"c2", "b3"}},
         {"Nwa8", {"b6", "c7"}},
         {"Nbh1", {"f2", "g3"}},
         {"Nbh8", {"g6", "f7"}},
      };
      for (const auto& test : testCases)
      {
         Piece piece(test.piece);
         Position pos({piece});
         VERIFY(verifyNextMoves(piece.nextMoves(pos), piece, pos, test.nextLocations),
                caseLabel);
      }
   }
   {
      const std::string caseLabel =
         "Piece::nextMoves for knight with pieces of same color";

      struct
      {
         std::string piece;
         std::vector<std::string> otherPieces;
         std::vector<std::string> nextLocations;
      } testCases[] = {
         // Not blocking.
         {"Nwd4", {"Bwa5", "wd2"}, {"c2", "e2", "c6", "e6", "b3", "b5", "f3", "f5"}},
         // Blocking a square.
         {"Nwd4", {"Bwc2"}, {"e2", "c6", "e6", "b3", "b5", "f3", "f5"}},
         // Blocking all squares.
         {"Nba1", {"bc2", "Rbb3"}, {}},
         // Jumps over pieces.
         {"Nwa1", {"wa2", "Rwb1"}, {"c2", "b3"}},
      };
      for (const auto& test : testCases)
      {
         Piece piece(test.piece);
         std::vector<Piece> all{piece};
         std::transform(begin(test.otherPieces), end(test.otherPieces),
                        std::back_inserter(all),
                        [](const std::string& notation) { return Piece(notation); });
         Position pos(all);
         VERIFY(verifyNextMoves(piece.nextMoves(pos), piece, pos, test.nextLocations),
                caseLabel);
      }
   }
   {
      const std::string caseLabel =
         "Piece::nextMoves for knight with pieces of other color";

      struct
      {
         std::string piece;
         std::vector<std::string> otherPieces;
         std::vector<std::string> nextLocations;
      } testCases[] = {
         // Not blocking.
         {"Nwd4", {"Bba5", "bd2"}, {"c2", "e2", "c6", "e6", "b3", "b5", "f3", "f5"}},
         // Blocking a square.
         {"Nwd4", {"Bbc2"}, {"c2", "e2", "c6", "e6", "b3", "b5", "f3", "f5"}},
         // Blocking all squares.
         {"Nba1", {"wc2", "Rwb3"}, {"c2", "b3"}},
         // Jumps over pieces.
         {"Nwa1", {"ba2", "Rbb1"}, {"c2", "b3"}},
      };
      for (const auto& test : testCases)
      {
         Piece piece(test.piece);
         std::vector<Piece> all{piece};
         std::transform(begin(test.otherPieces), end(test.otherPieces),
                        std::back_inserter(all),
                        [](const std::string& notation) { return Piece(notation); });
         Position pos(all);
         VERIFY(verifyNextMoves(piece.nextMoves(pos), piece, pos, test.nextLocations),
                caseLabel);
      }
   }
}


void testPieceNextMovesForPawn()
{
   {
      const std::string caseLabel = "Piece::nextMoves for pawn without other pieces";

      struct
      {
         std::string piece;
         std::vector<std::string> nextLocations;
      } testCases[] = {
         // From starting square.
         {"wd2", {"d3", "d4"}},
         {"bh7", {"h6", "h5"}},
         // From other square.
         {"ba5", {"a4"}},
         {"wg3", {"g4"}},
      };
      for (const auto& test : testCases)
      {
         Piece piece(test.piece);
         Position pos({piece});
         VERIFY(verifyNextMoves(piece.nextMoves(pos), piece, pos, test.nextLocations),
                caseLabel);
      }
   }
   {
      const std::string caseLabel = "Piece::nextMoves for pawn with pieces of same color";

      struct
      {
         std::string piece;
         std::vector<std::string> otherPieces;
         std::vector<std::string> nextLocations;
      } testCases[] = {
         // Not blocking.
         {"wd2", {"Bwa5", "wc2"}, {"d3", "d4"}},
         {"ba5", {"Bba3", "Qbc2"}, {"a4"}},
         // Blocking a square.
         {"wd2", {"Bwd4"}, {"d3"}},
         // Blocking all squares.
         {"wd2", {"Bwd3"}, {}},
         {"ba5", {"Bba4"}, {}},
      };
      for (const auto& test : testCases)
      {
         Piece piece(test.piece);
         std::vector<Piece> all{piece};
         std::transform(begin(test.otherPieces), end(test.otherPieces),
                        std::back_inserter(all),
                        [](const std::string& notation) { return Piece(notation); });
         Position pos(all);
         VERIFY(verifyNextMoves(piece.nextMoves(pos), piece, pos, test.nextLocations),
                caseLabel);
      }
   }
   {
      const std::string caseLabel =
         "Piece::nextMoves for pawn with pieces of other color";

      struct
      {
         std::string piece;
         std::vector<std::string> otherPieces;
         std::vector<std::string> nextLocations;
      } testCases[] = {
         // Not blocking.
         {"wd2", {"Bba5", "bc7"}, {"d3", "d4"}},
         {"ba5", {"Bwa3", "Qwc2"}, {"a4"}},
         // Blocking a square.
         {"wd2", {"Bbd4"}, {"d3"}},
         // Blocking all squares.
         {"wd2", {"Bbd3"}, {}},
         {"ba5", {"Bwa4"}, {}},
         // Capturing.
         {"wd2", {"Bbc3"}, {"d3", "d4", "c3"}},
         {"we5", {"Bbf6"}, {"e6", "f6"}},
         // Blocked and capturing.
         {"bf6", {"Bbf5", "Qwe5"}, {"e5"}},
      };
      for (const auto& test : testCases)
      {
         Piece piece(test.piece);
         std::vector<Piece> all{piece};
         std::transform(begin(test.otherPieces), end(test.otherPieces),
                        std::back_inserter(all),
                        [](const std::string& notation) { return Piece(notation); });
         Position pos(all);
         VERIFY(verifyNextMoves(piece.nextMoves(pos), piece, pos, test.nextLocations),
                caseLabel);
      }
   }
}


void testPieceNextPositionsForKing()
{
   // todo - write once tests for Position are in place.
}


void testPieceNextPositionsForQueen()
{
   // todo - write once tests for Position are in place.
}


void testPieceNextPositionsForRook()
{
   // todo - write once tests for Position are in place.
}


void testPieceNextPositionsForBishop()
{
   // todo - write once tests for Position are in place.
}


void testPieceNextPositionsForKnight()
{
   // todo - write once tests for Position are in place.
}


void testPieceNextPositionsForPawn()
{
   // todo - write once tests for Position are in place.
}


void testPieceEquality()
{
   {
      const std::string caseLabel = "Piece equality for equal pieces";

      VERIFY(Piece(Figure::King, Color::Black, "f4") ==
                Piece(Figure::King, Color::Black, "f4"),
             caseLabel);
      VERIFY(Piece(Figure::Queen, Color::White, "a1") ==
                Piece(Figure::Queen, Color::White, "a1"),
             caseLabel);
   }
   {
      const std::string caseLabel = "Piece equality for unequal pieces";

      VERIFY(!(Piece(Figure::King, Color::Black, "f4") ==
               Piece(Figure::Pawn, Color::Black, "f4")),
             caseLabel);
      VERIFY(!(Piece(Figure::King, Color::Black, "f4") ==
               Piece(Figure::King, Color::White, "f4")),
             caseLabel);
      VERIFY(!(Piece(Figure::Knight, Color::Black, "b4") ==
               Piece(Figure::Knight, Color::Black, "f4")),
             caseLabel);
      VERIFY(!(Piece(Figure::Knight, Color::Black, "f4") ==
               Piece(Figure::Knight, Color::Black, "f7")),
             caseLabel);
   }
}


void testPieceInequality()
{
   {
      const std::string caseLabel = "Piece inequality for equal pieces";

      VERIFY(!(Piece(Figure::King, Color::Black, "f4") !=
               Piece(Figure::King, Color::Black, "f4")),
             caseLabel);
      VERIFY(!(Piece(Figure::Queen, Color::White, "a1") !=
               Piece(Figure::Queen, Color::White, "a1")),
             caseLabel);
   }
   {
      const std::string caseLabel = "Piece inequality for unequal pieces";

      VERIFY(Piece(Figure::King, Color::Black, "f4") !=
                Piece(Figure::Pawn, Color::Black, "f4"),
             caseLabel);
      VERIFY(Piece(Figure::King, Color::Black, "f4") !=
                Piece(Figure::King, Color::White, "f4"),
             caseLabel);
      VERIFY(Piece(Figure::Knight, Color::Black, "b4") !=
                Piece(Figure::Knight, Color::Black, "f4"),
             caseLabel);
      VERIFY(Piece(Figure::Knight, Color::Black, "f4") !=
                Piece(Figure::Knight, Color::Black, "f7"),
             caseLabel);
   }
}


void testPieceEqualityWithOptionalPiece()
{
   {
      const std::string caseLabel =
         "Piece equality with optional piece as second operand";

      VERIFY(Piece(Figure::King, Color::Black, "f4") ==
                std::optional<Piece>(Piece(Figure::King, Color::Black, "f4")),
             caseLabel);
      VERIFY(!(Piece(Figure::Queen, Color::White, "a1") ==
               std::optional<Piece>(Piece(Figure::King, Color::White, "a1"))),
             caseLabel);
      VERIFY(!(Piece(Figure::Queen, Color::White, "a1") == std::nullopt), caseLabel);
   }
   {
      const std::string caseLabel = "Piece equality with optional piece as first operand";

      VERIFY(std::optional<Piece>(Piece(Figure::King, Color::Black, "f4")) ==
                Piece(Figure::King, Color::Black, "f4"),
             caseLabel);
      VERIFY(!(std::optional<Piece>(Piece(Figure::Queen, Color::White, "a1")) ==
               Piece(Figure::Queen, Color::Black, "a1")),
             caseLabel);
      VERIFY(!(std::nullopt == Piece(Figure::Queen, Color::White, "a1")), caseLabel);
   }
}


void testSwapPieces()
{
   {
      const std::string caseLabel = "Swap pieces";

      Piece a{Figure::Bishop, Color::Black, "g4"};
      Piece b{Figure::Rook, Color::White, "c6"};
      swap(a, b);
      VERIFY(a.figure() == Figure::Rook, caseLabel);
      VERIFY(a.color() == Color::White, caseLabel);
      VERIFY(a.coord() == "c6"_sq, caseLabel);
      VERIFY(b.figure() == Figure::Bishop, caseLabel);
      VERIFY(b.color() == Color::Black, caseLabel);
      VERIFY(b.coord() == "g4"_sq, caseLabel);
   }
}


void testPieceLiteral()
{
   {
      const std::string caseLabel = "Piece literal";

      VERIFY("Kwe1"_pc == Piece("Kwe1"), caseLabel);
      VERIFY("Qbc6"_pc == Piece("Qbc6"), caseLabel);
      VERIFY("bh7"_pc == Piece("bh7"), caseLabel);
   }
}


void testIsPawnOnInitialRank()
{
   {
      const std::string caseLabel = "isPawnOnInitialRank for white pawns on initial rank";

      for (const auto& coord :
           std::array<std::string, 8>{"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2"})
      {
         VERIFY(isPawnOnInitialRank(Piece(Figure::Pawn, Color::White, coord)), caseLabel);
      }
   }
   {
      const std::string caseLabel = "isPawnOnInitialRank for black pawns on initial rank";

      for (const auto& coord :
           std::array<std::string, 8>{"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7"})
      {
         VERIFY(isPawnOnInitialRank(Piece(Figure::Pawn, Color::Black, coord)), caseLabel);
      }
   }
   {
      const std::string caseLabel =
         "isPawnOnInitialRank for black pawns not on initial rank";

      VERIFY(!isPawnOnInitialRank(Piece(Figure::Pawn, Color::Black, Square("a2"))),
             caseLabel);
      VERIFY(!isPawnOnInitialRank(Piece(Figure::Pawn, Color::Black, Square("c3"))),
             caseLabel);
      VERIFY(!isPawnOnInitialRank(Piece(Figure::Pawn, Color::Black, Square("g6"))),
             caseLabel);
      VERIFY(!isPawnOnInitialRank(Piece(Figure::Pawn, Color::Black, Square("h8"))),
             caseLabel);
   }
   {
      const std::string caseLabel =
         "isPawnOnInitialRank for white pawns not on initial rank";

      VERIFY(!isPawnOnInitialRank(Piece(Figure::Pawn, Color::White, Square("f1"))),
             caseLabel);
      VERIFY(!isPawnOnInitialRank(Piece(Figure::Pawn, Color::White, Square("e3"))),
             caseLabel);
      VERIFY(!isPawnOnInitialRank(Piece(Figure::Pawn, Color::White, Square("d7"))),
             caseLabel);
      VERIFY(!isPawnOnInitialRank(Piece(Figure::Pawn, Color::White, Square("h8"))),
             caseLabel);
   }
   {
      const std::string caseLabel = "isPawnOnInitialRank for piece that is not a pawn";
      VERIFY(!isPawnOnInitialRank(Piece(Figure::Rook, Color::White, Square("b2"))),
             caseLabel);
   }
}


void testPawnDirection()
{
   {
      const std::string caseLabel = "pawnDirection for white pawn";
      VERIFY(pawnDirection(Piece(Figure::Pawn, Color::White, Square("f4"))) ==
                Offset(0, 1),
             caseLabel);
   }
   {
      const std::string caseLabel = "pawnDirection for black pawn";
      VERIFY(pawnDirection(Piece(Figure::Pawn, Color::Black, Square("g7"))) ==
                Offset(0, -1),
             caseLabel);
   }
   {
      const std::string caseLabel = "pawnDirection for piece that is not a pawn";
      VERIFY(pawnDirection(Piece(Figure::Knight, Color::Black, Square("g7"))) ==
                Offset(0, 0),
             caseLabel);
   }
}

} // namespace


///////////////////

void testPiece()
{
   testColorNegation();
   testNotateColor();
   testMakeColor();

   testNotateFigure();
   testMakeFigure();

   testPieceDefaultCtor();
   testPieceCtor();
   testPieceCtorWithLocationString();
   testPieceCtorWithNotation();
   testPieceCtorWithNotationAndColor();
   testPieceColor();
   testPieceCoordinate();
   testPieceIsFigure();
   testPieceNotate();
   testPieceMove();
   testPieceThreatenedSquaresForKing();
   testPieceThreatenedSquaresForQueen();
   testPieceThreatenedSquaresForRook();
   testPieceThreatenedSquaresForBishop();
   testPieceThreatenedSquaresForKnight();
   testPieceThreatenedSquaresForPawn();
   testPieceNextMovesForKing();
   testPieceNextMovesForQueen();
   testPieceNextMovesForRook();
   testPieceNextMovesForBishop();
   testPieceNextMovesForKnight();
   testPieceNextMovesForPawn();
   testPieceNextPositionsForKing();
   testPieceNextPositionsForQueen();
   testPieceNextPositionsForRook();
   testPieceNextPositionsForBishop();
   testPieceNextPositionsForKnight();
   testPieceNextPositionsForPawn();
   testPieceEquality();
   testPieceInequality();
   testPieceEqualityWithOptionalPiece();
   testSwapPieces();
   testPieceLiteral();

   testIsPawnOnInitialRank();
   testPawnDirection();
}
