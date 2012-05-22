//	Copyright (C) 2010-2012 Vaptistis Anogeianakis <el05208@mail.ntua.gr>
/*
 *	This file is part of Implementation-dependent Constants.
 *
 *	Implementation-dependent Constants is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	Implementation-dependent Constants is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with Implementation-dependent Constants.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::clog;
using std::left;
using std::right;

#include <iomanip>
using std::setw;
using std::setprecision;

#include <cstdlib>
using std::system;
using std::exit;

#include <GL/glew.h>

#if defined(__linux) || defined(__unix)
	#define PAUSE "echo 'press enter to continue...' ; read _"
#else
	#define PAUSE "pause"
#endif

#include <windows.h>
#include <tchar.h>

#include "print constants.h"

void createContextAndPrint(HDC gdiContext);

int main(int argc, char **argv)
{
	// fill and register a window class
	WNDCLASS soleWindowClass;
	soleWindowClass.style = CS_HREDRAW|CS_VREDRAW;
	soleWindowClass.lpfnWndProc = DefWindowProc;
	soleWindowClass.cbClsExtra = 0;
	soleWindowClass.cbWndExtra = 0;
	soleWindowClass.hInstance = GetModuleHandle(nullptr);
	soleWindowClass.hIcon = nullptr;	// can be null
	soleWindowClass.hCursor = nullptr;	// can be null
	soleWindowClass.hbrBackground = nullptr;
	soleWindowClass.lpszMenuName = nullptr;
	soleWindowClass.lpszClassName = _T("OpenGLConstantsClass");
	RegisterClass(&soleWindowClass);

	// print copyright notice
	cout << setw(8) << ' ' << "Copyright (C) 2010-2012  Vaptistis Anogeianakis\n\n";
	cout << setw(6) << ' ' << "This program comes with ABSOLUTELY NO WARRANTY.\n";
    cout << setw(6) << ' ' << "This is free software, and you are welcome to\n";
	cout << setw(6) << ' ' << "redistribute it under certain conditions.\n";
	cout << setw(6) << ' ' << "See license.txt for details.\n";


	// window OpenGL context
	cout << setw(4) << ' ' << "Window OpenGL context.";

	HWND window = CreateWindow(_T("OpenGLConstantsClass"),nullptr,WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN
									|WS_CLIPSIBLINGS,320,120,640,480,nullptr,nullptr,GetModuleHandle(nullptr),nullptr);
	HDC gdiContext = GetDC(window);
	createContextAndPrint(gdiContext);

	// memory OpenGL context
	cout << setw(4) << ' ' << "Memory OpenGL context.";

	HBITMAP gdiBitmap =	CreateCompatibleBitmap(gdiContext,2048,2048);
	HDC gdiMemContext = CreateCompatibleDC(gdiContext);
	// device context and window no longed required.
	ReleaseDC(window,gdiContext);
	DestroyWindow(window);
	gdiBitmap = (HBITMAP)SelectObject(gdiMemContext,gdiBitmap);	// select bitmap
	createContextAndPrint(gdiMemContext);
	gdiBitmap = (HBITMAP)SelectObject(gdiMemContext,gdiBitmap);	// restore the default
	DeleteDC(gdiMemContext);
	DeleteObject(gdiBitmap);

	system(PAUSE);
	return 0;
} // end function main


void createContextAndPrint(HDC gdiContext)
{
	PIXELFORMATDESCRIPTOR pixelFormatDescription = {0};
		pixelFormatDescription.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pixelFormatDescription.nVersion = 1;
		pixelFormatDescription.dwFlags = PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER|PFD_STEREO_DONTCARE;
		pixelFormatDescription.iPixelType = PFD_TYPE_RGBA;
		pixelFormatDescription.cColorBits = 128;
		pixelFormatDescription.cAlphaBits = 32;
		pixelFormatDescription.cAccumBits = 128;
		pixelFormatDescription.cDepthBits = 64;
		pixelFormatDescription.cStencilBits = 32;
		pixelFormatDescription.cAuxBuffers = 128;
		pixelFormatDescription.iLayerType = PFD_MAIN_PLANE;
	int pixelFormatIndex;
	HGLRC glContext;

	pixelFormatIndex = ChoosePixelFormat(gdiContext,&pixelFormatDescription);
	if(!SetPixelFormat(gdiContext,pixelFormatIndex,&pixelFormatDescription))
		exit(0);
	glContext = wglCreateContext(gdiContext);
	wglMakeCurrent(gdiContext,glContext);
		glewInit();
		printConstants();
	wglDeleteContext(glContext);
} // end function createContextAndPrint
