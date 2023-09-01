#include <iostream>
#include <ctime>

using namespace std;

const int ROW_COUNT = 3;
const int COL_COUNT = 3;

const int CELL_STATE_EMPTY = 0;
const int CELL_STATE_X = 1;
const int CELL_STATE_O = -1;

const int GAME_STATE_O_WON = 0;
const int GAME_STATE_X_WON = 1;
const int GAME_STATE_DRAW = 2;
const int GAME_STATE_NOT_FINISHED = 3;

int board[ROW_COUNT][COL_COUNT];

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

void makeBotTurn() {

}

void printBoard() {
    cout << "---------" << endl;
    for (int i = 0; i < ROW_COUNT; i++) {
        cout << "| ";
        for (int j = 0; j < COL_COUNT; j++) {
            if (board[i][j] == 1)
                cout << "X ";
            else if (board[i][j] == -1)
                cout << "Y ";
            else
                cout << "  ";
        }
        cout << "|" << endl;
    }
    cout << "---------" << endl;
}

int checkGameState() {
    return 0;
}

void printGameState(int gameState) {
    switch (gameState) {
        case 0:
            cout << "O has won!\n\n";
            break;
        case 1:
            cout << "X has won!\n\n";
            break;
        case 2:
            cout << "Draw!\n\n";
            break;
        default:
            cout << "Error\n\n";
    }
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
            break;
        }
    }
}

void startGameRound() {
    cout << "Starting new game" << endl;

    for (int i = 0; i < ROW_COUNT; i++)
        for (int j = 0; j < COL_COUNT; j++)
            board[i][j] = CELL_STATE_EMPTY;

    startGameLoop();
}

int main() {
    while (true) {
        startGameRound();
    }
    return 0;
}
