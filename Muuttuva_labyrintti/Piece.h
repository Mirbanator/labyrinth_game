#pragma once
#include "pelirajapinta.hh"
class Piece
{
public:
	Piece(Julkinen::Koordinaatti coord, Julkinen::PalaTyyppi type, unsigned int rotation);
	Piece(const Piece &org);
	~Piece();

	Piece& operator=(const Piece &);

	Julkinen::Koordinaatti getLocation() const;
	Julkinen::PalaTyyppi getType() const;
	unsigned int getRotation() const;
	Julkinen::ErikoispalaTyyppi getSpecialType() const;
	Julkinen::Koordinaatti getTarget() const;
	char getItem() const;

	void setLocation(Julkinen::Koordinaatti coord);
	void setType(Julkinen::PalaTyyppi type);
	void setRotation(unsigned int rotation);
	void setSpecialType(Julkinen::ErikoispalaTyyppi specialType);
	void setTarget(Julkinen::Koordinaatti coord);
	void setItem(char item);
	void removeItem();

private:
	Julkinen::Koordinaatti mLocation;
	Julkinen::PalaTyyppi mType;
	unsigned int mRotation;
	Julkinen::ErikoispalaTyyppi mSpecialType;
	Julkinen::Koordinaatti mTarget;
	char mItem;
};

