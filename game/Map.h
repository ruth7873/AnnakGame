#pragma once
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp> // include the necessary header for resize

#include "Routes.h"
#include "Cell.h"
#include <iostream>
#include <map>
using namespace std;
using namespace cv;

class Map
{
    unordered_map<string, string> routesMap = {
            {"Ground", "assets/TILES/tile_ground.png"},
            {"Water", "assets/TILES/tile_water.png"},
            {"Forest", "assets/TILES/tile_forest.png"},
            {"Field", "assets/TILES/tile_field.png"},
            {"IronMine", "assets/TILES/tile_iron_mine.png"},
            {"BlocksMine", "assets/TILES/tile_blocks_mine.png"},
            {"Road", "assets/TILES/tile_road.png"}
    };
public:
	void printMat(vector<vector<Cell>> worldMap);
	string getImagePath(string tileType);
};

