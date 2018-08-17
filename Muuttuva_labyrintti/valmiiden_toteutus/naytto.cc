
/**
 *	\version $Id: naytto.cc 1800 2011-02-05 06:54:47Z salone58 $
 *  \file  naytto.cc
 *  \brief Naytto-luokkan toteutus ($Revision: 1800 $)
 *  \author ©2010 Eero Salonen <eero.j.salonen@tut.fi>
 */

#include "include/naytto.hh"
#include "../nayttovirhe.hh"
#include "../vaittama.hh"
#include "../debug.hh"
#include <ostream>
#include <iostream>
#include <sstream>


static const Naytto::P TPALAP = { "+--+", "..", "+..+", ".." };
static const Naytto::P IPALAP = { "+..+", "||", "+..+", "||" };
static const Naytto::P LPALAP = { "+..+", "..", "+--+", "||" };
static const Naytto::P TPALAV = { "+||+", "..", "+..+", ".." };
static const Naytto::P IPALAV = { "+..+", "--", "+..+", "--" };
static const Naytto::P LPALAV = { "+..+", "..", "+||+", "--" };
static const int IRTOPALAX = 25;
static const int IRTOPALAY = 4;
static const std::string KULMA = ">";
static const std::string PELAAJA = "Pelaaja ";
static const std::string POIMI = " poimi esineen ";
static const std::string ASTUI = " astui erikoispalaan";
static const std::string TYYPPI = ", jonka tyyppi on ";
static const std::string PALKINTO = "palkinto";
static const std::string TELEPORTTI = "teleportti";
static const std::string SIUNATTU = "siunattu";
static const std::string KIROTTU = "kirottu";
static const std::string KAKSOISPISTE = ": ";
static const std::string PYSTYVIIVA = " | ";
static const std::string ALOITTAVAKAARE = "(";
static const std::string SULKEVAKAARE = ")";
static const std::string TYHJARIVI(26, ' ');

Naytto::Naytto(Julkinen::Koordinaatti const& mitat, 
               unsigned int x, 
               unsigned int y,
               bool debug_naytto): 
_debug_naytto(debug_naytto), _esineet(),_irtopalanEsine(0), _erikoispalat(), _irtopalanErikoispala(), _pelaajat(),
_tila(TULOSTUS), _kartta(x, y),_irtopala(IRTOPALAX, IRTOPALAY),
_koko(mitat)
{}
			

Naytto::~Naytto()
{

}


bool Naytto::onTulostustilassa() const
{
	if(_tila == TULOSTUS){ return true; }
	else{ return false; }
}


void Naytto::ilmoitusEsinePoimittu(char esine, 
	/*Julkinen::EsineTyyppi tyyppi,*/ 
	std::string const& pelaaja)
{
	std::ostringstream tulostevirta;
	tulostevirta << PELAAJA << pelaaja << POIMI << esine;
/*	
   switch(tyyppi)
	{
		case Julkinen::PALKINTO: tulostevirta << PALKINTO;
			break;
		case Julkinen::TELEPORTTI: tulostevirta << TELEPORTTI;
			break;
		case Julkinen::SIUNATTU: tulostevirta << SIUNATTU;
			break;
		case Julkinen::KIROTTU: tulostevirta << KIROTTU;
			break;
	}
 */
   tulostevirta << std::endl;
	tulosta(tulostevirta);
}

void Naytto::ilmoitusErikoispalaanAstuttu(Julkinen::ErikoispalaTyyppi tyyppi,
                                          std::string const& pelaaja)
{
   std::ostringstream tulostevirta;
   tulostevirta << PELAAJA << pelaaja << ASTUI << TYYPPI;
   switch(tyyppi)
   {
    case Julkinen::NORMAALI:
      break;
    case Julkinen::TELEPORTTI: tulostevirta << TELEPORTTI;
      break;
    case Julkinen::SIUNATTU: tulostevirta << SIUNATTU;
      break;
    case Julkinen::KIROTTU: tulostevirta << KIROTTU;
      break;
   }
   
   tulostevirta << std::endl;
   tulosta(tulostevirta);
}

void Naytto::ilmoitusVuorossa(std::string const& nimi)
{
	//std::ostringstream tulostevirta;
	//tulostevirta 
	std::cout << nimi << KULMA;
	_vuorossa = nimi;
	//tulosta(tulostevirta);
}

void Naytto::vuorossa()
{
	std::cout << _vuorossa << KULMA;
}

void Naytto::tulostaVoittaja()
{
	std::cout << "Pelin voitti "<< _vuorossa << std::endl;
}

void Naytto::tulostaPelaajantiedot(std::string const& nimi, 
		std::string const& keratytesineet, 
		std::string const& kerattavatesineet, 
		std::string const& edellinentoiminto)
{
	std::string temp = "";
	//std::ostringstream tulostevirta;
	temp = (nimi + KAKSOISPISTE + kerattavatesineet);
	temp += (PYSTYVIIVA + keratytesineet + " ");
	temp += (ALOITTAVAKAARE + edellinentoiminto + SULKEVAKAARE);
// 	temp.resize(30, ' ');
	_pelaajientiedot.push_back(temp);
	//tulostevirta << temp;
	//tulosta(tulostevirta);
}


void Naytto::komentoAloitaRakennus()
{
   _tila = RAKENNUS;
   _kartta.tyhjenna();
   if ( _debug_naytto )
   {
      _esineet.clear();
      _erikoispalat.clear();
      _pelaajat.clear();
   }
   
}


void Naytto::palaLaudalle(Julkinen::PalaTyyppi tyyppi, Julkinen::ErikoispalaTyyppi etyyppi, unsigned int rotaatio, 
                          Julkinen::Koordinaatti const& sijainti, Julkinen::Koordinaatti const& kohde)
{
   
   tarkistaOnkoRakennustila();
   tarkistaKoordinaatti(sijainti);
   

      
	P pala;
	if(sijainti.onkoIrtopala())
	{
		rotaatio = 1;
	}

	switch(tyyppi)
	{
         case Julkinen::IPALA: 
           if(rotaatio == 1 || rotaatio == 3){pala = IPALAP;}
           else{pala = IPALAV;}
           break;
         case Julkinen::LPALA: 
           if(rotaatio == 1 || rotaatio == 3){pala = LPALAP;}
           else{pala = LPALAV;}
           break;
         case Julkinen::TPALA: 
           if(rotaatio == 1 || rotaatio == 3){pala = TPALAP;}
           else{pala = TPALAV;}
           break;
	}
   
	if(sijainti.onkoIrtopala())
	{
           luoIrtopalaKartta(tyyppi);
           if ( _debug_naytto )
           {
              _irtopalanErikoispala.tyyppi = etyyppi;
              _irtopalanErikoispala.kohde = kohde;
              
           }
           
	}
	else
	{
	
           unsigned int long y = (sijainti.haeYkoordinaatti() - 1) * 4;
           unsigned int long x = (sijainti.haeXkoordinaatti() - 1) * 4;
           
           if ( _debug_naytto )
           {
              if ( etyyppi != Julkinen::NORMAALI )
              {
                 Erikoispala tmp;
                 tmp.tyyppi = etyyppi;
                 tmp.sijainti = sijainti;
                 tmp.kohde = kohde;
                 _erikoispalat.push_back(tmp);
              }
           }
		switch(rotaatio)
		{
			case 1:
				_kartta.vaakateksti( x, y, pala.yla );
				_kartta.pystyteksti( (x+3), (y+1), pala.oikea );
				_kartta.vaakateksti( x, (y+3), pala.ala );
				_kartta.pystyteksti( x, (y+1), pala.vasen );
				break;
			case 2:
				_kartta.vaakateksti( (x+1), y, pala.vasen );
				_kartta.pystyteksti( (x+3), y, pala.yla );
				_kartta.vaakateksti( (x+1), (y+3), pala.oikea );
				_kartta.pystyteksti( x, y, pala.ala );
				break;
			case 3:
				_kartta.vaakateksti( x, y, pala.ala );
				_kartta.pystyteksti( (x+3), (y+1), pala.vasen );
				_kartta.vaakateksti( x, (y+3), pala.yla );
				_kartta.pystyteksti( x, (y+1), pala.oikea );
				break;
			case 4:
				_kartta.vaakateksti( (x+1), y, pala.oikea );
				_kartta.pystyteksti( (x+3), y, pala.ala );
				_kartta.vaakateksti( (x+1), (y+3), pala.vasen );
				_kartta.pystyteksti( x, y, pala.yla );
				break;
			default:	throw Julkinen::Nayttovirhe("Virhe: Virheellinen rotaatio");
		}
		
		/*_kartta.vaakaviiva( (x+1), (y+1), 1, r );
		_kartta.vaakaviiva( (x+2), (y+1), 1, merkki );
		_kartta.vaakaviiva( (x+1), (y+2), 2, '.' );*/
		_kartta.suorakaide(x+1, y+1, 2, 2, '.');
	}
	
	
}


void Naytto::pelaajaLaudalle(char merkki, 
		Julkinen::Koordinaatti const& sijainti)
{

	tarkistaOnkoRakennustila();
	tarkistaKoordinaatti(sijainti);

   if ( _debug_naytto )
   {
      Pelaaja tmp;
      tmp.merkki = merkki;
      tmp.sijainti = sijainti;
      _pelaajat.push_back(tmp);
   }
   
   
   unsigned int long y = (sijainti.haeYkoordinaatti() - 1) * 4;
	unsigned int long x = (sijainti.haeXkoordinaatti() - 1) * 4;
	_kartta.vaakaviiva( (x+1), (y+1), 1, merkki );
	//_kartta.vaakaviiva( (x+2), (y+1), 1, '.' );
	//_kartta.vaakaviiva( (x+1), (y+2), 2, '.' );
}


void Naytto::esineLaudalle(char merkki, 
		Julkinen::Koordinaatti const& sijainti)
{
	tarkistaOnkoRakennustila();
	if(sijainti.onkoIrtopala())
	{
		 for( unsigned int i = 0; i < 4; ++i )
		 {
		   _irtopala.vaakaviiva( (2+i*5), 2, 1, merkki);
		 }
           
           if ( _debug_naytto )
           {
              _irtopalanEsine = merkki;
              
           }
           
	}
	else
	{
		tarkistaKoordinaatti(sijainti);
		unsigned int long y = (sijainti.haeYkoordinaatti() - 1) * 4;
		unsigned int long x = (sijainti.haeXkoordinaatti() - 1) * 4;
		//_kartta.vaakaviiva( (x+1), (y+2), 1, '.' );
		_kartta.vaakaviiva( (x+2), (y+2), 1, merkki );
           
           if ( _debug_naytto )
           {
              Esine tmp;
              tmp.merkki = merkki;
              tmp.sijainti = sijainti;
              _esineet.push_back(tmp);
           }
           
	}
}


void Naytto::komentoLopetaRakennus()
{
	
   tarkistaOnkoRakennustila();
   //std::ostringstream tulostevirta;

   if ( _debug_naytto )
   {
      for ( unsigned int i = 0; i < _pelaajat.size(); ++i )
      {
         std::cout << "Pelaaja: " << _pelaajat.at(i).merkki << " sijainti: x: " << _pelaajat.at(i).sijainti.haeXkoordinaatti() << " y: " << _pelaajat.at(i).sijainti.haeYkoordinaatti() << std::endl;
      }
      
      for ( unsigned int i = 0; i < _esineet.size(); ++i )
      {
         std::cout << "Esine: " << _esineet.at(i).merkki << " sijainti: x: " << _esineet.at(i).sijainti.haeXkoordinaatti() << " y: " << _esineet.at(i).sijainti.haeYkoordinaatti() << std::endl;
      }
      
      if ( _irtopalanEsine != 0 )
      {
         std::cout << "Esine irtopalassa: " << _irtopalanEsine << std::endl;
      }
      
      for ( unsigned int i = 0; i < _erikoispalat.size(); ++i )
      {
         std::cout << "Erikoispala: ";
         switch(_erikoispalat.at(i).tyyppi)
         {
          case Julkinen::NORMAALI:
            break;
          case Julkinen::TELEPORTTI:
            std::cout << TELEPORTTI;
            if ( _erikoispalat.at(i).kohde.onkoIrtopala() )
            {
               std::cout << " Kohde irtopalassa(tai kohdetta ei ole annettu) ";
            }
            else
            {
               std::cout << " Kohde x: " << _erikoispalat.at(i).kohde.haeXkoordinaatti() << " y: " << _erikoispalat.at(i).kohde.haeYkoordinaatti();
            }
            break;
          case Julkinen::SIUNATTU:
            std::cout << SIUNATTU;
            break;
          case Julkinen::KIROTTU:
            std::cout << KIROTTU;
            break;
         }
         
         std::cout << " sijainti: x: " << _erikoispalat.at(i).sijainti.haeXkoordinaatti() << " y: " << _erikoispalat.at(i).sijainti.haeYkoordinaatti() << std::endl;
      }
      
      if ( _irtopalanErikoispala.tyyppi != Julkinen::NORMAALI )
      {
         std::cout << "Erikoispala irtopalassa: ";
         switch(_irtopalanErikoispala.tyyppi)
         {
          case Julkinen::NORMAALI:
            break;
          case Julkinen::TELEPORTTI:
            std::cout << TELEPORTTI;
            if ( _irtopalanErikoispala.kohde.onkoIrtopala() )
            {
               std::cout << " Kohde irtopalassa(tai kohdetta ei ole annettu) ";
            }
            
            else
            {   
               std::cout << " Kohde x: " << _irtopalanErikoispala.kohde.haeXkoordinaatti() << " y: " << _irtopalanErikoispala.kohde.haeYkoordinaatti();
            }
            
            break;
          case Julkinen::SIUNATTU:
            std::cout << SIUNATTU;
            break;
          case Julkinen::KIROTTU:
            std::cout << KIROTTU;
            break;
         }
         
         std::cout << std::endl;
      }
   }
   
	_kartta.tulosta(std::cout);
	std::cout << TYHJARIVI << std::endl;
	
	for(unsigned int i = 0; i < _pelaajientiedot.size(); ++i)
	{
		std::cout << _pelaajientiedot.at(i) << std::endl;
	}
	_pelaajientiedot.clear();
	std::cout << TYHJARIVI << std::endl;
	
	_irtopala.tulosta(std::cout);
	//tulostevirta << TYHJARIVI;
	_tila = TULOSTUS; 
	//tulosta(tulostevirta);
}

void Naytto::tarkistaKoordinaatti(Julkinen::Koordinaatti const& tarkistettava)
{
	
	if(!tarkistettava.onkoIrtopala())
	{
		
		if(_koko.haeXkoordinaatti() < tarkistettava.haeXkoordinaatti() 
			|| _koko.haeYkoordinaatti() < tarkistettava.haeYkoordinaatti())
		{
			throw Julkinen::Nayttovirhe("Virhe: Virheellinen sijainti");
		}
	}
}

void Naytto::tulosta(std::ostringstream& virta)
{
	//if(virta.good())
	//{
		std::cout << virta.str();
	//}
	//else
	//{
//		throw Julkinen::Nayttovirhe("Virhe: Tulostus epäonnistui");
	//}
}

void Naytto::luoIrtopalaKartta(Julkinen::PalaTyyppi tyyppi)
{
	_irtopala.tyhjenna();
	P pala;
	P palav;
	if(tyyppi == Julkinen::IPALA){pala = IPALAP; palav = IPALAV;}
	if(tyyppi == Julkinen::TPALA){pala = TPALAP; palav = TPALAV;}
	if(tyyppi == Julkinen::LPALA){pala = LPALAP; palav = LPALAV;}
	// Lisätään bittikarttaan 1. rotaation reunat
	_irtopala.vaakateksti( 0, 0, pala.yla );
	_irtopala.pystyteksti( 3, 1, pala.oikea );
	_irtopala.vaakateksti( 0, 3, pala.ala );
	_irtopala.pystyteksti( 0, 1, pala.vasen );
   
	// 2. rotaation reunat
	_irtopala.vaakateksti( 6, 0, palav.vasen );
	_irtopala.pystyteksti( 8, 0, palav.yla );
	_irtopala.vaakateksti( 6, 3, palav.oikea );
	_irtopala.pystyteksti( 5, 0, palav.ala );
   
	// 3. rotaation reunat
	_irtopala.vaakateksti( 10, 0, pala.ala );
	_irtopala.pystyteksti( 13, 1, pala.vasen );
	_irtopala.vaakateksti( 10, 3, pala.yla );
	_irtopala.pystyteksti( 10, 1, pala.oikea );
   
	// 4. rotaation reunat
	_irtopala.vaakateksti( 16, 0, palav.oikea );   
	_irtopala.pystyteksti( 18, 0, palav.ala );
	_irtopala.vaakateksti( 16, 3, palav.vasen );
	_irtopala.pystyteksti( 15, 0, palav.yla );

	_irtopala.suorakaide( 1, 1, 2, 2, '.' );
	_irtopala.suorakaide( 6, 1, 2, 2, '.' );
	_irtopala.suorakaide( 11, 1, 2, 2, '.' );
	_irtopala.suorakaide( 16, 1, 2, 2, '.' );

}

void Naytto::lisaaEsineIrtopalaan(char merkki)
{
	for( unsigned int i = 0; i < 4; ++i )
	{
		_irtopala.vaakaviiva( (1+i*5), 1, 2, '.' );
		_irtopala.vaakaviiva( (1+i*5), 2, 1, '.' );
		_irtopala.vaakaviiva( (2+i*5), 2, 1, merkki);
	}
}

using namespace Julkinen;
void Naytto::tarkistaOnkoRakennustila()
{
	ESIEHTO(!onTulostustilassa());
}
