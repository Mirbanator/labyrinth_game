#include "pelitehdas.hh"
#include <iostream>

std::unique_ptr<Game> Julkinen::luoPeli(){
	return std::unique_ptr<Game>(new Game());
}