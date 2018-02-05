#pragma once
#include "Point.h"
#include "Character.h"


class Agent : public Character
{
public:
	Agent();
	~Agent();

	Inventory inventory;


	//! Update method for Agent
	void Agent::Update(Level& level);
	//! Movement method for Agent
	void Agent::Move(Level& level, Point& StartPoint, Point& EndPoint);



	//! Character Type
	std::string characterType = "NPC";

	//!* CHARACTER PATHFINDING */
	//! Create an instance of pathfinder
	Pathfinder pathfinder;
	//! Conains the list of nodes that makes the path
	std::vector<Point> path;

	//! Contains what the current status of the agent is doing
	/*! Types of agent state: (Idle, FoundPath, Dead...)*/
	//std::string agentStatus = "Idle";
	enum agentMovementStatus { Idle, TraversingPath, Waiting };
	agentMovementStatus movementStatus = Idle;

	//! Contains what the agent needs to do the most
	/*! Types of agent state: (Food, WC, Bed...)*/
	enum agentServicesStatus { NA, Hungry, Tired, WC, Suffocating };
	agentServicesStatus agentNeed = NA;

	//! Position in the world
	glm::vec2 chunkPos, cellPos;
	glm::vec2 cellInteractionDirection;


	//! Gets and Sets the agents hunger
	double getHunger() { return hunger; }
	double setHunger(double newHunger) { return hunger = newHunger; }

	//! Gets and Sets the agents tiredness (Tiredness increaes from 0)
	double getTiredness() { return tiredness; }
	double setTiredness(double newTiredness) { return tiredness = newTiredness; }

	//! Gets and Sets the agents tiredness (Tiredness increaes from 0)
	double getToietNeed() { return toiletLevel; }
	double setToiletNeed(double newToiletNeed) { return toiletLevel = newToiletNeed; }

	//! Gets and Sets the agents oxygen level
	double getOxygenLevel() { return oxygenLevel; }
	double setOxygenLevel(double newOxygenLevel) { return oxygenLevel = newOxygenLevel; }

	//! Boolean for whether character is alive
	bool isAlive = true;

	bool agentWonderWhenIdle = false;

	bool agentCanRotate = true;
	

private:

	//! Double to store agent hunger
	double hunger = 1.0;
	//! Integer to store agent tiredness
	double tiredness = 0.0;
	//! A Double for toilet level
	double toiletLevel = 0.0;
	//! A int for the agents's stored oxygen
	double oxygenLevel = 100.0;

	//! A double for storing agents health decay rate
	double healthDecayRate = 0.1;
	//! A double for storing agents hunger decay rate
	double hungerDecayRate = 0.001;
	//! A double for toilet decay rate
	double toiletDecayRate = 0.0004;
	//! A double for storing agents tiredness decay rate
	double tirednessDecayRate = 0.00010;
	//! A double for storing agents oxygen decay rate
	double oxygenDecayRate = 0.01;

	//! Stores where the agent is along the path
	int pathPointIterator = 0;
};

