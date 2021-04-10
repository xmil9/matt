//
// Mar-2021, Michael Lindner
// MIT license
//
#include "matt_tests.h"
#include "matt.h"
#include "position.h"
#include "test_util.h"
#include "deps/essentutils/time_util.h"
#include <iostream>
#include <chrono>


namespace
{
///////////////////

void testMakeMove(const std::string& casePrefix, const Position& pos,
                  std::size_t maxDepth, Color side)
{
   for (std::size_t i = 1; i <= maxDepth; ++i)
   {
      const std::string caseLabel = casePrefix + std::to_string(i);

      const auto result = makeMove(pos, side, i);

      VERIFY(result.has_value(), caseLabel);
      if (result.has_value())
      {
         const Position resPos = *result;
         VERIFY(resPos != pos, caseLabel);
      }
   }
}


///////////////////

void testMakeMoveForPositionA()
{
   const Position pos{"Kwd3 wf4 Kbb2"};

   {
      const std::string casePrefix = "Position A with white for depth ";
      testMakeMove(casePrefix, pos, 4, Color::White);
   }
   {
      const std::string casePrefix = "Position A with black for depth ";
      testMakeMove(casePrefix, pos, 4, Color::Black);
   }
}


void testMakeMoveForPositionB()
{
   const Position pos{"Rwb1 Kwd1 Bwf1 Rwh1 wa2 wf2 wg2 wh2 Qbc3 we3 Nwf3 Bwg3 wd4 Kbe4 "
                      "bd5 bg5 bc6 bh6 ba7 bb7 Kbe7 bf7 Bbg7 Rba8 Kbb8 Qwc8 Rbh8"};

   {
      const std::string casePrefix = "Position B with white for depth ";
      testMakeMove(casePrefix, pos, 2, Color::White);
   }
   {
      const std::string casePrefix = "Position B with black for depth ";
      testMakeMove(casePrefix, pos, 2, Color::Black);
   }
}

} // namespace


///////////////////

void testMatt()
{
   testMakeMoveForPositionA();
   testMakeMoveForPositionB();
}
