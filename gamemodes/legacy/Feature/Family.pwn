enum Familys
{
	familyID,
	bool:familyExists,
	familyName[50],
	familyLeader[MAX_PLAYER_NAME],
	familyRanks,
	familyMOTD[100],
	familyColor,
	Float:familyLockerPos[3],
	familyLockerInt,
	familyLockerVW,
	familyWeapons[10],
	familyAmmo[10],
	familyDurability[10],
	Text3D:familyText3D,
	STREAMER_TAG_PICKUP:familyPickup,
};

new FamilyData[MAX_FAMILY][Familys],
	Iterator:Family<MAX_FAMILY>;

enum familyStorage
{
	fItemID,
	fItemExists,
	fItemName[32 char],
	fItemModel,
	fItemQuantity
};

new FamilyStorage[MAX_FAMILY][MAX_FAMILY_STORAGE][familyStorage];

enum famInt
{
    intName[32],
    intID,
    Float:intX,
    Float:intY,
    Float:intZ,
    Float:intA
}

new const famInteriorArray[][famInt] =
{
	{"Int Gang 1", 	1, -577.2970, 127.0044, 1501.0859, 0.0000},
	{"Int Gang 2", 	2, 1408.7548, -1646.7239, 1259.8119, 0.0000}
};

function Family_Load()
{
	new
	    rows = cache_num_rows(),
		str[56];

	if(rows)
	{
		forex(i, rows)
		{
			FamilyData[i][familyExists] = true;
			cache_get_value_name_int(i, "familyID", FamilyData[i][familyID]);
			cache_get_value_name(i, "familyName", FamilyData[i][familyName], 32);
			cache_get_value_name(i, "familyLeader", FamilyData[i][familyLeader], 32);
			cache_get_value_name(i, "familyMOTD", FamilyData[i][familyMOTD], 32);
			cache_get_value_name_int(i, "familyColor", FamilyData[i][familyColor]);
			cache_get_value_name_float(i, "familyLockerX", FamilyData[i][familyLockerPos][0]);
			cache_get_value_name_float(i, "familyLockerY", FamilyData[i][familyLockerPos][1]);
			cache_get_value_name_float(i, "familyLockerZ", FamilyData[i][familyLockerPos][2]);
			cache_get_value_name_int(i, "familyLockerInt", FamilyData[i][familyLockerInt]);
			cache_get_value_name_int(i, "familyLockerVW", FamilyData[i][familyLockerVW]);
			for (new j = 0; j < 10; j ++)
			{
	            format(str, 24, "familyWeapon%d", j + 1);
	            cache_get_value_name_int(i,str,FamilyData[i][familyWeapons][j]);

	            format(str, 24, "familyAmmo%d", j + 1);
	            cache_get_value_name_int(i,str,FamilyData[i][familyAmmo][j]);
	            
	            format(str, 24, "familyDurability%d", j + 1);
	            cache_get_value_name_int(i,str,FamilyData[i][familyDurability][j]);
			}
			Iter_Add(Family, i);
			Family_Refresh(i);
		}
		printf("[FAMILY] Loaded %d Family from database", rows);
	}
	foreach(new i : Family)
	{
		mysql_format(sqlcon, str, sizeof(str), "SELECT * FROM `familystorage` WHERE `ID` = '%d'", FamilyData[i][familyID]);
		mysql_tquery(sqlcon, str, "OnLoadStorageFamily", "d", i);
	}
	return 1;
}

stock Family_Refresh(familyid)
{
	if (familyid != -1 && FamilyData[familyid][familyExists])
	{
		if(FamilyData[familyid][familyLockerPos][0] != 0 && FamilyData[familyid][familyLockerPos][1] != 0 && FamilyData[familyid][familyLockerPos][2] != 0)
		{
			if (IsValidDynamicPickup(FamilyData[familyid][familyPickup]))
			    DestroyDynamicPickup(FamilyData[familyid][familyPickup]);

			if (IsValidDynamic3DTextLabel(FamilyData[familyid][familyText3D]))
		    	DestroyDynamic3DTextLabel(FamilyData[familyid][familyText3D]);

			new str[156];
			format(str, sizeof(str), "[Family ID: %d]\n{FFFFFF}Type {FF0000}/family locker {FFFFFF}to access the locker.", familyid);

			FamilyData[familyid][familyPickup] = CreateDynamicPickup(1239, 23, FamilyData[familyid][familyLockerPos][0], FamilyData[familyid][familyLockerPos][1], FamilyData[familyid][familyLockerPos][2], FamilyData[familyid][familyLockerVW], FamilyData[familyid][familyLockerInt]);
			FamilyData[familyid][familyText3D] = CreateDynamic3DTextLabel(str, 0x007FFFFF, FamilyData[familyid][familyLockerPos][0], FamilyData[familyid][familyLockerPos][1], FamilyData[familyid][familyLockerPos][2], 15.0);
		}
	}
	return 1;
}

stock Family_Save(familyid)
{
	new
	    query[1536];

	mysql_format(sqlcon, query, sizeof(query), "UPDATE `familys` SET `familyName` = '%s', `familyLeader` = '%s', `familyMOTD` = '%s', `familyColor` = '%d', `familyLockerX` = '%.4f', `familyLockerY` = '%.4f', `familyLockerZ` = '%.4f', `familyLockerInt` = '%d', `familyLockerVW` = '%d'",
	    FamilyData[familyid][familyName],
	    FamilyData[familyid][familyLeader],
	    FamilyData[familyid][familyMOTD],
	    FamilyData[familyid][familyColor],
	    FamilyData[familyid][familyLockerPos][0],
	    FamilyData[familyid][familyLockerPos][1],
	    FamilyData[familyid][familyLockerPos][2],
	    FamilyData[familyid][familyLockerInt],
	    FamilyData[familyid][familyLockerVW]
	);
	for (new i = 0; i < 10; i ++)
	{
		mysql_format(sqlcon,query, sizeof(query), "%s, `familyWeapon%d` = '%d', `familyAmmo%d` = '%d', `familyDurability%d` = '%d'", query, i + 1, FamilyData[familyid][familyWeapons][i], i + 1, FamilyData[familyid][familyAmmo][i], i + 1, FamilyData[familyid][familyDurability][i]);
	}
	mysql_format(sqlcon,query, sizeof(query), "%s WHERE `familyID` = '%d'",
	    query,
        FamilyData[familyid][familyID]
	);
	return mysql_tquery(sqlcon, query);
}

stock Family_Delete(familyid)
{
	if (Iter_Contains(Family, familyid))
	{
	    new
	        string[128];

		foreach(new ii : Player)
		{
			if(PlayerData[ii][pFamily] == FamilyData[familyid][familyID])
			{
				PlayerData[ii][pFamily]= -1;
				PlayerData[ii][pFamilyRank] = 0;
			}
		}

		mysql_format(sqlcon,string, sizeof(string), "DELETE FROM `familys` WHERE `familyID` = '%d'", FamilyData[familyid][familyID]);
		mysql_tquery(sqlcon, string);

		mysql_format(sqlcon,string, sizeof(string), "UPDATE `characters` SET `Family` = '-1', `FamilyRank` = '0' WHERE `Family` = '%d'", FamilyData[familyid][familyID]);
		mysql_tquery(sqlcon, string);

        if (IsValidDynamic3DTextLabel(FamilyData[familyid][familyText3D]))
		    DestroyDynamic3DTextLabel(FamilyData[familyid][familyText3D]);

		if (IsValidDynamicPickup(FamilyData[familyid][familyPickup]))
		    DestroyDynamicPickup(FamilyData[familyid][familyPickup]);

	    FamilyData[familyid][familyExists] = false;
	    FamilyData[familyid][familyID] = 0;
	    Iter_SafeRemove(House, familyid, familyid);
	}
	return 1;
}

stock Family_Create(fname[], otherid)
{
	static
				string[256];
	forex(i, MAX_FAMILY) if (!FamilyData[i][familyExists])
	{
		PlayerData[otherid][pFamily] = FamilyData[i][familyID];
		PlayerData[otherid][pFamilyRank] = 6;

	    format(FamilyData[i][familyName], 32, fname);
		format(FamilyData[i][familyLeader], MAX_PLAYER_NAME, PlayerData[otherid][pName]);
		format(FamilyData[i][familyMOTD], 32, "");

        FamilyData[i][familyExists] = true;
        FamilyData[i][familyColor] = 0xFFFFFF00;

        FamilyData[i][familyLockerPos][0] = 0.0;
        FamilyData[i][familyLockerPos][1] = 0.0;
        FamilyData[i][familyLockerPos][2] = 0.0;
        FamilyData[i][familyLockerInt] = 0;
        FamilyData[i][familyLockerVW] = 0;

        for (new j = 0; j < 10; j ++) {
            FamilyData[i][familyWeapons][j] = 0;
            FamilyData[i][familyAmmo][j] = 0;
            FamilyData[i][familyDurability][j] = 0;
	    }
		mysql_format(sqlcon, string, sizeof(string), "INSERT INTO `familys` (`familyName`, `familyLeader`) VALUES('%s', '%s')", fname, PlayerData[otherid][pName]);
		mysql_tquery(sqlcon, string, "OnFamilyCreated", "d", i);
	    return i;
	}
	return -1;
}

function OnFamilyCreated(familyid)
{
	if (familyid == -1 || !FamilyData[familyid][familyExists])
	    return 0;

	FamilyData[familyid][familyID] = cache_insert_id();

	Family_Save(familyid);
	Family_Refresh(familyid);
	return 1;
}

stock Family_GetName(playerid)
{
    new
		familyid = PlayerData[playerid][pFamily],
		name[32] = "None";

 	if (familyid == -1)
	    return name;

	format(name, 32, FamilyData[familyid][familyName]);
	return name;
}

stock Family_GetRank(playerid)
{
    new
		familyid = PlayerData[playerid][pFamilyRank],
		rank[32];

 	if (familyid == 0)
	{
		rank = "None";
	}
	else if (familyid == 1)
	{
		rank = "Outsider[1]";
	}
	else if (familyid == 2)
	{
		rank = "Associate[2]";
	}
	else if (familyid == 3)
	{
		rank = "Soldier[3]";
	}
	else if (familyid == 4)
	{
		rank = "Advisor[4]";
	}
	else if (familyid == 5)
	{
		rank = "UnderBoss[5]";
	}
	else if (familyid == 6)
	{
		rank = "GodFather[6]";
	}
	
	return rank;
}

stock FamilyLocker_Inside(playerid)
{
	if (PlayerData[playerid][pFamily] != -1)
	{
	    foreach(new i : Family) if (FamilyData[i][familyID] == PlayerData[playerid][pFamily] && GetPlayerInterior(playerid) == FamilyData[i][familyLockerInt] && GetPlayerVirtualWorld(playerid) == FamilyData[i][familyLockerVW]) {
	        return i;
		}
	}
	return -1;
}

stock IsNearFamilyLocker(playerid)
{
	new familyid = PlayerData[playerid][pFamily];

	if (familyid == -1)
	    return 0;

	if (IsPlayerInRangeOfPoint(playerid, 3.0, FamilyData[familyid][familyLockerPos][0], FamilyData[familyid][familyLockerPos][1], FamilyData[familyid][familyLockerPos][2]) && GetPlayerInterior(playerid) == FamilyData[familyid][familyLockerInt] && GetPlayerVirtualWorld(playerid) == FamilyData[familyid][familyLockerVW])
	    return 1;

	return 0;
}

function OnLoadStorageFamily(familyid)
{
	static
		str[32];

	new rows = cache_num_rows();
 	if(rows)
  	{
		for(new i; i < rows; i++)
		{
		    FamilyStorage[familyid][i][fItemExists] = true;
		    
		    cache_get_value_name_int(i, "itemID", FamilyStorage[familyid][i][fItemID]);
		    cache_get_value_name_int(i, "itemModel", FamilyStorage[familyid][i][fItemModel]);
		    cache_get_value_name_int(i, "itemQuantity", FamilyStorage[familyid][i][fItemQuantity]);
		    cache_get_value_name(i, "itemName", str);
			strpack(FamilyStorage[familyid][i][fItemName], str, 32 char);
		}
	}
	return 1;
}

stock Family_WeaponStorage(playerid, familyid)
{
	static
		header[712], string[712];

	string[0] = 0;

	for (new i = 0; i < 10; i ++)
	{
	    if (!FamilyData[familyid][familyWeapons][i])
		{
			format(header, sizeof(header), "Weapon\t{FFFF00}Ammo\t{00FFFF}Durability{FFFFFF}\n", header);
	        format(string, sizeof(string), "%sEmpty Slot\t-\t-\n", string);

			strcat(header, string);
		}
		else
		{
			format(header, sizeof(header), "Weapon\t{FFFF00}Ammo\t{00FFFF}Durability{FFFFFF}\n", header);
			format(string, sizeof(string), "%s%s\t{FFFF00}%d\t{00FFFF}%d{FFFFFF}\n", string, ReturnWeaponName(FamilyData[familyid][familyWeapons][i]), FamilyData[familyid][familyAmmo][i], FamilyData[familyid][familyDurability][i]);
		
			strcat(header, string);
		}
	}
	ShowPlayerDialog(playerid, DIALOG_FAMILY_WEAPON, DIALOG_STYLE_TABLIST_HEADERS, "Weapon Storage", header, "Select", "Cancel");
	return 1;
}

stock Family_OpenStorage(playerid, familyid)
{
	new
		items[2],
		string[MAX_FAMILY_STORAGE * 32];

	for (new i = 0; i < MAX_FAMILY_STORAGE; i ++) if (FamilyStorage[familyid][i][fItemExists])
	{
	    items[0]++;
	}
	for (new i = 0; i < 10; i ++) if (FamilyData[familyid][familyWeapons][i])
	{
	    items[1]++;
	}
 	format(string, sizeof(string), "Item Storage (%d/%d)\nWeapon Storage (%d/10)", items[0], MAX_FAMILY_STORAGE, items[1]);
	ShowPlayerDialog(playerid, DIALOG_FAMILY_STORAGE, DIALOG_STYLE_LIST, "Family Storage", string, "Select", "Cancel");
	return 1;
}


stock Family_ShowItems(playerid, familyid)
{
    if (familyid == -1 || !FamilyData[familyid][familyExists])
	    return 0;

	static
	    string[MAX_FAMILY_STORAGE * 32],
		name[32];

	string[0] = 0;

	for (new i = 0; i != MAX_FAMILY_STORAGE; i ++)
	{
	    if (!FamilyStorage[familyid][i][fItemExists])
	        format(string, sizeof(string), "%sEmpty Slot\n", string);

		else
		{
			strunpack(name, FamilyStorage[familyid][i][fItemName]);

			if (FamilyStorage[familyid][i][fItemQuantity] == 1)
			{
			    format(string, sizeof(string), "%s%s\n", string, name);
			}
			else format(string, sizeof(string), "%s%s (%d)\n", string, name, FamilyStorage[familyid][i][fItemQuantity]);
		}
	}
	ShowPlayerDialog(playerid, DIALOG_FAMILY_ITEM, DIALOG_STYLE_LIST, "Item Storage", string, "Select", "Cancel");
	return 1;
}

stock Family_GetItemID(familyid, item[])
{
	if (familyid == -1 || !FamilyData[familyid][familyExists])
	    return 0;

	for (new i = 0; i < MAX_FAMILY_STORAGE; i ++)
	{
	    if (!FamilyStorage[familyid][i][fItemExists])
	        continue;

		if (!strcmp(FamilyStorage[familyid][i][fItemName], item)) return i;
	}
	return -1;
}

stock Family_GetFreeID(familyid)
{
	if (familyid == -1 || !FamilyData[familyid][familyExists])
	    return 0;

	for (new i = 0; i < MAX_FAMILY_STORAGE; i ++)
	{
	    if (!FamilyStorage[familyid][i][fItemExists])
	        return i;
	}
	return -1;
}

stock Family_AddItem(familyid, item[], model, quantity = 1, slotid = -1)
{
    if (familyid == -1 || !FamilyData[familyid][familyExists])
	    return 0;

	new
		itemid = Family_GetItemID(familyid, item),
		string[128];

	if (itemid == -1)
	{
	    itemid = Family_GetFreeID(familyid);

	    if (itemid != -1)
	    {
	        if (slotid != -1)
	            itemid = slotid;

	        FamilyStorage[familyid][itemid][fItemExists] = true;
	        FamilyStorage[familyid][itemid][fItemModel] = model;
	        FamilyStorage[familyid][itemid][fItemQuantity] = quantity;

	        strpack(FamilyStorage[familyid][itemid][fItemName], item, 32 char);

			mysql_format(sqlcon, string, sizeof(string), "INSERT INTO `familystorage` (`ID`, `itemName`, `itemModel`, `itemQuantity`) VALUES('%d', '%s', '%d', '%d')", FamilyData[familyid][familyID], item, model, quantity);
			mysql_tquery(sqlcon, string, "OnStorageFamilyAdd", "dd", familyid, itemid);

	        return itemid;
		}
		return -1;
	}
	else
	{
	    mysql_format(sqlcon, string, sizeof(string), "UPDATE `familystorage` SET `itemQuantity` = `itemQuantity` + %d WHERE `ID` = '%d' AND `itemID` = '%d'", quantity, FamilyData[familyid][familyID], FamilyStorage[familyid][itemid][fItemID]);
	    mysql_tquery(sqlcon, string);

	    FamilyStorage[familyid][itemid][fItemQuantity] += quantity;
	}
	return itemid;
}

function OnStorageFamilyAdd(familyid, itemid)
{
	FamilyStorage[familyid][itemid][fItemID] = cache_insert_id();
	return 1;
}

stock Family_RemoveItem(familyid, item[], quantity = 1)
{
    if (familyid == -1 || !FamilyData[familyid][familyExists])
	    return 0;

	new
		itemid = Family_GetItemID(familyid, item),
		string[128];

	if (itemid != -1)
	{
	    if (FamilyStorage[familyid][itemid][fItemQuantity] > 0)
	    {
	        FamilyStorage[familyid][itemid][fItemQuantity] -= quantity;
		}
		if (quantity == -1 || FamilyStorage[familyid][itemid][fItemQuantity] < 1)
		{
		    FamilyStorage[familyid][itemid][fItemExists] = false;
		    FamilyStorage[familyid][itemid][fItemModel] = 0;
		    FamilyStorage[familyid][itemid][fItemQuantity] = 0;

		    mysql_format(sqlcon, string, sizeof(string), "DELETE FROM `familystorage` WHERE `ID` = '%d' AND `itemID` = '%d'", FamilyData[familyid][familyID], FamilyStorage[familyid][itemid][fItemID]);
	        mysql_tquery(sqlcon, string);
		}
		else if (quantity != -1 && FamilyStorage[familyid][itemid][fItemQuantity] > 0)
		{
			mysql_format(sqlcon, string, sizeof(string), "UPDATE `familystorage` SET `itemQuantity` = `itemQuantity` - %d WHERE `ID` = '%d' AND `itemID` = '%d'", quantity, FamilyData[familyid][familyID], FamilyStorage[familyid][itemid][fItemID]);
            mysql_tquery(sqlcon, string);
		}
		return 1;
	}
	return 0;
}

CMD:famint(playerid, params[])
{
	static list[4096];

    if(PlayerData[playerid][pAdmin] < 4)
		return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if(isnull(list))
	{
	    for(new i = 0; i < sizeof(famInteriorArray); i ++)
	    {
	        format(list, sizeof(list), "%s\n%s", list, famInteriorArray[i][intName]);
		}
	}

	ShowPlayerDialog(playerid, DIALOG_FAMILY_INTERIOR, DIALOG_STYLE_LIST, "Goto Interior Family", list, "Select", "Cancel");
	return 1;
}

CMD:fcreate(playerid, params[])
{
	static 
		id = -1,
		otherid,
		name[50];

	if (PlayerData[playerid][pAdmin] < 5)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");
	
	if(sscanf(params, "s[50]u", name, otherid)) 
		return SendSyntaxMessage(playerid, "/fcreate [name] [playerid]");
	
	if(otherid == INVALID_PLAYER_ID)
		return SendErrorMessage(playerid, "Invalid playerid.");
	
	if(PlayerData[otherid][pFamily] != -1)
		return SendErrorMessage(playerid, "Player tersebut sudah bergabung Family lain");
		
	if(PlayerData[otherid][pFaction] != -1)
		return SendErrorMessage(playerid, "Player tersebut sudah bergabung Faction");

	id = Family_Create(name, otherid);

	if (id == -1)
	    return SendErrorMessage(playerid, "You can't add more Family!");

	SendServerMessage(playerid, "You have successfully created Family ID: %d | Name: %s", id, name);
	return 1;
}

CMD:fedit(playerid, params[])
{
	static
	    id,
	    type[24],
	    string[128];

	if (PlayerData[playerid][pAdmin] < 5)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "ds[24]S()[128]", id, type, string))
 	{
	 	SendSyntaxMessage(playerid, "/fedit [id] [name]");
	    SendClientMessage(playerid, COLOR_YELLOW, "(Names){FFFFFF} name, leader, locker");
		return 1;
	}

	if ((id < 0 || id >= MAX_FAMILY) || !FamilyData[id][familyExists])
	    return SendErrorMessage(playerid, "You have specified an invalid Family ID.");

	if (!strcmp(type, "name", true))
	{
	    new name[32];

	    if (sscanf(string, "s[32]", name))
	        return SendSyntaxMessage(playerid, "/fedit [id] [name] [new name]");

	    format(FamilyData[id][familyName], 32, name);

	    Family_Save(id);
		Family_Refresh(id);
		SendAdminMessage(COLOR_LIGHTRED, "AdmCmd: %s has adjusted the name of Family ID: %d to \"%s\".", PlayerData[playerid][pUCP], id, name);
	}
	else if (!strcmp(type, "leader", true))
	{
	    new otherid;

	    if (sscanf(string, "d", otherid))
	        return SendSyntaxMessage(playerid, "/fedit [id] [leader] [playerid]");
		
		if(otherid == INVALID_PLAYER_ID)
			return SendErrorMessage(playerid, "Invalid playerid");

		format(FamilyData[id][familyLeader], 32, PlayerData[otherid][pName]);
		PlayerData[otherid][pFamily] = id;
		PlayerData[otherid][pFamilyRank] = 6;

	    Family_Save(id);
		Family_Refresh(id);
		SendAdminMessage(COLOR_LIGHTRED, "AdmCmd: %s has adjusted the Leader of Family ID: %d to \"%s\".", PlayerData[playerid][pUCP], id, PlayerData[otherid][pName]);
	}
	/*else if (!strcmp(type, "color", true))
	{
	    new color;

	    if (sscanf(string, "h", color))
	        return SendSyntaxMessage(playerid, "/fedit [id] [color] [hex]");

	    FamilyData[id][familyColor] = color;

	    Family_Save(id);
		Family_Refresh(id);
		SendAdminMessage(COLOR_LIGHTRED, "AdmCmd: %s has adjusted the {%06x}color{FF6347} of family ID: %d.", PlayerData[playerid][pUCP], color >>> 8, id);
	}*/
	else if (!strcmp(type, "locker", true))
	{
	    GetPlayerPos(playerid, FamilyData[id][familyLockerPos][0], FamilyData[id][familyLockerPos][1], FamilyData[id][familyLockerPos][2]);
		FamilyData[id][familyLockerVW] = GetPlayerVirtualWorld(playerid);
		FamilyData[id][familyLockerInt] = GetPlayerInterior(playerid);

	    Family_Save(id);
		Family_Refresh(id);
		SendAdminMessage(COLOR_LIGHTRED, "AdmCmd: %s has adjusted the position Locker of Family ID: %d", PlayerData[playerid][pUCP], id);
	}
	return 1;
}

CMD:fdelete(playerid, params[])
{
	static
	    id = 0;

    if (PlayerData[playerid][pAdmin] < 5)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "d", id))
	    return SendSyntaxMessage(playerid, "/fdelete [family id]");

	if ((id < 0 || id >= MAX_FAMILY) || !FamilyData[id][familyExists])
	    return SendErrorMessage(playerid, "You have specified an invalid Family ID.");

	Family_Delete(id);
	SendServerMessage(playerid, "You have successfully deleted Family ID: %d.", id);
	return 1;
}

CMD:family(playerid, params[])
{
	new type[24], string[128];
	if (sscanf(params, "s[24]S()[128]", type, string))
		return SendSyntaxMessage(playerid, "/family [Names]"), SendClientMessage(playerid, COLOR_SERVER, "Names: {FFFFFF}locker, invite, kick, menu, accept, setrank");

	if(!strcmp(type, "locker", true))
	{
		if(PlayerData[playerid][pFamily] == -1)
			return SendErrorMessage(playerid, "You aren't in any family.");

		new familyid = PlayerData[playerid][pFamily];

	 	if (familyid == -1)
		    return SendErrorMessage(playerid, "You must be a family member.");

		if (!IsNearFamilyLocker(playerid))
		    return SendErrorMessage(playerid, "You are not in range of your family's locker.");

		ShowPlayerDialog(playerid, DIALOG_FAMILY_MENU, DIALOG_STYLE_LIST, "Family Menu", "Storage", "Select", "Close");
	}
	else if(!strcmp(type, "invite", true))
	{

		new
		    userid;

		if (PlayerData[playerid][pFamily] == -1)
		    return SendErrorMessage(playerid, "You must be a Family member.");

		if (PlayerData[playerid][pFamilyRank] < 5)
		    return SendErrorMessage(playerid, "You must be at least rank 5.");

		if (sscanf(string, "u", userid))
		    return SendSyntaxMessage(playerid, "/family invite [playerid/PartOfName]");

		if (userid == INVALID_PLAYER_ID || userid == playerid)
		    return SendErrorMessage(playerid, "That player is disconnected.");

		if (PlayerData[userid][pFamily] == PlayerData[playerid][pFamily])
		    return SendErrorMessage(playerid, "That player is already part of your Family.");

	    if (PlayerData[userid][pFamily] != -1)
		    return SendErrorMessage(playerid, "That player is already part of another Family.");

		if(!IsPlayerNearPlayer(playerid, userid, 5.0))
			return SendErrorMessage(playerid, "You must close to that player!");

		PlayerData[userid][pFamilyOffer] = playerid;
	    PlayerData[userid][pFamilyOffered] = PlayerData[playerid][pFamily];

	    SendServerMessage(playerid, "You have requested %s to join \"%s\".", ReturnName(userid), Family_GetName(playerid));
	    SendServerMessage(userid, "%s has offered you to join \"%s\" (type \"/family accept\").", ReturnName(playerid), Family_GetName(playerid));
	}
	else if(!strcmp(type, "accept", true) && PlayerData[playerid][pFamilyOffer] != INVALID_PLAYER_ID)
	{
	    new
	        targetid = PlayerData[playerid][pFamilyOffer],
	        familyid = PlayerData[playerid][pFamilyOffered];

		if (!FamilyData[familyid][familyExists] || PlayerData[targetid][pFamilyRank] < 5)
	   	 	return SendErrorMessage(playerid, "The family offer is no longer available.");

		PlayerData[playerid][pFamily] = familyid;
		PlayerData[playerid][pFamilyRank] = 1;

		SendServerMessage(playerid, "You have accepted %s's offer to join \"%s\".", ReturnName(targetid), Family_GetName(targetid));
		SendServerMessage(targetid, "%s has accepted your offer to join \"%s\".", ReturnName(playerid), Family_GetName(targetid));

        PlayerData[playerid][pFamilyOffer] = INVALID_PLAYER_ID;
        PlayerData[playerid][pFamilyOffered] = -1;
	}
	else if(!strcmp(type, "setrank", true))
	{
    	new
		    userid,
			rankid;

		if (PlayerData[playerid][pFamily] == -1)
		    return SendErrorMessage(playerid, "You must be a family member.");

		if (PlayerData[playerid][pFamilyRank] < 5)
		    return SendErrorMessage(playerid, "You must be at least rank 5.");

		if (sscanf(string, "ud", userid, rankid))
		    return SendSyntaxMessage(playerid, "/family setrank [playerid/PartOfName] [rank (1-5)]");

		if (userid == INVALID_PLAYER_ID || userid == playerid)
		    return SendErrorMessage(playerid, "That player is disconnected.");

		if (PlayerData[userid][pFamily] != PlayerData[playerid][pFamily])
		    return SendErrorMessage(playerid, "That player is not part of your family.");

		if (rankid < 0 || rankid > 5)
		    return SendErrorMessage(playerid, "Invalid rank specified. Ranks range from 1 to 5.");
		
		if(PlayerData[playerid][pFamilyRank] > PlayerData[userid][pFamilyRank])
			return SendErrorMessage(playerid, "You cant set rank him");

		PlayerData[userid][pFamilyRank] = rankid;

	    SendServerMessage(playerid, "You have adjusted %s rank to %s (%d).", ReturnName(userid), Family_GetRank(userid), rankid);
	    SendServerMessage(userid, "%s has adjusted your rank to %s (%d).", ReturnName(playerid), Family_GetRank(userid), rankid);
	}
	else if(!strcmp(type, "kick", true))
	{
		new
		    userid;

		if (PlayerData[playerid][pFamily] == -1)
		    return SendErrorMessage(playerid, "You must be a family member.");

		if (PlayerData[playerid][pFamilyRank] < 5)
		    return SendErrorMessage(playerid, "You must be at least rank 5.");

		if (sscanf(string, "u", userid))
		    return SendSyntaxMessage(playerid, "/family kick [playerid/PartOfName]");

		if (userid == INVALID_PLAYER_ID || userid == playerid)
		    return SendErrorMessage(playerid, "That player is disconnected.");

		if (PlayerData[userid][pFamily] != PlayerData[playerid][pFamily])
		    return SendErrorMessage(playerid, "That player is not part of your family.");

		if(!IsPlayerNearPlayer(playerid, userid, 5.0))
			return SendErrorMessage(playerid, "You must close to that player!");

		if(PlayerData[playerid][pFamilyRank] > PlayerData[userid][pFamilyRank])
			return SendErrorMessage(playerid, "You cant kick him");

		PlayerData[userid][pFamily] = -1;
		PlayerData[userid][pFamilyRank] = 0;
		SendServerMessage(playerid, "You have kicked %s from your family!", ReturnName(userid));
	}
	return 1;
}

CMD:familys(playerid, params[])
{
	new str[512];
	forex(i, MAX_FAMILY) if(FamilyData[i][familyExists])
	{
		format(str, sizeof(str), "%s{FFFFFF}[ID: %d] {%06x}%s\n", str, i, FamilyData[i][familyColor] >>> 8, FamilyData[i][familyName]);
	}
	ShowPlayerDialog(playerid, DIALOG_NONE, DIALOG_STYLE_MSGBOX, "Family List", str, "Close", "");
	return 1;
}