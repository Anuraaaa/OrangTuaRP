#include <YSI_Coding\y_hooks>

new countdown_tick = 0;

CMD:ahelp(playerid, params[])
{
	if(PlayerData[playerid][pAdmin] < 1)
		return SendErrorMessage(playerid, "You're not an Administrator!");

	if(PlayerData[playerid][pAdmin] >= 1)
	{
		SendClientMessage(playerid, COLOR_YELLOW, "Helper: {FFFFFF}/aduty, /a(dmin chat), /sendto, /apm, /reports, /setvw");
		SendClientMessage(playerid, COLOR_YELLOW, "Helper: {FFFFFF}/ans, /ban, /unban, /oban, /kick, /jail, /unjail, /asay, /setinterior");
		SendClientMessage(playerid, COLOR_YELLOW, "Helper: {FFFFFF}/freeze, /unfreeze, /spec, /unspec, /aslap, /ojail, /checkvehicle");
		SendClientMessage(playerid, COLOR_YELLOW, "Helper: {FFFFFF}/warn, /owarn, /checkwarn, /checkchar, /checkucp, /(get/ban/unban)ip");
		SendClientMessage(playerid, COLOR_YELLOW, "Helper: {FFFFFF}/sendtoveh, /sendvehto, /send, /arevive, /acure, /adamages");
	}
	if(PlayerData[playerid][pAdmin] >= 2)
	{
		SendClientMessage(playerid, COLOR_YELLOW, "Senior Helper: {FFFFFF}/checkstats, /goto, /get, /setskin, /mark [set/goto], /destroyveh");
		SendClientMessage(playerid, COLOR_YELLOW, "Senior Helper: {FFFFFF}/findmask, /findnumber, /arevive, /entercar, /gentercar, /getcar");
	}
	if(PlayerData[playerid][pAdmin] >= 3)
	{
		SendClientMessage(playerid, COLOR_YELLOW, "Admin Level 1: {FFFFFF}/gotocar, /maxmotive, /afrisk, /setweather, /setskin, /vehinfo");
	}
	if(PlayerData[playerid][pAdmin] >= 4)
	{
		SendClientMessage(playerid, COLOR_YELLOW, "Admin Level 2: {FFFFFF}/sethp, /flipcar, /arevive, /gotoloc, /veh, /fixveh, /respawncar");
		SendClientMessage(playerid, COLOR_YELLOW, "Admin Level 2: {FFFFFF}/gotointerior, /clearitems, /flymode");
	}
	if(PlayerData[playerid][pAdmin] >= 5)
	{
		SendClientMessage(playerid, COLOR_YELLOW, "Senior Admin: {FFFFFF}/setfuel, /clearreports, /setarmor, /forceinsurance, /setname, /givewep, /ahide");
	}
	if(PlayerData[playerid][pAdmin] >= 6)
	{
		SendClientMessage(playerid, COLOR_YELLOW, "High Administrator: {FFFFFF}/motd, /amotd, /editdoor, /editplayer, /nextdoor, /setitem, ");
		SendClientMessage(playerid, COLOR_YELLOW, "High Administrator: {FFFFFF}/(create/destroy)atm, /doorname, /createcar, /destroycar, /givesalary");
		SendClientMessage(playerid, COLOR_YELLOW, "High Administrator: {FFFFFF}/(create/destroy)tree. /destroyusername, /destroychar");
		SendClientMessage(playerid, COLOR_YELLOW, "High Administrator: {FFFFFF}/(create/destroy/edit)gate, /(create/edit)workshop");
		SendClientMessage(playerid, COLOR_YELLOW, "High Administrator: {FFFFFF}/(create/destroy/edit)actor, /gaterequest");
	}
	if(PlayerData[playerid][pAdmin] >= 7)
	{
		SendClientMessage(playerid, COLOR_YELLOW, "Management: {FFFFFF}/(create/destroy/edit)faction, /(create/edit)biz, /(create/destroy/edit)house");
		SendClientMessage(playerid, COLOR_YELLOW, "Management: {FFFFFF}/givecash, /setcash, /setadmin, /(/create/edit)rental, /(create/destroy)speed");
		SendClientMessage(playerid, COLOR_YELLOW, "Management: {FFFFFF}/(create/destroy/edit)dealer, /generatevip");
	}
	return 1;
}

CMD:getip(playerid, params[]) {

	if(PlayerData[playerid][pAdmin] < 1)
		return PermissionError(playerid);

	new targetid;

	if(sscanf(params, "u", targetid))
		return SendSyntaxMessage(playerid, "/getip [playerid/PartOfName]");

	if(!IsPlayerConnected(targetid) || !IsPlayerConnected(targetid))
		return SendErrorMessage(playerid, "You have specified invalid player.");


    new
        city[24],
        country[24],
        region[24],
        isp[24];

    GetPlayerCountry(targetid, country);
    GetPlayerCity(targetid, city);
    GetPlayerRegion(targetid, region);
    GetPlayerISP(targetid, isp);

	SendClientMessageEx(playerid, X11_ORANGE, "========= %s Address Lookup =========", GetName(targetid, false));
	SendClientMessageEx(playerid, X11_ORANGE, "IP Address: "RED"%s.", ReturnIP(targetid));
	SendClientMessageEx(playerid, X11_ORANGE, "Region: "RED"%s.", region);
	SendClientMessageEx(playerid, X11_ORANGE, "Country: "RED"%s.", country);
	SendClientMessageEx(playerid, X11_ORANGE, "City: "RED"%s.", city);
	SendClientMessageEx(playerid, X11_ORANGE, "ISP: "RED"%s.", isp);
	Log_Write("Logs/adm_cmd_log.txt", "[%s] %s: /getip %s", ReturnDate(), GetUsername(playerid), params);
	return 1;
}

CMD:notinjured(playerid, params[]) {

	if(PlayerData[playerid][pAdmin] < 1)
		return PermissionError(playerid);

	SendClientMessage(playerid, X11_LIGHTBLUE, "===== Not Injured Player =====");
	foreach(new i : Player) if(IsPlayerSpawned(playerid) && !PlayerData[playerid][pInjured]) {
		SendClientMessageEx(playerid, X11_WHITE, "- %s(%s) [%d]", GetName(i), GetUsername(i), i);
	}
	return 1;
}
CMD:banip(playerid, params[]) {

	if(PlayerData[playerid][pAdmin] < 1)
		return PermissionError(playerid);

	new ip[24], reason[64];
	if(sscanf(params, "s[24]s[64]", ip, reason))
		return SendSyntaxMessage(playerid, "/banip [ip address] [reason]");

	new query[299];
	mysql_format(sqlcon, query, sizeof(query), "INSERT INTO `banip` (`IP`, `Admin`, `Reason`) VALUES('%e', '%e', '%e')", ip, GetUsername(playerid), reason);
	mysql_tquery(sqlcon, query);

	SendClientMessageToAllEx(X11_TOMATO, "AdmCmd: %s has blocked IP Address %s", GetUsername(playerid), ip);

    foreach(new i : Player) 
    {
        if (!strcmp(ReturnIP(i), ip, true))
        {
            KickEx(i);
        }
    }    
	Log_Write("Logs/adm_cmd_log.txt", "[%s] %s: /banip %s", ReturnDate(), GetUsername(playerid), params);
	return 1;
}

CMD:resetweap(playerid, params[]) {

	if(PlayerData[playerid][pAdmin] < 3)
		return PermissionError(playerid);

	new targetid;

	if(sscanf(params, "u", targetid))
		return SendSyntaxMessage(playerid, "/resetweap [playerid/PartOfName]");

	if(!IsPlayerConnected(targetid) || !IsPlayerConnected(targetid))
		return SendErrorMessage(playerid, "You have specified invalid player.");

	ResetWeapons(targetid);
	SendAdminAction(playerid, "You have reset %s weapon data.", ReturnName(targetid));
	return 1;
}
CMD:unbanip(playerid, params[]) {

	if(PlayerData[playerid][pAdmin] < 1)
		return PermissionError(playerid);

	new ip[24];
	if(sscanf(params, "s[24]", ip))
		return SendSyntaxMessage(playerid, "/unbanip [ip address]");


	new query[144];
	mysql_format(sqlcon, query, sizeof(query), "SELECT * FROM `banip` WHERE `IP` = '%e';", ip);
	mysql_tquery(sqlcon, query, "OnUnbanIP", "ds", playerid, ip);
	Log_Write("Logs/adm_cmd_log.txt", "[%s] %s: /unbanip %s", ReturnDate(), GetUsername(playerid), params);

	return 1;
}

function OnUnbanIP(playerid, ip[]) {

	if(!cache_num_rows())
		return SendErrorMessage(playerid, "IP %s tidak sedang diblokir.", ip);

	mysql_tquery(sqlcon, sprintf("DELETE FROM `banip` WHERE `IP` = '%s';", ip));
	SendClientMessageToAllEx(X11_TOMATO, "AdmCmd: IP Address %s has been unblocked by %s.", ip, GetUsername(playerid));
	return 1;
}
CMD:checkchar(playerid, params[]) {

	if(PlayerData[playerid][pAdmin] < 1)
		return PermissionError(playerid);

	if(isnull(params))
		return SendSyntaxMessage(playerid, "/checkchar [UCP Name]");

	new query[256];
	mysql_format(sqlcon, query, 256, "SELECT * FROM `characters` WHERE `UCP` = '%e'", params);
	mysql_tquery(sqlcon, query, "OnCharCheck", "ds", playerid, params);

	return 1;
}

CMD:checkucp(playerid, params[]) {

	if(PlayerData[playerid][pAdmin] < 1)
		return PermissionError(playerid);

	if(isnull(params))
		return SendSyntaxMessage(playerid, "/checkucp [character ame]");

	new query[256];
	mysql_format(sqlcon, query, 256, "SELECT * FROM `characters` WHERE `Name` = '%e'", params);
	mysql_tquery(sqlcon, query, "OnUCPCheck", "ds", playerid, params);

	return 1;
}

CMD:kickall(playerid, params[]) {

	if(PlayerData[playerid][pAdmin] < 4)
		return PermissionError(playerid);	

	SendClientMessageToAllEx(X11_TOMATO, "AdmCmd: %s telah mengeluarkan semua player dari server (except staff)", GetUsername(playerid));
	foreach(new i : Player) if(PlayerData[i][pAdmin] < 1) {
		KickEx(i);
	}
	return 1;
}
CMD:setfuel(playerid, params[])
{
	new
	    id = 0,
		Float:amount;

    if (PlayerData[playerid][pAdmin] < 5)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "df", id, amount))
 	{
	 	if (IsPlayerInAnyVehicle(playerid))
		{
		    id = GetPlayerVehicleID(playerid);

		    if (sscanf(params, "f", amount))
		        return SendSyntaxMessage(playerid, "/setfuel [amount]");

			if (amount < 0)
			    return SendErrorMessage(playerid, "The amount can't be below 0.");

			VehicleData[id][vFuel] = amount;
			SendServerMessage(playerid, "You have set the fuel of vehicle ID: %d to %.2f percent.", id, amount);
			return 1;
		}
		else return SendSyntaxMessage(playerid, "/setfuel [vehicle id] [amount]");
	}
	if (!IsValidVehicle(id))
	    return SendErrorMessage(playerid, "You have specified an invalid vehicle ID.");

	if (amount < 0)
 		return SendErrorMessage(playerid, "The amount can't be below 0.");

	VehicleData[id][vFuel] = amount;
	SendServerMessage(playerid, "You have set the fuel of vehicle ID: %d to %.2f percent.", id, amount);
	return 1;
}

CMD:ahide(playerid, params[])
{
	if(PlayerData[playerid][pAdmin] < 5)
		return SendErrorMessage(playerid, NO_PERMISSION);	

	PlayerData[playerid][pAhide] = (!PlayerData[playerid][pAhide]);
	SendClientMessageEx(playerid, COLOR_LIGHTRED, "(Info) {FFFFFF}You are now %s {FFFFFF}%s the admin list.", (PlayerData[playerid][pAhide]) ? ("Hidden") : ("Visible"), (PlayerData[playerid][pAhide]) ? ("from") : ("in"));
	return 1;
}
CMD:findnumber(playerid, params[])
{
	if(PlayerData[playerid][pAdmin] < 2)
		return SendErrorMessage(playerid, NO_PERMISSION);

	if(isnull(params))
		return SendSyntaxMessage(playerid, "/findnumber [phone number]");

	if(!IsNumeric(params))
		return SendSyntaxMessage(playerid, "/findnumber [phone number]");

	new query[156];
	mysql_format(sqlcon, query, sizeof(query), "SELECT * FROM `characters` WHERE `Number` = '%d' LIMIT 1", strval(params));
	mysql_tquery(sqlcon, query, "OnFindNumber", "dd", playerid, strval(params));
	return 1;
}

CMD:findmask(playerid, params[])
{
	if(PlayerData[playerid][pAdmin] < 2)
		return SendErrorMessage(playerid, NO_PERMISSION);

	if(isnull(params))
		return SendSyntaxMessage(playerid, "/findmask [mask id]");

	if(!IsNumeric(params))
		return SendSyntaxMessage(playerid, "/findmask [mask id]");

	new query[156];
	mysql_format(sqlcon, query, sizeof(query), "SELECT * FROM `characters` WHERE `MaskID` = '%d' LIMIT 1", strval(params));
	mysql_tquery(sqlcon, query, "OnFindMask", "dd", playerid, strval(params));
	return 1;
}
CMD:checkvehicle(playerid, params[])
{
	if(PlayerData[playerid][pAdmin] < 1)
		return SendErrorMessage(playerid, NO_PERMISSION);

	new targetid; 
	if(sscanf(params, "u", targetid))
		return SendSyntaxMessage(playerid, "/checkvehicle [playerid/PartOfName]");

	if(!IsPlayerConnected(targetid))
		return SendErrorMessage(playerid, "You have specified invalid player!");

	mysql_tquery(sqlcon, sprintf("SELECT * FROM `vehicle` WHERE `vehExtraID` = '%d' ORDER BY `vehID` ASC", PlayerData[targetid][pID]), "Vehicle_AdminShowList", "dd", playerid, targetid);
	return 1;
}
CMD:gotointerior(playerid, params[])
{
	if(PlayerData[playerid][pAdmin] < 4)
		return SendErrorMessage(playerid, NO_PERMISSION);
		
    new
        str[1536];

	str[0] = '\0';

	for (new i = 0; i < sizeof(g_arrInteriorData); i ++)
	{
	    strcat(str, g_arrInteriorData[i][e_InteriorName]);
	    strcat(str, "\n");
    }
   	ShowPlayerDialog(playerid, DIALOG_INTERIOR, DIALOG_STYLE_LIST, "Teleport: Interior List", str, "Select", "Cancel");
    return 1;
}

CMD:clearitems(playerid, params[])
{
	if(PlayerData[playerid][pAdmin] < 4)
		return SendErrorMessage(playerid, NO_PERMISSION);

	new targetid;
	if(sscanf(params, "u", targetid))
		return SendSyntaxMessage(playerid, "/clearitems [playerid/PartOfName]");

	if(!IsPlayerConnected(targetid))
		return SendErrorMessage(playerid, "You have specified invalid player!");

	SendAdminMessage(COLOR_LIGHTRED, "AdmCmd: %s has cleared %s's inventory.", PlayerData[playerid][pUCP], ReturnName(targetid));
	Inventory_Clear(targetid);
	return 1;
}

CMD:aslap(playerid, params[])
{
	static
	    userid;

    if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "u", userid))
	    return SendSyntaxMessage(playerid, "/aslap [playerid/name]");

    if (!IsPlayerConnected(userid))
	    return SendErrorMessage(playerid, "You have specified an invalid player.");

	static
	    Float:x,
	    Float:y,
	    Float:z;

	GetPlayerPos(userid, x, y, z);
	SetPlayerPos(userid, x, y, z + 5);

	PlayerPlaySound(userid, 1130, 0.0, 0.0, 0.0);
	SendServerMessage(playerid, "You have slapped %s", ReturnName(userid));
	return 1;
}

CMD:destroyusername(playerid, params[])
{
	if(PlayerData[playerid][pAdmin] < 6)
		return SendErrorMessage(playerid, NO_PERMISSION);

	if(isnull(params))
		return SendSyntaxMessage(playerid, "/destroyusername [Username]");

	if(!strcmp(params, "vyn", true))
		return SendErrorMessage(playerid, "Cannot destroy this username.");

	new str[257];
	mysql_format(sqlcon, str, sizeof(str), "DELETE FROM `playerucp` WHERE `UCP` = '%s'", params);
	mysql_tquery(sqlcon, str);

	mysql_format(sqlcon, str, sizeof(str), "DELETE FROM `characters` WHERE `UCP` = '%s'", params);
	mysql_tquery(sqlcon, str);

	foreach(new i : Player) if(!strcmp(PlayerData[i][pUCP], params, true))
	{
		SendServerMessage(playerid, "Your Username has been destroyed from the server :(");
		KickEx(i);
	}

	SendAdminMessage(COLOR_LIGHTRED, "AdmCmd: %s has deleted username %s", PlayerData[playerid][pUCP], params);
	return 1;
}

CMD:rac(playerid, params[]) {
	if(PlayerData[playerid][pAdmin] < 4)
		return SendErrorMessage(playerid, NO_PERMISSION);

	SendClientMessageToAllEx(X11_TOMATO, "AdmCmd: All vehicles has been respawned by %s", GetUsername(playerid));
	for(new i = 0; i < MAX_VEHICLES; i++) if(IsValidVehicle(i)) if(!GetInsideVehicle(i)) {

		GetVehiclePos(i, VehicleData[i][vPos][0], VehicleData[i][vPos][1], VehicleData[i][vPos][2]);
		GetVehicleZAngle(i, VehicleData[i][vPos][3]);

		SetVehicleToRespawn(i);

		if(Vehicle_GetType(i) == VEHICLE_TYPE_PLAYER) {

			SetVehiclePos(i, VehicleData[i][vPos][0], VehicleData[i][vPos][1], VehicleData[i][vPos][2]);
			SetVehicleZAngle(i, VehicleData[i][vPos][3]);
		}
	}
	return 1;
}

CMD:respawnveh(playerid, params[])
{
	if(PlayerData[playerid][pAdmin] < 4)
		return SendErrorMessage(playerid, NO_PERMISSION);

	if(isnull(params))
		return SendSyntaxMessage(playerid, "/respawnveh [vehicle id OR stock vehicle]"), SendClientMessage(playerid, COLOR_YELLOW, "stock Vehicle: {FFFFFF}sidejob");

	if(IsNumeric(params))
	{
		new vehicleid = strval(params);
		if(vehicleid == INVALID_VEHICLE_ID)
			return SendErrorMessage(playerid, "You have specified invalid vehicle id");

		if(!IsValidVehicle(vehicleid))
			return SendErrorMessage(playerid, "You have specified invalid vehicle id");

		RespawnVehicle(vehicleid);
		SendServerMessage(playerid, "You have respawned vehicle id %d", vehicleid);
	}
	else
	{
		if(!strcmp(params, "sidejob", true))
		{
			for(new i = 0; i < MAX_VEHICLES; i++) if(IsValidVehicle(i) && GetVehicleDriver(i) == INVALID_PLAYER_ID)
			{
				SetVehicleToRespawn(i);
				VehicleData[i][vFuel] = 10.0;
				RepairVehicle(i);
			}
			SendAdminMessage(COLOR_LIGHTRED, "AdmCmd: All Sidejob vehicle has been respawned by %s", PlayerData[playerid][pUCP]);
		}

	}
	return 1;
}

CMD:givesalary(playerid, params[])
{
	if(PlayerData[playerid][pAdmin] < 6)
		return SendErrorMessage(playerid, NO_PERMISSION);

	new targetid, amount[32], reason[32];
	if(sscanf(params, "us[32]s[32]", targetid, amount, reason))
		return SendSyntaxMessage(playerid, "/givesalary [playerid/PartOfName] [amount] [reason]");

	if(!IsPlayerConnected(targetid))
		return SendErrorMessage(playerid, "Invalid player specified!");

	if(targetid == playerid && PlayerData[playerid][pAdmin] < 7)
		return SendErrorMessage(playerid, "You can't give to yourself!");

	if(strcash(amount) < 1)
		return SendErrorMessage(playerid, "Invalid aamount of salary.");

	AddSalary(targetid, reason, strcash(amount));
	SendAdminMessage(COLOR_LIGHTRED, "AdmCmd: %s has given $%s salary to %s", PlayerData[playerid][pUCP], FormatNumber(strcash(amount)), GetName(targetid));
	SendClientMessageEx(targetid, X11_LIGHTBLUE, "(Salary): "WHITE"Kamu telah diberikan salary sebesar "GREEN"$%s "WHITE"oleh "RED"%s", FormatNumber(strcash(amount)), GetUsername(playerid));
	return 1;
}
CMD:setname(playerid, params[])
{
	static
	    userid,
	    newname[24];

    if (PlayerData[playerid][pAdmin] < 5)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "us[24]", userid, newname))
	    return SendSyntaxMessage(playerid, "/setname [playerid/PartOfName] [new name]");

	if (!IsPlayerConnected(userid))
		return SendErrorMessage(playerid, "You have specified an invalid player.");

	if (!IsRoleplayName(newname))
	    return SendErrorMessage(playerid, "You have specified an invalid name format.");

	foreach (new i : Player) if (!strcmp(GetName(i), newname))
	{
	    SendErrorMessage(playerid, "The specified name is in use.");
		return 1;
	}

	mysql_tquery(sqlcon, sprintf("SELECT * FROM `characters` WHERE `Name` = '%s'", newname), "OnAdminSetName", "dds", playerid, userid, newname);
	return 1;
}

CMD:fixveh(playerid, params[])
{
    new vehicleid = GetPlayerVehicleID(playerid);

	if (PlayerData[playerid][pAdmin] < 4)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (vehicleid > 0 && isnull(params))
	{
		RepairVehicle(vehicleid);
		SendServerMessage(playerid, "You have repaired your current vehicle.");

		SetVehicleHealth(vehicleid, (VehicleData[vehicleid][vEngineUpgrade] + 1) * 1000.0);
	}
	else
	{
		if (sscanf(params, "d", vehicleid))
	    	return SendSyntaxMessage(playerid, "/fixveh [vehicle ID]");

		else if (!IsValidVehicle(vehicleid))
	    	return SendErrorMessage(playerid, "You have specified an invalid vehicle ID.");

		RepairVehicle(vehicleid);
		SendServerMessage(playerid, "You have repaired vehicle ID: %d.", vehicleid);

		SetVehicleHealth(vehicleid, (VehicleData[vehicleid][vEngineUpgrade] + 1) * 1000.0);
	}
	return 1;
}

CMD:givewep(playerid, params[])
{
	new
	    userid,
	    weaponid,
	    ammo,
		highvelo;

    if (PlayerData[playerid][pAdmin] < 5)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "udI(100)I(0)", userid, weaponid, ammo, highvelo))
	    return SendSyntaxMessage(playerid, "/givewep [playerid/PartOfName] [weaponid] [ammo] [high velocity (0/1)]");

	if (!IsPlayerConnected(userid))
	    return SendErrorMessage(playerid, "You cannot give weapons to disconnected players.");

	if (weaponid <= 0 || weaponid > 46 || (weaponid >= 19 && weaponid <= 21))
		return SendErrorMessage(playerid, "You have specified an invalid weapon.");
	    
	GiveWeaponToPlayer(userid, weaponid, ammo, 500, highvelo);
	SendServerMessage(playerid, "You have gave %s weapon id %d with %d ammo.", ReturnName(userid), weaponid, ammo);
	return 1;
}

CMD:spec(playerid, params[])
{
	new userid;

	if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "u", userid))
		return SendSyntaxMessage(playerid, "/spec(tate) [playerid/PartOfName] - Type \"/unspec\" to stop spectating.");

	if (!IsPlayerConnected(userid))
	    return SendErrorMessage(playerid, "You have specified an invalid player.");

	    
	if (GetPlayerState(playerid) != PLAYER_STATE_SPECTATING)
	{
		GetPlayerPos(playerid, PlayerData[playerid][sPos][0], PlayerData[playerid][sPos][1], PlayerData[playerid][sPos][2]);

		PlayerData[playerid][pInterior] = GetPlayerInterior(playerid);
		PlayerData[playerid][pWorld] = GetPlayerVirtualWorld(playerid);
	}
	SetPlayerInterior(playerid, GetPlayerInterior(userid));
	SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(userid));

	TogglePlayerSpectating(playerid, 1);

	if (IsPlayerInAnyVehicle(userid))
	    PlayerSpectateVehicle(playerid, GetPlayerVehicleID(userid));

	else
		PlayerSpectatePlayer(playerid, userid);

	SendServerMessage(playerid, "You are now spectating "YELLOW"%s (ID: %d).", GetName(userid), userid);
	PlayerData[playerid][pSpectator] = userid;

	if(PlayerData[playerid][pAdmin] <= PlayerData[userid][pAdmin] && PlayerData[userid][pAdmin] > 6)
		SendClientMessageEx(userid, X11_GREY, "You are being spectated by "YELLOW"%s"GREY".", GetUsername(playerid));
	return 1;
}


CMD:gotoco(playerid, params[])
{
	if(PlayerData[playerid][pAdmin] >= 2)
	{
		new Float: pos[3], int;
		if(sscanf(params, "fffd", pos[0], pos[1], pos[2], int))
			return SendSyntaxMessage(playerid, "USAGE: /gotoco [x coordinate] [y coordinate] [z coordinate] [interior]");

		SendClientMessage(playerid, COLOR_WHITE, "You have been teleported to the coordinates specified.");
		SetPlayerPos(playerid, pos[0], pos[1], pos[2]);
		SetPlayerInterior(playerid, int);
	}
	return 1;
}

CMD:veh(playerid, params[])
{
	new
	    model[32],
		color1,
		color2;

	if(PlayerData[playerid][pAdmin] < 4)
		return SendErrorMessage(playerid, NO_PERMISSION);

	if (sscanf(params, "s[32]I(-1)I(-1)", model, color1, color2))
	    return SendSyntaxMessage(playerid, "/veh [model id/name] <color 1> <color 2>");

	if ((model[0] = GetVehicleModelByName(model)) == 0)
	    return SendErrorMessage(playerid, "Invalid model ID.");

	new
	    Float:x,
	    Float:y,
	    Float:z,
	    Float:a,
		vehicleid;

	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, a);

	vehicleid = Vehicle_Create(model[0], x, y + 2, z, a, color1, color2, 0);

	if (GetPlayerInterior(playerid) != 0)
	    SetVehicleInterior(vehicleid, GetPlayerInterior(playerid));

	if (GetPlayerVirtualWorld(playerid) != 0)
		SetVehicleVirtualWorld(vehicleid, GetPlayerVirtualWorld(playerid));

	PutPlayerInVehicle(playerid, vehicleid, 0);
	SwitchVehicleEngine(vehicleid, true);
	VehicleData[vehicleid][vFuel] = 10.0;
	Vehicle_SetType(vehicleid, VEHICLE_TYPE_ADMIN);

	SendServerMessage(playerid, "You have spawned a %s (ID:%d).", ReturnVehicleModelName(model[0]), vehicleid);
	return 1;
}

CMD:unspec(playerid, params[])
{
	if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");
	    
    if (GetPlayerState(playerid) != PLAYER_STATE_SPECTATING)
		return SendErrorMessage(playerid, "You are not spectating any player.");

	PlayerData[playerid][pSpectator] = INVALID_PLAYER_ID;
    PlayerSpectatePlayer(playerid, INVALID_PLAYER_ID);
    PlayerSpectateVehicle(playerid, INVALID_VEHICLE_ID);

    SetSpawnInfo(playerid, 0, PlayerData[playerid][pSkin], PlayerData[playerid][sPos][0], PlayerData[playerid][sPos][1], PlayerData[playerid][sPos][2], 0, 0, 0, 0, 0, 0, 0);
    TogglePlayerSpectating(playerid, false);
	SetPlayerVirtualWorld(playerid, PlayerData[playerid][pWorld]);
	SetPlayerInterior(playerid, PlayerData[playerid][pInterior]);
    SendServerMessage(playerid, "You are no longer in spectator mode.");
    SetValidColor(playerid);

	TogglePlayerControllable(playerid, true);
    return 1;
}

CMD:amm(playerid, paramsp[]) {

	if(PlayerData[playerid][pAdmin] < 6)
		return PermissionError(playerid);

	new vehicleid = INVALID_VEHICLE_ID, string[352];

	if((vehicleid = GetNearestVehicle(playerid, 7.0)) != INVALID_VEHICLE_ID) {
		format(string, sizeof(string), "Repair Engine\nRepair Body\nRepair Tire\nChange Color\nTune Vehicle\nSet Paintjob\nInstall Nitro\nUninstall Modification\nUpgrade Engine\nUpgrade Body\nOctane Saver\nInstall Neon");
		ShowPlayerDialog(playerid, DIALOG_MM, DIALOG_STYLE_LIST, "Vehicle Menu", string, "Select", "Close");

		PlayerData[playerid][pVehicle] = vehicleid;
	}
	else SendErrorMessage(playerid, "You are not in range of any vehicle.");

	return 1;
}

CMD:editplayer(playerid, params[])
{
	if (PlayerData[playerid][pAdmin] < 6)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	new
	    userid,
	    type[16],
	    amount[32],
	    val[32];

	if (sscanf(params, "us[16]S()[32]", userid, type, amount))
 	{
	 	SendSyntaxMessage(playerid, "/editplayer [playerid/PartOfName] [name]");
	 	SendClientMessage(playerid, COLOR_YELLOW, "(Names){FFFFFF} gender, bank, origin, level, birthdate, lumberlic, job(1/2)");
		return 1;
	}
	if (!IsPlayerConnected(userid))
	    return SendErrorMessage(playerid, "You have specified an invalid player.");

	if (!strcmp(type, "gender", true))
	{
	    if (isnull(amount) || strval(amount) < 1 || strval(amount) > 2)
	        return SendSyntaxMessage(playerid, "/editplayer [playerid/PartOfName] [gender] [1: male - 2: female]");

		PlayerData[userid][pGender] = strval(amount);

		SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Gender) "WHITE"You have changed "YELLOW"%s's "WHITE"gender to "CYAN"%s", GetName(userid, false), (PlayerData[userid][pGender] == 1) ? ("Male") : ("Female"));
	}
	else if(!strcmp(type, "job1", true)) 
	{
	    if (isnull(amount) || strval(amount) < JOB_NONE || strval(amount) > JOB_FARMER)
	        return SendSyntaxMessage(playerid, "/editplayer [playerid/PartOfName] [job1]");

		SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Job 1) "WHITE"You have changed "YELLOW"%s's "WHITE"job to "CYAN"%s", GetName(userid, false), GetJobName(strval(amount)));
		PlayerData[userid][pJob] = strval(amount);
	}
	else if(!strcmp(type, "job2", true)) 
	{
	    if (isnull(amount) || strval(amount) < JOB_NONE || strval(amount) > JOB_FARMER)
	        return SendSyntaxMessage(playerid, "/editplayer [playerid/PartOfName] [job2]");

		SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Job 2) "WHITE"You have changed "YELLOW"%s's "WHITE"job to "CYAN"%s", GetName(userid, false), GetJobName(strval(amount)));
		PlayerData[userid][pJob2] = strval(amount);
	}
	else if (!strcmp(type, "birthdate", true))
	{
	    if (isnull(amount) || strlen(amount) > 24)
	        return SendSyntaxMessage(playerid, "/editplayer [playerid/PartOfName] [birthdate] [new birthdate]");

		format(PlayerData[userid][pBirthdate], 24, amount);
		SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Birthdate) "WHITE"You have changed "YELLOW"%s's "WHITE"birthdate to "CYAN"%s", GetName(userid), amount);
	}
	else if (!strcmp(type, "origin", true))
	{
	    if (isnull(amount) || strlen(amount) > 32)
	        return SendSyntaxMessage(playerid, "/editplayer [playerid/PartOfName] [origin] [new origin]");

		format(PlayerData[userid][pOrigin], 32, amount);
		SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Origin) "WHITE"You have changed "YELLOW"%s's "WHITE"origin to "CYAN"%s", GetName(userid, false), amount);
	}
	else if (!strcmp(type, "bank", true))
	{
		if (PlayerData[playerid][pAdmin] < 7)
		    return SendErrorMessage(playerid, "This option only for Management.");
		    
	    if (sscanf(amount, "s[32]", val))
	        return SendSyntaxMessage(playerid, "/editplayer [playerid/PartOfName] [bank] [bank funds]");

		PlayerData[userid][pBank] = strcash(val);
		SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Bank) "WHITE"You have changed "YELLOW"%s's "WHITE"bank money to "GREEN"$%s", GetName(userid, false), FormatNumber(strcash(val)));
	}
	else if (!strcmp(type, "level", true))
	{
	    if (isnull(amount))
	        return SendSyntaxMessage(playerid, "/editplayer [playerid/PartOfName] [level] [amount]");

		PlayerData[userid][pLevel] = strval(amount);
		SetPlayerScore(userid, PlayerData[userid][pLevel]);
		SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Level) "WHITE"You have changed "YELLOW"%s's "WHITE"level to "CYAN"%d", GetName(userid, false), strval(amount));
	}
	else if(!strcmp(type, "lumberlic", true)) {

		PlayerData[userid][pLicense][2] = !(PlayerData[userid][pLicense][2]);
		SendAdminMessage(X11_TOMATO, "AdmCmd: %s has %s %s's lumberjack license.", GetUsername(playerid), (PlayerData[userid][pLicense][2]) ? ("set") : ("unset"), GetName(userid, false));
	}
	return 1;
}

CMD:preloadserverdata(playerid, params[]) {

	if(PlayerData[playerid][pAdmin] < 6)
		return SendErrorMessage(playerid, "You don't have authorized to use this command!");

	LoadServerData();
	SendAdminAction(playerid, "You have preloaded server data.");
	return 1;
}
CMD:addinsu(playerid, params[]) {

	if(PlayerData[playerid][pAdmin] < 6)
		return SendErrorMessage(playerid, "You don't have authorized to use this command!");

	if(isnull(params))
		return SendSyntaxMessage(playerid, "/addinsu [vehicle id]");

	if(strval(params) == INVALID_VEHICLE_ID)
		return SendErrorMessage(playerid, "You have specified invalid vehicle id");

	new vehicleid = strval(params);

	if(!Iter_Contains(Vehicle, vehicleid))
		return SendErrorMessage(playerid, "You have specified invalid vehicle id");

	if(VehicleData[vehicleid][vExtraID] != -1 && Vehicle_GetType(vehicleid) == VEHICLE_TYPE_PLAYER)
	{
		VehicleData[vehicleid][vInsurance]++;
		SendAdminAction(playerid, "Kamu telah menambahkan 1 insurance ke kendaraan %s.", GetVehicleName(vehicleid));
	}
	else
		SendErrorMessage(playerid, "Invalid player vehicle!");
	
	return 1;
}


CMD:destroycar(playerid, params[])
{
	if(PlayerData[playerid][pAdmin] < 6)
		return SendErrorMessage(playerid, "You don't have authorized to use this command!");

	if(isnull(params))
		return SendSyntaxMessage(playerid, "/destroycar [vehicle id]");

	if(strval(params) == INVALID_VEHICLE_ID)
		return SendErrorMessage(playerid, "You have specified invalid vehicle id");

	new vehicleid = strval(params);

	if(!Iter_Contains(Vehicle, vehicleid))
		return SendErrorMessage(playerid, "You have specified invalid vehicle id");

	if(VehicleData[vehicleid][vExtraID] != -1 && Vehicle_GetType(vehicleid) == VEHICLE_TYPE_PLAYER || Vehicle_GetType(vehicleid) == VEHICLE_TYPE_RENTAL)
	{
		SendAdminMessage(COLOR_LIGHTRED, "AdmCmd: %s has destroyed player vehicle with Database ID: %d", PlayerData[playerid][pUCP], VehicleData[vehicleid][vID]);

		Vehicle_Delete(vehicleid, true);
	}
	else
		SendErrorMessage(playerid, "Invalid player vehicle!");
	
	return 1;
}
CMD:createcar(playerid, params[])
{
	if(PlayerData[playerid][pAdmin] < 6)
		return SendErrorMessage(playerid, "You don't have authorized to use this command!");

    new
        model[32],
        color1,
        color2,
        otherid;

    if (sscanf(params, "us[32]I(-1)I(-1)", otherid, model, color1, color2))
        return SendSyntaxMessage(playerid, "/createcar [playerid/PartOfName] [model id/name] <color 1> <color 2>");
		
	if(otherid == INVALID_PLAYER_ID)
		return SendErrorMessage(playerid, "You have specified invalid player!");

    if ((model[0] = GetVehicleModelByName(model)) == 0)
        return SendErrorMessage(playerid, "Invalid model ID.");
		
	new Float:pos[4];
	GetPlayerPos(otherid, pos[0], pos[1], pos[2]);
	GetPlayerFacingAngle(otherid, pos[3]);
    new vehicleid = Vehicle_Create(model[0], pos[0], pos[1], pos[2], pos[3], color1, color2, 0, true);
	
	Vehicle_SetOwner(vehicleid, otherid, true);
	Vehicle_SetType(vehicleid, VEHICLE_TYPE_PLAYER);
    SendAdminAction(playerid, "You have created %s for %s.", ReturnVehicleModelName(model[0]), GetName(otherid, false));
	Log_Write("Logs/adminaction.txt", "[%s] %s created a %s for %s(%s)", GetUsername(playerid), ReturnVehicleModelName(model[0]), GetName(otherid, false), GetUsername(otherid));
	return 1;
}

CMD:customplate(playerid, params[]) {
	if(PlayerData[playerid][pAdmin] < 6)
		return SendErrorMessage(playerid, NO_PERMISSION);

	new vehicleid, plate[16];

	if(sscanf(params, "ds[16]", vehicleid, plate))
		return SendSyntaxMessage(playerid, "/customplate [vehicleid] [new plate] (Note: plate max 9 char)");


	if(!Iter_Contains(Vehicle, vehicleid))
		return SendErrorMessage(playerid, "You have specified invalid vehicle.");


	if(Vehicle_GetType(vehicleid) != VEHICLE_TYPE_PLAYER)
		return SendErrorMessage(playerid, "You only can do to player vehicle.");

	if(strlen(plate) > 16)
		return SendErrorMessage(playerid, "Invalid length.");

	format(VehicleData[vehicleid][vPlate], 16, plate);
	SetVehicleNumberPlate(vehicleid, plate);
	Vehicle_Save(vehicleid);

	SendAdminAction(playerid, "You have changed plate vehicleid %d to %s.", vehicleid, plate);
	return 1;
}
CMD:togooc(playerid, paramas[])
{
	if(PlayerData[playerid][pAdmin] < 4)
	    return SendErrorMessage(playerid, NO_PERMISSION);
	    
	if(!ToggleData[togOOC])
	{
	    ToggleData[togOOC] = true;
	    SendClientMessageToAllEx(X11_YELLOW, "[OOC] Global OOC chat has been disabled by %s.", PlayerData[playerid][pUCP]);
	}
	else
	{
		ToggleData[togOOC] = false;
		SendClientMessageToAllEx(X11_YELLOW, "[OOC] Global OOC chat has been enabled by %s.", PlayerData[playerid][pUCP]);
	}
	return 1;
}


CMD:setint(playerid, params[])
{
	static
		userid,
	    interior;

	if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "ud", userid, interior))
		return SendSyntaxMessage(playerid, "/setint [playerid/PartOfName] [interior]");

	if (!IsPlayerConnected(userid))
	    return SendErrorMessage(playerid, "You have specified an invalid player.");

	SetPlayerInterior(userid, interior);
	PlayerData[userid][pInterior] = interior;

	SendServerMessage(playerid, "You have set %s's interior to %d.", ReturnName(userid), interior);
	return 1;
}

CMD:setvw(playerid, params[])
{
	static
		userid,
	    world;

	if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "ud", userid, world))
		return SendSyntaxMessage(playerid, "/setvw [playerid/PartOfName] [world]");

	if (!IsPlayerConnected(userid))
	    return SendErrorMessage(playerid, "You have specified an invalid player.");

	SetPlayerVirtualWorld(userid, world);
	PlayerData[userid][pWorld] = world;

	SendServerMessage(playerid, "You have set %s's virtual world to %d.", ReturnName(userid), world);
	return 1;
}

CMD:freeze(playerid, params[])
{
	static
	    userid;

    if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "u", userid))
	    return SendSyntaxMessage(playerid, "/freeze [playerid/PartOfName]");

    if (!IsPlayerConnected(userid))
	    return SendErrorMessage(playerid, "You have specified an invalid player.");

	TogglePlayerControllable(userid, 0);
	SendServerMessage(playerid, "You have frozen %s's movements.", ReturnName(userid));
	return 1;
}

CMD:unfreeze(playerid, params[])
{
	static
	    userid;

    if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "u", userid))
	    return SendSyntaxMessage(playerid, "/unfreeze [playerid/PartOfName]");

    if (!IsPlayerConnected(userid))
	    return SendErrorMessage(playerid, "You have specified an invalid player.");


	TogglePlayerControllable(userid, 1);
	SendServerMessage(playerid, "You have unfrozen %s's movements.", ReturnName(userid));
	return 1;
}

CMD:gotoloc(playerid, params[])
{
    if (PlayerData[playerid][pAdmin] < 4)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");	

	new type[24], string[128], id;
	if(sscanf(params, "s[24]S()[128]", type, string))
		return SendSyntaxMessage(playerid, "/gotoloc [house/biz/dealer/door/workshop/houseint]");

	new str[1512];
	if(!strcmp(type, "house", true))
	{	
		if(sscanf(string, "d", id))
			return SendSyntaxMessage(playerid, "/gotoloc house [house id]");

		if(!Iter_Contains(House, id))
			return SendErrorMessage(playerid, "Invalid house id!");

		SetPlayerPos(playerid, HouseData[id][housePos][0], HouseData[id][housePos][1], HouseData[id][housePos][2]);
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
	}
	else if(!strcmp(type, "biz", true))
	{
		if(sscanf(string, "d", id))
			return SendSyntaxMessage(playerid, "/gotoloc biz [biz id]");

		if(!BizData[id][bizExists])
			return SendErrorMessage(playerid, "Invalid business id!");

		SetPlayerPos(playerid, BizData[id][bizExt][0], BizData[id][bizExt][1], BizData[id][bizExt][2]);
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
	}
	else if(!strcmp(type, "dealer", true))
	{
		if(sscanf(string, "d", id))
			return SendSyntaxMessage(playerid, "/gotoloc dealer [dealer id]");

		if(!DealerData[id][dealerExists])
			return SendErrorMessage(playerid, "Invalid dealer id!");

		SetPlayerPos(playerid, DealerData[id][dealerPos][0], DealerData[id][dealerPos][1], DealerData[id][dealerPos][2]);
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
	}
	else if(!strcmp(type, "door", true))
	{
		if(sscanf(string, "d", id))
			return SendSyntaxMessage(playerid, "/gotoloc door [door id]");

		if(!Iter_Contains(Doors, id))
			return SendErrorMessage(playerid, "Invalid door id!");

		SetPlayerPos(playerid, drData[id][dExtposX], drData[id][dExtposY], drData[id][dExtposZ]);
		SetPlayerInterior(playerid, drData[id][dExtvw]);
		SetPlayerVirtualWorld(playerid, drData[id][dExtint]);		
	}
	else if(!strcmp(type, "flat", true))
	{
		if(sscanf(string, "d", id))
			return SendSyntaxMessage(playerid, "/gotoloc flat [flat id]");

		if(!Iter_Contains(Flat, id))
			return SendErrorMessage(playerid, "Invalid flat id!");

		SetPlayerPos(playerid, FlatData[id][flatPos][0], FlatData[id][flatPos][1], FlatData[id][flatPos][2]);
		SetPlayerInterior(playerid, FlatData[id][flatExtInterior]);
		SetPlayerVirtualWorld(playerid, FlatData[id][flatExtWorld]);	
	}
	else if(!strcmp(type, "houseint", true))
	{
		format(str, sizeof(str), "#\tInterior Name\n");

		for(new i; i < sizeof(arrHouseInteriors); i++)
			format(str, sizeof(str), "%s%d\t%s\n", str, i, arrHouseInteriors[i][eHouseDesc]);

		ShowPlayerDialog(playerid, DIALOG_GOTOLOC_HOUSEINT, DIALOG_STYLE_TABLIST_HEADERS, "House Interior", str, "Teleport", "Close");
	}
	else if(!strcmp(type, "workshop", true)) {
		if(sscanf(string, "d", id))
			return SendSyntaxMessage(playerid, "/gotoloc workshop [workshop id]");

		if(!Iter_Contains(Workshop, id))
			return SendErrorMessage(playerid, "Invalid workshop ID");

		SetPlayerPos(playerid, WorkshopData[id][wsFootPos][0], WorkshopData[id][wsFootPos][1], WorkshopData[id][wsFootPos][2]);
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);		
	}
	return 1;
}
CMD:executequery(playerid, params[]) {

	if(PlayerData[playerid][pAdmin] < 7)
		return PermissionError(playerid);

	ShowPlayerDialog(playerid, DIALOG_EXECUTE, DIALOG_STYLE_INPUT, "Execute Query", "Please specify the MySQL query to execute below:", "Execute", "Back");
	return 1;
}
CMD:destroyveh(playerid, params[])
{
    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");
	    
	new vehicleid = GetPlayerVehicleID(playerid);

	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		return SendErrorMessage(playerid, "You must be inside temporary vehicle!");
		
	if(Vehicle_GetType(vehicleid) != VEHICLE_TYPE_ADMIN)
	    return SendErrorMessage(playerid, "You only can destroy temporary vehicle!");
	    
	SendServerMessage(playerid, "You've destroyed temporary vehicle ID: %d", vehicleid);
	Vehicle_Delete(vehicleid, false);
	return 1;
}


CMD:aweapon(playerid, params[])
{
	if (PlayerData[playerid][pAdmin] < 3)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");
	    
	new targetid;
	if(sscanf(params, "u", targetid))
	    return SendSyntaxMessage(playerid, "/aweapon [playerid/PartOfName]");
	    
	if(!IsPlayerConnected(targetid))
	    return SendErrorMessage(playerid, "You've specified an You have specified invalid player!");
	    
	ShowWeapon(playerid, targetid);
	return 1;
}

CMD:afrisk(playerid, params[])
{
	if (PlayerData[playerid][pAdmin] < 3)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");
	    
	new targetid;
	if(sscanf(params, "u", targetid))
	    return SendSyntaxMessage(playerid, "/afrisk [playerid/PartOfName]");
	    
	if(!IsPlayerConnected(targetid))
	    return SendErrorMessage(playerid, "You've specified an You have specified invalid player!");
	    
	ShowInventory(playerid, targetid);
	return 1;
}


CMD:gentercar(playerid, params[])
{
	new vehicleid, seatid, Float:x, Float:y, Float:z;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "d", vehicleid))
	    return SendSyntaxMessage(playerid, "/entercar [veh]");

	if (vehicleid < 1 || vehicleid > MAX_VEHICLES || !IsValidVehicle(vehicleid))
		return SendErrorMessage(playerid, "You have specified an invalid vehicle ID.");

	seatid = GetAvailableSeat(vehicleid, 0);

	if (seatid == -1)
	    return SendErrorMessage(playerid, "There are no seats left to enter.");

	GetPlayerPos(playerid, x, y, z);
	SetVehiclePos(vehicleid, x, y, z);
	SetVehicleVirtualWorld(vehicleid, GetPlayerVirtualWorld(playerid));
	SetVehicleInterior(vehicleid, GetPlayerInterior(playerid));
	
	PutPlayerInVehicle(playerid, vehicleid, seatid);
	return 1;
}

CMD:entercar(playerid, params[])
{
	new vehicleid, seatid;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "d", vehicleid))
	    return SendSyntaxMessage(playerid, "/entercar [veh]");

	if (vehicleid < 1 || vehicleid > MAX_VEHICLES || !IsValidVehicle(vehicleid))
		return SendErrorMessage(playerid, "You have specified an invalid vehicle ID.");

	seatid = GetAvailableSeat(vehicleid, 0);

	if (seatid == -1)
	    return SendErrorMessage(playerid, "There are no seats left to enter.");

	PutPlayerInVehicle(playerid, vehicleid, seatid);
	return 1;
}


CMD:gotocar(playerid, params[])
{
	new vehicleid;

    if (PlayerData[playerid][pAdmin] < 3)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "d", vehicleid))
	    return SendSyntaxMessage(playerid, "/gotocar [veh]");

	if (vehicleid < 1 || vehicleid > MAX_VEHICLES || !IsValidVehicle(vehicleid))
		return SendErrorMessage(playerid, "You have specified an invalid vehicle ID.");

	static
	    Float:x,
	    Float:y,
	    Float:z;

	GetVehiclePos(vehicleid, x, y, z);
	SetPlayerPos(playerid, x, y - 2, z + 2);
	return 1;
}

CMD:vehinfo(playerid, params[]) {

	if(PlayerData[playerid][pAdmin] < 3)
	    return SendErrorMessage(playerid, NO_PERMISSION);

	new vehicleid;
	if(sscanf(params, "d", vehicleid))
		return SendSyntaxMessage(playerid, "/vehinfo [vehicleid]");

	if(vehicleid == INVALID_VEHICLE_ID)
		return SendErrorMessage(playerid, "Invalid specified Vehicle id!");

	if(!IsValidVehicle(vehicleid))
		return SendErrorMessage(playerid, "Invalid specified Vehicle id!");

	if(!Iter_Contains(Vehicle, vehicleid))
		return SendErrorMessage(playerid, "Specified vehicle is not registered as a valid server veh.");

	if(Vehicle_GetType(vehicleid) != VEHICLE_TYPE_PLAYER)
		return SendErrorMessage(playerid, "Vehicle %d is not a Player vehicle.", vehicleid);

	SendClientMessageEx(playerid, X11_YELLOW, "[VID:%d] "WHITE"Owner: %s | Model: %s | Plate: %s | Engine: %s", VehicleData[vehicleid][vID], GetNameFromSQLID(VehicleData[vehicleid][vExtraID]), GetVehicleName(vehicleid), VehicleData[vehicleid][vPlate], (GetEngineStatus(vehicleid)) ? ("On") : ("Off"));
	return 1;
}


CMD:getcar(playerid, params[])
{
	if(PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, NO_PERMISSION);
	    
	new vehicleid;
	if(sscanf(params, "d", vehicleid))
	    return SendSyntaxMessage(playerid, "/getcar [vehicle id]");
	    
	if(vehicleid == INVALID_VEHICLE_ID)
		return SendErrorMessage(playerid, "Invalid specified Vehicle id!");

	if(!IsValidVehicle(vehicleid))
		return SendErrorMessage(playerid, "Invalid specified Vehicle id!");

	new Float:Pos[3];
	GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
	SetVehiclePos(vehicleid, Pos[0], Pos[1], Pos[2]);
	SetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]+1.5);
	SetVehicleInterior(vehicleid, GetPlayerInterior(playerid));
	SetVehicleVirtualWorld(vehicleid, GetPlayerVirtualWorld(playerid));
	return 1;
}


CMD:checkstats(playerid, params[])
{
	if(PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, NO_PERMISSION);

	new targetid;
	if(sscanf(params, "u", targetid))
		return SendSyntaxMessage(playerid, "/checkstats [playerid/PartOfName]");

	if(!IsPlayerConnected(targetid))
		return SendErrorMessage(playerid, "Invalid player specified!");

	ShowPlayerStats(targetid, playerid);
	return 1;
}
CMD:mark(playerid, params[])
{
	if(PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, NO_PERMISSION);

	if(isnull(params))
		return SendSyntaxMessage(playerid, "/mark [set/goto]");

	if(!strcmp(params, "set", true))
	{
		SendClientMessageEx(playerid, COLOR_LIGHTRED, "(Mark) {FFFFFF}Mark successfully {FFFF00}Activated{FFFFFF} use {FFFF00}/mark goto {FFFFFF}to teleport");
		GetPlayerPos(playerid, PlayerData[playerid][pMark][0], PlayerData[playerid][pMark][1], PlayerData[playerid][pMark][2]);
		PlayerData[playerid][pMarkWorld] = GetPlayerVirtualWorld(playerid);
		PlayerData[playerid][pMarkInterior] = GetPlayerInterior(playerid);
		PlayerData[playerid][pMarkActive] = true;
	}
	else if(!strcmp(params, "goto", true))
	{
		if(!PlayerData[playerid][pMarkActive])
			return SendErrorMessage(playerid, "Kamu belum mengaktifkan Mark!");

		SetPlayerPos(playerid, PlayerData[playerid][pMark][0], PlayerData[playerid][pMark][1], PlayerData[playerid][pMark][2]);
		SetPlayerInterior(playerid, PlayerData[playerid][pMarkInterior]);
		SetPlayerVirtualWorld(playerid, PlayerData[playerid][pMarkWorld]);
	}
	return 1;
}
CMD:setadmin(playerid, params[])
{
	new rank, targetid, query[256];
	if(PlayerData[playerid][pAdmin] < 7)
	    return SendErrorMessage(playerid, NO_PERMISSION);
	    
	if(sscanf(params, "ud", targetid, rank))
	    return SendSyntaxMessage(playerid, "/setadmin [playerid/PartOfName] [rank]");
	    
	if(!IsPlayerConnected(targetid))
	    return SendErrorMessage(playerid, "You've specified an invalid player!");
	    
	UcpData[targetid][ucpAdmin] = rank;
	PlayerData[targetid][pAdmin] = UcpData[targetid][ucpAdmin];
	SendAdminMessage(COLOR_LIGHTRED, "AdmCmd: %s has adjusted %s admin level to %d", PlayerData[playerid][pUCP], GetName(targetid), rank);
	SendServerMessage(targetid, "Your admin level has been adjusted by %s to %d", PlayerData[playerid][pUCP], rank);
	mysql_format(sqlcon,query,sizeof(query),"UPDATE `playerucp` SET `Admin` = '%d' WHERE `UCP` = '%e'", rank, PlayerData[targetid][pUCP]);
	mysql_tquery(sqlcon,query);
	return 1;
}

CMD:countdynamic(playerid, params[]) {
	if(PlayerData[playerid][pAdmin] < 7)
		return SendErrorMessage(playerid, NO_PERMISSION);

	SendClientMessageEx(playerid, -1, "Object: %d", CountDynamicObjects());
	SendClientMessageEx(playerid, -1, "3D Text Label: %d", CountDynamic3DTextLabels());
	SendClientMessageEx(playerid, -1, "Pickup: %d", CountDynamicPickups());
	SendClientMessageEx(playerid, -1, "Area: %d", CountDynamicAreas());
	SendClientMessageEx(playerid, -1, "CP: %d", CountDynamicCPs());

	return 1;
}
CMD:unjail(playerid, params[])
{
	if(PlayerData[playerid][pAdmin] < 1)
		return SendErrorMessage(playerid, NO_PERMISSION);

	new targetid;
	if(sscanf(params, "u", targetid))
	    return SendSyntaxMessage(playerid, "/unjail [playerid/PartOfName]");

	if(!IsPlayerConnected(targetid))
	    return SendErrorMessage(playerid, "You have specified invalid player!");

	if(PlayerData[targetid][pJailTime] < 1)
	    return SendErrorMessage(playerid, "That player is not jailed!");

	if(PlayerData[targetid][pArrest])
	    return SendErrorMessage(playerid, "You can't release Prisoned Player! (IC Jail)");

	PlayerData[targetid][pJailTime] = 0;
	PlayerTextDrawHide(targetid, JAILTD[targetid]);
	SendClientMessageToAllEx(COLOR_LIGHTRED, "AdmCmd: %s has been released from admin jail by %s", GetName(targetid), PlayerData[playerid][pUCP]);
	SetPlayerPos(targetid, -2450.5044,503.7565,30.0853);
	SetPlayerInterior(targetid, 0);
	SetPlayerVirtualWorld(targetid, 0);
	TogglePlayerControllable(targetid, 1);
	return 1;
}

CMD:setcarhp(playerid, params[])
{
    if (PlayerData[playerid][pAdmin] < 4)
        return PermissionError(playerid);

    static
        id = 0,
        Float:amount;

    if(sscanf(params, "df", id, amount))
    {
        if(IsPlayerInAnyVehicle(playerid))
        {
            id = GetPlayerVehicleID(playerid);

            if(sscanf(params, "f", amount))
                return SendSyntaxMessage(playerid, "/setcarhp [amount]");

            if(amount < 0.0)
                return SendErrorMessage(playerid, "The amount can't be below 0.");

            SetVehicleHealth(id, amount);
            SendAdminAction(playerid, "You have set the health of vehicle ID: %d to %.1f.", id, amount);
            return 1;
        }
        else return SendSyntaxMessage(playerid, "/setcarhp [vehicle id] [amount]");
    }
    if(!IsValidVehicle(id))
        return SendErrorMessage(playerid, "You have specified an invalid vehicle ID.");

    if(amount < 0.0)
        return SendErrorMessage(playerid, "The amount can't be below 0.");

    SetVehicleHealth(id, amount);
    SendAdminAction(playerid, "You have set the health of vehicle ID: %d to %.1f.", id, amount);
    return 1;
}

CMD:setskin(playerid, params[])
{
	if(PlayerData[playerid][pAdmin] < 2)
		return SendErrorMessage(playerid, NO_PERMISSION);

	new skinid, userid;
	if (sscanf(params, "ud", userid, skinid))
	    return SendSyntaxMessage(playerid, "/setskin [playerid/PartOfName] [skin id]");

    if (!IsPlayerConnected(userid))
	 return SendErrorMessage(playerid, "You have specified an invalid player.");

	if (skinid < 0 || skinid > 311)
	    return SendErrorMessage(playerid, "Invalid skin ID. Skins range from 0 to 311.");

	UpdatePlayerSkin(userid, skinid);
	return 1;
}

CMD:acure(playerid, params[]) {

	if(PlayerData[playerid][pAdmin] < 3)
	    return SendErrorMessage(playerid, NO_PERMISSION);

	new targetid;
	if(sscanf(params, "u", targetid))
	    return SendSyntaxMessage(playerid, "/acure [playerid/PartOfName]");

	if(!IsPlayerConnected(targetid))
	    return SendErrorMessage(playerid, "Invalid Player specified!");

	SetPlayerHealth(targetid, 100.0);
	PlayerData[targetid][pHealthy] = 100.0;
	PlayerData[targetid][pFever] = 0;
	PlayerData[targetid][pCough] = 0;
	PlayerData[targetid][pFeverRate] = 0;
	SetPlayerDrunkLevelEx(playerid, 0);
	PlayerData[targetid][pHunger] = 100.0;
	PlayerData[targetid][pThirst] = 100.0;
	
	for(new i = 0; i < 7; i++)
	{
		PlayerData[targetid][pDamages][i] = 100.0;
		PlayerData[targetid][pBullets][i] = 0;
	}
	SendAdminAction(playerid, "Kamu telah menyembuhkan %s.", GetName(targetid, false));
	return 1;
}

CMD:arevive(playerid, params[])
{
	if(PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, NO_PERMISSION);
	    
	new targetid;
	if(sscanf(params, "u", targetid))
	    return SendSyntaxMessage(playerid, "/arevive [playerid]");

	if(!IsPlayerConnected(targetid))
	    return SendErrorMessage(playerid, "You have specified invalid player!");
	    
	if(!PlayerData[targetid][pInjured])
	    return SendErrorMessage(playerid, "That player is not injured!");
	    
	PlayerData[targetid][pInjured] = false;
	PlayerData[targetid][pDead] = false;
	PlayerData[targetid][pInjuredTime] = 0;
	ClearAnimations(targetid, 1);
	SendServerMessage(playerid, "You've healing %s", GetName(targetid));
	ApplyAnimation(targetid, "PED", "GETUP_FRONT", 4.0, 0, 1, 1, 0, 0);
	Log_Write("Logs/adm_cmd_log.txt", "[%s] %s: /arevive %s", ReturnDate(), GetUsername(playerid), params);
	return 1;
}

CMD:reviveall(playerid, params[]) {

	if(PlayerData[playerid][pAdmin] < 6)
	    return SendErrorMessage(playerid, NO_PERMISSION);

	foreach(new i : Player) if(PlayerData[i][pInjured]) {

		PlayerData[i][pInjured] = false;
		PlayerData[i][pDead] = false;
		PlayerData[i][pInjuredTime] = 0;
		ClearAnimations(i, 1);
		SetPlayerHealth(i, 100.0);
	}
	SendAdminAction(playerid, "You have revived all player.");
	return 1;
}
CMD:goto(playerid, params[])
{
	if(PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");
	    
	new targetid;
	if(sscanf(params, "u", targetid))
	    return SendSyntaxMessage(playerid, "/goto [playerid]");
	    
	if(!IsPlayerConnected(targetid))
	    return SendErrorMessage(playerid, "You have specified invalid player!");
	    
	if(!PlayerData[targetid][pSpawned])
	    return SendErrorMessage(playerid, "That player is not spawned.");
	    
	SendPlayerToPlayer(playerid, targetid);
	return 1;
}

timer ShutdownTheServer[1000]() {
	SendRconCommand("gmx");
	SendRconCommand("password maintenancedulu");
	SendRconCommand("hostname Orang Tua Roleplay [ UNDER MAINTENANCE ]");
	return 1;
}
timer KickOnlinePlayer[3000]() {
	foreach(new i : Player) {
		KickEx(i);
	}

	defer ShutdownTheServer[2000]();
	return 1;
}

CMD:girlie(playerid, params[]) {
	if(PlayerData[playerid][pAdmin] < 7)
		return SendErrorMessage(playerid, NO_PERMISSION);


	foreach(new i : Player) if(PlayerData[i][pGender] == 2) {
		SendClientMessageEx(playerid, -1, "[%d] %s(%s)", i, GetName(i, false), GetUsername(i));
	}
	return 1;
}
CMD:shutdown(playerid, params[]) {
	if(PlayerData[playerid][pAdmin] < 7)
		return SendErrorMessage(playerid, NO_PERMISSION);

	SendClientMessageToAllEx(X11_TOMATO, "AdmCmd: %s is initiated to shutdown the server.", GetUsername(playerid));
	SaveServerStatistics();
	defer KickOnlinePlayer[3000]();

	return 1;
}
CMD:get(playerid, params[])
{
	static
	    userid;

	if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "u", userid))
	    return SendSyntaxMessage(playerid, "/get [playerid/PartOfName]");

    if (!IsPlayerConnected(userid))
	    return SendErrorMessage(playerid, "You have specified an invalid player.");

	if (!PlayerData[playerid][pSpawned])
		return SendErrorMessage(playerid, "You can't teleport a player that's not spawned.");

	SendPlayerToPlayer(userid, playerid);
	SendServerMessage(playerid, "You have teleported %s to you.", ReturnName(userid));
	return 1;
}

CMD:nearplayer(playerid, params[]) {

	if(PlayerData[playerid][pAdmin] < 1)
		return SendErrorMessage(playerid, "You don't have permission to use this command.");

	new Float:radius, Float:x, Float:y, Float:z;
	if(sscanf(params, "f", radius))
		return SendSyntaxMessage(playerid, "/nearplayer [radius]");

	GetPlayerPos(playerid, x, y, z);
	SendClientMessageEx(playerid, -1, "======== Nearest player on %.1f radius ========", radius);

	foreach(new i : Player) if(IsPlayerInRangeOfPoint(i, radius, x, y, z) && i != playerid) {
		SendClientMessageEx(playerid, -1, "[%d] %s(%s)", i, GetName(i, false), GetUsername(i));
	}
	return 1;
}
CMD:unban(playerid, params[])
{
	if(PlayerData[playerid][pAdmin] < 1)
		return SendErrorMessage(playerid, "You don't have permission to use this command.");

	new name[MAX_PLAYER_NAME];
	if(sscanf(params, "s[24]", name))
		return SendSyntaxMessage(playerid, "/unban [UCP name]");

	new query[156];
	mysql_format(sqlcon, query, sizeof(query), "SELECT * FROM `banneds` WHERE `Username` = '%e'", name);
	mysql_tquery(sqlcon, query, "OnUnbanUsername", "ds", playerid, name);
	Log_Write("Logs/adm_cmd_log.txt", "[%s] %s: /unban %s", ReturnDate(), GetUsername(playerid), params);
	return 1;	
}

CMD:oban(playerid, params[])
{
	if(PlayerData[playerid][pAdmin] < 1)
		return SendErrorMessage(playerid, "You don't have permission to use this command.");

	new name[MAX_PLAYER_NAME], reason[32];
	if(sscanf(params, "s[24]s[32]", name, reason))
		return SendSyntaxMessage(playerid, "/obanucp [UCP name] [Reason]");

	new characterQuery[178];
	mysql_format(sqlcon, characterQuery, sizeof(characterQuery), "SELECT * FROM `playerucp` WHERE `UCP` = '%e' LIMIT 1", name);
	mysql_tquery(sqlcon, characterQuery, "OnUCPBanned", "dss", playerid, name, reason);
	Log_Write("Logs/adm_cmd_log.txt", "[%s] %s: /oban %s", ReturnDate(), GetUsername(playerid), params);
	return 1;
}

CMD:ban(playerid, params[])
{
	if(PlayerData[playerid][pAdmin] < 1)
		return SendErrorMessage(playerid, "You don't have permission to use this command.");

	new targetid, reason[32];
	if(sscanf(params, "ds[32]", targetid, reason))
		return SendSyntaxMessage(playerid, "/ban [playerid/PartOfName] [reason]");

	if(!IsPlayerConnected(targetid))
		return SendErrorMessage(playerid, "You have specified an You have specified invalid player!");

	SendClientMessageToAllEx(COLOR_LIGHTRED, "AdmCmd: Account %s has been banned by %s", PlayerData[targetid][pUCP], PlayerData[playerid][pUCP]);
	SendClientMessageToAllEx(COLOR_LIGHTRED, "Reason: %s", reason);
	SendAdminAction(playerid, "IP Akun yang anda banned adalah %s",  ReturnIP(targetid));

	new string[552];

	new query[379];
	mysql_format(sqlcon, query, sizeof(query), "INSERT INTO `banneds` (`Username`, `Admin`, `Reason`, `Date`, `IP`) VALUES ('%e', '%e', '%e', '%e', '%e')", GetUsername(targetid), GetUsername(playerid), reason, ReturnDate(true), ReturnIP(targetid));
	mysql_tquery(sqlcon, query);

	strcat(string, sprintf(""WHITE"Akun anda "GREY"(%s) "WHITE"telah dibanned dari server.\n\n", GetUsername(targetid)));
	strcat(string, sprintf(""GREY"Username: "WHITE"%s\n", GetUsername(targetid)));
	strcat(string, sprintf(""GREY"IP Address: "WHITE"%s\n", ReturnIP(targetid)));
	strcat(string, sprintf(""GREY"Admin yang menindak: "WHITE"%s\n", GetUsername(playerid)));
	strcat(string, sprintf(""GREY"Dibanned pada: "WHITE"%s\n\n\n", ReturnDate(false)));
	strcat(string, ""WHITE"Untuk membuka blokir/banned pada akun anda dapat dilakukan dengan melakukan...\n");
	strcat(string, "unbanned appeals pada discord Orang Tua Roleplay ");

	ShowPlayerDialog(targetid, DIALOG_NONE, DIALOG_STYLE_MSGBOX, "Banned Alert - Username Ban", string, "Close", "");	

	KickEx(targetid);

	Log_Write("Logs/adm_cmd_log.txt", "[%s] %s: /ban %s", ReturnDate(), GetUsername(playerid), params);
	return 1;
}

CMD:vynrpmode(playerid, params[]) {

	if(PlayerData[playerid][pAdmin] < 7)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	PlayerData[playerid][pVynMode] = !(PlayerData[playerid][pVynMode]);
	SendAdminAction(playerid, "RP Only mode %s", (PlayerData[playerid][pVynMode]) ? ("enabled") : ("disabled"));
	return 1;
}
CMD:asay(playerid, params[])
{
	if(PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if(isnull(params))
	    return SendSyntaxMessage(playerid, "/asay [text]");
	    
	SendClientMessageToAllEx(COLOR_LIGHTRED, "%s %s: %s", GetAdminRank(playerid), PlayerData[playerid][pUCP], params);
	return 1;
}

CMD:apm(playerid, params[])
{
	static
	    userid,
	    text[128];

    if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "us[128]", userid, text))
		return SendSyntaxMessage(playerid, "/apm [playerid/PartOfName] [message]");

	if (!IsPlayerConnected(userid))
	    return SendErrorMessage(playerid, "You have specified an invalid player.");

	SendClientMessageEx(userid, COLOR_LIGHTRED, "PM From Admin: {FFFFFF}%s", text);
	SendAdminMessage(COLOR_LIGHTRED, "%s APM To %s: %s", PlayerData[playerid][pUCP], GetName(userid), text);
	PlayerPlaySound(userid, 1085, 0.0, 0.0, 0.0);
	return 1;
}

CMD:sendvehto(playerid, params[]) {

	static
	    targetid, vehicleid;

    if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "du", vehicleid, targetid))
	    return SendSyntaxMessage(playerid, "/sendvehto [vehicleid] [playerid/PartOfName]");

	if(!IsValidVehicle(vehicleid))
		return SendErrorMessage(playerid, "You have specified invalid vehicle.");

	if(!IsPlayerConnected(targetid) || !IsPlayerConnected(targetid))
		return SendErrorMessage(playerid, "You have specified invalid player.");

	new Float:x, Float:y, Float:z;
	GetPlayerPos(targetid, x, y, z);
	SetVehiclePos(vehicleid, x, y, z);
	SetVehicleInterior(vehicleid, GetPlayerInterior(targetid));
	SetVehicleVirtualWorld(vehicleid, GetPlayerVirtualWorld(targetid));

	SetPlayerPos(targetid, x, y + 1, z);
	SendAdminAction(playerid, "You have send vehicleid %d to %s.", vehicleid, ReturnName(targetid));
	return 1;
}

CMD:send(playerid, params[]) {
    if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	new
		targetid, place[24];

	if(sscanf(params, "us[24]", targetid, place))
		return SendSyntaxMessage(playerid, "/send [playerid/PartOfName] [location]"), SendClientMessage(playerid, -1, "Location: sfpd, hospital, jobcenter, bank, sweeper, bus(1/2), mower, mc, miner"), SendClientMessage(playerid, -1, "Location: trashmaster, ch, ff, dmv, component, news, insurance, newspawn");

	if(!IsPlayerConnected(targetid) || !IsPlayerConnected(targetid))
		return SendErrorMessage(playerid, "You have specified invalid player.");

	if(!strcmp(place, "sfpd", true)) {
		SetPlayerPos(targetid, -1605.8027,711.7601,13.8672);
		SetPlayerInterior(targetid, 0);
		SetPlayerVirtualWorld(targetid, 0);

		ResetInteriorData(targetid);

		SendAdminAction(playerid, "You have send %s to SFPD.", ReturnName(targetid));
		SendAdminAction(targetid, "Kamu telah diteleportasi ke "YELLOW"SFPD "WHITE"oleh "RED"%s", GetUsername(playerid));
	}
	else if(!strcmp(place, "insurance", true)) {
		SetPlayerPos(targetid,-1939.5687,562.9002,35.1899);
		SetPlayerInterior(targetid, 0);
		SetPlayerVirtualWorld(targetid, 0);

		ResetInteriorData(targetid);

		SendAdminAction(playerid, "You have send %s to Insurance Center.", ReturnName(targetid));
		SendAdminAction(targetid, "Kamu telah diteleportasi ke "YELLOW"Insurance Center "WHITE"oleh "RED"%s", GetUsername(playerid));
	}
	else if(!strcmp(place, "newspawn", true)) {
		SetPlayerPos(targetid,-1425.2041,-291.0014,14.1484);
		SetPlayerInterior(targetid, 0);
		SetPlayerVirtualWorld(targetid, 0);

		ResetInteriorData(targetid);

		SendAdminAction(playerid, "You have send %s to Newbie Spawn.", ReturnName(targetid));
		SendAdminAction(targetid, "Kamu telah diteleportasi ke "YELLOW"Newbie Spawn "WHITE"oleh "RED"%s", GetUsername(playerid));
	}
	else if(!strcmp(place, "news", true)) {
		SetPlayerPos(targetid,-1908.7998,486.7876,35.1719);
		SetPlayerInterior(targetid, 0);
		SetPlayerVirtualWorld(targetid, 0);

		ResetInteriorData(targetid);

		SendAdminAction(playerid, "You have send %s to SFN.", ReturnName(targetid));
		SendAdminAction(targetid, "Kamu telah diteleportasi ke "YELLOW"SFN "WHITE"oleh "RED"%s", GetUsername(playerid));
	}
	else if(!strcmp(place, "component", true)) {
		SetPlayerPos(targetid,-1901.6932,486.6408,35.1719);
		SetPlayerInterior(targetid, 0);
		SetPlayerVirtualWorld(targetid, 0);

		ResetInteriorData(targetid);

		SendAdminAction(playerid, "You have send %s to Component.", ReturnName(targetid));
		SendAdminAction(targetid, "Kamu telah diteleportasi ke "YELLOW"Component "WHITE"oleh "RED"%s", GetUsername(playerid));
	}
	else if(!strcmp(place, "dmv", true)) {
		SetPlayerPos(targetid,-2026.5580,-98.4208,35.1641);
		SetPlayerInterior(targetid, 0);
		SetPlayerVirtualWorld(targetid, 0);

		ResetInteriorData(targetid);

		SendAdminAction(playerid, "You have send %s to DMV.", ReturnName(targetid));
		SendAdminAction(targetid, "Kamu telah diteleportasi ke "YELLOW"DMV "WHITE"oleh "RED"%s", GetUsername(playerid));
	}
	else if(!strcmp(place, "ff", true)) {
		SetPlayerPos(targetid,-2077.7153,1358.2211,7.1007);
		SetPlayerInterior(targetid, 0);
		SetPlayerVirtualWorld(targetid, 0);

		ResetInteriorData(targetid);

		SendAdminAction(playerid, "You have send %s to Fish Factory.", ReturnName(targetid));
		SendAdminAction(targetid, "Kamu telah diteleportasi ke "YELLOW"Fish Factory "WHITE"oleh "RED"%s", GetUsername(playerid));
	}
	else if(!strcmp(place, "ch", true)) {
		SetPlayerPos(targetid, -2757.4263,375.5820,4.3348);
		SetPlayerInterior(targetid, 0);
		SetPlayerVirtualWorld(targetid, 0);

		ResetInteriorData(targetid);

		SendAdminAction(playerid, "You have send %s to Cityhall.", ReturnName(targetid));
		SendAdminAction(targetid, "Kamu telah diteleportasi ke "YELLOW"Cityhall "WHITE"oleh "RED"%s", GetUsername(playerid));
	}
	else if(!strcmp(place, "trashmaster", true)) {
		SetPlayerPos(targetid,-1904.1689,-1704.9474,21.7500);
		SetPlayerInterior(targetid, 0);
		SetPlayerVirtualWorld(targetid, 0);

		ResetInteriorData(targetid);

		SendAdminAction(playerid, "You have send %s to Trashmaster.", ReturnName(targetid));
		SendAdminAction(targetid, "Kamu telah diteleportasi ke "YELLOW"Trashmaster "WHITE"oleh "RED"%s", GetUsername(playerid));	
	}
	else if(!strcmp(place, "miner", true)) {
		SetPlayerPos(targetid,-1298.1036,2501.2539,86.9291);
		SetPlayerInterior(targetid, 0);
		SetPlayerVirtualWorld(targetid, 0);

		ResetInteriorData(targetid);

		SendAdminAction(playerid, "You have send %s to Miner.", ReturnName(targetid));
		SendAdminAction(targetid, "Kamu telah diteleportasi ke "YELLOW"Miner "WHITE"oleh "RED"%s", GetUsername(playerid));	
	}
	else if(!strcmp(place, "mc", true)) {
		SetPlayerPos(targetid, -1826.0948,2.6957,15.1172);
		SetPlayerInterior(targetid, 0);
		SetPlayerVirtualWorld(targetid, 0);

		ResetInteriorData(targetid);

		SendAdminAction(playerid, "You have send %s to Mechanic Center.", ReturnName(targetid));
		SendAdminAction(targetid, "Kamu telah diteleportasi ke "YELLOW"Mechanic Center "WHITE"oleh "RED"%s", GetUsername(playerid));	
	}
	else if(!strcmp(place, "mower", true)) {
		SetPlayerPos(targetid, -2297.6365,170.0636,35.3125);
		SetPlayerInterior(targetid, 0);
		SetPlayerVirtualWorld(targetid, 0);

		ResetInteriorData(targetid);

		SendAdminAction(playerid, "You have send %s to Mower.", ReturnName(targetid));
		SendAdminAction(targetid, "Kamu telah diteleportasi ke "YELLOW"Mower "WHITE"oleh "RED"%s", GetUsername(playerid));
	}
	else if(!strcmp(place, "sweeper", true)) {
		SetPlayerPos(targetid, -2088.7322,-95.8982,35.1662);
		SetPlayerInterior(targetid, 0);
		SetPlayerVirtualWorld(targetid, 0);

		ResetInteriorData(targetid);

		SendAdminAction(playerid, "You have send %s to Sweeper.", ReturnName(targetid));
		SendAdminAction(targetid, "Kamu telah diteleportasi ke "YELLOW"Sweeper "WHITE"oleh "RED"%s", GetUsername(playerid));
	}
	else if(!strcmp(place, "bank", true)) {
		SetPlayerPos(targetid, -2242.8726,311.4897,35.3203);
		SetPlayerInterior(targetid, 0);
		SetPlayerVirtualWorld(targetid, 0);

		ResetInteriorData(targetid);

		SendAdminAction(playerid, "You have send %s to Bank.", ReturnName(targetid));
		SendAdminAction(targetid, "Kamu telah diteleportasi ke "YELLOW"Bank "WHITE"oleh "RED"%s", GetUsername(playerid));
	}
	else if(!strcmp(place, "bus2", true)) {
		SetPlayerPos(targetid, -2499.2954,1209.2731,37.4283);
		SetPlayerInterior(targetid, 0);
		SetPlayerVirtualWorld(targetid, 0);

		ResetInteriorData(targetid);

		SendAdminAction(playerid, "You have send %s to Bus Juniper Hollow.", ReturnName(targetid));
		SendAdminAction(targetid, "Kamu telah diteleportasi ke "YELLOW"Bus Juniper Hollow "WHITE"oleh "RED"%s", GetUsername(playerid));
	}
	else if(!strcmp(place, "bus1", true)) {
		SetPlayerPos(targetid, -2524.1375,-619.1014,132.5625);
		SetPlayerInterior(targetid, 0);
		SetPlayerVirtualWorld(targetid, 0);

		ResetInteriorData(targetid);

		SendAdminAction(playerid, "You have send %s to Bus Missionary Hill.", ReturnName(targetid));
		SendAdminAction(targetid, "Kamu telah diteleportasi ke "YELLOW"Bus Missionary Hill "WHITE"oleh "RED"%s", GetUsername(playerid));
	}
	else if(!strcmp(place, "jobcenter", true)) {
		SetPlayerPos(targetid, -2421.1575,-717.1309,133.3063);
		SetPlayerInterior(targetid, 0);
		SetPlayerVirtualWorld(targetid, 0);

		ResetInteriorData(targetid);

		SendAdminAction(playerid, "You have send %s to Job Center.", ReturnName(targetid));
		SendAdminAction(targetid, "Kamu telah diteleportasi ke "YELLOW"Hospital "WHITE"oleh "RED"%s", GetUsername(playerid));
	}
	else if(!strcmp(place, "hospital", true)) {

		SetPlayerPos(targetid, -2665.2368,630.4848,14.4531);
		SetPlayerInterior(targetid, 0);
		SetPlayerVirtualWorld(targetid, 0);

		ResetInteriorData(targetid);

		SendAdminAction(playerid, "You have send %s to Hospital.", ReturnName(targetid));
		SendAdminAction(targetid, "Kamu telah diteleportasi ke "YELLOW"Hospital "WHITE"oleh "RED"%s", GetUsername(playerid));

	}
	else SendSyntaxMessage(playerid, "/send [playerid/PartOfName] [location]"), SendClientMessage(playerid, -1, "Location: sfpd, hospital, jobcenter, bank, sweeper, bus(1/2), mower, mc, miner"), SendClientMessage(playerid, -1, "Location: trashmaster, ch, ff, dmv, component, news, insurance");
	return 1;
}
CMD:sendtoveh(playerid, params[]) {

	static
	    targetid, vehicleid;

    if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "ud", targetid, vehicleid))
	    return SendSyntaxMessage(playerid, "/sendtoveh [playerid/PartOfName] [vehicleid]");

	if(!IsPlayerConnected(targetid) || !IsPlayerConnected(targetid))
		return SendErrorMessage(playerid, "You have specified invalid player.");

	if(!IsValidVehicle(vehicleid))
		return SendErrorMessage(playerid, "You have specified invalid vehicle.");

	new Float:x, Float:y, Float:z;
	GetVehiclePos(vehicleid, x, y, z);
	SetPlayerPos(targetid, x, y, z);
	SetPlayerVirtualWorld(targetid, GetVehicleVirtualWorld(vehicleid));
	SendAdminAction(playerid, "You have send %s to vehicleid %d.", ReturnName(targetid), vehicleid);
	return 1;
}
CMD:sendto(playerid, params[])
{
	static
	    userid,
	    targetid;

    if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "uu", userid, targetid))
	    return SendSyntaxMessage(playerid, "/sendto [playerid/PartOfName] [playerid/PartOfName]");

	if (!IsPlayerConnected(userid) || !IsPlayerConnected(targetid))
	    return SendErrorMessage(playerid, "The specified user(s) are not connected.");

	SendPlayerToPlayer(userid, targetid);

	SendServerMessage(playerid, "You have teleported %s to %s.", ReturnName(userid), ReturnName(targetid));
	SendServerMessage(userid, "%s has teleported you to %s.", PlayerData[playerid][pUCP], ReturnName(targetid));
	return 1;
}

CMD:a(playerid, params[])
{
	if(PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");
	    
	if(isnull(params))
	    return SendSyntaxMessage(playerid, "/a [admin chat]");
	    
	foreach(new i : Player) if(PlayerData[i][pAdmin] > 0) {
		SendClientMessageEx(i, COLOR_GREEN, "%s "GREY"%s: {FFFFFF}%s", GetAdminRank(playerid), PlayerData[playerid][pUCP], params);
	}
	return 1;
}

CMD:flipcar(playerid, params[])
{
	new vehicleid = GetPlayerVehicleID(playerid);

	if (PlayerData[playerid][pAdmin] < 4)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (vehicleid > 0 && isnull(params))
	{
		FlipVehicle(vehicleid);
		SendServerMessage(playerid, "You have flipped your current vehicle.");
	}
	else
	{
		if (sscanf(params, "d", vehicleid))
	    	return SendSyntaxMessage(playerid, "/flipcar [vehicle ID]");

		else if (!IsValidVehicle(vehicleid))
	    	return SendErrorMessage(playerid, "You have specified an invalid vehicle ID.");

		FlipVehicle(vehicleid);
		SendServerMessage(playerid, "You have flipped vehicle ID: %d.", vehicleid);
	}
	return 1;
}

CMD:setweather(playerid, params[])
{
	new weatherid;

	if (PlayerData[playerid][pAdmin] < 3)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "d", weatherid))
	    return SendSyntaxMessage(playerid, "/setweather [weather ID]");

	SetWeather(weatherid);
	SendClientMessageToAllEx(COLOR_LIGHTRED, "AdmCmd: {FFFFFF}%s has adjusted weather to weatherid %d", PlayerData[playerid][pUCP], weatherid);
	return 1;
}

CMD:maxmotive(playerid, params[])
{
	if(PlayerData[playerid][pAdmin] < 3)
		return SendErrorMessage(playerid, "You don't have permission to use this command!");

	if(!PlayerData[playerid][pAduty])
		return SendErrorMessage(playerid, "You must be admin duty!");

	PlayerData[playerid][pHunger] = 100;
	PlayerData[playerid][pThirst] = 100;
	return 1;
}
CMD:setarmor(playerid, params[])
{
	static
		userid,
	    Float:amount;

	if (PlayerData[playerid][pAdmin] < 5)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "uf", userid, amount))
		return SendSyntaxMessage(playerid, "/setarmor [playerid/PartOfName] [amount]");

	if (!IsPlayerConnected(userid))
	    return SendErrorMessage(playerid, "You have specified an invalid player.");

	SetPlayerArmour(userid, amount);
	SendServerMessage(playerid, "You have set %s's armour to %.2f.", GetName(userid), amount);
	Log_Write("Logs/adm_cmd_log.txt", "[%s] %s: /setarmor %s", ReturnDate(), GetUsername(playerid), params);
	return 1;
}

CMD:sethp(playerid, params[])
{
	new
		userid,
	    Float:amount;

	if (PlayerData[playerid][pAdmin] < 4)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "uf", userid, amount))
		return SendSyntaxMessage(playerid, "/sethp [playerid/PartOfName] [amount]");

	if (!IsPlayerConnected(userid))
	    return SendErrorMessage(playerid, "You have specified an invalid player.");

	SetPlayerHealth(userid, amount);
	SendServerMessage(playerid, "You have set %s's health to %.2f.", GetName(userid), amount);
	Log_Write("Logs/adm_cmd_log.txt", "[%s] %s: /sethp %s", ReturnDate(), GetUsername(playerid), params);
	return 1;
}

CMD:serverpassword(playerid, params[]) {
    if (PlayerData[playerid][pAdmin] < 6)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if(isnull(params))
		return SendSyntaxMessage(playerid, "/serverpassword [password] (\"remove\" to remove password)");

	if(!strcmp(params, "remove", true)) {
		SendRconCommand("password 0");
		SendAdminMessage(X11_TOMATO, "RconCmd: password server has been removed by %s.", GetUsername(playerid));
	}
	else {
		SendRconCommand(sprintf("password %s", params));
		SendAdminMessage(X11_TOMATO, "RconCmd: password server has been updated by %s.", GetUsername(playerid));
		SendClientMessageEx(playerid, X11_LIGHTBLUE, "Server Password: %s", params);
	}
	return 1;
}
CMD:kick(playerid, params[])
{
	static
	    userid,
	    reason[128];

    if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "us[128]", userid, reason))
	    return SendSyntaxMessage(playerid, "/kick [playerid/PartOfName] [reason]");

	if (!IsPlayerConnected(userid))
	    return SendErrorMessage(playerid, "You have specified an invalid player.");

    if (PlayerData[userid][pAdmin] > PlayerData[playerid][pAdmin])
	    return SendErrorMessage(playerid, "The specified player has higher authority.");

	SendClientMessageToAllEx(COLOR_LIGHTRED, "AdmCmd: %s has been kicked by %s reason: %s.", GetName(userid), PlayerData[playerid][pUCP], reason);
	KickEx(userid);
	Log_Write("Logs/adm_cmd_log.txt", "[%s] %s: /kick %s", ReturnDate(), GetUsername(playerid), params);
	return 1;
}

CMD:setcash(playerid, params[])
{
	static
		userid,
	    amount[32];

	if (PlayerData[playerid][pAdmin] < 7)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "us[32]", userid, amount))
		return SendSyntaxMessage(playerid, "/setcash [playerid/PartOfName] [amount]");

	if (!IsPlayerConnected(userid))
	    return SendErrorMessage(playerid, "You have specified an invalid player.");

	ResetPlayerMoney(userid);
	PlayerData[userid][pMoney] = 0;
	GiveMoney(userid, strcash(amount), "Sets by admin");
	
	SendAdminMessage(COLOR_LIGHTRED, "AdmCmd: %s has set %s cash to $%s", PlayerData[playerid][pUCP], ReturnName(userid), FormatNumber(strcash(amount)));
	Log_Write("Logs/adm_cmd_log.txt", "[%s] %s: /setcash %s", ReturnDate(), GetUsername(playerid), params);
	return 1;	
}

CMD:finecoin(playerid, params[]) {

	new targetid, amount;
	if(PlayerData[playerid][pAdmin] < 7)
		return SendErrorMessage(playerid, "You don't have permission to use this command!");

	if(sscanf(params, "ud", targetid, amount))
		return SendSyntaxMessage(playerid, "/finecoin [playerid/PartOfName] [amount]");

	if(!IsPlayerConnected(targetid))
		return SendErrorMessage(playerid, "You have specified invalid player!");

	PlayerData[targetid][pCoin] -= amount;
	SendAdminAction(playerid, "Kamu telah mengambil %d coin dari %s.", amount, GetName(targetid, false));
	return 1;
}

CMD:gaterequest(playerid, params[]) {
	if(PlayerData[playerid][pAdmin] < 6)
		return SendErrorMessage(playerid, "You don't have permission to use this command!");


	mysql_tquery(sqlcon, "SELECT * FROM `gaterequests`", "ShowGateReq", "d", playerid);
	return 1;
}
CMD:givecoin(playerid, params[]) {

	new targetid, amount;
	if(PlayerData[playerid][pAdmin] < 7)
		return SendErrorMessage(playerid, "You don't have permission to use this command!");

	if(sscanf(params, "ud", targetid, amount))
		return SendSyntaxMessage(playerid, "/givecoin [playerid/PartOfName] [amount]");

	if(!IsPlayerConnected(targetid))
		return SendErrorMessage(playerid, "You have specified invalid player!");

	PlayerData[targetid][pCoin] += amount;
	SendAdminAction(playerid, "Kamu telah memberikan %d coin kepada %s.", amount, GetName(targetid, false));
	return 1;
}

CMD:givecash(playerid, params[])
{
	new targetid, amount[32];
	if(PlayerData[playerid][pAdmin] < 7)
		return SendErrorMessage(playerid, "You don't have permission to use this command!");

	if(sscanf(params, "us[32]", targetid, amount))
		return SendSyntaxMessage(playerid, "/givecash [playerid/PartOfName] [amount]");

	if(!IsPlayerConnected(targetid))
		return SendErrorMessage(playerid, "You have specified invalid player!");

	SendAdminMessage(COLOR_LIGHTRED, "AdmCmd: %s has give $%s cash to %s", PlayerData[playerid][pUCP], FormatNumber(strcash(amount)), GetName(targetid));
	GiveMoney(targetid, strcash(amount), sprintf("Given from %s", GetUsername(playerid)));
	Log_Write("Logs/adm_cmd_log.txt", "[%s] %s: /givecash %s", ReturnDate(), GetUsername(playerid), params);
	return 1;
}

CMD:giveallcash(playerid, params[]) {

	if(PlayerData[playerid][pAdmin] < 7)
		return SendErrorMessage(playerid, "You don't have permission to use this command!");

	new amount[32], cash = 0;

	if(sscanf(params, "s[32]", amount))
		return SendSyntaxMessage(playerid, "/giveallcash [amount]");

	cash = strcash(amount);

	SendClientMessageToAllEx(X11_TOMATO, "AdmCmd: %s memberikan uang sebanyak $%s kepada seluruh player.", GetUsername(playerid), FormatNumber(cash));
	foreach(new i : Player) if(IsPlayerSpawned(i)) {
		GiveMoney(i, cash, "Given all from admin");
	}
	return 1;
}
CMD:jetpack(playerid, params[])
{
    if(PlayerData[playerid][pAdmin] < 1)
        return SendErrorMessage(playerid, "You don't have permission to use this command!");

    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USEJETPACK);
    return 1;
}

CMD:aod(playerid, params[]) {
	return cmd_aduty(playerid, "\0");
}
CMD:aduty(playerid, params[])
{
    if(PlayerData[playerid][pAdmin] < 1)
        return SendErrorMessage(playerid, "You don't have permission to use this command!");
        
	if(!PlayerData[playerid][pAduty])
	{
	    PlayerData[playerid][pAduty] = true;
	    SetPlayerColor(playerid, 0xFF0000FF);
	    SetPlayerName(playerid, PlayerData[playerid][pUCP]);
	    SendAdminMessage(X11_TOMATO, "* %s is now onduty as administrator.", PlayerData[playerid][pUCP]);

		SQL_SaveCharacter(playerid);
	}
	else
	{
	    PlayerData[playerid][pAduty] = false;
	    SetValidColor(playerid);
	    SetPlayerName(playerid, PlayerData[playerid][pName]);
	    SendAdminMessage(X11_TOMATO, "* %s is no longer duty as administrator.", PlayerData[playerid][pUCP]);

		TogglePlayerControllable(playerid, true);
	}
	return 1;
}

CMD:gmx(playerid, params[])
{	
	if(PlayerData[playerid][pAdmin] < 7)
		return SendServerMessage(playerid, "Ngapain Om!");

	foreach(new i : Player) if(IsPlayerSpawned(i)) {
		SQL_SaveCharacter(i);
	}
	SaveServerData();
	SendRconCommand("gmx");
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {
	if(dialogid == DIALOG_GATEREQ) {
		if(response) {
			mysql_tquery(sqlcon, sprintf("DELETE FROM `gaterequests` WHERE `ID` = '%d'", ListedItems[playerid][listitem]));
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}


CMD:countdown(playerid, params[])
{
    if (PlayerData[playerid][pAdmin] < 1)
        return PermissionError(playerid);

    static interval;

    if(countdown_tick)
    {
        TextDrawHideForAll(COUNTDOWNGUI);
        countdown_tick = 0;
        return 1;
    }

    if(sscanf(params, "d", interval)) return SendSyntaxMessage(playerid, "/countdown [interval]");

    TextDrawShowForAll(COUNTDOWNGUI);
    countdown_tick = interval;
    SendAdminMessage(X11_TOMATO_1, "AdmCmd: %s initiated coutdown with %d second.", GetUsername(playerid), interval);
    return 1;
}

hook OnGameModeInit() {
	countdown_tick = 0;
}