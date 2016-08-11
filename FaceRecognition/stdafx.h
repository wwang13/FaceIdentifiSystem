#pragma once


#define WIN32_LEAN_AND_MEAN          
#include <windows.h>


#include <string>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include "DuiLib\UIlib.h"
using namespace DuiLib;

#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
using namespace cv;

#ifdef _DEBUG
#   ifdef _UNICODE
#       pragma comment(lib, "DuiLib_ud.lib")
#   else
#       pragma comment(lib, "DuiLib_d.lib")
#   endif
#else
#   ifdef _UNICODE
#       pragma comment(lib, "DuiLib_u.lib")
#   else
#       pragma comment(lib, "DuiLib.lib")
#   endif
#endif
