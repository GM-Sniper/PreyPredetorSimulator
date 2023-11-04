/*
Name: Ramy Shehata 900222862
Name: Seif ElAnsary 900221511
  */


#include <iostream>
#include <ctime>
#include <string>
#include <map>
#include <windows.h>

#define ANT_NUM 100
#define CRIT_NUM 5
#define SIZE 20

using namespace std;
enum Direction { UP, DOWN, LEFT, RIGHT };

map<string, int> cmap = {
						{ "Black"       , 0  },
						{ "Blue"        , 1  },
						{ "Green"       , 2  },
						{ "Aqua"        , 3  },
						{ "Red"         , 4  },
						{ "Purple"      , 5  },
						{ "Yellow"      , 6  },
						{ "White"       , 7  },
						{ "Gray"        , 8  },
						{ "Light_Blue"  , 9  },
						{ "Light_Green" , 10 },
						{ "Light_Aqua"  , 11 },
						{ "Light_Red"   , 12 },
						{ "Light_Purple", 13 },
						{ "Light_Yellow", 14 },
						{ "Bright_White", 15 }
						};

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);


void color(string s)
{
	SetConsoleTextAttribute(h, cmap[s]);
}


class Organism
{
protected:
	int currX = 0;
	int currY = 0;
public:
	virtual void Move(Organism***) = 0;
	virtual void Breed(Organism***, int) = 0;
};
class Ant : public Organism
{
public:
	static int antAlive;
	Ant(int x, int y);
	virtual void Move(Organism***) override;
	virtual void Breed(Organism***, int) override;
};
class DoodleBug : public Organism
{
private:
	int deathTime;
public:
	static int doodleBugAlive;
	DoodleBug() { deathTime = 0; doodleBugAlive++;}
	DoodleBug(int x, int y);
	virtual void Move(Organism***) override;
	virtual void Breed(Organism***, int) override;
	void Starve(Organism***, int);
};
int Ant::antAlive = 0;
int DoodleBug::doodleBugAlive = 0;

Ant::Ant(int x, int y)
{
	currX = x;
	currY = y;
	antAlive++;
}
void Ant::Move(Organism*** game) {
	Direction direction = static_cast<Direction>(rand() % 4);
	int newX = currX, newY = currY;

	// Calculate the new coordinates based on the chosen direction
	if (direction == UP && newY!=0)
		{
            
            newY--;
        }
    else if (direction == DOWN && newY<SIZE)
		{
            
            newY++;
        }
    else if (direction == LEFT && newX != 0)
		{
            newX--;
            
        }
    else if (direction == RIGHT && newX<SIZE)
		{
            newX++;
           
        }
	// Ensure new coordinates are within bounds
	if (newX >= 0 && newX < SIZE && newY >= 0 && newY < SIZE && game[newX][newY] == nullptr) {
		// Move the Ant to the new cell
		game[newX][newY] = this;
		game[currX][currY] = nullptr;
		currX = newX;
		currY = newY;
	}
}

void Ant::Breed(Organism*** game, int step) {
	if (step % 3 == 0) {
		int newX = currX, newY = currY;
		Direction direction = static_cast<Direction>(rand() % 4);

	  if (direction == UP && newY<0)
		{
           
            newY--;
        }
    else if (direction == DOWN && newY<SIZE)
		{
            
            newY++;
        }
    else if (direction == LEFT && newX<0)
		{
            newX--;
            
        }
    else if (direction == RIGHT && newX<SIZE)
		{
            newX++;
           
        }

		// Ensure new coordinates are within bounds
		if (newX >= 0 && newX < SIZE && newY >= 0 && newY < SIZE && game[newX][newY] == nullptr) {
			// Create a new Ant in the adjacent cell
			game[newX][newY] = new Ant(newX, newY);
		}
	}
}

DoodleBug::DoodleBug(int x, int y)
{
	currX = x;
	currY = y;
	doodleBugAlive++;
	deathTime = 0;
}

void DoodleBug::Move(Organism*** game) {
    int possibleMoves[4] = {UP, DOWN, LEFT, RIGHT};

    int newX = currX;
    int newY = currY;

    for (int i = 0; i < 4; i++) {
        Direction checkDirection = static_cast<Direction>(possibleMoves[rand()%4]);

        // Calculate the new coordinates based on the chosen direction
        if (checkDirection == UP && newY!=0)
		{
           
            newY--;

			
        }
        else if (checkDirection == DOWN && newY<SIZE)
		{
           
            newY++;

			
        }
        else if (checkDirection == LEFT && newX != 0)
		{
            newX--;

			
            
        }
        else if (checkDirection == RIGHT && newX<SIZE)
		{
            newX++;

			
            
        }

        // Ensure new coordinates are within bounds
        if (newX >= 0 && newX < SIZE && newY >= 0 && newY < SIZE && game[newX][newY] != nullptr) {
            // Check if the destination cell contains an Ant
            if (dynamic_cast<Ant*>(game[newX][newY])) {
                // The DoodleBug eats the Ant
                //delete game[newX][newY];
                game[newX][newY] = this;
                game[currX][currY] = nullptr;
                currX = newX;
                currY = newY;
                deathTime = 0;
				Ant::antAlive--;
                return;
            }
        }
    }

	newX = currX;

	newY = currY;

    // If no adjacent cell contains an Ant, move randomly or increment death time
    Direction randomDirection = static_cast<Direction>(rand() % 4);
   

    // Calculate the new coordinates based on the random direction
   	if (randomDirection == UP && newY!=0)
		{
            
            newY--;
        }
    else if (randomDirection == DOWN && newY<SIZE)
		{
            
            newY++;
        }
    else if (randomDirection == LEFT && newX != 0)
		{
            newX--;
           
        }
    else if (randomDirection == RIGHT && newX<SIZE)
		{
            newX++;
            
        }

    // Ensure new coordinates are within bounds
    if (newX >= 0 && newX < SIZE && newY >= 0 && newY < SIZE) {
        if (game[newX][newY] == nullptr) {
            // Move the DoodleBug to the new cell
            game[newX][newY] = this;
            game[currX][currY] = nullptr;
            currX = newX;
            currY = newY;
            deathTime++;
        }
        else {
            deathTime++; // Increment death time if DoodleBug couldn't move
        }
    }
}

void DoodleBug::Breed(Organism*** game, int step) {
	if (step % 8 == 0) {
		int newX = currX, newY= currX;
		Direction direction = static_cast<Direction>(rand() % 4);

		if (direction == UP) {
			
			newY = currY - 1;
		}
		else if (direction == DOWN) {
			
			newY = currY + 1;
		}
		else if (direction == LEFT) {
			newX = currX - 1;
			
		}
		else if (direction == RIGHT) {
			newX = currX + 1;
			
		}

		// Ensure new coordinates are within bounds
		if (newX >= 0 && newX < SIZE && newY >= 0 && newY < SIZE && game[newX][newY] == nullptr) {
			// Create a new DoodleBug in the adjacent cell
			game[newX][newY] = new DoodleBug(newX, newY);
		}

	}
}

void DoodleBug::Starve(Organism*** game, int step) {
	if (this->deathTime == 3) {
		// DoodleBug starves and dies
		game[currX][currY] = nullptr;
		DoodleBug::doodleBugAlive--;
	}
}

void initializeWorld(Organism*** game) {
	int x, y;
	for (int i = 0; i < ANT_NUM; i++)
	{
		x = rand() % SIZE;
		y = rand() % SIZE;
		while (game[x][y] != nullptr)
		{
			x = rand() % SIZE;
			y = rand() % SIZE;

		}
		game[x][y] = new Ant(x, y);
	}
	for (int i = 0; i < CRIT_NUM; i++) {
		x = rand() % SIZE;
		y = rand() % SIZE;
		while (game[x][y] != nullptr)
		{
			x = rand() % SIZE;
			y = rand() % SIZE;

		}
		game[x][y] = new DoodleBug(x, y);
	}
}

void drawWorld(Organism *** game) {
	for (int y = 0; y < SIZE; y++) {
		for (int x = 0; x < SIZE; x++) {
			if (game[x][y] == nullptr) {
				// Cell is empty
				color("Purple");
				cout << " . ";
			}
			else if (dynamic_cast<DoodleBug*>(game[x][y]) != nullptr) {
				// Cell contains a Doodlebug
				color("Light_Blue"); 
				cout << " X ";
			}
			else if (dynamic_cast<Ant*>(game[x][y]) != nullptr) {
				// Cell contains an Ant
				color("Light_Red");
				cout << " o ";
			}

			// Add spacing or newlines as needed for a clear grid
		}
		cout << endl;// Start a new line for the next row
	}
}


int main()
{
	srand(time(0));
	Organism*** gameWorld = new Organism ** [SIZE];  // Allocate memory for the array

	for (int i = 0; i < SIZE; i++)
	{
		gameWorld[i] = new Organism * [SIZE];  // Allocate memory for the inner arrays
		for (int j = 0; j < SIZE; j++)
		{
			gameWorld[i][j] = nullptr;  // Initialize each element to nullptr
		}
	}
	std::string ContinueGame;
	int timeStep = 1;
	initializeWorld(gameWorld);
	do {
		std::cout << "Time Step: " << timeStep << std::endl;
		drawWorld(gameWorld);

		// Simulate movement, breeding, and death of doodlebugs
		for (int x = 0; x < SIZE; x++) {
			for (int y = 0; y < SIZE; y++) {
				if (dynamic_cast<DoodleBug*>(gameWorld[x][y]) != nullptr) {
					DoodleBug* doodleBug = dynamic_cast<DoodleBug*>(gameWorld[x][y]);
					doodleBug->Move(gameWorld);
					doodleBug->Breed(gameWorld, timeStep);
					doodleBug->Starve(gameWorld, timeStep);
				}

			}
		}
		// Simulate movement, breeding, and death of ants
		for (int x = 0; x < SIZE; x++) {
			for (int y = 0; y < SIZE; y++) {
				if (dynamic_cast<Ant*>(gameWorld[x][y]) != nullptr) {
					Ant* ant = dynamic_cast<Ant*>(gameWorld[x][y]);
					ant->Move(gameWorld);
					ant->Breed(gameWorld, timeStep);
				}
			}
		}
		// Checks if all doodlebugs died to end the game
		if (DoodleBug::doodleBugAlive == 0)
		{

			cout << "\n\n";
			cout<< "At TimeStep: "<<timeStep<<endl;
			drawWorld(gameWorld);
			cout << "Ants win with Ants= " <<Ant::antAlive<< endl;
			break;
		}
		// Checks if all ants died to end the game
		if(Ant::antAlive==0)
		{
			cout << "\n\n";
			cout<< "At TimeStep: "<<timeStep<<endl;
			drawWorld(gameWorld);
			cout << "Doodlebugs win with number= " <<DoodleBug::doodleBugAlive<< endl;
			break;
		}
		// Prompt the user to press Enter to continue
		cout << "Press Enter to continue (or type 'quit' to exit)..." << endl;
		getline(std::cin, ContinueGame);

		timeStep++;
		cout << endl;
	} while (ContinueGame != "quit");

	for (int i = 0; i < SIZE; i++)
	{
		delete[] gameWorld[i];  // Deallocate inner arrays
	}
	delete[] gameWorld;  // Deallocate the main array

	return 0;
}