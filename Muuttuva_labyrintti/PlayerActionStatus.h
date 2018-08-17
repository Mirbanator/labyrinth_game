#pragma once
class PlayerActionStatus
{
public:
	PlayerActionStatus();
	~PlayerActionStatus();
	
	bool isMoved();
	bool isPushed();
	void setMoved();
	void setPushed();
	bool actionsDone();
	void reset();

private:
	bool mPlayerMoved;
	bool mPlayerPushed;
};

