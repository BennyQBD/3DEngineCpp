/*
 * Copyright (C) 2014 Benny Bobaganoosh
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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
