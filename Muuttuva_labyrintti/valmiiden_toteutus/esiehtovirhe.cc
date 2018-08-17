/**
 *  \file esiehtovirhe.cc
 *  \brief Julkinen::Esiehtovirhe-luokan toteutus.
 *  \author ©2010 Jarmo Jaakkola <jarmo.jaakkola@tut.fi>,
 *      TTY Ohjelmistotekniikka
 */


#include "include/esiehtovirhe.hh"  // Esittely.

#include <ostream>
using std::basic_ostream;

using Julkinen::Esiehtovirhe;


Esiehtovirhe::Esiehtovirhe(
        char const* lauseke,
        char const* tiedostonNimi,
        unsigned int rivinumero,
        char const* funktionNimi
      )
    throw()
    : Vaittamavirhe(lauseke, tiedostonNimi, rivinumero, funktionNimi)
{
}

Esiehtovirhe::~Esiehtovirhe()
    throw()
{
}

basic_ostream<char>&
Esiehtovirhe::tulosta(basic_ostream<char>& tuloste)
    const
{
    tuloste << "Esiehdon ";
    Vaittamavirhe::tulosta(tuloste);

    return tuloste;
}
