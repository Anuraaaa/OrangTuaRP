#include <YSI_Coding\y_hooks>

#define SMUGGLER_DEFAULT_OBJ            11745
#define SMUGGLER_RECOVER_TIME           3600

new Float: RandomPacketPos[12][3] =
{
    {-788.65, 1565.19, 26.32},
    {-166.42, 1177.99, 22.15},
    {2428.71, 86.60, 27.05},
    {1270.54, 307.02, 18.73},
    {774.23, -484.35, 16.54},
    {206.32, -102.91, 4.10},
    {-1663.82, 1080.81, 7.13},
    {-2147.69, 1229.76, 33.13},
    {-673.34, 2706.38, 69.97},
    {2354.80, -680.41, 132.14},
    {-1635.92, -2246.49, 30.68},
    {858.25, -18.09, 62.40}
};

new Float:RandomDeliverPos[2][3] = {
    {-2214.3440,618.3339,35.1641},
    {-1435.9888,-965.0600,201.0257}
};

enum E_SMUGGLER_DATA {
    STREAMER_TAG_OBJECT:smugObject,
    STREAMER_TAG_CP:smugCP,
    Float:smugX,
    Float:smugY,
    Float:smugZ,
    Float:smugDelivX,
    Float:smugDelivY,
    Float:smugDelivZ,
    bool:smugIsReady,
    bool:smugHaveTaken,
    smugTime,
    smugCarrier,
    bool:smugOnTaked,
    smugDeliverTime
};

new SmugglerData[E_SMUGGLER_DATA];

hook OnGameModeInit() {

    SmugglerData[smugCarrier] = INVALID_PLAYER_ID;
    SmugglerData[smugTime] = 5;
    SmugglerData[smugIsReady] = false;
    SmugglerData[smugHaveTaken] = false;
    SmugglerData[smugObject] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
    SmugglerData[smugCP] = STREAMER_TAG_CP:INVALID_STREAMER_ID;
    SmugglerData[smugOnTaked] = false;
    SmugglerData[smugDelivX] = 0.0;
    SmugglerData[smugDelivY] = 0.0;
    SmugglerData[smugDelivZ] = 0.0;
    SmugglerData[smugDeliverTime] = 0;

	CreateDynamicPickup(1239, 23,-2215.5137,117.5038,35.3203, 0, 0, -1, 5.0);
	CreateDynamic3DTextLabel(""LIGHTBLUE"[SMUGGLER]\n"WHITE"Use "YELLOW"/takejob "WHITE"to become smuggler", -1, -2215.5137,117.5038,35.3203, 2.0);
}


hook OnPlayerEnterDynamicCP(playerid, STREAMER_TAG_CP:checkpointid) {
    if(checkpointid == SmugglerData[smugCP] && IsPlayerInRangeOfPoint(playerid, 5.0, SmugglerData[smugX],SmugglerData[smugY], SmugglerData[smugZ])) {
        ShowMessage(playerid, "~r~/takepacket ~w~untuk mengambil paket.", 3);
    }
}

hook OnPlayerInjured(playerid) {
    if(SmugglerData[smugCarrier] == playerid) {
        Smuggler_Drop(playerid);
        SendClientMessage(playerid, X11_TOMATO, "(Smuggler) "WHITE"Paket terjatuh dikarenakan kamu injured.");
    }
}

hook OnPlayerDisconnectEx(playerid) {
    if(SmugglerData[smugCarrier] == playerid) {
        Smuggler_Drop(playerid);
    }
}
hook OnPlayerEnterRaceCP(playerid) {
    if(SmugglerData[smugCarrier] == playerid) {
        if(IsPlayerInRangeOfPoint(playerid, 5.0, SmugglerData[smugDelivX],  SmugglerData[smugDelivY],  SmugglerData[smugDelivZ])) {

            new salary = RandomEx(30000, 50000);

            AddSalary(playerid, "Delivering Packet (smuggler)", salary);

            SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Smuggler) "WHITE"Berhasil mengantarkan paket dan mendapatkan "GREEN"$%s", FormatNumber(salary));

            SendJobMessage(JOB_SMUGGLER, X11_LIGHTBLUE, "(Smuggler) "WHITE"Smuggler Packet berhasil diantarkan ke tujuan! packet akan kembali dalam 60 menit.");
            DisablePlayerRaceCheckpoint(playerid);

            SmugglerData[smugTime] = SMUGGLER_RECOVER_TIME;
            SmugglerData[smugCarrier] = INVALID_PLAYER_ID;
            SmugglerData[smugHaveTaken] = false;
            SmugglerData[smugDeliverTime] = 0;
        }
    }
}
Smuggler_Create() {
    new rand_pos = random(12);

    SmugglerData[smugX] = RandomPacketPos[rand_pos][0];
    SmugglerData[smugY] = RandomPacketPos[rand_pos][1];
    SmugglerData[smugZ] = RandomPacketPos[rand_pos][2];

    SmugglerData[smugObject] = CreateDynamicObject(SMUGGLER_DEFAULT_OBJ, SmugglerData[smugX],SmugglerData[smugY], SmugglerData[smugZ], 0.0, 0.0, 0.0, 0, 0, -1, 30.0, 30.0);
    SmugglerData[smugCP] = CreateDynamicCP(SmugglerData[smugX],SmugglerData[smugY], SmugglerData[smugZ], 0.7, 0, 0, -1, 3.0);
    return 1;
}

Smuggler_Drop(playerid) {
    if(SmugglerData[smugCarrier] == playerid) {

        new Float:x, Float:y, Float:z;
        GetPlayerPos(playerid, x, y, z);

        SmugglerData[smugX] = x;
        SmugglerData[smugY] = y;
        SmugglerData[smugZ] = z;

        SmugglerData[smugObject] = CreateDynamicObject(SMUGGLER_DEFAULT_OBJ, SmugglerData[smugX],SmugglerData[smugY], SmugglerData[smugZ] - 0.9, 0.0, 0.0, 0.0, 0, 0, -1, 30.0, 30.0);
        SmugglerData[smugCP] = CreateDynamicCP(SmugglerData[smugX],SmugglerData[smugY], SmugglerData[smugZ], 0.7, 0, 0, -1, 3.0);
        SmugglerData[smugCarrier] = INVALID_PLAYER_ID;

        DisablePlayerRaceCheckpoint(playerid);
    }
}

Smuggler_DeliverInfo(playerid) {
    if(SmugglerData[smugCarrier] == playerid) {

        new idx = random(2);
        SmugglerData[smugDelivX] = RandomDeliverPos[idx][0];
        SmugglerData[smugDelivY] = RandomDeliverPos[idx][1];
        SmugglerData[smugDelivZ] = RandomDeliverPos[idx][2];

        SetPlayerRaceCheckpoint(playerid, 2, SmugglerData[smugDelivX], SmugglerData[smugDelivY], SmugglerData[smugDelivZ], 0.0, 0.0, 0.0, 5.0);
    }
}
task timer_SmugglerUpdate[1000]() {
    
    if(SmugglerData[smugTime] && SmugglerData[smugCarrier] == INVALID_PLAYER_ID) {
        if(--SmugglerData[smugTime] <= 0) {
            Smuggler_Create();

            SmugglerData[smugIsReady] = true;
            SmugglerData[smugOnTaked] = false;
            SmugglerData[smugCarrier] = INVALID_PLAYER_ID;

            SendJobMessage(JOB_SMUGGLER, X11_RED, "(Smuggler) "WHITE"Packet is now available! type "YELLOW"/trackpacket "WHITE"to track.");
        }
    }

    if(SmugglerData[smugHaveTaken]) {
        if(--SmugglerData[smugDeliverTime] <= 0) {

            SendJobMessage(JOB_SMUGGLER, X11_LIGHTBLUE, "(Smuggler) "WHITE"Paket kembali diambil dikarenakan tidak diantar dalam 30 menit.");
            DisablePlayerRaceCheckpoint(SmugglerData[smugCarrier]);

            SmugglerData[smugTime] = SMUGGLER_RECOVER_TIME;
            SmugglerData[smugHaveTaken] = false;
            SmugglerData[smugIsReady] = true;
            SmugglerData[smugOnTaked] = false;
            SmugglerData[smugCarrier] = INVALID_PLAYER_ID;
            SmugglerData[smugDeliverTime] = 0;
        }
    }
    return 1;
}

timer timer_TakeSmugglerPacketEx[5000](playerid) {

    TogglePlayerControllable(playerid, true);
    ClearAnimations(playerid, 1);
    SmugglerData[smugOnTaked] = false;

    if(PlayerData[playerid][pInjured]) {
        SendErrorMessage(playerid, "Gagal mengambil paket dikarenakan kamu sekarat.");
        return 1;
    }
    if(IsPlayerInRangeOfPoint(playerid, 3.0, SmugglerData[smugX],SmugglerData[smugY], SmugglerData[smugZ])) {

        if(IsValidDynamicObject(SmugglerData[smugObject]))
            DestroyDynamicObject(SmugglerData[smugObject]);

        if(IsValidDynamicCP(SmugglerData[smugCP]))
            DestroyDynamicCP(SmugglerData[smugCP]);

        SmugglerData[smugCarrier] = playerid;
        SendServerMessage(playerid, "Paket berhasil diambil! antarkan ke checkpoint pada radarmu.");

        SetPlayerRaceCheckpoint(playerid, 2, SmugglerData[smugDelivX], SmugglerData[smugDelivY], SmugglerData[smugDelivZ], 0.0, 0.0, 0.0, 5.0);
    }
    else SendErrorMessage(playerid, "Kamu tidak berada didekat paket.");

    return 1;
}

timer timer_TakeSmugglerPacket[5000](playerid) {

    TogglePlayerControllable(playerid, true);
    ClearAnimations(playerid, 1);
    SmugglerData[smugOnTaked] = false;

    if(PlayerData[playerid][pInjured]) {
        SendErrorMessage(playerid, "Gagal mengambil paket dikarenakan kamu sekarat.");
        return 1;
    }
    if(IsPlayerInRangeOfPoint(playerid, 3.0, SmugglerData[smugX],SmugglerData[smugY], SmugglerData[smugZ])) {

        if(IsValidDynamicObject(SmugglerData[smugObject]))
            DestroyDynamicObject(SmugglerData[smugObject]);

        if(IsValidDynamicCP(SmugglerData[smugCP]))
            DestroyDynamicCP(SmugglerData[smugCP]);

        SmugglerData[smugCarrier] = playerid;
        SmugglerData[smugIsReady] = false;
        SmugglerData[smugTime] = 0;
        SmugglerData[smugHaveTaken] = true;
        SmugglerData[smugDeliverTime] = 1800;

        SendServerMessage(playerid, "Paket berhasil diambil! antarkan ke checkpoint pada radarmu.");

        Smuggler_DeliverInfo(playerid);
    }
    else SendErrorMessage(playerid, "Kamu tidak berada didekat paket.");

    return 1;
}

CMD:spawnpacket(playerid, params[]) {
    if(PlayerData[playerid][pAdmin] < 7)
        return SendErrorMessage(playerid, NO_PERMISSION);


    if(SmugglerData[smugCarrier] != INVALID_PLAYER_ID)
        DisablePlayerRaceCheckpoint(SmugglerData[smugCarrier]);


    SmugglerData[smugIsReady] = true;
    SmugglerData[smugOnTaked] = false;
    SmugglerData[smugCarrier] = INVALID_PLAYER_ID;
    SmugglerData[smugHaveTaken] = false;
    SmugglerData[smugDeliverTime] = 0;
    SmugglerData[smugTime] = 0;
    SendJobMessage(JOB_SMUGGLER, X11_RED, "(Smuggler) "WHITE"Packet is now available! type "YELLOW"/trackpacket "WHITE"to track.");

    SendAdminAction(playerid, "You have respawned smuggler packet.");

    Smuggler_Create();
    return 1;
}
CMD:takepacket(playerid, params[]) {

    if(CheckPlayerJob(playerid, JOB_SMUGGLER)) {


        if(SmugglerData[smugCarrier] == INVALID_PLAYER_ID) {
            if(!SmugglerData[smugHaveTaken]) {
                if(!IsPlayerInRangeOfPoint(playerid, 3.0, SmugglerData[smugX],SmugglerData[smugY], SmugglerData[smugZ]))
                    return SendErrorMessage(playerid, "Kamu tidak berada didekat paket.");

                if(SmugglerData[smugOnTaked])
                    return SendErrorMessage(playerid, "Paket ini sedang diambil.");

                if(PlayerData[playerid][pInjured])
                    return SendErrorMessage(playerid, "Kamu sedang injured dan tidak dapat mengambil paket.");

                SmugglerData[smugOnTaked] = true;
                TogglePlayerControllable(playerid, false);
                ApplyAnimation(playerid,"BOMBER","BOM_Plant_Loop", 4.1, 1, 0, 0, 1, 0, 1);
                defer timer_TakeSmugglerPacket[5000](playerid);
                StartPlayerLoadingBar(playerid, 5, "Taking_Packet", 1000);	
            }
            else {
                if(!IsPlayerInRangeOfPoint(playerid, 3.0, SmugglerData[smugX],SmugglerData[smugY], SmugglerData[smugZ]))
                    return SendErrorMessage(playerid, "Kamu tidak berada didekat paket.");

                if(SmugglerData[smugOnTaked])
                    return SendErrorMessage(playerid, "Paket ini sedang diambil.");

                if(PlayerData[playerid][pInjured])
                    return SendErrorMessage(playerid, "Kamu sedang injured dan tidak dapat mengambil paket.");

                SmugglerData[smugOnTaked] = true;
                TogglePlayerControllable(playerid, false);
                ApplyAnimation(playerid,"BOMBER","BOM_Plant_Loop", 4.1, 1, 0, 0, 1, 0, 1);
                defer timer_TakeSmugglerPacketEx[5000](playerid);
                StartPlayerLoadingBar(playerid, 5, "Taking_Packet", 1000);	
            }
        } 
        else if(SmugglerData[smugCarrier] == playerid) {
            SendErrorMessage(playerid, "Kamu sedang membawa paket smuggler!");
        }
        else SendErrorMessage(playerid, "Paket sedang dibawa oleh orang lain, gunakan (( /trackpacket ))");
    }
    else SendErrorMessage(playerid, "Kamu harus menjadi smuggler terlebih dahulu.");
    return 1;
}


CMD:trackpacket(playerid, params[]) {
    if(CheckPlayerJob(playerid, JOB_SMUGGLER)) {

        if(SmugglerData[smugTime]) {
            return SendErrorMessage(playerid, "Smuggler is on cooldown! please wait for %d minutes.", SmugglerData[smugTime]/60);
        }
        new
            carrier = SmugglerData[smugCarrier];

        if(carrier == INVALID_PLAYER_ID) {
            SendClientMessage(playerid, X11_LIGHTBLUE, "(Smuggler) "WHITE"Smuggler packet is "LIGHTGREEN"standing still");

            SetPlayerCheckpoint(playerid, SmugglerData[smugX], SmugglerData[smugY], SmugglerData[smugZ], 5.0);
            PlayerData[playerid][pTracking] = true;
        }
        else {
            if(IsPlayerConnected(carrier)) {

                if(carrier == playerid) {
                    SendErrorMessage(playerid, "Smuggler paket ada pada kamu.");
                    return 1;
                }
                
                new Float:x, Float:y, Float:z;
                ReturnSpecificLocation(carrier, x, y, z);

                SendClientMessage(playerid, X11_LIGHTBLUE, "(Smuggler) "WHITE"Smuggler packet is "TOMATO"moving");

                SetPlayerCheckpoint(playerid, x, y, z, 5.0);
                PlayerData[playerid][pTracking] = true;
            }
        }
    }
    else SendErrorMessage(playerid, "Kamu harus menjadi smuggler terlebih dahulu.");

    return 1;
}

