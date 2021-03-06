//
// Feb-2021, Michael Lindner
// MIT license
//
#include "position.h"
#include "move.h"
#include <algorithm>
#include <iterator>


///////////////////

Position::Position()
{
}


Position::Position(const std::vector<Piece>& pieces)
{
   pieces;
   assert(false && "todo");
}


Position::Position(const std::string& notation)
{
   notation;
   assert(false && "todo");
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


void Position::makeMove(const Move& move)
{
   const auto it = at(move.from());
   if (it != end(m_pieces))
   {
      assert(*it == move.piece());
      m_pieces.erase(it);
      m_pieces.push_back(move.piece());
      m_record.record(move.notation());
   }
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
