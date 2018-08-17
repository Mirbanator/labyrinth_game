/**
 *  \file jalkiehtovirhe.cc
 *  \brief Julkinen::Jalkiehtovirhe-luokan toteutus.
 *  \author ©2010 Jarmo Jaakkola <jarmo.jaakkola@tut.fi>,
 *      TTY Ohjelmistotekniikka
 */


#include "include/jalkiehtovirhe.hh"    // Esittely.

#include <ostream>
using std::basic_ostream;

using Julkinen::Jalkiehtovirhe;


Jalkiehtovirhe::Jalkiehtovirhe(
        char const* lauseke,
        char const* tiedostonNimi,
        unsigned int rivinumero,
        char const* funktionNimi
      )
    throw()
    : Vaittamavirhe(lauseke, tiedostonNimi, rivinumero, funktionNimi)
{
}

Jalkiehtovirhe::~Jalkiehtovirhe()
    throw()
{
}

basic_ostream<char>&
Jalkiehtovirhe::tulosta(basic_ostream<char>& tuloste)
    const
{
    tuloste << "Jälkiehdon ";
    Vaittamavirhe::tulosta(tuloste);

    return tuloste;
}
