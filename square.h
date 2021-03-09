//
// Feb-2021, Michael Lindner
// MIT license
//
#pragma once
#include <cassert>
#include <optional>
#include <string>
#include <utility>


///////////////////

class Square
{
 public:
   Square() = default;
   Square(char f, char r);
   Square(int f, int r);

   char file() const { return m_file; }
   char rank() const { return m_rank; }
   std::string notate() const;

   operator bool() const;

   friend void swap(Square& a, Square& b) noexcept
   {
      using std::swap;
      swap(a.m_file, b.m_file);
      swap(a.m_rank, b.m_rank);
   }

 private:
   char m_file = 0;
   char m_rank = 0;
};


inline Square::Square(char f, char r) : m_file{f}, m_rank{r}
{
   const bool isValidFile = m_file >= 'a' && m_file <= 'h';
   const bool isValidRank = m_rank >= '1' && m_rank <= '8';
   if (!isValidFile || !isValidRank)
   {
      m_file = 0;
      m_rank = 0;
   }
}

inline Square::Square(int f, int r) : Square{static_cast<char>(f), static_cast<char>(r)}
{
}

inline std::string Square::notate() const
{
   if (operator bool())
      return std::string{m_file} + std::string{m_rank};
   return "";
}

inline Square::operator bool() const
{
   return m_file != 0 && m_rank != 0;
}

inline Square denotateSquare(std::string_view notation)
{
   if (notation.size() < 2)
      return Square{};
   return Square{notation[0], notation[1]};
}

inline bool operator==(Square a, Square b)
{
   return a.file() == b.file() && a.rank() == b.rank();
}

inline bool operator!=(Square a, Square b)
{
   return !(a == b);
}


///////////////////

class Offset
{
 public:
   Offset() = default;
   Offset(int df, int dr);

   int df() const { return m_df; }
   int dr() const { return m_dr; }

   friend void swap(Offset& a, Offset& b) noexcept
   {
      using std::swap;
      swap(a.m_df, b.m_df);
      swap(a.m_dr, b.m_dr);
   }

 private:
   int m_df = 0;
   int m_dr = 0;
};


inline Offset::Offset(int df, int dr) : m_df{df}, m_dr{dr}
{
}

inline bool operator==(Offset a, Offset b)
{
   return a.df() == b.df() && a.dr() == b.dr();
}

inline bool operator!=(Offset a, Offset b)
{
   return !(a == b);
}

inline Offset operator*(Offset off, int v)
{
   return Offset{off.df() * v, off.dr() * v};
}

inline Offset operator*(int v, Offset off)
{
   return off * v;
}


///////////////////

inline std::optional<Square> operator+(Square from, Offset off)
{
   const Square to{from.file() + off.df(), from.rank() + off.dr()};
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
