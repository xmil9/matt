//
// Feb-2021, Michael Lindner
// MIT license
//
#pragma once
#include <cassert>
#include <optional>


///////////////////

struct Square
{
   Square(char f, char r) : file{f}, rank{r} {}
   Square(int f, int r) : file{static_cast<char>(f)}, rank{static_cast<char>(r)} {}

   char file = 0;
   char rank = 0;

   operator bool() const
   {
      return file >= '1' && file <= '8' && rank >= 'a' && rank <= 'h';
   }
   bool operator!() const { return !operator bool(); }
};


inline bool operator==(Square a, Square b)
{
   return a.file == b.file && a.rank == b.rank;
}


///////////////////

struct Offset
{
   Offset(int df_, int dr_) : df{df_}, dr{dr_}
   {
      assert(isValidOffset(df) && isValidOffset(dr));
   }

   static bool isValidOffset(int offset) { return -7 <= offset && offset <= 7; }

   int df = 0;
   int dr = 0;
};


///////////////////

inline std::optional<Square> operator+(Square from, Offset off)
{
   const Square to{from.file + off.df, from.rank + off.dr};
   if (to)
      return to;
   return std::nullopt;
}


inline std::optional<Square> operator+(std::optional<Square> from, Offset off)
{
   if (from.has_value())
      return *from + off;
   return std::nullopt;
}
