#include <gl/glew.h>
#include <gl/freeglut.h>
#include <cstdlib>
#include <cstring>

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

#define esquape(A) #A
#define W 49

int main(int argc, char **argv)
{
	// glut initialization
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL | GLUT_ACCUM);
	int windowID = glutCreateWindow("Creating Geometry");

	// glew initialization
	if(glewInit())
	{
		cerr << "Unable to initialize glew. Exiting..." << endl;
		exit(0);
	} // end if

	// declarations
	const GLubyte *sval;
	GLint ival;
	GLfloat fval;
	GLboolean bval;
	GLint iv[2];
	GLfloat fv[2];
	GLint v[3];
	GLint nTextureFormats;
	GLint nExtensions;
	GLint majorVersion;

	// application initialization
	glGetIntegerv(GL_NUM_EXTENSIONS,&nExtensions);
	glGetIntegerv(GL_MAJOR_VERSION,&majorVersion);
	glGetIntegerv(GL_NUM_COMPRESSED_TEXTURE_FORMATS,&nTextureFormats);
	cout << left;

	/* %--% */	// code will be inserted here!

	cout << setw(W) << esquape(GL_EXTENSIONS) ":" << '\n';
	if(majorVersion >= 3)
		for(int c = 0 ; c < nExtensions ; ++c)
			cout << setw(W-15) << ' ' << glGetStringi(GL_EXTENSIONS,c) << '\n';
	else
	{
		char *extensions = new char[strlen((const char *)glGetString(GL_EXTENSIONS))+1];
		char *e;
		strcpy(extensions,(const char *)glGetString(GL_EXTENSIONS));
		if(e = strtok(extensions," "))
			cout << setw(W-15) << ' ' << e << '\n';
		while(e = strtok(NULL," "))
			cout << setw(W-15) << ' ' << e << '\n';
		delete[] extensions;
	} // end else

	/* %--% */	// code will be inserted here!

	GLint *textureFormats = new GLint[nTextureFormats];
	glGetIntegerv(GL_COMPRESSED_TEXTURE_FORMATS,textureFormats);
	cout << setw(W) << esquape(GL_COMPRESSED_TEXTURE_FORMATS) << setw(15) << '-';
	if(nTextureFormats == 0)
		cout << "-\n";
	else
		cout << textureFormats[0] << '\n';
	for(int c = 1 ; c < nTextureFormats ; ++c)
		cout << setw(W+15) << ' ' << textureFormats[c] << '\n';
	delete[] textureFormats;

	/* %--% */	// code will be inserted here!

	// event handling initialization
	glutDestroyWindow(windowID);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,GLUT_ACTION_CONTINUE_EXECUTION);
	glutMainLoop();

	system("PAUSE");
	return 0;
} // end function main