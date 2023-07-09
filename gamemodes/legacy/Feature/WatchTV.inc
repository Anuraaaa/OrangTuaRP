#include <YSI_Coding\y_hooks>

enum {
    LIVE_STATUS_OFF_AIR = 0,
    LIVE_STATUS_ON_AIR
};

new g_LiveStatus,
    g_ReporterPlayerID,
    g_BroadcastTitle[32];

new Text:LIVETD[6];


hook OnGameModeInit() {
    g_LiveStatus = LIVE_STATUS_OFF_AIR,
    g_ReporterPlayerID = INVALID_PLAYER_ID;

    LIVETD[0] = TextDrawCreate(181.000000, 337.000000, "_");
	TextDrawFont(LIVETD[0], 1);
	TextDrawLetterSize(LIVETD[0], 0.600000, 6.399999);
	TextDrawTextSize(LIVETD[0], 355.000000, 39.000000);
	TextDrawSetOutline(LIVETD[0], 1);
	TextDrawSetShadow(LIVETD[0], 0);
	TextDrawAlignment(LIVETD[0], 2);
	TextDrawColor(LIVETD[0], -1);
	TextDrawBackgroundColor(LIVETD[0], 255);
	TextDrawBoxColor(LIVETD[0], -16776961);
	TextDrawUseBox(LIVETD[0], 1);
	TextDrawSetProportional(LIVETD[0], 1);
	TextDrawSetSelectable(LIVETD[0], 0);

	LIVETD[1] = TextDrawCreate(210.000000, 339.000000, "_");
	TextDrawFont(LIVETD[1], 1);
	TextDrawLetterSize(LIVETD[1], 0.412500, 1.950000);
	TextDrawTextSize(LIVETD[1], 400.000000, 17.000000);
	TextDrawSetOutline(LIVETD[1], 0);
	TextDrawSetShadow(LIVETD[1], 0);
	TextDrawAlignment(LIVETD[1], 1);
	TextDrawColor(LIVETD[1], 255);
	TextDrawBackgroundColor(LIVETD[1], 255);
	TextDrawBoxColor(LIVETD[1], 50);
	TextDrawUseBox(LIVETD[1], 0);
	TextDrawSetProportional(LIVETD[1], 1);
	TextDrawSetSelectable(LIVETD[1], 0);

	LIVETD[2] = TextDrawCreate(168.000000, 348.000000, "LIVE");
	TextDrawFont(LIVETD[2], 1);
	TextDrawLetterSize(LIVETD[2], 0.412500, 1.950000);
	TextDrawTextSize(LIVETD[2], 400.000000, 17.000000);
	TextDrawSetOutline(LIVETD[2], 0);
	TextDrawSetShadow(LIVETD[2], 0);
	TextDrawAlignment(LIVETD[2], 1);
	TextDrawColor(LIVETD[2], -1);
	TextDrawBackgroundColor(LIVETD[2], 255);
	TextDrawBoxColor(LIVETD[2], 50);
	TextDrawUseBox(LIVETD[2], 0);
	TextDrawSetProportional(LIVETD[2], 1);
	TextDrawSetSelectable(LIVETD[2], 0);

	LIVETD[3] = TextDrawCreate(345.000000, 337.000000, "_");
	TextDrawFont(LIVETD[3], 1);
	TextDrawLetterSize(LIVETD[3], 0.600000, 4.749993);
	TextDrawTextSize(LIVETD[3], 355.000000, 283.000000);
	TextDrawSetOutline(LIVETD[3], 1);
	TextDrawSetShadow(LIVETD[3], 0);
	TextDrawAlignment(LIVETD[3], 2);
	TextDrawColor(LIVETD[3], -1);
	TextDrawBackgroundColor(LIVETD[3], 255);
	TextDrawBoxColor(LIVETD[3], -1);
	TextDrawUseBox(LIVETD[3], 1);
	TextDrawSetProportional(LIVETD[3], 1);
	TextDrawSetSelectable(LIVETD[3], 0);

	LIVETD[4] = TextDrawCreate(345.000000, 384.000000, "_");
	TextDrawFont(LIVETD[4], 1);
	TextDrawLetterSize(LIVETD[4], 0.600000, 1.149993);
	TextDrawTextSize(LIVETD[4], 355.000000, 283.000000);
	TextDrawSetOutline(LIVETD[4], 1);
	TextDrawSetShadow(LIVETD[4], 0);
	TextDrawAlignment(LIVETD[4], 2);
	TextDrawColor(LIVETD[4], -1);
	TextDrawBackgroundColor(LIVETD[4], 255);
	TextDrawBoxColor(LIVETD[4], 255);
	TextDrawUseBox(LIVETD[4], 1);
	TextDrawSetProportional(LIVETD[4], 1);
	TextDrawSetSelectable(LIVETD[4], 0);

	LIVETD[5] = TextDrawCreate(209.000000, 384.000000, "_");
	TextDrawFont(LIVETD[5], 1);
	TextDrawLetterSize(LIVETD[5], 0.183333, 0.900000);
	TextDrawTextSize(LIVETD[5], 400.000000, 17.000000);
	TextDrawSetOutline(LIVETD[5], 0);
	TextDrawSetShadow(LIVETD[5], 0);
	TextDrawAlignment(LIVETD[5], 1);
	TextDrawColor(LIVETD[5], -1);
	TextDrawBackgroundColor(LIVETD[5], 255);
	TextDrawBoxColor(LIVETD[5], 50);
	TextDrawUseBox(LIVETD[5], 0);
	TextDrawSetProportional(LIVETD[5], 1);
	TextDrawSetSelectable(LIVETD[5], 0);
}

hook OnPlayerDisconnectEx(playerid) {
    if(g_ReporterPlayerID == playerid) {

        g_ReporterPlayerID = INVALID_PLAYER_ID;
        g_LiveStatus = LIVE_STATUS_OFF_AIR;

        TextDrawSetString(LIVETD[1], "_");
        TextDrawSetString(LIVETD[5], "_");

        foreach(new i : Player) if(IsPlayerWatchingCamera(i)) {
            StopPlayerWatchingCamera(i);
            SendClientMessage(playerid, X11_LIGHTBLUE, "(Live) "WHITE"Siaran langsung telah "RED"berakhir");
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            HideLiveTD(i);
        }
    }
}
bool:IsTVModel(modelid) {

    new bool:istv = false;

    switch(modelid) {
        case 1518: istv = true;
        case 1717: istv = true;
        case 1747, 1748, 1749, 1750, 1752: istv = true;
        case 1781: istv = true;
        case 1791, 1792: istv = true;
        case 2312: istv = true;
        case 2316, 2317, 2318, 2320: istv = true;
        case 2595: istv = true;
        case 16377: istv = true;
        default: istv = false;
    }
    return istv;
}

GetClosestTVObjectToPlayer(playerid) {
    new STREAMER_TAG_OBJECT:objectid = INVALID_STREAMER_ID;

    for (new i = Streamer_GetUpperBound(STREAMER_TYPE_OBJECT); i; --i) if(IsValidDynamicObject(i) && IsTVModel(Streamer_GetIntData(STREAMER_TYPE_OBJECT, i, E_STREAMER_MODEL_ID)) ) {
        
        new Float:fX, Float:fY, Float:fZ;
        Streamer_GetItemPos(STREAMER_TYPE_OBJECT, i, fX, fY, fZ);

        if(IsPlayerInRangeOfPoint(playerid, 10.0, fX, fY, fZ)) {
            objectid = i;
            break;
        }
    }
    return STREAMER_TAG_OBJECT:objectid;
}

HideLiveTD(playerid) {
    for(new i = 0; i < 6; i++) {
        TextDrawHideForPlayer(playerid, LIVETD[i]);
    }
}

ShowLiveTD(playerid) {
    for(new i = 0; i < 6; i++) {
        TextDrawShowForPlayer(playerid, LIVETD[i]);
    }
}
CMD:watchlive(playerid, params[]) {

    new STREAMER_TAG_OBJECT:objectid;

    if((objectid = GetClosestTVObjectToPlayer(playerid)) != STREAMER_TAG_OBJECT:INVALID_STREAMER_ID) {


        if(IsPlayerRecording(playerid)) {
            return SendErrorMessage(playerid, "Tidak dapat melakukan ini jika sedang merekam.");
        }

        if(g_LiveStatus == LIVE_STATUS_OFF_AIR && g_ReporterPlayerID == INVALID_PLAYER_ID) {
            return SendErrorMessage(playerid, "Tidak ada siaran yang sedang berlangsung.");

        }
        new Float:x, Float:y, Float:z;
        Streamer_GetItemPos(STREAMER_TYPE_OBJECT, objectid, x, y, z);

        SetPlayerFace(playerid, x, y);
        SendClientMessage(playerid, X11_LIGHTBLUE, "(Live) "WHITE"Kamu sekarang menonton televisi.");
        SendClientMessage(playerid, X11_LIGHTBLUE, "(Live) "WHITE"Gunakan "YELLOW"/stopwatchlive "WHITE"untuk berhenti.");
        SendNearbyMessage(playerid, 15.0, X11_PLUM, "** %s starts watching live broadcast from their television", ReturnName(playerid));

        StartPlayerWatchingCamera(playerid, g_ReporterPlayerID);

        ShowLiveTD(playerid);
    }
    else SendErrorMessage(playerid, "Kamu tidak berada didekat televisi.");

    return 1;
}

CMD:stopwatchlive(playerid, params[]) {
    if(!IsPlayerWatchingCamera(playerid))
        return SendErrorMessage(playerid, "Kamu sedang tidak menonton siaran langsung saat ini.");
        
    SendClientMessage(playerid, X11_LIGHTBLUE, "(Live) "WHITE"Kamu tidak lagi menonton siaran langsung.");

    StopPlayerWatchingCamera(playerid);
    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
    HideLiveTD(playerid);
    return 1;
}
CMD:camera(playerid, params[]) {

    if(GetFactionType(playerid) != FACTION_NEWS) {
        return SendErrorMessage(playerid, "Command ini hanya dapat diakses oleh anggota SFN.");
    }

    if(!PlayerData[playerid][pOnDuty])
        return SendErrorMessage(playerid, "Kamu harus bertugas terlebih dahulu untuk menggunakan command ini");
        
    if(g_ReporterPlayerID != playerid && g_LiveStatus == LIVE_STATUS_ON_AIR) {
        return SendErrorMessage(playerid, "Siaran langsung hanya dapat direkam oleh 1 orang.");
    }


    if(g_LiveStatus == LIVE_STATUS_OFF_AIR) {

        if(sscanf(params, "s[32]", g_BroadcastTitle))
            return SendSyntaxMessage(playerid, "/camera [broadcast title]");

        g_LiveStatus = LIVE_STATUS_ON_AIR;
        g_ReporterPlayerID = playerid;

        GivePlayerCamera(playerid);

        SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Live) "WHITE"Kamu telah memulai siaran langsung dengan judul "YELLOW"%s", g_BroadcastTitle);

        TextDrawSetString(LIVETD[1], g_BroadcastTitle);
        TextDrawSetString(LIVETD[5], sprintf("Cameraman:_%s", GetName(playerid)));
    }
    else {
        RemovePlayerCamera(playerid);
        g_ReporterPlayerID = INVALID_PLAYER_ID;
        g_LiveStatus = LIVE_STATUS_OFF_AIR;

        TextDrawSetString(LIVETD[1], "_");
        TextDrawSetString(LIVETD[5], "_");
        SendClientMessage(playerid, X11_LIGHTBLUE, "(Live) "WHITE"Siaran langsung telah "RED"berakhir");
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        
        foreach(new i : Player) if(IsPlayerWatchingCamera(i)) {
            StopPlayerWatchingCamera(i);
            
        

            HideLiveTD(i);
        }
    }
    return 1;
}