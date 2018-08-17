/**
 *	\version $Id: koordinaatti.cc 2735 2013-04-18 11:35:51Z bitti $
 *  \file koordinaatti.cc
 *  \brief Koordinaatti-luokan toteutus. ($Revision: 2735 $)
 *  \author ©2010 Eero Salonen <eero.j.salonen@tut.fi> 
 */

#include "../koordinaatti.hh"
#include "../vaittama.hh"


Julkinen::Koordinaatti::Koordinaatti(unsigned int xkoord, unsigned int ykoord):
				_xkoord(xkoord), _ykoord(ykoord), _irtopala(false){}


Julkinen::Koordinaatti::Koordinaatti(): 
				_xkoord(0), _ykoord(0), _irtopala(true)
{}


Julkinen::Koordinaatti::Koordinaatti(Koordinaatti const& koordinaatti): 
				_xkoord(koordinaatti._xkoord),
				_ykoord(koordinaatti._ykoord), 
				_irtopala(koordinaatti.onkoIrtopala()){}


Julkinen::Koordinaatti::~Koordinaatti(){}


unsigned int Julkinen::Koordinaatti::haeXkoordinaatti() const 
{ 
	ESIEHTO(!onkoIrtopala());
	return _xkoord;
}

unsigned int Julkinen::Koordinaatti::haeYkoordinaatti() const
{
	ESIEHTO(!onkoIrtopala());
	return _ykoord;
}

bool Julkinen::Koordinaatti::onkoIrtopala() const
{ 
	return _irtopala;
}

void Julkinen::Koordinaatti::operator=(Koordinaatti const& koordinaatti)
{
	_irtopala = koordinaatti.onkoIrtopala();
	if(koordinaatti.onkoIrtopala())
	{
		_xkoord = 0;
		_ykoord = 0;
	}
	else
	{
		_xkoord = koordinaatti.haeXkoordinaatti();
		_ykoord = koordinaatti.haeYkoordinaatti();
	}
	
}

bool Julkinen::Koordinaatti::operator==(Koordinaatti const& koordinaatti) const
{
	if(_irtopala && koordinaatti.onkoIrtopala())
	{ return true; }
	if(!koordinaatti.onkoIrtopala() && 
		_xkoord == koordinaatti.haeXkoordinaatti() &&
		_ykoord == koordinaatti.haeYkoordinaatti())
	{
		return true;
	}
	
	return false;	
}

bool Julkinen::Koordinaatti::operator<(Koordinaatti const& koordinaatti) const
{
        if(koordinaatti.onkoIrtopala())
        { return false; }
        else if(_irtopala)
        { return true; }
        else if (_xkoord < koordinaatti.haeXkoordinaatti())
        { return true; }
        else if (_xkoord == koordinaatti.haeXkoordinaatti() &&
                 _ykoord < koordinaatti.haeYkoordinaatti())
        { return true; }
        else
        { return false; }
}
