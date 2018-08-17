/**
 *	\version $Id: Bittikartta.cc 1800 2011-02-05 06:54:47Z salone58 $
 *  \file  Bittikartta.cc
 *  \brief Bittikartta-luokan toteutus ($Revision: 1800 $)
 *  \author ©2010 Eero Salonen <eero.j.salonen@tut.fi> 
 */

#include <iostream>
#include <cassert>

#include "include/Bittikartta.hh"

Dim Bittikartta::indeksi(Dim x, Dim y) const
{
  return (x_+1)*y + x;
}

Bittikartta::Bittikartta(Dim x, Dim y)
  : x_(x), y_(y), kartta_((x+1)*y, ' ')
{
  for (Dim i=0; i!=y_; ++i)
  {
    kartta_[indeksi(x_, i)] = '\n';
  }
}

Bittikartta::~Bittikartta()
{
}

void Bittikartta::vaakateksti(Dim x, Dim y, std::string const& teksti)
{
  assert(y < y_ && x + teksti.length() <= x_);
  kartta_.replace(indeksi(x, y), teksti.length(), teksti);
}

void Bittikartta::pystyteksti(Dim x, Dim y, std::string const& teksti)
{
  assert(x < x_ && y + teksti.length() <= y_);
  for (Dim i=0; i!=teksti.length(); ++i)
  {
    kartta_[indeksi(x, y+i)] = teksti[i];
  }
}

void Bittikartta::suorakaide(Dim x, Dim y, Dim lev, Dim kork, char merkki)
{
  suorakaide(x, y, lev, kork,
	     merkki,
	     merkki, merkki, merkki,
	     merkki, merkki, merkki,
	     merkki, merkki, merkki, merkki, merkki, merkki, merkki, merkki);
}

void Bittikartta::suorakaide(Dim x, Dim y, Dim lev, Dim kork,
			     char k, // Yhden merkin kaide
			     char v, char kv, char o, // Vaakaviiva
			     char yy, char kp, char a, // Pystyviiva
			     char vy, char yv, char oy, char vp, char op,
			     char va, char av, char oa // Suorakaide
  )
{
  assert(x+lev <= x_ && y+kork <= y_);
  if (kork == 0 || lev == 0) { return; }

  if (kork == 1)
  {
    if (lev == 1)
    { // Yhden merkin kokoinen
      kartta_[indeksi(x, y)] = k;
    }
    else
    { // Vaakaviiva
      kartta_[indeksi(x, y)] = v;
      kartta_[indeksi(x+lev-1, y)] = o;
      vaakaviiva(x+1, y, lev-2, kv);
    }
  }
  else
  {
    if (lev == 1)
    { // Pystyviiva
      kartta_[indeksi(x, y)] = yy;
      kartta_[indeksi(x, y+kork-1)] = a;
      pystyviiva(x, y+1, kork-2, kp);
    }
    else
    { // Suorakaide
      kartta_[indeksi(x, y)] = vy;
      kartta_[indeksi(x+lev-1, y)] = oy;
      kartta_[indeksi(x, y+kork-1)] = va;
      kartta_[indeksi(x+lev-1, y+kork-1)] = oa;
      vaakaviiva(x+1, y, lev-2, yv);
      vaakaviiva(x+1, y+kork-1, lev-2, av);
      pystyviiva(x, y+1, kork-2, vp);
      pystyviiva(x+lev-1, y+1, kork-2, op);
    }
  }
}

void Bittikartta::vaakaviiva(Dim x, Dim y, Dim lev, char merkki)
{
  assert(x+lev <= x_ && y < y_);
  if (lev == 0) { return; }

  for (Dim i=0; i!=lev; ++i)
  {
    kartta_[indeksi(x+i, y)] = merkki;
  }
}

void Bittikartta::pystyviiva(Dim x, Dim y, Dim kork, char merkki)
{
  assert(x < x_ && y+kork <= y_);
  if (kork == 0) { return; }

  for (Dim i=0; i!=kork; ++i)
  {
    kartta_[indeksi(x, y+i)] = merkki;
  }
}

void Bittikartta::tyhjenna()
{
  for (Dim y=0; y != y_; ++y)
  {
    vaakaviiva(0, y, x_, ' ');
  }
}

void Bittikartta::tulosta(std::ostream& virta) const
{
  virta << kartta_;
}


