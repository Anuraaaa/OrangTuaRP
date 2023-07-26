new
	SanNewsVehicles[11],
	LSMDVehicles[10],
	LSPDVehicles[38],
	BusVehicle[3],
	Bus2Vehicle[2],
	SweeperVehicle[3],
	TrashVehicle[3],
	MowerVehicle[4],
	ForkliftVehicle[6],
	RumpoVehicle[6],
	CourierVehicle[5];

ShowMDC(playerid)
{
	if(!IsPlayerInAnyVehicle(playerid))
		return SendErrorMessage(playerid, "You must inside faction vehicle!");

	if(GetFactionType(playerid) == FACTION_POLICE)
	{
		if(!IsPoliceVehicle(GetPlayerVehicleID(playerid)))
			return SendErrorMessage(playerid, "You must be inside Police Vehicle!");

		ShowPlayerDialog(playerid, DIALOG_MDC, DIALOG_STYLE_LIST, "MDC > Dashboard", "Recent 911 calls\nPlate Search\nCitizen Lookup\nVehicle Lookup", "Select", "Logout");
		PlayerPlayNearbySound(playerid, MDC_OPEN);
		SetPlayerChatBubble(playerid, "* Logs into the Mobile Data Computer *", COLOR_PURPLE, 15.0, 10000);
	}
	else
	{
		if(!IsMedicVehicle(GetPlayerVehicleID(playerid)))
			return SendErrorMessage(playerid, "You must be inside Medic Vehicle!");		

		ShowPlayerDialog(playerid, DIALOG_MDC, DIALOG_STYLE_LIST, "MDC > Dashboard", "Recent 911 calls", "Select", "Close");
		PlayerPlayNearbySound(playerid, MDC_OPEN);
		SetPlayerChatBubble(playerid, "* Logs into the Mobile Data Computer *", COLOR_PURPLE, 15.0, 10000);
	}
	return 1;
}

ReturnMDC(playerid) {
	PlayerPlayNearbySound(playerid, MDC_SELECT);
	return ShowMDC(playerid);
}

function OnLookupTicketMDC(playerid) {
	
	new name[MAX_PLAYER_NAME],
		str[1012];

	GetPVarString(playerid, "LookupName", name, MAX_PLAYER_NAME);

	if(!cache_num_rows()) {
		SendErrorMessage(playerid, "There is no unpaid tickets on %s.", name);
		ReturnMDC(playerid);
	}
	else {

		for(new i = 0; i < cache_num_rows(); i++) {

			new date[24], reason[120];
			cache_get_value_name(i, "ticketDate", date, sizeof(date));
			cache_get_value_name(i, "ticketReason", reason, sizeof(reason));

			strcat(str, sprintf("Date: %s | Reason: %s\n", date, reason));
		}
		ShowPlayerDialog(playerid, DIALOG_MDC_RETURN, DIALOG_STYLE_LIST, "MDC > Unpaid Tickets Lookup", str, "Return", "");
	}
	DeletePVar(playerid, "LookupName");
	return 1;
}

function OnLookupCrimeRecord(playerid) {
	
	new string[1512], count = 0;

	strcat(string, "Date\tCharge\tIssued By\tStatus\n");
	if(!cache_num_rows()) {
		strcat(string, "There is no crime record to view.");
		ShowPlayerDialog(playerid, DIALOG_NONE, DIALOG_STYLE_TABLIST_HEADERS, "MDC > Crime Record", string, "Close", "");
	}
	else {
		for(new i = 0; i < cache_num_rows(); i++) {
			new issuer_name[24],
				date[18],
				status,
				description[64],
				sql_id;

			cache_get_value_name_int(i, "ID", sql_id);
			cache_get_value_name(i, "Issuer", issuer_name, 24);
			cache_get_value_name(i, "Date", date, 18);
			cache_get_value_name_int(i, "Status", status);
			cache_get_value_name(i, "Description", description, 64);

			strcat(string, sprintf("%s\t%s\t%s\t%s\n", date, description, issuer_name, (status) ? (""YELLOW"Active") : (""RED"Not Active")));
			ListedItems[playerid][count++] = sql_id;
		}
		ShowPlayerDialog(playerid, DIALOG_CRIMERECORD, DIALOG_STYLE_TABLIST_HEADERS, "MDC > Crime Record", string, "Toggle", "Close");
	}
	return 1;
}
function OnLookupArrestMDC(playerid) {

	new name[MAX_PLAYER_NAME],
		str[1312];

	GetPVarString(playerid, "LookupName", name, MAX_PLAYER_NAME);

	if(!cache_num_rows()) {
		SendErrorMessage(playerid, "There is no arrest history on %s.", name);
		ReturnMDC(playerid);
	}
	else {

		for(new i = 0; i < cache_num_rows(); i++) {
			new reason[64],
				date[24];

			cache_get_value_name(i, "reason", reason, 64);
			cache_get_value_name(i, "date", date, 24);

			strcat(str, sprintf("Date: %s >> Reason: %s\n", date, reason));
		}
		ShowPlayerDialog(playerid, DIALOG_MDC_RETURN, DIALOG_STYLE_LIST, "MDC > Arrest History Lookup", str, "Return", "");
	}
	DeletePVar(playerid, "LookupName");
	return 1;
}
function OnLookupInformationMDC(playerid) {

	if(!cache_num_rows()) {
		SendErrorMessage(playerid, "We couldn't find data for specified name.");
		ReturnMDC(playerid);
		return 1;
	}


	new name[MAX_PLAYER_NAME],
		str[1512],
		number,
		drivelic,
		origin[32],
		dob[24],
		gender,
		idcard,
		sql_id,
		job,
		lumber,
		Cache:veh_check;

	cache_get_value_name_int(0, "IDCard", idcard);

	if(!idcard) {
		SendErrorMessage(playerid, "We couldn't find data for specified name.");
		ReturnMDC(playerid);
		return 1;
	}

	cache_get_value_name(0, "Name", name, MAX_PLAYER_NAME);
	cache_get_value_name(0, "Origin", origin, 32);
	cache_get_value_name(0, "Birthdate", dob, 24);
	cache_get_value_name_int(0, "Number", number);	
	cache_get_value_name_int(0, "Gender", gender);
	cache_get_value_name_int(0, "IDCardExpired", idcard);
	cache_get_value_name_int(0, "DrivingLicense", drivelic);
	cache_get_value_name_int(0, "pID", sql_id);
	cache_get_value_name_int(0, "Job", job);
	cache_get_value_name_int(0, "LumberLicense", lumber);
	
	strcat(str, sprintf("{AAC4E5}I. Personal information\n"WHITE"Personal ID: "YELLOW"SA%07d\n"WHITE"Name: "YELLOW"%s\n", sql_id, name));
	strcat(str, sprintf(""WHITE"Phone Number: "YELLOW"%d\n"WHITE"Job: "YELLOW"%s\n", number, GetJobName(job)));
	strcat(str, "\n{AAC4E5}II. Licenses"WHITE"\n");
	if(drivelic) strcat(str, sprintf("Driving: ["GREEN"Passed"WHITE"]\n"));
	else strcat(str, "Driving: ["RED"Not Passed"WHITE"]\n");
	if(lumber) strcat(str, sprintf("Lumberjack: ["GREEN"Passed"WHITE"]\n"));
	else strcat(str, "Lumberjack: ["RED"Not Passed"WHITE"]\n");

	strcat(str, "\n{AAC4E5}III. Registered Vehicle"WHITE"\n");
	veh_check = mysql_query(sqlcon, sprintf("SELECT * FROM `vehicle` WHERE `vehExtraID` = '%d' AND `vehType` = '%d' ORDER BY `vehID` ASC;", sql_id, 1));
    if(!cache_num_rows())
        strcat(str, "None\n");

    for(new i = 0; i < cache_num_rows(); i++)
    {
        new plate[32],
            model;

        cache_get_value_name(i, "vehPlate", plate, 16);
		cache_get_value_name_int(i, "vehModel", model);

        if(!strcmp(plate, "NONE", true))
        {
            continue;
        }
        else
        {
            strcat(str, sprintf(""WHITE"%d. "CYAN"%s - "YELLOW"P: %s"WHITE"\n", (i + 1), ReturnVehicleModelName(model), plate));
        }
    }
	cache_delete(veh_check);

	ShowPlayerDialog(playerid, DIALOG_MDC_RETURN, DIALOG_STYLE_MSGBOX, "MDC > Summary", str, "Return", "");
	DeletePVar(playerid, "LookupName");
	return 1;
}


function OnLookupVehicle(playerid, string:plate[]) {
	if(!cache_num_rows())
		return SendErrorMessage(playerid, "Data for plate \"%s\" not found.", plate), ReturnMDC(playerid);

	new owner, modelid, name[24], sqlid, str[512], vehicleid;
	cache_get_value_name_int(0, "vehID", sqlid);
	cache_get_value_name_int(0, "vehExtraID", owner);
	cache_get_value_name_int(0, "vehModel", modelid);

	inline const QueryLookupVeh() {
		if(cache_num_rows()) {

			cache_get_value_name(0, "Name", name, 24);

			strcat(str, "{AAC4E5}I. Owner Data\n");
			strcat(str, sprintf(""WHITE"Name: "YELLOW"%s\n\n", name));
			strcat(str, "{AAC4E5}II. Vehicle Data\n");
			strcat(str, sprintf(""WHITE"Model: "YELLOW"%s\n", ReturnVehicleModelName(modelid)));
			strcat(str, sprintf(""WHITE"Plate: "YELLOW"%s\n", plate));

			if((vehicleid = Vehicle_GetFromID(sqlid)) != -1) {
				new Float:x, Float:y, Float:z;
				GetVehiclePos(vehicleid, x,y,z);
				strcat(str, sprintf(""WHITE"Last Seen: "YELLOW"%s", GetLocation(x, y, z)));
			}

			ShowPlayerDialog(playerid, DIALOG_MDC_RETURN, DIALOG_STYLE_MSGBOX, "MDC > Vehicle Lookup", str, "Return", "");
		}	
		else SendErrorMessage(playerid, "There is an error when lookup vehicle data (report to developer)"), ReturnMDC(playerid);
	}
	
	MySQL_TQueryInline(sqlcon, using inline QueryLookupVeh, "SELECT * FROM `characters` WHERE `pID` = %d LIMIT 1;", owner);

	return 1;
}
function OnLookupMDC(playerid, string:namez[]) {
	if(!cache_num_rows())
		return SendErrorMessage(playerid, "Citizen with name %s is unregistered name.", namez), ReturnMDC(playerid);

	new name[MAX_PLAYER_NAME], sql_id;
	cache_get_value_name(0, "Name", name, MAX_PLAYER_NAME);
	cache_get_value_name_int(0, "pID", sql_id);

	SetPVarString(playerid, "LookupName", name);
	
	SetPVarInt(playerid, "LookupID", sql_id);
	ShowPlayerDialog(playerid, DIALOG_MDC_CITIZEN_MENU, DIALOG_STYLE_LIST, "MDC > Lookup Menu", "Summary\nArrest history\nUnpaid tickets\nCrime record", "Select", "Close");
	return 1;
}

SendFactionMessageEx(faction, color, const str[], {Float,_}:...)
{
	static
	    args,
	    start,
	    end,
	    string[256]
	;
	#emit LOAD.S.pri 8
	#emit STOR.pri args

	if (args > 8)
	{
		#emit ADDR.pri str
		#emit STOR.pri start

	    for (end = start + (args - 8); end > start; end -= 4)
		{
	        #emit LREF.pri end
	        #emit PUSH.pri
		}
		#emit PUSH.S str
		#emit PUSH.C 144
		#emit PUSH.C string

		#emit LOAD.S.pri 8
		#emit ADD.C 4
		#emit PUSH.pri

		#emit SYSREQ.C format
		#emit LCTRL 5
		#emit SCTRL 4

        foreach (new i : Player)
		{
			if (GetFactionType(i) == faction)
			{
  				SendClientMessage(i, color, string);
			}
		}
		return 1;
	}
	foreach (new i : Player)
	{
		if (GetFactionType(i) == faction) {
			SendClientMessage(i, color, str);
		}
	}
	return 1;
}

SendFactionMessage(factionid, color, const str[], {Float,_}:...)
{
	static
	    args,
	    start,
	    end,
	    string[144]
	;
	#emit LOAD.S.pri 8
	#emit STOR.pri args

	if (args > 12)
	{
		#emit ADDR.pri str
		#emit STOR.pri start

	    for (end = start + (args - 12); end > start; end -= 4)
		{
	        #emit LREF.pri end
	        #emit PUSH.pri
		}
		#emit PUSH.S str
		#emit PUSH.C 144
		#emit PUSH.C string
		#emit PUSH.C args

		#emit SYSREQ.C format
		#emit LCTRL 5
		#emit SCTRL 4

		foreach (new i : Player) if (PlayerData[i][pFaction] == factionid) 
		{
		    SendClientMessage(i, color, string);
		}
		return 1;
	}
	foreach (new i : Player) if (PlayerData[i][pFaction] == factionid) 
	{
 		SendClientMessage(i, color, str);
	}
	return 1;
}

SetFactionSkin(playerid, model)
{
	SetPlayerSkin(playerid, model);
	PlayerData[playerid][pFactionSkin] = model;
}
ResetFaction(playerid)
{
    PlayerData[playerid][pFaction] = -1;
    PlayerData[playerid][pFactionID] = -1;
    PlayerData[playerid][pFactionRank] = 0;
    PlayerData[playerid][pOnDuty] = false;
    SetPlayerSkin(playerid, PlayerData[playerid][pSkin]);
    SetPlayerColor(playerid, COLOR_WHITE);
}

CountFaction(faction)
{
	new count = 0;
	foreach(new i : Player) if(GetFactionType(i) == faction && PlayerData[i][pOnDuty])
	{
		count++;
	}
	return count;
}

CMD:gov(playerid, params[]) {
    if(isnull(params))
        return SendSyntaxMessage(playerid, "/gov [text]");
    if(PlayerData[playerid][pFactionRank] > FactionData[PlayerData[playerid][pFaction]][factionRanks] - 3)
        if(GetFactionType(playerid) == FACTION_POLICE) {
            SendClientMessageToAllEx(FactionData[PlayerData[playerid][pFaction]][factionColor],"|___________ Government News Announcement ___________|");
            SendClientMessageToAllEx(FactionData[PlayerData[playerid][pFaction]][factionColor],"** %s: %s %s: %s **",GetInitials(Faction_GetName(playerid)),Faction_GetRank(playerid), GetName(playerid, false) ,params);
        }
        else if(GetFactionType(playerid) == FACTION_MEDIC) {
            SendClientMessageToAllEx(FactionData[PlayerData[playerid][pFaction]][factionColor],"|___________ Government News Announcement ___________|");
            SendClientMessageToAllEx(FactionData[PlayerData[playerid][pFaction]][factionColor],"** %s: %s %s: %s **",GetInitials(Faction_GetName(playerid)),Faction_GetRank(playerid), GetName(playerid, false) ,params);
        }
        else if(GetFactionType(playerid) == FACTION_GOV) {
            SendClientMessageToAllEx(FactionData[PlayerData[playerid][pFaction]][factionColor],"|___________ Government News Announcement ___________|");
            SendClientMessageToAllEx(FactionData[PlayerData[playerid][pFaction]][factionColor],"** %s: %s %s: %s **",GetInitials(Faction_GetName(playerid)),Faction_GetRank(playerid), GetName(playerid, false) ,params);
        }
        else
            return SendErrorMessage(playerid,"You're not in any government faction");
    else
        return SendErrorMessage(playerid, "Kamu harus pada rank %d untuk menggunakan ini.", FactionData[PlayerData[playerid][pFaction]][factionRanks] - 1);
    return 1;
}

CMD:mdc(playerid, params[])
{
	if(GetFactionType(playerid) != FACTION_POLICE && GetFactionType(playerid) != FACTION_MEDIC)
		return SendErrorMessage(playerid, "You don't have permission to use this command!");

	ShowMDC(playerid);
	return 1;
}

CMD:megaphone(playerid, params[])
	return cmd_m(playerid, params);

CMD:m(playerid, params[])
{
	if (GetFactionType(playerid) != FACTION_POLICE && GetFactionType(playerid) != FACTION_MEDIC && GetFactionType(playerid) != FACTION_GOV)
		return SendErrorMessage(playerid, "You must be a part of Departement Faction!");

	if(!PlayerData[playerid][pOnDuty])
	    return SendErrorMessage(playerid, "You can't use this while not onduty.");
	    
	if(isnull(params))
	    return SendSyntaxMessage(playerid, "/m(egaphone) [megaphone]");
	    
    SendNearbyMessage(playerid, 60.0, COLOR_YELLOW, "[MEGAPHONE] %s: %s", ReturnName(playerid), params);
    return 1;
}

CMD:callsign(playerid, params[])
{
    new vehicleid;
    vehicleid = GetPlayerVehicleID(playerid);
	new string[32];
	if(!IsPlayerInAnyVehicle(playerid))
		return SendErrorMessage(playerid, "You're not in a vehicle.");
		
	if (GetFactionType(playerid) != FACTION_POLICE && GetFactionType(playerid) != FACTION_MEDIC)
		return SendErrorMessage(playerid, "You must be a LSPD or LSES!");
		
	if (!IsPoliceVehicle(GetPlayerVehicleID(playerid)) && !IsMedicVehicle(GetPlayerVehicleID(playerid)))
		return SendErrorMessage(playerid, "You must be inside a police or medic vehicles");
	    
	if(vehiclecallsign[GetPlayerVehicleID(playerid)] == 1)
	{
 		DestroyDynamic3DTextLabel(vehicle3Dtext[vehicleid]);
	    vehiclecallsign[vehicleid] = 0;

	    SendClientMessage(playerid, COLOR_SERVER, "(Callsign) {FFFFFF}Vehicle Callsign removed.");
	    return 1;
	}
	if(sscanf(params, "s[32]",string))
		return SendSyntaxMessage(playerid, "/callsign [callsign]");
		
	if(!vehiclecallsign[GetPlayerVehicleID(playerid)])
	{
		vehicle3Dtext[vehicleid] = CreateDynamic3DTextLabel(string, -1, 0.0, -2.8, 0.0, 10.0,INVALID_PLAYER_ID, GetPlayerVehicleID(playerid));
		vehiclecallsign[vehicleid] = 1;
		SendClientMessage(playerid, COLOR_SERVER, "CALLSIGN: {FFFFFF}Type {FFFF00}/callsign {FFFFFF}again to remove.");
	}
	return 1;
}

CMD:showbadge(playerid, params[])
{
    static
        userid;

    if(PlayerData[playerid][pFaction] == -1)
        return SendErrorMessage(playerid, "You must be a faction member.");

    if(GetFactionType(playerid) == FACTION_FAMILY)
        return SendErrorMessage(playerid, "This faction can't show a badge.");

    if(sscanf(params, "u", userid))
        return SendSyntaxMessage(playerid, "/showbadge [playerid]");

    if(userid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, userid, 5.0))
        return SendErrorMessage(playerid, "That player is disconnected or not near you.");

    SendClientMessageEx(userid, X11_WHITE,"====== [ Badge of {%06x}%s "WHITE"] ======", FactionData[PlayerData[playerid][pFaction]][factionColor] >>> 8, FactionData[PlayerData[playerid][pFaction]][factionName]);
    SendClientMessageEx(userid, X11_LIGHTBLUE, "Full Name: "GREEN"%s.", ReturnName(playerid));
    SendClientMessageEx(userid, X11_LIGHTBLUE, "Badge Number: "GREEN"%s. %03d.", GetInitials(Faction_GetRank(playerid)), PlayerData[playerid][pFactionBadge]);
    SendClientMessageEx(userid, X11_LIGHTBLUE, "Rank: "GREEN"%s.", Faction_GetRank(playerid));
    cmd_me(playerid, sprintf("showing his badge to %s", ReturnName(userid)));
    return 1;
}


CMD:r(playerid, params[])
{
	new
		text[144];

	if (GetFactionType(playerid) != FACTION_POLICE && GetFactionType(playerid) != FACTION_MEDIC && GetFactionType(playerid) != FACTION_GOV && GetFactionType(playerid) != FACTION_NEWS)
	    return SendErrorMessage(playerid, "You must be a civil service worker.");

	if(sscanf(params, "s[144]", text))
		return SendSyntaxMessage(playerid, "/r(adio) [IC Radio]");

	new
	    string[128];
		
	format(string, sizeof(string), "[RADIO] %s", text);
 	SetPlayerChatBubble(playerid, string, COLOR_RADIO, 30.0, 5000);

	strreplace(text, "@", sprintf("%03d",PlayerData[playerid][pFactionBadge]), .limit = 1);


	if (strlen(text) > 64)
	{
  		SendFactionMessage(PlayerData[playerid][pFaction], COLOR_RADIO, "[RADIO] %s %s: %.64s", Faction_GetRank(playerid), GetName(playerid), text);
		SendFactionMessage(PlayerData[playerid][pFaction], COLOR_RADIO, "...%s", text[64]);
	}
	else
	{
		SendFactionMessage(PlayerData[playerid][pFaction], COLOR_RADIO, "[RADIO] %s %s: %.64s", Faction_GetRank(playerid), GetName(playerid), text);
	}
	return 1;
}

CMD:d(playerid, params[])
{
	if (GetFactionType(playerid) != FACTION_POLICE && GetFactionType(playerid) != FACTION_MEDIC && GetFactionType(playerid) != FACTION_GOV)
	    return SendErrorMessage(playerid, "You must be a civil service worker.");

	if (isnull(params))
	    return SendSyntaxMessage(playerid, "/d(ept) [department radio]");

	params[0] = toupper(params[0]);
	for (new i = 0; i != MAX_FACTIONS; i ++) if (FactionData[i][factionType] == FACTION_POLICE || FactionData[i][factionType] == FACTION_MEDIC || FactionData[i][factionType] == FACTION_GOV) {
		SendFactionMessage(i, COLOR_DEPARTMENT, "[%s] %s %s: %s", GetInitials(Faction_GetName(playerid)), Faction_GetRank(playerid), GetName(playerid), params);
	}
	return 1;
}

CMD:trace(playerid, params[]) {

	if(GetFactionType(playerid) != FACTION_POLICE)
		return SendErrorMessage(playerid, "This command only allowed for Police Department.");

	new 
		number,
		targetid,
		Float:x, Float:y, Float:z;

	if(sscanf(params, "d", number))
		return SendSyntaxMessage(playerid, "/trace [phone number]");

	if(!PlayerData[playerid][pOnDuty])
		return SendErrorMessage(playerid, "You must onduty first!");

	if((targetid = GetNumberOwner(number)) != INVALID_PLAYER_ID) {

		if (!PlayerHasItem(playerid, "Cellphone") || PlayerData[targetid][pPhoneOff])
			return SendErrorMessage(playerid, "The specified phone number went offline.");

		DisablePlayerCheckpoint(playerid);

		GetPlayerPos(targetid, x, y, z);
		if(!IsPlayerInAnyVehicle(playerid))
			SetPlayerCheckpoint(playerid, x, y, z, 5.0), PlayerData[playerid][pTracing] = true;
		else 
			SetVehicleCheckpoint(GetPlayerVehicleID(playerid), x, y, z, 5.0, true);
	} 
	else SendErrorMessage(playerid, "You have specified invalid phone number.");
	return 1;
}
CMD:backup(playerid, params[]) {
	if (GetFactionType(playerid) != FACTION_POLICE && GetFactionType(playerid) != FACTION_MEDIC && GetFactionType(playerid) != FACTION_GOV)
	    return SendErrorMessage(playerid, "You must be a civil service worker.");

	ShowPlayerDialog(playerid, DIALOG_BACKUP, DIALOG_STYLE_LIST, "Backup", "SFPD\nSFFD", "Select", "Close");
	return 1;
}
CMD:od(playerid, params[])
{
	if (GetFactionType(playerid) != FACTION_POLICE && GetFactionType(playerid) != FACTION_MEDIC && GetFactionType(playerid) != FACTION_GOV)
	    return SendErrorMessage(playerid, "You must be a civil service worker.");

	if (isnull(params))
	    return SendSyntaxMessage(playerid, "/od [ooc department radio]");

	for (new i = 0; i != MAX_FACTIONS; i ++) if (FactionData[i][factionType] == FACTION_POLICE || FactionData[i][factionType] == FACTION_MEDIC || FactionData[i][factionType] == FACTION_GOV) {
		SendFactionMessage(i, COLOR_DEPARTMENT, " (( [%s] %s: %s ))", GetInitials(Faction_GetName(playerid)), GetName(playerid), params);
	}
	return 1;
}

CMD:or(playerid, params[])
{
    new factionid = PlayerData[playerid][pFaction];

 	if (factionid == -1)
	    return SendErrorMessage(playerid, "You must be a faction member.");

	if (isnull(params))
	    return SendSyntaxMessage(playerid, "/or [ooc radio message]");

	SendFactionMessage(factionid, 0x01FCFFC8, "(( (%d) %s %s: %s ))", PlayerData[playerid][pFactionRank], Faction_GetRank(playerid), GetName(playerid), params);
	return 1;
}

CMD:detain(playerid, params[])
{
	new
		userid,
		vehicleid = GetNearestVehicle(playerid, 5.0);

	if (GetFactionType(playerid) != FACTION_POLICE && GetFactionType(playerid) != FACTION_MEDIC)
		return SendErrorMessage(playerid, "You must be a police officer or emergency service!");

	if (sscanf(params, "u", userid))
	    return SendSyntaxMessage(playerid, "/detain [playerid/name]");

	if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "That player is disconnected.");

    if (userid == playerid)
	    return SendErrorMessage(playerid, "You cannot detained yourself.");

    if (!IsPlayerNearPlayer(playerid, userid, 3.0))
	    return SendErrorMessage(playerid, "You must be near this player.");

	if (vehicleid == INVALID_VEHICLE_ID)
	    return SendErrorMessage(playerid, "You are not near any vehicle.");

	if (GetVehicleMaxSeats(vehicleid) < 2)
  	    return SendErrorMessage(playerid, "You can't detain that player in this vehicle.");

	if (IsPlayerInVehicle(userid, vehicleid))
	{
		TogglePlayerControllable(userid, 1);

		RemovePlayerFromVehicle(userid);
		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "* %s opens the door and pulls %s out the vehicle.", ReturnName(playerid), ReturnName(userid));
	
		defer CuffPlayerBack[2000](userid);
	}
	else
	{
		new seatid = GetAvailableSeat(vehicleid, 2);

		if (seatid == -1)
		    return SendErrorMessage(playerid, "There are no more seats remaining.");

		new
		    string[64];

		format(string, sizeof(string), "You've been ~r~detained~w~ by %s.", ReturnName(playerid));
		RemoveDrag(userid);
		TogglePlayerControllable(userid, 0);

		PutPlayerInVehicle(userid, vehicleid, seatid);

		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "* %s opens the door and places %s into the vehicle.", ReturnName(playerid), ReturnName(userid));
		ShowMessage(userid, string, 2);
	}
	return 1;
}

CMD:factions(playerid, params[])
{
	new str[512]; 
	for(new i = 0; i < MAX_FACTIONS; i++) if(FactionData[i][factionExists])
	{
		if(FactionData[i][factionType] == FACTION_FAMILY) 
			format(str, sizeof(str), "%s{FFFFFF}[ID: %d] {%06x}%s\n", str, i, FactionData[i][factionColor] >>> 8, FactionData[i][factionName]);
		else 
			format(str, sizeof(str), "%s{FFFFFF}[ID: %d] {%06x}%s - (%d duty)\n", str, i, FactionData[i][factionColor] >>> 8, FactionData[i][factionName], Faction_CountDutyByID(i));
	}
	ShowPlayerDialog(playerid, DIALOG_NONE, DIALOG_STYLE_MSGBOX, "Faction List", str, "Close", "");
	return 1;
}


timer CuffPlayerBack[1000](userid) {
	if(PlayerData[userid][pCuffed]) {
		SetPlayerSpecialAction(userid, SPECIAL_ACTION_CUFFED);

		for(new i=MAX_PLAYER_ATTACHED_OBJECTS-1; i!=0; i--)
		{
			if(!IsPlayerAttachedObjectSlotUsed(userid, i))
			{
				SetPlayerArmedWeapon(userid, 0);
				SetPVarInt(userid, "Cuff_Index", i);
				SetPlayerAttachedObject(userid, i, 19418, 6, -0.027999, 0.051999, -0.030000, -18.699926, 0.000000, 104.199928, 1.489999, 3.036000, 1.957999);
				break;
			}
		}
	}
	return 1;
}