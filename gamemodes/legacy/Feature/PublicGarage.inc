#include <YSI_Coding\y_hooks>

enum E_PUBLIC_GARAGE {
    garageID,
    Float:garageX,
    Float:garageY,
    Float:garageZ,
    Text3D:garageLabel,
    STREAMER_TAG_PICKUP:garagePickup
};
new
    GarageData[MAX_PUBLIC_GARAGE][E_PUBLIC_GARAGE],
    Iterator:Garage<MAX_PUBLIC_GARAGE>,
    g_NearGarage[MAX_PLAYERS];

hook OnGameModeInit() {

    if (IsSQLConnected()) {
        Iter_Init(Garage);
		mysql_tquery(sqlcon, "SELECT * FROM `garage`", "Garage_Load", "");
    }
}

hook OnGameModeExit() {

    if (IsSQLConnected()) {
        Iter_Clear(Garage);
    }
}

Garage_Create(Float:x, Float:y, Float:z) {

    new
        index = ITER_NONE;

    if((index = Iter_Alloc(Garage)) != ITER_NONE) {

        GarageData[index][garageX] = x;
        GarageData[index][garageY] = y;
        GarageData[index][garageZ] = z;
        Garage_Sync(index);
        mysql_tquery(sqlcon, "INSERT INTO `garage` (`PosX`) VALUES(0)", "OnGarageCreated", "d", index);
    }
    return index;
}

function OnGarageCreated(index) {
    GarageData[index][garageID] = cache_insert_id();
    Garage_Save(index);
    return 1;
}
Garage_Sync(index) {
    if(!Iter_Contains(Garage, index))
        return 0;

    if(IsValidDynamicPickup(GarageData[index][garagePickup])) 
        DestroyDynamicPickup(GarageData[index][garagePickup]);

    GarageData[index][garagePickup] = CreateDynamicPickup(19134, 23, GarageData[index][garageX], GarageData[index][garageY], GarageData[index][garageZ], -1, -1, -1, 20.0);


    if(IsValidDynamic3DTextLabel(GarageData[index][garageLabel])) {
        Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, GarageData[index][garageLabel], GarageData[index][garageX], GarageData[index][garageY], GarageData[index][garageZ]);
    }
    else GarageData[index][garageLabel] = CreateDynamic3DTextLabel(sprintf(""LIGHTBLUE"[ID:%d]\n"WHITE"Type "YELLOW"/garage "WHITE"to access public garage.", index), -1, GarageData[index][garageX], GarageData[index][garageY], GarageData[index][garageZ], 7.0, _, _, _, -1, -1, -1, 10.0);
    return 1;
}

Garage_Save(index) {
    if(!Iter_Contains(Garage, index))
        return 0;

    new query[412];
    mysql_format(sqlcon, query, sizeof(query), "UPDATE `garage` SET `PosX` = '%.4f', `PosY` = '%.4f', `PosZ` = '%.4f' WHERE `ID` = '%d'", 
        GarageData[index][garageX], 
        GarageData[index][garageY], 
        GarageData[index][garageZ],
        GarageData[index][garageID]
    );
    mysql_tquery(sqlcon, query);
    return 1;
}

Garage_Nearest(playerid, Float:rad = 5.0) {
    new idx = -1;
    foreach(new index : Garage) if(IsPlayerInRangeOfPoint(playerid, rad, GarageData[index][garageX], GarageData[index][garageY], GarageData[index][garageZ])) {
        idx = index;
        break;
    }
    return idx;
}

function Garage_Load() {

    new index = ITER_NONE;

    if(cache_num_rows()) {
        for(new i = 0; i < cache_num_rows(); i++) {

            if((index = Iter_Alloc(Garage)) != ITER_NONE) {
                cache_get_value_name_int(i, "ID", GarageData[index][garageID]);
                cache_get_value_name_float(i, "PosX", GarageData[index][garageX]);
                cache_get_value_name_float(i, "PosY", GarageData[index][garageY]);
                cache_get_value_name_float(i, "PosZ", GarageData[index][garageZ]);

                Garage_Sync(index);
            }

        }
    }
    printf("[GARAGE] Loaded %d public garage from database.", cache_num_rows());
    return 1;
}

function OnTakeVehicleGarage(playerid) {

    if(!cache_num_rows())
        return SendErrorMessage(playerid, "Tidak ada kendaraanmu pada garasi ini.");

    new str[512], count;
    for(new i = 0; i < cache_num_rows(); i++) {
        new model_id, plate[16], sql_id;

        cache_get_value_name_int(i, "vehModel", model_id);
        cache_get_value_name(i, "vehPlate", plate, 16);
        cache_get_value_name_int(i, "vehID", sql_id);

        strcat(str, sprintf("%d). %s (Plate: %s)\n", i + 1, ReturnVehicleModelName(model_id), plate));

        g_Selected_Vehicle_ID[playerid][count++] = sql_id;
    }
    ShowPlayerDialog(playerid, DIALOG_GARAGE_TAKE, DIALOG_STYLE_LIST, "Garage Take", str, "Take", "Close");
    return 1;
}
CMD:creategarage(playerid, params[]) {

    if(PlayerData[playerid][pAdmin] < 6)
        return PermissionError(playerid);

    new Float:x, Float:y, Float:z, index = ITER_NONE;
    GetPlayerPos(playerid, x, y, z);

    index = Garage_Create(x, y, z);

    if(index == ITER_NONE)
        return SendErrorMessage(playerid, "Cannot create more garage.");

    SendAdminAction(playerid, "You have successfully created garage %d.", index);
    return 1;
}

CMD:editgarage(playerid, params[]) {

    if(PlayerData[playerid][pAdmin] < 6)
        return PermissionError(playerid);

    
    new type[24], index;
    if(sscanf(params, "ds[24]", index, type))
        return SendSyntaxMessage(playerid, "/editgarage [garage id] [location]");

    if(!Iter_Contains(Garage, index))   
        return SendErrorMessage(playerid, "You have specified invalid garage.");

    if(!strcmp(type, "location", true)) {
        GetPlayerPos(playerid, GarageData[index][garageX], GarageData[index][garageY], GarageData[index][garageZ]);
        Garage_Save(index);
        Garage_Sync(index);

        SendAdminAction(playerid, "You have adjusted location of garage %d.", index);
    }
    return 1;
}

CMD:deletegarage(playerid, params[]) {

    if(PlayerData[playerid][pAdmin] < 6)
        return PermissionError(playerid);


    new index;

    if(sscanf(params, "d", index))
        return SendSyntaxMessage(playerid, "/deletegarage [garage id]");

    if(!Iter_Contains(Garage, index))
        return SendErrorMessage(playerid, "You have specified invalid garage.");


    mysql_tquery(sqlcon, sprintf("UPDATE `vehicle` SET `vehState` = '%d', `vehGarage` = '%d' WHERE `vehGarage` = '%d' AND `vehState` = '%d'", VEHICLE_STATE_GARAGE, GarageData[index][garageID],  GarageData[index][garageID], VEHICLE_STATE_GARAGE));
    mysql_tquery(sqlcon, sprintf("DELETE FROM `garage` WHERE `ID` = '%d'", GarageData[index][garageID]));
    if(IsValidDynamic3DTextLabel(GarageData[index][garageLabel]))
        DestroyDynamic3DTextLabel(GarageData[index][garageLabel]);

    if(IsValidDynamicPickup(GarageData[index][garagePickup]))
        DestroyDynamicPickup(GarageData[index][garagePickup]);

    Iter_Remove(Garage, index);
    SendAdminAction(playerid, "You have removed garage %d.", index);
    return 1;
}

CMD:garage(playerid, params[]) {

    if(Garage_Nearest(playerid) == -1)
        return SendErrorMessage(playerid, "Kamu tidak didekat garasi manapun.");


    ShowPlayerDialog(playerid, DIALOG_GARAGE, DIALOG_STYLE_LIST, "Public Garage", "Put vehicle\nTake vehicle", "Select", "Close");
    g_NearGarage[playerid] = Garage_Nearest(playerid);
    return 1;

}