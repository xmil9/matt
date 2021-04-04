//
// Mar-2021, Michael Lindner
// MIT license
//
#include "matt_tests.h"
#include "move_tests.h"
#include "piece_tests.h"
#include "position_tests.h"
#include "square_tests.h"
#include <cstdlib>
#include <iostream>


int main()
{
   testMatt();
   testMove();
   testPiece();
   testPosition();
   testSquare();

   std::cout << "matt tests finished.\n";
   return EXIT_SUCCESS;
}
