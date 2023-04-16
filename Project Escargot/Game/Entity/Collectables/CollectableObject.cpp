#include "stdafx.h"
#include "CollectableObject.h"

namespace Snail {

	CollectableObject::CollectableObject() {
		this->m_type = Life();
		this->m_value = 15;
	}

	CollectableObject::~CollectableObject()
	{
	}

	void CollectableObject::Init(PhysicBodyManager& pbm)
	{
		m_InitPhysicBody(pbm);
	}

	void CollectableObject::Update(float dt )
	{

		
	}

	void CollectableObject::Draw()
	{
		//m_collectablePhysicBody->Draw();
	}

	void CollectableObject::m_InitPhysicBody(PhysicBodyManager& pbm)
	{
		m_collectablePhysicBody = PhysicBodyRef(PhysicBody::CreateBoxBody(
			sf::Vector2f(16.f, 16.f), sf::Vector2f(170, 170), 0.f, true,true, false
		));
		pbm.AddPhysicBody("Collectible", m_collectablePhysicBody);
	}

	void CollectableObject::m_CollectObject(Player livingEntity)
	{
		//livingEntity.UpdateLifeEntity(this->m_value, true);
		std::cout << "life up \n";
		
	}

	void CollectableObject::m_SetType(Type type)
	{
		m_type = type;
	}
	void CollectableObject::m_SetValue(float value)
	{
		m_value = value;
	}

	PhysicBodyRef CollectableObject::GetPhysicBodyRefCollectable()
	{
		return this->m_collectablePhysicBody;
	}


}