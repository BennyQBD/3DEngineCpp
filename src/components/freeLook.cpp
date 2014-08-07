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

#include "freeLook.h"
#include "../rendering/window.h"

void FreeLook::ProcessInput(const Input& input, float delta)
{
	if(input.GetKey(m_unlockMouseKey))
	{
		input.SetCursor(true);
		m_mouseLocked = false;
	}

	if(m_mouseLocked)
	{
		Vector2f deltaPos = input.GetMousePosition() - m_windowCenter;
		
		bool rotY = deltaPos.GetX() != 0;
		bool rotX = deltaPos.GetY() != 0;
			
		if(rotY)
		{
			GetTransform()->Rotate(Vector3f(0,1,0), ToRadians(deltaPos.GetX() * m_sensitivity));
		}
		if(rotX)
		{
			GetTransform()->Rotate(GetTransform()->GetRot()->GetRight(), ToRadians(deltaPos.GetY() * m_sensitivity));
		}
			
		if(rotY || rotX)
		{
			input.SetMousePosition(m_windowCenter);
		}
	}

	if(input.GetMouseDown(Input::MOUSE_LEFT_BUTTON))
	{
		input.SetCursor(false);
		input.SetMousePosition(m_windowCenter);
		m_mouseLocked = true;
	}
}
