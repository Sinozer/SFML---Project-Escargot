#include "stdafx.h"
#include "Player.h"
#include "Game/Spawner/SpawnerManager.h"
namespace Snail
{
	Player* Player::m_instance = nullptr;

	Player* Player::GetInstance()
	{
		if (m_instance == nullptr)
			m_instance = new Player();

		return m_instance;
	}

	void Player::DestroyInstance()
	{
		if (m_instance != nullptr)
			delete m_instance;
		m_instance = nullptr;
	}

	Player::Player()
	{
		m_speed = 1.25f * PHYSIC_SCALE;
		m_jumpHeight = 1.4f * PHYSIC_SCALE;
		m_clampVelocity = { m_speed, m_jumpHeight };
	}

	Player::~Player()
	{
	}

	void Player::Init(sf::Vector2f position)
	{
		m_InitPhysicBody(position);
		m_InitWeaponManager();
	}

	void Player::m_InitPhysicBody(sf::Vector2f position)
	{
		m_physicBodyRef = PhysicBodyRef(PhysicBody::CreateBoxBody(
			sf::Vector2f(2522.f, 1685.f), position, 0.f, false, AssetManager::GetInstance()->LoadTexture("PLAYER", STATE_GAME_PLAYER_FILEPATH)
		));

		m_physicBodyRef->Masks = MASK_PLAYER;
		m_physicBodyRef->CollideMasks = MASK_MAP | MASK_MAP_OBJECT | MASK_BULLET_ENEMY;
		m_physicBodyRef->TriggerMasks = MASK_ENEMY;

		m_physicBodyRef->Scale(sf::Vector2f(0.015f, 0.015f));

		PhysicBodyManager::GetInstance()->AddPhysicBody("PLAYER", m_physicBodyRef);
	}

	void Player::m_InitWeaponManager()
	{
		m_weaponManager.AddWeapon("BOW");
	}

	void Player::HandleInput()
	{
		m_physicBodyRef->Velocity.x = 0.f;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			m_physicBodyRef->AddVelocity({ -m_speed, 0 }, m_clampVelocity);
			m_ChangeDirection(LEFT);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			m_physicBodyRef->AddVelocity({ m_speed, 0 }, m_clampVelocity);
			m_ChangeDirection(RIGHT);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			m_speed = 2.f * PHYSIC_SCALE;
		else
			m_speed = 1.25f * PHYSIC_SCALE;
		m_clampVelocity.x = m_speed;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_physicBodyRef->IsOnGround)
		{
			m_physicBodyRef->IsOnGround = false;
			m_physicBodyRef->Velocity.y = -sqrtf(2.0f * GAME_GRAVITY * m_jumpHeight);
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_weaponManager.Use();
		}

		if (DEBUG)
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
				m_physicBodyRef->SetPosition({ 150, 150 });
	}

	sf::Vector2f Player::GetLocalPosition()
	{
		return Game::m_data->window.mapPixelToCoords((sf::Vector2i)m_physicBodyRef->GetPosition());
	}

	void Player::m_ChangeDirection(Direction direction)
	{
		m_direction = direction;
	}

	void Player::Update()
	{
		m_UpdateSprite();
		m_UpdateWeaponManager();
		m_UpdateDamageBuffer();

		m_UpdateDamageBuffer();

		if (!m_physicBodyRef->IsTriggered) return;

		if ((m_physicBodyRef->TriggeredMasks & MASK_ENEMY) == MASK_ENEMY)
		{
			int damages = STATE_GAME_BASE_ENEMIES_DAMAGES + STATE_GAME_BASE_ENEMIES_DAMAGES_PER_WAVE * (SpawnerManager::GetInstance()->GetWave() - 1);
			
			m_TakeDamage(damages);
		}

		m_physicBodyRef->IsTriggered = false;
		m_physicBodyRef->TriggeredMasks = MASK_EMPTY;
	}

	void Player::m_UpdateWeaponManager()
	{
		m_weaponManager.Update();

		m_weaponManager.HandlerPos(m_physicBodyRef->GetPosition());
	}

	void Player::Draw()
	{
		m_DrawWeaponManager();
	}

	void Player::m_DrawWeaponManager()
	{
		m_weaponManager.Draw();
	}

	PhysicBodyRef Player::GetPhysicBodyRef()
	{
		return m_physicBodyRef;
	}

	float Player::GetMunitions()
	{
		return m_weaponManager.GetMunitions();
	}

	std::string Player::GetMunitionsString()
	{
		std::string temp = std::to_string(GetMunitions());
		temp = temp.substr(0, temp.find("."));
		return temp;
	}

	float Player::GetMaxMunitions()
	{
		return m_weaponManager.GetMaxMunitions();
	}

	std::string Player::GetMaxMunitionsString()
	{
		std::string temp = std::to_string(GetMaxMunitions());
		temp = temp.substr(0, temp.find("."));
		return temp;
	}

	float Player::GetLoaders()
	{
		return m_weaponManager.GetLoaders();
	}

	std::string Player::GetLoadersString()
	{
		std::string temp = std::to_string(GetLoaders());
		temp = temp.substr(0, temp.find("."));
		return temp;
	}

	std::string Player::GetAllMunitionsString()
	{
		std::string temp = std::to_string(GetLoaders() * GetMaxMunitions());
		temp = temp.substr(0, temp.find("."));
		return temp;
	}

	float Player::GetDamages()
	{
		return m_weaponManager.GetDamages();
	}

	std::string Player::GetDamagesString()
	{
		std::string temp = std::to_string(GetDamages());
		temp = temp.substr(0, temp.find("."));
		return temp;
	}

	unsigned long int Player::GetScore()
	{
		return m_score;
	}

	void Player::AddScore()
	{
		m_score += (unsigned long int)GetDamages()/* ^ waveCount */;
	}
}
