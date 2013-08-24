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

#define ZERO_MEM(a) memset(a,0,sizeof(a))
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))
#define SAFE_DELETE(p) if(p) {delete p; p = NULL;}
#define INVALID_VALUE 0xFFFFFFFF

#define ToRadian(x) (float)(((x) * 3.1415926536f / 180.0f))
#define ToDegree(x) (float)(((x) * 180.0f / 3.1415926536f))

namespace Util
{
	void sleep(int milliseconds);
};

#endif