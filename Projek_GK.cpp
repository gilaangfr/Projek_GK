#include "stdafx.h"
#include <cmath>
#include "glut.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define MAKS 100

typedef struct {
    float x;
    float y;
} point2D_t;

bool isAnimating = false;
int tick = 0;
float morphStep = 0.0f;  // Step untuk perubahan morphing

point2D_t kura2[MAKS] = {
 {-85, 37}, {-76, 40}, {-69, 39}, {-59, 32}, {-49, 24}, {-43, 16}, {-40, 12}, {-40, 9}, {-38, 4}, {-29, 6},
    {-7, 16}, {5, 17}, {16, 20}, {32, 19}, {42, 15}, {51, 12}, {59, 9}, {70, 0}, {77, -7}, {82, -12},
    {87, -14}, {92, -19}, {94, -21}, {88, -23}, {93, -31}, {99, -36}, {104, -42}, {117, -43}, {106, -43}, {92, -42},
    {77, -45}, {70, -44}, {67, -48}, {54, -52}, {43, -51}, {36, -46}, {-18, -52}, {-33, -47}, {-39, -46}, {-56, -51},
    {-78, -54}, {-79, -48}, {-68, -42}, {-63, -36}, {-58, -27}, {-50, -24}, {-49, -21}, {-64, -9}, {-73, -3}, {-81, 10},
    {-86, 21}, {-88, 26}, {-87, 31}, {-86, 34}, {-85, 37}
};

point2D_t pesawat[MAKS] = {
  {-154, -12}, {-131, 0}, {-119, 8}, {-119, 9}, {-60, 9}, {-45, 9}, {-11, 59}, {3, 57}, {-10, 6}, {78, 5},
    {79, 4}, {97, 14}, {131, 41}, {148, 43}, {132, 29}, {123, 7}, {129, 5}, {129, 1}, {120, 0}, {137, 9},
    {158, -17}, {144, -17}, {102, -6}, {87, -11}, {65, -16}, {49, -21}, {13, -23}, {34, -35}, {74, -51}, {116, -64},
    {109, -72}, {60, -65}, {58, -67}, {28, -71}, {24, -67}, {23, -63}, {26, -58}, {42, -55}, {3, -43}, {10, -47},
    {2, -52}, {-8, -53}, {-22, -54}, {-29, -47}, {-25, -44}, {-4, -41}, {-34, -27}, {-63, -25}, {-88, -27}, {-106, -28},
    {-128, -26}, {-143, -19}, {-153, -16}, {-154, -11}, {-154, -12}
};


point2D_t interpolate(point2D_t a, point2D_t b, float r) {
    point2D_t result;
    result.x = a.x + (b.x - a.x) * r;
    result.y = a.y + (b.y - a.y) * r;
    return result;
}

void userDraw(void) {
    int totalFrames = 100;
    int i;
    float rtick = morphStep;
    glClearColor(0.0f, 0.3f, 0.0f, 1.0f); // Warna hijau tua untuk latar belakang
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINES);
    for (i = 0; i < MAKS - 1; i++) {
        point2D_t p1 = interpolate(kura2[i], pesawat[i], rtick);
        point2D_t p2 = interpolate(kura2[i + 1], pesawat[i + 1], rtick);
        glVertex2f(p1.x, p1.y);
        glVertex2f(p2.x, p2.y);
    }
    glEnd();

#ifdef _WIN32
    Sleep(10);
#else
    usleep(10000);
#endif
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    userDraw();
    glutSwapBuffers();
}

void menu(int option) {
    switch (option) {
    case 1: // Start
        isAnimating = true;
        break;
    case 2: // Reset
        tick = 0;
        isAnimating = false;
        break;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case ' ':  // Tombol Space untuk memulai/menghentikan animasi
        isAnimating = !isAnimating;
        break;
    case 'w':  // Tombol 'w' untuk memperlihatkan perubahan morphing
        morphStep += 0.01f;  // Menambah step perubahan morphing
        if (morphStep > 1.0f) morphStep = 0.0f;  // Kembali ke awal setelah mencapai 1.0
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Project Morphing Obyek");

    glClearColor(0, 0, 0, 0);
    glOrtho(-320, 320, -240, 240, -1, 1);

    glutIdleFunc(display);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutCreateMenu(menu);
    glutAddMenuEntry("Start", 1);
    glutAddMenuEntry("Reset", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);


    glutMainLoop();

    return 0;
}