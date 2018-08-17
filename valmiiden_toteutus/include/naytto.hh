#ifndef NAYTTO_HH
#define NAYTTO_HH

/**
 *	\version $Id: naytto.hh 1800 2011-02-05 06:54:47Z salone58 $
 *  \file naytto.hh
 *  \brief Naytto-luokan esittely. ($Revision: 1800 $)
 *  \author ©2010 Eero Salonen <eero.j.salonen@tut.fi> 
 */

//	Julkisen rajapinnan kirjastot:
#include "../../nayttorajapinta.hh"
#include "../../koordinaatti.hh"
#include "../../pelirajapinta.hh"

// Pääohjelman kirjastot:
#include "Bittikartta.hh"

//	STL:n kirjastot:
#include <string>
#include <vector>




/**
*	\brief Labyrintti-pelin tulostusluokka.
*/
class Naytto : public Julkinen::Nayttorajapinta
{
	public:

		/**
		 *	\brief Tulostuksessa avustava structi.
		 */
		struct P
		{
			///	\brief Palan ylälaitaa kuvaava merkkijono.
			std::string yla;
			///	\brief Palan oikeaalaitaa kuvaava merkkijono.
			std::string oikea;
			///	\brief Palan alalaitaa kuvaava merkkijono.
			std::string ala;
			///	\brief Palan vasentalaitaa kuvaava merkkijono.
			std::string vasen;
		};
			
		/**
		 *	\brief Näytönrakentaja
		 *
		 *	Rakentaa näytön ja luo tarvittava \c Bittikartta -oliot.
		 *
		 *	\param[in] mitat Pelialueen koko <code>Koordinaatti</code>-luokkana.
		 *	\param[in] x \c Bittikartta -olion leveys.
		 *	\param[in] y \c Bittikartta -olion korkeus.
		 */
		Naytto(Julkinen::Koordinaatti const& mitat, 
                       unsigned int x, 
                       unsigned int y,
                       bool debug_naytto);
			
		/**
		 *	\brief Purkaja.
		 *
		 *	\post No-throw takuu.
		 */
		virtual ~Naytto();
			
		/**
         *  \copydoc Julkinen::Nayttorajapinta::onTulostustilassa() const
         */
		virtual bool onTulostustilassa() const;
			
		/**
         *  \copydoc Julkinen::Nayttorajapinta::ilmoitusEsinePoimittu(char esine, 
		 *	Julkinen::EsineTyyppi tyyppi, 
		 *	std::string const& pelaaja)
         */
		virtual void ilmoitusEsinePoimittu(char esine, 
			/*Julkinen::EsineTyyppi tyyppi,*/ 
			std::string const& pelaaja);
   /**
    * \copydoc Julkinen::Nayttorajapinta::ilmoitusErikoispalaanAstuttu(
    * Julkinen::ErikoispalaTyyppi tyyppi,
    * std::string const& pelaaja)
    */
   virtual void ilmoitusErikoispalaanAstuttu(Julkinen::ErikoispalaTyyppi tyyppi,
                                             std::string const& pelaaja);
		/**
         *  \copydoc Julkinen::Nayttorajapinta::ilmoitusVuorossa(std::string const& nimi)
         */
		virtual void ilmoitusVuorossa(std::string const& nimi);
			
		/**
         *  \copydoc Julkinen::Nayttorajapinta::tulostaPelaajantiedot(std::string const& nimi, 
		 *	std::string const& keratytesineet, 
		 *	std::string const& kerattavatesineet, 
		 *	std::string const& edellinentoiminto)
         */
		virtual void tulostaPelaajantiedot(std::string const& nimi, 
			std::string const& keratytesineet, 
			std::string const& kerattavatesineet, 
			std::string const& edellinentoiminto);
			
		/**
         *  \copydoc Julkinen::Nayttorajapinta::komentoAloitaRakennus()
         */
		virtual void komentoAloitaRakennus();
			
		/**
         *  \copydoc Julkinen::Nayttorajapinta::palaLaudalle(Julkinen::PalaTyyppi tyyppi, int rotaatio, 
		 *		Julkinen::Koordinaatti const& sijainti, Julkinen::Koordinaatti const& kohde = Julkinen::Koordinaatti())
         */
   virtual void palaLaudalle(Julkinen::PalaTyyppi tyyppi, Julkinen::ErikoispalaTyyppi etyyppi, unsigned int rotaatio, 
                             Julkinen::Koordinaatti const& sijainti, Julkinen::Koordinaatti const& kohde = Julkinen::Koordinaatti());
			
		/**
         *  \copydoc Julkinen::Nayttorajapinta::pelaajaLaudalle(char merkki, 
		 *		Julkinen::Koordinaatti const& sijainti)
         */
		virtual void pelaajaLaudalle(char merkki, 
				Julkinen::Koordinaatti const& sijainti);
			
		/**
         *  \copydoc Julkinen::Nayttorajapinta::esineLaudalle(char merkki, 
		 *		Julkinen::Koordinaatti const& sijainti)
         */
		virtual void esineLaudalle(char merkki, 
				Julkinen::Koordinaatti const& sijainti);
			
		/**
         *  \copydoc Julkinen::Nayttorajapinta::komentoLopetaRakennus() 
         */
		virtual void komentoLopetaRakennus();

		/**
		 *	\brief Tulostaa virran.
		 *	
		 *	Näyttö käyttää kaikeen tulostamiseen tätä funktiota.
		 *
		 *	\param[in] virta Tulostettava virta.
		 */
		void tulosta(std::ostringstream& virta);

		/**
		 *	\brief Tulostaa ilmoituksen pelin voittajasta.
		 */
		void tulostaVoittaja();

		/**
		 *	\brief Tulostaa vuorossa olevan pelaajan nimen ja kulman
		 *	\pre ilmoitusVuorossa() metodi on ajettu ja naytto on tulostustilassa.
		 *	\post vuorossa olevan pelaajan nimi ja kulma on tulostettu.
		 */
		void vuorossa();
		
 private:
   bool _debug_naytto;
   
   struct Esine
   {
      char merkki;
      Julkinen::Koordinaatti sijainti;
   };
   
   std::vector<Esine> _esineet;
   char _irtopalanEsine;
   
   struct Erikoispala
   {
      Julkinen::ErikoispalaTyyppi tyyppi;
      Julkinen::Koordinaatti sijainti;
      Julkinen::Koordinaatti kohde;
   };
   
   
   std::vector<Erikoispala> _erikoispalat;
   Erikoispala _irtopalanErikoispala;
   struct Pelaaja
   {
      char merkki;
      Julkinen::Koordinaatti sijainti;
   };
   
   std::vector<Pelaaja> _pelaajat;
   /**
    *	\brief Näytön tilat sisältävä luettelotyyppi.
    */
   enum Tila
   {
      TULOSTUS,
        RAKENNUS
   };
		
		//	Näytön tila
		Tila _tila;

		//	Pelialueen 
		Bittikartta _kartta;
		Bittikartta _irtopala;
		Julkinen::Koordinaatti _koko;
		std::vector<std::string> _pelaajientiedot;

		//	Vuorossa olevan pelaajan nimi.
		std::string _vuorossa;
		
		/**
		 *  \brief Ei sallittu.
		 */
		Naytto();
		/**
		 *  \brief Ei sallittu.
		 */
		Naytto(Naytto const& naytto);

		/**
		 *  \brief Ei sallittu.
		 */
		Naytto& operator=(Naytto const& naytto);

		/**
		 *  \brief Apufunktio \c Koordinaatti -luokan arvojen oikeellisuuteen.
		 *
		 *	\param[in] tarkistettava Tarkistettava \c Koordinaatti
		 */
		void tarkistaKoordinaatti(Julkinen::Koordinaatti const& tarkistettava);

		/**
		 *  \brief Apufunkttio irtopalan \c Bittikartta luomiseen.
		 *
		 *	\post Irtopalaa kuvaa bittikartta on asetettu kuvaamaan annettua 
		 *	palaa. Poikkeusturvallisuus: No-throw takuu.
		 *
		 *	\param pala[in] irtopalan tulostetyyppi.
		 */
		void luoIrtopalaKartta(Julkinen::PalaTyyppi tyyppi);

		/**
		 *  \brief Apufunkktio esineen merkkin lisäämiseen irtopalaan.
		 *
		 *	\post Irtopala kartaan on asetettu annetun palan tiedot.
		 *		Poikkeusturvallisuus: No-throw takuu.
		 *
		 *	\param[in] merkki Irtopalaan lisättävän esineen merkki.
		 */
		void lisaaEsineIrtopalaan(char merkki);

		/**
		 *	\brief Apufunktio joka tarkistaa että näyttö on rakennustilassa.
		 *
		 *	Tekee assertoinnin jos peli ei ole rakennustilassa.
		 *
		 *	\pre on kutsuttu jotain Laudalle metodia.
		 *	\post funktio on suoritettu.
		 *		Poikkeusturvallisuus: No-throw.
		 */
		void tarkistaOnkoRakennustila();
};

 #endif // NAYTTO_HH

 
