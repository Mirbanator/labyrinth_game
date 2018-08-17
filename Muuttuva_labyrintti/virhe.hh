#ifndef JULKINEN_VIRHE_HH
#define JULKINEN_VIRHE_HH


/**
 *	\version $Id: virhe.hh 2660 2013-02-15 10:27:37Z bitti $
 *  \file virhe.hh
 *  \brief Virhe-luokan esittely.
 *  \author ©2010 Jarmo Jaakkola <jarmo.jaakkola@tut.fi>,
 *      TTY Ohjelmistotekniikka
 */

/*
 *	Jos kääntäjä on GNUG pohjainen esim. gcc tai tutg++ käytetään tr1/memory
 *	kirjastoa.
 */
#	if defined(__GNUG__)

#include <tr1/memory>
/*
 *	Muussa tapauksessa käytetään memory kirjastoa ja toivotaan että kääntäjästä
 *	löytyy alustava tuki uudelle C++ standardille. 
 *	Toimii esim. Visual Studio 2010.
 */
#	else 
#include <memory>
#	endif

//	STL:n kijastot
#include <iosfwd>       // std::basic_ostream
#include <string>       // std::string
#include <memory>   // std::tr1::shared_ptr

/**
 * \brief Nimiavaruus harjoitustyön valmiina annetulle koodille
 * 
 * Kaikki harjoitustyön valmiina annettu koodi on nimiavaruudessa
 * <code>Julkinen</code>. Ko. nimiavaruuteen ei ole suotavaa laittaa
 * omaa koodia.
 */
namespace
Julkinen
{
    /**
	 *	\class Virhe
     *  \brief Labyrintin poikkeusten kantaluokka.
     *
     *  Virheilmoitus voidaan antaa joko std::string-oliona kopioitavaksi,
     *  jolloin olion rakentaminesta voi tulla poikkeus, tai osoittimena
     *  C-merkkijonovakioon, jolloin rakentaminen on no-throw.
     *
     *  Mikäli virheilmoitukseen tarvitsee liittää muutakin kuin viesti,
     *  periytä luokasta uusi tyyppi, jolle tarvittavat tiedot voi antaa
     *  ja uudelleenmäärittele tulosta()-metodi käyttämään näitä tietoja.
     */
    class
    Virhe
    {
        public:

            /**
             *  \brief Kopioidulla viestillä.
             *
             *  \post Perustakuu poikkeuksen sattuessa.
             *  \param virheviesti Merkkijono, joka kopioidaan poikkeuksen
             *      viestiksi.
             *  \exception std::bad_alloc Ei saatu varattua muistia viestiä
             *      varten.
             */
            explicit
            Virhe(std::string const& virheviesti);

            /**
             *  \brief Muualla tallessa olevalla viestillä.
             *
             *  HUOM!  Tämä luokka \e ei ota vastuuta osoittimen päässä
             *  olevan olion tuhoamisesta, eikä tee osoittimen osoittamasta
             *  tiedosta kopiota.  Tarkoituksena on antaa osoitin
             *  esim. käännösyksikön tai luokan sisäiseen
             *  virheviestivakioon, jotta tämä rakentaja voi tarjota
             *  no-throw -takuun.
             *
             *  \post No-throw -takuu.
             *  \param[in] virheviesti Osoitin oikeaan C-merkkijonovakioon
             *      tai vakioisen <code>std::string</code>-olion
             *      <code>c_str()</code> metodin palauttamaan arvoon.
             */
            explicit
            Virhe(char const* virheviesti);

            /**
             *  \brief Kopiorakentaja.
             *
             *  \post No-throw -takuu.
			 *
			 *	\param[in] toinen Kopioitava \c Virhe.
             */
            Virhe(Virhe const& toinen);

            /**
             *  \brief Purkaja.
             *
             *  \post No-throw -takuu.
             */
            virtual
            ~Virhe();

            /**
             *  \brief Sijoitusoperaattori.
             *
             *  \post No-throw -takuu.
			 *
			 *	\param[in] toinen Sijoitettava \c Virhe.
             */
            Virhe&
            operator=(Virhe const& toinen);

            /**
             *  \brief Virheeseen liittyva ilmoitus.
             *
             *  \post No-throw -takuu.
             */
            char const*
            viesti()
                const;

            /**
             *  \brief Tulosta virheen viesti virtaan.
             *
             *  Tulostaa virheen viestin virtaan, eikä tee muuta.
             *
             *  \post Vahva poikkeustakuu.
             *  \param[in] tuloste Virta, jonne viesti tulostetaan.
             *  \return \p tuloste
             */
            virtual
            std::basic_ostream<char>&
            tulosta(std::basic_ostream<char>& tuloste)
                const;

        private:

            /**
             *  \brief Kopioitu virheviesti.
             *
             *  Vain toinen muuttujista viestinKopio_ tai viesti_ on
             *  kerrallaan nollasta poikkeava.
             */
            std::tr1::shared_ptr<char>
            viestinKopio_;

            /**
             *  \brief Muualla sijaitseva virheviesti.
             *
             *  Tämä luokka \e ei ole vastuussa osoittimen päässä olevan
             *  luokan tuhoamisesta.
             *
             *  Vain toinen muuttujista viestinKopio_ tai viesti_ on
             *  kerrallaan nollasta poikkeava.
             */
            char const*
            viesti_;
    };

    /**
     *  \brief Tulosta virhe.
     *
     *  Virhe tulostetaan Virhe::tulosta()-metodilla.
     *
     *  \param[in, out] tuloste Virta jonne tulostetaan.
     *  \param[in] virhe Tulostettava virhe.
     *  \return \p tuloste
     *  \relates Julkinen::Virhe
     */
    std::basic_ostream<char>&
    operator<<(std::basic_ostream<char>& tuloste, Virhe const& virhe);
}


#endif  // JULKINEN_VIRHE_HH
