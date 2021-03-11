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
}
