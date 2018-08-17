

/**
 *	\version $Id: komentotulkki.cc 1802 2011-02-07 09:17:58Z salone58 $
 *  \file komentotulkki.cc
 *  \brief Komentotulkki-luokan toteutus. ($Revision: 1802 $)
 *  \author ©2010 Eero Salonen <eero.j.salonen@tut.fi> 
 */

#include "include/komentotulkki.hh"
#include "../pelirajapinta.hh"
#include "../koordinaatti.hh"
#include "../luettelotyypit.hh"
#include "../komentovirhe.hh"
#include "../toimintovirhe.hh"
#include "../toteuttamaton_virhe.hh"
#include "../debug.hh"
#include<iostream>
#include<cstdlib>
#include<string>
#include<vector>
#include<sstream>
#include <algorithm>
#include <cctype>


std::shared_ptr<Komentotulkki> Komentotulkki::uusiKomentotulkki(std::shared_ptr<Naytto> naytto)
{
	std::shared_ptr<Komentotulkki> osoitin(new Komentotulkki(naytto));
	return osoitin;
}

Komentotulkki::~Komentotulkki()
{

}

void Komentotulkki::kaynnistaKomentotulkki(std::shared_ptr<Julkinen::Pelirajapinta> peli)
{
	if(peli != 0)
	{
		_peli = peli;
	}
	do
	{
		try
		{
			if(_edellinen == LIIKU || _edellinen == PAIKALLAAN || _edellinen == AUTOMAATTI)
			{
				if(!_peli->vaihdaVuoro())
				{
					_tila = LOPETUS;
					_naytto->tulostaVoittaja();
					continue;
				}
				_edellinen = TYHJA;
			}
			else if(_peli->haeVuorossa() == Julkinen::TIETOKONE)
			{
				std::cout << std::endl;
				  _peli->komentoLiiku(Julkinen::AUTOMAATTI);
				_edellinen = AUTOMAATTI;
			}
			else
			{
				lueKomento();
                                if (_tila != LOPETUS)
                                {
                                  suoritaKomento();
                                }
			}
		}
		catch(Julkinen::Toimintovirhe virhe)
		{
			std::cout << virhe << std::endl;
			_naytto->vuorossa();
			_edellinen = VIRHE;
			continue;
		}
		catch(Julkinen::Komentovirhe virhe)
		{
			std::cout << virhe << std::endl;
			_naytto->vuorossa();
			_edellinen = VIRHE;
			continue;
		}
		catch(Julkinen::ToteuttamatonVirhe virhe)
		{
			if(!Komentotulkki::onkoRaakileTilassa())
			{	throw;	}
			std::cout << "Ajettiin toteuttamaton komento" << std::endl;

		}
	}
	while(_tila != LOPETUS);

}

Komentotulkki::Komentotulkki(std::shared_ptr<Naytto> naytto): _tila(ALUSTUS), _naytto(naytto), _edellinen(VIRHE)
{
	
}

void Komentotulkki::lueKomento()
{
	_komento.clear();
	std::string rivi("");
	//bool komentolukemati = true;
    // Tarkastellaan ettei syöte lopu kesken
    //while(komentolukemati)
	
	if(getline(std::cin, rivi))
    {
      std::cout << rivi << std::endl;
		
		std::istringstream rivivirta(rivi);
		std::string sana = "";
		
		while(rivivirta >> sana)
		{
			//if(sana != "")
			_komento.push_back(sana);
		}
		//if(sana != "")
			//komentolukemati = false;
    }
    else
    {
      _tila = LOPETUS;
    }
}
		

void Komentotulkki::suoritaKomento()
{
	if(_komento.empty())
	{
		throw Julkinen::Komentovirhe(Julkinen::Komentovirhe::VIRHE_TUNNISTAMATON_KOMENTO);
	}

	Komentotulkki::Komento_tiedot komento = tarkistaKomento(_komento.at(0));

	if(komento.komento == VIRHE)
	{
		throw Julkinen::Komentovirhe(Julkinen::Komentovirhe::VIRHE_TUNNISTAMATON_KOMENTO);
	}

	if(_komento.size() - 1 != komento.parametreja )
	{
		throw Julkinen::Komentovirhe(Julkinen::Komentovirhe::VIRHE_LIIKAA_PARAMETREJA);

	}

	if(komento.komento == TYONNA)
	{
		_peli->komentoTyonna(maaritaReuna(_komento.at(2)), static_cast<unsigned int>(str2int(_komento.at(3))), 
			static_cast<unsigned int>(str2int(_komento.at(1))));
		_edellinen = TYONNA;
	}

	if(komento.komento == LIIKU)
	{
		_peli->komentoLiiku(maaritaSuunta(_komento.at(1)), 
			static_cast<unsigned int>(str2int(_komento.at(2))));
		_edellinen = LIIKU;
		
	}

	if(komento.komento == PAIKALLAAN)
	{
		_peli->komentoLiiku(Julkinen::PAIKALLAAN);
		_edellinen = PAIKALLAAN;
	}

	if(komento.komento == LOPETA)
	{
		_tila = LOPETUS;
	}
}

Komentotulkki::Komento_tiedot Komentotulkki::tarkistaKomento(std::string& syote)
{
	int (*pf)(int)=std::tolower; 
	std::transform(syote.begin(), syote.end(), syote.begin(), pf);

	
	if(syote == "tyonna") { return Komento_tiedot(TYONNA, 3); }
	if(syote == "liiku") { return Komento_tiedot(LIIKU, 2); }
	if(syote == "paikallaan") { return Komento_tiedot(PAIKALLAAN, 0); }
	if(syote == "lopeta") { return Komento_tiedot(LOPETA, 0); }
	
	
	return Komento_tiedot(VIRHE, 0);
}

int Komentotulkki::str2int (std::string const & str) 
{
	std::stringstream ss(str);
	int n;
	ss >> n;
	return n;
}

Julkinen::Reuna Komentotulkki::maaritaReuna(std::string& str)
{
	if(str == "y"){ return Julkinen::YLA; }
	if(str == "a"){ return Julkinen::ALA; }
	if(str == "v"){ return Julkinen::VASEN; }
	if(str == "o"){ return Julkinen::OIKEA; }
	return Julkinen::EIOLE;
}

Julkinen::Suunta Komentotulkki::maaritaSuunta(std::string& str)
{
	if(str == "y"){ return Julkinen::YLOS; }
	if(str == "a"){ return Julkinen::ALAS; }
	if(str == "v"){ return Julkinen::VASEMMALLE; }
	if(str == "o"){ return Julkinen::OIKEALLE; }
	return Julkinen::AUTOMAATTI;
}

void Komentotulkki::asetaRaakileTilaan()
{
	_raakiletila = true;
}

bool Komentotulkki::onkoRaakileTilassa()
{
        return _raakiletila;
}

bool Komentotulkki::_raakiletila = false;
