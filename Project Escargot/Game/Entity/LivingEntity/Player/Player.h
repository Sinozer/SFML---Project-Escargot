#pragma once
#include "Game/Entity/LivingEntity/LivingEntity.h"
#include "Game/Entity/Weapon/WeaponManager.h"


namespace Snail
{
	class Player : LivingEntity
	{
	private:
		GameDataRef m_data;
		WeaponManager* m_weaponManager;

		
		void m_InitPhysicBody(PhysicBodyManager& pbm, sf::Vector2f position);
		void m_InitWeaponManager(PhysicBodyManager& pbm);
		void m_ChangeDirection(Direction direction = NONE);
		void m_UpdateWeaponManager(float dt);
		void m_DrawWeaponManager();
	public:
		int bulletCount;
		
		/**
		 * \brief Constructor.
		 * 
		 * \param data
		 */
		Player(GameDataRef data);
		~Player();

		void Init(PhysicBodyManager &pbm, sf::Vector2f position = sf::Vector2f(150, 150));

		void HandleInput();

		void Update(float dt);

		void Draw();

		PhysicBodyRef GetPhysicBodyRef();
	};
}