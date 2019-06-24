#include<stdio.h>
#include<windows.h>
#include <mmsystem.h>
#include<GL/glut.h>
#include <Gl/gl.h>
#include<math.h>
#include<time.h>
#include <sys/timeb.h>


const float clockR    = 35.0f,
            clockVol  = 200.0f,

            angle1min = M_PI / 30.0f,

            minStart  = 0.9f,
            minEnd    = 1.0f,

            stepStart = 0.8f,
            stepEnd   = 1.0f;

float angleHour = 0,
      angleMin  = 0,
      angleSec  = 0;

void init()
{
   glClearColor(1.000, 0.973, 0.863, 1.0);
    glOrtho(-200,200,-200,200,-200,200);
}


void newLine(float rStart, float rEnd, float angle)
{
  float c = cos(angle), s = sin(angle);
  glVertex2f( 0, 40);
  glVertex2f(  clockR*rEnd*c, 40+clockR*rEnd*s);
}


void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    //RIGHT WALL
    glColor3f(0.847, 0.749, 0.847);
    glBegin(GL_POLYGON);
    glVertex2f(-200,-200);
    glVertex2f(-100,-40);
    glVertex2f(-100,200);
    glVertex2f(-200,200);
    glEnd();

    //FRONT WALL
    glColor3f(0.867, 0.627, 0.867);
    glBegin(GL_POLYGON);
    glVertex2f(-100,-40);
    glVertex2f(-100,200);
    glVertex2f(200,200);
    glVertex2f(200,-40);
    glEnd();

    //MIDDLE LEFT LEG WITH BAR
    glColor3f(0.502, 0.502, 0.502);
    glBegin(GL_POLYGON);
    glVertex2f(80,-20);
    glVertex2f(80,-100);
    glVertex2f(68,-100);
    glVertex2f(68,-32);
    glVertex2f(-108,-32);
    glVertex2f(-120,-20);
    glEnd();

    //LEFT LEG
     glColor3f(0.502, 0.502, 0.502);
     glBegin(GL_QUADS);
     glVertex2f(-120,-100);
     glVertex2f(-108,-100);
     glVertex2f(-108,-32);
     glVertex2f(-120,-20);
     glEnd();

     //LEFT MIDDLE LEG
     glColor3f(0.412, 0.412, 0.412);
     glBegin(GL_QUADS);
     glVertex2f(-80,-70);
     glVertex2f(-70,-70);
     glVertex2f(-70,-32);
     glVertex2f(-80,-32);
     glEnd();

    //UPER PART OF TABLE
    glColor3f(0.753, 0.753, 0.753);
    glBegin(GL_POLYGON);
    glVertex2f(-120,-20);
    glVertex2f(80,-20);
    glVertex2f(116,20);
    glVertex2f(-80,20);
    glEnd();

    //MIDDLE RIGHT LEG
    glColor3f(0.663, 0.663, 0.663);
    glBegin(GL_QUADS);
    glVertex2f(80,-100);
    glVertex2f(84,-96);
    glVertex2f(84,-28);
    glVertex2f(80,-20);
    glEnd();

    //RIGHT LEG
    glColor3f(0.663, 0.663, 0.663);
    glBegin(GL_QUADS);
    glVertex2f(110,4);
    glVertex2f(110,-64);
    glVertex2f(116,-56);
    glVertex2f(116,20);
    glEnd();

    //RIGHT UPER BAR
    glColor3f(0.663, 0.663, 0.663);
    glBegin(GL_QUADS);
    glVertex2f(110,4);
    glVertex2f(116,20);
    glVertex2f(80,-20);
    glVertex2f(84,-28);
    glEnd();

    // CLOCK BASEMENT
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(40,-5);
    glVertex2f(-40,-5);
    glVertex2f(-32,20);
    glVertex2f(32,20);
    glEnd();

    // LEFT WINDOW
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glVertex2f(-10,140);
    glVertex2f(-10,80);
    glVertex2f(-70,80);
    glVertex2f(-70,140);
    glEnd();

    // RIGHT WINDOW
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glVertex2f(70,140);
    glVertex2f(70,80);
    glVertex2f(130,80);
    glVertex2f(130,140);
    glEnd();
    //SUN
    glBegin(GL_POLYGON);
        GLfloat a=95, b=120, c=10;
        glColor3f(1, 1, 0);
            for(float l=0; l<=7; l=l+.1)
            {
                glVertex3f(a+c*cos(l),b+c*sin(l),0);
            }

    glEnd();

    // CLOCK CIRCLE
    glBegin(GL_POLYGON);
        GLfloat x=0, y=40, r=40;
        glColor3f(0, 0, 0);
            for(float i=0; i<=7; i=i+.1)
            {
                glVertex3f(x+r*cos(i),y+r*sin(i),0);
            }

    glEnd();

    // CLOCK STRIPES
  int i;
    glBegin(GL_LINES);
    for(i=0; i<60; i++)
    {
      if(i%5)
      { // normal minute
        if(i%5 == 1)
          glColor3f(1.000, 0.000, 1.000);
        newLine(minEnd, minStart, i*angle1min);
      }
    else
      {

        glColor3f(1, 0, 0);
        newLine(stepStart, stepEnd, i*angle1min);

      }
    }

    glEnd();

    // CLOCK HAND
    glLineWidth(4.0f);
    glColor3f(1, 1, 1);
  glBegin(GL_LINES);
    newLine(0.0f, 0.5f, -angleHour+M_PI/2);
    newLine(0.0f, 0.7f, -angleMin+M_PI/2);
  glEnd();

  glLineWidth(4.0f);
  glColor3f(1, 1, 1);
  glBegin(GL_LINES);
    newLine(0.0f, 0.9f, -angleSec+M_PI/2);
  glEnd();
    glFlush();
}
void TimerFunction(int value){
  struct timeb tb;
  time_t tim=time(0);
  struct tm* t;
  t=localtime(&tim);
  ftime(&tb);

  angleSec = (float)(t->tm_sec+ (float)tb.millitm/1000.0f)/30.0f * M_PI;
  angleMin = (float)(t->tm_min)/30.0f * M_PI + angleSec/60.0f;
  angleHour = (float)(t->tm_hour > 12 ? t->tm_hour-12 : t->tm_hour)/6.0f * M_PI+
              angleMin/12.0f;

  glutPostRedisplay();
  glutTimerFunc(33,TimerFunction, 1);
}

int main()
{
    PlaySound(TEXT("tik.wav"),NULL,SND_ASYNC|SND_FILENAME|SND_LOOP);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1200,700);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Time and tide waits for none");
    init();
    glutDisplayFunc(RenderScene);
    glutTimerFunc(33, TimerFunction, 1);


    glutMainLoop();
    return 0;
}
