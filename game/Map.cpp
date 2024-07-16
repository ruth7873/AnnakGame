#include "Map.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void Map::printMat(vector<vector<Cell>> worldMap) {
    // Load the first image to get the tile size
    Mat lilImage = imread(Routes::BLOCKS_MINE, IMREAD_UNCHANGED);
    if (lilImage.empty()) {
        cout << "Could not read the image: " << Routes::BLOCKS_MINE << endl;
        return;
    }

    int tileWidth = lilImage.cols;
    int tileHeight = lilImage.rows;
    int sizeWorldWidth = worldMap[0].size();
    int sizeWorldHeight = worldMap.size();

    // Create a blank canvas to draw the map
    Mat worldPicture(sizeWorldHeight * tileHeight, sizeWorldWidth * tileWidth, lilImage.type(), Scalar(255, 255, 255));

    // Loop through the map matrix and place each tile image on the canvas
    for (size_t i = 0; i < worldMap.size(); ++i) {
        for (size_t j = 0; j < worldMap[i].size(); ++j) {
            string imagePath = getImagePath(worldMap[i][j].getName());
            if (!imagePath.empty()) {
                // Load the tile image
                Mat tileImage = imread(imagePath, IMREAD_UNCHANGED);
                if (!tileImage.empty()) {
                    // Calculate the position to place the tile image
                    int xPos = j * tileWidth;
                    int yPos = i * tileHeight;

                    // Copy the tile image onto the canvas
                    tileImage.copyTo(worldPicture(Rect(xPos, yPos, tileWidth, tileHeight)));
                }
            }
        }
    }

    // Draw grid if the option is enabled
   
        Scalar gridColor = Scalar(0, 0, 0); // Black color
        int thickness = 1; // Line thickness

        // Draw vertical lines
        for (int i = 0; i <= sizeWorldWidth; ++i) {
            int x = i * tileWidth;
            line(worldPicture, Point(x, 0), Point(x, worldPicture.rows), gridColor, thickness);
        }

        // Draw horizontal lines
        for (int i = 0; i <= sizeWorldHeight; ++i) {
            int y = i * tileHeight;
            line(worldPicture, Point(0, y), Point(worldPicture.cols, y), gridColor, thickness);
        }

    // Display the map image
    namedWindow("Map", WINDOW_NORMAL);
    imshow("Map", worldPicture);
    waitKey(0); // Wait for a keystroke to close the window
}

string Map::getImagePath(string tileType) {
    return routesMap[tileType];
}



//#include "Map.h"
//void Map::printMat(vector<vector<Cell>> worldMap) {
//	// Load the first image to get the tile size
//	Mat lilImage = imread(Routes::BLOCKS_MINE, IMREAD_UNCHANGED);
//	if (lilImage.empty()) {
//		cout << "Could not read the image: " << Routes::BLOCKS_MINE << endl;
//		return;
//	}
//
//	int tileWidth = lilImage.cols;
//	int tileHeight = lilImage.rows;
//	int sizeWorldWidth = worldMap[0].size();
//	int sizeWorldHeight = worldMap.size();
//
//	// Create a blank canvas to draw the map
//	Mat worldPicture(sizeWorldHeight * tileHeight, sizeWorldWidth * tileWidth, lilImage.type(), Scalar(255, 255, 255));
//
//	// Loop through the map matrix and place each tile image on the canvas
//	for (size_t i = 0; i < worldMap.size(); ++i) {
//		for (size_t j = 0; j < worldMap[i].size(); ++j) {
//			for (size_t k = 0; k < 5; k++)
//			{
//				for (size_t l = 0; l < 5; l++)
//				{
//					string imagePath = (getImagePath(worldMap[i][j].getName()));
//					if (!imagePath.empty()) {
//						// Load the tile image
//						Mat tileImage = imread(imagePath, IMREAD_UNCHANGED);
//						if (!tileImage.empty()) {
//							// Calculate the position to place the tile image
//							int xPos = j * tileWidth;
//							int yPos = i * tileHeight;
//
//							// Copy the tile image onto the canvas
//							tileImage.copyTo(worldPicture(Rect(xPos, yPos, tileWidth, tileHeight)));
//						}
//					}
//				}
//			}
//
//		}
//	}
//
//	// Display the map image
//	namedWindow("Map", WINDOW_NORMAL);
//	imshow("Map", worldPicture);
//	waitKey(0); // Wait for a keystroke to close the window
//}
//string Map::getImagePath(string tileType) {
//	
//	return routesMap[tileType];
//	
//}