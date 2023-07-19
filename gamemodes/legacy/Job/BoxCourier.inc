#include <YSI_Coding\y_hooks>

#define MAX_DELIVERED_BOX 5

enum {
    COURIER_STATE_NOT_STARTED = 0,
    COURIER_STATE_DELIVERING,
    COURIER_STATE_ONFINISH
}

new bool:g_CarryBox[MAX_PLAYERS] = {false, ...},
    g_CourierState[MAX_PLAYERS] = {COURIER_STATE_NOT_STARTED, ...},
    STREAMER_TAG_MAP_ICON:CourierIcons[MAX_PLAYERS],
    g_CurrentHouse[MAX_PLAYERS] = {-1, ...},
    found_house[MAX_PLAYERS][MAX_DELIVERED_BOX],
    STREAMER_TAG_CP:CourierVehicleCP[MAX_PLAYERS],
    g_TotalSalary[MAX_PLAYERS],
    g_CurrentHouseIdx[MAX_PLAYERS],
    g_CourierVehicleID[MAX_PLAYERS];

hook OnPlayerConnect(playerid) {
    g_CarryBox[playerid] = false;
    g_CourierState[playerid] = COURIER_STATE_NOT_STARTED;
    g_CurrentHouse[playerid] = -1;
    CourierVehicleCP[playerid] = STREAMER_TAG_CP:INVALID_STREAMER_ID;
    g_CourierVehicleID[playerid] = INVALID_VEHICLE_ID;
}

hook OnPlayerStateChange(playerid, newstate, oldstate) {
    if(newstate == PLAYER_STATE_DRIVER && IsCourierVehicle(GetPlayerVehicleID(playerid))) {

        if(PlayerData[playerid][pCourierDelay]) {
            RemovePlayerFromVehicle(playerid);
            SendErrorMessage(playerid, "Kamu harus bekerja %d menit untuk kembali bekerja sebagai Box Courier!", PlayerData[playerid][pCourierDelay]/60);
            return 1;
        }

        if(g_CourierState[playerid] == COURIER_STATE_NOT_STARTED) {

            if(Iter_Count(House) < 5)
                return SendErrorMessage(playerid, "Rumah yang ada di server kurang dari 5, minta staff untuk membuat rumah.");

            ShowPlayerDialog(playerid, DIALOG_BOXCOURIER, DIALOG_STYLE_MSGBOX, "Box Courier", ""WHITE"Apakah kamu ingin memulai pekerjaan sebagai Box Courier? klik \"Start\" untuk mulai", "Start", "Close");
        }
        else if(g_CourierState[playerid] == COURIER_STATE_DELIVERING) {
            if(IsValidDynamicCP(CourierVehicleCP[playerid]))
                DestroyDynamicCP(CourierVehicleCP[playerid]);       
        }
    }
    if(oldstate == PLAYER_STATE_DRIVER && newstate == PLAYER_STATE_ONFOOT && IsCourierVehicle(g_CourierVehicleID[playerid]) && g_CourierState[playerid] == COURIER_STATE_DELIVERING) {

        new vehicleid = g_CourierVehicleID[playerid];

        if(IsValidDynamicCP(CourierVehicleCP[playerid]))
            DestroyDynamicCP(CourierVehicleCP[playerid]);

        new Float:x, Float:y, Float:z;
        GetVehicleBoot(vehicleid, x, y, z);

        CourierVehicleCP[playerid] = CreateDynamicCP(x, y, z, 1.2, .playerid = playerid);
        SendClientMessage(playerid, X11_LIGHTBLUE, "(Box Courier) "WHITE"Pergi ke belakang kendaraan ini untuk mengambil box.");

    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerEnterDynamicCP(playerid, STREAMER_TAG_CP:checkpointid) {
    if(checkpointid == CourierVehicleCP[playerid] && g_CourierState[playerid] == COURIER_STATE_DELIVERING) {
        if(IsValidDynamicCP(CourierVehicleCP[playerid]))
            DestroyDynamicCP(CourierVehicleCP[playerid]);

        new vehicleid = g_CourierVehicleID[playerid];

        new Float:x, Float:y, Float:z;
        GetVehicleBoot(vehicleid, x, y, z);

        SetPlayerFace(playerid,  x, y);

        TogglePlayerControllable(playerid, false);
        SetCameraBehindPlayer(playerid);
        ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 1, 1, 1, 0, 1);
        StartPlayerLoadingBar(playerid, 50, "Grabbing_box...", 50, "OnTakingBox");
    }
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {
    if(dialogid == DIALOG_BOXCOURIER) {
        if(response) {
            if(PlayerData[playerid][pMasked])
                return SendErrorMessage(playerid, "Buka maskermu terlebih dahulu!"), RemovePlayerFromVehicle(playerid);

            g_CourierState[playerid] = COURIER_STATE_DELIVERING;
            SwitchVehicleEngine(GetPlayerVehicleID(playerid), true);

            StartPlayerBoxCourier(playerid);
            g_CourierVehicleID[playerid] = GetPlayerVehicleID(playerid);
        }
        else {
            RemovePlayerFromVehicle(playerid);
        }
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerEnterVehicle(playerid, vehicleid, ispassenger) {
	if(g_CourierState[playerid] != COURIER_STATE_NOT_STARTED && vehicleid != g_CourierVehicleID[playerid]) {
		SetPlayerCurrentPos(playerid);
		SendErrorMessage(playerid, "Tidak bisa menaiki kendaraan lain saat bekerja Box Courier.");
	}
    return Y_HOOKS_CONTINUE_RETURN_1;
}
hook OnPlayerEnterCheckpoint(playerid) {
    if(IsPlayerInRangeOfPoint(playerid,  5.0, -1945.0291,-1085.2745,30.7779) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER && IsCourierVehicle(GetPlayerVehicleID(playerid))  && g_CourierState[playerid] == COURIER_STATE_ONFINISH) {
        AddSalary(playerid, "Box Courier", g_TotalSalary[playerid]);
        SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Box Courier) "WHITE"Kamu telah menyelesaikan pekerjaan! "GREEN"$%s "WHITE"dimasukkan pada pending salary.",  FormatNumber(g_TotalSalary[playerid]));
        g_TotalSalary[playerid] = 0;
        g_CarryBox[playerid] =  false;
        g_CourierState[playerid] = COURIER_STATE_NOT_STARTED;
        SetVehicleToRespawn(g_CourierVehicleID[playerid]);
        VehicleData[g_CourierVehicleID[playerid]][vFuel] = 100;
        DisablePlayerCheckpoint(playerid);

        PlayerData[playerid][pCourierDelay] = 1800;

        if(IsValidDynamicMapIcon(CourierIcons[playerid]))
            DestroyDynamicMapIcon(CourierIcons[playerid]);

    }
}

hook OnPlayerDisconnectEx(playerid) {
    if(g_CourierState[playerid] != COURIER_STATE_NOT_STARTED) {
        g_TotalSalary[playerid] = 0;
        g_CarryBox[playerid] =  false;
        g_CourierState[playerid] = COURIER_STATE_NOT_STARTED;
        SetVehicleToRespawn(g_CourierVehicleID[playerid]);
        VehicleData[g_CourierVehicleID[playerid]][vFuel] = 100;
        DisablePlayerCheckpoint(playerid);

        PlayerData[playerid][pCourierDelay] = 1800;


        if(IsValidDynamicMapIcon(CourierIcons[playerid]))
            DestroyDynamicMapIcon(CourierIcons[playerid]);
    }
}
function OnTakingBox(playerid) {

    TogglePlayerControllable(playerid,  true);
    SendClientMessage(playerid, X11_LIGHTBLUE, "(Box Courier) "WHITE"Antarkan box ini hingga ke depan pintu rumah (lalu gunakan command "YELLOW"/deliverbox"WHITE")");
	SetPlayerAttachedObject(playerid, 9, 1271, 1,0.237980,0.473312,-0.066999, 1.099999,88.000007,-177.400085, 0.716000,0.572999,0.734000);
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
    g_CarryBox[playerid] = true;
    return 1;
}
StartPlayerBoxCourier(playerid) {


    found_house[playerid][0] = Iter_Random(House);
    found_house[playerid][1] = Iter_Random(House, found_house[playerid][0]);
    found_house[playerid][2] = Iter_Random(House, found_house[playerid][0], found_house[playerid][1]);
    found_house[playerid][3] = Iter_Random(House, found_house[playerid][0], found_house[playerid][1], found_house[playerid][2]);
    found_house[playerid][4] = Iter_Random(House, found_house[playerid][0], found_house[playerid][1], found_house[playerid][2], found_house[playerid][3]);

    g_CurrentHouse[playerid] = found_house[playerid][0];
    g_CurrentHouseIdx[playerid] = 0;

    printf("Current House: %d", g_CurrentHouse[playerid]);

    new houseid = g_CurrentHouse[playerid];

    CourierIcons[playerid] = CreateDynamicMapIcon(HouseData[houseid][housePos][0], HouseData[houseid][housePos][1], HouseData[houseid][housePos][2] + 0.5, 56, 0, _, _, playerid, 20000.0, MAPICON_GLOBAL);

    SendClientMessage(playerid, X11_LIGHTBLUE, "(Box Courier) "WHITE"Kamu telah memulai pekerjaan sebagai "YELLOW"Box Courier");
    SendClientMessage(playerid, X11_LIGHTBLUE, "(Box Courier) "WHITE"Antarkan 5 box ke-rumah yang ditandai dengan "RED"icon kuning "WHITE"pada peta-mu.");
    SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Box Courier) "WHITE"Antarkan ke rumah yang berada di "YELLOW"%s "WHITE"(( House ID %d ))", GetLocation(HouseData[houseid][housePos][0], HouseData[houseid][housePos][1], HouseData[houseid][housePos][2]), houseid);
    return 1;
}

GenerateNewDeliveredHouse(playerid) {

    g_CurrentHouseIdx[playerid]++;

    if(g_CurrentHouseIdx[playerid] >= MAX_DELIVERED_BOX) {

        g_CurrentHouse[playerid] = found_house[playerid][g_CurrentHouseIdx[playerid]];

        if(IsValidDynamicMapIcon(CourierIcons[playerid]))
            DestroyDynamicMapIcon(CourierIcons[playerid]);

        new houseid = g_CurrentHouse[playerid];

        CourierIcons[playerid] = CreateDynamicMapIcon(HouseData[houseid][housePos][0], HouseData[houseid][housePos][1], HouseData[houseid][housePos][2] + 0.5, 56, 0, _, _, playerid, 20000.0, MAPICON_GLOBAL);

        SendClientMessage(playerid, X11_LIGHTBLUE, "(Box Courier) "WHITE"Silahkan antar ke rumah terakhir, ditandai pada "RED"icon kuning "WHITE"pada peta-mu.");
        SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Box Courier) "WHITE"Antarkan ke rumah yang berada di "YELLOW"%s "WHITE"(( House ID %d ))", GetLocation(HouseData[houseid][housePos][0], HouseData[houseid][housePos][1], HouseData[houseid][housePos][2]), houseid);

    }
    else {
        g_CurrentHouse[playerid] = found_house[playerid][g_CurrentHouseIdx[playerid]];

        if(IsValidDynamicMapIcon(CourierIcons[playerid]))
            DestroyDynamicMapIcon(CourierIcons[playerid]);

        new houseid = g_CurrentHouse[playerid];

        CourierIcons[playerid] = CreateDynamicMapIcon(HouseData[houseid][housePos][0], HouseData[houseid][housePos][1], HouseData[houseid][housePos][2] + 0.5, 56, 0, _, _, playerid, 20000.0, MAPICON_GLOBAL);

        SendClientMessage(playerid, X11_LIGHTBLUE, "(Box Courier) "WHITE"Silahkan antar ke rumah selanjutnya, ditandai pada "RED"icon kuning "WHITE"pada peta-mu.");
        SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Box Courier) "WHITE"Antarkan ke rumah yang berada di "YELLOW"%s "WHITE"(( House ID %d ))", GetLocation(HouseData[houseid][housePos][0], HouseData[houseid][housePos][1], HouseData[houseid][housePos][2]), houseid);
    }
}
IsCourierVehicle(vehicleid)
{
	for(new i = 0; i < sizeof(CourierVehicle); i++)
	{
		if(vehicleid == CourierVehicle[i]) return 1;
	}
	return 0;	
}

CMD:deliverbox(playerid, params[]) {

    if(g_CourierState[playerid] != COURIER_STATE_DELIVERING)
        return SendErrorMessage(playerid, "Kamu tidak sedang bekerja sebagai box courier.");

    if(!g_CarryBox[playerid]) {
        return SendErrorMessage(playerid, "Kamu sedang tidak mengangkat box untuk diantar.");
    }

    new houseid = -1;

    if((houseid  = House_Nearest(playerid)) != -1) {

        if(houseid ==  g_CurrentHouse[playerid]) {
            new Float:dist = GetPlayerDistanceFromPoint(playerid, -1941.6987,-1040.1519,32.1719),
                calculated_salary = 0,
                i = g_CurrentHouse[playerid];

            calculated_salary = floatround(dist, floatround_ceil) * 2;
            g_TotalSalary[playerid] += calculated_salary;
            g_CarryBox[playerid] = false;
            
            SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Box Courier) "WHITE"Berhasil mengantarkan box! "GREEN"$%s "WHITE"ditambahkan pada pending box-courier salary anda nanti.",  FormatNumber(calculated_salary));
            SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Box Courier) "WHITE"Selanjutnya, antarkan ke rumah yang berada di "YELLOW"%s "WHITE"(( House ID %d ))", GetLocation(HouseData[i][housePos][0], HouseData[i][housePos][1], HouseData[i][housePos][2]), i);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            ApplyAnimation(playerid, "CARRY", "putdwn05", 4.1, 0, 1, 1, 0, 0, 1);
            RemovePlayerAttachedObject(playerid, 9);

            if(g_CurrentHouseIdx[playerid] < 4)
                GenerateNewDeliveredHouse(playerid);
            else {

                if(IsValidDynamicMapIcon(CourierIcons[playerid]))
                    DestroyDynamicMapIcon(CourierIcons[playerid]);

                SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Box Courier) "WHITE"Berhasil mengantarkan semua box! "RED"kembalikan kendaraan "WHITE"untuk mendapatkan salary (Ditandai pada radar)");
                g_CourierState[playerid] = COURIER_STATE_ONFINISH;
                SetPlayerCheckpoint(playerid, -1945.0291,-1085.2745,30.7779,  3.5);
            }
        }
        else {
            SendErrorMessage(playerid, "Rumah ini tidak menerima box dari-mu.");
        }
    }
    return  1;
}