/**
 *	\version $Id: logiikkavirhe.cc 1797 2011-02-03 01:56:31Z salone58 $
 *  \file logiikkavirhe.cc
 *  \brief Logiikkavirhe-luokan toteutus. ($Revision: 1797 $)
 *  \author ©2010 Eero Salonen <eero.j.salonen@tut.fi>
 */

#include "../logiikkavirhe.hh"
#include <string>
 
#include "hyodykkeet.hh"

// Standardikirjastot
#include <map>
using std::map;

// Using-lauseet otsikkotiedostossa käytteen otetuille asioille.
using std::basic_ostream;
using std::string;

using Julkinen::Logiikkavirhe;


namespace
{
    typedef
    map<Logiikkavirhe::Virhekoodi, char const*>
    Virheviestit;

    typedef
    Virheviestit::value_type
    Virheviesti;

    Virheviestit::value_type const VIRHEVIESTIARVOT[] = {
            Virheviesti(
                    Logiikkavirhe::VIRHE_TUNNISTAMATON,
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
    muunnaViestiksi(Logiikkavirhe::Virhekoodi virhe)
    {
        Virheviestit::const_iterator viesti(VIRHEVIESTIT.find(virhe));

        if (VIRHEVIESTIT.end() == viesti)
        {
            viesti = VIRHEVIESTIT.find(Logiikkavirhe::VIRHE_TUNNISTAMATON);
        }

        return viesti->second;
    }
*/
}


Logiikkavirhe::Logiikkavirhe(std::string const& virheviesti)
    : Virhe(virheviesti), virhe_(VIRHE_TUNNISTAMATON)
{
}

Logiikkavirhe::Logiikkavirhe(Virhekoodi virhekoodi)
    : Virhe(muunna(virhekoodi, VIRHEVIESTIT, VIRHE_TUNNISTAMATON)),
        virhe_(virhekoodi)
{
}

Logiikkavirhe::Logiikkavirhe(Logiikkavirhe const& toinen)
    : Virhe(toinen), virhe_(toinen.virhe_)
{
}

Logiikkavirhe::Virhekoodi
Logiikkavirhe::virhe()
    const
{
    return virhe_;
}

Logiikkavirhe&
Logiikkavirhe::operator=(Logiikkavirhe const& toinen)
{
    Virhe::operator=(toinen);

    if (this != &toinen)
    {
        virhe_ = toinen.virhe_;
    }

    return *this;
}

basic_ostream<char>&
Logiikkavirhe::tulosta(basic_ostream<char>& tuloste)
    const
{
    tuloste << "VIRHE: ";
    Virhe::tulosta(tuloste);

    return tuloste;
}
