#pragma once
#include "Game/Entity/Weapon/Range/Range.h"
#include "Game/Entity/Projectile/list/Arrow.h"


namespace Snail
{
	class Bow : public Range
	{
	private:
		void m_InitPhysicBody(PhysicBodyManager& pbm, sf::Vector2f position);
	public:
		Bow(sf::Vector2f targetPosition);
		~Bow();
		
		void Use();
		
		void Init(PhysicBodyManager& pbm, sf::Vector2f position);

		void Update(float dt);

		void Draw();
	};
}