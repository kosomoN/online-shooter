#pragma once
#include <string>
#include <vector>

class CSprite;
class CAnimation;

enum EState
{
	MOVE, IDLE = 2, SHOOT = 4
};

class CPlayerAnimController
{
public:
	CPlayerAnimController();
	~CPlayerAnimController();

	void init(std::vector<std::string>& files, CSprite* body, CSprite* feet);
	void setState(EState state);
	std::vector<CAnimation*> m_animData;
private:
	CSprite* m_pBody;
	CSprite* m_pFeet;
	EState m_lastState = MOVE;

};

