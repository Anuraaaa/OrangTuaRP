#include <YSI_Coding\y_hooks>

enum furnitureData {
	furnitureID,
	furnitureProperty,
    furniturePropertyType,
	furnitureExists,
	furnitureModel,
	furnitureWorld,
	furnitureInterior,
	furnitureName[32],
	Float:furniturePos[3],
	Float:furnitureRot[3],
	STREAMER_TAG_OBJECT:furnitureObject,
	furnitureTextureModelid,
	furnitureTextureTXDName[24],
	furnitureTextureName[24]
};

new FurnitureData[MAX_FURNITURE][furnitureData];
new ListedFurniture[MAX_PLAYERS][150];
new Iterator:Furniture<MAX_FURNITURE>;

enum {
    FURNITURE_TYPE_HOUSE,
    FURNITURE_TYPE_FLAT
};

enum e_FurnitureData {
	e_FurnitureType,
	e_FurnitureName[32],
	e_FurnitureModel
};

new const g_aFurnitureTypes[][] = {
	{"Frames"},
	{"Tables"},
	{"Chairs"},
	{"Beds"},
	{"Cabinets"},
	{"Television Sets"},
	{"Kitchen Appliances"},
	{"Bathroom Appliances"},
	{"Misc Furniture"}
};

new const g_aFurnitureData[][e_FurnitureData] = {
	{1, "Frame 1", 2289},
	{1, "Frame 2", 2288},
	{1, "Frame 3", 2287},
	{1, "Frame 4", 2286},
	{1, "Frame 5", 2285},
	{1, "Frame 6", 2284},
    {1, "Frame 7", 2283},
    {1, "Frame 8", 2282},
    {1, "Frame 9", 2281},
    {1, "Frame 10", 2280},
    {1, "Frame 11", 2279},
	{1, "Frame 12", 2278},
	{1, "Frame 13", 2277},
	{1, "Frame 14", 2276},
	{1, "Frame 15", 2275},
	{1, "Frame 16", 2274},
    {1, "Frame 17", 2273},
    {1, "Frame 18", 2272},
    {1, "Frame 19", 2271},
    {1, "Frame 20", 2270},
    {2, "Table 1", 1433},
	{2, "Table 2", 1998},
	{2, "Table 3", 2008},
	{2, "Table 4", 2180},
	{2, "Table 5", 2185},
    {2, "Table 6", 2205},
    {2, "Table 7", 2314},
    {2, "Table 8", 2635},
    {2, "Table 9", 2637},
    {2, "Table 10", 2644},
	{2, "Table 11", 2747},
	{2, "Table 12", 2764},
	{2, "Table 13", 2763},
	{2, "Table 14", 2762},
	{2, "Table 15", 936},
	{2, "Table 16", 937},
	{2, "Table 17", 941},
	{2, "Table 18", 2115},
	{2, "Table 19", 2116},
	{2, "Table 20", 2112},
	{2, "Table 21", 2111},
	{2, "Table 22", 2110},
	{2, "Table 23", 2109},
	{2, "Table 24", 2085},
	{2, "Table 25", 2032},
	{2, "Table 26", 2031},
	{2, "Table 27", 2030},
	{2, "Table 28", 2029},
    {3, "Chair 1", 1671},
    {3, "Chair 2", 1704},
    {3, "Chair 3", 1705},
    {3, "Chair 4", 1708},
    {3, "Chair 5", 1711},
    {3, "Chair 6", 1715},
    {3, "Chair 7", 1721},
    {3, "Chair 8", 1724},
    {3, "Chair 9", 1727},
    {3, "Chair 10", 1729},
    {3, "Chair 11", 1735},
    {3, "Chair 12", 1739},
    {3, "Chair 13", 1805},
    {3, "Chair 14", 1806},
    {3, "Chair 15", 1810},
    {3, "Chair 16", 1811},
    {3, "Chair 17", 2079},
    {3, "Chair 18", 2120},
    {3, "Chair 19", 2124},
    {3, "Chair 20", 2356},
    {3, "Chair 21", 1768},
    {3, "Chair 22", 1766},
    {3, "Chair 23", 1764},
    {3, "Chair 24", 1763},
    {3, "Chair 25", 1761},
    {3, "Chair 26", 1760},
    {3, "Chair 27", 1757},
    {3, "Chair 28", 1756},
    {3, "Chair 29", 1753},
    {3, "Chair 30", 1713},
    {3, "Chair 31", 1712},
    {3, "Chair 32", 1706},
    {3, "Chair 33", 1703},
    {3, "Chair 34", 1702},
    {3, "Chair 35", 1754},
    {3, "Chair 36", 1755},
    {3, "Chair 37", 1758},
    {3, "Chair 38", 1759},
    {3, "Chair 39", 1762},
    {3, "Chair 40", 1765},
    {3, "Chair 41", 1767},
    {3, "Chair 42", 1769},
	{4, "Bed 1", 1700},
	{4, "Bed 2", 1701},
	{4, "Bed 3", 1725},
	{4, "Bed 4", 1745},
	{4, "Bed 5", 1793},
	{4, "Bed 6", 1794},
	{4, "Bed 7", 1795},
	{4, "Bed 8", 1796},
	{4, "Bed 9", 1797},
	{4, "Bed 10", 1771},
	{4, "Bed 11", 1798},
	{4, "Bed 12", 1799},
    {4, "Bed 13", 1800},
    {4, "Bed 14", 1801},
    {4, "Bed 15", 1802},
    {4, "Bed 16", 1812},
    {4, "Bed 17", 2090},
    {4, "Bed 18", 2299},
    {5, "Cabinet 1", 1416},
	{5, "Cabinet 2", 1417},
	{5, "Cabinet 3", 1741},
	{5, "Cabinet 4", 1742},
	{5, "Cabinet 5", 1743},
	{5, "Cabinet 6", 2025},
	{5, "Cabinet 7", 2065},
	{5, "Cabinet 8", 2066},
	{5, "Cabinet 9", 2067},
	{5, "Cabinet 10", 2087},
    {5, "Cabinet 11", 2088},
    {5, "Cabinet 12", 2094},
    {5, "Cabinet 13", 2095},
    {5, "Cabinet 14", 2306},
    {5, "Cabinet 15", 2307},
	{5, "Cabinet 16", 2323},
	{5, "Cabinet 17", 2328},
	{5, "Cabinet 18", 2329},
	{5, "Cabinet 19", 2330},
	{5, "Cabinet 20", 2708},
	{6, "Television 1", 1518},
	{6, "Television 2", 1717},
	{6, "Television 3", 1747},
	{6, "Television 4", 1748},
	{6, "Television 5", 1749},
	{6, "Television 6", 1750},
	{6, "Television 7", 1752},
	{6, "Television 8", 1781},
	{6, "Television 9", 1791},
	{6, "Television 10", 1792},
    {6, "Television 11", 2312},
	{6, "Television 12", 2316},
	{6, "Television 13", 2317},
	{6, "Television 14", 2318},
	{6, "Television 15", 2320},
	{6, "Television 16", 2595},
	{6, "Television 17", 16377},
	{6, "LCD Television 1", 19786},
	{6, "LCD Television 2", 19787},
	{7, "Kitchen 1", 2013},
	{7, "Kitchen 2", 2017},
	{7, "Kitchen 3", 2127},
	{7, "Kitchen 4", 2130},
	{7, "Kitchen 5", 2131},
	{7, "Kitchen 6", 2132},
	{7, "Kitchen 7", 2135},
	{7, "Kitchen 8", 2136},
	{7, "Kitchen 9", 2144},
	{7, "Kitchen 10", 2147},
    {7, "Kitchen 11", 2149},
    {7, "Kitchen 12", 2150},
    {7, "Kitchen 13", 2415},
    {7, "Kitchen 14", 2417},
    {7, "Kitchen 15", 2421},
    {7, "Kitchen 16", 2426},
    {7, "Kitchen 17", 2014},
    {7, "Kitchen 18", 2015},
    {7, "Kitchen 19", 2016},
    {7, "Kitchen 20", 2018},
    {7, "Kitchen 21", 2019},
    {7, "Kitchen 22", 2022},
    {7, "Kitchen 23", 2133},
    {7, "Kitchen 24", 2134},
	{7, "Kitchen 25", 2137},
	{7, "Kitchen 26", 2138},
	{7, "Kitchen 27", 2139},
	{7, "Kitchen 28", 2140},
	{7, "Kitchen 29", 2141},
	{7, "Kitchen 30", 2142},
	{7, "Kitchen 31", 2143},
	{7, "Kitchen 32", 2145},
	{7, "Kitchen 33", 2148},
	{7, "Kitchen 34", 2151},
	{7, "Kitchen 35", 2152},
	{7, "Kitchen 36", 2153},
	{7, "Kitchen 37", 2154},
	{7, "Kitchen 38", 2155},
	{7, "Kitchen 39", 2156},
	{7, "Kitchen 40", 2157},
	{7, "Kitchen 41", 2158},
	{7, "Kitchen 42", 2159},
	{7, "Kitchen 43", 2160},
	{7, "Kitchen 44", 2134},
	{7, "Kitchen 45", 2135},
	{7, "Kitchen 46", 2338},
	{7, "Kitchen 47", 2341},
	{8, "Bathroom 1", 2514},
	{8, "Bathroom 2", 2516},
	{8, "Bathroom 3", 2517},
	{8, "Bathroom 4", 2518},
	{8, "Bathroom 5", 2520},
	{8, "Bathroom 6", 2521},
	{8, "Bathroom 7", 2522},
	{8, "Bathroom 8", 2523},
	{8, "Bathroom 9", 2524},
	{8, "Bathroom 10", 2525},
    {8, "Bathroom 11", 2526},
    {8, "Bathroom 12", 2527},
    {8, "Bathroom 13", 2528},
    {8, "Bathroom 14", 2738},
    {8, "Bathroom 15", 2739},
	{9, "Washer", 1208},
	{9, "Ceiling Fan", 1661},
	{9, "Moose Head", 1736},
	{9, "Radiator", 1738},
	{9, "Mop and Pail", 1778},
	{9, "Water Cooler", 1808},
	{9, "Water Cooler 2", 2002},
	{9, "Money Safe", 1829},
	{9, "Printer", 2186},
	{9, "Computer", 2190},
	{9, "Treadmill", 2627},
	{9, "Bench Press", 2629},
	{9, "Exercise Bike", 2630},
	{9, "Mat 1", 2631},
	{9, "Mat 2", 2632},
	{9, "Mat 3", 2817},
	{9, "Mat 4", 2818},
	{9, "Mat 5", 2833},
	{9, "Mat 6", 2834},
	{9, "Mat 7", 2835},
	{9, "Mat 8", 2836},
	{9, "Mat 9", 2841},
	{9, "Mat 10", 2842},
	{9, "Mat 11", 2847},
	{9, "Book Pile 1", 2824},
	{9, "Book Pile 2", 2826},
	{9, "Book Pile 3", 2827},
	{9, "Basketball", 2114},
	{9, "Lamp 1", 2108},
	{9, "Lamp 2", 2106},
	{9, "Lamp 3", 2069},
	{9, "Dresser 1", 2569},
	{9, "Dresser 2", 2570},
	{9, "Dresser 3", 2573},
	{9, "Dresser 4", 2574},
	{9, "Dresser 5", 2576},
	{9, "Book", 2894},
	{9, "Wall 015", 19367},
	{9, "Wall 016", 19368},
	{9, "Wooden Wall", 19370},
	{9, "Small Concrete Wall", 19362},
	{9, "Wooden Plank", 19433},
	{9, "Brick Plank", 19437},
	{9, "Big Wooden Wall", 19376},
	{9, "Big Cement Wall", 19371},
	{9, "Big White Wall", 19377},
	{9, "Wardrobe Door", 1567},
	{9, "Wood Door", 1491},
	{9, "Wooden Fabric Door", 1493},
	{9, "Dirty Green Door", 1492},
	{9, "Holed Wall", 19383},
	{9, "Short Wall", 19426},
	{9, "Pump Drinks", 1541},
	{9, "Music Column", 2231},
	{9, "Empty Fridge", 2531},
	{9, "Ufo Light",  16780},
	{9, "CJ Mlight", 1734},
	{9, "Music Cabinet", 2100},
	{9, "Boombox", 2103},
	{9, "Pool Table", 14651},
	{9, "Bottle and Cigarettes", 1670},
	{9, "Bookshelf", 1742},
	{9, "Complex Wooden Door", 1502},
	{9, "Pot of Red Flowers", 2245},
	{9, "Plant Pot 1", 2240},
	{9, "Plant Pot 2", 2244},
	{9, "Plant Pot 3", 2248},
	{9, "Plant Pot 4", 948},
	{9, "Pot of Small Bush", 15038},
	{9, "Light", 18075}

};

hook OnGameModeInit() {

	if (IsSQLConnected()) {
		Iter_Init(Furniture);
		mysql_tquery(sqlcon, "SELECT * FROM `furniture`", "OnLoadFurniture", "");
	}
}

hook OnGameModeExit() {
	
	if (IsSQLConnected()) {
		Iter_Clear(Furniture);
	}
}

function OnLoadFurniture()
{
	for(new i = 0; i < cache_num_rows(); i++)
	{
		new id = ITER_NONE;

		if(i > MAX_FURNITURE)
			break;

		if((id = Iter_Alloc(Furniture)) != ITER_NONE) {
			FurnitureData[id][furnitureExists] = true;

			cache_get_value_name(i, "furnitureName", FurnitureData[id][furnitureName], 32);

			cache_get_value_name_int(i, "furnitureID", FurnitureData[id][furnitureID]);
			cache_get_value_name_int(i, "furnitureModel", FurnitureData[id][furnitureModel]);

			cache_get_value_name_float(i, "furnitureX", FurnitureData[id][furniturePos][0]);
			cache_get_value_name_float(i, "furnitureY", FurnitureData[id][furniturePos][1]);
			cache_get_value_name_float(i, "furnitureZ", FurnitureData[id][furniturePos][2]);

			cache_get_value_name_float(i, "furnitureRX", FurnitureData[id][furnitureRot][0]);
			cache_get_value_name_float(i, "furnitureRY", FurnitureData[id][furnitureRot][1]);
			cache_get_value_name_float(i, "furnitureRZ", FurnitureData[id][furnitureRot][2]);

			cache_get_value_name_int(i, "furnitureWorld", FurnitureData[id][furnitureWorld]);
			cache_get_value_name_int(i, "furnitureInterior", FurnitureData[id][furnitureInterior]);

			cache_get_value_name_int(i, "ID", FurnitureData[id][furnitureProperty]);
			cache_get_value_name_int(i, "furnitureType", FurnitureData[id][furniturePropertyType]);

			cache_get_value_name_int(i, "TextureModelID", FurnitureData[id][furnitureTextureModelid]);
			cache_get_value_name(i, "TextureTXD", FurnitureData[id][furnitureTextureTXDName], 24);
			cache_get_value_name(i, "TextureName", FurnitureData[id][furnitureTextureName], 24);
			
			Iter_Add(Furniture, id);

			Furniture_Spawn(id);
		}
	}

	printf("[FURNITURE] Loaded %d furniture from database.", cache_num_rows());
	return 1;
}

GetFurnitureNameByModel(model)
{
	new
	    name[32];

	for (new i = 0; i < sizeof(g_aFurnitureData); i ++) if (g_aFurnitureData[i][e_FurnitureModel] == model) {
		strcat(name, g_aFurnitureData[i][e_FurnitureName]);

		break;
	}
	return name;
}

Furniture_ReturnPrice(index)
{
	new price;
	switch(index)
	{
		case 0: price = 3000;
		case 1: price = 5000;
		case 2: price = 3500;
		case 3: price = 4500;
		case 4: price = 6300;
		case 5: price = 10000;
		case 6: price = 7000;
		case 7: price = 7000;
		case 8: price = 6800;
		case 9: price = 5500;
	}
	return price;
}

Furniture_Refresh(furnitureid)
{
	if(Iter_Contains(Furniture, furnitureid))
	{
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FurnitureData[furnitureid][furnitureObject], E_STREAMER_X, FurnitureData[furnitureid][furniturePos][0]);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FurnitureData[furnitureid][furnitureObject], E_STREAMER_Y, FurnitureData[furnitureid][furniturePos][1]);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FurnitureData[furnitureid][furnitureObject], E_STREAMER_Z, FurnitureData[furnitureid][furniturePos][2]);

		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FurnitureData[furnitureid][furnitureObject], E_STREAMER_R_X, FurnitureData[furnitureid][furnitureRot][0]);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FurnitureData[furnitureid][furnitureObject], E_STREAMER_R_Y, FurnitureData[furnitureid][furnitureRot][1]);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FurnitureData[furnitureid][furnitureObject], E_STREAMER_R_Z, FurnitureData[furnitureid][furnitureRot][2]);
	}
	return 1;
}

Furniture_Save(furnitureid)
{
	static
	    string[712];

	mysql_format(sqlcon, string, sizeof(string), "UPDATE `furniture` SET `furnitureModel` = '%d', `furnitureName` = '%s', `furnitureX` = '%.4f', `furnitureY` = '%.4f', `furnitureZ` = '%.4f', `furnitureRX` = '%.4f', `furnitureRY` = '%.4f', `furnitureRZ` = '%.4f', `ID` = '%d', `furnitureType` = '%d', `furnitureWorld` = '%d', `furnitureInterior` = '%d', `TextureModelID` = '%d', `TextureTXD` = '%e', `TextureName` = '%e' WHERE `furnitureID` = '%d'",
	    FurnitureData[furnitureid][furnitureModel],
	    FurnitureData[furnitureid][furnitureName],
	    FurnitureData[furnitureid][furniturePos][0],
	    FurnitureData[furnitureid][furniturePos][1],
	    FurnitureData[furnitureid][furniturePos][2],
	    FurnitureData[furnitureid][furnitureRot][0],
	    FurnitureData[furnitureid][furnitureRot][1],
	    FurnitureData[furnitureid][furnitureRot][2],
	    FurnitureData[furnitureid][furnitureProperty],
		FurnitureData[furnitureid][furniturePropertyType],
		FurnitureData[furnitureid][furnitureWorld],
		FurnitureData[furnitureid][furnitureInterior],
		FurnitureData[furnitureid][furnitureTextureModelid],
		FurnitureData[furnitureid][furnitureTextureTXDName],
		FurnitureData[furnitureid][furnitureTextureName],
	    FurnitureData[furnitureid][furnitureID]
	);
	return mysql_tquery(sqlcon, string);
}

Furniture_Add(propid, name[], vw, int, modelid, type, Float:x, Float:y, Float:z, Float:rx = 0.0, Float:ry = 0.0, Float:rz = 0.0)
{
	static
	    string[64],
		id = -1;

	id = Iter_Free(Furniture);

	if(id != INVALID_ITERATOR_SLOT) {

		FurnitureData[id][furnitureExists] = true;
		format(FurnitureData[id][furnitureName], 32, name);

		FurnitureData[id][furnitureProperty] = propid;
		FurnitureData[id][furnitureModel] = modelid;
		FurnitureData[id][furniturePos][0] = x;
		FurnitureData[id][furniturePos][1] = y;
		FurnitureData[id][furniturePos][2] = z;
		FurnitureData[id][furnitureRot][0] = rx;
		FurnitureData[id][furnitureRot][1] = ry;
		FurnitureData[id][furnitureRot][2] = rz;
        FurnitureData[id][furniturePropertyType] = type;
		FurnitureData[id][furnitureInterior] = int;
		FurnitureData[id][furnitureWorld] = vw;
		FurnitureData[id][furnitureTextureModelid] = 0;
		format(FurnitureData[id][furnitureTextureTXDName], 24, "NoTexture");
		format(FurnitureData[id][furnitureTextureName], 24, "NoTexture");

		Iter_Add(Furniture, id);

		mysql_format(sqlcon, string, sizeof(string), "INSERT INTO `furniture` (`ID`) VALUES(%d)", FurnitureData[id][furnitureProperty]);
		mysql_tquery(sqlcon, string, "OnFurnitureCreated", "d", id);
	}
	return id;
}

function OnFurnitureCreated(furnitureid)
{
	FurnitureData[furnitureid][furnitureID] = cache_insert_id();
    Furniture_Spawn(furnitureid);
	Furniture_Save(furnitureid);
	return 1;
}

Furniture_Delete(furnitureid, bool:safe_remove = false)
{
	static
	    string[72];

	if (Iter_Contains(Furniture, furnitureid))
	{
	    mysql_format(sqlcon, string, sizeof(string), "DELETE FROM `furniture` WHERE `furnitureID` = '%d'", FurnitureData[furnitureid][furnitureID]);
		mysql_tquery(sqlcon, string);

		FurnitureData[furnitureid][furnitureExists] = false;
		FurnitureData[furnitureid][furnitureModel] = 0;
		FurnitureData[furnitureid][furniturePropertyType] = -1;
		FurnitureData[furnitureid][furnitureProperty] = -1;
		if(IsValidDynamicObject(FurnitureData[furnitureid][furnitureObject]))
			DestroyDynamicObject(FurnitureData[furnitureid][furnitureObject]);

        if(!safe_remove)
		    Iter_Remove(Furniture, furnitureid);
        else {
            new next = furnitureid;
            Iter_SafeRemove(Furniture, next, furnitureid);
        }
	}
	return 1;
}


ShowFurnitureEditMenu(playerid) {
	ShowPlayerDialog(playerid, DIALOG_FURNITURE_MENU, DIALOG_STYLE_LIST, sprintf("Furniture Option(s) - %s", FurnitureData[PlayerData[playerid][pEditing]][furnitureName]), "Edit position (click n drag)\nEdit position (click textdraw)\n"RED"(beta) "WHITE"Change Texture\nRemove furniture", "Select", "Close");
	return 1;
}