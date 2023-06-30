InjuredPlayer(playerid, killerid, weaponid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_WASTED)
		return 0;

	if(PlayerData[playerid][pInjured])
		return 0;

	foreach(new i : Player) if(PlayerData[i][pAdmin] > 0)
	{
		SendDeathMessageToPlayer(i, killerid, playerid, weaponid);
	}

	GetPlayerPos(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);
	
	if (IsPlayerInAnyVehicle(playerid))
 		SetPlayerPos(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2] + 0.7);

	PlayerData[playerid][pInjured] = true;
	SetPlayerHealth(playerid, 100);
	PlayerData[playerid][pInjuredTime] = 300;
	SendClientMessage(playerid, COLOR_LIGHTRED, "(Warning) {FFFFFF}You have been {E20000}downed.{FFFFFF} You may choose to {44C300}/accept death");
	SendClientMessage(playerid, COLOR_WHITE, "...after your death timer expires or wait until you are revived.");

	ApplyAnimation(playerid, "PED", "KO_SHOT_STOM", 4.0, 1, 0, 0, 0, 0, 1);
	ShowText(playerid, "~n~~r~BRUTALLY WOUNDED!", 3);
	return 1;
}