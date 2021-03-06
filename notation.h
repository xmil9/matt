//
// Feb-2021, Michael Lindner
// MIT license
//
#pragma once
#include "piece.h"
#include <string>
#include <vector>


///////////////////

std::string noteMove(const Piece& piece, Square to, const Position& pos);
std::string noteCapture(const Piece& piece, Square to, const Position& pos);


///////////////////

std::vector<Piece> parsePositionNotation(const std::string& notation);
std::tuple<Piece::Type, Color, Square> parsePieceNotation(const std::string& notation);


///////////////////

class Record
{
 public:
   Record() = default;
   explicit Record(std::string pos);

   void record(const std::string& move) { m_moves.push_back(move); }

 private:
   std::string m_initialPos;
   std::vector<std::string> m_moves;
};
