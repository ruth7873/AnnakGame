#pragma once

#ifdef _DEBUG
// the debug version that corresponds to the opencv_world420d.dll:
#pragma comment(lib, "opencv_world4100d.lib")
#else
// the release version that corresponds to the opencv_world420.dll:
#pragma comment(lib, "opencv_world4100.lib")
#endif

#include"Input.h"
#include"WorldMap.h"
#include "Map.h"
class Game
{
public:
	Game() {
		Input input;
		input.parse_and_store();
		WorldMap worldMap(input.world->data);
		Map m;
		m.printMat(WorldMap::map);
		worldMap.initMap(input.start);
		worldMap.doTurn(input.steps);
		worldMap.printAsserts(input.asserts);
	}
};