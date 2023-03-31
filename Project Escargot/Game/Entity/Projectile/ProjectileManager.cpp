#include "stdafx.h"

/**
 *
 * MainState
 * Player
 *
 * WeaponManager
 * Weapon (abstraite)
 * -- Arc
 * -- Famas
 *
 * ProjectileManager
 * Projectile	: Entity
 * {
 * m_physicBody
 *
 * m_velocity
 *
 * }
 * -- Fl�ches
 * -- Balles
 *
 */

namespace Snail
{
	ProjectileManager::ProjectileManager(GameDataRef data, sf::Vector2f shooterCoord, sf::Vector2f mousePositon)
	{
		m_data = data;
		/*Init();*/
	}

	ProjectileManager::~ProjectileManager()
	{
		for (auto& i : m_projectiles)
			delete i;
	}

	void ProjectileManager::Init(PhysicBodyManager& pbm)
	{
		m_InitPhysicBody(pbm);
	}

	void ProjectileManager::m_InitPhysicBody(PhysicBodyManager& pbm)
	{
		m_physicBodyManager = pbm;
	}

	void ProjectileManager::SetProjectile(EProjectile ref)
	{
		m_projectileReference = ref;
	}

	void ProjectileManager::Shoot(sf::Vector2f startingPoint)
	{
		switch (m_projectileReference)
		{
		case Snail::NONE:
			break;
		case Snail::ARROW:
			Arrow* temp = new Arrow(m_data, startingPoint);
			temp->Init(m_physicBodyManager);
			temp->Shoot();
			m_projectiles.push_back(temp);
			
			break;
		}
	}

	void ProjectileManager::Update(float dt)
	{
		for (auto& i : m_projectiles)
			i->Update(dt);
	}

	void ProjectileManager::Draw()
	{
		for (auto& i : m_projectiles)
			i->Draw();
	}
}
