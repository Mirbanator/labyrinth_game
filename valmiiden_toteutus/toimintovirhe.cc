
/**
 *	\version $Id: toimintovirhe.cc 2677 2013-02-20 13:03:17Z voutilai $
 *  \file toimintovirhe.cc
 *  \brief Toimintovirhe-luokan toteutus. ($Revision: 2677 $)
 *  \author ©2010 Eero Salonen <eero.j.salonen@tut.fi>
 */
 
#include "../toimintovirhe.hh"
 
#include "hyodykkeet.hh"

// Standardikirjastot
#include <map>
using std::map;

// Using-lauseet otsikkotiedostossa käytteen otetuille asioille.
using std::basic_ostream;
using std::string;

using Julkinen::Toimintovirhe;


namespace
{
    typedef
    map<Toimintovirhe::Virhekoodi, char const*>
    Virheviestit;

    typedef
    Virheviestit::value_type
    Virheviesti;

    Virheviestit::value_type const VIRHEVIESTIARVOT[] = {
            
			Virheviesti(
                    Toimintovirhe::VIRHE_EI_VOITU_LIIKKUA_ANNETTUA_MAARAA,
					"Vuorossa oleva pelaaja ei voi liikkua annettuun suuntaan annettua maaraa."
				),
			Virheviesti(
                    Toimintovirhe::VIRHE_IRTOPALAA_EI_OLE_TYONNETTY,
					"Vuorossa oleva pelaaja ei ole tyontanyt irtopalaa."
				),
			Virheviesti(
                    Toimintovirhe::VIRHE_IRTOPALAA_ON_JO_TYONNETTY,
					"Pelaaja on jo tyontanyt palaa talla vuorolla."
				),
			Virheviesti(
                    Toimintovirhe::VIRHE_PELAAJA_EI_OLE_LIIKKUNUT,
					"Pelaajaa ei ole liikkunut ennen vuoron vaihdon kutsua."
				),
            Virheviesti(
                    Toimintovirhe::VIRHE_TUNNISTAMATON,
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
    muunnaViestiksi(Toimintovirhe::Virhekoodi virhe)
    {
        Virheviestit::const_iterator viesti(VIRHEVIESTIT.find(virhe));

        if (VIRHEVIESTIT.end() == viesti)
        {
            viesti = VIRHEVIESTIT.find(Toimintovirhe::VIRHE_TUNNISTAMATON);
        }

        return viesti->second;
    }
*/
}


Toimintovirhe::Toimintovirhe(std::string const& virheviesti)
    : Virhe(virheviesti), virhe_(VIRHE_TUNNISTAMATON)
{
}

Toimintovirhe::Toimintovirhe(Virhekoodi virhekoodi)
    : Virhe(muunna(virhekoodi, VIRHEVIESTIT, VIRHE_TUNNISTAMATON)),
        virhe_(virhekoodi)
{
}

Toimintovirhe::Toimintovirhe(Toimintovirhe const& toinen)
    : Virhe(toinen), virhe_(toinen.virhe_)
{
}

Toimintovirhe::Virhekoodi Toimintovirhe::virhe() const
{
    return virhe_;
}

Toimintovirhe&
Toimintovirhe::operator=(Toimintovirhe const& toinen)
{
    Virhe::operator=(toinen);

    if (this != &toinen)
    {
        virhe_ = toinen.virhe_;
    }

    return *this;
}

basic_ostream<char>&
Toimintovirhe::tulosta(basic_ostream<char>& tuloste)
    const
{
    tuloste << "VIRHE: ";
    Virhe::tulosta(tuloste);

    return tuloste;
}
