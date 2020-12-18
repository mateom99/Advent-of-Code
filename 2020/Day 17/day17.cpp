using namespace std;

#include <iostream>
#include <vector>
#include <fstream>
#include <map>

	class pocketDimension{
		map<int, map<int, map<int, bool>>> dimension;
		map<int, map<int, map<int, map<int, bool>>>> dimension4D;

	public:
	// Reads input file and return a vector<int> from the input
	void loadFirstSlice(string file){
		// Instantinate the input file object and open the file
		ifstream inFile;
		inFile.open(file);
		// Read line by line
		string line;
		// Store the 2d slice in both the 3d and 4d dimension
		vector<vector<int>> slice;
		int y = 0;
		while (getline(inFile, line)){
			int x = 0;
			for (int i = 0; i < line.size(); i++){
				if (line[i] == '#'){
					dimension[0][y][x] = 1;
					dimension4D[0][0][y][x] = 1;
				}
				else{
					dimension[0][y][x] = 0;
					dimension4D[0][0][y][x] = 0;
				}
				x++;
			}
			y++;
		}

		// Close the file
		inFile.close();
	}

	// Checks if a cube is active given its 3D coordinates
	bool checkActive(int z, int y, int x){
		if (dimension.find(z) == dimension.end())
			return false;
		if (dimension[z].find(y) == dimension[z].end())
			return false;
		if (dimension[z][y].find(x) == dimension[z][y].end())
			return false;

		if (dimension[z][y][x])
			return true;
	}

	// Counts all active neighbors in all 3D directions of a given cube using checkActive()
	int countActiveNeighbors(int z, int y, int x){
		int neighbors = 0;

		for (int zz = z-1; zz <= z+1; zz++){
			for (int yy = y-1; yy <= y+1; yy++){
				for (int xx = x-1; xx <= x+1; xx++){
					if (zz == z && yy == y && xx == x)
						continue;
					if (checkActive(zz,yy,xx))
						neighbors++;
				}
			}
		}

		return neighbors;
	}

	// Goes through every cube and updates its state based on the state update rules
	// We also check around the current dimension to properly expand
	void updateState(){
		map<int, map<int, map<int, bool>>> updatedDimension = dimension;
		int startZ = dimension.begin()->first-1;
		int endZ = dimension.begin()->first + dimension.size();
		for(int z = startZ; z <= endZ; z++){
			int startY = dimension[0].begin()->first-1;
			int endY = dimension[0].begin()->first + dimension[0].size();
			for(int y = startY; y <= endY; y++){
				int startX = dimension[0][0].begin()->first-1;
				int endX = dimension[0][0].begin()->first + dimension[0][0].size();
				for(int x = startX; x <= endX; x++){
					int count = countActiveNeighbors(z,y,x);
					if (dimension[z][y][x]){
						if (count == 2 || count == 3){
							updatedDimension[z][y][x] = 1;
						} else {
							updatedDimension[z][y][x] = 0;
						}
					} else {
						if (count == 3){
							updatedDimension[z][y][x] = 1;
						} else {
							updatedDimension[z][y][x] = 0;
						}
					}
				}
			}
		}
		// Switch to the updated dimension
		dimension = updatedDimension;
	}

	// Returns the count of all active cubes after a given amount of cycles
	int countActiveCubes(int cycles){
		// Update the state specified amount of times
		for (int i = 0; i < cycles; i++)
			updateState();
		// Count every active cube in 3D space
		int count = 0;
		int startZ = dimension.begin()->first;
		int endZ = dimension.begin()->first + dimension.size();
		for(int z = startZ; z < endZ; z++){
			int startY = dimension[z].begin()->first;
			int endY = dimension[z].begin()->first + dimension[z].size();
			for(int y = startY; y < endY; y++){
				int startX = dimension[z][y].begin()->first;
				int endX = dimension[z][y].begin()->first + dimension[z][y].size();
				for(int x = startX; x < endX; x++){
					if (dimension[z][y][x]){
						count++;
					}
				}
			}
		}
		return count;
	}


// ----------------------------------Begin 4D Wizardry---------------------------------- //

	// Checks if a cube is active given its 4Dcoordinates
	bool checkActive4D(int w, int z, int y, int x){
		if (dimension4D.find(w) == dimension4D.end())
			return false;
		if (dimension4D[w].find(z) == dimension4D[w].end())
			return false;
		if (dimension4D[w][z].find(y) == dimension4D[w][z].end())
			return false;
		if (dimension4D[w][z][y].find(x) == dimension4D[w][z][y].end())
			return false;

		if (dimension4D[w][z][y][x])
			return true;
	}

	// Counts all active neighbors in all 4D directions of a given cube using checkActive4D()
	int countActiveNeighbors4D(int w, int z, int y, int x){
		int neighbors = 0;
		for (int ww = w-1; ww <= w+1; ww++){
			for (int zz = z-1; zz <= z+1; zz++){
				for (int yy = y-1; yy <= y+1; yy++){
					for (int xx = x-1; xx <= x+1; xx++){
						if (ww == w && zz == z && yy == y && xx == x)
							continue;
						if (checkActive4D(ww,zz,yy,xx))
							neighbors++;
					}
				}
			}
		}
		return neighbors;
	}

	// Goes through every cube and updates its state based on the state update rules
	// We also check around the current dimension to properly expand
	void updateState4D(){
		map<int, map<int, map<int, map<int, bool>>>> updatedDimension = dimension4D;
		int startW = dimension4D.begin()->first-1;
		int endW = dimension4D.begin()->first + dimension4D.size();
		for (int w = startW; w <= endW; w++){
			int startZ = dimension4D[0].begin()->first-1;
			int endZ = dimension4D[0].begin()->first + dimension4D[0].size();
			for(int z = startZ; z <= endZ; z++){
				int startY = dimension4D[0][0].begin()->first-1;
				int endY = dimension4D[0][0].begin()->first + dimension4D[0][0].size();
				for(int y = startY; y <= endY; y++){
					int startX = dimension4D[0][0][0].begin()->first-1;
					int endX = dimension4D[0][0][0].begin()->first + dimension4D[0][0][0].size();
					for(int x = startX; x <= endX; x++){
						int count = countActiveNeighbors4D(w,z,y,x);
						if (dimension4D[w][z][y][x]){
							if (count == 2 || count == 3){
								updatedDimension[w][z][y][x] = 1;
							} else {
								updatedDimension[w][z][y][x] = 0;
							}
						} else {
							if (count == 3){
								updatedDimension[w][z][y][x] = 1;
							} else {
								updatedDimension[w][z][y][x] = 0;
							}
						}
					}
				}
			}
		}
		// Switch to the updated dimension
		dimension4D = updatedDimension;
	}

	// Returns the count of all active cubes after a given amount of cycles
	int countActiveCubes4D(int cycles){
		// Update the state specified amount of times
		for (int i = 0; i < cycles; i++)
			updateState4D();
		int count = 0;
		// Count every active cube in 4D space
		int startW = dimension4D.begin()->first;
		int endW = dimension4D.begin()->first + dimension4D.size();
		for (int w = startW; w < endW; w++){
			int startZ = dimension4D[w].begin()->first;
			int endZ = dimension4D[w].begin()->first + dimension4D[w].size();
			for(int z = startZ; z < endZ; z++){
				int startY = dimension4D[w][z].begin()->first;
				int endY = dimension4D[w][z].begin()->first + dimension4D[w][z].size();
				for(int y = startY; y < endY; y++){
					int startX = dimension4D[w][z][y].begin()->first;
					int endX = dimension4D[w][z][y].begin()->first + dimension4D[w][z][y].size();
					for(int x = startX; x < endX; x++){
						if (dimension4D[w][z][y][x]){
							count++;
						}
					}
				}
			}
		}
		return count;
	}
};

int main(){
	// Create the dimension and load the first slice
	pocketDimension myDimension;
	myDimension.loadFirstSlice("input17.txt");

	// Output the results
	cout << "Part 1: " << myDimension.countActiveCubes(6) << endl;
	cout << "Part 2: " << myDimension.countActiveCubes4D(6) << endl;
	return 0;
}
