#include "PlayerActionStatus.h"

PlayerActionStatus::PlayerActionStatus():
mPlayerMoved(false), mPlayerPushed(false)
{}
PlayerActionStatus::~PlayerActionStatus(){
}

bool PlayerActionStatus::isMoved(){
	return mPlayerMoved;
}
bool PlayerActionStatus::isPushed(){
	return mPlayerPushed;
}
void PlayerActionStatus::setMoved(){
	mPlayerMoved = true;
}
void PlayerActionStatus::setPushed(){
	mPlayerPushed = true;
}
bool PlayerActionStatus::actionsDone(){
	if (mPlayerMoved && mPlayerPushed)
		return true;

	return false;
}
void PlayerActionStatus::reset(){
	mPlayerMoved = false;
	mPlayerPushed = false;
}