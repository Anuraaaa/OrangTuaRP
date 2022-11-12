enum dealer_data
{
	dealerID,
	bool:dealerExists,
	dealerOwner,
	dealerName[24],
	Float:dealerPos[3],
	Float:dealerSpawn[4],
	Text3D:dealerLabel,
	STREAMER_TAG_PICKUP:dealerPickup,
	dealerVehicle[6],
	dealerStock[6],
	dealerPrice,
	dealerCost[6],
	dealerVault,
	dealerVIP,
	STREAMER_TAG_MAP_ICON:dealerIcon,
};
new DealerData[MAX_DEALER][dealer_data],
	ListedDealer[MAX_PLAYERS][6];

stock FormatStock(id, slot)
{
	new str[32];
	if(DealerData[id][dealerVehicle][slot] == 19300)
	{
		str = "0";
	}
	else
	{
		format(str, sizeof(str), "%d", DealerData[id][dealerStock][slot]);
	}
	return str;
}
stock ReturnRestockPrice(price)
{
	new str[56];
	format(str, sizeof(str), "$0.00");
	if(price > 0)
	{
		format(str, sizeof(str), "$%s", FormatNumber(floatround(price * 50 / 100)));
	}
	return str;
}
stock ReturnDealerVehicle(model)
{
	new str[32];
	if(model == 19300)
	{
		str = "Unknown Vehicle";
	}
	else
	{
		format(str, sizeof(str), "%s", ReturnVehicleModelName(model));
	}
	return str;
}

stock Dealer_IsOwner(playerid, id)
{
	if(DealerData[id][dealerOwner] == PlayerData[playerid][pID])
		return true;

	return false;
}
stock Dealer_Nearest(playerid, Float:range = 4.0)
{
	forex(i, MAX_DEALER) if(DealerData[i][dealerExists])
	{
		if(IsPlayerInRangeOfPoint(playerid, range, DealerData[i][dealerPos][0], DealerData[i][dealerPos][1], DealerData[i][dealerPos][2]))
		{
			return i;
		}
	}
	return -1;
}

stock Dealer_Create(playerid, price)
{
	new Float:x, Float:y, Float:z;
	if(GetPlayerPos(playerid, x, y, z))
	{
		forex(i, MAX_DEALER)
		{
			if(!DealerData[i][dealerExists])
			{
				DealerData[i][dealerExists] = true;
				DealerData[i][dealerOwner] = -1;
				DealerData[i][dealerPrice] = price;
				DealerData[i][dealerVault] = 0;
				DealerData[i][dealerVIP] = 0;

				format(DealerData[i][dealerName], 24, "Undefined");
				forex(q, 6)
				{
					DealerData[i][dealerVehicle][q] = 19300;
					DealerData[i][dealerCost][q] = 0;
					DealerData[i][dealerStock][q] = 2;
				}
				DealerData[i][dealerPos][0] = x;
				DealerData[i][dealerPos][1] = y;
				DealerData[i][dealerPos][2] = z;
				DealerData[i][dealerSpawn][0] = 0.0;
				DealerData[i][dealerSpawn][1] = 0.0;
				DealerData[i][dealerSpawn][2] = 0.0;
				DealerData[i][dealerSpawn][3] = 0.0;
				Dealer_Spawn(i);
				mysql_tquery(sqlcon, "INSERT INTO `dealer` (`Price`) VALUES(0)", "OnDealerCreated", "d", i);
				return i;
			}
		}
	}
	return -1;
}

FUNC::OnDealerCreated(id)
{
	DealerData[id][dealerID] = cache_insert_id();
	Dealer_Save(id);
}

stock Dealer_Delete(id)
{
	if(!DealerData[id][dealerExists])
		return 0;

	if(IsValidDynamic3DTextLabel(DealerData[id][dealerLabel]))
		DestroyDynamic3DTextLabel(DealerData[id][dealerLabel]);

	if(IsValidDynamicPickup(DealerData[id][dealerPickup]))
		DestroyDynamicPickup(DealerData[id][dealerPickup]);

	new str[64];
	mysql_format(sqlcon, str, sizeof(str), "DELETE FROM `dealer` WHERE `ID` = '%d'", DealerData[id][dealerID]);
	mysql_tquery(sqlcon, str);

	DealerData[id][dealerID] = 0;
	DealerData[id][dealerOwner] = -1;
	DealerData[id][dealerExists] = false;
	return 1;
}

stock Dealer_Refresh(id)
{
	if(id != -1 && DealerData[id][dealerExists])
	{

		new str[175];
		format(str, sizeof(str), "[ID %d]\nName: {FFFF00}%s\n{FFFFFF}Type {FFFF00}/buyvehicle {FFFFFF}to buy vehicle", id, DealerData[id][dealerName]);
		UpdateDynamic3DTextLabelText(DealerData[id][dealerLabel], COLOR_SERVER, str);

		Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, DealerData[id][dealerLabel], E_STREAMER_X, DealerData[id][dealerPos][0]);
		Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, DealerData[id][dealerLabel], E_STREAMER_Y, DealerData[id][dealerPos][1]);
		Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, DealerData[id][dealerLabel], E_STREAMER_Z, DealerData[id][dealerPos][2]);

		Streamer_SetFloatData(STREAMER_TYPE_PICKUP, DealerData[id][dealerPickup], E_STREAMER_X, DealerData[id][dealerPos][0]);
		Streamer_SetFloatData(STREAMER_TYPE_PICKUP, DealerData[id][dealerPickup], E_STREAMER_Y, DealerData[id][dealerPos][1]);
		Streamer_SetFloatData(STREAMER_TYPE_PICKUP, DealerData[id][dealerPickup], E_STREAMER_Z, DealerData[id][dealerPos][2]);
	}
	return 1;
}

FUNC::Dealer_Load()
{
	new rows = cache_num_rows();
	if(rows)
	{
	    forex(i, rows)
	    {
	    	DealerData[i][dealerExists] = true;
	    	cache_get_value_name_int(i, "ID", DealerData[i][dealerID]);
	    	cache_get_value_name(i, "Name", DealerData[i][dealerName]);
	    	cache_get_value_name_int(i, "Price", DealerData[i][dealerPrice]);
	    	cache_get_value_name_int(i, "Owner", DealerData[i][dealerOwner]);
	    	cache_get_value_name_float(i, "PosX", DealerData[i][dealerPos][0]);
	    	cache_get_value_name_float(i, "PosY", DealerData[i][dealerPos][1]);
	    	cache_get_value_name_float(i, "PosZ", DealerData[i][dealerPos][2]);
	    	cache_get_value_name_float(i, "SpawnX", DealerData[i][dealerSpawn][0]);
	    	cache_get_value_name_float(i, "SpawnY", DealerData[i][dealerSpawn][1]);
	    	cache_get_value_name_float(i, "SpawnZ", DealerData[i][dealerSpawn][2]);
	    	cache_get_value_name_float(i, "SpawnA", DealerData[i][dealerSpawn][3]);
	    	cache_get_value_name_int(i, "Vault", DealerData[i][dealerVault]);
			cache_get_value_name_int(i, "VIP", DealerData[i][dealerVIP]);

			forex(z, 6)
			{
			    new zquery[256];
			    format(zquery, sizeof(zquery), "Cost%d", z + 1);
			    cache_get_value_name_int(i,zquery,DealerData[i][dealerCost][z]);

			    format(zquery, sizeof(zquery), "Vehicle%d", z + 1);
			    cache_get_value_name_int(i,zquery,DealerData[i][dealerVehicle][z]);

			    format(zquery, sizeof(zquery), "Stock%d", z + 1);
			    cache_get_value_name_int(i, zquery, DealerData[i][dealerStock][z]);
			}
			Dealer_Spawn(i);
		}
		printf("[DEALER] Loaded %d dealership from database", rows);
	}
	return 1;
}

stock Dealer_Spawn(i)
{
	new str[175];
	format(str, sizeof(str), "[ID %d]\nName: {FFFF00}%s\n{FFFFFF}Type {FFFF00}/buyvehicle {FFFFFF}to buy vehicle", i, DealerData[i][dealerName]);
	DealerData[i][dealerLabel] = CreateDynamic3DTextLabel(str, -1, DealerData[i][dealerPos][0], DealerData[i][dealerPos][1], DealerData[i][dealerPos][2], 15.0);
	DealerData[i][dealerPickup] = CreateDynamicPickup(19133, 23,  DealerData[i][dealerPos][0], DealerData[i][dealerPos][1], DealerData[i][dealerPos][2]);
	return 1;
}
stock Dealer_Save(id)
{
	new query[1052];
	mysql_format(sqlcon, query, sizeof(query), "UPDATE `dealer` SET ");
	mysql_format(sqlcon, query, sizeof(query), "%s`Name`='%s', ", query, DealerData[id][dealerName]);
	mysql_format(sqlcon, query, sizeof(query), "%s`Owner`='%d', ", query, DealerData[id][dealerOwner]);
	mysql_format(sqlcon, query, sizeof(query), "%s`Stock`='%d', ", query, DealerData[id][dealerStock]);
	mysql_format(sqlcon, query, sizeof(query), "%s`Vault`='%d', ", query, DealerData[id][dealerVault]);
	mysql_format(sqlcon, query, sizeof(query), "%s`PosX`='%f', ", query, DealerData[id][dealerPos][0]);
	mysql_format(sqlcon, query, sizeof(query), "%s`PosY`='%f', ", query, DealerData[id][dealerPos][1]);
	mysql_format(sqlcon, query, sizeof(query), "%s`PosZ`='%f', ", query, DealerData[id][dealerPos][2]);
	mysql_format(sqlcon, query, sizeof(query), "%s`SpawnX`='%f', ", query, DealerData[id][dealerSpawn][0]);
	mysql_format(sqlcon, query, sizeof(query), "%s`SpawnY`='%f', ", query, DealerData[id][dealerSpawn][1]);
	mysql_format(sqlcon, query, sizeof(query), "%s`SpawnZ`='%f', ", query, DealerData[id][dealerSpawn][2]);
	mysql_format(sqlcon, query, sizeof(query), "%s`SpawnA`='%f', ", query, DealerData[id][dealerSpawn][3]);
	mysql_format(sqlcon, query, sizeof(query), "%s`VIP`='%d', ", query, DealerData[id][dealerVIP]);
	forex(i, 6)
	{
		mysql_format(sqlcon, query, sizeof(query), "%s`Vehicle%d` = '%d', `Cost%d` = '%d', `Stock%d` = '%d', ", query, i + 1, DealerData[id][dealerVehicle][i], i + 1, DealerData[id][dealerCost][i], i + 1, DealerData[id][dealerStock][i]);
	}
	mysql_format(sqlcon, query, sizeof(query), "%s`Price`='%d' ", query, DealerData[id][dealerPrice]);
	mysql_format(sqlcon, query, sizeof(query), "%sWHERE `ID` = '%d'", query, DealerData[id][dealerID]);
	mysql_tquery(sqlcon, query);
	return 1;
}

CMD:buyvehicle(playerid, params[])
{
	new id = -1;

	if((id = Dealer_Nearest(playerid)) != -1) {

		if(DealerData[id][dealerVIP] && !GetPlayerVIPLevel(playerid))
			return SendErrorMessage(playerid, "Dealership ini diperuntukkan kepada Donater Player.");
			
		new str[512], bool:has = false, count = 0;
		format(str, sizeof(str), "Price\tVehicle\tStock\n");
		for(new i = 0; i < 6; i++) if(DealerData[id][dealerVehicle][i] != 19300)
		{
			format(str, sizeof(str), "%s"DARKGREEN"$%s\t"WHITE"%s\t"GREY"%s left\n", str, FormatNumber(DealerData[id][dealerCost][i]), ReturnDealerVehicle(DealerData[id][dealerVehicle][i]), FormatStock(id, i));
			has = true;
			ListedDealer[playerid][count++] = i;
		}

		PlayerData[playerid][pSelecting] = id;

		if(has)
			ShowPlayerDialog(playerid, DIALOG_DEALER_BUY, DIALOG_STYLE_TABLIST_HEADERS, "Purchase Vehicle", str, "Purchase", "Close");

		else SendErrorMessage(playerid, "Tidak ada kendaraan pada dealer ini.");
		
	}
	else SendErrorMessage(playerid, "Kamu tidak berada di dealer-ship manapun.");
	return 1;
}

CMD:editdealer(playerid, params[])
{
	new id, type[24], string[128];
    if(PlayerData[playerid][pAdmin] < 6)
        return SendErrorMessage(playerid, "You don't have permission to use this command!");

    if(sscanf(params, "ds[24]S()[128]", id, type, string))
    {
        SendSyntaxMessage(playerid, "/editdealer [id] [name]");
        SendClientMessage(playerid, COLOR_SERVER, "Names:{FFFFFF} location, vehicle, spawn, stock, name, vip");
        return 1;
    }	
    if((id < 0 || id >= MAX_DEALER))
        return SendErrorMessage(playerid, "You have specified an invalid ID.");

	if(!DealerData[id][dealerExists])
        return SendErrorMessage(playerid, "You have specified an invalid ID.");  

    if(!strcmp(type, "location", true))
    {
    	GetPlayerPos(playerid, DealerData[id][dealerPos][0], DealerData[id][dealerPos][1], DealerData[id][dealerPos][2]);
    	Dealer_Save(id);
    	Dealer_Refresh(id);

    	SendAdminAction(playerid, "Kamu telah mengubah posisi Dealership ID %d", id);
    }
    else if(!strcmp(type, "spawn", true))
    {
    	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
    		return SendErrorMessage(playerid, "Kamu harus berada didalam kendaraan!");

    	new vid = GetPlayerVehicleID(playerid);
    	GetVehiclePos(vid, DealerData[id][dealerSpawn][0], DealerData[id][dealerSpawn][1], DealerData[id][dealerSpawn][2]);
    	GetVehicleZAngle(vid, DealerData[id][dealerSpawn][3]);

    	Dealer_Save(id);

    	SendAdminAction(playerid, "Kamu telah mengubah posisi spawn Dealership ID %d", id);
    }
	else if(!strcmp(type, "vip", true)) {

		DealerData[id][dealerVIP] = !(DealerData[id][dealerVIP]);
		SendAdminAction(playerid, "Kamu telah mengubah Dealership ID %d menjadi %s", id, (DealerData[id][dealerVIP]) ? ("only donater") : ("Tidak only donater"));
		Dealer_Save(id);
	}
    else if(!strcmp(type, "vehicle", true))
    {
		new str[512];
		format(str, sizeof(str), "Price\tVehicle\tStock\n");
		forex(i, 6)
		{
			format(str, sizeof(str), "%s"DARKGREEN"$%s\t"WHITE"%s\t"GREY"%s left\n", str, FormatNumber(DealerData[id][dealerCost][i]), ReturnDealerVehicle(DealerData[id][dealerVehicle][i]), FormatStock(id, i));
		}
    	ShowPlayerDialog(playerid, DIALOG_EDITDEALER_SELECT, DIALOG_STYLE_TABLIST_HEADERS, "Edit Vehicle", str, "Select", "Close");
    	PlayerData[playerid][pSelecting] = id;
    }
	else if(!strcmp(type, "name", true)) {

		ShowPlayerDialog(playerid, DIALOG_DEALER_SETNAME, DIALOG_STYLE_INPUT, "Dealer Name", "Silahkan masukan nama baru untuk dealership:", "Set", "Close");
		PlayerData[playerid][pSelecting] = id;
	}
	else if(!strcmp(type, "stock", true)) {

		new str[512];
		format(str, sizeof(str), "Model\tStock\n");
		forex(i, 6)
		{
			format(str, sizeof(str), "%s%s\t%d\n", str, ReturnDealerVehicle(DealerData[id][dealerVehicle][i]), DealerData[id][dealerStock][i]);
		}
		ShowPlayerDialog(playerid, DIALOG_DEALER_RESTOCK_LIST, DIALOG_STYLE_TABLIST_HEADERS, "Restock List", str, "Select", "Close");
		PlayerData[playerid][pSelecting] = id;
	}
    return 1; 
}

CMD:createdealer(playerid, params[])
{
	new price[32];
    if (PlayerData[playerid][pAdmin] < 7)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if(sscanf(params, "s[32]", price))
		return SendSyntaxMessage(playerid, "/createdealer [price]");

	new id = Dealer_Create(playerid, strcash(price));
	if(id == -1)
		return SendErrorMessage(playerid, "The server has reached the limit for dealerships.");

	SendServerMessage(playerid, "You have successfully created Dealership ID: %d.", id);
	return 1;
}

CMD:destroydealer(playerid, params[])
{
	static
	    id = 0;

    if (PlayerData[playerid][pAdmin] < 7)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "d", id))
	    return SendSyntaxMessage(playerid, "/destroydealer [dealer id]");

	if ((id < 0 || id >= MAX_DEALER) || !DealerData[id][dealerExists])
	    return SendErrorMessage(playerid, "You have specified an invalid Delership ID.");

	Dealer_Delete(id);
	SendServerMessage(playerid, "You have successfully destroyed Dealership ID: %d.", id);
	return 1;
}

