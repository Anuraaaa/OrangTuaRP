#include <YSI_Coding\y_hooks>

new
    bool:IsMining[MAX_PLAYERS] = {false, ...},
    MinerIndex[MAX_PLAYERS] = {0, ...},
    MinedRock[MAX_PLAYERS];

new const rock_names[][] = {"None", ""BROWN"Bronze", ""BROWN"Bronze", ""GREY"Silver", ""GOLD"Gold", ""CYAN"Diamond"};

hook OnPlayerConnect(playerid) {
    IsMining[playerid] = false;
    MinerIndex[playerid] = 0;
    MinedRock[playerid] = -1;

}

hook OnPlayerEnterCheckpoint(playerid) {
    if(MinerIndex[playerid] == 1 && IsPlayerInRangeOfPoint(playerid, 5.0, -1332.8300,2518.1953,87.0469)) {

        MinerIndex[playerid] = 2;

        ApplyAnimation(playerid, "CARRY", "null", 4.0, 0, 0, 0, 0, 0);
        ApplyAnimation(playerid, "CARRY", "putdwn", 4.0, 0, 0, 0, 0, 0);

        RemovePlayerAttachedObject(playerid, 9);

        DisablePlayerCheckpoint(playerid);

        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        TogglePlayerControllable(playerid, 0);

        ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
        StartPlayerLoadingBar(playerid, 50, "Processing_Rock...", 300, "OnRockProgress");

        SetPlayerFace(playerid, -1332.8300,2518.1953);

        SetCameraBehindPlayer(playerid);
    }
    if(MinerIndex[playerid] == 3 && IsPlayerInRangeOfPoint(playerid, 5.0, -1299.5569,2549.2720,87.5599)) {

        DisablePlayerCheckpoint(playerid);

        MinerIndex[playerid] = 4;
        
        ApplyAnimation(playerid, "CARRY", "liftup", 4.1, 0, 0, 0, 0, 0, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);

        new hasil_tambang = random(5) + 1;
        switch(hasil_tambang) {
            case 1, 2: SetPlayerAttachedObject(playerid, 9, 2936, 5, 0.105, 0.086, 0.22, -80.3, 3.3, 28.7, 0.35, 0.35, 0.35, RGBAToARGB(X11_BROWN));
            case 3: SetPlayerAttachedObject(playerid, 9, 2936, 5, 0.105, 0.086, 0.22, -80.3, 3.3, 28.7, 0.35, 0.35, 0.35, RGBAToARGB(X11_GREY));
            case 4: SetPlayerAttachedObject(playerid, 9, 2936, 5, 0.105, 0.086, 0.22, -80.3, 3.3, 28.7, 0.35, 0.35, 0.35, RGBAToARGB(X11_GOLD));
            case 5: SetPlayerAttachedObject(playerid, 9, 2936, 5, 0.105, 0.086, 0.22, -80.3, 3.3, 28.7, 0.35, 0.35, 0.35, RGBAToARGB(X11_CYAN));
        }

        SetPVarInt(playerid, "HasilTambang", hasil_tambang);

        SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Miner) "WHITE"Kamu berhasil mendapatkan %s "WHITE"! antarkan ke Checkpoint untuk mendapatkan upah.", rock_names[hasil_tambang]);
        SetPlayerCheckpoint(playerid, -1304.1875,2491.8530,87.1437, 3.0);


    }
    if(MinerIndex[playerid] == 4 && IsPlayerInRangeOfPoint(playerid, 5.0, -1304.1875,2491.8530,87.1437)) {

        MinerIndex[playerid] = 0;
        DisablePlayerCheckpoint(playerid);

        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        ApplyAnimation(playerid, "CARRY", "null", 4.0, 0, 0, 0, 0, 0);
        ApplyAnimation(playerid, "CARRY", "putdwn", 4.0, 0, 0, 0, 0, 0);

        RemovePlayerAttachedObject(playerid, 9);

        if(StockData[stockRock] < 500) {

            StockData[stockRock]++;

            new rock_type = GetPVarInt(playerid, "HasilTambang"),
                rock_price[] = {0, 1000, 1000, 2500, 5000, 10000},
                gaji = 0,
                bonus;

            switch(rock_type) {
                case 1: {
                    bonus = RandomEx(1, 500);
                }
                case 2: {
                    bonus = RandomEx(1, 1500);
                }
                case 3: {
                    bonus = RandomEx(1, 2500);
                }
                case 4: {
                    bonus = RandomEx(1, 4000);
                }
            }
            gaji = rock_price[rock_type] + bonus;

            GiveMoney(playerid, gaji, "Miner");

            SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Miner) "WHITE"Kamu berhasil mengantarkan batu dengan tipe %s "WHITE"dan mendapatkan "GREEN"$%s"WHITE"!", rock_names[rock_type], FormatNumber(gaji));

            UpdateServerStock(SERVER_STOCK_ROCK);
        }
        else {
            SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Miner) "WHITE"Stock batu sedang penuh! kamu tidak mendapatkan apa-apa.");
        }
        DeletePVar(playerid, "HasilTambang");

        PlayerData[playerid][pThirst] -= 2.0;

        PlayerData[playerid][pMineDelay] = 30;

        MinedRock[playerid] = -1;
    }
}

hook OnPlayerDisconnectEx(playerid) {
    if(MinedRock[playerid] != -1) {

        RockData[MinedRock[playerid]][rockMined] = INVALID_PLAYER_ID;
        RockData[MinedRock[playerid]][rockTime] = 0;

    }
}
CMD:mine(playerid, params[]) {

    if(!CheckPlayerJob(playerid, JOB_MINER))
        return SendErrorMessage(playerid, "Kamu bukan seorang miner.");

    if(IsHungerOrThirst(playerid))
        return SendErrorMessage(playerid, "Kamu terlalu lelah untuk bekerja.");

    if(PlayerData[playerid][pMineDelay])
        return SendErrorMessage(playerid, "Tunggu %d detik untuk menambang kembali.", PlayerData[playerid][pMineDelay]);

    if(MinerIndex[playerid]) {
        return SendErrorMessage(playerid, "Kamu sedang bekerja!");
    }
    new rock_id;

    if((rock_id = Rock_Nearest(playerid)) != -1) {

        if(RockData[rock_id][rockTime] > 0)
            return SendErrorMessage(playerid, "Batu ini masih Cooldown!");

        if(RockData[rock_id][rockMined] != INVALID_PLAYER_ID)
            return SendErrorMessage(playerid, "Batu ini sedang ditambang orang lain!");

        MinedRock[playerid] = rock_id;
        TogglePlayerControllable(playerid, 0);
        IsMining[playerid] = true;
        RockData[rock_id][rockMined] = playerid;
        StartPlayerLoadingBar(playerid, 100, "Mining_Progress..", 50, "OnRockMined");
        ApplyAnimation(playerid, "CHAINSAW", "WEAPON_csawlo", 4.1, 1, 0, 0, 0, 0, 1);
        GiveWeaponToPlayer(playerid, WEAPON_SHOVEL, 1, 1);
        SetPlayerArmedWeapon(playerid, WEAPON_SHOVEL);

        PlayerData[playerid][pThirst] -= 2.0;

        SetCameraBehindPlayer(playerid);

        SetPlayerFace(playerid, RockData[rock_id][rockX], RockData[rock_id][rockY]);
    }
    return 1;
}

function OnRockMined(playerid) {


    new id = MinedRock[playerid];

    RockData[id][rockMined] = INVALID_PLAYER_ID;
    RockData[id][rockTime] = 900;
    
    if(!IsMining[playerid]) {
        return 0;
    }

    IsMining[playerid] = false;
    MinerIndex[playerid] = 1;

    TogglePlayerControllable(playerid, 1);

    ResetWeapon(playerid, WEAPON_SHOVEL);
    SetPlayerArmedWeapon(playerid, 0);

    ClearAnimations(playerid, 1);
    SetPlayerArmedWeapon(playerid, 0);
    SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Miner) "WHITE"Kamu berhasil menambang batu! antarkan batu ke checkpoint.");

    ApplyAnimation(playerid, "CARRY", "liftup", 4.1, 0, 0, 0, 0, 0, 1);
    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
    
    SetPlayerCheckpoint(playerid, -1332.8300, 2518.1953, 87.0469, 1.5);

    Streamer_SetItemPos(STREAMER_TYPE_OBJECT, RockData[id][rockObject], RockData[id][rockX], RockData[id][rockY], RockData[id][rockZ] - 15.0);
    Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, RockData[id][rockText],  RockData[id][rockX], RockData[id][rockY], RockData[id][rockZ] - 15.0);


    SetPlayerAttachedObject(playerid, 9, 2936, 5, 0.105, 0.086, 0.22, -80.3, 3.3, 28.7, 0.35, 0.35, 0.35);
    return 1;
}

function OnRockProgress(playerid) {

    if(MinerIndex[playerid] != 2)
        return 0;

    MinerIndex[playerid] = 3;
    TogglePlayerControllable(playerid, 1);
    ClearAnimations(playerid, 1);

    SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Miner) "WHITE"Batu selesai diproses! pergi ke Checkpoint untuk mengambil batu.");
    SetPlayerCheckpoint(playerid, -1299.5569,2549.2720,87.5599, 2.0);
    return 1;
}