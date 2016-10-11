#ifndef ShipHeader
#define ShipHeader


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Map.h"

using namespace std;


int PirateDamage = 0;		// A global variable that tracks the total damage of Pirate Ships
int MerchantDamage = 0;		// A global variable that tracks the total damage of Merchant Ships
int ExplorationDamage = 0;	// A global variable that tracks the total damage of Exploration Ships
int RepairDamage = 0;		// A global variable that tracks the total damage of Repair Ships
int NavalDamage = 0;		// A global variable that tracks the total damage of Naval Ships
int SubMarineDamage = 0;	// A global variable that tracks the total damage of Submarines

/**The class that describes all Ships*/

class Ship
{
private:
	int maxResistance = 0;		// The maximum resistance of the ship
	int curResistance = 0;		// The current resistance of the ship
	int speed = 0;				// Integer value that represents the number of blocks that a ship can move in each round
	int treasure = 0;			// The amount of treasure a ship has collected
	int positionx = 0;			// The position of the ship on the x axis
	int positiony = 0;			// The position of the ship on the y axis
	int positionInVector = -1;	// The position of the ship in the vector where the ships are stored, acts as an identifier for each ship
	int type = 0;				/**< This variable determines the type of the ship :
								1--->PirateShip
								2--->MerchantShip
								3--->RepairShip
								4--->ExplorationShip
								5--->NavalShip
								6--->Submarine*/
	int blocksMoved = 0;		// The number of blocks the ship has travelled since the begining of the simulation
	int totalDamage = 0;		//The total damage the ship has suffered
public:
	static int treasureAmount;		 ///< A static variable that tracks the total gathered treasoure by all the ships
	static int NumberOfShips;		///< A static variable that tracks how many ships have existed in the simulation in order to name each new ship

	/** The default constructor of each Ship. The body of the constructor is empty as the behavior of each ship is determined by the constructors
	of the inherited classes*/

	Ship(){};

	/** The default destructor of each Ship. A brief message points out that the ship has been destructed successfully*/

	~Ship()
	{
		cout << "Ship " << getPositionInVector() << " has been destructed !!" << endl;
	};

	/***Operator OverLoading***/

	/**Overloading of operator --. It is used in order to make changes in any ship that has been damaged by bad weather	conditions ,as well as,
	to modify totalDamage
	@param Damage a value that points out the damage to be caused*/

	void operator-- (int Damage)
	{
		cout << "Ship " << this->getPositionInVector() << " has been damaged due to bad weather" << endl;
		this->setCurResistance(this->getCurResistance() - Damage);
		this->setTotalDamage(this->getTotalDamage() + Damage);
	}

	/**Overloading of operator +. It is used in order to accomplish the repairing of each ship in ports	by a pre-stated percentage.
	@param Percentage a percentage that points out the healing of each ship*/

	void operator+(double Percentage)
	{
		this->setCurResistance(this->getCurResistance() + (double)Percentage*this->getCurResistance());
	}

	/**Overloading of operator <<. It is used in order to print information about a ship that is passed as parameter.
	@param ploio : the ship whose printInfo() method is called */

	friend void operator<<(ostream &os, Ship* ploio)
	{
		ploio->printInfo();
	}

	/**Overloading of operator <<. It is used in order to check if an instnace's treasure is greater than the one of that passed as parameter.
	@param x : the ship whose printInfo() method is called
	@return a booelan variable that shows which ship's treasure is greater*/

	bool operator>(Ship* x)
	{
		if (this->getTreasure() > x->getTreasure())
			return true;
		else
			return false;
	}
	/*End Of Operator Overloading*/

	/**Determines the location in which a new ship is positioned . It generates two random values for x and y and  tries
	to place the ship in those coordinates or changes the afformentioned values until it succeeds.
	@param mapship : the map that contains the world of the simulation*/

	void setLocation(Map*& mapship)
	{
		bool flag = false;				// a variable that determines when a location is sucessfully set
		while (flag == false)
		{
			srand((unsigned int)time(0));
			int x = rand() % ARRAYSIZEX;
			int y = rand() % ARRAYSIZEY;
			if (mapship->locations[x][y].isEmpty())
			{
				mapship->locations[x][y].setHasShip(true);			//if the randomly generated position is empty, the property hasShip of the location is changed to occupied
				this->setX(x);										//the position of the ship is set to the new coordinates
				this->setY(y);
				flag = true;
			}
		}
	}

	/**Prints the location of the ship */

	void printLocation()
	{
		cout << "The ship's location is (" << this->getX() << "," << this->getY() << ")" << endl;
	}

	/**Prints a report about all the ship's information. It calls printLocation() and printType() in order to accomplish its goal*/

	void printInfo()
	{
		cout << "Ship " << getPositionInVector() << " : " << endl;
		cout << "Maximum Resistance : " << getMaxResistance() << endl;
		cout << "Current Resistance : " << getCurResistance() << endl;
		cout << "Speed : " << getSpeed() << endl;
		cout << "Treasure : " << getTreasure() << endl;
		cout << "Blocks Moved : " << getBlocksMoved() << endl;
		cout << "Total Damage : " << getTotalDamage() << endl;
		printLocation();
		printType();
	}

	/** A method that moves each ship in every round
	@param x : the current position of the ship on the x axis
	@param y : the current position of the ship on the y axis
	@param Speed : the default speed of the ship, it will be accessed through the get method for each object
	@param myMap : the map of the simulation */

	void movement(int x, int y, int Speed, Map* myMap)
	{
		if (this->getCurResistance() > 0)
		{
			srand((unsigned int)time(0));	// initialization of the seed using the current time 
			int counter = 0;				// this counter checks how many times the while loop has been accessed.When counter reaches 4 ,while loop is automatically broken
			bool done = false;				// a boolean variable which will become true if a ship successfully moves
			int direction = rand() % 4;		// a random value to show in which direction a ship will move towards
			while (!done)
			{
				switch (direction)	// this switch gets as a parameter a random value [0-3] and defines the movement of the ship
				{
				case 0:		//moving upwards
					if ((x - Speed) >= 0)	//checks if the attemted movement is legal or gets out of the map's bounds
					{
						if (myMap->locations[x - Speed][y].isEmpty())				//checks if the new position has already a ship or a port
						{
							myMap->locations[x][y].setHasShip(false);				//sets the old position's hasShip variable to false
							this->setX(x - Speed);									//sets the new position 
							myMap->locations[x - Speed][y].setHasShip(true);		//sets the new position's hasShip variable to true
							done = true;											//declares that a movement has been achieved in order to break while loop
							this->setBlocksMoved(this->getBlocksMoved() + Speed);	//increments the total moved blocks of the ship
							break;
						}
						else
						{
							counter++;
							direction++;		//if the ship cannot move towards a direction,it tries to move it towards another.
						}
					}
					else
					{
						counter++;
						direction++;
						if (counter >= 4){		// checks if the counter has exceeded 4 in order to break the loop 
							done = true;
							break;
						}
					}
				case 1:		//moving to the right
					if ((y + Speed) <= (ARRAYSIZEY - 1))
					{
						if (myMap->locations[x][y + Speed].isEmpty())
						{
							myMap->locations[x][y].setHasShip(false);
							this->setY(y + Speed);
							done = true;
							myMap->locations[x][y + Speed].setHasShip(true);
							this->setBlocksMoved(this->getBlocksMoved() + Speed);
							break;
						}
						else
						{
							counter++;
							direction++;
						}
					}
					else
					{
						counter++;
						direction++;
						if (counter >= 4){
							done = true;
							break;
						}
					}
				case 2:		//moving downwards
					if ((x + Speed) <= (ARRAYSIZEX - 1))
					{
						if (myMap->locations[x + Speed][y].isEmpty())
						{
							myMap->locations[x][y].setHasShip(false);
							this->setX(x + Speed);
							done = true;
							myMap->locations[x + Speed][y].setHasShip(true);
							this->setBlocksMoved(this->getBlocksMoved() + Speed);
							break;
						}
						else
						{
							counter++;
							direction++;
						}
					}
					else
					{
						counter++;
						direction++;
						if (counter >= 4){
							done = true;
							break;
						}
					}
				case 3:		//moving to the left
					if ((y - Speed) >= 0)
					{
						if (myMap->locations[x][y - Speed].isEmpty())
						{
							myMap->locations[x][y].setHasShip(false);
							this->setY(y - Speed);
							done = true;
							myMap->locations[x][y - Speed].setHasShip(true);
							this->setBlocksMoved(this->getBlocksMoved() + Speed);
							break;
						}
						else
						{
							counter++;
							direction = 0;
						}
					}
					else
					{
						counter++;
						direction = 0;
						if (counter >= 4)
						{
							done = true;
							break;
						}
					}
				}

			}
		}
	}

	/**Determines the type of the ship and prints an according message*/

	void printType()
	{
		switch (this->getType())
		{
		case 1:
			cout << "Type : Pirate Ship" << endl;
			break;
		case 2:
			cout << "Type : Merchant Ship" << endl;
			break;
		case 3:
			cout << "Type : Repair Ship" << endl;
			break;
		case 4:
			cout << "Type : Exploration Ship" << endl;
			break;
		case 5:
			cout << "Type : Naval Ship" << endl;
			break;
		case 6:
			cout << "Type : Submarine" << endl;
			break;
		}

	}

	/**A virtual method that determines the operation of each ship
	@param x : the position of the ship on the x axis
	@param y : the position of the ship on the y axis
	@param map : the map containing the world of the simulation
	@param myVector : the vector that contains the created ships*/

	virtual void operation(int x, int y, Map* map, vector<Ship*> myVector) {}

	/**Searches the vector for the ship corresponding to the coordinates that are beeing passed.
	@param x : the position of the ship on the x axis
	@param y : the position of the ship on the y axis
	@param myVector: the vector that contains the created ships
	@return A pointer to a ship that matches the coordinates.*/

	Ship* findShip(int x, int y, vector<Ship*> myVector)
	{
		for (unsigned int i = 0; i < myVector.size(); i++)
		{
			if ((myVector[i]->getX() == x) && (myVector[i]->getY() == y))
			{
				return myVector[i];
			}
		}

		return NULL;
	}

	/*******************************************************************************/
	/*****We use get-set methods, in case we want to act on a private variable*****/
	/*****************************************************************************/

	void setPositionInVector(int PositionInVector)
	{
		this->positionInVector = PositionInVector;
	}

	int getPositionInVector()
	{
		return positionInVector;
	}

	void setMaxResistance(int maxResistance)
	{
		this->maxResistance = maxResistance;
	}

	int getMaxResistance()
	{
		return maxResistance;
	}

	void setCurResistance(int curResistance)
	{
		this->curResistance = curResistance;
	}

	int getCurResistance()
	{
		return curResistance;
	}

	int getTreasure()
	{
		return treasure;
	}

	void setTreasure(int treasure)
	{
		this->treasure = treasure;
	}

	void setSpeed(int speed)
	{
		this->speed = speed;
	}

	int getSpeed()
	{
		return speed;
	}

	void setX(int positionx)
	{
		this->positionx = positionx;
	}

	int getX()
	{
		return positionx;
	}

	void setY(int positiony)
	{
		this->positiony = positiony;
	}

	int getY()
	{
		return positiony;
	}

	void setType(int Type)
	{
		this->type = Type;
	}

	int getType()
	{
		return type;
	}

	int getBlocksMoved()

	{
		return blocksMoved;
	}

	void setBlocksMoved(int blocksMoved)
	{
		this->blocksMoved = blocksMoved;
	}

	int getTotalDamage()
	{
		return totalDamage;
	}

	void setTotalDamage(int totalDamage)
	{
		this->totalDamage = totalDamage;
	}

	/*********************************/
	/*****End of get-set methods*****/
	/*******************************/

};

/**The class that describes Pirate Ships.It inherits class Ship*/

class PirateShip : public Ship
{
private:
	int attackingDamage = 20;		//a property pirate ships and submarines share and datermines their attacking abillity
	int causedDamage = 0;			//the total caused damage of each pirate ship
public:
	/** The default constructor of the pirate ships. It initializes the treasure to 50 , max resistance to 500 ,speed to 1 and sets the type to 1*/
	PirateShip()
	{
		setTreasure(50);
		setMaxResistance(500);
		setCurResistance(getMaxResistance());
		setSpeed(1);
		setType(1);
	}

	/** The operation of pirate ships. If a nearby ship exists , the pirate ship attacks it(reduces its resistance by the attacking damage),as well as,
	wins the 20% of its treasure.
	@param x : the position of the pirate ship on the x axis
	@param y : the position of the pirate ship on the y axis
	@param map : the map of the simulation's world
	@param myVector : the vector containing the created ships*/

	virtual void operation(int x, int y, Map* map, vector<Ship*> myVector)
	{
		if (this->getCurResistance() > 0)		//checks if the ship is able to function or has 0 Current Resistance
		{
			Ship* victim = NULL;				// a pointer to the victim ship
			bool flag = false;					// a flag that indicates that a ship exists nearby
			if (x + 1 <= ARRAYSIZEX - 1){		//checks if the index is inside the map's bounds and if in that position a ship exists
				if (map->locations[x + 1][y].getHasShip() == true)
				{
					victim = findShip(x + 1, y, myVector);		//if the ship exists the variable victim acts as a duplicate to the afformentioned ship
					if (victim->getCurResistance()>0)
						flag = true;
				}
			}
			if (x - 1 >= 0){
				if (map->locations[x - 1][y].getHasShip() == true)
				{
					victim = findShip(x - 1, y, myVector);
					if (victim->getCurResistance()>0)
						flag = true;
				}
			}
			if (y + 1 <= ARRAYSIZEY - 1){
				if (map->locations[x][y + 1].getHasShip() == true) {
					victim = findShip(x, y + 1, myVector);
					if (victim->getCurResistance()>0)
						flag = true;
				}
			}
			if (y - 1 >= 0){
				if (map->locations[x][y - 1].getHasShip() == true)
				{
					victim = findShip(x, y - 1, myVector);
					if (victim->getCurResistance()>0)
						flag = true;
				}
			}
			if (flag)		//if a ship exists(flag==true),it is being attacked and the attacking pirate ship
			{
				victim->setCurResistance(victim->getCurResistance() - this->getAttackDamage()); // the victim's current resistance is decreased by the pirate ship's attacking damage
				this->setCausedDamage(this->getCausedDamage() + this->getAttackDamage());		//the total caused damage of the pirate ship is increased by the attacking damage
				int treasure = victim->getTreasure();
				victim->setTreasure((double)0.8*treasure);										//the victim looses the 20% of its treasure
				this->setTreasure((double)0.2*treasure + this->getTreasure());					//the attacking ship gains a 20% of the victim's treasure
				victim->setTotalDamage(victim->getTotalDamage() + this->getAttackDamage());		//the total damage of the victim is being increased by the attacking damage
				switch (victim->getType())
				{
				case 1:
					PirateDamage += this->getAttackDamage();
					break;
				case 2:
					MerchantDamage += this->getAttackDamage();
					break;
				case 3:
					RepairDamage += this->getAttackDamage();
					break;
				case 4:
					ExplorationDamage += this->getAttackDamage();
					break;
				case 5:
					NavalDamage += this->getAttackDamage();
					break;
				case 6:
					SubMarineDamage += this->getAttackDamage();
					break;
				}
				cout << "Ship " << victim->getPositionInVector() << " has been damaged due to a battle with Ship " << this->getPositionInVector() << endl;
				cout << "Ship " << victim->getPositionInVector() << " has lost " << (double)0.2*treasure << " coins due to a battle with Ship " << this->getPositionInVector() << endl;
				cout << "Ship " << this->getPositionInVector() << " has gained " << (double)0.2*treasure << " coins due to a battle with Ship " << victim->getPositionInVector() << endl;
			}
		}
	}

	/*******************************************************************************/
	/*****We use get-set methods, in case we want to act on a private variable*****/
	/*****************************************************************************/

	void setAttackDamage(int value)
	{
		attackingDamage = value;
	}

	int getAttackDamage()
	{
		return attackingDamage;
	}

	void setCausedDamage(int totalDamage)
	{
		this->causedDamage = totalDamage;
	}

	int getCausedDamage()
	{
		return causedDamage;
	}

	/*********************************/
	/*****End of get-set methods*****/
	/*******************************/
};

/**The class that describes Merchant Ships.It inherits class Ship*/

class MerchantShip : public Ship
{
private:
	int portTreasure = 0;		//a variable that stores the total treasure a ship has gathered from ports
public:

	/** The default constructor of the merchant ships. It initializes the treasure to 100 , max resistance to 150 ,speed to 3 and sets the type to 2*/

	MerchantShip()
	{
		setTreasure(100);
		setMaxResistance(150);
		setCurResistance(getMaxResistance());
		setSpeed(3);
		setType(2);
	}

	/** The operation of merchant ships. If there is a port nearby the merchant ship increases its treasure by 50 coins.
	@param x : the position of the pirate ship on the x axis
	@param y : the position of the pirate ship on the y axis
	@param map : the map of the simulation's world
	@param myVector : the vector containing the created ships*/

	virtual void operation(int x, int y, Map* map, vector<Ship*> myVector)
	{
		if (this->getCurResistance() > 0)		//checks if the ship is able to function or has 0 Current Reistance
		{
			if (x + 1 <= ARRAYSIZEX - 1){		//checks if the position of the ship is inside the map's bounds
				if (map->locations[(x + 1)][y].getIsPort() == true)			//if  there is a port nearby 
				{
					this->setTreasure(getTreasure() + 50);					//the ships treasure is increased by 50
					this->setPortTreasure(this->getPortTreasure() + 50);	//the total treasure acquired by the ship is increased by 50
					Ship::treasureAmount += 50;								//the global variable that tracks all ships' treasure is increased by 50
					cout << "Ship " << this->getPositionInVector() << " has updated its treasure by reaching a port" << endl;
				}
			}
			if (x - 1 >= 0){
				if (map->locations[x - 1][y].getIsPort() == true)
				{
					this->setTreasure(getTreasure() + 50);
					this->setPortTreasure(this->getPortTreasure() + 50);
					Ship::treasureAmount += 50;
					cout << "Ship " << this->getPositionInVector() << " has updated its treasure by reaching a port" << endl;
				}
			}
			if (y + 1 <= ARRAYSIZEY - 1){
				if (map->locations[x][y + 1].getIsPort() == true)
				{
					this->setTreasure(getTreasure() + 50);
					this->setPortTreasure(this->getPortTreasure() + 50);
					Ship::treasureAmount += 50;
					cout << "Ship " << this->getPositionInVector() << " has updated its treasure by reaching a port" << endl;
				}
			}
			if (y - 1 >= 0){
				if (map->locations[x][y - 1].getIsPort() == true)
				{
					this->setTreasure(getTreasure() + 50);
					this->setPortTreasure(this->getPortTreasure() + 50);
					Ship::treasureAmount += 50;
					cout << "Ship " << this->getPositionInVector() << " has updated its treasure by reaching a port" << endl;
				}
			}
		}
	}

	void setPortTreasure(int portTreasure)
	{
		this->portTreasure = portTreasure;
	}
	int getPortTreasure()
	{
		return portTreasure;
	}
};

/**The class that describes Repair Ships.It inherits class Ship*/

class RepairShip : public Ship
{
private:
	int totalHeal = 0;		//a variable that tracks the total healing caused of the particular repair ship
public:

	/** The default constructor of the repair ships. It initializes the treasure to 50 , max resistance to 250 ,speed to 2 and sets the type to 3*/

	RepairShip()
	{
		setTreasure(50);
		setMaxResistance(250);
		setCurResistance(getMaxResistance());
		setSpeed(2);
		setType(3);
	}

	/** The operation of repair ships. If there is a ship nearby that its current resistance is less than its maximum, the repair ship heals it in exchange with the appropriate amount of coins.
	@param x : the position of the pirate ship on the x axis
	@param y : the position of the pirate ship on the y axis
	@param map : the map of the simulation's world
	@param myVector : the vector containing the created ships*/

	virtual void operation(int x, int y, Map* map, vector<Ship*> myVector)
	{
		bool flag = false;
		Ship* target = NULL;
		if (this->getCurResistance() > 0)
		{
			if (x + 1 <= ARRAYSIZEX - 1)
			{
				if ((map->locations[x + 1][y].getHasShip() == true))
				{
					target = findShip(x + 1, y, myVector);
					if (target->getCurResistance()>0)
						flag = true;
				}
			}
			if (x - 1 >= 0)
			{
				if ((map->locations[x - 1][y].getHasShip() == true))
				{
					target = findShip(x - 1, y, myVector);
					if (target->getCurResistance()>0)
						flag = true;
				}
			}
			if (y + 1 <= ARRAYSIZEY - 1)
			{
				if ((map->locations[x][y + 1].getHasShip() == true))
				{
					target = findShip(x, y + 1, myVector);
					if (target->getCurResistance()>0)
						flag = true;
				}
			}
			if (y - 1 >= 0)
			{
				if ((map->locations[x][y - 1].getHasShip() == true))
				{
					target = findShip(x, y - 1, myVector);
					if (target->getCurResistance()>0)
						flag = true;

				}
			}

			if (flag)
			{
				int damage = target->getMaxResistance() - target->getCurResistance();
				if (damage > 0)
				{
					if (damage < target->getTreasure())		//if the damage is less than the target's treasure
					{
						target->setCurResistance(target->getMaxResistance());	//the target is healed  until it reaches its maximum resistance
						target->setTreasure(target->getTreasure() - damage);	//the target's treasure is decreased by the amount of resistance that  has been restored
						this->setTotalHeal(this->getTotalHeal() + damage);		// the total healing of the repair ship is increased by that amount
						cout << "Ship " << target->getPositionInVector() << " has been repaired by Ship " << this->getPositionInVector() << endl;
						cout << "This action has cost to Ship " << target->getPositionInVector() << " , " << damage << " coins" << endl;
					}
					else
					{
						this->setTotalHeal(this->getTotalHeal() + target->getTreasure());				// the total healing of the repair ship is increased by all the coins of the target
						target->setCurResistance(target->getCurResistance() + target->getTreasure());	//the target is repaired for as coins as it possesses
						target->setTreasure(0);															//Tthe target's treasure is set to 0
						cout << "Ship " << target->getPositionInVector() << " has been repaired by Ship " << this->getPositionInVector() << endl;
						cout << "This action has cost to Ship " << target->getPositionInVector() << " , all of its treasure" << endl;
					}
				}
			}
		}
	}

	int getTotalHeal()
	{
		return totalHeal;
	}
	void setTotalHeal(int totalHeal)
	{
		this->totalHeal = totalHeal;
	}
};

/**The class that describes Exploration Ships.It inherits class Ship*/

class ExplorationShip : public Ship
{

public:

	/** The default constructor of Exploration ships. It initializes the treasure to 80 , max resistance to 300 , speed to 5 and sets the type to 4*/

	ExplorationShip()
	{
		setTreasure(80);
		setMaxResistance(300);
		setCurResistance(getMaxResistance());
		setSpeed(5);
		setType(4);
	}

	/** The operation of exploration ships. If there is a pirate ship nearby or bad weather conditions then the ship moves one block in the opposite direction.
	@param x : the position of the pirate ship on the x axis
	@param y : the position of the pirate ship on the y axis
	@param map : the map of the simulation's world
	@param myVector : the vector containing the created ships*/

	virtual void operation(int x, int y, Map* map, vector<Ship*> myVector)
	{
		bool done = false;						//a boolean value that tracks if a movement has been achieved
		if (this->getCurResistance() > 0)		//if this ship is able to function(its current resistance is >0
		{
			if (x + 1 <= ARRAYSIZEX - 1)		//if the x position is inside the map's bounds
			{
				if ((map->locations[x + 1][y].getHasShip() == true))		//if there is a ship nearby
				{
					if (findShip(x + 1, y, myVector)->getType() == 1)		//if the ship is a pirate ship
					{
						movement(0, map);			//make the exploration ship go up
						cout << "Ship " << this->getPositionInVector() << " has moved 1 block up in order to avoid a Pirate Ship " << endl;
						done = true;
					}
				}
				if ((map->locations[x + 1][y].getWeather() >= 7))		//if the nearby weather is greater that 7(bad weather conditions limit)
				{
					movement(0, map);
					cout << "Ship " << this->getPositionInVector() << " has moved 1 block up in order to avoid bad weather conditions " << endl;
					done = true;
				}
			}
		 if ((x - 1 >= 0)&&(!done))
			{
				if ((map->locations[x - 1][y].getHasShip() == true))
				{
					if (findShip(x - 1, y, myVector)->getType() == 1)
					{
						movement(2, map);
						cout << "Ship " << this->getPositionInVector() << " has moved 1 block down in order to avoid a Pirate Ship " << endl;
						done = true;
					}
				}
				if ((map->locations[x - 1][y].getWeather() >= 7))
				{
					movement(2, map);
					cout << "Ship " << this->getPositionInVector() << " has moved 1 block down in order to avoid bad weather conditions" << endl;
					done = true;
				}
			}
			 if ((y + 1 <= ARRAYSIZEY - 1)&&(!done))
			{
				if ((map->locations[x][y + 1].getHasShip() == true))
				{
					if (findShip(x, y + 1, myVector)->getType() == 1)
					{
						movement(3, map);
						cout << "Ship " << this->getPositionInVector() << " has moved 1 block to the left in order to avoid a Pirate Ship " << endl;
						done = true;
					}
				}
				if ((map->locations[x][y + 1].getWeather() >= 7))
				{
					movement(3, map);
					cout << "Ship " << this->getPositionInVector() << " has moved 1 block to the left in order to avoid a bad weather conditions " << endl;
					done = true;
				}
			}
			 if ((y - 1 >= 0) && (!done))
			{
				if (map->locations[x][y - 1].getHasShip() == true)
				{
					if (findShip(x, y - 1, myVector)->getType() == 1)
					{
						movement(1, map);
						cout << "Ship " << this->getPositionInVector() << " has moved 1 block to the right in order to avoid a Pirate Ship " << endl;
						done = true;
					}
				}
				if ((map->locations[x][y - 1].getWeather() >= 7))
				{
					movement(1, map);
					cout << "Ship " << this->getPositionInVector() << " has moved 1 block to the right in order to avoid bad weather conditions" << endl;
					done = true;
				}
			}
		}
	}

	/** The movement of exploration ships in order to avoid pirate ship or bad weather conditions. It is called by the method operation of the exploaration ship.
	@param myMap : the map of the simulation's world
	@param direction : the direction towards to a ship will move*/

	void movement(int direction, Map* myMap)
	{
		int x = this->getX();		//the current position of the ship on the x axis
		int y = this->getY();		//the current position of the ship on the y axis
		int Speed = 1;				//the speed of all exploration ships is by default set to 1
		switch (direction)			// this switch gets as a parameter a random value [1-4] and defines the movement of the ship
		{
		case 0:	 //up
			if (x - Speed >= 0)		//checks if the ship is on the corners of the map and if the movement is legal(index inside map's bounds
			{
				if (myMap->locations[x - Speed][y].isEmpty()) // if the new position has already a ship or a port the movement is cancelled* /																					
				{
					myMap->locations[x][y].setHasShip(false);				//the old position's variable hasShip is set to falsee
					this->setX(x - Speed);									//the position of the ship on the x axis is updated
					myMap->locations[x - Speed][y].setHasShip(true);		//the new position's variable hasShip is set to true
					this->setBlocksMoved(this->getBlocksMoved() + Speed);	//the total blocks moved is increased by 1
					break;
				}
			}
		case 1:	 //right
			if (y + Speed <= (ARRAYSIZEY - 1)){
				if (myMap->locations[x][y + Speed].isEmpty())
				{
					myMap->locations[x][y].setHasShip(false);
					this->setY(y + Speed);
					myMap->locations[x][y + Speed].setHasShip(true);
					this->setBlocksMoved(this->getBlocksMoved() + Speed);
					break;
				}
			}
		case 2:	 //down
			if (x + Speed <= ARRAYSIZEX - 1){
				if (myMap->locations[x + Speed][y].isEmpty())
				{
					myMap->locations[x][y].setHasShip(false);
					this->setX(x + Speed);
					myMap->locations[x + Speed][y].setHasShip(true);
					this->setBlocksMoved(this->getBlocksMoved() + Speed);
					break;
				}
			}
		case 3:	 //left
			if (((y - Speed) >= 0)){
				if (myMap->locations[x][y - Speed].isEmpty())
				{
					myMap->locations[x][y].setHasShip(false);
					myMap->locations[x][y - Speed].setHasShip(true);
					this->setY(y - Speed);
					this->setBlocksMoved(this->getBlocksMoved() + Speed);
					break;
				}
			}
		}
	}
};

/**The class that describes Naval Ships.It inherits class ExplorationShip*/

class NavalShip : public ExplorationShip
{
public:

	/** The default constructor of Naval ships. It initializes the treasure to 150 , max resistance to 300 ,speed to 1 and sets the type to 5*/

	NavalShip()
	{
		setTreasure(150);
		setMaxResistance(300);
		setCurResistance(getMaxResistance());
		setSpeed(1);
		setType(5);
	}

	/** The operation of naval ships. If there is a pirate ship nearby,the ship attacks it and either kills it or reduces the victim's resistance by the resistance of the naval ship.
	@param x : the position of the pirate ship on the x axis
	@param y : the position of the pirate ship on the y axis
	@param map : the map of the simulation's world
	@param myVector : the vector containing the created ships*/

	virtual void operation(int x, int y, Map* map, vector<Ship*> myVector)
	{
		bool flag = false;
		Ship* victim = NULL;
		if (this->getCurResistance() > 0)
		{
			if (x + 1 <= ARRAYSIZEX - 1){
				if ((map->locations[x + 1][y].getHasShip() == true))
				{
					victim = findShip(x + 1, y, myVector);
					if (victim->getCurResistance()>0)
						flag = true;
				}
			}
			if (x - 1 >= 0){
				if ((map->locations[x - 1][y].getHasShip() == true))
				{
					victim = findShip(x - 1, y, myVector);
					if (victim->getCurResistance()>0)
						flag = true;
				}
			}
			if (y + 1 <= ARRAYSIZEY - 1){
				if ((map->locations[x][y + 1].getHasShip() == true))
				{
					victim = findShip(x, y + 1, myVector);
					if (victim->getCurResistance()>0)
						flag = true;
				}
			}
			if (y - 1 >= 0){
				if ((map->locations[x][y - 1].getHasShip() == true))
				{
					victim = findShip(x, y - 1, myVector);
					if (victim->getCurResistance()>0)
						flag = true;
				}
			}
			if (flag)
			{
				if (victim->getType() == 1)		//if the victim is a pirate ship
				{
					int damage = victim->getCurResistance() - this->getCurResistance();
					if (damage > 0){			//if the pirate ship's resistance is greater that the one of the naval ship 
						PirateDamage += this->getCurResistance();					//the damage of the pirate ships is increased by the naval ship's resistance
						victim->setCurResistance(damage);							//the current resistance of the pirate ship is set to damage
						victim->setTotalDamage(victim->getTotalDamage() + damage);	//the total damage caused by the naval ship is increased
						this->setCurResistance(0);									//the naval ship is destroyed
						cout << "Ship " << this->getPositionInVector() << " has dealt  " << damage << " damage to Ship " << victim->getPositionInVector() << endl;
					}
					else
					{
						PirateDamage += victim->getCurResistance();				//the damage of the pirate ships is increased by the naval ship's resistance
						this->setCurResistance(-damage);						//the current resistance of the pirate ship is set to -damage
						this->setTotalDamage(this->getTotalDamage() + damage);	//is it correct?		//the total damage caused by the naval ship is increased
						cout << "Ship " << this->getPositionInVector() << " has dealt  " << victim->getCurResistance() << " damage to Ship " << victim->getPositionInVector() << endl;
						victim->setCurResistance(0);							//the pirate ship is destroyed

					}
				}
			}
		}
	}
};


/**The class that describes Submarines.It inherits class PirateShip*/

class Submarine : public PirateShip
{
private:
	int kills = 0;			//the number of ships killed by each submarine

public:

	/** The default constructor of Submarines. It initializes the treasure to 50 , max resistance to 300 ,speed to 1 and sets the type to 6*/

	Submarine()
	{
		setTreasure(50);
		setMaxResistance(300);
		setCurResistance(getMaxResistance());
		setSpeed(1);
		setType(6);
	}


	/** The operation of submarines. If there is a ship nearby,the submarine attacks it and either kills it or if it has already killed 3 ships it is automatically destroyed and its treasure is passed to the nearby ship.
	@param x : the position of the pirate ship on the x axis
	@param y : the position of the pirate ship on the y axis
	@param map : the map of the simulation's world
	@param myVector : the vector containing the created ships*/


	virtual void operation(int x, int y, Map* map, vector<Ship*> myVector)
	{
		if (this->getCurResistance() > 0)
		{
			Ship* victim = NULL;
			bool flag = false;
			if (x + 1 <= ARRAYSIZEX - 1){
				if (map->locations[x + 1][y].getHasShip() == true)
				{
					victim = findShip(x + 1, y, myVector);
					if (victim->getCurResistance()>0)
						flag = true;
				}
			}
			if (x - 1 >= 0){
				if (map->locations[x - 1][y].getHasShip() == true)
				{
					victim = findShip(x - 1, y, myVector);
					if (victim->getCurResistance()>0)
						flag = true;
				}
			}
			if (y + 1 <= ARRAYSIZEY - 1){
				if (map->locations[x][y + 1].getHasShip() == true) {
					victim = findShip(x, y + 1, myVector);
					if (victim->getCurResistance()>0)
						flag = true;
				}
			}
			if (y - 1 >= 0){
				if (map->locations[x][y - 1].getHasShip() == true)
				{
					victim = findShip(x, y - 1, myVector);
					if (victim->getCurResistance()>0)
						flag = true;
				}
			}
			if (flag)
			{
				if (this->getKills() < 3)		//checks if the submarine has already destroyed 3 ships
				{
					switch (victim->getType())	//increases the total damage of the victim 
					{
					case 1:
						PirateDamage += victim->getCurResistance();
						break;
					case 2:
						MerchantDamage += victim->getCurResistance();
						break;
					case 3:
						RepairDamage += victim->getCurResistance();
						break;
					case 4:
						ExplorationDamage += victim->getCurResistance();
						break;
					case 5:
						NavalDamage += victim->getCurResistance();
						break;
					case 6:
						SubMarineDamage += victim->getCurResistance();
						break;
					}
					this->setKills(this->getKills() + 1);											//the total kills are increased and act as a counter 
					victim->setTotalDamage(victim->getTotalDamage() + victim->getCurResistance());	//the total damage of the victim is increased by the victim's resistance 
					victim->setCurResistance(0);													//the victim is destroyed
					this->setTreasure(victim->getTreasure() + this->getTreasure());					//the victim's treasure is added to the one of the submarine
					victim->setTreasure(0);															//the victim's treasure is seto to 0
					cout << "Ship " << victim->getPositionInVector() << " has been damaged due to a battle with Ship " << this->getPositionInVector() << endl;
					cout << "Ship " << this->getPositionInVector() << " has acquired all the treasure of Ship " << victim->getPositionInVector() << endl;
				}
				else
				{
					SubMarineDamage += this->getCurResistance();								//the total damage of submarines is increased by the instance's resistance
					this->setTotalDamage(this->getTotalDamage() + this->getCurResistance());	//the total damage of the submarine is increased 
					this->setCurResistance(0);													//the submarine is destroyed 
					victim->setTreasure(this->getTreasure() + victim->getTreasure());			//the victim's treasure is increased
					this->setTreasure(0);														//the submarine's treasure is set to 0
					cout << "Ship " << victim->getPositionInVector() << " has acquired all the treasure of Ship " << this->getPositionInVector() << endl;
				}
			}
		}
	}

	/*******************************************************************************/
	/*****We use get-set methods, in case we want to act on a private variable*****/
	/*****************************************************************************/

	int getKills()
	{
		return this->kills;
	}
	void setKills(int kills)
	{
		this->kills = kills;
	}

	/*********************************/
	/*****End of get-set methods*****/
	/*******************************/
};

#endif // !ShipHeader
