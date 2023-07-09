new vehicleStream[MAX_VEHICLES][128];

enum
{
	MUSIC_NONE,
	MUSIC_BOOMBOX,
	MUSIC_VEHICLE
};

enum enumURL
{
	NameURL[32],
	LinkURL[100],
};

new const ListURLMusic[][enumURL] =
{
	{"San Fierro News", },
	{"Dj Dear God", "http://d.zaix.ru/mfDN.txt"},
	{"Death Bed", "http://d.zaix.ru/md7Z.jpg"},
	{"Dat Stick", "http://d.zaix.ru/kTm3.png"},
	{"Blue Bird", "http://d.zaix.ru/kwdu.jpg"},
	{"Love Story", "http://d.zaix.ru/mfLg.txt"},
	{"Someone You Loved", "http://d.zaix.ru/krgQ.mp3"},
	{"Dj All Night", "http://d.zaix.ru/kDiA.png"}
};

IsPlayerInRangeOfDynamicObject(playerid, objectid, Float:radius)
{
	if(IsValidDynamicObject(objectid))
	{
		new
		    interiorid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_INTERIOR_ID),
			worldid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_WORLD_ID),
		    Float:x,
		    Float:y,
		    Float:z;

		GetDynamicObjectPos(objectid, x, y, z);

		if(interiorid == -1) {
		    interiorid = GetPlayerInterior(playerid);
		} if(worldid == -1) {
		    worldid = GetPlayerVirtualWorld(playerid);
		}

		if(IsPlayerInRangeOfPoint(playerid, radius, x, y, z) && GetPlayerInterior(playerid) == interiorid && GetPlayerVirtualWorld(playerid) == worldid)
		{
		    return 1;
		}
	}

	return 0;
}

SetMusicStream(type, playerid, url[])
{
	switch(type)
	{
		case MUSIC_BOOMBOX:
		{
		    foreach(new i : Player)
		    {
		        if(PlayerData[i][pBoomboxListen] == playerid)
		        {
				    if(isnull(url) && PlayerData[i][pStreamType] == type)
				    {
				        StopAudioStreamForPlayer(i);
			            PlayerData[i][pStreamType] = MUSIC_NONE;
			        }
			        else if(PlayerData[i][pStreamType] == MUSIC_NONE || PlayerData[i][pStreamType] == MUSIC_BOOMBOX)
			        {
			            PlayAudioStreamForPlayer(i, url);
			            PlayerData[i][pStreamType] = type;
			        }
				}
			}

			strcpy(PlayerData[playerid][pBoomboxURL], url, 128);
		}
		case MUSIC_VEHICLE:
		{
		    foreach(new i : Player)
		    {
		        if(IsPlayerInVehicle(i, playerid))
		        {
				    if(isnull(url) && PlayerData[i][pStreamType] == type)
				    {
		        		StopAudioStreamForPlayer(i);
	            		PlayerData[i][pStreamType] = MUSIC_NONE;
			        }
	    		    else if(PlayerData[i][pStreamType] == MUSIC_NONE || PlayerData[i][pStreamType] == MUSIC_VEHICLE)
			        {
	    		        PlayAudioStreamForPlayer(i, url);
	           		 	PlayerData[i][pStreamType] = type;
					}
				}
			}

			strcpy(vehicleStream[playerid], url, 128);
		}
	}
}

DestroyBoombox(playerid)
{
	if(PlayerData[playerid][pBoomboxPlaced])
	{
		if(IsValidDynamicObject(PlayerData[playerid][pBoomboxObject]))
    		DestroyDynamicObject(PlayerData[playerid][pBoomboxObject]);

		if(IsValidDynamic3DTextLabel(PlayerData[playerid][pBoomboxText]))
			DestroyDynamic3DTextLabel(PlayerData[playerid][pBoomboxText]);

		PlayerData[playerid][pBoomboxObject] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
		PlayerData[playerid][pBoomboxText] = Text3D:INVALID_STREAMER_ID;
        PlayerData[playerid][pBoomboxPlaced] = 0;
        PlayerData[playerid][pBoomboxURL] = 0;
	}
}

GetNearbyBoombox(playerid)
{
	foreach(new i : Player)
	{
	    if(PlayerData[i][pBoomboxPlaced] && IsPlayerInRangeOfDynamicObject(playerid, PlayerData[i][pBoomboxObject], 30.0))
	    {
	        return i;
		}
	}

	return INVALID_PLAYER_ID;
}

CMD:boombox(playerid, params[])
{
	new option[10], param[128];

	if(GetPlayerVIPLevel(playerid) < VIP_LEVEL_SILVER)
		return SendErrorMessage(playerid, "Command ini untuk Silver Donater dan diatasnya.");
		
	if(Inventory_Count(playerid, "Boombox") < 1)
		return SendErrorMessage(playerid, "You don't have a Boombox!");

	if(sscanf(params, "s[10]S()[128]", option, param))
	    return SendSyntaxMessage(playerid, "/boombox [ place, pickup, list, url ]");

	if(IsPlayerInAnyVehicle(playerid))
	    return SendErrorMessage(playerid, "You can't use this command in the vehicle!");

	if(!strcmp(option, "place", true))
	{
	    if(PlayerData[playerid][pBoomboxPlaced])
	        return SendErrorMessage(playerid, "You've put the Boombox!");

	    if(GetNearbyBoombox(playerid) != INVALID_PLAYER_ID)
	        return SendErrorMessage(playerid, "Around your place there are already other people's Boomboxes, please move");

		new
		    Float:x,
	    	Float:y,
	    	Float:z,
	    	Float:a,
			string[128];

		format(string, sizeof(string), "{62da92}[Boombox]\n{FFFFFF}Use {FFFF00}'/boombox'{FFFFFF} to play music.", GetName(playerid));

		GetPlayerPos(playerid, x, y, z);
		GetPlayerFacingAngle(playerid, a);

	    PlayerData[playerid][pBoomboxPlaced] = 1;
    	PlayerData[playerid][pBoomboxObject] = CreateDynamicObject(2103, x, y, z - 0.9, 0.0, 0.0, a, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
    	PlayerData[playerid][pBoomboxText] = CreateDynamic3DTextLabel(string, COLOR_LIGHTORANGE, x, y, z - 0.8, 10.0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
        PlayerData[playerid][pBoomboxURL] = 0;

    	ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 0, 0, 0, 0, 0);
		SendNearbyMessage(playerid, 10.0, COLOR_PURPLE, "* %s put the boombox below", ReturnName(playerid));
	}
	else if(!strcmp(option, "pickup", true))
	{
	    if(!PlayerData[playerid][pBoomboxPlaced])
	        return SendErrorMessage(playerid, "You haven't put Boombox!");

	    if(!IsPlayerInRangeOfDynamicObject(playerid, PlayerData[playerid][pBoomboxObject], 3.0))
	        return SendErrorMessage(playerid, "You are not within reach of your Boombox!");

		SendNearbyMessage(playerid, 10.0, COLOR_PURPLE, "* %s pick up the boombox and turn off the music.", ReturnName(playerid));
		DestroyBoombox(playerid);
	}
    else if(!strcmp(option, "url", true))
	{
        if(!PlayerData[playerid][pBoomboxPlaced])
	        return SendErrorMessage(playerid, "You haven't put Boombox!");

	    if(!IsPlayerInRangeOfDynamicObject(playerid, PlayerData[playerid][pBoomboxObject], 3.0))
	        return SendErrorMessage(playerid, "You are not within reach of your Boombox!");

    	PlayerData[playerid][pMusicType] = MUSIC_BOOMBOX;
    	ShowPlayerDialog(playerid, DIALOG_BOOMBOX_URL, DIALOG_STYLE_INPUT, "URL Music", "Please enter the URL of the music you want to play:", "Input", "Close");
	}
	else if(!strcmp(option, "list", true))
	{
		new str[2048];

		if(!PlayerData[playerid][pBoomboxPlaced])
	        return SendErrorMessage(playerid, "You haven't put Boombox!");

	    if(!IsPlayerInRangeOfDynamicObject(playerid, PlayerData[playerid][pBoomboxObject], 3.0))
	        return SendErrorMessage(playerid, "You are not within reach of your Boombox!");
		
		if(isnull(str))
		{
			format(str, sizeof(str), "Song Title\n");			
			
			for(new i = 0; i < sizeof(ListURLMusic); i ++)
			{
				format(str, sizeof(str), "%s\n%s\n", str, ListURLMusic[i][NameURL]);
			}
		}

		PlayerData[playerid][pMusicType] = MUSIC_BOOMBOX;

		ShowPlayerDialog(playerid, DIALOG_BOOMBOX_LIST, DIALOG_STYLE_TABLIST_HEADERS, "List Music", str, "Select", "Close");
	}
	else if(!strcmp(option, "stop", true))
	{
		SendServerMessage(playerid, "You have turn off the music.");
		SendNearbyMessage(playerid, 10.0, COLOR_PURPLE, "* %s turn off the music.", ReturnName(playerid));
		PlayerData[playerid][pStreamType] = MUSIC_NONE;
		PlayerData[playerid][pBoomboxURL] = 0;
		StopAudioStreamForPlayer(playerid);
	}

	return 1; 
}

CMD:destorybb(playerid, params[])
{
	new boomboxid;

	if(PlayerData[playerid][pAdmin] < 3)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if((boomboxid = GetNearbyBoombox(playerid)) == INVALID_PLAYER_ID)
		return SendErrorMessage(playerid, "You are not within reach of your Boombox!");

	SendServerMessage(playerid, "You have destroyed {FF0000}%s {FFFFFF}Boombox", GetName(boomboxid));
	DestroyBoombox(boomboxid);

	return 1;
}