/**
 *	\version $Id: nayttovirhe.cc 2677 2013-02-20 13:03:17Z voutilai $
 *  \file nayttovirhe.cc
 *  \brief Nayttovirhe-luokan toteutus. ($Revision: 2677 $)
 *  \author ©2010 Eero Salonen <eero.j.salonen@tut.fi>
 */

#include "../nayttovirhe.hh"
#include <string>
 
#include "hyodykkeet.hh"

// Standardikirjastot
#include <map>
using std::map;

// Using-lauseet otsikkotiedostossa käytteen otetuille asioille.
using std::basic_ostream;
using std::string;

using Julkinen::Nayttovirhe;


namespace
{
    typedef
    map<Nayttovirhe::Virhekoodi, char const*>
    Virheviestit;

    typedef
    Virheviestit::value_type
    Virheviesti;

    Virheviestit::value_type const VIRHEVIESTIARVOT[] = {
            Virheviesti(
                    Nayttovirhe::VIRHE_TUNNISTAMATON,
                    "Tunnistamaton virhe."
                  )
          };

    Virheviestit VIRHEVIESTIT(
            VIRHEVIESTIARVOT,
            VIRHEVIESTIARVOT +
                sizeof(VIRHEVIESTIARVOT)/sizeof(Virheviestit::value_type)
          );
/*
    char const*
    muunnaViestiksi(Nayttovirhe::Virhekoodi virhe)
    {
        Virheviestit::const_iterator viesti(VIRHEVIESTIT.find(virhe));

        if (VIRHEVIESTIT.end() == viesti)
        {
            viesti = VIRHEVIESTIT.find(Nayttovirhe::VIRHE_TUNNISTAMATON);
        }

        return viesti->second;
    }
*/
}


Nayttovirhe::Nayttovirhe(std::string const& virheviesti)
    : Virhe(virheviesti), virhe_(VIRHE_TUNNISTAMATON)
{
}

Nayttovirhe::Nayttovirhe(Virhekoodi virhekoodi)
    : Virhe(muunna(virhekoodi, VIRHEVIESTIT, VIRHE_TUNNISTAMATON)),
        virhe_(virhekoodi)
{
}

Nayttovirhe::Nayttovirhe(Nayttovirhe const& toinen)
    : Virhe(toinen), virhe_(toinen.virhe_)
{
}

Nayttovirhe::Virhekoodi
Nayttovirhe::virhe()
    const
{
    return virhe_;
}

Nayttovirhe&
Nayttovirhe::operator=(Nayttovirhe const& toinen)
{
    Virhe::operator=(toinen);

    if (this != &toinen)
    {
        virhe_ = toinen.virhe_;
    }

    return *this;
}

basic_ostream<char>&
Nayttovirhe::tulosta(basic_ostream<char>& tuloste)
    const
{
    tuloste << "VIRHE: ";
    Virhe::tulosta(tuloste);

    return tuloste;
}
