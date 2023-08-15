new 
	PlayerText:spectateTD[MAX_PLAYERS][15];

SpectateTextdraws(playerid) {
	spectateTD[playerid][0] = CreatePlayerTextDraw(playerid, 318.000000, 253.000000, "_");
	PlayerTextDrawFont(playerid, spectateTD[playerid][0], 1);
	PlayerTextDrawLetterSize(playerid, spectateTD[playerid][0], 0.725000, 18.750011);
	PlayerTextDrawTextSize(playerid, spectateTD[playerid][0], 338.500000, 228.000000);
	PlayerTextDrawSetOutline(playerid, spectateTD[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, spectateTD[playerid][0], 0);
	PlayerTextDrawAlignment(playerid, spectateTD[playerid][0], 2);
	PlayerTextDrawColor(playerid, spectateTD[playerid][0], -1);
	PlayerTextDrawBackgroundColor(playerid, spectateTD[playerid][0], 255);
	PlayerTextDrawBoxColor(playerid, spectateTD[playerid][0], 150);
	PlayerTextDrawUseBox(playerid, spectateTD[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, spectateTD[playerid][0], 1);
	PlayerTextDrawSetSelectable(playerid, spectateTD[playerid][0], 0);

	spectateTD[playerid][1] = CreatePlayerTextDraw(playerid, 216.000000, 261.000000, "Orang_Ganteng");
	PlayerTextDrawFont(playerid, spectateTD[playerid][1], 1);
	PlayerTextDrawLetterSize(playerid, spectateTD[playerid][1], 0.537499, 2.349999);
	PlayerTextDrawTextSize(playerid, spectateTD[playerid][1], 407.000000, 2.000000);
	PlayerTextDrawSetOutline(playerid, spectateTD[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, spectateTD[playerid][1], 0);
	PlayerTextDrawAlignment(playerid, spectateTD[playerid][1], 1);
	PlayerTextDrawColor(playerid, spectateTD[playerid][1], 866792447);
	PlayerTextDrawBackgroundColor(playerid, spectateTD[playerid][1], 255);
	PlayerTextDrawBoxColor(playerid, spectateTD[playerid][1], 50);
	PlayerTextDrawUseBox(playerid, spectateTD[playerid][1], 0);
	PlayerTextDrawSetProportional(playerid, spectateTD[playerid][1], 1);
	PlayerTextDrawSetSelectable(playerid, spectateTD[playerid][1], 0);

	spectateTD[playerid][2] = CreatePlayerTextDraw(playerid, 385.000000, 262.000000, "(10)");
	PlayerTextDrawFont(playerid, spectateTD[playerid][2], 1);
	PlayerTextDrawLetterSize(playerid, spectateTD[playerid][2], 0.537499, 2.349999);
	PlayerTextDrawTextSize(playerid, spectateTD[playerid][2], 407.000000, 2.000000);
	PlayerTextDrawSetOutline(playerid, spectateTD[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, spectateTD[playerid][2], 0);
	PlayerTextDrawAlignment(playerid, spectateTD[playerid][2], 1);
	PlayerTextDrawColor(playerid, spectateTD[playerid][2], 866792447);
	PlayerTextDrawBackgroundColor(playerid, spectateTD[playerid][2], 255);
	PlayerTextDrawBoxColor(playerid, spectateTD[playerid][2], 50);
	PlayerTextDrawUseBox(playerid, spectateTD[playerid][2], 0);
	PlayerTextDrawSetProportional(playerid, spectateTD[playerid][2], 1);
	PlayerTextDrawSetSelectable(playerid, spectateTD[playerid][2], 0);

	spectateTD[playerid][3] = CreatePlayerTextDraw(playerid, 229.000000, 292.000000, "Level:");
	PlayerTextDrawFont(playerid, spectateTD[playerid][3], 1);
	PlayerTextDrawLetterSize(playerid, spectateTD[playerid][3], 0.549999, 2.749999);
	PlayerTextDrawTextSize(playerid, spectateTD[playerid][3], 407.000000, 2.000000);
	PlayerTextDrawSetOutline(playerid, spectateTD[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, spectateTD[playerid][3], 0);
	PlayerTextDrawAlignment(playerid, spectateTD[playerid][3], 1);
	PlayerTextDrawColor(playerid, spectateTD[playerid][3], -1);
	PlayerTextDrawBackgroundColor(playerid, spectateTD[playerid][3], 255);
	PlayerTextDrawBoxColor(playerid, spectateTD[playerid][3], 50);
	PlayerTextDrawUseBox(playerid, spectateTD[playerid][3], 0);
	PlayerTextDrawSetProportional(playerid, spectateTD[playerid][3], 1);
	PlayerTextDrawSetSelectable(playerid, spectateTD[playerid][3], 0);

	spectateTD[playerid][4] = CreatePlayerTextDraw(playerid, 290.000000, 293.000000, "~y~99");
	PlayerTextDrawFont(playerid, spectateTD[playerid][4], 1);
	PlayerTextDrawLetterSize(playerid, spectateTD[playerid][4], 0.549999, 2.749999);
	PlayerTextDrawTextSize(playerid, spectateTD[playerid][4], 407.000000, 2.000000);
	PlayerTextDrawSetOutline(playerid, spectateTD[playerid][4], 1);
	PlayerTextDrawSetShadow(playerid, spectateTD[playerid][4], 0);
	PlayerTextDrawAlignment(playerid, spectateTD[playerid][4], 1);
	PlayerTextDrawColor(playerid, spectateTD[playerid][4], 2094792959);
	PlayerTextDrawBackgroundColor(playerid, spectateTD[playerid][4], 255);
	PlayerTextDrawBoxColor(playerid, spectateTD[playerid][4], 50);
	PlayerTextDrawUseBox(playerid, spectateTD[playerid][4], 0);
	PlayerTextDrawSetProportional(playerid, spectateTD[playerid][4], 1);
	PlayerTextDrawSetSelectable(playerid, spectateTD[playerid][4], 0);

	spectateTD[playerid][5] = CreatePlayerTextDraw(playerid, 221.000000, 316.000000, "Money:");
	PlayerTextDrawFont(playerid, spectateTD[playerid][5], 1);
	PlayerTextDrawLetterSize(playerid, spectateTD[playerid][5], 0.524999, 3.049998);
	PlayerTextDrawTextSize(playerid, spectateTD[playerid][5], 407.000000, 2.000000);
	PlayerTextDrawSetOutline(playerid, spectateTD[playerid][5], 1);
	PlayerTextDrawSetShadow(playerid, spectateTD[playerid][5], 0);
	PlayerTextDrawAlignment(playerid, spectateTD[playerid][5], 1);
	PlayerTextDrawColor(playerid, spectateTD[playerid][5], -1);
	PlayerTextDrawBackgroundColor(playerid, spectateTD[playerid][5], 255);
	PlayerTextDrawBoxColor(playerid, spectateTD[playerid][5], 50);
	PlayerTextDrawUseBox(playerid, spectateTD[playerid][5], 0);
	PlayerTextDrawSetProportional(playerid, spectateTD[playerid][5], 1);
	PlayerTextDrawSetSelectable(playerid, spectateTD[playerid][5], 0);

	spectateTD[playerid][6] = CreatePlayerTextDraw(playerid, 293.000000, 320.000000, "$10,000");
	PlayerTextDrawFont(playerid, spectateTD[playerid][6], 1);
	PlayerTextDrawLetterSize(playerid, spectateTD[playerid][6], 0.487500, 2.449999);
	PlayerTextDrawTextSize(playerid, spectateTD[playerid][6], 407.000000, 2.000000);
	PlayerTextDrawSetOutline(playerid, spectateTD[playerid][6], 1);
	PlayerTextDrawSetShadow(playerid, spectateTD[playerid][6], 0);
	PlayerTextDrawAlignment(playerid, spectateTD[playerid][6], 1);
	PlayerTextDrawColor(playerid, spectateTD[playerid][6], 1433087999);
	PlayerTextDrawBackgroundColor(playerid, spectateTD[playerid][6], 255);
	PlayerTextDrawBoxColor(playerid, spectateTD[playerid][6], 50);
	PlayerTextDrawUseBox(playerid, spectateTD[playerid][6], 0);
	PlayerTextDrawSetProportional(playerid, spectateTD[playerid][6], 1);
	PlayerTextDrawSetSelectable(playerid, spectateTD[playerid][6], 0);

	spectateTD[playerid][7] = CreatePlayerTextDraw(playerid, 237.000000, 345.000000, "Ping:");
	PlayerTextDrawFont(playerid, spectateTD[playerid][7], 1);
	PlayerTextDrawLetterSize(playerid, spectateTD[playerid][7], 0.549999, 2.749999);
	PlayerTextDrawTextSize(playerid, spectateTD[playerid][7], 407.000000, 2.000000);
	PlayerTextDrawSetOutline(playerid, spectateTD[playerid][7], 1);
	PlayerTextDrawSetShadow(playerid, spectateTD[playerid][7], 0);
	PlayerTextDrawAlignment(playerid, spectateTD[playerid][7], 1);
	PlayerTextDrawColor(playerid, spectateTD[playerid][7], -1);
	PlayerTextDrawBackgroundColor(playerid, spectateTD[playerid][7], 255);
	PlayerTextDrawBoxColor(playerid, spectateTD[playerid][7], 50);
	PlayerTextDrawUseBox(playerid, spectateTD[playerid][7], 0);
	PlayerTextDrawSetProportional(playerid, spectateTD[playerid][7], 1);
	PlayerTextDrawSetSelectable(playerid, spectateTD[playerid][7], 0);

	spectateTD[playerid][8] = CreatePlayerTextDraw(playerid, 290.000000, 346.000000, "~r~212");
	PlayerTextDrawFont(playerid, spectateTD[playerid][8], 1);
	PlayerTextDrawLetterSize(playerid, spectateTD[playerid][8], 0.549999, 2.749999);
	PlayerTextDrawTextSize(playerid, spectateTD[playerid][8], 407.000000, 2.000000);
	PlayerTextDrawSetOutline(playerid, spectateTD[playerid][8], 1);
	PlayerTextDrawSetShadow(playerid, spectateTD[playerid][8], 0);
	PlayerTextDrawAlignment(playerid, spectateTD[playerid][8], 1);
	PlayerTextDrawColor(playerid, spectateTD[playerid][8], 2094792959);
	PlayerTextDrawBackgroundColor(playerid, spectateTD[playerid][8], 255);
	PlayerTextDrawBoxColor(playerid, spectateTD[playerid][8], 50);
	PlayerTextDrawUseBox(playerid, spectateTD[playerid][8], 0);
	PlayerTextDrawSetProportional(playerid, spectateTD[playerid][8], 1);
	PlayerTextDrawSetSelectable(playerid, spectateTD[playerid][8], 0);

	spectateTD[playerid][9] = CreatePlayerTextDraw(playerid, 345.000000, 346.000000, "PL:");
	PlayerTextDrawFont(playerid, spectateTD[playerid][9], 1);
	PlayerTextDrawLetterSize(playerid, spectateTD[playerid][9], 0.549999, 2.749999);
	PlayerTextDrawTextSize(playerid, spectateTD[playerid][9], 407.000000, 2.000000);
	PlayerTextDrawSetOutline(playerid, spectateTD[playerid][9], 1);
	PlayerTextDrawSetShadow(playerid, spectateTD[playerid][9], 0);
	PlayerTextDrawAlignment(playerid, spectateTD[playerid][9], 1);
	PlayerTextDrawColor(playerid, spectateTD[playerid][9], -1);
	PlayerTextDrawBackgroundColor(playerid, spectateTD[playerid][9], 255);
	PlayerTextDrawBoxColor(playerid, spectateTD[playerid][9], 50);
	PlayerTextDrawUseBox(playerid, spectateTD[playerid][9], 0);
	PlayerTextDrawSetProportional(playerid, spectateTD[playerid][9], 1);
	PlayerTextDrawSetSelectable(playerid, spectateTD[playerid][9], 0);

	spectateTD[playerid][10] = CreatePlayerTextDraw(playerid, 377.000000, 346.000000, "11.2");
	PlayerTextDrawFont(playerid, spectateTD[playerid][10], 1);
	PlayerTextDrawLetterSize(playerid, spectateTD[playerid][10], 0.549999, 2.749999);
	PlayerTextDrawTextSize(playerid, spectateTD[playerid][10], 407.000000, 2.000000);
	PlayerTextDrawSetOutline(playerid, spectateTD[playerid][10], 1);
	PlayerTextDrawSetShadow(playerid, spectateTD[playerid][10], 0);
	PlayerTextDrawAlignment(playerid, spectateTD[playerid][10], 1);
	PlayerTextDrawColor(playerid, spectateTD[playerid][10], 2094792959);
	PlayerTextDrawBackgroundColor(playerid, spectateTD[playerid][10], 255);
	PlayerTextDrawBoxColor(playerid, spectateTD[playerid][10], 50);
	PlayerTextDrawUseBox(playerid, spectateTD[playerid][10], 0);
	PlayerTextDrawSetProportional(playerid, spectateTD[playerid][10], 1);
	PlayerTextDrawSetSelectable(playerid, spectateTD[playerid][10], 0);

	spectateTD[playerid][11] = CreatePlayerTextDraw(playerid, 223.000000, 374.000000, "FPS:");
	PlayerTextDrawFont(playerid, spectateTD[playerid][11], 1);
	PlayerTextDrawLetterSize(playerid, spectateTD[playerid][11], 0.549999, 2.749999);
	PlayerTextDrawTextSize(playerid, spectateTD[playerid][11], 407.000000, 2.000000);
	PlayerTextDrawSetOutline(playerid, spectateTD[playerid][11], 1);
	PlayerTextDrawSetShadow(playerid, spectateTD[playerid][11], 0);
	PlayerTextDrawAlignment(playerid, spectateTD[playerid][11], 1);
	PlayerTextDrawColor(playerid, spectateTD[playerid][11], -1);
	PlayerTextDrawBackgroundColor(playerid, spectateTD[playerid][11], 255);
	PlayerTextDrawBoxColor(playerid, spectateTD[playerid][11], 50);
	PlayerTextDrawUseBox(playerid, spectateTD[playerid][11], 0);
	PlayerTextDrawSetProportional(playerid, spectateTD[playerid][11], 1);
	PlayerTextDrawSetSelectable(playerid, spectateTD[playerid][11], 0);

	spectateTD[playerid][12] = CreatePlayerTextDraw(playerid, 270.000000, 374.000000, "~y~30");
	PlayerTextDrawFont(playerid, spectateTD[playerid][12], 1);
	PlayerTextDrawLetterSize(playerid, spectateTD[playerid][12], 0.549999, 2.749999);
	PlayerTextDrawTextSize(playerid, spectateTD[playerid][12], 407.000000, 2.000000);
	PlayerTextDrawSetOutline(playerid, spectateTD[playerid][12], 1);
	PlayerTextDrawSetShadow(playerid, spectateTD[playerid][12], 0);
	PlayerTextDrawAlignment(playerid, spectateTD[playerid][12], 1);
	PlayerTextDrawColor(playerid, spectateTD[playerid][12], 2094792959);
	PlayerTextDrawBackgroundColor(playerid, spectateTD[playerid][12], 255);
	PlayerTextDrawBoxColor(playerid, spectateTD[playerid][12], 50);
	PlayerTextDrawUseBox(playerid, spectateTD[playerid][12], 0);
	PlayerTextDrawSetProportional(playerid, spectateTD[playerid][12], 1);
	PlayerTextDrawSetSelectable(playerid, spectateTD[playerid][12], 0);

	spectateTD[playerid][13] = CreatePlayerTextDraw(playerid, 307.000000, 384.000000, "Weap:");
	PlayerTextDrawFont(playerid, spectateTD[playerid][13], 1);
	PlayerTextDrawLetterSize(playerid, spectateTD[playerid][13], 0.358333, 2.000000);
	PlayerTextDrawTextSize(playerid, spectateTD[playerid][13], 407.000000, 2.000000);
	PlayerTextDrawSetOutline(playerid, spectateTD[playerid][13], 1);
	PlayerTextDrawSetShadow(playerid, spectateTD[playerid][13], 0);
	PlayerTextDrawAlignment(playerid, spectateTD[playerid][13], 1);
	PlayerTextDrawColor(playerid, spectateTD[playerid][13], -1);
	PlayerTextDrawBackgroundColor(playerid, spectateTD[playerid][13], 255);
	PlayerTextDrawBoxColor(playerid, spectateTD[playerid][13], 50);
	PlayerTextDrawUseBox(playerid, spectateTD[playerid][13], 0);
	PlayerTextDrawSetProportional(playerid, spectateTD[playerid][13], 1);
	PlayerTextDrawSetSelectable(playerid, spectateTD[playerid][13], 0);

	spectateTD[playerid][14] = CreatePlayerTextDraw(playerid, 349.000000, 386.000000, "Desert Eagle");
	PlayerTextDrawFont(playerid, spectateTD[playerid][14], 1);
	PlayerTextDrawLetterSize(playerid, spectateTD[playerid][14], 0.316666, 1.850000);
	PlayerTextDrawTextSize(playerid, spectateTD[playerid][14], 497.000000, 2.000000);
	PlayerTextDrawSetOutline(playerid, spectateTD[playerid][14], 1);
	PlayerTextDrawSetShadow(playerid, spectateTD[playerid][14], 0);
	PlayerTextDrawAlignment(playerid, spectateTD[playerid][14], 1);
	PlayerTextDrawColor(playerid, spectateTD[playerid][14], -1378294017);
	PlayerTextDrawBackgroundColor(playerid, spectateTD[playerid][14], 255);
	PlayerTextDrawBoxColor(playerid, spectateTD[playerid][14], 50);
	PlayerTextDrawUseBox(playerid, spectateTD[playerid][14], 0);
	PlayerTextDrawSetProportional(playerid, spectateTD[playerid][14], 1);
	PlayerTextDrawSetSelectable(playerid, spectateTD[playerid][14], 0);
}

hook OnPlayerConnect(playerid) {

	for (new i = 0; i < 15; i++) {
		PlayerTextDrawDestroy(playerid, spectateTD[playerid][i]);
	}

	SpectateTextdraws(playerid);	
}

hook OnPlayerDisconnect(playerid, reason) {

	for (new i = 0; i < 15; i++) {
		PlayerTextDrawDestroy(playerid, spectateTD[playerid][i]);
	}
} 

hook OnPlayerStateChange(playerid, newstate, oldstate) {

	if (newstate == PLAYER_STATE_SPECTATING && !IsAtEvent(playerid) && !FlyMode[playerid]) {
		if (oldstate == PLAYER_STATE_ONFOOT) {

			for (new i = 0; i < 15; i++) {
				PlayerTextDrawShow(playerid, spectateTD[playerid][i]);
			}
		}
		else if (oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER) {
			
			for (new i = 0; i < 15; i++) {
				PlayerTextDrawShow(playerid, spectateTD[playerid][i]);
			}
		}
	}
	else if (oldstate == PLAYER_STATE_SPECTATING) {

		for (new i = 0; i < 15; i++) {
			PlayerTextDrawHide(playerid, spectateTD[playerid][i]);
		}
	}
}

ptask OnSpectateUpdate[1000](playerid) {
	
	if (IsPlayerConnected(playerid)) {

		if (GetPlayerState(playerid) == PLAYER_STATE_SPECTATING && PlayerData[playerid][pSpectator] != INVALID_PLAYER_ID) {

			new targetid = PlayerData[playerid][pSpectator];

			PlayerTextDrawSetString(playerid, spectateTD[playerid][1], sprintf("%s", GetName(targetid)));
			PlayerTextDrawSetString(playerid, spectateTD[playerid][2], sprintf("(%d)", targetid));

			PlayerTextDrawSetString(playerid, spectateTD[playerid][4], sprintf("~y~%d", GetPlayerScore(targetid)));
			PlayerTextDrawSetString(playerid, spectateTD[playerid][6], sprintf("$%s", FormatNumber(GetMoney(targetid))));

			PlayerTextDrawSetString(playerid, spectateTD[playerid][8], sprintf("~r~%d", GetPlayerPing(targetid)));
			PlayerTextDrawSetString(playerid, spectateTD[playerid][10], sprintf("%.1f", NetStats_PacketLossPercent(targetid)));

			PlayerTextDrawSetString(playerid, spectateTD[playerid][12], sprintf("~y~%d", GetPlayerFPS(targetid)));
			PlayerTextDrawSetString(playerid, spectateTD[playerid][14], sprintf("%s", ReturnWeaponName(GetWeapon(targetid))));
		}
		else if (GetPlayerState(playerid) != PLAYER_STATE_SPECTATING) {
			for (new i = 0; i < 15; i++) {
				PlayerTextDrawHide(playerid, spectateTD[playerid][i]);
			}
		}
	}
}