enum ticketData
{
    ticketID,
    ticketExists,
    ticketFee,
    ticketDate[36],
    ticketReason[64]
};
new TicketData[MAX_PLAYERS][MAX_PLAYER_TICKETS][ticketData];

stock Ticket_Add(suspectid, price, reason[])
{
    new
        string[160];

    for (new i = 0; i != MAX_PLAYER_TICKETS; i ++) if (!TicketData[suspectid][i][ticketExists])
    {
        TicketData[suspectid][i][ticketExists] = true;
        TicketData[suspectid][i][ticketFee] = price;

        format(TicketData[suspectid][i][ticketDate], 36, ReturnDate());
        format(TicketData[suspectid][i][ticketReason], 64, reason);

        mysql_format(sqlcon, string, sizeof(string), "INSERT INTO `tickets` (`ID`, `ticketFee`, `ticketDate`, `ticketReason`) VALUES('%d', '%d', '%s', '%s')", PlayerData[suspectid][pID], price, TicketData[suspectid][i][ticketDate], reason);
        mysql_tquery(sqlcon, string, "OnTicketCreated", "dd", suspectid, i);

        return i;
    }
    return -1;
}

stock Ticket_Remove(playerid, ticketid)
{
    if (ticketid != -1 && TicketData[playerid][ticketid][ticketExists])
    {
        new
            string[90];

        mysql_format(sqlcon, string, sizeof(string), "DELETE FROM `tickets` WHERE `ID` = '%d' AND `ticketID` = '%d'", PlayerData[playerid][pID], TicketData[playerid][ticketid][ticketID]);
        mysql_tquery(sqlcon, string);

        TicketData[playerid][ticketid][ticketExists] = false;
        TicketData[playerid][ticketid][ticketID] = 0;
        TicketData[playerid][ticketid][ticketFee] = 0;
    }
    return 1;
}

function OnTicketCreated(playerid, ticketid)
{
    TicketData[playerid][ticketid][ticketID] = cache_insert_id();
    return 1;
}

function LoadPlayerTicket(playerid)
{
    new count = cache_num_rows();
    if(count > 0)
    {
        for(new i = 0; i < count; i++)
        {
            cache_get_value_name(i, "ticketReason", TicketData[playerid][i][ticketReason]);
            cache_get_value_name(i, "ticketDate", TicketData[playerid][i][ticketDate]);

            TicketData[playerid][i][ticketExists] = true;
            cache_get_value_name_int(i, "ticketID", TicketData[playerid][i][ticketID]);
            cache_get_value_name_int(i, "ticketFee", TicketData[playerid][i][ticketFee]);
        }
        printf("Loaded Player Ticket for %s", GetName(playerid));
    }
    return 1;
}

CMD:payticket(playerid, params[])
{
    static
        string[MAX_PLAYER_TICKETS * 64];

    if (!IsPlayerInRangeOfPoint(playerid, 3.0, 1380.9594,1557.6090,3001.0859))
        return SendErrorMessage(playerid, "You must be at SAPD to pay your tickets.");

    string[0] = 0;

    for (new i = 0; i < MAX_PLAYER_TICKETS; i ++)
    {
        if (TicketData[playerid][i][ticketExists])
            format(string, sizeof(string), "%s%s (%s - %s)\n", string, TicketData[playerid][i][ticketReason], FormatNumber(TicketData[playerid][i][ticketFee]), TicketData[playerid][i][ticketDate]);

        else format(string, sizeof(string), "%sEmpty Slot\n", string);
    }
    return ShowPlayerDialog(playerid, DIALOG_TICKET, DIALOG_STYLE_LIST, "Ticket List", string, "Pay", "Close");
}

CMD:ticket(playerid, params[])
{
    static
        userid,
        reason[64];

    if (GetFactionType(playerid) != FACTION_POLICE)
        return SendErrorMessage(playerid, "You must be a police officer.");

    if (sscanf(params, "us[64]", userid, reason))
        return SendSyntaxMessage(playerid, "/ticket [playerid/PartOfName] [reason]");

    if (userid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, userid, 5.0))
        return SendErrorMessage(playerid, "That player is disconnected or not near you.");

    if (userid == playerid)
        return SendErrorMessage(playerid, "You can't write a ticket to yourself.");

    SetPVarInt(playerid, "TargetID", userid);
    SetPVarString(playerid, "TicketReason", reason);
    PlayerData[playerid][pTarget] = userid;
    ShowPlayerDialog(playerid, DIALOG_GIVETICKET, DIALOG_STYLE_INPUT, sprintf("Ticket - %s", ReturnName(userid)), sprintf("Masukkan denda ticket untuk %s.", ReturnName(userid)), "Done", "Close");
    return 1;
}