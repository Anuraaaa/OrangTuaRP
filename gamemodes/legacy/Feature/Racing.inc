#include <YSI_Coding\y_hooks>

#define             MAX_RACING_CP             51

enum E_PLAYER_RACING {
    bool:raceExists,
    bool:raceStarted,
    raceWinner,
    raceFinish,
    Float:raceX[MAX_RACING_CP],
    Float:raceY[MAX_RACING_CP],
    Float:raceZ[MAX_RACING_CP],
    bool:racePosExists[MAX_RACING_CP],
    raceCountdown,
    Timer:raceTimer,
};

enum {
    RACE_CP_NORMAL = 0,
    RACE_CP_FINISH
};
new
    RaceData[MAX_PLAYERS][E_PLAYER_RACING],
    RaceWith[MAX_PLAYERS],
    InRace[MAX_PLAYERS],
    RaceIndex[MAX_PLAYERS];


Race_ResetData(playerid) {

    RaceData[playerid][raceExists] = false;
    RaceData[playerid][raceStarted] = false;
    RaceData[playerid][raceWinner] = INVALID_PLAYER_ID;
    RaceData[playerid][raceFinish] = -1;

    for(new i = 0; i < MAX_RACING_CP; i++) {
        RaceData[playerid][raceX][i] = 0.0;
        RaceData[playerid][raceY][i] = 0.0;
        RaceData[playerid][raceZ][i] = 0.0;
        RaceData[playerid][racePosExists][i] = false;
    }

    return 1;
}

Race_SetCheckpoint(playerid, index) {

    if(!IsPlayerConnected(playerid))
        return 0;

    new Float:x, Float:y, Float:z;

    if(IsPlayerInAnyVehicle(playerid))
        GetVehiclePos(GetPlayerVehicleID(playerid), x, y, z);
    else 
        GetPlayerPos(playerid, x, y, z);

    RaceData[playerid][raceX][index] = x;
    RaceData[playerid][raceY][index] = y;
    RaceData[playerid][raceZ][index] = z;
    RaceData[playerid][racePosExists][index] = true;

    SendServerMessage(playerid, "Checkpoint ke %d berhasil diatur!", index + 1);
    return 1;
}

IsPlayerHasRaceCP(playerid) {

    new is_have = 0;
    for(new i = 0; i < MAX_RACING_CP; i++) if(RaceData[playerid][racePosExists][i]) {
        is_have = 1;
        break;
    }
    return is_have;
}

Race_GetLastAvailableCP(playerid) {

    new index_result = -1;
    for(new i = 0; i < MAX_RACING_CP; i++) if(!RaceData[playerid][racePosExists][i]) {
        index_result = i;
        break;
    }
    return index_result;
}

Race_ResetPlayer(playerid) {

    InRace[playerid] = false;
    RaceIndex[playerid] = -1;
    RaceWith[playerid] = INVALID_PLAYER_ID;

    DisablePlayerRaceCheckpoint(playerid);
    return 1;
}
Race_ProgressCP(playerid) {

    new
        racing = RaceWith[playerid], 
        index = -1;

    index = RaceIndex[playerid];
    
    if(RaceIndex[playerid] == RaceData[racing][raceFinish]) {
        if(RaceData[racing][raceWinner] == INVALID_PLAYER_ID) 
            RaceData[racing][raceWinner] = playerid;

        if(RaceData[racing][raceWinner] == playerid) {
            foreach(new i : Player) if(InRace[i] && RaceWith[i] == racing) {
                SendClientMessageEx(i, X11_LIGHTBLUE, "(Race) "WHITE"Posisi finish pertama didapatkan oleh "YELLOW"%s", ReturnName(playerid));
            }
        }

        Race_ResetPlayer(playerid);

        if(Race_IsAnyPlayerInRace(racing) == INVALID_PLAYER_ID) {
            SendClientMessage(racing, X11_LIGHTBLUE, "(Race) "WHITE"Balapan selesai, semua player yang ikut balapan sudah memasuki checkpoint finish!");

            RaceData[racing][raceStarted] = false;
        }
    }
    else if(RaceIndex[playerid] == RaceData[racing][raceFinish] - 1) {
        SetPlayerRaceCheckpoint(playerid, 1, RaceData[racing][raceX][index],  RaceData[racing][raceY][index],  RaceData[racing][raceZ][index], 0.0, 0.0, 0.0, 5.0);
        RemovePlayerMapIcon(playerid, 98);
    }
    else {
        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
        SetPlayerRaceCheckpoint(playerid, 0, RaceData[racing][raceX][index],  RaceData[racing][raceY][index],  RaceData[racing][raceZ][index], RaceData[racing][raceX][index + 1],  RaceData[racing][raceY][index + 1],  RaceData[racing][raceZ][index + 1], 5.0);
        SetPlayerMapIcon(playerid, 98, RaceData[racing][raceX][index + 1],  RaceData[racing][raceY][index + 1],  RaceData[racing][raceZ][index + 1], 56, X11_WHITE, MAPICON_GLOBAL);
    }
    return 1;
}

Race_SetStart(playerid, time) {

    RaceData[playerid][raceStarted] = true;
    RaceData[playerid][raceTimer] = repeat Race_Countdown[1000](playerid);
    RaceData[playerid][raceCountdown] = time;

    return 1;
}

Race_IsAnyPlayerInRace(playerid) {
    new index = INVALID_PLAYER_ID;
    foreach(new i : Player) if(InRace[i] && RaceWith[i] == playerid) {

        index = i;
        break;
    }
    return index;
}
hook OnPlayerConnect(playerid) {

    Race_ResetData(playerid);

    RaceWith[playerid] = INVALID_PLAYER_ID;
    InRace[playerid] = false;
    RaceIndex[playerid] = -1;
}


hook OnPlayerEnterRaceCP(playerid) {
    if(InRace[playerid] && RaceWith[playerid] != INVALID_PLAYER_ID) {

        RaceIndex[playerid]++;
        Race_ProgressCP(playerid);
    }
}

hook OnPlayerDisconnectEx(playerid) {

    foreach(new i : Player) if(InRace[i] && RaceWith[i] == playerid) {

        if(i == playerid)
            continue;

        Race_ResetPlayer(i);
        SendServerMessage(playerid, "Penyelenggara balapan keluar dari server, balapan otomatis dihentikan.");
    }
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {
    if(dialogid == DIALOG_LOAD_RACE) {
        if(response) {

            new query[172];
            mysql_format(sqlcon, query, sizeof(query), "SELECT * FROM `race_cps` WHERE `RaceID` = '%d' ORDER BY `ID` ASC;", ListedItems[playerid][listitem]);
            mysql_tquery(sqlcon, query, "OnLoadRace", "d", playerid);
        }
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}
timer Race_Countdown[1000](playerid) {

    if(RaceData[playerid][raceCountdown] == 0) {
        foreach(new i : Player) if(RaceWith[i] == playerid) {
            GameTextForPlayer(i, "Start!", 3000, 3);
            PlayerPlaySound(i, 1057, 0,0,0);
            InRace[i] = true;
            RaceIndex[i] = 0;

            SetPlayerRaceCheckpoint(i, 0, RaceData[playerid][raceX][0], RaceData[playerid][raceY][0], RaceData[playerid][raceZ][0], RaceData[playerid][raceX][1], RaceData[playerid][raceY][1], RaceData[playerid][raceZ][1], 5.0);
            TogglePlayerControllable(i, 1);
        }

        stop RaceData[playerid][raceTimer];
    }
    else {

        RaceData[playerid][raceCountdown]--;
        foreach(new i : Player) if(RaceWith[i] == playerid) {
            GameTextForPlayer(i, sprintf("%d", RaceData[playerid][raceCountdown]), 1000, 3);
            PlayerPlaySound(i, 1056, 0,0,0);
        }
    }
}

function OnRaceListCreated(playerid) {
    
    new get_id = cache_insert_id();
    new string[512];

    for(new i = 0; i < 50; i++) if(RaceData[playerid][racePosExists][i]) {

        if(i == RaceData[playerid][raceFinish]) {

            mysql_format(sqlcon, string, sizeof(string), "INSERT INTO `race_cps` (`RaceID`, `Type`, `PosX`, `PosY`, `PosZ`, `CPIndex`) VALUES('%d', '%d', '%f', '%f', '%f', 'Index_%d')", get_id, RACE_CP_FINISH, RaceData[playerid][raceX][i], RaceData[playerid][raceY][i], RaceData[playerid][raceZ][i], i);
            mysql_tquery(sqlcon, string);
        } 
        else {
            mysql_format(sqlcon, string, sizeof(string), "INSERT INTO `race_cps` (`RaceID`, `Type`, `PosX`, `PosY`, `PosZ`, `CPIndex`) VALUES('%d', '%d', '%f', '%f', '%f', 'Index_%d')", get_id, RACE_CP_NORMAL, RaceData[playerid][raceX][i], RaceData[playerid][raceY][i], RaceData[playerid][raceZ][i], i);
            mysql_tquery(sqlcon, string);
        }
    }
    return 1;
}
/* Commands */

CMD:race(playerid, params[]) {
    
    new type[24], string[128];
        
    if(sscanf(params, "s[24]S()[128]", type, string))
        return SendSyntaxMessage(playerid, "/race [scp/finish/invite/kick/start/removefinish/leave]");


    if(!strcmp(type, "scp", true)) {

        new index,
            real_index;

        if(sscanf(string, "d", index))
            return SendSyntaxMessage(playerid, "/race [scp] [Checkpoint 1 - 50]"), SendClientMessage(playerid, -1, "INFO: Tidak wajib sampai 50, 50 hanya untuk limitasi maksimal checkpoint.");


        if(index < 1 || index > 50)
            return SendErrorMessage(playerid, "Invalid checkpoint index!");

        real_index = index - 1;

        if(index > 1 && !RaceData[playerid][racePosExists][real_index - 1])
            return SendErrorMessage(playerid, "Checkpoint ke %d masih belum ada! kamu harus set Checkpoint sebelumnya terlebih dahulu!", real_index);

        Race_SetCheckpoint(playerid, real_index);
    }
    else if(!strcmp(type, "save", true)) {

        if(!IsPlayerHasRaceCP(playerid))
            return SendErrorMessage(playerid, "Kamu belum mengatur checkpoint satupun!");

        if(RaceData[playerid][raceFinish] == -1)
            return SendErrorMessage(playerid, "Kamu belum mengatur checkpoint finish!");
            
        if(isnull(string))
            return SendSyntaxMessage(playerid, "/race [save] <name>");

        if(strlen(string) > 24)
            return SendErrorMessage(playerid, "Nama map balapan tidak boleh lebih dari 24 huruf.");

        new query[156];
        mysql_format(sqlcon, query, sizeof(query), "SELECT * FROM `race_list` WHERE `RaceName` = '%s'", string);
        mysql_tquery(sqlcon, query, "CheckRaceName", "ds", playerid, string);

    }
    else if(!strcmp(type, "load", true)) {

        new query[156];
        mysql_format(sqlcon, query, sizeof(query), "SELECT * FROM `race_list` WHERE `OwnerID` = '%d'", PlayerData[playerid][pID]);
        mysql_tquery(sqlcon, query, "OnLoadRaceCheck", "d", playerid);    
    }
    else if(!strcmp(type, "removefinish", true)) {

        if(RaceData[playerid][raceStarted])
            return SendErrorMessage(playerid, "Tidak bisa menggunakan ini ketika balapan sudah dimulai.");

        if(RaceData[playerid][raceFinish] == -1)
            return SendErrorMessage(playerid, "Kamu belum mengatur checkpoint finish.");

        SendServerMessage(playerid, "Kamu telah menghapus checkpoint finish.");

        new
            index = RaceData[playerid][raceFinish];

        RaceData[playerid][raceFinish] = -1;
        RaceData[playerid][raceX][index] = 0.0;
        RaceData[playerid][raceY][index] = 0.0;
        RaceData[playerid][raceZ][index] = 0.0;
        RaceData[playerid][racePosExists][index] = false;
    }
    else if(!strcmp(type, "kick", true)) {
        new targetid;

        if(sscanf(string, "u", targetid))
            return SendSyntaxMessage(playerid, "/race [kick] [playerid/PartOfName]");

        if(targetid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, targetid, 5.0))
            return SendErrorMessage(playerid, "You must near this player.");    

        if(RaceWith[targetid] != playerid)
            return SendErrorMessage(playerid, "Player tersebut tidak ada pada balapanmu!");

        Race_ResetPlayer(targetid); 
        SendServerMessage(playerid, "Kamu telah mengeluarkan %s dari balapanmu.", ReturnName(targetid));
        SendServerMessage(targetid, "Kamu telah dikeluarkan dari balapan oleh %s.", ReturnName(playerid));
    }
    else if(!strcmp(type, "leave", true)) {

        if(RaceWith[playerid] == INVALID_PLAYER_ID)
            return SendErrorMessage(playerid, "Kamu tidak berada pada balapan manapun.");

        if(RaceData[playerid][raceStarted])
            return SendErrorMessage(playerid, "Kamu tidak bisa keluar pada balapanmu sendiri!");

        
        Race_ResetPlayer(playerid);
        SendClientMessage(playerid, X11_LIGHTBLUE, "(Race) "WHITE"Kamu telah keluar dari balapan.");
    }
    else if(!strcmp(type, "invite", true)) {
        new targetid;

        if(sscanf(string, "u", targetid))
            return SendSyntaxMessage(playerid, "/race [invite] [playerid/PartOfName]");

        if(targetid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, targetid, 5.0))
            return SendErrorMessage(playerid, "You must near this player.");

        if(RaceWith[targetid] != INVALID_PLAYER_ID)
            return SendErrorMessage(playerid, "Player tersebut sudah pada balapan lain.");

        RaceWith[targetid] = playerid;
        SendServerMessage(playerid, "Kamu telah mengundang %s kedalam balapanmu.", ReturnName(targetid));
        SendServerMessage(targetid, "Kamu telah diundah oleh %s ke balapannya, gunakan \"/race leave\" untuk keluar.", ReturnName(playerid));
    }
    else if(!strcmp(type, "finish", true)) {

        if(!IsPlayerHasRaceCP(playerid))
            return SendErrorMessage(playerid, "Kamu belum mengatur checkpoint satupun!");

        if(RaceData[playerid][raceFinish] != -1) 
            return SendErrorMessage(playerid, "Kamu sudah mengatur Checkpoint finish! (/race removefinish terlebih dahulu)");
        new index = Race_GetLastAvailableCP(playerid),
            Float:x, Float:y, Float:z;

        if(index == -1)
            return SendErrorMessage(playerid, "Tidak dapat mengatur Checkpoint untuk finish, silahkan lapor ke Developer.");

        if(index == 1)
            return SendErrorMessage(playerid, "Tidak dapat membuat Finish, silahkan buat 1 Checkpoint lagi.");
            
        if(IsPlayerInAnyVehicle(playerid))
            GetVehiclePos(GetPlayerVehicleID(playerid), x, y, z);
        else 
            GetPlayerPos(playerid, x, y, z);
            
        RaceData[playerid][raceFinish] = index;
        RaceData[playerid][raceX][index] = x;
        RaceData[playerid][raceY][index] = y;
        RaceData[playerid][raceZ][index] = z;
        RaceData[playerid][racePosExists][index] = true;

        SendServerMessage(playerid, "Checkpoint finish berhasil diatur!");
    }
    else if(!strcmp(type, "start", true)) {

        if(!IsPlayerHasRaceCP(playerid))
            return SendErrorMessage(playerid, "Kamu belum mengatur checkpoint satupun!");

        if(RaceData[playerid][raceFinish] == -1)
            return SendErrorMessage(playerid, "Kamu belum mengatur checkpoint finish!");

        if(RaceData[playerid][raceStarted])
            return SendErrorMessage(playerid, "Balapan sudah dimulai!");
            
        new time, freeze;

        if(sscanf(string, "dd", time, freeze))
            return SendSyntaxMessage(playerid, "/race [start] [countdown (second)] [freeze = 0 | not freeze = 1]");

        if(time < 1 || time > 20)
            return SendErrorMessage(playerid, "Invalid time in second!");

        if(freeze < 0 || freeze > 1)
            return SendErrorMessage(playerid, "Invalid freeze option.");

        RaceWith[playerid] = playerid;
        Race_SetStart(playerid, time + 1);

        foreach(new i : Player) if(RaceWith[i] == playerid) {
            TogglePlayerControllable(i, freeze);
            SetCameraBehindPlayer(i);
            SendClientMessageEx(i, X11_YELLOW, "(Race) "WHITE"%s telah menginisiasikan untuk memulai balapan dalam %d detik.", ReturnName(playerid), time);
        }
    }
    return 1;
}

function OnLoadRaceCheck(playerid) {
    new e_str[512], count = 0;
    if(cache_num_rows()) {
        for(new i = 0; i < cache_num_rows(); i++) {
            new race_name[24], build_date[26], id;
            cache_get_value_name(i, "RaceName", race_name);
            cache_get_value_name(i, "CreationDate", build_date);
            id = cache_get_field_int(i, "ID");

            strcat(e_str, sprintf("%s\t%s\n", race_name, build_date));

            ListedItems[playerid][count++] = id;
        }
        ShowPlayerDialog(playerid, DIALOG_LOAD_RACE, DIALOG_STYLE_TABLIST, "Race List", e_str, "Load", "Close");
    }
    return 1;
}

function CheckRaceName(playerid, name[]) {
    if(cache_num_rows()) {
        SendErrorMessage(playerid, "Nama map ini sudah digunakan!");
    }
    else {
        new query[352];
        mysql_format(sqlcon, query, sizeof(query), "INSERT INTO `race_list` (`OwnerID`, `RaceName`, `CreationDate`) VALUES('%d','%e','%e')", PlayerData[playerid][pID], name, ReturnDate(false));
        mysql_tquery(sqlcon, query, "OnRaceListCreated", "d", playerid);
    }
    return 1;
}

function OnLoadRace(playerid) {
    if(cache_num_rows()) {

        RaceData[playerid][raceFinish] = -1;

        for(new i = 0; i < MAX_RACING_CP; i++) {
            RaceData[playerid][raceX][i] = 0.0;
            RaceData[playerid][raceY][i] = 0.0;
            RaceData[playerid][raceZ][i] = 0.0;
            RaceData[playerid][racePosExists][i] = false;
        }

        for(new i = 0; i < cache_num_rows(); i++) {
            new race_idx[16], type = cache_get_field_int(i, "Type"), 
                Float:x,
                Float:y,
                Float:z
            ;
            cache_get_value_name(i, "CPIndex", race_idx, sizeof(race_idx));
            cache_get_value_name_float(i, "PosX", x);
            cache_get_value_name_float(i, "PosY", y);
            cache_get_value_name_float(i, "PosZ", z);

            RaceData[playerid][raceX][i] = x;
            RaceData[playerid][raceY][i] = y;
            RaceData[playerid][raceZ][i] = z;
            RaceData[playerid][racePosExists][i] = true;

            if(type == RACE_CP_FINISH) {
                RaceData[playerid][raceFinish] = i;
            }
        }
        SendClientMessage(playerid, X11_YELLOW, "(Race) "WHITE"Kamu berhasil me-load map race.");
    }
    return 1;
}