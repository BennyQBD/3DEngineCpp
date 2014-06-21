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

#ifndef UTIL_H
#define UTIL_H

//#include <stdio.h>
//#include <GL/glew.h>
//
//#define GL_CHECK(x) do{
//    x;
//    GLenum glerr = glGetError();
//    if (glerr != GL_NO_ERROR) 
//	{
//        printf("OpenGL error: %d, file: %s, line: %d", glerr, __FILE__, __LINE__);
//    }
//} while (0)

#ifndef WIN32
#include <unistd.h>
#endif

#ifdef WIN32
#define SNPRINTF _snprintf_s
#else
#define SNPRINTF snprintf
#endif

//#define ZERO_MEM(a) memset(a,0,sizeof(a))
//#define SAFE_DELETE(p) if(p) {delete p; p = NULL;}
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
#define INVALID_VALUE 0xFFFFFFFF

#include <vector>
#include <string>

namespace Util
{
	void Sleep(int milliseconds);
	std::vector<std::string> Split(const std::string &s, char delim);
};

#endif
