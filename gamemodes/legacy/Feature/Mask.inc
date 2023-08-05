SetupPlayerMask(playerid)
{
	new str[64];
	if(PlayerData[playerid][pMasked])
	{
		if(IsValidDynamic3DTextLabel(PlayerData[playerid][pMaskLabel]))
			DestroyDynamic3DTextLabel(PlayerData[playerid][pMaskLabel]);

		PlayerData[playerid][pMaskLabel] = Text3D:INVALID_STREAMER_ID;
		PlayerData[playerid][pMasked] = false;
		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "* %s takes their mask off and puts it away.", ReturnName(playerid));

		foreach(new i : Player)
		{
			ShowPlayerNameTagForPlayer(i, playerid, 1);
		}
	}
	else
	{
		if(IsPlayerOnJob(playerid))
			return SendErrorMessage(playerid, "Tidak dapat menggunakan masker ketika bekerja.");
			
		PlayerData[playerid][pMasked] = true;

		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "* %s takes out a mask and puts it on.", ReturnName(playerid));

		if(!IsPlayerInAnyVehicle(playerid))
			ApplyAnimation(playerid, "shop","ROB_Shifty", 4.1, 0, 0, 0, 0, 0, 1);

		format(str, sizeof(str), "Unknown_#%d\n{FF0000}HP: {FFFFFF}%.2f | {007FFF}AP: {FFFFFF}%.2f", PlayerData[playerid][pMaskID], ReturnHealth(playerid), ReturnArmour(playerid));

		if(IsValidDynamic3DTextLabel(PlayerData[playerid][pMaskLabel])) {
			DestroyDynamic3DTextLabel(PlayerData[playerid][pMaskLabel]);
			
			PlayerData[playerid][pMaskLabel] = Text3D:INVALID_3DTEXT_ID;
		}
		
		PlayerData[playerid][pMaskLabel] = CreateDynamic3DTextLabel(str, COLOR_WHITE, 0.0, 0.0, 0.1, 20.0, playerid, INVALID_VEHICLE_ID, 1, -1, -1, -1, 10.0);
		
		foreach(new i : Player)
		{
			ShowPlayerNameTagForPlayer(i, playerid, 0);
		}
	}
	return 1;
}

UpdateMaskLabel(playerid) {
	if(PlayerData[playerid][pMasked] && IsValidDynamic3DTextLabel(PlayerData[playerid][pMaskLabel])) {
		new str[128];
		format(str, sizeof(str), "Unknown_#%d\n{FF0000}HP: {FFFFFF}%.2f | {007FFF}AP: {FFFFFF}%.2f", PlayerData[playerid][pMaskID], ReturnHealth(playerid), ReturnArmour(playerid));
		UpdateDynamic3DTextLabelText(PlayerData[playerid][pMaskLabel], -1, str);
	}
}
CMD:mask(playerid, params[])
{
	if(!PlayerHasItem(playerid, "Mask"))
		return SendErrorMessage(playerid, "You don't have a mask!");

	if(PlayerData[playerid][pOnDuty] && !PlayerData[playerid][pMasked])
		return SendErrorMessage(playerid, "You can't use mask since you onduty!");

	SetupPlayerMask(playerid);
	return 1;
}