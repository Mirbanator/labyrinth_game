#ifndef JULKINEN_TOTEUTTAMATON_VIRHE_HH
#define JULKINEN_TOTEUTTAMATON_VIRHE_HH


/**
 *	\version $Id: toteuttamaton_virhe.hh 2660 2013-02-15 10:27:37Z bitti $
 *  \file toteuttamaton_virhe.hh
 *  \brief ToteuttamatonVirhe-luokan esittely.
 *  \author ©2010 Jarmo Jaakkola <jarmo.jaakkola@tut.fi>,
 *      TTY Ohjelmistotekniikka
 */


#include "virhe.hh" // Kantaluokka.

/// \namespace Julkinen
namespace
Julkinen
{
    /**
	 *	\class ToteuttamatonVirhe
     *  \brief Toimintoa ei ole vielä toteutettu.
     *
     *  Mikäli rajapinnan toteuttavassa luokassa on tynkätoteutuksia,
     *  joiden ei kuulukaan vielä toimia, niiden tulee heittää tätä
     *  tyyppiä oleva poikkeus.
     */
    class
    ToteuttamatonVirhe
        : public Virhe
    {
        public:

            /**
             *  \copydoc Virhe::Virhe(std::string const&)
             */
            explicit
            ToteuttamatonVirhe(std::string const& virheviesti);

            /**
             *  \copydoc Virhe::Virhe(char const*)
             */
            explicit
            ToteuttamatonVirhe(const char* virheviesti);

            /**
             *  \copydoc Virhe::Virhe(Virhe const&)
             */
            ToteuttamatonVirhe(ToteuttamatonVirhe const& toinen);

            /**
             *  \copydoc Virhe::~Virhe()
             */
            virtual
            ~ToteuttamatonVirhe();

            /**
             *  \copydoc Virhe::operator=(Virhe const&)
             */
            ToteuttamatonVirhe&
            operator=(ToteuttamatonVirhe const& toinen);
    };
}


#endif  // JULKINEN_TOTEUTTAMATON_VIRHE_HH
