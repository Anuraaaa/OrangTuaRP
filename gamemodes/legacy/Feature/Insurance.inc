new Float:Random_Insu[][] = {
{-1935.5217,583.7208,35.3109,179.5877},
{-1929.3014,583.8879,35.3110,180.7003},
{-1941.4504,583.7183,35.3114,179.2933},
{-1950.2317,583.7834,35.3107,180.0581}
};

GetInsuPrice(modelid)
{
	new price;
	switch(modelid)
	{
		case 448, 461..463, 468, 521, 523, 586, 510: price = 10000;//motorcycle normal
		case 499, 609, 598, 524, 532, 578, 486, 406, 573, 455, 588, 403, 423, 414, 443, 515, 525: price = 13000;//truck
		case 429, 541, 415, 480, 562, 565, 434, 494, 502, 503, 411, 559, 561, 560, 506, 451, 558, 555, 477, 522: price = 30000;//sport vehicle
		case 581, 481, 509: price = 5000;//bicycle
		default: price = 10000;
	}
	return price;
}

CMD:insu(playerid, params[])
{
	if(isnull(params))
		return SendSyntaxMessage(playerid, "/insu [Names]"), SendClientMessage(playerid, COLOR_SERVER, "Names: {FFFFFF}buy, claim");

	if(!IsPlayerInRangeOfPoint(playerid, 5.0, -1939.4851,555.0747,35.1719))
		return SendErrorMessage(playerid, "You're not at Insurance Center!");

	if(!strcmp(params, "claim", true))
	{

		new query[172];
		mysql_format(sqlcon, query, sizeof(query), "SELECT `vehID`, `vehInsuTime`, `vehModel` FROM `vehicle` WHERE `vehExtraID`='%d' AND `vehType`='%d' AND `vehState`='%d';", PlayerData[playerid][pID], VEHICLE_TYPE_PLAYER, VEHICLE_STATE_INSURANCE);
		mysql_tquery(sqlcon, query, "OnViewVehClaim", "d", playerid);
	}
	else if(!strcmp(params, "buy", true))
	{
		new bool:found = false, str[512], count = 0;
		format(str, sizeof(str), "Model\tInsurance\tPrice\n");
		foreach(new i : Vehicle) if(IsValidVehicle(i) && Vehicle_IsOwner(playerid, i))
		{
			format(str, sizeof(str), "%s%s\t%d Left\t$%s\n", str, ReturnVehicleModelName(VehicleData[i][vModel]), VehicleData[i][vInsurance], FormatNumber(GetInsuPrice(VehicleData[i][vModel])));
			found = true;
			g_ListedVehicle[playerid][count++] = i;
		}
		if(found)
			ShowPlayerDialog(playerid, DIALOG_BUYINSU, DIALOG_STYLE_TABLIST_HEADERS, "Purchase Insurance", str, "Purchase", "Close");		
		else
			SendErrorMessage(playerid, "You don't have any vehicle.");
	}
	return 1;
}

function OnViewVehClaim(playerid) {
	new output[255];
	if(cache_num_rows())
	{
		strcat(output, sprintf("Vehicle Model\tClaim Time\n"));
		for(new i = 0; i != cache_num_rows(); i++)
		{
			new 
				id,
				time, model;

			cache_get_value_name_int(i, "vehInsuTime", time);
			cache_get_value_name_int(i, "vehID", id);	
			cache_get_value_name_int(i, "vehModel", model);

			g_Selected_Vehicle_ID[playerid][i] = id;
			g_Selected_Vehicle_Time[playerid][i] = time;
			g_Selected_Vehicle_Model[playerid][i] = model;

			strcat(output, sprintf(WHITE"%s\t%s\n", ReturnVehicleModelName(model), ConvertTimestamp(Timestamp:time)));
		}
		ShowPlayerDialog(playerid, DIALOG_CLAIMINSU, DIALOG_STYLE_TABLIST_HEADERS, "Insurance Center", output, "Claim", "Close");
	}
	else SendErrorMessage(playerid, "Tidak ada kendaraanmu dalam asuransi.");
	return 1;
}
CMD:forceinsurance(playerid, params[])
{
	new targetid;
	if(PlayerData[playerid][pAdmin] < 5)
 		return SendErrorMessage(playerid, NO_PERMISSION);
	    
	if(sscanf(params, "u", targetid))
	    return SendSyntaxMessage(playerid, "/forceinsurance [playerid/PartOfName]");
	    
	if(targetid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "Invalid player ID!");
	    
	PlayerData[playerid][pTarget] = targetid;

	new query[182];
	mysql_format(sqlcon, query, sizeof(query),"SELECT `vehID`, `vehInsuTime`, `vehModel` FROM `vehicle` WHERE `vehExtraID`='%d' AND `vehType`='%d' AND `vehState`='%d';", PlayerData[targetid][pID], VEHICLE_TYPE_PLAYER, VEHICLE_STATE_INSURANCE);
	mysql_tquery(sqlcon,query, "OnForceInsu", "dd", playerid, targetid);
	return 1;
}

function OnForceInsu(playerid, targetid) {
	if(cache_num_rows())
	{
		new output[355];

		strcat(output, sprintf("Vehicle Model\tClaim Time\n"));
		for(new i = 0; i != cache_num_rows(); i++)
		{
			new 
				id,
				time, model;

			cache_get_value_name_int(i, "vehInsuTime", time);
			cache_get_value_name_int(i, "vehID", id);	
			cache_get_value_name_int(i, "vehModel", model);

			g_Selected_Vehicle_ID[playerid][i] = id;
			g_Selected_Vehicle_Time[playerid][i] = time;
			g_Selected_Vehicle_Model[playerid][i] = model;

			strcat(output, sprintf(WHITE"%s\t%s\n", ReturnVehicleModelName(model), ConvertTimestamp(Timestamp:time)));
		}
		ShowPlayerDialog(playerid, DIALOG_FORCEINSURANCE, DIALOG_STYLE_TABLIST_HEADERS, "Insurance Center", output, "Claim", "Close");
	}
	else SendErrorMessage(playerid, "Tidak ada kendaraan %s dalam asuransi.", GetName(targetid));
	return 1;
}
