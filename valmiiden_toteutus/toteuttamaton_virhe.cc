/**
 *  \file toteuttamaton_virhe.cc
 *  \brief Julkinen::ToteuttamatonVirhe-luokan toteutus. ($Revision: 2677 $)
 *  \author ©2010 Jarmo Jaakkola <jarmo.jaakkola@tut.fi>,
 *      TTY Ohjelmistotekniikka
 */


#include "../toteuttamaton_virhe.hh"    // Esittely

// Using-lauseet otsikkotiedostossa käyttöön otetuille asioille.
using Julkinen::ToteuttamatonVirhe;

using std::string;

ToteuttamatonVirhe::ToteuttamatonVirhe(std::string const& virheviesti)
    : Virhe(virheviesti)
{
}

ToteuttamatonVirhe::ToteuttamatonVirhe(char const* virheviesti)
    : Virhe(virheviesti)
{
}

ToteuttamatonVirhe::ToteuttamatonVirhe(ToteuttamatonVirhe const& toinen)
    : Virhe(toinen)
{
}


ToteuttamatonVirhe::~ToteuttamatonVirhe()
{
}

ToteuttamatonVirhe&
ToteuttamatonVirhe::operator=(ToteuttamatonVirhe const& toinen)
{
    Virhe::operator=(toinen);

    return *this;
}
