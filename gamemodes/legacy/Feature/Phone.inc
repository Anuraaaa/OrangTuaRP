enum contactData
{
	contactID,
	contactExists,
	contactName[32],
	contactNumber,
	contactOwner,
};

new ContactData[MAX_PLAYERS][MAX_CONTACTS][contactData];
new ListedContacts[MAX_PLAYERS][MAX_CONTACTS];

HasPhoneSignal(playerid)
{
	if(IsPlayerInRangeOfPoint(playerid, 40.0, 322.8956,1795.4436,899.3750)) return true;
	if(IsPlayerInRangeOfPoint(playerid, 50.0, -1271.2010, -2061.0656, 22.9706)) return true;
	if(IsPlayerInRangeOfPoint(playerid, 50.0, -185.9363,1886.0468,102.80237)) return true;
	if(IsPlayerInArea(playerid, -2172.085, -2931.147, -980.9415, -2172.085)) return false;
	if(IsPlayerInArea(playerid, 46.7115, -1599.869, -1564.835, -2989.536)) return false;
	if(IsPlayerInArea(playerid, 945.9079, -2989.536, 2989.536, 2697.589)) return false;
	if(IsPlayerInArea(playerid, 2966.18, 1868.46, -315.3026, -899.1964)) return false;
	if(IsPlayerInArea(playerid, 548.8602, -934.23, 2872.757, 2195.441)) return false;
	if(!IsPlayerInArea(playerid, 3000.0, -3000.0, 3000.0, -3000.0)) return false;
	return true;
}

CancelCall(playerid)
{
    if (PlayerData[playerid][pCallLine] != INVALID_PLAYER_ID)
	{
		SetPlayerSpecialAction(PlayerData[playerid][pCallLine], SPECIAL_ACTION_STOPUSECELLPHONE);
		SendClientMessage(PlayerData[playerid][pCallLine], X11_GREY, "Panggilan terputus...");

 		PlayerData[PlayerData[playerid][pCallLine]][pCallLine] = INVALID_PLAYER_ID;
   		PlayerData[PlayerData[playerid][pCallLine]][pIncomingCall] = 0;

		PlayerData[playerid][pCallLine] = INVALID_PLAYER_ID;
		PlayerData[playerid][pIncomingCall] = 0;
	}
	return 1;
}

IsPlayerOnPhone(playerid)
{
	if (PlayerData[playerid][pCallLine] != INVALID_PLAYER_ID || ServiceIndex[playerid] != 0)
	    return 1;

	return 0;
}

function LoadPlayerContact(playerid)
{
	new count = cache_num_rows();
	if(count > 0)
	{
		for(new i = 0; i < count; i++)
		{
		    ContactData[playerid][i][contactExists] = true;
	        cache_get_value_name(i, "contactName", ContactData[playerid][i][contactName]);
            cache_get_value_name_int(i, "contactOwner", ContactData[playerid][i][contactOwner]);
		    cache_get_value_name_int(i, "contactNumber", ContactData[playerid][i][contactNumber]);
		    cache_get_value_name_int(i, "contactID", ContactData[playerid][i][contactID]);
		}
	}
	return 1;
}

Contact_GetFreeID(playerid) {

	new idx = -1;
	for (new i = 0; i != MAX_CONTACTS; i ++) if(!ContactData[playerid][i][contactExists])
	{
		idx = i;
		break;
	}
	return idx;
}
Contact_Add(playerid, number, name[]) {

	new id = -1, string[156];
	if((id = Contact_GetFreeID(playerid)) != -1) {
		ContactData[playerid][id][contactExists] = true;
		ContactData[playerid][id][contactNumber] = number;
		ContactData[playerid][id][contactOwner] = PlayerData[playerid][pID];
		format(ContactData[playerid][id][contactName], 32, name);

		mysql_format(sqlcon, string, sizeof(string), "INSERT INTO `contacts` (`ID`, `contactName`, `contactNumber`, `contactOwner`) VALUES('%d', '%s', '%d', '%d')", PlayerData[playerid][pID], name, number, PlayerData[playerid][pID]);
		mysql_tquery(sqlcon, string, "OnContactAdd", "dd", playerid, id);
	}
	return id;
}
ShowContacts(playerid)
{
	new
	    string[48 * MAX_CONTACTS],
		count = 0;

	string = ""GREY"New contacts\n";

	for (new i = 0; i != MAX_CONTACTS; i ++) if (ContactData[playerid][i][contactExists] && ContactData[playerid][i][contactOwner] == PlayerData[playerid][pID])
	{
	    format(string, sizeof(string), "%s"WHITE"%s - #%d\n", string, ContactData[playerid][i][contactName], ContactData[playerid][i][contactNumber]);

		ListedContacts[playerid][count++] = i;
	}
	ShowPlayerDialog(playerid, DIALOG_CONTACT, DIALOG_STYLE_LIST, "Contact List", string, "Select", "Back");
	return 1;
}

IsNumberKnown(playerid, number, bool:english = false)
{
    new str[56], idx = -1;
    for(new i = 0; i < MAX_CONTACTS; i++) if(ContactData[playerid][i][contactExists] && ContactData[playerid][i][contactNumber] == number)
    {
        idx = i;
        break;
    }
    if(idx == -1)
        if(!english)
            str = "Tidak dikenal";
        else
            str = "Unknown";
    else
        format(str, sizeof(str), "%s", ContactData[playerid][idx][contactName]);

    return str;
}

CMD:phone(playerid, params[])
{
	if(!PlayerHasItem(playerid, "Cellphone"))
	    return SendErrorMessage(playerid, "You don't have a cellphone on you.");

    if (PlayerData[playerid][pInjured])
	    return SendErrorMessage(playerid, "You can't use this command now.");

	new
	    str[156];


	if (PlayerData[playerid][pPhoneOff])
	{
		format(str, sizeof(str), "Number: %d\nCredits: %d\nDial Number\nMy Contacts\nSend Text Message\nAdvertisement List\nShare Location\nWatch live broadcast\nTurn On Phone", PlayerData[playerid][pPhoneNumber], PlayerData[playerid][pCredit]);
	}
	else
	{
	    format(str, sizeof(str), "Number: %d\nCredits: %d\nDial Number\nMy Contacts\nSend Text Message\nAdvertisement List\nShare Location\nWatch live broadcast\nTurn Off Phone", PlayerData[playerid][pPhoneNumber], PlayerData[playerid][pCredit]);
	}
	ShowPlayerDialog(playerid, DIALOG_PHONE, DIALOG_STYLE_LIST, "Home Screen", str, "Select", "Close");
	new string[128];
	format(string, sizeof(string), "* %s Take out cellphone and use it", ReturnName(playerid), params);
 	SetPlayerChatBubble(playerid, string, COLOR_PURPLE, 30.0, 5000);
	return 1;
}

CMD:sms(playerid, params[])
{
    new number,
        text[128];

    if(!PlayerHasItem(playerid, "Cellphone"))
        return SendErrorMessage(playerid, "You don't have cellphone on you.");

    if(PlayerData[playerid][pPhoneOff])
        return SendErrorMessage(playerid, "You must turn-on your cellphone first.");

    if(sscanf(params, "ds[128]", number, text))
        return SendSyntaxMessage(playerid, "/sms [phone number] [message]");
    
    if(strlen(text) > 90)
        return SendClientMessage(playerid, X11_GREY, "ERROR: Panjang karakter tidak bisa lebih dari 90 karakter.");

    new targetid = GetNumberOwner(number);

    if(!IsPlayerConnected(targetid))
        return SendErrorMessage(playerid, "Nomor ini sedang tidak aktif.");

    if(PlayerData[targetid][pPhoneOff])
        return SendErrorMessage(playerid, "Nomor yang dituju sedang tidak aktif.");

	if(!PlayerData[playerid][pCredit])
		return SendErrorMessage(playerid, "Kamu tidak memiliki phone credit!");

	PlayerData[playerid][pCredit] -= 3;

	if(PlayerData[playerid][pCredit] < 0)
		PlayerData[playerid][pCredit] = 0;
		
    SendClientMessageEx(targetid, X11_LIGHTBLUE, "** SMS from %s(%d): "WHITE"%s", IsNumberKnown(targetid, PlayerData[playerid][pPhoneNumber], true), PlayerData[playerid][pPhoneNumber], text);
    SendClientMessageEx(playerid, X11_LIGHTBLUE, "** SMS to %s(%d): "WHITE"%s", IsNumberKnown(playerid, number, true), number, text);
    PlayerPlaySound(playerid, targetid, 0.0, 0.0, 0.0);
	cmd_ame(playerid, "types something on his cellphone.");
	PlayerData[targetid][pLastNumber] = PlayerData[playerid][pPhoneNumber];
	return 1;
}

CMD:reply(playerid, params[]) {

    if(!PlayerHasItem(playerid, "Cellphone"))
        return SendErrorMessage(playerid, "You don't have cellphone on you.");

    if(PlayerData[playerid][pPhoneOff])
        return SendErrorMessage(playerid, "You must turn-on your cellphone first.");

	if(!PlayerData[playerid][pLastNumber])
		return SendErrorMessage(playerid, "Tidak ada yang mengirimkan pesan padamu baru-baru ini.");

	if(GetNumberOwner(PlayerData[playerid][pLastNumber]) != INVALID_PLAYER_ID) {

		new str[156];
		format(str, sizeof(str), ""WHITE"Reply to: "YELLOW"%d\n"WHITE"Message: "GREEN"(input below)", PlayerData[playerid][pLastNumber]);
		ShowPlayerDialog(playerid, DIALOG_REPLY, DIALOG_STYLE_INPUT, "Reply Message", str, "Send", "Close");
	}
	else SendErrorMessage(playerid, "Pengirim pesan terakhir tidak dapat dijangkau.");

	return 1;
}
CMD:call(playerid, params[])
{
	if(!PlayerHasItem(playerid, "Cellphone"))
	    return SendErrorMessage(playerid, "You don't have a cellphone on you.");

    if (PlayerData[playerid][pPhoneOff])
		return SendErrorMessage(playerid, "Your phone must be powered on.");

    if (PlayerData[playerid][pInjured])
	    return SendErrorMessage(playerid, "You can't use this command now.");

	if(!HasPhoneSignal(playerid))
		return SendErrorMessage(playerid, "Signal Service is unreachable on your location.");

	if(IsPlayerOnPhone(playerid))
		return SendErrorMessage(playerid, "You already on a call.");

	if(ServiceIndex[playerid] != 0)
		return SendErrorMessage(playerid, "You already on a call.");

	new
	    targetid,
		number;

	if (sscanf(params, "d", number))
 	   return SendSyntaxMessage(playerid, "/call [phone number] (1222 - Taxi | 911 - Emergency | 143 - Mechanic | 193 - News)");

	if (!number)
	    return SendErrorMessage(playerid, "Nomor ini sedang tidak aktif.");
	    
	if (number == 911)
	{
		if(!IsPlayerInAnyVehicle(playerid))
		{
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);
		}
		SetPlayerAttachedObject(playerid, 3, 18867, 6, 0.0909, -0.0030, 0.0000, 80.4001, 159.8000, 18.0000, 1.0000, 1.0000, 1.0000, 0xFFFFFFFF, 0xFFFFFFFF);

		ServiceIndex[playerid] = 1;
		PlayerPlaySound(playerid, 3600, 0.0, 0.0, 0.0);
		SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "* %s takes out their cellphone and places a call.", ReturnName(playerid));
		SendClientMessage(playerid, COLOR_SERVER, "(Operator){FFFFFF} Which service do you require: \"sfpd\" or \"sffd\"?");
	}
	else if (number == 1222)
	{
		PlayerData[playerid][pTaxiCalled] = true;
		PlayerPlayNearbySound(playerid, 3600);
		SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "* %s takes out their cellphone and places a call.", ReturnName(playerid));
		SendClientMessage(playerid, COLOR_YELLOW, "(Operator){FFFFFF} The taxi department has been notified of your call.");
		
		foreach(new i : Player) if(CheckPlayerJob(i, JOB_TAXI) && PlayerData[i][pJobduty]) {
			SendClientMessageEx(i, X11_YELLOW, "[1222]: "WHITE"%s[%d] membutuhkan Taxi pada lokasi %s (/taxi calls untuk menerima)", GetName(playerid, false), PlayerData[playerid][pPhoneNumber], GetSpecificLocation(playerid));
		}
	}
	else if (number == 143)
	{
	    PlayerPlayNearbySound(playerid, 3600);
		SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "* %s takes out their cellphone and places a call.", ReturnName(playerid));
		SendClientMessage(playerid, COLOR_LIGHTGREEN, "(Operator){FFFFFF} The mechanic has been notified of your call.");
		foreach(new i : Player) if(CheckPlayerJob(i, JOB_MECHANIC) && PlayerData[i][pJobduty])  {
			SendClientMessageEx(i, COLOR_LIGHTGREEN, "[143]: {FFFFFF}%s is requesting a mechanic at %s (%d)", GetName(playerid, false), GetSpecificLocation(playerid), PlayerData[playerid][pPhoneNumber]);
		}
	}
	else if(number == 193) {

		if(!IsPlayerInAnyVehicle(playerid))
		{
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);
		}
		SetPlayerAttachedObject(playerid, 3, 18867, 6, 0.0909, -0.0030, 0.0000, 80.4001, 159.8000, 18.0000, 1.0000, 1.0000, 1.0000, 0xFFFFFFFF, 0xFFFFFFFF);


	    PlayerPlayNearbySound(playerid, 3600);
		SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "* %s takes out their cellphone and places a call.", ReturnName(playerid));
		SendClientMessage(playerid, X11_TURQUOISE_1, "(News Operator)"WHITE" What can we help you? don't send junk message for this service.");	
		PlayerData[playerid][pCallNews] = true;	
	}
	else if ((targetid = GetNumberOwner(number)) != INVALID_PLAYER_ID)
	{
	    if (targetid == playerid)
	        return SendErrorMessage(playerid, "Kamu tidak dapat menelfon diri sendiri.");

		if (PlayerData[targetid][pPhoneOff])
		    return SendErrorMessage(playerid, "Nomor yang dituju sedang tidak aktif.");
		    
		if(PlayerData[playerid][pCredit] < 5)
		    return SendErrorMessage(playerid, "Kamu tidak memiliki pulsa yang cukup.");

		if(PlayerData[targetid][pIncomingCall])
		    return SendErrorMessage(playerid, "Nomor ini sedang sibuk.");

        if (IsPlayerOnPhone(targetid))
		    return SendErrorMessage(playerid, "Nomor ini sedang sibuk.");
		    
		PlayerData[targetid][pIncomingCall] = 1;
		PlayerData[playerid][pIncomingCall] = 1;

		PlayerData[targetid][pCallLine] = playerid;
		PlayerData[playerid][pCallLine] = targetid;

		SendClientMessageEx(playerid, X11_GREY, "Kamu mencoba menelfon nomor \"%d\" tunggu hingga penerima menerima panggilan...", number);
		SendClientMessageEx(targetid, X11_GREY, "Panggilan masuk dari nomor %s (%d), gunakan \"/answer\" untuk menerima dan \"/h\" untuk menolak...", IsNumberKnown(targetid, PlayerData[playerid][pPhoneNumber]), PlayerData[playerid][pPhoneNumber]);
		
		PlayerData[playerid][pCredit] -= Random(5, 15);
        PlayerPlayNearbySound(playerid, 3600);
        PlayerPlayNearbySound(targetid, 23000);

		SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "* %s takes out their cellphone and places a call.", ReturnName(playerid));

		if(!IsPlayerInAnyVehicle(playerid))
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);

		SetPlayerAttachedObject(playerid, 3, 18867, 6, 0.0909, -0.0030, 0.0000, 80.4001, 159.8000, 18.0000, 1.0000, 1.0000, 1.0000, 0xFFFFFFFF, 0xFFFFFFFF);
	}
	else
	{
	    SendErrorMessage(playerid, "Nomor ini sedang tidak aktif.");
	}
	return 1;
}
