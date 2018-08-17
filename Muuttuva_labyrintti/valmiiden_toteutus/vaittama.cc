/**
 *  \file vaittama.cc
 *  \brief Pysyväisväittämien tarkistamisen toteutus.
 *  \author ©2010 Jarmo Jaakkola <jarmo.jaakkola@tut.fi>,
 *      TTY Ohjelmistotekniikka
 */


#include "../vaittama.hh"   // Esittely

#include "include/invarianttivirhe.hh"
#include "include/esiehtovirhe.hh"
#include "include/jalkiehtovirhe.hh"


#include <cassert>


void
Julkinen::vaittamaToteutus(
        VaittamaTyyppi tyyppi,
        bool vaite,
        char const* lauseke,
        char const* tiedosto,
        unsigned int rivi,
        char const* funktio
      )
{
    if (!vaite)
    {
        switch (tyyppi)
        {
            case INVARIANTTIVAITTAMA:
            {
                throw Invarianttivirhe(lauseke, tiedosto, rivi, funktio);

            }

            case ESIEHTOVAITTAMA:
            {
                throw Esiehtovirhe(lauseke, tiedosto, rivi, funktio);

            }

            case JALKIEHTOVAITTAMA:
            {
                throw Jalkiehtovirhe(lauseke, tiedosto, rivi, funktio);

            }

       
        }
       
       assert(false && "Tuntematon väittämätyyppi!");
       
       
    }
}
