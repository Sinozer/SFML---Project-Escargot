#pragma once
#include "../Entity.h"
namespace Snail
{
	class Ennemy : Entity
	{
	private:
		GameDataRef m_data;

		float m_speed;

		void m_InitPhysicBody();

		Player& m_target;
	public:
		PhysicBodyRef m_physicBodyRef;

		/**
		 * \brief Constructor.
		 *
		 * \param data
		 */
		Ennemy(GameDataRef data, Player& target);

		void Init();

		void HandleInput();

		void Update(float dt);

		void Draw();
	};
}