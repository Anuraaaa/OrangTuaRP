#define         	House_GetType(%0)			house_type[%0]

enum hData
{
	houseID,
	bool:houseExists,
	houseOwner,
	houseOwnerName[64],
	housePrice,
	Float:housePos[4],
	Float:houseInt[4],
	houseInterior,
	houseExterior,
	houseExteriorVW,
	houseLocked,
	houseType,
	bool:houseLights,
	Text3D:houseText3D,
	STREAMER_TAG_PICKUP:housePickup,
	STREAMER_TAG_CP:houseCP,
	houseWeapons[10],
	houseAmmo[10],
	houseDurability[10],
	houseHighVelocity[10],
	houseMoney,
	housePark,
	houseVehInside,
	houseLastLogin,
	Float:houseParkPos[3],
	STREAMER_TAG_CP:houseParkCP,
	Text3D:houseParkLabel,
	STREAMER_TAG_MAP_ICON:houseIcon,
	houseTaxPaid,
	houseTaxState,
	houseTaxDate,
	houseFurnitureLevel

};

enum { 
	HOUSE_TYPE_LOW = 1,
	HOUSE_TYPE_MEDIUM,
	HOUSE_TYPE_HIGH
};

new HouseData[MAX_HOUSES][hData];
new Iterator:House<MAX_HOUSES>;

enum houseStorage
{
	hItemID,
	hItemExists,
	hItemName[32 char],
	hItemModel,
	hItemQuantity
};

new HouseStorage[MAX_HOUSES][MAX_HOUSE_STORAGE][houseStorage];

new house_type[][] = {
	"None",
	"Low",
	"Medium",
	"High"
};

stock House_WeaponStorage(playerid, houseid)
{
	static
	    string[712];

	string[0] = 0;

	for (new i = 0; i < 10; i ++)
	{
	    if (!HouseData[houseid][houseWeapons][i])
	        format(string, sizeof(string), "%sEmpty Slot\n", string);

		else
			format(string, sizeof(string), "%s%s ({FFFF00}Ammo: %d{FFFFFF}) ({00FFFF}Durability: %d{FFFFFF})\n", string, ReturnWeaponName(HouseData[houseid][houseWeapons][i]), HouseData[houseid][houseAmmo][i], HouseData[houseid][houseDurability][i]);
	}
	ShowPlayerDialog(playerid, DIALOG_HOUSEWEAPON, DIALOG_STYLE_LIST, "Weapon Storage", string, "Select", "Cancel");
	return 1;
}

stock House_OpenStorage(playerid, houseid)
{
	new
		items[2],
		string[MAX_HOUSE_STORAGE * 32];

	for (new i = 0; i < MAX_HOUSE_STORAGE; i ++) if (HouseStorage[houseid][i][hItemExists])
	{
	    items[0]++;
	}
	for (new i = 0; i < 10; i ++) if (HouseData[houseid][houseWeapons][i])
	{
	    items[1]++;
	}
 	format(string, sizeof(string), "Item Storage (%d/%d)\nWeapon Storage (%d/10)", items[0], MAX_HOUSE_STORAGE, items[1]);
	ShowPlayerDialog(playerid, DIALOG_HOUSESTORAGE, DIALOG_STYLE_LIST, "House Storage", string, "Select", "Cancel");
	return 1;
}


stock House_ShowItems(playerid, houseid)
{
    if (houseid == -1 || !HouseData[houseid][houseExists])
	    return 0;

	static
	    string[MAX_HOUSE_STORAGE * 32],
		name[32];

	string[0] = 0;

	for (new i = 0; i != MAX_HOUSE_STORAGE; i ++)
	{
	    if (!HouseStorage[houseid][i][hItemExists])
	        format(string, sizeof(string), "%sEmpty Slot\n", string);

		else
		{
			strunpack(name, HouseStorage[houseid][i][hItemName]);

			if (HouseStorage[houseid][i][hItemQuantity] == 1)
			{
			    format(string, sizeof(string), "%s%s\n", string, name);
			}
			else format(string, sizeof(string), "%s%s (%d)\n", string, name, HouseStorage[houseid][i][hItemQuantity]);
		}
	}
	ShowPlayerDialog(playerid, DIALOG_HOUSEITEM, DIALOG_STYLE_LIST, "Item Storage", string, "Select", "Cancel");
	return 1;
}

House_TenantLimit(type) {

	new limit = 0;
	switch(type) {
		case HOUSE_TYPE_LOW: limit = 3;
		case HOUSE_TYPE_MEDIUM: limit = 5;
		case HOUSE_TYPE_HIGH: limit = 7;
		default: limit = 3;
	}
	return limit;
}
stock House_GetItemID(houseid, item[])
{
	if (houseid == -1 || !HouseData[houseid][houseExists])
	    return 0;

	for (new i = 0; i < MAX_HOUSE_STORAGE; i ++)
	{
	    if (!HouseStorage[houseid][i][hItemExists])
	        continue;

		if (!strcmp(HouseStorage[houseid][i][hItemName], item)) return i;
	}
	return -1;
}

stock House_GetFreeID(houseid)
{
	if (houseid == -1 || !HouseData[houseid][houseExists])
	    return 0;

	for (new i = 0; i < MAX_HOUSE_STORAGE; i ++)
	{
	    if (!HouseStorage[houseid][i][hItemExists])
	        return i;
	}
	return -1;
}

stock House_AddItem(houseid, item[], model, quantity = 1, slotid = -1)
{
    if (houseid == -1 || !HouseData[houseid][houseExists])
	    return 0;

	new
		itemid = House_GetItemID(houseid, item),
		string[128];

	if (itemid == -1)
	{
	    itemid = House_GetFreeID(houseid);

	    if (itemid != -1)
	    {
	        if (slotid != -1)
	            itemid = slotid;

	        HouseStorage[houseid][itemid][hItemExists] = true;
	        HouseStorage[houseid][itemid][hItemModel] = model;
	        HouseStorage[houseid][itemid][hItemQuantity] = quantity;

	        strpack(HouseStorage[houseid][itemid][hItemName], item, 32 char);

			mysql_format(sqlcon, string, sizeof(string), "INSERT INTO `housestorage` (`ID`, `itemName`, `itemModel`, `itemQuantity`) VALUES('%d', '%s', '%d', '%d')", HouseData[houseid][houseID], item, model, quantity);
			mysql_tquery(sqlcon, string, "OnStorageAdd", "dd", houseid, itemid);

	        return itemid;
		}
		return -1;
	}
	else
	{
	    mysql_format(sqlcon, string, sizeof(string), "UPDATE `housestorage` SET `itemQuantity` = `itemQuantity` + %d WHERE `ID` = '%d' AND `itemID` = '%d'", quantity, HouseData[houseid][houseID], HouseStorage[houseid][itemid][hItemID]);
	    mysql_tquery(sqlcon, string);

	    HouseStorage[houseid][itemid][hItemQuantity] += quantity;
	}
	return itemid;
}

FUNC::OnStorageAdd(houseid, itemid)
{
	HouseStorage[houseid][itemid][hItemID] = cache_insert_id();
	return 1;
}

stock House_RemoveItem(houseid, item[], quantity = 1)
{
    if (houseid == -1 || !HouseData[houseid][houseExists])
	    return 0;

	new
		itemid = House_GetItemID(houseid, item),
		string[128];

	if (itemid != -1)
	{
	    if (HouseStorage[houseid][itemid][hItemQuantity] > 0)
	    {
	        HouseStorage[houseid][itemid][hItemQuantity] -= quantity;
		}
		if (quantity == -1 || HouseStorage[houseid][itemid][hItemQuantity] < 1)
		{
		    HouseStorage[houseid][itemid][hItemExists] = false;
		    HouseStorage[houseid][itemid][hItemModel] = 0;
		    HouseStorage[houseid][itemid][hItemQuantity] = 0;

		    mysql_format(sqlcon, string, sizeof(string), "DELETE FROM `housestorage` WHERE `ID` = '%d' AND `itemID` = '%d'", HouseData[houseid][houseID], HouseStorage[houseid][itemid][hItemID]);
	        mysql_tquery(sqlcon, string);
		}
		else if (quantity != -1 && HouseStorage[houseid][itemid][hItemQuantity] > 0)
		{
			mysql_format(sqlcon, string, sizeof(string), "UPDATE `housestorage` SET `itemQuantity` = `itemQuantity` - %d WHERE `ID` = '%d' AND `itemID` = '%d'", quantity, HouseData[houseid][houseID], HouseStorage[houseid][itemid][hItemID]);
            mysql_tquery(sqlcon, string);
		}
		return 1;
	}
	return 0;
}

stock House_Inside(playerid)
{
	if (PlayerData[playerid][pInHouse] != -1)
	{
	    foreach(new i : House) if (HouseData[i][houseID] == PlayerData[playerid][pInHouse] && GetPlayerInterior(playerid) == HouseData[i][houseInterior] && GetPlayerVirtualWorld(playerid) > 0) {
	        return i;
		}
	}
	return -1;
}

stock House_Nearest(playerid)
{
    foreach(new i : House) if (IsPlayerInRangeOfPoint(playerid, 3.0, HouseData[i][housePos][0], HouseData[i][housePos][1], HouseData[i][housePos][2]))
	{
		return i;
	}
	return -1;
}

stock HousePark_Nearest(playerid)
{
	foreach(new i : House) if(IsPlayerInDynamicCP(playerid, HouseData[i][houseParkCP]))
	{
		return i;
	}
	return 1;
}

stock House_IsOwner(playerid, houseid)
{
	if (PlayerData[playerid][pID] == -1)
	    return 0;

    if (HouseData[houseid][houseOwner] != 0 && HouseData[houseid][houseOwner] == PlayerData[playerid][pID])
		return 1;

	return 0;
}

stock House_Spawn(i)
{
	static
	    string[256];

	if(HouseData[i][houseParkPos][0] != 0 && HouseData[i][houseParkPos][1] != 0 && HouseData[i][houseParkPos][2] != 0 && HouseData[i][housePark] != 0)
	{
		new str[156];
		format(str, sizeof(str), "[ID: %d]\n{FFFFFF}Parking Slot: {FF6347}%d\n{FFFFFF}Type {FF0000}/house park {FFFFFF}to access", i, HouseData[i][housePark]);

		HouseData[i][houseParkCP] = CreateDynamicCP(HouseData[i][houseParkPos][0], HouseData[i][houseParkPos][1], HouseData[i][houseParkPos][2], 3.0, -1, -1, -1, 3.0);
		HouseData[i][houseParkLabel] = CreateDynamic3DTextLabel(str, 0x007FFFFF, HouseData[i][houseParkPos][0], HouseData[i][houseParkPos][1], HouseData[i][houseParkPos][2], 15.0);
	}
	if (!HouseData[i][houseOwner])
	{
		format(string, sizeof(string), "[ID: %d]\n{33CC33}This house for sell\n{FFFFFF}House Type: {FFFF00}%s\n{FFFFFF}Address: {FFFF00}%s\n{FFFFFF}Price: {FFFF00}$%s\n{FFFFFF}Parking Slot: {FF6347}%d\n{FFFFFF}Type /house buy to purchase", i, House_GetType(HouseData[i][houseType]), GetLocation(HouseData[i][housePos][0], HouseData[i][housePos][1], HouseData[i][housePos][2]), FormatNumber(HouseData[i][housePrice]), HouseData[i][housePark]);
        HouseData[i][houseText3D] = CreateDynamic3DTextLabel(string, 0x007FFFFF, HouseData[i][housePos][0], HouseData[i][housePos][1], HouseData[i][housePos][2], 7.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, HouseData[i][houseExteriorVW], HouseData[i][houseExterior]);
        HouseData[i][housePickup] = CreateDynamicPickup(1272, 23, HouseData[i][housePos][0], HouseData[i][housePos][1], HouseData[i][housePos][2], HouseData[i][houseExteriorVW], HouseData[i][houseExterior]);
		HouseData[i][houseIcon] = CreateDynamicMapIcon(HouseData[i][housePos][0], HouseData[i][housePos][1], HouseData[i][housePos][2], 31, -1, -1, -1, -1, 30.0);
	}
	else
	{
		format(string, sizeof(string), "[ID: %d]\n{FFFFFF}Owner: {FFFF00}%s\n{FFFFFF}Address: {FFFF00}%s\n{FFFFFF}Parking Slot: {FF6347}%d\n{FFFFFF}Press {FF0000}ENTER {FFFFFF}to enter house", i, HouseData[i][houseOwnerName], GetLocation(HouseData[i][housePos][0], HouseData[i][housePos][1], HouseData[i][housePos][2]), HouseData[i][housePark]);
		HouseData[i][houseText3D] = CreateDynamic3DTextLabel(string, 0x007FFFFF, HouseData[i][housePos][0], HouseData[i][housePos][1], HouseData[i][housePos][2], 7.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, HouseData[i][houseExteriorVW], HouseData[i][houseExterior]);
        HouseData[i][housePickup] = CreateDynamicPickup(1272, 23, HouseData[i][housePos][0], HouseData[i][housePos][1], HouseData[i][housePos][2], HouseData[i][houseExteriorVW], HouseData[i][houseExterior]);
		HouseData[i][houseIcon] = CreateDynamicMapIcon(HouseData[i][housePos][0], HouseData[i][housePos][1], HouseData[i][housePos][2], 32, -1, -1, -1, -1, 15.0);
	}
	return 1;
}
stock House_Create(playerid, price, type)
{
	static
	    Float:x,
	    Float:y,
	    Float:z,
		Float:angle;

	if (GetPlayerPos(playerid, x, y, z) && GetPlayerFacingAngle(playerid, angle))
	{
		new i = Iter_Free(House);

        HouseData[i][houseExists] = true;
	    HouseData[i][houseOwner] = 0;
    	HouseData[i][housePrice] = price;
    	HouseData[i][houseMoney] = 0;
        HouseData[i][housePos][0] = x;
        HouseData[i][housePos][1] = y;
        HouseData[i][housePos][2] = z;
        HouseData[i][housePos][3] = angle;
        HouseData[i][housePark] = 0;
		HouseData[i][houseVehInside] = 0;

		HouseData[i][houseType] = type;

		HouseData[i][houseExterior] = GetPlayerInterior(playerid);
		HouseData[i][houseExteriorVW] = GetPlayerVirtualWorld(playerid);

		HouseData[i][houseLocked] = true;

		HouseData[i][houseTaxDate] = gettime() + (14 * 86400);
		HouseData[i][houseTaxState] = TAX_STATE_COOLDOWN;
		HouseData[i][houseTaxPaid] = true;
		HouseData[i][houseFurnitureLevel] = 1;

		House_Spawn(i);

		Iter_Add(House, i);
		mysql_tquery(sqlcon, "INSERT INTO `houses` (`houseOwner`) VALUES(0)", "OnHouseCreated", "d", i);

		House_SetInterior(i);
		return i;
	}
	return -1;
}

stock House_Save(houseid)
{
	new
	    query[2836];

	mysql_format(sqlcon, query, sizeof(query), "UPDATE `houses` SET `houseOwner` = '%d', `housePrice` = '%d', `houseOwnerName` = '%s', `housePosX` = '%.4f', `housePosY` = '%.4f', `housePosZ` = '%.4f', `housePosA` = '%.4f', `houseIntX` = '%.4f', `houseIntY` = '%.4f', `houseIntZ` = '%.4f', `houseIntA` = '%.4f', `houseInterior` = '%d', `houseExterior` = '%d', `houseExteriorVW` = '%d'",
	    HouseData[houseid][houseOwner],
	    HouseData[houseid][housePrice],
	    HouseData[houseid][houseOwnerName],
	    HouseData[houseid][housePos][0],
	    HouseData[houseid][housePos][1],
	    HouseData[houseid][housePos][2],
	    HouseData[houseid][housePos][3],
	    HouseData[houseid][houseInt][0],
	    HouseData[houseid][houseInt][1],
	    HouseData[houseid][houseInt][2],
	    HouseData[houseid][houseInt][3],
        HouseData[houseid][houseInterior],
        HouseData[houseid][houseExterior],
        HouseData[houseid][houseExteriorVW]
	);
	for (new i = 0; i < 10; i ++)
	{
		mysql_format(sqlcon,query, sizeof(query), "%s, `houseWeapon%d` = '%d', `houseAmmo%d` = '%d', `houseDurability%d` = '%d', `houseHighVelocity%d` = '%d'", query, i + 1, HouseData[houseid][houseWeapons][i], i + 1, HouseData[houseid][houseAmmo][i], i + 1, HouseData[houseid][houseDurability][i], i + 1, HouseData[houseid][houseHighVelocity][i]);
	}
	mysql_format(sqlcon,query, sizeof(query), "%s, `houseLocked` = '%d', `houseMoney` = '%d', `housePark` = '%d', `houseParkX` = '%f', `houseParkY` = '%f', `houseParkZ` = '%f', `houseVehInside` = '%d', `houseType` = '%d', `LastLogin` = '%d', `TaxPaid` = '%d', `TaxDate` = '%d', `TaxState` = '%d', `FurnitureLevel` = '%d' WHERE `houseID` = '%d'",
	    query,
	    HouseData[houseid][houseLocked],
	    HouseData[houseid][houseMoney],
	    HouseData[houseid][housePark],
	    HouseData[houseid][houseParkPos][0],
	    HouseData[houseid][houseParkPos][1],
	    HouseData[houseid][houseParkPos][2],
		HouseData[houseid][houseVehInside],
		HouseData[houseid][houseType],
		HouseData[houseid][houseLastLogin],
		HouseData[houseid][houseTaxPaid],
		HouseData[houseid][houseTaxDate],
		HouseData[houseid][houseTaxState],
		HouseData[houseid][houseFurnitureLevel],
        HouseData[houseid][houseID]
	);
	return mysql_tquery(sqlcon, query);
}

CMD:sethwep(playerid, params[]) {

	new query[612];
	mysql_format(sqlcon, query, sizeof(query), "UPDATE `houses` SET `houseWeapon1` = '%d'", 0);
	for (new i = 0; i < 10; i ++)
	{
		mysql_format(sqlcon,query, sizeof(query), "%s, `houseWeapon%d` = '%d', `houseAmmo%d` = '%d', `houseDurability%d` = '%d'", query, i + 1, 0, i + 1, 0, i + 1, 0);
	}
	mysql_tquery(sqlcon, query);
	return 1;
}
stock House_CountVehicle(id)
{
	return HouseData[id][houseVehInside];
}

ShowHouseMenu(playerid) {
	return ShowPlayerDialog(playerid, DIALOG_HOUSE_MENU, DIALOG_STYLE_LIST, "House Menu", "Manage Furniture\nAccess Storage\nKey Management", "Select", "Close");
}
FUNC::OnHouseCreated(houseid)
{
	if (houseid == -1 || !HouseData[houseid][houseExists])
	    return 0;

	HouseData[houseid][houseID] = cache_insert_id();
	House_Save(houseid);

	return 1;
}

stock House_HaveAccess(playerid, id) {

	new bool:access = false;

	if(!Iter_Contains(House, id))
		return false;

	if(House_IsOwner(playerid, id))
		return true;

	else {


		new Cache:result = mysql_query(sqlcon, sprintf("SELECT * FROM `housekeys` WHERE `PlayerID` = %d AND `HouseID` = %d ORDER BY `ID` ASC LIMIT  1;", PlayerData[playerid][pID], HouseData[id][houseID]));
	
		if(!cache_num_rows()) 
			access = false;

		else
			access = true;

		cache_delete(result);
	
	}
	return access;
}


FUNC::House_CheckSharedKey(playerid, id) {
	if(!cache_num_rows())
		return ShowPlayerDialog(playerid, DIALOG_NONE, DIALOG_STYLE_MSGBOX, "House Shared Key", "Tidak ada player yang memiliki kunci rumah ini.", "Close", "");

	new str[356];
	for(new i = 0; i < cache_num_rows(); i++) {
		new name[MAX_PLAYER_NAME];
		cache_get_value_name(i, "Name", name, MAX_PLAYER_NAME);

		strcat(str, sprintf("%d). %s\n", i + 1, name));
	}
	ShowPlayerDialog(playerid, DIALOG_NONE, DIALOG_STYLE_MSGBOX, "House Shared Key", str, "Close", "");
	return 1;
}

House_ShowKeyMenu(playerid, id) {

	if(!Iter_Contains(House, id))
		return 0;

	if(!House_IsOwner(playerid, id))
		return 0;

	ShowPlayerDialog(playerid, DIALOG_HOUSE_KEY, DIALOG_STYLE_LIST, "House Key Management", "Share Key\nRevoke Key\nWho have this house key..", "Select", "Close");
	return 1;
}

stock IsPlayerHouseGuest(playerid) {
	new is_guest = 0,
		Cache:execute;

	execute = mysql_query(sqlcon, sprintf("SELECT * FROM `housekeys` WHERE `PlayerID` = '%d'", PlayerData[playerid][pID]));

	if(cache_num_rows()) {
		is_guest = 1;
	}

	cache_delete(execute);
	return is_guest;
}

stock House_FurnitureCount(houseid)
{
	new count;

	foreach(new i : Furniture) if (FurnitureData[i][furnitureProperty] == HouseData[houseid][houseID] && FurnitureData[i][furniturePropertyType] == FURNITURE_TYPE_HOUSE) {
	    count++;
	}
	return count;
}
/*
stock Furniture_Spawn(furnitureid)
{
	if(Iter_Contains(Furniture, furnitureid))
	{
		if(FurnitureData[furnitureid][furniturePropertyType] == FURNITURE_TYPE_HOUSE) {
			FurnitureData[furnitureid][furnitureObject] = CreateDynamicObject(
				FurnitureData[furnitureid][furnitureModel],
				FurnitureData[furnitureid][furniturePos][0],
				FurnitureData[furnitureid][furniturePos][1],
				FurnitureData[furnitureid][furniturePos][2],
				FurnitureData[furnitureid][furnitureRot][0],
				FurnitureData[furnitureid][furnitureRot][1],
				FurnitureData[furnitureid][furnitureRot][2],
				HouseData[FurnitureData[furnitureid][furnitureProperty]][houseID] + 5000,
				HouseData[FurnitureData[furnitureid][furnitureProperty]][houseInterior]	
			);
		}	
		else {

			FurnitureData[furnitureid][furnitureObject] = CreateDynamicObject(
				FurnitureData[furnitureid][furnitureModel],
				FurnitureData[furnitureid][furniturePos][0],
				FurnitureData[furnitureid][furniturePos][1],
				FurnitureData[furnitureid][furniturePos][2],
				FurnitureData[furnitureid][furnitureRot][0],
				FurnitureData[furnitureid][furnitureRot][1],
				FurnitureData[furnitureid][furnitureRot][2],
				FlatData[FurnitureData[furnitureid][furnitureProperty]][flatIntWorld] + 5000,
				Flat[FurnitureData[furnitureid][furnitureProperty]][flatIntInterior]	
			);
		}
	}
	return 1;
}
*/


FUNC::House_Load()
{
	new owner[64], str[128];
	
	new rows = cache_num_rows();
 	if(rows)
  	{
		for(new i; i < rows; i++)
		{
			HouseData[i][houseExists] = true;
            cache_get_value_name_int(i,"houseID",HouseData[i][houseID]);
            cache_get_value_name_int(i,"houseOwner",HouseData[i][houseOwner]);
            cache_get_value_name_int(i,"housePrice",HouseData[i][housePrice]);

			cache_get_value_name(i, "houseOwnerName", owner);
			format(HouseData[i][houseOwnerName], 64, owner);

            cache_get_value_name_float(i,"housePosX",HouseData[i][housePos][0]);
            cache_get_value_name_float(i,"housePosY",HouseData[i][housePos][1]);
            cache_get_value_name_float(i,"housePosZ",HouseData[i][housePos][2]);
            cache_get_value_name_float(i,"housePosA",HouseData[i][housePos][3]);

            cache_get_value_name_float(i,"houseIntX",HouseData[i][houseInt][0]);
            cache_get_value_name_float(i,"houseIntY",HouseData[i][houseInt][1]);
            cache_get_value_name_float(i,"houseIntZ",HouseData[i][houseInt][2]);
            cache_get_value_name_float(i,"houseIntA",HouseData[i][houseInt][3]);

            cache_get_value_name_int(i,"houseInterior",HouseData[i][houseInterior]);
            cache_get_value_name_int(i,"houseExterior",HouseData[i][houseExterior]);
			cache_get_value_name_int(i,"houseExteriorVW",HouseData[i][houseExteriorVW]);
			cache_get_value_name_int(i,"houseLocked",HouseData[i][houseLocked]);
			cache_get_value_name_int(i,"houseMoney",HouseData[i][houseMoney]);
			cache_get_value_name_int(i,"housePark", HouseData[i][housePark]);

			cache_get_value_name_float(i, "houseParkX", HouseData[i][houseParkPos][0]);
			cache_get_value_name_float(i, "houseParkY", HouseData[i][houseParkPos][1]);
			cache_get_value_name_float(i, "houseParkZ", HouseData[i][houseParkPos][2]);
			cache_get_value_name_int(i, "houseVehInside", HouseData[i][houseVehInside]);

			cache_get_value_name_int(i, "houseType", HouseData[i][houseType]);

			cache_get_value_name_int(i, "LastLogin", HouseData[i][houseLastLogin]);

			cache_get_value_name_int(i, "TaxPaid", HouseData[i][houseTaxPaid]);
			cache_get_value_name_int(i, "TaxDate", HouseData[i][houseTaxDate]);
			cache_get_value_name_int(i, "TaxState", HouseData[i][houseTaxState]);
			cache_get_value_name_int(i, "FurnitureLevel", HouseData[i][houseFurnitureLevel]);
			
	        for (new j = 0; j < 10; j ++)
			{
	            format(str, 24, "houseWeapon%d", j + 1);
	            cache_get_value_name_int(i,str,HouseData[i][houseWeapons][j]);

	            format(str, 24, "houseAmmo%d", j + 1);
	            cache_get_value_name_int(i,str,HouseData[i][houseAmmo][j]);
	            
	            format(str, 24, "houseDurability%d", j + 1);
	            cache_get_value_name_int(i,str,HouseData[i][houseDurability][j]);

	            format(str, 24, "houseHighVelocity%d", j + 1);
	            cache_get_value_name_int(i,str,HouseData[i][houseHighVelocity][j]);
			}
			// mysql_format(sqlcon, str, sizeof(str), "SELECT * FROM `furniture` WHERE `ID` = '%d'", HouseData[i][houseID]);
			// mysql_tquery(sqlcon, str, "OnLoadFurniture", "dd", HouseData[i][houseID], FURNITURE_TYPE_HOUSE);//a

			Iter_Add(House, i);
			House_Spawn(i);
		}
		printf("[HOUSE] Loaded %d House from the Database", rows);
	}
	foreach(new i : House)
	{
		mysql_format(sqlcon, str, sizeof(str), "SELECT * FROM `housestorage` WHERE `ID` = '%d'", HouseData[i][houseID]);
		mysql_tquery(sqlcon, str, "OnLoadStorage", "d", i);
	}
	return 1;
}

House_SetInterior(houseid) {

	if(!Iter_Contains(House, houseid))
		return 0;

	new randomize;

	switch(HouseData[houseid][houseType]) {

		case HOUSE_TYPE_LOW: {

			randomize = random(2);
			if(randomize == 0) {
				HouseData[houseid][houseInt][0] = 2819.3452;
				HouseData[houseid][houseInt][1] = 1537.2881;
				HouseData[houseid][houseInt][2] = 510.9844;
				HouseData[houseid][houseInt][3] = 3.8450;
				HouseData[houseid][houseInterior] = 11;			
			}
			else if(randomize == 1) {
				HouseData[houseid][houseInt][0] = 2815.4443;
				HouseData[houseid][houseInt][1] = 1039.8804;
				HouseData[houseid][houseInt][2] = 1092.5538;
				HouseData[houseid][houseInt][3] = 358.1671;
				HouseData[houseid][houseInterior] = 10;		
			}
		}
		case HOUSE_TYPE_MEDIUM: {
			randomize = random(2);

			if(randomize == 0) {
				HouseData[houseid][houseInt][0] = 1882.1200;
				HouseData[houseid][houseInt][1] = -2434.8401;
				HouseData[houseid][houseInt][2] = 13.5845;
				HouseData[houseid][houseInt][3] = 358.3110;
				HouseData[houseid][houseInterior] = 4;					
			}
			else if(randomize == 1) {
				HouseData[houseid][houseInt][0] = 2886.9766;
				HouseData[houseid][houseInt][1] = 2225.2100;
				HouseData[houseid][houseInt][2] = 710.9063;
				HouseData[houseid][houseInt][3] = 1.6160;
				HouseData[houseid][houseInterior] = 8;					
			}
		}
		case HOUSE_TYPE_HIGH: {
			randomize = random(2);
			if(randomize == 0) {
				HouseData[houseid][houseInt][0] = 1410.0056;
				HouseData[houseid][houseInt][1] = 1781.1700;
				HouseData[houseid][houseInt][2] = 11008.9063;
				HouseData[houseid][houseInt][3] = 87.1983;
				HouseData[houseid][houseInterior] = 9;			
			}
			else if(randomize == 1) {
				HouseData[houseid][houseInt][0] = 1882.1200;
				HouseData[houseid][houseInt][1] = -2434.8401;
				HouseData[houseid][houseInt][2] = 13.5845;
				HouseData[houseid][houseInt][3] = 358.3110;
				HouseData[houseid][houseInterior] = 5;				
			}
		}
	}
	return 1;
}
FUNC::OnLoadStorage(houseid)
{
	static
		str[32];

	new rows = cache_num_rows();
 	if(rows)
  	{
		for(new i; i < rows; i++)
		{
		    HouseStorage[houseid][i][hItemExists] = true;
		    
		    cache_get_value_name_int(i, "itemID", HouseStorage[houseid][i][hItemID]);
		    cache_get_value_name_int(i, "itemModel", HouseStorage[houseid][i][hItemModel]);
		    cache_get_value_name_int(i, "itemQuantity", HouseStorage[houseid][i][hItemQuantity]);
		    cache_get_value_name(i, "itemName", str);
			strpack(HouseStorage[houseid][i][hItemName], str, 32 char);
		}
	}
	return 1;
}
stock House_Refresh(houseid)
{
	if (houseid != -1 && HouseData[houseid][houseExists])
	{
		new string[256];
		if(HouseData[houseid][houseParkPos][0] != 0 && HouseData[houseid][houseParkPos][1] != 0 && HouseData[houseid][houseParkPos][2] != 0 && HouseData[houseid][housePark] != 0)
		{
			new str[156];
			format(str, sizeof(str), "[ID: %d]\n{FFFFFF}Parking Slot: {FF6347}%d\n{FFFFFF}Type {FF0000}/house park {FFFFFF}to access", houseid, HouseData[houseid][housePark]);
			UpdateDynamic3DTextLabelText(HouseData[houseid][houseParkLabel], 0x007FFFFF, str);

			Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, HouseData[houseid][houseParkLabel], E_STREAMER_X, HouseData[houseid][houseParkPos][0]);
			Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, HouseData[houseid][houseParkLabel], E_STREAMER_Y, HouseData[houseid][houseParkPos][1]);
			Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, HouseData[houseid][houseParkLabel], E_STREAMER_Z, HouseData[houseid][houseParkPos][2]);

			Streamer_SetFloatData(STREAMER_TYPE_CP, HouseData[houseid][houseParkCP], E_STREAMER_X, HouseData[houseid][houseParkPos][0]);
			Streamer_SetFloatData(STREAMER_TYPE_CP, HouseData[houseid][houseParkCP], E_STREAMER_Y, HouseData[houseid][houseParkPos][1]);
			Streamer_SetFloatData(STREAMER_TYPE_CP, HouseData[houseid][houseParkCP], E_STREAMER_Z, HouseData[houseid][houseParkPos][2]);
		}
		if(HouseData[houseid][houseOwner] < 1)
		{
			format(string, sizeof(string), "[ID: %d]\n{33CC33}This house for sell\n{FFFFFF}House Type: {FFFF00}%s\n{FFFFFF}Address: {FFFF00}%s\n{FFFFFF}Price: {FFFF00}$%s\n{FFFFFF}Parking Slot: {FF6347}%d\n{FFFFFF}Type /house buy to purchase", houseid, House_GetType(HouseData[houseid][houseType]), GetLocation(HouseData[houseid][housePos][0], HouseData[houseid][housePos][1], HouseData[houseid][housePos][2]), FormatNumber(HouseData[houseid][housePrice]), HouseData[houseid][housePark]);
		}
		else
		{
			format(string, sizeof(string), "[ID: %d]\n{FFFFFF}Owned by {FFFF00}%s\n{FFFFFF}Address: {FFFF00}%s\n{FFFFFF}Parking Slot: {FF6347}%d\n{FFFFFF}Press {FF0000}ENTER {FFFFFF}to enter house", houseid, HouseData[houseid][houseOwnerName], GetLocation(HouseData[houseid][housePos][0], HouseData[houseid][housePos][1], HouseData[houseid][housePos][2]), HouseData[houseid][housePark]);
		}

		UpdateDynamic3DTextLabelText(HouseData[houseid][houseText3D], 0x007FFFFF, string);
		Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, HouseData[houseid][houseText3D], E_STREAMER_X, HouseData[houseid][housePos][0]);
		Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, HouseData[houseid][houseText3D], E_STREAMER_Y, HouseData[houseid][housePos][1]);
		Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, HouseData[houseid][houseText3D], E_STREAMER_Z, HouseData[houseid][housePos][2]);

		Streamer_SetFloatData(STREAMER_TYPE_PICKUP, HouseData[houseid][housePickup], E_STREAMER_X, HouseData[houseid][housePos][0]);
		Streamer_SetFloatData(STREAMER_TYPE_PICKUP, HouseData[houseid][housePickup], E_STREAMER_Y, HouseData[houseid][housePos][1]);
		Streamer_SetFloatData(STREAMER_TYPE_PICKUP, HouseData[houseid][housePickup], E_STREAMER_Z, HouseData[houseid][housePos][2]);

		Streamer_SetPosition(STREAMER_TYPE_MAP_ICON, HouseData[houseid][houseIcon], HouseData[houseid][housePos][0], HouseData[houseid][housePos][1], HouseData[houseid][housePos][2]);
	}
	return 1;
}

stock House_Delete(houseid)
{
	if (Iter_Contains(House, houseid))
	{
	    new
	        string[128];


		mysql_format(sqlcon,string, sizeof(string), "DELETE FROM `houses` WHERE `houseID` = '%d'", HouseData[houseid][houseID]);
		mysql_tquery(sqlcon, string);

		mysql_tquery(sqlcon, sprintf("DELETE FROM `housekeys` WHERE `HouseID` = '%d'", HouseData[houseid][houseID]));

        if (IsValidDynamic3DTextLabel(HouseData[houseid][houseText3D]))
		    DestroyDynamic3DTextLabel(HouseData[houseid][houseText3D]);

		if (IsValidDynamicPickup(HouseData[houseid][housePickup]))
		    DestroyDynamicPickup(HouseData[houseid][housePickup]);
        
        if(IsValidDynamicCP(HouseData[houseid][houseParkCP]))
        	DestroyDynamicCP(HouseData[houseid][houseParkCP]);

        if(IsValidDynamic3DTextLabel(HouseData[houseid][houseParkLabel]))
        	DestroyDynamic3DTextLabel(HouseData[houseid][houseParkLabel]);

        if(IsValidDynamicMapIcon(HouseData[houseid][houseIcon]))
        	DestroyDynamicMapIcon(HouseData[houseid][houseIcon]);

	    foreach(new i : Furniture) if (FurnitureData[i][furnitureProperty] == houseid) 
	    {
	        FurnitureData[i][furnitureExists] = false;
	        FurnitureData[i][furnitureModel] = 0;
            FurnitureData[i][furnitureProperty] = -1;

            if(IsValidDynamicObject(FurnitureData[i][furnitureObject]))
	        	DestroyDynamicObject(FurnitureData[i][furnitureObject]);
		}
		mysql_format(sqlcon, string, sizeof(string), "DELETE FROM `furniture` WHERE `ID` = '%d'", HouseData[houseid][houseID]);
		mysql_tquery(sqlcon, string);

	    HouseData[houseid][houseExists] = false;
	    HouseData[houseid][houseOwner] = 0;
	    HouseData[houseid][houseID] = 0;
	    Iter_SafeRemove(House, houseid, houseid);
	}
	return 1;
}

stock House_GetCount(playerid)
{
	new
		count = 0;

	foreach(new i : House)
	{
		if (House_IsOwner(playerid, i))
   		{
   		    count++;
		}
	}
	return count;
}

CMD:house(playerid, params[])
{
	new
	    type[24],
	    string[128],
	    id,
		index = -1;

	if (sscanf(params, "s[24]S()[128]", type, string))
	{
	    SendSyntaxMessage(playerid, "/house [entity]");
	    SendClientMessage(playerid, COLOR_SERVER, "ENTITY:{FFFFFF} buy, lock, menu, park, give");
	    return 1;
	}	
	if(!strcmp(type, "buy", true))
	{
		id = House_Nearest(playerid);

		if(House_GetCount(playerid) >= CountPlayerHouseSlot(playerid))
			return SendErrorMessage(playerid, "Kamu hanya bisa memiliki %d rumah!", CountPlayerHouseSlot(playerid));

		if(id == -1)
			return SendErrorMessage(playerid, "You're not in range of any houses!");

		if(HouseData[id][houseOwner] > 0)
			return SendErrorMessage(playerid, "This house is already owned!");

		if(GetMoney(playerid) < HouseData[id][housePrice])
			return SendErrorMessage(playerid, "You don't have enough money!");

		HouseData[id][houseTaxDate] = gettime() + (14 * 86400);
		HouseData[id][houseTaxState] = TAX_STATE_COOLDOWN;
		HouseData[id][houseTaxPaid] = true;

		HouseData[id][houseOwner] = PlayerData[playerid][pID];
		format(HouseData[id][houseOwnerName], 64, PlayerData[playerid][pName]);
		GiveMoney(playerid, -HouseData[id][housePrice]);
		SendServerMessage(playerid, "Kamu berhasil membeli house ini dengan harga {00FF00}$%s", FormatNumber(HouseData[id][housePrice]));
		SendServerMessage(playerid, "Jangan lupa untuk membayar pajak rumah ini setiap 14 hari!");
		
		House_Refresh(id);
		House_Save(id);
		notification.Show(playerid, "Property Info", "Property (House) purchased successfully!", "hud:radar_propertyG");
	}
	else if(!strcmp(type, "give", true)) {

		if((index = House_Nearest(playerid)) != -1) {

			if(!House_IsOwner(playerid, index))
				return SendErrorMessage(playerid, "Ini bukan rumah milikmu!");

			new targetid;

			if(sscanf(string, "u", targetid))
				return SendSyntaxMessage(playerid, "/house [give] [playerid/PartOfName]");

			if(!IsPlayerNearPlayer(playerid, targetid, 5.0) || targetid == INVALID_PLAYER_ID)
				return SendErrorMessage(playerid, "You have specified invalid player!");

			if(House_GetCount(targetid) >= CountPlayerHouseSlot(targetid))
				return SendErrorMessage(playerid, "Player tersebut tidak dapat memiliki banyak rumah lagi.");
				
			PlayerData[targetid][pHouseOffer] = index;
			PlayerData[targetid][pHouseOfferID] = playerid;
			SendServerMessage(targetid, "%s telah menawarkan kunci rumah miliknya, \"/accept house\" untuk menerima.", ReturnName(playerid));
			SendServerMessage(playerid, "Kamu telah menawarkan kunci rumah kepada %s.", ReturnName(targetid));
		}
		else SendErrorMessage(playerid, "Kamu harus didekat point rumah-mu!");
	}
	else if(!strcmp(type, "park", true))
	{
		if((id = HousePark_Nearest(playerid)) != -1 && House_IsOwner(playerid, id))
		{
			ShowPlayerDialog(playerid, DIALOG_HOUSE_PARK, DIALOG_STYLE_LIST, sprintf("Parking Slot: %d", HouseData[id][housePark]), "Take Vehicle\nPark Vehicle", "Select", "Close");
		}
	}
	else if(!strcmp(type, "lock", true))
	{
	    if ((id = House_Nearest(playerid)) != -1 && House_HaveAccess(playerid, id))
	    {
			if (!HouseData[id][houseLocked])
			{
				HouseData[id][houseLocked] = true;
				House_Save(id);

				ShowMessage(playerid, "You've ~r~locked ~w~the house", 3);
				PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
			}
			else
			{
				HouseData[id][houseLocked] = false;
				House_Save(id);

				ShowMessage(playerid, "You've ~g~unlocked ~w~the house", 3);
				PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
			}
			return 1;
		}
		else if ((id = House_Inside(playerid)) != -1 && House_HaveAccess(playerid, id) && IsPlayerInRangeOfPoint(playerid, 2.5, HouseData[id][houseInt][0], HouseData[id][houseInt][1], HouseData[id][houseInt][2]))
	    {
			if (!HouseData[id][houseLocked])
			{
				HouseData[id][houseLocked] = true;
				House_Save(id);

				ShowMessage(playerid, "You've ~r~locked ~w~the house", 3);
				PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
			}
			else
			{
				HouseData[id][houseLocked] = false;
				House_Save(id);

				ShowMessage(playerid, "You've ~g~unlocked ~w~the house", 3);
				PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
			}
			return 1;
		}
	}
	else if(!strcmp(type, "menu", true))
	{
		id = House_Inside(playerid);

		if(House_Inside(playerid) == -1)
			return SendErrorMessage(playerid, "You must inside your own house!");

		if(!House_HaveAccess(playerid, id))
			return SendErrorMessage(playerid, "You must inside your own house!");

		ShowHouseMenu(playerid);
	}
	return 1;
}

CMD:sethint(playerid, params[]) {

	foreach(new i : House) {
		House_SetInterior(i);
		House_Save(i);
	}
	return 1;
}
CMD:edithouse(playerid, params[])
{
	static
	    id,
	    type[24],
	    string[128];

	if (PlayerData[playerid][pAdmin] < 7)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "ds[24]S()[128]", id, type, string))
 	{
	 	SendSyntaxMessage(playerid, "/edithouse [id] [names]");
	    SendClientMessage(playerid, COLOR_YELLOW, "Names:{FFFFFF} location, interior, price, parkslot, parkpos, asell");
		return 1;
	}
	if (!Iter_Contains(House, id))
	    return SendErrorMessage(playerid, "You have specified an invalid house ID.");

	if (!strcmp(type, "location", true))
	{
		GetPlayerPos(playerid, HouseData[id][housePos][0], HouseData[id][housePos][1], HouseData[id][housePos][2]);
		GetPlayerFacingAngle(playerid, HouseData[id][housePos][3]);

		HouseData[id][houseExterior] = GetPlayerInterior(playerid);
		HouseData[id][houseExteriorVW] = GetPlayerVirtualWorld(playerid);

		House_Refresh(id);
		House_Save(id);

		SendAdminMessage(COLOR_LIGHTRED, "AdmCmd: %s has adjusted the location of house ID: %d.", PlayerData[playerid][pUCP], id);
	}
	else if(!strcmp(type, "type", true)) {

		new htype;
		if(sscanf(string, "d", htype))
			return SendSyntaxMessage(playerid, "/edithouse [id] [type] [1 - 3]");

		SendAdminMessage(COLOR_LIGHTRED, "AdmCmd: %s has adjusted House ID %d type to %s.", GetUsername(playerid), id, House_GetType(htype));
		HouseData[id][houseType] = htype;

		House_SetInterior(id);
		House_Refresh(id);
		House_Save(id);
	}
	else if (!strcmp(type, "parkpos", true))
	{
		GetPlayerPos(playerid, HouseData[id][houseParkPos][0], HouseData[id][houseParkPos][1], HouseData[id][houseParkPos][2]);

		if(!IsValidDynamic3DTextLabel(HouseData[id][houseParkLabel]))
		{
			new str[156];
			format(str, sizeof(str), "[ID: %d]\n{FFFFFF}Parking Slot: {FF6347}%d\n{FFFFFF}Type {FF0000}/house park {FFFFFF}to access", id, HouseData[id][housePark]);

			HouseData[id][houseParkCP] = CreateDynamicCP(HouseData[id][houseParkPos][0], HouseData[id][houseParkPos][1], HouseData[id][houseParkPos][2], 3.0, -1, -1, -1, 3.0);
			HouseData[id][houseParkLabel] = CreateDynamic3DTextLabel(str, 0x007FFFFF, HouseData[id][houseParkPos][0], HouseData[id][houseParkPos][1], HouseData[id][houseParkPos][2], 4.0);
		}
		House_Refresh(id);
		House_Save(id);

		SendAdminMessage(COLOR_LIGHTRED, "AdmCmd: %s has adjusted the park position of house ID: %d.", PlayerData[playerid][pUCP], id);
	}
	else if (!strcmp(type, "interior", true))
	{
	    GetPlayerPos(playerid, HouseData[id][houseInt][0], HouseData[id][houseInt][1], HouseData[id][houseInt][2]);
		GetPlayerFacingAngle(playerid, HouseData[id][houseInt][3]);

		HouseData[id][houseInterior] = GetPlayerInterior(playerid);

        foreach (new i : Player)
		{
			if (PlayerData[i][pInHouse] == id)
			{
				SetPlayerPos(i, HouseData[id][houseInt][0], HouseData[id][houseInt][1], HouseData[id][houseInt][2]);
				SetPlayerFacingAngle(i, HouseData[id][houseInt][3]);

				SetPlayerInterior(i, HouseData[id][houseInterior]);
				SetCameraBehindPlayer(i);
			}
		}
		House_Refresh(id);
		House_Save(id);
		SendAdminMessage(COLOR_LIGHTRED, "AdmCmd: %s has adjusted the interior spawn of house ID: %d.", PlayerData[playerid][pUCP], id);
	}
	else if (!strcmp(type, "price", true))
	{
	    new price[32];

	    if (sscanf(string, "s[32]", price))
	        return SendSyntaxMessage(playerid, "/edithouse [id] [price] [new price]");

	    HouseData[id][housePrice] = strcash(price);

		House_Refresh(id);
		House_Save(id);

		SendAdminMessage(COLOR_LIGHTRED, "AdmCmd: %s has adjusted the price of house ID: %d to $%s.",PlayerData[playerid][pUCP], id, FormatNumber(strcash(price)));
	}
	else if(!strcmp(type, "parkslot", true))
	{
		if(isnull(string))
			return SendSyntaxMessage(playerid, "/edithouse [id] [parkslot] [new slot]");

		HouseData[id][housePark] = strval(string);
		House_Refresh(id);
		House_Save(id);
		SendAdminMessage(COLOR_LIGHTRED, "AdmCmd: %s has adjusted the parking slot of house ID: %d to %d.",PlayerData[playerid][pUCP], id, strval(string));
	}
	else if(!strcmp(type, "asell", true))
	{
		HouseData[id][houseOwner] = 0;
		format(HouseData[id][houseOwner], 24, "No Owner");
		House_Refresh(id);
		House_Save(id);
		SendAdminMessage(COLOR_LIGHTRED, "AdmCmd: %s has aselled house ID: %d", PlayerData[playerid][pUCP], id);
	}
	else if(!strcmp(type, "hvi", true))
	{
		HouseData[id][houseVehInside] = 0;
		House_Save(id);
		SendAdminMessage(COLOR_LIGHTRED, "AdmCmd: %s has fixed house veh inside house ID: %d", PlayerData[playerid][pUCP], id);
	}
	return 1;
}

CMD:switch(playerid, params[])
{
	static
	    id = -1;

	if ((id = House_Inside(playerid)) != -1)
	{
		if (!HouseData[id][houseLights])
		{
		    foreach (new i : Player) if (House_Inside(i) == id) {
		        PlayerTextDrawHide(i, HOUSELAMP[i]);
		    }
		    SendNearbyMessage(playerid, 10.0, COLOR_PURPLE, "* %s flicks the light switch on.", ReturnName(playerid));
		    HouseData[id][houseLights] = true;
		}
		else
		{
		    foreach (new i : Player) if (House_Inside(i) == id) {
		        PlayerTextDrawShow(i, HOUSELAMP[i]);
		    }
		    SendNearbyMessage(playerid, 10.0, COLOR_PURPLE, "** %s flicks the light switch off.", ReturnName(playerid));
		    HouseData[id][houseLights] = false;
		}
	}
	else {
	    SendErrorMessage(playerid, "You must be in a house to use the lights.");
	}
	return 1;
}

CMD:createhouse(playerid, params[])
{
	new
	    price[32],
	    id,
		type;

    if (PlayerData[playerid][pAdmin] < 6)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "ds[32]", type, price))
	    return SendSyntaxMessage(playerid, "/createhouse [type] [price]"), SendClientMessage(playerid, COLOR_YELLOW, "Type: {FFFFFF}1. Low | 2. Medium | 3. High");

	if (type < 1 || type > 3)
	    return SendErrorMessage(playerid, "Invalid type specified. Types range from 1 to 3.");

	id = House_Create(playerid, strcash(price), type);

	if (id == -1)
	    return SendErrorMessage(playerid, "You can't add more Houses!");

	SendServerMessage(playerid, "You have successfully created house ID: %d.", id);
	return 1;
}

CMD:destroyhouse(playerid, params[])
{
	static
	    id = 0;

    if (PlayerData[playerid][pAdmin] < 7)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "d", id))
	    return SendSyntaxMessage(playerid, "/destroyhouse [house id]");

	if (!Iter_Contains(House, id))
	    return SendErrorMessage(playerid, "You have specified an invalid house ID.");

	House_Delete(id);
	SendServerMessage(playerid, "You have successfully destroyed house ID: %d.", id);
	return 1;
}

ptask HouseSwitchUpdate[1000](playerid) {

	new id = -1;
	if(IsPlayerSpawned(playerid))
	{
		switch (PlayerData[playerid][pHouseLights])
		{
			case 0:
			{
				if ((id = House_Inside(playerid)) != -1 && !HouseData[id][houseLights])
				{
					PlayerData[playerid][pHouseLights] = true;
					PlayerTextDrawShow(playerid, HOUSELAMP[playerid]);
				}
				else PlayerTextDrawHide(playerid, HOUSELAMP[playerid]);
			}
			case 1:
			{
				if ((id = House_Inside(playerid)) == -1 || (id != -1 && HouseData[id][houseLights]))
				{
					PlayerData[playerid][pHouseLights] = false;
					PlayerTextDrawHide(playerid, HOUSELAMP[playerid]);
				}
			}
		}
	}
	return 1;
}

FUNC::OnHouseQueue(playerid) {
	if(cache_num_rows()) {
		for(new i = 0; i < cache_num_rows(); i++) {
			new biz_id, msg[128];
			cache_get_value_name_int(i, "HouseID", biz_id);
			cache_get_value_name(i, "Message", msg, 128);

			if(!strcmp(msg, "idk", true))
				SendClientMessageEx(playerid, X11_LIGHTBLUE, "HOUSE: "WHITE"Housemu "YELLOW"(ID:%d) "WHITE"secara otomatis dijual oleh server karena tidak login selama 10 hari.", biz_id);
			else
				SendClientMessageEx(playerid, X11_LIGHTBLUE, "HOUSE: "WHITE"Housemu "YELLOW"(ID:%d) "WHITE"secara otomatis dijual oleh server karena tidak membayar pajak.", biz_id);
		}
	}
	mysql_tquery(sqlcon, sprintf("DELETE FROM `house_queue` WHERE `Username` = '%s'", GetName(playerid)));

	return 1;
}
task OnHouseAsellCheck[10000]() {
	foreach(new i : House) if(HouseData[i][houseLastLogin] != 0) {
		if(HouseData[i][houseLastLogin] < gettime()) {
			SendAdminMessage(X11_TOMATO, "HouseWarn: House ID: %d has been automatically aselled by the system.", i);

			mysql_tquery(sqlcon, sprintf("INSERT INTO `house_queue` (`Username`, `HouseID`) VALUES('%s','%d')", HouseData[i][houseOwnerName], i));
			HouseData[i][houseLastLogin] = 0;

			HouseData[i][houseOwner] = 0;
			// format(HouseData[i][houseOwnerName], MAX_PLAYER_NAME, "No Owner");

			House_Save(i);
			House_Refresh(i);
		}
	}
	return 1;
}//a