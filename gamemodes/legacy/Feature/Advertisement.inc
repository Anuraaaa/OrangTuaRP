enum adData
{
	advertID,
	advertExists,
	advertOwner,
	advertText[128],
	advertNumber,
	advertName[32],
	advertTime,
};
new AdvertData[MAX_ADVERT][adData],
	AdvertText[MAX_PLAYERS][128];

Advert_Show(playerid)
{
	new list[2012];
	format(list, sizeof(list), "Owner\tAdvertisement\n");
	for(new i; i < MAX_ADVERT; i++) if(AdvertData[i][advertExists])
	{
	    format(list, sizeof(list), "%s%s[#%d]\t%s\n", list, AdvertData[i][advertName], AdvertData[i][advertNumber], AdvertData[i][advertText]);
	}
	ShowPlayerDialog(playerid, DIALOG_NONE, DIALOG_STYLE_TABLIST_HEADERS, "Advertisement List", list, "Close", "");
	return 1;
}

Advert_Count()
{
	new count = 0;
	for(new i = 0; i < MAX_ADVERT; i ++) if(AdvertData[i][advertExists])
	{
	    count++;
	}
	return count;
}
Advert_CountPlayer(playerid)
{
	new count = 0;
	for(new i = 0; i < MAX_ADVERT; i ++) if(AdvertData[i][advertExists])
	{
	    if(AdvertData[i][advertOwner] == PlayerData[playerid][pID])
	    {
	        count++;
		}
	}
	return count;
}
Advert_Create(number, text[], pid, name[], &time)
{
	for(new i = 0; i < MAX_ADVERT; i ++) if(!AdvertData[i][advertExists])
	{
	    AdvertData[i][advertExists] = true;
	    AdvertData[i][advertOwner] = pid;
	    format(AdvertData[i][advertText], 128, text);
	    format(AdvertData[i][advertName], 32, name);
	    AdvertData[i][advertNumber] = number;
	    AdvertData[i][advertTime] = RandomEx(1, 3);
		time = AdvertData[i][advertTime];
	    return i;
	}
	return -1;
}

Advert_Delete(adid)
{
	if (adid != -1 && AdvertData[adid][advertExists])
	{
	    AdvertData[adid][advertExists] = false;
	    AdvertData[adid][advertOwner] = -1;
	}
	return 1;
}

CMD:ad(playerid, params[])
{
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, -192.3483, 1338.7361, 1500.9823))
	    return SendErrorMessage(playerid, "You only can perform this inside San Fierro News!");

	if(Faction_CountDuty(FACTION_NEWS) > 0)
		return SendErrorMessage(playerid, "Tidak bisa digunakan jika ada SFN duty! RP dengan member SFN untuk membuat ads.");

	if(Advert_CountPlayer(playerid) > 0)
	    return SendErrorMessage(playerid, "You already have a pending advertisement, you must wait first.");

	if(Advert_Count() >= 50)
		return SendErrorMessage(playerid, "The server has reached limit of ads list, comeback later.");

	if(!PlayerHasItem(playerid, "Cellphone"))
		return SendErrorMessage(playerid, "You don't have Cellphone on you!");

	if(PlayerData[playerid][pPhoneNumber] == 0)
		return SendErrorMessage(playerid, "You don't have Phone Number!");

	if(isnull(params))
	    return SendSyntaxMessage(playerid, "/ad [advertisement]"), SendClientMessage(playerid, COLOR_YELLOW, "(Info) {FFFFFF}Advertisement is charged {009000}$0,50 {FFFFFF}per character.");

	if(strlen(params) > 128)
	    return SendErrorMessage(playerid, "Text cannot more than 128 characters.");

	if(GetMoney(playerid) < strlen(params)*50)
	    return SendErrorMessage(playerid, "You need $%s to make advertisement", FormatNumber(strlen(params)*50));

	GiveMoney(playerid, -strlen(params)*50, "Advertisement");
	new time = 1;
	Advert_Create(PlayerData[playerid][pPhoneNumber], params, PlayerData[playerid][pID], GetName(playerid, false), time);
	SendClientMessageEx(playerid, COLOR_SERVER, "(Advertisement) {FFFFFF}Your advertisement will be appear %d minutes from now.", time);
	return 1;
}

CMD:postad(playerid, params[]) {
	if(GetFactionType(playerid) != FACTION_NEWS)
		return SendErrorMessage(playerid, "Kamu bukan anggota dari San Fierro News!");

	if(!IsPlayerInRangeOfPoint(playerid, 13.0, -192.3483, 1338.7361, 1500.9823))
	    return SendErrorMessage(playerid, "Kamu hanya dapat menggunakannya di Advertisement Desk!");

	new targetid;

	if(sscanf(params, "u", targetid))
		return SendSyntaxMessage(playerid, "/postad [playerid/PartOfName]");

	if(!IsPlayerNearPlayer(playerid, targetid, 9.0) || !IsPlayerConnected(targetid))
		return SendErrorMessage(playerid, "You have specified invalid player.");

	if(!PlayerHasItem(targetid, "Cellphone"))
		return SendErrorMessage(playerid, "That player doesn't have a cellphone!");

	if(PlayerData[targetid][pPhoneNumber] == 0)
		return SendErrorMessage(playerid, "That player doesn't have a phone number.");

	SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Post-Ad) "WHITE"You have given "CYAN"advertisement letter "WHITE"to "YELLOW"%s", ReturnName(targetid));
	SendClientMessageEx(targetid, X11_LIGHTBLUE, "(Post-Ad) "WHITE"You have been given an "CYAN"advertisement letter "WHITE"from "YELLOW"%s", ReturnName(playerid));

	ShowPlayerDialog(targetid, DIALOG_ADS_TEXT, DIALOG_STYLE_INPUT, "Advertisement", "Silahkan masukkan apa yang akan kamu iklankan:\n(maksimal 128 karakter)", ">>>", "Close");
	PlayerData[targetid][pTarget] = playerid;

	return 1;

}//