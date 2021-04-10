//
// Feb-2021, Michael Lindner
// MIT license
//
#include "matt.h"
#include "position.h"
#include <algorithm>
#include <execution>
#include <iterator>


namespace
{
///////////////////

template <typename T> class VectorSlice
{
 public:
   using const_iterator = typename std::vector<T>::const_iterator;

   VectorSlice(const std::vector<T>& source, std::size_t start, std::size_t size);
   VectorSlice(const std::vector<T>& source);

   std::size_t size() const { return m_size; }
   const const_iterator cbegin() const { return m_source->begin() + m_start; }
   const const_iterator cend() const { return m_source->begin() + m_start + m_size; }
   const const_iterator begin() const { return cbegin(); }
   const const_iterator end() const { return cend(); }
   const T& operator[](std::size_t idx) const { return (*m_source)[idx]; }

 private:
   const std::vector<T>* m_source = nullptr;
   std::size_t m_start = 0;
   std::size_t m_size = 0;
};


template <typename T>
inline VectorSlice<T>::VectorSlice(const std::vector<T>& source, std::size_t start,
                                   std::size_t size)
: m_source{&source}, m_start{start}, m_size{size}
{
}


template <typename T>
inline VectorSlice<T>::VectorSlice(const std::vector<T>& source)
: m_source{&source}, m_start{0}, m_size{source.size()}
{
}


template <typename T>
typename VectorSlice<T>::const_iterator begin(const VectorSlice<T>& slice)
{
   return slice.begin();
}


template <typename T>
typename VectorSlice<T>::const_iterator end(const VectorSlice<T>& slice)
{
   return slice.end();
}


template <typename T>
typename VectorSlice<T>::const_iterator cbegin(const VectorSlice<T>& slice)
{
   return slice.cbegin();
}


template <typename T>
typename VectorSlice<T>::const_iterator cend(const VectorSlice<T>& slice)
{
   return slice.cend();
}


///////////////////

std::optional<Position> bestPosition(const VectorSlice<Position>& positions, Color side)
{
   // Use best scoring position depending on the piece's color.
   const auto endPos = end(positions);
   auto bestPos = endPos;
   if (side == Color::White)
      bestPos = std::max_element(begin(positions), endPos);
   else
      bestPos = std::min_element(begin(positions), endPos);

   if (bestPos == endPos)
      return std::nullopt;
   return *bestPos;
}


std::vector<Position> allMoves(const Position& pos, Color side)
{
   std::vector<Position> allMoves;
   const auto pieces = pos.pieces(side);
   for (const auto& piece : pieces)
   {
      const auto pieceMoves = piece.nextPositions(pos);
      allMoves.insert(std::end(allMoves), std::begin(pieceMoves), std::end(pieceMoves));
   }

   return allMoves;
}


std::optional<Position> processMovesUnthreaded(const VectorSlice<Position>& moves,
                                               Color side, std::size_t plies)
{
   if (plies > 1)
   {
      // Look further ahead by, for each move, calculating all following moves of the
      // opposite color.
      std::vector<Position> bestNextMoves;
      bestNextMoves.reserve(moves.size());

      for (const auto& move : moves)
      {
         if (const auto nextMove =
                processMovesUnthreaded(allMoves(move, side), !side, plies - 1);
             nextMove.has_value())
         {
            bestNextMoves.push_back(*nextMove);
         }
      }

      return bestPosition(bestNextMoves, side);
   }
   else
   {
      // Final step. Simply find best of the given moves.
      return bestPosition(moves, side);
   }
}


std::optional<Position> processMoves(const VectorSlice<Position>& moves, Color side,
                                     std::size_t plies)
{
   if (plies > 1)
   {
      // Look further ahead by, for each move, calculating all following moves of the
      // opposite color.
      std::mutex bestMovesMx;
      std::vector<Position> bestNextMoves;
      bestNextMoves.reserve(moves.size());

      std::for_each(std::execution::par, begin(moves), end(moves), [&](const auto& move) {
         if (const auto nextMove = processMoves(allMoves(move, side), !side, plies - 1);
             nextMove.has_value())
         {
            std::lock_guard<std::mutex> lock(bestMovesMx);
            bestNextMoves.push_back(*nextMove);
         }
      });

      return bestPosition(bestNextMoves, side);
   }
   else
   {
      // Final step. Simply find best of the given moves.
      return bestPosition(moves, side);
   }
}


} // namespace


///////////////////

std::optional<Position> makeMove(const Position& pos, Color side, std::size_t turns)
{
   // Convert turns (one move of each player) to plies (one move of one player).
   return processMoves(allMoves(pos, side), side, 2 * turns);
}
