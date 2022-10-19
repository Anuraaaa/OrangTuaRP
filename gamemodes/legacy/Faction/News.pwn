CMD:bc(playerid, params[])
{
    if(GetFactionType(playerid) != FACTION_NEWS)
        return SendErrorMessage(playerid, "You must be part of a news faction.");

    if(!PlayerData[playerid][pOnDuty])
        return SendErrorMessage(playerid, "You must duty first.");

    if(isnull(params))
        return SendSyntaxMessage(playerid, "/bc [broadcast text]");

    if(!IsNewsVehicle(GetPlayerVehicleID(playerid)) && !IsPlayerInRangeOfPoint(playerid, 25.0, -158.0952,1338.7379,1500.9943))
        return SendErrorMessage(playerid, "You must be inside a news van or chopper or in SFN studio.");

    if(!PlayerData[playerid][pBroadcast])
        return SendErrorMessage(playerid, "You must be broadcasting to use this command.");

    if(strlen(params) > 64) {
        foreach (new i : Player) {
            SendClientMessageEx(i, COLOR_ORANGE, "[SFN] Anchor %s: %.64s", ReturnName(playerid), params);
            SendClientMessageEx(i, COLOR_ORANGE, "...%s", params[64]);
        }
    }
    else {
        foreach (new i : Player) {
            SendClientMessageEx(i, COLOR_ORANGE, "[SFN] Anchor %s: %s", ReturnName(playerid), params);
        }
    }
    return 1;
}

CMD:camera(playerid, params[]) {
    GivePlayerCamera(playerid); 
    return 1;
}

CMD:watch(playerid, params[]) {
    StartPlayerWatchingCamera(playerid, playerid);
    return 1;
}

CMD:unwatch(playerid, params[]) {
    StopPlayerWatchingCamera(playerid);
    return 1;
}
CMD:broadcast(playerid, params[])
{
    if(GetFactionType(playerid) != FACTION_NEWS)
        return SendErrorMessage(playerid, "You must be part of a news faction.");

    if(!PlayerData[playerid][pOnDuty])
        return SendErrorMessage(playerid, "You must duty first.");

    if(!IsNewsVehicle(GetPlayerVehicleID(playerid)) && !IsPlayerInRangeOfPoint(playerid, 25.0, -158.0952,1338.7379,1500.9943))
        return SendErrorMessage(playerid, "You must be inside a news van or chopper or in SFN studio.");

    if(!PlayerData[playerid][pBroadcast])
    {
        PlayerData[playerid][pBroadcast] = true;

        SendNearbyMessage(playerid, 15.0, X11_PLUM, "* %s has started a news broadcast.", ReturnName(playerid));
        SendServerMessage(playerid, "You have started a news broadcast (use \"/bc [broadcast text]\" to broadcast).");
    }
    else
    {
        PlayerData[playerid][pBroadcast] = false;

        foreach (new i : Player) if(PlayerData[i][pNewsGuest] == playerid) {
            PlayerData[i][pNewsGuest] = INVALID_PLAYER_ID;
        }
        SendNearbyMessage(playerid, 15.0, X11_PLUM, "* %s has stopped a news broadcast.", ReturnName(playerid));
        SendServerMessage(playerid, "You have stopped the news broadcast.");
    }
    return 1;
}

CMD:live(playerid, params[])
{
    static
        livechat[128];

    if(sscanf(params, "s[128]", livechat))
        return SendSyntaxMessage(playerid, "/live [live chat]");

    if(PlayerData[playerid][pNewsGuest] == INVALID_PLAYER_ID)
        return SendErrorMessage(playerid, "You're not invite by SFN member to live!");

    if(!IsNewsVehicle(GetPlayerVehicleID(playerid)) && !IsPlayerInRangeOfPoint(playerid, 25.0, -158.0952,1338.7379,1500.9943))
        return SendErrorMessage(playerid, "You must be inside a news van or chopper or in SFN studio.");

    if(GetFactionType(PlayerData[playerid][pNewsGuest]) == FACTION_NEWS)
    {
        foreach (new i : Player) {
            SendClientMessageEx(i, COLOR_ORANGE, "[SFN] %s %s: %s", (GetFactionType(playerid) == FACTION_NEWS) ? ("Reporter") : ("Guest"), ReturnName(playerid), livechat);
        }
    }
    return 1;
}
CMD:inviteguest(playerid, params[])
{
    static
        userid;

    if(GetFactionType(playerid) != FACTION_NEWS)
        return SendErrorMessage(playerid, "You must be part of a news faction.");

    if(!PlayerData[playerid][pOnDuty])
        return SendErrorMessage(playerid, "You must duty first.");

    if(sscanf(params, "u", userid))
        return SendSyntaxMessage(playerid, "/inviteguest [playerid/PartOfName]");

    if(!PlayerData[playerid][pBroadcast])
        return SendErrorMessage(playerid, "You must be broadcasting to use this command.");

    if(userid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, userid, 5.0))
        return SendErrorMessage(playerid, "That player is disconnected or not near you.");

    if(userid == playerid)
        return SendErrorMessage(playerid, "You can't add yourself as a guest.");

    if(PlayerData[userid][pNewsGuest] == playerid)
        return SendErrorMessage(playerid, "That player is already a guest of your broadcast.");

    if(PlayerData[userid][pNewsGuest] != INVALID_PLAYER_ID)
        return SendErrorMessage(playerid, "That player is already a guest of another broadcast.");

    PlayerData[userid][pNewsGuest] = playerid;

    SendServerMessage(playerid, "You have added %s as a broadcast guest.", ReturnName(userid));
    SendServerMessage(userid, "%s has added you as a broadcast guest ((/live to start broadcast)).", ReturnName(userid));
    return 1;
}

CMD:removemic(playerid, params[]) {


    new userid;

    if(GetFactionType(playerid) != FACTION_NEWS)
        return SendErrorMessage(playerid, "You must be part of a news faction.");

    if(!PlayerData[playerid][pOnDuty])
        return SendErrorMessage(playerid, "You must duty first.");

    if(sscanf(params, "u", userid))
        return SendSyntaxMessage(playerid, "/removemic [playerid/PartOfName]");

    if(userid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, userid, 5.0))
        return SendErrorMessage(playerid, "That player is disconnected or not near you.");

    if(!PlayerData[userid][pMicrophone])
        return SendErrorMessage(playerid, "That player is doesn't have a microphone.");

    PlayerData[userid][pMicrophone] = false;

    SendServerMessage(userid, "%s telah mengambil "YELLOW"Microphone "WHITE"darimu.", ReturnName(playerid));
    SendServerMessage(playerid, "Kamu telah mengambil "YELLOW"Microphone "WHITE"dari %s.", ReturnName(userid));

    return 1;
}


CMD:givemic(playerid, params[]) {

    if(GetFactionType(playerid) != FACTION_NEWS)
        return SendErrorMessage(playerid, "You must be part of a news faction.");

    new userid;
    
    if(!PlayerData[playerid][pOnDuty])
        return SendErrorMessage(playerid, "You must duty first.");

    if(sscanf(params, "u", userid))
        return SendSyntaxMessage(playerid, "/givemic [playerid/PartOfName]");

    if(userid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, userid, 5.0))
        return SendErrorMessage(playerid, "That player is disconnected or not near you.");

    if(PlayerData[userid][pMicrophone])
        return SendErrorMessage(playerid, "That player is already have a microphone.");

    PlayerData[userid][pMicrophone] = true;

    SendServerMessage(userid, "Kamu diberikan "YELLOW"Microphone "WHITE"oleh %s, chat seperti biasa untuk menggunakannya.", ReturnName(playerid));
    SendServerMessage(playerid, "Kamu telah memberikan "YELLOW"Microphone "WHITE"kepada %s.", ReturnName(userid));

    return 1;
}

CMD:removeguest(playerid, params[])
{
    static
        userid;

    if(GetFactionType(playerid) != FACTION_NEWS)
        return SendErrorMessage(playerid, "You must be part of a news faction.");

    if(!PlayerData[playerid][pOnDuty])
        return SendErrorMessage(playerid, "You must duty first.");

    if(sscanf(params, "u", userid))
        return SendSyntaxMessage(playerid, "/removeguest [playerid/PartOfName]");

    if(!PlayerData[playerid][pBroadcast])
        return SendErrorMessage(playerid, "You must be broadcasting to use this command.");

    if(userid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, userid, 5.0))
        return SendErrorMessage(playerid, "That player is disconnected or not near you.");

    if(userid == playerid)
        return SendErrorMessage(playerid, "You can't remove yourself as a guest.");

    if(PlayerData[userid][pNewsGuest] != playerid)
        return SendErrorMessage(playerid, "That player is not a guest of your broadcast.");

    PlayerData[userid][pNewsGuest] = INVALID_PLAYER_ID;

    SendServerMessage(playerid, "You have removed %s from your broadcast.", ReturnName(userid));
    SendServerMessage(userid, "%s has removed you from their broadcast.", ReturnName(userid));
    return 1;
}
