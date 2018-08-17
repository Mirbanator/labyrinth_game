#ifndef JULKINEN_PELITEHDAS_HH
#define JULKINEN_PELITEHDAS_HH
/**
*	\version $Id: pelitehdas.hh 2660 2013-02-15 10:27:37Z bitti $
* 	\file pelitehdas.hh
*	\brief Rajapinta pelin luomiseksi
*	\author ©2010 Eero Salonen <eero.j.salonen@tut.fi>
*
**/

#include "Game.h"
#include <memory>

/// \namespace Julkinen
namespace
Julkinen
{

    /**
     *  \brief Luo instanssi pelirajapinnasta.
     *
     *  Pääohjelma kutsuu tätä funktiota saadakseen itselleen instanssin
     *  oliosta, joka toteuttaa pelirajapinnan.
     *  Funktion toteutus on tehtävä omaan koodiin.
     *
     *  \post Luodun peli-instanssin tuhoamisvastuu siirtyi pääohjelmalle.
     *      Luotu olio on alustustilassa.
     *  \return Dynaamisesti luotu instanssi luokasta, joka toteuttaa
     *      Labyrintti-pelin.
     */
	std::unique_ptr<Game> luoPeli();
}
	
#endif  // JULKINEN_PELITEHDAS_HH
