
#ifndef KOMENTOTULKKI_HH
#define KOMENTOTULKKI_HH

/**
 *	\version $Id: komentotulkki.hh 1802 2011-02-07 09:17:58Z salone58 $
 *  \file komentotulkki.hh
 *  \brief Komentotulkki-luokan esittely. ($Revision: 1802 $)
 *  \author ©2010 Eero Salonen <eero.j.salonen@tut.fi> 
 */

/**
 *	Jos kääntäjä on GNUG pohjainen esim. gcc tai tutg++ käytetään tr1/memory
 *	kirjastoa.
 */
#	if defined(__GNUG__)

#include <tr1/memory>
/**
 *	Muussa tapauksessa käytetään memory kirjastoa ja toivotaan että kääntäjästä
 *	löytyy alustava tuki uudelle C++ standardille. 
 *	Toimii esim. Visual Studio 2010.
 */
#	else
#include <memory>
#	endif
#include <string>
#include <vector>
#include "../../pelirajapinta.hh"
#include "naytto.hh"

 //	TODO: Poistaa ylimääräiset funktiot
 //	TODO: Tarkistaa että kaikki tarpeellinen löytyy.



/**
 *	\brief Komentotulkin toteuttava luokka.
 */
class Komentotulkki
{
	public:
		
		//Esitellään funktiot
		
		/**
		 *	\brief Luo \c Komentotulkki olion ja palauttaa osoittimen siihen.
		 *
		 *	\post Palauttanut jaetunosoittiminen Komentotulkki -osoittimeen.
		 *
		 *	\return Palauttaa osoittimen komenttotulkki olioon.
		 */
		static std::shared_ptr<Komentotulkki> uusiKomentotulkki(std::shared_ptr<Naytto> naytto);

		/**
		 *	\brief Asettaa komentotulkin raakile tilaan.
		 *
		 *	\post Komentotulkki on raakile tilassa.
		 */
		static void asetaRaakileTilaan();

                /**
                 *      \brief Kysyy, onko komentotulkki raakiletilassa.
                 *
                 */
                static bool onkoRaakileTilassa();

		/**
		 *	\brief Metodi komentotulkin käynnistämiseen.
		 *
		 *	\pre Peli on pelitilassa.
		 *	\post Komentotulkki on käynnistetty.
		 *
		 *	\param peli Osoitin peliin.
		 */
		void kaynnistaKomentotulkki(std::shared_ptr<Julkinen::Pelirajapinta> peli);
      ~Komentotulkki();
	private:
		
		/**
		 *	\brief Komennot
		 */
		enum Komento { TYONNA, LIIKU, PAIKALLAAN, LOPETA, AUTOMAATTI, VIRHE, TYHJA };

		/**
		 *	\brief Komentotulkin tilat.
		 */
		enum Tila
		{
			/// \brief Pelin alustustila
			ALUSTUS,
			/// \brief Odottaa pelaajan työntö komentoa.
			TYONTO,
			/// \brief Odottaa pelaajan liikkumiskomentoa.
			LIIKE,
			///	\brief Pelin lopetustila.
			LOPETUS
		};

		// Komennoille tehty tietorakenne
		struct Komento_tiedot
		{
			Komento komento;
			unsigned int parametreja;
			Komento_tiedot(Komento k, unsigned int p):
			komento(k), parametreja(p){}
		};
		
		/**
		 *	\brief perusrakentaja
		 */
		Komentotulkki(std::shared_ptr<Naytto> naytto);

		/**
		 *	\brief metodi komennon lukemiseen käyttäjältä.
		 *
		 *	\post Komento on luettu.
		 */
		void lueKomento();
		
		/**
		 *	\brief Suorittaa komennon.
		 *
		 *	\post Komento on suoritettu.
		 */ 
		void suoritaKomento();

		/**
		 *	\brief Tarkistaa komennon
		 *
		 *	\post Komento on tarkistettu.
		 *
		 *	\param syote Pelaajan syöte.
		 *	\return Pelaajan komennon tiedot.
		 */ 
		Komento_tiedot tarkistaKomento(std::string& syote);

		/**
		 *	\brief Merkkijono kokonaisluvuksi metodi.
		 *
		 *	\post Merkkijono on muutettu kokonaisluvuksi.
		 *
		 *	\param str Muutettava merkkijono.
		 *	\return Palauttaa merkkijonon kokonaislukuna.
		 */
		int str2int (std::string const & str);

		/**
		 *	\brief Metodi reunan määrittämiseen.
		 *
		 *	\post Reuna on määritetty ja palautettu.
		 *
		 *	\param str Maaritettava merkkijono.
		 */
		Julkinen::Reuna maaritaReuna(std::string& str);
		
		/**
		 *	\brief Metodi suunnan määrittämiseen.
		 *
		 *	\post Suunta on määritetty ja palautettu.
		 *
		 *	\param str Maaritettava merkkijono.
		 */
		Julkinen::Suunta maaritaSuunta(std::string& str);
		
		/**
		 *	\brief Tieto komentotulkin tilasta
		 */
		Tila _tila;
		
		/**
		 *	\brief Osoitin peliin.
		 */
		std::shared_ptr<Julkinen::Pelirajapinta> _peli;

		/**
		 *	\brief Merkkijono vektori, jossa säilytetään käyttäjän komento.
		 */
		std::vector<std::string> _komento;

		/**
		 *	\brief Osoitin nayttoon.
		 */
		std::shared_ptr<Naytto> _naytto;
		Komento _edellinen;
			

                static bool _raakiletila;
                
};		
			

#endif // KOMENTOTULKKI_HH

