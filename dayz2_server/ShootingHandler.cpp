#include "ShootingHandler.h"

#include "main.h"

#define STEP_LENGTH 5
#define MAX_RAY_STEPS (2000 / STEP_LENGTH)

CShootingHandler::CShootingHandler()
{
}


CShootingHandler::~CShootingHandler()
{
}

void CShootingHandler::fire(Player* pPlayer, float shootingAngle)
{
	//Raycast shot

	//TODO Use barrel position instead
	glm::vec2 rayPos = pPlayer->m_pos;
	glm::vec2 step(cos(shootingAngle), sin(shootingAngle));
	step *= STEP_LENGTH;

	//TODO Add better data structures for entity collsion
	int steps = 0;
	bool hasHit = false;
	while (!hasHit && steps < MAX_RAY_STEPS)
	{
		for (IEntity* ent : gMain->entityList)
		{
			if (ent == pPlayer)
				continue;

			float width = ent->m_width;
			float height = ent->m_height;

			//Bounding box
			glm::vec2 p1 = ent->m_pos;
			glm::vec2 p2 = p1;

			p1.x -= width / 2;
			p1.y -= height / 2;

			p2.x += width / 2;
			p2.y += height / 2;

			if (rayPos.x < p1.x || rayPos.x > p2.x || rayPos.y < p1.y || rayPos.y > p2.y)
				continue;

			ent->hit(pPlayer);
			hasHit = true;
			break;
		}

		rayPos += step;
		steps++;
	}
}
