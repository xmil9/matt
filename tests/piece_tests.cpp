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
#include <iterator>
#include <vector>


namespace
{
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
      VERIFY(p.isFigure(Figure::Pawn), caseLabel);
      VERIFY(p.color() == Color::White, caseLabel);
      VERIFY(p.location() == Square(), caseLabel);
   }
}


void testPieceCtor()
{
   {
      const std::string caseLabel = "Piece ctor";

      const Piece p{Figure::King, Color::Black, Square{'c', '5'}};
      VERIFY(p.isFigure(Figure::King), caseLabel);
      VERIFY(p.color() == Color::Black, caseLabel);
      VERIFY(p.location() == Square('c', '5'), caseLabel);
   }
}


void testPieceCtorWithLocationString()
{
   {
      const std::string caseLabel = "Piece ctor with location string";

      const Piece p{Figure::King, Color::Black, "c5"};
      VERIFY(p.isFigure(Figure::King), caseLabel);
      VERIFY(p.color() == Color::Black, caseLabel);
      VERIFY(p.location() == Square('c', '5'), caseLabel);
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


void testPieceLocation()
{
   {
      const std::string caseLabel = "Piece::location";

      VERIFY(Piece(Figure::King, Color::Black, "f4").location() == Square('f', '4'),
             caseLabel);
      VERIFY(Piece(Figure::Pawn, Color::White, "a1").location() == Square('a', '1'),
             caseLabel);
   }
}


void testPieceIsFigure()
{
   {
      const std::string caseLabel = "Piece::isFigure";

      VERIFY(Piece(Figure::King, Color::Black, "f4").isFigure(Figure::King), caseLabel);
      VERIFY(!Piece(Figure::King, Color::Black, "f4").isFigure(Figure::Queen), caseLabel);
      VERIFY(Piece(Figure::Pawn, Color::White, "h1").isFigure(Figure::Pawn), caseLabel);
      VERIFY(!Piece(Figure::Pawn, Color::White, "b7").isFigure(Figure::Rook), caseLabel);
   }
}


void testPieceNotate()
{
   {
      const std::string caseLabel = "Piece::notate";

      VERIFY(Piece(Figure::King, Color::Black, "f4").notate() == "Kf4", caseLabel);
      VERIFY(Piece(Figure::Queen, Color::Black, "a2").notate() == "Qa2", caseLabel);
      VERIFY(Piece(Figure::Rook, Color::White, "h8").notate() == "Rh8", caseLabel);
      VERIFY(Piece(Figure::Bishop, Color::White, "c6").notate() == "Bc6", caseLabel);
      VERIFY(Piece(Figure::Knight, Color::Black, "b8").notate() == "Nb8", caseLabel);
      VERIFY(Piece(Figure::Pawn, Color::White, "b7").notate() == "b7", caseLabel);
   }
}


void testPieceNotateWithColor()
{
   {
      const std::string caseLabel = "Piece::notateWithColor";

      VERIFY(Piece(Figure::King, Color::Black, "f4").notateWithColor() == "Kbf4",
             caseLabel);
      VERIFY(Piece(Figure::Queen, Color::Black, "a2").notateWithColor() == "Qba2",
             caseLabel);
      VERIFY(Piece(Figure::Rook, Color::White, "h8").notateWithColor() == "Rwh8",
             caseLabel);
      VERIFY(Piece(Figure::Bishop, Color::White, "c6").notateWithColor() == "Bwc6",
             caseLabel);
      VERIFY(Piece(Figure::Knight, Color::Black, "b8").notateWithColor() == "Nbb8",
             caseLabel);
      VERIFY(Piece(Figure::Pawn, Color::White, "b7").notateWithColor() == "wb7",
             caseLabel);
   }
}


void testPieceMove()
{
   {
      const std::string caseLabel = "Piece::move";

      VERIFY(Piece(Figure::King, Color::Black, "f4").move(Square("g3")).location() ==
                Square("g3"),
             caseLabel);
   }
   {
      const std::string caseLabel = "Piece::move to invalid field";

      VERIFY(Piece(Figure::King, Color::Black, "f4").move(Square("k3")).location() ==
                Square(),
             caseLabel);
   }
   {
      const std::string caseLabel = "Piece::move that is invalid for piece";

      // No checking for illegal moves.
      VERIFY(Piece(Figure::King, Color::Black, "f4").move(Square("a1")).location() ==
                Square("a1"),
             caseLabel);
   }
}


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
                  [&piece, &pos](const std::string& loc) {
                     const Square to{loc};
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
         Piece piece = makePiece(test.piece);
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
         Piece piece = makePiece(test.piece);
         std::vector<Piece> all{piece};
         std::transform(begin(test.otherPieces), end(test.otherPieces),
                        std::back_inserter(all),
                        [](const std::string& notation) { return makePiece(notation); });
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
         {"Kwd4", {"Bbg4", "bc2"}, {"c3", "c4", "c5", "d3", "d5", "e3", "e4", "e5"}},
         // Blocking some squares.
         {"Kwd4", {"Bbc4", "be3"}, {"c3", "c4", "c5", "d3", "d5", "e3", "e4", "e5"}},
         // Blocking all squares.
         {"Kba1", {"wa2", "Rwb2", "Qwb1"}, {"a2", "b2", "b1"}},
      };
      for (const auto& test : testCases)
      {
         Piece piece = makePiece(test.piece);
         std::vector<Piece> all{piece};
         std::transform(begin(test.otherPieces), end(test.otherPieces),
                        std::back_inserter(all),
                        [](const std::string& notation) { return makePiece(notation); });
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
         Piece piece = makePiece(test.piece);
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
         Piece piece = makePiece(test.piece);
         std::vector<Piece> all{piece};
         std::transform(begin(test.otherPieces), end(test.otherPieces),
                        std::back_inserter(all),
                        [](const std::string& notation) { return makePiece(notation); });
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
         Piece piece = makePiece(test.piece);
         std::vector<Piece> all{piece};
         std::transform(begin(test.otherPieces), end(test.otherPieces),
                        std::back_inserter(all),
                        [](const std::string& notation) { return makePiece(notation); });
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
         Piece piece = makePiece(test.piece);
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
         Piece piece = makePiece(test.piece);
         std::vector<Piece> all{piece};
         std::transform(begin(test.otherPieces), end(test.otherPieces),
                        std::back_inserter(all),
                        [](const std::string& notation) { return makePiece(notation); });
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
         Piece piece = makePiece(test.piece);
         std::vector<Piece> all{piece};
         std::transform(begin(test.otherPieces), end(test.otherPieces),
                        std::back_inserter(all),
                        [](const std::string& notation) { return makePiece(notation); });
         Position pos(all);
         VERIFY(verifyNextMoves(piece.nextMoves(pos), piece, pos, test.nextLocations),
                caseLabel);
      }
   }
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
      VERIFY(a.isFigure(Figure::Rook), caseLabel);
      VERIFY(a.color() == Color::White, caseLabel);
      VERIFY(a.location() == Square("c6"), caseLabel);
      VERIFY(b.isFigure(Figure::Bishop), caseLabel);
      VERIFY(b.color() == Color::Black, caseLabel);
      VERIFY(b.location() == Square("g4"), caseLabel);
   }
}


void testMakePieceWithColor()
{
   {
      const std::string caseLabel = "makePiece with color in notation";

      VERIFY(makePiece("Bbg4") == Piece(Figure::Bishop, Color::Black, "g4"), caseLabel);
      VERIFY(makePiece("Kwh8") == Piece(Figure::King, Color::White, "h8"), caseLabel);
      VERIFY(makePiece("wh8") == Piece(Figure::Pawn, Color::White, "h8"), caseLabel);
      VERIFY(makePiece("bc4") == Piece(Figure::Pawn, Color::Black, "c4"), caseLabel);
   }
   {
      const std::string caseLabel =
         "makePiece with color in notation for invalid notation";

      VERIFY(makePiece("Tbg4") == Piece(Figure::Pawn, Color::White, Square()), caseLabel);
      VERIFY(makePiece("Kqh8") == Piece(Figure::King, Color::White, "h8"), caseLabel);
      VERIFY(makePiece("Rwr0") == Piece(Figure::Rook, Color::White, Square()), caseLabel);
   }
}


void testMakePieceWithoutColor()
{
   {
      const std::string caseLabel = "makePiece without color in notation";

      VERIFY(makePiece("Bg4", Color::Black) == Piece(Figure::Bishop, Color::Black, "g4"),
             caseLabel);
      VERIFY(makePiece("Kh8", Color::White) == Piece(Figure::King, Color::White, "h8"),
             caseLabel);
      VERIFY(makePiece("h8", Color::White) == Piece(Figure::Pawn, Color::White, "h8"),
             caseLabel);
      VERIFY(makePiece("c4", Color::Black) == Piece(Figure::Pawn, Color::Black, "c4"),
             caseLabel);
   }
   {
      const std::string caseLabel =
         "makePiece without color in notation for invalid notation";

      VERIFY(makePiece("Tg4", Color::White) ==
                Piece(Figure::Pawn, Color::White, Square()),
             caseLabel);
      VERIFY(makePiece("Rr0", Color::Black) ==
                Piece(Figure::Rook, Color::Black, Square()),
             caseLabel);
   }
}


void testIsPawnOnInitialRank()
{
   {
      const std::string caseLabel = "isPawnOnInitialRank for white pawns on initial rank";

      for (char file = 'a'; file <= 'h'; ++file)
         VERIFY(isPawnOnInitialRank(Piece(Figure::Pawn, Color::White, Square(file, '2'))),
                caseLabel);
   }
   {
      const std::string caseLabel = "isPawnOnInitialRank for black pawns on initial rank";

      for (char file = 'a'; file <= 'h'; ++file)
         VERIFY(isPawnOnInitialRank(Piece(Figure::Pawn, Color::Black, Square(file, '7'))),
                caseLabel);
   }
   {
      const std::string caseLabel =
         "isPawnOnInitialRank for black pawns not on initial rank";

      for (char rank : std::vector<char>{'1', '2', '3', '4', '5', '6', '8'})
         VERIFY(
            !isPawnOnInitialRank(Piece(Figure::Pawn, Color::Black, Square('a', rank))),
            caseLabel);
   }
   {
      const std::string caseLabel =
         "isPawnOnInitialRank for white pawns not on initial rank";
      for (char rank : std::vector<char>{'1', '3', '4', '5', '6', '7', '8'})
         VERIFY(
            !isPawnOnInitialRank(Piece(Figure::Pawn, Color::White, Square('f', rank))),
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
   testPieceColor();
   testPieceLocation();
   testPieceIsFigure();
   testPieceNotate();
   testPieceNotateWithColor();
   testPieceMove();
   testPieceNextMovesForKing();
   testPieceNextMovesForQueen();
   testPieceNextMovesForRook();
   testPieceEquality();
   testPieceInequality();
   testPieceEqualityWithOptionalPiece();
   testSwapPieces();
   testMakePieceWithColor();
   testMakePieceWithoutColor();

   testIsPawnOnInitialRank();
   testPawnDirection();
}
