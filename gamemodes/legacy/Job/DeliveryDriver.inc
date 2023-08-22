#include <YSI_Coding\y_hooks>


new bool:OnDeliveryWork[MAX_PLAYERS] = {false, ...};

IsForkliftVehicle(vehicleid) {
    for(new i = 0; i < sizeof(ForkliftVehicle); i++) {
        if(vehicleid == ForkliftVehicle[i]) return 1;
    }
    return 0;
}

IsRumpoVehicle(vehicleid) {
    for(new i = 0; i < sizeof(RumpoVehicle); i++) {
        if(vehicleid == RumpoVehicle[i]) return 1;
    }
    return 0;
}

hook OnPlayerEnterVehicle(playerid, vehicleid, ispassenger) {

    if(IsRumpoVehicle(vehicleid)) {
        foreach(new i : Player) if(PlayerData[i][pRumpoVehicle] == vehicleid && i != playerid) {
            SetPlayerCurrentPos(playerid);
            FreezePlayer(playerid, 2000);
            SendErrorMessage(playerid, "Kendaraan tersebut sedang digunakan oleh player lain!");
            break;
        }
    }
    if(IsForkliftVehicle(vehicleid) && GetPVarInt(playerid, "ReturnRumpo")) {
        SendServerMessage(playerid, "Pergi ke-checkpoint untuk menyelesaikan pekerjaan!");
        SetPlayerCurrentPos(playerid);
    }
}

hook OnPlayerStateChange(playerid, newstate, oldstate) 
{
    if(newstate == PLAYER_STATE_DRIVER && IsRumpoVehicle(GetPlayerVehicleID(playerid))) {

        if(!OnDeliveryWork[playerid]) {
            RemovePlayerFromVehicle(playerid);
            SendErrorMessage(playerid, "Kamu belum memulai pekerjaan ini.");
        }
        else {
            if(PlayerData[playerid][pRumpoVehicle] != INVALID_VEHICLE_ID && PlayerData[playerid][pRumpoVehicle] != GetPlayerVehicleID(playerid)) {
                SendErrorMessage(playerid, "Ini bukan kendaraan rumpo-mu!");
                RemovePlayerFromVehicle(playerid);
            }
            else {

                if(PlayerData[playerid][pRumpoVehicle] == INVALID_VEHICLE_ID)
                    PlayerData[playerid][pRumpoVehicle] = GetPlayerVehicleID(playerid);

                if(VehicleData[PlayerData[playerid][pRumpoVehicle]][vLoadedCrate] > 0)
                   SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Delivery Driver) "WHITE"Rumpo ini berisi "YELLOW"%d/15 crate"WHITE", antarkan ke Delivery Driver Unloading Point (lokasi di GPS)", VehicleData[PlayerData[playerid][pRumpoVehicle]][vLoadedCrate]);
            }
        }
    }
    if(newstate == PLAYER_STATE_DRIVER && IsForkliftVehicle(GetPlayerVehicleID(playerid)) && !OnDeliveryWork[playerid]) {
        RemovePlayerFromVehicle(playerid);
        SendErrorMessage(playerid, "Kamu belum memulai pekerjaan ini.");
    }
    if(newstate == PLAYER_STATE_ONFOOT && oldstate == PLAYER_STATE_DRIVER) {

        if(IsForkliftVehicle(PlayerData[playerid][pLastVehicleID])) {

            /*if(IsValidDynamicObject(VehicleData[PlayerData[playerid][pLastVehicleID]][vCrateObject]))
                DestroyDynamicObject(VehicleData[PlayerData[playerid][pLastVehicleID]][vCrateObject]);

            VehicleData[PlayerData[playerid][pLastVehicleID]][vCrateObject] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;*/

            SetVehicleToRespawn(PlayerData[playerid][pLastVehicleID]);
            VehicleData[PlayerData[playerid][pLastVehicleID]][vHaveCrate] = false;
            VehicleData[PlayerData[playerid][pLastVehicleID]][vFuel] = 10.0;
        }
    }
}

hook OnPlayerEnterCheckpoint(playerid) {

    if(IsPlayerInRangeOfPoint(playerid, 7.0, -1720.2201,53.4831,3.5495) && GetPVarInt(playerid, "ReturnRumpo")) {
        
        if(IsRumpoVehicle(PlayerData[playerid][pRumpoVehicle])) {
            SetVehicleToRespawn(PlayerData[playerid][pRumpoVehicle]);
            VehicleData[PlayerData[playerid][pRumpoVehicle]][vFuel] = 10.0;
            RepairVehicle(PlayerData[playerid][pRumpoVehicle]);
            VehicleData[PlayerData[playerid][pRumpoVehicle]][vLoadedCrate] = 0;

            new payment = GetPVarInt(playerid, "BoxPayment");
            GiveMoney(playerid, payment, "Delivery Crate Rumpo Sidejob");
            SendServerMessage(playerid, "Kamu berhasil menyelesaikan pekerjaan dan mendapatkan "GREEN"$%s", FormatNumber(payment));
            DisablePlayerCheckpoint(playerid);
            
            OnDeliveryWork[playerid] = false;
            DeletePVar(playerid, "BoxPayment");
            DeletePVar(playerid, "ReturnRumpo");

            PlayerData[playerid][pDriverDelay] = 1200;
            PlayerData[playerid][pRumpoVehicle] = INVALID_VEHICLE_ID;
        }
    }
}
hook OnPlayerConnect(playerid) {
    OnDeliveryWork[playerid] = false;
}

hook OnPlayerDisconnectEx(playerid) {

    if(OnDeliveryWork[playerid] && PlayerData[playerid][pRumpoVehicle] != INVALID_VEHICLE_ID && IsRumpoVehicle(PlayerData[playerid][pRumpoVehicle])) {
        SetVehicleToRespawn(PlayerData[playerid][pRumpoVehicle]);
        VehicleData[PlayerData[playerid][pRumpoVehicle]][vLoadedCrate] = 0;
        OnDeliveryWork[playerid] = false;
    }
}
CMD:stopdeliver(playerid, params[]) {

    if(!IsPlayerInRangeOfPoint(playerid, 5.0, -1702.7526,33.5595,3.5547))
        return SendErrorMessage(playerid, "Kamu tidak berada di tempat bekerja.");

    if(!OnDeliveryWork[playerid])
        return SendErrorMessage(playerid, "Kamu belum memulai pekerjaan ini.");

    OnDeliveryWork[playerid] = false;
    SendServerMessage(playerid, "Kamu berhenti bekerja sebagai "YELLOW"Delivery Driver"WHITE".");

    if(IsPlayerInAnyVehicle(playerid))
        RemovePlayerFromVehicle(playerid);

    if(PlayerData[playerid][pRumpoVehicle] != INVALID_VEHICLE_ID && IsRumpoVehicle(PlayerData[playerid][pRumpoVehicle])) {
        SetVehicleToRespawn(PlayerData[playerid][pRumpoVehicle]);
        VehicleData[PlayerData[playerid][pRumpoVehicle]][vLoadedCrate] = 0;
    }
    return 1;
}


CMD:startdeliver(playerid, params[]) {

    if(PlayerData[playerid][pDriverDelay])
        return SendErrorMessage(playerid, "Tunggu %d menit untuk kembali bekerja.", PlayerData[playerid][pDriverDelay]/60);

    if(!IsPlayerInRangeOfPoint(playerid, 5.0, -1702.7526,33.5595,3.5547))
        return SendErrorMessage(playerid, "Kamu tidak berada di tempat bekerja.");

    if(OnDeliveryWork[playerid])
        return SendErrorMessage(playerid, "Kamu sudah memulai pekerjaan ini.");

    if(PlayerData[playerid][pMasked])
        return SendErrorMessage(playerid, "Buka maskermu terlebih dahulu!");
        
    OnDeliveryWork[playerid] = true;
    SendServerMessage(playerid, "Kamu memulai bekerja sebagai "YELLOW"Delivery Driver"WHITE", gunakan /help untuk petunjuk pekerjaan.");
    return 1;
}

CMD:unloadcrate(playerid, params[]) {
    
    new vehicleid = GetPlayerVehicleID(playerid),
        veh_box = 0,
        payment = 0;

    if(!IsPlayerInRangeOfPoint(playerid, 5.0, -2750.7354,203.6906,7.0267))
        return SendErrorMessage(playerid, "Kamu tidak berada di unload point.");

    if(!OnDeliveryWork[playerid])
        return SendErrorMessage(playerid, "Kamu belum memulai pekerjaan.");

    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
        return SendErrorMessage(playerid, "Kamu harus mengemudi Rumpo milikmu.");

    if(!IsRumpoVehicle(vehicleid))
        return SendErrorMessage(playerid, "Kamu harus mengemudi Rumpo milikmu.");

    if(vehicleid != PlayerData[playerid][pRumpoVehicle])
        return SendErrorMessage(playerid, "Kamu harus mengemudi Rumpo milikmu.");

    veh_box = VehicleData[vehicleid][vLoadedCrate];
    
    if(veh_box < 1)
        return SendErrorMessage(playerid, "Tidak ada crate pada kendaraan ini.");

    payment = veh_box * 1000;

    SendServerMessage(playerid, "Kamu berhasil mengantarkan "YELLOW"%d"WHITE" crate.", veh_box);
    SendServerMessage(playerid, "Sekarang, antarkan Rumpo ini kembali untuk mendapatkan gaji-mu.");
    SetPlayerCheckpoint(playerid, -1720.2201,53.4831,3.5495, 5.0);
    SetPVarInt(playerid, "BoxPayment", payment);
    SetPVarInt(playerid, "ReturnRumpo", 1);

    VehicleData[PlayerData[playerid][pRumpoVehicle]][vLoadedCrate] = 0;
    return 1;
}
CMD:pickupcrate(playerid, params[]) {
    
    new vehicleid = GetPlayerVehicleID(playerid);

    if(!IsPlayerInRangeOfPoint(playerid, 5.0, -1699.6128,6.0661,3.5547))
        return SendErrorMessage(playerid, "Kamu tidak berada di pickup point.");

    if(!OnDeliveryWork[playerid])
        return SendErrorMessage(playerid, "Kamu belum memulai pekerjaan.");

    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
        return SendErrorMessage(playerid, "Kamu harus mengemudi Forklift!");

    if(!IsForkliftVehicle(vehicleid))
        return SendErrorMessage(playerid, "Kamu harus mengemudi Forklift!");

    if(VehicleData[vehicleid][vHaveCrate])
        return SendErrorMessage(playerid, "Kendaraan ini sudah mengangkut Crate!");

    StartPlayerLoadingBar(playerid, 150, "Picking_up_crate...", 30, "OnLoadingForkliftCrate");
    TogglePlayerControllable(playerid, false);
    return 1;
}

CMD:loadcrate(playerid, params[]) {

    new vehicleid = GetPlayerVehicleID(playerid),
        veh_rumpo;

    if(!OnDeliveryWork[playerid])
        return SendErrorMessage(playerid, "Kamu belum memulai pekerjaan.");

    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
        return SendErrorMessage(playerid, "Kamu harus mengemudi Forklift!");

    if(!IsForkliftVehicle(vehicleid))
        return SendErrorMessage(playerid, "Kamu harus mengemudi Forklift!");

    if((veh_rumpo = GetNearestVehicle(playerid, 8.0)) != INVALID_VEHICLE_ID) {
        if(GetVehicleModel(veh_rumpo) == 440 && PlayerData[playerid][pRumpoVehicle] == veh_rumpo) {
    
            if(!VehicleData[vehicleid][vHaveCrate])
                return SendErrorMessage(playerid, "Kamu belum mengangkut Crate!");

            if(VehicleData[veh_rumpo][vLoadedCrate] >= 15)
                return SendErrorMessage(playerid, "Kamu tidak bisa menampung lebih banyak dari 15 crate.");
            
            VehicleData[veh_rumpo][vLoadedCrate]++;
            SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Delivery Driver) "WHITE"Kendaraan rumpo-mu sekarang berisi "YELLOW"%d/15 crate", VehicleData[veh_rumpo][vLoadedCrate]);
            ShowMessage(playerid, "Crate_Loaded!", 2, 1);
            VehicleData[vehicleid][vHaveCrate] = false;
            
            /*if(IsValidDynamicObject(VehicleData[vehicleid][vCrateObject]))
                DestroyDynamicObject(VehicleData[vehicleid][vCrateObject]);

            VehicleData[vehicleid][vCrateObject] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;*/
        }
        else SendErrorMessage(playerid, "Kamu hanya bisa memasukan crate ke rumpo-mu.");
    }
    else SendErrorMessage(playerid, "Kamu hanya bisa memasukan crate ke rumpo-mu.");
    return 1;
}
function OnLoadingForkliftCrate(playerid) {

    new vehicleid = GetPlayerVehicleID(playerid);

    if(OnDeliveryWork[playerid] && IsForkliftVehicle(vehicleid)) {

        /*if(IsValidDynamicObject(VehicleData[vehicleid][vCrateObject]))
           DestroyDynamicObject(VehicleData[vehicleid][vCrateObject]);

        VehicleData[vehicleid][vCrateObject] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;*/

        // VehicleData[vehicleid][vCrateObject] = CreateDynamicObject(1220,0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
        // AttachDynamicObjectToVehicle(VehicleData[vehicleid][vCrateObject], vehicleid, -0.010, 0.580, 0.270, 0.000, 0.000, 0.000);

        ShowMessage(playerid, "Crate Pickuped!", 3, 1);
        TogglePlayerControllable(playerid, true);
        SendClientMessage(playerid, X11_LIGHTBLUE, "(Delivery Driver) "WHITE"Masukkan box kedalam rumpo dengan "YELLOW"/loadcrate");
        VehicleData[vehicleid][vHaveCrate] = true;
    }
    return 1;
}