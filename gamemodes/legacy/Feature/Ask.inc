#include <YSI_Coding\y_hooks>

CountAsk() {
    new e_count = 0;
    foreach(new i : Player) if(PlayerData[i][pAsking]) {
        e_count++;
    }
    return e_count;
}


ShowPendingAsk(playerid) {
    new
        string[512],
        count = 0;

    strcat(string, "Ask from (ID)\tQuestion\n");
    foreach(new i : Player) if(PlayerData[i][pAsking]) {
        strcat(string, sprintf("%s (%d)\t%s\n", GetName(i, false), i, PlayerData[i][pAsk]));
        ListedItems[playerid][count++] = i;
    }
    ShowPlayerDialog(playerid, DIALOG_ASKS, DIALOG_STYLE_TABLIST_HEADERS, sprintf("%d pending ask", CountAsk()), string, "Select", "Close");
    return 1;

}
CMD:ask(playerid, params[])
{

	if(askDelay[playerid])
		return SendErrorMessage(playerid, "Tunggu %d detik untuk kembali bertanya.", askDelay[playerid]);

	if(PlayerData[playerid][pJailTime])
		return SendErrorMessage(playerid, "Tidak bisa menggunakan command ini sekarang.");

	if(PlayerData[playerid][pAsking])
		return SendErrorMessage(playerid, "Kamu sudah memiliki pertanyaan pending.");

	if(isnull(params))
		return SendSyntaxMessage(playerid, "/ask [question]");

	if(strlen(params) >= 128)
		return SendErrorMessage(playerid, "Panjang teks tidak bisa lebih dari 128 huruf!");

	format(PlayerData[playerid][pAsk], 128, params);
	PlayerData[playerid][pAsking] = true;
	SendServerMessage(playerid, "Berhasil mengirim pertanyaan ke Administrator!");
	askDelay[playerid] = 180;

	if(strlen(params) > 64) {
        if(CountAdminDuty() > 1) {
            SendAdminDutyMessage(COLOR_YELLOW, "ASK from {00FFFF}%s [%d]: {FFFFFF}%.64s", GetName(playerid), playerid, params);
            SendAdminDutyMessage(-1, "...%s", params[64]);
        }
        else {
            SendAdminMessage(COLOR_YELLOW, "ASK from {00FFFF}%s [%d]: {FFFFFF}%.64s", GetName(playerid), playerid, params);
            SendAdminMessage(-1, "...%s", params[64]);
        }
	}
	else {
		if(CountAdminDuty()) {
            SendAdminDutyMessage(COLOR_YELLOW, "ASK from {00FFFF}%s [%d]: {FFFFFF}%s", GetName(playerid), playerid, params);
        }
        else {
            SendAdminMessage(COLOR_YELLOW, "ASK from {00FFFF}%s [%d]: {FFFFFF}%s", GetName(playerid), playerid, params);
        }
	}
	return 1;
}

CMD:ans(playerid, params[])
{
	new
	    userid,
	    text[128];

    if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "us[128]", userid, text))
		return SendSyntaxMessage(playerid, "/ans [playerid/PartOfName] [answer]");

	if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "You have specified an invalid player.");

	if(!PlayerData[userid][pAsking])
	    return SendErrorMessage(playerid, "That player is not asking.");
	    
	SendClientMessageEx(userid, COLOR_SERVER, "(Answer) {FFFFFF}%s", text);
	SendAdminMessage(COLOR_LIGHTRED, "%s Answer To %s: %s", PlayerData[playerid][pUCP], GetName(userid), text);
	PlayerData[userid][pAsking] = false;
	PlayerData[playerid][pAdminPoint]++;
	return 1;
}

CMD:asks(playerid, params[]) {
    if(PlayerData[playerid][pAdmin] < 1)
        return PermissionError(playerid);

    if(!CountAsk()) {
        return SendErrorMessage(playerid, "Tidak ada pertanyaan yang aktif.");
    }

    ShowPendingAsk(playerid);
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {
    if(dialogid == DIALOG_ASKS) {
        if(response) {
            new targetid = ListedItems[playerid][listitem];

            if(!IsPlayerConnected(targetid))
                return SendErrorMessage(playerid, "Player tidak lagi berada di server."), ShowPendingAsk(playerid);

            if(!PlayerData[targetid][pAsking])
                return SendErrorMessage(playerid, "Player tersebut tidak lagi bertanya."), ShowPendingAsk(playerid);

            SetPVarInt(playerid, "TargetID", targetid);
            new 
                string[256];

            strcat(string, sprintf("Ask from: %s\n", GetName(targetid, false)));
            strcat(string, sprintf("Question: %s\n", PlayerData[targetid][pAsk]));
            ShowPlayerDialog(playerid, DIALOG_ASKS_ANSWER, DIALOG_STYLE_INPUT, sprintf("Answer question of %s", GetName(targetid, false)), string, "Send", "Close");
        }
    }
    if(dialogid == DIALOG_ASKS_ANSWER) {
        if(response) {

            new targetid = GetPVarInt(playerid, "TargetID");

            if(!IsPlayerConnected(targetid))
                return SendErrorMessage(playerid, "Player tidak lagi berada di server."), ShowPendingAsk(playerid);

            if(!PlayerData[targetid][pAsking])
                return SendErrorMessage(playerid, "Player tersebut tidak lagi bertanya."), ShowPendingAsk(playerid);      

            SendClientMessageEx(targetid, COLOR_SERVER, "(Answer) {FFFFFF}%s", inputtext);
            SendAdminMessage(COLOR_LIGHTRED, "%s Answer To %s: %s", PlayerData[playerid][pUCP], GetName(targetid), inputtext);
            PlayerData[targetid][pAsking] = false;
            PlayerData[playerid][pAdminPoint]++;
        }
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}