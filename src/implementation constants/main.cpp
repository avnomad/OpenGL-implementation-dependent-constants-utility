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
#include <Winspool.h>
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
	cout << setw(14) << ' ' << "Copyright (C) 2010-2012  Vaptistis Anogeianakis\n\n";
	cout << setw(14) << ' ' << "This program comes with ABSOLUTELY NO WARRANTY.\n";
	cout << setw(14) << ' ' << "This is free software, and you are welcome to\n";
	cout << setw(14) << ' ' << "redistribute it under certain conditions.\n";
	cout << setw(14) << ' ' << "See license.txt for details.\n\n\n\n";


	// window OpenGL context
	cout << setw(18) << ' ' << ">>>>>>>> Window OpenGL context <<<<<<<<\n";

	HWND window = CreateWindow(_T("OpenGLConstantsClass"),nullptr,WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN
									|WS_CLIPSIBLINGS,320,120,640,480,nullptr,nullptr,GetModuleHandle(nullptr),nullptr);
	HDC gdiContext = GetDC(window);
	createContextAndPrint(gdiContext);

	// memory OpenGL context
	cout << setw(18) << ' ' << ">>>>>>>> Memory OpenGL context <<<<<<<<\n";

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

	// printer OpenGL contexts.
	unsigned long requiredSize;
	unsigned long nPrinters;
	EnumPrinters(PRINTER_ENUM_LOCAL,nullptr,4,nullptr,0,&requiredSize,&nPrinters);	// get required size.
	BYTE *printers = new BYTE[requiredSize];
		EnumPrinters(PRINTER_ENUM_LOCAL,nullptr,4,printers,requiredSize,&requiredSize,&nPrinters);	// get printers list.
		for(unsigned long i = 0 ; i < nPrinters ; ++i)
		{
			cout << setw(9) << ' ' << ">>>>>>>> OpenGL context for " << ((PRINTER_INFO_4*)printers)[i].pPrinterName << " <<<<<<<<\n";
			gdiContext = CreateDC(nullptr,((PRINTER_INFO_4*)printers)[i].pPrinterName,nullptr,nullptr);
				createContextAndPrint(gdiContext);
			DeleteDC(gdiContext);
		} // end for
	delete[] printers;

	system(PAUSE);
	return 0;
} // end function main


void createContextAndPrint(HDC gdiContext)
{
	PIXELFORMATDESCRIPTOR pixelFormatDescription = {0};
		pixelFormatDescription.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pixelFormatDescription.nVersion = 1;
		pixelFormatDescription.dwFlags = PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER_DONTCARE|PFD_STEREO_DONTCARE|PFD_DRAW_TO_BITMAP;
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
		GLenum errorCode = glewInit();
		if(errorCode != GLEW_OK)
		{
			cerr << "\n\nCall to glewInit failed with error message: " << glewGetErrorString(errorCode) << endl;
			cerr << "Current context not supported? Skipping to next context...\n\n\n" << endl;
		}
		else
			printConstants();
	wglDeleteContext(glContext);
} // end function createContextAndPrint
