#ifndef __j1MAP_H__
#define __j1MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"

// TODO 2: Create a struct to hold information for a TileSet
// Ignore Terrain Types and Tile Types for now, but we want the image!
// ----------------------------------------------------
struct TileInfo
{
	SDL_Texture* tileImage = nullptr;
	uint firstgid = 0u;
	p2SString name;
	uint tileWidth = 0u;
	uint tileHeight = 0u;
	uint spacing = 0u;
	uint margin = 0u;
};

struct LayerInfo {

	p2SString name;
	uint width = 0u;
	uint height = 0u;
	uint* tileArray = nullptr;
};

// TODO 1: Create a struct needed to hold the information to Map node
enum orientation
{
	OR_UNDEFINED,
	OR_ORTHOGONAL,
	OR_ISOMETRICAL,
	OR_HEXAGONAL,

};

enum RenderOrder
{
	RE_UNDEFINED,
	RE_RIGHT_DOWN,
	RE_LEFT_DOWN,
	RE_RIGHT_UP,
	RE_LEFT_UP,
};

struct MapInfo
{
	double version;
	
	orientation tileOrientation;
	RenderOrder renderOrder;
	uint width = 0u;
	uint height = 0u;

	uint tileWidth = 0u;
	uint tileHeight = 0u;

	uint nextobjectid = 0u;
};
// ----------------------------------------------------
class j1Map : public j1Module
{
public:

	j1Map();

	// Destructor
	virtual ~j1Map();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called each loop iteration
	void Draw();

	// Called before quitting
	bool CleanUp();

	// Load new map
	bool Load(const char* path);

	//Create a map
	

private:

	bool create_Map(pugi::xml_node& map);
	bool create_Tile(pugi::xml_node& tileset);
	bool load_Layer(pugi::xml_node& layer);


public:

	// TODO 1: Add your struct for map info as public for now
	MapInfo* firstMap = nullptr;
	p2List<TileInfo> tileList;
	p2List<LayerInfo> layerList;

private:

	pugi::xml_document	map_file;
	p2SString			folder;
	bool				map_loaded;
};

#endif // __j1MAP_H__