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

#ifndef __3DENGINE_H_INCLUDED
#define __3DENGINE_H_INCLUDED

//This header is just a convinient way to include all necessary files to use the engine.

#include "mesh.h"
#include "shader.h"
#include "transform.h"
#include "camera.h"
#include "lighting.h"
#include "entity.h"
#include "meshRenderer.h"
#include "window.h"
#include "coreEngine.h"
#include "game.h"

//SDL2 defines a main macro, which can prevent certain compilers from finding the main function.
#undef main

#endif // 3DENGINE_H_INCLUDED
