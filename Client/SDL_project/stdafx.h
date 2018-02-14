// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <SDL_image.h>
#include <SDL.h>






// Additional headers
#include <iostream>
#include <memory>
#include <map>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <queue>
#include <set>
#include <list>
#include <math.h>
#include <fstream>
#include <thread>
#include <numeric>
#include <random>

#define PI 3.14159265

// Graphics headers
#include <glm.hpp>
#include <GL\glew.h>

//SDL TTF for writing to screen
#include <SDL_ttf.h>


// Networking headers
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/write.hpp>
#include <boost/bind.hpp>
using boost::asio::ip::tcp;

// json parser
#include "json.hpp"
using json = nlohmann::json;