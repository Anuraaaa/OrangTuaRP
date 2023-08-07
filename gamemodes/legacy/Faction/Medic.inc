#include <YSI_Coding\y_hooks>


new STREAMER_TAG_OBJECT:StretcherEquipped[MAX_PLAYERS];
new StretcherHolding[MAX_PLAYERS];
new StretcherPlayerID[MAX_PLAYERS];
new StretcherTimer[MAX_PLAYERS];

function Float:DistanceBetweenPoints(Float:x1, Float:y1, Float:z1, Float:x2, Float:y2, Float:z2)
{
	return floatadd(floatadd(floatsqroot(floatpower(floatsub(x1,x2),2)),floatsqroot(floatpower(floatsub(y1,y2),2))),floatsqroot(floatpower(floatsub(z1,z2),2)));
}

function Float:GetXYInFrontOfPlayer(playerid, &Float:X, &Float:Y, Float:distance)
{
	new Float:A;
	GetPlayerPos(playerid, X, Y, A);

	if(IsPlayerInAnyVehicle(playerid)) GetVehicleZAngle(GetPlayerVehicleID(playerid), A);
	else GetPlayerFacingAngle(playerid, A);

	X += (distance * floatsin(-A, degrees));
	Y += (distance * floatcos(-A, degrees));

	return A;
}

IsPlayerOnStretcher(playerid) {
	new index = INVALID_PLAYER_ID;
	foreach(new i : Player) if(StretcherPlayerID[i] == playerid) {
		index = i;
		break;
	}
	return index;
}
SpawnStretcher(playerid)
{
	new Float:angle;
	GetPlayerFacingAngle(playerid, angle);
	SetPlayerFacingAngle(playerid, angle + 180);

	AttachDynamicObjectToPlayer(StretcherEquipped[playerid], playerid, 0.0, 1.4, -1.0, 0.0, 0.0, 180.0);

	SendClientMessage(playerid, COLOR_SERVER, "(Info) {FFFFFF}You now have a stretcher. Use /stretcher for actions.");
	return true;
}

function DestroyStretcher(playerid, objectid)
{
	if(IsValidDynamicObject(StretcherEquipped[playerid]))
		DestroyDynamicObject(StretcherEquipped[playerid]);

	StretcherTimer[playerid] = -1;
	StretcherEquipped[playerid] = INVALID_PLAYER_ID;
	StretcherHolding[playerid] = 0;

	return 1;
}


CMD:stretcher(playerid, params[])
{

	if(GetFactionType(playerid) != FACTION_MEDIC)
		return SendErrorMessage(playerid,"You need to be a member of the Medic Department!");
		
	new action[24], playa = -1, string[128];
	if (sscanf(params, "s[24]S()[128]", action, string))
	{
	    SendSyntaxMessage(playerid, "/stretcher [name]");
	    SendClientMessage(playerid, COLOR_YELLOW, "(Names){FFFFFF} equip/drop/pickup/putaway/load/unload/ambulance");
	    return 1;
	}
	new Float:pX,Float:pY,Float:pZ, Float:oX,Float:oY,Float:oZ;
	GetPlayerPos(playerid, pX, pY, pZ);
			
	if(!strcmp(action, "equip", true))
	{
		if(IsValidDynamicObject(StretcherEquipped[playerid]))
			return SendErrorMessage(playerid,"You already have a stretcher.");
		
		if(GetVehicleModel(GetPlayerVehicleID(playerid)) != 416)
			return SendErrorMessage(playerid,"You must be in the back of an Ambulance to get a stretcher.");

		if(GetPlayerVehicleSeat(playerid) != 2 && GetPlayerVehicleSeat(playerid) != 3)
			return SendErrorMessage(playerid,"You must be in the back of an Ambulance to get a stretcher.");
			
		RemovePlayerFromVehicle(playerid);

		SendNearbyMessage(playerid, 30.0, X11_PLUM, "** %s pulls a stretcher out of the Ambulance. *",ReturnName(playerid));

		if(!IsValidDynamicObject(StretcherEquipped[playerid]))
			StretcherEquipped[playerid] = CreateDynamicObject(1997, pX, pY + 1.5, pZ - 1.0, 0.0, 0.0, 100.0);

		StretcherHolding[playerid] = 1;
		StretcherPlayerID[playerid] = INVALID_PLAYER_ID;

		Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
	}
	else if(!strcmp(action, "drop", true))
	{
		new Float:pXb, Float:pYb;
		new Float:Ang = GetXYInFrontOfPlayer(playerid, pXb, pYb, 1.7);

		if(StretcherHolding[playerid] == 0)
			return SendErrorMessage(playerid,"You need to have a stretcher.");
		
		if(StretcherPlayerID[playerid] != INVALID_PLAYER_ID)
			return SendErrorMessage(playerid,"You can not drop the stretcher with someone on it");

		if(IsValidDynamicObject(StretcherEquipped[playerid]))
			DestroyDynamicObject(StretcherEquipped[playerid]);

		StretcherEquipped[playerid] = CreateDynamicObject(1997, pXb, pYb, pZ-1.0, 0.0, 0.0, Ang+180);
		StretcherHolding[playerid] = 0;

		StretcherTimer[playerid] = SetTimerEx("DestroyStretcher", 300000, 0, "ii", playerid, StretcherEquipped[playerid]);
		Streamer_Update(playerid, STREAMER_TYPE_OBJECT);

		SendNearbyMessage(playerid, 30.0, X11_PLUM, "** %s locks the wheels of the stretcher in place. *",ReturnName(playerid));
	}
	else if(!strcmp(action, "pickup", true))
	{
		GetDynamicObjectPos(StretcherEquipped[playerid],oX,oY,oZ);
		new Float:distance = DistanceBetweenPoints(pX,pY,pZ,oX,oY,oZ);
		
		if(!IsValidDynamicObject(StretcherEquipped[playerid]))
			return SendErrorMessage(playerid,"You need to have a stretcher.");
		
		if(StretcherPlayerID[playerid] != INVALID_PLAYER_ID)
			return SendErrorMessage(playerid,"You can not drop the stretcher with someone on it");

		if(StretcherHolding[playerid] == 2)
			return SendErrorMessage(playerid,"You already have a stretcher");
		
		if(distance > 5)
			return SendErrorMessage(playerid,"You aren't close enough");

		KillTimer(StretcherTimer[playerid]);
		StretcherTimer[playerid] = -1;
		StretcherHolding[playerid] = 2;

		SendNearbyMessage(playerid, 30.0, X11_PLUM, "** %s unlocks the wheels of the stretcher *",ReturnName(playerid));
	}
	else if(!strcmp(action, "putaway", true))
	{
		if(!IsValidDynamicObject(StretcherEquipped[playerid]))
			return SendErrorMessage(playerid,"You do not have a stretcher to put away.");
			
		if(StretcherPlayerID[playerid] != INVALID_PLAYER_ID)
			return SendErrorMessage(playerid,"Please unload the stretcher before putting it away.");

		new Float:vX, Float:vY, Float:vZ;
		foreach(new v : Vehicle) if(IsValidVehicle(v) && GetVehicleModel(v) == 416)
		{
			GetVehiclePos(v, vX, vY, vZ);
			if(IsPlayerInRangeOfPoint(playerid, 10.0, vX, vY, vZ))
			{
				if(IsValidDynamicObject(StretcherEquipped[playerid]))
					DestroyDynamicObject(StretcherEquipped[playerid]);
					
				StretcherHolding[playerid] = 0;

				SendNearbyMessage(playerid, 30.0, X11_PLUM, "** %s puts their stretcher into the back of the Ambulance. *",ReturnName(playerid));
				return 1;
			}
		}
		SendErrorMessage(playerid,"You must be near an Ambulance in order to put a stretcher away.");

	}
	else if(!strcmp(action, "load", true))
	{
		if(!IsValidDynamicObject(StretcherEquipped[playerid]))
			return SendErrorMessage(playerid,"You must have a stretcher to load someone on it.");
			
		if(StretcherPlayerID[playerid] != INVALID_PLAYER_ID)
			return SendErrorMessage(playerid,"You already have someone loaded on the stretcher.");

	    if (sscanf(string, "u", playa))
	        return SendSyntaxMessage(playerid,"/stretcher load [playerid/name]");
			 
		if(playa == INVALID_PLAYER_ID)
			return SendErrorMessage(playerid,"That player is not connected.");
			
		if(playa == playerid)
			return SendErrorMessage(playerid,"You may not do this to yourself.");
			
		if(IsValidDynamicObject(StretcherEquipped[playa]))
			return SendErrorMessage(playerid,"You may not put someone with a stretcher on a stretcher.");
			
		if(!StretcherHolding[playerid])
			return SendErrorMessage(playerid, "You need to be holding the stretcher");

		new Float:tX,Float:tY,Float:tZ;
		GetPlayerPos(playa,tX,tY,tZ);
		
		if(!IsPlayerInRangeOfPoint(playerid,3.5,tX,tY,tZ))
			return SendErrorMessage(playerid,"You must be close to the player to put them on a stretcher.");

		StretcherPlayerID[playerid] = playa;
		ApplyAnimation(playa,"BEACH", "bather", 4.0, 1, 0, 0, 1, -1, 1);

		SendNearbyMessage(playerid, 30.0, X11_PLUM, "** %s is now pulling the stretcher with %s on it. *", GetName(playerid), GetName(StretcherPlayerID[playerid]));

		SendServerMessage(playerid, "%s in now on your stretcher. You can get them off using '/stretcher unload'",ReturnName(StretcherPlayerID[playerid]));

		SendServerMessage(StretcherPlayerID[playerid] ,"%s has put you onto their stretcher.",ReturnName(playerid));

	}
	else if(!strcmp(action, "unload", true))
	{
		if(!IsValidDynamicObject(StretcherEquipped[playerid]))
			return SendErrorMessage(playerid,"You must have a stretcher to load someone on it.");
			
		if(StretcherPlayerID[playerid] == INVALID_PLAYER_ID)
			return SendErrorMessage(playerid,"You don't even have someone loaded on the stretcher.");
			
		if(!StretcherHolding[playerid])
			return SendErrorMessage(playerid, "You need to be holding the stretcher");

		new Float:playerpos[4];
		TogglePlayerControllable(StretcherPlayerID[playerid], 1);
		GetPlayerPos(playerid, playerpos[0], playerpos[1], playerpos[2]);
		GetXYInFrontOfPlayer(playerid, playerpos[0], playerpos[1], -2);
		SetPlayerPos(StretcherPlayerID[playerid], playerpos[0], playerpos[1], playerpos[2]);
		ClearAnimations(StretcherPlayerID[playerid]);

		SendServerMessage(playerid,"%s has been removed from the stretcher.",ReturnName(StretcherPlayerID[playerid]));
		
		SendServerMessage(playerid,"%s has removed you from their stretcher.",ReturnName(playerid));

		StretcherPlayerID[playerid] = INVALID_PLAYER_ID;

	}
	else if(!strcmp(action, "ambulance", true))
	{
		if(!IsValidDynamicObject(StretcherEquipped[playerid]))
			return SendErrorMessage(playerid,"You must have a stretcher.");
			
		if(StretcherPlayerID[playerid] == -1)
			return SendErrorMessage(playerid,"You don't even have someone loaded on the stretcher.");

		new Float:vX, Float:vY, Float:vZ;
		foreach(new v : Vehicle) if(IsValidVehicle(v) && GetVehicleModel(v) == 416)
		{
			GetVehiclePos(v, vX, vY, vZ);
			if(IsPlayerInRangeOfPoint(playerid, 10.0, vX, vY, vZ))
			{
				new seatid = 2;
				foreach(new i : Player)
				{
					if(GetPlayerVehicleID(i) == v)
					{
						if(GetPlayerVehicleSeat(i) == 2) seatid = 3;
						if(GetPlayerVehicleSeat(i) == 3 && seatid == 3) seatid = -1;
					}
				}
				if(seatid == -1)
					return SendErrorMessage(playerid,"There are no seats free in the back of this Ambulance.");

				PutPlayerInVehicle(StretcherPlayerID[playerid], v, seatid);
				TogglePlayerControllable(StretcherPlayerID[playerid], 1);

				SendNearbyMessage(playerid, 30.0, X11_PLUM, "** %s pushes the stretcher with %s on it into the back of the Ambulance. *",ReturnName(playerid),ReturnName(StretcherPlayerID[playerid]));

				if(IsValidDynamicObject(StretcherEquipped[playerid]))
					DestroyDynamicObject(StretcherEquipped[playerid]);

				StretcherPlayerID[playerid] = INVALID_PLAYER_ID;
				StretcherHolding[playerid] = 0;
			}
		}
		SendErrorMessage(playerid,"You must be near an Ambulance in order to put a stretcher inside.");
		return 1;
	}

	return 1;
}

CMD:healme(playerid, params[]) {

	if(GetFactionType(playerid) != FACTION_MEDIC)
		return SendErrorMessage(playerid, "This command is only for Medic Department!!");

	if(!PlayerData[playerid][pOnDuty])
		return SendErrorMessage(playerid, "You must be faction duty first!");

	PlayerData[playerid][pInjured] = false;
	PlayerData[playerid][pDead] = false;
	PlayerData[playerid][pInjuredTime] = 0;
	ClearAnimations(playerid, 1);
	SendServerMessage(playerid, "Kamu berhasil menyembuhkan dirimu sendiri.");

	return 1;
}

CMD:inspect(playerid, params[]) {

	if(GetFactionType(playerid) != FACTION_MEDIC)
		return SendErrorMessage(playerid, "This command is only for Medic Department!");

	if(!PlayerData[playerid][pOnDuty])
		return SendErrorMessage(playerid, "You must be faction duty first!");

	new targetid;
	if(sscanf(params, "u", targetid))
		return SendErrorMessage(playerid, "/inspect [playerid/PartOfName]");

	if (!IsPlayerConnected(targetid) || !IsPlayerNearPlayer(playerid, targetid, 5.0))
	    return SendErrorMessage(playerid, "That player is disconnected or not near you.");

	DisplayHealth(playerid, targetid);
	return 1;
}
CMD:treatment(playerid, params[])
{
	if(GetFactionType(playerid) != FACTION_MEDIC)
		return SendErrorMessage(playerid, "This command is only for Medic Department!");

	if(!PlayerData[playerid][pOnDuty])
		return SendErrorMessage(playerid, "You must be faction duty first!");

	new targetid;
	if(sscanf(params, "u", targetid))
		return SendErrorMessage(playerid, "/treatment [playerid/PartOfName]");

	if(!IsPlayerNearPlayer(playerid, targetid, 5.0) || !IsPlayerConnected(targetid))
		return SendErrorMessage(playerid, "You must be close to that player!");

	PlayerData[playerid][pTargetid] = targetid;
	ShowPlayerDialog(playerid, DIALOG_TREATMENT, DIALOG_STYLE_LIST, "Treatment Menu", "Revive\nHeal\nCure\nOperate", "Select", "Close");
	return 1;
}

CMD:getmedkit(playerid, params[]) {

	new factionid = PlayerData[playerid][pFaction];

	if (factionid == -1)
		return SendErrorMessage(playerid, "You must be a faction member.");

	if(GetFactionType(playerid) != FACTION_MEDIC)
		return SendErrorMessage(playerid, "This command is only for Medical faction type.");

	if (!IsNearFactionLocker(playerid))
		return SendErrorMessage(playerid, "You are not in range of your faction's locker.");

	if(isnull(params))
		return SendSyntaxMessage(playerid, "/getmedkit [amount (max: 15)]");

	if(!IsNumeric(params))
			return SendSyntaxMessage(playerid, "/getmedkit [amount (max: 15)]");

	if(strval(params) < 1 || strval(params) > 15)
		return SendErrorMessage(playerid, "Invalid amount of medkit.");

	if(Inventory_Add(playerid, "Medkit", 1580, strval(params)) == -1)
		return 1;

	SendServerMessage(playerid, "Kamu mengambil %d medkit dari Faction Locker.", strval(params));
	SendNearbyMessage(playerid, 10.0, X11_PLUM, "** %s grabs %d amount of medkits from faction locker.", ReturnName(playerid),  strval(params));
	return 1;
}

CMD:getpills(playerid, params[]) {


	if(GetFactionType(playerid) != FACTION_MEDIC)
		return SendErrorMessage(playerid, "This command is only for Medical faction type.");

	if (!IsPlayerInRangeOfPoint(playerid, 6.0, -1437.7163,-1517.8572,3001.5059))
		return SendErrorMessage(playerid, "You are not in range of pharmacy point.");

	if(isnull(params))
		return SendSyntaxMessage(playerid, "/getpills [1. Promethazine, 2. Acetaminophen]");

	if(!IsNumeric(params))
			return SendSyntaxMessage(playerid, "/getpills [1. Promethazine, 2. Acetaminophen]");

	if(strval(params) < 1 || strval(params) > 2)
		return SendErrorMessage(playerid, "/getpills [1. Promethazine, 2. Acetaminophen]");


	new pill_name[][] = {
		"None",
		"Promethazine",
		"Acetaminophen"
	};

	if(GetMoney(playerid) < 1000)
		return SendErrorMessage(playerid, "Kamu harus memiliki $10.00 untuk mengambil pills.");

	GiveMoney(playerid, -1000, "Getpills");
	Inventory_Set(playerid, pill_name[strval(params)], 2709, 10);
	SendServerMessage(playerid, "Kamu mengambil %s dari Faction Locker.", pill_name[strval(params)]);
	SendNearbyMessage(playerid, 10.0, X11_PLUM, "** %s grabs a %s from faction locker.", ReturnName(playerid), pill_name[strval(params)]);
	return 1;
}

hook OnPlayerDisconnectEx(playerid) {
	new targetid;

	if((targetid = IsPlayerOnStretcher(playerid)) != INVALID_PLAYER_ID) {

		StretcherPlayerID[targetid] = INVALID_PLAYER_ID;
	}
}

hook OnPlayerInjured(playerid) {

	new msg[128], Float:x, Float:y, Float:z;

	ReturnSpecificLocation(playerid, x, y, z);

	format(msg, sizeof(msg), "Coordinate: %.1f, %.1f, %.1f~n~Location: %s", x, y, z, GetLocation(x, y, z));
	foreach(new i : Player) if(GetFactionType(i) == FACTION_MEDIC && PlayerData[i][pOnDuty]) {
		notification.Show(i, "Injured Person", msg, "hud:radar_gangG");
	}
}
hook OnPlayerConnect(playerid) {

	if(IsValidDynamicObject(StretcherEquipped[playerid]))
		DestroyDynamicObject(StretcherEquipped[playerid]);

	StretcherTimer[playerid] = 0;
	StretcherPlayerID[playerid] = INVALID_PLAYER_ID;
	StretcherEquipped[playerid] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
	StretcherHolding[playerid] = 0;
}