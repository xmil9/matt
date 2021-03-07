//
// Mar-2021, Michael Lindner
// MIT license
//
#pragma once
#include "piece.h"

class Position;


std::optional<Position> makeMove(const Position& pos, Color side);
std::optional<Position> makeMove(const Position& pos, const Piece& piece);
