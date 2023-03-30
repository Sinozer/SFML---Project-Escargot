#pragma once
#include "Game/Physic/PhysicBodyManager.h"
#include "Game/Entity/LivingEntity/LivingEntity.h"
#include "Game/Entity/LivingEntity/Player/Player.h"
#include "Game/Entity/LivingEntity/Enemy/Enemy.h"
#include "Game/Entity/Projectile/BulletManager.h"
namespace Snail
{
	/**
	 * \brief Main state used as a menu.
	 */
	class GameState : public State
	{
	private:
		PhysicBodyManager m_physicBodyManager;
		
		Player m_player;

		Enemy m_enemy;

		GameDataRef m_data;

		sf::Clock m_clock;

		BulletManager *m_bullet;

		int m_tempBulletCount;
		int m_timerBulletFire;
		int m_numberBullet;

		void m_InitBackground();
		void m_InitView();
		void m_InitUIManager();

		void m_UpdateView();
		void m_UpdateUIManager(float dt);

		void m_DrawUIManager();
	public:
		GameState(GameDataRef data);
		~GameState() {}

		void Init();
		void AddBullet();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
	};
}