//
// Feb-2021, Michael Lindner
// MIT license
//
#include "piece.h"
#include "move.h"
#include "position.h"
#include <algorithm>
#include <array>
#include <cassert>
#include <iterator>
#include <stdexcept>
#include <tuple>


namespace
{
///////////////////

inline Move makeMove(const Piece& piece, Square to, const Position& pos)
{
   return Move{piece, to, notateMove(piece, to, pos)};
}


// Adds move to a given square to a collection if the move is possible.
// Returns whether the destination square was occupied by a piece.
bool collectMoveTo(const Piece& piece, Square to, const Position& pos,
                   std::vector<Move>& moves)
{
   const auto& occupant = pos[to];
   if (!occupant)
   {
      // Open square:
      // - can move to it
      // - further squares in this direction are accessible
      moves.push_back(makeMove(piece, to, pos));
   }
   else
   {
      // Occupied square:
      // - can move to it if occupied by other color (capture unless piece is a pawn)
      // - further squares in this direction are not accessible
      if (occupant->color() != piece.color() && !piece.isFigure(Figure::Pawn))
         moves.push_back(makeMove(piece, to, pos));
   }

   return occupant.has_value();
}


// Adds the possible moves in a given direction to a collection.
void collectMovesInDirection(const Piece& piece, const Position& pos, Offset dir,
                             std::vector<Move>& moves)
{
   std::optional<Square> to = piece.location() + dir;
   while (to.has_value())
   {
      if (collectMoveTo(piece, *to, pos, moves))
         to = std::nullopt;
      else
         to = to + dir;
   }
}


// Adds the possible moves in given directions to a collection.
template <typename DirectionIter>
void collectMovesInDirections(const Piece& piece, const Position& pos,
                              DirectionIter first, DirectionIter last,
                              std::vector<Move>& moves)
{
   std::for_each(first, last, [&](const auto& dir) {
      collectMovesInDirection(piece, pos, dir, moves);
   });
}


// Adds the possible moves for given offsets to a collection.
template <typename OffsetIter>
void collectMovesTo(const Piece& piece, const Position& pos, OffsetIter first,
                    OffsetIter last, std::vector<Move>& moves)
{
   std::for_each(first, last, [&](const auto& off) {
      std::optional<Square> to = piece.location() + off;
      if (to.has_value())
         collectMoveTo(piece, *to, pos, moves);
   });
}


///////////////////

std::vector<Move> kingMoves(const Piece& king, const Position& pos)
{
   assert(pos[king.location()] == king);

   static const std::array<Offset, 8> Offsets{Offset{1, 1}, {1, 0},  {1, -1}, {0, 1},
                                              {0, -1},      {-1, 1}, {-1, 0}, {-1, -1}};

   std::vector<Move> moves;
   collectMovesTo(king, pos, begin(Offsets), end(Offsets), moves);
   // todo - filter out moves that lead into check
   return moves;
}


std::vector<Move> queenMoves(const Piece& queen, const Position& pos)
{
   assert(pos[queen.location()] == queen);

   static const std::array<Offset, 8> Directions{
      Offset{1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}};

   std::vector<Move> moves;
   collectMovesInDirections(queen, pos, begin(Directions), end(Directions), moves);
   return moves;
}


std::vector<Move> rookMoves(const Piece& rook, const Position& pos)
{
   assert(pos[rook.location()] == rook);

   static const std::array<Offset, 4> Directions{Offset{1, 0}, {0, 1}, {0, -1}, {-1, 0}};

   std::vector<Move> moves;
   collectMovesInDirections(rook, pos, begin(Directions), end(Directions), moves);
   return moves;
}


std::vector<Move> bishopMoves(const Piece& bishop, const Position& pos)
{
   static const std::array<Offset, 4> Directions{
      Offset{1, 1}, {-1, 1}, {1, -1}, {-1, -1}};

   std::vector<Move> moves;
   collectMovesInDirections(bishop, pos, begin(Directions), end(Directions), moves);
   return moves;
}


std::vector<Move> knightMoves(const Piece& knight, const Position& pos)
{
   assert(pos[knight.location()] == knight);

   static const std::array<Offset, 8> Offsets{Offset{2, 1}, {2, -1}, {-2, 1}, {-2, -1},
                                              {1, 2},       {-1, 2}, {1, -2}, {-1, -2}};

   std::vector<Move> moves;
   collectMovesTo(knight, pos, begin(Offsets), end(Offsets), moves);
   return moves;
}


std::vector<Move> pawnMoves(const Piece& pawn, const Position& pos)
{
   assert(pos[pawn.location()] == pawn);

   std::vector<Move> moves;
   const Offset dir = pawnDirection(pawn);

   // Move one square forward.
   if (const auto to = pawn.location() + dir; to.has_value())
      collectMoveTo(pawn, *to, pos, moves);

   // Move two squares forward from starting square.
   if (isPawnOnInitialRank(pawn) &&
       // Only if moving one square forward succeeded.
       !moves.empty())
   {
      if (const auto to = pawn.location() + 2 * dir; to.has_value())
         collectMoveTo(pawn, *to, pos, moves);
   }

   // Capture diagonally on lower file.
   if (const auto to = pawn.location() + dir + Offset{-1, 0}; to.has_value())
   {
      if (const auto target = pos[*to];
          target.has_value() && pawn.color() != target->color())
      {
         moves.push_back(makeMove(pawn, *to, pos));
      }
   }

   // Capture diagonally on higher file.
   if (const auto to = pawn.location() + dir + Offset{1, 0}; to.has_value())
   {
      if (const auto target = pos[*to];
          target.has_value() && pawn.color() != target->color())
      {
         moves.push_back(makeMove(pawn, *to, pos));
      }
   }

   // todo - capture en passant

   return moves;
}

} // namespace


///////////////////

Piece::Piece(Figure figure, Color color, std::string_view loc)
: Piece{figure, color, Square{loc}}
{
}


Piece::Piece(std::string_view notation)
{
   m_figure = makeFigure(notation);
   std::size_t idx = m_figure == Figure::Pawn ? 0 : 1;
   m_color = makeColor(notation.substr(idx++));
   m_loc = Square{notation.substr(idx)};
}


Piece::Piece(std::string_view notation, Color side)
{
   m_color = side;
   m_figure = makeFigure(notation);
   std::size_t idx = m_figure == Figure::Pawn ? 0 : 1;
   if (notation[idx] == 'x')
      ++idx;
   m_loc = Square{notation.substr(idx)};
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
      notation += m_loc.notate();
   return notation;
}


///////////////////

bool isPawnOnInitialRank(const Piece& pawn)
{
   if (!pawn.isFigure(Figure::Pawn))
      return false;

   const char initialRank = pawn.color() == Color::White ? '2' : '7';
   return pawn.location().rank() == initialRank;
}


Offset pawnDirection(const Piece& pawn)
{
   if (!pawn.isFigure(Figure::Pawn))
      return {0, 0};
   return {0, pawn.color() == Color::White ? 1 : -1};
}
