#include <iostream>
#include <string>
using namespace std;


#define MAX_OBJECTS 100
#define MAX_PLAYERS 9
#define NONEXISTENT 999
// Defining the size of the map (the task did not specify the values)
#define MAX_ROWS 11
#define MAX_COLUMNS 11
#define CENTER_THE_MAP 5

// Struct containing every player's coordinates and whether they: guessed the password, picked up the treasure, won the game or lost the game
struct Player
{
    int x = 0;
    int y = 0;
    bool guessedPassword = false;
    bool pickedUp = false;
    bool wonGame = false;
    bool lostGame = false;
};
Player player[MAX_PLAYERS];
int playerIds[MAX_PLAYERS];
// Struct containing all the information about coordinates of treasures, trapdoors and walls
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

// Function to count the number of treasures
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

// Function to count the number of traps
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

// Function to set walls on the game map
void setWall(char mapOfTheGame[MAX_ROWS][MAX_COLUMNS])
{
    for (int i = 0; i < MAX_OBJECTS; i++)
    {
        if (objects[i].wallX == NONEXISTENT && objects[i].wallY == NONEXISTENT)
        {
            cin >> objects[i].wallX;
            cin >> objects[i].wallY;
            mapOfTheGame[objects[i].wallX + CENTER_THE_MAP][objects[i].wallY + CENTER_THE_MAP] = '#';
            break;
        }
    }
}

// Function to set trapdoors on the game map
void setTrapdoor(char mapOfTheGame[MAX_ROWS][MAX_COLUMNS])
{
    for (int i = 0; i < MAX_OBJECTS; i++)
    {
        if (objects[i].trapX == NONEXISTENT && objects[i].trapY == NONEXISTENT)
        {
            cin >> objects[i].trapX;
            cin >> objects[i].trapY;
            mapOfTheGame[objects[i].trapX + CENTER_THE_MAP][objects[i].trapY + CENTER_THE_MAP] = '_';
            break;
        }
    }
}

// Function to set treasures on the game map
void setTreasure(char mapOfTheGame[MAX_ROWS][MAX_COLUMNS])
{
    for (int i = 0; i < MAX_OBJECTS; i++)
    {
        if (objects[i].treaX == NONEXISTENT && objects[i].treaY == NONEXISTENT)
        {
            cin >> objects[i].treaX;
            cin >> objects[i].treaY;
            mapOfTheGame[objects[i].treaX + CENTER_THE_MAP][objects[i].treaY + CENTER_THE_MAP] = '+';
            break;
        }
    }
}

// Function to switch to the next active player
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

// Function for players to guess a password
void guessPassword(int& activePlayer)
{
    if (playerIds[activePlayer - 1] != 0)
    {
        if (!player[activePlayer - 1].guessedPassword)
        {
            unsigned char password = 123;
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

// Function to check if a player sees a trap
void seeingTrap(int& activePlayer)
{
    for (int j = 0; j < trapSize(); j++)
    {
        if (((player[activePlayer - 1].y == objects[j].trapX) || (player[activePlayer - 1].y == objects[j].trapX + 1) || (player[activePlayer - 1].y == objects[j].trapX - 1)) && ((player[activePlayer - 1].x == objects[j].trapY) || (player[activePlayer - 1].x == objects[j].trapY + 1) || (player[activePlayer - 1].x == objects[j].trapY - 1)))
        {
            cout << "You see a trapdoor at (" << objects[j].trapX << "," << objects[j].trapY << ")" << endl;
            break;
        }
    }
}

// Function to check if a player sees a treasure
void seeingTreasure(int& activePlayer)
{
    for (int i = 0; i < treaSize(); i++)
    {
        if (((player[activePlayer - 1].y == objects[i].treaX) || (player[activePlayer - 1].y == objects[i].treaX + 1) || (player[activePlayer - 1].y == objects[i].treaX - 1)) && ((player[activePlayer - 1].x == objects[i].treaY) || (player[activePlayer - 1].x == objects[i].treaY + 1) || (player[activePlayer - 1].x == objects[i].treaY - 1)))
        {
            cout << "You see a treasure at (" << objects[i].treaX << "," << objects[i].treaY << ")" << endl;
            break;
        }
    }
}

// Function to move a player on the game map
void movePlayer(int& activePlayer) {
    char direction;
    cin >> direction;
    if (player[activePlayer - 1].guessedPassword)
    {
        if (direction == 'N')
        {
            player[activePlayer - 1].y--;
        }
        if (direction == 'S')
        {
            player[activePlayer - 1].y++;
        }
        if (direction == 'E')
        {
            player[activePlayer - 1].x++;
        }
        if (direction == 'W')
        {
            player[activePlayer - 1].x--;
        }
    }
    else
    {
        cout << "GUESS PASSWORD FIRST" << endl;
    }
    for (int i = 0; i < trapSize(); i++)
    {
        if (player[activePlayer - 1].y == objects[i].trapX && player[activePlayer - 1].x == objects[i].trapY)
        {
            cout << "Player " << activePlayer << " lost" << endl;
            player[activePlayer - 1].lostGame = true;
            return;
        }
    }
    if (player[activePlayer - 1].y == 0 && player[activePlayer - 1].x == 0 && player[activePlayer - 1].pickedUp)
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

// Function for players to pick up an object
void pickUp(int& activePlayer)
{
    for (int i = 0; i < treaSize(); i++)
    {
        if (player[activePlayer - 1].x == objects[i].treaY && player[activePlayer - 1].y == objects[i].treaX)
        {
            player[activePlayer - 1].pickedUp = true;
        }
    }
}

// Print function for mode 0
void prt_0(int& activePlayer)
{
    Player& currentPlayer = player[activePlayer - 1];

    cout << "Active Player: " << activePlayer << " ";
    cout << "Coordinates: " << currentPlayer.y << ", " << currentPlayer.x << " ";
    cout << " Entered: " << (currentPlayer.guessedPassword ? "T " : "F ");
    cout << "Lost: " << (currentPlayer.lostGame ? "T " : "F ");
    cout << "Has Treasure: " << (currentPlayer.pickedUp ? "T " : "F ");
    cout << "Won Game: " << (currentPlayer.wonGame ? "T" : "F");
    cout << endl;
}

// Print function for mode 1
void prt_1(int& activePlayer)
{
    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        if (playerIds[i] != 0)
        {
            cout << (playerIds[i] == activePlayer ? "Active Player: " : "Player: ") << playerIds[i] << " ";
            cout << "Coordinates: " << player[i].y << ", " << player[i].x << " ";
            cout << "Entered: " << (player[i].guessedPassword ? "T " : "F ");
            cout << "Lost: " << (player[i].lostGame ? "T " : "F ");
            cout << "Has Treasure: " << (player[i].pickedUp ? "T " : "F ");
            cout << "Won Game: " << (player[i].wonGame ? "T" : "F") << endl;
        }
    }
}

// Function to reset the game to its default state
void defaultState()
{
    for (int i = 0; i < MAX_PLAYERS; i++) {
        playerIds[i] = 0;
    }
    for (int i = 0; i < MAX_OBJECTS; i++) {
        objects[i].treaX = NONEXISTENT;
        objects[i].treaY = NONEXISTENT;
        objects[i].trapX = NONEXISTENT;
        objects[i].trapY = NONEXISTENT;
        objects[i].wallX = NONEXISTENT;
        objects[i].wallY = NONEXISTENT;
    }
}

// Function to set up new players and start the game
void npsFunction(int& activePlayer, char mapOfTheGame[MAX_ROWS][MAX_COLUMNS])
{
    int numPlayers;
    cin >> numPlayers;
    if (numPlayers < MAX_PLAYERS)
    {
        for (int i = 0; i < numPlayers; ++i)
        {
            playerIds[i] = i + 1;
            cin >> player[i].y >> player[i].x;
            if (player[i].y >= 0 && player[i].y < MAX_COLUMNS && player[i].x >= 0 && player[i].x < MAX_ROWS)
            {
                mapOfTheGame[CENTER_THE_MAP + player[i].y][CENTER_THE_MAP + player[i].x] = '0' + i;
            }
        }
        for (int i = numPlayers; i < MAX_PLAYERS; ++i)
        {
            playerIds[i] = 0;
        }
        activePlayer = 1;
    }
    else
    {
        cout << "ERROR, 10 IS THE MAXIMUM NUMBER OF PLAYERS";
    }
}

int main()
{
    // Default players 1 and 2 declaration
    playerIds[0] = 1;
    playerIds[1] = 2;
    objects[0].treaX = -3;
    objects[0].treaY = 0;
    objects[0].trapX = 3;
    objects[0].trapY = 0;

    // Default active player
    int activePlayer = playerIds[0];

    // Create the map and make it 11x11 with all dots
    char mapOfTheGame[MAX_ROWS][MAX_COLUMNS]{};

    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLUMNS; j++)
        {
            mapOfTheGame[i][j] = '.';
        }
    }

    // Game
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
                string submode;
                cin >> submode;
                if (submode == "5")
                {
                    prt_0(activePlayer);
                    for (int i = 0; i < MAX_ROWS; i++)
                    {
                        for (int j = 0; j < MAX_COLUMNS; j++)
                        {
                            cout << mapOfTheGame[i][j];
                        }
                        cout << endl;
                    }
                }
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
        else if (command == "NDS")
        {
            defaultState();
        }
        else if (command == "NPS")
        {
            npsFunction(activePlayer, mapOfTheGame);
        }
        else if (command == "SKP");
        else if (command == "PCK")
        {
            pickUp(activePlayer);
        }
        else if (command == "TRS")
        {
            setTreasure(mapOfTheGame);
        }
        else if (command == "WLL")
        {
            setWall(mapOfTheGame);
        }
        else if (command == "TRD")
        {
            setTrapdoor(mapOfTheGame);
        }
        else if (command == "HLP")
        {
            cout << "Avaliable commands: PRT [0/1], PSS, MOV, END, NDS, NPS, SKP, PCK, TRS, WLL, TRD, HLP" << endl;
        }
        else
        {
            cout << "Unknown command. Avaliable commands: PRT [0/1], PSS, MOV, END, NDS, NPS, SKP, PCK, TRS, WLL, TRD, HLP" << endl;
        }
        if (command != "PRT" && command != "NDS" && command != "NPS" && command != "TRS" && command != "WLL" && command != "TRD")
        {
            changePlayer(activePlayer);
        }
    }
}