#include <YSI_Coding\y_hooks>

#define             MAX_LISTED_DAMAGE           55

enum E_DAMAGE_DATA {
    bool:DAMAGE_EXISTS,
    DAMAGE_ID,
    DAMAGE_WEAPONID,
    DAMAGE_TIME,
    DAMAGE_BODYPART,
    DAMAGE_ISSUER,
    DAMAGE_AMOUNT
};
new
    DamageData[MAX_PLAYERS][MAX_LISTED_DAMAGE][E_DAMAGE_DATA];


Damage_GetSame(playerid, weaponid, bodypart) {

    new index = -1;
    for(new i = 0; i < MAX_LISTED_DAMAGE; i++) if(DamageData[playerid][i][DAMAGE_EXISTS]) {
        if(DamageData[playerid][i][DAMAGE_BODYPART] == bodypart && DamageData[playerid][i][DAMAGE_WEAPONID] == weaponid) {
            index  = i;
            break;
        }
    }
    return index;
}

Damage_GetFreeID(playerid) {
    new index = -1;
    for(new i = 0; i < MAX_LISTED_DAMAGE; i++) if(!DamageData[playerid][i][DAMAGE_EXISTS]) {
        index = i;
        break;
    }
    return index;
}

Damage_Add(playerid, weaponid, bodypart) {

    new
        id = -1;

    if((id = Damage_GetSame(playerid, weaponid, bodypart)) != -1) {
        DamageData[playerid][id][DAMAGE_AMOUNT]++;
        DamageData[playerid][id][DAMAGE_TIME] = gettime();
        
        Damage_Save(playerid, id);
        // Update the damagelog.

    }
    else {
        if((id = Damage_GetFreeID(playerid)) != -1) {

            DamageData[playerid][id][DAMAGE_WEAPONID] = weaponid;
            DamageData[playerid][id][DAMAGE_AMOUNT]++;
            DamageData[playerid][id][DAMAGE_BODYPART] = bodypart;
            DamageData[playerid][id][DAMAGE_TIME] = gettime();
            DamageData[playerid][id][DAMAGE_EXISTS] = true;

            mysql_tquery(sqlcon, sprintf("INSERT INTO `damagelog` (`PlayerID`) VALUES('%d')", PlayerData[playerid][pID]),"OnDamageAdded", "dd", playerid, id);

            // Issue new damagelog.
        }
    }

    return 1;
}

FUNC::OnDamageAdded(playerid, slot) {
    DamageData[playerid][slot][DAMAGE_ID] = cache_insert_id();
    Damage_Save(playerid, slot);

    return 1;
}

Damage_Save(playerid, slot) {
    new query[352];
    mysql_format(sqlcon, query, 512, "UPDATE `damagelog` SET `Amount` = '%d', `Time` = '%d', `Bodypart` = '%d', `Weaponid` = %d WHERE `ID` = '%d' LIMIT 1;",  
        DamageData[playerid][slot][DAMAGE_AMOUNT],
        DamageData[playerid][slot][DAMAGE_TIME],
        DamageData[playerid][slot][DAMAGE_BODYPART],
        DamageData[playerid][slot][DAMAGE_WEAPONID],
        DamageData[playerid][slot][DAMAGE_ID]
    );

    return mysql_tquery(sqlcon, query);
}

Damage_Reset(playerid) {
    for(new i = 0; i < MAX_LISTED_DAMAGE; i++) {
        DamageData[playerid][i][DAMAGE_AMOUNT] = 0;
        DamageData[playerid][i][DAMAGE_BODYPART] = 0;
        DamageData[playerid][i][DAMAGE_EXISTS] = false;
        DamageData[playerid][i][DAMAGE_TIME] = 0;
    }

    return mysql_tquery(sqlcon, sprintf("DELETE FROM `damagelog` WHERE `PlayerID` = '%d'", PlayerData[playerid][pID]));
}
GetBodyPartName(bodypart)
{
    new part[11];
    switch(bodypart)
    {
        case BODY_PART_TORSO: part = "Torso";
        case BODY_PART_GROIN: part = "Groin";
        case BODY_PART_LEFT_ARM: part = "Left Arm";
        case BODY_PART_RIGHT_ARM: part = "Right Arm";
        case BODY_PART_LEFT_LEG: part = "Left Leg";
        case BODY_PART_RIGHT_LEG: part = "Right Leg";
        case BODY_PART_HEAD: part = "Head";
        default: part = "None";
    }
    return part;
}

Damage_Count(playerid) {

    new count = 0;
    for(new i = 0; i < MAX_LISTED_DAMAGE; i++) if(DamageData[playerid][i][DAMAGE_EXISTS]) {
        count++;
    }
    return count;
}
Damage_Show(playerid, showto) {

    if(!IsPlayerConnected(showto)) 
        return 0;

    if(!Damage_Count(playerid))
        return SendErrorMessage(showto, "There is no damages on %s.", ReturnName(playerid));

    new string[1012];

    strcat(string, "Weapon\tBullet(s)\tBodypart\tLast Updated\n");
    for(new i = 0; i < MAX_LISTED_DAMAGE; i++) if(DamageData[playerid][i][DAMAGE_EXISTS]) {
        strcat(string, sprintf("%s\t%d bullet\t%s\t%s\n", ReturnWeaponName(DamageData[playerid][i][DAMAGE_WEAPONID]), DamageData[playerid][i][DAMAGE_AMOUNT], GetBodyPartName(DamageData[playerid][i][DAMAGE_BODYPART]), GetDuration(gettime() - DamageData[playerid][i][DAMAGE_TIME])));
    }
    return ShowPlayerDialog(showto, DIALOG_NONE, DIALOG_STYLE_TABLIST_HEADERS, sprintf("%s Damage Log", ReturnName(playerid)), string, "Close", "");
}

FUNC::OnDamageLoaded(playerid) {
    if(cache_num_rows()) {

        for(new i = 0; i < cache_num_rows(); i++) {
            DamageData[playerid][i][DAMAGE_EXISTS] = true;
            cache_get_value_name_int(i, "Amount", DamageData[playerid][i][DAMAGE_AMOUNT]);
            cache_get_value_name_int(i, "Bodypart", DamageData[playerid][i][DAMAGE_BODYPART]);
            cache_get_value_name_int(i, "Time", DamageData[playerid][i][DAMAGE_TIME]);
            cache_get_value_name_int(i, "Weaponid", DamageData[playerid][i][DAMAGE_WEAPONID]);
            cache_get_value_name_int(i, "ID", DamageData[playerid][i][DAMAGE_ID]);
        }
        printf("[PLAYER_DMG] Loaded %d damagelog from player %s.", cache_num_rows(), GetName(playerid, false));
    }
}
CMD:damages(playerid, params[]) {

    new targetid;
    if(sscanf(params, "u", targetid))
        return Damage_Show(playerid, playerid);

    if (targetid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, targetid, 5.0))
        return SendErrorMessage(playerid, "That player is disconnected or not near you.");

    Damage_Show(playerid, targetid);
    SendServerMessage(targetid, "%s memperlihatkan damagelog-nya kepadamu.", ReturnName(playerid));
    return 1;
}


/* Callback */

hook OnPlayerDamage(playerid, issuerid, Float:amount, weaponid, bodypart) {

    if(weaponid >= 22 && weaponid <= 38)
        Damage_Add(playerid, weaponid, bodypart);

    return 1;
}

hook OnPlayerLogin(playerid) {

    mysql_tquery(sqlcon, sprintf("SELECT * FROM `damagelog` WHERE `PlayerID` = '%d'", PlayerData[playerid][pID]), "OnDamageLoaded", "d", playerid);
}