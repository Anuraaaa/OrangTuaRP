#include <YSI_Coding\y_hooks>

enum e_weed
{
	weedID,
	bool:weedExists,
	bool:weedHarvested,
	Float:weedPos[3],
	weedGrow,
	STREAMER_TAG_OBJECT:weedObject,
	STREAMER_TAG_AREA:weedArea,
};
new WeedData[MAX_WEED][e_weed];

stock IsAtDrugField(playerid)
{
	if(IsPlayerInDynamicArea(playerid, AreaData[areaDrug]))
		return 1;

	return 0;
}

stock Weed_Delete(id)
{
	if(!WeedData[id][weedExists])
		return 0;

	new str[158];
	mysql_format(sqlcon, str, sizeof(str), "DELETE FROM `weed` WHERE `ID` = '%d'", WeedData[id][weedID]);
	mysql_tquery(sqlcon, str);

	if (IsValidDynamicObject(WeedData[id][weedObject]))
	    DestroyDynamicObject(WeedData[id][weedObject]);

	if(IsValidDynamicArea(WeedData[id][weedArea]))
		DestroyDynamicArea(WeedData[id][weedArea]);

	WeedData[id][weedArea] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
	WeedData[id][weedObject] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
	WeedData[id][weedExists] = false;
	WeedData[id][weedID] = 0;
	return 1;
}
function HarvestWeed(playerid, wid)
{
	if(!WeedData[wid][weedExists])
		return 0;

	ClearAnimations(playerid, 1);
	Weed_Delete(wid);
	Inventory_Add(playerid, "Weed", 1578, 1);
	SendClientMessage(playerid, COLOR_SERVER, "(Drugs) {FFFFFF}Item added to inventory: {FFFF00}Weed +1");
	return 1;
}
stock Weed_Nearest(playerid)
{
	new index = -1;
	
	forex(i, MAX_WEED) if(WeedData[i][weedExists])
	{
		if(IsPlayerInRangeOfPoint(playerid, 2.5, WeedData[i][weedPos][0], WeedData[i][weedPos][1], WeedData[i][weedPos][2])) {
			index = i;
			break;
		}
	}
	return index;
}

stock Weed_Count()
{
	new count = 0;
	forex(i, MAX_WEED) if(WeedData[i][weedExists])
	{
		count++;
	}
	return count;
}


function Combined(playerid)
{
	ClearAnimations(playerid, 1);
	SendClientMessage(playerid, COLOR_SERVER, "(Drugs) {FFFFFF}Item added to inventory: {FFFF00}Rolled Weed +1");
	Inventory_Add(playerid, "Rolled Weed", 3027, 1);
	return 1;
}

function PlantWeed(playerid, Float:x, Float:y, Float:z)
{
	if(Weed_Count() >= MAX_WEED)
		return SendErrorMessage(playerid, "The server cannot create more Weeds!");

	if(Weed_Nearest(playerid) != -1)
		return SendErrorMessage(playerid, "Tidak bisa menanam didekat tanaman lain.");

	ClearAnimations(playerid, 1);
	Weed_Create(x ,y ,z);
	ShowMessage(playerid, "Weed ~r~planted ~w~successfully.", 3);
	return 1;
}

stock Weed_Create(Float:x, Float:y, Float:z)
{
	forex(i, MAX_WEED) if(!WeedData[i][weedExists])
	{ 
		WeedData[i][weedExists] = true;
		WeedData[i][weedPos][0] = x;
		WeedData[i][weedPos][1] = y;
		WeedData[i][weedPos][2] = z;
		WeedData[i][weedGrow] = 0;
		WeedData[i][weedHarvested] = false;

		Weed_Refresh(i);
		mysql_tquery(sqlcon, "INSERT INTO `weed` (`Grow`) VALUES(0)", "OnWeedCreated", "d", i);
		return i;
	}
	return -1;
}

function OnWeedCreated(id)
{
	WeedData[id][weedID] = cache_insert_id();
	Weed_Save(id);
}
stock Weed_Refresh(plantid)
{
	if (plantid != -1 && WeedData[plantid][weedExists])
	{

		if (IsValidDynamicObject(WeedData[plantid][weedObject]))
			Streamer_SetItemPos(STREAMER_TYPE_OBJECT, WeedData[plantid][weedObject], WeedData[plantid][weedPos][0], WeedData[plantid][weedPos][1], WeedData[plantid][weedPos][2] - 1.80);
		else
			WeedData[plantid][weedObject] = CreateDynamicObject(19473, WeedData[plantid][weedPos][0], WeedData[plantid][weedPos][1], WeedData[plantid][weedPos][2] - 1.80, 0.0, 0.0, 0.0, -1, -1);

		if(IsValidDynamicArea(WeedData[plantid][weedArea]))
			Streamer_SetItemPos(STREAMER_TYPE_AREA, WeedData[plantid][weedArea], WeedData[plantid][weedPos][0], WeedData[plantid][weedPos][1], WeedData[plantid][weedPos][2]);
		else
			WeedData[plantid][weedArea] = CreateDynamicSphere( WeedData[plantid][weedPos][0], WeedData[plantid][weedPos][1], WeedData[plantid][weedPos][2],1.5);

		Streamer_SetIntData(STREAMER_TYPE_AREA, WeedData[plantid][weedArea], E_STREAMER_EXTRA_ID, AREA_TYPE_WEED);
	}
	return 1;
}


function Weed_Load()
{
	new rows = cache_num_rows();
	if(rows)
	{
		forex(i, rows)
		{
			WeedData[i][weedExists] = true;
			cache_get_value_name_int(i, "ID", WeedData[i][weedID]);
			cache_get_value_name_float(i, "PosX", WeedData[i][weedPos][0]);
			cache_get_value_name_float(i, "PosY", WeedData[i][weedPos][1]);
			cache_get_value_name_float(i, "PosZ", WeedData[i][weedPos][2]);
			cache_get_value_name_int(i, "Grow", WeedData[i][weedGrow]);
			Weed_Refresh(i);

		}
		printf("[WEED] Loaded %d Weed from database", rows);
	}
	return 1;
}

stock Weed_Save(id)
{
	new query[352];
	mysql_format(sqlcon, query, sizeof(query), "UPDATE `weed` SET ");
	mysql_format(sqlcon, query, sizeof(query), "%s`PosX`='%f', ", query, WeedData[id][weedPos][0]);
	mysql_format(sqlcon, query, sizeof(query), "%s`PosY`='%f', ", query, WeedData[id][weedPos][1]);
	mysql_format(sqlcon, query, sizeof(query), "%s`PosZ`='%f', ", query, WeedData[id][weedPos][2]);
	mysql_format(sqlcon, query, sizeof(query), "%s`Grow`='%d' ", query, WeedData[id][weedGrow]);
	mysql_format(sqlcon, query, sizeof(query), "%sWHERE `ID` = '%d'", query, WeedData[id][weedID]);
	mysql_tquery(sqlcon, query);
	return 1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA:areaid) {

	for(new i = 0; i < MAX_WEED; i++) if(WeedData[i][weedExists]) {
		if(areaid == WeedData[i][weedArea] && Streamer_GetIntData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID) == AREA_TYPE_WEED) {
			new str[128];
			if(WeedData[i][weedGrow] < MAX_GROW)
				format(str, 128, "On Growth~n~~y~%d minute left.", MAX_GROW-WeedData[i][weedGrow]);
			else
				format(str, 128, "Ready to harvest~n~Press ~y~H ~w~to harvest.");

			ShowBox(playerid, "~r~Plant_Info", str, 2);		
		}
	}
/*
	new weedid = Streamer_GetIntData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID);

	if(WeedData[weedid][weedExists] && areaid == WeedData[weedid][weedArea])
	{
		new str[128];
		if(WeedData[weedid][weedGrow] < MAX_GROW)
			format(str, 128, "On Growth~n~~y~%d minute left.", MAX_GROW-WeedData[weedid][weedGrow]);
		else
			format(str, 128, "Ready to harvest~n~Press ~y~H ~w~to harvest.");

		ShowBox(playerid, "~r~Plant_Info", str, 2);
	}*/
}

task timer_SaveWeedData[1200000]() {
	for(new i = 0; i < MAX_WEED; i++) if(WeedData[i][weedExists]) {
		Weed_Save(i);
	}
	return 1;
}