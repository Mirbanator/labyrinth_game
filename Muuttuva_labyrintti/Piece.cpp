#include "Piece.h"


Piece::Piece(Julkinen::Koordinaatti coord, Julkinen::PalaTyyppi type, unsigned int rotation) :
mLocation(coord), mType(type), mRotation(rotation), 
mSpecialType(Julkinen::ErikoispalaTyyppi()), mTarget(Julkinen::Koordinaatti()), mItem('x')
{
}
Piece::Piece(const Piece &org) :
mLocation(org.mLocation), mType(org.mType), mRotation(org.mRotation), 
mSpecialType(org.mSpecialType), mTarget(org.mTarget), mItem(org.mItem)
{
}
Piece::~Piece()
{
}

Piece& Piece::operator=(const Piece &source)
{
	if (this != &source)
	{
		mLocation = source.mLocation;
		mType = source.mType;
		mRotation = source.mRotation;
		mSpecialType = source.mSpecialType;
		mTarget = source.mTarget;
		mItem = source.mItem;
	}
	return *this;
}

Julkinen::Koordinaatti Piece::getLocation() const{
	return mLocation;
}
Julkinen::PalaTyyppi Piece::getType() const{
	return mType;
}
unsigned int Piece::getRotation() const{
	return mRotation;
}
Julkinen::ErikoispalaTyyppi Piece::getSpecialType() const{
	return mSpecialType;
}
Julkinen::Koordinaatti Piece::getTarget() const{
	return mTarget;
}
char Piece::getItem() const{
	return mItem;
}

void Piece::setType(Julkinen::PalaTyyppi type){
	mType = type;
}
void Piece::setRotation(unsigned int rotation){
	mRotation = rotation;
}
void Piece::setLocation(Julkinen::Koordinaatti coord){
	mLocation = coord;
}
void Piece::setSpecialType(Julkinen::ErikoispalaTyyppi specialType){
	mSpecialType = specialType;
}
void Piece::setTarget(Julkinen::Koordinaatti coord){
	mTarget = coord;
}
void Piece::setItem(char item){
	mItem = item;
}
void Piece::removeItem(){
	mItem = 'x';
}