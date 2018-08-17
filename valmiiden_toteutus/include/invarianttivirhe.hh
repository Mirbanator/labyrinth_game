#ifndef JULKINEN_TOT_INVARIANTTIVIRHE_HH
#define JULKINEN_TOT_INVARIANTTIVIRHE_HH


/**
 *  \file invarianttivirhe.hh
 *  \brief Julkinen::Invarianttivirhe-luokan esittely.
 *  \author ©2010 Jarmo Jaakkola <jarmo.jaakkola@tut.fi>,
 *      TTY Ohjelmistotekniikka
 */


#include "vaittamavirhe.hh" // Kantaluokka.


namespace
Julkinen
{
	/**
	 *	\brief Invariantti assertin lähettämän virhe.
	 */
    class
    Invarianttivirhe
        : public Vaittamavirhe
    {
        public:

			/**
			 *	\brief Invarianttivirhe rakentaja.
			 *
			 *	\param lauseke Merkkijono.
			 *	\param tiedosto Merkkijono.
			 *	\param rivi Rivinumero.
			 *	\param funktio Merkkijono.
			 */
            Invarianttivirhe(
                    char const* lauseke,
                    char const* tiedosto,
                    unsigned int rivi,
                    char const* funktio
                  )
                throw();

			/**
			 *	\brief Purkaja.
			 */
            ~Invarianttivirhe()
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


#endif  // JULKINEN_TOT_INVARIANTTIVIRHE_HH


