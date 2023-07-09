#include <YSI_Coding\y_hooks>

#define IsPlayerWorkInBus(%0)		busWorking[%0]
#define SetPlayerWorkInBus(%0)		busWorking[%0]=true
#define StopPlayerWorkInBus(%0)		busWorking[%0]=false
#define BUS_WAIT_TIME               11

new
	bool:busWorking[MAX_PLAYERS] = {false, ...},
	busRoute[MAX_PLAYERS] = {0, ...},
	busCounter[MAX_PLAYERS] = {0, ...},
	currentBRoute[MAX_PLAYERS] = {0, ...},
	busSelect[MAX_PLAYERS] = {0, ...};

enum array_busRoute
{
	Float:b_x,
	Float:b_y,
	Float:b_z,
	b_time
};

stock const arr_busRoute2[][array_busRoute] = 
{
	{-2493.0969,1205.6937,37.5687, 1},
	{-2465.1934,1202.5853,35.2232, 1},
	{-2374.6880,1171.4390,40.1752, 1},
	{-2270.1462,1171.9271,55.8418, 1},
	{-2185.1318,1170.9242,55.7114, BUS_WAIT_TIME},
	{-2115.9705,1171.6208,55.4400, 1},
	{-2000.3407,1172.7792,45.4284, 1},
	{-1910.3883,1173.1915,45.4301, 1},
	{-1887.6951,1121.4043,45.4310, 1},
	{-1889.1847,1034.0194,44.0851, 1},
	{-1901.8806,954.2606,35.1519, 1},
	{-1904.6952,868.1244,35.1500, BUS_WAIT_TIME},
	{-1904.0762,778.2046,42.1248, 1},
	{-1904.0800,710.1663,45.4272, 1},
	{-1902.6516,624.5620,35.1361, 1},
	{-1868.8833,600.6541,35.1453, 1},
	{-1813.6892,600.1019,35.1411, BUS_WAIT_TIME},
	{-1760.4617,600.7271,27.1051, 1},
	{-1709.3553,658.1788,24.8682, 1},
	{-1708.4792,752.4242,24.8682, 1},
	{-1708.3351,822.7542,24.8677, 1},
	{-1708.6582,901.0592,24.8756, BUS_WAIT_TIME},
	{-1691.6158,916.8223,24.8755, 1},
	{-1648.0221,915.9064,19.6018, 1},
	{-1578.4419,914.4130,7.5997, 1},
	{-1527.3176,920.7675,7.1745, 1},
	{-1546.4274,985.8467,7.1753, 1},
	{-1579.8539,1082.3457,7.1722, 1},
	{-1599.2021,1214.5353,7.1802, 1},
	{-1656.2833,1276.8704,7.1742, BUS_WAIT_TIME},
	{-1705.9993,1325.8055,7.1784, 1},
	{-1818.7672,1383.4622,7.1784, 1},
	{-1902.1912,1333.0243,7.1738, 1},
	{-1996.0337,1312.1827,7.1725, 1},
	{-2055.9734,1314.3273,7.2679, 1},
	{-2123.9617,1337.7192,7.1806, BUS_WAIT_TIME},
	{-2209.6116,1336.0403,7.1724, 1},
	{-2312.6963,1362.4697,7.1723, 1},
	{-2406.1306,1379.9022,7.1761, 1},
	{-2456.2229,1362.2827,7.1719, 1},
	{-2458.0994,1301.1880,18.8369, 1},
	{-2458.0669,1227.8545,35.2028, 1}
};
stock const arr_busRoute[][array_busRoute] = 
{
	{-2495.3174,-618.0724,132.6652, 1}, // BUS START 
	{-2425.8555,-600.4403,132.5534, 1},
	{-2489.7603,-477.2790,96.7570, 1},
	{-2606.2676,-496.5646,73.0760, 1},
	{-2572.3364,-470.8302,68.2287, 1},
	{-2412.1599,-420.7068,85.1571, 1},
	{-2319.2644,-438.3484,79.6811, 1},
	{-2469.6067,-365.2186,66.8749, 1},
	{-2674.6912,-415.1922,32.2461, 1},
	{-2684.7021,-521.6697,16.6752, 1},
	{-2778.5869,-489.4317,7.2912, 1},
	{-2819.5525,-424.3371,7.1391, BUS_WAIT_TIME},
	{-2813.5835,-339.2420,7.1370, 1},
	{-2800.8013,-212.6677,7.1350, 1},
	{-2695.9995,-212.2656,4.2799, 1},
	{-2581.8105,-212.8384,5.3832, 1},
	{-2477.4790,-212.8295,29.1301, 1},
	{-2418.3984,-125.7228,35.2764, BUS_WAIT_TIME},
	{-2415.4614,-72.2354,35.3328, 1},
	{-2300.6995,-72.6971,35.2651, 1},
	{-2260.2378,-80.0457,35.2828, 1},
	{-2260.9436,-190.6208,35.2725, 1},
	{-2259.6064,-352.8658,50.9679, 1},
	{-2155.9097,-499.6466,41.4387, 1},
	{-2041.3738,-582.6265,28.3405, 1},
	{-1923.0901,-584.6866,24.5462, 1},
	{-1766.1971,-584.7265,16.4401, 1},
	{-1651.4172,-548.4160,11.4586, 1},
	{-1490.8353,-490.5949,14.0979, 1},
	{-1411.6761,-450.1790,14.1004, 1},
	{-1399.5204,-328.4450,14.0960, BUS_WAIT_TIME},
	{-1446.2764,-283.2455,14.0988, BUS_WAIT_TIME},
	{-1498.0927,-271.0721,14.0990, 1},
	{-1594.8668,-335.0157,14.1012, 1},
	{-1621.8987,-428.8995,13.9284, 1},
	{-1674.2947,-555.0622,11.6736, 1},
	{-1801.7444,-575.6653,16.1961, 1},
	{-1953.2938,-575.7706,24.5460, 1},
	{-2087.6013,-551.7770,31.7777, 1},
	{-2179.8269,-463.8686,48.4447, 1},
	{-2198.5061,-487.5386,48.1490, 1},
	{-2218.2244,-593.7000,54.0590, 1},
	{-2264.2908,-657.9260,69.3433, 1},
	{-2229.6226,-726.7208,65.1793, 1},
	{-2251.3335,-749.2892,72.0525, 1},
	{-2309.2151,-776.0093,90.1131, 1},
	{-2351.2388,-766.0828,96.5238, 1},
	{-2344.5229,-680.4827,115.4866, 1},
	{-2410.7642,-619.2969,132.6090, 1},
	{-2472.2148,-615.1833,132.6516, 1},
	{-2500.9663,-607.3792,132.6710, 1}
  
};

IsBus2Vehicle(vehicleid)
{
	forex(i, sizeof(Bus2Vehicle))
	{
		if(vehicleid == Bus2Vehicle[i]) return 1;
	}
	return 0;
}


IsBusVehicle(vehicleid)
{
	forex(i, sizeof(BusVehicle))
	{
		if(vehicleid == BusVehicle[i]) return 1;
	}
	return 0;
}

hook OnPlayerConnect(playerid)
{
	StopPlayerWorkInBus(playerid);
	busRoute[playerid] = 0;
	busCounter[playerid] = 0;
	currentBRoute[playerid] = 0;
    PlayerData[playerid][pLastVehicleID] = INVALID_VEHICLE_ID;
	busSelect[playerid] = 0;
}

hook OnPlayerDisconnectEx(playerid, reason)
{
	if(IsPlayerWorkInBus(playerid) && (IsBusVehicle(GetPlayerVehicleID(playerid)) || IsBus2Vehicle(GetPlayerVehicleID(playerid))))
	{
		DisablePlayerRaceCheckpoint(playerid);

		SetVehicleToRespawn(GetPlayerVehicleID(playerid));

		PlayerData[playerid][pLastVehicleID] = INVALID_VEHICLE_ID;

	}
}

hook OnPlayerEnterVehicle(playerid, vehicleid, ispassenger) {

	if(!ispassenger && (IsBusVehicle(vehicleid) || IsBus2Vehicle(vehicleid)) && GetVehicleDriver(vehicleid) != INVALID_PLAYER_ID && IsPlayerWorkInBus(GetVehicleDriver(vehicleid))) {
		SetPlayerCurrentPos(playerid);
		FreezePlayer(playerid, 2000);
		SendErrorMessage(playerid, "Dilarang melakukan car-jacking ke pengendara bus!");
	}
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(newstate == PLAYER_STATE_DRIVER && (IsBusVehicle(GetPlayerVehicleID(playerid)) || IsBus2Vehicle(GetPlayerVehicleID(playerid))))
    {
		if(IsHungerOrThirst(playerid))
			return SendErrorMessage(playerid, "Kamu terlalu lelah untuk bekerja.");

        EnteringBusVehicle(playerid);
    }
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerEnterRaceCP(playerid)
{
	if(IsPlayerConnected(playerid) && IsPlayerWorkInBus(playerid) && busCounter[playerid] == 1 && (IsBusVehicle(GetPlayerVehicleID(playerid)) || IsBus2Vehicle(GetPlayerVehicleID(playerid))))
	{
		SetBusCheckpointRoute(playerid);
	}
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerLeaveRaceCP(playerid)
{
	if(IsPlayerConnected(playerid) && IsPlayerWorkInBus(playerid))
	{
		switch(busSelect[playerid]) {
			case 1: busCounter[playerid] = arr_busRoute[currentBRoute[playerid]][b_time];
			case 2: busCounter[playerid] = arr_busRoute2[currentBRoute[playerid]][b_time];
		}
	}
}

ptask Player_BusUpdate[1000](playerid)
{
    if(!IsPlayerConnected(playerid))
        return 0;

	if(IsPlayerWorkInBus(playerid) && (IsBusVehicle(GetPlayerVehicleID(playerid)) || IsBus2Vehicle(GetPlayerVehicleID(playerid))))
	{
		if(IsPlayerInRaceCheckpoint(playerid))
		{
			if(--busCounter[playerid] <= 0)
			{
				SetBusCheckpointRoute(playerid);
				return 1;
			}

			GameTextForPlayer(playerid, sprintf("WAITING TIME~n~%02d", busCounter[playerid]), 1000, 6);
			PlayerPlaySound(playerid, 43000, 0.0, 0.0, 0.0);
		}
	}

	if(PlayerData[playerid][pBusDelay])
	{
		if(--PlayerData[playerid][pBusDelay] == 0) {
			PlayerData[playerid][pBusDelay] = 0;

			SendClientMessage(playerid, COLOR_SERVER, "(Sidejob) {FFFFFF}Kamu bisa bekerja sebagai Bus Driver kembali.");
		}
	}
	return 1;
}

EnteringBusVehicle(playerid)
{

    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
        return 0;

	if(PlayerData[playerid][pMasked])
		return SendErrorMessage(playerid, "Buka maskermu terlebih dahulu!"), RemovePlayerFromVehicle(playerid);

    if(PlayerData[playerid][pBusDelay] > 0)
        return RemovePlayerFromVehicle(playerid), SendServerMessage(playerid, "Kamu harus menunggu %d menit untuk bekerja kembali.", PlayerData[playerid][pBusDelay]/60);

    SetCameraBehindPlayer(playerid);
    ShowPlayerDialog(playerid, DIALOG_BUS, DIALOG_STYLE_MSGBOX, "{FFFFFF}Bus Sidejob", "{FFFFFF}Pekerjaan ini mengharuskan kamu untuk mengikuti semua petunjuk(Checkpoint)\n{FFFFFF}Pada radar hingga selesai, Gunakan Roleplay Driving saat sedang berkendara Bus\n{FFFFFF}Saat sudah selesai kamu akan mendapatkan Salary\nNamun jika tidak selesai, kamu tidak akan mendapat apa-apa.\n\n{FFFFFF}HINT: Jangan turun dari bus saat berkerja, atau kamu akan gagal!", "Start", "Cancel");
    return 1;
}

SetBusCheckpoint(playerid, mode)
{
	if(IsPlayerWorkInBus(playerid))
	{
		switch(busSelect[playerid]) {
			case 1: {
				SetPlayerRaceCheckpoint(playerid, mode, arr_busRoute[currentBRoute[playerid]][b_x], arr_busRoute[currentBRoute[playerid]][b_y], arr_busRoute[currentBRoute[playerid]][b_z], mode ? (-1.0) : (arr_busRoute[currentBRoute[playerid] + 1][b_x]), mode ? (-1.0) : (arr_busRoute[currentBRoute[playerid] + 1][b_y]), mode ? (-1.0) : (arr_busRoute[currentBRoute[playerid] + 1][b_z]), 4);
				busCounter[playerid] = arr_busRoute[currentBRoute[playerid]][b_time];
			}
			case 2: {
				SetPlayerRaceCheckpoint(playerid, mode, arr_busRoute2[currentBRoute[playerid]][b_x], arr_busRoute2[currentBRoute[playerid]][b_y], arr_busRoute2[currentBRoute[playerid]][b_z], mode ? (-1.0) : (arr_busRoute2[currentBRoute[playerid] + 1][b_x]), mode ? (-1.0) : (arr_busRoute2[currentBRoute[playerid] + 1][b_y]), mode ? (-1.0) : (arr_busRoute2[currentBRoute[playerid] + 1][b_z]), 4);
				busCounter[playerid] = arr_busRoute2[currentBRoute[playerid]][b_time];
			}
		}
	}
	return 1;
}

RespawnPlayerBusVehicle(playerid)
{
	currentBRoute[playerid] = 0;

    VehicleData[PlayerData[playerid][pLastVehicleID]][vFuel] = 100;

	if((IsBusVehicle(PlayerData[playerid][pLastVehicleID]) || IsBus2Vehicle(PlayerData[playerid][pLastVehicleID])) && GetVehicleDriver(PlayerData[playerid][pLastVehicleID]) == INVALID_PLAYER_ID)
		SetVehicleToRespawn(PlayerData[playerid][pLastVehicleID]);
		
    RepairVehicle(PlayerData[playerid][pLastVehicleID]);

    DisablePlayerRaceCheckpoint(playerid);
    StopPlayerWorkInBus(playerid);
    PlayerData[playerid][pLastVehicleID] = INVALID_VEHICLE_ID;
    return 1;
}

SetBusCheckpointRoute(playerid)
{
	currentBRoute[playerid] ++;

	if((busSelect[playerid] == 1 && currentBRoute[playerid] == sizeof(arr_busRoute)) ||	(busSelect[playerid] == 2 && currentBRoute[playerid] == sizeof(arr_busRoute2)))
	{
		new
			vehicleid = GetPlayerVehicleID(playerid);
			
		PlayerData[playerid][pBusDelay] = 900;
		AddSalary(playerid, "Bus SideJob", salaryBus);
		SendClientMessageEx(playerid, COLOR_SERVER, "(Sidejob) {FFFFFF}Kamu berhasil menyelesaikan pekerjaan dan mendapatkan {00FF00}$%s {FFFFFF}pada pending salary.", FormatNumber(salaryBus));
		
		VehicleData[vehicleid][vFuel] = 100;
		SetVehicleToRespawn(vehicleid);
		RepairVehicle(vehicleid);
		DisablePlayerRaceCheckpoint(playerid);
		StopPlayerWorkInBus(playerid);
	}
	else if((busSelect[playerid] == 1 && currentBRoute[playerid] == sizeof(arr_busRoute) - 1) || (busSelect[playerid] == 2 && currentBRoute[playerid] == sizeof(arr_busRoute2) - 1))
	{
		SetBusCheckpoint(playerid, 1);
	}
	else SetBusCheckpoint(playerid, 0);
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {

	if(dialogid == DIALOG_BUS) {

		if(!response)
			return RemovePlayerFromVehicle(playerid);

		new vehicleid = GetPlayerVehicleID(playerid);
		if(!IsBusVehicle(vehicleid) && !IsBus2Vehicle(vehicleid))
			return SendErrorMessage(playerid, "Kamu harus didalam kendaraan Bus!");

		if(PlayerData[playerid][pMasked])
			return SendErrorMessage(playerid, "Buka maskermu terlebih dahulu!"), RemovePlayerFromVehicle(playerid);

		if(PlayerData[playerid][pBusDelay] > 0)
			return RemovePlayerFromVehicle(playerid), SendServerMessage(playerid, "Kamu harus menunggu %d menit untuk bekerja kembali.", PlayerData[playerid][pBusDelay]/60);

		if(IsBusVehicle(vehicleid))
			busSelect[playerid] = 1;
		else 
			busSelect[playerid] = 2;

		busCounter[playerid] = 0;
		currentBRoute[playerid] = 0;

		SendClientMessage(playerid, COLOR_SERVER, "(Sidejob) {FFFFFF}Kamu mulai bekerja sebagai Bus Driver, silahkan ikuti semua Checkpoint pada radar.");
		SetPlayerWorkInBus(playerid);

		SetBusCheckpoint(playerid, 0);
		PlayerData[playerid][pLastVehicleID] = vehicleid;
		OnBus[playerid] = true;

		SwitchVehicleEngine(vehicleid,true);
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}