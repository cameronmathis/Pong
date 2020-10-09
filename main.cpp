#include <iostream>
#include <time.h>
using namespace std;

enum eDir{
    STOP = 0,
    LEFT = 1,
    UPLEFT = 2,
    DOWNLEFT = 3,
    RIGHT = 4,
    UPRIGHT = 5,
    DOWNRIGHT = 6
};

class cBall {
    private:
        int x, y;
        int originalX, originalY;
        eDir direction;
    public:
        cBall(int posX, int posY) {
            originalX = posX;
            originalY = posY;
            x = posX; y = posY;
            direction = STOP;
        }
        void reset() {
            x = originalX; y = originalY;
            direction = STOP;
        }
        void changeDirection(eDir d) {
            direction = d;
        }
        void randomDirection() {
            direction = (eDir)((rand() % 6) + 1);
        }
        inline int getX() {
            return x;
        }
        inline int getY() {
            return y;
        }
        inline eDir getDirection() {
            return direction;
        }
        void move() {
            switch(direction){
                case STOP:
                    break;
                case LEFT:
                    x--;
                    break;
                case UPLEFT:
                    x--; y --;
                    break;
                case DOWNLEFT:
                    x--; y++;
                    break;
                case RIGHT:
                    x++;
                    break;
                case UPRIGHT:
                    x++; y--;
                    break;
                case DOWNRIGHT:
                    x++; y++;
                    break;
                default:
                    break;
            }
        }
};

class cPaddle {
    private:
        int x, y;
        int originalX, originalY;
    public:
        cPaddle() {
            x = y = 0;
        }
        cPaddle(int posX, int posY) : cPaddle() {
            originalX = posX;
            originalY = posY;
            x = posX;
            y = posY;
        }
        inline void reset() {
            x = originalX; y = originalY;
        }
        inline int getX() {
            return x;
        }
        inline int getY() {
            return y;
        }
        inline void moveUp() {
            y--;
        }
        inline void moveDown() {
            y++;
        }
};

class cGameManager {
    private:
        int width, height;
        int score1, score2;
        char up1, down1, up2, down2;
        bool quit;
        cBall *ball;
        cPaddle *player1;
        cPaddle *player2;
    public:
        cGameManager(int w, int h) {
            srand(time(NULL));
            quit = false;
            up1 = 'w'; up2 = 'i';
            down1 = 's'; down2 = 'k';
            score1 = score2 = 0;
            width = w; height = h;
            ball = new cBall(w/2, h/2);
            player1 = new cPaddle(1, h/2 - 3);
            player2 = new cPaddle (w - 2, h/2 -3);
        }
        ~cGameManager() {
            delete ball, player1, player2;
        }
        void scoreUp(cPaddle *player) {
            if (player == player1) {
                score1++;
            } else if (player == player2) {
                score2++;
            }

            ball -> reset();
            player1 -> reset();
            player2 -> reset();
        }
        void draw() {
            system("clear");
            for (int i = 0; i < width + 2; i++) {
                cout << "#";
            }
            cout << endl;

            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    int ballX = ball -> getX();
                    int ballY = ball -> getY();
                    int player1X = player1 -> getX();
                    int player1Y = player1 -> getY();
                    int player2X = player2 -> getX();
                    int player2Y = player2 -> getY();
                }
            }

            for (int i = 0; i < width + 2; i++) {
                cout << "#";
            }
            cout << endl;
        }
};

int main() {
    cGameManager c(40, 20);
    c.draw();
    return 0;
}