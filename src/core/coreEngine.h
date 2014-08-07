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

#ifndef COREENGINE_H
#define COREENGINE_H

#include "../rendering/renderingEngine.h"
#include <string>
class Game;

//This is the central part of the game engine. It's purpose is to manage interaction 
//between the various sub-engines (such as the rendering and physics engines) and the game itself.
class CoreEngine
{
public:
	CoreEngine(double frameRate, Window* window, RenderingEngine* renderingEngine, Game* game);
	
	void Start(); //Starts running the game; contains central game loop.
	void Stop();  //Stops running the game, and disables all subsystems.
	
	inline RenderingEngine* GetRenderingEngine() { return m_renderingEngine; }
protected:
private:
	bool             m_isRunning;       //Whether or not the engine is running
	double           m_frameTime;       //How long, in seconds, one frame should take
	Window*          m_window;          //Used to display the game
	RenderingEngine* m_renderingEngine; //Used to render the game. Stored as pointer so the user can pass in a derived class.
	Game*            m_game;            //The game itself. Stored as pointer so the user can pass in a derived class.
};

#endif // COREENGINE_H
