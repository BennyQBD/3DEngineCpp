#include "physicsObject.h"
#include <iostream>
#include <cassert>

void PhysicsObject::Integrate(float delta)
{
	m_position += m_velocity * delta;
}

void PhysicsObject::Test()
{
	PhysicsObject test(Vector3f(0.0f, 1.0f, 0.0f), Vector3f(1.0f, 2.0f, 3.0f));

	test.Integrate(20.0f);

	Vector3f testPos = test.GetPosition();
	Vector3f testVel = test.GetVelocity();

	assert(testPos.GetX() == 20.0f);
	assert(testPos.GetY() == 41.0f);
	assert(testPos.GetZ() == 60.0f);

	assert(testVel.GetX() == 1.0f);
	assert(testVel.GetY() == 2.0f);
	assert(testVel.GetZ() == 3.0f);

//	
//	std::cout << "("<<testPos.GetX()<<", "<<testPos.GetY()<<", "
//		<<testPos.GetZ()<<")"<<std::endl;
//	std::cout << "("<<testVel.GetX()<<", "<<testVel.GetY()<<", "
//		<<testVel.GetZ()<<")"<<std::endl;
}
