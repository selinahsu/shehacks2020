#include "CollectComponent.h"

#include "GameEngine/Util/CollisionManager.h"
#include "GameEngine/EntitySystem/Entity.h"

#include <vector>


//using namespace GameEngine;
//
//CollectComponent::CollectComponent()
//{
//
//}
//
//
//CollectComponent::~CollectComponent()
//{
//
//}
//
//
//void CollectComponent::OnAddToWorld()
//{
//	__super::OnAddToWorld();
//}
//
//
//void CollectComponent::OnRemoveFromWorld()
//{
//	__super::OnAddToWorld();
//}
//
//
//void CollectComponent::Update()
//{
//	//For the time being just a simple intersection check that moves the entity out of all potential intersect boxes
//	std::vector<CollidableComponent*>& collidables = CollisionManager::GetInstance()->GetCollidables();
//
//	for (int a = 0; a < collidables.size(); ++a)
//	{
//		CollidableComponent* colComponent = collidables[a];
//		if (colComponent == this)
//			continue;
//
//		AABBRect intersection;
//		AABBRect myBox = GetWorldAABB();
//		AABBRect colideBox = colComponent->GetWorldAABB();
//		if (myBox.intersects(colideBox, intersection))
//		{
//			GetEntity()->OnRemoveFromWorld();
//			/*
//			if (intersection.width < intersection.height)
//			{
//				if (myBox.left < colideBox.left)
//					pos.x -= intersection.width;
//				else
//					pos.x += intersection.width;
//			}
//			else
//			{
//				if (myBox.top < colideBox.top)
//					pos.y -= intersection.height;
//				else
//					pos.y += intersection.height;
//			}*/
//
//			//GetEntity()->SetPos(pos);
//		}
//	}
//}