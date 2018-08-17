#ifndef JULKINEN_PELIRAJAPINTA_HH
#define JULKINEN_PELIRAJAPINTA_HH


/**
 *	\version $Id: pelirajapinta.hh 2738 2013-04-18 12:04:14Z voutilai $
 *	\file pelirajapinta.hh
 *	\brief Pelirajapinta-luokan esittely. ($Revision: 2738 $)
 *	\author ©2011 Eero Salonen <eero.j.salonen@tut.fi> 
 * 
 * 	\mainpage
 * 	Tämä on OHJ-1450 Olio-ohjelmoinnin jatkokurssin vuoden
 *      2013 harjoitustyön Labyrinttipeli valmiina annettu sovelluskehys.
 * 
 * 	Valmiina annetut rajapinnat, tyypit ja luokat löytyvät kaikki
 * 	nimiavaruudesta <code>Julkinen</code>.
 */

#include <string>
#include "koordinaatti.hh"
#include "luettelotyypit.hh"


/// \namespace Julkinen
namespace
Julkinen
{
    
	class Nayttorajapinta;

	/**
	 *	\class Pelirajapinta
	 *	\brief Labyrintti-pelin ohjausrajapinta
	 *
	 *	Tämän rajapinnan läpi pelin pääohjelma pystyy ohjaamaan pelin toiminta
	 *	logiikaa. Pääohjelman vastuulla on pelin alustustiedoston lukeminen ja
	 *	komentotulkin pyörittäminen. 
	 *
	 *	Peli voi olla kahdessa eri tilassa, alustustilassa ja pelitilassa.
	 *	Kun peli-olio luodaan se on alustustilassa ja sille voidaan syöttää
	 *	peliin liittyvät tiedot, kuten pelialueen koko, pelaajat, palat ja 
	 *	esineet. Kun peli on alustustilassa ei pelivuoroihin liittyviä 
         *      toiminnalluuksia voida ajaa.
	 *
	 *	Peli alustetaan kutsumalla ensiksi lisaaNaytto() metodia, jolla peli
	 *	liitetään tulostusrajapintaan. Näytön lisäyksen jälkeen kutsutaan
	 *	maaritaPelialueenKoko() metodia, jolla kerrotaan kuinka suuri pelialue
	 *	pelissä on. Tämän jälkeen peliin lisätään palat ja pelaajat kutsumalla
	 *	jokaiselle palalle ja pelaajalle lisaaPala tai lisaaPelaaja metodeja.
	 *	Kun palat ja pelaajat on lisätty, niin peliin lisätään esineet
	 *	kutsumalla lisaaEsine metodia jokaiselle esineelle. Kun alustus on 
	 *	suoritettu loppuun kutsutaan alustusLopeta metodia.
	 *
	 *	Peliä pelataan, niin että pelaaja vuorollaan työntää irtopalan
	 *	komentoTyonna() metodilla ja tämän jälkeen pelaaja liikkuu 
	 *	komentoLiiku() metodilla. Poikkeuksena yllä olevaan on tietokone-
	 *	pelaaja, joka ei välttämättä työnnä palaa vuorollaan vaan käyttää
	 *	automaatti-liikkumista. Pelaajan vuoron lopuksi kutsutaan 
	 *	vaihdaVuoro()-metodia.
         * 
         *      Poikkeuksista bac_alloc saa vuotaa ulos, jos muisti loppuu. Käytännössä
         *      tämä tarkoittaa sitä, että muistin loppumiseen ei välttämättä tarvitse 
         *      varautua.
         * 
         *      Muistin loppumisesta sekä näyttörajapinnan heittämistä poikkeuksista tarjotaan minimitakuu.
	 *
	 */
	class Pelirajapinta
	{
		public:
			
			
			/**
			 *	\brief Oletusrakentaja.
			 *
             *  Tämä rakentaja on määritelty, jotta voidaan
             *  dokumentoida Pelirajapinnan tila pelin luomisen jälkeen.
             *	
                         *  \pre -
			 *	\post Peli on alustustilassa ja sen alustaminen voidaan
			 *      aloittaa.
			 *		Poikkeustakuu: Poikkeuksen sattuessa Pelirajapinta-olion 
			 *			luonti epäonnistui, mistä syytä oliolla ei ole sisäistä 
			 *			tilaa jolle voisi antaa takuita.
			 */
			Pelirajapinta()
			{
			}
			
			/**
			 *	\brief Tuhoaja.
			 * \pre -
			 *	\post No-throw takuu.
			 */
			virtual ~Pelirajapinta()
			{
			}

			/**
			 *	\brief Kertoo onko peli alustustilassa.
			 * \pre -
			 *	\post On palauttanut tiedon onko peli alustustilassa. 
			 *		Poikkeustakuu: No-throw takuu.
			 *
			 *	\return Palauttaa <code>true</code> jos peli on alustustilassa.
			 *		Palauttaa <code>false</code> jos peli ei ole alustustilassa.
			 */
			virtual bool onkoAlustustilassa() const = 0;
			
			/**
			 *	\brief Lisaa tulostus olion peliin
			 *
			 *	\pre Peli on alustustilassa. Annettu parametri ei ole tyhjä. Näyttöä ei ole lisätty.
			 *	\post Tulostus-olio lisätty peliin. 
			 *		Poikkeustakuu: No-throw takuu.
			 *
			 *	\param[in, out] naytto osoitin Nayttorajapinta -luokan 
			 *	toteuttavaan olioon.
			 */
			virtual void lisaaNaytto(Nayttorajapinta* naytto) = 0;
			
			/**
			 *	\brief Maarittaa pelikentän koon.
			 *
			 *	\pre Naytto lisatty peliin.
			 *	\post Pelialueen koko on määritelty. Perustakuu.
			 *
			 *	\param[in] koko Julkinen::Koordinaatti joka määrittää pelialueen rajat
                         *                      eli kertoo pelialueen oikean alakulman koordinaatin.
                         *                      
			 */
			virtual void maaritaPelialueenKoko(Julkinen::Koordinaatti const& koko) = 0;
			
			/**
			 *	\brief Pelin alustusfunktio, joka lisaa pelaajan peliin
			 *
			 *	\pre Pelialueen koko on määritelty. Peli on alustustilassa.
			 *	\post Pelaaja lisätty peliin.
			 *		Poikkeustakuu: Perustakuu poikkeuksen sattuessa.
			 *
			 *	\param[in] tyyppi Tieto siitä minkälainen pelaaja lisätään.
			 *	\param[in] nimi Pelaajan nimi.
			 *	\param[in] lyhenne Pelaajaa kuvaava merkki pelissä.
			 *	\param[in] sijainti Kertoo mihin labyrintin koordinaattiin pelaaja laitetaan.
			 *
			 *	\exception Alustusvirhe Annettu koordinaatti on pelialueen ulkopuolella.
                         *      \exception Alustusvirhe Annetussa koordinaatissa on jo pelaaja.
			 */
			virtual void lisaaPelaaja(PelaajaTyyppi tyyppi, std::string const& nimi, char lyhenne, Julkinen::Koordinaatti const& sijainti) = 0;
			
			/**
			 *	\brief Pelin alustusfunktio, joka lisaa palan peliin.
			 *
			 *	\pre Peli on alustustilassa. Pelialueen koko on määritelty. Annettuun koordinaattiin ei vielä lisätty palaa.
			 *	\post Pelilautaan on lisätty pala.
			 *		Poikkeustakuu: Perustakuu poikkeuksen sattuessa.
			 *
			 *	\param[in] pala Tieto siitä minkä laista palaa lisätään.
			 *	\param[in] rotaatio Lisättävän palan rotaatio (1-4).
			 *				rotaatiota ei tarkasteta jos irtopala
			 *	\param[in] sijainti koordinaatti mihin pala lisätään.
			 *		Jos sijainti.onkoIrtopala() palautaa <code>true</code>,
			 *		niin lisättävä pala on irtopala.
			 *
			 *	\exception Alustusvirhe Annettu koordinaatti on pelialueen ulkopuolella.
			 *	\exception Alustusvirhe	Annettu rotaatio on virheellinen.
			 */
			virtual void lisaaPala(PalaTyyppi pala, unsigned int rotaatio, Julkinen::Koordinaatti const& sijainti) = 0;
			
			/**
			 *	\brief Pelin alustusfunktio, joka lisaa esineen peliin.
			 *
			 *	\pre Peli on alustustilassa. Pelilauta ja pelaajat on alustettu.
			 *	\post Esine on lisatty peliin ja mahdollisesti annetulle 
			 *		pelaajalle, esine on lisätty kerättäviin esineisiin.
			 *		Poikkeustakuu: Perustakuu poikkeuksen sattuessa.
			 *
			 *	\param[in] merkki Esinettä kuvaava merkki pelissä.
			 *	\param[in] sijainti Kertoo mihin labyrintin koordinaattiin esine laitetaan.
			 *	\param[in] pelaaja Pelaajan nimi jonka tehtävänä on poimia esine. 
			 *
			 *	\exception Alustusvirhe Pelaajaa ei ole lisatty peliin.
			 *	\exception Alustusvirhe Annettu koordinaatti on pelialueen ulkopuolella.
			 */
           virtual void lisaaEsine(char merkki, Julkinen::Koordinaatti const& sijainti, std::string const& pelaaja) = 0;
           
           /**
            * \brief Pelin alustusfunktio, joka asettaa palan erikoispalan tyypin.
            * 
            * \pre Peli on alustustilassa. Pelilauta ja palat on alustettu.
            * \post Palan erikoisominaisuudet on luotu.
            *       Poikkeustakuu: Perustakuu poikkeuksen sattuessa.
            * 
            * \param[in] tyyppi Palan erikoistyyppi, joka kertoo onko pala normaali, teleportti, siunattu tai kirottu.
            * \param[in] sijainti Kertoo mitä labyrintin palaa käsitellään.
            * \param[in] kohde Teleportti-palan kohderuudun koordinaatti, muilla paloilla parametria ei anneta.
            * 
            * \exception Alustusvirhe Annettu koordinaatti on pelialueen ulkopuolella.
            */
           virtual void asetaPalanTyyppi(Julkinen::ErikoispalaTyyppi tyyppi, Julkinen::Koordinaatti const& sijainti, Julkinen::Koordinaatti const& kohde = Julkinen::Koordinaatti()) = 0;
           
			/**
			 *	\brief Lopettaa pelin alustuksen.
			 *
			 *	\pre Peli on alustettu.
			 *	\post Peli on pelitilassa.
			 *		Poikkeustakuu: Perustakuu poikkeuksen sattuessa.
			 */
			virtual void alustusLopeta() = 0;

			/**
			 *	\brief Kertoo onko peli pelitilassa.
			 * \pre -
			 *	\post On palauttanut tiedon onko peli pelitilassa.
			 *		Poikkeustakuu: No-throw takuu.
			 *
			 * 	\return Palauttaa <code>true</code> jos peli on pelitilassa.
			 *		Palauttaa <code>false</code> jos peli ei ole pelitilassa.
			 */
			virtual bool onkoPelitilassa() const = 0;
			
			/**
			 *	\brief Työntää irtopalan annettuun kohtaan.
			 *
                         *      Raakilepalautuksessa tätä operaatiota ei kutsuta.
                         * 
			 *	\pre Peli on pelitilassa.
			 *	\post Irtopala on asetettu annettuun kohtaan ja työntö kohdan
			 *		työntösuunnan mukaisen vastapään pala on otettu uudeksi 
			 *		irtopalaksi. Pelilauta on tulostettu uudestaan.
			 *		Poikkeustakuu: Vahvatakuu Komentovirhe poikkeuksen sattuessa.
			 *				       
			 *
			 *	\param[in] reuna Reuna jolle pala työnnetään.
			 *	\param[in] rotaatio Työnnettävän palan rotaatio (1-4)
			 *	\param[in] paikka Mihin kohtaan reunaa pala työnnetään.
			 *
			 *	\exception Toimintovirhe Pelaaja on jo työntänyt palaa 
			 *	tällä vuorolla.
			 *	\exception Komentovirhe Paikka on virheellinen.
			 *	\exception Komentovirhe	Rotaatio on virheellinen.
			 */
			virtual void komentoTyonna(Reuna reuna, unsigned int paikka, unsigned int rotaatio) = 0;
			
			/**
			 *	\brief Liikuttaa vuorossa olevaa pelaajaa.
			 *
			 *	Liikuttaa vuorossa olevaa pelaajaa annettuun suuntaan annetun
			 *	määrän. Jos pelaaja ei pysty liikkumaan annettuun suuntaan
			 *	annettua määrää heitetään Toimintovirhe. Toimintovirhe
			 *	heitetään myös silloin jos pelaaja ei ole työntänyt palaa 
			 *	tällä vuorolla, paitsi jos suunta on AUTOMAATTI.
                         *      Raakilepalautuksessa liikkuminen suoritetaan, vaikka työntämistä
                         *      ei olekaan suoritettu (eli poikkeusta ei heitetä).
			 *
			 *	
			 *
			 *	\pre Peli on pelitilassa.
			 *	\post Pelaaja on liikutettu ja pelilauta on tulostettu uudestaan.
			 *		Poikkeustakuu: Vahvatakuu Komentovirhe tai Toimintovirhe 
			 *				poikkeuksen sattuessa.
			 *
			 *	\param[in] suunta Suunta johon pelaajaa siirretään.
			 *	\param[in] maara Pelaajan liikkumien ruutujen määrä.
			 *
			 *	\exception Toimintovirhe Vuorossa oleva pelaaja ei voi liikkua
			 *		annettuun suuntaan annettua määrää.
			 *	\exception Toimintovirhe Vuorossa oleva pelaaja ei ole 
			 *		työntänyt irtopalaa. Ei heitetä jos suunta on AUTOMAATTI.
                         *              Ei heitetä raakilepalautuksessa.
			 *	\exception Komentovirhe maara on negatiivinen.
			 *	\exception Komentovirhe maara on 0, mutta suunta ei ole
			 *		PAIKALLAAN.
			 */
			virtual void komentoLiiku(Suunta suunta, unsigned int maara = 0) = 0;
			
			/**
			 *	\brief Vaihtaa vuoron seuraavalle pelaajalle ja ilmoittaa,
                         *      jatketaanko peliä, vai onko jokin pelaaja voittanut pelin.
                         *      <b>Huom!</b> Raakilepalautuksessa tulkitaan, että kukaan ei voita
                         *      peliä koskaan (koska kerättäviä esineitä ei ole).
			 *
			 *	\pre Peli on pelitilassa ja pelaajan toimminnot suoritettu.
			 *	\post Peli on loppu tai valmis ottamaan komennon vastaan
			 *		vuorossa olevalta pelaajalta.
			 *		Poikkeustakuu: Vahvatakuu Toimintovirhe poikkeuksen 
			 *		sattuessa.
			 *
			 *	\return <code>false</code>, mikäli peli loppui jonkin
                         *      pelaajan voittoon, <code>true</code> jos peli vielä
                         *      jatkuu.
			 *
			 *	\exception Toimintovirhe Pelaajaa ei ole liikkunut
			 *		ennen vuoron vaihdon kutsua.
			 */
			virtual bool vaihdaVuoro() = 0;
			
			/**
			 *	\brief Palauttaa vuorossa olevan pelaajan tyypin
			 *
			 *	\pre Peli on pelitilassa.
			 * 	\post Peli on pelitilassa ja vuorossa olevan pelaajan 
			 *	\c PelaajaTyyppi on palautettu. Poikkeustakuu: No-throw takuu.
			 *
			 *	\return Palauttaa vuorossa olevan pelaajan <code>PelaajaTyyppi</code>.
			 */
			virtual PelaajaTyyppi haeVuorossa() = 0;
			
	};
}

	
#endif //JULKINEN_PELIRAJAPINTA_HH

