/**
 *	\version $Id: komentovirhe.cc 2677 2013-02-20 13:03:17Z voutilai $
 *  \file komentovirhe.cc
 *  \brief Julkinen::Komentovirhe-luokan toteutus. ($Revision: 2677 $)
 *  \author ©2010 Jarmo Jaakkola <jarmo.jaakkola@tut.fi>,
 *      TTY Ohjelmistotekniikka
 */


#include "../komentovirhe.hh" // Esittely.


#include "hyodykkeet.hh"

// Standardikirjastot
#include <map>
using std::map;

// Using-lauseet otsikkotiedostossa käytteen otetuille asioille.
using std::basic_ostream;
using std::string;

using Julkinen::Komentovirhe;


namespace
{
    typedef
    map<Komentovirhe::Virhekoodi, char const*>
    Virheviestit;

    typedef
    Virheviestit::value_type
    Virheviesti;

    Virheviestit::value_type const VIRHEVIESTIARVOT[] = {
            Virheviesti(
                    Komentovirhe::VIRHE_OLEMATON_PAIKKA,
                    "Tyonto paikka ei ole pelialueella."
                  ),
            Virheviesti(
                    Komentovirhe::VIRHE_VIRHEELLINEN_ROTAATIO,
                    "Rotaatio on virheellinen."
                  ),
            Virheviesti(
                    Komentovirhe:: VIRHE_TUNNISTAMATON_PARAMETRI,
                    "Parametria ei tunnistettu."
                  ),
            Virheviesti(
                    Komentovirhe::VIRHE_TUNNISTAMATON_KOMENTO,
                    "Tunnistamaton komento."
                  ),
            Virheviesti(
                    Komentovirhe::VIRHE_LIIKAA_PARAMETREJA,
                    "Komennolla on liikaa parametreja."
                  ),
            Virheviesti(
                    Komentovirhe::VIRHE_TUNNISTAMATON,
                    "unnistamaton virhe.."
                  )
          };

    Virheviestit VIRHEVIESTIT(
            VIRHEVIESTIARVOT,
            VIRHEVIESTIARVOT +
                sizeof(VIRHEVIESTIARVOT)/sizeof(Virheviestit::value_type)
          );
/*
    char const*
    muunnaViestiksi(Komentovirhe::Virhekoodi virhe)
    {
        Virheviestit::const_iterator viesti(VIRHEVIESTIT.find(virhe));

        if (VIRHEVIESTIT.end() == viesti)
        {
            viesti = VIRHEVIESTIT.find(Komentovirhe::VIRHE_TUNNISTAMATON);
        }

        return viesti->second;
    }
*/
}


Komentovirhe::Komentovirhe(std::string const& virheviesti)
    : Virhe(virheviesti), virhe_(VIRHE_TUNNISTAMATON)
{
}

Komentovirhe::Komentovirhe(Virhekoodi virhekoodi)
    : Virhe(muunna(virhekoodi, VIRHEVIESTIT, VIRHE_TUNNISTAMATON)),
        virhe_(virhekoodi)
{
}

Komentovirhe::Komentovirhe(Komentovirhe const& toinen)
    : Virhe(toinen), virhe_(toinen.virhe_)
{
}

Komentovirhe::Virhekoodi
Komentovirhe::virhe()
    const
{
    return virhe_;
}

Komentovirhe&
Komentovirhe::operator=(Komentovirhe const& toinen)
{
    Virhe::operator=(toinen);

    if (this != &toinen)
    {
        virhe_ = toinen.virhe_;
    }

    return *this;
}

basic_ostream<char>&
Komentovirhe::tulosta(basic_ostream<char>& tuloste)
    const
{
    tuloste << "VIRHE: ";
    Virhe::tulosta(tuloste);

    return tuloste;
}
