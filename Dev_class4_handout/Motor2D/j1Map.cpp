#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include <math.h>

j1Map::j1Map() : j1Module(), map_loaded(false)
{
	name.create("map");
}

// Destructor
j1Map::~j1Map()
{}

// Called before render is available
bool j1Map::Awake(pugi::xml_node& config)
{
	LOG("Loading Map Parser");
	bool ret = true;

	folder.create(config.child("folder").child_value());

	firstMap = new MapInfo;

	return ret;
}

void j1Map::Draw()
{
	if(map_loaded == false)
		return;

	// TODO 6: Iterate all tilesets and draw all their 
	// images in 0,0 (you should have only one tileset for now)
	for (p2List_item<TileInfo>* tileInfo = tileList.start;  tileInfo != NULL; tileInfo = tileInfo->next)
	{
		App->render->Blit(tileInfo->data.tileImage,0,0);
	}
}

// Called before quitting
bool j1Map::CleanUp()
{
	LOG("Unloading map");

	// TODO 2: Make sure you clean up any memory allocated
	// from tilesets / map
	delete firstMap;

	tileList.clear();
	layerList.clear();

	map_file.reset();

	return true;
}

// Load new map
bool j1Map::Load(const char* file_name)
{
	bool ret = true;
	p2SString tmp("%s%s", folder.GetString(), file_name);

	pugi::xml_parse_result result = map_file.load_file(tmp.GetString());

	if(result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", file_name, result.description());
		ret = false;
	}

	if(ret == true)
	{
		// TODO 3: Create and call a private function to load and fill
		// all your map data
		create_Map(map_file.child("map"));
	}

	// TODO 4: Create and call a private function to load a tileset
	// remember to support more any number of tilesets!

	for (pugi::xml_node tileset = map_file.child("map").child("tileset"); tileset; tileset = tileset.next_sibling("tileset")) 
		create_Tile(tileset);

;
	for (pugi::xml_node nodeLayer = map_file.child("map").child("layer"); nodeLayer; nodeLayer = nodeLayer.next_sibling("layer"))
			load_Layer(nodeLayer);


	if(ret == true)
	{
		// TODO 5: LOG all the data loaded
		// iterate all tilesets and LOG everythingF


	}

	map_loaded = ret;

	return ret;
}

bool j1Map::create_Map(pugi::xml_node& map)
{
	firstMap->height = map.attribute("height").as_uint();
	firstMap->width = map.attribute("width").as_uint();

	firstMap->tileWidth = map.attribute("tilewidth").as_uint();
	firstMap->tileHeight = map.attribute("tileheight").as_uint();

	firstMap->nextobjectid = map.attribute("nextobjectid").as_uint();

	p2SString orientation(map.attribute("orientation").as_string());

	if (orientation == "orthogonal")
	{
		firstMap->tileOrientation = OR_ORTHOGONAL;
	}
	else if (orientation == "isometric")
	{
		firstMap->tileOrientation = OR_ISOMETRICAL;
	}
	else if (orientation == "hexagonal")
	{
		firstMap->tileOrientation = OR_HEXAGONAL;
	}
	else
	{
		firstMap->tileOrientation = OR_UNDEFINED;
	}


	p2SString renderOrder(map.attribute("renderorder").as_string());

	if (renderOrder == "right-down")
	{
		firstMap->renderOrder = RE_RIGHT_DOWN;
	}
	else if (renderOrder == "left-down")
	{
		firstMap->renderOrder = RE_LEFT_DOWN;
	}
	else if (renderOrder == "right-up")
	{
		firstMap->renderOrder = RE_RIGHT_UP;
	}
	else if (renderOrder == "left-down")
	{
		firstMap->renderOrder = RE_LEFT_UP;
	}
	else
	{
		firstMap->renderOrder = RE_UNDEFINED;
	}

	
	return true;
}

bool j1Map::create_Tile(pugi::xml_node& tileset)
{
	TileInfo tileInfo;

	tileInfo.tileImage = App->tex->Load(tileset.child("image").attribute("source").as_string());
	tileInfo.firstgid = tileset.attribute("firstgid").as_uint();
	tileInfo.margin = tileset.attribute("margin").as_uint();
	tileInfo.name = tileset.attribute("name").as_string();
	tileInfo.spacing = tileset.attribute("margin").as_uint();
	tileInfo.tileHeight = tileset.attribute("tileheight").as_uint();
	tileInfo.tileWidth = tileset.attribute("tilewidth").as_uint();


	if (tileList.add(tileInfo)) {

		LOG("TileSet: %s \n", tileInfo.name.GetString());
		LOG("First Gid: %d ", tileInfo.firstgid);
		LOG("Width: %d  Height: %d ", tileInfo.tileWidth, tileInfo.tileHeight);
		LOG("Width: %d  Height: %d ", tileInfo.tileWidth, tileInfo.tileHeight);
		LOG("Spacing: %d  Margin: %d ", tileInfo.spacing, tileInfo.margin);

	}
	else
		LOG("TILESET Not Loaded! ");

	return true;
}

bool j1Map::load_Layer(pugi::xml_node& node)
{
	LayerInfo layerInfo;


	layerInfo.name = node.attribute("name").as_string();
	layerInfo.width = node.attribute("width").as_uint();
	layerInfo.height = node.attribute("height").as_uint();

	layerInfo.tileArray = new uint[layerInfo.width * layerInfo.height];

	uint i = 0;
	for (pugi::xml_node tile = node.child("data").child("tile"); tile; tile = tile.next_sibling("tile")) {
		layerInfo.tileArray[i] = tile.attribute("gid").as_uint();
		++i;
	}
	if (layerList.add(layerInfo)) {


		LOG("Layer: %s \n", layerInfo.name);
		LOG("Width: %d  Height: %d ", layerInfo.width, layerInfo.height);


		for (int y = 0; y < i; y++) {
			LOG("Tile %d: %d \n",y+1 , layerInfo.tileArray[y]);
		}
	}

	return true;
}