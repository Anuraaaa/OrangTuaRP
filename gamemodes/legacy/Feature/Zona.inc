#include <YSI_Coding\y_hooks>

#define MAX_SAFEZONE 	(50)

new editZone[MAX_PLAYERS] = {-1, ...};

enum e_gzone
{
	gzSafezone,
};
new G_ZoneData[e_gzone];

enum e_zone {
	zoneID,
	Float:zonePos[4],
	zoneType,
	zoneArea,
	zoneName[24]
};
new ZoneData[MAX_SAFEZONE][e_zone];
new Iterator:Zone<MAX_SAFEZONE>;

hook OnGameModeInit()
{
	if (IsSQLConnected()) {
		Iter_Init(Zone);
		G_ZoneData[gzSafezone] = GangZoneCreate(-3000, -3000, 3000, 3000);
		mysql_tquery(sqlcon, "SELECT * FROM `zones`", "Zone_Load", "");
	}
}

hook OnGameModeExit()
{
	if (IsSQLConnected()) {
		GangZoneDestroy(G_ZoneData[gzSafezone]);
		Iter_Clear(Zone);
	}
}

hook OnPlayerConnect(playerid)
{
	editZone[playerid] = -1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	editZone[playerid] = -1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
	foreach (new i : Zone)
	{
		if (areaid == ZoneData[i][zoneArea])
		{
			switch (ZoneData[i][zoneType])
			{
				case 1: GangZoneShowForPlayer(playerid, G_ZoneData[gzSafezone], X11_BLUE);
				case 2: GangZoneShowForPlayer(playerid, G_ZoneData[gzSafezone], X11_GREEN);
				case 3: GangZoneShowForPlayer(playerid, G_ZoneData[gzSafezone], X11_YELLOW);
				case 4:
				{
					GangZoneShowForPlayer(playerid, G_ZoneData[gzSafezone], X11_GREY);
					SendClientMessage(playerid, X11_LIGHTGREY, "[OOC] : Kamu telah memasuki kawasan OOC Zone!");
				}
			}
		}
	}
	return 1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
	foreach (new id : Zone)
	{
		if (areaid == ZoneData[id][zoneArea] && ZoneData[id][zoneType] == 4)
		{
			SendClientMessage(playerid, X11_LIGHTGREY, "[OOC] : Kamu telah keluar dari kawasan OOC Zone!");
		}
	}
	GangZoneHideForPlayer(playerid, G_ZoneData[gzSafezone]);

	return 1;
}

Zone_Create(Float:min_x, Float:min_y, Float:max_x, Float:max_y, type, const name[])
{
	new id = Iter_Free(Zone);

	if (id != INVALID_ITERATOR_SLOT)
	{
		Iter_Add(Zone, id);
		ZoneData[id][zonePos][0] = min_x;
		ZoneData[id][zonePos][1] = min_y;

		ZoneData[id][zonePos][2] = max_x;
		ZoneData[id][zonePos][3] = max_y;

		ZoneData[id][zoneType] = type;
		format(ZoneData[id][zoneName], 24, name);
		
		Zone_Refresh(id);

		mysql_tquery(sqlcon, "INSERT INTO `zones` (`zoneType`) VALUES (0)", "OnZoneCreated", "d", id);

		return id;
	}
	return INVALID_ITERATOR_SLOT;
}

Zone_Refresh(id)
{
	if (Iter_Contains(Zone, id))
	{
		if (!IsValidDynamicArea(ZoneData[id][zoneArea]))
			ZoneData[id][zoneArea] = CreateDynamicSphere(ZoneData[id][zonePos][0], ZoneData[id][zonePos][1], ZoneData[id][zonePos][2], ZoneData[id][zonePos][3]);

		else if (IsValidDynamicArea(ZoneData[id][zoneArea]))
		{
			Streamer_SetFloatData(STREAMER_TYPE_AREA, ZoneData[id][zoneArea], E_STREAMER_X, ZoneData[id][zonePos][0]);
			Streamer_SetFloatData(STREAMER_TYPE_AREA, ZoneData[id][zoneArea], E_STREAMER_Y, ZoneData[id][zonePos][1]);
			Streamer_SetFloatData(STREAMER_TYPE_AREA, ZoneData[id][zoneArea], E_STREAMER_Z, ZoneData[id][zonePos][2]);
			Streamer_SetFloatData(STREAMER_TYPE_AREA, ZoneData[id][zoneArea], E_STREAMER_SIZE, ZoneData[id][zonePos][3]);
		}
		foreach (new i : Player) if (IsPlayerInRangeOfPoint(i, 10.0, ZoneData[id][zonePos][0], ZoneData[id][zonePos][1], ZoneData[id][zonePos][2]))
		{
			Streamer_Update(i, STREAMER_TYPE_AREA);
		}
		return 1;
	}
	return 0;
}

Zone_Delete(id)
{
	if (Iter_Contains(Zone, id))
	{
		mysql_tquery(sqlcon, sprintf("DELETE FROM `zones` WHERE `zoneID` = '%d'", ZoneData[id][zoneID]));

		if (IsValidDynamicArea(ZoneData[id][zoneArea]))
			DestroyDynamicArea(ZoneData[id][zoneArea]);

		GangZoneDestroy(ZoneData[id][zoneArea]);
	}
	return 0;
}

Zone_EditMenu(playerid)
{
	new id = editZone[playerid];

	Dialog_Show(playerid, EditZone, DIALOG_STYLE_TABLIST, "Zone Menu",
		sprintf("Type\t%d\n\
				Zone Position\t%.2f\n\
				Zone Size\t%.1f\n\
				Zone Name\t%s",
				ZoneData[id][zoneType],
				ZoneData[id][zonePos][0],
				ZoneData[id][zonePos][3],
				ZoneData[id][zoneName]
		), "Edit", "Close"
	);
	return 1;
}

Zone_Save(id)
{
	if (!Iter_Contains(Zone, id))
		return 0;

	static
		query[1024];

	mysql_format(sqlcon, query, sizeof(query), "UPDATE `zones` SET `zoneName` = '%e', `zoneMin_X` = '%.1f', `zoneMin_Y` = '%.1f', `zoneMax_X` = '%.1f', `zoneMax_Y` = '%.1f', `zoneType` = '%d' WHERE `zoneID` = '%d'",
		ZoneData[id][zoneName],
		ZoneData[id][zonePos][0],
		ZoneData[id][zonePos][1],
		ZoneData[id][zonePos][2],
		ZoneData[id][zonePos][3],
		ZoneData[id][zoneType],
		ZoneData[id][zoneID]
	);
	return mysql_tquery(sqlcon, query);
}

GetZoneTypeName(id) 
{
	new str[24];
	switch (ZoneData[id][zoneType])
	{
		case 1: str = "Blue Zone";
		case 2: str = "Green Zone";
		case 3: str = "Yellow Zone";
		case 4: str = "OOC Zone";
	}
	return str;
}

function Zone_Load()
{
	if (cache_num_rows())
	{
		forex (i, cache_num_rows())
		{
			new id = Iter_Free(Zone);

			if (id != INVALID_ITERATOR_SLOT)
			{
				Iter_Add(Zone, id);
				cache_get_value_name_int(i, "zoneID", ZoneData[id][zoneID]);
				cache_get_value_name_float(i, "zoneMin_X", ZoneData[id][zonePos][0]);
				cache_get_value_name_float(i, "zoneMin_Y", ZoneData[id][zonePos][1]);
				cache_get_value_name_float(i, "zoneMax_X", ZoneData[id][zonePos][2]);
				cache_get_value_name_float(i, "zoneMax_Y", ZoneData[id][zonePos][3]);
				cache_get_value_name_int(i, "zoneType", ZoneData[id][zoneType]);
				cache_get_value_name(i, "zoneName", ZoneData[id][zoneName]);				

				Zone_Refresh(id);
			}
		}
		printf("[Zona] Loaded server zone area(s): %d.", Iter_Count(Zone));
	}
}

function OnZoneCreated(id)
{
	ZoneData[id][zoneID] = cache_insert_id();
	Zone_Save(id);
}

CMD:zone(playerid, params[])
{
	if (PlayerData[playerid][pAdmin] < 7)
		return PermissionError(playerid);

	static tmp[12], id, name[24];

	if (sscanf(params, "s[12]", tmp))
		return SendSyntaxMessage(playerid, "/zone [create/edit/list/destroy]");

	if (!strcmp(tmp, "create", true, 6))
	{
		if (sscanf(params, "s[12]ds[24]", tmp, id, name))
		{
			SendSyntaxMessage(playerid, "/zone create [type] [zone name]");
			SendClientMessage(playerid, COLOR_YELLOW, "(Type){FFFFFF} [1: Blue Zone | 2: Green Zone | 3: Yellow Zone | 4: OOC Zone]");
			return 1;
		}

		if (id < 1 || id > 4)
			return SendErrorMessage(playerid, "Invalid zone type (1-4)!");

		new Float:x, Float:y, Float:z;
		GetPlayerPos(playerid, x, y, z);

		new idx = Zone_Create(x, y, z, 0, id, name);

		if (idx == INVALID_ITERATOR_SLOT)
			return SendErrorMessage(playerid, "The server has reached the limit of zone area!");

		SendClientMessage(playerid, COLOR_SERVER, "ZONE: "YELLOW"Created zone area on your position!");
	}
	else if (!strcmp(tmp, "edit", true, 4))
	{
		if (sscanf(params, "s[12]d", tmp, id))
			return SendSyntaxMessage(playerid, "/zone edit [zoneid]");

		if (!Iter_Contains(Zone, id))
			return SendErrorMessage(playerid, "Invalid zone ID!");

		if (editZone[playerid] != -1)
			return SendErrorMessage(playerid, "You're already on editing mode!");

		editZone[playerid] = id;
		Zone_EditMenu(playerid);
	}
	else if (!strcmp(tmp, "destroy", true, 7))
	{
		if (sscanf(params, "s[12]d", tmp, id))
			return SendSyntaxMessage(playerid, "/zone destroy [zoneid]");

		if (!Iter_Contains(Zone, id))
			return SendErrorMessage(playerid, "Invalid zone ID!");

		SendClientMessage(playerid, COLOR_SERVER, "ZONE: "YELLOW"Deleted zone area from your position!");
		Zone_Delete(id);

		if (Iter_Contains(Zone, id))
		{
			Iter_Remove(Zone, id);
		}		
	}
	else if (!strcmp(tmp, "list", true, 4))
	{
		new zoneData[512];
		foreach (new i : Zone) 
		{
			format(zoneData, sizeof(zoneData), "%s\n%d\t%s\t%s\t%.1fm", zoneData, ZoneData[i][zoneID], ZoneData[i][zoneName], GetZoneTypeName(i), ZoneData[i][zonePos][3]);
		}
		if (!Iter_Count(Zone))
			return SendErrorMessage(playerid, "Tidak ada zona area yang ditemukan.");

		Dialog_Show(playerid, Null, DIALOG_STYLE_TABLIST_HEADERS, "Zone List", sprintf("Zone ID\tZone Name\tZone Type\tZone Size\n%s", zoneData), "Close", "");
	}
	else SendSyntaxMessage(playerid, "/zone [create/edit/list/destroy]");

	return 1;
}

Dialog:EditZone(playerid, response, listitem, inputtext[])
{
	if (!response)
		return editZone[playerid] = -1;

	new Float:e_pos[3];
	new id = editZone[playerid];

	GetPlayerPos(playerid, e_pos[0], e_pos[1], e_pos[2]);

	switch (listitem)
	{
		case 0:
			Dialog_Show(playerid, EditZoneType, DIALOG_STYLE_LIST, "Edit Zone Type", "Blue Zone\nGreen Zone\nYellow Zone\nOOC Zone", "Change", "Back");

		case 1:	
		{
			ZoneData[id][zonePos][0] = e_pos[0];
			ZoneData[id][zonePos][1] = e_pos[1];
			ZoneData[id][zonePos][2] = e_pos[2];

			Zone_Refresh(id);
			Zone_Save(id);

			Zone_EditMenu(playerid);
		}
		case 2:
			Dialog_Show(playerid, EditZoneSize, DIALOG_STYLE_INPUT, "Edit Zone Size", "Please fill a radius of this zone size below:", "Resize", "Back");

		case 3:
			Dialog_Show(playerid, EditZoneName, DIALOG_STYLE_INPUT, "Edit Zone Name", "Please fill a name of this zone below:", "Rename", "Back");
	}
	Zone_Refresh(id);
	Zone_Save(id);

	return 1;
}

Dialog:EditZoneType(playerid, response, listitem, inputtext[])
{
	if (!response)
		return Zone_EditMenu(playerid);

	new
		id = editZone[playerid];

	ZoneData[id][zoneType] = listitem + 1;

	Zone_Refresh(id);
	Zone_Save(id);

	SendClientMessageEx(playerid, COLOR_SERVER, "Zone: "YELLOW"Type of area has been changed to "CYAN1"%s", inputtext);
	Zone_EditMenu(playerid);

	return 1;
}

Dialog:EditZoneSize(playerid, response, listitem, inputtext[])
{
	if (!response)
		return Zone_EditMenu(playerid);

	if (isnull(inputtext) || strlen(inputtext) > 2)
		return dialog_EditZone(playerid, 1, 2, "\1");

	ZoneData[editZone[playerid]][zonePos][3] = floatstr(inputtext);

	Zone_Refresh(editZone[playerid]);
	Zone_Save(editZone[playerid]);

	Zone_EditMenu(playerid);

	return 1;
}

Dialog:EditZoneName(playerid, response, listitem, inputtext[])
{
	if (!response)
		return Zone_EditMenu(playerid);

	if (isnull(inputtext))
		return dialog_EditZone(playerid, 1, 2, "\1");

	format(ZoneData[editZone[playerid]][zoneName], 24, inputtext);

	Zone_Refresh(editZone[playerid]);
	Zone_Save(editZone[playerid]);

	Zone_EditMenu(playerid);

	return 1;
}