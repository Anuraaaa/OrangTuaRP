#include <YSI_Coding\y_hooks>

new
    bool:OnMower[MAX_PLAYERS] = {false, ...},
    MowerIndex[MAX_PLAYERS] = {0, ...},
    MowerWarn[MAX_PLAYERS] = {0, ...};


enum E_MOWER_CP {
    Float:mowerX,
    Float:mowerY,
    Float:mowerZ
};

stock const arr_MowerCP[][E_MOWER_CP] = 
{
    {-2297.6345,168.7445,34.8924},
    {-2313.9292,161.4223,34.8925},
    {-2330.3623,167.1888,34.8924},
    {-2346.0918,183.3402,34.8925},
    {-2353.8499,204.9607,34.8925},
    {-2347.7356,212.4322,34.8924},
    {-2321.4885,213.2702,34.8925},
    {-2304.4072,209.5732,34.8925},
    {-2300.9790,191.4325,34.8925},
    {-2299.6152,137.9250,34.8906},
    {-2300.9714,107.0035,34.8905},
    {-2307.2310,87.2408,34.8923},
    {-2339.3472,86.6720,34.8925},
    {-2350.9429,102.3985,34.8925},
    {-2339.8496,122.0143,34.8925},
    {-2313.6958,136.5158,34.8924},
    {-2310.3923,147.8261,34.8847}
};

IsMowerVehicle(vehicleid)
{
	forex(i, sizeof(MowerVehicle))
	{
		if(vehicleid == MowerVehicle[i]) return 1;
	}
	return 0;
}

hook OnPlayerConnect(playerid) {
    OnMower[playerid] = false;
    MowerIndex[playerid] = 0;
    MowerWarn[playerid] = 0;
}

hook OnPlayerDisconnectEx(playerid) {

    if(OnMower[playerid] && IsMowerVehicle(GetPlayerVehicleID(playerid))) {
        VehicleData[GetPlayerVehicleID(playerid)][vFuel] = 10.0;
        SetVehicleToRespawn(GetPlayerVehicleID(playerid));
        OnMower[playerid] = false;
        MowerWarn[playerid] = 0;
    }
}

hook OnPlayerEnterCheckpoint(playerid) {
    if(IsPlayerConnected(playerid) && OnMower[playerid] && IsMowerVehicle(GetPlayerVehicleID(playerid))) {
        SetMowerCheckpoint(playerid);
    }
}

hook OnVehDmgStatusUpdate(vehicleid, playerid) {

    if (OnMower[playerid] && IsMowerVehicle(GetPlayerVehicleID(playerid))) {

        SendClientMessage(playerid, COLOR_SERVER, "(Sidejob) {FFFFFF}Hati-hati kamu bisa gagal bekerja sebagai {FFFF00}Mower {FFFFFF}karena kendaraan lecet!");
        if (++MowerWarn[playerid] >= 3) {

            SetVehicleToRespawn(vehicleid);
            VehicleData[vehicleid][vFuel] = GetVehicleFuelMax(GetVehicleModel(vehicleid));
            SendClientMessage(playerid, COLOR_SERVER, "(Sidejob) {FFFFFF}Kamu gagal bekerja sebagai {FFFF00}Mower {FFFFFF}karena kendaraan lecet!");
            OnMower[playerid] = false;
            MowerIndex[playerid] = 0;
            MowerWarn[playerid] = 0;
            DisablePlayerCheckpoint(playerid);
        }            
    }
}

hook OnPlayerStateChange(playerid, newstate, oldstate) {

    if (oldstate == PLAYER_STATE_DRIVER) {

		new vehicleid = PlayerData[playerid][pLastVehicleID];
		if(OnMower[playerid] && IsMowerVehicle(vehicleid))
		{
			SetVehicleToRespawn(vehicleid);
			VehicleData[vehicleid][vFuel] = GetVehicleFuelMax(GetVehicleModel(vehicleid));
			SendClientMessage(playerid, COLOR_SERVER, "(Sidejob) {FFFFFF}Kamu gagal bekerja sebagai {FFFF00}Mower {FFFFFF}karena mencoba keluar dari kendaraan!");
			OnMower[playerid] = false;
			MowerIndex[playerid] = 0;
            MowerWarn[playerid] = 0;
			DisablePlayerCheckpoint(playerid);
		}
    }
    else if (newstate == PLAYER_STATE_DRIVER) {

	    new vehicleid = GetPlayerVehicleID(playerid);
		if(IsMowerVehicle(vehicleid))
		{
			if(!OnMower[playerid])
			{	

				if(PlayerData[playerid][pMasked])
					return SendErrorMessage(playerid, "Buka maskermu terlebih dahulu!"), RemovePlayerFromVehicle(playerid);

				if(PlayerData[playerid][pMowerDelay] > 0)
					return SendErrorMessage(playerid, "Kamu harus menunggu %d menit sebelum bekerja kembali!", PlayerData[playerid][pMowerDelay]/60), RemovePlayerFromVehicle(playerid);


				if(IsHungerOrThirst(playerid)) {
					RemovePlayerFromVehicle(playerid);
					return SendErrorMessage(playerid, "Kamu terlalu lelah untuk bekerja.");
				}

				ShowPlayerDialog(playerid, DIALOG_MOWER, DIALOG_STYLE_MSGBOX, "{FFFFFF}Mower Sidejob", "{FFFFFF}Pekerjaan ini mengharuskan kamu untuk mengikuti semua petunjuk(Checkpoint)\nSelalu gunakan RP Drive & jangan abuse kendaraan jika tidak ingin\nDi beri punishment oleh {FF0000}Administrator","Start", "Cancel");
			}
		}		
    }
    return 1;
}

SetMowerCheckpoint(playerid) {

	MowerIndex[playerid]++;
	new vid = GetPlayerVehicleID(playerid);
	if(MowerIndex[playerid] == sizeof(arr_MowerCP)) {

		OnMower[playerid] = false;
		MowerIndex[playerid] = 0;
        MowerWarn[playerid] = 0;
		SetVehicleToRespawn(vid);
		VehicleData[vid][vFuel] = 10.0;
		GiveMoney(playerid, salaryMower, "Mower");
		SendClientMessageEx(playerid, COLOR_SERVER, "(Sidejob) {FFFFFF}Kamu berhasil menyelesaikan pekerjaan dan mendapatkan {00FF00}$%s", FormatNumber(salaryMower));
		DisablePlayerCheckpoint(playerid);
		PlayerData[playerid][pMowerDelay] = 900;
	}
	else SetPlayerCheckpoint(playerid, arr_MowerCP[MowerIndex[playerid]][mowerX], arr_MowerCP[MowerIndex[playerid]][mowerY], arr_MowerCP[MowerIndex[playerid]][mowerZ], 4.0);
	return 1;
}
