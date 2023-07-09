#include "RasterSurface.h"
#include "XTime.h"
#include <vector>

#include <random>

#include "Globals.h"
#include "ImageExtractor.h"
#include <iostream>

#include <thread>



Globals* Globals::instance = 0;
static XTime timer;


int main() {
	
	

	if (RS_Initialize("Tyler Reber", WIDTH, HEIGHT)) {

		Globals* RasterData = RasterData->GetGlobalsInstance();

		int convert2d_to_1d = 112 * 400 + 336;
		ImageExtractor* groundTile = new ImageExtractor(convert2d_to_1d, 32, 32, floor_tiles);
		ImageExtractor* blue_building = new ImageExtractor(16 * 400 + 16, 96, 82, floor_tiles);
		ImageExtractor* flower = new ImageExtractor(192 * 400 + 48, 16, 16, floor_tiles);

		Animator* flame = new Animator(0, 128, 128, fire);
		Animator* spell = new Animator(0, 64, 64, skull);

		//Place 10 Flower randomly on Raster
		std::vector<int> flowerIndexes;
		srand(time(NULL));
		for (int i = 0; i < 10; i++) {
			int random_x = std::rand() % (WIDTH - 32) + 16;
			int random_y = std::rand() % (HEIGHT - 32) + 16;
			flowerIndexes.push_back(random_y * WIDTH + random_x);
		}
		timer.Restart();
		//Correct Race Condition
		std::this_thread::sleep_for(std::chrono::milliseconds(100));


		float fps_30 = 1.0f / 30.0f;
		float fps_10 = 1.0f / 15.0f;


		while (true) {

			timer.Signal();

			if (timer.TotalTime() >= fps_30) {

				//Tiles the Background
				RasterData->TileBackground(groundTile);

				//Overwrites a block of values in the raster to draw on top of the background
				
				int Raster_Draw_Location = 16075;
				RasterData->TransferBlock(blue_building, Raster_Draw_Location);

				for (int i = 0; i < 10; i++) {
					RasterData->TransferBlock(flower, flowerIndexes[i]);
				}

				//The Drawlocation for the animation were given the same starting pixel to draw at.
				RasterData->AnimateBlock(flame, 140100);
				RasterData->AnimateBlock(spell, 140100);

				//Tell the Raster to apply the changes to the Raster array to the window.
				RS_Update(RasterData->GetRasterPixels(), WIDTH * HEIGHT);
				timer.Restart();
			}

		}
		delete flower;
		delete groundTile;
		delete flame;
		delete spell;
		delete blue_building;

	}
	
	RS_Shutdown();
	
}