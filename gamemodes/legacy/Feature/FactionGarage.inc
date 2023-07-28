#include <YSI_Coding\y_hooks>

new ListedGarageVeh[MAX_PLAYERS][100];

#define             MAX_FACTION_GARAGE              15

enum E_FACTION_GARAGE {
    fgID,
    fgFaction,
    Float:fgPos[3],
    Float:fgSpawnPos[4],
    STREAMER_TAG_CP:fgCP,
    Text3D:fgLabel
};
new
    FactionGarage[MAX_FACTION_GARAGE][E_FACTION_GARAGE],
    Iterator:FactionGarages<MAX_FACTION_GARAGE>;


FactionGarage_Create(faction_id, Float:x, Float:y, Float:z) {

    new id = ITER_NONE;

    if((id = Iter_Alloc(FactionGarages)) != ITER_NONE) {

        FactionGarage[id][fgFaction] = faction_id;
        FactionGarage[id][fgPos][0] = x;
        FactionGarage[id][fgPos][1] = y;
        FactionGarage[id][fgPos][2] = z;

        for(new i = 0; i < 4; i++) {
            FactionGarage[id][fgSpawnPos][i] = 0.0;
        }
        FactionGarage_Sync(id);

        mysql_tquery(sqlcon, "INSERT INTO `factiongarage` (`Faction`) VALUES('0')", "OnFactionGarageCreated", "d", id);
    }
    return id;
}

function OnFactionGarageCreated(id) {
    if(Iter_Contains(FactionGarages, id)) {
        FactionGarage[id][fgID] = cache_insert_id();
        FactionGarage_Save(id);
    }
    return 1;
}

FactionGarage_Save(id) {
    if(Iter_Contains(FactionGarages, id)) {
        new query[512];
        mysql_format(sqlcon, query, 512, "UPDATE `factiongarage` SET `Faction` = '%d', `PosX` = '%.4f', `PosY` = '%.4f', `PosZ` = '%.4f', `SpawnX` = '%.4f', `SpawnY` = '%.4f', `SpawnZ` = '%.4f', `SpawnA` = '%.4f' WHERE `ID` = '%d'",
            FactionGarage[id][fgFaction],
            FactionGarage[id][fgPos][0],
            FactionGarage[id][fgPos][1],
            FactionGarage[id][fgPos][2],
            FactionGarage[id][fgSpawnPos][0],
            FactionGarage[id][fgSpawnPos][1],
            FactionGarage[id][fgSpawnPos][2],
            FactionGarage[id][fgSpawnPos][3],
            FactionGarage[id][fgID]
        );
        mysql_tquery(sqlcon, query);
    }
    return 1;
}

FactionGarage_Sync(id) {
    if(Iter_Contains(FactionGarages, id)) {
        if(IsValidDynamic3DTextLabel(FactionGarage[id][fgLabel])) {
            Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, FactionGarage[id][fgLabel], FactionGarage[id][fgPos][0], FactionGarage[id][fgPos][1], FactionGarage[id][fgPos][2]);
        }
        else FactionGarage[id][fgLabel] = CreateDynamic3DTextLabel(sprintf("[ID:%d]\n%s\nFaction Garage", id, FactionData[FactionGarage[id][fgFaction]][factionName]), -1, FactionGarage[id][fgPos][0], FactionGarage[id][fgPos][1], FactionGarage[id][fgPos][2], 10.0);
    
        if(IsValidDynamicCP(FactionGarage[id][fgCP])) {
            Streamer_SetItemPos(STREAMER_TYPE_CP, FactionGarage[id][fgCP], FactionGarage[id][fgPos][0], FactionGarage[id][fgPos][1], FactionGarage[id][fgPos][2]);
        }
        else FactionGarage[id][fgCP] = CreateDynamicCP(FactionGarage[id][fgPos][0], FactionGarage[id][fgPos][1], FactionGarage[id][fgPos][2], 3.0, _, _, _, 5.0);
    }
    return 1;
}

FactionGarage_GetVehicleID(sql_id) {
    new vehicleid = INVALID_VEHICLE_ID;
    foreach(new i : Vehicle) if(VehicleData[i][vType] == VEHICLE_TYPE_FACTION && VehicleData[i][vExtraID] == sql_id) {
        vehicleid = i;
        break;
    }
    return vehicleid;
}

FactionGarage_Nearest(playerid) {
    new index = -1;
    foreach(new i : FactionGarages) if(IsPlayerInDynamicCP(playerid, FactionGarage[i][fgCP])) {
        index = i;
        break;
    }
    return index;
}

function OnVehicleGarageAdded(playerid, garage_id, modelid) {
    SendAdminAction(playerid, "You have added \"%s\" to Garage ID:%d", ReturnVehicleModelName(modelid), garage_id);
    return 1;
}

function FactionGarage_Load() {
    if(cache_num_rows()) {
        for(new i = 0; i < cache_num_rows(); i++) {

            Iter_Add(FactionGarages, i);

            cache_get_value_name_int(i, "ID", FactionGarage[i][fgID]);
            cache_get_value_name_int(i, "Faction", FactionGarage[i][fgFaction]);
            cache_get_value_name_float(i, "SpawnX", FactionGarage[i][fgSpawnPos][0]);
            cache_get_value_name_float(i, "SpawnY", FactionGarage[i][fgSpawnPos][1]);
            cache_get_value_name_float(i,"SpawnZ", FactionGarage[i][fgSpawnPos][2]);
            cache_get_value_name_float(i,"SpawnA", FactionGarage[i][fgSpawnPos][3]);
            cache_get_value_name_float(i,"PosX", FactionGarage[i][fgPos][0]);
            cache_get_value_name_float(i,"PosY", FactionGarage[i][fgPos][1]);
            cache_get_value_name_float(i,"PosZ", FactionGarage[i][fgPos][2]);

            FactionGarage_Sync(i);
        }
        printf("[FACTIONGARAGE] Loaded %d faction garage from database.", cache_num_rows());
    }
    return 1;
}
CMD:createfgarage(playerid, params[]) {
    if(PlayerData[playerid][pAdmin] < 5)
        return PermissionError(playerid);

    new faction_id = -1, faction_garage = ITER_NONE;

    if(sscanf(params, "d", faction_id))
        return SendSyntaxMessage(playerid, "/createfgarage [faction id]");

    if(!FactionData[faction_id][factionExists])
        return SendErrorMessage(playerid, "Specified faction is doesn't exists!");

    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);

    faction_garage = FactionGarage_Create(faction_id, x, y, z);

    if(faction_garage == ITER_NONE)
        return SendErrorMessage(playerid, "Server cannot create more faction garage.");

    SendAdminAction(playerid, "You have successfully created faction garage ID:%d for faction %s", faction_garage, FactionData[faction_id][factionName]);
    return 1;
}

CMD:editfgarage(playerid, params[]) {

    if(PlayerData[playerid][pAdmin] < 5)
        return PermissionError(playerid);

    new garage_id, string[128], type[24];
    if(sscanf(params, "ds[24]S()[128]", garage_id, type, string))
        return SendSyntaxMessage(playerid, "/editfgarage [garage id] [addveh/removeveh/location/spawnpos/destroy]");

    if(!strcmp(type, "addveh", true)) {
        new modelid[32], color1, color2;

        if(sscanf(string, "s[32]I(0)I(0)", modelid, color1, color2)) 
            return SendSyntaxMessage(playerid, "/editfgarage [garage id] [addveh] [modelid] [color1] [color2]");

        if ((modelid[0] = GetVehicleModelByName(modelid)) == 0)
            return SendErrorMessage(playerid, "Invalid model ID.");

        new query[382];
        mysql_format(sqlcon, query, 352, "INSERT INTO `factiongaragevehs` (`Garage`, `Model`, `Color1`, `Color2`) VALUES('%d','%d','%d','%d')", FactionGarage[garage_id][fgID], modelid[0], color1, color2);
        mysql_tquery(sqlcon, query, "OnVehicleGarageAdded", "ddd", playerid, garage_id, modelid);
    }
    else if(!strcmp(type, "destroy", true)) {

        if(IsValidDynamicCP(FactionGarage[garage_id][fgCP]))
            DestroyDynamicCP(FactionGarage[garage_id][fgCP]);

        if(IsValidDynamic3DTextLabel(FactionGarage[garage_id][fgLabel]))
            DestroyDynamic3DTextLabel(FactionGarage[garage_id][fgLabel]);

        SendAdminAction(playerid,  "You have destroyed Faction Garage ID:%d", garage_id);
        mysql_tquery(sqlcon, sprintf("DELETE FROM `factiongarage` WHERE `ID` = '%d'", FactionGarage[garage_id][fgID]));
        
        Iter_Remove(FactionGarages, garage_id);
    }
    else if(!strcmp(type, "location", true)) {

        GetPlayerPos(playerid, FactionGarage[garage_id][fgPos][0], FactionGarage[garage_id][fgPos][1], FactionGarage[garage_id][fgPos][2]);

        SendAdminAction(playerid, "You have adjusted location of Faction Garage ID: %d.", garage_id);
        FactionGarage_Sync(garage_id);

        FactionGarage_Save(garage_id);
    }
    else if(!strcmp(type, "spawnpos", true)) {

        if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
            return SendErrorMessage(playerid, "You must driving a vehicle.");

        GetVehiclePos(GetPlayerVehicleID(playerid), FactionGarage[garage_id][fgSpawnPos][0], FactionGarage[garage_id][fgSpawnPos][1], FactionGarage[garage_id][fgSpawnPos][2]);
        GetVehicleZAngle(GetPlayerVehicleID(playerid), FactionGarage[garage_id][fgSpawnPos][3]);

        FactionGarage_Save(garage_id);

        SendAdminAction(playerid, "You have adjusted vehicle spawn position Garage ID:%d", garage_id);
    }
    else if(!strcmp(type, "removeveh", true)) {

        new sql_id;
        if(sscanf(string, "d", sql_id))
            return SendSyntaxMessage(playerid, "/editfgarage [garage id] [removeveh] [vehicle sql id]");

        new query[156];
        mysql_format(sqlcon, query, sizeof(query), "DELETE FROM `factiongaragevehs` WHERE `ID` = '%d'", sql_id);
        mysql_tquery(sqlcon,query, "FactionRemoveVeh", "dd", playerid, sql_id);
    }
    return 1;
}

function FactionRemoveVeh(playerid, sql_id) {
    if(cache_affected_rows()) {
        SendAdminAction(playerid, "You have successfully removed vehicle sql id %d.", sql_id);

        foreach(new i : Vehicle) if(Vehicle_GetType(i) == VEHICLE_TYPE_FACTION && VehicleData[i][vExtraID] == sql_id) {
            Vehicle_Delete(i);
            break;
        }
    }
    else {
        SendErrorMessage(playerid, "Cannot find faction garage vehicle sql id %d.", sql_id);
    }
    return 1;
}
CMD:fgarage(playerid, params[]) {

    new garage_id = -1;
    if((garage_id = FactionGarage_Nearest(playerid)) != -1) {

        if(FactionGarage[garage_id][fgFaction] != PlayerData[playerid][pFaction]) 
            return SendErrorMessage(playerid, "Kamu tidak memiliki akses garasi ini.");

        if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {

            if(FactionGarage[garage_id][fgSpawnPos][0] == 0.0) {
                return SendErrorMessage(playerid, "Faction Garage ini belum memiliki spawn point.");
            }

            new query[178];
            mysql_format(sqlcon, query, sizeof(query), "SELECT * FROM `factiongaragevehs` WHERE `Garage` = '%d'", FactionGarage[garage_id][fgID]);
            mysql_tquery(sqlcon, query, "OnFactionGarage", "dd", playerid, garage_id);
        }
        else {

            new vehicleid = GetPlayerVehicleID(playerid);

            if(FactionGarage[garage_id][fgFaction] != PlayerData[playerid][pFaction]) 
                return SendErrorMessage(playerid, "Kamu tidak memiliki akses garasi ini.");

            if(Vehicle_GetType(vehicleid) != VEHICLE_TYPE_FACTION)
                return SendErrorMessage(playerid, "Ini bukan kendaraan faction!");

            if(VehicleData[vehicleid][vGarageID] != garage_id)
                return SendErrorMessage(playerid, "Kendaraan ini tidak bisa dimasukkan disini!");


            notification.Show(playerid, "Faction Vehicle", sprintf("You have returned %s~n~into faction garage.", GetVehicleName(vehicleid)), "hud:radar_impound");
            
            new Float:health, damage1, damage2, damage3, damage4;


            GetVehicleDamageStatus(vehicleid, damage1, damage2, damage3, damage4);
            GetVehicleHealth(vehicleid, health);

            new query[382];
            mysql_format(sqlcon, query, 382, "UPDATE `factiongaragevehs` SET `Health` = '%.4f', `Damage1` = '%d', `Damage2` = '%d', `Damage3` = '%d', `Damage4` = '%d', `Spawned` = '0' WHERE `ID` = '%d'",
                health, damage1, damage2, damage3, damage4, VehicleData[vehicleid][vExtraID]
            );

            mysql_tquery(sqlcon, query);

            Vehicle_Delete(vehicleid);
        }
    }
    return 1;
}

function OnFactionGarage(playerid, garage_id) {
    new string[1012];
    if(cache_num_rows()) {

        format(string, sizeof(string), "Unique ID\tVehicle Model\tHealth Left\n");

        new count = 0;
        for(new i = 0; i < cache_num_rows(); i++) {
            new modelid, Float:health, sqlid, spawned;

            cache_get_value_name_int(i, "Model", modelid);
            cache_get_value_name_float(i, "Health", health);
            cache_get_value_name_int(i, "ID", sqlid);
            cache_get_value_name_int(i, "Spawned", spawned);

            if(!spawned)
                format(string, sizeof(string), "%s#%d\t%s\t%.2f\n", string, sqlid, ReturnVehicleModelName(modelid), health);
            else 
                format(string, sizeof(string), "%s#%d\t%s "YELLOW"("WHITE"Used ID:%d"YELLOW")\t"WHITE"%.2f\n", string, sqlid, ReturnVehicleModelName(modelid), FactionGarage_GetVehicleID(sqlid), health);
            
            ListedGarageVeh[playerid][count++] = sqlid;
        }
        ShowPlayerDialog(playerid, DIALOG_FGARAGE_SPAWN, DIALOG_STYLE_TABLIST_HEADERS, sprintf("Faction Garage (ID:%d)", garage_id), string, "Spawn", "Close");
    }
    else {
        SendErrorMessage(playerid, "Faction Garage ini tidak memiliki kendaraan yang dapat dispawn.");
    }
    return 1;
}
hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {

 	if (newkeys & KEY_CROUCH && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
        new garage_id = -1;
        if((garage_id = FactionGarage_Nearest(playerid)) != -1) {

            new vehicleid = GetPlayerVehicleID(playerid);

            if(FactionGarage[garage_id][fgFaction] != PlayerData[playerid][pFaction]) 
                return SendErrorMessage(playerid, "Kamu tidak memiliki akses garasi ini.");

            if(Vehicle_GetType(vehicleid) != VEHICLE_TYPE_FACTION)
                return SendErrorMessage(playerid, "Ini bukan kendaraan faction!");

            if(VehicleData[vehicleid][vGarageID] != garage_id)
                return SendErrorMessage(playerid, "Kendaraan ini tidak bisa dimasukkan disini!");


            notification.Show(playerid, "Faction Vehicle", sprintf("You have returned %s~n~into faction garage.", GetVehicleName(vehicleid)), "hud:radar_impound");

            new Float:health, damage1, damage2, damage3, damage4;

            GetVehicleDamageStatus(vehicleid, damage1, damage2, damage3, damage4);
            GetVehicleHealth(vehicleid, health);

            new query[382];
            mysql_format(sqlcon, query, 382, "UPDATE `factiongaragevehs` SET `Health` = '%.4f', `Damage1` = '%d', `Damage2` = '%d', `Damage3` = '%d', `Damage4` = '%d', `Spawned` = '0' WHERE `ID` = '%d'",
                health, damage1, damage2, damage3, damage4, VehicleData[vehicleid][vExtraID]
            );

            mysql_tquery(sqlcon, query);

            Vehicle_Delete(vehicleid);
        }
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}
hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {
    if(dialogid == DIALOG_FGARAGE_SPAWN) {
        if(response) {
            new sql_id = ListedGarageVeh[playerid][listitem], garage_id = FactionGarage_Nearest(playerid);


            new query[156];
            mysql_format(sqlcon, query, sizeof(query), "SELECT * FROM `factiongaragevehs` WHERE `ID` = '%d' LIMIT 1;", sql_id);
            mysql_tquery(sqlcon, query, "SpawnFacGarage", "ddd", playerid, sql_id, garage_id);
        }
    }
}

function SpawnFacGarage(playerid, sql_id, garage_id) {
    if(cache_num_rows()) {
        new modelid, Float:health, damage1, damage2, damage3, damage4, color1, color2, vehicleid, siren = 0, spawned = 0;

        cache_get_value_name_int(0, "Model", modelid);
        cache_get_value_name_float(0, "Health", health);
        cache_get_value_name_int(0, "Color1", color1);
        cache_get_value_name_int(0, "Color2", color2);
        cache_get_value_name_int(0, "Damage1", damage1);
        cache_get_value_name_int(0, "Damage2", damage2);
        cache_get_value_name_int(0, "Damage3", damage3);
        cache_get_value_name_int(0, "Damage4", damage4);
        cache_get_value_name_int(0, "Spawned", spawned);

        if(spawned)
        {
            SendErrorMessage(playerid, "Kendaraan ini sudah terspawn!");
        }
        else {
            new factionid = FactionGarage[garage_id][fgFaction];

            if(FactionData[factionid][factionType] == FACTION_POLICE || FactionData[factionid][factionType] == FACTION_MEDIC)
                siren = 1;

            vehicleid = Vehicle_Create(modelid, FactionGarage[garage_id][fgSpawnPos][0], FactionGarage[garage_id][fgSpawnPos][1], FactionGarage[garage_id][fgSpawnPos][2], FactionGarage[garage_id][fgSpawnPos][3], color1, color2, siren, false, sprintf("%s", Faction_GetNameByID(factionid)));
            
            UpdateVehicleDamageStatus(vehicleid,  damage1, damage2, damage3, damage4);
            SetVehicleHealth(vehicleid, health);

            VehicleData[vehicleid][vFactionType] = FactionData[factionid][factionType];
            Vehicle_SetType(vehicleid, VEHICLE_TYPE_FACTION);
            VehicleData[vehicleid][vGarageID] = garage_id;
            VehicleData[vehicleid][vExtraID] = sql_id;

            PutPlayerInVehicle(playerid, vehicleid, 0);
            SetVehicleNumberPlate(vehicleid, sprintf("%s", Faction_GetNameByID(factionid)));

            mysql_tquery(sqlcon, sprintf("UPDATE `factiongaragevehs` SET `Spawned` = '1' WHERE `ID` = '%d'", sql_id));
        }
    }
    return 1;
}