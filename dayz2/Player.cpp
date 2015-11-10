#include "Player.h"

CPlayer::CPlayer()
{
	gSys->pEntitySystem->registerEntity(this);
}

void CPlayer::init()
{
}
