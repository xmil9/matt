//
// Mar-2021, Michael Lindner
// MIT license
//
#pragma once
#include "piece.h"

class Position;


Position makeMove(const Position& pos, Color side);
Position makeMove(const Position& pos, const Piece& piece);
