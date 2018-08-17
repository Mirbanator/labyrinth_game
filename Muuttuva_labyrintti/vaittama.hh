#ifndef JULKINEN_VAITTAMA_HH
#define JULKINEN_VAITTAMA_HH


/**
 *  \file vaittama.hh
 *  \brief Väittämien tarkistustyökalujen esittelyt.
 *  \author ©2010 Jarmo Jaakkola <jarmo.jaakkola@tut.fi>,
 *      TTY Ohjelmistotekniikka
 */


namespace
Julkinen
{
	/**
	 *	\brief Luettelotyyppi julkisenrajpinnan assertioille.
	 */
    enum
    VaittamaTyyppi
    {
        INVARIANTTIVAITTAMA,
        ESIEHTOVAITTAMA,
        JALKIEHTOVAITTAMA
    };

    /**
     *  \brief Väittämien tarkistamiseen käytettävä funktio.
     *
     *  Tätä funktiota ei ole tarkoitettu kutsuttavaksi suoraan.
     *  Käytä tätä ESIEHTO()-, INVARIANTTI()- tai JALKIEHTO()-makron
     *  avulla.
     *
     *  \pre
        \htmlonly
          <var>lauseke</var> &ne; 0 &and; <var>tiedosto</var> &ne; 0
        \endhtmlonly
     *  \post Funktio ei koskaan palaa normaalisti.  Perustakuu poikkeuksen
     *      sattuessa.
     *  \param[in] tyyppi Väittämän tyyppi.
     *  \param[in] vaite Testatun väittämän totuusarvo.
     *  \param[in] lauseke Testatun väittämän lauseke merkkijonona.
     *  \param[in] tiedosto Sen tiedoston nimi, jossa väittämä oli.
     *  \param[in] rivi Rivinumero, jolla väittämä oli tiedostossa.
     *  \param[in] funktio Sen funktion nimi, jossa väittämä oli (jos
     *      saatavilla).
     */
    void
    vaittamaToteutus(
            VaittamaTyyppi tyyppi,
            bool vaite,
            char const* lauseke,
            char const* tiedosto,
            unsigned int rivi,
            char const* funktio
          );
}


#ifdef NDEBUG
/** \brief Varmista luokkainvariantti. */
#  define INVARIANTTI(lauseke)  // Tyhjä.
/** \brief Varmista esiehto. */
#  define ESIEHTO(lauseke)      // Tyhjä.
/** \brief varmista jälkiehto. */
#  define JALKIEHTO(lauseke)    // Tyhjä.
#else
/**
 *  \brief Kutsu vaittamaToteutus()-funktiota sopivin parametrein.
 *
 *  Ei ole tarkoitettu kutsuttavaksi suoraan.
 */
#  define VAITTAMA(tyyppi, lauseke)                                     \
    Julkinen::vaittamaToteutus(tyyppi, lauseke, #lauseke,               \
            __FILE__, __LINE__, VAITTAMAFUNKTIO)

/**
 *  \brief Varmista luokkainvariantti.
 *  \pre Lauseke on tosi, ts. jos väittämä ei pidä paikkaansa,
 *      mitä vain voi tapahtua, ohjelmas voidaan vaikka kaataa ;-)
 *  \param lauseke Tarkistettavan luokkainvariantin lauseke.
 */
#  define INVARIANTTI(lauseke)                                          \
    VAITTAMA(Julkinen::INVARIANTTIVAITTAMA, lauseke)

/**
 *  \brief Varmista esiehto.
 *  \pre Lauseke on tosi, ts. jos väittämä ei pidä paikkaansa,
 *      mitä vain voi tapahtua, ohjelmas voidaan vaikka kaataa ;-)
 *  \param lauseke Tarkistettavan esiehdon lauseke.
 */
#  define ESIEHTO(lauseke)                                              \
    VAITTAMA(Julkinen::ESIEHTOVAITTAMA, lauseke)

/**
 *  \brief varmista jälkiehto.
 *  \pre Lauseke on tosi, ts. jos väittämä ei pidä paikkaansa,
 *      mitä vain voi tapahtua, ohjelmas voidaan vaikka kaataa ;-)
 *  \param lauseke Tarkistettavan jälkiehdon lauseke.
 */
#  define JALKIEHTO(lauseke)                                            \
    VAITTAMA(Julkinen::JALKIEHTOVAITTAMA, lauseke)

// GNU assert.h:ta mukaillen
#  if defined(__GNUG__)
/**
 *  \brief GNU-kääntäjän hieno funktionimimakro.
 */
#    define VAITTAMAFUNKTIO __PRETTY_FUNCTION__
#  else
/**
 *  \brief Funktion nimi ei ole saatavilla tällä kääntäjällä.
 */
#    define VAITTAMAFUNKTIO (0)
#  endif

#endif

#endif  // JULKINEN_VAITTAMA_HH
