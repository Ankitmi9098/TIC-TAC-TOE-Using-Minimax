#include <bits/stdc++.h>

using namespace std;

#define COMPUTER 1
#define HUMAN 2
#define SIDE 3 // 3*3 matrix
#define COMPUTERMOVE '0'
#define HUMANMOVE 'X'
#define defaultCellVal '#'

void showBoard(char board[][SIDE])
{
    for (int i = 0; i < SIDE; i++)
    {
        cout << "\t\t\t";
        for (int j = 0; j < SIDE; j++)
        {
            cout << board[i][j];
            if (j != SIDE - 1)
            {
                cout << " | ";
            }
        }
        cout << endl;
        if (i != 2)
        {
            cout << "\t\t\t----------" << endl;
        }
    }
}

void initializeBoard(char board[][SIDE])
{
    for (int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++)
        {
            board[i][j] = defaultCellVal;
        }
    }
}

void showInstructions()
{
    cout << "\n Choose the cell from 1 to 9 as shown below and play" << endl;
    int k = 1;
    for (int i = 0; i < SIDE; i++)
    {
        cout << "\t\t\t";
        for (int j = 0; j < SIDE; j++)
        {
            cout << k;
            k++;
            if (j != SIDE - 1)
            {
                cout << " | ";
            }
        }
        cout << endl;
        if (i != 2)
        {
            cout << "\t\t\t----------" << endl;
        }
    }
}

void declareWinner(int whoseTurn)
{
    if (whoseTurn == COMPUTER)
    {
        cout << "Computer has WON  " << endl; // whoseTurn == 1
    }
    else
    {
        cout << "Human has WON  " << endl; // whoseTurn == 2
    }
}

bool rowCrossed(char board[][SIDE])
{
    for (int i = 0; i < SIDE; i++)
    {
        if (board[i][0] != defaultCellVal && board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            return true;
        }
    }
    return false;
}

bool columnCrossed(char board[][SIDE])
{
    for (int i = 0; i < SIDE; i++)
    {
        if (board[0][i] != defaultCellVal && board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            return true;
        }
    }
    return false;
}

bool diagonalCrossed(char board[][SIDE])
{
    if (board[0][0] != defaultCellVal && board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        return true;
    }
    else if (board[0][2] != defaultCellVal && board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        return true;
    }
    return false;
}

bool gameOver(char board[][SIDE])
{
    if (rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board))
    {
        return true;
    }
    return false;
}

// isAI true means last move was of COMPUTER and we are searching what is the best move that human can play.
int minimax(char board[][SIDE], int depth, bool isAI)
{
    int score = 0;
    int bestScore = 0;
    if (gameOver(board) == true)
    {
        if (isAI == true)
        { // this is computer's chance  and the  game was finished in the last chance. so Human Won
            return -10;
        }
        else
            return 10; // AI won
    }
    else
    {
        if (depth < 9)
        {
            // Computer Move
            if (isAI == true)
            {
                bestScore = -999;
                for (int i = 0; i < SIDE; i++)
                {
                    for (int j = 0; j < SIDE; j++)
                    {
                        if (board[i][j] == '#')
                        {
                            board[i][j] = COMPUTERMOVE;
                            score = minimax(board, depth + 1, false);
                            board[i][j] = '#';
                            if (score > bestScore)
                            {
                                bestScore = score;
                            }
                        }
                    }
                }
                return bestScore;
            }
            else
            {
                bestScore = 999;
                for (int i = 0; i < SIDE; i++)
                {
                    for (int j = 0; j < SIDE; j++)
                    {
                        if (board[i][j] == defaultCellVal)
                        {
                            board[i][j] = HUMANMOVE;
                            score = minimax(board, depth + 1, true);
                            board[i][j] = defaultCellVal;
                            if (score < bestScore)
                            {
                                bestScore = score;
                            }
                        }
                    }
                }
                return bestScore;
            }
        }
        else
        {
            return 0;
        }
    }
}

int bestMove(char board[][SIDE], int moveIndex)
{
    int x = -1, y = -1;
    int score = 0, bestScore = -999;
    for (int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++)
        {
            if (board[i][j] == defaultCellVal)
            {
                board[i][j] = COMPUTERMOVE;
                score = minimax(board, moveIndex + 1, false);
                board[i][j] = defaultCellVal;
                if (score > bestScore)
                {
                    x = i;
                    y = j;
                    bestScore = score;
                }
            }
        }
    }
    return x * 3 + y;
}

void playTicTacToe(int whoseTurn)
{
    char board[SIDE][SIDE];
    initializeBoard(board);
    showInstructions();

    int moveIndex = 0, x = 0, y = 0;

    while (gameOver(board) == false && moveIndex < SIDE * SIDE)
    {
        int n;
        if (whoseTurn == COMPUTER)
        {
            n = bestMove(board, moveIndex);
            x = n / SIDE;
            y = n % SIDE;
            board[x][y] = COMPUTERMOVE;
            cout << "\nComputer has put a " << COMPUTERMOVE << " in the cell " << n + 1 << endl;
            showBoard(board);
            moveIndex++;
            whoseTurn = HUMAN;
        }
        else if (whoseTurn == HUMAN)
        {
            cout << "\nYou can insert in the following positions: ";
            for (int i = 0; i < SIDE; i++)
            {
                for (int j = 0; j < SIDE; j++)
                {
                    if (board[i][j] == defaultCellVal)
                    {
                        cout << (i * 3) + j + 1 << " ";
                    }
                }
            }
            cout << endl;
            cout << "\nEnter the position where you want to mark your move:" << endl;
            cin >> n;
            n--;
            x = n / SIDE;
            y = n % SIDE;
            if (n < 0 || n >= 9)
            {
                cout << "\nInvalid Position!!! " << endl;
            }
            else if (board[x][y] != defaultCellVal)
            {
                cout << "\n Position is already occupied, select any other position.";
            }
            else if (board[x][y] == defaultCellVal)
            {
                board[x][y] = HUMANMOVE;
                cout << "\nHuman has put a " << HUMANMOVE << " in the position " << n << endl;
                showBoard(board);
                moveIndex++;
                whoseTurn = COMPUTER;
            }
        }
    }
    if (gameOver(board) == false && moveIndex == SIDE * SIDE)
    {
        cout << "\nIts a draw!!!" << endl;
    }
    else
    {
        if (whoseTurn == COMPUTER)
        {
            whoseTurn = HUMAN;
        }
        else
        {
            whoseTurn = COMPUTER;
        }
        declareWinner(whoseTurn);
    }
}

int main()
{
    cout << "\n ***************TIC TIC TOE***************" << endl;
    char cont = 'y';
    do
    {
        char choice;
        cout << "\nDo you want to start first(y/n): " << endl;
        cin >> choice;
        if (choice == 'y' || choice == 'Y')
        {
            playTicTacToe(HUMAN);
        }
        else if (choice == 'n' || choice == 'N')
        {
            playTicTacToe(COMPUTER);
        }
        else
        {
            cout << "\nPlease enter valid Input" << endl;
        }
        cout << "Do you want to quit game (y/n): ";
        cin >> cont;
    } while (cont == 'n');
    return 0;
}