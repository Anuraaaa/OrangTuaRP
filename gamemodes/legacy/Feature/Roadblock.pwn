#define MAX_DYNAMIC_ROADBLOCK	100

new gRoadblockModels[] = 
{
    19975, 	19972, 	19966, 	1459, 	978,     981, 	
    1238, 	1425,	3265,	3091,   1422,    19970, 	
    19971, 	1237,   1423,	983, 	 1251,   19953,
    19954,  19974, 	19834, 1428, 1437
};


enum E_BARRICADE_DATA
{
    cadeType,
    cadeModel,

    cadeText[225],
    Float:cadePos[6],
    STREAMER_TAG_OBJECT:cadeObject
};

new
	Iterator:Barricade<MAX_DYNAMIC_ROADBLOCK>,
	BarricadeData[MAX_DYNAMIC_ROADBLOCK][E_BARRICADE_DATA];


Barricade_IsExists(index)
{
	if(Iter_Contains(Barricade, index))
		return 1;

	return 0;
}

Barricade_Create(playerid, type, model, text[])
{
	static
		index;

	if((index = Iter_Free(Barricade)) != cellmin)
	{
		Iter_Add(Barricade, index);

		BarricadeData[index][cadeType] = type;
		BarricadeData[index][cadeModel] = model;

		FixText(text);    
        format(BarricadeData[index][cadeText], 225, text);

		GetPlayerPos(playerid, BarricadeData[index][cadePos][0], BarricadeData[index][cadePos][1], BarricadeData[index][cadePos][2]);
		BarricadeData[index][cadePos][4] = 0.0;
		BarricadeData[index][cadePos][3] = 0.0;
		GetPlayerFacingAngle(playerid, BarricadeData[index][cadePos][5]);

		new Float:x, Float:y;
		GetXYInFrontOfPlayer(playerid, x, y, 1.5);
		SetPlayerPos(playerid, x, y, BarricadeData[index][cadePos][2]);
		Barricade_Sync(index);
		return index;
	}
	return -1;
}

Barricade_Delete(index, bool:remove_all = false)
{
	if(Barricade_IsExists(index))
	{
		if(!remove_all)
			Iter_Remove(Barricade, index);

		if(IsValidDynamicObject(BarricadeData[index][cadeObject]))
			DestroyDynamicObject(BarricadeData[index][cadeObject]);

		new tmp_BarricadeData[E_BARRICADE_DATA];
		BarricadeData[index] = tmp_BarricadeData;

		BarricadeData[index][cadeObject] = INVALID_STREAMER_ID;
		return 1;
	}
	return 0;
}

Barricade_Sync(index)
{
	if(Barricade_IsExists(index))
	{
		new Float:z_min;

		switch(BarricadeData[index][cadeModel])
		{
			case 981, 978: z_min = 0.2;
			case 1423: z_min = 0.3;
			case 3091, 1459, 983: z_min = 0.5;
			case 1238, 1422, 1425: z_min = 0.7;
			case 19834: z_min = -0.3;
			case 2899: z_min = 0.9;
			default: z_min = 1.0;
		}

		if(IsValidDynamicObject(BarricadeData[index][cadeObject]))
		{
			Streamer_SetFloatData(STREAMER_TYPE_OBJECT, BarricadeData[index][cadeObject], E_STREAMER_X, BarricadeData[index][cadePos][0]);
			Streamer_SetFloatData(STREAMER_TYPE_OBJECT, BarricadeData[index][cadeObject], E_STREAMER_Y, BarricadeData[index][cadePos][1]);
			Streamer_SetFloatData(STREAMER_TYPE_OBJECT, BarricadeData[index][cadeObject], E_STREAMER_Z, BarricadeData[index][cadePos][2]);
			Streamer_SetFloatData(STREAMER_TYPE_OBJECT, BarricadeData[index][cadeObject], E_STREAMER_R_X, BarricadeData[index][cadePos][3]);
			Streamer_SetFloatData(STREAMER_TYPE_OBJECT, BarricadeData[index][cadeObject], E_STREAMER_R_Y, BarricadeData[index][cadePos][4]);
			Streamer_SetFloatData(STREAMER_TYPE_OBJECT, BarricadeData[index][cadeObject], E_STREAMER_R_Z, BarricadeData[index][cadePos][5]);
		}
		else
		{
			BarricadeData[index][cadeObject] = CreateDynamicObject(BarricadeData[index][cadeModel], BarricadeData[index][cadePos][0], BarricadeData[index][cadePos][1], BarricadeData[index][cadePos][2] - z_min, BarricadeData[index][cadePos][3], BarricadeData[index][cadePos][4], BarricadeData[index][cadePos][5], 0, 0);
			if(BarricadeData[index][cadeModel] == 981)
            	SetDynamicObjectMaterialText(BarricadeData[index][cadeObject], 2, BarricadeData[index][cadeText], 100, "Arial", 30, 1, -1, 0xFF000000, 1);
		}
	}
	return 1;
}

Barricade_Nearest(playerid, Float:range = 3.0)
{
	new id = -1, Float: playerdist, Float: tempdist = 9999.0;
	
	foreach(new i : Barricade) 
	{
        playerdist = GetPlayerDistanceFromPoint(playerid, BarricadeData[i][cadePos][0], BarricadeData[i][cadePos][1], BarricadeData[i][cadePos][2]);
        
        if(playerdist > range) continue;

	    if(playerdist <= tempdist) {
	        tempdist = playerdist;
	        id = i;
	    }
	}
	return id;
}

CMD:roadblock(playerid, params[])
{
    new
        index,
        option[15],
        nextParams[225],
        Float:fX, Float:fY, Float:fZ;
        
    if(GetFactionType(playerid) != FACTION_POLICE && GetFactionType(playerid) != FACTION_MEDIC)
        return SendErrorMessage(playerid, "Kamu bukan seorang petugas kepolisian atau medic!");

    if(!PlayerData[playerid][pOnDuty])
        return SendErrorMessage(playerid, "Kamu harus faction duty terlebih dahulu.");

    if(IsPlayerInAnyVehicle(playerid))
        return SendErrorMessage(playerid, "Harus turun dari kendaraan untuk menggunakan perintah!");

    if(GetPlayerInterior(playerid) > 0 || GetPlayerVirtualWorld(playerid) > 0)
        return SendErrorMessage(playerid, "Hanya bisa digunakan di lokasi outdoor!");

    if(sscanf(params,"s[15]S()[225]", option, nextParams))
    {
        SendSyntaxMessage(playerid, "/roadblock [add/addcustom/edit/nearest/destroy/destroyall]");
        return 1;
    }
    GetPlayerPos(playerid, fX, fY, fZ);

    if(!strcmp(option, "add", true))
    {
        new text[225];

        if(sscanf(nextParams,"s[225]", text))
            return SendSyntaxMessage(playerid, "/roadblock add [text]");

        if((index = Barricade_Create(playerid, 2, 981, text)) != -1) 
        {
            PlayerData[playerid][pEditType] = EDIT_ROADBLOCK;
            PlayerData[playerid][pEditing] = index;
            EditDynamicObject(playerid, BarricadeData[index][cadeObject]);
            SendFactionMessage(PlayerData[playerid][pFaction], COLOR_RADIO, "[RADIO] %s has dropped a roadblock at %s. ((ID %d))", ReturnName(playerid), GetSpecificLocation(playerid), index);
        }
        else 
        {
            SendErrorMessage(playerid, "Roadblock sudah mencapai batas maksimal ("#MAX_DYNAMIC_ROADBLOCK" roadblock).");
        }
    }
    else if(!strcmp(option, "addcustom", true))
    {
        ShowModelSelectionMenu(playerid, "Roadblock Models", MODEL_SELECTION_ROADBLOCK, gRoadblockModels, sizeof(gRoadblockModels));
    }
    else if(!strcmp(option, "edit", true))
    {
        if(sscanf(nextParams, "d", index))
            return SendSyntaxMessage(playerid, "/roadblock edit <roadblockid>");

        if(Barricade_IsExists(index))
        {
            PlayerData[playerid][pEditType] = EDIT_ROADBLOCK;
            PlayerData[playerid][pEditing] = index;
            EditDynamicObject(playerid, BarricadeData[index][cadeObject]);
        }
        else SendErrorMessage(playerid, "Invalid roadblock id!");
    }
    else if(!strcmp(option, "nearest", true))
    {
        if((index = Barricade_Nearest(playerid)) != -1 && BarricadeData[index][cadeType] == 2)
        {
            SendServerMessage(playerid, "You stands near roadblock (( ID : %d ))", index);
        }
        else SendErrorMessage(playerid, "Kamu tidak berada didekat roadblock.");
    }
    else if(!strcmp(option, "destroy", true))
    {
        if((index = Barricade_Nearest(playerid)) != -1 && BarricadeData[index][cadeType] == 2)
        {
            Barricade_Delete(index);
            SendFactionMessage(PlayerData[playerid][pFaction], COLOR_RADIO, "[RADIO] %s has picked up a roadblock at %s.", ReturnName(playerid), GetLocation(fX, fY, fZ));
        }
        else SendErrorMessage(playerid, "Kamu tidak berada didekat roadblock.");
    }
    else if(!strcmp(option, "destroyall", true))
    {
        foreach(new i : Barricade) if(BarricadeData[i][cadeType] == 2)
        {
            Barricade_Delete(i, true);

            new next;
            Iter_SafeRemove(Barricade, i, next);
            i = next;
        }
        SendFactionMessage(PlayerData[playerid][pFaction], COLOR_RADIO, "[RADIO] %s has destroyed all of the roadblocks.", ReturnName(playerid));
    }
    else 
    {
        SendSyntaxMessage(playerid, "/roadblock [add/addcustom/edit/nearest/destroy/destroyall]");
    }
    return 1;
}