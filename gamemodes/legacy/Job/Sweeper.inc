#include <YSI_Coding\y_hooks>

new WarnSweeper[MAX_PLAYERS] = {0, ...};

IsSweeperVehicle(vehicleid)
{
	forex(i, sizeof(SweeperVehicle))
	{
		if(vehicleid == SweeperVehicle[i]) return 1;
	}
	return 0;	
}

new Float:SweeperPoint[][] =
{
	{-2079.4163,-95.2996,34.8891},
	{-2048.1409,-87.5633,34.8892},
	{-2035.1797,-73.2394,34.8970},
	{-2009.2290,-63.0337,34.8969},
	{-2008.9694,-9.0742,34.1987},
	{-2018.5808,32.0513,32.7070},
	{-2077.8962,33.4436,34.8970},
	{-2104.3479,41.9685,34.8892},
	{-2104.3135,95.5012,34.8892},
	{-2111.7122,113.2501,34.8969},
	{-2139.9861,112.3061,34.8970},
	{-2149.2532,125.0013,34.8970},
	{-2143.6411,185.8268,34.9141},
	{-2150.9436,210.8561,34.8970},
	{-2196.2761,211.0544,34.8970},
	{-2239.9480,211.2813,34.8970},
	{-2254.8518,196.7767,34.9049},
	{-2255.0955,140.1270,34.8970},
	{-2257.6738,56.8340,34.8970},
	{-2261.0110,-32.1519,34.8970},
	{-2261.2576,-65.7298,34.8970},
	{-2260.8926,-113.4255,34.9047},
	{-2261.3945,-171.8331,34.8970},
	{-2238.9749,-192.4964,34.8970},
	{-2187.7563,-189.9676,34.8970},
	{-2164.4856,-150.6740,34.8970},
	{-2165.2009,-83.6619,34.8969},
	{-2155.7134,-72.6013,34.8970},
	{-2121.9578,-73.1972,34.9029},
	{-2066.7024,-72.7499,34.8970}
};

SetSweeperPoint(playerid) {

	SweeperIndex[playerid]++;
	new vid = GetPlayerVehicleID(playerid);
	if(SweeperIndex[playerid] == sizeof(SweeperPoint)) {

		OnSweeping[playerid] = false;
		SweeperIndex[playerid] = 0;
		SetVehicleToRespawn(vid);
		VehicleData[vid][vFuel] = 10.0;
		GiveMoney(playerid, salarySweeper, "Salary Sweeper");
		SendClientMessageEx(playerid, COLOR_SERVER, "(Sidejob) {FFFFFF}Kamu berhasil menyelesaikan pekerjaan dan mendapatkan {00FF00}$%s", FormatNumber(salarySweeper));
		DisablePlayerCheckpoint(playerid);
		PlayerData[playerid][pSweeperDelay] = 900;
	}
	else SetPlayerCheckpoint(playerid, SweeperPoint[SweeperIndex[playerid]][0], SweeperPoint[SweeperIndex[playerid]][1], SweeperPoint[SweeperIndex[playerid]][2], 4.0);
	return 1;
}

hook OnPlayerConnect(playerid) {
	WarnSweeper[playerid] = 0;
}

hook OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if(!ispassenger && IsSweeperVehicle(vehicleid) && GetVehicleDriver(vehicleid) != INVALID_PLAYER_ID && OnSweeping[GetVehicleDriver(vehicleid)]) {
		SetPlayerCurrentPos(playerid);
		FreezePlayer(playerid, 2000);
		SendErrorMessage(playerid, "Dilarang melakukan car-jacking ke pengendara sweeper!");
	}
}

hook OnVehDmgStatusUpdate(vehicleid, playerid) {

	if (OnSweeping[playerid] && IsSweeperVehicle(GetPlayerVehicleID(playerid))) {

		SendClientMessage(playerid, COLOR_SERVER, "(Sidejob) {FFFFFF}Hati-hati kamu bisa gagal bekerja sebagai {FFFF00}Street Sweeper {FFFFFF}karena kendaraan lecet!");
		if (++WarnSweeper[playerid] >= 3) {

			SetVehicleToRespawn(vehicleid);
			VehicleData[vehicleid][vFuel] = GetVehicleFuelMax(GetVehicleModel(vehicleid));
			SendClientMessage(playerid, COLOR_SERVER, "(Sidejob) {FFFFFF}Kamu gagal bekerja sebagai {FFFF00}Street Sweeper {FFFFFF}karena kendaraan lecet!");
			OnSweeping[playerid] = false;
			WarnSweeper[playerid] = 0;
			SweeperIndex[playerid] = 0;
			DisablePlayerCheckpoint(playerid);
		}
	}
}

hook OnPlayerStateChange(playerid, newstate, oldstate) {

	if (oldstate == PLAYER_STATE_DRIVER) {

		new vehicleid = PlayerData[playerid][pLastVehicleID];
		if(OnSweeping[playerid] && IsSweeperVehicle(vehicleid))
		{
			SetVehicleToRespawn(vehicleid);
			VehicleData[vehicleid][vFuel] = GetVehicleFuelMax(GetVehicleModel(vehicleid));
			SendClientMessage(playerid, COLOR_SERVER, "(Sidejob) {FFFFFF}Kamu gagal bekerja sebagai {FFFF00}Street Sweeper {FFFFFF}karena mencoba keluar dari kendaraan!");
			OnSweeping[playerid] = false;
			WarnSweeper[playerid] = 0;
			SweeperIndex[playerid] = 0;
			DisablePlayerCheckpoint(playerid);
		}
	}	
	else if (newstate == PLAYER_STATE_DRIVER) {

	    new vehicleid = GetPlayerVehicleID(playerid);
		if(IsSweeperVehicle(vehicleid))
		{
			if(!OnSweeping[playerid])
			{	
				if(PlayerData[playerid][pMasked])
					return SendErrorMessage(playerid, "Buka maskermu terlebih dahulu!"), RemovePlayerFromVehicle(playerid);

				if(PlayerData[playerid][pSweeperDelay] > 0)
					return SendErrorMessage(playerid, "Kamu harus menunggu %d menit sebelum bekerja kembali!", PlayerData[playerid][pSweeperDelay]/60), RemovePlayerFromVehicle(playerid);

				if(IsHungerOrThirst(playerid)) {
					RemovePlayerFromVehicle(playerid);
					return SendErrorMessage(playerid, "Kamu terlalu lelah untuk bekerja.");
				}

				ShowPlayerDialog(playerid, DIALOG_SWEEPER, DIALOG_STYLE_MSGBOX, "{FFFFFF}Sweeper Sidejob", "{FFFFFF}Pekerjaan ini mengharuskan kamu untuk mengikuti semua petunjuk(Checkpoint)\nSelalu gunakan RP Drive & jangan abuse kendaraan jika tidak ingin\nDi beri punishment oleh {FF0000}Administrator","Start", "Cancel");
			}
		}		
	}
	return 1;
}