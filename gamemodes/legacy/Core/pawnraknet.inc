#include <YSI_Coding\y_hooks>
#include <Pawn.RakNet>

#define ANTICHEAT_VEHICLE_TOLERANCE_TIME (2000)
#define MIN_DEPTH_VEHICLE_DROWNED        (0.5)

static ARQ_callback[MAX_PLAYERS];
new
    countNotification[MAX_PLAYERS],
    countNotificationLastCheck[MAX_PLAYERS]
;

hook OnPlayerConnect(playerid)
{
    countNotification[playerid] = 0;
}
hook OnPlayerDisconnect(playerid, reason)
{
    countNotification[playerid] = 0;
}

task ResetNotification[1000]()
{
    foreach(new i : Player)
    {
        if ((GetTickCount() - countNotificationLastCheck[i]) >= ANTICHEAT_VEHICLE_TOLERANCE_TIME)
        {
            countNotification[i] = 0;
        }
    }
    return 1;
}

timer Anticheat_RespawnVehicle[1000](vehicleid)
{
    SetVehicleToRespawn(vehicleid);
    return 1;
}

timer Anticheat_IsVehicleDrown[1000](playerid, vehicleid)
{
    if (!IsPlayerConnected(playerid))
    {
        return 1;
    }

    if (!IsValidVehicle(vehicleid))
    {
        return 1;
    }

    new
        Float:x,
        Float:y,
        Float:z_samp, // Untuk menyimpan ketinggian berdasarkan koordinat dari SA-MP
        Float:z_mapandreas, // Untuk menyimpan ketinggian berdasarkan koordinat dari ColAndreas
        Float:vehiclehealth
    ;

    GetVehiclePos(vehicleid, x, y, z_samp);
    CA_FindZ_For2DCoord(x, y, z_mapandreas);
    GetVehicleHealth(vehicleid, vehiclehealth);

    if (z_mapandreas > 0.00)
    {
        if(countNotification[playerid] < 5)
        {
            countNotification[playerid]++;
            countNotificationLastCheck[playerid] = GetTickCount();
        }
        else
        {
            Kick(playerid);
        }

        return 1;
    }

    if (IsABoat(vehicleid))
    {
        return 1;
    }

    new Float:delta = floatabs(z_samp);

    if (delta > MIN_DEPTH_VEHICLE_DROWNED)
    {
        CallRemoteFunction("OnVehicleDeath", "dd", vehicleid, playerid);
        defer Anticheat_RespawnVehicle(vehicleid);
    }
    else
    {
        defer Anticheat_IsVehicleDrown(playerid, vehicleid);
    }

    return 1;
}
public OnIncomingPacket(playerid, packetid, BitStream:bs) {
    if(packetid == 0xCF)
    {
        new Float:OPTUD_w, Float:OPTUD_x, Float:OPTUD_y, Float:OPTUD_z;
        
        BS_SetReadOffset(bs, 0x98);
        
        BS_ReadValue(
            bs,
            PR_FLOAT, OPTUD_w,
            PR_FLOAT, OPTUD_x,
            PR_FLOAT, OPTUD_y,
            PR_FLOAT, OPTUD_z
        );
            
        BS_ResetReadPointer(bs);
            
        new const Float:OPTUD_angle = atan2(2 * ((OPTUD_y * OPTUD_z) + (OPTUD_w * OPTUD_x)), (OPTUD_w * OPTUD_w) - (OPTUD_x * OPTUD_x) - (OPTUD_y * OPTUD_y) + (OPTUD_z * OPTUD_z));
        
        if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_NONE) 
        {
            if((OPTUD_angle > 85.0 || OPTUD_angle < -85.0) && OPTUD_angle == OPTUD_angle)
            {
                if(gettime() > ARQ_callback[playerid])
                {
                    ARQ_callback[playerid] = gettime();
                    CallLocalFunction("OnAntiCheatTurnUpsideDown", "df", playerid, OPTUD_angle);
                }
            }
        }
    }
    return 1;
}

function OnAntiCheatTurnUpsideDown(playerid, Float:angle) {
    SendAdminMessage(X11_TOMATO, "AntiCheat: "GREY"Cheat detected on "YELLOW"%s "TOMATO"(Upside Down)", GetName(playerid));
    SendClientMessageEx(playerid, X11_YELLOW, "(AntiCheat) "GREY"You have been kicked from the server because of using some suspicious programs (Upside Down)");
    KickEx(playerid);
    return 1;
}
public OnIncomingRPC(playerid, rpcid, BitStream:bs)
{
    if (rpcid != 136)
    {
        return 1;
    }

    new
        vehicleid,
        Float:vehiclehealth
    ;

    BS_ReadUint16(bs, vehicleid);

    GetVehicleHealth(vehicleid, vehiclehealth);
    if (vehiclehealth >= 250.0)
    {
        defer Anticheat_IsVehicleDrown(playerid, vehicleid);
        return 0;
    }

    return 1;
}
