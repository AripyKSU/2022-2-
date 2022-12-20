#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include "include\GL\freeglut.h"
#include <vector>

// ������ ũ��
int Width = 800, Height = 800;

// ��� ������ ���� ������
int ManipulateMode = 0; // 1: ȸ��, 2: �̵�
int StartPt[2];
float Axis[3] = { 1.0, 0.0, 0.0 };
float Angle = 0.0;
float RotMat[16] = { 1, 0, 0, 0,
					0, 1, 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 1 };
float Zoom = -30.0;
float Pan[3] = { 0.0, 0.0, 0.0 };
float UpArmRot = 0.0;
float DownArmRot = 0.0;
float FingerMove = 0.0;

//materials
float mat0_ambient[] = { 0.5,0.5,0.5 };
float mat0_diffuse[] = { 0.8,0.2,0.8 };
float mat0_specular[] = { 1.0,0.3,1.0 };
float mat0_shininess = 32;
float mat1_ambient[] = { 0.5,0.5,0.5 };
float mat1_diffuse[] = { 0.8,0.8,0.2 };
float mat1_specular[] = { 1.0,1.0,0.3 };
float mat1_shininess = 32;
float mat2_ambient[] = { 0.5,0.5,0.5 };
float mat2_diffuse[] = { 0.2,0.8,0.8 };
float mat2_specular[] = { 0.3,1.0,1.0 };
float mat2_shininess = 32;
float mat3_ambient[] = { 0.5,0.5,0.5 };
float mat3_diffuse[] = { 0.4,0.4,0.4 };
float mat3_specular[] = { 0.6,0.6,0.6 };
float mat3_shininess = 32;
GLuint texId[1];

// �ݹ� �Լ���
void Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void MouseWheel(int button, int dir, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void Render();

// ����� ���� �Լ���
void InitOpenGL();
void GetSphereCoord(int x, int y, float *px, float *py, float *pz);
void RenderFloor();
void RenderRobot();
void drawCube(float sx, float sy, float sz);
void SetupViewVolume();
void SetupViewTransform();
void Sub(double out[3], double a[3], double b[3]);
void Add(double out[3], double a[3], double b[3]);
void Cross(double out[3], double a[3], double b[3]);
unsigned char* ReadBmpFile(const char* fname, int* w, int* h);


void Cross(double out[3], double a[3], double b[3])
{
	out[0] = a[1] * b[2] - a[2] * b[1];
	out[1] = a[2] * b[0] - a[0] * b[2];
	out[2] = a[0] * b[1] - a[1] * b[0];
}

void Sub(double out[3], double a[3], double b[3])
{
	out[0] = a[0] - b[0];
	out[1] = a[1] - b[1];
	out[2] = a[2] - b[2];
}

void Add(double out[3], double a[3], double b[3])
{
	out[0] = a[0] + b[0];
	out[1] = a[1] + b[1];
	out[2] = a[2] + b[2];
}

int main(int argc, char **argv)
{
	// GLUT �ʱ�ȭ(���� Į�����, RBGA, ���̹��� ���)
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	// ������ ����
	glutInitWindowSize(Width, Height);
	glutCreateWindow("3DViewer");

	// OpenGL �ʱ�ȭ
	InitOpenGL();

	// �ݹ��Լ� ���
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutMotionFunc(Motion); // ���콺 ��ư ������ ������ ��, �ڵ����� ȣ��Ǵ� �Լ�
	glutMouseWheelFunc(MouseWheel);
	glutDisplayFunc(Render);

	// �޽��� ���� ����
	glutMainLoop();
	return 0;
}


void InitOpenGL()
{
	// ���� �׽�Ʈ�� Ȱ��ȭ
	glEnable(GL_DEPTH_TEST);

	// ���� �� Ȱ��ȭ
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// �� ���� ��ġ
	GLfloat light0_position[] = { 0.0f, 10.0f, 100.0f, 1.0f };
	GLfloat light0_ambient[] = { 0.5f, 0.5f, 0.5f};
	GLfloat light0_diffuse[] = { 0.8f, 0.8f, 0.8f};
	GLfloat light0_specular[] = { 0.8f, 0.8f, 0.8f};

	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

	//texture
	glGenTextures(1, texId);

	int w, h;
	unsigned char* pImage;
	pImage = ReadBmpFile("./texture0.bmp", &w, &h);
	glBindTexture(GL_TEXTURE_2D, texId[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pImage);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, w, h, GL_RGBA, GL_UNSIGNED_BYTE, pImage);
	delete[] pImage;
}

void Render()
{
	// Clear color buffer
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set up viewing volume
	SetupViewVolume();

	// Set up viewing transformation
	SetupViewTransform();

	glMatrixMode(GL_MODELVIEW);
	RenderFloor();
	RenderRobot();

	// Swap buffers for double buffering.
	glutSwapBuffers();
}

void RenderRobot()
{
	// ���� �ϼ���.
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glBindTexture(GL_TEXTURE_2D, texId[0]);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	drawCube(10.0f, 1.0f, 10.0f);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_2D);
	//1�� ��ǥ��
	glPushMatrix();
	glTranslatef(0,1,0);
	glRotatef(UpArmRot, 0, 1, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat0_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat0_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat0_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &mat0_shininess);
	drawCube(1.0f, 5.0f, 1.0f);
	//2�� ��ǥ��
	glPushMatrix();
	glTranslatef(0, 5, 0);
	glRotatef(DownArmRot, 0, 0, 1);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat1_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat1_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat1_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &mat1_shininess);
	glutSolidSphere(1, 10, 10);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat2_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat2_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat2_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &mat2_shininess);
	drawCube(1.0f, 5.0f, 1.0f);
	//3�� ��ǥ��
	glPushMatrix();
	glTranslatef(-0.5 - FingerMove, 5.0, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat3_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat3_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat3_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &mat3_shininess);
	drawCube(0.1, 2.0, 1.0);
	glPopMatrix();
	//4�� ��ǥ��

	glTranslatef(0.5 + FingerMove, 5.0, 0);
	drawCube(0.1, 2.0, 1.0);
	glPopMatrix();
	glPopMatrix();
}

void Keyboard(unsigned char key, int x, int y)
{
	// Complete implementation...
	switch(key) {
	case '1':
		UpArmRot -= 3.0;
		break;
	case '2':
		UpArmRot += 3.0;
		break;
	case '3':
		DownArmRot -= 3.0;
		break;
	case '4':
		DownArmRot += 3.0;
		break;
	case '5':
		FingerMove -= 0.1;
		if (FingerMove < 0) FingerMove = 0;
		break;
	case '6':
		FingerMove += 0.1;
		break;
	}
	glutPostRedisplay();
}

void drawCube(float sx, float sy, float sz)
{
	glPushMatrix();
	glTranslatef(0.0, sy * 0.5, 0.0);
	glScalef(sx, sy, sz);
	glutSolidCube(1.0);
	glPopMatrix();
}

void Reshape(int w, int h)
{
	// ����Ʈ ��ȯ
	glViewport(0, 0, w, h);
	Width = w;
	Height = h;
}

void SetupViewVolume()
{
	// ���� ���� ����
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, (double)Width / (double)Height, 1.0, 10000.0);
}

void SetupViewTransform()
{
	// �� �� ����� ���� ��ķ� �ʱ�ȭ, M = I
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// �� ��/�ƿ��� ���� ��ȯ, M = I * T_zoom
	glTranslatef(0.0, 0.0, Zoom);

	// ���ο� ȸ���� ����, M = I * T_zoom * R_new
	glRotatef(Angle, Axis[0], Axis[1], Axis[2]);

	// ���� ȸ���� ����, M = I * T_zoom * R_new * R_old	//   R_n .... * R3 * R2 * R1
	glMultMatrixf(RotMat);

	// ȸ�� ��� ����, R_old = R_new * R_old
	glGetFloatv(GL_MODELVIEW_MATRIX, RotMat);
	RotMat[12] = RotMat[13] = RotMat[14] = 0.0;

	// �̵� ��ȯ�� ����, M = I * T_zoom * R_new * R_old * T_pan
	glTranslatef(Pan[0], Pan[1], Pan[2]);
}

void RenderFloor()
{
	glDisable(GL_LIGHTING);
	glColor3f(0.7f, 0.7f, 0.7f);
	for (int x = -10; x <= 10; x++)
	{
		if (x == 0)
			continue;
		glBegin(GL_LINES);
		glVertex3f((float)x, 0.0, -10.0f);
		glVertex3f((float)x, 0.0, 10.0f);
		glVertex3f(-10.0f, 0.0, (float)x);
		glVertex3f(10.0f, 0.0, (float)x);
		glEnd();
	}

	glLineWidth(2.0f);
	glColor3f(0.3f, 0.3f, 0.3f);
	glBegin(GL_LINES);
	glVertex3f(-10.0f, 0.0f, 0.0f);
	glVertex3f(10.0f, 0.0, 0.0f);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, -10.0f);
	glVertex3f(0.0f, 0.0, 10.0f);
	glEnd();
	glLineWidth(1.0f);
	glEnable(GL_LIGHTING);
}

void Mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		StartPt[0] = x;
		StartPt[1] = y;
		if (button == GLUT_LEFT_BUTTON)
			ManipulateMode = 1;	// ȸ��

		if (button == GLUT_RIGHT_BUTTON)
			ManipulateMode = 2;	// �̵�
	}
	if (state == GLUT_UP)
	{
		ManipulateMode = 0;	// ����
		StartPt[0] = StartPt[1] = 0;
		Angle = 0.0;
	}
}

void Motion(int x, int y)
{
	// ȸ����� ȸ�� ���� ���
	if (ManipulateMode == 1)
	{
		// ���� �� ���� ��ǥ ���
		float px, py, pz, qx, qy, qz;
		GetSphereCoord(StartPt[0], StartPt[1], &px, &py, &pz);
		GetSphereCoord(x, y, &qx, &qy, &qz);

		// ȸ�� ��� ���� ���
		Axis[0] = py * qz - pz * qy;
		Axis[1] = pz * qx - px * qz;
		Axis[2] = px * qy - py * qx;
		Angle = 0.0;
		float len = Axis[0] * Axis[0] + Axis[1] * Axis[1] + Axis[2] * Axis[2];
		if (len > 0.0001) // ���� ���� �̻� ó��
			Angle = acos(px * qx + py * qy + pz * qz) * 180.0f / 3.141592f;
	}

	// �̵� ���� ���
	if (ManipulateMode == 2)
	{
		float dx = (float)(x - StartPt[0]) * 0.01f;
		float dy = (float)(StartPt[1] - y) * 0.01f;
		// ȸ�� ��� �� �����
		// R = 0 4 8   invR = 0 1 2
		//     1 5 9          4 5 6    
		//     2 6 10         8 9 10
		// invR * (dx, dy, 0)
		Pan[0] += RotMat[0] * dx + RotMat[1] * dy;
		Pan[1] += RotMat[4] * dx + RotMat[5] * dy;
		Pan[2] += RotMat[8] * dx + RotMat[9] * dy;
	}

	StartPt[0] = x;	// Update startpt as current position
	StartPt[1] = y;
	glutPostRedisplay();
}

/*!
*	\brief ���콺 ��ũ���� ó���ϴ� �ݹ� �Լ�
*
*	\param button[in]	���콺 ��ư ����(GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON)
*	\param dir[in]		��ũ���� ����
*	\param x[in]		���� ����� (0, 0) �������� ���콺 �������� ���� ��ġ
*	\param y[in]		���� ����� (0, 0) �������� ���콺 �������� ���� ��ġ
*/
void MouseWheel(int button, int dir, int x, int y)
{
	if (dir > 0)
		Zoom += 1.0;
	else
		Zoom -= 1.0;
	glutPostRedisplay();
}

void GetSphereCoord(int x, int y, float *px, float *py, float *pz)
{
	*px = (2.0f * x - Width) / Width;
	*py = (-2.0f * y + Height) / Height;

	float r = (*px) * (*px) + (*py) * (*py); // �������κ����� �Ÿ� ���
	if (r >= 1.0f)
	{
		*px = *px / sqrt(r);
		*py = *py / sqrt(r);
		*pz = 0.0f;
	}
	else
		*pz = sqrt(1.0f - r);  // �Ϲ����� ���
}

unsigned char* ReadBmpFile(const char* fname, int* w, int* h)
{
	// ������ �����Ѵ�.
	FILE* fp;
	fopen_s(&fp, fname, "rb");

	// BMP ������ ��� ������ �д´�.
	BITMAPFILEHEADER fileheader;
	BITMAPINFOHEADER infoheader;
	RGBTRIPLE rgb;
	fread(&fileheader, sizeof(fileheader), 1, fp);
	fseek(fp, sizeof(fileheader), SEEK_SET); // Jump the fileheader
	fread(&infoheader, sizeof(infoheader), 1, fp); // and read the infoheader

	// ��� ������ �ʺ�� ���̸� �����Ѵ�.
	*w = infoheader.biWidth;
	*h = infoheader.biHeight;

	// �̹��� �����͸� ������ �迭�� �����Ѵ�.
	int size = infoheader.biWidth * infoheader.biHeight;
	unsigned char* pData = new unsigned char[size * 4];
	memset(pData, 0, size * 4);

	// �̹��� �����͸� �迭�� �����Ѵ�.
	for (int i = 0; i < size; ++i)
	{
		fread(&rgb, sizeof(rgb), 1, fp); // load RGB value
		pData[i * 4 + 0] = rgb.rgbtRed;
		pData[i * 4 + 1] = rgb.rgbtGreen;
		pData[i * 4 + 2] = rgb.rgbtBlue;
		pData[i * 4 + 3] = 255; // Alpha value
	}
	fclose(fp);

	// �迭�� ��ȯ�Ѵ�.
	return pData;
}