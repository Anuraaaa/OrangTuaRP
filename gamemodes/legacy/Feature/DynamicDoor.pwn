enum ddoor
{
	dName[128],
	dPass[32],
	dIcon,
	dLocked,
	dAdmin,
	dVip,
	dFaction,
	dFamily,
	dGarage,
	dCustom,
	dExtvw,
	dExtint,
	Float:dExtposX,
	Float:dExtposY,
	Float:dExtposZ,
	Float:dExtposA,
	dIntvw,
	dIntint,
	Float:dIntposX,
	Float:dIntposY,
	Float:dIntposZ,
	Float:dIntposA,
	//NotSave
	Text3D:dLabelext,
	Text3D:dLabelint,
	dPickupext,
	dPickupint,
	dMapIconID,
	dMapIcon,
	STREAMER_TAG_CP:dCP
};

new drData[MAX_DOOR][ddoor],
	Iterator: Doors<MAX_DOOR>;

Doors_Save(id)
{
	new dquery[2048];
	mysql_format(sqlcon, dquery, sizeof(dquery), "UPDATE doors SET name='%s', password='%s', icon='%d', locked='%d', admin='%d', vip='%d', faction='%d', family='%d', garage='%d', custom='%d', extvw='%d', extint='%d', extposx='%f', extposy='%f', extposz='%f', extposa='%f', intvw='%d', intint='%d', intposx='%f', intposy='%f', intposz='%f', intposa='%f', mapicon='%d' WHERE ID='%d'",
	drData[id][dName], drData[id][dPass], drData[id][dIcon], drData[id][dLocked], drData[id][dAdmin], drData[id][dVip], drData[id][dFaction], drData[id][dFamily], drData[id][dGarage], drData[id][dCustom], drData[id][dExtvw], drData[id][dExtint], drData[id][dExtposX], drData[id][dExtposY], drData[id][dExtposZ], drData[id][dExtposA], drData[id][dIntvw], drData[id][dIntint],
	drData[id][dIntposX], drData[id][dIntposY], drData[id][dIntposZ], drData[id][dIntposA], drData[id][dMapIcon], id);
	mysql_tquery(sqlcon, dquery);
	return 1;
}

Doors_Updatelabel(id)
{
	if(id != -1)
	{
		if(IsValidDynamic3DTextLabel(drData[id][dLabelext]))
            DestroyDynamic3DTextLabel(drData[id][dLabelext]);

        if(IsValidDynamicPickup(drData[id][dPickupext]))
            DestroyDynamicPickup(drData[id][dPickupext]);

        if(IsValidDynamic3DTextLabel(drData[id][dLabelint]))
            DestroyDynamic3DTextLabel(drData[id][dLabelint]);

        if(IsValidDynamicPickup(drData[id][dPickupint]))
            DestroyDynamicPickup(drData[id][dPickupint]);
		
		if(IsValidDynamicMapIcon(drData[id][dMapIconID]))
			DestroyDynamicMapIcon(drData[id][dMapIconID]);
		
		if(IsValidDynamicCP(drData[id][dCP]))
			DestroyDynamicCP(drData[id][dCP]);

		new mstr[144];
		if(drData[id][dGarage] == 1)
		{
			format(mstr,sizeof(mstr),"[Door: %d]\n{FFFFFF}%s\n{FFFFFF}Press "GOLD"[Y] {FFFFFF}to enter", id, drData[id][dName]);
			drData[id][dPickupext] = CreateDynamicPickup(19130, 23, drData[id][dExtposX], drData[id][dExtposY], drData[id][dExtposZ], drData[id][dExtvw], drData[id][dExtint], -1, 50);
			drData[id][dLabelext] = CreateDynamic3DTextLabel(mstr, X11_LIGHTBLUE, drData[id][dExtposX], drData[id][dExtposY], drData[id][dExtposZ]+0.35, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, drData[id][dExtvw], drData[id][dExtint]);
		}
		else
		{
			format(mstr,sizeof(mstr),"[Door: %d]\n{FFFFFF}%s\n{FFFFFF}Press "GOLD"[F/ENTER] {FFFFFF}to enter", id, drData[id][dName]);
			drData[id][dPickupext] = CreateDynamicPickup(19130, 23, drData[id][dExtposX], drData[id][dExtposY], drData[id][dExtposZ], drData[id][dExtvw], drData[id][dExtint], -1, 50);
			drData[id][dLabelext] = CreateDynamic3DTextLabel(mstr, X11_LIGHTBLUE, drData[id][dExtposX], drData[id][dExtposY], drData[id][dExtposZ]+0.35, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, drData[id][dExtvw], drData[id][dExtint]);
			drData[id][dCP] = CreateDynamicCP(drData[id][dExtposX], drData[id][dExtposY], drData[id][dExtposZ], 2.0, drData[id][dExtvw], drData[id][dExtint], -1, 3.0);
		}
		
        if(drData[id][dIntposX] != 0.0 && drData[id][dIntposY] != 0.0 && drData[id][dIntposZ] != 0.0)
        {
			if(drData[id][dGarage] == 1)
			{
				format(mstr,sizeof(mstr),"[Door: %d]\n{FFFFFF}%s\n{FFFFFF}Press "GOLD"[Y] {FFFFFF}to exit", id, drData[id][dName]);

				drData[id][dLabelint] = CreateDynamic3DTextLabel(mstr, X11_LIGHTBLUE, drData[id][dIntposX], drData[id][dIntposY], drData[id][dIntposZ]+0.7, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, drData[id][dIntvw], drData[id][dIntint]);
				drData[id][dPickupint] = CreateDynamicPickup(19130, 23, drData[id][dIntposX], drData[id][dIntposY], drData[id][dIntposZ], drData[id][dIntvw], drData[id][dIntint], -1, 50);
			}
			else
			{
				format(mstr,sizeof(mstr),"[Door: %d]\n{FFFFFF}%s\n{FFFFFF}Press "GOLD"[F/ENTER] {FFFFFF}to exit", id, drData[id][dName]);

				drData[id][dLabelint] = CreateDynamic3DTextLabel(mstr, X11_LIGHTBLUE, drData[id][dIntposX], drData[id][dIntposY], drData[id][dIntposZ]+0.7, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, drData[id][dIntvw], drData[id][dIntint]);
				drData[id][dPickupint] = CreateDynamicPickup(19130, 23, drData[id][dIntposX], drData[id][dIntposY], drData[id][dIntposZ], drData[id][dIntvw], drData[id][dIntint], -1, 50);
			}
		}

		if(drData[id][dMapIcon])
		{
		    drData[id][dMapIconID] = CreateDynamicMapIcon(drData[id][dExtposX], drData[id][dExtposY], drData[id][dExtposZ], drData[id][dMapIcon], 0, .worldid = drData[id][dExtvw], .interiorid = drData[id][dExtint]);
		}
	}
}

/*LoadDoors()
{
	mysql_tquery(D_SQL, "SELECT ID,name,password,icon,locked,admin,vip,faction,family,custom,extvw,extint,extposx,extposy,extposz,extposa,intvw,intint,intposx,intposy,intposz,intposa FROM doors ORDER BY ID", "LoadDoorsData");
}*/

function Doors_Created(playerid, id)
{
	Doors_Save(id);
	Doors_Updatelabel(id);
	SendServerMessage(playerid, "Door [%d] berhasil di buat!", id);
	return 1;
}

function Doors_Load()
{
    new rows = cache_num_rows();
 	if(rows)
  	{
   		new did, name[128], password[128];
		for(new i; i < rows; i++)
		{
  			cache_get_value_name_int(i, "ID", did);
	    	cache_get_value_name(i, "name", name);
			format(drData[did][dName], 128, name);
		    cache_get_value_name(i, "password", password);
			format(drData[did][dPass], 128, password);
		    cache_get_value_name_int(i, "icon", drData[did][dIcon]);
			cache_get_value_name_int(i, "mapicon", drData[did][dMapIcon]);
		    cache_get_value_name_int(i, "locked", drData[did][dLocked]);
		    cache_get_value_name_int(i, "admin", drData[did][dAdmin]);
		    cache_get_value_name_int(i, "vip", drData[did][dVip]);
		    cache_get_value_name_int(i, "faction", drData[did][dFaction]);
		    cache_get_value_name_int(i, "family", drData[did][dFamily]);
			cache_get_value_name_int(i, "garage", drData[did][dGarage]);
		    cache_get_value_name_int(i, "custom", drData[did][dCustom]);
		    cache_get_value_name_int(i, "extvw", drData[did][dExtvw]);
		    cache_get_value_name_int(i, "extint", drData[did][dExtint]);
		    cache_get_value_name_float(i, "extposx", drData[did][dExtposX]);
			cache_get_value_name_float(i, "extposy", drData[did][dExtposY]);
			cache_get_value_name_float(i, "extposz", drData[did][dExtposZ]);
			cache_get_value_name_float(i, "extposa", drData[did][dExtposA]);
			cache_get_value_name_int(i, "intvw", drData[did][dIntvw]);
			cache_get_value_name_int(i, "intint", drData[did][dIntint]);
			cache_get_value_name_float(i, "intposx", drData[did][dIntposX]);
			cache_get_value_name_float(i, "intposy", drData[did][dIntposY]);
			cache_get_value_name_float(i, "intposz", drData[did][dIntposZ]);
			cache_get_value_name_float(i, "intposa", drData[did][dIntposA]);
			drData[did][dMapIconID] = -1;

			
			Iter_Add(Doors, did);
			Doors_Updatelabel(did);
	    }
	    printf("[DOOR] Loaded %d door from database", rows);
	}
}

CMD:createdoor(playerid, params[])
{
	if(PlayerData[playerid][pAdmin] < 3)
		return SendErrorMessage(playerid, NO_PERMISSION);
	
	new did = Iter_Free(Doors), mstr[128], query[248];
	if(did == -1) return SendErrorMessage(playerid, "You cant create more door!");
	new name[128];
	if(sscanf(params, "s[128]", name)) return SendClientMessageEx(playerid, COLOR_WHITE, "[USAGE]: /createdoor [name]");
	format(drData[did][dName], 128, name);
	GetPlayerPos(playerid, drData[did][dExtposX], drData[did][dExtposY], drData[did][dExtposZ]);
	GetPlayerFacingAngle(playerid, drData[did][dExtposA]);
	drData[did][dExtvw] = GetPlayerVirtualWorld(playerid);
	drData[did][dExtint] = GetPlayerInterior(playerid);
	format(drData[did][dPass], 32, "");
	drData[did][dIcon] = 19130;
	drData[did][dLocked] = 0;
	drData[did][dAdmin] = 0;
	drData[did][dVip] = 0;
	drData[did][dFaction] = -1;
	drData[did][dFamily] = -1;
	drData[did][dGarage] = 0;
	drData[did][dCustom] = 0;
	drData[did][dIntvw] = 0;
	drData[did][dIntint] = 0;
	drData[did][dIntposX] = 0;
	drData[did][dIntposY] = 0;
	drData[did][dIntposZ] = 0;
	drData[did][dIntposA] = 0;
	drData[did][dMapIcon] = 0;
	drData[did][dMapIconID] = -1;
	
	format(mstr,sizeof(mstr),"[ID: %d]\n{FFFFFF}%s\n{FFFFFF}Press {FF0000}[F] {FFFFFF}to enter", did, drData[did][dName]);
	drData[did][dPickupext] = CreateDynamicPickup(19130, 23, drData[did][dExtposX], drData[did][dExtposY], drData[did][dExtposZ], drData[did][dExtvw], drData[did][dExtint], -1, 50);
	drData[did][dLabelext] = CreateDynamic3DTextLabel( mstr, X11_LIGHTBLUE, drData[did][dExtposX], drData[did][dExtposY], drData[did][dExtposZ]+0.35, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, drData[did][dExtvw], drData[did][dExtint]);
    
	Doors_Updatelabel(did);
	Iter_Add(Doors, did);

	mysql_format(sqlcon, query, sizeof(query), "INSERT INTO doors SET ID=%d, extvw=%d, extint=%d, extposx=%f, extposy=%f, extposz=%f, extposa=%f, name='%s'", did, drData[did][dExtvw], drData[did][dExtint], drData[did][dExtposX], drData[did][dExtposY], drData[did][dExtposZ], drData[did][dExtposA], name);
	mysql_tquery(sqlcon, query, "Doors_Created", "ii", playerid, did);
	return 1;
}

CMD:gotodoor(playerid, params[])
{
	new did;
	if(PlayerData[playerid][pAdmin] < 2)
        return SendErrorMessage(playerid, NO_PERMISSION);
		
	if(sscanf(params, "d", did))
		return SendClientMessageEx(playerid, COLOR_WHITE, "[USAGE]: /gotodoor [id]");
	if(!Iter_Contains(Doors, did)) return SendErrorMessage(playerid, "The doors you specified ID of doesn't exist.");

	SetPlayerPositionEx(playerid, drData[did][dExtposX], drData[did][dExtposY], drData[did][dExtposZ]);
    SetPlayerInterior(playerid, drData[did][dExtint]);
    SetPlayerVirtualWorld(playerid, drData[did][dExtvw]);
	PlayerData[playerid][pInDoor] = -1;
	PlayerData[playerid][pInHouse] = -1;
	PlayerData[playerid][pInBiz] = -1;	
	SendServerMessage(playerid, "You has teleport to door id %d", did);
	return 1;
}
CMD:editdoor(playerid, params[])
{
    static
        did,
        type[24],
        string[128];

    if(PlayerData[playerid][pAdmin] < 3)
        return SendErrorMessage(playerid, NO_PERMISSION);

    if(sscanf(params, "ds[24]S()[128]", did, type, string))
    {
        SendClientMessageEx(playerid, COLOR_WHITE, "(Usage) /editdoor [id] [name]");
        SendClientMessage(playerid, X11_LIGHTBLUE, "(Names){FFFFFF} location, interior, password, name, locked, admin, vip, faction, family, custom, virtual, iconmap");
        return 1;
    }
    if((did < 0 || did >= MAX_DOOR))
        return SendErrorMessage(playerid, "You have specified an invalid entrance ID.");
	if(!Iter_Contains(Doors, did)) return SendErrorMessage(playerid, "The doors you specified ID of doesn't exist.");

    if(!strcmp(type, "location", true))
    {
		GetPlayerPos(playerid, drData[did][dExtposX], drData[did][dExtposY], drData[did][dExtposZ]);
		GetPlayerFacingAngle(playerid, drData[did][dExtposA]);

        drData[did][dExtvw] = GetPlayerVirtualWorld(playerid);
		drData[did][dExtint] = GetPlayerInterior(playerid);
        Doors_Save(did);
		Doors_Updatelabel(did);

        SendAdminMessage(COLOR_RED, "%s has adjusted the location of entrance ID: %d.", PlayerData[playerid][pUCP], did);
    }
    else if(!strcmp(type, "interior", true))
    {
        GetPlayerPos(playerid, drData[did][dIntposX], drData[did][dIntposY], drData[did][dIntposZ]);
		GetPlayerFacingAngle(playerid, drData[did][dIntposA]);

        drData[did][dIntvw] = GetPlayerVirtualWorld(playerid);
		drData[did][dIntint] = GetPlayerInterior(playerid);
        Doors_Save(did);
		Doors_Updatelabel(did);

       /*foreach (new i : Player)
        {
            if(PlayerData[i][pEntrance] == EntranceData[id][entranceID])
            {
                SetPlayerPos(i, EntranceData[id][entranceInt][0], EntranceData[id][entranceInt][1], EntranceData[id][entranceInt][2]);
                SetPlayerFacingAngle(i, EntranceData[id][entranceInt][3]);

                SetPlayerInterior(i, EntranceData[id][entranceInterior]);
                SetCameraBehindPlayer(i);
            }
        }*/
        SendAdminMessage(COLOR_RED, "%s has adjusted the interior spawn of entrance ID: %d.", PlayerData[playerid][pUCP], did);
    }
    else if(!strcmp(type, "custom", true))
    {
        new status;

        if(sscanf(string, "d", status))
            return SendClientMessageEx(playerid, COLOR_WHITE, "[USAGE]: /editdoor [id] [custom] [0/1]");

        if(status < 0 || status > 1)
            return SendErrorMessage(playerid, "You must specify at least 0 or 1.");

        drData[did][dCustom] = status;
        Doors_Save(did);
		Doors_Updatelabel(did);

        if(status) {
            SendAdminMessage(COLOR_RED, "%s has enabled custom interior mode for entrance ID: %d.", PlayerData[playerid][pUCP], did);
        }
        else {
            SendAdminMessage(COLOR_RED, "%s has disabled custom interior mode for entrance ID: %d.", PlayerData[playerid][pUCP], did);
        }
    }
    else if(!strcmp(type, "virtual", true))
    {
        new worldid;

        if(sscanf(string, "d", worldid))
            return SendClientMessageEx(playerid, COLOR_WHITE, "[USAGE]: /editdoor [id] [virtual] [interior world]");

        drData[did][dExtvw] = worldid;

        Doors_Save(did);
		Doors_Updatelabel(did);
        SendAdminMessage(COLOR_RED, "%s has adjusted the virtual of entrance ID: %d to %d.", PlayerData[playerid][pUCP], did, worldid);
    }
    else if(!strcmp(type, "password", true))
    {
        new password[32];

        if(sscanf(string, "s[32]", password))
            return SendClientMessageEx(playerid, COLOR_WHITE, "[USAGE]: /editdoor [id] [password] [entrance pass] (use 'none' to disable)");

        if(!strcmp(password, "none", true)) {
            format(drData[did][dPass], 32, "");
        }
        else {
            format(drData[did][dPass], 32, password);
        }
        Doors_Save(did);
		Doors_Updatelabel(did);
        SendAdminMessage(COLOR_RED, "%s has adjusted the password of entrance ID: %d to %s", PlayerData[playerid][pUCP], did, password);
    }
    else if(!strcmp(type, "locked", true))
    {
        new locked;

        if(sscanf(string, "d", locked))
            return SendClientMessageEx(playerid, COLOR_WHITE, "[USAGE]: /editdoor [id] [locked] [locked 0/1]");

        if(locked < 0 || locked > 1)
            return SendErrorMessage(playerid, "Invalid value. Use 0 for unlocked and 1 for locked.");

        drData[did][dLocked] = locked;
        Doors_Save(did);
		Doors_Updatelabel(did);

        if(locked) {
            SendAdminMessage(COLOR_RED, "%s has locked entrance ID: %d.", PlayerData[playerid][pUCP], did);
        } else {
            SendAdminMessage(COLOR_RED, "%s has unlocked entrance ID: %d.", PlayerData[playerid][pUCP], did);
        }
    }
    else if(!strcmp(type, "name", true))
    {
        new name[128];

        if(sscanf(string, "s[128]", name))
            return SendClientMessageEx(playerid, COLOR_WHITE, "[USAGE]: /editdoor [id] [name] [new name]");

        format(drData[did][dName], 128, name);

        Doors_Save(did);
		Doors_Updatelabel(did);

        SendAdminMessage(COLOR_RED, "%s has adjusted the name of entrance ID: %d to \"%s\".", PlayerData[playerid][pUCP], did, name);
    }
	else if(!strcmp(type, "admin", true))
    {
        new level;

        if(sscanf(string, "d", level))
            return SendClientMessageEx(playerid, COLOR_WHITE, "[USAGE]: /editdoor [id] [admin] [level]");

        if(level < 0 || level > 5)
            return SendErrorMessage(playerid, "Invalid value. Use 0 - 5 for level.");

        drData[did][dAdmin] = level;
        Doors_Save(did);
		Doors_Updatelabel(did);

        SendAdminMessage(COLOR_RED, "%s has set entrance ID: %d to admin level %d.", PlayerData[playerid][pUCP], did, level);
    }
	else if(!strcmp(type, "vip", true))
    {
        new level;

        if(sscanf(string, "d", level))
            return SendClientMessageEx(playerid, COLOR_WHITE, "[USAGE]: /editdoor [id] [VIP] [level]");

        if(level < 0 || level > 3)
            return SendErrorMessage(playerid, "Invalid value. Use 0 - 3 for level.");

        drData[did][dVip] = level;
        Doors_Save(did);
		Doors_Updatelabel(did);

        SendAdminMessage(COLOR_RED, "%s has set entrance ID: %d to VIP level %d.", PlayerData[playerid][pUCP], did, level);
    }
	else if(!strcmp(type, "faction", true))
    {
        new fid;

        if(sscanf(string, "d", fid))
            return SendClientMessageEx(playerid, COLOR_WHITE, "[USAGE]: /editdoor [id] [faction] [faction id]");


        drData[did][dFaction] = fid;
        Doors_Save(did);
		Doors_Updatelabel(did);

        SendAdminMessage(COLOR_RED, "%s has set entrance ID: %d to faction id %d.", PlayerData[playerid][pUCP], did, fid);
    }
	else if(!strcmp(type, "family", true))
    {
        new fid;

        if(sscanf(string, "d", fid))
            return SendClientMessageEx(playerid, COLOR_WHITE, "[USAGE]: /editdoor [id] [family] [family id]");

        if(fid < -1 || fid > 9)
            return SendErrorMessage(playerid, "Invalid value. Use -1 - 9 for family id.");

        drData[did][dFamily] = fid;
        Doors_Save(did);
		Doors_Updatelabel(did);

        SendAdminMessage(COLOR_RED, "%s has set entrance ID: %d to family id %d.", PlayerData[playerid][pUCP], did, fid);
    }
	else if(!strcmp(type, "garage", true))
	{
		new gid;

        if(sscanf(string, "d", gid))
            return SendClientMessageEx(playerid, COLOR_WHITE, "[USAGE]: /editdoor [id] [garage] [0 - 1]");

        if(gid < 0 || gid > 1)
            return SendErrorMessage(playerid, "Invalid value! Use 0 to disable, 1 to enable.");
		
		if(gid == 0)
		{
			drData[did][dGarage] = 0;
			SendAdminMessage(COLOR_RED, "%s has set entrance ID: %d to garage vehicle disable.", PlayerData[playerid][pUCP], did);
		}
		else
		{
			drData[did][dGarage] = 1;
			SendAdminMessage(COLOR_RED, "%s has set entrance ID: %d to garage vehicle enable.", PlayerData[playerid][pUCP], did);
		}
		Doors_Save(gid);
		Doors_Updatelabel(gid);
	}
	else if(!strcmp(type, "iconmap", true))
	{
		new iconid;
	    if(sscanf(string, "i", iconid))
	    {
	        return SendClientMessageEx(playerid, COLOR_WHITE, "[USAGE]: /editdoor [id] [iconmap] [iconid (0-63)]");
		}
		if(!(0 <= iconid <= 63))
		{
		    return SendErrorMessage(playerid, "Ikon peta tidak valid..");
		}

		drData[did][dMapIcon] = iconid;

		Doors_Save(did);
		Doors_Updatelabel(did);

	    SendAdminMessage(COLOR_RED, "%s has set entrance ID: %d to Map Icon id %d.", PlayerData[playerid][pUCP], did, iconid);
	}
	else if(!strcmp(type, "delete", true))
    {
		DestroyDynamic3DTextLabel(drData[did][dLabelext]);
		DestroyDynamicPickup(drData[did][dPickupext]);
		DestroyDynamic3DTextLabel(drData[did][dLabelint]);
		DestroyDynamicPickup(drData[did][dPickupint]);
		DestroyDynamicMapIcon(drData[did][dMapIconID]);
		DestroyDynamicCP(drData[did][dCP]);
		
		drData[did][dExtposX] = 0;
		drData[did][dExtposY] = 0;
		drData[did][dExtposZ] = 0;
		drData[did][dExtposA] = 0;
		drData[did][dExtvw] = 0;
		drData[did][dExtint] = 0;
		format(drData[did][dPass], 32, "");
		drData[did][dIcon] = 0;
		drData[did][dLocked] = 0;
		drData[did][dAdmin] = 0;
		drData[did][dVip] = 0;
		drData[did][dFaction] = -1;
		drData[did][dFamily] = -1;
		drData[did][dGarage] = 0;
		drData[did][dCustom] = 0;
		drData[did][dIntvw] = 0;
		drData[did][dIntint] = 0;
		drData[did][dIntposX] = 0;
		drData[did][dIntposY] = 0;
		drData[did][dIntposZ] = 0;
		drData[did][dIntposA] = 0;
		drData[did][dMapIconID] = -1;
		drData[did][dMapIcon] = 0;
		
		drData[did][dLabelext] = Text3D: INVALID_3DTEXT_ID;
		drData[did][dLabelint] = Text3D: INVALID_3DTEXT_ID;
		drData[did][dPickupext] = -1;
		drData[did][dPickupint] = -1;
		
		Iter_Remove(Doors, did);
		new query[128];
		mysql_format(sqlcon, query, sizeof(query), "DELETE FROM doors WHERE ID=%d", did);
		mysql_tquery(sqlcon, query);
        SendAdminMessage(COLOR_RED, "%s has delete door ID: %d.", PlayerData[playerid][pUCP], did);
	}
    return 1;
}