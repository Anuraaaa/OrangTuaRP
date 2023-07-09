new Float:ArrestPoint[][] = 
{
    {1366.4015,1571.7664,1468.7877},
    {1366.3246,1579.0751,1468.7877},
    {1363.3896,1581.9220,1468.7877}
};

SetPlayerArrest(playerid)
{
    FreezePlayer(playerid, 3000);
    new rand = random(3);

    SetPlayerInterior(playerid, 16);
    SetPlayerPos(playerid, ArrestPoint[rand][0], ArrestPoint[rand][1], ArrestPoint[rand][2]);
    ResetWeapons(playerid);
    PlayerTextDrawShow(playerid, JAILTD[playerid]);
    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
    PlayerData[playerid][pCuffed] = false;
    RemovePlayerAttachedObject(playerid, GetPVarInt(playerid, "Cuff_Index"));

    return 1;
}


CMD:beanbag(playerid, params[])
{
	if(GetFactionType(playerid) == FACTION_POLICE)
	{
		if(GetWeapon(playerid) != 25) 
            return SendErrorMessage(playerid, "You must be holding a shotgun to use this.");

		HasRubberBullet[playerid] = !(HasRubberBullet[playerid]);

		if(HasRubberBullet[playerid]) SendNearbyMessage(playerid, 15.0 , X11_PLUM, "** %s has equipped beanbag shells into his shotgun", ReturnName(playerid));
		else SendNearbyMessage(playerid, 15.0 , X11_PLUM, "** %s has unequipped beanbag shells from his shotgun", ReturnName(playerid));
	}
	else return SendErrorMessage(playerid, "You must be police officer to use beanbag.");
	return true;
}

CMD:cuff(playerid, params[])
{
    new
        userid;

    if (GetFactionType(playerid) != FACTION_POLICE)
        return SendErrorMessage(playerid, "You must be a police officer.");
        
    if (sscanf(params, "u", userid))
        return SendSyntaxMessage(playerid, "/cuff [playerid/name]");

    if (userid == INVALID_PLAYER_ID)
        return SendErrorMessage(playerid, "That player is disconnected.");

    if (!IsPlayerNearPlayer(playerid, userid, 5.0))
        return SendErrorMessage(playerid, "You must be near this player.");

    if (GetPlayerState(userid) != PLAYER_STATE_ONFOOT)
        return SendErrorMessage(playerid, "The player must be onfoot before you can cuff them.");

    if (PlayerData[userid][pCuffed])
        return SendErrorMessage(playerid, "The player is already cuffed at the moment.");

    static
        string[64];

    PlayerData[userid][pCuffed] = true;

    format(string, sizeof(string), "You've been cuffed by ~r~%s", GetName(playerid));
    ShowMessage(userid, string, 3);
    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "* %s tightens a pair of handcuffs on %s's wrists.", ReturnName(playerid), ReturnName(userid));
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
    return 1;
}

CMD:seizeweed(playerid, params[])
{
    if (GetFactionType(playerid) != FACTION_POLICE)
        return SendErrorMessage(playerid, "You must be a police officer.");

    new id = Weed_Nearest(playerid);
    if(id == -1)
        return SendErrorMessage(playerid, "You are not in range of any weed.");

    SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "* %s performing seized a plant.", ReturnName(playerid));
    Weed_Delete(id);
    ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 0, 0, 0, 0, 0, 1);
    return 1;
}
CMD:uncuff(playerid, params[])
{
    new
        userid;

    if (GetFactionType(playerid) != FACTION_POLICE)
        return SendErrorMessage(playerid, "You must be a police officer.");

    if (sscanf(params, "u", userid))
        return SendSyntaxMessage(playerid, "/uncuff [playerid/name]");

    if (userid == INVALID_PLAYER_ID)
        return SendErrorMessage(playerid, "That player is disconnected.");

    if (!IsPlayerNearPlayer(playerid, userid, 5.0))
        return SendErrorMessage(playerid, "You must be near this player.");

    if (GetPlayerState(userid) != PLAYER_STATE_ONFOOT)
        return SendErrorMessage(playerid, "The player must be onfoot before you can uncuff them.");

    if (!PlayerData[userid][pCuffed])
        return SendErrorMessage(playerid, "The player is not cuffed at the moment.");

    static
        string[64];

    PlayerData[userid][pCuffed] = false;

    format(string, sizeof(string), "You've been uncuffed by ~g~%s", GetName(playerid));
    ShowMessage(userid, string, 3);
    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "* %s taken outs handcuffs from %s's wrists.", ReturnName(playerid), ReturnName(userid));
    RemovePlayerAttachedObject(userid, GetPVarInt(userid, "Cuff_Index"));
    SetPlayerSpecialAction(userid, SPECIAL_ACTION_NONE);
    return 1;
}

CMD:arrest(playerid, params[])
{
    new
        userid,
        time;

    if (GetFactionType(playerid) != FACTION_POLICE)
        return SendErrorMessage(playerid, "You must be a officer.");

    if (!IsPlayerInRangeOfPoint(playerid, 5.0, 1360.5981,1575.5034,1468.7885))
        return SendErrorMessage(playerid, "You must be near an arrest point.");

    if (sscanf(params, "ud", userid, time))
        return SendSyntaxMessage(playerid, "/arrest [playerid/PartOfName] [minutes]");

    if (userid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, userid, 5.0))
        return SendErrorMessage(playerid, "The player is disconnected or not near you.");

  /*  if(userid == playerid)
        return SendErrorMessage(playerid, "You can't arrest yourself.");*/
        
    if (time < 1 || time > 120)
        return SendErrorMessage(playerid, "The specified time can't be below 1 or above 120.");

    if (!PlayerData[userid][pCuffed])
        return SendErrorMessage(playerid, "The player must be cuffed before an arrest is made.");

    PlayerData[playerid][pTarget] = userid;
    SetPVarInt(playerid, "ArrestTime", time);
    SetPVarInt(playerid, "TargetID", userid);
    ShowPlayerDialog(playerid, DIALOG_ARREST, DIALOG_STYLE_INPUT, sprintf("Arrest - %s", ReturnName(userid)), sprintf("Masukkan denda penjara untuk %s.", ReturnName(userid)), "Arrest", "Close");
    return 1;
}

CMD:grant(playerid, params[]) {

    if (GetFactionType(playerid) != FACTION_POLICE)
        return SendErrorMessage(playerid, "You must be a police officer.");

    if(!PlayerData[playerid][pOnDuty])
        return SendErrorMessage(playerid, "You must faction duty to use this command!");

    new targetid, str[24], string[128];
    if(sscanf(params, "s[24]S()[128]", str, string))
        return SendSyntaxMessage(playerid, "/grant [item name]"), SendClientMessage(playerid, -1, "ITEM NAME: lumberjack, hauling");

    if(!strcmp(str, "lumberjack", true)) {

        if(sscanf(string, "u", targetid))
            return SendSyntaxMessage(playerid, "/grant [lumberjack] [playerid/PartOfName]");

        if(!IsPlayerNearPlayer(playerid, targetid, 5.0) || targetid == INVALID_PLAYER_ID)
            return SendErrorMessage(playerid, "You have specified invalid player.");

        if(targetid == playerid)
            return SendErrorMessage(playerid, "Kamu tidak bisa memberikan lisensi ini kepada diri sendiri.");

        if(PlayerData[targetid][pLicense][2])
            return SendErrorMessage(playerid, "Player tersebut sudah memiliki lisensi Lumberjack!");

        PlayerData[targetid][pLicense][2] = true;
        SendClientMessageEx(targetid, X11_LIGHTBLUE, "(License) "WHITE"%s telah mengizinkan "YELLOW"Lumberjack License "WHITE"kepadamu.", ReturnName(playerid));
        SendClientMessageEx(playerid, X11_LIGHTBLUE, "(License) Kamu telah mengizinkan "YELLOW"Lumberjack License "WHITE"kepada %s.", ReturnName(targetid));
    }
    else if(!strcmp(str, "hauling", true)) {
        if(sscanf(string, "u", targetid))
            return SendSyntaxMessage(playerid, "/grant [hauling] [playerid/PartOfName]");

        if(!IsPlayerNearPlayer(playerid, targetid, 5.0) || targetid == INVALID_PLAYER_ID)
            return SendErrorMessage(playerid, "You have specified invalid player.");

        if(targetid == playerid)
            return SendErrorMessage(playerid, "Kamu tidak bisa memberikan lisensi ini kepada diri sendiri.");

        if(PlayerData[targetid][pLicense][3])
            return SendErrorMessage(playerid, "Player tersebut sudah memiliki lisensi Lumberjack!");

        PlayerData[targetid][pLicense][3] = true;
        SendClientMessageEx(targetid, X11_LIGHTBLUE, "(License) "WHITE"%s telah mengizinkan "YELLOW"Hauling License "WHITE"kepadamu.", ReturnName(playerid));
        SendClientMessageEx(playerid, X11_LIGHTBLUE, "(License) "WHITE"Kamu telah mengizinkan "YELLOW"Hauling License "WHITE"kepada %s.", ReturnName(targetid));
    }
    return 1;
}
CMD:tirelock(playerid, params[]) {


    if (GetFactionType(playerid) != FACTION_POLICE)
        return SendErrorMessage(playerid, "You must be a police officer.");

    new
        vehicleid = INVALID_VEHICLE_ID;

    vehicleid = GetNearestVehicle(playerid, 5.0);

    if(vehicleid == INVALID_VEHICLE_ID) 
        return SendErrorMessage(playerid, "There is no vehicle in range of you.");

    if(Vehicle_GetType(vehicleid) != VEHICLE_TYPE_PLAYER)
        return SendErrorMessage(playerid, "This is not a Player vehicle.");

    if(!VehicleData[vehicleid][vTireLock]) {

        VehicleData[vehicleid][vTireLock] = true;

        if(!IsValidDynamic3DTextLabel(VehicleData[vehicleid][vTireLockText]))
            VehicleData[vehicleid][vTireLockText] = CreateDynamic3DTextLabel("** Vehicle Tire locked **", -1, VehicleData[vehicleid][vPos][0], VehicleData[vehicleid][vPos][1], VehicleData[vehicleid][vPos][2], 15, INVALID_PLAYER_ID, vehicleid, 1);
        
        GetVehiclePos(vehicleid, VehicleData[vehicleid][vPos][0], VehicleData[vehicleid][vPos][1], VehicleData[vehicleid][vPos][2]);
        GetVehicleZAngle(vehicleid,  VehicleData[vehicleid][vPos][3]);

        VehicleData[vehicleid][vTireLockTimer] = repeat OnVehicleTireLock[3000](vehicleid);

        SwitchVehicleEngine(vehicleid, false);
        SendNearbyMessage(playerid, 20.0, X11_PLUM, "** %s pairs a tire lock on %s.", ReturnName(playerid), GetVehicleName(vehicleid));

        foreach(new i : Player) if(Vehicle_IsOwner(i, vehicleid)) {
            SendClientMessageEx(i, X11_LIGHTBLUE, "(Tirelock) {FFFFFF}Your vehicle "YELLOW"(%s) "WHITE"is "RED"tirelocked "WHITE"by %s.", GetVehicleName(vehicleid), ReturnName(playerid));
            break;
        }
    }
    else {

        VehicleData[vehicleid][vTireLock] = false;

        if(IsValidDynamic3DTextLabel(VehicleData[vehicleid][vTireLockText]))
            DestroyDynamic3DTextLabel(VehicleData[vehicleid][vTireLockText]);

        stop VehicleData[vehicleid][vTireLockTimer];

        SendNearbyMessage(playerid, 20.0, X11_PLUM, "** %s removes a tire lock from %s.", ReturnName(playerid), GetVehicleName(vehicleid));
    }
    return 1;
}
CMD:impound(playerid, params[])
{
	new
		price[24],
		vehicleid = GetPlayerVehicleID(playerid);

    if (GetFactionType(playerid) != FACTION_POLICE)
		return SendErrorMessage(playerid, "This command is only for Police Department.");

	if (!IsPlayerInRangeOfPoint(playerid, 7.0,-1634.1038,653.5013,7.1875))
		return SendErrorMessage(playerid, "You are not in range of impound point.");

	if (GetVehicleModel(vehicleid) != 525)
	    return SendErrorMessage(playerid, "You are not driving a tow truck.");

	if (!GetVehicleTrailer(vehicleid))
	    return SendErrorMessage(playerid, "There is no vehicle hooked.");


	if (Vehicle_GetType(GetVehicleTrailer(vehicleid)) != VEHICLE_TYPE_PLAYER)
	    return SendErrorMessage(playerid, "You only can impound player vehicle!");

    if (sscanf(params, "s[24]", price))
        return SendSyntaxMessage(playerid, "/impound [price]");

	if (strcash(price) < 100)
	    return SendErrorMessage(playerid, "The price can't be below $1.00");

	VehicleData[GetVehicleTrailer(vehicleid)][vImpound] = 1;
	VehicleData[GetVehicleTrailer(vehicleid)][vImpoundPrice] = strcash(price);
    VehicleData[GetVehicleTrailer(vehicleid)][vState] = VEHICLE_STATE_IMPOUNDED;

	SendFactionMessage(PlayerData[playerid][pFaction], COLOR_RADIO, "[IMPOUND] %s has impounded a %s for $%s.", ReturnName(playerid), ReturnVehicleModelName(GetVehicleModel(GetVehicleTrailer(vehicleid))), FormatNumber(strcash(price)));
 	
    foreach(new i : Player) if(VehicleData[GetVehicleTrailer(vehicleid)][vExtraID] == PlayerData[i][pID]) {

        SendCustomMessage(i, X11_LIGHTBLUE, "Impound", "Kendaraan "YELLOW"%s "WHITE"mu telah diimpound oleh "RED"%s"WHITE".", GetVehicleName(GetVehicleTrailer(vehicleid)), ReturnName(playerid));
        break;
    }
    Vehicle_Save(GetVehicleTrailer(vehicleid), false);
    Vehicle_Delete(GetVehicleTrailer(vehicleid), false);

    DetachTrailerFromVehicle(vehicleid);
	return 1;
}

CMD:take(playerid, params[])
{
    new
        userid,
        string[128];

    if(GetFactionType(playerid) != FACTION_POLICE)
        return SendErrorMessage(playerid, "You must be a police officer.");

    if(!PlayerData[playerid][pOnDuty])
        return SendErrorMessage(playerid, "You must duty first.");

    if(sscanf(params, "u", userid))
        return SendSyntaxMessage(playerid, "/take [playerid/PartOfName]");

    if(userid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, userid, 5.0))
        return SendErrorMessage(playerid, "That player is disconnected or not near you.");

    if(ReturnWeaponCount(userid) > 0)
        strcat(string, "Take Weapons\n");

    if(PlayerHasItem(userid, "Weed") || PlayerHasItem(userid, "Rolled Weed") || PlayerHasItem(userid, "Weed Seed"))
        strcat(string, "Take Drugs\n");

    if(PlayerHasItem(userid, "9mm Luger") || (PlayerHasItem(userid, "12 Gauge") || PlayerHasItem(userid, "9mm Silenced Schematic") || PlayerHasItem(userid, "Shotgun Schematic") || PlayerHasItem(userid, "9mm Silenced Material") || PlayerHasItem(userid, "Shotgun Material")))
        strcat(string, "Take weapon parts\n");

    if(!strlen(string))
        return SendErrorMessage(playerid, "This player has no illegal items to take.");

    PlayerData[playerid][pTarget] = userid;
    ShowPlayerDialog(playerid, DIALOG_TAKE, DIALOG_STYLE_LIST, "Take Items", string, "Take", "Cancel");
    return 1;
}

CMD:su(playerid, params[]) {
    new targetid, description[64];

    if(GetFactionType(playerid) != FACTION_POLICE)
        return SendErrorMessage(playerid, "This command is only for San Andreas Police Departement!");

    if(sscanf(params, "us[64]", targetid, description))
        return SendSyntaxMessage(playerid, "/su [playerid/PartOfName] [charge/description]");

    if(targetid == INVALID_PLAYER_ID)
        return SendErrorMessage(playerid, "You have specified invalid player.");

    if(strlen(description) > 64)
        return SendErrorMessage(playerid, "Karakter deskripsi tidak dapat lebih dari 64 huruf.");

    new query[712];
    mysql_format(sqlcon, query, 712, "INSERT INTO `crime_record` (`PlayerID`, `Issuer`, `Description`, `Status`, `Date`) VALUES('%d','%e','%e','%d','%e')", PlayerData[targetid][pID], GetName(playerid, false), description, 1, ReturnDate(false));
    mysql_tquery(sqlcon, query);

    SendFactionMessage(PlayerData[playerid][pFaction], X11_BLUE, "CRIME RECORD: "WHITE"Suspect: [ %s ] Issued By: [ %s ]", GetName(targetid, false), GetName(playerid, false));
    SendFactionMessage(PlayerData[playerid][pFaction], X11_BLUE, "CRIME RECORD: "WHITE"Charge: [ %s ] Status: [ "YELLOW"Active "WHITE"]", description);
    return 1;

}
CMD:tazer(playerid, params[])
{
    if(GetFactionType(playerid) != FACTION_POLICE)
        return SendErrorMessage(playerid, "This command is only for San Andreas Police Departement!");

    if(!PlayerData[playerid][pTazer])
    {
        
        for(new i=MAX_PLAYER_ATTACHED_OBJECTS-1; i!=0; i--)
        {
            if(!IsPlayerAttachedObjectSlotUsed(playerid, i))
            {
                SetPlayerArmedWeapon(playerid, 0);
                SetPVarInt(playerid, "Tazer_Index", i);
                PlayerData[playerid][pTazer] = true;
                SetPlayerAttachedObject(playerid, i, 18642, 6, 0.06, 0.01, 0.08, 180.0, 0.0, 0.0);
                SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "* %s takes out a tazer from their utility belt.", ReturnName(playerid));
                return 1;
            }
        }
    }
    else
    {
        PlayerData[playerid][pTazer] = false;
        RemovePlayerAttachedObject(playerid, GetPVarInt(playerid, "Tazer_Index"));
        DeletePVar(playerid, "Tazer_Index");
        SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "* %s puts their tazer into their utility belt.", ReturnName(playerid));
    }
    return 1;
}
