#include <YSI_Coding\y_hooks>

#define 			MAX_DEALER_VEHICLE				30

enum dealer_data
{
	dealerID,
	bool:dealerExists,
	dealerName[24],
	Float:dealerPos[3],
	Float:dealerSpawn[4],
	Text3D:dealerLabel,
	STREAMER_TAG_PICKUP:dealerPickup,
	dealerPrice,
	dealerVault,
	dealerVIP,
	STREAMER_TAG_MAP_ICON:dealerIcon,
};

enum E_DEALER_VEHICLE {
	dealer_veh_id,
	dealer_veh_model,
	dealer_veh_stock,
	dealer_veh_dealerID,
	dealer_veh_price,
	bool:dealer_veh_exists
};
new DealerVehicle[MAX_DEALER][MAX_DEALER_VEHICLE][E_DEALER_VEHICLE];
new DealerData[MAX_DEALER][dealer_data];

GetNearestDealership(playerid, Float:range = 4.0)
{
	new index = -1;
	forex(i, MAX_DEALER) if(DealerData[i][dealerExists])
	{
		if(IsPlayerInRangeOfPoint(playerid, range, DealerData[i][dealerPos][0], DealerData[i][dealerPos][1], DealerData[i][dealerPos][2]))
		{
			index = i;
			break;
		}
	}
	return index;
}

CreateDealership(playerid, price)
{
	new Float:x, Float:y, Float:z;
	if(GetPlayerPos(playerid, x, y, z))
	{
		for(new i = 0 ; i < MAX_DEALER; i++)
		{
			if(!DealerData[i][dealerExists])
			{
				DealerData[i][dealerExists] = true;
				DealerData[i][dealerPrice] = price;
				DealerData[i][dealerVault] = 0;
				DealerData[i][dealerVIP] = 0;

				format(DealerData[i][dealerName], 24, "Undefined");

				DealerData[i][dealerPos][0] = x;
				DealerData[i][dealerPos][1] = y;
				DealerData[i][dealerPos][2] = z;
				DealerData[i][dealerSpawn][0] = 0.0;
				DealerData[i][dealerSpawn][1] = 0.0;
				DealerData[i][dealerSpawn][2] = 0.0;
				DealerData[i][dealerSpawn][3] = 0.0;

				for(new j = 0; j < MAX_DEALER_VEHICLE; j++) {
					DealerVehicle[i][j][dealer_veh_exists] = false;
				}
				SpawnDealership(i);
				mysql_tquery(sqlcon, "INSERT INTO `dealer` (`Price`) VALUES(0)", "OnDealerCreated", "d", i);
				return i;
			}
		}
	}
	return -1;
}

function OnDealerCreated(id)
{
	DealerData[id][dealerID] = cache_insert_id();
	SQL_SaveDealership(id);
}

RemoveDealership(id)
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
	DealerData[id][dealerExists] = false;

	mysql_tquery(sqlcon, sprintf("DELETE FROM `dealervehicle` WHERE `DealerID` = '%d'", DealerData[id][dealerID]));
	for(new index = 0; index < MAX_DEALER_VEHICLE; index++) {
		DealerVehicle[id][index][dealer_veh_exists] = false;
		DealerVehicle[id][index][dealer_veh_model] = 0;
		DealerVehicle[id][index][dealer_veh_price] = 0;
		DealerVehicle[id][index][dealer_veh_stock] = 0;
		DealerVehicle[id][index][dealer_veh_dealerID] = -1;
	}
	return 1;
}

SyncDealership(id)
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

function SQL_LoadDealership()
{
	new rows = cache_num_rows();
	if(rows)
	{
	    for(new i = 0 ; i < rows; i++)
	    {
	    	DealerData[i][dealerExists] = true;
	    	cache_get_value_name_int(i, "ID", DealerData[i][dealerID]);
	    	cache_get_value_name(i, "Name", DealerData[i][dealerName]);
	    	cache_get_value_name_int(i, "Price", DealerData[i][dealerPrice]);
	    	cache_get_value_name_float(i, "PosX", DealerData[i][dealerPos][0]);
	    	cache_get_value_name_float(i, "PosY", DealerData[i][dealerPos][1]);
	    	cache_get_value_name_float(i, "PosZ", DealerData[i][dealerPos][2]);
	    	cache_get_value_name_float(i, "SpawnX", DealerData[i][dealerSpawn][0]);
	    	cache_get_value_name_float(i, "SpawnY", DealerData[i][dealerSpawn][1]);
	    	cache_get_value_name_float(i, "SpawnZ", DealerData[i][dealerSpawn][2]);
	    	cache_get_value_name_float(i, "SpawnA", DealerData[i][dealerSpawn][3]);
	    	cache_get_value_name_int(i, "Vault", DealerData[i][dealerVault]);
			cache_get_value_name_int(i, "VIP", DealerData[i][dealerVIP]);

			SpawnDealership(i);

			mysql_tquery(sqlcon, sprintf("SELECT * FROM `dealervehicle` WHERE `DealerID` = '%d'", DealerData[i][dealerID]), "OnDealerVehicleLoad", "d", i);
		}
		printf("[DEALER] Loaded %d dealership from database", rows);
	}
	return 1;
}

function OnDealerVehicleLoad(id) {

	for(new i = 0; i < cache_num_rows(); i++) {
		DealerVehicle[id][i][dealer_veh_exists] = true;
		DealerVehicle[id][i][dealer_veh_dealerID] = id;
		DealerVehicle[id][i][dealer_veh_model] = cache_get_field_int(i, "Model");
		DealerVehicle[id][i][dealer_veh_stock] = cache_get_field_int(i, "Stock");
		DealerVehicle[id][i][dealer_veh_price] = cache_get_field_int(i, "Price");
	}
	return 1;
}
SpawnDealership(i)
{
	new str[175];
	format(str, sizeof(str), "[ID %d]\nName: {FFFF00}%s\n{FFFFFF}Type {FFFF00}/buyvehicle {FFFFFF}to buy vehicle", i, DealerData[i][dealerName]);
	DealerData[i][dealerLabel] = CreateDynamic3DTextLabel(str, -1, DealerData[i][dealerPos][0], DealerData[i][dealerPos][1], DealerData[i][dealerPos][2], 15.0);
	DealerData[i][dealerPickup] = CreateDynamicPickup(19133, 23,  DealerData[i][dealerPos][0], DealerData[i][dealerPos][1], DealerData[i][dealerPos][2]);
	return 1;
}

SQL_SaveDealership(id)
{
	new query[1052];
	mysql_format(sqlcon, query, sizeof(query), "UPDATE `dealer` SET ");
	mysql_format(sqlcon, query, sizeof(query), "%s`Name`='%s', ", query, DealerData[id][dealerName]);
	mysql_format(sqlcon, query, sizeof(query), "%s`Vault`='%d', ", query, DealerData[id][dealerVault]);
	mysql_format(sqlcon, query, sizeof(query), "%s`PosX`='%f', ", query, DealerData[id][dealerPos][0]);
	mysql_format(sqlcon, query, sizeof(query), "%s`PosY`='%f', ", query, DealerData[id][dealerPos][1]);
	mysql_format(sqlcon, query, sizeof(query), "%s`PosZ`='%f', ", query, DealerData[id][dealerPos][2]);
	mysql_format(sqlcon, query, sizeof(query), "%s`SpawnX`='%f', ", query, DealerData[id][dealerSpawn][0]);
	mysql_format(sqlcon, query, sizeof(query), "%s`SpawnY`='%f', ", query, DealerData[id][dealerSpawn][1]);
	mysql_format(sqlcon, query, sizeof(query), "%s`SpawnZ`='%f', ", query, DealerData[id][dealerSpawn][2]);
	mysql_format(sqlcon, query, sizeof(query), "%s`SpawnA`='%f', ", query, DealerData[id][dealerSpawn][3]);
	mysql_format(sqlcon, query, sizeof(query), "%s`VIP`='%d' ", query, DealerData[id][dealerVIP]);
	mysql_format(sqlcon, query, sizeof(query), "%sWHERE `ID` = '%d'", query, DealerData[id][dealerID]);
	mysql_tquery(sqlcon, query);
	return 1;
}

CMD:buyvehicle(playerid, params[])
{
	new id = -1;

	if((id = GetNearestDealership(playerid)) != -1) {

		if(DealerData[id][dealerVIP] && !GetPlayerVIPLevel(playerid))
			return SendErrorMessage(playerid, "Dealership ini diperuntukkan kepada Donater Player.");

		if(!GetDealerTotalVehicle(id))
			return SendErrorMessage(playerid, "Tidak ada kendaraan yang dapat ditampilkan.");
		
		new str[MAX_DEALER_VEHICLE * 32];
		for(new i = 0; i < MAX_DEALER_VEHICLE; i++) if(DealerVehicle[id][i][dealer_veh_exists]) {
			format(str, sizeof(str), "%s%i\t~g~$%s~n~~w~%s\n", str, DealerVehicle[id][i][dealer_veh_model], FormatNumber(DealerVehicle[id][i][dealer_veh_price]), ReturnVehicleModelName(DealerVehicle[id][i][dealer_veh_model]));
			//strcat(str, sprintf(""WHITE"%d. %s\t"DARKGREEN"$%s\t"WHITE"%d\n", i + 1, ReturnVehicleModelName(DealerVehicle[id][i][dealer_veh_model]), FormatNumber(DealerVehicle[id][i][dealer_veh_price]), DealerVehicle[id][i][dealer_veh_stock]));
		}
		ShowPlayerDialog(playerid, DIALOG_DEALER_BUY, DIALOG_STYLE_PREVIEW_MODEL, "Beli Kendaraan", str, "Select", "Close");
		PlayerData[playerid][pSelecting] = id;
		
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
        SendClientMessage(playerid, COLOR_SERVER, "(Names){FFFFFF} location, vehicle, spawn, stock, name, vip");
        return 1;
    }	
    if((id < 0 || id >= MAX_DEALER))
        return SendErrorMessage(playerid, "You have specified an invalid ID.");

	if(!DealerData[id][dealerExists])
        return SendErrorMessage(playerid, "You have specified an invalid ID.");  

    if(!strcmp(type, "location", true))
    {
    	GetPlayerPos(playerid, DealerData[id][dealerPos][0], DealerData[id][dealerPos][1], DealerData[id][dealerPos][2]);
    	SQL_SaveDealership(id);
    	SyncDealership(id);

    	SendAdminAction(playerid, "Kamu telah mengubah posisi Dealership ID %d", id);
    }
    else if(!strcmp(type, "spawn", true))
    {
    	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
    		return SendErrorMessage(playerid, "Kamu harus berada didalam kendaraan!");

    	new vid = GetPlayerVehicleID(playerid);
    	GetVehiclePos(vid, DealerData[id][dealerSpawn][0], DealerData[id][dealerSpawn][1], DealerData[id][dealerSpawn][2]);
    	GetVehicleZAngle(vid, DealerData[id][dealerSpawn][3]);

    	SQL_SaveDealership(id);

    	SendAdminAction(playerid, "Kamu telah mengubah posisi spawn Dealership ID %d", id);
    }
	else if(!strcmp(type, "vip", true)) {

		DealerData[id][dealerVIP] = !(DealerData[id][dealerVIP]);
		SendAdminAction(playerid, "Kamu telah mengubah Dealership ID %d menjadi %s", id, (DealerData[id][dealerVIP]) ? ("only donater") : ("Tidak only donater"));
		SQL_SaveDealership(id);
	}
    else if(!strcmp(type, "vehicle", true))
    {
		new str[MAX_DEALER_VEHICLE * 32], total_vehs = 0;
		strcat(str, "Vehicle\tPrice\tStock\n");
		for(new i = 0; i < MAX_DEALER_VEHICLE; i++) if(DealerVehicle[id][i][dealer_veh_exists]) {
			strcat(str, sprintf(""WHITE"%d. %s\t"DARKGREEN"$%s\t"WHITE"%d\n", i + 1, ReturnVehicleModelName(DealerVehicle[id][i][dealer_veh_model]), FormatNumber(DealerVehicle[id][i][dealer_veh_price]), DealerVehicle[id][i][dealer_veh_stock]));
			total_vehs++;
		}
		if(total_vehs < MAX_DEALER_VEHICLE) 
			strcat(str, "Tambahkan kendaraan");
			
    	ShowPlayerDialog(playerid, DIALOG_EDITDEALER_SELECT, DIALOG_STYLE_TABLIST_HEADERS, "Edit Dealership Vehicle", str, "Select", "Close");
    	PlayerData[playerid][pSelecting] = id;
    }
	else if(!strcmp(type, "name", true)) {

		ShowPlayerDialog(playerid, DIALOG_DEALER_SETNAME, DIALOG_STYLE_INPUT, "Dealer Name", "Silahkan masukan nama baru untuk dealership:", "Set", "Close");
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
		return SendSyntaxMessage(playerid, "/createdealer");

	new id = CreateDealership(playerid, strcash(price));
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

	RemoveDealership(id);
	SendServerMessage(playerid, "You have successfully destroyed Dealership ID: %d.", id);
	return 1;
}


ShowEditDealerMenu(playerid) {
	ShowPlayerDialog(playerid, DIALOG_EDITDEALER_MENU, DIALOG_STYLE_LIST, sprintf("Editing Vehicle: index #%d", PlayerData[playerid][pListitem]), "Edit model\nUpdate stock\nChange price\nRemove from list", "Select", "Close");
	return 1;
}

SQL_UpdateDealerVehicle(id, index) {
	new query[512];
	mysql_format(sqlcon, query, sizeof(query), "UPDATE `dealervehicle` SET `Model` = '%d', `Stock` = '%d', `Price` = '%d' WHERE `ID` = '%d'",
		DealerVehicle[id][index][dealer_veh_model], DealerVehicle[id][index][dealer_veh_stock], DealerVehicle[id][index][dealer_veh_price], DealerVehicle[id][index][dealer_veh_id]
	);
	return mysql_tquery(sqlcon, query);
}

RemoveVehicleFromList(id, index) {
	if(DealerData[id][dealerExists]) {
		DealerVehicle[id][index][dealer_veh_exists] = false;
		DealerVehicle[id][index][dealer_veh_model] = 0;
		DealerVehicle[id][index][dealer_veh_price] = 0;
		DealerVehicle[id][index][dealer_veh_stock] = 0;
		DealerVehicle[id][index][dealer_veh_dealerID] = -1;
		mysql_tquery(sqlcon, sprintf("DELETE FROM `dealervehicle` WHERE `ID` = '%d'", DealerVehicle[id][index][dealer_veh_id]));
	}
	return 1;
}

GetDealerTotalVehicle(id) {
	new total = 0;
	for(new i = 0; i < MAX_DEALER_VEHICLE; i++) if(DealerVehicle[id][i][dealer_veh_exists]) {
		total++;
	}
	return total;
}

GetFreeDealerVehicle(id) {
	new index = -1;
	for(new i = 0; i < MAX_DEALER_VEHICLE; i++) if(!DealerVehicle[id][i][dealer_veh_exists]) {
		index = i;
		break;
	}
	return index;
}
AddDealerVehicle(id, modelid) {

	new index = -1;
	if((index = GetFreeDealerVehicle(id)) != -1) {
		DealerVehicle[id][index][dealer_veh_dealerID] = DealerData[id][dealerID];
		DealerVehicle[id][index][dealer_veh_model] = modelid;
		DealerVehicle[id][index][dealer_veh_stock] = 0;
		DealerVehicle[id][index][dealer_veh_price] = 0;
		DealerVehicle[id][index][dealer_veh_exists] = true;
		mysql_tquery(sqlcon, sprintf("INSERT INTO `dealervehicle` (`DealerID`, `Model`, `Stock`, `Price`) VALUES('%d', '%d', '%d', '%d')", DealerData[id][dealerID], modelid, 0, 0), "OnDealerVehicleAdd", "dd", id, index);
	}
	return index;
}

function OnDealerVehicleAdd(id, index) {
	DealerVehicle[id][index][dealer_veh_id] = cache_insert_id();
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {
	if(dialogid == DIALOG_DEALER_BUY) {
		if(response) {
			PlayerData[playerid][pListitem] = listitem;
			ShowPlayerDialog(playerid, DIALOG_DEALER_BUYMENU, DIALOG_STYLE_LIST, "Opsi Kendaraan", "Check details\nPurchase this vehicle", "Select", "Close");
		}
	}
	if(dialogid == DIALOG_DEALER_RETURN) {
		ShowPlayerDialog(playerid, DIALOG_DEALER_BUYMENU, DIALOG_STYLE_LIST, "Opsi Kendaraan", "Check details\nPurchase this vehicle", "Select", "Close");
	}
	if(dialogid == DIALOG_DEALER_BUYMENU) {
		if(response) {
			new string[512],
				id = PlayerData[playerid][pSelecting],
				slot = CountPlayerVehicleSlot(playerid),
				index = PlayerData[playerid][pListitem];

			if(listitem == 0) {
				format(string, sizeof(string), ""GREY"Nama kendaraan:\n"LIGHTBLUE"%s\n\n\
												"GREY"Kategori:\n\
												"LIGHTBLUE"%s\n\n\
												"GREY"Kapasitas bahan bakar:\n\
												"GOLD"%.2f liter/h\n\n\
												"GREY"Potensial TopSpeed (km/h):\n\
												"GOLD"%ikm/h\n\n\n\n\
												"WHITE"Kendaraan ini dihargai sebesar "GREEN"$%s",
												ReturnVehicleModelName(DealerVehicle[id][index][dealer_veh_model]),
												GetVehicleCategoryName(DealerVehicle[id][index][dealer_veh_model]),
												GetVehicleFuelMax(DealerVehicle[id][index][dealer_veh_model]),
												Model_TopSpeed(DealerVehicle[id][index][dealer_veh_model]),
												FormatNumber(DealerVehicle[id][index][dealer_veh_price]));
				ShowPlayerDialog(playerid, DIALOG_DEALER_RETURN, DIALOG_STYLE_MSGBOX, "Detail Kendaraan", string, "Return", "");
			}
			if(listitem == 1) {
				if(Vehicle_Count(playerid) >= slot)
					return SendErrorMessage(playerid, "Kamu hanya dapat memiliki %d kendaraan sekarang.", slot);

				if(DealerData[id][dealerSpawn][0] == 0)
					return SendErrorMessage(playerid, "Dealership ini belum memiliki posisi spawn.");

				if(DealerVehicle[id][index][dealer_veh_stock] < 1)
					return SendErrorMessage(playerid, "Tidak ada stok untuk kendaraan ini.");

				if(GetMoney(playerid) < DealerVehicle[id][index][dealer_veh_price])
					return SendErrorMessage(playerid, "Kamu tidak membawa uang yang cukup.");

				new vehicleid = Vehicle_Create(DealerVehicle[id][index][dealer_veh_model], DealerData[id][dealerSpawn][0], DealerData[id][dealerSpawn][1], DealerData[id][dealerSpawn][2], DealerData[id][dealerSpawn][3], random(255), random(255));
				Vehicle_SetOwner(vehicleid, playerid, true);
				Vehicle_SetType(vehicleid, VEHICLE_TYPE_PLAYER);
				VehicleData[vehicleid][vPrice] = DealerVehicle[id][index][dealer_veh_price];

				SendServerMessage(playerid, "Kamu berhasil membeli {FFFF00}%s {FFFFFF}dengan harga {00FF00}$%s", ReturnVehicleModelName(DealerVehicle[id][index][dealer_veh_model]), FormatNumber(DealerVehicle[id][index][dealer_veh_price]));
				GiveMoney(playerid, -DealerVehicle[id][index][dealer_veh_price], "Membeli kendaraan");
				DealerData[id][dealerVault] += DealerVehicle[id][index][dealer_veh_price];
				DealerVehicle[id][index][dealer_veh_stock]--;

				SQL_UpdateDealerVehicle(id, index);
				PutPlayerInVehicle(playerid, vehicleid, 0);
			}
		}
	}
	if(dialogid == DIALOG_DEALER_SETNAME)
	{
		if(!response)
			return 0;

		if(isnull(inputtext))
			return ShowPlayerDialog(playerid, DIALOG_DEALER_SETNAME, DIALOG_STYLE_INPUT, "Dealer Name", "Silahkan masukan nama baru untuk dealership:", "Set", "Close");

		if(strlen(inputtext) > 24)
			return ShowPlayerDialog(playerid, DIALOG_DEALER_SETNAME, DIALOG_STYLE_INPUT, "Dealer Name", "ERROR: Nama dealer tidak bisa lebih dari 24 huruf!\nSilahkan masukan nama baru untuk dealership:", "Set", "Close");
		
		format(DealerData[PlayerData[playerid][pSelecting]][dealerName], 24, inputtext);
		SendServerMessage(playerid, "Kamu berhasil mengubah nama dealership menjadi {FFFF00}%s", DealerData[PlayerData[playerid][pSelecting]][dealerName]);
		SQL_SaveDealership(PlayerData[playerid][pSelecting]);
		SyncDealership(PlayerData[playerid][pSelecting]);
	}
	if(dialogid == DIALOG_EDITDEALER_ADDVEH) {
		if(response) {
			new model[16];
			if(sscanf(inputtext, "s[16]", model))
				return ShowPlayerDialog(playerid, DIALOG_EDITDEALER_ADDVEH, DIALOG_STYLE_INPUT, "Add new vehicle", "Masukkan Model ID atau Nama Model yang akan ditambahkan:", "Add", "Close");
			
			if ((model[0] = GetVehicleModelByName(model)) == 0)
				return SendErrorMessage(playerid, "Invalid model ID."), ShowPlayerDialog(playerid, DIALOG_EDITDEALER_ADDVEH, DIALOG_STYLE_INPUT, "Add new vehicle", "Masukkan Model ID atau Nama Model yang akan ditambahkan:", "Add", "Close");
		
			new idx = AddDealerVehicle(PlayerData[playerid][pSelecting], model[0]);
			if(idx != -1) {
				SendServerMessage(playerid, "Kendaraan (%s) ditambahkan pada index baru #%d", ReturnVehicleModelName(model[0]), idx);
				SendServerMessage(playerid, "Kamu dapat mengubah harga dan stock kendaraan pada "GREY"/editdealer %d vehicle", PlayerData[playerid][pSelecting]);
			}
		}
	}
	if(dialogid == DIALOG_EDITDEALER_SELECT) {
		if(response) {
			if(isequal(inputtext, "Tambahkan kendaraan")) {
				ShowPlayerDialog(playerid, DIALOG_EDITDEALER_ADDVEH, DIALOG_STYLE_INPUT, "Add new vehicle", "Masukkan Model ID atau Nama Model yang akan ditambahkan:", "Add", "Close");
			}
			else {
				PlayerData[playerid][pListitem] = listitem;
				
				ShowEditDealerMenu(playerid);
			}
		}
	}
	if(dialogid == DIALOG_EDITDEALER_MENU) {
		if(response) {
			switch(listitem) {
				case 0: ShowPlayerDialog(playerid, DIALOG_EDITDEALER_MODEL, DIALOG_STYLE_INPUT, "Edit Model", "Masukkan Model ID atau Nama dari kendaraan yang akan diubah:", "Edit", "Close");
				case 1: ShowPlayerDialog(playerid, DIALOG_EDITDEALER_STOCK, DIALOG_STYLE_INPUT, "Update Stock", "Masukkan jumlah stock yang akan diupdate:", "Set", "Close");
				case 2: ShowPlayerDialog(playerid, DIALOG_EDITDEALER_PRICE, DIALOG_STYLE_INPUT, "Change Price", "Masukkan harga kendaraan yang akan diubah:", "Set", "Close");
				case 3: {
					RemoveVehicleFromList(PlayerData[playerid][pSelecting], PlayerData[playerid][pListitem]);
					SendServerMessage(playerid, "Kendaraan berhasil dihapus.");
				}
			}
		}
	}
	if(dialogid == DIALOG_EDITDEALER_PRICE) {
		if(response) {

			new index = PlayerData[playerid][pListitem],
				id = PlayerData[playerid][pSelecting];

			DealerVehicle[id][index][dealer_veh_price] = strcash(inputtext);
			SQL_UpdateDealerVehicle(id, index);
			SendServerMessage(playerid, "Harga kendaraan pada index %d berhasil diupdate menjadi $%s.", index, FormatNumber(strcash(inputtext)));
			ShowEditDealerMenu(playerid);	
		}
	}
	if(dialogid == DIALOG_EDITDEALER_STOCK) {
		if(response) {

			new index = PlayerData[playerid][pListitem],
				id = PlayerData[playerid][pSelecting];

			DealerVehicle[id][index][dealer_veh_stock] = strval(inputtext);
			SQL_UpdateDealerVehicle(id, index);
			SendServerMessage(playerid, "Stock kendaraan pada index %d berhasil diupdate menjadi %d.", index, strval(inputtext));
			ShowEditDealerMenu(playerid);	
		}
	}
	if(dialogid == DIALOG_EDITDEALER_MODEL) {
		if(response) {

			new model[16];
			if(sscanf(inputtext, "s[16]", model))
				return ShowPlayerDialog(playerid, DIALOG_EDITDEALER_MODEL, DIALOG_STYLE_INPUT, "Edit Model", "Masukkan Model ID atau Nama dari kendaraan yang akan diubah:", "Edit", "Close");
			
			if ((model[0] = GetVehicleModelByName(model)) == 0)
				return SendErrorMessage(playerid, "Invalid model ID."), ShowPlayerDialog(playerid, DIALOG_EDITDEALER_MODEL, DIALOG_STYLE_INPUT, "Edit Model", "Masukkan Model ID atau Nama dari kendaraan yang akan diubah:", "Edit", "Close");

			new index = PlayerData[playerid][pListitem],
				id = PlayerData[playerid][pSelecting];

			DealerVehicle[id][index][dealer_veh_model] = model[0];
			SQL_UpdateDealerVehicle(id, index);
			SendServerMessage(playerid, "Kendaraan pada index %d berhasil diubah menjadi %s.", index, ReturnVehicleModelName(model[0]));
			ShowEditDealerMenu(playerid);
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}