new bool:voteStarted,
    Iterator:VoteYes<MAX_PLAYERS>,
    Iterator:VoteNo<MAX_PLAYERS>;

Vote_GetUnknown()
{
    new count = 0;
    foreach(new i : Player) if(IsPlayerSpawned(i) && !Iter_Contains(VoteYes, i) && !Iter_Contains(VoteNo, i))
        count++;

    return count;
}

timer ClearVoteIter[2000]()
{
    Iter_Clear(VoteYes);
    Iter_Clear(VoteNo);
    return 1;
}

CMD:vote(playerid, params[])
{
    new option[24], string[128];
    if(PlayerData[playerid][pAdmin] < 2)
        return PermissionError(playerid);

    if(sscanf(params, "s[24]S()[128]", option, string))
        return SendSyntaxMessage(playerid, "/vote [start/end]");

    if(!strcmp(option, "start", true))
    {
        if(voteStarted)
            return SendErrorMessage(playerid, "Please end the current vote first.");

        new votewhat[128];
        if(sscanf(string, "s[128]", votewhat))
            return SendSyntaxMessage(playerid, "/vote start [vote]");

        SendClientMessageToAllEx(X11_YELLOW, "VOTE: "CYAN"%s", votewhat);
        SendClientMessageToAllEx(X11_YELLOW, "VOTE: "CYAN"Type "GREEN"/yes "CYAN"or "RED"/no "CYAN"to vote.");
        voteStarted = true;
    }
    else if(!strcmp(option, "end", true))
    {
        if(!voteStarted)
            return SendErrorMessage(playerid, "There are no vote started.");

        SendClientMessageToAllEx(X11_WHITE, "[ Vote has ended with results "GREEN"%d yes "RED"%d no "WHITE"and "YELLOW"%d unknown "WHITE"]", Iter_Count(VoteYes), Iter_Count(VoteNo), Vote_GetUnknown());
        voteStarted = false;
        
        defer ClearVoteIter[2000]();
    }
    return 1;
}

CMD:no(playerid, params[])
{
    if(!voteStarted)
        return SendErrorMessage(playerid, "There are no vote started.");   

    if(Iter_Contains(VoteYes, playerid))
        return SendErrorMessage(playerid, "You already voted.");

    if(Iter_Contains(VoteNo, playerid))
        return SendErrorMessage(playerid, "You already voted.");

    Iter_Add(VoteNo, playerid);
    SendServerMessage(playerid, "You have successfully voted "RED"no");
    return 1;
}

CMD:yes(playerid, params[])
{
    if(!voteStarted)
        return SendErrorMessage(playerid, "There are no vote started.");   

    if(Iter_Contains(VoteYes, playerid))
        return SendErrorMessage(playerid, "You already voted.");

    if(Iter_Contains(VoteNo, playerid))
        return SendErrorMessage(playerid, "You already voted.");

    Iter_Add(VoteYes, playerid);
    SendServerMessage(playerid, "You have successfully voted "GREEN"yes");
    return 1;
}
