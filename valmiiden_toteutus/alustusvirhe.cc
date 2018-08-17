
/**
 *	\version $Id: alustusvirhe.cc 2677 2013-02-20 13:03:17Z voutilai $
 *  \file alustusvirhe.cc
 *  \brief Alustusvirhe-luokan toteutus. ($Revision: 2677 $)
 *  \author ©2010 Eero Salonen <eero.j.salonen@tut.fi>
 */

#include "../alustusvirhe.hh"
#include <string>
 
#include "hyodykkeet.hh"

// Standardikirjastot
#include <map>
using std::map;

// Using-lauseet otsikkotiedostossa käytteen otetuille asioille.
using std::basic_ostream;
using std::string;

using Julkinen::Alustusvirhe;


namespace
{
    typedef
    map<Alustusvirhe::Virhekoodi, char const*>
    Virheviestit;

    typedef
    Virheviestit::value_type
    Virheviesti;

    Virheviestit::value_type const VIRHEVIESTIARVOT[] = {
            Virheviesti(
                    Alustusvirhe::VIRHE_PALASSA_ON_JO_ESINE,
                    "Koordinaatissa on jo esine."
                  ),
            Virheviesti(
                    Alustusvirhe::VIRHEELLINEN_SIJAINTI,
                    "Annettu koordinaatti on pelialueen ulkopuolella."
                  ),
            
            Virheviesti(
                    Alustusvirhe::VIRHE_ANNETTUA_PELAAJAA_EI_LOYTYNYT,
                    "Esineelle annettua pelaajaa ei loytynyt pelaajien joukosta."
                  ),
            Virheviesti(
                    Alustusvirhe::VIRHE_LIIKAA_PARAMETREJA,
                    "Liikaa parametreja."
                  ),
            Virheviesti(
                    Alustusvirhe::VIRHE_TUNNISTAMATON,
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
    muunnaViestiksi(Alustusvirhe::Virhekoodi virhe)
    {
        Virheviestit::const_iterator viesti(VIRHEVIESTIT.find(virhe));

        if (VIRHEVIESTIT.end() == viesti)
        {
            viesti = VIRHEVIESTIT.find(Alustusvirhe::VIRHE_TUNNISTAMATON);
        }

        return viesti->second;
    }
 */
}


Alustusvirhe::Alustusvirhe(std::string const& virheviesti)
    : Virhe(virheviesti), virhe_(VIRHE_TUNNISTAMATON)
{
}

Alustusvirhe::Alustusvirhe(Virhekoodi virhekoodi)
    : Virhe(muunna(virhekoodi, VIRHEVIESTIT, VIRHE_TUNNISTAMATON)),
        virhe_(virhekoodi)
{
}

Alustusvirhe::Alustusvirhe(Alustusvirhe const& toinen)
    : Virhe(toinen), virhe_(toinen.virhe_)
{
}

Alustusvirhe::Virhekoodi
Alustusvirhe::virhe()
    const
{
    return virhe_;
}

Alustusvirhe&
Alustusvirhe::operator=(Alustusvirhe const& toinen)
{
    Virhe::operator=(toinen);

    if (this != &toinen)
    {
        virhe_ = toinen.virhe_;
    }

    return *this;
}

basic_ostream<char>&
Alustusvirhe::tulosta(basic_ostream<char>& tuloste)
    const
{
    tuloste << "VIRHE: ";
    Virhe::tulosta(tuloste);

    return tuloste;
}
