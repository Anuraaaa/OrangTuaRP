#include <YSI_Coding\y_hooks>

new PlayerText:NAVIGATORTD[MAX_PLAYERS][2];
new PlayerText:ARAHANGIN[MAX_PLAYERS];
new PlayerText:NAMAJALAN[MAX_PLAYERS];

new
    bool:Navigated[MAX_PLAYERS];

hook OnPlayerConnect(playerid) {

	NAVIGATORTD[playerid][0] = CreatePlayerTextDraw(playerid, 167.000000, 395.000000, "ld_dual:white");
	PlayerTextDrawFont(playerid, NAVIGATORTD[playerid][0], 4);
	PlayerTextDrawLetterSize(playerid, NAVIGATORTD[playerid][0], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, NAVIGATORTD[playerid][0], 2.000000, 28.500000);
	PlayerTextDrawSetOutline(playerid, NAVIGATORTD[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, NAVIGATORTD[playerid][0], 0);
	PlayerTextDrawAlignment(playerid, NAVIGATORTD[playerid][0], 1);
	PlayerTextDrawColor(playerid, NAVIGATORTD[playerid][0], -1061109505);
	PlayerTextDrawBackgroundColor(playerid, NAVIGATORTD[playerid][0], 255);
	PlayerTextDrawBoxColor(playerid, NAVIGATORTD[playerid][0], 50);
	PlayerTextDrawUseBox(playerid, NAVIGATORTD[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, NAVIGATORTD[playerid][0], 1);
	PlayerTextDrawSetSelectable(playerid, NAVIGATORTD[playerid][0], 0);

    ARAHANGIN[playerid] = CreatePlayerTextDraw(playerid, 151.000000, 402.000000, "IDK");
    PlayerTextDrawFont(playerid, ARAHANGIN[playerid], 1);
    PlayerTextDrawLetterSize(playerid, ARAHANGIN[playerid], 0.304166, 1.899999);
    PlayerTextDrawTextSize(playerid, ARAHANGIN[playerid], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, ARAHANGIN[playerid], 1);
    PlayerTextDrawSetShadow(playerid, ARAHANGIN[playerid], 0);
    PlayerTextDrawAlignment(playerid, ARAHANGIN[playerid], 2);
    PlayerTextDrawColor(playerid, ARAHANGIN[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, ARAHANGIN[playerid], 255);
    PlayerTextDrawBoxColor(playerid, ARAHANGIN[playerid], 50);
    PlayerTextDrawUseBox(playerid, ARAHANGIN[playerid], 0);
    PlayerTextDrawSetProportional(playerid, ARAHANGIN[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, ARAHANGIN[playerid], 0);

	NAMAJALAN[playerid] = CreatePlayerTextDraw(playerid, 174.000000, 410.000000, "_");
	PlayerTextDrawFont(playerid, NAMAJALAN[playerid], 1);
	PlayerTextDrawLetterSize(playerid, NAMAJALAN[playerid], 0.204166, 1.200000);
	PlayerTextDrawTextSize(playerid, NAMAJALAN[playerid], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, NAMAJALAN[playerid], 1);
	PlayerTextDrawSetShadow(playerid, NAMAJALAN[playerid], 0);
	PlayerTextDrawAlignment(playerid, NAMAJALAN[playerid], 1);
	PlayerTextDrawColor(playerid, NAMAJALAN[playerid], -764862721);
	PlayerTextDrawBackgroundColor(playerid, NAMAJALAN[playerid], 255);
	PlayerTextDrawBoxColor(playerid, NAMAJALAN[playerid], 50);
	PlayerTextDrawUseBox(playerid, NAMAJALAN[playerid], 0);
	PlayerTextDrawSetProportional(playerid, NAMAJALAN[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, NAMAJALAN[playerid], 0);

	NAVIGATORTD[playerid][1] = CreatePlayerTextDraw(playerid, 174.000000, 398.000000, "San Andreas");
	PlayerTextDrawFont(playerid, NAVIGATORTD[playerid][1], 1);
	PlayerTextDrawLetterSize(playerid, NAVIGATORTD[playerid][1], 0.170833, 1.000000);
	PlayerTextDrawTextSize(playerid, NAVIGATORTD[playerid][1], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, NAVIGATORTD[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, NAVIGATORTD[playerid][1], 0);
	PlayerTextDrawAlignment(playerid, NAVIGATORTD[playerid][1], 1);
	PlayerTextDrawColor(playerid, NAVIGATORTD[playerid][1], -1094795521);
	PlayerTextDrawBackgroundColor(playerid, NAVIGATORTD[playerid][1], 255);
	PlayerTextDrawBoxColor(playerid, NAVIGATORTD[playerid][1], 50);
	PlayerTextDrawUseBox(playerid, NAVIGATORTD[playerid][1], 0);
	PlayerTextDrawSetProportional(playerid, NAVIGATORTD[playerid][1], 1);
	PlayerTextDrawSetSelectable(playerid, NAVIGATORTD[playerid][1], 0);

    Navigated[playerid] = false;
}

hook OnPlayerStateChange(playerid, newstate, oldstate) {
    if(newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER) {
        if(VehicleData[GetPlayerVehicleID(playerid)][vFactionType] == FACTION_POLICE || VehicleData[GetPlayerVehicleID(playerid)][vFactionType] == FACTION_MEDIC) {
            Navigator_Show(playerid);
        }
    }
    if(newstate == PLAYER_STATE_ONFOOT) {

        new vehicleid = PlayerData[playerid][pLastVehicleID];

		if(vehicleid != INVALID_VEHICLE_ID) {
        	if(VehicleData[vehicleid][vFactionType] == FACTION_POLICE || VehicleData[vehicleid][vFactionType] == FACTION_MEDIC) 
			{
				Navigator_Hide(playerid);
			}   
		}
    }
}

Navigator_Show(playerid) {
    PlayerTextDrawShow(playerid, NAVIGATORTD[playerid][0]);
    PlayerTextDrawShow(playerid, NAVIGATORTD[playerid][1]);
    PlayerTextDrawShow(playerid, NAMAJALAN[playerid]);
    PlayerTextDrawShow(playerid, ARAHANGIN[playerid]);

    return Navigated[playerid] = true;
}

Navigator_Hide(playerid) {

    PlayerTextDrawHide(playerid, NAVIGATORTD[playerid][0]);
    PlayerTextDrawHide(playerid, NAVIGATORTD[playerid][1]);
    PlayerTextDrawHide(playerid, NAMAJALAN[playerid]);
    PlayerTextDrawHide(playerid, ARAHANGIN[playerid]);

    return Navigated[playerid] = false;
}

ReturnCompass(playerid) {

    new direction[64], Float:rz;


	if(IsPlayerInAnyVehicle(playerid)) {
		GetVehicleZAngle(GetPlayerVehicleID(playerid), rz);
	}
	else {
		GetPlayerFacingAngle(playerid, rz);
	}

	if(rz >= 348.75 || rz < 11.25) direction = "N";
	else if(rz >= 326.25 && rz < 348.75) direction = "NNE";
	else if(rz >= 303.75 && rz < 326.25) direction = "NE";
	else if(rz >= 281.25 && rz < 303.75) direction = "ENE";
	else if(rz >= 258.75 && rz < 281.25) direction = "E";
	else if(rz >= 236.25 && rz < 258.75) direction = "ESE";
	else if(rz >= 213.75 && rz < 236.25) direction = "SE";
	else if(rz >= 191.25 && rz < 213.75) direction = "SSE";
	else if(rz >= 168.75 && rz < 191.25) direction = "S";
	else if(rz >= 146.25 && rz < 168.75) direction = "SSW";
	else if(rz >= 123.25 && rz < 146.25) direction = "SW";
	else if(rz >= 101.25 && rz < 123.25) direction = "WSW";
	else if(rz >= 78.75 && rz < 101.25) direction = "W";
	else if(rz >= 56.25 && rz < 78.75) direction = "WNW";
	else if(rz >= 33.75 && rz < 56.25) direction = "NW";
	else if(rz >= 11.5 && rz < 33.75) direction = "NNW";

    return direction;
}
ptask OnNavigatorUpdate[2000](playerid) {
    if(IsPlayerSpawned(playerid) && Navigated[playerid] && IsPlayerInAnyVehicle(playerid)) {

        new Float:x, Float:y, Float:z;
        GetPlayerPos(playerid, x, y, z);
        PlayerTextDrawSetString(playerid, NAMAJALAN[playerid], sprintf("%s", GetLocation(x, y, z)));

        PlayerTextDrawSetString(playerid, ARAHANGIN[playerid], sprintf("%s", ReturnCompass(playerid)));
    }
    return 1;
}