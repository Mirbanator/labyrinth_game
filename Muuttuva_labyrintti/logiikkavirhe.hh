#ifndef JULKINEN_LOGIIKKAVIRHE_HH
#define JULKINEN_LOGIIKKAVIRHE_HH

#include "virhe.hh"

/**
 *	\version $Id: koordinaatti.cc 1797 2011-02-03 01:56:31Z salone58 $
 *  \file logiikkavirhe.hh
 *  \brief Logiikkavirhe-luokan esittely.
 *  \author ©2010 Eero Salonen <eero.j.salonen@tut.fi>
 */

/// \namespace Julkinen
namespace Julkinen
{
	/**
	 *	\class Logiikkavirhe
	 *	\brief Virhe toimintalogiikka virhetilanteita varten.
	 */
	class Logiikkavirhe : public Virhe
	{
		public:

			/**
             *  \brief Tunnisteet esimääritellyille virhetilanteille
             *      käyttäjän antamissa komennoissa.
             */
            enum
            Virhekoodi
            {
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
			explicit Logiikkavirhe(std::string const& virheviesti);
			
			/**
             *  \brief Esimääritelty virhetilanne.
             *
             *  \post No-throw -takuu.
             *  \param virhekoodi Virhetilanteen tunniste.
             *      Mikäli koodi on VIRHE_TUNNISTAMATON, tulee viestiksi
             *      "Tunnistamaton virhe.".
             */
			explicit Logiikkavirhe(Virhekoodi virhekoodi);
			
			/**
             *  \brief Kopiorakentaja.
             *
             *  \post No-throw -takuu.
             */
            Logiikkavirhe(Logiikkavirhe const& toinen);
			
			/**
             *  \brief Sijoitusoperaattori.
             *
             *  \post No-throw -takuu.
             */
            Logiikkavirhe& operator=(Logiikkavirhe const& toinen);

			/**
             *  \brief Sattuneen virhetilanteen virhekoodi.
			 *
			 *	\return Palauttaa virheen <code>Virhekoodi</code>.
             */
			Virhekoodi virhe() const;
			
			
			/**
             *  \brief Tulosta virheen viesti virtaan.
             *
             *  Tulostaa virheen viestin virtaan, eikä tee muuta.
             *
             *  \post Vahva poikkeustakuu.
             *  \param tuloste Virta, jonne viesti tulostetaan.
             *  \return \p tuloste
             */
            virtual
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

#endif // JULKINEN_Logiikkavirhe_HH
