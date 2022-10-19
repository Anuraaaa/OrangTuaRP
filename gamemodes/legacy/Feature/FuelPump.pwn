#include <YSI_Coding\y_hooks>

#define             MAX_PUMP                100

enum E_PUMP_DATA 
{
    pumpID,
    Float:pumpPos[4],
    pumpFuel,
    pumpBusiness,
    Text3D:pumpLabel,
    STREAMER_TAG_OBJECT:pumpObject,
};
new 
    PumpData[MAX_PUMP][E_PUMP_DATA],
    Iterator:Pump<MAX_PUMP>;

Pump_Create(bizid, Float:x, Float:y, Float:z, Float:a)
{
    new idx = -1;
    if((idx = Iter_Free(Pump)) != INVALID_ITERATOR_SLOT)
    {
        Iter_Add(Pump, idx);

        x += 5.0 * floatsin(-a, degrees);
        y += 5.0 * floatcos(-a, degrees);

        PumpData[idx][pumpFuel] = 3000;
        PumpData[idx][pumpPos][0] = x;
        PumpData[idx][pumpPos][1] = y;
        PumpData[idx][pumpPos][2] = z;
        PumpData[idx][pumpPos][3] = a;
        PumpData[idx][pumpBusiness] = BizData[bizid][bizID];

        PumpData[idx][pumpObject] = CreateDynamicObject(1676, x, y, z, 0.0, 0.0, a);
        mysql_tquery(sqlcon, "INSERT INTO `fuelpump` (`Fuel`) VALUES('100.0')", "Pump_OnCreated", "d", idx);
        return idx;
    }
    return -1;
}

Pump_Delete(idx, bool:remove_safe = false) {
    if(!Iter_Contains(Pump, idx))
        return 0;

    if(IsValidDynamic3DTextLabel(PumpData[idx][pumpLabel]))
        DestroyDynamic3DTextLabel(PumpData[idx][pumpLabel]);

    if(IsValidDynamicObject(PumpData[idx][pumpObject]))
        DestroyDynamicObject(PumpData[idx][pumpObject]);

    mysql_tquery(sqlcon, sprintf("DELETE FROM `fuelpump` WHERE `ID` = '%d'", PumpData[idx][pumpID]));

    PumpData[idx][pumpFuel] = 3000;
    PumpData[idx][pumpID]  = 0;
    PumpData[idx][pumpBusiness] = 0;

    if(remove_safe) {
        new next = idx;
        Iter_SafeRemove(Pump, next, idx);
    }
    else Iter_Remove(Pump, idx);
    return 1;
}
Pump_Sync(idx)
{
    if(!Iter_Contains(Pump, idx))
        return 0;

    if(IsValidDynamic3DTextLabel(PumpData[idx][pumpLabel]))
        DestroyDynamic3DTextLabel(PumpData[idx][pumpLabel]);

    new str[144];
    format(str, sizeof(str), "{AAC4E5}[ Fuel Pump %d ]\n{FFFFFF}Fuel left: {FFFF00}%d liter\n{FFFFFF}Gunakan /refuel untuk mengisi bahan bakar.", idx, PumpData[idx][pumpFuel]);
    PumpData[idx][pumpLabel] = CreateDynamic3DTextLabel(str, -1, PumpData[idx][pumpPos][0],  PumpData[idx][pumpPos][1],  PumpData[idx][pumpPos][2], 10.0, _, _, 0, -1, -1, -1, 10.0);
    
    if(!IsValidDynamicObject(PumpData[idx][pumpObject]))
        PumpData[idx][pumpObject] = CreateDynamicObject(1676, PumpData[idx][pumpPos][0],  PumpData[idx][pumpPos][1],  PumpData[idx][pumpPos][2], 0.0, 0.0,  PumpData[idx][pumpPos][3]);
    else
        Streamer_SetItemPos(STREAMER_TYPE_OBJECT, PumpData[idx][pumpObject], PumpData[idx][pumpPos][0],  PumpData[idx][pumpPos][1],  PumpData[idx][pumpPos][2]);

    return 1;
}

Pump_Save(idx) 
{
    new query[1212];
    mysql_format(sqlcon, query, sizeof(query), "UPDATE `fuelpump` SET `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f', `PosA` = '%f', `Fuel` = '%d', `Business` = '%d' WHERE `ID` = '%d'",
        PumpData[idx][pumpPos][0],
        PumpData[idx][pumpPos][1], 
        PumpData[idx][pumpPos][2], 
        PumpData[idx][pumpPos][3], 
        PumpData[idx][pumpFuel],
        PumpData[idx][pumpBusiness],
        PumpData[idx][pumpID]
    );
    mysql_tquery(sqlcon, query);
    return 1;
}

Pump_Nearest(playerid, Float:range = 5.0)
{
    new id = -1;
    foreach(new i : Pump) if(IsPlayerInRangeOfPoint(playerid, range, PumpData[i][pumpPos][0], PumpData[i][pumpPos][1], PumpData[i][pumpPos][2]))
    {
        id = i;
        break;
    }
    return id;
} 

FUNC::Pump_Load() 
{
    new idx, rows = cache_num_rows();
    if(rows)
    {
        forex(i, rows)
        {
            if((idx = Iter_Free(Pump)) != INVALID_ITERATOR_SLOT)
            {            
                Iter_Add(Pump, idx);
                PumpData[idx][pumpID] = cache_get_field_int(i, "ID");
                PumpData[idx][pumpPos][0] = cache_get_field_float(i, "PosX");
                PumpData[idx][pumpPos][1] = cache_get_field_float(i, "PosY");
                PumpData[idx][pumpPos][2] = cache_get_field_float(i, "PosZ");
                PumpData[idx][pumpPos][3] = cache_get_field_float(i, "PosA");
                PumpData[idx][pumpFuel] = cache_get_field_int(i, "Fuel");
                PumpData[idx][pumpBusiness] = cache_get_field_int(i, "Business");

                Pump_Sync(idx);
            }
        }
    }
    printf("[PUMP] Loaded %d Fuel Pump from database", rows);
    return 1;       
}

FUNC::Pump_OnCreated(idx) 
{
    PumpData[idx][pumpID] = cache_insert_id();
    Pump_Save(idx);
    Pump_Sync(idx);

    return 1;
}

Pump_GetBizID(real_id) {

    new ret = -1;
    for(new i = 0; i < MAX_BUSINESS; i++) if(BizData[i][bizExists] && BizData[i][bizID] == real_id) {
        ret = i;
        break;
    }
    return ret;
}
/* Callback */

hook OnBusinessDeleted(bizid) {

    foreach(new i : Pump) if(PumpData[i][pumpBusiness] == BizData[bizid][bizID]) {
        Pump_Delete(i, true);
    }
}

hook OnBusinessRefuel(bizid) {

    foreach(new i : Pump) if(PumpData[i][pumpBusiness] == BizData[bizid][bizID]) {

        PumpData[i][pumpFuel] = 3000;
        Pump_Sync(i);
        Pump_Save(i);
    }
}
/* Commands */

CMD:createpump(playerid, params[]) 
{
    if(PlayerData[playerid][pAdmin] < 5)
        return PermissionError(playerid);

    new idx, Float:x, Float:y, Float:z, Float:a, bizid;

    if(sscanf(params, "d", bizid))
        return SendSyntaxMessage(playerid, "/createpump [business id]");

    if(!BizData[bizid][bizExists])
        return SendErrorMessage(playerid, "You have specified invalid busines id.");

    if(BizData[bizid][bizType] != TYPE_247)
        return SendErrorMessage(playerid, "This command only for 24/7 or market business.");

    GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid, a);

    idx = Pump_Create(bizid, x, y, z, a);
    
    if(idx == -1)
        return SendErrorMessage(playerid, "This server cannot create more fuel pumps.");

    SendAdminMessage(X11_TOMATO, "AdmCmd: %s has created Fuel Pump ID %d.", GetUsername(playerid), idx);

    PlayerData[playerid][pEditType] = EDIT_PUMP;
    PlayerData[playerid][pEditing] = idx;

    EditDynamicObject(playerid, PumpData[idx][pumpObject]);
    return 1;
}

CMD:setpump(playerid, params[]) {

    if(PlayerData[playerid][pAdmin] < 5)
        return PermissionError(playerid);

    new index = -1;

    if(sscanf(params, "d", index))
        return SendSyntaxMessage(playerid, "/setpump [pump id]");

    if(!Iter_Contains(Pump, index))
        return SendErrorMessage(playerid, "Pump ID %d is doesn't exists.", index);

    PumpData[index][pumpFuel] = 3000;
    Pump_Sync(index);
    SendAdminAction(playerid, "Berhasil merestock pump %d.", index);
    return 1;
}

CMD:deletepump(playerid, params[]) {

    if(PlayerData[playerid][pAdmin] < 5)
        return PermissionError(playerid);

    new index = -1;

    if(sscanf(params, "d", index))
        return SendSyntaxMessage(playerid, "/deletepump [pump id]");

    if(!Iter_Contains(Pump, index))
        return SendErrorMessage(playerid, "Pump ID %d is doesn't exists.", index);

    Pump_Delete(index);
    SendAdminMessage(X11_TOMATO, "AdmCmd: %s has deleted Pump ID %d.", GetUsername(playerid), index);
    return 1;
}