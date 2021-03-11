//
// Mar-2021, Michael Lindner
// MIT license
//
#include "piece_tests.h"
#include "square_tests.h"
#include <cstdlib>
#include <iostream>


int main()
{
   testSquare();
   testPiece();

   std::cout << "matt tests finished.\n";
   return EXIT_SUCCESS;
}
