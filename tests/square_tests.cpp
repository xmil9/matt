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
         {
            std::string coord(1, file);
            coord += rank;
            VERIFY(Square(coord).operator bool(), caseLabel);
         }
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

      VERIFY(!Square("i1").operator bool(), caseLabel);
      VERIFY(!Square("a9").operator bool(), caseLabel);
      VERIFY(!Square("A1").operator bool(), caseLabel);
      VERIFY(!Square("a0").operator bool(), caseLabel);
      VERIFY(!Square("1a").operator bool(), caseLabel);
      VERIFY(!Square("*8").operator bool(), caseLabel);
      VERIFY(!Square("b-").operator bool(), caseLabel);
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

      VERIFY(Square("a1").file() == 'a', caseLabel);
      VERIFY(Square("b1").file() == 'b', caseLabel);
      VERIFY(Square("c1").file() == 'c', caseLabel);
      VERIFY(Square("d1").file() == 'd', caseLabel);
      VERIFY(Square("e1").file() == 'e', caseLabel);
      VERIFY(Square("f1").file() == 'f', caseLabel);
      VERIFY(Square("g1").file() == 'g', caseLabel);
      VERIFY(Square("h1").file() == 'h', caseLabel);
   }
   {
      const std::string caseLabel = "Square::file for invalid values";

      VERIFY(Square("j4").file() == 0, caseLabel);
      VERIFY(Square("A7").file() == 0, caseLabel);
   }
   {
      const std::string caseLabel = "Square::file for default value";

      VERIFY(Square().file() == 0, caseLabel);
   }
}


void testSquareRank()
{
   {
      const std::string caseLabel = "Square::rank for valid values";


      VERIFY(Square("e1").rank() == '1', caseLabel);
      VERIFY(Square("e2").rank() == '2', caseLabel);
      VERIFY(Square("e3").rank() == '3', caseLabel);
      VERIFY(Square("e4").rank() == '4', caseLabel);
      VERIFY(Square("e5").rank() == '5', caseLabel);
      VERIFY(Square("e6").rank() == '6', caseLabel);
      VERIFY(Square("e7").rank() == '7', caseLabel);
      VERIFY(Square("e8").rank() == '8', caseLabel);
   }
   {
      const std::string caseLabel = "Square::rank for invalid values";

      VERIFY(Square("aa").rank() == 0, caseLabel);
      VERIFY(Square("f9").rank() == 0, caseLabel);
   }
   {
      const std::string caseLabel = "Square::rank for default value";

      VERIFY(Square().rank() == 0, caseLabel);
   }
}


void testSquareNotate()
{
   {
      const std::string caseLabel = "Square::notate for valid squares";

      VERIFY(Square("a1").notate() == "a1", caseLabel);
      VERIFY(Square("b1").notate() == "b1", caseLabel);
      VERIFY(Square("c1").notate() == "c1", caseLabel);
      VERIFY(Square("d1").notate() == "d1", caseLabel);
      VERIFY(Square("e1").notate() == "e1", caseLabel);
      VERIFY(Square("f1").notate() == "f1", caseLabel);
      VERIFY(Square("g1").notate() == "g1", caseLabel);
      VERIFY(Square("h1").notate() == "h1", caseLabel);
      VERIFY(Square("a1").notate() == "a1", caseLabel);
      VERIFY(Square("a2").notate() == "a2", caseLabel);
      VERIFY(Square("a3").notate() == "a3", caseLabel);
      VERIFY(Square("a4").notate() == "a4", caseLabel);
      VERIFY(Square("a5").notate() == "a5", caseLabel);
      VERIFY(Square("a6").notate() == "a6", caseLabel);
      VERIFY(Square("a7").notate() == "a7", caseLabel);
      VERIFY(Square("a8").notate() == "a8", caseLabel);
   }
   {
      const std::string caseLabel = "Square::notate for invalid values";

      VERIFY(Square("t0").notate() == "", caseLabel);
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

      VERIFY(Square("a1").operator bool(), caseLabel);
      VERIFY(Square("h8").operator bool(), caseLabel);
   }
   {
      const std::string caseLabel = "Square::operator bool() for invalid squares";

      VERIFY(Square("t0").operator bool() == false, caseLabel);
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

      Square a{"c3"};
      Square b{"g7"};
      swap(a, b);
      VERIFY(a.file() == 'g' && a.rank() == '7', caseLabel);
      VERIFY(b.file() == 'c' && b.rank() == '3', caseLabel);
   }
}


void testSquareEquality()
{
   {
      const std::string caseLabel = "Square equality for equal squares";

      VERIFY(Square("c3") == Square("c3"), caseLabel);
   }
   {
      const std::string caseLabel = "Square equality for unequal squares";

      VERIFY(!(Square("c3") == Square("f3")), caseLabel);
      VERIFY(!(Square("c3") == Square("c4")), caseLabel);
   }
   {
      const std::string caseLabel = "Square equality for default square";

      VERIFY(Square() == Square(), caseLabel);
      VERIFY(!(Square() == Square("c4")), caseLabel);
   }
}


void testSquareInequality()
{
   {
      const std::string caseLabel = "Square inequality for equal squares";

      VERIFY(!(Square("c3") != Square("c3")), caseLabel);
   }
   {
      const std::string caseLabel = "Square inequality for unequal squares";

      VERIFY(Square("c3") != Square("f3"), caseLabel);
      VERIFY(Square("c3") != Square("c4"), caseLabel);
   }
   {
      const std::string caseLabel = "Square inequality for default square";

      VERIFY(!(Square() != Square()), caseLabel);
      VERIFY(Square() != Square("c4"), caseLabel);
   }
}


void testSquareLiteral()
{
   {
      const std::string caseLabel = "Square literal";

      VERIFY("e3"_sq == Square("e3"), caseLabel);
      VERIFY(""_sq == Square(), caseLabel);
      VERIFY("e3zzzzz"_sq == Square("e3"), caseLabel);
      VERIFY("ez"_sq == Square(), caseLabel);
      VERIFY("z2"_sq == Square(), caseLabel);
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

      VERIFY(Square("b2") + Offset(1, 1) == std::make_optional<Square>("c3"), caseLabel);
      VERIFY(Square("b2") + Offset(4, 5) == std::make_optional<Square>("f7"), caseLabel);
      VERIFY(Square("g6") + Offset(1, 2) == std::make_optional<Square>("h8"), caseLabel);
      VERIFY(Square("g6") + Offset(-1, -2) == std::make_optional<Square>("f4"),
             caseLabel);
      VERIFY(Square("g6") + Offset(3, 1) == std::nullopt, caseLabel);
      VERIFY(Square("g6") + Offset(1, 5) == std::nullopt, caseLabel);
      VERIFY(Square("d6") + Offset(-5, -1) == std::nullopt, caseLabel);
      VERIFY(Square("d3") + Offset(-1, -4) == std::nullopt, caseLabel);
      VERIFY(Square("d3") + Offset(0, 0) == std::make_optional<Square>("d3"), caseLabel);
   }
}


void testOffsetSquareAddition()
{
   {
      const std::string caseLabel =
         "Square and offset addition with square as second operand";

      VERIFY(Offset(1, 1) + Square("b2") == std::make_optional<Square>("c3"), caseLabel);
      VERIFY(Offset(4, 5) + Square("b2") == std::make_optional<Square>("f7"), caseLabel);
      VERIFY(Offset(1, 2) + Square("g6") == std::make_optional<Square>("h8"), caseLabel);
      VERIFY(Offset(-1, -2) + Square("g6") == std::make_optional<Square>("f4"),
             caseLabel);
      VERIFY(Offset(3, 1) + Square("g6") == std::nullopt, caseLabel);
      VERIFY(Offset(1, 5) + Square("g6") == std::nullopt, caseLabel);
      VERIFY(Offset(-5, -1) + Square("d6") == std::nullopt, caseLabel);
      VERIFY(Offset(-1, -4) + Square("d3") == std::nullopt, caseLabel);
      VERIFY(Offset(0, 0) + Square("d3") == std::make_optional<Square>("d3"), caseLabel);
   }
}


void testOptionalSquareOffsetAddition()
{
   {
      const std::string caseLabel =
         "std::optional<Square> and offset addition with square as first operand";

      VERIFY(std::make_optional<Square>("b2") + Offset(1, 1) ==
                std::make_optional<Square>("c3"),
             caseLabel);
      VERIFY(std::make_optional<Square>("b2") + Offset(4, 5) ==
                std::make_optional<Square>("f7"),
             caseLabel);
      VERIFY(std::make_optional<Square>("g6") + Offset(1, 2) ==
                std::make_optional<Square>("h8"),
             caseLabel);
      VERIFY(std::make_optional<Square>("g6") + Offset(-1, -2) ==
                std::make_optional<Square>("f4"),
             caseLabel);
      VERIFY(std::make_optional<Square>("g6") + Offset(3, 1) == std::nullopt, caseLabel);
      VERIFY(std::make_optional<Square>("g6") + Offset(1, 5) == std::nullopt, caseLabel);
      VERIFY(std::make_optional<Square>("d6") + Offset(-5, -1) == std::nullopt,
             caseLabel);
      VERIFY(std::make_optional<Square>("d3") + Offset(-1, -4) == std::nullopt,
             caseLabel);
      VERIFY(std::nullopt + Offset(1, 4) == std::nullopt, caseLabel);
      VERIFY(std::make_optional<Square>("d3") + Offset(0, 0) ==
                std::make_optional<Square>("d3"),
             caseLabel);
   }
}


void testOffsetOptionalSquareAddition()
{
   {
      const std::string caseLabel =
         "std::optional<Square> and offset addition with square as second operand";

      VERIFY(Offset(4, 5) + std::make_optional<Square>("b2") ==
                std::make_optional<Square>("f7"),
             caseLabel);
      VERIFY(Offset(3, 1) + std::make_optional<Square>("g6") == std::nullopt, caseLabel);
      VERIFY(Offset(1, 4) + std::nullopt == std::nullopt, caseLabel);
      VERIFY(Offset(0, 0) + std::make_optional<Square>("d3") ==
                std::make_optional<Square>("d3"),
             caseLabel);
   }
}

} // namespace


///////////////////

void testSquare()
{
   testSquareDefaultCtor();
   testSquareCharCtor();
   testSquareStringCtor();
   testSquareFile();
   testSquareRank();
   testSquareNotate();
   testSquareOperatorBool();
   testSwapSquares();
   testSquareEquality();
   testSquareInequality();
   testSquareLiteral();

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
