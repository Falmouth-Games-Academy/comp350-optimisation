#pragma once
#include "stdafx.h"
#include "NetworkClient.h"
#include "Agent.h"
#include "Player.h"
#include "Level.h"
#include "AgentManager.h"

class NetworkManager
{
public:
	NetworkManager();
	~NetworkManager();
	std::vector<std::shared_ptr<Player>> allPlayers;
	int getPlayer(std::string ID);
	void Connect();
	//! Main Network update function
	void NetworkUpdate(Level& level,Player& player, AgentManager& agentManager);
	//! Send a message using TCP
	void sendTCPMessage(std::string message);

	//! Process the players location from json
	void ProcessPlayerLocations(Level& level, AgentManager& agentManager, Player& player);
	//! Process cell data
	void MapNetworkUpdate(Level& level);
	//! Return a string from recieve message
	std::string RecieveMessage();

	void SpawnPlayer(Player& player);

	

	void NetworkManager::runMultiThread(std::shared_ptr<tcp::socket> socket, boost::asio::io_service& io_service);

	// Server connection deets
	int port = 2222;
	
	std::string ExternalIPAddress = "46.101.9.185";
	std::string InternalIPAddress = "127.0.0.1";

	//! Whether the client should connect to external server
	bool isServerLocal = true;
	//! Whether the client can enter their name in console
	bool clientCanEnterName = false;
	//! Whether the client should request playernumers
	bool GetNumPlayers = false;

	//! How frequent the client will update player positions
	int networkPlayerUpdateInterval = 50;
	//! How frequent the client will update the map from server
	int networkMapUpdateInterval = 1000;

	//! Stores the number of players in the game
	int numberOfPlayers = 0;

	// Values for the network update timer
	double lastTimeP = SDL_GetTicks();
	double lastTimeM = SDL_GetTicks();
	double timebehindP = 0;
	double timebehindM = 0;
	bool runPlayerNetworkTick = false;
	bool runMapNetworkTick = false;

	//! get and set server IP address
	std::string getServerIP() { return IPAddress; }
	std::string setServerIP(std::string newIP) { return IPAddress = newIP; }

	//! get and set server IP address
	std::string getPlayerName() { return localPlayerName; }
	std::string setPlayerName(std::string newPlayerName) { return localPlayerName = newPlayerName; }
	

	//! Vector of all other players names in the game
	std::vector<std::string> otherPlayerNames;

	//! the io service for creating the socket
	boost::asio::io_service io_service;
	std::shared_ptr<tcp::socket> socket;
	std::thread t;
	

private:
	//! for when I get round to making the client multi threaded
	std::vector<std::thread> some_threads;
	//! for ip Address
	std::string IPAddress;
	//! For the name of the local player
	std::string localPlayerName;
};

