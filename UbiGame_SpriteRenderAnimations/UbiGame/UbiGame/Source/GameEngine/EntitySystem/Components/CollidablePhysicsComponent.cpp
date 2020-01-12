#include "CollidablePhysicsComponent.h"

#include "GameEngine/Util/CollisionManager.h"
#include "GameEngine/EntitySystem/Entity.h"
#include "GameEngine/EntitySystem/Components/CollectComponent.h"
#include "GameEngine/EntitySystem/Components/FinishComponent.h"
#include "GameEngine/GameEngineMain.h"

#include <vector>

using namespace GameEngine;

CollidablePhysicsComponent::CollidablePhysicsComponent()
{

}


CollidablePhysicsComponent::~CollidablePhysicsComponent()
{

}


void CollidablePhysicsComponent::OnAddToWorld()
{
	__super::OnAddToWorld();
}


void CollidablePhysicsComponent::OnRemoveFromWorld()
{
	__super::OnAddToWorld();
}


void CollidablePhysicsComponent::Update()
{
	//For the time being just a simple intersection check that moves the entity out of all potential intersect boxes
	std::vector<CollidableComponent*>& collidables = CollisionManager::GetInstance()->GetCollidables();

	for (int a = 0; a < collidables.size(); ++a)
	{
		CollidableComponent* colComponent = collidables[a];
		if (colComponent == this)
			continue;

		AABBRect intersection;
		AABBRect myBox = GetWorldAABB();
		AABBRect colideBox = colComponent->GetWorldAABB();
		if (myBox.intersects(colideBox, intersection))
		{
			sf::Vector2f pos = GetEntity()->GetPos();
			if (intersection.width < intersection.height)
			{
				if (myBox.left < colideBox.left)
					pos.x -= intersection.width;
				else
					pos.x += intersection.width;
			}
			else
			{
				if (myBox.top < colideBox.top)
					pos.y -= intersection.height;
				else
					pos.y += intersection.height;
			}

			GetEntity()->SetPos(pos);

			if (colComponent)
			{
				if (CollectComponent* collectComp = dynamic_cast<CollectComponent*>(colComponent))
				{
					Entity* item = colComponent->GetEntity();
					GameEngine::GameEngineMain::GetInstance()->RemoveEntity(item);
				}

				if (FinishComponent* finishComp = dynamic_cast<FinishComponent*>(colComponent))
				{
					Entity* finish = colComponent->GetEntity();
					GameEngine::GameEngineMain::GetInstance()->GetRenderWindow()->close();
				}
			}

		}
	}
}