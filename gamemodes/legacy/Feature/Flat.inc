#include <YSI_Coding\y_hooks>

#define MAX_FLAT 					300
#define MAX_PLAYER_FLAT 			1
#define MAX_FLAT_STORAGE			6

enum flatData
{
	flatID,
	flatOwner,
	flatOwnerName[MAX_PLAYER_NAME],
	flatMoney,
	flatPrice,
	Float:flatPos[3],
	Float:flatInt[3],
	Text3D:flatLabel,
	STREAMER_TAG_PICKUP:flatPickup,
	flatExtWorld,
	flatIntWorld,
	flatExtInterior,
	flatIntInterior,
	flatLocked,
	flatWeapons[5],
	flatAmmo[5],
	flatDurability[5],
	flatSerial[5],
	flatHighVelocity[5],
	flatType,
	flatLastLogin,
	flatTaxDate,
	flatTaxPaid,
	flatTaxState,
	flatFurnitureLevel,
	flatSealed
};

new FlatData[MAX_FLAT][flatData], 
	Iterator:Flat<MAX_FLAT>;

enum E_FLAT_STORAGE
{
	fItemID,
	fItemExists,
	fItemName[32 char],
	fItemModel,
	fItemQuantity
};

new FlatStorage[MAX_FLAT][MAX_FLAT_STORAGE][E_FLAT_STORAGE];

enum {
	FLAT_TYPE_LOW = 0,
	FLAT_TYPE_MEDIUM,
	FLAT_TYPE_HIGH
};

hook OnGameModeInit() {

	if (IsSQLConnected()) {
		Iter_Init(Flat);
		mysql_tquery(sqlcon, "SELECT * FROM `flat`", "Flat_Load", "");
	}
}

hook OnGameModeExit() {

	if (IsSQLConnected()) {

		new time = GetTickCount();

		foreach(new i :  Flat) {
			Flat_Save(i);
		}
		printf("** Saved flat data in %dms", GetTickCount() - time);
		Iter_Clear(Flat);
	}
}

Flat_WeaponStorage(playerid, flatid)
{
	static
	    string[712];

	string[0] = 0;

	for (new i = 0; i < 5; i ++)
	{
	    if (!FlatData[flatid][flatWeapons][i])
	        format(string, sizeof(string), "%sEmpty Slot\n", string);

		else
			format(string, sizeof(string), "%s%s ({FFFF00}Ammo: %d{FFFFFF}) ({00FFFF}Durability: %d{FFFFFF})\n", string, ReturnWeaponName(FlatData[flatid][flatWeapons][i]), FlatData[flatid][flatAmmo][i], FlatData[flatid][flatDurability][i]);
	}
	ShowPlayerDialog(playerid, DIALOG_FLAT_WEAPON, DIALOG_STYLE_LIST, "Weapon Storage", string, "Select", "Cancel");
	return 1;
}

Flat_OpenStorage(playerid, flatid)
{
	new
		items[2],
		string[MAX_FLAT_STORAGE * 32];

	for (new i = 0; i < MAX_FLAT_STORAGE; i ++) if (FlatStorage[flatid][i][fItemExists])
	{
	    items[0]++;
	}
	for (new i = 0; i < 5; i ++) if (FlatData[flatid][flatWeapons][i])
	{
	    items[1]++;
	}
 	format(string, sizeof(string), "Item Storage (%d/%d)\nWeapon Storage (%d/5)", items[0], MAX_FLAT_STORAGE, items[1]);
	ShowPlayerDialog(playerid, DIALOG_FLAT_STORAGE, DIALOG_STYLE_LIST, "Flat Storage", string, "Select", "Cancel");
	return 1;
}


Flat_ShowItems(playerid, flatid)
{
	static
	    string[MAX_FLAT_STORAGE * 32],
		name[32];

	string[0] = 0;

	for (new i = 0; i != MAX_FLAT_STORAGE; i ++)
	{
	    if (!FlatStorage[flatid][i][fItemExists])
	        format(string, sizeof(string), "%sEmpty Slot\n", string);

		else
		{
			strunpack(name, FlatStorage[flatid][i][fItemName]);

			if (FlatStorage[flatid][i][fItemQuantity] == 1)
			{
			    format(string, sizeof(string), "%s%s\n", string, name);
			}
			else format(string, sizeof(string), "%s%s (%d)\n", string, name, FlatStorage[flatid][i][fItemQuantity]);
		}
	}
	ShowPlayerDialog(playerid, DIALOG_FLAT_ITEM, DIALOG_STYLE_LIST, "Item Storage", string, "Select", "Cancel");
	return 1;
}

Flat_GetItemID(flatid, item[])
{
	for (new i = 0; i < MAX_FLAT_STORAGE; i ++)
	{
	    if (!FlatStorage[flatid][i][fItemExists])
	        continue;

		if (!strcmp(FlatStorage[flatid][i][fItemName], item)) return i;
	}
	return -1;
}

Flat_GetFreeID(flatid)
{
	for (new i = 0; i < MAX_FLAT_STORAGE; i ++)
	{
	    if (!FlatStorage[flatid][i][fItemExists])
	        return i;
	}
	return -1;
}

IsPlayerFlatGuest(playerid) {
	new is_guest = 0,
		Cache:execute;

	execute = mysql_query(sqlcon, sprintf("SELECT * FROM `flatkeys` WHERE `PlayerID` = '%d'", PlayerData[playerid][pID]));

	if(cache_num_rows()) {
		is_guest = 1;
	}

	cache_delete(execute);
	return is_guest;
}

Flat_AddItem(flatid, item[], model, quantity = 1, slotid = -1)
{
	new
		itemid = Flat_GetItemID(flatid, item),
		string[256];

	if (itemid == -1)
	{
	    itemid = Flat_GetFreeID(flatid);

	    if (itemid != -1)
	    {
	        if (slotid != -1)
	            itemid = slotid;

	        FlatStorage[flatid][itemid][fItemExists] = true;
	        FlatStorage[flatid][itemid][fItemModel] = model;
	        FlatStorage[flatid][itemid][fItemQuantity] = quantity;

	        strpack(FlatStorage[flatid][itemid][fItemName], item, 32 char);

			mysql_format(sqlcon, string, sizeof(string), "INSERT INTO `flatstorage` (`ID`, `itemName`, `itemModel`, `itemQuantity`) VALUES('%d', '%s', '%d', '%d')", FlatData[flatid][flatID], item, model, quantity);
			mysql_tquery(sqlcon, string, "OnFlatStorageAdd", "dd", flatid, itemid);

	        return itemid;
		}
		return -1;
	}
	else
	{
	    mysql_format(sqlcon, string, sizeof(string), "UPDATE `flatstorage` SET `itemQuantity` = `itemQuantity` + %d WHERE `ID` = '%d' AND `itemID` = '%d'", quantity, FlatData[flatid][flatID], FlatStorage[flatid][itemid][fItemID]);
	    mysql_tquery(sqlcon, string);

	    FlatStorage[flatid][itemid][fItemQuantity] += quantity;
	}
	return itemid;
}

function OnFlatStorageAdd(flatid, itemid)
{
	FlatStorage[flatid][itemid][fItemID] = cache_insert_id();
	return 1;
}

Flat_RemoveItem(flatid, item[], quantity = 1)
{
	new
		itemid = Flat_GetItemID(flatid, item),
		string[128];

	if (itemid != -1)
	{
	    if (FlatStorage[flatid][itemid][fItemQuantity] > 0)
	    {
	        FlatStorage[flatid][itemid][fItemQuantity] -= quantity;
		}
		if (quantity == -1 || FlatStorage[flatid][itemid][fItemQuantity] < 1)
		{
		    FlatStorage[flatid][itemid][fItemExists] = false;
		    FlatStorage[flatid][itemid][fItemModel] = 0;
		    FlatStorage[flatid][itemid][fItemQuantity] = 0;

		    mysql_format(sqlcon, string, sizeof(string), "DELETE FROM `flatstorage` WHERE `ID` = '%d' AND `itemID` = '%d'", FlatData[flatid][flatID], FlatStorage[flatid][itemid][fItemID]);
	        mysql_tquery(sqlcon, string);
		}
		else if (quantity != -1 && FlatStorage[flatid][itemid][fItemQuantity] > 0)
		{
			mysql_format(sqlcon, string, sizeof(string), "UPDATE `flatstorage` SET `itemQuantity` = `itemQuantity` - %d WHERE `ID` = '%d' AND `itemID` = '%d'", quantity, FlatData[flatid][flatID], FlatStorage[flatid][itemid][fItemID]);
            mysql_tquery(sqlcon, string);
		}
		return 1;
	}
	return 0;
}


Flat_Create(Float:x, Float:y, Float:z, vw = 0, interior = 0, price = 0, type = FLAT_TYPE_LOW) {

	new index = INVALID_ITERATOR_SLOT;
	if((index = Iter_Alloc(Flat)) != INVALID_ITERATOR_SLOT) {

		FlatData[index][flatPos][0] = x;
		FlatData[index][flatPos][1] = y;
		FlatData[index][flatPos][2] = z;
		FlatData[index][flatType] = type;
		FlatData[index][flatPrice] = price;
		FlatData[index][flatLocked] = 1;
		FlatData[index][flatExtWorld] = vw;
		FlatData[index][flatExtInterior] = interior;
		FlatData[index][flatMoney] = 0;
		FlatData[index][flatOwner] = -1;
		FlatData[index][flatFurnitureLevel] = 1;
		FlatData[index][flatSealed] = 0;

		format(FlatData[index][flatOwnerName], MAX_PLAYER_NAME, "_");

		FlatData[index][flatTaxDate] = gettime() + (14 * 86400);
		FlatData[index][flatTaxState] = TAX_STATE_COOLDOWN;
		FlatData[index][flatTaxPaid] = true;

		for(new i = 0; i < 5; i++) {
			FlatData[index][flatWeapons][i] = 0;
			FlatData[index][flatAmmo][i] = 0;
			FlatData[index][flatDurability][i] = 0;
			FlatData[index][flatSerial][i] = 0;
		}
		Flat_SetupInterior(index, FlatData[index][flatType]);
		Flat_Sync(index);

		mysql_tquery(sqlcon, "INSERT INTO `flat` (`Price`) VALUES('0')", "OnFlatCreated", "d", index);
	}
	return index;
}

Flat_GetCount(playerid) {

	new total = 0;
	foreach(new i : Flat) if(Flat_IsOwner(playerid, i)) {
		total++;
	}
	return total;
}
Flat_Save(index) {
	new query[2512];
	mysql_format(sqlcon, query, sizeof(query), "UPDATE `flat` SET `Owner` = '%d', `OwnerName` = '%e', `Price` = '%d', `Money` = '%d', `Locked` = '%d', `Type` = '%d'",
		FlatData[index][flatOwner],
		FlatData[index][flatOwnerName],
		FlatData[index][flatPrice],
		FlatData[index][flatMoney],
		FlatData[index][flatLocked],
		FlatData[index][flatType]
	);
	mysql_format(sqlcon, query, sizeof(query), "%s, `ExtPosX` = '%f', `ExtPosY` = '%f', `ExtPosZ` = '%f', `IntPosX` = '%f', `IntPosY` = '%f', `IntPosZ` = '%f'", 
		query, 
		FlatData[index][flatPos][0],
		FlatData[index][flatPos][1],
		FlatData[index][flatPos][2],
		FlatData[index][flatInt][0],
		FlatData[index][flatInt][1], 
		FlatData[index][flatInt][2]
	);
	for (new i = 0; i < 5; i ++)
	{
		mysql_format(sqlcon,query, sizeof(query), "%s, `Weapon%d` = '%d', `Ammo%d` = '%d', `Durability%d` = '%d', `HighVelocity%d` = '%d'", query, i + 1, FlatData[index][flatWeapons][i], i + 1, FlatData[index][flatAmmo][i], i + 1, FlatData[index][flatDurability][i], i + 1, FlatData[index][flatHighVelocity][i]);
	}
	mysql_format(sqlcon, query, sizeof(query), "%s, `IntWorld` = '%d', `IntInterior` = '%d', `ExtWorld` = '%d', `ExtInterior` = '%d', `LastLogin` = '%d', `TaxState` = '%d', `TaxPaid` = '%d', `TaxDate` = '%d', `FurnitureLevel` = '%d', `Sealed` = '%d'",
		query, 
		FlatData[index][flatIntWorld],
		FlatData[index][flatIntInterior],
		FlatData[index][flatExtWorld],
		FlatData[index][flatExtInterior],
		FlatData[index][flatLastLogin],
		FlatData[index][flatTaxState],
		FlatData[index][flatTaxPaid],
		FlatData[index][flatTaxDate],
		FlatData[index][flatFurnitureLevel],
		FlatData[index][flatSealed]
	);
	mysql_format(sqlcon, query, sizeof(query), "%s WHERE `ID` = '%d' LIMIT 1;", query, FlatData[index][flatID]);
	return mysql_tquery(sqlcon, query);
}
Flat_Sync(index) {

	if(!Iter_Contains(Flat, index))
		return 0;

	new str[194];

	if(FlatData[index][flatOwner] == -1)
		format(str, sizeof(str), ""LIGHTBLUE"[Flat: %d]\n"WHITE"Flat type %s\nPrice: $%s\nType "GOLD"/flat buy "WHITE"to purchase.", index, Flat_ReturnType(FlatData[index][flatType]), FormatNumber(FlatData[index][flatPrice]));
	else {

		if(!FlatData[index][flatSealed])
			format(str, sizeof(str), ""LIGHTBLUE"[Flat: %d]\n"WHITE"Flat type %s\nOwned by %s", index, Flat_ReturnType(FlatData[index][flatType]), FlatData[index][flatOwnerName]);
		else
			format(str, sizeof(str), ""LIGHTBLUE"[Flat: %d]\n"WHITE"Flat type %s\nOwned by %s\n"WHITE"This flat is sealed by "RED"authority", index, Flat_ReturnType(FlatData[index][flatType]), FlatData[index][flatOwnerName]);
	}
	if(IsValidDynamic3DTextLabel(FlatData[index][flatLabel])) {
		Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, FlatData[index][flatLabel], FlatData[index][flatPos][0], FlatData[index][flatPos][1], FlatData[index][flatPos][2]);
		Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, FlatData[index][flatLabel], E_STREAMER_INTERIOR_ID, FlatData[index][flatExtInterior]);
		Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, FlatData[index][flatLabel], E_STREAMER_WORLD_ID, FlatData[index][flatExtWorld]);

		UpdateDynamic3DTextLabelText(FlatData[index][flatLabel], -1, str);
	}
	else FlatData[index][flatLabel] = CreateDynamic3DTextLabel(str, -1, FlatData[index][flatPos][0], FlatData[index][flatPos][1], FlatData[index][flatPos][2], 5.0, _, _, _, FlatData[index][flatExtWorld], FlatData[index][flatExtInterior], _, 5.0);
	
	if(IsValidDynamicPickup(FlatData[index][flatPickup])) {
		Streamer_SetItemPos(STREAMER_TYPE_PICKUP, FlatData[index][flatPickup], FlatData[index][flatPos][0], FlatData[index][flatPos][1], FlatData[index][flatPos][2]);
		Streamer_SetIntData(STREAMER_TYPE_PICKUP, FlatData[index][flatPickup], E_STREAMER_INTERIOR_ID, FlatData[index][flatExtInterior]);
		Streamer_SetIntData(STREAMER_TYPE_PICKUP, FlatData[index][flatPickup], E_STREAMER_WORLD_ID, FlatData[index][flatExtWorld]);
	}
	else FlatData[index][flatPickup] = CreateDynamicPickup(19523, 23, FlatData[index][flatPos][0], FlatData[index][flatPos][1], FlatData[index][flatPos][2], FlatData[index][flatExtWorld], FlatData[index][flatExtInterior], _, 10.0);
	
	return 1;
}

Flat_ReturnType(type) {

	new const flat_type[][] = {
		"Low",
		"Medium",
		"High"
	};
	new str[32];
	format(str, sizeof(str), "%s", flat_type[type]);
	return str;
}
Flat_SetupInterior(index, type) {
	if(!Iter_Contains(Flat, index))	
		return 0;

	switch(type) {
		case FLAT_TYPE_LOW: {
			FlatData[index][flatInt][0] =  2358.2234;
			FlatData[index][flatInt][1] = 968.2344;
			FlatData[index][flatInt][2] = 20.9434;
			FlatData[index][flatIntInterior] = 1;
		}
		case FLAT_TYPE_MEDIUM: {
			FlatData[index][flatInt][0] =  -147.5886;
			FlatData[index][flatInt][1] = 2826.3650;
			FlatData[index][flatInt][2] = 89.2977;
			FlatData[index][flatIntInterior] = 1;	
		}
		case FLAT_TYPE_HIGH: {
			FlatData[index][flatInt][0] =  2199.9990;
			FlatData[index][flatInt][1] = 2853.9646;
			FlatData[index][flatInt][2] = 13.3265;
			FlatData[index][flatIntInterior] = 1;
		}
	}
	return 1;
}
Flat_IsOwner(playerid, flat_id) {
	if(!Iter_Contains(Flat, flat_id))
		return 0;

	if(FlatData[flat_id][flatOwner] == PlayerData[playerid][pID])
		return 1;

	return 0;
}

function OnFlatCreated(flat_id) {
	if(!Iter_Contains(Flat, flat_id))
		return 0;

	FlatData[flat_id][flatID] = cache_insert_id();
	FlatData[flat_id][flatIntWorld] = FlatData[flat_id][flatID] + 150 + flat_id; /* This should be safe i guess lmao */

	Flat_Save(flat_id);

	return 1;
}

Flat_Interior(playerid, Float:range = 3.0) {

	new
		i = PlayerData[playerid][pInFlat];

	if(i == -1)
		return -1;

	if(IsPlayerInRangeOfPoint(playerid, range, FlatData[i][flatInt][0],  FlatData[i][flatInt][1],  FlatData[i][flatInt][2]) && GetPlayerVirtualWorld(playerid) == FlatData[i][flatIntWorld] && GetPlayerInterior(playerid) == FlatData[i][flatIntInterior]) {
		return i;
	}
	return -1;
}

Flat_Exterior(playerid, Float:range = 3.0) {

	new index = -1;
	foreach(new i : Flat) if(IsPlayerInRangeOfPoint(playerid, range, FlatData[i][flatPos][0],  FlatData[i][flatPos][1],  FlatData[i][flatPos][2]) && GetPlayerVirtualWorld(playerid) == FlatData[i][flatExtWorld] && GetPlayerInterior(playerid) == FlatData[i][flatExtInterior]) {
		index = i;
		break;
	}
	return index;
}

Flat_ShowKeyMenu(playerid, flatid) {

	if(!Iter_Contains(Flat, flatid))
		return 0;

	if(!Flat_IsOwner(playerid, flatid))
		return 0;

	ShowPlayerDialog(playerid, DIALOG_FLAT_KEY, DIALOG_STYLE_LIST, "Flat Key Management", "Share Key\nRevoke Key\nWho have this flat key..", "Select", "Close");
	return 1;
}


function Flat_CheckSharedKey(playerid, flatid) {
	if(!cache_num_rows())
		return ShowPlayerDialog(playerid, DIALOG_NONE, DIALOG_STYLE_MSGBOX, "Flat Shared Key", "Tidak ada player yang memiliki kunci flat ini.", "Close", "");

	new name[MAX_PLAYER_NAME];
	cache_get_value_name(0, "Name", name, MAX_PLAYER_NAME);
	ShowPlayerDialog(playerid, DIALOG_NONE, DIALOG_STYLE_MSGBOX, "Flat Shared Key", sprintf("Player yang memiliki kunci flat ini adalah %s.", name), "Close", "");
	return 1;
}
function Flat_Load() {

	new str[128];

	if(cache_num_rows()) {

		for(new i = 0; i < cache_num_rows(); i++) {

 			Iter_Add(Flat, i);

			cache_get_value_name(i, "OwnerName", FlatData[i][flatOwnerName], MAX_PLAYER_NAME);

			cache_get_value_name_int(i, "ID", FlatData[i][flatID]);
			cache_get_value_name_int(i, "Owner", FlatData[i][flatOwner]);
			cache_get_value_name_int(i, "Type", FlatData[i][flatType]);
			cache_get_value_name_int(i, "Locked", FlatData[i][flatLocked]);
			cache_get_value_name_int(i, "Price", FlatData[i][flatPrice]);
			cache_get_value_name_float(i, "ExtPosX", FlatData[i][flatPos][0]);
			cache_get_value_name_float(i, "ExtPosY", FlatData[i][flatPos][1]);
			cache_get_value_name_float(i, "ExtPosZ", FlatData[i][flatPos][2]);
			cache_get_value_name_float(i, "IntPosX", FlatData[i][flatInt][0]);
			cache_get_value_name_float(i, "IntPosY", FlatData[i][flatInt][1]);
			cache_get_value_name_float(i, "IntPosZ", FlatData[i][flatInt][2]);
			cache_get_value_name_int(i, "IntInterior", FlatData[i][flatIntInterior]);
			cache_get_value_name_int(i, "IntWorld", FlatData[i][flatIntWorld]);
			cache_get_value_name_int(i, "ExtInterior", FlatData[i][flatExtInterior]);
			cache_get_value_name_int(i, "ExtWorld", FlatData[i][flatExtWorld]);
			cache_get_value_name_int(i, "LastLogin", FlatData[i][flatLastLogin]);
			cache_get_value_name_int(i, "TaxState", FlatData[i][flatTaxState]);
			cache_get_value_name_int(i, "TaxPaid", FlatData[i][flatTaxPaid]);
			cache_get_value_name_int(i, "TaxDate", FlatData[i][flatTaxDate]);
			cache_get_value_name_int(i, "FurnitureLevel", FlatData[i][flatFurnitureLevel]);
			cache_get_value_name_int(i, "Sealed", FlatData[i][flatSealed]);

	        for (new j = 0; j < 5; j ++)
			{
	            format(str, 24, "Weapon%d", j + 1);
	            cache_get_value_name_int(i,str,FlatData[i][flatWeapons][j]);

	            format(str, 24, "Ammo%d", j + 1);
	            cache_get_value_name_int(i,str,FlatData[i][flatAmmo][j]);
	            
	            format(str, 24, "Durability%d", j + 1);
	            cache_get_value_name_int(i,str,FlatData[i][flatDurability][j]);

	            format(str, 24, "HighVelocity%d", j + 1);
	            cache_get_value_name_int(i,str,FlatData[i][flatHighVelocity][j]);
			}

			Flat_Sync(i);

			// mysql_format(sqlcon, str, sizeof(str), "SELECT * FROM `furniture` WHERE `ID` = '%d'", FlatData[i][flatID]);
			// mysql_tquery(sqlcon, str, "OnLoadFurniture", "dd", FlatData[i][flatID], FURNITURE_TYPE_FLAT);//a
		}
	}
	printf("[FLAT] Loaded %d Flat from database.", cache_num_rows());

	foreach(new i : Flat)
	{
		mysql_format(sqlcon, str, sizeof(str), "SELECT * FROM `flatstorage` WHERE `ID` = '%d'", FlatData[i][flatID]);
		mysql_tquery(sqlcon, str, "OnFlatLoadStorage", "d", i);
	}
	return 1;
}

function OnFlatLoadStorage(flatid)
{
	static
		str[32];

	new rows = cache_num_rows();
 	if(rows)
  	{
		for(new i; i < rows; i++)
		{
		    FlatStorage[flatid][i][fItemExists] = true;
		    
		    cache_get_value_name_int(i, "itemID", FlatStorage[flatid][i][fItemID]);
		    cache_get_value_name_int(i, "itemModel", FlatStorage[flatid][i][fItemModel]);
		    cache_get_value_name_int(i, "itemQuantity", FlatStorage[flatid][i][fItemQuantity]);
		    cache_get_value_name(i, "itemName", str);
			strpack(FlatStorage[flatid][i][fItemName], str, 32 char);
		}
	}
	return 1;
}

Flat_Inside(playerid) {
	new flatid = PlayerData[playerid][pInFlat];

	if(!Iter_Contains(Flat, flatid))
		return -1;

	return flatid;
}

Flat_IsHaveAccess(playerid, flat_id) {

	new bool:access = false;

	if(!Iter_Contains(Flat, flat_id))
		return false;

	if(Flat_IsOwner(playerid, flat_id))
		return true;

	else {


		new Cache:result = mysql_query(sqlcon, sprintf("SELECT * FROM `flatkeys` WHERE `PlayerID` = %d AND `FlatID` = %d ORDER BY `ID` ASC LIMIT  1;", PlayerData[playerid][pID], FlatData[flat_id][flatID]));
	
		if(!cache_num_rows()) 
			access = false;

		else
			access = true;

		cache_delete(result);
	
	}
	return access;
}
Flat_Delete(index, bool:safe_remove = false) {

	if(!Iter_Contains(Flat, index))
		return 0;

	mysql_tquery(sqlcon, sprintf("DELETE FROM `flat` WHERE `ID` = %d", FlatData[index][flatID]));
	mysql_tquery(sqlcon, sprintf("DELETE FROM `flatkeys` WHERE `FlatID` = %d", FlatData[index][flatID]));
	
	new string[156];
	foreach(new i : Furniture) if(FurnitureData[i][furnitureProperty] == FlatData[index][flatID] && FurnitureData[i][furniturePropertyType] == FURNITURE_TYPE_FLAT)
	{
		mysql_format(sqlcon, string, sizeof(string), "DELETE FROM `furniture` WHERE `furnitureID` = '%d'", FurnitureData[i][furnitureID]);
		mysql_tquery(sqlcon, string);

		FurnitureData[i][furnitureExists] = false;
		FurnitureData[i][furnitureModel] = 0;
		FurnitureData[i][furniturePropertyType] = -1;
		FurnitureData[i][furnitureProperty] = -1;
		
		if(IsValidDynamicObject(FurnitureData[i][furnitureObject]))
			DestroyDynamicObject(FurnitureData[i][furnitureObject]);

		new next = i;
		Iter_SafeRemove(Furniture, next, i);
	}


	for(new i = 0; i < MAX_FLAT_STORAGE; i++) if(FlatStorage[index][i][fItemExists]) {
		FlatStorage[index][i][fItemExists] = false;
		FlatStorage[index][i][fItemModel] = 0;
		FlatStorage[index][i][fItemQuantity] = 0;

		mysql_format(sqlcon, string, sizeof(string), "DELETE FROM `flatstorage` WHERE `ID` = '%d' AND `itemID` = '%d'", FlatData[index][flatID], FlatStorage[index][i][fItemID]);
		mysql_tquery(sqlcon, string);
	}

	if(IsValidDynamic3DTextLabel(FlatData[index][flatLabel]))
		DestroyDynamic3DTextLabel(FlatData[index][flatLabel]);

	if(IsValidDynamicPickup(FlatData[index][flatPickup]))
		DestroyDynamicPickup(FlatData[index][flatPickup]);

	FlatData[index][flatType] = FLAT_TYPE_LOW;
	FlatData[index][flatPrice] = 0;
	FlatData[index][flatLocked] = 0;
	FlatData[index][flatExtWorld] = 0;
	FlatData[index][flatExtInterior] = 0;
	FlatData[index][flatMoney] = 0;
	FlatData[index][flatOwner] = -1;

	format(FlatData[index][flatOwnerName], MAX_PLAYER_NAME, "_");
	for(new i = 0; i < 5; i++) {
		FlatData[index][flatWeapons][i] = 0;
		FlatData[index][flatAmmo][i] = 0;
		FlatData[index][flatDurability][i] = 0;
		FlatData[index][flatSerial][i] = 0;
	}

	if(safe_remove) {

		new next = index;
		Iter_SafeRemove(Flat, next, index);
	}
	else 
		Iter_Remove(Flat, index);

	return 1;
}
/* Commands */

CMD:createflat(playerid, params[]) {
	if(PlayerData[playerid][pAdmin] < 6)
		return PermissionError(playerid);

	new price[24], type = FLAT_TYPE_LOW;
	if(sscanf(params, "ds[24]", type, price))
		return SendSyntaxMessage(playerid, "/createflat [flat type (1 - 3)] [flat price]");

	if(type < 1 || type > 3)
		return SendErrorMessage(playerid, "You have specified invalid flat type.");

	new real_type = type - 1, index = INVALID_ITERATOR_SLOT,
		Float:x, Float:y, Float:z;

	GetPlayerPos(playerid, x, y, z);

	index = Flat_Create(x, y, z, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), strcash(price), real_type);

	if(index == INVALID_ITERATOR_SLOT)
		return SendErrorMessage(playerid, "This server cannot create more flat.");

	SendServerMessage(playerid, "You have created new Flat ID %d.", index);
	return 1;
}

CMD:editflat(playerid, params[]) {
	if(PlayerData[playerid][pAdmin] < 6)
		return PermissionError(playerid);

	new string[156], type[24], flatid = -1, Float:x, Float:y, Float:z;
	if(sscanf(params, "ds[24]S()[128]", flatid, type, string))
		return SendSyntaxMessage(playerid, "/editflat [flatid]  [delete/location/interior/asell/price/type]");

	if(!Iter_Contains(Flat, flatid))
		return SendErrorMessage(playerid, "Flat ID %d is doesn't exists.", flatid);

	if(!strcmp(type, "delete", true)) {
		Flat_Delete(flatid, false);
		SendServerMessage(playerid, "You have removed Flat ID %d.", flatid);
	}
	else if(!strcmp(type,  "location", true)) {
		
		GetPlayerPos(playerid, x, y, z);

		FlatData[flatid][flatPos][0] = x;
		FlatData[flatid][flatPos][1] = y;
		FlatData[flatid][flatPos][2] = z;

		FlatData[flatid][flatExtInterior] = GetPlayerInterior(playerid);
		FlatData[flatid][flatExtWorld] = GetPlayerVirtualWorld(playerid);

		Flat_Sync(flatid);
		Flat_Save(flatid);

		SendServerMessage(playerid, "You have adjusted location of Flat ID %d.", flatid);
	}
	else if(!strcmp(type, "interior", true)) {

		GetPlayerPos(playerid, x, y, z);

		FlatData[flatid][flatInt][0] = x;
		FlatData[flatid][flatInt][1] = y;
		FlatData[flatid][flatInt][2] = z;

		FlatData[flatid][flatIntInterior] = GetPlayerInterior(playerid);

		Flat_Sync(flatid);
		Flat_Save(flatid);

		SendServerMessage(playerid, "You have adjusted interior of Flat ID %d.", flatid);
	}
	else if(!strcmp(type, "asell", true)) {

		if(FlatData[flatid][flatOwner] == -1)
			return SendErrorMessage(playerid, "That flat is already selled.");

		FlatData[flatid][flatOwner] = -1;
		FlatData[flatid][flatLocked] = 1;
		FlatData[flatid][flatMoney] = 0;

		format(FlatData[flatid][flatOwnerName], MAX_PLAYER_NAME, "_");
		for(new i = 0; i < 5; i++) {
			FlatData[flatid][flatWeapons][i] = 0;
			FlatData[flatid][flatAmmo][i] = 0;
			FlatData[flatid][flatDurability][i] = 0;
			FlatData[flatid][flatSerial][i] = 0;
		}

		for(new i = 0; i < MAX_FLAT_STORAGE; i++) if(FlatStorage[flatid][i][fItemExists]) {
			FlatStorage[flatid][i][fItemExists] = false;
			FlatStorage[flatid][i][fItemModel] = 0;
			FlatStorage[flatid][i][fItemQuantity] = 0;

			mysql_format(sqlcon, string, sizeof(string), "DELETE FROM `flatstorage` WHERE `ID` = '%d' AND `itemID` = '%d'", FlatData[flatid][flatID], FlatStorage[flatid][i][fItemID]);
			mysql_tquery(sqlcon, string);
		}
		SendServerMessage(playerid, "You have aselled Flat ID %d.", flatid);

		Flat_Save(flatid);
		Flat_Sync(flatid);
	}
	else if(!strcmp(type, "price", true)) {
		if(isnull(string))
			return SendSyntaxMessage(playerid, "/editflat [flatid] [flat price]");

		new valid_price = strcash(string);
		FlatData[flatid][flatPrice] = valid_price;
		Flat_Save(flatid);
		Flat_Sync(flatid);

		SendServerMessage(playerid, "You have adjusted Flat ID %d price to $%s.", flatid, FormatNumber(valid_price));

	}
	else if(!strcmp(type, "type", true)) {
		if(isnull(string))
			return SendSyntaxMessage(playerid, "/editflat [flatid] [flat type (1 - 3)]");

		if(!IsNumeric(string))
			return SendSyntaxMessage(playerid, "/editflat [flatid] [flat type (1 - 3)]");

		new valid_type = strval(string) - 1;
		FlatData[flatid][flatType] = valid_type;
		Flat_Save(flatid);
		Flat_Sync(flatid);

		SendServerMessage(playerid, "You have adjusted Flat ID %d type to %s.", flatid, Flat_ReturnType(valid_type));	
	}
	return 1;
}
CMD:flat(playerid, params[]) {

	new index = -1, string[128], type[24];
	if(sscanf(params, "s[24]S()[128]", type, string))
		return SendSyntaxMessage(playerid, "/flat [entity]"), SendClientMessage(playerid, -1, "ENTITIY: buy, lock, menu, give");

	if(!strcmp(type, "buy", true)) {

		if((index = Flat_Exterior(playerid, 3.0)) != -1) {

			if(Flat_GetCount(playerid) > 0 && PlayerData[playerid][pAdmin] < 6)
				return SendErrorMessage(playerid, "Kamu hanya bisa memiliki 1 Flat.");

			if(FlatData[index][flatOwner] != -1)
				return SendErrorMessage(playerid, "Flat ini sudah dimiliki oleh orang lain.");

			if(GetMoney(playerid) < FlatData[index][flatPrice])
				return SendErrorMessage(playerid, "Kamu tidak memiliki cukup uang untuk membeli flat ini.");

			GiveMoney(playerid, -FlatData[index][flatPrice], "Membeli Flat");
			SendServerMessage(playerid, "Kamu berhasil membeli Flat dengan type %s seharga "GREEN"$%s", Flat_ReturnType(FlatData[index][flatType]), FormatNumber(FlatData[index][flatPrice]));
			LogProperty_DCChannel(Str_Format("[%s]\nPROPERTY: %s (%s) has purchased flat (ID: %d), price: $%s, type: %s", ReturnDate(), GetName(playerid), GetUsername(playerid), FormatNumber(FlatData[index][flatPrice]), Flat_ReturnType(FlatData[index][flatType])));
			SendServerMessage(playerid, "Jangan lupa untuk membayar pajak Flat setiap 14 hari!");
			
			FlatData[index][flatOwner] = PlayerData[playerid][pID];
			format(FlatData[index][flatOwnerName], MAX_PLAYER_NAME, GetName(playerid));

			FlatData[index][flatTaxDate] = gettime() + (14 * 86400);
			FlatData[index][flatTaxState] = TAX_STATE_COOLDOWN;
			FlatData[index][flatTaxPaid] = true;

			Flat_Sync(index);
			Flat_Save(index);

			notification.Show(playerid, "Property Info", "Property (Flat) purchased successfully!", "hud:radar_propertyG");
		}
		else SendErrorMessage(playerid, "Kamu tidak berada didekat flat yang dijual.");
	}
	else if(!strcmp(type, "give", true)) {

		if((index = Flat_Exterior(playerid, 3.0)) != -1) {

			if(!Flat_IsOwner(playerid, index))
				return SendErrorMessage(playerid, "Ini bukan flat milikmu!");

			new targetid;

			if(sscanf(string, "u", targetid))
				return SendSyntaxMessage(playerid, "/flat [give] [playerid/PartOfName]");

			if(!IsPlayerNearPlayer(playerid, targetid, 5.0) || !IsPlayerConnected(targetid))
				return SendErrorMessage(playerid, "You have specified invalid player!");

			if(Flat_GetCount(targetid) >= 1)
				return SendErrorMessage(playerid, "Player tersebut hanya bisa memiliki 1 flat.");
				
			PlayerData[targetid][pFlatOffer] = index;
			PlayerData[targetid][pFlatOfferID] = playerid;
			SendServerMessage(targetid, "%s telah menawarkan kunci flat miliknya, \"/accept flat\" untuk menerima.", ReturnName(playerid));
			LogProperty_DCChannel(Str_Format("[%s]\nPROPERTY: %s (%s) has trying offer flat (ID: %d), to: %s (%s)", ReturnDate(), GetName(playerid), GetUsername(playerid), index, GetName(targetid), GetUsername(targetid)));
			SendServerMessage(playerid, "Kamu telah menawarkan kunci flat kepada %s.", ReturnName(targetid));
		}
		else SendErrorMessage(playerid, "Kamu harus didekat point flat-mu!");
	}
	else if(!strcmp(type, "lock", true)) {

		if((index = Flat_Exterior(playerid, 3.0)) != -1 && Flat_IsHaveAccess(playerid, index)) {

			FlatData[index][flatLocked] = !(FlatData[index][flatLocked]);
			ShowMessage(playerid, sprintf("(%d) You have %s ~w~the flat.", index, (FlatData[index][flatLocked]) ? ("~r~locked") : ("~g~unlocked")), 2);
			Flat_Save(index);
		}
		else if((index = Flat_Inside(playerid)) != -1 && Flat_IsHaveAccess(playerid, index)) {

			FlatData[index][flatLocked] = !(FlatData[index][flatLocked]);
			ShowMessage(playerid, sprintf("(%d) You have %s ~w~the flat.", index, (FlatData[index][flatLocked]) ? ("~r~locked") : ("~g~unlocked")), 2);
			Flat_Save(index);
		}
	}
	else if(!strcmp(type, "menu", true)) {

		if((index = Flat_Inside(playerid)) != -1 && Flat_IsHaveAccess(playerid, index)) {

			ShowPlayerDialog(playerid, DIALOG_FLAT_MENU, DIALOG_STYLE_LIST, "Flat Menu", "Key Management\nAccess Storage\nManage Furniture\nTax Details", "Select", "Close");
		}
		else SendErrorMessage(playerid, "Kamu tidak berada didalam flat milikmu.");
	}
	return 1;

}

function OnFlatQueue(playerid) {
	if(cache_num_rows()) {
		for(new i = 0; i < cache_num_rows(); i++) {
			new id, msg[128];
			cache_get_value_name_int(i, "FlatID", id);
			cache_get_value_name(i, "Message", msg, 128);

			if(!strcmp(msg, "idk", true)) {
				SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Flat) "WHITE"Flatmu "YELLOW"(ID:%d) "WHITE"secara otomatis dijual oleh server karena tidak login selama 10 hari.", id);
			}
			
			else {
				SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Flat) "WHITE"Flatmu "YELLOW"(ID:%d) "WHITE"secara otomatis dijual oleh server karena tidak membayar pajak.", id);
			}
		}
	}
	mysql_tquery(sqlcon, sprintf("DELETE FROM `flat_queue` WHERE `Username` = '%s'", GetName(playerid)));

	return 1;
}
task OnFlatAsellCheck[3600000]() {
	foreach(new i : Flat) if(FlatData[i][flatLastLogin] != 0) {
		if(FlatData[i][flatLastLogin] < gettime()) {
			SendAdminMessage(X11_TOMATO, "FlatWarn: Flat ID %d has been automatically aselled by the system.", i);

			mysql_tquery(sqlcon, sprintf("INSERT INTO `flat_queue` (`Username`, `FlatID`) VALUES('%s','%d')", FlatData[i][flatOwnerName], i));
			FlatData[i][flatLastLogin] = 0;

			for(new j = 0; j < MAX_FLAT_STORAGE; j++) if(FlatStorage[i][j][fItemExists]) {
				FlatStorage[i][j][fItemExists] = false;
				FlatStorage[i][j][fItemModel] = 0;
				FlatStorage[i][j][fItemQuantity] = 0;

				new string[156];
				mysql_format(sqlcon, string, sizeof(string), "DELETE FROM `flatstorage` WHERE `ID` = '%d' AND `itemID` = '%d'", FlatData[i][flatID], FlatStorage[i][j][fItemID]);
				mysql_tquery(sqlcon, string);
			}

			FlatData[i][flatOwner] = -1;
			format(FlatData[i][flatOwnerName], MAX_PLAYER_NAME, "No Owner");

			Flat_Save(i);
			Flat_Sync(i);
		}
	}
	return 1;
}

function FlatKeyShare(playerid) {
	if(cache_num_rows()) {
		
		SendErrorMessage(playerid, "Kunci pada Flat tidak bisa diberikan lebih dari 1 orang.");
	}
	else {
		ShowPlayerDialog(playerid, DIALOG_FLAT_KEY_SHARE, DIALOG_STYLE_INPUT, "Flat Share Key", "Masukkan ID/Nama player yang akan diberikan kunci Flat.", "Share", "Close");
	}
	return 1;
}

function FlatKeyRemove(playerid) {
	if(cache_num_rows()) {

		new count = 0, string[512];
		for(new i = 0; i < cache_num_rows(); i++) {
			new sqlid, name[24];
			cache_get_value_name(i, "Name", name, 24);
			cache_get_value_name_int(i, "PlayerID", sqlid);
			g_ListedTenant[playerid][count++] = sqlid;

			strcat(string, sprintf("%d) Name: %s\n", i + 1, name));

		}

		if(count)
			ShowPlayerDialog(playerid, DIALOG_FLAT_TENANT_REMOVE, DIALOG_STYLE_LIST, "Remove Tenant", string, "Remove", "Close");
	}
	else {
		SendServerMessage(playerid, "Tidak ada tenant pada flat ini.");
	}
	return 1;
}