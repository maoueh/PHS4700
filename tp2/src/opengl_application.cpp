#include "command_line.h"
#include "logger.h"
#include "opengl_application.h"
#include "window.h"

OpenGlApplication::OpenGlApplication(CommandLine* commandLine) : Application(commandLine),
    mCamera(new Camera(30.0f, DEG2RAD(45.0f), DEG2RAD(205.0f))),  mFramerate(50),
    mIsPerspective(TRUE)  
{

}

OpenGlApplication::~OpenGlApplication()
{

}

void OpenGlApplication::initialize()
{
    Application::initialize();

    glewInit();
    if ( !glewIsSupported("GL_VERSION_2_0") ) 
    {
	    mLogger->log("OpenGL version 2.0 or above required");
        exit(1);
    }

    glShadeModel(GL_SMOOTH);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_FOG);

    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void OpenGlApplication::process()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    updateCamera();
    updateWorld();

    draw(); 

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    updateProjection();

    mWindow->swapBuffers();
}

void OpenGlApplication::keyPressed(KeyEvent& event)
{
   switch(event.keyCode) 
   {
      case VK_ESCAPE : // Fall Through
      case VK_Q :
		stop();
        break;
      case VK_P :
         mIsPerspective = !mIsPerspective;
         break;
      case VK_MINUS :  // Fall Through
      case VK_MINUS_2 :
         mCamera->zoomIn(2.0f);
         break;
      case VK_PLUS : // Fall Through
      case VK_PLUS_2 :
         mCamera->zoomOut(2.0f);
         break;
      case VK_RIGHT :
         mCamera->stepRight();
         break;
      case VK_LEFT :
         mCamera->stepLeft();
         break;
      case VK_UP :
         mCamera->stepFoward();
         break;
      case VK_DOWN :
         mCamera->stepBackward();
         break;
   }
}

void OpenGlApplication::mouseWheel(MouseEvent& event)
{
    mCamera->zoom(event.delta / 120.0f);
}

void OpenGlApplication::windowResized(WindowEvent& event)
{
    updateViewport();
}

void OpenGlApplication::updateCamera()
{
   mCamera->update();

   const Vector3d& position = mCamera->getPosition();
   const Vector3d& target = mCamera->getTarget();
   const Vector3d& up = mCamera->getUp();

   gluLookAt(position.x(), position.y(), position.z(), 
             target.x(),   target.y(),   target.z(), 
             up.x(),       up.y(),       up.z());
}

void OpenGlApplication::updateProjection()
{
    FLOAT height = (FLOAT) mWindow->getHeight();
    if (mIsPerspective)
    {
        if ( height != 0 )
            gluPerspective(60.0, (FLOAT) mWindow->getWidth() / height, 0.1, 300.0);
    } 
    else
    {
        FLOAT width = (FLOAT) mWindow->getWidth();
        if ( width <= height && width != 0.0 ) 
            glOrtho(-15.0, 15.0, -15.0 * height / width, 15.0 * height / width, 0.01, 300.0);
        else if ( height != 0.0 )
            glOrtho(-15.0 * width / height, 15.0 * width / height, -15.0, 15.0, 0.01, 300.0);
    }
}

void OpenGlApplication::updateViewport()
{
    glViewport(0, 0, mWindow->getWidth(), mWindow->getHeight());
    draw();
}


void OpenGlApplication::updateWorld()
{

}

void OpenGlApplication::idle()
{

}