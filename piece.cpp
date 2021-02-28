//
// Feb-2021, Michael Lindner
// MIT license
//
#include "piece.h"
#include "position.h"
#include <algorithm>
#include <array>
#include <iterator>


namespace
{
///////////////////

// Adds move to a given square to a collection if the move is possible.
// Returns whether the destination square was occupied by a piece.
bool collectMoveTo(Square to, Color color, const Position& pos,
                   std::vector<Square>& moves)
{
   const auto& piece = pos[to];
   if (!piece)
   {
      // Open square:
      // - can move to it
      // - further squares in this direction are accessible
      moves.push_back(to);
   }
   else
   {
      // Occupied square:
      // - can move to it if occupied by other color (capture)
      // - further squares in this direction are not accessible
      if (!hasColor(*piece, color))
         moves.push_back(to);
   }

   return piece.has_value();
}


// Adds the possible moves in a given direction to a collection.
void collectMovesInDirection(Square from, Color color, const Position& pos, Offset dir,
                             std::vector<Square>& moves)
{
   std::optional<Square> to = from + dir;
   while (to.has_value())
   {
      if (collectMoveTo(*to, color, pos, moves))
         to = std::nullopt;
      else
         to = to + dir;
   }
}


// Adds the possible moves in given directions to a collection.
template <typename DirectionIter>
void collectMovesInDirections(Square from, Color color, const Position& pos,
                              DirectionIter first, DirectionIter last,
                              std::vector<Square>& moves)
{
   std::for_each(first, last, [&](const auto& dir) {
      collectMovesInDirection(from, color, pos, dir, moves);
   });
}


// Adds the possible moves for given offsets to a collection.
template <typename OffsetIter>
void collectMovesTo(Square from, Color color, const Position& pos, OffsetIter first,
                    OffsetIter last, std::vector<Square>& moves)
{
   std::for_each(first, last, [&](const auto& off) {
      std::optional<Square> to = from + off;
      if (to.has_value())
         collectMoveTo(*to, color, pos, moves);
   });
}

} // namespace


///////////////////

std::vector<Square> King::moves_(const Position& pos) const
{
   assert(pos[location()] == Piece{*this});

   static const std::array<Offset, 8> Offsets{Offset{1, 1}, {1, 0},  {1, -1}, {0, 1},
                                              {0, -1},      {-1, 1}, {-1, 0}, {-1, -1}};

   std::vector<Square> moves;
   collectMovesTo(location(), color(), pos, begin(Offsets), end(Offsets), moves);
   // todo - filter out moves that lead into check
   return moves;
}


///////////////////

std::vector<Square> Queen::moves_(const Position& pos) const
{
   assert(pos[location()] == Piece{*this});

   static const std::array<Offset, 8> Directions{
      Offset{1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}};

   std::vector<Square> moves;
   collectMovesInDirections(location(), color(), pos, begin(Directions), end(Directions),
                            moves);
   return moves;
}


///////////////////

std::vector<Square> Rook::moves_(const Position& pos) const
{
   assert(pos[location()] == Piece{*this});

   static const std::array<Offset, 4> Directions{Offset{1, 0}, {0, 1}, {0, -1}, {-1, 0}};

   std::vector<Square> moves;
   collectMovesInDirections(location(), color(), pos, begin(Directions), end(Directions),
                            moves);
   return moves;
}


///////////////////

std::vector<Square> Bishop::moves_(const Position& pos) const
{
   assert(pos[location()] == Piece{*this});

   static const std::array<Offset, 4> Directions{
      Offset{1, 1}, {-1, 1}, {1, -1}, {-1, -1}};

   std::vector<Square> moves;
   collectMovesInDirections(location(), color(), pos, begin(Directions), end(Directions),
                            moves);
   return moves;
}


///////////////////

std::vector<Square> Knight::moves_(const Position& pos) const
{
   assert(pos[location()] == Piece{*this});

   static const std::array<Offset, 8> Offsets{Offset{2, 1}, {2, -1}, {-2, 1}, {-2, -1},
                                              {1, 2},       {-1, 2}, {1, -2}, {-1, -2}};

   std::vector<Square> moves;
   collectMovesTo(location(), color(), pos, begin(Offsets), end(Offsets), moves);
   return moves;
}


///////////////////

std::vector<Square> Pawn::moves_(const Position& pos) const
{
   assert(pos[location()] == Piece{*this});

   const Offset dir{0, color() == Color::White ? 1 : -1};

   std::vector<Square> moves;

   // Move one square forward.
   if (const auto to = location() + dir; to.has_value())
      collectMoveTo(*to, color(), pos, moves);

   // Move two squares forward from starting square.
   const char startRank = color() == Color::White ? 2 : 7;
   if (location().rank == startRank)
      if (const auto to = location() + 2 * dir; to.has_value())
         collectMoveTo(*to, color(), pos, moves);

   // Capture diagonally to lower file.
   if (const auto to = location() + dir + Offset{-1, 0}; to.has_value())
      if (const auto piece = pos[*to]; piece.has_value() && hasColor(*piece, !color()))
         moves.push_back(*to);

   // Capture diagonally to higher file.
   if (const auto to = location() + dir + Offset{1, 0}; to.has_value())
      if (const auto piece = pos[*to]; piece.has_value() && hasColor(*piece, !color()))
         moves.push_back(*to);

   // todo - capture en passant

   return moves;
}
