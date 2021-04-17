//
// Feb-2021, Michael Lindner
// MIT license
//
#pragma once
#include <string>
#include <vector>


///////////////////

class Record
{
 public:
   Record() = default;
   explicit Record(std::string pos);

   const std::string& initialPosition() const { return m_initialPos; }
   const std::string& moves() const { return m_moves; }
   void add(const std::string& move);

 private:
   std::string m_initialPos;
   std::string m_moves;
};


inline Record::Record(std::string pos) : m_initialPos{std::move(pos)}
{
}


inline void Record::add(const std::string& move)
{
   if (!m_moves.empty())
      m_moves += " ";
   m_moves += move;
}