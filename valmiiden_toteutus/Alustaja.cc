/**
 *	\version $Id: Alustaja.cc 1800 2011-02-05 06:54:47Z salone58 $
 *  \file  Alustaja.cc
 *  \brief Alustaja-luokan toteutus($Revision: 1800 $)
 *  \author ©2010 Eero Salonen <eero.j.salonen@tut.fi>
 */

#include "include/Alustaja.hh"
#include "../luettelotyypit.hh"
#include "../debug.hh"

#include <iostream>
#include <algorithm>
#include <ctime>
#include <cassert>

//STL Kirjastot.
/**
 *	Jos k‰‰nt‰j‰ on GNUG pohjainen esim. gcc tai tutg++ esitell‰‰n
 *  luokkavakiot.
 */
#	if defined(__GNUG__)
unsigned int const Alustaja::LABYRINTIN_KORKEUS;
unsigned int const Alustaja::LABYRINTIN_LEVEYS;
char const Alustaja::EI_ESINETTA;
#   endif

Alustaja::Alustaja(unsigned int pelaajia)
  : erikoisesineidenmaara_(4), pelaajia_(pelaajia), labyrintinRuudut(25),
	labyrintinRotaatiot(25, 1), labyrintinEsineet(25, EI_ESINETTA),
	pelaajienEsineet(4), labyrintinErikoispalat(25, EI_ESINETTA), kohdePalat(), annettuKohde(0)
{
  assert(2 <= pelaajia && pelaajia <= 4);

  siemen1_ = static_cast<unsigned long int>(std::time(NULL));
  siemen2_ = siemen1_ % 7 + 1;

  alkusiemen_ = siemen1_;

  arvoAlkutilanne();
}

Alustaja::Alustaja(unsigned int pelaajia, unsigned long int siemen)
  : alkusiemen_(siemen), siemen1_(siemen), siemen2_(siemen % 7 + 1),
    erikoisesineidenmaara_(4), pelaajia_(pelaajia), labyrintinRuudut(25),
	labyrintinRotaatiot(25, 1), labyrintinEsineet(25, EI_ESINETTA),
	pelaajienEsineet(4), labyrintinErikoispalat(25, EI_ESINETTA), kohdePalat(), annettuKohde(0)
{
  assert(2 <= pelaajia && pelaajia <= 4);

  arvoAlkutilanne();
}

Alustaja::~Alustaja()
{

}

Alustaja::Ruututyyppi Alustaja::annaIrtopalanTyyppi() const
{
  return irtopala_;
}

Alustaja::Ruututyyppi Alustaja::annaKoordinaatinRuututyyppi(unsigned int x,
							    unsigned int y) const
{
  assert(1 <= x && x <= LABYRINTIN_LEVEYS);
  assert(1 <= y && y <= LABYRINTIN_KORKEUS);

  return labyrintinRuudut.at((x - 1) + (y - 1) * LABYRINTIN_LEVEYS);
}

unsigned int Alustaja::annaKoordinaatinRotaatio(unsigned int x,
						unsigned int y) const
{
  assert(1 <= x && x <= LABYRINTIN_LEVEYS);
  assert(1 <= y && y <= LABYRINTIN_KORKEUS);

  return labyrintinRotaatiot.at((x - 1) + (y - 1) * LABYRINTIN_LEVEYS);
}

char Alustaja::annaKoordinaatinEsine(unsigned int x, unsigned int y) const
{
  assert(1 <= x && x <= LABYRINTIN_LEVEYS);
  assert(1 <= y && y <= LABYRINTIN_KORKEUS);

  return labyrintinEsineet.at((x - 1) + (y - 1) * LABYRINTIN_LEVEYS);
}

char Alustaja::annaKoordinaatinErikoispala(unsigned int x, unsigned int y) const
{
   
     assert(1 <= x && x <= LABYRINTIN_LEVEYS);
     assert(1 <= y && y <= LABYRINTIN_KORKEUS);
   
     return labyrintinErikoispalat.at((x - 1) + (y - 1) * LABYRINTIN_LEVEYS);
}

Julkinen::Koordinaatti Alustaja::annaSeuraavaKohde()
{
   Julkinen::Koordinaatti kohde((kohdePalat.at(annettuKohde) % LABYRINTIN_LEVEYS) + 1, (kohdePalat.at(annettuKohde)+1) / LABYRINTIN_LEVEYS + 1);
   annettuKohde++;
   if ( annettuKohde == kohdePalat.size() )
   {
      annettuKohde = 0;
   }
   
   return kohde;
   
}


std::vector<char> Alustaja::annaPelaajanEsinelista(unsigned int pelaaja) const
{
  assert(pelaaja < pelaajia_);

  return pelaajienEsineet[pelaaja];
}

unsigned long int Alustaja::annaSiemenluku() const
{
  return alkusiemen_;
}

// private

void Alustaja::arvoAlkutilanne()
{
  std::vector<Ruututyyppi> ruudut;
  std::vector<Ruututyyppi>::iterator iter;

  ruudut.insert(ruudut.begin(), 9, Alustaja::L);
  ruudut.insert(ruudut.begin(), 9, Alustaja::T);
  ruudut.insert(ruudut.begin(), 8, Alustaja::I);

  // arvotaan irtopala

  iter = ruudut.begin() + static_cast<const long>(arvo(25));
  irtopala_ = *iter;
  ruudut.erase(iter);

  // arvotaan ruutujen j‰rjestys ja joka ruudulle rotaatio

  for(int i = 24; i >= 0; i--) {
    unsigned long int ruutuNro = arvo(static_cast<unsigned int>(i));
    iter = ruudut.begin() + static_cast<const long>(ruutuNro);

    labyrintinRuudut[static_cast<unsigned long>(i)] = *iter;
    labyrintinRotaatiot[static_cast<unsigned long>(i)] = static_cast<unsigned int>(arvo(3) + 1);

    ruudut.erase(iter);
  }

  // arvotaan jokaiselle esineelle oma ruutu

  for(char esine = 'a'; esine < 'm'; esine++) {
    unsigned long int ruutuun = arvo(24);

    while(labyrintinEsineet[ruutuun] != EI_ESINETTA) {
      ruutuun = arvo(24);
    }

    labyrintinEsineet[ruutuun] = esine;
  }

  // arvotaan erikoisesineet
  for(unsigned int i = 0; i < erikoisesineidenmaara_; i++) {

	unsigned long int esinenro = arvo(2);

     char esine =' ';
	switch(esinenro)
	{
         case 0:
           {   
              esine = 'T';
              unsigned int kohde = static_cast<unsigned int>(arvo(23));
              while ( std::find( kohdePalat.begin(), kohdePalat.end(), kohde) != kohdePalat.end() )
              {
                 kohde = static_cast<unsigned int>(arvo(23));
              }
              kohdePalat.push_back(kohde);
              break;
           }
         case 1: 
           esine = 'K';
           break;
         case 2:	
           esine = 'S';
           break;

	}
	unsigned long int ruutuun = arvo(24);
     while(labyrintinErikoispalat[ruutuun] != EI_ESINETTA) {
        ruutuun = arvo(24);
     }
     
     labyrintinErikoispalat[ruutuun] = esine;
  }

  // arvotaan jokaiselle pelaajalle lista etsitt‰vist‰ esineist‰

  unsigned int pelaajalleEsineita = 12 / pelaajia_;
  std::vector<char> esineet;
  std::vector<char>::iterator esine_iter;

  for(char esine = 'a'; esine < 'm'; esine++) {
    esineet.push_back(esine);
  }

  for(unsigned int i = 0; i < pelaajia_; i++) {
    for(unsigned int j = 0; j < pelaajalleEsineita; j++) {
      esine_iter = esineet.begin() + static_cast<const long>(arvo(11 - i*pelaajalleEsineita - j));
      pelaajienEsineet[i].push_back(*esine_iter);
      esineet.erase(esine_iter);
    }
  }
}

unsigned long int Alustaja::raakaArvo()
{
  siemen1_ = 15625 * siemen1_ + 22221;
  siemen2_ = 15625 * siemen2_ + (siemen1_ >> 16);
  siemen1_ &= 0xFFFFul;
  siemen2_ &= 0xFFFFul;

  return (((siemen1_ & 0x7FFFul) << 16) | siemen2_);
}

unsigned long int Alustaja::arvo(unsigned long int raja)
{
  // Lasketaan rajaa vastaava raakaraja
  unsigned long int raakaraja = raakamax_ - (raakamax_ - raja) % (raja+1);
  unsigned long int raakaluku = 0;

  do { raakaluku = raakaArvo(); } while (raakaluku > raakaraja);

  // Palautetaan tulos skaalattuna v‰lille 0 .. raja
  unsigned long int luku = raakaluku / (raakaraja/(raja+1) + 1);
  assert(luku <= raja);

  return luku;
}

