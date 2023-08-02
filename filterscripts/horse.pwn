#include <a_samp>
#include <YSI_Data\y_iterate>
#include <YSI_Coding\y_timers>
#include <streamer>
#include <colandreas>
#include <izcmd>

#define FILTERSCRIPT


#define MAX_HORSES      MAX_PLAYERS
#define HORSE_INDEX     3
#define function %0(%1)          forward%0(%1); public%0(%1)

enum E_HORSE_DATA
{
    horseID,
    Float:horsePos[6],
    horseRider,
    horseOwner,
    STREAMER_TAG_OBJECT:horseObject,
    horseSpeed,
    Float:horseEnergy
};
new
    HorseData[MAX_HORSES][E_HORSE_DATA],
    Iterator:Horse<MAX_HORSES>,
    RidingHorse[MAX_PLAYERS];

Horse_Create(Float:x, Float:y, Float:z, Float:a)
{
    new horseid;
    if((horseid = Iter_Free(Horse)) != INVALID_ITERATOR_SLOT)
    {
        Iter_Add(Horse, horseid);

        CA_FindZ_For2DCoord(x, y, z);
        HorseData[horseid][horseOwner] = -1;
        HorseData[horseid][horseRider] = INVALID_PLAYER_ID;
        HorseData[horseid][horsePos][0] = x;
        HorseData[horseid][horsePos][1] = y;
        HorseData[horseid][horsePos][2] = z-0.2;
        HorseData[horseid][horsePos][3] = 0.0;
        HorseData[horseid][horsePos][4] = 0.0;
        HorseData[horseid][horsePos][5] = a;
        HorseData[horseid][horseObject] = CreateDynamicObject(11733, x, y, z-0.24, 0.0, 0.0, a);
        HorseData[horseid][horseEnergy] = 20.0;
        //mysql_tquery(sqldata, "INSERT INTO `horse` (`Owner`) VALUES('-1')", "Horse_OnCreated", "d", horseid);
        return horseid;
    }
    return -1;
}

function Horse_OnCreated(id)
{
    if(!Iter_Contains(Horse, id))
        return 0;

    return 1;
}

GetPlayerSpeed(playerid, bool:kmh = false)
{
    new 
        Float:Vx,
        Float:Vy,
        Float:Vz,
        Float:rtn;

    if(IsPlayerInAnyVehicle(playerid)) {
        GetVehicleVelocity(GetPlayerVehicleID(playerid), Vx, Vy, Vz);
    } else {
        GetPlayerVelocity(playerid, Vx, Vy, Vz);        
    }

    rtn = floatsqroot(floatabs(floatpower(Vx + Vy + Vz, 2)));
    return kmh ? floatround(rtn * 100 * 1.61) : floatround(rtn * 100);
}

Horse_GetSpeed(horseid) {
    return HorseData[horseid][horseSpeed];
}

Horse_GetRider(horseid) {
    return HorseData[horseid][horseRider];
}
Horse_GetNearby(playerid)
{
    new
        horseid = -1;

    foreach(new i : Horse) if(HorseData[i][horseRider] == INVALID_PLAYER_ID)
    {
        if(IsPlayerInRangeOfPoint(playerid, 3.0, HorseData[i][horsePos][0], HorseData[i][horsePos][1], HorseData[i][horsePos][2]))
        {
            horseid = i;
            break;
        }
    }
    return horseid;
}

timer AttachHorseObject[1000](playerid) {
    
    if(RidingHorse[playerid] != -1)
        SetPlayerAttachedObject(playerid, HORSE_INDEX, 11733, 5, -0.627999, 1.480000, -0.126000, 93.399879, 1.999998, 77.299987, 1.103000, 1.112997, 1.014999);
    
    return 1;
}

public OnFilterScriptInit() {
    CA_Init();

    for(new i = 0; i < MAX_PLAYERS; i++) if(IsPlayerConnected(i)) {
        RidingHorse[i] = -1;
    }
}
public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{

    if(newkeys & KEY_SECONDARY_ATTACK)
    {
        if(RidingHorse[playerid] != -1)
        {
            new idx = RidingHorse[playerid],
                Float:x, Float:y, Float:z, Float:a;

            ClearAnimations(playerid, 1);

            GetPlayerPos(playerid, x, y, z);
            GetPlayerFacingAngle(playerid, a);

            CA_FindZ_For2DCoord(x, y, z);

            SetPlayerPos(playerid, x + 1.0, y, z + 0.45);
            SetPlayerFacingAngle(playerid, a);
            SetCameraBehindPlayer(playerid);

            RemovePlayerAttachedObject(playerid, HORSE_INDEX);

            HorseData[idx][horsePos][0] = x;
            HorseData[idx][horsePos][1] = y;
            HorseData[idx][horsePos][2] = z-0.24;
            HorseData[idx][horsePos][3] = 0.0;
            HorseData[idx][horsePos][4] = 0.0;
            HorseData[idx][horsePos][5] = a;

            HorseData[idx][horseObject] = CreateDynamicObject(11733, HorseData[idx][horsePos][0], HorseData[idx][horsePos][1], HorseData[idx][horsePos][2], HorseData[idx][horsePos][3], HorseData[idx][horsePos][4], HorseData[idx][horsePos][5] - 180.0);
            HorseData[idx][horseRider] = INVALID_PLAYER_ID;
            RidingHorse[playerid] = -1;

            Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
        }
        else
        {

            if(Horse_GetNearby(playerid) != -1)
            {
                new 
                    idx = Horse_GetNearby(playerid),
                    Float:x, Float:y, Float:z;

                GetPlayerPos(playerid, x, y, z);

                HorseData[idx][horseRider] = playerid;

                if(IsValidDynamicObject(HorseData[idx][horseObject]))
                    DestroyDynamicObject(HorseData[idx][horseObject]);

                CA_FindZ_For2DCoord(x, y, z);
                SetPlayerFacingAngle(playerid, HorseData[idx][horsePos][5]);
                
                ApplyAnimation(playerid, "BIKED", "BIKED_RIDE", 4.1, 1, 1, 1, 1, 0, 1);
                defer AttachHorseObject[1000](playerid);

                RidingHorse[playerid] = idx;

            }
        }
    }
    return 1;
}

public OnPlayerUpdate(playerid) {
    if(RidingHorse[playerid] != -1)
    {

        new
            k, ud, lr,
            Float:angle,
            Float:forwd,
            horse_id = - 1,
            Float:final_speed;

        horse_id = RidingHorse[playerid];

        final_speed = 0.5;

        GetPlayerKeys(playerid, k, ud, lr);
        GetPlayerFacingAngle(playerid, angle);

        if(ud == KEY_UP) {
            forwd = final_speed;

            new Float:move[3];

            move[0] = forwd*floatsin(-angle, degrees);
            move[1] = forwd*floatcos(-angle, degrees);

            CA_FindZ_For2DCoord(move[0], move[1], move[2]);
            SetPlayerVelocity(playerid, move[0], move[1], 0);
        }

        if(lr == KEY_LEFT)
            SetPlayerFacingAngle(playerid, angle + 2.0);

        else if(lr == KEY_RIGHT)
            SetPlayerFacingAngle(playerid, angle - 2.0);

        new Float:x, Float:y, Float:z;
        GetPlayerPos(playerid, x, y, z);
        CA_FindZ_For2DCoord(x, y, z);

        HorseData[horse_id][horseSpeed] = GetPlayerSpeed(playerid);
        HorseData[horse_id][horsePos][0] = x;
        HorseData[horse_id][horsePos][1] = y;
        HorseData[horse_id][horsePos][2] = z;
	}
    return 1;
}
ptask RideHorseCheck[1000](playerid)
{

    if(RidingHorse[playerid] == -1)
        return 0;

    if(GetPlayerAnimationIndex(playerid) != 72)
        ApplyAnimation(playerid, "BIKED", "BIKED_RIDE", 4.1, 1, 1, 1, 1, 0, 1);

    return 1;
}

CMD:createhorse(playerid, params[])
{
    new Float:x, Float:y, Float:z, Float:a;
    GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid, a);

    new idx = Horse_Create(x, y, z, a);

    if(idx == -1)
        return SendClientMessage(playerid, -1, "This server cannot create more horses!");

    SetPlayerPos(playerid, x, y + 1, z);
    return 1;
}