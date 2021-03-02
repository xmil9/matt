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


namespace
{
///////////////////

inline Move makeMove(const Piece& piece, Square to, const Position& pos)
{
   return Move{piece, to, noteMove(piece, to, pos)};
}

Move makeCapture(const Piece& piece, Square to, const Position& pos)
{
   return Move{piece, to, noteCapture(piece, to, pos)};
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
      // - can move to it if occupied by other color (capture)
      // - further squares in this direction are not accessible
      if (occupant->color() != piece.color())
         moves.push_back(makeCapture(piece, to, pos));
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

   const Offset dir{0, pawn.color() == Color::White ? 1 : -1};

   std::vector<Move> moves;

   // Move one square forward.
   if (const auto to = pawn.location() + dir; to.has_value())
      collectMoveTo(pawn, *to, pos, moves);

   // Move two squares forward from starting square.
   const char startRank = pawn.color() == Color::White ? 2 : 7;
   if (pawn.location().rank == startRank)
      if (const auto to = pawn.location() + 2 * dir; to.has_value())
         collectMoveTo(pawn, *to, pos, moves);

   // Capture diagonally to lower file.
   if (const auto to = pawn.location() + dir + Offset{-1, 0}; to.has_value())
   {
      if (const auto target = pos[*to];
          target.has_value() && pawn.color() != target->color())
      {
         moves.push_back(makeCapture(pawn, *to, pos));
      }
   }

   // Capture diagonally to higher file.
   if (const auto to = pawn.location() + dir + Offset{1, 0}; to.has_value())
      if (const auto target = pos[*to];
          target.has_value() && pawn.color() != target->color())
         moves.push_back(makeCapture(pawn, *to, pos));

   // todo - capture en passant

   return moves;
}

} // namespace


///////////////////

std::string Piece::notation() const
{
   switch (m_type)
   {
   case Type::King:
      return "K";
   case Type::Queen:
      return "Q";
   case Type::Rook:
      return "R";
   case Type::Bishop:
      return "B";
   case Type::Knight:
      return "N";
   case Type::Pawn:
      return "";
   default:
      assert(false && "Huh, a new piece type?");
      return "";
   }
}


std::vector<Move> Piece::moves(const Position& pos) const
{
   switch (m_type)
   {
   case Type::King:
      return kingMoves(*this, pos);
   case Type::Queen:
      return queenMoves(*this, pos);
   case Type::Rook:
      return rookMoves(*this, pos);
   case Type::Bishop:
      return bishopMoves(*this, pos);
   case Type::Knight:
      return knightMoves(*this, pos);
   case Type::Pawn:
      return pawnMoves(*this, pos);
   default:
      assert(false && "Huh, a new piece type?");
      return {};
   }
}
