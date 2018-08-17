#ifndef JULKINEN_TOIMINTOVIRHE_HH
#define JULKINEN_TOIMINTOVIRHE_HH


/**
 *	\version $Id: toimintovirhe.hh 2660 2013-02-15 10:27:37Z bitti $
 *  \file toimintovirhe.hh
 *  \brief Toimintovirhe-luokan esittely.
 *  \author ©2010 Eero Salonen <eero.j.salonen@tut.fi>
 */
#include "virhe.hh" 

/// \namespace Julkinen
namespace Julkinen
{
	/**
	 *	\class Toimintovirhe
	 *	\brief Toiminnoissa tapahtuvia virheitä kuvaava poikkeus
	 */
	class Toimintovirhe : public Virhe
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
				 *	\brief Pelaaja ei pysty liikkumaan annetua määrää, 
				 *	annettuun suuntaan.
				 */
				VIRHE_EI_VOITU_LIIKKUA_ANNETTUA_MAARAA,
				/**
				 *	\brief Pelaaja ei ole työntänyt irtopalaa tällä vuorolla.
				 */
				VIRHE_IRTOPALAA_EI_OLE_TYONNETTY,
				/**
				 *	\brief Pelaaja on jo työntänyt irtopalan tällä vuorolla.
				 */
				VIRHE_IRTOPALAA_ON_JO_TYONNETTY,
				/**
				 *	\brief Pelaaja ei ole liikkunut tällä vuorolla.
				 */
				VIRHE_PELAAJA_EI_OLE_LIIKKUNUT,
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
			explicit Toimintovirhe(std::string const& virheviesti);

			/**
             *  \brief Esimääritelty virhetilanne.
             *
             *  \post No-throw -takuu.
             *  \param virhekoodi Virhetilanteen tunniste.
             *      Mikäli koodi on VIRHE_TUNNISTAMATON, tulee viestiksi
             *      "Tunnistamaton virhe.".
             */
            explicit Toimintovirhe(Virhekoodi virhekoodi);
			
			/**
             *  \brief Kopiorakentaja.
             *
             *  \post No-throw -takuu.
             */
            Toimintovirhe(Toimintovirhe const& toinen);

			/**
             *  \brief Sattuneen virhetilanteen virhekoodi.
			 *
			 *	\return Palauttaa virheen <code>Virhekoodi</code>.
             */
			Virhekoodi virhe() const;
			
			
			/**
             *  \brief Sijoitusoperaattori.
             *
             *  \post No-throw -takuu.
             */
            Toimintovirhe& operator=(Toimintovirhe const& toinen);
			
			
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

#endif // JULKINEN_ToimintoVIRHE_HH
