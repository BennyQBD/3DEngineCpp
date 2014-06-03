#include "freeMove.h"
	
void FreeMove::ProcessInput(const Input& input, float delta)
{
	float movAmt = m_speed * delta;

	if(input.GetKey(m_forwardKey))
		Move(GetTransform()->GetRot()->GetForward(), movAmt);
	if(input.GetKey(m_backKey))
		Move(GetTransform()->GetRot()->GetBack(), movAmt);
	if(input.GetKey(m_leftKey))
		Move(GetTransform()->GetRot()->GetLeft(), movAmt);
	if(input.GetKey(m_rightKey))
		Move(GetTransform()->GetRot()->GetRight(), movAmt);
}

void FreeMove::Move(const Vector3f& direction, float amt)
{
	GetTransform()->SetPos(*GetTransform()->GetPos() + (direction * amt));
}
