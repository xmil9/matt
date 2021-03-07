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

   void record(const std::string& move) { m_moves.push_back(move); }

 private:
   std::string m_initialPos;
   std::vector<std::string> m_moves;
};


inline Record::Record(std::string pos) : m_initialPos{std::move(pos)}
{
}
