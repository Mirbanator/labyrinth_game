#pragma once
#include "pelirajapinta.hh"
#include <queue>
class Player
{
public:
	Player(Julkinen::PelaajaTyyppi type, std::string name, char abbr, Julkinen::Koordinaatti location);
	Player(const Player &org);
	~Player();

	Player& operator=(const Player &);

	Julkinen::PelaajaTyyppi getType() const;
	std::string getName() const;
	char getAbbr() const;
	Julkinen::Koordinaatti getLocation() const;
	std::string getLastCommand() const;
	std::string getTargetItems() const;
	std::string getCollectedItems() const;

	void setLocation(Julkinen::Koordinaatti coord);
	void setLastCommand(std::string command);
	
	void addTargetItem(char item);
	void collectItem();
	char nextItem() const;
	bool isWinner() const;

private:
	Julkinen::PelaajaTyyppi mType;
	std::string mName;
	char mAbbr;
	Julkinen::Koordinaatti mLocation;
	std::string mLastCommand;
	std::string mTargetItems;
	std::string mCollectedItems;
};

