#include "Ships.h"
#include <conio.h>
#include <windows.h>
#include <iomanip>
#include <algorithm>
#include <random>

int Ship::treasureAmount = 0;		//initialization of treasureAmount
int Ship::NumberOfShips = 0;		//initialization of NumberOfShips


/** The bubblesort algorithm. It is used in order to sort the ships by treasure , current resistance or type
@param myVector: the map containing the ships
@param select : defines the type of sorting that will happen*/


void BubbleSort(vector<Ship*> myVector, int select)
{
	if (myVector.size() != 0){
		Ship *temp1 = NULL;		//declaration of a temporary variable that will be used for bubblesorting
		for (unsigned int i = 0; i < myVector.size() - 1; ++i)
		{
			for (unsigned int j = 0; j < myVector.size() - 1 - i; ++j)
			{
				switch (select)
				{
				case 1://by treasure
					if (myVector[j + 1]->operator>(myVector[j]))
					{
						temp1 = myVector[j + 1];
						myVector[j + 1] = myVector[j];
						myVector[j] = temp1;
					}
					break;
				case 2://by cur resistance
					if (myVector[j]->getCurResistance() < myVector[j + 1]->getCurResistance())
					{
						temp1 = myVector[j + 1];
						myVector[j + 1] = myVector[j];
						myVector[j] = temp1;
					}
					break;
				case 3://by type
					if (myVector[j]->getType() < myVector[j + 1]->getType())
					{
						temp1 = myVector[j + 1];
						myVector[j + 1] = myVector[j];
						myVector[j] = temp1;
					}
					break;

				}
			}
		}

		for (unsigned int i = 0; i < myVector.size(); i++)		//result of the sorting printing 
		{
			cout << "Ship " << myVector[i]->getPositionInVector() << " --> ";
			switch (select)
			{
			case 1:
				cout << "Treasure : " << myVector[i]->getTreasure() << endl;
				break;
			case 2:
				cout << "Current Resistance : " << myVector[i]->getCurResistance() << endl;
				break;
			case 3:
				cout << "Type : " << myVector[i]->getType() << endl;
			}
			cout << endl;
		}
	}
	else          //if the vector is empty
		cout << "Cannot sort due to lack of ships !!" << endl;

}


/** It is used in order to visualize the simulaiton. It graphs, ships,ports,weather and treasure
@param xartis : the map of the simulation
@param ploia : the vector containing the ships
@param choice : the user's choice of what to be graphed */


void graph(Map* xartis, vector<Ship*> ploia, int choice)
{
	int i, j, k;
	for (i = 0; i < ARRAYSIZEX; i++)
	{
		for (k = 0; k < 2 * ARRAYSIZEX + 1; k++)
			cout << "-";
		cout << endl;
		cout << "|";
		switch (choice){
		case 1:
			for (j = 0; j < ARRAYSIZEY; j++)
			{
				if (xartis->locations[i][j].getHasShip())
				{
					Ship* test = new Ship();
					test = test->findShip(i, j, ploia);
					cout << test->getPositionInVector();
				}
				else
					cout << " ";
				cout << "|";
			}
			break;
		case 2:
			for (j = 0; j < ARRAYSIZEY; j++)
			{
				if (xartis->locations[i][j].getIsPort())
					cout << "*";
				else
					cout << " ";
				cout << "|";
			}
			break;
		case 3:
			for (j = 0; j < ARRAYSIZEY; j++)
			{
				cout << xartis->locations[i][j].getWeather();
				cout << "|";
			}
			break;
		case 4:
			for (j = 0; j < ARRAYSIZEY; j++)
			{
				if (xartis->locations[i][j].getHasTreasure())
					cout << xartis->locations[i][j].getTreasure();
				else
					cout << " ";
				cout << "|";
			}
			break;
		}
		cout << endl;
	}
	for (j = 0; j < 2 * ARRAYSIZEX + 1; j++)
		cout << "-";
	cout << endl;
}


/** The menu that contains the functionality of the simulation.
@param map : the map of the simulation
@param myVector : the vector containing the ship
@return a value that indicates if the simulation must end*/


bool menu(Map* &map, vector <Ship*> &myVector)
{
	int choice;				//the choice of the user to be passed in various functions
	int x;					//a x coordinate on the map
	int y;					//a y coordiante on the map
	int select;				//the selection of the user in the main menu
	int amount;				//the amount of treasure to be added or removed from a location
	bool done = false;		//the variable that tracks if the game is finished 
	Ship* ploio = NULL;		//a variable of type ship*
	vector <Ship*> temp;	// a vector that will act as a "mirror" for the vector containing the ships
	cout << "\n*** MENU ***" << endl;
	cout << endl;
	cout << "1 : Continue Simulation" << endl;
	cout << "2 : Get Information about a ship" << endl;
	cout << "3 : Get Information about a position on the map" << endl;
	cout << "4 : Get Information about a type of ship" << endl;
	cout << "5 : General Information" << endl;
	cout << "6 : Add / Remove a Ship" << endl;
	cout << "7 : Modify a position on the map" << endl;
	cout << "8 : Graph" << endl;
	cout << "9 : Sort Ships" << endl;
	cout << "10 : End Game" << endl;
	cin >> select;
	switch (select)
	{
	case 1:
		for (int i = 0; i < ARRAYSIZEX; i++)
		{
			for (int j = 0; j < ARRAYSIZEY; j++)
			{
				if (map->locations[i][j].getWeather() > 7)			//check for weather greater than 7 in every location
				{
					if (map->locations[i][j].getHasShip())			//if in that location happens to be a ship
					{
						ploio = ploio->findShip(i, j, myVector);	//find which ship lies there
						ploio ->operator-- (DAMAGEWEATHER);			//use of overloaded operator -- in order to decrease the resistance of the ship
						switch (ploio->getType())					//increase the victim's type total damage by DAMAGEWEATHER
						{
						case 1:
							PirateDamage += DAMAGEWEATHER;
							break;
						case 2:
							MerchantDamage += DAMAGEWEATHER;
							break;
						case 3:
							RepairDamage += DAMAGEWEATHER;
							break;
						case 4:
							ExplorationDamage += DAMAGEWEATHER;
							break;
						case 5:
							NavalDamage += DAMAGEWEATHER;
							break;
						case 6:
							SubMarineDamage += DAMAGEWEATHER;
							break;
						}
					}
				}

				if (map->locations[i][j].getHasTreasure() == true)	//check if in that location treasure exists
				{
					if (map->locations[i][j].getHasShip())			//check if there lies a ship
					{
						ploio = ploio->findShip(i, j, myVector);										//if there is a ship ,return it
						ploio->setTreasure(ploio->getTreasure() + map->locations[i][j].getTreasure());	//increase the ship's treasure by the treasure of the location
						Ship::treasureAmount += map->locations[i][j].getTreasure();						//increase the total amount of the gathered treasure by the afformentioned amount
						cout << "Ship " << ploio->getPositionInVector() << " gathered treasure ( " << map->locations[i][j].getTreasure() << " coins) !!" << endl;
					}
				}

				/*Interaction of ships with ports.*/
				bool done = false;
				if (i + 1 <= ARRAYSIZEX - 1)
				{
					if ((map->locations[i + 1][j].getHasShip() == true))
					{
						ploio = ploio->findShip(i + 1, j, myVector);
						done = true;
					}
				}
				if (i - 1 >= 0)
				{
					if ((map->locations[i - 1][j].getHasShip() == true))
					{
						ploio = ploio->findShip(i - 1, j, myVector);
						done = true;
					}
				}
				if (j + 1 <= ARRAYSIZEY - 1)
				{
					if ((map->locations[i][j + 1].getHasShip() == true))
					{
						ploio = ploio->findShip(i, j + 1, myVector);
						done = true;
					}
				}
				if (j - 1 >= 0)
				{
					if ((map->locations[i][j - 1].getHasShip() == true))
					{
						ploio = ploio->findShip(i, j - 1, myVector);
						done = true;
					}
				}
				if (done){		//if a ship has been found
					if (ploio->getType() == 1)	//if the ship found is a pirate ship
					{
						ploio->setCurResistance(ploio->getCurResistance() - DAMAGEPORT);	//damage it by DAMAGEPORT
						ploio->setTotalDamage(ploio->getTotalDamage() + DAMAGEPORT);		//increase its total damage 
						PirateDamage += DAMAGEPORT;											//increase the total damage of pirate ships
						cout << "Ship " << ploio->getPositionInVector() << " has been damaged due to an attempted approach to a port" << endl;
					}
					else		//if the ship is not a pirate ship
					{
						if (ploio->getCurResistance() + (double)HEALPORT*ploio->getCurResistance() <= ploio->getMaxResistance())//if by healing it by HEALPORT it doesn't reach its maximum resistance
							ploio->operator+(HEALPORT);								//heal it using operator overloading
						else
							ploio->setCurResistance(ploio->getMaxResistance());		//set its current resistance to the maximum that it can reach
						cout << "Ship " << ploio->getPositionInVector() << " has been repaired in a port (new Resistance :" << ploio->getCurResistance() << ")" << endl;
					}
				}
			}
		}
		for (unsigned int i = 0; i < myVector.size(); i++)		//calling of movement method of every ship
			myVector[i]->movement(myVector[i]->getX(), myVector[i]->getY(), myVector[i]->getSpeed(), map);
		for (unsigned int i = 0; i < myVector.size(); i++)		//calling of operation method of every ship
			myVector[i]->operation(myVector[i]->getX(), myVector[i]->getY(), map, myVector);

		for (unsigned int i = 0; i < myVector.size(); i++)
		{
			if (myVector[i]->getCurResistance() <= 0)		//check if a ship has current resistance <=0 in order to be deleted 
			{
				map->locations[myVector[i]->getX()][myVector[i]->getY()].setHasShip(false);							//set the variable hasShip false in that location
				map->locations[myVector[i]->getX()][myVector[i]->getY()].setHasTreasure(true);						//set the variable hasTreasure to true in that location
				map->locations[myVector[i]->getX()][myVector[i]->getY()].setTreasure(myVector[i]->getTreasure());	//set the treasure in that location to the ship's treasure
				delete (myVector[i]);																				//call the destructor of the ship
				myVector.erase(myVector.begin() + i);																//erase the ship from the vevtor
			}
		}
		map->setBadWeather(0);	//reseting of the counter that tracks locations with weather >7
		for (int i = 0; i < ARRAYSIZEX; i++)
		{
			for (int j = 0; j < ARRAYSIZEY; j++)
			{
				map->locations[i][j].weatherChange();				//change the weather in every location
				if (map->locations[i][j].getWeather()>7)
					map->setBadWeather(map->getBadWeather() + 1);	//count the locations with weather >7
			}
		}

		if (myVector.size() == 0)		//if the vector is empty end the simulation
		{
			cout << "End of simulation due to lack of ships!!" << endl;
			return true;

		}
		temp = myVector;	//copying of the vector containing the ships
		for (unsigned int i = 0; i < myVector.size() - 1; ++i)	//sort the ships by treasure in order to check if any ship has reached the treasure target
		{
			for (unsigned int j = 0; j < myVector.size() - 1 - i; ++j)
			{
				if (temp[j]->getTreasure() > temp[j + 1]->getTreasure())
				{
					ploio = temp[j + 1];
					temp[j + 1] = temp[j];
					temp[j] = ploio;
				}
			}
		}
		if (temp[myVector.size() - 1]->getTreasure() >= TARGET)		//if a ship with treasure greater that TARGET has been found
		{
			cout << "\nShip " << temp[myVector.size() - 1]->getPositionInVector() << " has won!! (treasure = " << temp[myVector.size() - 1]->getTreasure() << ")" << endl;
			temp[myVector.size() - 1]->printInfo();	//show information abou the ship
			switch (temp[myVector.size() - 1]->getType())
			{
			case 1:
				cout << "Total damage caused : " << static_cast<PirateShip*>(temp[myVector.size() - 1])->getCausedDamage() << endl;
				break;
			case 2:
				cout << "Total treasure gathered from ports : " << static_cast<MerchantShip*>(temp[myVector.size() - 1])->getPortTreasure() << endl;
				break;
			case 3:
				cout << "Total treasure gathered from healing : " << static_cast<RepairShip*>(temp[myVector.size() - 1])->getTotalHeal() << endl;
				break;
			}
			return true;
		}
		return false;
		break;
	case 2:		//printing of information about one or multiple ships by calling each instance's printInfo()
		cout << "Enter the number of the ship whose information are to be shown or -1 to print info about all the ships" << endl;
		cin >> choice;
		if (choice == -1){
			for (unsigned int i = 0; i < myVector.size(); i++)
			{
				cout << myVector[i];
				switch (myVector[i]->getType())
				{
				case 1:
					cout << "Total damaged caused : " << static_cast<PirateShip*>(myVector[i])->getCausedDamage() << endl;;
					break;
				case 2:
					cout << "Total treasure gathered from ports : " << static_cast<MerchantShip*>(myVector[i])->getPortTreasure() << endl;
					break;
				case 3:
					cout << "Total treasure gathered from healing : " << static_cast<RepairShip*>(myVector[i])->getTotalHeal() << endl;
					break;
				}
				done = true;
				cout << endl;
			}

		}
		else{
			for (unsigned int i = 0; i < myVector.size(); i++)
			{
				if (myVector[i]->getPositionInVector() == choice){
					cout << myVector[i];
					switch (myVector[i]->getType())
					{
					case 1:
						cout << "Total damage caused : " << static_cast<PirateShip*>(myVector[i])->getCausedDamage() << endl;;
						break;
					case 2:
						cout << "Total treasure gathered from ports : " << static_cast<MerchantShip*>(myVector[i])->getPortTreasure() << endl;
						break;
					case 3:
						cout << "Total treasure gathered from healing : " << static_cast<RepairShip*>(myVector[i])->getTotalHeal() << endl;
						break;
					}
					done = true;
					cout << endl;
					break;
				}

			}
		}
		if (!done)
			cout << "Ship not found!" << endl;
		return false;
		break;
	case 3:		//printing of information about a location of the map.
		cout << "Enter the x position of the ship : ";
		cin >> x;
		cout << "Enter the y position of the ship : ";
		cin >> y;
		cout << endl;
		if (x >= 0 && x <= ARRAYSIZEX - 1 && y >= 0 && y <= ARRAYSIZEY - 1)
			map->locations[x][y].printInfo();
		else
			cout << "Index out of bounds" << endl;
		return false;
		break;
	case 4:	//printin of information about a type of ship
		cout << "Enter the type of the ship whose information are to be shown" << endl;
		cout << "   1 ---> PirateShip " << endl;
		cout << "   2 ---> MerchantShip" << endl;
		cout << "   3 ---> RepairShip" << endl;
		cout << "   4 ---> ExplorationShip" << endl;
		cout << "   5 ---> NavalShip" << endl;
		cout << "   6 ---> Submarine" << endl;
		cin >> choice;
		if (choice > 0 && choice < 7)
		{
			for (unsigned int i = 0; i < myVector.size(); i++)
			{
				if (myVector[i]->getType() == choice){
					{
						cout << myVector[i];
						cout << endl;
					}
					cout << endl;
					done = true;
				}
			}
			if (!done)
				cout << "Ship not found!" << endl;
			switch (choice)
			{
			case 1:
				cout << "Total damage of pirate ships : " << PirateDamage << endl;
				break;
			case 2:
				cout << "Total damage of merchant ships : " << MerchantDamage << endl;
				break;
			case 3:
				cout << "Total damage of repairships : " << RepairDamage << endl;
				break;
			case 4:
				cout << "Total damage of exploration ships : " << ExplorationDamage << endl;
				break;
			case 5:
				cout << "Total damage of naval ships : " << NavalDamage << endl;
				break;
			case 6:
				cout << "Total damage of submarines : " << SubMarineDamage << endl;
				break;
			}
		}
		else
		{
			cout << "Choice not available! " << endl;
		}
		return false;
	case 5:		//printing of general information about the simulation
		cout << "1 : Number of locations with bad weather conditions " << endl;
		cout << "2 : Number of locations with ports" << endl;
		cout << "3 : Total amount of gathered treasure" << endl;
		cin >> choice;
		if (choice == 3)
			cout << Ship::treasureAmount << endl;
		else if (choice == 2)
			cout << map->getNumberOfPorts() << endl;
		else if (choice == 1)
			cout << map->getBadWeather() << endl;
		else
			cout << "Not Available Choice!" << endl;
		return false;
	case 6:
		system("cls");
		cout << "1 : Add Ship" << endl;
		cout << "2 : Remove Ship" << endl;
		cout << "3 : Remove All Ships" << endl;
		cin >> choice;
		if (choice == 1)
		{
			do{
				cout << "Enter the Type of of the ship to be added" << endl;
				cout << "   1 ---> PirateShip" << endl;
				cout << "   2 ---> MerchantShip" << endl;
				cout << "   3 ---> RepairShip" << endl;
				cout << "   4 ---> ExplorationShip" << endl;
				cout << "   5 ---> NavalShip" << endl;
				cout << "   6 ---> Submarine" << endl;
				cin >> choice;
			} while (choice < 1 || choice > 6);
			switch (choice) //depending on the user's choice a ship is pushed back in the vector
			{
			case 1:
				myVector.push_back(new PirateShip());
				Ship::NumberOfShips++;
				break;
			case 2:
				myVector.push_back(new MerchantShip());
				Ship::NumberOfShips++;
				break;
			case 3:
				myVector.push_back(new RepairShip());
				Ship::NumberOfShips++;
				break;
			case 4:
				myVector.push_back(new ExplorationShip());
				Ship::NumberOfShips++;
				break;
			case 5:
				myVector.push_back(new NavalShip());
				Ship::NumberOfShips++;
				break;
			case 6:
				myVector.push_back(new Submarine());
				Ship::NumberOfShips++;
				break;
			}
			myVector[myVector.size() - 1]->setLocation(map);	//the is placed in a random location that has been empty 
			myVector[myVector.size() - 1]->setPositionInVector(Ship::NumberOfShips - 1);		//the ship is given an identifier
		}
		else if (choice == 2)
		{
			cout << "Choose Ship to be destroyed!" << endl;
			cin >> choice;
			done = false;
			for (unsigned int i = 0; i < myVector.size(); i++)
			{
				if (choice == myVector[i]->getPositionInVector())	//if the choice is matched in the vector
				{
					map->locations[myVector[i]->getX()][myVector[i]->getY()].setHasShip(false);							//the hasShip variable in that location is turned to false
					map->locations[myVector[i]->getX()][myVector[i]->getY()].setHasTreasure(true);						//the hasTreasure variable is turned to true
					map->locations[myVector[i]->getX()][myVector[i]->getY()].setTreasure(myVector[i]->getTreasure());	//the treasure of the ship is placed on that location
					delete (myVector[i]);																				//the destructor of the ship is called 
					myVector.erase(myVector.begin() + i);																//the ship is erased from the vector
					done = true;
				}
			}
			if (!done)
				cout << "Ship not found!" << endl;
		}
		else if (choice == 3)
		{
			for (unsigned int i = 0; i < myVector.size(); i++)
			{
				map->locations[myVector[i]->getX()][myVector[i]->getY()].setHasShip(false);
				map->locations[myVector[i]->getX()][myVector[i]->getY()].setHasTreasure(true);
				map->locations[myVector[i]->getX()][myVector[i]->getY()].setTreasure(myVector[i]->getTreasure());
			}
			myVector.clear();	//all the ships are cleared from the vector
		}
		return false;
	case 7:
		system("cls");
		do{
			cout << "Enter x position : ";
			cin >> x;
		} while (x<0 || x>ARRAYSIZEX - 1);
		do{
			cout << "Enter y position : ";
			cin >> y;
		} while (y<0 || y>ARRAYSIZEY - 1);
		cout << endl;
		cout << "1 : Add Port" << endl;
		cout << "2 : Remove Port" << endl;
		cout << "3 : Add Treasure" << endl;
		cout << "4 : Remove Treasure" << endl;
		cin >> select;
		switch (select)
		{
		case 1:
			if (map->locations[x][y].getIsPort())	//if a port already exists there 
				cout << "Port already exists there" << endl;
			else
			{
				map->locations[x][y].setIsPort(true);	//set the variable IsPort to true
				map->setNumberOfPorts(map->getNumberOfPorts() + 1);		//increase the number of ports
			}
			break;
		case 2:
			if (!(map->locations[x][y].getIsPort()))
				cout << "Port doesn't exist there" << endl;	//if there isn't a port ot be deleted 
			else
			{
				map->locations[x][y].setIsPort(false);					//set the variable isPort to false
				map->setNumberOfPorts(map->getNumberOfPorts() - 1);		//decrease the number of ports
			}
			break;
		case 3:
			do{
				cout << "Enter amount of treasure to be added: ";
				cin >> amount;		//enter amount 
			} while (amount < 0);
			if (map->locations[x][y].getHasTreasure())												//if in the specified location treasure exists
				map->locations[x][y].setTreasure(map->locations[x][y].getTreasure() + amount);		//the entered amount of treasure is added to the existing one
			else
			{
				map->locations[x][y].setHasTreasure(true);		//the hasTreasure in the specified location becomes true 
				map->locations[x][y].setTreasure(amount);		//the entered amount is placed in the specified position
			}
			break;
		case 4:
			do{
				cout << "Enter amount of treasure to be removed: ";
				cin >> amount;
			} while (amount < 0);
			if (map->locations[x][y].getHasTreasure()) //if there is treasure in the specified position
			{
				if (map->locations[x][y].getTreasure() - amount > 0)	//if the subtraction returns >0
					map->locations[x][y].setTreasure(map->locations[x][y].getTreasure() - amount);	//the entered amount is subtracted 
				else
					map->locations[x][y].setTreasure(0);	//else the treasure is set to 0 
			}
			else
			{
				map->locations[x][y].setHasTreasure(true);  //the hasTreasure is set to true 
				map->locations[x][y].setTreasure(0);		//the treasure in that position is set to 0
			}
			break;
		}
		return false;
	case 8:
		do{
			cout << "1 : Graph Ships" << endl;
			cout << "2 : Graph Ports" << endl;
			cout << "3 : Graph Weather" << endl;
			cout << "4 : Graph Treasure" << endl;
			cin >> choice;
		} while (choice < 0 || choice>4);	//check if the current choice is valid	
		graph(map, myVector, choice);
		return false;
	case 9:
		do{
			cout << "Sort ships by" << endl;
			cout << "1 : Treasure" << endl;
			cout << "2 : Current Resistance " << endl;
			cout << "3 : Type" << endl;
			cin >> choice;
		} while (choice < 0 || choice>3);		//check if the given choice is valid
		BubbleSort(myVector, choice);
		return false;
	case 10:
		return true;
	default:
		cout << "Option not available!" << endl;
		return false;
	}
}


int main()
{
	char ch;
	do{
		//int choice = 0;
		cout << "Please wait while the map and the ships are being initialized!" << endl;
		Map* xartis = new Map();
		vector<Ship*> myVector;
		Ship* ploio = new Ship();
		srand((unsigned int)time(NULL));
		for (int i = 0; i < NUMBEROFSHIPS; i++)		//2 ships of each type are added to the vector
		{
			if (i <= 1)
				myVector.push_back(new PirateShip());
			else if (i <= 3)
				myVector.push_back(new MerchantShip());
			else if (i <= 5)
				myVector.push_back(new ExplorationShip());
			else if (i <= 7)
				myVector.push_back(new RepairShip());
			else if (i <= 9)
				myVector.push_back(new NavalShip());
			else
				myVector.push_back(new Submarine());
			myVector[i]->setLocation(xartis);					// a location is assigned to each ship
		}
		random_shuffle(myVector.begin(), myVector.end());		// the vector is shuffled in order to ensure the randomness of the game 
		for (unsigned int i = 0; i < myVector.size(); i++){
			myVector[i]->setPositionInVector(i);				//each ship is assigned a unique id
			Ship::NumberOfShips++;								//the static variable that counts the number of ships is increased
		}
		system("cls");
		bool done = true;
		do{		//the menu is repeatedly called until 10 is given(true is returned)
			done = menu(xartis, myVector);
		} while (!done);
		cout << "Play again (y / n)? ";
		cin >> ch;
	} while (ch == 'y');	//if "1" is pressed , the while loop is accessed again and the simulation starts again
}

