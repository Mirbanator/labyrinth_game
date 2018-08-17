#ifndef JULKINEN_NAYTTOVIRHE_HH
#define JULKINEN_NAYTTOVIRHE_HH

#include "virhe.hh"

/**
 *	\version $Id: nayttovirhe.hh 2660 2013-02-15 10:27:37Z bitti $
 *  \file nayttovirhe.hh 
 *  \brief Nayttovirhe-luokan esittely.
 *  \author ©2010 Eero Salonen <eero.j.salonen@tut.fi>
 */
 
/// \namespace Julkinen
namespace Julkinen
{
	/**
	 *	\class Nayttovirhe
     *  \brief Näyttörajapinnan tulostusoperaatio ei onnistunut.
	 *
	 *	Virhe jolla kerrotaan, jos näytön toiminnassa on tapahtunut jokin
	 *	virhe
     */
	class Nayttovirhe : public Virhe
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
			explicit Nayttovirhe(std::string const& virheviesti);
			
			
			/**
             *  \brief Esimääritelty virhetilanne.
             *
             *  \post No-throw -takuu.
             *  \param virhekoodi Virhetilanteen tunniste.
             *      Mikäli koodi on VIRHE_TUNNISTAMATON, tulee viestiksi
             *      "Tunnistamaton virhe.".
             */
			explicit Nayttovirhe(Virhekoodi virhekoodi);
			
			/**
             *  \brief Kopiorakentaja.
             *
             *  \post No-throw -takuu.
             */
            Nayttovirhe(Nayttovirhe const& toinen);
			
			/**
             *  \brief Sijoitusoperaattori.
             *
             *  \post No-throw -takuu.
             */
            Nayttovirhe& operator=(Nayttovirhe const& toinen);

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

#endif // JULKINEN_NAYTTOVIRHE_HH
