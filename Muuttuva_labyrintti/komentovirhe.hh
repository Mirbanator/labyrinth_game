#ifndef JULKINEN_KOMENTOVIRHE_HH
#define JULKINEN_KOMENTOVIRHE_HH


/**
 *	\version $Id: komentovirhe.hh 2660 2013-02-15 10:27:37Z bitti $
 *  \file komentovirhe.hh
 *  \brief Komentovirhe-luokan esittely.
 *  \author ©2010 Eero Salonen <eero.j.salonen@tut.fi>
 */
 
#include "virhe.hh" // Kantaluokka.

/// \namespace Julkinen
namespace
Julkinen
{
    /**
	 *	\class Komentovirhe
     *  \brief Käyttäjän antamaa pelikomentoa ei saatu suoritettua.
     *
     *  Mikäli käyttäjän ohjelmalle vuorovaikutteisesti antama komento
     *  on jotenkin virheellinen, heitetään tätä tyyppiä oleva poikkeus.
     *  Olio alustetaan jollakin esimääritellyistä virhekoodeista
     *  tai pelkällä virheviestillä.
     *  Virhekoodilla alustettaessa virheen viestiksi tulee sopiva
     *  selkokielinen viesti ja virheviestillä alustettaessa koodiksi
     *  tulee VIRHE_TUNNISTAMATON.
     *  Virheviestillä alustamista tulee käyttää vain sellaisille
     *  virhetilanteille, joille ei ole esimääriteltyä koodia.
     */
    class
    Komentovirhe
        : public Virhe
    {
        public:

            /**
			 *!	\enum Virhekoodi	
             *  \brief Tunnisteet esimääritellyille virhetilanteille
             *      käyttäjän antamissa komennoissa.
             */
            enum
            Virhekoodi
            {
                
				/**
				 *	\brief Annettua paikkaa ei ole kartalla.
				 */
				VIRHE_OLEMATON_PAIKKA,
				/**
				 *	\brief Annettu rotaatio on virheellinen.
				 */
				VIRHE_VIRHEELLINEN_ROTAATIO,
                /**
				 *	\var Virhekoodi::VIRHE_TUNNISTAMATON_PARAMETRI
                 *  \brief Komennolle annettua parametriä ei pystytty 
				 *		tunnistamaan.
                 */
                VIRHE_TUNNISTAMATON_PARAMETRI,
                /**
				 *	\var Virhekoodi::VIRHE_TUNNISTAMATON_KOMENTO
                 *  \brief Tunnistamaton komento.
                 */
                VIRHE_TUNNISTAMATON_KOMENTO,
                /**
				 *	\var Virhekoodi::VIRHE_LIIKAA_PARAMETREJA
                 *  \brief Liikaa parametreja.
                 */
                VIRHE_LIIKAA_PARAMETREJA,
                /**
                 *  \brief Tunnistamaton virhe.
                 */
                VIRHE_TUNNISTAMATON
            };

            /**
             *  \brief Tunnistamaton virhetilanne kopioidulla viestillä.
             *
             *  Käytä tätä vain, jos kyseessä ei ole mikään
             *  esimääritellyistä virheistä.
             *
             *  \copydetails Virhe::Virhe(std::string const&)
             */
            explicit Komentovirhe(std::string const& virheviesti);

            /**
             *  \brief Esimääritelty virhetilanne.
             *
             *  \post No-throw -takuu.
             *  \param virhekoodi Virhetilanteen tunniste.
             *      Mikäli koodi on VIRHE_TUNNISTAMATON, tulee viestiksi
             *      "Tunnistamaton virhe.".
             */
            explicit Komentovirhe(Virhekoodi virhekoodi);

            /**
             *  \copydoc Virhe::Virhe(Virhe const&);
             */
            Komentovirhe(Komentovirhe const& toinen);

            /**
             *  \copydoc Virhe::operator=(Virhe const& toinen)
             */
            Komentovirhe& operator=(Komentovirhe const& toinen);

            /**
             *  \brief Sattuneen virhetilanteen virhekoodi.
             */
            Virhekoodi virhe() const;

            /**
             *  \brief Tulosta "VIRHE: " ja virhekoodiin liittyvä viesti.
             */
            std::basic_ostream<char>&
            tulosta(std::basic_ostream<char>& tuloste)
                const;

        private:

            /**
             * \brief Sattuneen virhetilanteen virhekoodi.
             */
            Virhekoodi virhe_;
    };
}


#endif  // JULKINEN_KOMENTOVIRHE_HH
