#ifndef JULKINEN_TOT_JALKIEHTOVIRHE_HH
#define JULKINEN_TOT_JALKIEHTOVIRHE_HH


/**
 *  \file jalkiehtovirhe.hh
 *  \brief Julkinen::Jalkiehtovirhe-luokan esittely.
 *  \author ©2010 Jarmo Jaakkola <jarmo.jaakkola@tut.fi>,
 *      TTY Ohjelmistotekniikka
 */


#include "vaittamavirhe.hh" // Kantaluokka.


namespace
Julkinen
{
	/**
	 *	\brief Jälkiehto assertin lähettämän virhe.
	 */
    class
    Jalkiehtovirhe
        : public Vaittamavirhe
    {
        public:

			/**
			 *	\brief Jalkiehtovirhe rakentaja.
			 *
			 *	\param lauseke Merkkijono.
			 *	\param tiedosto Merkkijono.
			 *	\param rivi Rivinumero.
			 *	\param funktio Merkkijono.
			 */
            Jalkiehtovirhe(
                    char const* lauseke,
                    char const* tiedosto,
                    unsigned int rivi,
                    char const* funktio
                  )
                throw();

			/**
			 *	\brief Purkaja.
			 */
            ~Jalkiehtovirhe()
                throw();

			/**
			 *	\brief Tulostus virran luonti metodi
			 *
			 *	\param tuloste Perus tulostevirta.
			 *	\return Palauttaa perus tulostevirran.
			 */
            std::basic_ostream<char>&
            tulosta(std::basic_ostream<char>& tuloste)
                const;
    };
}


#endif  // JULKINEN_TOT_JALKIEHTOVIRHE_HH

