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

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <SDL2/SDL.h>
#include <string>
#include "../core/input.h"

class Window
{
public:
	Window(int width, int height, const std::string& title);
	virtual ~Window();
	
	void Update();
	void SwapBuffers();
	void BindAsRenderTarget() const;

	inline bool IsCloseRequested()          const { return m_isCloseRequested; }
	inline int GetWidth()                   const { return m_width; }
	inline int GetHeight()                  const { return m_height; }
	inline float GetAspect()                const { return (float)m_width/(float)m_height; }
	inline const std::string& GetTitle()    const { return m_title; }
	inline Vector2f GetCenter()             const { return Vector2f((float)m_width/2.0f, (float)m_height/2.0f); }
	inline SDL_Window* GetSDLWindow()             { return m_window; }
	inline const Input& GetInput()          const { return m_input; }

	void SetFullScreen(bool value);
protected:
private:
	int           m_width;
	int           m_height;
	std::string   m_title;
	SDL_Window*   m_window;
	SDL_GLContext m_glContext;
	Input         m_input;
	bool          m_isCloseRequested;
	
	Window(const Window& other) : m_input(this) {}
	void operator=(const Window& other) {}
};

#endif
