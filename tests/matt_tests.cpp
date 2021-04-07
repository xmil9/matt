//
// Mar-2021, Michael Lindner
// MIT license
//
#include "matt_tests.h"
#include "matt.h"
#include "position.h"
#include "test_util.h"
#include <iostream>
#include <chrono>


namespace
{
///////////////////

void testMakeMove()
{
   {
      const std::string caseLabel = "makeMove for depth 1";

      const Position pos{"Kwd3 wf4 Kbb2"};
      const auto result = makeMove(pos, Color::White, 1);

      VERIFY(result.has_value(), caseLabel);
      if (result.has_value())
      {
         const Position resPos = *result;
         VERIFY(resPos != pos, caseLabel);
      }
   }
   {
      const std::string caseLabel = "makeMove for depth 2";

      const Position pos{"Kwd3 wf4 Kbb2"};
      const auto result = makeMove(pos, Color::White, 2);

      VERIFY(result.has_value(), caseLabel);
      if (result.has_value())
         VERIFY(*result != pos, caseLabel);
   }
   {
      const std::string caseLabel = "makeMove for depth 3";

      const Position pos{"Kwd3 wf4 Kbb2"};
      const auto result = makeMove(pos, Color::White, 3);

      VERIFY(result.has_value(), caseLabel);
      if (result.has_value())
         VERIFY(*result != pos, caseLabel);
   }
   {
      const std::string caseLabel = "makeMove for depth 4";

      const Position pos{"Kwd3 wf4 Kbb2"};
      const auto result = makeMove(pos, Color::White, 4);

      VERIFY(result.has_value(), caseLabel);
      if (result.has_value())
         VERIFY(*result != pos, caseLabel);
   }
}

} // namespace


///////////////////

void testMatt()
{
   testMakeMove();
}
