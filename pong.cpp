#include <iostream>
#include <time.h>
#include <curses.h>
#include <unistd.h>
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
                    x -= 2;
                    break;
                case UPLEFT:
                    x--; y --;
                    break;
                case DOWNLEFT:
                    x--; y++;
                    break;
                case RIGHT:
                    x += 2;
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

                    if (j == 0) {
                        cout << "#";
                    }

                    if (ballX == j && ballY == i) {
                        cout << "O"; // ball
                    } else if (player1X == j && player1Y == i) {
                        cout << "|"; // player1
                    } else if (player1X == j && player1Y + 1 == i) {
                        cout << "|"; // player1
                    } else if (player1X == j && player1Y + 2 == i) {
                        cout << "|"; // player1
                    } else if (player1X == j && player1Y + 3  == i) {
                        cout << "|"; // player1
                    } else if (player2X == j && player2Y == i) {
                        cout << "|"; // player2
                    } else if (player2X == j && player2Y + 1 == i) {
                        cout << "|"; // player2
                    } else if (player2X == j && player2Y + 2 == i) {
                        cout << "|"; // player2
                    } else if (player2X == j && player2Y + 3 == i) {
                        cout << "|"; // player2
                    } else {
                        cout << " ";
                    }

                    if (j == width - 1) {
                        cout << "#";
                    }
                }
                cout << endl;
            }

            for (int i = 0; i < width + 2; i++) {
                cout << "#";
            }
            cout << endl;

            cout << "Score 1: " << score1 << endl << "Score 2: " << score2 << endl;
        }
        void input() {
            ball -> move();

            int player1Y = player1 -> getY();
            int player2Y = player2 -> getY();

            char current = getch();
            if (current ==  up1) {
                if (player1Y > 0) {
                    player1 -> moveUp();
                }
            }
            if (current ==  down1) {
                if (player2Y + 4 < height) {
                    player1 -> moveDown();
                }
            }
            if (current ==  up2) {
                if (player2Y > 0) {
                    player2 -> moveUp();
                }
            }
            if (current ==  down2) {
                if (player2Y + 4 < height) {
                    player1 -> moveDown();
                }
            }
                

            if (ball -> getDirection() == STOP) {
                ball -> randomDirection();
            }

            if (current == 'q') {
                quit = true;
            }
        }
        void logic() {
            int ballX = ball -> getX();
            int ballY = ball -> getY();
            int player1X = player1 -> getX();
            int player1Y = player1 -> getY();
            int player2X = player2 -> getX();
            int player2Y = player2 -> getY();

            // left paddle
            for (int i = 0; i < 4; i++) {
                if (ballX <= player1X + 1) {
                    if (ballY == player1Y + i) {
                        ball -> changeDirection((eDir)((rand() % 3) + 4));
                    }
                }
            }
            // right paddle
            for (int i = 0; i < 4; i++) {
                if (ballX >= player2X - 1) {
                    if (ballY == player2Y + i) {
                        ball -> changeDirection((eDir)((rand() % 3) + 1));
                    }
                }
            }

            // bottom wall
            if (ballY >= height - 1) {
                ball -> changeDirection(ball -> getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);
            }
            // top wall
            if (ballY <= 0) {
                ball -> changeDirection(ball -> getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
            }
            // right wall
            if (ballX >= width - 1) {
                scoreUp(player1);
            }
            // left wall
            if (ballX <= 0) {
                scoreUp(player2);
            }
        }
        void run() {
            while (!quit) {
                draw();
                input();
                logic();
                usleep(75000);
            }
        }
};

int main() {
    cGameManager c(87, 20);
    c.run();
    return 0;
}