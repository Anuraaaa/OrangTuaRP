#include <YSI_Coding\y_hooks>

task OnVehicleELMFlash[300]() {
    foreach(new vehicleid : Vehicle) if(IsValidVehicle(vehicleid) && VehicleData[vehicleid][vType] == VEHICLE_TYPE_FACTION && VehicleData[vehicleid][vELM]) {

        if(!IsValidVehicle(vehicleid))
            return KillTimer(FlashTime[vehicleid]);

        new panels, doors, lights, tires;
        GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);

        switch(Flash[vehicleid])
        {
            case 0: UpdateVehicleDamageStatus(vehicleid, panels, doors, 2, tires);

            case 1: UpdateVehicleDamageStatus(vehicleid, panels, doors, 5, tires);

            case 2: UpdateVehicleDamageStatus(vehicleid, panels, doors, 2, tires);

            case 3: UpdateVehicleDamageStatus(vehicleid, panels, doors, 4, tires);

            case 4: UpdateVehicleDamageStatus(vehicleid, panels, doors, 5, tires);

            case 5: UpdateVehicleDamageStatus(vehicleid, panels, doors, 4, tires);
        }
        if(Flash[vehicleid] >=5) Flash[vehicleid] = 0;
        else Flash[vehicleid] ++;
    }
    return  1;
}

CMD:elm(playerid, params[]) {

    new vehicleid = GetPlayerVehicleID(playerid);

 	if (GetFactionType(playerid) != FACTION_POLICE && GetFactionType(playerid) != FACTION_MEDIC && GetFactionType(playerid) != FACTION_GOV)
	    return SendErrorMessage(playerid, "You must be a civil service worker to use ELM");

    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
        return SendErrorMessage(playerid, "Kamu harus berada didalam kendaraan faction!");

    VehicleData[vehicleid][vELM] = !(VehicleData[vehicleid][vELM]);
    ShowMessage(playerid, sprintf("~y~ELM ~w~kendaraan berhasil %s", (VehicleData[vehicleid][vELM]) ? ("~g~dinyalakan") : ("~r~dimatikan")), 4);

    if(!VehicleData[vehicleid][vELM]) {
        SwitchVehicleLight(vehicleid, false);
    }
    return 1;
}