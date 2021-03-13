//
// Feb-2021, Michael Lindner
// MIT license
//
#include "position.h"
#include "move.h"
#include "essentutils/rand_util.h"
#include "essentutils/string_util.h"
#include <algorithm>
#include <iterator>
#include <sstream>


///////////////////

static constexpr char PieceDelimCh = ' ';
static constexpr char PieceDelim[] = {PieceDelimCh};


///////////////////

Position::Position()
{
}


Position::Position(const std::vector<Piece>& pieces)
   : m_pieces{pieces}, m_score{calcScore()}
{
}


bool Position::isOccupied(Square loc) const
{
   return (*this)[loc].has_value();
}


bool Position::isOccupiedBy(Square loc, Color byColor) const
{
   const auto it = at(loc);
   return it != end(m_pieces) && it->color() == byColor;
}


std::optional<Piece> Position::operator[](Square loc) const
{
   const auto it = at(loc);
   if (it != end(m_pieces))
      return *it;
   return std::nullopt;
}


std::vector<Piece> Position::pieces(Color side) const
{
   std::vector<Piece> result;
   std::copy_if(begin(m_pieces), end(m_pieces), std::back_inserter(result),
                [side](const auto& piece) { return piece.color() == side; });
   return result;
}


std::string Position::notate() const
{
   std::stringstream notation;
   std::transform(begin(m_pieces), end(m_pieces),
                  std::ostream_iterator<std::string>(notation, PieceDelim),
                  [](const auto& piece) { return piece.notateWithColor(); });
   return esl::trimRight(notation.str(), PieceDelimCh);
}


Position Position::makeMove(const Move& move) const
{
   Piece movingPiece = move.piece();

   std::vector<Piece> nextPieces;
   std::copy_if(begin(m_pieces), end(m_pieces), std::back_inserter(nextPieces),
                [&movingPiece](const Piece& elem) { return elem != movingPiece; });
   nextPieces.push_back(move.movedPiece());
   return Position{nextPieces};
}


Position::Iter Position::at(Square loc)
{
   return std::find_if(begin(m_pieces), end(m_pieces),
                       [&loc](const Piece& piece) { return piece.location() == loc; });
}


Position::Citer Position::at(Square loc) const
{
   return std::find_if(begin(m_pieces), end(m_pieces),
                       [&loc](const Piece& piece) { return piece.location() == loc; });
}


float Position::calcScore() const
{
   esl::Random<float> rnd;
   return rnd.next();
}


///////////////////

Position makePosition(std::string_view notation)
{
   const std::vector<std::string> pieceNotations =
      esl::split(std::string{notation}, PieceDelim);

   std::vector<Piece> pieces;
   std::transform(
      begin(pieceNotations), end(pieceNotations), std::back_inserter(pieces),
      [](const std::string& pieceNotation) { return makePiece(pieceNotation); });

   return Position{pieces};
}
