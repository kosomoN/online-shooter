#pragma once
#include <string>
#include <vector>

class CSprite;
class CAnimation;

enum EState
{
	MOVE, IDLE, SHOOT
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
private:
	std::vector<SAnimData> m_animData;
	CSprite* m_pBody;
	CSprite* m_pFeet;
	CSprite* m_pShoot;

};

