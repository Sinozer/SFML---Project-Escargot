#include "stdafx.h"
#include "Bow.h"


namespace Snail
{

	Bow::Bow(sf::Vector2f targetPosition)
	{
		float angle = std::atan2f(targetPosition.y - 150, targetPosition.x - 150);
		m_targetPosition = { std::cos(angle), std::sin(angle) };
	}

	Bow::~Bow()
	{
	}


	void Bow::Init(PhysicBodyManager &pbm)
	{
		m_InitPhysicBody(pbm);
	}

	void Bow::m_InitPhysicBody(PhysicBodyManager &pbm)
	{
		m_physicBodyRef = PhysicBodyRef(PhysicBody::CreateBoxBody(
			sf::Vector2f(5.f, 5.f), sf::Vector2f(150, 150), 0.f, false
		));

		pbm.AddPhysicBody("BOW", m_physicBodyRef);
	}

	void Bow::Use()
	{
		std::cout << "Bow::Use()" << "\n";
	}

	void Bow::Update(float dt)
	{
		m_physicBodyRef->SetPosition(InputManager::GetInstance()->GetMousePosition());
	}
	void Bow::Draw()
	{
	}
}
