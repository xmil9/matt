//
// Feb-2021, Michael Lindner
// MIT license
//
#include "piece.h"
#include "move.h"
#include "position.h"
#include <algorithm>
#include <array>
#include <algorithm>
#include <cassert>
#include <iterator>
#include <stdexcept>
#include <tuple>


namespace
{
///////////////////

// Adds a given square to a collection if the move is possible.
// Returns whether the destination square was occupied by a piece.
bool collectSquare(const Piece& piece, Square to, const Position& pos,
                   std::vector<Square>& squares)
{
   const auto& occupant = pos[to];
   if (!occupant)
   {
      // Open square:
      // - can move to it
      // - further squares in this direction are accessible
      squares.push_back(to);
   }
   else
   {
      // Occupied square:
      // - can move to it if occupied by other color (capture unless piece is a pawn)
      // - further squares in this direction are not accessible
      if (occupant->color() != piece.color() && piece.figure() != Figure::Pawn)
         squares.push_back(to);
   }

   return occupant.has_value();
}


// Adds the reachable squares in a given direction to a collection.
void collectSquaresInDirection(const Piece& piece, const Position& pos, Offset dir,
                               std::vector<Square>& squares)
{
   std::optional<Square> to = piece.coord() + dir;
   while (to.has_value())
   {
      if (collectSquare(piece, *to, pos, squares))
         to = std::nullopt;
      else
         to = to + dir;
   }
}


// Adds the reachable squares in given directions to a collection.
template <typename DirectionIter>
void collectSquaresInDirections(const Piece& piece, const Position& pos,
                                DirectionIter first, DirectionIter last,
                                std::vector<Square>& squares)
{
   std::for_each(first, last, [&](const auto& dir) {
      collectSquaresInDirection(piece, pos, dir, squares);
   });
}


// Adds the reachable squares for given offsets to a collection.
template <typename OffsetIter>
void collectSquares(const Piece& piece, const Position& pos, OffsetIter first,
                    OffsetIter last, std::vector<Square>& squares)
{
   std::for_each(first, last, [&](const auto& off) {
      std::optional<Square> to = piece.coord() + off;
      if (to.has_value())
         collectSquare(piece, *to, pos, squares);
   });
}


// Builds moves from given destination squares.
std::vector<Move> buildMoves(const Piece& piece, const std::vector<Square>& squares,
                             const Position& pos)
{
   std::vector<Move> moves;
   moves.reserve(squares.size());
   std::transform(std::begin(squares), std::end(squares), std::back_inserter(moves),
                  [&](const auto& to) {
                     return Move{piece, to, pos};
                  });
   return moves;
}


// Check if the king on a given square is in check.
bool isCheck(const Position& pos, Square at)
{
   const auto piece = pos[at];
   if (!piece.has_value() || piece->figure() != Figure::King)
      return false;

   return pos.isThreatenedBy(at, !piece->color());
}


// Remove moves that lead into check.
void removeChecks(const Position& pos, std::vector<Move>& moves)
{
   moves.erase(std::remove_if(moves.begin(), moves.end(),
                              [&pos](const Move& move) {
                                 // Create the position and test for check.
                                 return isCheck(pos.makeMove(move), move.to());
                              }),
               moves.end());
}


///////////////////

// Returns collection of squares that a given king can move to using its basic
// movement rule. Does not account for castling.
std::vector<Square> kingBasicSquares(const Piece& king, const Position& pos)
{
   assert(king.figure() == Figure::King);
   assert(pos[king.coord()] == king);

   static const std::array<Offset, 8> Offsets{Offset{1, 1}, {1, 0},  {1, -1}, {0, 1},
                                              {0, -1},      {-1, 1}, {-1, 0}, {-1, -1}};

   std::vector<Square> to;
   collectSquares(king, pos, std::begin(Offsets), std::end(Offsets), to);
   return to;
}


// Returns collection of squares that a given king is threatening.
std::vector<Square> kingThreatenedSquares(const Piece& king, const Position& pos)
{
   // Ignore squares that can be reached by castling because castling is not allowed
   // if the target square is occupied.
   return kingBasicSquares(king, pos);
}


// Returns collection of moves that a given king can make.
std::vector<Move> kingMoves(const Piece& king, const Position& pos)
{
   const std::vector<Square> to = kingBasicSquares(king, pos);
   std::vector<Move> moves = buildMoves(king, to, pos);
   // Special rule - king can not move into check.
   removeChecks(pos, moves);
   return moves;
}


std::vector<Square> queenSquares(const Piece& queen, const Position& pos)
{
   assert(queen.figure() == Figure::Queen);
   assert(pos[queen.coord()] == queen);

   static const std::array<Offset, 8> Directions{
      Offset{1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}};

   std::vector<Square> to;
   collectSquaresInDirections(queen, pos, begin(Directions), end(Directions), to);
   return to;
}


std::vector<Move> queenMoves(const Piece& queen, const Position& pos)
{
   return buildMoves(queen, queenSquares(queen, pos), pos);
}


std::vector<Square> rookSquares(const Piece& rook, const Position& pos)
{
   assert(rook.figure() == Figure::Rook);
   assert(pos[rook.coord()] == rook);

   static const std::array<Offset, 4> Directions{Offset{1, 0}, {0, 1}, {0, -1}, {-1, 0}};

   std::vector<Square> to;
   collectSquaresInDirections(rook, pos, begin(Directions), end(Directions), to);
   return to;
}


std::vector<Move> rookMoves(const Piece& rook, const Position& pos)
{
   return buildMoves(rook, rookSquares(rook, pos), pos);
}


std::vector<Square> bishopSquares(const Piece& bishop, const Position& pos)
{
   assert(bishop.figure() == Figure::Bishop);
   assert(pos[bishop.coord()] == bishop);

   static const std::array<Offset, 4> Directions{
      Offset{1, 1}, {-1, 1}, {1, -1}, {-1, -1}};

   std::vector<Square> to;
   collectSquaresInDirections(bishop, pos, begin(Directions), end(Directions), to);
   return to;
}


std::vector<Move> bishopMoves(const Piece& bishop, const Position& pos)
{
   return buildMoves(bishop, bishopSquares(bishop, pos), pos);
}


std::vector<Square> knightSquares(const Piece& knight, const Position& pos)
{
   assert(knight.figure() == Figure::Knight);
   assert(pos[knight.coord()] == knight);

   static const std::array<Offset, 8> Offsets{Offset{2, 1}, {2, -1}, {-2, 1}, {-2, -1},
                                              {1, 2},       {-1, 2}, {1, -2}, {-1, -2}};

   std::vector<Square> to;
   collectSquares(knight, pos, begin(Offsets), end(Offsets), to);
   return to;
}


std::vector<Move> knightMoves(const Piece& knight, const Position& pos)
{
   return buildMoves(knight, knightSquares(knight, pos), pos);
}


// Returns collection of squares that a given pawn can move to using its basic
// movement rule. Does not include squares reached by capturing diagonally or
// en passant.
std::vector<Square> pawnBasicSquares(const Piece& pawn, const Position& pos)
{
   assert(pawn.figure() == Figure::Pawn);
   assert(pos[pawn.coord()] == pawn);

   std::vector<Square> squares;
   const Offset dir = pawnDirection(pawn);

   // Move one square forward.
   if (const auto to = pawn.coord() + dir; to.has_value())
      collectSquare(pawn, *to, pos, squares);

   // Move two squares forward from starting square.
   if (isPawnOnInitialRank(pawn) &&
       // Only if moving one square forward succeeded.
       !squares.empty())
   {
      if (const auto to = pawn.coord() + 2 * dir; to.has_value())
         collectSquare(pawn, *to, pos, squares);
   }

   return squares;
}


std::vector<Square> pawnThreatenedSquares(const Piece& pawn, const Position& pos)
{
   assert(pawn.figure() == Figure::Pawn);

   std::vector<Square> squares;
   const Offset dir = pawnDirection(pawn);

   // Capture diagonally on lower file.
   if (const auto to = pawn.coord() + dir + Offset{-1, 0}; to.has_value())
      // Only if square is not occupied by the same color.
      if (const auto target = pos[*to];
          !target.has_value() || pawn.color() != target->color())
      {
         squares.push_back(*to);
      }

   // Capture diagonally on higher file.
   if (const auto to = pawn.coord() + dir + Offset{1, 0}; to.has_value())
      // Only if square is not occupied by the same color.
      if (const auto target = pos[*to];
          !target.has_value() || pawn.color() != target->color())
      {
         squares.push_back(*to);
      }

   // todo - capture en passant

   return squares;
}


std::vector<Move> pawnMoves(const Piece& pawn, const Position& pos)
{
   auto squares = buildMoves(pawn, pawnBasicSquares(pawn, pos), pos);

   // Add squares that pawn can capture on if occupied by opposite piece.
   const auto threatened = pawnThreatenedSquares(pawn, pos);
   for (const auto& sq : threatened)
   {
      if (const auto target = pos[sq];
          target.has_value() && pawn.color() != target->color())
      {
         squares.push_back(Move{pawn, sq, pos});
      }
   }

   return squares;
}

} // namespace


///////////////////

Piece::Piece(Figure figure, Color color, std::string_view coord)
: Piece{figure, color, Square{coord}}
{
}


Piece::Piece(std::string_view notation)
{
   m_figure = makeFigure(notation);
   std::size_t idx = m_figure == Figure::Pawn ? 0 : 1;
   m_color = makeColor(notation.substr(idx++));
   m_coord = Square{notation.substr(idx)};
}


Piece::Piece(std::string_view notation, Color side)
{
   m_color = side;
   m_figure = makeFigure(notation);
   std::size_t idx = m_figure == Figure::Pawn ? 0 : 1;
   if (notation[idx] == 'x')
      ++idx;
   m_coord = Square{notation.substr(idx)};
}


std::vector<Square> Piece::threatenedSquares(const Position& pos) const
{
   switch (m_figure)
   {
   case Figure::King:
      return kingThreatenedSquares(*this, pos);
   case Figure::Queen:
      return queenSquares(*this, pos);
   case Figure::Rook:
      return rookSquares(*this, pos);
   case Figure::Bishop:
      return bishopSquares(*this, pos);
   case Figure::Knight:
      return knightSquares(*this, pos);
   case Figure::Pawn:
      return pawnThreatenedSquares(*this, pos);
   default:
      assert(false && "Invalid figure");
      return {};
   }
}


std::vector<Move> Piece::nextMoves(const Position& pos) const
{
   switch (m_figure)
   {
   case Figure::King:
      return kingMoves(*this, pos);
   case Figure::Queen:
      return queenMoves(*this, pos);
   case Figure::Rook:
      return rookMoves(*this, pos);
   case Figure::Bishop:
      return bishopMoves(*this, pos);
   case Figure::Knight:
      return knightMoves(*this, pos);
   case Figure::Pawn:
      return pawnMoves(*this, pos);
   default:
      assert(false && "Invalid figure");
      return {};
   }
}


std::vector<Position> Piece::nextPositions(const Position& pos) const
{
   const std::vector<Move> moves = nextMoves(pos);

   std::vector<Position> result;
   result.reserve(moves.size());
   std::transform(begin(moves), end(moves), std::back_inserter(result),
                  [&pos](const auto& move) { return pos.makeMove(move); });
   return result;
}


std::string Piece::notate(Notation format) const
{
   std::string notation = notateFigure(m_figure);
   if (format == Notation::FC || format == Notation::FCL)
      notation += notateColor(m_color);
   if (format == Notation::FL || format == Notation::FCL)
      notation += m_coord.notate();
   return notation;
}


///////////////////

bool isPawnOnInitialRank(const Piece& pawn)
{
   if (pawn.figure() != Figure::Pawn)
      return false;

   const char initialRank = pawn.color() == Color::White ? '2' : '7';
   return pawn.coord().rank() == initialRank;
}


Offset pawnDirection(const Piece& pawn)
{
   if (pawn.figure() != Figure::Pawn)
      return {0, 0};
   return {0, pawn.color() == Color::White ? 1 : -1};
}
