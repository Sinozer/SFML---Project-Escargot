#pragma once
namespace Snail
{
	class PhysicBody;
	typedef std::shared_ptr<PhysicBody> PhysicBodyRef;
	class PhysicBody
	{
	private:
		sf::RectangleShape m_body;

		bool m_canCollide;
		bool m_canGravitate;

#pragma region Constructors
		PhysicBody(sf::Vector2f position, float restitution,
			bool isStatic, bool canCollide, bool canGravitate, sf::Vector2f size);

		PhysicBody(sf::Vector2f position, float restitution,
			bool isStatic, sf::Vector2f size, sf::Texture& texture, bool canCollide, bool canGravitate);

		PhysicBody(sf::Vector2f position, float restitution,
			bool isStatic, sf::Vector2f size, sf::Texture& texture, sf::Vector2i texturePosition, bool canCollide, bool canGravitate);
#pragma endregion

		void m_Move();
	public:

		uint8_t Masks;
		uint8_t CollideMasks;
		uint8_t TriggerMasks;

		bool IsTriggered;

		sf::Vector2f Velocity;

		bool IsOnGround;
		
		float Restitution;
		
		bool IsStatic;

#pragma region Constructors
		static PhysicBody* CreateBoxBody(sf::Vector2f size, sf::Vector2f position, float restitution, bool isStatic, bool canCollide = true, bool canGravitate = true);

		static PhysicBody* CreateBoxBody(sf::Vector2f size, sf::Vector2f position, float restitution, bool isStatic, sf::Texture& texture, bool canCollide = true, bool canGravitate = true);
		
		static PhysicBody* CreateBoxBody(sf::Vector2f size, sf::Vector2f position, float restitution, bool isStatic, sf::Texture& texture, sf::Vector2i texturePosition, bool canCollide = true, bool canGravitate = true);
#pragma endregion

		void Rotate(float angle);

		sf::Vector2f GetScale();

		void Scale(sf::Vector2f scale);

		void SetPosition(sf::Vector2f position);

		sf::Vector2f GetPosition();

		void Move(sf::Vector2f step);

		void AddVelocity(sf::Vector2f step, sf::Vector2f clamp);

		sf::Vector2f GetHalfSize();

		bool CheckCollision(PhysicBodyRef other, sf::Vector2f& direction);

		void OnCollision(sf::Vector2f direction);

		void Update();

		void Draw(sf::RenderWindow& window);
	};
}