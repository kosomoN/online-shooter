#pragma once

class CSprite;

enum EStates
{
	IDLE, ACTIVE
};

class CPlayerState
{
public:
	CPlayerState();
	~CPlayerState();

	void setState(EStates state);
private:

};

