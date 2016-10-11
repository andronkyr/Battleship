#ifndef LocationInfo
#define LocationInfo

#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

/**The class that describes each location of the simulation. It is used as a base for the map as it defines the functionality of every point on the map*/

class Location	{
private:
	int weather = 0;
	int treasure = 0;
	bool hasTreasure = false;
	bool isPort = false;
	bool hasShip = false;

public:

	/** The default constructor of each Location. It sets the weather and the treasure of each point*/

	Location()
	{
		srand((unsigned int)time(0));		//initialization of the seed of random function 
		weather = rand() % 10 + 1;			//The variable weather takes random values [1,10]

		if (rand() % 9 == 1)				//If the function random with values [0,8] returns us the value 1, then in the specific point there is a treasure.
		{
			hasTreasure = true;				//Specificaly, there is a 1/8 probability this point is a treasure.
			treasure = rand() % 101 + 50;	//The variable treasure takes random values [50,150]
		}
		else
			hasTreasure = false;

		if (rand() % 10 == 1)				//If the function random with values [0,9] returns us the value 1, then in the specific point there is a port.
			isPort = true;					//Specificaly, there is a 10% probability this point is a port.
		else
			isPort = false;
		Sleep(1000);							//it is used in order to change the seed
	}


	/** Changes the weather after the end of each round. */

	void weatherChange()
	{
		srand((unsigned int)time(0));
		if ((rand() % 2 == 1) && (this->getWeather() < 10))
			this->setWeather(this->getWeather() + 1);
		else if ((rand() % 2 == 0) && (this->getWeather() > 1))
			this->setWeather(this->getWeather() - 1);
		else if (this->getWeather() == 10)
			this->setWeather(9);
		else if (this->getWeather() == 1)
			this->setWeather(2);
	}

	/**Checks if a location object is port or has a ship, if not it returns true */

	bool isEmpty()
	{
		bool available = false;
		if ((this->getIsPort() == false) && (this->getHasShip() == false))
			available = true;
		return available;
	}

	/** Prints information about a point on the map. More specifically it prints the amount of treasure a location has, the weather that there is and if the location has a ship or a port,too*/

	void printInfo()
	{
		cout << "Treasure : " << this->getTreasure() << endl;
		cout << "Weather : " << this->getWeather() << endl;
		cout << "Has Ship : ";
		if (this->getHasShip())
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
		cout << "Has Port : ";
		if (this->getIsPort())
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}

	/*******************************************************************************/
	/*****We use get-set methods, in case we want to act on a private variable*****/
	/*****************************************************************************/

	int getWeather()
	{
		return weather;
	}

	void setWeather(int weather)
	{
		this->weather = weather;
	}

	int getTreasure()
	{
		return  treasure;
	}

	void setTreasure(int treasure)
	{
		this->treasure = treasure;
	}

	bool getHasTreasure()
	{
		return hasTreasure;
	}

	void setHasTreasure(bool hasTreasure)
	{
		this->hasTreasure = hasTreasure;
	}

	bool getIsPort()
	{
		return isPort;
	}

	void setIsPort(bool isPort)
	{
		this->isPort = isPort;
	}

	void setHasShip(bool hasShip)
	{
		this->hasShip = hasShip;
	}

	bool getHasShip()
	{
		return hasShip;
	}

	/*********************************/
	/*****End of get-set methods*****/
	/*******************************/

};

#endif // !LocationInfo