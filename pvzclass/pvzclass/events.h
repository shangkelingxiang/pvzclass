#pragma once
#define InvokeEvent(a,b) {for(int i=0;i<a.size();i++)a[i](b);}
#include "PVZ.h"
#include <vector>
#include <queue>
typedef PVZ::Plant Plant;
typedef PVZ::Zombie Zombie;
typedef PVZ::Projectile Projectile;
typedef std::vector<void (*)(Plant*)> vecplant;
typedef std::vector<void (*)()> vecvoid;
typedef std::vector<void (*)(int)> vecint;
typedef std::vector<void (*)(Zombie*)> veczombie;
typedef std::vector<void (*)(Projectile*)> vecproj;

/*
**testing**
The EventHandler API
*/

class EventHandler
{
private:
	PVZ* pvz;
	std::vector<Plant*> GetAllPlants();
	std::vector<Zombie*> GetAllZombies();
	std::vector<Projectile*> GetAllProjectiles();//wait for Projectile event
	std::vector<Plant*> PlantList;
	std::vector<Zombie*> ZombieList;
	std::vector<Projectile*> ProjectileList;//wait for projectile event
	int Address;
	bool Started;
	bool IsStarted;
	/*Starts the events.*/
	vecplant    FunctionPlantPlantEvent;
	vecplant    FunctionPlantRemoveEvent;
	vecplant    FunctionPlantUpgradeEvent;
	vecvoid     FunctionLevelOpenEvent;
	vecvoid     FunctionLevelCloseEvent;
	vecint      FunctionLevelWaveEvent;
	vecvoid	    FunctionLevelStartEvent;
	veczombie   FunctionZombieSpawnEvent;
	veczombie   FunctionZombieRemoveEvent;
	veczombie   FunctionZombieDeathEvent;
	vecproj     FunctionProjectileFireEvent;
	vecproj     FunctionProjectileRemoveEvent;
	/*end of the events.*/
	void Update()
	{
		UpdateLevels();
		//For some reason, we should first invoke
		UpdatePlants();
		UpdateZombies();
		UpdateProjectiles();
	}
	void UpdatePlants();
	void UpdateLevels();
	void UpdateZombies();
	void UpdateProjectiles();
	
public:
	EventHandler(PVZ* pvz)
	{
		this->pvz = pvz;
		Address = 0;
		Started = 0;
		IsStarted = 0;
	}
	~EventHandler()
	{

	}
	void Run()
	{
		Update();
	}
	/*Starts the events.*/
	/*You should never access ANY api in Remove event.*/
	void	RegisterPlantPlantEvent(void function(Plant*));
	void	RegisterPlantRemoveEvent(void function(Plant*));
	void	RegisterPlantUpgradeEvent(void function(Plant*));
	void	RegisterLevelOpenEvent(void function());
	void	RegisterLevelCloseEvent(void function());
	void	RegisterLevelWaveEvent(void function(int));
	void    RegisterLevelStartEvent(void function());
	void	RegisterZombieSpawnEvent(void function(Zombie*));
	void	RegisterZombieRemoveEvent(void function(Zombie*));
	void    RegisterProjectileFireEvent(void function(Projectile*));
	void    RegisterProjectileRemoveEvent(void function(Projectile*));
	/*end of the events.*/
};
