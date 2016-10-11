#ifndef MapInfo
#define MapInfo

#include "Location.h"

#define ARRAYSIZEX 9		//the size of the array on the x axis
#define ARRAYSIZEY 9		//the size of the array on the y axis
#define NUMBEROFSHIPS 12	//the number of the ships in the simulation
#define WIDTH 100
#define DAMAGEWEATHER 30	//the damage that is caused by bad weather conditions
#define TARGET 500			//the target of the simulation
#define DAMAGEPORT 30		//the damage that is caused by a port to pirate ships
#define HEALPORT 0.1		//the healing that takes place by a port to nearby ships

using namespace std;

/**The class that describes the map of the simulation*/

class Map
{
private:
	int numberOfPorts = 0;		//the number of ports that are created 
	int badWeather = 0;			//the places in the map whose weather variable is >7


public:
	Location** locations = new Location*[ARRAYSIZEX];		//a dynamic array of 2 dimensions

	/** The default constructor of the Map */

	Map()
	{
		for (int i = 0; i <ARRAYSIZEX; i++)
		{
			locations[i] = new Location[ARRAYSIZEX];
		}
		for (int i = 0; i < ARRAYSIZEX; i++)
		{
			for (int j = 0; j < ARRAYSIZEY; j++)
			{
				if (this->locations[i][j].getIsPort())
					this->setNumberOfPorts(this->getNumberOfPorts() + 1);		//the number of ports is increased by one if in a location a port exists 
				if (this->locations[i][j].getWeather()>7)
					this->setBadWeather(this->getBadWeather() + 1);				//the places with bad weather is increased by one 
			}
		}
	}

	/*******************************************************************************/
	/*****We use get-set methods, in case we want to act on a private variable*****/
	/*****************************************************************************/

	int getNumberOfPorts()
	{
		return numberOfPorts;
	}

	void setNumberOfPorts(int numberOfPorts)
	{
		this->numberOfPorts = numberOfPorts;
	}

	int getBadWeather()
	{
		return badWeather;
	}
	void setBadWeather(int badWeather)
	{
		this->badWeather = badWeather;
	}

	/*********************************/
	/*****End of get-set methods*****/
	/*******************************/
};




#endif // !Map