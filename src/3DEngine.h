#ifndef __3DENGINE_H_INCLUDED
#define __3DENGINE_H_INCLUDED

//This header is just a convinient way to include all necessary files to use the engine.

#include "mesh.h"
#include "shader.h"
#include "transform.h"
#include "camera.h"
#include "lighting.h"
#include "gameObject.h"
#include "meshRenderer.h"
#include "window.h"
#include "coreEngine.h"
#include "game.h"

//SDL2 defines a main macro, which can prevent certain compilers from finding the main function.
#undef main

#endif // 3DENGINE_H_INCLUDED
