#include <iostream>
// #include <algorithm>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
//#include "src/Engine.h"


#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include "GrContext.h"
#include "gl/GrGLInterface.h"
#include "SkData.h"
#include "SkImage.h"
#include "SkStream.h"
#include "SkSurface.h"
#include "SkCanvas.h"

#include "src/Stroke.h"

void gl_example(int width, int height, void(*draw)(SkCanvas*), const char* path) {
    // You've already created your OpenGL context and bound it.
    const GrGLInterface* interface = nullptr;
    // Leaving interface as null makes Skia extract pointers to OpenGL functions for the current
    // context in a platform-specific way. Alternatively, you may create your own GrGLInterface and
    // initialize it however you like to attach to an alternate OpenGL implementation or intercept
    // Skia's OpenGL calls.
    GrContext* context = GrContext::Create(kOpenGL_GrBackend, (GrBackendContext) interface);
    SkImageInfo info = SkImageInfo:: MakeN32Premul(width, height);
    sk_sp<SkSurface> gpuSurface(
            SkSurface::MakeRenderTarget(context, SkBudgeted::kNo, info));
    if (!gpuSurface) {
        SkDebugf("SkSurface::MakeRenderTarget returned null\n");
        return;
    }
    SkCanvas* gpuCanvas = gpuSurface->getCanvas();
    draw(gpuCanvas);
    sk_sp<SkImage> img(gpuSurface->makeImageSnapshot());
    if (!img) { return; }
    sk_sp<SkData> png(img->encode());
    if (!png) { return; }
    //SkFILEWStream out(path);
    //(void)out.write(png->data(), png->size());
}

void displayMe(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.5, 0.0, 0.0);
        glVertex3f(0.5, 0.5, 0.0);
        glVertex3f(0.0, 0.5, 0.0);
    glEnd();
    glFlush();
}

GeneticImages::Stroke stroke;

void draw(SkCanvas* gpuCanvas) 
{
	gpuCanvas->clear(SK_ColorTRANSPARENT);

	for (int i = 0; i < 250; ++i)
	{
		gpuCanvas->drawLine(
			stroke.points[0].x(), stroke.points[0].y(),
			stroke.points[1].x(), stroke.points[1].y(),
			stroke.paint
		);

		//gpuCanvas->drawLine(30, 30, 70, 70,)
	}
}

int main(int argc, char** argv)
{
	// Seed the random number generator
	srand(time(NULL));

    // Create the engine output directory
    boost::filesystem::path engineOutputDirectory("engine-output");
    boost::filesystem::create_directory(engineOutputDirectory);

	// GeneticImages::Engine engine("sonic32x32.png");
	// engine.Run();


	stroke.InitRandomly(100, 100);


	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hello world :D");
    //glutDisplayFunc(displayMe);

	void (*f)(SkCanvas*);
	f = &draw;

	int t0 = time(NULL);
	for (int i = 0; i < 10000; ++i)
	{
		std::string outputFile = "engine-output/test" + boost::lexical_cast<std::string>(i) + ".png";
		gl_example(32, 32, f, outputFile.c_str());
	}

	int t1 = time(NULL);
	std::cout << t1 - t0 << std::endl;

	//glutMainLoop();

	return(0);
}