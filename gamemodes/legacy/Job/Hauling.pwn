#include <YSI_Coding\y_hooks>

new HaulingIndex[MAX_PLAYERS] = {0, ...},
    HaulingTrailer[MAX_PLAYERS] = {INVALID_VEHICLE_ID, ...},
    HaulingSelect[MAX_PLAYERS] = {-1, ...};

new Float:cp_Trailer_arr[][] = {
    {-1954.3209,-2448.8643,31.6436},
    {-508.0465,-53.9130,61.9896},
    {-1322.8235,2469.0925,87.9129},
    {-1313.1876,462.6803,8.2093}
};

new Float:cp_TrailerPos[][] = {
    {-1967.9357,-2435.2939,31.2513,228.0825},
    {-504.1354,-23.8634,58.1263,169.6636},
    {-1323.3628,2480.6775,87.5684,265.9292},
    {-1302.3353,454.4590,7.8231,87.4387}
};

new Float:cp_deliver_arr[][] = {
    {168.8105,-289.1317,1.5724},
    {-2268.7971,2391.6914,4.9567},
    {-1018.6514,-680.7415,32.0078},
    {388.3375,2537.9609,16.5391}
};

/*
new Float:cp_Trailer_arr[][] = 
{
    {-1965.6925,-2439.4729,30.6250},
    {-483.1145,-62.6066,60.5743},
    {-1273.1163,2496.2063,87.0322},
    {-1317.5649,473.3308,7.1875}
};
*/

forward OnPlayerSelectHauling(playerid, id);

#define                 MAX_HAULING_MISSION             4

enum E_HAULING_DATA {
    bool:haulingTaken,
    haulingPrice
};
new HaulingData[MAX_HAULING_MISSION][E_HAULING_DATA];

Hauling_Show(playerid) {

    new string[512];

    format(string, sizeof(string), "ID\tProduct\tSalary\tStatus\n");
    for(new i = 0; i < MAX_HAULING_MISSION; i++) {
        format(string, sizeof(string), "%s"WHITE"%d)\t%s\t"DARKGREEN"$%s\t%s\n", string, i + 1, Hauling_MissionName(i), FormatNumber(HaulingData[i][haulingPrice]), (HaulingData[i][haulingTaken]) ? (""RED"Taken") : (""YELLOW"Available"));
    }
    return ShowPlayerDialog(playerid, DIALOG_HAULING, DIALOG_STYLE_TABLIST_HEADERS, "Hauling Mission", string, "Select", "Close");
}

Hauling_Refresh(hauling_id) {

    HaulingData[hauling_id][haulingTaken] = false;
    HaulingData[hauling_id][haulingPrice] = RandomEx(15000, 40000);
}

Hauling_MissionName(id) {
    new str[56];
    switch(id) {
        case 0: str = "Angelpine Wood Company";
        case 1: str = "Lumberyard Wood Company";
        case 2: str = "Mining Company";
        case 3: str = "Aircraft Tools";
    }
    return str;
}

Hauling_SetTrailerCP(playerid) {

    new idx = HaulingSelect[playerid];

    SetPlayerRaceCheckpoint(playerid, 2, cp_Trailer_arr[idx][0], cp_Trailer_arr[idx][1], cp_Trailer_arr[idx][2], 0.0, 0.0, 0.0, 5.0);
    HaulingIndex[playerid] = 2;
    SendClientMessageEx(playerid, X11_LIGHTBLUE, "MISSION: "WHITE"Pergi ke Checkpoint untuk mengambil Trailer.", Hauling_MissionName(HaulingSelect[playerid]));
    return 1;
}

Hauling_ReturnTrailerCP(id, &Float:x, &Float:y, &Float:z) {
    x = cp_Trailer_arr[id][0];
    y = cp_Trailer_arr[id][1];
    z = cp_Trailer_arr[id][2];

    return 1;
}

Hauling_ReturnTrailerPos(id, &Float:x, &Float:y, &Float:z, &Float:a) {

    x = cp_TrailerPos[id][0];
    y = cp_TrailerPos[id][1];
    z = cp_TrailerPos[id][2];
    a = cp_TrailerPos[id][3];
}

Hauling_ReturnTrailerModel(id) {
    new modelid;
    switch(id) { 
        case 0: modelid = 450;
        case 1: modelid = 435;
        case 2: modelid = 450;
        case 3: modelid = 591;

    }
    return modelid;
}

Hauling_ReturnDeliverCP(id, &Float:x, &Float:y, &Float:z) {
    x = cp_deliver_arr[id][0];
    y = cp_deliver_arr[id][1];
    z = cp_deliver_arr[id][2];
}
timer AttachTrailer[1000](playerid) {
    AttachTrailerToVehicle(HaulingTrailer[playerid], GetPlayerVehicleID(playerid));
    
    return 1;
}
Hauling_AttachTrailer(playerid) {
    new id = HaulingSelect[playerid],
        Float:x, Float:y, Float:z, Float:a, modelid;

    modelid = Hauling_ReturnTrailerModel(id);

    Hauling_ReturnTrailerPos(id, x, y,z, a);

    HaulingTrailer[playerid] = Vehicle_Create(modelid, x, y, z, a, -1, -1, 0);
    if(HaulingTrailer[playerid] != INVALID_VEHICLE_ID) {
        Vehicle_SetType(HaulingTrailer[playerid], VEHICLE_TYPE_ADMIN);

        
        SendClientMessageEx(playerid, X11_LIGHTBLUE, "MISSION: "WHITE"Antarkan trailer %s ke Checkpoint yang ada di radar.", Hauling_MissionName(id));
        HaulingIndex[playerid] = 3;

        defer AttachTrailer[1000](playerid);

        Hauling_ReturnDeliverCP(id, x, y, z);

        SetPlayerRaceCheckpoint(playerid, 1, x, y, z, x, y, z, 5.0);
    }
    else SendErrorMessage(playerid, "Terjadi kesalahan ketika memunculkan trailer, lapor kepada developer.");
    return 1;
}
hook OnGameModeInit() {


    for(new i = 0; i < MAX_HAULING_MISSION; i++) {
        HaulingData[i][haulingTaken] = false;
        HaulingData[i][haulingPrice] = RandomEx(15000, 40000);
    }
}

hook OnPlayerConnect(playerid) {
    HaulingIndex[playerid] = 0;
    HaulingTrailer[playerid] = INVALID_VEHICLE_ID;
    HaulingSelect[playerid] = -1;
}

hook OnPlayerDisconnectEx(playerid) {
    if(HaulingIndex[playerid] != 0) {
        if(IsValidVehicle(HaulingTrailer[playerid]))
            Vehicle_Delete(HaulingTrailer[playerid], false);

        HaulingData[HaulingSelect[playerid]][haulingTaken] = false;
        Hauling_Refresh(HaulingSelect[playerid]);
    }
}

hook OnPlayerEnterRaceCP(playerid) {

    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 403 || GetVehicleModel(GetPlayerVehicleID(playerid)) == 514 || GetVehicleModel(GetPlayerVehicleID(playerid)) == 515) {
        if(HaulingIndex[playerid] == 2) {
        
            new Float:x, Float:y, Float:z;
            Hauling_ReturnTrailerCP(HaulingSelect[playerid], x, y, z);
            if(IsPlayerInRangeOfPoint(playerid, 5.0, x, y, z)) {
                DisablePlayerRaceCheckpoint(playerid);

                Hauling_AttachTrailer(playerid);
            }
        }
        else if(HaulingIndex[playerid] == 3) {
            if(GetVehicleTrailer(GetPlayerVehicleID(playerid)) == HaulingTrailer[playerid]) {
                
                if(IsValidVehicle(HaulingTrailer[playerid]))
                    Vehicle_Delete(HaulingTrailer[playerid], false);

                new id = HaulingSelect[playerid], bonus = RandomEx(3000, 10000);

                AddSalary(playerid, "Hauling Mission", HaulingData[id][haulingPrice]);
                GiveMoney(playerid, bonus, "Bonus Hauling");

                SendClientMessageEx(playerid, X11_LIGHTBLUE, "MISSION: "WHITE"Kamu berhasil mengantarkan produk %s dan mendapatkan "GREEN"$%s", Hauling_MissionName(id), FormatNumber(HaulingData[id][haulingPrice]));
                SendClientMessageEx(playerid, X11_LIGHTBLUE, "MISSION: "WHITE"Kamu juga mendapatkan bonus "GREEN"$%s "WHITE"dimasukkan pada dompetmu.", FormatNumber(bonus));

                Hauling_Refresh(id);

                HaulingSelect[playerid] = -1;
                HaulingIndex[playerid] = 0;

                DisablePlayerRaceCheckpoint(playerid);

                PlayerData[playerid][pHaulingDelay] = 3000;
            }
        }
    }
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {
    if(dialogid == DIALOG_HAULING) {
        if(response) {
            static idx;
            
            idx = listitem;

            if(HaulingData[idx][haulingTaken])
                return SendErrorMessage(playerid, "Misi ini tidak tersedia untuk sekarang.");

            HaulingData[idx][haulingTaken] = true;
            HaulingSelect[playerid] = idx;
            HaulingIndex[playerid] = 1;
            Hauling_SetTrailerCP(playerid);
        }
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}
CMD:missions(playerid, params[]) {
    if(!CheckPlayerJob(playerid, JOB_TRUCKER))
        return SendErrorMessage(playerid, "Kamu bukan seorang trucker.");

    if(!PlayerData[playerid][pLicense][3])
        return SendErrorMessage(playerid, "Kamu tidak memiliki lisensi hauling.");

    if(PlayerData[playerid][pHaulingDelay])
        return SendErrorMessage(playerid, "Tunggu %d menit untuk misi hauling kembali.", PlayerData[playerid][pHaulingDelay]/60);
        
    if(HaulingSelect[playerid] != -1)
        return SendErrorMessage(playerid, "Kamu sedang mengerjakan misi hauling.");

    if(IsHungerOrThirst(playerid))
        return SendErrorMessage(playerid, "Kamu terlalu lelah untuk bekerja.");

    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 403 || GetVehicleModel(GetPlayerVehicleID(playerid)) == 514 || GetVehicleModel(GetPlayerVehicleID(playerid)) == 515) {

        Hauling_Show(playerid);
    }
    else SendErrorMessage(playerid, "Kamu tidak berada didalam kendaraan hauling.");

    return 1;
}