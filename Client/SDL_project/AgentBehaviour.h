#pragma once
#include "BehaviourTree.h"
#include "Agent.h"

class AgentBehaviour
{
public:
	//! Constructor
	AgentBehaviour();
	// Destructor
	~AgentBehaviour();

	//! Bool that stores whether the level has a bed
	bool levelHasBed = false;
	//! A vector that stores empty bed locations
	std::vector<Point> emptyBedLocations;

	//! Bool that stores whether the level has a toilet
	bool LevelHasToilet = false;
	//! A vector that stores empty toilet locations 
	std::vector<Point> emptyToiletLocations;

	//! To Decide what task needs to be done
	void AgentBehaviour::DecideTask(Level& level, Agent& agent);


private:
	const double tirednessThreshold = 0.4;
	const double toiletThreshold = 0.2;
	const double hungerThreshold = 0.2;
};