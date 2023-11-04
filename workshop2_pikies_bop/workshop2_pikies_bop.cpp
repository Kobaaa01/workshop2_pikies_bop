#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int MAX_WALLS = 100;
const int MAX_TRAPDOORS = 100;
const int MAX_TREASURES = 100;
const int MAX_PLAYERS = 9;
const int MAX_ROWS = 11;
const int MAX_COLUMNS = 11; 

bool guessedPassword[MAX_PLAYERS];
bool pickedUp[MAX_PLAYERS];
bool wonGame[MAX_PLAYERS];
bool lostGame[MAX_PLAYERS];

int playerIds[MAX_PLAYERS];
int playerX[MAX_PLAYERS] = { 0 };
int playerY[MAX_PLAYERS] = { 0 };
// test //
vector<int> trapdoorsX;
vector<int> trapdoorsY;

vector<int> treasuresX;
vector<int> treasuresY;

int wallsX[MAX_WALLS];
int wallsY[MAX_WALLS];

struct Player
{
    int x, y;
    bool guessedPassword = false;
    bool pickedUp = false;
    bool wonGame = false;
    bool lostGame = false;
};
Player player[MAX_PLAYERS];


// Player adding function //
void addPlayer()
{
    for (int j = 0; j < MAX_PLAYERS; j++)
    {
        if (playerIds[j] == 0)
        {
            playerIds[j] = j + 1;
            break;
        }
    }
}
// Player changing function //

void changePlayer(int& activePlayer)
{
    if (activePlayer < 9)
    {
        for (int i = activePlayer; i < MAX_PLAYERS; i++)
        {
            if (!lostGame[i] && playerIds[i] != 0)
            {
                activePlayer = i + 1;
                return;
            }
        }
    }

    for (int j = 0; j < activePlayer - 1; j++)
    {
        if (!lostGame[j] && playerIds[j] != 0)
        {
            activePlayer = j + 1;
            return;
        }
    }
}

// Password guessing function //
void guessPassword(int& activePlayer)
{
    unsigned char password = 123;
    if (!player[activePlayer - 1].guessedPassword)
    {
        bool passwordGuessed = true;
        for (int i = 0; i < 8; i++)
        {
            char charBit;
            cin >> charBit;
            int bitScanned;
            if (charBit == '1')
            {
                bitScanned = 1;
            }
            else
            {
                bitScanned = 0;
            }
            unsigned char flag = 1 << (7 - i);
            unsigned char PasswordAtPosition = password & flag;
            unsigned char PasswordBitAtPosition = PasswordAtPosition >> (7 - i);
            if (PasswordBitAtPosition != bitScanned)
            {
                passwordGuessed = false;
            }
        }
        if (passwordGuessed)
        {
            player[activePlayer - 1].guessedPassword = true;
            cout << "PASSWORD GUESSED" << endl;
        }
        else
        {
            cout << "PASSWORD NOT GUESSED" << endl;
        }
    }
    else
    {
        cout << "PASSWORD ALREADY STATED" << endl;
    }
}
// Player moving function //
void movePlayer(int& activePlayer)
{
    char direction;
    cin >> direction;
    if (player[activePlayer - 1].guessedPassword)
    {
        if (direction == 'N')
        {
            (player[activePlayer-1].x)--;
        }
        else if (direction == 'S')
        {
            (player[activePlayer-1].x)++;
        }
        else if (direction == 'E')
        {
            (player[activePlayer-1].y)++;
        }
        else if (direction == 'W')
        {
            (player[activePlayer-1].y)--;
        }
    }
    else
    {
        cout << "GUESS PASSWORD FIRST" << endl;
    }
    for (int i = 0; i < MAX_TRAPDOORS; i++)
    {
        if (player[activePlayer-1].y == trapdoorsY[i] && player[activePlayer-1].x == trapdoorsX[i])
        {
            cout << "Player " << activePlayer << " lost" << endl;
            lostGame[activePlayer - 1] = true;
            return;
        }
    }
    if (player[activePlayer-1].y == 0 && player[activePlayer-1].x == 0 && pickedUp[activePlayer - 1])
    {
        cout << "Player " << activePlayer << " won" << endl;
        wonGame[activePlayer - 1] = true;
    }
    if (!pickedUp[activePlayer - 1])
        for (int i = 0; i < treasuresX.size(); i++)
        {
            if (((player[activePlayer-1].y == treasuresY[i]) || (player[activePlayer-1].y == treasuresY[i] + 1) || (player[activePlayer-1].y == treasuresY[i] - 1)) && ((player[activePlayer-1].x == treasuresX[i]) || (player[activePlayer-1].x == treasuresX[i] + 1) || (player[activePlayer-1].x == treasuresX[i] - 1)))
            {
                cout << "You see a treasure at (" << treasuresX[i] << "," << treasuresY[i] << ")" << endl;
                break;
            }
        }
    for (int j = 0; j < trapdoorsX.size(); j++)
    {
        if (((player[activePlayer-1].y == trapdoorsY[j]) || (player[activePlayer-1].y == trapdoorsY[j] + 1) || (player[activePlayer-1].y == trapdoorsY[j] - 1)) && ((player[activePlayer-1].x == trapdoorsX[j]) || (player[activePlayer-1].x == trapdoorsX[j] + 1) || (player[activePlayer-1].x == trapdoorsX[j] - 1)))
        {
            cout << "You see a trapdoor at (" << trapdoorsX[j] << "," << trapdoorsY[j] << ")" << endl;
            break;
        }
    }
}
// Picking up function //
void pickUp(int& activePlayer)
{
    for (int i = 0; i < MAX_TREASURES; i++)
    {
        if (player[activePlayer-1].x == treasuresX[i] && player[activePlayer-1].y == treasuresY[i])
        {
            pickedUp[activePlayer - 1] = true;
        }
    }
}

// Function for PRT 0 //
void prt_0(int& activePlayer)
{
    cout << "Active Player: " << activePlayer << " ";
    cout << "Coordinates: ";
    cout << player[activePlayer-1].x << ", " << player[activePlayer-1].y;
    cout << " Entered: ";
    if (player[activePlayer - 1].guessedPassword)
    {
        cout << "T ";
    }
    else
    {
        cout << "F ";
    }
    cout << "Lost: ";
    if (lostGame[activePlayer - 1])
    {
        cout << "T ";
    }
    else if (!lostGame[activePlayer - 1])
    {
        cout << "F ";
    }
    cout << "Has Treasure: ";
    if (pickedUp[activePlayer - 1])
    {
        cout << "T ";
    }
    else if (!pickedUp[activePlayer - 1])
    {
        cout << "F ";
    }
    cout << "Won Game: ";
    if (wonGame[activePlayer - 1])
    {
        cout << "T";
    }
    else if (!wonGame[activePlayer - 1])
    {
        cout << "F";
    }
    cout << endl;
}
// Function for PRT 1 //
void prt_1(int& activePlayer)
{
    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        if (playerIds[i] == activePlayer && playerIds[i] != 0)
        {
            cout << "Active Player: " << playerIds[i] << " ";
            cout << "Coordinates: " << player[i].x << ", " << player[i].y << " ";
            cout << "Entered: ";
            if (player[i].guessedPassword)
            {
                cout << "T ";
            }
            else if (!player[i].guessedPassword)
            {
                cout << "F ";
            }
            cout << "Lost: ";
            if (lostGame[i])
            {
                cout << "T ";
            }
            else if (!lostGame[i])
            {
                cout << "F ";
            }
            cout << "Has Treasure: ";
            if (pickedUp[i])
            {
                cout << "T ";
            }
            else if (!pickedUp[i])
            {
                cout << "F ";
            }
            cout << "Won Game: ";
            if (wonGame[i])
            {
                cout << "T";
            }
            else if (!wonGame[i])
            {
                cout << "F";
            }
            cout << endl;
        }
        if (playerIds[i] != activePlayer && playerIds[i] != 0)
        {
            cout << "Player: " << playerIds[i] << " ";
            cout << "Coordinates: " << player[i].x << ", " << player[i].y << " ";
            cout << "Entered: ";
            if (player[i].guessedPassword)
            {
                cout << "T ";
            }
            else if (!player[i].guessedPassword)
            {
                cout << "F ";
            }
            cout << "Lost: ";
            if (lostGame[i])
            {
                cout << "T ";
            }
            else if (!lostGame[i])
            {
                cout << "F ";
            }
            cout << "Has Treasure: ";
            if (pickedUp[i])
            {
                cout << "T ";
            }
            else if (!pickedUp[i])
            {
                cout << "F ";
            }
            cout << "Won Game: ";
            if (wonGame[i])
            {
                cout << "T";
            }
            else if (!wonGame[i])
            {
                cout << "F";
            }
            cout << endl;
        }
    }
}
int main()
{
    // Default players 1 and 2 declaration // 
    playerIds[0] = 1;
    playerIds[1] = 2;

    treasuresX.push_back(-3);
    treasuresY.push_back(0);
    trapdoorsX.push_back(3);
    trapdoorsY.push_back(0);
    // Default active player //
    int activePlayer = playerIds[0];

    // Create the map and make it 11x11 with all dots //
    char mapOfTheGame[MAX_ROWS][MAX_COLUMNS];

    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLUMNS; j++)
        {
            mapOfTheGame[i][j] = '.';
        }
    }

    // Game //
    while (true)
    {
        string command;
        cin >> command;
        if (command == "PRT")
        {
            string mode;
            cin >> mode;
            if (mode == "0")
            {
                prt_0(activePlayer);
            }
            else if (mode == "1")
            {
                prt_1(activePlayer);
            }
        }
        else if (command == "PSS")
        {
            guessPassword(activePlayer);
        }
        else if (command == "MOV")
        {
            movePlayer(activePlayer);
        }
        else if (command == "END")
        {
            return 0;
        }
        else if (command == "SKP");
        else if (command == "PCK")
        {
            pickUp(activePlayer);
        }
        if (command != "PRT")
        {
            changePlayer(activePlayer);
        }
    }
}

