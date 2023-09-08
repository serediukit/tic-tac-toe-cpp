#include <iostream>
#include <ctime>

using namespace std;

const int GAME_DIFFICULTY_EASY = 0;
const int GAME_DIFFICULTY_NORMAL = 1;
const int GAME_DIFFICULTY_HARD = 2;

const int ROW_COUNT = 3;
const int COL_COUNT = 3;

const int CELL_STATE_EMPTY = 0;
const int CELL_STATE_X = 1;
const int CELL_STATE_O = -1;

const int GAME_STATE_O_WON = 0;
const int GAME_STATE_X_WON = 1;
const int GAME_STATE_DRAW = 2;
const int GAME_STATE_NOT_FINISHED = 3;

int gameDifficulty = 0;
int playerScore = 0;
int botScore = 0;

int board[ROW_COUNT][COL_COUNT];

int checkGameState() {
    int sum[8] = { 0 };

    for (int i = 0; i < ROW_COUNT; i++) {
        for (int j = 0; j < COL_COUNT; j++) {
            sum[i] += board[i][j];
            sum[j + 3] += board[i][j];
        }

        sum[6] += board[i][i];
        sum[7] += board[i][2 - i];
    }

    for (int i = 0; i < 8; i++) {
        if (sum[i] == 3)
            return GAME_STATE_X_WON;
        if (sum[i] == -3)
            return GAME_STATE_O_WON;
    }

    for (int i = 0; i < ROW_COUNT; i++) {
        for (int j = 0; j < COL_COUNT; j++) {
            if (board[i][j] == CELL_STATE_EMPTY)
                return GAME_STATE_NOT_FINISHED;
        }
    }

    return GAME_STATE_DRAW;
}

void makePlayerTurn() {
    while (true) {
        cout << "Input 2 digits (row and column) between 1 and 3: ";
        int row, col;
        cin >> row >> col;

        if (row < 1 || row > ROW_COUNT || col < 1 || col > COL_COUNT) {
            cout << "Incorrect input!!!" << endl;
        } else if (board[row - 1][col - 1] != CELL_STATE_EMPTY) {
            cout << "The cell is not empty!!!" << endl;
        } else {
            board[row - 1][col - 1] = CELL_STATE_X;
            return;
        }
    }
}

void makeEasyBotTurn() {
    while (true) {
        int row = rand() % ROW_COUNT;
        int col = rand() % COL_COUNT;

        if (board[row][col] == CELL_STATE_EMPTY) {
            board[row][col] = CELL_STATE_O;
            break;
        }
    }
}

void makeNormalBotTurn() {
    for (int i = 0; i < ROW_COUNT; i++) {
        for (int j = 0; j < COL_COUNT; j++) {
            if (board[i][j] == CELL_STATE_EMPTY) {
                board[i][j] = CELL_STATE_X;
                if (checkGameState() == GAME_STATE_X_WON) {
                    board[i][j] = CELL_STATE_EMPTY;
                    int chance = rand() % 10;
                    if (chance >= 3) {
                        board[i][j] = CELL_STATE_O;
                    } else {
                        makeEasyBotTurn();
                    }
                    return;
                }
                board[i][j] = CELL_STATE_EMPTY;
            }
        }
    }
    makeEasyBotTurn();
}

void makeHardBotTurn() {
    for (int i = 0; i < ROW_COUNT; i++) {
        for (int j = 0; j < COL_COUNT; j++) {
            if (board[i][j] == CELL_STATE_EMPTY) {
                board[i][j] = CELL_STATE_X;
                if (checkGameState() == GAME_STATE_X_WON) {
                    board[i][j] = CELL_STATE_O;
                    return;
                }
                board[i][j] = CELL_STATE_EMPTY;
            }
        }
    }
    makeEasyBotTurn();
}

void makeBotTurn() {
    cout << "Bot's turn\n";
    switch (gameDifficulty) {
        case GAME_DIFFICULTY_EASY:
            makeEasyBotTurn();
            break;
        case GAME_DIFFICULTY_NORMAL:
            makeNormalBotTurn();
            break;
        case GAME_DIFFICULTY_HARD:
            makeHardBotTurn();
            break;
    }
}

void printBoard() {
    cout << "+-------+" << endl;
    for (int i = 0; i < ROW_COUNT; i++) {
        cout << "| ";
        for (int j = 0; j < COL_COUNT; j++) {
            if (board[i][j] == 1)
                cout << "X ";
            else if (board[i][j] == -1)
                cout << "O ";
            else
                cout << "  ";
        }
        cout << "|" << endl;
    }
    cout << "+-------+" << endl;
}

void printGameState(int gameState) {
    switch (gameState) {
        case 0:
            cout << "O has won!\n";
            break;
        case 1:
            cout << "X has won!\n";
            break;
        case 2:
            cout << "Draw!\n";
            break;
        default:
            cout << "Error\n";
    }
}

void printGameScore(int gameState) {
    switch (gameState) {
        case 0:
            botScore++;
            break;
        case 1:
            playerScore++;
            break;
        case 2:
            playerScore++;
            botScore++;
            break;
        default:
            cout << "Error\n\n";
    }
    cout << "Player - " << playerScore << " : " << botScore << " - Bot\n\n";
}

void startGameLoop() {
    bool playerTurn = true;

    while (true) {
        if (playerTurn) {
            makePlayerTurn();
            printBoard();
        } else {
            makeBotTurn();
            printBoard();
        }

        playerTurn = !playerTurn;

        int gameState = checkGameState();
        if (gameState != GAME_STATE_NOT_FINISHED) {
            printGameState(gameState);
            printGameScore(gameState);
            system("PAUSE");
            break;
        }
    }
}

void startGameRound() {
    system("CLS");
    cout << "Starting new game" << endl;

    for (int i = 0; i < ROW_COUNT; i++)
        for (int j = 0; j < COL_COUNT; j++)
            board[i][j] = CELL_STATE_EMPTY;

    printBoard();

    startGameLoop();
}

int main() {
    cout << "Choose your difficulty:\n";
    cout << "1. Easy\n";
    cout << "2. Normal\n";
    cout << "3. Hard\n";
    cin >> gameDifficulty;
    gameDifficulty--;

    while (true) {
        startGameRound();
    }

    return 0;
}
