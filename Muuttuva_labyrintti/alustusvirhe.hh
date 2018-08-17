#ifndef JULKINEN_ALUSTUSVIRHE_HH
#define JULKINEN_ALUSTUSVIRHE_HH


/**
 *	\version $Id: alustusvirhe.hh 2660 2013-02-15 10:27:37Z bitti $
 *  \file alustusvirhe.hh
 *  \brief Alustusvirhe-luokan esittely. ($Revision: 2660 $)
 *  \author ©2010 Eero Salonen <eero.j.salonen@tut.fi>
 */

#include "virhe.hh"

/// \namespace Julkinen
namespace Julkinen
{
	/**
	 *	\class Alustusvirhe
	 *	\brief Alustuksessa tapahtuvaa virhettä kuvaava poikkeus
	 */
	class Alustusvirhe : public Virhe
	{
		public:
			
			/**
			 *	\enum Virhekoodi
             *  \brief Tunnisteet esimääritellyille virhetilanteille
             *      käyttäjän antamissa komennoissa.
             */
            enum
            Virhekoodi
            {
                /**
                 *  \brief Irtopala on jo työnnetty tällä vuorolla ja
				 *		pelaaja yrittää työntää sitä uudestaan.
                 */
                VIRHE_PALASSA_ON_JO_ESINE,
				/**
				 *	\brief Annettu sijainti on virheellinen.
				 */
				VIRHEELLINEN_SIJAINTI,
                
				/**
				 *	\brief Annettu rotaatio on virheellinen.
				 */
				VIRHEELLINEN_ROTAATIO,
                
                /**
				 *	\var Virhekoodi::VIRHE_ANNETTUA_PELAAJAA_EI_LOYTYNYT
                 *  \brief Tunnistamaton komento.
                 */
                VIRHE_ANNETTUA_PELAAJAA_EI_LOYTYNYT,
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
			explicit Alustusvirhe(std::string const& virheviesti);

			/**
             *  \brief Esimääritelty virhetilanne.
             *
             *  \post No-throw -takuu.
             *  \param virhekoodi Virhetilanteen tunniste.
             *      Mikäli koodi on VIRHE_TUNNISTAMATON, tulee viestiksi
             *      "Tunnistamaton virhe.".
             */
			explicit Alustusvirhe(Julkinen::Alustusvirhe::Virhekoodi virhekoodi);
			
			/**
             *  \brief Kopiorakentaja.
             *
             *  \post No-throw -takuu.
             */
            Alustusvirhe(Julkinen::Alustusvirhe const& toinen);
			
			/**
             *  \brief Sijoitusoperaattori.
             *
             *  \post No-throw -takuu.
             */
            Alustusvirhe& operator=(Julkinen::Alustusvirhe const& toinen);

			/**
             *  \brief Sattuneen virhetilanteen virhekoodi.
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
            Julkinen::Alustusvirhe::Virhekoodi virhe_;
		
	};
	
}
#endif // JULKINEN_ALUSTUSVIRHE_HH
