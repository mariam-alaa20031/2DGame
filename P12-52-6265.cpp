#include <stdio.h>
#include <math.h>
#include <string.h>
#include <random>
#include <glut.h>
#include <math.h>
#include <Windows.h>

void AnimCollect(void);
void drawRect(int x, int y, int w, int h);
void drawHealth();
void drawPlayer(float r, int w, int h);
void drawCircle(int x, int y, float r);
void drawBorder(int x, int y, int w, int h);
void drawBackGround();
void drawTwoBorders();
void drawTarget();
void drawTimer();
void drawLineVertical(int x, int y, int h);
void drawLineHorizontal(int x, int y, int h);
void drawFixedCollectibles(int x, int y);
bool ObstacleCollision(int playerXLeft, int playerXRight, int playerYBottom, int playerYTop);
bool targetCollide(int playerXLeft, int playerXRight, int playerYBottom, int playerYTop);
bool collectibleCollision(int playerXLeft, int playerXRight, int playerYBottom, int playerYTop);
bool powerUps1Collide(int playerXLeft, int playerXRight, int playerYBottom, int playerYTop);
bool powerUps2Collide(int playerXLeft, int playerXRight, int playerYBottom, int playerYTop);
void drawFiveCollectibles();
void drawFourObstacles();
void drawTriangle(int x, int y, int w, int h);
void drawSmile(int x, int y, int w, int h);
void drawScore();
void soundWin();
void hitTargetSound();
void soundGameWon(int value);
void soundBackground();
void powerSound();
void drawCircleOutline();
void print(int x, int y, char* string);
void GenerateLocPowerUps();
void drawP(int x, int y, float r);
void drawPowerUps();
void drawPowerUp1();
void drawPowerUp2();
void removeCollectible();
void soundHit();
void Key(int key, int x, int y);
void soundLose();
void repeatSound(int value);
void SpecialKeyUp(int key, int x, int y);
void Timer(int value);
void Display();
//-----------------


//  Global Variables

int playerXMid = 400;       //center player x
int playerYMid = 400;        //center player y
int playerXRight = 422;     // right boundary
int playerXLeft = 378;      //left boundary
int playerYTop = 422;       //top boundary
int playerYBottom = 378;    // bottom boundary
bool inMotion = false;     //checks if I'm moving or not
int rotateState = 0;      // sets rotation angle wana bat7arak depending on key pressed
int obstaclesXmin[] = { 150,300,500,600 };
int obstaclesXmax[] = { 190,340,540,640 };
int obstaclesYmax[] = { 590,340,540,290 };
int obstaclesYmin[] = { 550,300,500,250 };
int collectiblesXmin[] = { -1,-1,-1,-1,-1 ,-1,-1,-1,-1,-1 };
int collectiblesXmax[] = { -1,-1,-1,-1 ,-1,-1,-1,-1,-1,-1 };
int collectiblesYmin[] = { -1,-1,-1,-1 ,-1,-1,-1,-1 ,-1,-1 };
int collectiblesYmax[] = { -1,-1,-1,-1 ,-1,-1,-1,-1 ,-1,-1 };
int translateBack = 0;
int power1Xmin;
int power1Xmax;
int power1Ymin;
int power1Ymax;
int power2Xmin;
int power2Xmax;
int power2Ymin;
int power2Ymax;
int currHealth = 5;
int collectNumbers = 0;
int powerUps = 0;
int score = 0;
int posCollision = -1;
int startTime = 0;
int duration = 30;
int rotationAngle = 0;
bool power1Effect = false;
bool power2Effect = false;
int freezeTime = 0;
int extraTime1 = 0; //3amla problem
float scaling = 1;
float scaling2 = 1;
bool start = false;
int powerUp = -1;
int translateX = 0;
bool removePower1 = false;
bool removePower2 = false;
bool powerUpsGenerated = false;
bool gameWin = false;
bool targetReached = false; //checks if reached target or not;
bool backgroundSoundPlaying = true;
DWORD backgroundSoundPosition = 0;
DWORD soundDuration = 18000; // Adjust as needed
DWORD soundStartTime = 0;

GLfloat colorOutline = 1;
GLfloat colorWire1 = 0;
GLfloat colorWire2 = 0;
GLfloat colorWire3 = 0;
const wchar_t* correct = L"C:\\Sounds\\correct.wav";
const wchar_t* impact = L"C:\\Sounds\\impact.wav";
const wchar_t* gameLose = L"C:\\Sounds\\gameLose.wav";
const wchar_t* powerTime = L"C:\\Sounds\\effectTimer.wav";
const wchar_t* gameWinSound = L"C:\\Sounds\\gameWin.wav";
const wchar_t* background = L"C:\\Sounds\\background.wav";
const wchar_t* target = L"C:\\Sounds\\target.wav";
//-----------------



void main(int argc, char** argr) {
    glutInit(&argc, argr);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(150, 150);
    glutCreateWindow("Game");
    glutDisplayFunc(Display);
    glutSpecialFunc(Key);
    glutSpecialUpFunc(SpecialKeyUp);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutTimerFunc(1000, Timer, 0);
    if (startTime < duration) {
        soundBackground();
    }
    glClearColor(1, 1, 1, 0);
    gluOrtho2D(0, 800, 0, 800);
    glutIdleFunc(AnimCollect);
    srand((unsigned int)time(NULL));
    glutMainLoop();
}

void drawRect(int x, int y, int w, int h) {
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}

void drawBackGround() {
    glPushMatrix();
    glTranslatef(translateBack, 0, 0);
    // glColor3f(0, 0.8, 0);
    glColor3f(1, 1, 1);
    drawCircle(737.5, 75, 10);
    glPopMatrix();
}

void drawTwoBorders() {
    glColor3f(1, 1, 1);
    drawBorder(50, 50, 700, 700);  //draw inner border    from (50,50) to (50,750) & (750,750) & (750,50)
    drawBorder(15, 15, 760, 760); //draw outer border    from (25,25) to (25,775) & (775,775) & (775,50)

}

void drawObstacles(int x, int y, int w, int h) {
    glColor3f(0.863f, 0.078f, 0.235f);
    drawRect(x, y, w, h);
    glColor3f(0, 0, 0);
    drawBorder(x, y, w, h);
}

void drawCollectibles() {

    glColor3f(1.0f, 0.8f, 0.0f);
    bool generateValid = false;
    int x, y;

    while (!generateValid) {
        x = 51 + (float)rand() / RAND_MAX * (700 - 51);
        y = 51 + (float)rand() / RAND_MAX * (650 - 51);
        bool collide = false;
        int xRight = x + 40;
        int yTop = y + 40;
        bool inRangeX = (x <= playerXLeft && xRight >= playerXLeft) || (x >= playerXLeft && xRight <= playerXRight) || (xRight >= playerXRight && x <= playerXRight);
        bool inRangeY = (y <= playerYBottom && yTop >= playerYBottom) || (y >= playerYBottom && yTop <= playerYTop) || (yTop >= playerYTop && y <= playerYTop);
        // collectible overlaps with player position

        if ((xRight >= playerXLeft && x <= playerXRight && yTop >= playerYBottom && y <= playerYTop) || (inRangeX && inRangeY)) {
            collide = true;
        }
        bool inRangeXTarget = (x <= 60 && xRight >= 60) || (x >= 60 && xRight <= 125) || (xRight >= 125 && x <= 125);
        bool inRangeYTarget = (y <= 60 && yTop >= 105) || (y >= 60 && yTop <= 105) || (yTop >= 105 && y <= 105);
        // collectible overlaps with the target
        if ((xRight >= 60 && x <= 125 && yTop >= 60 && y <= 105) || (inRangeXTarget && inRangeYTarget)) {
            collide = true;
        }

        for (int i = 0; i < 4; i++) {
            bool inRangeXObs = (x <= obstaclesXmin[i] && xRight >= obstaclesXmin[i]) || (x >= obstaclesXmin[i] && xRight <= obstaclesXmax[i]) || (xRight >= obstaclesXmax[i] && x <= obstaclesXmax[i]);
            bool inRangeYObs = (y <= obstaclesYmin[i] && yTop >= obstaclesYmax[i]) || (y >= obstaclesYmin[i] && yTop <= obstaclesYmax[i]) || (yTop >= obstaclesYmax[i] && y <= obstaclesYmax[i]);
            if ((xRight >= obstaclesXmin[i] && x <= obstaclesXmax[i] && yTop >= obstaclesYmin[i] && y <= obstaclesYmax[i]) || (inRangeXObs && inRangeYObs)) {
                collide = true;
                break;
            }

        }

        for (int i = 0; i < collectNumbers; i++) {
            bool inRangeXCollect = (x <= collectiblesXmin[i] && xRight >= collectiblesXmin[i]) || (x >= collectiblesXmin[i] && xRight <= collectiblesXmax[i]) || (xRight >= collectiblesXmax[i] && x <= collectiblesXmax[i]);
            bool inRangeYCollect = (y <= collectiblesYmin[i] && yTop >= collectiblesYmax[i]) || (y >= collectiblesYmin[i] && yTop <= collectiblesYmax[i]) || (yTop >= collectiblesYmax[i] && y <= collectiblesYmax[i]);
            if ((xRight >= collectiblesXmin[i] && x <= collectiblesXmax[i] && yTop >= collectiblesYmin[i] && y <= collectiblesYmax[i]) || (inRangeXCollect && inRangeYCollect)) {
                collide = true;
                break;
            }

        }



        if (!collide) {
            generateValid = true;
        }

    }

    // Store the collectible position and increment the count
    collectiblesXmin[collectNumbers] = x;
    collectiblesXmax[collectNumbers] = x + 40;
    collectiblesYmin[collectNumbers] = y;
    collectiblesYmax[collectNumbers] = y + 40;
    collectNumbers++;

    // Draw the collectible
    glColor3f(0.8, 0.6, 0.4);
    drawRect(x, y, 40, 40);
    glColor3f(0.6, 0.4, 0.2);
    drawBorder(x, y, 40, 40);
    glColor3f(1, 1, 1);
    drawBorder(x + 10, y + 10, 20, 20);
    drawLineHorizontal(x + 15, y + 15, 10);
    drawLineVertical(x + 15, y + 15, 10);
    drawLineHorizontal(x + 15, y + 25, 10);
}

void soundBackground() {
    if (startTime < duration && !(power1Effect || power2Effect) && !(currHealth == 0)) {
        PlaySound(background, NULL, SND_FILENAME | SND_ASYNC);
        glutTimerFunc(18000, repeatSound, 0);
    }
}

// Function to play the winning sound.
void soundWin() {
    PlaySound(correct, NULL, SND_FILENAME | SND_ASYNC);
    glutTimerFunc(1000, repeatSound, 0);

}
void repeatSound(int value) {
    if (startTime < duration && !gameWin) {
        soundBackground();
    }

}


void soundHit() {
    PlaySound(impact, NULL, SND_FILENAME | SND_ASYNC);
    if (startTime < duration) {
        glutTimerFunc(1000, repeatSound, 0);
    }

}
void hitTargetSound() {
    PlaySound(target, NULL, SND_FILENAME | SND_ASYNC);
    glutTimerFunc(2000, soundGameWon, 0);
}
void soundGameWon(int value) {
    PlaySound(gameWinSound, NULL, SND_FILENAME | SND_ASYNC);
}
void powerSound() {
    PlaySound(powerTime, NULL, SND_FILENAME | SND_ASYNC);
    glutTimerFunc(5000, repeatSound, 0);
}

void soundLose() {
    PlaySound(gameLose, NULL, SND_FILENAME | SND_ASYNC);
    if (startTime < duration) {
        glutTimerFunc(1000, repeatSound, 0);
    }
}
void GenerateLocPowerUps() {
    bool generateValid = false;
    int x, y;
    while (!generateValid) {
        x = 51 + (float)rand() / RAND_MAX * (700 - 51);
        y = 51 + (float)rand() / RAND_MAX * (650 - 51);
        bool collide = false;
        int xRight = x + 20;
        int yTop = y + 20;
        int xLeft = x - 20;
        int yBottom = y - 20;
        bool inRangeX = (xLeft <= playerXLeft && xRight >= playerXLeft) || (xLeft >= playerXLeft && xRight <= playerXRight) || (xRight >= playerXRight && xLeft <= playerXRight);
        bool inRangeY = (yBottom <= playerYBottom && yTop >= playerYBottom) || (yBottom >= playerYBottom && yTop <= playerYTop) || (yTop >= playerYTop && yBottom <= playerYTop);
        // collectible overlaps with player position

        if ((xRight >= playerXLeft && xLeft <= playerXRight && yTop >= playerYBottom && yBottom <= playerYTop) || (inRangeX && inRangeY)) {
            collide = true;
        }
        bool inRangeXTarget = (xLeft <= 60 && xRight >= 60) || (xLeft >= 60 && xRight <= 125) || (xRight >= 125 && xLeft <= 125);
        bool inRangeYTarget = (yBottom <= 60 && yTop >= 105) || (yBottom >= 60 && yTop <= 105) || (yTop >= 105 && yBottom <= 105);

        if ((xRight >= 60 && xLeft <= 125 && yTop >= 60 && yBottom <= 105) || (inRangeXTarget && inRangeYTarget)) {
            collide = true;
        }
        if ((yBottom < 50 || xRight>750 || yTop > 690 || xLeft < 50))
            collide = true;

        for (int i = 0; i < 4; i++) {
            //    bool inRangeXObs = (xLeft <= obstaclesXmin[i] && xRight >= obstaclesXmin[i]) || (xLeft >= obstaclesXmin[i] && xRight <= obstaclesXmax[i]) || (xRight >= obstaclesXmax[i] && xLeft <= obstaclesXmax[i]);
              //  bool inRangeYObs = (yBottom <= obstaclesYmin[i] && yTop >= obstaclesYmax[i]) || (yBottom >= obstaclesYmin[i] && yTop <= obstaclesYmax[i]) || (yTop >= obstaclesYmax[i] && yBottom <= obstaclesYmax[i]);
            if ((xRight >= obstaclesXmin[i] && xLeft <= obstaclesXmax[i] && yTop >= obstaclesYmin[i] && yBottom <= obstaclesYmax[i])/* || (inRangeXObs && inRangeYObs)*/) {
                collide = true;
                break;
            }

        }

        for (int i = 0; i < collectNumbers; i++) {
            bool inRangeXCollect = (xLeft <= collectiblesXmin[i] && xRight >= collectiblesXmin[i]) || (xLeft >= collectiblesXmin[i] && xRight <= collectiblesXmax[i]) || (xRight >= collectiblesXmax[i] && xLeft <= collectiblesXmax[i]);
            bool inRangeYCollect = (y <= collectiblesYmin[i] && yTop >= collectiblesYmax[i]) || (yBottom >= collectiblesYmin[i] && yTop <= collectiblesYmax[i]) || (yTop >= collectiblesYmax[i] && yBottom <= collectiblesYmax[i]);
            if ((xRight >= collectiblesXmin[i] && xLeft <= collectiblesXmax[i] && yTop >= collectiblesYmin[i] && yBottom <= collectiblesYmax[i]) || (inRangeXCollect && inRangeYCollect)) {
                collide = true;
                break;
            }

        }

        for (int i = 0; i < 1; i++) {
            bool inRangeXCollect = (xLeft <= power1Xmin && xRight >= power1Xmin) || (xLeft >= power1Xmin && xRight <= power1Xmax) || (xRight >= power1Xmax && xLeft <= power1Xmax);
            bool inRangeYCollect = (y <= power1Ymin && yTop >= power1Ymax) || (yBottom >= power1Ymin && yTop <= power1Ymax) || (yTop >= power1Ymax && yBottom <= power1Ymax);
            if ((xRight >= power1Xmin && xLeft <= power1Xmax && yTop >= power1Ymin && yBottom <= power1Ymax) || (inRangeXCollect && inRangeYCollect)) {
                collide = true;
                break;
            }

        }

        if (!collide) {
            generateValid = true;
        }
    }
    if (powerUps == 0) {
        power1Xmin = x - 20;
        power1Xmax = x + 20;
        power1Ymin = y - 20;
        power1Ymax = y + 20;
        powerUps++;
    }
    else {
        power2Xmin = x - 20;
        power2Xmax = x + 20;
        power2Ymin = y - 20;
        power2Ymax = y + 20;
        powerUps++;
    }
    // Draw the powerUp
    if (powerUps == 1) {
        drawPowerUp1();
    }
    else {
        drawPowerUp2();
    }
}

void AnimCollect() {

    GLfloat colorChangeRate = 0.001; // Adjust as needed.
    colorOutline -= colorChangeRate;
    colorWire1 -= colorChangeRate;
    colorWire2 -= colorChangeRate;
    colorWire3 -= colorChangeRate;

    // Check if colors have faded completely and reset them.
    if (colorOutline <= 0.1) {
        colorOutline = 1.0;
        colorWire1 = 1.0;
        colorWire2 = 1.0;
        colorWire3 = 1.0; // Reset the start time.
    }
    drawTarget();

    translateBack -= 1;
    if (translateBack <= -675) {
        translateBack = 0;
    }
    drawBackGround();
    scaling2 -= 0.00025;
    if (scaling2 <= 0.7) {
        scaling2 = 1;
    }

    drawFiveCollectibles();

    scaling -= 0.0005;
    if (scaling <= 0.5) {
        scaling = 1;
    }
    drawPowerUps();
    rotationAngle += 1;
    if (rotationAngle > 360) {
        rotationAngle = 0;
    }

    glutPostRedisplay();

}

void drawPowerUps() {
    if (!powerUpsGenerated) {
        GenerateLocPowerUps();
        GenerateLocPowerUps();
        powerUpsGenerated = true;
        return;
    }
    else if (!removePower2 && removePower1) {
        drawPowerUp2();
        return;
    }
    else if (!removePower1 && removePower2) {
        drawPowerUp1();
        return;
    }
    else if (!removePower1 && !removePower2) {
        drawPowerUp1();
        drawPowerUp2();

    }
    else if (removePower1 && removePower2) {
        return;
    }

}

void drawP(int x, int y, float r) {
    glColor3f(1, 1, 1);
    drawLineHorizontal(x, y, 7);
    drawLineHorizontal(x, y - 7, 7);
    drawLineVertical(x + 7, y - 7, 7);
    drawLineVertical(x, y - 14, 14);

}
void drawPowerUp1() { //responsible for giving a five second effect le en el score ye increase
    glPushMatrix();
    glTranslatef(power1Xmin + 20, power1Ymin + 20, 0);
    glRotatef(rotationAngle, 0, 0, 1);
    glTranslatef(-(power1Xmin + 20), -(power1Ymin + 20), 0);
    glColor3f(0.0f, 0.392f, 0.0f);
    drawCircle(power1Xmin + 20, power1Ymin + 20, 20);
    glColor3f(0.0f, 0.5019f, 0.0f);
    drawCircle(power1Xmax - 20, power1Ymax - 20, 15);
    glColor3f(0.1333f, 0.5451f, 0.1333f);
    drawCircle(power1Xmin + 20, power1Ymin + 20, 10);
    glColor3f(0.1961f, 0.8039f, 0.1961f);
    drawCircle(power1Xmin + 20, power1Ymin + 20, 5);
    drawP(power1Xmin + 17, power1Ymax - 15, 20);
    glPopMatrix();
}

void drawPowerUp2() {
    glPushMatrix();
    glTranslatef(power2Xmin + 20, power2Ymin + 20, 0);
    glRotatef(rotationAngle, 0, 0, 1);
    glTranslatef(-(power2Xmin + 20), -(power2Ymin + 20), 0);
    glColor3f(0.8f, 0.333f, 0.0f);

    drawCircle(power2Xmin + 20, power2Ymin + 20, 20);
    glColor3f(1.0f, 0.549f, 0.0f);
    drawCircle(power2Xmax - 20, power2Ymax - 20, 15);
    glColor3f(1.0f, 0.647f, 0.0f);
    drawCircle(power2Xmin + 20, power2Ymin + 20, 10);
    glColor3f(1.0f, 0.702f, 0.278f);
    drawCircle(power2Xmin + 20, power2Ymin + 20, 5);
    drawP(power2Xmin + 17, power2Ymax - 15, 20);
    glPopMatrix();
}
void drawFixedCollectibles(int x, int y) {
    glPushMatrix();
    glTranslatef(x + 20, y + 20, 0);
    glScalef(scaling, scaling, 1);
    glTranslatef(-(x + 20), -(y + 20), 0);
    glColor3f(1.0f, 0.8f, 0.0f);
    drawRect(x, y, 40, 40);
    glColor3f(0.6, 0.4, 0.2);
    drawBorder(x, y, 40, 40);
    glColor3f(1, 1, 1);
    drawBorder(x + 10, y + 10, 20, 20);
    drawLineHorizontal(x + 15, y + 15, 10);
    drawLineVertical(x + 15, y + 15, 10);
    drawLineHorizontal(x + 15, y + 25, 10);
    glPopMatrix();
}

void drawFiveCollectibles() {
    if (!start) {
        drawCollectibles();
        drawCollectibles();
        drawCollectibles();
        drawCollectibles();
        drawCollectibles();
        drawCollectibles();
        drawCollectibles();
        drawCollectibles();
        drawCollectibles();
        drawCollectibles();
        start = true;
    }
    else {
        for (int i = 0; i < collectNumbers; i++) {
            drawFixedCollectibles(collectiblesXmin[i], collectiblesYmin[i]);
        }
    }
}




//not sure

void drawHealth() {
    float scaleX = (float)currHealth / 5;
    glPushMatrix();
    glColor3f(0, 0.5, 0);
    glTranslatef(60, 700, 0);
    glScalef(scaleX, 1, 0);
    glTranslatef(-60, -700, 0);
    drawRect(60, 700, 150, 40);
    glPopMatrix();

}

void drawScore() {
    glColor3f(1, 1, 1);
    char* p0s[20] = { "Score" };
    sprintf((char*)p0s, "Score: %d", score);
    print(230, 710, (char*)p0s);
}


void print(int x, int y, char* string)
{
    int len, i;

    //set the position of the text in the window using the x and y coordinates
    glRasterPos2f(x, y);

    //get the length of the string to display
    len = (int)strlen(string);

    //loop to display character by character
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
    }
}
void drawTriangle(int x, int y, int w, int h) {
    int half = w / 2;
    int halfH = h;
    glBegin(GL_POLYGON);
    glVertex2f(x - half, y - halfH);
    glVertex2f(x + half, y - halfH);
    glVertex2f(x, y);
    glEnd();
}

void drawTarget() {
    glPushMatrix();
    glTranslatef(62.5, 52.5, 0);
    glScalef(scaling2, scaling2, 1);
    glTranslatef(-62.5, -52.5, 0);
    glColor3f(1, 1, 1);
    drawRect(60, 60, 65, 45);
    glColor3f(0, colorOutline, 0);
    drawBorder(62, 62, 60, 40); //outer
    drawBorder(60, 60, 65, 45);  //inner
    glColor3f(colorWire1, colorWire2, colorWire3);
    for (int i = 63; i < 123; i += 4) {
        drawLineVertical(i, 62, 40);
    }
    for (int i = 63; i < 103; i += 4) {
        drawLineHorizontal(62, i, 60);
    }
    glPopMatrix();
}

void drawLineVertical(int x, int y, int h) {
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x, y + h);
    glEnd();

}



void drawLineHorizontal(int x, int y, int w) {
    glBegin(GL_LINES);

    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glEnd();

}

void drawPlayer(float r, int w, int h) {
    int x = playerXMid;
    int y = playerYMid;
    glPushMatrix();
    glTranslatef(playerXMid, playerYMid, 0);
    glRotatef(rotateState, 0, 0, 1);
    glTranslatef(-(playerXMid), -(playerYMid), 0);
    glColor3f(1, 0.8, 0);
    drawCircle(x, y, r);
    glColor3f(0, 0.2, 0);
    drawRect(x - w, y, -w, h);
    drawRect(x + w, y, w, h);
    drawTriangle(x, y, w, h);
    drawSmile(x, y, w, h);
    glPopMatrix();
}



void drawFourObstacles() {

    glColor3f(0.863f, 0.078f, 0.235f);
    drawObstacles(150, 550, 40, 40);
    drawObstacles(600, 250, 40, 40);
    drawObstacles(300, 300, 40, 40);
    drawObstacles(500, 500, 40, 40);
    glBegin(GL_LINES);
    glVertex2f(150, 550);
    glVertex2f(190, 590);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(150, 590);
    glVertex2f(190, 550);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(600, 250);
    glVertex2f(640, 290);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(600, 290);
    glVertex2f(640, 250);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(300, 300);
    glVertex2f(340, 340);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(300, 340);
    glVertex2f(340, 300);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(500, 500);
    glVertex2f(540, 540);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(540, 500);
    glVertex2f(500, 540);
    glEnd();


}
void drawSmile(int x, int y, int w, int h) {
    glBegin(GL_LINE_STRIP);                               //color mouth white
    glVertex2f(x - 2 * w, y - h);
    glVertex2f(x - w, y - 2 * h);
    glVertex2f(x + w, y - 2 * h);
    glVertex2f(x + 2 * w, y - h);
    glEnd();
}
void drawBorder(int x, int y, int w, int h) {
    glBegin(GL_LINE_LOOP); //color border big blue
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}

void drawCircle(int x, int y, float r) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    GLUquadric* quadObj = gluNewQuadric();
    gluDisk(quadObj, 0, r, 50, 50);
    glPopMatrix();
}

void Key(int key, int x, int y) {
    if (currHealth > 0) {
        switch (key) {

        case GLUT_KEY_LEFT:

            if (!(gameWin) && (ObstacleCollision(playerXLeft - 5, playerXRight - 5, playerYBottom, playerYTop) || playerXLeft - 5 < 50)) { //check coll
                currHealth--;
                soundHit();
                break;
            }
            else if (collectibleCollision(playerXLeft - 5, playerXRight - 5, playerYBottom, playerYTop)) {
                if (power1Effect) {
                    score += 20;
                }
                else {
                    score += 10;
                }
                soundWin();
            }
            else if (!removePower1 && powerUps1Collide(playerXLeft - 5, playerXRight - 5, playerYBottom, playerYTop)) {
                powerSound();
                power1Effect = true;  //score zawedo
                powerUp = 1;

            }
            else if (!removePower2 && powerUps2Collide(playerXLeft - 5, playerXRight - 5, playerYBottom, playerYTop)) {
                powerSound();
                power2Effect = true;  //score zawedo
                powerUp = 2;
            }
            else if (startTime < duration && targetCollide(playerXLeft - 5, playerXRight - 5, playerYBottom, playerYTop)) {
                gameWin = true;
                hitTargetSound();
            }

            playerXMid -= 5;
            playerXLeft -= 5;
            playerXRight -= 5;
            inMotion = true;
            rotateState = -90;// Adjust this value for the desired movement amount
            break;
        case GLUT_KEY_RIGHT:
            // Move player to the right (for example, increment playerX
            if (!(gameWin) && (ObstacleCollision(playerXLeft + 5, playerXRight + 5, playerYBottom, playerYTop) || playerXRight + 5 > 750)) { //check coll
                currHealth--;
                soundHit();
                break;
            }
            else if (collectibleCollision(playerXLeft + 5, playerXRight + 5, playerYBottom, playerYTop)) {
                if (power1Effect) {
                    score += 20;
                }
                else {
                    score += 10;
                }
                soundWin();
            }
            else if (!removePower1 && powerUps1Collide(playerXLeft + 5, playerXRight + 5, playerYBottom, playerYTop)) {
                powerSound();
                power1Effect = true;  //score zawedo
                powerUp = 1;
            }
            else if (!removePower2 && powerUps2Collide(playerXLeft + 5, playerXRight + 5, playerYBottom, playerYTop)) {
                powerSound();
                power2Effect = true;  //score zawedo
                powerUp = 2;
            }
            else if (startTime < duration && targetCollide(playerXLeft + 5, playerXRight + 5, playerYBottom, playerYTop)) {
                gameWin = true;
                hitTargetSound();
            }

            playerXMid += 5;
            playerXRight += 5;
            playerXLeft += 5;
            inMotion = true;
            rotateState = 90;// Adjust this value for the desired movement amount
            break;
        case GLUT_KEY_DOWN:
            if (!(gameWin) && (ObstacleCollision(playerXLeft, playerXRight, playerYBottom - 5, playerYTop - 5) || playerYBottom - 5 < 50)) { //check coll
                currHealth--;
                soundHit();
                break;
            }
            else if (collectibleCollision(playerXLeft, playerXRight, playerYBottom - 5, playerYTop - 5)) {
                if (power1Effect) {
                    score += 20;
                }
                else {
                    score += 10;
                }
                soundWin();
            }
            else if (!removePower1 && powerUps1Collide(playerXLeft, playerXRight, playerYBottom - 5, playerYTop - 5)) {
                powerSound();
                power1Effect = true;  //score zawedo
                powerUp = 1;
            }
            else if (!removePower2 && powerUps2Collide(playerXLeft, playerXRight, playerYBottom - 5, playerYTop - 5)) {
                powerSound();
                power2Effect = true;  //score zawedo
                powerUp = 2;
            }
            else if (startTime < duration && targetCollide(playerXLeft, playerXRight, playerYBottom - 5, playerYTop - 5)) {
                gameWin = true;
                hitTargetSound();
            }

            playerYMid -= 5;
            playerYTop -= 5;
            playerYBottom -= 5;
            inMotion = true;
            rotateState = 0;
            break;
        case GLUT_KEY_UP:
            if (!(gameWin) && ObstacleCollision(playerXLeft, playerXRight, playerYBottom + 5, playerYTop + 5) || playerYTop + 5 > 690) { //check coll
                currHealth--;
                soundHit();
                break;
            }
            else if (collectibleCollision(playerXLeft, playerXRight, playerYBottom + 5, playerYTop + 5)) {
                if (power1Effect) {
                    score += 20;
                }
                else {
                    score += 10;
                }
                soundWin();
            }
            else if (!removePower1 && powerUps1Collide(playerXLeft, playerXRight, playerYBottom + 5, playerYTop + 5)) {
                powerSound();
                power1Effect = true;  //score zawedo
                powerUp = 1;
            }
            else if (!removePower2 && powerUps2Collide(playerXLeft, playerXRight, playerYBottom + 5, playerYTop + 5)) {
                powerSound();
                power2Effect = true;  //score zawedo
                powerUp = 2;
            }
            else if (startTime < duration && targetCollide(playerXLeft, playerXRight, playerYBottom + 5, playerYTop + 5)) {
                gameWin = true;
                hitTargetSound();
            }
            playerYMid += 5;
            playerYBottom += 5;
            playerYTop += 5;
            inMotion = true;
            rotateState = 180;


        }
    }

    if (currHealth == 0) {
        gameWin = false;
        soundLose();
        glutPostRedisplay();
    }
    if (posCollision != -1) {
        removeCollectible();
    }
    if (powerUp == 1) {
        removePower1 = true;
    }
    else if (powerUp == 2) {
        removePower2 = true;
    }

    glutPostRedisplay(); // Request a redraw of the scene
}






void SpecialKeyUp(int key, int x, int y) {
    if (key == GLUT_KEY_RIGHT || key == GLUT_KEY_DOWN || key == GLUT_KEY_LEFT || key == GLUT_KEY_UP) {
        rotateState = 0;
        inMotion = false;
    }
    glutPostRedisplay();

}

bool ObstacleCollision(int playerXLeft, int playerXRight, int playerYBottom, int playerYTop) {
    bool collide = false;
    for (int i = 0; i < 4; i++) {
        if ((playerXRight >= obstaclesXmin[i] && playerXLeft <= obstaclesXmax[i] && playerYTop >= obstaclesYmin[i] && playerYBottom <= obstaclesYmax[i])) {
            collide = true;
            break;
        }

    }
    return collide;
}


bool collectibleCollision(int playerXLeft, int playerXRight, int playerYBottom, int playerYTop) {
    bool collide = false;
    bool shift = false;
    for (int i = 0; i < collectNumbers; i++) {
        bool inRangeXObs = (playerXLeft <= collectiblesXmin[i] && playerXRight >= collectiblesXmin[i]) || (playerXLeft >= collectiblesXmin[i] && playerXRight <= collectiblesXmax[i]) || (playerXRight >= collectiblesXmax[i] && playerXLeft <= collectiblesXmax[i]);
        bool inRangeYObs = (playerYBottom <= collectiblesYmin[i] && playerYTop >= collectiblesYmax[i]) || (playerYBottom >= collectiblesYmin[i] && playerYTop <= collectiblesYmax[i]) || (playerYTop >= collectiblesYmax[i] && playerYBottom <= collectiblesYmax[i]);
        if ((playerXRight >= collectiblesXmin[i] && playerXLeft <= collectiblesXmax[i] && playerYTop >= collectiblesYmin[i] && playerYBottom <= collectiblesYmax[i]) || (inRangeXObs && inRangeYObs)) {
            collide = true;
            posCollision = i;
            break;
        }

    }
    return collide;
}

bool powerUps1Collide(int playerXLeft, int playerXRight, int playerYBottom, int playerYTop) {
    bool collide = false;
    if ((playerXRight >= power1Xmin && playerXLeft <= power1Xmax && playerYTop >= power1Ymin && playerYBottom <= power1Ymax)) {
        return true;

    }
    powerUps--;
    return false;
}
bool powerUps2Collide(int playerXLeft, int playerXRight, int playerYBottom, int playerYTop) {
    if ((playerXRight >= power2Xmin && playerXLeft <= power2Xmax && playerYTop >= power2Ymin && playerYBottom <= power2Ymax)) {
        return true;

    }
    powerUps--;
    return false;
}


void removeCollectible() {
    bool shift = false;
    for (int j = 0; j < collectNumbers - 1; j++) {
        if (j == posCollision) {
            shift = true;
        }
        if (shift) {
            collectiblesXmin[j] = collectiblesXmin[j + 1];
            collectiblesXmax[j] = collectiblesXmax[j + 1];
            collectiblesYmin[j] = collectiblesYmin[j + 1];
            collectiblesYmax[j] = collectiblesYmax[j + 1];
        }
    }
    if (posCollision > -1) {
        collectNumbers--;
        posCollision = -1;
    }
}

void Timer(int value) {

    if (startTime <= duration && power1Effect && power2Effect) {
        extraTime1++;
        freezeTime++;
        if (extraTime1 == 5) {
            power1Effect = false;
        }
        if (freezeTime == 5) {
            power2Effect = false;
        }
    }
    else if (startTime <= duration && power1Effect) {
        extraTime1++;
        if (extraTime1 == 5) {
            power1Effect = false;
        }
        startTime++;
    }
    else if (startTime <= duration && power2Effect) {
        freezeTime++;
        if (freezeTime == 5) {
            power2Effect = false;
        }
    }
    else if (startTime <= duration) {
        startTime++;
    }
    drawTimer();
    glutTimerFunc(1000, Timer, 0);
    glutPostRedisplay();

    // Request a redraw of the scene
}


void drawTimer() {
    glColor3f(1, 1, 1);
    if (startTime < 30) {
        char* p0s[10] = { "Time" };
        sprintf((char*)p0s, "Time: %d", 30 - startTime);
        print(550, 710, (char*)p0s);
    }
    else {
        if (startTime == 30 && !gameWin) {
            soundLose();
        }
        char* p0s[11] = { "Timeout" };
        sprintf((char*)p0s, "Timeout");
        print(550, 710, (char*)p0s);
    }
}

bool targetCollide(int playerXLeft, int playerXRight, int playerYBottom, int playerYTop) {
    // player overlaps with the target
    if ((playerXRight > 60 && playerXLeft < 125 && playerYTop >= 60 && playerYBottom < 105)) {
        return true;
    }
    return false;
}






void Display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0.25, 0, 0);
    drawTwoBorders();
    if (gameWin) {
        glColor3f(1, 1, 1);
        char* p0s[20] = { "You Won!" };
        sprintf((char*)p0s, "You Won!");
        print(370, 400, (char*)p0s);

    }
    else if (startTime >= duration && currHealth > 0) {
        glColor3f(0, 0, 0);
        char* p0s[20] = { "Timeout!" };
        sprintf((char*)p0s, "TIMEOUT!");
        print(350, 450, (char*)p0s);
        char* x0s[20] = { "You ran out of time!" };
        sprintf((char*)x0s, "Better Luck Next Time :)");
        print(315, 410, (char*)x0s);
    }
    else if (currHealth == 0) {
        glColor3f(1, 1, 1);
        char* p0s[20] = { "Died!" };
        sprintf((char*)p0s, "X ran out of lives X");
        print(310, 450, (char*)p0s);

    }
    else {

        drawLineHorizontal(50, 690, 700);
        drawFourObstacles();
        drawScore();
        drawCircleOutline();
        drawPlayer(22, 6, 6);//handle appearance only once
        drawHealth();
        drawTimer();
        AnimCollect();
        glColor3f(1, 1, 1);
        char* p0s[20] = { "Target!" };
        sprintf((char*)p0s, "TARGET");
        print(60, 25, (char*)p0s);
        //Note radius is 20--> If you change this CHANGE GLOBAL PARAMS
    }
    glFlush();
}


void drawCircleOutline() {
    glColor3f(1, 1, 1);
    drawBorder(50, 270, 80, 200);//
    drawBorder(670, 270, 80, 200);//
    drawBorder(50, 320, 30, 100);//
    drawBorder(720, 320, 30, 100);//
    drawBorder(50, 50, 350, 640);//
    drawBorder(400, 50, 350, 640);//
    glBegin(GL_LINE_STRIP);
    float radius = 50.0;
    int numSegments = 100;

    for (int i = 0; i <= numSegments; i++) {
        float div = (float)i / numSegments;
        float theta = 2.0f * 3.14 * div;
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex2f(x + 400, y + 370);
    }
    glEnd();
}