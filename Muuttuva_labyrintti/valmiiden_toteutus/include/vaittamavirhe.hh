#ifndef JULKINEN_TOT_VAITTAMAVIRHE_HH
#define JULKINEN_TOT_VAITTAMAVIRHE_HH


/**
 *  \file vaittamavirhe.hh
 *  \brief Julkinen::Vaittamavirhe-luokan esittely.
 *  \author ©2010 Jarmo Jaakkola <jarmo.jaakkola@tut.fi>,
 *      TTY Ohjelmistotekniikka
 */


// Kantaluokat
#include "../../virhe.hh"

// Standardikirjastot
#include <iosfwd>   // std::basic_ostream


namespace
Julkinen
{
	/**
	 *	\brief Assertio rajapinnan käyttämä virhetyyppi.
	 */
    class
    Vaittamavirhe
        : public Virhe
    {
        public:

			/**
			 *	\brief Vaittamavirhe rakentaja.
			 *
			 *	\param lauseke Merkkijono.
			 *	\param tiedosto Merkkijono.
			 *	\param rivi Rivinumero.
			 *	\param funktio Merkkijono.
			 */
            Vaittamavirhe(
                    char const* lauseke,
                    char const* tiedosto,
                    unsigned int rivi,
                    char const* funktio
                  )
                throw();

			/**
			 *	\brief Kopiorakentaja.
			 *
			 *	\param toinen Kopioitava Vaittamavirhe.
			 */
            Vaittamavirhe(Vaittamavirhe const& toinen)
                throw();

			/**
			 *	\brief Purkaja.
			 */
            virtual
            ~Vaittamavirhe()
                throw() =0;

			/**
			 *	\brief Virhe tiedoston kertova metodi.
			 *
			 *	\return Palauttaa virhe tiedoston nimen.
			 */
            char const*
            tiedosto()
                const throw();

			/**
			 *	\brief	Virhe rivin kertova metodi.
			 *
			 *	\return Palauttaa virheen rivin.
			 */
            unsigned int
            rivi()
                const throw();

			/**
			 *	\brief Virhe funktion kertova metodi.
			 *
			 *	\return Palauttaa virhe funktion nimen.
			 */
            char const*
            funktio()
                const throw();

			/**
			 *	\brief Tulostus virran luonti metodi
			 *
			 *	\param tuloste Perus tulostevirta.
			 *	\return Palauttaa perus tulostevirran.
			 */
            std::basic_ostream<char>&
            tulosta(std::basic_ostream<char>& tuloste)
                const;

			/**
			 *	\brief Yhtäsuuruus vertailu operaattori.
			 *
			 *	\param toinen Verrattava Vaittamavirhe.
			 */
            Vaittamavirhe&
            operator==(Vaittamavirhe const& toinen)
                throw();

        private:

			/**
			 *	\brief
			 */
            char const*
            tiedosto_;

			/**
			 *	\brief
			 */
            unsigned int
            rivi_;

			/**
			 *	\brief
			 */
            char const*
            funktio_;
    };
}


#endif  // JULKINEN_TOT_VAITTAMAVIRHE_HH
