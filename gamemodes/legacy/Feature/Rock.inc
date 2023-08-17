#include <YSI_Coding\y_hooks>

#define                 MAX_ROCK                500

enum E_ROCK_DATA {
    rockID,
    rockTime,
    rockMined,
    Float:rockX,
    Float:rockY,
    Float:rockZ,
    STREAMER_TAG_OBJECT:rockObject,
    Text3D:rockText
};
new
    RockData[MAX_ROCK][E_ROCK_DATA],
    Iterator:Rock<MAX_ROCK>;

hook OnGameModeInit() {

    if (IsSQLConnected()) {
        Iter_Init(Rock);
		mysql_tquery(sqlcon, "SELECT * FROM `rock`", "Rock_Load", "");
    }
}

hook OnGameModeExit() {

    if (IsSQLConnected()) {
        Iter_Clear(Rock);
    }
}

Rock_Create(Float:x, Float:y, Float:z) {
    new id = INVALID_ITERATOR_SLOT;

    if((id = Iter_Alloc(Rock)) != INVALID_ITERATOR_SLOT) {

        RockData[id][rockX] = x + 1.0;
        RockData[id][rockY] = y;
        RockData[id][rockZ] = z;
        RockData[id][rockMined] = INVALID_PLAYER_ID;
        RockData[id][rockTime] = 0;

        Rock_Sync(id);

        mysql_tquery(sqlcon, "INSERT INTO `rock` (`RockX`) VALUES(0)", "OnRockCreated", "d", id);
    }
    return id;
}

Rock_Save(id) {
    if(!Iter_Contains(Rock, id))
        return 0;

    new query[354];
    mysql_format(sqlcon, query, sizeof(query), "UPDATE `rock` SET `RockX` = '%.4f', `RockY` = '%.4f', `RockZ` = '%.4f' WHERE `ID` = '%d'", 
        RockData[id][rockX],
        RockData[id][rockY],
        RockData[id][rockZ],
        RockData[id][rockID]
    );
    return mysql_tquery(sqlcon, query);
}

function Rock_Load(id) {

    if(cache_num_rows()) {
        for(new i = 0; i < cache_num_rows(); i++) {
            Iter_Add(Rock, i);

            cache_get_value_name_int(i, "ID", RockData[i][rockID]);
            cache_get_value_name_float(i, "RockX", RockData[i][rockX]);
            cache_get_value_name_float(i, "RockY", RockData[i][rockY]);
            cache_get_value_name_float(i, "RockZ", RockData[i][rockZ]);

            RockData[i][rockMined] = INVALID_PLAYER_ID;
            RockData[i][rockTime] = 0;

            Rock_Sync(i);
        }
    }
    printf("[ROCK] Loaded %d rock from database.", cache_num_rows());
    return 1;
}
function OnRockCreated(id) {
    RockData[id][rockID] = cache_insert_id();
    Rock_Save(id);
    
    return 1;
}

Rock_Nearest(playerid) {
    new index = -1;
    foreach(new i : Rock) if(IsValidDynamicObject(RockData[i][rockObject]) && IsPlayerInRangeOfPoint(playerid, 2.0, RockData[i][rockX], RockData[i][rockY], RockData[i][rockZ])) {
        index = i;
        break;
    }
    return index;
}
Rock_Sync(id) {
    if(!Iter_Contains(Rock, id))
        return 0;

    if(!IsValidDynamicObject(RockData[id][rockObject])) {
        RockData[id][rockObject] = CreateDynamicObject(3929, RockData[id][rockX], RockData[id][rockY], RockData[id][rockZ], 0.0, 0.0, 0.0, -1, -1, -1, 30.0, 30.0);
    }
    else {
        Streamer_SetItemPos(STREAMER_TYPE_OBJECT, RockData[id][rockObject], RockData[id][rockX], RockData[id][rockY], RockData[id][rockZ]);
    }

    if(!IsValidDynamic3DTextLabel(RockData[id][rockText])) {
        RockData[id][rockText] = CreateDynamic3DTextLabel(sprintf(""LIGHTBLUE"[Rock: %d]\n"WHITE"Type "YELLOW"/mine "WHITE"to begin.", id), -1, RockData[id][rockX], RockData[id][rockY], RockData[id][rockZ], 5.0);
    }
    else Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, RockData[id][rockText], RockData[id][rockX], RockData[id][rockY], RockData[id][rockZ]);

    return 1;
}

CMD:createrock(playerid, params[]) {
    if(PlayerData[playerid][pAdmin] < 6) 
        return PermissionError(playerid);

    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);

    new rock_id = Rock_Create(x, y, z);

    if(rock_id == INVALID_ITERATOR_SLOT) 
        return SendErrorMessage(playerid, "Tidak dapat membuat lebih banyak batu.");

    EditDynamicObject(playerid, RockData[rock_id][rockObject]);
    PlayerData[playerid][pEditing] = rock_id;
    PlayerData[playerid][pEditType] = EDIT_ROCK;
    SendAdminAction(playerid, "You have created Rock ID: %d.", rock_id);
    return 1;
}

CMD:destroyrock(playerid, params[]) {

    if(PlayerData[playerid][pAdmin] < 6) 
        return PermissionError(playerid);

    new id;
    if(sscanf(params, "d", id))
        return SendSyntaxMessage(playerid, "/destroyrock [rock id]");

    if(!Iter_Contains(Rock, id))
        return SendErrorMessage(playerid, "Invalid rock ID.");

    if(IsValidDynamicObject(RockData[id][rockObject]))
        DestroyDynamicObject(RockData[id][rockObject]);

    if(IsValidDynamic3DTextLabel(RockData[id][rockText]))
        DestroyDynamic3DTextLabel(RockData[id][rockText]);

    RockData[id][rockObject] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
    
    mysql_tquery(sqlcon, sprintf("DELETE FROM `rock` WHERE `ID` = '%d'", RockData[id][rockID]));

    Iter_Remove(Rock, id);

    SendAdminAction(playerid, "You have destroyed Rock ID: %d", id);   

    return 1;
}

task OnRockUpdate[1000]() {
    foreach(new i : Rock) {
        if(RockData[i][rockTime]) {
            if(--RockData[i][rockTime] == 0) {
                Rock_Sync(i);
                RockData[i][rockMined] = INVALID_PLAYER_ID;
                RockData[i][rockTime] = 0;
            }
        }
    }
    return 1;
}