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

#pragma warning(disable : 4996)	// disable deprecation warnings for Visual Studio.

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

#include <cstring>
using std::strcpy;
using std::strtok;

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "print constants.h"

#define escape(A) #A
#define W 49
#define GL_GPU_MEM_INFO_TOTAL_AVAILABLE_MEM_NVX 0x9048
#define GL_GPU_MEM_INFO_CURRENT_AVAILABLE_MEM_NVX 0x9049

void printConstants()
{
	// declarations
	const GLubyte *sval;
	GLint ival;
	GLfloat fval;
	GLboolean bval;
	GLint iv[2];
	GLfloat fv[2];
	GLint nTextureFormats;
	GLint nExtensions;
	GLint majorVersion = 0;
	char *extensions;
	char *e;

	glGetIntegerv(GL_NUM_EXTENSIONS,&nExtensions);
	glGetIntegerv(GL_MAJOR_VERSION,&majorVersion);
	glGetIntegerv(GL_NUM_COMPRESSED_TEXTURE_FORMATS,&nTextureFormats);
	cout << left;

	/* %--% */	// code will be inserted here!

	cout << setw(W) << escape(GL_EXTENSIONS) ":" << '\n';
	if(majorVersion >= 3)
		for(int c = 0 ; c < nExtensions ; ++c)
			cout << setw(W-15) << ' ' << glGetStringi(GL_EXTENSIONS,c) << '\n';
	else
	{
		extensions = new char[strlen((const char *)glGetString(GL_EXTENSIONS))+1];
		strcpy(extensions,(const char *)glGetString(GL_EXTENSIONS));
		if(e = strtok(extensions," "))
			cout << setw(W-15) << ' ' << e << '\n';
		while(e = strtok(NULL," "))
			cout << setw(W-15) << ' ' << e << '\n';
		delete[] extensions;
	} // end else

	/* %--% */	// code will be inserted here!

	cout << setw(W) << escape(GLU_EXTENSIONS) ":" << '\n';
	extensions = new char[strlen((const char *)gluGetString(GLU_EXTENSIONS))+1];
	strcpy(extensions,(const char *)gluGetString(GLU_EXTENSIONS));
	if(e = strtok(extensions," "))
		cout << setw(W-15) << ' ' << e << '\n';
	else
		cout << setw(W-15) << ' ' << "-\n";
	while(e = strtok(NULL," "))
		cout << setw(W-15) << ' ' << e << '\n';
	delete[] extensions;

	/* %--% */	// code will be inserted here!

	cout << setw(W) << escape(GL_COMPRESSED_TEXTURE_FORMATS) << setw(15) << '-';
	if(nTextureFormats == 0)
		cout << "-\n";
	else
	{
		GLint *textureFormats = new GLint[nTextureFormats];
		glGetIntegerv(GL_COMPRESSED_TEXTURE_FORMATS,textureFormats);
		cout << textureFormats[0] << '\n';
		for(int c = 1 ; c < nTextureFormats ; ++c)
			cout << setw(W+15) << ' ' << textureFormats[c] << '\n';
		delete[] textureFormats;
	} // end else

	/* %--% */	// code will be inserted here!

	cout << right << '\n' << setw(W) << "--END--\n\n\n";
} // end function printConstants