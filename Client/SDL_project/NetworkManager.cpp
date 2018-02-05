#include "stdafx.h"
#include "NetworkManager.h"

NetworkManager::NetworkManager()
{
}

NetworkManager::~NetworkManager()
{
}

void NetworkManager::Connect()
{
	socket = std::shared_ptr<tcp::socket>(new tcp::socket(io_service));
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(getServerIP()), port);
	socket->connect(endpoint);
	io_service.run();
}

//! Returns whether the player exists in the list of players
bool DoesPlayerExist(std::vector<std::string>& playerNames, std::string playername)
{
	// Return true if theres a match
	for (int i = 0; i < playerNames.size(); i++)
	{
		if (playername == playerNames[i])
			return true;
	}
	// Return false if no player with that name exists
	return false;
}
int NetworkManager::getPlayer(std::string ID)
{
	for (int i = 0; i < allPlayers.size(); i++)
	{
		if (ID == allPlayers[i]->getID())
		{
			return i;
		}
	}
}

void NetworkManager::SpawnPlayer(Player& player)
{
	auto playerPtr = std::make_shared<Player>(player);
	allPlayers.push_back(playerPtr);
}

//! main netwrok update function
void NetworkManager::NetworkUpdate(Level& level, Player& player, AgentManager& agentManager)
{
	// Interval Timer
	timebehindP += SDL_GetTicks() - lastTimeP;
	lastTimeP = SDL_GetTicks();

	// Interval Timer
	timebehindM += SDL_GetTicks() - lastTimeM;
	lastTimeM = SDL_GetTicks();

	// Update intervalTimer
	while (timebehindP >= networkPlayerUpdateInterval)
	{
		runPlayerNetworkTick = true;
		timebehindP -= networkPlayerUpdateInterval;
	}
	while (timebehindM >= networkMapUpdateInterval)
	{
		runMapNetworkTick = true;
		timebehindM -= networkMapUpdateInterval;
	}

	// Update network
	if (runPlayerNetworkTick)
	{
		runPlayerNetworkTick = false;
		ProcessPlayerLocations(level, agentManager, player);
	}
	if (runMapNetworkTick)
	{
		runMapNetworkTick = false;
		//Process the map data
		MapNetworkUpdate(level);
	}
}

void NetworkManager::ProcessPlayerLocations(Level& level, AgentManager& agentManager, Player& player)
{
	//Create the json to send to the server
	json playerData = player.getPlayerJson();


	sendTCPMessage("[PlayerUpdate]" + playerData.dump() + "\n");

	// process the list of players
	std::string updateData = RecieveMessage();

	// Remove anything at the end of the json string that isn't suppose to be there
	int endOfJsonString = updateData.find_last_of("}");
	int startOfJsonString = updateData.find_first_of("{");
	if(startOfJsonString >= 0)
	updateData.erase(updateData.begin(), updateData.begin() + startOfJsonString);
	if(endOfJsonString >= 0)
	updateData.erase(updateData.begin() + endOfJsonString + 1, updateData.end());

	try
	{
		json jsonData = json::parse(updateData.begin(), updateData.end());;
		json playerData = jsonData.at("PlayerData");

		for (auto& element : playerData)
		{
			// Player movement
			int x = element.at("X").get<int>();
			int y = element.at("Y").get<int>();
			int rotation = element.at("rotation").get<int>();
			std::string name = element.at("name").get<std::string>();
			bool isMoving = element.at("isMoving").get<bool>();

			// Player clothes
			int headWear = element.at("headWear").get<int>();
			int bodyWear = element.at("bodyWear").get<int>();
			int legWear = element.at("legWear").get<int>();

			// Hair and eye colour
			json hairColour = element.at("hairColour");
			json eyeColour = element.at("eyeColour");
			int hr = hairColour.at("r").get<int>();
			int hg = hairColour.at("g").get<int>();
			int hb = hairColour.at("b").get<int>();
			int er = eyeColour.at("r").get<int>();
			int eg = eyeColour.at("g").get<int>();
			int eb = eyeColour.at("b").get<int>();

			json bodyColour = element.at("bodyColour");
			int br = bodyColour.at("r").get<int>();
			int bg = bodyColour.at("g").get<int>();
			int bb = bodyColour.at("b").get<int>();
			json legsColour = element.at("legColour");
			int lr = legsColour.at("r").get<int>();
			int lg = legsColour.at("g").get<int>();
			int lb = legsColour.at("b").get<int>();

			// IF player exists update deets
			if (DoesPlayerExist(otherPlayerNames, name))
			{
				//Get players array number
				int val = getPlayer(name);
				allPlayers[val]->setEyeColour(er, eg, eb);
				allPlayers[val]->setHairColour(hr, hg, hb);
				allPlayers[val]->setJacketColour(br, bg, bb);
				allPlayers[val]->setJeansColour(lr, lg, lb);
				allPlayers[val]->PlayerClothes.head = (Player::Clothing::HeadWear)headWear;
				allPlayers[val]->PlayerClothes.body = (Player::Clothing::BodyWear)bodyWear;
				allPlayers[val]->PlayerClothes.leg = (Player::Clothing::LegWear)legWear;
				allPlayers[val]->setPlayerMoving(isMoving);
				allPlayers[val]->setX(x);
				allPlayers[val]->setY(y);
				allPlayers[val]->setTargetRotation(rotation);
			}
			//Create a new player
			else
			{
				if (name.size() > 1 && name != localPlayerName)
				{
					otherPlayerNames.push_back(name);
					Player newPlayer;
					newPlayer.setID(name);
					SpawnPlayer(newPlayer);
				}
			}
		}
	}
	catch (std::exception e)
	{
		std::cout << "Error processing player location data: " << e.what() << std::endl;
	}
}




//TODO: reimplement multi threaded networking
void NetworkManager::runMultiThread(std::shared_ptr<tcp::socket> socket, boost::asio::io_service& io_service)
{
	//std::thread readerThread;
	//boost::thread_group g;
	//g.create_thread(&NetworkManager::RecieveMessage);
	//g.join_all();
	//std::thread t2(this);
	//some_threads.push_back(t2);
	//std::string receiveMessage = RecieveMessage();
	//ProcessArrayOfPlayerLocations(receiveMessage, level, agentManager);

	//boost::thread_group g;
	//g.create_thread(&NetworkManager::RecieveMessage);
	//boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
	//g.create_thread([] { &NetworkManager::RecieveMessage; });
}




//! Process map network update
//Make sure the network send name is the same as the recieve
void NetworkManager::MapNetworkUpdate(Level& level)
{
	sendTCPMessage("[RequestMapUpdate]\n");
	//! What an empty map looks like
	std::string EmptyMap = "{\"MapData\":[]}\r\n";
	std::string mapData = RecieveMessage();
	if (mapData != EmptyMap)
	{
		// Remove anything at the end of the json string that isn't suppose to be there

		int endOfJsonString = mapData.find_last_of("}");
		int startOfJsonString = mapData.find_first_of("{");
		if (startOfJsonString >= 0)
			mapData.erase(mapData.begin(), mapData.begin() + startOfJsonString);
		int cellsUpdated = 0;

		try
		{
			json jsonData = json::parse(mapData.begin(), mapData.end());;
			json mapData = jsonData.at("MapData");

			// Range-based for loop to iterate through the map data
			for (auto& element : mapData)
			{
				
				Cell newCell;
				newCell = level.GetCellFromJson(element);
				level.SetCell(newCell.getX(), newCell.getY(), newCell);
				cellsUpdated++;
			}
			std::cout << "Cells Updated: " << cellsUpdated << std::endl;
		}
		catch (std::exception e)
		{
			std::cout << "Error processing map data: " << e.what() << std::endl;
		}
	}
}



//! Sends a tcp message to the socket
void NetworkManager::sendTCPMessage(std::string message)
{
	// Fill the buffer with the data from the string
	boost::array<char, 512> buf;
	for (int i = 0; i < message.size(); i++)
	{
		buf[i] = message[i];
	}
	//Try sending the data
	try
	{
		boost::system::error_code error;
		socket->write_some(boost::asio::buffer(buf, message.size()), error);

		//std::cout << "Message sent: " << message << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

std::string make_string(boost::asio::streambuf& streambuf)
{
	return { boost::asio::buffers_begin(streambuf.data()),
		boost::asio::buffers_end(streambuf.data()) };
}
//! returns a string from the socket
std::string NetworkManager::RecieveMessage()
{
	//Create return messages and an instream to put the buffer data into
	std::string returnMessage;
	std::stringstream inStream;
	try
	{
		boost::array<char, 128> buffer;
		boost::asio::streambuf read_buffer;
		 //bytes_transferred = boost::asio::write(*socket, write_buffer);
		 auto bytes_transferred = boost::asio::read_until(*socket, read_buffer, ("\r\n"));
		
		//std::cout << "Read: " << make_string(read_buffer) << std::endl;

		return returnMessage = make_string(read_buffer);

	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}
