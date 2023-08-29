#include <YSI_Coding\y_hooks>

#define     TRASH_BAG_VALUE     (800)    	// value of a collected trash bag (default: 125)
#define     REFILL_TIME         (300)   	// trash container refill time - in seconds (default: 300)
#define     ATTACHMENT_INDEX    (9)     	// for setplayerattachedobject (default: 4)
#define     TRASH_LIMIT         (10)    	// trashmaster capacity (default: 10)

new Text3D: FactoryLabel,
	FactoryCurrent,
	FactoryCP,
	FactoryIcons[MAX_PLAYERS],
	TrashIcons[MAX_PLAYERS][MAX_TRASH];

enum E_TRASH_DATA
{
	TrashID,
	bool: TrashExists,
	TrashType,
	Float: TrashX,
	Float: TrashY,
	Float: TrashZ,
	Float: TrashRotX,
	Float: TrashRotY,
	Float: TrashRotZ,
	Text3D: TrashLabel,
	TrashLevel,
	TrashModel,
	TrashObject,
	TrashTimer	
}

new	TrashData[MAX_TRASH][E_TRASH_DATA];

new
	OnTrash[MAX_PLAYERS],
	bool: HasTrash[MAX_PLAYERS],
	LoadedTrash[MAX_VEHICLES],
	TrashCP[MAX_PLAYERS] = {-1, ...},
    PlayerText: CapacityText[MAX_PLAYERS],
    PlayerBar: CapacityBar[MAX_PLAYERS];

function Trash_Load()
{
	new rows = cache_num_rows();
	if(rows)
	{
	    for(new i = 0; i < rows; i++)
	    {
            TrashData[i][TrashExists] = true;
            cache_get_value_name_int(i, "TrashID", TrashData[i][TrashID]);
			cache_get_value_name_int(i, "TrashType", TrashData[i][TrashType]);
			cache_get_value_name_float(i, "TrashX", TrashData[i][TrashX]);
			cache_get_value_name_float(i, "TrashY", TrashData[i][TrashY]);
			cache_get_value_name_float(i, "TrashZ", TrashData[i][TrashZ]);
			cache_get_value_name_float(i, "TrashRotX", TrashData[i][TrashRotX]);
			cache_get_value_name_float(i, "TrashRotY", TrashData[i][TrashRotY]);
			cache_get_value_name_float(i, "TrashRotZ", TrashData[i][TrashRotZ]);

			Trash_Spawn(i);
            Trash_Refresh(i);
        }
        printf("[TRASH] Loaded %d Trash from database", rows);
    }
}    

Trash_Create(playerid, type)
{
	new
	    Float:x,
	    Float:y,
	    Float:z,
	    Float:angle;

	if (GetPlayerPos(playerid, x, y, z) && GetPlayerFacingAngle(playerid, angle))
	{
		for (new i = 0; i < MAX_TRASH; i ++) if (!TrashData[i][TrashExists])
		{
		    TrashData[i][TrashExists] = true;
			TrashData[i][TrashType] = type;

			TrashData[i][TrashX] = x + (3.0 * floatsin(-angle, degrees));
			TrashData[i][TrashY] = y + (3.0 * floatcos(-angle, degrees));
			TrashData[i][TrashZ] = z;
			TrashData[i][TrashRotX] = 0.0;
			TrashData[i][TrashRotY] = 0.0;
			TrashData[i][TrashRotZ] = angle;

			Trash_Spawn(i);
            Trash_Refresh(i);
			mysql_tquery(sqlcon, "INSERT INTO `trash` (`TrashType`) VALUES(1)", "OnTrashCreated", "d", i);

			PlayerData[playerid][pEditing] = -1;
			EditDynamicObject(playerid, TrashData[i][TrashObject]);
			PlayerData[playerid][pEditing] = i;
			PlayerData[playerid][pEditType] = EDIT_TRASH;
			SendServerMessage(playerid, "Kamu membuat Trash ID: %d.", i);
			return i;
		}
	}
	return -1;
}

function OnTrashCreated(id)
{
	if (id == -1 || !TrashData[id][TrashExists])
	    return 0;

	TrashData[id][TrashID] = cache_insert_id();
	Trash_Save(id);

	return 1;
}

Trash_Delete(id)
{
    if (id != -1 && TrashData[id][TrashExists])
	{

        if(IsValidDynamic3DTextLabel(TrashData[id][TrashLabel]))
            DestroyDynamic3DTextLabel(TrashData[id][TrashLabel]);
		
		if(IsValidDynamicObject(TrashData[id][TrashObject]))
            DestroyDynamicObject(TrashData[id][TrashObject]);

        new string[64];
        mysql_format(sqlcon, string, sizeof(string), "DELETE FROM `trash` WHERE `TrashID` = '%d'", TrashData[id][TrashID]);
        mysql_tquery(sqlcon, string);

        TrashData[id][TrashID] = 0;
        TrashData[id][TrashExists] = false;
    }    
	return 1;
}

Trash_Spawn(id)
{
	if(id != -1 && TrashData[id][TrashExists])
	{		    
		if(IsValidDynamicObject(TrashData[id][TrashObject]))
            DestroyDynamicObject(TrashData[id][TrashObject]);

		if(IsValidDynamic3DTextLabel(TrashData[id][TrashLabel]))
            DestroyDynamic3DTextLabel(TrashData[id][TrashLabel]);

		if(TrashData[id][TrashType] == 1)
		{
			if(TrashData[id][TrashLevel] > 0)
			{
				new string[156];
				format(string, sizeof(string), "{00FF00}[Trash Bin: %d]\n{FFFF00}/trash {FFFFFF}- to drop trash.\n{FFFF00}/pickup {FFFFFF}- collect trash.", id);
				TrashData[id][TrashLabel] = CreateDynamic3DTextLabel(string, COLOR_CLIENT, TrashData[id][TrashX], TrashData[id][TrashY], TrashData[id][TrashZ] + 0.5, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0);		
				TrashData[id][TrashObject] = CreateDynamicObject(1343, TrashData[id][TrashX], TrashData[id][TrashY], TrashData[id][TrashZ], TrashData[id][TrashRotX], TrashData[id][TrashRotY], TrashData[id][TrashRotZ], 0, 0);
			}
			else
			{
				new string[156];
				format(string, sizeof(string), "{FF0000}[Trash Bin: %d]\n{FFFF00}/trash {FFFFFF}- to drop trash.\n{FFFF00}/pickup {FFFFFF}- collect trash.", id);
				TrashData[id][TrashLabel] = CreateDynamic3DTextLabel(string, COLOR_CLIENT, TrashData[id][TrashX], TrashData[id][TrashY], TrashData[id][TrashZ] + 0.5, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0);		
				TrashData[id][TrashObject] = CreateDynamicObject(1343, TrashData[id][TrashX], TrashData[id][TrashY], TrashData[id][TrashZ], TrashData[id][TrashRotX], TrashData[id][TrashRotY], TrashData[id][TrashRotZ], 0, 0);
			}
		}
		else
		{
			if(TrashData[id][TrashLevel] > 0)
			{
				new string[156];
				format(string, sizeof(string), "{00FF00}[Dumpster: %d]\n{FFFF00}/trash {FFFFFF}- to drop trash.\n{FFFF00}/pickup {FFFFFF}- collect trash.", id);
				TrashData[id][TrashLabel] = CreateDynamic3DTextLabel(string, COLOR_CLIENT, TrashData[id][TrashX], TrashData[id][TrashY], TrashData[id][TrashZ] + 1.25, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0);		
				TrashData[id][TrashObject] = CreateDynamicObject(1372, TrashData[id][TrashX], TrashData[id][TrashY], TrashData[id][TrashZ], TrashData[id][TrashRotX], TrashData[id][TrashRotY], TrashData[id][TrashRotZ], 0, 0);
			}
			else 
			{
				new string[156];
				format(string, sizeof(string), "{FF0000}[Dumpster: %d]\n{FFFF00}/trash {FFFFFF}- to drop trash.\n{FFFF00}/pickup {FFFFFF}- collect trash.", id);
				TrashData[id][TrashLabel] = CreateDynamic3DTextLabel(string, COLOR_CLIENT, TrashData[id][TrashX], TrashData[id][TrashY], TrashData[id][TrashZ] + 1.25, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0);		
				TrashData[id][TrashObject] = CreateDynamicObject(1372, TrashData[id][TrashX], TrashData[id][TrashY], TrashData[id][TrashZ], TrashData[id][TrashRotX], TrashData[id][TrashRotY], TrashData[id][TrashRotZ], 0, 0);
			}
		}

		TrashData[id][TrashLevel] = (TrashData[id][TrashType] == 1) ? 1 : 2;
	}
	return 1;
}

Trash_Refresh(id)
{
	new string[156];
	if(id != -1 && TrashData[id][TrashExists])
	{	
		if(TrashData[id][TrashType] == 1)
		{
			if(TrashData[id][TrashLevel] > 0)
			{
				format(string, sizeof(string), "{00FF00}[Trash Bin: %d]\n{FFFF00}/trash {FFFFFF}- to drop trash.\n{FFFF00}/pickup {FFFFFF}- collect trash.", id);
			}
			else
			{
				format(string, sizeof(string), "{FF0000}[Trash Bin: %d]\n{FFFF00}/trash {FFFFFF}- to drop trash.\n{FFFF00}/pickup {FFFFFF}- collect trash.", id);
			}
		}
		else
		{
			if(TrashData[id][TrashLevel] > 0)
			{
				format(string, sizeof(string), "{00FF00}[Dumpster: %d]\n{FFFF00}/trash {FFFFFF}- to drop trash.\n{FFFF00}/pickup {FFFFFF}- collect trash.", id);
			}
			else
			{
				format(string, sizeof(string), "{FF0000}[Dumpster: %d]\n{FFFF00}/trash {FFFFFF}- to drop trash.\n{FFFF00}/pickup {FFFFFF}- collect trash.", id);
			}
		}

		UpdateDynamic3DTextLabelText(TrashData[id][TrashLabel], 0x007FFFFF, string);
		Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, TrashData[id][TrashLabel], E_STREAMER_X, TrashData[id][TrashX]);
		Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, TrashData[id][TrashLabel], E_STREAMER_Y, TrashData[id][TrashY]);
		Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, TrashData[id][TrashLabel], E_STREAMER_Z, TrashData[id][TrashZ]);


		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, TrashData[id][TrashObject], E_STREAMER_X, TrashData[id][TrashX]);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, TrashData[id][TrashObject], E_STREAMER_Y, TrashData[id][TrashY]);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, TrashData[id][TrashObject], E_STREAMER_Z, TrashData[id][TrashZ]);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, TrashData[id][TrashObject], E_STREAMER_R_X, TrashData[id][TrashRotX]);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, TrashData[id][TrashObject], E_STREAMER_R_Y, TrashData[id][TrashRotY]);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, TrashData[id][TrashObject], E_STREAMER_R_Z, TrashData[id][TrashRotZ]);
	}
	return 1;
}

Trash_Save(id)
{
	new query[512];
	mysql_format(sqlcon, query, sizeof(query), "UPDATE `trash` SET ");
	mysql_format(sqlcon, query, sizeof(query), "%s`TrashType`='%i', ", query, TrashData[id][TrashType]);
	mysql_format(sqlcon, query, sizeof(query), "%s`TrashX`='%f', ", query, TrashData[id][TrashX]);
	mysql_format(sqlcon, query, sizeof(query), "%s`TrashY`='%f', ", query, TrashData[id][TrashY]);
	mysql_format(sqlcon, query, sizeof(query), "%s`TrashZ`='%f', ", query, TrashData[id][TrashZ]);
	mysql_format(sqlcon, query, sizeof(query), "%s`TrashRotX`='%f', ", query, TrashData[id][TrashRotX]);
	mysql_format(sqlcon, query, sizeof(query), "%s`TrashRotY`='%f', ", query, TrashData[id][TrashRotY]);
	mysql_format(sqlcon, query, sizeof(query), "%s`TrashRotZ`='%f' ", query, TrashData[id][TrashRotZ]);
	mysql_format(sqlcon, query, sizeof(query), "%sWHERE `TrashID` = '%d'", query, TrashData[id][TrashID]);
	mysql_tquery(sqlcon, query);
	return 1;
}

Trash_InitPlayer(playerid)
{
    HasTrash[playerid] = false;
    TrashCP[playerid] = -1;

    
	TogglePlayerDynamicCP(playerid, FactoryCP, 0);
	FactoryIcons[playerid] = -1;

	CapacityText[playerid] = CreatePlayerTextDraw(playerid, 89.000000, 145.000000, "Vehicle Capacity (10/10)");
	PlayerTextDrawFont(playerid, CapacityText[playerid], 1);
	PlayerTextDrawLetterSize(playerid, CapacityText[playerid], 0.254166, 1.350000);
	PlayerTextDrawTextSize(playerid, CapacityText[playerid], 463.000000, 247.000000);
	PlayerTextDrawSetOutline(playerid, CapacityText[playerid], 0);
	PlayerTextDrawSetShadow(playerid, CapacityText[playerid], 0);
	PlayerTextDrawAlignment(playerid, CapacityText[playerid], 2);
	PlayerTextDrawColor(playerid, CapacityText[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, CapacityText[playerid], 255);
	PlayerTextDrawBoxColor(playerid, CapacityText[playerid], 50);
	PlayerTextDrawUseBox(playerid, CapacityText[playerid], 0);
	PlayerTextDrawSetProportional(playerid, CapacityText[playerid], 1);

	CapacityBar[playerid] = CreatePlayerProgressBar(playerid, 43.000000, 134.000000, 91.500000, 6.500000, 1296911871, TRASH_LIMIT, 0);
	return 1;
}

Trash_ResetPlayer(playerid, removeUI = 0)
{
	if(IsPlayerAttachedObjectSlotUsed(playerid, ATTACHMENT_INDEX)) 
		RemovePlayerAttachedObject(playerid, ATTACHMENT_INDEX);
		
	if(IsValidDynamicCP(TrashCP[playerid])) 
		DestroyDynamicCP(TrashCP[playerid]);

	HasTrash[playerid] = false;
	TrashCP[playerid] = -1;

	if(removeUI)
	{
	    PlayerTextDrawDestroy(playerid, CapacityText[playerid]);
	    DestroyPlayerProgressBar(playerid, CapacityBar[playerid]);
	}

	return 1;
}

Trash_ShowCapacity(playerid)
{
    new vehicleid = GetPlayerVehicleID(playerid), capacity_string[32];
    format(capacity_string, sizeof(capacity_string), "Vehicle Capacity (%d/%d)", LoadedTrash[vehicleid], TRASH_LIMIT);
    PlayerTextDrawSetString(playerid, CapacityText[playerid], capacity_string);
    PlayerTextDrawShow(playerid, CapacityText[playerid]);

	SetPlayerProgressBarValue(playerid, CapacityBar[playerid], LoadedTrash[vehicleid]);
	ShowPlayerProgressBar(playerid, CapacityBar[playerid]);
	return 1;
}

Trash_Closest(playerid)
{
	new closest_id = -1, Float: dist = 3.0, Float: tempdist;
    for(new i; i < sizeof(TrashData); i++)
	{
	    tempdist = GetPlayerDistanceFromPoint(playerid, TrashData[i][TrashX], TrashData[i][TrashY], TrashData[i][TrashZ]);
		if(tempdist > 3.0) continue;
		if(tempdist <= dist)
		{
		    dist = tempdist;
		    closest_id = i;
		}
	}

	return closest_id;
}

IsTrashmasterVehicle(carid)
{
    for(new v = 0; v < sizeof(TrashVehicle); v++) {
        if(carid == TrashVehicle[v]) return 1;
    }
    return 0;
}

function FillTrash(id)
{
	TrashData[id][TrashLevel]++;
	if(TrashData[id][TrashType] == 1 && TrashData[id][TrashLevel] > 1) TrashData[id][TrashLevel] = 1;

	if(TrashData[id][TrashType] == 2) {
		if(TrashData[id][TrashLevel] == 1) TrashData[id][TrashTimer] = SetTimerEx("FillTrash", REFILL_TIME * 1000, false, "i", id);
		if(TrashData[id][TrashLevel] >= 2)
		{
			TrashData[id][TrashLevel] = 2;
			KillTimer(TrashData[id][TrashTimer]);
			TrashData[id][TrashTimer] = -1;
		}

		Trash_Refresh(id);
		return 1;
	}

	Trash_Refresh(id);
	return 1;
}

function TrashDone(playerid)
{
	new string[128], reson[50], vehicleid = PlayerData[playerid][pTrashVehicleID], cash = 5000;

	cash = LoadedTrash[vehicleid] * salaryTrashmaster;
	SendClientMessage(playerid, COLOR_JOB, string);
	format(reson, sizeof reson, "Trashmaster (%d Trash bag)", LoadedTrash[vehicleid]);
	GiveMoney(playerid, cash, reson);
	FactoryCurrent += LoadedTrash[vehicleid];
	LoadedTrash[vehicleid] = 0;
	Trash_ShowCapacity(playerid);
	format(string, sizeof(string), "Recycling Factory\n\n{FFFFFF}Current Trash Bags: {F39C12}%d\n{FFFFFF}Bring trash here to earn money!", FactoryCurrent);
	UpdateDynamic3DTextLabelText(FactoryLabel, 0x2ECC71FF, string);

	if(IsValidDynamicMapIcon(FactoryIcons[playerid]))
	{
		DestroyDynamicMapIcon(FactoryIcons[playerid]);
		FactoryIcons[playerid] = -1;
	}
	TogglePlayerDynamicCP(playerid, FactoryCP, 0);
	OnTrash[playerid] = 0;
	PlayerData[playerid][pTrashmasterDelay] = 800;
	TogglePlayerControllable(playerid, 1);

	VehicleData[GetPlayerVehicleID(playerid)][vFuel] = 10.0;
	SetVehicleToRespawn(GetPlayerVehicleID(playerid));
	SendClientMessageEx(playerid, COLOR_SERVER, "(Sidejob) {FFFFFF}Kamu berhasil menyelesaikan pekerjaan dan mendapatkan {00FF00}$%s {FFFFFF}di {FFFF00}/salary", FormatNumber(cash));
	return 1;	
}

CMD:createtrash(playerid, params[])
{
	static id = -1, idx;
    if(PlayerData[playerid][pAdmin] < 5) 
		return SendErrorMessage(playerid, NO_PERMISSION);
	if (sscanf(params, "d", idx)) 
		return SendSyntaxMessage(playerid, "/createtrash [type]");
	if(idx < 1 || idx > 2)
		return SendSyntaxMessage(playerid, "/createtrash [1. Trash Bin 2. Dumpster]");

	id = Trash_Create(playerid, idx);
	if (id == -1) return SendErrorMessage(playerid, "Server telah mencapai batas untuk trash.");
	SendServerMessage(playerid, "Kamu telah membuat Trash ID: %d.", id);
	return 1;
}

CMD:edittrash(playerid, params[])
{
	static id;
    if(PlayerData[playerid][pAdmin] < 5) 
		return SendErrorMessage(playerid, NO_PERMISSION);
	if (sscanf(params, "d", id)) 
		return SendSyntaxMessage(playerid, "/edittrash [id]");
	if ((id < 0 || id >= MAX_TRASH) || !TrashData[id][TrashExists]) 
		return SendErrorMessage(playerid, "Trash ID tidak valid!");

	PlayerData[playerid][pEditing] = -1;
	EditDynamicObject(playerid, TrashData[id][TrashObject]);
	PlayerData[playerid][pEditing] = id;
	PlayerData[playerid][pEditType] = EDIT_TRASH;
	SendServerMessage(playerid, "Kamu sekarang mengubah posisi Trash ID: %d.", id);
	return 1;
}

CMD:deletetrash(playerid, params[])
{
	static id = 0;
    if(PlayerData[playerid][pAdmin] < 5) 
		return SendErrorMessage(playerid, NO_PERMISSION);
	if (sscanf(params, "d", id)) 
		return SendSyntaxMessage(playerid, "/deletetrash [id]");
	if ((id < 0 || id >= MAX_TRASH) || !TrashData[id][TrashExists]) 
		return SendErrorMessage(playerid, "Trash ID tidak valid!");

	Trash_Delete(id);
	SendServerMessage(playerid, "Kamu telah menghapus Trash ID: %d.", id);
	return 1;
}

CMD:pickup(playerid, params[])
{	
	new vehicleid = PlayerData[playerid][pTrashVehicleID];
    new Float: x, Float: y, Float: z;

	if(IsPlayerInAnyVehicle(playerid)) 
		return SendErrorMessage(playerid, "Kamu harus keluar dari kendaraan terlebih dahulu");

	if(OnTrash[playerid] < 1)
		return SendErrorMessage(playerid, "Kamu tidak bekerja sebagai Trashmaster!");

	if(!IsTrashmasterVehicle(vehicleid)) 	
		return SendErrorMessage(playerid, "Kendaraan terakhirmu harus Trashmaster!");

    if(HasTrash[playerid]) 
		return SendErrorMessage(playerid, "Kamu sudah membawa kantung sampah.");

	new id = Trash_Closest(playerid);
	if(id == -1) 
		return SendErrorMessage(playerid, "Kamu tidak didekat tempat sampah manapun.");

	if(TrashData[id][TrashLevel] < 1) 
		return SendErrorMessage(playerid, "Tidak ada sampah pada tempat sampah ini.");

    GetVehicleBoot(vehicleid, x, y, z);

    if(GetPlayerDistanceFromPoint(playerid, x, y, z) >= 30.0) 
		return SendErrorMessage(playerid, "Kamu harus berada didekat Trashmaster yang kamu gunakan.");

	TrashData[id][TrashLevel]--;
	KillTimer(TrashData[id][TrashTimer]);
    TrashData[id][TrashTimer] = SetTimerEx("FillTrash", REFILL_TIME * 1000, false, "i", id);
	TrashCP[playerid] = CreateDynamicCP(x, y, z, 3.0, .playerid = playerid);
	HasTrash[playerid] = true;
	ApplyAnimation(playerid, "CARRY", "liftup105", 4.1, 0, 0, 0, 0, 0);
	SetPlayerAttachedObject(playerid, ATTACHMENT_INDEX, 1264, 6, 0.222, 0.024, 0.128, 1.90, -90.0, 0.0, 0.5,0.5, 0.5);
	
	Trash_Refresh(id);
	SendClientMessage(playerid, COLOR_JOB, "(Trashmaster) {FFFFFF}Kamu dapat menekan "YELLOW"N "WHITE"untuk menghilangkan kantung sampah.");
	return 1;
}
CMD:trash(playerid, params[])
{
	new id = Trash_Closest(playerid);
	if(id == -1) 	
		return SendErrorMessage(playerid, "Kamu tidak berada didekat tempat sampah manapun.");

	if(TrashData[id][TrashLevel] < 1) 
		return SendErrorMessage(playerid, "Tidak ada sampah pada tempat sampah ini.");

    if(PlayerData[playerid][pTrash] < 0)
		return SendErrorMessage(playerid, "Kamu tidak mempunyai sampah di inventory mu!");

	PlayerData[playerid][pTrash] -= 1;
	SendServerMessage(playerid, "Kamu Telah membuang sampah ke tempatnya");
	return 1;
}

hook OnGameModeInit() {

	if (IsSQLConnected()) {
		mysql_tquery(sqlcon, "SELECT * FROM `trash`", "Trash_Load", "");
	}
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	if((newkeys & KEY_NO) && HasTrash[playerid])
	{
		Trash_ResetPlayer(playerid);
		SendClientMessage(playerid, COLOR_JOB, "(Trashmaster) {FFFFFF}Kamu telah membuang kantung sampah.");
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}