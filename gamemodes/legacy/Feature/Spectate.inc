new 
	PlayerText:spectateTD[MAX_PLAYERS][13];

SpectateTextdraws(playerid) {
    spectateTD[playerid][0] = CreatePlayerTextDraw(playerid, 319.000000, 332.000000, "_");
    PlayerTextDrawFont(playerid, spectateTD[playerid][0], 1);
    PlayerTextDrawLetterSize(playerid, spectateTD[playerid][0], 0.600000, 12.300003);
    PlayerTextDrawTextSize(playerid, spectateTD[playerid][0], 413.500000, 175.000000);
    PlayerTextDrawSetOutline(playerid, spectateTD[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, spectateTD[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, spectateTD[playerid][0], 2);
    PlayerTextDrawColor(playerid, spectateTD[playerid][0], -1);
    PlayerTextDrawBackgroundColor(playerid, spectateTD[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, spectateTD[playerid][0], 135);
    PlayerTextDrawUseBox(playerid, spectateTD[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, spectateTD[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, spectateTD[playerid][0], 0);

    spectateTD[playerid][1] = CreatePlayerTextDraw(playerid, 319.000000, 333.000000, "~y~~h~Orang Ganteng ~r~(10)");
    PlayerTextDrawFont(playerid, spectateTD[playerid][1], 1);
    PlayerTextDrawLetterSize(playerid, spectateTD[playerid][1], 0.224996, 1.450000);
    PlayerTextDrawTextSize(playerid, spectateTD[playerid][1], 440.000000, 134.000000);
    PlayerTextDrawSetOutline(playerid, spectateTD[playerid][1], 0);
    PlayerTextDrawSetShadow(playerid, spectateTD[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, spectateTD[playerid][1], 2);
    PlayerTextDrawColor(playerid, spectateTD[playerid][1], 16777214);
    PlayerTextDrawBackgroundColor(playerid, spectateTD[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, spectateTD[playerid][1], 30);
    PlayerTextDrawUseBox(playerid, spectateTD[playerid][1], 0);
    PlayerTextDrawSetProportional(playerid, spectateTD[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, spectateTD[playerid][1], 0);

    spectateTD[playerid][2] = CreatePlayerTextDraw(playerid, 319.000000, 346.000000, "~y~~h~Cash: ~g~$10.000,00");
    PlayerTextDrawFont(playerid, spectateTD[playerid][2], 1);
    PlayerTextDrawLetterSize(playerid, spectateTD[playerid][2], 0.224996, 1.450000);
    PlayerTextDrawTextSize(playerid, spectateTD[playerid][2], 440.000000, 134.000000);
    PlayerTextDrawSetOutline(playerid, spectateTD[playerid][2], 0);
    PlayerTextDrawSetShadow(playerid, spectateTD[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, spectateTD[playerid][2], 2);
    PlayerTextDrawColor(playerid, spectateTD[playerid][2], 16777215);
    PlayerTextDrawBackgroundColor(playerid, spectateTD[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, spectateTD[playerid][2], 30);
    PlayerTextDrawUseBox(playerid, spectateTD[playerid][2], 0);
    PlayerTextDrawSetProportional(playerid, spectateTD[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, spectateTD[playerid][2], 0);

    spectateTD[playerid][3] = CreatePlayerTextDraw(playerid, 266.000000, 360.000000, "~y~~h~Health: ~r~~h~100%");
    PlayerTextDrawFont(playerid, spectateTD[playerid][3], 1);
    PlayerTextDrawLetterSize(playerid, spectateTD[playerid][3], 0.224996, 1.450000);
    PlayerTextDrawTextSize(playerid, spectateTD[playerid][3], 440.000000, 134.000000);
    PlayerTextDrawSetOutline(playerid, spectateTD[playerid][3], 0);
    PlayerTextDrawSetShadow(playerid, spectateTD[playerid][3], 0);
    PlayerTextDrawAlignment(playerid, spectateTD[playerid][3], 2);
    PlayerTextDrawColor(playerid, spectateTD[playerid][3], 16777215);
    PlayerTextDrawBackgroundColor(playerid, spectateTD[playerid][3], 255);
    PlayerTextDrawBoxColor(playerid, spectateTD[playerid][3], 30);
    PlayerTextDrawUseBox(playerid, spectateTD[playerid][3], 0);
    PlayerTextDrawSetProportional(playerid, spectateTD[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, spectateTD[playerid][3], 0);

    spectateTD[playerid][4] = CreatePlayerTextDraw(playerid, 365.000000, 360.000000, "~y~~h~Armour: ~w~~h~100%");
    PlayerTextDrawFont(playerid, spectateTD[playerid][4], 1);
    PlayerTextDrawLetterSize(playerid, spectateTD[playerid][4], 0.224996, 1.449998);
    PlayerTextDrawTextSize(playerid, spectateTD[playerid][4], 440.000000, 134.000000);
    PlayerTextDrawSetOutline(playerid, spectateTD[playerid][4], 0);
    PlayerTextDrawSetShadow(playerid, spectateTD[playerid][4], 0);
    PlayerTextDrawAlignment(playerid, spectateTD[playerid][4], 2);
    PlayerTextDrawColor(playerid, spectateTD[playerid][4], 16777215);
    PlayerTextDrawBackgroundColor(playerid, spectateTD[playerid][4], 255);
    PlayerTextDrawBoxColor(playerid, spectateTD[playerid][4], 30);
    PlayerTextDrawUseBox(playerid, spectateTD[playerid][4], 0);
    PlayerTextDrawSetProportional(playerid, spectateTD[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, spectateTD[playerid][4], 0);

    spectateTD[playerid][5] = CreatePlayerTextDraw(playerid, 266.000000, 373.000000, "~y~~h~Interior: ~y~100");
    PlayerTextDrawFont(playerid, spectateTD[playerid][5], 1);
    PlayerTextDrawLetterSize(playerid, spectateTD[playerid][5], 0.224996, 1.450000);
    PlayerTextDrawTextSize(playerid, spectateTD[playerid][5], 440.000000, 134.000000);
    PlayerTextDrawSetOutline(playerid, spectateTD[playerid][5], 0);
    PlayerTextDrawSetShadow(playerid, spectateTD[playerid][5], 0);
    PlayerTextDrawAlignment(playerid, spectateTD[playerid][5], 2);
    PlayerTextDrawColor(playerid, spectateTD[playerid][5], -2686721);
    PlayerTextDrawBackgroundColor(playerid, spectateTD[playerid][5], 255);
    PlayerTextDrawBoxColor(playerid, spectateTD[playerid][5], 30);
    PlayerTextDrawUseBox(playerid, spectateTD[playerid][5], 0);
    PlayerTextDrawSetProportional(playerid, spectateTD[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, spectateTD[playerid][5], 0);

    spectateTD[playerid][6] = CreatePlayerTextDraw(playerid, 360.000000, 373.000000, "~y~~h~Virtual World: ~y~100");
    PlayerTextDrawFont(playerid, spectateTD[playerid][6], 1);
    PlayerTextDrawLetterSize(playerid, spectateTD[playerid][6], 0.224996, 1.450000);
    PlayerTextDrawTextSize(playerid, spectateTD[playerid][6], 440.000000, 134.000000);
    PlayerTextDrawSetOutline(playerid, spectateTD[playerid][6], 0);
    PlayerTextDrawSetShadow(playerid, spectateTD[playerid][6], 0);
    PlayerTextDrawAlignment(playerid, spectateTD[playerid][6], 2);
    PlayerTextDrawColor(playerid, spectateTD[playerid][6], -2686721);
    PlayerTextDrawBackgroundColor(playerid, spectateTD[playerid][6], 255);
    PlayerTextDrawBoxColor(playerid, spectateTD[playerid][6], 30);
    PlayerTextDrawUseBox(playerid, spectateTD[playerid][6], 0);
    PlayerTextDrawSetProportional(playerid, spectateTD[playerid][6], 1);
    PlayerTextDrawSetSelectable(playerid, spectateTD[playerid][6], 0);

    spectateTD[playerid][7] = CreatePlayerTextDraw(playerid, 281.000000, 385.000000, "~y~~h~Weapon: ~r~Fist");
    PlayerTextDrawFont(playerid, spectateTD[playerid][7], 1);
    PlayerTextDrawLetterSize(playerid, spectateTD[playerid][7], 0.224996, 1.450000);
    PlayerTextDrawTextSize(playerid, spectateTD[playerid][7], 440.000000, 134.000000);
    PlayerTextDrawSetOutline(playerid, spectateTD[playerid][7], 0);
    PlayerTextDrawSetShadow(playerid, spectateTD[playerid][7], 0);
    PlayerTextDrawAlignment(playerid, spectateTD[playerid][7], 2);
    PlayerTextDrawColor(playerid, spectateTD[playerid][7], -2686721);
    PlayerTextDrawBackgroundColor(playerid, spectateTD[playerid][7], 255);
    PlayerTextDrawBoxColor(playerid, spectateTD[playerid][7], 30);
    PlayerTextDrawUseBox(playerid, spectateTD[playerid][7], 0);
    PlayerTextDrawSetProportional(playerid, spectateTD[playerid][7], 1);
    PlayerTextDrawSetSelectable(playerid, spectateTD[playerid][7], 0);

    spectateTD[playerid][8] = CreatePlayerTextDraw(playerid, 361.000000, 385.000000, "~y~~h~Ammo: ~r~55");
    PlayerTextDrawFont(playerid, spectateTD[playerid][8], 1);
    PlayerTextDrawLetterSize(playerid, spectateTD[playerid][8], 0.224996, 1.450000);
    PlayerTextDrawTextSize(playerid, spectateTD[playerid][8], 440.000000, 134.000000);
    PlayerTextDrawSetOutline(playerid, spectateTD[playerid][8], 0);
    PlayerTextDrawSetShadow(playerid, spectateTD[playerid][8], 0);
    PlayerTextDrawAlignment(playerid, spectateTD[playerid][8], 2);
    PlayerTextDrawColor(playerid, spectateTD[playerid][8], -2686721);
    PlayerTextDrawBackgroundColor(playerid, spectateTD[playerid][8], 255);
    PlayerTextDrawBoxColor(playerid, spectateTD[playerid][8], 30);
    PlayerTextDrawUseBox(playerid, spectateTD[playerid][8], 0);
    PlayerTextDrawSetProportional(playerid, spectateTD[playerid][8], 1);
    PlayerTextDrawSetSelectable(playerid, spectateTD[playerid][8], 0);

    spectateTD[playerid][9] = CreatePlayerTextDraw(playerid, 266.000000, 398.000000, "~y~~h~Ping: ~g~~h~45ms");
    PlayerTextDrawFont(playerid, spectateTD[playerid][9], 1);
    PlayerTextDrawLetterSize(playerid, spectateTD[playerid][9], 0.224996, 1.450000);
    PlayerTextDrawTextSize(playerid, spectateTD[playerid][9], 440.000000, 134.000000);
    PlayerTextDrawSetOutline(playerid, spectateTD[playerid][9], 0);
    PlayerTextDrawSetShadow(playerid, spectateTD[playerid][9], 0);
    PlayerTextDrawAlignment(playerid, spectateTD[playerid][9], 2);
    PlayerTextDrawColor(playerid, spectateTD[playerid][9], -2686721);
    PlayerTextDrawBackgroundColor(playerid, spectateTD[playerid][9], 255);
    PlayerTextDrawBoxColor(playerid, spectateTD[playerid][9], 30);
    PlayerTextDrawUseBox(playerid, spectateTD[playerid][9], 0);
    PlayerTextDrawSetProportional(playerid, spectateTD[playerid][9], 1);
    PlayerTextDrawSetSelectable(playerid, spectateTD[playerid][9], 0);

    spectateTD[playerid][10] = CreatePlayerTextDraw(playerid, 360.000000, 398.000000, "~y~~h~FPS: ~g~~h~60");
    PlayerTextDrawFont(playerid, spectateTD[playerid][10], 1);
    PlayerTextDrawLetterSize(playerid, spectateTD[playerid][10], 0.224996, 1.450000);
    PlayerTextDrawTextSize(playerid, spectateTD[playerid][10], 440.000000, 134.000000);
    PlayerTextDrawSetOutline(playerid, spectateTD[playerid][10], 0);
    PlayerTextDrawSetShadow(playerid, spectateTD[playerid][10], 0);
    PlayerTextDrawAlignment(playerid, spectateTD[playerid][10], 2);
    PlayerTextDrawColor(playerid, spectateTD[playerid][10], -2686721);
    PlayerTextDrawBackgroundColor(playerid, spectateTD[playerid][10], 255);
    PlayerTextDrawBoxColor(playerid, spectateTD[playerid][10], 30);
    PlayerTextDrawUseBox(playerid, spectateTD[playerid][10], 0);
    PlayerTextDrawSetProportional(playerid, spectateTD[playerid][10], 1);
    PlayerTextDrawSetSelectable(playerid, spectateTD[playerid][10], 0);

    spectateTD[playerid][11] = CreatePlayerTextDraw(playerid, 319.000000, 411.000000, "~y~~h~Vehicle Health: ~b~~h~1000.00");
    PlayerTextDrawFont(playerid, spectateTD[playerid][11], 1);
    PlayerTextDrawLetterSize(playerid, spectateTD[playerid][11], 0.224996, 1.450000);
    PlayerTextDrawTextSize(playerid, spectateTD[playerid][11], 440.000000, 134.000000);
    PlayerTextDrawSetOutline(playerid, spectateTD[playerid][11], 0);
    PlayerTextDrawSetShadow(playerid, spectateTD[playerid][11], 0);
    PlayerTextDrawAlignment(playerid, spectateTD[playerid][11], 2);
    PlayerTextDrawColor(playerid, spectateTD[playerid][11], -2686721);
    PlayerTextDrawBackgroundColor(playerid, spectateTD[playerid][11], 255);
    PlayerTextDrawBoxColor(playerid, spectateTD[playerid][11], 30);
    PlayerTextDrawUseBox(playerid, spectateTD[playerid][11], 0);
    PlayerTextDrawSetProportional(playerid, spectateTD[playerid][11], 1);
    PlayerTextDrawSetSelectable(playerid, spectateTD[playerid][11], 0);

    spectateTD[playerid][12] = CreatePlayerTextDraw(playerid, 319.000000, 424.000000, "~y~~h~Vehicle Speed: ~y~100km/h");
    PlayerTextDrawFont(playerid, spectateTD[playerid][12], 1);
    PlayerTextDrawLetterSize(playerid, spectateTD[playerid][12], 0.224996, 1.450000);
    PlayerTextDrawTextSize(playerid, spectateTD[playerid][12], 440.000000, 134.000000);
    PlayerTextDrawSetOutline(playerid, spectateTD[playerid][12], 0);
    PlayerTextDrawSetShadow(playerid, spectateTD[playerid][12], 0);
    PlayerTextDrawAlignment(playerid, spectateTD[playerid][12], 2);
    PlayerTextDrawColor(playerid, spectateTD[playerid][12], -2686721);
    PlayerTextDrawBackgroundColor(playerid, spectateTD[playerid][12], 255);
    PlayerTextDrawBoxColor(playerid, spectateTD[playerid][12], 30);
    PlayerTextDrawUseBox(playerid, spectateTD[playerid][12], 0);
    PlayerTextDrawSetProportional(playerid, spectateTD[playerid][12], 1);
    PlayerTextDrawSetSelectable(playerid, spectateTD[playerid][12], 0);
}

hook OnPlayerConnect(playerid) {

	for (new i = 0; i < 13; i++) {
		PlayerTextDrawDestroy(playerid, spectateTD[playerid][i]);
	}

	SpectateTextdraws(playerid);	
}

hook OnPlayerDisconnect(playerid, reason) {

	for (new i = 0; i < 13; i++) {
		PlayerTextDrawDestroy(playerid, spectateTD[playerid][i]);
	}
} 

hook OnPlayerStateChange(playerid, newstate, oldstate) {

	if (newstate == PLAYER_STATE_SPECTATING && GetPVarInt(playerid, "IsAtEvent") == 0 && !FlyMode[playerid]) {
		if (oldstate == PLAYER_STATE_ONFOOT) {

			for (new i = 0; i < 13; i++) {
				PlayerTextDrawShow(playerid, spectateTD[playerid][i]);
			}
		}
		else if (oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER) {
			
			for (new i = 0; i < 13; i++) {
				PlayerTextDrawShow(playerid, spectateTD[playerid][i]);
			}
		}
	}
	else if (oldstate == PLAYER_STATE_SPECTATING) {

		for (new i = 0; i < 13; i++) {
			PlayerTextDrawHide(playerid, spectateTD[playerid][i]);
		}
	}
}

ptask OnSpectateUpdate[1000](playerid) {
	
	if (IsPlayerConnected(playerid)) {

		if (GetPlayerState(playerid) == PLAYER_STATE_SPECTATING && PlayerData[playerid][pSpectator] != INVALID_PLAYER_ID) {

			new 
				targetid = PlayerData[playerid][pSpectator],
				Float:health,
				Float:armour,
				vehicleid = GetPlayerVehicleID(targetid);

			PlayerTextDrawSetString(playerid, spectateTD[playerid][1], sprintf("~y~~h~%s ~r~~h~(%d)", GetName(targetid), targetid));
			PlayerTextDrawSetString(playerid, spectateTD[playerid][2], sprintf("~y~~h~Cash ~g~$%s", FormatNumber(GetMoney(targetid))));

			PlayerTextDrawSetString(playerid, spectateTD[playerid][3], sprintf("~y~~h~Health: ~r~~h~%.0f%", GetPlayerHealth(targetid, health)));
			PlayerTextDrawSetString(playerid, spectateTD[playerid][4], sprintf("~y~~h~Armour: ~w~~h~%.0f%", GetPlayerArmour(targetid, armour)));

			PlayerTextDrawSetString(playerid, spectateTD[playerid][5], sprintf("~y~~h~Interior: ~y~%d", GetPlayerInterior(targetid)));
			PlayerTextDrawSetString(playerid, spectateTD[playerid][6], sprintf("~y~~h~Virtual World: ~y~%d", GetPlayerVirtualWorld(targetid)));

			PlayerTextDrawSetString(playerid, spectateTD[playerid][7], sprintf("~y~~h~Weapon: ~r~%s", ReturnWeaponName(GetPlayerWeapon(targetid))));

			if (GetPlayerWeapon(targetid) == 0)
				PlayerTextDrawSetString(playerid, spectateTD[playerid][7], sprintf("~y~~h~Ammo: ~r~-"));

			else if (GetPlayerWeapon(targetid) != 0) {

				for (new i = 0; i < 13; i++) {

					if (PlayerData[targetid][pGuns][i] == GetPlayerWeapon(targetid)) {
						PlayerTextDrawSetString(playerid, spectateTD[playerid][8], sprintf("~y~~h~Ammo: ~r~%d", PlayerData[targetid][pAmmo][i]));
					}
				}
			}

			if (GetPlayerPing(targetid) > 0 && GetPlayerPing(targetid) < 100)
				PlayerTextDrawSetString(playerid, spectateTD[playerid][9], sprintf("~y~~h~Ping: ~g~~h~%dms", GetPlayerPing(targetid)));

			else if (GetPlayerPing(targetid) >= 100 && GetPlayerPing(targetid) < 150)
				PlayerTextDrawSetString(playerid, spectateTD[playerid][9], sprintf("~y~~h~Ping: ~y~~h~%dms", GetPlayerPing(targetid)));

			else if (GetPlayerPing(targetid) >= 150)
				PlayerTextDrawSetString(playerid, spectateTD[playerid][9], sprintf("~y~~h~Ping: ~r~%dms", GetPlayerPing(targetid)));

			if (GetPlayerFPS(targetid) > 0 && GetPlayerFPS(targetid) <= 15)
				PlayerTextDrawSetString(playerid, spectateTD[playerid][10], sprintf("~y~~h~FPS: ~r~%d", GetPlayerFPS(targetid)));

			else if (GetPlayerFPS(targetid) > 15 && GetPlayerFPS(targetid) <= 30)
				PlayerTextDrawSetString(playerid, spectateTD[playerid][10], sprintf("~y~~h~FPS: ~y~%d", GetPlayerFPS(targetid)));

			else if (GetPlayerFPS(targetid) > 30 && GetPlayerFPS(targetid) <= 60)
				PlayerTextDrawSetString(playerid, spectateTD[playerid][10], sprintf("~y~~h~FPS: ~g~%d", GetPlayerFPS(targetid)));

			else if (GetPlayerFPS(targetid) > 60)
				PlayerTextDrawSetString(playerid, spectateTD[playerid][10], sprintf("~y~~h~FPS: ~g~~h~%d", GetPlayerFPS(targetid)));

			if (vehicleid == INVALID_VEHICLE_ID) {
				PlayerTextDrawSetString(playerid, spectateTD[playerid][11], sprintf("~y~~h~Vehicle Health: ~b~~h~-"));
				PlayerTextDrawSetString(playerid, spectateTD[playerid][12], sprintf("~y~~h~Vehicle Speed: ~y~-"));
			}
			else if (vehicleid != INVALID_VEHICLE_ID) {
				new Float:vhealth;
				PlayerTextDrawSetString(playerid, spectateTD[playerid][11], sprintf("~y~~h~Vehicle Health: ~b~~h~%.2f", GetVehicleHealth(vehicleid, vhealth)));
				PlayerTextDrawSetString(playerid, spectateTD[playerid][12], sprintf("~y~~h~Vehicle Speed: ~y~%d", floatround(GetVehicleSpeed(vehicleid))));
			}
		}
		else if (GetPlayerState(playerid) != PLAYER_STATE_SPECTATING) {
			for (new i = 0; i < 13; i++) {
				PlayerTextDrawHide(playerid, spectateTD[playerid][i]);
			}
		}
	}
}