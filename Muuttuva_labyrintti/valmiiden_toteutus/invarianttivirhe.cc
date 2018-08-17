/**
 *  \file invarianttivirhe.cc
 *  \brief Julkinen::Invarianttivirhe-luokan toteutus.
 *  \author ©2010 Jarmo Jaakkola <jarmo.jaakkola@tut.fi>,
 *      TTY Ohjelmistotekniikka
 */


#include "include/invarianttivirhe.hh"  // Esittely.

#include <ostream>
using std::basic_ostream;

using Julkinen::Invarianttivirhe;


Invarianttivirhe::Invarianttivirhe(
        char const* lauseke,
        char const* tiedostonNimi,
        unsigned int rivinumero,
        char const* funktionNimi
      )
    throw()
    : Vaittamavirhe(lauseke, tiedostonNimi, rivinumero, funktionNimi)
{
}

Invarianttivirhe::~Invarianttivirhe()
    throw()
{
}

basic_ostream<char>&
Invarianttivirhe::tulosta(basic_ostream<char>& tuloste)
    const
{
    tuloste << "Luokkainvariantin ";
    Vaittamavirhe::tulosta(tuloste);

    return tuloste;
}

