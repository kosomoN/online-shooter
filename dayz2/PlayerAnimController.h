#pragma once
#include <string>
#include <vector>

class CSprite;
class CAnimation;

enum EState
{
	MOVE, IDLE = 2, SHOOT = 4
};

struct SAnimData
{
	unsigned int texId;
	CAnimation* anim;
};


class CPlayerAnimController
{
public:
	CPlayerAnimController();
	~CPlayerAnimController();

	void init(std::vector<std::string>& files, CSprite* body, CSprite* feet, CSprite* shoot);
	void setState(EState state);
	std::vector<SAnimData> m_animData;
private:
	CSprite* m_pBody;
	CSprite* m_pFeet;
	CSprite* m_pShoot;
	EState m_lastState;

};

