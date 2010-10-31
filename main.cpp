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


	cout << "\n\n" esquape(Version Information) "\n\n";
	cout << setw(W) << "state variable" << setw(15) << "minimum value" << "actual value\n";
	sval = glGetString(GL_VENDOR);
	if(glGetError() == GL_NO_ERROR && sval != NULL)
		cout << setw(W-15) << esquape(GL_VENDOR) ":" << sval << '\n';
	sval = glGetString(GL_RENDERER);
	if(glGetError() == GL_NO_ERROR && sval != NULL)
		cout << setw(W-15) << esquape(GL_RENDERER) ":" << sval << '\n';
	sval = glGetString(GL_VERSION);
	if(glGetError() == GL_NO_ERROR && sval != NULL)
		cout << setw(W-15) << esquape(GL_VERSION) ":" << sval << '\n';
	sval = glGetString(GL_SHADING_LANGUAGE_VERSION);
	if(glGetError() == GL_NO_ERROR && sval != NULL)
		cout << setw(W-15) << esquape(GL_SHADING_LANGUAGE_VERSION) ":" << sval << '\n';
	glGetIntegerv(GL_MAJOR_VERSION,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAJOR_VERSION) << setw(15) << '-' << ival << '\n';
	glGetIntegerv(GL_MINOR_VERSION,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MINOR_VERSION) << setw(15) << '-' << ival << '\n';
	glGetIntegerv(GL_CONTEXT_FLAGS,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_CONTEXT_FLAGS) << setw(15) << '-' << ival << '\n';
	cout << setw(W-15) << esquape(GLU_VERSION) ":" << gluGetString(GLU_VERSION) << '\n';
	cout << setw(W-15) << esquape(GLU_EXTENSIONS) ":" << gluGetString(GLU_EXTENSIONS) << '\n';
	glGetIntegerv(GL_NUM_EXTENSIONS,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_NUM_EXTENSIONS) << setw(15) << '-' << ival << '\n';

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


	cout << "\n\n" esquape(Available Buffers	) "\n\n";
	cout << setw(W) << "state variable" << setw(15) << "minimum value" << "actual value\n";
	glGetBooleanv(GL_RGBA_MODE,&bval);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_RGBA_MODE) << setw(15) << '-' << (bval?"yes":"no") << '\n';
	glGetBooleanv(GL_INDEX_MODE,&bval);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_INDEX_MODE) << setw(15) << '-' << (bval?"yes":"no") << '\n';
	glGetBooleanv(GL_DOUBLEBUFFER,&bval);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_DOUBLEBUFFER) << setw(15) << '-' << (bval?"yes":"no") << '\n';
	glGetBooleanv(GL_STEREO,&bval);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_STEREO) << setw(15) << '-' << (bval?"yes":"no") << '\n';
	glGetIntegerv(GL_AUX_BUFFERS,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_AUX_BUFFERS) << setw(15) << 0 << ival << '\n';

	cout << "\n\n" esquape(Pixel Depths) "\n\n";
	cout << setw(W) << "state variable" << setw(15) << "minimum value" << "actual value\n";
	glGetIntegerv(GL_RED_BITS,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_RED_BITS) << setw(15) << '-' << ival << '\n';
	glGetIntegerv(GL_GREEN_BITS,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_GREEN_BITS) << setw(15) << '-' << ival << '\n';
	glGetIntegerv(GL_BLUE_BITS,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_BLUE_BITS) << setw(15) << '-' << ival << '\n';
	glGetIntegerv(GL_ALPHA_BITS,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_ALPHA_BITS) << setw(15) << '-' << ival << '\n';
	glGetIntegerv(GL_INDEX_BITS,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_INDEX_BITS) << setw(15) << '-' << ival << '\n';
	glGetIntegerv(GL_DEPTH_BITS,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_DEPTH_BITS) << setw(15) << '-' << ival << '\n';
	glGetIntegerv(GL_STENCIL_BITS,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_STENCIL_BITS) << setw(15) << '-' << ival << '\n';
	glGetIntegerv(GL_ACCUM_RED_BITS,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_ACCUM_RED_BITS) << setw(15) << '-' << ival << '\n';
	glGetIntegerv(GL_ACCUM_GREEN_BITS,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_ACCUM_GREEN_BITS) << setw(15) << '-' << ival << '\n';
	glGetIntegerv(GL_ACCUM_BLUE_BITS,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_ACCUM_BLUE_BITS) << setw(15) << '-' << ival << '\n';
	glGetIntegerv(GL_ACCUM_ALPHA_BITS,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_ACCUM_ALPHA_BITS) << setw(15) << '-' << ival << '\n';

	cout << "\n\n" esquape(Stack Depths) "\n\n";
	cout << setw(W) << "state variable" << setw(15) << "minimum value" << "actual value\n";
	glGetIntegerv(GL_MAX_MODELVIEW_STACK_DEPTH,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_MODELVIEW_STACK_DEPTH) << setw(15) << 32 << ival << '\n';
	glGetIntegerv(GL_MAX_PROJECTION_STACK_DEPTH,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_PROJECTION_STACK_DEPTH) << setw(15) << 2 << ival << '\n';
	glGetIntegerv(GL_MAX_TEXTURE_STACK_DEPTH,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_TEXTURE_STACK_DEPTH) << setw(15) << 2 << ival << '\n';
	glGetIntegerv(GL_MAX_COLOR_MATRIX_STACK_DEPTH,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_COLOR_MATRIX_STACK_DEPTH) << setw(15) << 2 << ival << '\n';
	glGetIntegerv(GL_MAX_ATTRIB_STACK_DEPTH,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_ATTRIB_STACK_DEPTH) << setw(15) << 16 << ival << '\n';
	glGetIntegerv(GL_MAX_CLIENT_ATTRIB_STACK_DEPTH,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_CLIENT_ATTRIB_STACK_DEPTH) << setw(15) << 16 << ival << '\n';
	glGetIntegerv(GL_MAX_NAME_STACK_DEPTH,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_NAME_STACK_DEPTH) << setw(15) << 64 << ival << '\n';

	cout << "\n\n" esquape(Texturing) "\n\n";
	cout << setw(W) << "state variable" << setw(15) << "minimum value" << "actual value\n";
	glGetIntegerv(GL_MAX_TEXTURE_COORDS,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_TEXTURE_COORDS) << setw(15) << 2 << ival << '\n';
	glGetIntegerv(GL_MAX_TEXTURE_UNITS,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_TEXTURE_UNITS) << setw(15) << 2 << ival << '\n';
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_TEXTURE_IMAGE_UNITS) << setw(15) << 2 << ival << '\n';
	glGetIntegerv(GL_MAX_3D_TEXTURE_SIZE,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_3D_TEXTURE_SIZE) << setw(15) << 16 << ival << '\n';
	glGetIntegerv(GL_MAX_TEXTURE_SIZE,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_TEXTURE_SIZE) << setw(15) << 64 << ival << '\n';
	glGetIntegerv(GL_MAX_ARRAY_TEXTURE_LAYERS,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_ARRAY_TEXTURE_LAYERS) << setw(15) << 256 << ival << '\n';
	glGetFloatv(GL_MAX_TEXTURE_LOD_BIAS,&fval);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_TEXTURE_LOD_BIAS) << setw(15) << 2.0 << fval << '\n';
	glGetIntegerv(GL_MAX_CUBE_MAP_TEXTURE_SIZE,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_CUBE_MAP_TEXTURE_SIZE) << setw(15) << 16 << ival << '\n';
	glGetIntegerv(GL_NUM_COMPRESSED_TEXTURE_FORMATS,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_NUM_COMPRESSED_TEXTURE_FORMATS) << setw(15) << '-' << ival << '\n';
	glGetIntegerv(GL_NUM_COMPRESSED_TEXTURE_FORMATS,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_NUM_COMPRESSED_TEXTURE_FORMATS) << setw(15) << 0 << ival << '\n';

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


	cout << "\n\n" esquape(Miscellaneous	) "\n\n";
	cout << setw(W) << "state variable" << setw(15) << "minimum value" << "actual value\n";
	glGetIntegerv(GL_MAX_LIGHTS,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_LIGHTS) << setw(15) << 8 << ival << '\n';
	glGetIntegerv(GL_MAX_CLIP_DISTANCES,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_CLIP_DISTANCES) << setw(15) << 6 << ival << '\n';
	glGetIntegerv(GL_SUBPIXEL_BITS,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_SUBPIXEL_BITS) << setw(15) << 4 << ival << '\n';
	glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_RENDERBUFFER_SIZE) << setw(15) << 1024 << ival << '\n';
	glGetIntegerv(GL_MAX_PIXEL_MAP_TABLE,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_PIXEL_MAP_TABLE) << setw(15) << 32 << ival << '\n';
	glGetIntegerv(GL_MAX_LIST_NESTING,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_LIST_NESTING) << setw(15) << 64 << ival << '\n';
	glGetIntegerv(GL_MAX_EVAL_ORDER,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_EVAL_ORDER) << setw(15) << 8 << ival << '\n';
	glGetIntegerv(GL_MAX_VIEWPORT_DIMS,iv);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_VIEWPORT_DIMS) << setw(15) << "-,-" << iv[0] << ',' << iv[1] << '\n';
	glGetIntegerv(GL_MAX_ELEMENTS_INDICES,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_ELEMENTS_INDICES) << setw(15) << '-' << ival << '\n';
	glGetIntegerv(GL_MAX_ELEMENTS_VERTICES,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_ELEMENTS_VERTICES) << setw(15) << '-' << ival << '\n';
	glGetIntegerv(GL_SAMPLE_BUFFERS,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_SAMPLE_BUFFERS) << setw(15) << 0 << ival << '\n';
	glGetIntegerv(GL_SAMPLES,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_SAMPLES) << setw(15) << 0 << ival << '\n';

	cout << "\n\n" esquape(Points & Lines) "\n\n";
	cout << setw(W) << "state variable" << setw(15) << "minimum value" << "actual value\n";
	glGetFloatv(GL_ALIASED_POINT_SIZE_RANGE,fv);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_ALIASED_POINT_SIZE_RANGE) << setw(15) << "1,1" << fv[0] << ',' << fv[1] << '\n';
	glGetFloatv(GL_SMOOTH_POINT_SIZE_RANGE,fv);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_SMOOTH_POINT_SIZE_RANGE) << setw(15) << "1,1" << fv[0] << ',' << fv[1] << '\n';
	glGetFloatv(GL_SMOOTH_POINT_SIZE_GRANULARITY,&fval);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_SMOOTH_POINT_SIZE_GRANULARITY) << setw(15) << '-' << fval << '\n';
	glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE,fv);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_ALIASED_LINE_WIDTH_RANGE) << setw(15) << "1,1" << fv[0] << ',' << fv[1] << '\n';
	glGetFloatv(GL_SMOOTH_LINE_WIDTH_RANGE,fv);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_SMOOTH_LINE_WIDTH_RANGE) << setw(15) << "1,1" << fv[0] << ',' << fv[1] << '\n';
	glGetFloatv(GL_SMOOTH_LINE_WIDTH_GRANULARITY,&fval);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_SMOOTH_LINE_WIDTH_GRANULARITY) << setw(15) << '-' << fval << '\n';

	cout << "\n\n" esquape(Shaders) "\n\n";
	cout << setw(W) << "state variable" << setw(15) << "minimum value" << "actual value\n";
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_VERTEX_ATTRIBS) << setw(15) << 16 << ival << '\n';
	glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_VERTEX_UNIFORM_COMPONENTS) << setw(15) << 512 << ival << '\n';
	glGetIntegerv(GL_MAX_VARYING_COMPONENTS,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_VARYING_COMPONENTS) << setw(15) << 32 << ival << '\n';
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS) << setw(15) << 2 << ival << '\n';
	glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS) << setw(15) << 0 << ival << '\n';
	glGetIntegerv(GL_MAX_TEXTURE_BUFFER_SIZE,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_TEXTURE_BUFFER_SIZE) << setw(15) << 65536 << ival << '\n';
	glGetIntegerv(GL_MAX_RECTANGLE_TEXTURE_SIZE,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_RECTANGLE_TEXTURE_SIZE) << setw(15) << 1024 << ival << '\n';
	glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS) << setw(15) << 64 << ival << '\n';
	glGetIntegerv(GL_MIN_PROGRAM_TEXEL_OFFSET,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MIN_PROGRAM_TEXEL_OFFSET) << setw(15) << -8 << ival << '\n';
	glGetIntegerv(GL_MAX_PROGRAM_TEXEL_OFFSET,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_PROGRAM_TEXEL_OFFSET) << setw(15) << 7 << ival << '\n';
	glGetIntegerv(GL_MAX_DRAW_BUFFERS,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_DRAW_BUFFERS) << setw(15) << 1 << ival << '\n';
	glGetIntegerv(GL_MAX_VERTEX_UNIFORM_BLOCKS,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_VERTEX_UNIFORM_BLOCKS) << setw(15) << 12 << ival << '\n';
	glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_BLOCKS,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_FRAGMENT_UNIFORM_BLOCKS) << setw(15) << 12 << ival << '\n';
	glGetIntegerv(GL_MAX_COMBINED_UNIFORM_BLOCKS,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_COMBINED_UNIFORM_BLOCKS) << setw(15) << 24 << ival << '\n';
	glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_UNIFORM_BUFFER_BINDINGS) << setw(15) << 24 << ival << '\n';
	glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_UNIFORM_BLOCK_SIZE) << setw(15) << 16384 << ival << '\n';
	glGetIntegerv(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT) << setw(15) << 1 << ival << '\n';
	glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_VERTEX_UNIFORM_COMPONENTS) << setw(15) << 1 << ival << '\n';
	glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS) << setw(15) << 1 << ival << '\n';
	glGetIntegerv(GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS) << setw(15) << 1 << ival << '\n';
	glGetIntegerv(GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS,&ival);
	if(glGetError() == GL_NO_ERROR)
		cout << setw(W) << esquape(GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS) << setw(15) << 1 << ival << '\n';

	// event handling initialization
	glutDestroyWindow(windowID);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,GLUT_ACTION_CONTINUE_EXECUTION);
	glutMainLoop();

	system("PAUSE");
	return 0;
} // end function main
