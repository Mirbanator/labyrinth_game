/**
 *	\version $Id: pala.hh 1797 2011-02-03 01:56:31Z salone58 $
 *  \file vaittamavirhe.cc
 *  \brief Julkinen::Vaittamavirhe-luokan toteutus.
 *  \authors ©2010 Jarmo Jaakkola <jarmo.jaakkola@tut.fi>,
 *      TTY Ohjelmistotekniikka @2011 Eero Salonen <eero.j.salonen@tut.fi>,
 *		TTY Ohjelmistotekniikka
 */


#include "include/vaittamavirhe.hh"

#include <ostream>
using std::basic_ostream;
using std::endl;

using Julkinen::Vaittamavirhe;


Vaittamavirhe::Vaittamavirhe(
        char const* lauseke,
        char const* tiedostonNimi,
        unsigned int rivinumero,
        char const* funktionNimi
      )
    throw()
    : Virhe(lauseke), tiedosto_(tiedostonNimi), rivi_(rivinumero),
        funktio_(funktionNimi)
{
}

Vaittamavirhe::Vaittamavirhe(Vaittamavirhe const& toinen)
    throw()
    : Virhe(toinen), tiedosto_(toinen.tiedosto_), rivi_(toinen.rivi_),
        funktio_(toinen.funktio_)
{
}

Vaittamavirhe::~Vaittamavirhe()
    throw()
{
    // Ei olla vastuussa osoittimien p‰‰ss‰ olevasta tiedosta.
}

char const*
Vaittamavirhe::tiedosto()
    const throw()
{
    return tiedosto_;
}

unsigned int
Vaittamavirhe::rivi()
    const throw()
{
    return rivi_;
}

char const*
Vaittamavirhe::funktio()
    const throw()
{
    return funktio_;
}

basic_ostream<char>&
Vaittamavirhe::tulosta(basic_ostream<char>& tuloste)
    const
{
    tuloste << "v‰itt‰m‰ ei pid‰ paikkaansa.\n"
            << "  v‰itt‰m‰:  " << viesti() << "\n"
            << "  tiedosto:  " << tiedosto_ << "\n"
            << "  rivi:      " << rivi_ << "\n";
    if (0 != funktio_)
    {
        tuloste << "  funktio:   " << funktio_ << "\n";
    }
    tuloste << endl;

    return tuloste;
}

Vaittamavirhe&
Vaittamavirhe::operator==(Vaittamavirhe const& toinen)
    throw()
{
    if (this != &toinen)
    {
        tiedosto_ = toinen.tiedosto_;
        rivi_ = toinen.rivi_;
        funktio_ = toinen.funktio_;
    }

    return *this;
}
