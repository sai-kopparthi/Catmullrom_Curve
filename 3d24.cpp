#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <stdio.h>
 int win_height;
int win_width;
int grid_width;
int grid_height;
float pixel_size;
 FILE *fp = fopen("in.txt", "r+");
struct point
{
	float x;
	float y;
}p[100][100];
 
 
int n,f[100]; 
 void draw_pix(int x, int y){
    glBegin(GL_POINTS);
    glColor3f(0.2,0.2,0.4);
    glVertex3f(x+.01,y+.01,0);
    glEnd();
}
struct point CatmullRoll(float t, struct point p1, struct point p2, struct point p3, struct point p4)
{
 
	float t2 = t*t;
	float t3 = t*t*t;
	struct point v; // Interpolated point
 
	/* Catmull Rom spline Calculation */
 
	v.x = ((-t3 + 2*t2-t)*(p1.x) + (3*t3-5*t2+2)*(p2.x) + (-3*t3+4*t2+t)* (p3.x) + (t3-t2)*(p4.x))/2;
	v.y = ((-t3 + 2*t2-t)*(p1.y) + (3*t3-5*t2+2)*(p2.y) + (-3*t3+4*t2+t)* (p3.y) + (t3-t2)*(p4.y))/2;

 
	return v;	
}
 
void initScene()                                                
{
	glClearColor(0.0,0.0,0.0,0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);	// Make round points, not square points
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);		// Antialias the lines
 
}
 
/* void mouse(int button,)
{
 
*/
void reshape(int width,int height)
{
	/*glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	if(w<=h)
		glOrtho(-60.0,60.0,-60.0*(GLfloat)h/(GLfloat)w,60.0*(GLfloat)h/(GLfloat)w,-60.0,60.0);
	else
		glOrtho(-60.0,6.0,-60.0*(GLfloat)w/(GLfloat)h,60.0*(GLfloat)w/(GLfloat)h,-60.0,60.0);*/
win_width = width;
	win_height = height;
    
    //creates a rendering area across the window
	glViewport(0,0,width,height);
    // up an orthogonal projection matrix so that
    // the pixel space is mapped to the grid space
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrtho(0,grid_width,0,grid_height,-10,10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
 
}
void display(void)
{
	float t;
	struct point v;	//Interpolated point 
	

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f,1.0f,1.0f);
	glPointSize(8);
 
	
for(int i=0;i<n;i++)
	{
	 for( int j=0;j<(f[i]-3);j++)
	{
	for(t=0;t<1;t+=0.02)
	{
		v = CatmullRoll(t,p[i][j],p[i][j+1],p[i][j+2],p[i][j+3]);
		glBegin(GL_POINTS);
			glVertex2f(v.x,v.y);
		glEnd();
	}
}
for(t=0;t<1;t+=0.02)
	{
		v = CatmullRoll(t,p[i][f[i]-3],p[i][f[i]-2],p[i][f[i]-1],p[i][f[i]]);
		glBegin(GL_POINTS);
			glVertex2f(v.x,v.y);
		glEnd();
	}
}
 for(int i=0;i<n;i++)
	{
	 for( int j=0;j<(f[i]);j++)
	{
         /*glBegin(GL_POINTS);
			glVertex2f(p[i][j].x,p[i][j].y);
		glEnd();*/draw_pix(p[i][j].x,p[i][j].y);
}
}
	glFlush();
 
}
 
 
int main(int argc, char *argv[])
{
 //the number of pixels in the grid
    grid_width = 100;
    grid_height = 100;
    
    //the size of pixels sets the inital window height and width
    //don't make the pixels too large or the screen size will be larger than
    //your display size
    pixel_size = 5;
    
    /*Window information*/
    win_height = grid_height*pixel_size;
    win_width = grid_width*pixel_size;
GLint nump;
fscanf(fp,"%d",&nump);
	n=nump;
int j;
	for(int i=0;i<n;i++)
	{
	//printf("Enter the number of vertices in a %d polygon\n",i+1);
	GLint vertex;
	fscanf(fp,"%d",&vertex);
	f[i]=vertex;
	//scanf("%d",&v[i]);
	  for( j=0;j<f[i];j++)
	{
	    // printf("Enter the %d point x and y coordinate respectively\n",j+1);
	    GLfloat xcord,ycord;
	     fscanf(fp,"%f",&xcord);
	     fscanf(fp,"%f",&ycord);
	      p[i][j].x=xcord;
	      p[i][j].y=ycord;
	     printf("\n");
	}
	}
	fclose(fp);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Catmull Rom");
	initScene();
	glutDisplayFunc(display);	
	glutReshapeFunc(reshape);
	glutMainLoop();
}
