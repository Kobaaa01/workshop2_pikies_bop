#include <iostream>
#include <string>
#include <vector>
using namespace std;
 
const int MAX_OBJECTS = 100;
const int MAX_PLAYERS = 9;
const int MAX_ROWS = 11;
const int MAX_COLUMNS = 11; 

bool guessedPassword[MAX_PLAYERS];
bool pickedUp[MAX_PLAYERS];
bool wonGame[MAX_PLAYERS];
bool lostGame[MAX_PLAYERS];

int playerIds[MAX_PLAYERS];

struct Player
{
    int x, y;
    bool guessedPassword = false;
    bool pickedUp = false;
    bool wonGame = false;
    bool lostGame = false;
    char playersMap[MAX_ROWS][MAX_COLUMNS];
    int centerMapX = 5; // X coordinate of the center marker for this player
    int centerMapY = 5;
};
Player player[MAX_PLAYERS];


struct Objects
{
    int treaX;
    int treaY;
    int trapX;
    int trapY;
    int wallX;
    int wallY;
};
Objects objects[MAX_OBJECTS];

int wallsSize() 
{
    int count = 0;
    for (int i = 0; i < MAX_OBJECTS; i++) 
    {
        if (objects[i].wallX != 0 || objects[i].wallY != 0) 
        {
            count++;
        }
    }
    return count;
}

int treaSize() 
{
    int count = 0;
    for (int i = 0; i < MAX_OBJECTS; i++) 
    {
        if (objects[i].treaX != 0 || objects[i].treaY != 0) 
        {
            count++;
        }
    }
    return count;
}

int trapSize()
{
    int count = 0;
    for (int i = 0; i < MAX_OBJECTS; i++)
    {
        if (objects[i].trapX != 0 || objects[i].trapY != 0)
        {
            count++;
        }
    }
    return count;
}

void setWall(char mapOfTheGame[MAX_ROWS][MAX_COLUMNS], Player player[], int playerIds[])
{
    for (int i = 0; i < MAX_OBJECTS; i++)
    {
        if (objects[i].wallX == -999 && objects[i].wallY == -999)
        {
            cin >> objects[i].wallX;
            cin >> objects[i].wallY;
            mapOfTheGame[objects[i].wallX + 5][objects[i].wallY + 5] = '#';

            for (int j = 0; j < MAX_PLAYERS; j++)
            {
                if (playerIds[j] != 0)
                {
                    player[j].playersMap[objects[i].wallX + 5][objects[i].wallY + 5] = '#';
                }
            }
            break;
        }
    }
}

void setTrapdoor(char mapOfTheGame[MAX_ROWS][MAX_COLUMNS], Player player[], int playerIds[])
{
    for (int i = 0; i < MAX_OBJECTS; i++)
    {
        if (objects[i].trapX == -999 && objects[i].trapY == -999)
        {
            cin >> objects[i].trapX;
            cin >> objects[i].trapY;
            mapOfTheGame[objects[i].trapX + 5][objects[i].trapY + 5] = '_';
            for (int j = 0; j < MAX_PLAYERS; j++)
            {
                if (playerIds[j] != 0)
                {
                    player[j].playersMap[objects[i].trapX + 5][objects[i].trapY + 5] = '_';
                }
            }
            break;
        }
    }
}

void setTreasure(char mapOfTheGame[MAX_ROWS][MAX_COLUMNS], Player player[], int playerIds[])
{
    for (int i = 0; i < MAX_OBJECTS; i++)
    {
        if (objects[i].treaX == -999 && objects[i].treaY == -999)
        {
            cin >> objects[i].treaX;
            cin >> objects[i].treaY;
            mapOfTheGame[objects[i].treaX + 5][objects[i].treaY + 5] = '+';
            for (int j = 0; j < MAX_PLAYERS; j++)
            {
                if (playerIds[j] != 0)
                {
                    player[j].playersMap[objects[i].treaX + 5][objects[i].treaY + 5] = '+';
                }
            }
            break;
        }
    }
}

// Player adding function //
void addPlayer(char mapOfTheGame[MAX_ROWS][MAX_COLUMNS])
{
    for (int j = 0; j < MAX_PLAYERS; j++)
    {
        if (playerIds[j] == 0)
        {
            playerIds[j] = j + 1;
            for (int m = 0; m < MAX_ROWS; m++)
            {
                for (int n = 0; n < MAX_COLUMNS; n++)
                {
                    player[j].playersMap[m][n] = mapOfTheGame[m][n];
                }
            }
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
            if (!player[i].lostGame && playerIds[i] != 0)
            {
                activePlayer = i + 1;
                return;
            }
        }
    }

    for (int j = 0; j < activePlayer - 1; j++)
    {
        if (!player[j].lostGame && playerIds[j] != 0)
        {
            activePlayer = j + 1;
            return;
        }
    }
}

// Password guessing function //
void guessPassword(int& activePlayer)
{
    if (playerIds[activePlayer-1] != 0)
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
}
// Checking if player sees a trap function //
void seeingTrap(int &activePlayer)
{
    for (int j = 0; j < trapSize(); j++)
    {
        if (((player[activePlayer - 1].y == objects[j].trapY) || (player[activePlayer - 1].y == objects[j].trapY + 1) || (player[activePlayer - 1].y == objects[j].trapY - 1)) && ((player[activePlayer - 1].x == objects[j].trapX) || (player[activePlayer - 1].x == objects[j].trapX + 1) || (player[activePlayer - 1].x == objects[j].trapX - 1)))
        {
            cout << "You see a trapdoor at (" << objects[j].trapX << "," << objects[j].trapY << ")" << endl;
            break;
        }
    }
}

// Checking if player sees a treasure function //
void seeingTreasure(int& activePlayer)
{
    for (int i = 0; i < treaSize(); i++)
    {
        if (((player[activePlayer - 1].y == objects[i].treaY) || (player[activePlayer - 1].y == objects[i].treaY + 1) || (player[activePlayer - 1].y == objects[i].treaY - 1)) && ((player[activePlayer - 1].x == objects[i].treaX) || (player[activePlayer - 1].x == objects[i].treaX + 1) || (player[activePlayer - 1].x == objects[i].treaX - 1)))
        {
            cout << "You see a treasure at (" << objects[i].treaX << "," << objects[i].treaY << ")" << endl;
            break;
        }
    }
}

// Player moving function //
void movePlayer(int& activePlayer, Player player[], int playerIds[]) {
    char direction;
    cin >> direction;
    if (player[activePlayer - 1].guessedPassword)
    {
        if (direction == 'N')
        {
            player[activePlayer - 1].y--;
            player[activePlayer - 1].centerMapY++;
            for (int i = MAX_ROWS - 2; i >= 0; --i)
            {
                for (int j = 0; j < MAX_COLUMNS; ++j)
                {
                    player[activePlayer - 1].playersMap[i + 1][j] = player[activePlayer - 1].playersMap[i][j];
                }
            }
            for (int j = 0; j < MAX_COLUMNS; ++j)
            {
                player[activePlayer - 1].playersMap[0][j] = '.';
            }
        }
        if (direction == 'S')
        {

        }
        if (direction == 'E')
        {

        }
        if (direction == 'W')
        {

        }
        for (int i = 0; i < MAX_ROWS; ++i)
        {
            for (int j = 0; j < MAX_COLUMNS; ++j)
            {
                // Reset each cell to empty
                player[activePlayer - 1].playersMap[i][j] = '.';
                for (int p = 0; p < MAX_PLAYERS; p++)
                {
                    if (p != activePlayer && player[p].y == 0)
                    {
                        player[activePlayer - 1].playersMap[5][5 + player[p].x] = '0' + p;
                    }
                    else if (p != activePlayer && player[p].y < 0)
                    {
                        player[activePlayer - 1].playersMap[5 - player[p].y][5 + player[activePlayer].x] = '0' + activePlayer;
                    }
                }
                player[activePlayer - 1].playersMap[5][5] = '0' + activePlayer-1;
                // Update treasures
                for (int t = 0; t < treaSize(); ++t)
                {
                    if (i == objects[t].treaY + 5 && j == objects[t].treaX + 5)
                    {
                        player[activePlayer - 1].playersMap[j + 1][i] = '+';
                    }
                }
                // Update traps
                for (int t = 0; t < trapSize(); ++t)
                {
                    if (i == objects[t].trapY + 5 && j == objects[t].trapX + 5)
                    {
                        player[activePlayer - 1].playersMap[j + 1][i] = '_';
                    }
                }
                // Update walls
                for (int t = 0; t < wallsSize(); ++t)
                {
                    if (i == objects[t].wallY + 5 && j == objects[t].wallX + 5)
                    {
                        player[activePlayer - 1].playersMap[j + 1][i] = '#';
                    }
                }
            }
        }
        player[activePlayer - 1].playersMap[player[activePlayer - 1].centerMapY][player[activePlayer - 1].centerMapX] = '^';
    }
    else
    {
        cout << "GUESS PASSWORD FIRST" << endl;
    }
    for (int i = 0; i < trapSize(); i++)
    {
        if (player[activePlayer-1].y == objects[i].trapY && player[activePlayer-1].x == objects[i].trapX)
        {
            cout << "Player " << activePlayer << " lost" << endl;
            player[activePlayer - 1].lostGame = true;
            return;
        }
    }
    if (player[activePlayer-1].y == 0 && player[activePlayer-1].x == 0 && player[activePlayer - 1].pickedUp)
    {
        cout << "Player " << activePlayer << " won" << endl;
        player[activePlayer - 1].wonGame = true;
    }
    if (!player[activePlayer - 1].pickedUp)
    {
        seeingTreasure(activePlayer);
        seeingTrap(activePlayer);
    }
}
// Picking up function //
void pickUp(int& activePlayer)
{
    for (int i = 0; i < treaSize(); i++)
    {
        if (player[activePlayer-1].x == objects[i].treaX && player[activePlayer-1].y == objects[i].treaY)
        {
            player[activePlayer - 1].pickedUp = true;
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
    if (player[activePlayer - 1].lostGame)
    {
        cout << "T ";
    }
    else if (!player[activePlayer - 1].lostGame)
    {
        cout << "F ";
    }
    cout << "Has Treasure: ";
    if (player[activePlayer - 1].pickedUp)
    {
        cout << "T ";
    }
    else if (!player[activePlayer - 1].pickedUp)
    {
        cout << "F ";
    }
    cout << "Won Game: ";
    if (player[activePlayer - 1].wonGame)
    {
        cout << "T";
    }
    else if (!player[activePlayer - 1].wonGame)
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
            if (player[i].lostGame)
            {
                cout << "T ";
            }
            else if (!player[i].lostGame)
            {
                cout << "F ";
            }
            cout << "Has Treasure: ";
            if (player[i].pickedUp)
            {
                cout << "T ";
            }
            else if (!player[i].pickedUp)
            {
                cout << "F ";
            }
            cout << "Won Game: ";
            if (player[i].wonGame)
            {
                cout << "T";
            }
            else if (!player[i].wonGame)
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
            if (player[i].lostGame)
            {
                cout << "T ";
            }
            else if (!player[i].lostGame)
            {
                cout << "F ";
            }
            cout << "Has Treasure: ";
            if (player[i].pickedUp)
            {
                cout << "T ";
            }
            else if (!player[i].pickedUp)
            {
                cout << "F ";
            }
            cout << "Won Game: ";
            if (player[i].wonGame)
            {
                cout << "T";
            }
            else if (!player[i].wonGame)
            {
                cout << "F";
            }
            cout << endl;
        }
    }
}

void defaultState(Objects objects[], int playerIds[]) 
{
    for (int i = 0; i < MAX_PLAYERS; i++) {
        playerIds[i] = 0;
    }
    for (int i = 0; i < MAX_OBJECTS; i++) {
        objects[i].treaX = -999;
        objects[i].treaY = -999;
        objects[i].trapX = -999;
        objects[i].trapY = -999;
        objects[i].wallX = -999;
        objects[i].wallY = -999;
    }
}

void npsFunction(int& activePlayer, char mapOfTheGame[MAX_ROWS][MAX_COLUMNS], Player player[])
{
    int numPlayers;
    cin >> numPlayers;
    for (int i = 0; i < numPlayers; ++i)
    {
        playerIds[i] = i + 1;
        cin >> player[i].y >> player[i].x;
        if (player[i].y >= 0 && player[i].y < MAX_COLUMNS && player[i].x >= 0 && player[i].x < MAX_ROWS)
        {
            mapOfTheGame[5+player[i].y][5+player[i].x] = '0' + i;
        }
    }
    for (int i = numPlayers; i < MAX_PLAYERS; ++i)
    {
        playerIds[i] = 0;
    }
    activePlayer = 1;

    for (int i = 0; i < MAX_PLAYERS; i++) 
    {
        if (playerIds[i] != 0) 
        {
            for (int n = 0; n < MAX_ROWS; n++) 
            {
                for (int m = 0; m < MAX_COLUMNS; m++) 
                {
                    player[i].playersMap[n][m] = mapOfTheGame[n][m];
                }
            }
        }
    }
}


int main()
{
    // Default players 1 and 2 declaration // 
    playerIds[0] = 1;
    playerIds[1] = 2;
    objects[0].treaX = -3;
    objects[0].treaY = 0;
    objects[0].trapX = 3;
    objects[0].trapY = 0;

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

    for (int j = 0; j < MAX_PLAYERS; j++)
    {
        if (playerIds[j] != 0)
        {
            for (int n = 0; n < MAX_ROWS; n++)
            {
                for (int m = 0; m < MAX_COLUMNS; m++)
                {
                    player[j].playersMap[n][m] = '.';
                }
            }
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
            else if (mode == "0+")
            {
                int submode;
                cin >> submode;
                prt_0(activePlayer);
                //CREATE function printing things submode distance from player//
                for (int i = 0; i < MAX_ROWS; i++)
                {
                    for (int j = 0; j < MAX_COLUMNS; j++)
                    {
                        cout << player[activePlayer-1].playersMap[i][j];
                    }
                    cout << endl;
                }
            }
        }
        else if (command == "PSS")
        {
            guessPassword(activePlayer);
        }
        else if (command == "MOV")
        {
            movePlayer(activePlayer, player, playerIds);
        }
        else if (command == "END")
        {
            return 0;
        }
        else if (command == "NDS")
        {
            defaultState(objects, playerIds);
        }
        else if (command == "NPS")
        {
            npsFunction(activePlayer, mapOfTheGame, player);
        }
        else if (command == "SKP");
        else if (command == "PCK")
        {
            pickUp(activePlayer);
        }
        else if (command == "TRS")
        {
            setTreasure(mapOfTheGame, player, playerIds);
        }
        else if (command == "WLL")
        {
            setWall(mapOfTheGame, player, playerIds);
        }
        else if (command == "TRD")
        {
            setTrapdoor(mapOfTheGame, player, playerIds);
        }
        if (command != "PRT" && command != "NDS" && command != "NPS" && command != "TRS" && command != "WLL" && command != "TRD")
        {
            changePlayer(activePlayer);
        }
    }
}


