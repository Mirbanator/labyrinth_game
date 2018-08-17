/**
 *	\version $Id: pelirajapinta.hh 1795 2011-02-01 07:31:30Z salone58 $
 *  \file rakentaja.cc
 *  \brief Rakentaa-luokan toteutus. ($Revision: 1795 $)
 *  \author ©2010 Eero Salonen <eero.j.salonen@tut.fi>
 */

#include "include/rakentaja.hh"
#include "include/Alustaja.hh"
#include "include/komentotulkki.hh"
#include "../vaittama.hh"
#include "../alustusvirhe.hh"
#include "../toteuttamaton_virhe.hh"
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "../debug.hh"
#include <cctype>

static const std::string SIEMENLUKU = "SIEMENLUKU";
static const std::string PELAAJIA = "PELAAJIA";
static const std::string IHMINEN = "IHMINEN";
static const std::string TIETOKONE = "TIETOKONE";
static const std::string RAAKILE = "RAAKILE";

Rakentaja::Rakentaja(std::shared_ptr<Julkinen::Pelirajapinta> peli,
	Julkinen::Koordinaatti const& pelialueenkoko,
	std::string tiedosto,
	std::shared_ptr<Naytto> naytto):
	_peli(peli), _naytto(naytto), _koko(pelialueenkoko), _tiedosto(tiedosto),
	_pelaajienmaara(2), _siemenluku(0), _pelaajialisatty(0)
{

}

Rakentaja::~Rakentaja()
{

}

void Rakentaja::lueTiedosto()
{
	std::ifstream tiedostovirta(_tiedosto.c_str());
	if(!tiedostovirta)
	{
		throw Julkinen::Alustusvirhe("Annettua alustus tiedostoa ei lˆytynyt");
	}

	std::string komento = "";

	while(tiedostovirta)
	{
		tiedostovirta >> komento;
		int (*pf)(int)=std::toupper;
		std::transform(komento.begin(), komento.end(), komento.begin(), pf);
		std::string temp;
		tiedostovirta >> temp;
		if(komento == SIEMENLUKU)
		{
			_siemenluku = str2int(temp);
			komento = "";
		}
		else if(komento == PELAAJIA)
		{
			_pelaajienmaara = static_cast<unsigned int>(str2int(temp));
			komento = "";
		}
		else if(komento == IHMINEN)
		{
                        char merkki = int2char(static_cast<int>(_pelaajialisatty));
			PelaajaTiedot tiedot = {Julkinen::IHMINEN,
                          merkki+static_cast<std::string>(" ")+temp, merkki, luoSijainti() };
			_pelaajat.push_back(tiedot);
			komento = "";
			_pelaajialisatty++;
		}
		else if(komento == TIETOKONE)
		{
                        char merkki = int2char(static_cast<int>(_pelaajialisatty));
			PelaajaTiedot tiedot = {Julkinen::TIETOKONE,
                          merkki+static_cast<std::string>(" ")+temp, merkki, luoSijainti() };
			_pelaajat.push_back(tiedot);
			komento = "";
			_pelaajialisatty++;
		}
		else if (komento == RAAKILE)
		{
			Komentotulkki::asetaRaakileTilaan();
		}

	}
	
	if(_pelaajienmaara != _pelaajialisatty)
	{
		throw Julkinen::Alustusvirhe("Peliin lis‰ttyjen pelaajien m‰‰r‰ on eri kuin ilmoitettu pelaajien m‰‰r‰");
	}
	if(_siemenluku == 0)
	{
		_alustaja = std::shared_ptr<Alustaja>(new Alustaja(_pelaajienmaara));
	}
	else
	{
		_alustaja = std::shared_ptr<Alustaja>(new Alustaja(_pelaajienmaara,
			static_cast<unsigned long>(_siemenluku)));
	}
}

void Rakentaja::lisaaPalat()
{
   ESIEHTO(_alustaja != 0);
   _peli->maaritaPelialueenKoko(_koko);
   for(unsigned int y = 1; y <= _koko.haeYkoordinaatti(); y++)
   {
      for(unsigned int x = 1; x <= _koko.haeXkoordinaatti(); x++)
      {
         Julkinen::Koordinaatti koordinaatti(x, y);
         
         _peli->lisaaPala(maaritaPalaTyyppi(x,y),
                          _alustaja->annaKoordinaatinRotaatio(x, y), koordinaatti);
      }
   }
   if (Komentotulkki::onkoRaakileTilassa())
   {
      return;
   }
   
   
   for(unsigned int i = 1; i <= _koko.haeYkoordinaatti(); i++ )
   {
      for(unsigned int j = 1; j <= _koko.haeXkoordinaatti(); j++)
      {
         Julkinen::ErikoispalaTyyppi tyyppi = Julkinen::NORMAALI;
         Julkinen::Koordinaatti kohde = Julkinen::Koordinaatti();
         char erikoispala = _alustaja->annaKoordinaatinErikoispala(j, i);
         if(erikoispala == 'T' || erikoispala == 'K' || erikoispala =='S')
         {   
            if(erikoispala == 'T')
            {
               tyyppi = Julkinen::TELEPORTTI;
               kohde = _alustaja->annaSeuraavaKohde();
            }
            
            else if(erikoispala == 'K')
            {
               tyyppi = Julkinen::KIROTTU; 
            }
            
            else if(erikoispala == 'S')
            {
               tyyppi = Julkinen::SIUNATTU; 
            }
            
            erikoispala = '*';
         }
         
         Julkinen::Koordinaatti sijainti(j,i);        
         try
         {
            _peli->asetaPalanTyyppi(tyyppi, sijainti, kohde);
         }
         catch(Julkinen::ToteuttamatonVirhe virhe)
         {
            std::cerr << virhe << std::endl;
            _peli->asetaPalanTyyppi(Julkinen::NORMAALI, sijainti, kohde);
            
         }
         
      }
         
   }
      
}
   

void Rakentaja::lisaaIrtopala()
{

	Julkinen::Koordinaatti koordinaatti;

	_peli->lisaaPala(maaritaIrtoPalanTyyppi(), 1, koordinaatti);


}

void Rakentaja::luoPelaajat()
{
	unsigned int ihmispelaajia = 0;
	for(unsigned int i = 0; i < ihmispelaajia; i++)
	{
		PelaajaTiedot tiedot;
		tiedot._tyyppi = Julkinen::IHMINEN;
		tiedot._nimi = maaritaNimi();
		tiedot._merkki = int2char(static_cast<int>(i) + 1);
		tiedot._sijainti = luoSijainti();
		_pelaajat.push_back(tiedot);
	}

	unsigned int tietokonepelaajia = 0;
	for(unsigned int i = 0; i < tietokonepelaajia; i++)
	{
		PelaajaTiedot tiedot;
		std::string nimi = "Tietokone";
		nimi += int2char(static_cast<int>(i) + 1);
		tiedot._tyyppi = Julkinen::TIETOKONE;
		tiedot._nimi = nimi;
		tiedot._merkki = int2char(static_cast<int>(i) + 1 + static_cast<int>(ihmispelaajia));
		tiedot._sijainti = luoSijainti();
		_pelaajat.push_back(tiedot);
	}


}

void Rakentaja::lisaaPelaajat()
{
	for(unsigned int i = 0; i < _pelaajat.size(); i++)
	{
		_peli->lisaaPelaaja(_pelaajat[i]._tyyppi,
			_pelaajat[i]._nimi,
			_pelaajat[i]._merkki,
			_pelaajat[i]._sijainti);

	}


}

void Rakentaja::lisaaEsineet()
{
    if (Komentotulkki::onkoRaakileTilassa()) { return; }
  
	for(unsigned int i = 1; i <= _koko.haeYkoordinaatti(); i++ )
	{
		for(unsigned int j = 1; j <= _koko.haeXkoordinaatti(); j++)
		{
			
			char esine = _alustaja->annaKoordinaatinEsine(j, i);
			
			Julkinen::Koordinaatti sijainti(j,i);
			std::string pelaaja = "";
			for(unsigned int p = 0; p < _pelaajienmaara; p++)
			{
				std::vector<char> esineet = _alustaja->annaPelaajanEsinelista(p);
				for(unsigned int k = 0; k < esineet.size(); k++)
				{
					if(esineet[k] == esine){ pelaaja = _pelaajat[p]._nimi; }
				}

			}
			if(esine != 'x')
			{
				_peli->lisaaEsine(esine, sijainti, pelaaja);
			}


		}
	}
}


Julkinen::PalaTyyppi
	Rakentaja::maaritaPalaTyyppi(unsigned int x, unsigned int y) const
{
	return maaritaPalaTyyppi(_alustaja->annaKoordinaatinRuututyyppi( x, y ));
}

Julkinen::PalaTyyppi
	Rakentaja::maaritaIrtoPalanTyyppi() const
{
	return maaritaPalaTyyppi(_alustaja->annaIrtopalanTyyppi());
}

Julkinen::PalaTyyppi
	Rakentaja::maaritaPalaTyyppi(Alustaja::Ruututyyppi alustustyyppi) const
{
	Julkinen::PalaTyyppi tyyppi = Julkinen::IPALA;
	switch(alustustyyppi)
	{
		case Alustaja::I: tyyppi = Julkinen::IPALA;
			break;
		case Alustaja::T: tyyppi = Julkinen::TPALA;
			break;
		case Alustaja::L: tyyppi = Julkinen::LPALA;
	}

	return tyyppi;
}

// Ei tarvita
std::string Rakentaja::maaritaNimi()
{
	std::string nimi = "";
	/// \todo Tiedustelu pelaajan nimen suhteen.
	std::cin >> nimi;
	return nimi;
}

char Rakentaja::int2char(int a)
{
	std::stringstream ss;
	std::string str;
	ss << a;
	str = ss.str();

	return str.at(0);
}

Julkinen::Koordinaatti Rakentaja::luoSijainti()
{
	Julkinen::Koordinaatti sijainti;
	switch(_pelaajialisatty)
	{
	case 0:
		sijainti = Julkinen::Koordinaatti(1 , 1);
		break;
	case 1:
		sijainti = Julkinen::Koordinaatti(1 , _koko.haeYkoordinaatti());
		break;
	case 2:
		sijainti = Julkinen::Koordinaatti(_koko.haeXkoordinaatti() , 1);
		break;
	case 3:
		sijainti = Julkinen::Koordinaatti(_koko.haeXkoordinaatti(),
				_koko.haeYkoordinaatti());
		break;
	}
	return sijainti;
}

int Rakentaja::str2int (std::string const & str)  const
{
	std::stringstream ss(str);
	int n;
	ss >> n;
	return n;
}
