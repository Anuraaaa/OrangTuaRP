#define             MAX_SPIKE                   100

enum E_SPIKE_DATA
{
    spikeWorld,
    spikeInterior,
    spikeOwner,
    spikeLobby,
    Float:spikePos[3],
    STREAMER_TAG_OBJECT:spikeObject
};
new
    SpikeData[MAX_SPIKE][E_SPIKE_DATA],
    Iterator:Spike<MAX_SPIKE>;

Spike_Create(playerid)
{
    new idx = INVALID_ITERATOR_SLOT, Float:x, Float:y, Float:z, Float:a;
    if((idx = Iter_Free(Spike)) != INVALID_ITERATOR_SLOT)
    {
        Iter_Add(Spike, idx);
        GetPlayerPos(playerid, x, y, z);
        GetPlayerFacingAngle(playerid, a);
        
        SpikeData[idx][spikeWorld] = GetPlayerVirtualWorld(playerid);
        SpikeData[idx][spikeInterior] = GetPlayerInterior(playerid);
        SpikeData[idx][spikePos][0] = x;
        SpikeData[idx][spikePos][1] = y;
        SpikeData[idx][spikePos][2] = z;

        SpikeData[idx][spikeObject] = CreateDynamicObject(2899, x, y, z - 0.8, 0.0, 0.0, a + 90.0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
        return idx;
    }
    return INVALID_ITERATOR_SLOT;
}

Spike_Nearest(playerid, Float:range = 5.0) {
    new index = -1;
    foreach(new idx : Spike) if(IsPlayerInRangeOfPoint(playerid, range, SpikeData[idx][spikePos][0], SpikeData[idx][spikePos][1], SpikeData[idx][spikePos][2])) {
        index = idx;
        break;
    }
    return index;
}

CMD:spike(playerid, params[])
{
    if(GetFactionType(playerid) != FACTION_POLICE)
        return SendErrorMessage(playerid, "This command is only allowed for Police!");

    if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
        return SendErrorMessage(playerid, "You must be on-foot to deploy spike!");
        
    new idx = Spike_Create(playerid);

    if(idx == INVALID_ITERATOR_SLOT)
        return SendErrorMessage(playerid, "This server cannot create more spike!");

    SendFactionMessage(PlayerData[playerid][pFaction], COLOR_RADIO, "[RADIO] %s %s has deployed a spikestrip on %s.", Faction_GetRank(playerid), GetName(playerid, false), GetSpecificLocation(playerid));
    return 1;
}

CMD:removespike(playerid, params[]) {

    if(GetFactionType(playerid) != FACTION_POLICE)
        return SendErrorMessage(playerid, "This command is only allowed for Police!");

    if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
        return SendErrorMessage(playerid, "You must be on-foot to remove spike!");

    new index = -1;
    if((index = Spike_Nearest(playerid)) != -1) {

        if(IsValidDynamicObject(SpikeData[index][spikeObject]))
            DestroyDynamicObject(SpikeData[index][spikeObject]);

        Iter_Remove(Spike, index);

        SendServerMessage(playerid, "You have removed spike on %s.", GetSpecificLocation(playerid));

    }
    else SendErrorMessage(playerid, "Tidak ada spike didekatmu.");

    return 1;
}
