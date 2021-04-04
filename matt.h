//
// Mar-2021, Michael Lindner
// MIT license
//
#pragma once
#include "piece.h"
#include <cstdlib>

class Position;


std::optional<Position> makeMove(const Position& pos, Color side, std::size_t depth);
