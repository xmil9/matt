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

inline bool isValidFile(char file)
{
   return file >= 'a' && file <= 'h';
}

inline bool isValidRank(char rank)
{
   return rank >= '1' && rank <= '8';
}


///////////////////

class Square
{
 public:
   Square() = default;
   explicit Square(std::string_view notation);

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


inline Square::Square(std::string_view notation) : Square{}
{
   if (notation.size() >= 2 && isValidFile(notation[0]) && isValidRank(notation[1]))
   {
      m_file = notation[0];
      m_rank = notation[1];
   }
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

inline bool operator==(Square a, Square b)
{
   return a.file() == b.file() && a.rank() == b.rank();
}

inline bool operator!=(Square a, Square b)
{
   return !(a == b);
}

inline Square operator"" _sq(const char* str, std::size_t)
{
   return Square{str};
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
   const char toFile = from.file() + static_cast<char>(off.df());
   const char toRank = from.rank() + static_cast<char>(off.dr());
   if (isValidFile(toFile) && isValidRank(toRank))
   {
      std::string to(1, toFile);
      to += toRank;
      return Square{to};
   }
   return std::nullopt;
}


inline std::optional<Square> operator+(Offset off, Square from)
{
   return from + off;
}


inline std::optional<Square> operator+(std::optional<Square> from, Offset off)
{
   if (from.has_value())
      return *from + off;
   return std::nullopt;
}


inline std::optional<Square> operator+(Offset off, std::optional<Square> from)
{
   return from + off;
}
