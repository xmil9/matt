//
// Mar-2021, Michael Lindner
// MIT license
//
#include "square_tests.h"
#include "square.h"
#include "test_util.h"


namespace
{
///////////////////

void testSquareDefaultCtor()
{
   {
      const std::string caseLabel = "Square default ctor";

      const Square s;
      VERIFY(!s, caseLabel);
   }
}


void testSquareCharCtor()
{
   {
      const std::string caseLabel = "Square ctor for valid characters";

      for (char file = 'a'; file <= 'h'; ++file)
         for (char rank = '1'; rank <= '8'; ++rank)
            VERIFY(Square(file, rank).operator bool(), caseLabel);
   }
   {
      const std::string caseLabel = "Square ctor for invalid characters";

      VERIFY(!Square('i', '1').operator bool(), caseLabel);
      VERIFY(!Square('a', '9').operator bool(), caseLabel);
      VERIFY(!Square('A', '1').operator bool(), caseLabel);
      VERIFY(!Square('a', '0').operator bool(), caseLabel);
      VERIFY(!Square('1', 'a').operator bool(), caseLabel);
      VERIFY(!Square('*', '8').operator bool(), caseLabel);
      VERIFY(!Square('b', '-').operator bool(), caseLabel);
   }
   {
      const std::string caseLabel = "Square ctor for zero character";

      VERIFY(!Square(static_cast<char>(0), static_cast<char>(0)).operator bool(),
             caseLabel);
   }
}


void testSquareIntegerCtor()
{
   {
      const std::string caseLabel = "Square ctor for integers";

      for (int file = 'a'; file <= 'h'; ++file)
         for (int rank = '1'; rank <= '8'; ++rank)
            VERIFY(Square(file, rank).operator bool(), caseLabel);
   }
   {
      const std::string caseLabel = "Square ctor for invalid integers";

      VERIFY(!Square(4, 7).operator bool(), caseLabel);
      VERIFY(!Square(1000, 1000).operator bool(), caseLabel);
      VERIFY(!Square(-65, -static_cast<int>('1')).operator bool(), caseLabel);
   }
   {
      const std::string caseLabel = "Square ctor for zero integer";

      VERIFY(!Square(0, 0).operator bool(), caseLabel);
   }
}


void testSquareStringCtor()
{
   {
      const std::string caseLabel = "Square ctor for string";

      VERIFY(Square("a1").file() == 'a', caseLabel);
      VERIFY(Square("a1").rank() == '1', caseLabel);
      VERIFY(Square("h8").file() == 'h', caseLabel);
      VERIFY(Square("h8").rank() == '8', caseLabel);
   }
   {
      const std::string caseLabel = "Square ctor for invalid string";

      VERIFY(Square("z1").file() == 0, caseLabel);
      VERIFY(Square("z1").rank() == 0, caseLabel);
      VERIFY(Square("h9").file() == 0, caseLabel);
      VERIFY(Square("h9").rank() == 0, caseLabel);
   }
   {
      const std::string caseLabel = "Square ctor for longer string";

      VERIFY(Square("c5345").file() == 'c', caseLabel);
      VERIFY(Square("c5345").rank() == '5', caseLabel);
   }
}


void testSquareFile()
{
   {
      const std::string caseLabel = "Square::file for valid values";

      for (char file = 'a'; file <= 'h'; ++file)
         VERIFY(Square(file, '1').file() == file, caseLabel);
   }
   {
      const std::string caseLabel = "Square::file for invalid values";

      VERIFY(Square('j', '4').file() == 0, caseLabel);
      VERIFY(Square('A', '7').file() == 0, caseLabel);
   }
   {
      const std::string caseLabel = "Square::file for zero value";

      VERIFY(Square(static_cast<char>(0), '4').file() == 0, caseLabel);
   }
}


void testSquareRank()
{
   {
      const std::string caseLabel = "Square::rank for valid values";

      for (char rank = '1'; rank <= '8'; ++rank)
         VERIFY(Square('d', rank).rank() == rank, caseLabel);
   }
   {
      const std::string caseLabel = "Square::rank for invalid values";

      VERIFY(Square('a', 'a').rank() == 0, caseLabel);
      VERIFY(Square('f', '9').rank() == 0, caseLabel);
   }
   {
      const std::string caseLabel = "Square::rank for zero value";

      VERIFY(Square('g', static_cast<char>(0)).rank() == 0, caseLabel);
   }
}


void testSquareNotate()
{
   {
      const std::string caseLabel = "Square::notate for valid squares";

      VERIFY(Square('a', '1').notate() == "a1", caseLabel);
      VERIFY(Square('b', '1').notate() == "b1", caseLabel);
      VERIFY(Square('c', '1').notate() == "c1", caseLabel);
      VERIFY(Square('d', '1').notate() == "d1", caseLabel);
      VERIFY(Square('e', '1').notate() == "e1", caseLabel);
      VERIFY(Square('f', '1').notate() == "f1", caseLabel);
      VERIFY(Square('g', '1').notate() == "g1", caseLabel);
      VERIFY(Square('h', '1').notate() == "h1", caseLabel);
      VERIFY(Square('a', '1').notate() == "a1", caseLabel);
      VERIFY(Square('a', '2').notate() == "a2", caseLabel);
      VERIFY(Square('a', '3').notate() == "a3", caseLabel);
      VERIFY(Square('a', '4').notate() == "a4", caseLabel);
      VERIFY(Square('a', '5').notate() == "a5", caseLabel);
      VERIFY(Square('a', '6').notate() == "a6", caseLabel);
      VERIFY(Square('a', '7').notate() == "a7", caseLabel);
      VERIFY(Square('a', '8').notate() == "a8", caseLabel);
   }
   {
      const std::string caseLabel = "Square::notate for invalid values";

      VERIFY(Square('t', '0').notate() == "", caseLabel);
   }
   {
      const std::string caseLabel = "Square::notate for default square";

      VERIFY(Square().notate() == "", caseLabel);
   }
}


void testSquareOperatorBool()
{
   {
      const std::string caseLabel = "Square::operator bool() for valid squares";

      VERIFY(Square('a', '1').operator bool(), caseLabel);
      VERIFY(Square('h', '8').operator bool(), caseLabel);
   }
   {
      const std::string caseLabel = "Square::operator bool() for invalid squares";

      VERIFY(Square('t', '0').operator bool() == false, caseLabel);
   }
   {
      const std::string caseLabel = "Square::operator bool() for default square";

      VERIFY(Square().operator bool() == false, caseLabel);
   }
}


void testSwapSquares()
{
   {
      const std::string caseLabel = "swap for Square objects";

      Square a{'c', '3'};
      Square b{'g', '7'};
      swap(a, b);
      VERIFY(a.file() == 'g' && a.rank() == '7', caseLabel);
      VERIFY(b.file() == 'c' && b.rank() == '3', caseLabel);
   }
}


void testMakeSquare()
{
   {
      const std::string caseLabel = "makeSquare for valid notations";

      VERIFY(makeSquare("a1") == Square('a', '1'), caseLabel);
      VERIFY(makeSquare("b1") == Square('b', '1'), caseLabel);
      VERIFY(makeSquare("c1") == Square('c', '1'), caseLabel);
      VERIFY(makeSquare("d1") == Square('d', '1'), caseLabel);
      VERIFY(makeSquare("e1") == Square('e', '1'), caseLabel);
      VERIFY(makeSquare("f1") == Square('f', '1'), caseLabel);
      VERIFY(makeSquare("g1") == Square('g', '1'), caseLabel);
      VERIFY(makeSquare("h1") == Square('h', '1'), caseLabel);
      VERIFY(makeSquare("a1") == Square('a', '1'), caseLabel);
      VERIFY(makeSquare("a2") == Square('a', '2'), caseLabel);
      VERIFY(makeSquare("a3") == Square('a', '3'), caseLabel);
      VERIFY(makeSquare("a4") == Square('a', '4'), caseLabel);
      VERIFY(makeSquare("a5") == Square('a', '5'), caseLabel);
      VERIFY(makeSquare("a6") == Square('a', '6'), caseLabel);
      VERIFY(makeSquare("a7") == Square('a', '7'), caseLabel);
      VERIFY(makeSquare("a8") == Square('a', '8'), caseLabel);
   }
   {
      const std::string caseLabel =
         "makeSquare for strings starting with valid notations";

      VERIFY(makeSquare("a1dbskuu") == Square('a', '1'), caseLabel);
      VERIFY(makeSquare("h873kHH") == Square('h', '8'), caseLabel);
   }
   {
      const std::string caseLabel =
         "makeSquare for invalid notations with valid length";

      VERIFY(makeSquare("i1") == Square(), caseLabel);
      VERIFY(makeSquare("a9") == Square(), caseLabel);
      VERIFY(makeSquare("B6") == Square(), caseLabel);
      VERIFY(makeSquare("h*") == Square(), caseLabel);
      VERIFY(makeSquare("4d") == Square(), caseLabel);
   }
   {
      const std::string caseLabel =
         "makeSquare for invalid notations with invalid length";

      VERIFY(makeSquare("1") == Square(), caseLabel);
      VERIFY(makeSquare("a") == Square(), caseLabel);
      VERIFY(makeSquare("B6skd8") == Square(), caseLabel);
   }
   {
      const std::string caseLabel = "makeSquare for empty string";

      VERIFY(makeSquare("") == Square(), caseLabel);
   }
}


void testSquareEquality()
{
   {
      const std::string caseLabel = "Square equality for equal squares";

      VERIFY(Square('c', '3') == Square('c', '3'), caseLabel);
   }
   {
      const std::string caseLabel = "Square equality for unequal squares";

      VERIFY(!(Square('c', '3') == Square('f', '3')), caseLabel);
      VERIFY(!(Square('c', '3') == Square('c', '4')), caseLabel);
   }
   {
      const std::string caseLabel = "Square equality for default square";

      VERIFY(Square() == Square(), caseLabel);
      VERIFY(!(Square() == Square('c', '4')), caseLabel);
   }
}


void testSquareInequality()
{
   {
      const std::string caseLabel = "Square inequality for equal squares";

      VERIFY(!(Square('c', '3') != Square('c', '3')), caseLabel);
   }
   {
      const std::string caseLabel = "Square inequality for unequal squares";

      VERIFY(Square('c', '3') != Square('f', '3'), caseLabel);
      VERIFY(Square('c', '3') != Square('c', '4'), caseLabel);
   }
   {
      const std::string caseLabel = "Square inequality for default square";

      VERIFY(!(Square() != Square()), caseLabel);
      VERIFY(Square() != Square('c', '4'), caseLabel);
   }
}


void testOffsetDefaultCtor()
{
   {
      const std::string caseLabel = "Offset default ctor";

      const Offset off;
      VERIFY(off.df() == 0, caseLabel);
      VERIFY(off.dr() == 0, caseLabel);
   }
}


void testOffsetIntegerCtor()
{
   {
      const std::string caseLabel = "Offset ctor for integers";

      VERIFY(Offset(0, 0).df() == 0 && Offset(0, 0).dr() == 0, caseLabel);
      VERIFY(Offset(1, 1).df() == 1 && Offset(1, 1).dr() == 1, caseLabel);
      VERIFY(Offset(-1, -1).df() == -1 && Offset(-1, -1).dr() == -1, caseLabel);
      VERIFY(Offset(-5, 5).df() == -5 && Offset(-5, 5).dr() == 5, caseLabel);
   }
}


void testSwapOffsets()
{
   {
      const std::string caseLabel = "swap() for Offset objects";

      Offset a{1, 2};
      Offset b{3, 4};
      swap(a, b);
      VERIFY(a.df() == 3 && a.dr() == 4, caseLabel);
      VERIFY(b.df() == 1 && b.dr() == 2, caseLabel);
   }
}


void testOffsetEquality()
{
   {
      const std::string caseLabel = "Offset equality for equal offsets";

      VERIFY(Offset(1, 2) == Offset(1, 2), caseLabel);
   }
   {
      const std::string caseLabel = "Offset equality for unequal offsets";

      VERIFY(!(Offset(1, 2) == Offset(2, 2)), caseLabel);
      VERIFY(!(Offset(1, 2) == Offset(1, 1)), caseLabel);
   }
   {
      const std::string caseLabel = "Offset equality for default offset";

      VERIFY(Offset() == Offset(), caseLabel);
      VERIFY(!(Offset() == Offset(1, 2)), caseLabel);
   }
}


void testOffsetInequality()
{
   {
      const std::string caseLabel = "Offset inequality for equal offsets";

      VERIFY(!(Offset(1, 2) != Offset(1, 2)), caseLabel);
   }
   {
      const std::string caseLabel = "Offset inequality for unequal offsets";

      VERIFY(Offset(1, 2) != Offset(2, 2), caseLabel);
      VERIFY(Offset(1, 2) != Offset(1, 1), caseLabel);
   }
   {
      const std::string caseLabel = "Offset inequality for default offset";

      VERIFY(!(Offset() != Offset()), caseLabel);
      VERIFY(Offset() != Offset(1, 2), caseLabel);
   }
}


void testOffsetMultiplicationWithScalar()
{
   {
      const std::string caseLabel = "Offset multiplication with scalar as first operand";

      VERIFY(2 * Offset(1, 2) == Offset(2, 4), caseLabel);
      VERIFY(-1 * Offset(1, 2) == Offset(-1, -2), caseLabel);
      VERIFY(0 * Offset(1, 2) == Offset(), caseLabel);
   }
   {
      const std::string caseLabel = "Offset multiplication with scalar as second operand";

      VERIFY(Offset(1, 2) * 2 == Offset(2, 4), caseLabel);
      VERIFY(Offset(1, 2) * -1 == Offset(-1, -2), caseLabel);
      VERIFY(Offset(1, 2) * 0 == Offset(), caseLabel);
   }
}


void testSquareOffsetAddition()
{
   {
      const std::string caseLabel =
         "Square and offset addition with square as first operand";

      VERIFY(Square('b', '2') + Offset(1, 1) == std::make_optional<Square>('c', '3'),
             caseLabel);
      VERIFY(Square('b', '2') + Offset(4, 5) == std::make_optional<Square>('f', '7'),
             caseLabel);
      VERIFY(Square('g', '6') + Offset(1, 2) == std::make_optional<Square>('h', '8'),
             caseLabel);
      VERIFY(Square('g', '6') + Offset(-1, -2) == std::make_optional<Square>('f', '4'),
             caseLabel);
      VERIFY(Square('g', '6') + Offset(3, 1) == std::nullopt, caseLabel);
      VERIFY(Square('g', '6') + Offset(1, 5) == std::nullopt, caseLabel);
      VERIFY(Square('d', '6') + Offset(-5, -1) == std::nullopt, caseLabel);
      VERIFY(Square('d', '3') + Offset(-1, -4) == std::nullopt, caseLabel);
      VERIFY(Square('d', '3') + Offset(0, 0) == std::make_optional<Square>('d', '3'),
             caseLabel);
   }
}


void testOffsetSquareAddition()
{
   {
      const std::string caseLabel =
         "Square and offset addition with square as second operand";

      VERIFY(Offset(1, 1) + Square('b', '2') == std::make_optional<Square>('c', '3'),
             caseLabel);
      VERIFY(Offset(4, 5) + Square('b', '2') == std::make_optional<Square>('f', '7'),
             caseLabel);
      VERIFY(Offset(1, 2) + Square('g', '6') == std::make_optional<Square>('h', '8'),
             caseLabel);
      VERIFY(Offset(-1, -2) + Square('g', '6') == std::make_optional<Square>('f', '4'),
             caseLabel);
      VERIFY(Offset(3, 1) + Square('g', '6') == std::nullopt, caseLabel);
      VERIFY(Offset(1, 5) + Square('g', '6') == std::nullopt, caseLabel);
      VERIFY(Offset(-5, -1) + Square('d', '6') == std::nullopt, caseLabel);
      VERIFY(Offset(-1, -4) + Square('d', '3') == std::nullopt, caseLabel);
      VERIFY(Offset(0, 0) + Square('d', '3') == std::make_optional<Square>('d', '3'),
             caseLabel);
   }
}


void testOptionalSquareOffsetAddition()
{
   {
      const std::string caseLabel =
         "std::optional<Square> and offset addition with square as first operand";

      VERIFY(std::make_optional<Square>('b', '2') + Offset(1, 1) ==
                std::make_optional<Square>('c', '3'),
             caseLabel);
      VERIFY(std::make_optional<Square>('b', '2') + Offset(4, 5) ==
                std::make_optional<Square>('f', '7'),
             caseLabel);
      VERIFY(std::make_optional<Square>('g', '6') + Offset(1, 2) ==
                std::make_optional<Square>('h', '8'),
             caseLabel);
      VERIFY(std::make_optional<Square>('g', '6') + Offset(-1, -2) ==
                std::make_optional<Square>('f', '4'),
             caseLabel);
      VERIFY(std::make_optional<Square>('g', '6') + Offset(3, 1) == std::nullopt,
             caseLabel);
      VERIFY(std::make_optional<Square>('g', '6') + Offset(1, 5) == std::nullopt,
             caseLabel);
      VERIFY(std::make_optional<Square>('d', '6') + Offset(-5, -1) == std::nullopt,
             caseLabel);
      VERIFY(std::make_optional<Square>('d', '3') + Offset(-1, -4) == std::nullopt,
             caseLabel);
      VERIFY(std::nullopt + Offset(1, 4) == std::nullopt, caseLabel);
      VERIFY(std::make_optional<Square>('d', '3') + Offset(0, 0) ==
                std::make_optional<Square>('d', '3'),
             caseLabel);
   }
}


void testOffsetOptionalSquareAddition()
{
   {
      const std::string caseLabel =
         "std::optional<Square> and offset addition with square as second operand";

      VERIFY(Offset(4, 5) + std::make_optional<Square>('b', '2') ==
                std::make_optional<Square>('f', '7'),
             caseLabel);
      VERIFY(Offset(3, 1) + std::make_optional<Square>('g', '6') == std::nullopt,
             caseLabel);
      VERIFY(Offset(1, 4) + std::nullopt == std::nullopt, caseLabel);
      VERIFY(Offset(0, 0) + std::make_optional<Square>('d', '3') ==
                std::make_optional<Square>('d', '3'),
             caseLabel);
   }
}

} // namespace


///////////////////

void testSquare()
{
   testSquareDefaultCtor();
   testSquareCharCtor();
   testSquareIntegerCtor();
   testSquareStringCtor();
   testSquareFile();
   testSquareRank();
   testSquareNotate();
   testSquareOperatorBool();
   testSwapSquares();
   testMakeSquare();
   testSquareEquality();
   testSquareInequality();

   testOffsetDefaultCtor();
   testOffsetIntegerCtor();
   testSwapOffsets();
   testOffsetEquality();
   testOffsetInequality();
   testOffsetMultiplicationWithScalar();

   testSquareOffsetAddition();
   testOffsetSquareAddition();
   testOptionalSquareOffsetAddition();
   testOffsetOptionalSquareAddition();
}
