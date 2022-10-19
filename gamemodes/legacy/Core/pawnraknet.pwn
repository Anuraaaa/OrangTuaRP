#include <YSI_Coding\y_hooks>
#include <Pawn.RakNet>

#define ANTICHEAT_VEHICLE_TOLERANCE_TIME (2000)
#define MIN_DEPTH_VEHICLE_DROWNED        (0.5)

new
    countNotification[MAX_PLAYERS],
    countNotificationLastCheck[MAX_PLAYERS]
;

hook OnGameModeExit()
{
    MapAndreas_Unload();
    return 1;
}

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
        Float:z_mapandreas, // Untuk menyimpan ketinggian berdasarkan koordinat dari MapAndreas
        Float:vehiclehealth
    ;

    GetVehiclePos(vehicleid, x, y, z_samp);
    MapAndreas_FindZ_For2DCoord(x, y, z_mapandreas);
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

forward OnIncomingRPC(playerid, rpcid, BitStream:bs);
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
