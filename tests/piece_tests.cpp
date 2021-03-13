//
// Mar-2021, Michael Lindner
// MIT license
//
#include "piece_tests.h"
#include "piece.h"
#include "test_util.h"


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


void testDenotateColor()
{
   {
      const std::string caseLabel = "denotateColor from char";

      VERIFY(denotateColor('w') == Color::White, caseLabel);
      VERIFY(denotateColor('b') == Color::Black, caseLabel);
      // Invalid chars.
      VERIFY(denotateColor('a') == Color::White, caseLabel);
      VERIFY(denotateColor(' ') == Color::White, caseLabel);
   }
   {
      const std::string caseLabel = "denotateColor from string";

      VERIFY(denotateColor("w") == Color::White, caseLabel);
      VERIFY(denotateColor("b") == Color::Black, caseLabel);
      // At beginning.
      VERIFY(denotateColor("we5") == Color::White, caseLabel);
      VERIFY(denotateColor("bg8") == Color::Black, caseLabel);
      // Invalid strings.
      VERIFY(denotateColor(" ") == Color::White, caseLabel);
      VERIFY(denotateColor("aaaa") == Color::White, caseLabel);
      // Empty string.
      VERIFY(denotateColor("") == Color::White, caseLabel);
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


void testDenotateFigure()
{
   {
      const std::string caseLabel = "denotateFigure from char";

      VERIFY(denotateFigure('K') == Figure::King, caseLabel);
      VERIFY(denotateFigure('Q') == Figure::Queen, caseLabel);
      VERIFY(denotateFigure('R') == Figure::Rook, caseLabel);
      VERIFY(denotateFigure('B') == Figure::Bishop, caseLabel);
      VERIFY(denotateFigure('N') == Figure::Knight, caseLabel);
      // Invalid chars.
      VERIFY(denotateFigure('a') == Figure::Pawn, caseLabel);
      VERIFY(denotateFigure(' ') == Figure::Pawn, caseLabel);
   }
   {
      const std::string caseLabel = "denotateFigure from string";

      VERIFY(denotateFigure("K") == Figure::King, caseLabel);
      VERIFY(denotateFigure("Q") == Figure::Queen, caseLabel);
      VERIFY(denotateFigure("R") == Figure::Rook, caseLabel);
      VERIFY(denotateFigure("B") == Figure::Bishop, caseLabel);
      VERIFY(denotateFigure("N") == Figure::Knight, caseLabel);
      VERIFY(denotateFigure("") == Figure::Pawn, caseLabel);
      // At beginning.
      VERIFY(denotateFigure("Kwe5") == Figure::King, caseLabel);
      VERIFY(denotateFigure("Rbg8") == Figure::Rook, caseLabel);
      // Invalid strings.
      VERIFY(denotateFigure(" ") == Figure::Pawn, caseLabel);
      VERIFY(denotateFigure("aaaa") == Figure::Pawn, caseLabel);
      // Empty string.
      VERIFY(denotateFigure("") == Figure::Pawn, caseLabel);
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


void testDenotatePieceWithColor()
{
   {
      const std::string caseLabel = "denotatePiece with color in notation";

      VERIFY(denotatePiece("Bbg4") == Piece(Figure::Bishop, Color::Black, "g4"),
             caseLabel);
      VERIFY(denotatePiece("Kwh8") == Piece(Figure::King, Color::White, "h8"), caseLabel);
      VERIFY(denotatePiece("wh8") == Piece(Figure::Pawn, Color::White, "h8"), caseLabel);
      VERIFY(denotatePiece("bc4") == Piece(Figure::Pawn, Color::Black, "c4"), caseLabel);
   }
   {
      const std::string caseLabel =
         "denotatePiece with color in notation for invalid notation";

      VERIFY(denotatePiece("Tbg4") == Piece(Figure::Pawn, Color::White, Square()),
             caseLabel);
      VERIFY(denotatePiece("Kqh8") == Piece(Figure::King, Color::White, "h8"), caseLabel);
      VERIFY(denotatePiece("Rwr0") == Piece(Figure::Rook, Color::White, Square()),
             caseLabel);
   }
}


void testDenotatePieceWithoutColor()
{
   {
      const std::string caseLabel = "denotatePiece without color in notation";

      VERIFY(denotatePiece("Bg4", Color::Black) ==
                Piece(Figure::Bishop, Color::Black, "g4"),
             caseLabel);
      VERIFY(denotatePiece("Kh8", Color::White) ==
                Piece(Figure::King, Color::White, "h8"),
             caseLabel);
      VERIFY(denotatePiece("h8", Color::White) == Piece(Figure::Pawn, Color::White, "h8"),
             caseLabel);
      VERIFY(denotatePiece("c4", Color::Black) == Piece(Figure::Pawn, Color::Black, "c4"),
             caseLabel);
   }
   {
      const std::string caseLabel =
         "denotatePiece without color in notation for invalid notation";

      VERIFY(denotatePiece("Tg4", Color::White) ==
                Piece(Figure::Pawn, Color::White, Square()),
             caseLabel);
      VERIFY(denotatePiece("Rr0", Color::Black) ==
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
   testDenotateColor();

   testNotateFigure();
   testDenotateFigure();

   testPieceDefaultCtor();
   testPieceCtor();
   testPieceCtorWithLocationString();
   testPieceColor();
   testPieceLocation();
   testPieceIsFigure();
   testPieceNotate();
   testPieceNotateWithColor();
   testPieceMove();
   testPieceEquality();
   testPieceInequality();
   testPieceEqualityWithOptionalPiece();
   testSwapPieces();
   testDenotatePieceWithColor();
   testDenotatePieceWithoutColor();

   testIsPawnOnInitialRank();
   testPawnDirection();
}
