#pragma once
#include "../Entity.h"
namespace Snail
{
	/**
	 * \TODO Make it virtual
	 */
	class Weapon : public Entity
	{
	protected:
		std::string m_name;

		PhysicBodyRef m_physiBodyRef;

		sf::Vector2f m_wantedWosition;

		BulletManager m_bulletManager;

		float m_offset;


	public:
		virtual void Use() = 0;

		virtual void Draw() = 0;

		virtual void Update(float dt) = 0;
	};
}

