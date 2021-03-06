//
// Feb-2021, Michael Lindner
// MIT license
//
#include "notation.h"
#include "move.h"
#include "essentutils/string_util.h"
#include <algorithm>
#include <iterator>


namespace
{
///////////////////

Piece::Type decodeType(char code)
{
   switch (code)
   {
   case 'K':
      return Piece::Type::King;
   case 'Q':
      return Piece::Type::Queen;
   case 'R':
      return Piece::Type::Rook;
   case 'B':
      return Piece::Type::Bishop;
   case 'N':
      return Piece::Type::Knight;
   case 'b':
   case 'w':
      // For pawns the first letter is a color code.
      return Piece::Type::Pawn;
   default:
      throw std::runtime_error("Unknown piece type notation.");
   }
}


Color decodeColor(char code)
{
   switch (code)
   {
   case 'b':
      return Color::Black;
   case 'w':
      return Color::White;
   default:
      throw std::runtime_error("Unknown piece color notation.");
   }
}


char decodeFile(char code)
{
   if (code >= 'a' && code <= 'h')
      return code;
   throw std::runtime_error("Unknown file notation.");
}


char decodeRank(char code)
{
   if (code >= '1' && code <= '8')
      return code;
   throw std::runtime_error("Unknown rank notation.");
}

} // namespace


///////////////////

std::string noteMove(const Piece& piece, Square to, const Position& /*pos*/)
{
   // todo - check for ambiguities
   return piece.notation() + to.notation();
}


std::string noteCapture(const Piece& piece, Square to, const Position& /*pos*/)
{
   // todo - check for ambiguities
   return piece.notation() + std::string("x") + to.notation();
}


///////////////////

std::vector<Piece> parsePositionNotation(const std::string& notation)
{
   std::vector<Piece> pieces;
   const auto pieceNotations = esl::split(notation, " ");
   std::transform(begin(pieceNotations), end(pieceNotations), std::back_inserter(pieces),
                  [](const std::string& pieceNotation) { return Piece{pieceNotation}; });
   return pieces;
}


std::tuple<Piece::Type, Color, Square> parsePieceNotation(const std::string& notation)
{
   if (notation.size() < 3)
      throw std::runtime_error("Invalid notation for creating pieces.");

   std::size_t idx = 0;
   const Piece::Type type = decodeType(notation[idx]);
   if (type != Piece::Type::Pawn)
      ++idx;
   const Color color = decodeColor(notation[idx++]);
   const char file = decodeFile(notation[idx++]);
   const char rank = decodeRank(notation[idx++]);

   return {type, color, Square{file, rank}};
}


///////////////////

Record::Record(std::string pos) : m_initialPos{std::move(pos)}
{
}
