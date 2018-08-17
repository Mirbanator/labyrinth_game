#include "Player.h"

Player::Player(Julkinen::PelaajaTyyppi type, std::string name, char abbr, Julkinen::Koordinaatti location) :
mType(type), mName(name), mAbbr(abbr), mLocation(location), mCollectedItems(""), mTargetItems("")
{};
Player::Player(const Player &org) :
mType(org.mType), mName(org.mName), mAbbr(org.mAbbr), mLocation(org.mLocation), mLastCommand(org.mLastCommand), mTargetItems(org.mTargetItems), mCollectedItems(org.mCollectedItems)
{
}
Player::~Player()
{
}

Player& Player::operator=(const Player &source)
{
	if (this != &source)
	{
		mType = source.mType;
		mName = source.mName;
		mAbbr = source.mAbbr;
		mLocation = source.mLocation;
		mLastCommand = source.mLastCommand;
		mTargetItems = source.mTargetItems;
		mCollectedItems = source.mCollectedItems;
	}
	return *this;
}

Julkinen::PelaajaTyyppi Player::getType() const{
	return mType;
}
std::string Player::getName() const{
	return mName;
}
char Player::getAbbr() const{
	return mAbbr;
}
Julkinen::Koordinaatti Player::getLocation() const{
	return mLocation;
}
std::string Player::getLastCommand() const{
	return mLastCommand;
}
std::string Player::getTargetItems() const{
	std::string result = mTargetItems;
	result.replace(result.begin() + 1, result.end(), result.size()-1, '*');
	return result;
}
std::string Player::getCollectedItems() const{
	return mCollectedItems;
}

void Player::setLocation(Julkinen::Koordinaatti coord){
	mLocation = coord;
}
void Player::setLastCommand(std::string command){
	mLastCommand = command;
}

void Player::addTargetItem(char item){
	mTargetItems += item;
}
void Player::collectItem(){
	mCollectedItems += mTargetItems.at(0);
	mTargetItems.erase(0, 1);
}
char Player::nextItem() const{
	if (mTargetItems.size() > 0){
		return mTargetItems.at(0);
	}
	return 0;
}
bool Player::isWinner() const{
	if (mTargetItems.size() == 0)
		return true;
	else
		return false;
}