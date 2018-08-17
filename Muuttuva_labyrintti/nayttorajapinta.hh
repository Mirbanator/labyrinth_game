#ifndef JULKINEN_NAYTTORAJAPINTA_HH
#define JULKINEN_NAYTTORAJAPINTA_HH

/**
*	\version $Id: nayttorajapinta.hh 2677 2013-02-20 13:03:17Z voutilai $
* 	\file nayttorajapinta.hh
*	\brief Rajapinta pelin luomiseksi ($Revision: 2677 $)
*	\author ©2010 Eero Salonen <eero.j.salonen@tut.fi
**/


#include "luettelotyypit.hh"
#include "koordinaatti.hh"
#include <string>

/// \namespace Julkinen
namespace 
Julkinen
{
	/**
	 *	\class Nayttorajapinta
	 *	\brief Labyrintti-pelin tulostusrajapinta
	 *
	 *	Labyrintti pelin toiminnalisuuden toteuttava kirjasto tekee kaikki
	 *	tulostukset tämän rajapinnan läpi. Rajapinnan toteutus on pääohjelman
	 *	vastuulla.
	 *
	 *	Nayttorajapinnan toteutus voi olla kahdessa eri tilassa, 
	 *	tulostustilassa tai rakennustilassa. Oletuksena näyttö on 
	 *	tulostustilassa, jossa näyttö tulostaa ilmoitukset ja tiedot. 
	 *	Kutsumalla komentoAloitaRakennus() metodia näyttö siirtyy 
	 *	rakennustilaan. Rakennustilassa näyttö alkaa odottamaan pelialueen 
	 *	rakennusta. Pelialue rakennetaan kutsumalla palaLaudalle(), 
	 *	pelaajaLaudalle() ja esineLaudalle() -metodeja. Rakennus tilassa pitää
	 *	kutsua myös tulostaPelaajantiedot() -metodia jokaiselle pelaajalle.
	 *	Pelialueen rakennus lopetetaan kutsumalla komentoLopetaRakennus() 
	 *	-metodia.
	 *
	 *	Kaikki ei No-throw metodit heittävät std::bad_alloc poikkeuksen, jos 
	 *	muisti loppuu. bac_alloc:n yhteydessä luokka tarjoaa minimitakuun.
         *      bad_alloc saa vuotaa ulos, eli muistin loppumiseen ei tarvitse erikseen varautua.
	 */
	class Nayttorajapinta
	{
		public:
			
			/**
             *  \brief Oletusrakentaja.
             *
             *  Tämä on määritelty vain, jotta voitaisiin määritellä
             *  olion tila heti luomisen jälkeen.
             *  \pre -
             *  \post Näyttörajapinta on tulostustilassa.
			 *		Poikkeustakuu: Poikkeuksen sattuessa Pelirajapinta-olion 
			 *			luontiepäonnistui, mistä syytä oliolla ei ole sisäistä 
			 *			tilaa jolle voisi antaa takuita
             */
			Nayttorajapinta(){}
			
			/**
             *  \brief Oletuspurkaja.
             *  \pre -
             *  \post No-throw -takuu.
             */
            virtual ~Nayttorajapinta(){}
			
			/**
             *  \brief Tulostustilan tarkistus.
             *
			 *	Kertoo näytön käyttäjälle onko näyttö tulostustilassa vai
			 *	rakennustilassa.
			 * \pre -
			 *	\post Palautettu tieto laudan tilasta.
			 *		Poikkeusturvallisuus: No-throw takuu.
			 *
             *  \return <code>true</code> jos näyttö on tulostustilassa, 
			 *	<code>false</code> jos näyttö on rakennustilassa.
             */
            virtual bool onTulostustilassa() const =0;
			/**
			 *	\brief Tulostaa ilmoituksen esineen poimisesta.
			 *
			 *	Tulostaa ilmoituksen jossa kerrotaan että annettu pelaaja on
			 *	poiminut annetun esineen.
                         * 
                         *      
			 *	\pre Näyttö tulostustilassa.
			 *	\post Ilmoitus esineen poimisesta tehty.
			 *		Poikkeusturvallisuus: Vahvatakuu, jos Nayttovirhe.
			 *		Muuten perustakuu.
			 *
			 *	\param[in] esine Poimitun esineen merkki.
			 *	\param[in] pelaaja Pelaajan nimi, joka poimi esineen.
			 *
			 *	\exception Nayttovirhe Tulostus epäonnistui.
			 */
			virtual void ilmoitusEsinePoimittu(
				char esine, 
				std::string const& pelaaja) = 0;
			
           /**
            * \brief Tulostaa ilmoituksen erikoispalaan astumisesta.
            * Tulostaa ilmoituksen, jossa kerrotaan että annettu pelaaja on astunut erikoispalaan, jonka tyyppi on annettu
            * 
            * \pre Näyttö on tulostustilassa.
            * \post Ilmoitus palaan astumisesta tehty.
            * Poikkeusturvallisuus: Vahvatakuu, jos Nayttovirhe.
            * Muuten perustakuu.
            * 
            * \param[in] tyyppi Erikoispalan Julkinen:ErikoispalaTyyppi
            * \param[in] pelaaja Pelaajan nimi, joka astui erikoispalaan
            * 
            * \exception Nayttovirhe Tulostus epäonnistui
            */ 
           virtual void ilmoitusErikoispalaanAstuttu(Julkinen::ErikoispalaTyyppi tyyppi, std::string const& pelaaja) = 0;
			/**
			 *	\brief Tulostaa tiedon vuorossa olevasta pelaajasta.
			 *
			 *	Tulostaa vuorossa olevan pelaajan nimen ja > merkin sen 
			 *	jälkeen. Metodi pitää ajaa Pelirajapinta::vaihdaVuoro()
			 *	-metodi ajon jälkeen ja aina kun pelaajan antamassa komennossa
			 *	on virhe. 
			 *
			 *	\pre Näyttö tulostustilassa 
			 *	\post Vuorossa olevan pelaajan nimi tulostettu.
			 *		Poikkeustuvallisuus: Vahvatakuu, jos Nayttovirhe.
			 *		Muuten perustakuu.
			 *
			 *	\param[in] nimi Vuorossa olevan pelaajan nimi.
			 *
			 *	\exception Nayttovirhe Tulostus epäonnistui.
			 */
			virtual void ilmoitusVuorossa(std::string const& nimi) = 0;
			
			/**
			 *	\brief Lisää yksittäisen pelaajan tiedot kartan alle tulostusta varten
			 *
			 *	\pre Näyttö on on rakennustilassa. Pelaajan nimen
			 *  pituus on <a href="tyoohje.html">työohjeen</a> rajoissa.
			 *	\post Pelaajan tiedot on lisätty tulostettavaksi.
			 *		Poikkeusturvallisuus: Perustakuu.
			 *
			 *	\param[in] nimi Pelaajan, jonka tiedot tulostetaan, nimi.
			 *	\param[in] keratytesineet Pelaajan keräämät esineet.
			 *	\param[in] kerattavatesineet Pelaajan jäljellä olevat kerättävät 
			 *		esineet.
			 *	\param[in] edellinentoiminto Pelaajan edellinen toiminto.
			 */
			 virtual void tulostaPelaajantiedot(std::string const& nimi, 
					std::string const& keratytesineet, 
					std::string const& kerattavatesineet, 
					std::string const& edellinentoiminto) = 0;
			
           /**
            *  \brief Laittaa näytön pelialueen rakennustilaan
            *
            *	Asettaa näytön tilan rakennustilaan. Tämä metodi on ajettava 
            *	ennen palaLaudalle(), pelaajaLaudalle(), esineLaudalle() ja
            *	komentoLopetaRakennus() metodeja.
            * 
            * \pre -
            *  \post Näyttö on rakennustilassa ja pelilaudan 
            *	kuva on tyhjä. 
            *	Poikkeusturvallisuus: No-throw takuu.
             */
            virtual void komentoAloitaRakennus() = 0;
			
			/**
			 *	\brief Lisää palan tulostettavaan karttaan.
			 *
			 *	\pre Nayttö on rakennustilassa. 
			 *		Koordinaatti on pelialueen rajoissa.
			 *		Rotaatio on 1-4.
			 *	\post Pala on lisatty tulostettavassa bittikartassa annettuun
			 *		sijaintiin. Poikkeusturvallisuus: Perustakuu.
			 *	\param[in] tyyppi Lisättävän palan tyyppi.
                         * \param[in] etyyppi palaan liitetty Julkinen::ErikoispalaTyyppi, käytetään -n vivun tulostuksen apuna.
			 *	\param[in] rotaatio Lisättävän palan rotaatio.
			 *
			 *	\param[in] sijainti koordinaatti mihin pala lisätään.  
                         *      Jos sijainti.onkoIrtopala() palautaa <code>true</code>,
                         *      niin palasta tehdään irtopala -kartta.
                         * 
                         * \param[in] kohde Teleporttipalan kohteen koordinaatti. Muilla paloilla parametria ei anneta.
			 *		
                         */
			virtual void palaLaudalle(Julkinen::PalaTyyppi tyyppi, 
                                                  Julkinen::ErikoispalaTyyppi etyyppi, unsigned int rotaatio, 
                                                  Julkinen::Koordinaatti const& sijainti, Julkinen::Koordinaatti const& kohde = Julkinen::Koordinaatti()) = 0;
			
			/**
			 *	\brief Lisää pelaajan merkin tulostettavaan karttaan.
			 *	
			 *	\pre Nayttö on rakennustilassa. Koordinaatti on
			 *	pelialueen rajoissa.
			 *	\post Pelaaja on lisätty tulostettavalle kartalle.
			 *		Poikkeusturvallisuus: Perustakuu.
			 *
			 *	\param[in] merkki Pelaajan sijaintia esittävä merkki kartalla.
			 *	\param[in] sijainti Pelaajan koordinaatti kartalla.
			 *
			 */
			virtual void pelaajaLaudalle(char merkki, 
					Julkinen::Koordinaatti const& sijainti) = 0;
			
			/**
			 *	\brief Lisää esineen tulostettavaan lautaan
			 *	
			 *	\pre Nayttö on rakennustilassa. Esineen merkki, jokin
			 *	<a href="tyoohje.html">työohjeessa</a> annetuista merkeistä.
			 *	Koordinaatti on pelialueen rajoissa.
			 *
			 *	\post Esine on lisätty tulostettavalle kartalle.
			 *		Poikkeusturvallisuus: Perustakuu.
			 *
			 *	\param[in] merkki Esine sijaintia esittävä merkki kartalla.
			 *	\param[in] sijainti Esine koordinaatti kartalla.
			 *
			 */
			virtual void esineLaudalle(char merkki, 
					Julkinen::Koordinaatti const& sijainti) = 0;
			
			/**
             *  \brief Lopeta laudanmuodostustila ja tulosta kartta, pelaajien tiedot ja irtopala.
             *
             *  \pre Näyttö on rakennustilassa.
             *  \post Näyttörajapinta on tulostustilassa ja pelilauta on
             *      tulostettu. Poikkeusturvallisuus: Perustakuu.
			 *
             *  \exception Nayttovirhe Tulostaminen epäonnistui.
             */
			virtual void komentoLopetaRakennus() = 0;
	};


}

#endif // JULKINEN_NAYTTORAJAPINTA_HH

