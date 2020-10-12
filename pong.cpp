#include <iostream>
#include <time.h>
#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

void initTermios(termios& oldTio, termios& newTio);
void resetTermios(termios& oldTio);
int kbhit();

enum Direction{
    STOP = 0,
    LEFT = 1,
    UPLEFT = 2,
    DOWNLEFT = 3,
    RIGHT = 4,
    UPRIGHT = 5,
    DOWNRIGHT = 6
};

class Ball {
    private:
        int x, y;
        int originalX, originalY;
        Direction direction;
    public:
        Ball(int posX, int posY) {
            originalX = posX;
            originalY = posY;
            x = posX; y = posY;
            direction = STOP;
        }
        void reset() {
            x = originalX; y = originalY;
            direction = STOP;
        }
        void changeDirection(Direction d) {
            direction = d;
        }
        void randomDirection() {
            direction = (Direction)((rand() % 6) + 1);
        }
        inline int getX() {
            return x;
        }
        inline int getY() {
            return y;
        }
        inline Direction getDirection() {
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

class Paddle {
    private:
        int x, y;
        int originalX, originalY;
    public:
        Paddle() {
            x = y = 0;
        }
        Paddle(int posX, int posY) : Paddle() {
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

class GameManager {
    private:
        int width, height;
        int score1, score2;
        char up1, down1, up2, down2;
        bool quit;
        Ball *ball;
        Paddle *player1;
        Paddle *player2;
    public:
        GameManager(int w, int h) {
            srand(time(NULL));
            quit = false;
            up1 = 'w'; up2 = 'i';
            down1 = 's'; down2 = 'k';
            score1 = score2 = 0;
            width = w; height = h;
            ball = new Ball(w/2, h/2);
            player1 = new Paddle(1, h/2 - 3);
            player2 = new Paddle (w - 2, h/2 -3);
        }
        ~GameManager() {
            delete ball, player1, player2;
        }
        void scoreUp(Paddle *player) {
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
                        cout << "o"; // ball
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

            if (kbhit()) {
                char current = getchar();
                if (current ==  up1) {
                    if (player1Y > 0) {
                        player1 -> moveUp();
                    }
                }
                if (current ==  down1) {
                    if (player1Y + 4 < height) {
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
                        player2 -> moveDown();
                    }
                }
                
                if (ball -> getDirection() == STOP) {
                    ball -> randomDirection();
                }

                if (current == 'q') {
                    quit = true;
                }
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
                        ball -> changeDirection((Direction)((rand() % 3) + 4));
                    }
                }
            }
            // right paddle
            for (int i = 0; i < 4; i++) {
                if (ballX >= player2X - 1) {
                    if (ballY == player2Y + i) {
                        ball -> changeDirection((Direction)((rand() % 3) + 1));
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
                usleep(50000);
            }
            system("clear");
        }
};

/* Initialize new terminal i/o settings */
void initTermios(termios& oldTio, termios& newTio) {
    // get the terminal settings for stdin
    tcgetattr(STDIN_FILENO, &oldTio);
    // make new settings same as old settings
    newTio = oldTio;
    // disable buffered i/o 
    newTio.c_lflag &= ~ICANON; 
    // set no echo mode
    newTio.c_lflag &= ~ECHO; 
    // use these new terminal i/o settings
    tcsetattr(STDIN_FILENO, TCSANOW, &newTio); 
}

/* Restore old terminal i/o settings */
void resetTermios(termios& oldTio) {
  tcsetattr(STDIN_FILENO, TCSANOW, &oldTio);
}

/* Returns int indicating if a key is being pressed */
int kbhit() {
    int oldFlags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldFlags | O_NONBLOCK);
 
    int ch = getchar();
 
    fcntl(STDIN_FILENO, F_SETFL, oldFlags);
 
    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
 
    return 0;
}

int main() {
    struct termios oldTio, newTio;
    // initialize new terminal settings
    initTermios(oldTio, newTio);

    // run the game
    GameManager c(87, 20);
    c.run();

    // restore the former terminal settings
    resetTermios(oldTio);

    // end program
    return 0;
}