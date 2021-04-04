//
// Mar-2021, Michael Lindner
// MIT license
//
#pragma once
#include "piece.h"

class Position;


// Makes move for given side.
std::optional<Position> makeMove(const Position& pos, Color side);
// Makes move for given piece.
std::optional<Position> makeMove(const Position& pos, const Piece& piece);
