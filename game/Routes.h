#pragma once

#pragma once
#ifdef _DEBUG
// the debug version that corresponds to the opencv_world420d.dll:
#pragma comment(lib, "opencv_world4100d.lib")
#else
// the release version that corresponds to the opencv_world420.dll:
#pragma comment(lib, "opencv_world4100.lib")
#endif


#include <string>
using namespace std;
class Routes
{
public:
	static const string GROUND;
	static const string FOREST;
	static const string FIELD;
	static const string WATER;
	static const string ROAD;
	static const string IRON_MINE;
	static const string BLOCKS_MINE;
};
