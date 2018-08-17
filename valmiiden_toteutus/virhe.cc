//#ifndef JULKINEN_VIRHE_HH
//#define JULKINEN_VIRHE_HH

/**
 *	\version $Id: virhe.cc 1854 2011-02-17 03:21:07Z salone58 $
 *  \file virhe.cc
 *  \brief Julkinen::Virhe-luokan toteutus. ($Revision: 1854 $)
 *  \author ©2010 Jarmo Jaakkola <jarmo.jaakkola@tut.fi>,
 *      TTY Ohjelmistotekniikka
 */


#include "../virhe.hh"  // Esittely.

#include "hyodykkeet.hh"

#include <ostream>
using std::basic_ostream;
using std::endl;

// Using-lauseet otsikkotiedostossa käyttöön otetuille asioille.
using std::string;

using namespace Julkinen;

using Julkinen::Virhe;


Virhe::Virhe(std::string const& virheviesti)
    : viestinKopio_(cMerkkijonoksi(virheviesti)), viesti_(0)
{
}

Virhe::Virhe(char const* virheViesti)
    : viestinKopio_(), viesti_(virheViesti)
{
}

Virhe::Virhe(Virhe const& toinen)
    : viestinKopio_(toinen.viestinKopio_), viesti_(toinen.viesti_)
{
}

Virhe::~Virhe()
{
}

Virhe&
Virhe::operator=(Virhe const& toinen)
{
    if (this != &toinen)
    {
        viestinKopio_ = toinen.viestinKopio_;
        viesti_ = toinen.viesti_;
    }

    return *this;
}

char const*
Virhe::viesti()
    const
{
    return (viestinKopio_ ? viestinKopio_.get() : viesti_);
}

basic_ostream<char>&
Virhe::tulosta(basic_ostream<char>& tuloste)
    const
{
    tuloste << viesti();

    return tuloste;
}

/**
 *  \brief Tulosta virhe.
 *
 *  Virhe tulostetaan Virhe::tulosta()-metodilla.
 *	
 *  \param[in, out] tuloste Virta jonne tulostetaan.
 *  \param[in] virhe Tulostettava Virhe.
 *  \return \p tuloste
 *  \relates Julkinen::Virhe
 */
basic_ostream<char>&
Julkinen::operator<<(basic_ostream<char>& tuloste, Virhe const& virhe)
{
    return virhe.tulosta(tuloste);
}
