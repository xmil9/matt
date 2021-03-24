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

Position::Position(const std::vector<Piece>& pieces)
: m_pieces{pieces}, m_score{calcScore()}
{
}


Position::Position(std::string_view notation)
{
   const std::vector<std::string> pieceNotations =
      esl::split(std::string{notation}, PieceDelim);

   std::transform(begin(pieceNotations), end(pieceNotations),
                  std::back_inserter(m_pieces),
                  [](const std::string& pieceNotation) { return Piece(pieceNotation); });

   m_score = calcScore();
}


bool Position::isOccupiedBy(Square loc, Color byColor) const
{
   const auto it = at(loc);
   return it != end(m_pieces) && it->color() == byColor;
}


std::optional<Piece> Position::operator[](Square loc) const
{
   if (const auto it = at(loc); it != end(m_pieces))
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
                  [](const auto& piece) { return piece.notate(Piece::Notation::FCL); });
   return esl::trimRight(notation.str(), PieceDelimCh);
}


Position Position::makeMove(const Move& move) const
{
   const Piece movingPiece = move.piece();
   const Square to = move.to();

   std::vector<Piece> nextPieces;
   std::copy_if(begin(m_pieces), end(m_pieces), std::back_inserter(nextPieces),
                [&movingPiece, &to](const Piece& elem) {
                   // Skip moving piece and piece at moved-to coordinate.
                   return elem != movingPiece && elem.location() != to;
                });
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

bool operator==(const Position& a, const Position& b)
{
   if (a.m_pieces.size() != b.m_pieces.size())
      return false;

   for (const Piece& piece : a.m_pieces)
      if (std::find(begin(b.m_pieces), end(b.m_pieces), piece) == end(b.m_pieces))
         return false;

   return true;
}
