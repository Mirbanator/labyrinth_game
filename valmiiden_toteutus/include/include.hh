#ifndef INCLUDE_HH
#define INCLUDE_HH

/**
 *	\version $Id: include.hh 1802 2011-02-07 09:17:58Z salone58 $
 *	\file include.hh
 *	\brief p‰‰ohjelman kirjastojen liitt‰mistiedosto
 *	\author ©2011 Eero Salonen <eero.j.salonen@tut.fi>
 */

//Julkinen rajapinta
#include "../../koordinaatti.hh"
#include "../../pelirajapinta.hh"
#include "../../nayttorajapinta.hh"
#include "../../pelitehdas.hh"
#include "../../vaittama.hh"
#include "../../alustusvirhe.hh"
#include "../../komentovirhe.hh"
#include "../../logiikkavirhe.hh"
#include "../../toteuttamaton_virhe.hh"
#include "../../virhe.hh"
#include "../../debug.hh"

//Toteutus
#include "komentotulkki.hh"
#include "rakentaja.hh"


//STL Kirjastot.
/**
 *	Jos k‰‰nt‰j‰ on GNUG pohjainen esim. gcc tai tutg++ k‰ytet‰‰n tr1/memory
 *	kirjastoa.
 */
#	if defined(__GNUG__)

#include <tr1/memory>
/**
 *	Muussa tapauksessa k‰ytet‰‰n memory kirjastoa ja toivotaan ett‰ k‰‰nt‰j‰st‰
 *	lˆytyy alustava tuki uudelle C++ standardille.
 *	Toimii esim. Visual Studio 2010.
 */
#	else
#include <memory>
#	endif
#include <iostream>
#include <string>
#include <deque>
#include <cstdlib>


#endif //INCLUDE_HH
