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
#include <map>
#include <numeric>
#include <sstream>


///////////////////

const Position StartPos{"Rba8 Nbb8 Bbc8 Qbd8 Kbe8 Bbf8 Nbg8 Rbh8 "
                        "ba7 bb7 bc7 bd7 be7 bf7 bg7 bh7 "
                        "wa2 wb2 wc2 wd2 we2 wf2 wg2 wh2 "
                        "Rwa1 Nwb1 Bwc1 Qwd1 Kwe1 Bwf1 Nwg1 Rwh1"};

static constexpr char PieceDelimCh = ' ';
static constexpr char PieceDelim[] = {PieceDelimCh};

static constexpr unsigned char OccuppiedField = 1;
static constexpr unsigned char EmptyField = 0;

static std::size_t BoardIndex(const Square& coord)
{
   return (coord.file() - 'a') * 8 + (coord.rank() - '1');
}


///////////////////

Position::Position(const std::vector<Piece>& pieces)
: m_pieces{pieces.begin(), pieces.end()}, m_record{notate()}, m_score{calcScore()}
{
   populateBoard();
}


Position::Position(ds::SboVector<Piece, 32>&& pieces, Record&& record)
: m_pieces{std::move(pieces)}, m_record{std::move(record)}, m_score{calcScore()}
{
   populateBoard();
}


Position::Position(std::string_view notation) : m_record{std::string{notation}}
{
   const std::vector<std::string> pieceNotations =
      esl::split(std::string{notation}, PieceDelim);

   m_pieces.reserve(pieceNotations.size());
   std::transform(begin(pieceNotations), end(pieceNotations),
                  std::back_inserter(m_pieces),
                  [](const std::string& pieceNotation) { return Piece(pieceNotation); });

   populateBoard();
   m_score = calcScore();
}


bool Position::isOccupiedBy(Square coord, Color side) const
{
   const auto it = at(coord);
   return it != m_pieces.end() && it->color() == side;
}


bool Position::isThreatenedBy(Square coord, Color side) const
{
   for (const auto& piece : m_pieces)
   {
      if (piece.color() == side)
      {
         const auto threatened = piece.threatenedSquares(*this);
         if (std::find(threatened.begin(), threatened.end(), coord) != threatened.end())
            return true;
      }
   }

   return false;
}


std::optional<Piece> Position::operator[](Square coord) const
{
   if (const auto it = at(coord); it != m_pieces.end())
      return *it;
   return std::nullopt;
}


std::vector<Piece> Position::pieces(Color side) const
{
   std::vector<Piece> result;
   result.reserve(m_pieces.size());
   std::copy_if(m_pieces.begin(), m_pieces.end(), std::back_inserter(result),
                [side](const auto& piece) { return piece.color() == side; });
   return result;
}


std::string Position::notate() const
{
   std::stringstream notation;
   std::transform(m_pieces.begin(), m_pieces.end(),
                  std::ostream_iterator<std::string>(notation, PieceDelim),
                  [](const auto& piece) { return piece.notate(Piece::Notation::FCL); });
   return esl::trimRight(notation.str(), PieceDelimCh);
}


Position Position::makeMove(const Move& move) const
{
   const Piece movingPiece = move.piece();
   const Square to = move.to();

   ds::SboVector<Piece, 32> movedPieces;
   movedPieces.reserve(m_pieces.size());
   std::copy_if(std::begin(m_pieces), std::end(m_pieces), std::back_inserter(movedPieces),
                [&movingPiece, &to](const Piece& elem) {
                   // Skip moving piece and piece at moved-to coordinate.
                   return elem != movingPiece && elem.coord() != to;
                });
   movedPieces.push_back(move.movedPiece());

   Record movedRecord = m_record;
   movedRecord.add(move.notate());

   return Position{std::move(movedPieces), std::move(movedRecord)};
}


void Position::populateBoard()
{
   memset(m_board.data(), EmptyField, m_board.size());

   for (const auto& piece : m_pieces)
      m_board[BoardIndex(piece.coord())] = OccuppiedField;
}


Position::Iter Position::at(Square coord)
{
   if (m_board[BoardIndex(coord)] == OccuppiedField)
   {
      return std::find_if(
         std::begin(m_pieces), std::end(m_pieces),
         [&coord](const Piece& piece) { return piece.coord() == coord; });
   }
   return std::end(m_pieces);
}


Position::Citer Position::at(Square coord) const
{
   if (m_board[BoardIndex(coord)] == OccuppiedField)
   {
      return std::find_if(
         std::begin(m_pieces), std::end(m_pieces),
         [&coord](const Piece& piece) { return piece.coord() == coord; });
   }
   return std::end(m_pieces);
}


float Position::calcScore() const
{
   return calcValue(pieces(Color::White)) - calcValue(pieces(Color::Black));
}


float Position::calcValue(const std::vector<Piece>& pieces) const
{
   static std::map<Figure, float> PieceValues = {
      {Figure::Pawn, 1.f}, {Figure::Knight, 3.f}, {Figure::Bishop, 3.f},
      {Figure::Rook, 5.f}, {Figure::Queen, 9.f},  {Figure::King, 100.f}};

   return std::accumulate(begin(pieces), end(pieces), 0.f,
                          [](const float& currValue, const Piece& piece) {
                             return currValue + PieceValues[piece.figure()];
                          });
}


///////////////////

bool operator==(const Position& a, const Position& b)
{
   if (a.m_pieces.size() != b.m_pieces.size())
      return false;

   for (const Piece& piece : a.m_pieces)
      if (std::find(b.m_pieces.begin(), b.m_pieces.end(), piece) == b.m_pieces.end())
         return false;

   return true;
}
