#include <YSI_Coding\y_hooks>

forward OnPlayerRedeemVIP(playerid);
forward OnPlayerExpireVIP(playerid);

#define             GetVIPName(%0)                vip_name[%0]
#define             GetPlayerVIPLevel(%0)         PlayerVIP[%0][vipLevel]
#define             ReturnVIPCoin(%0)             vip_coin[%0]


new const vip_name[4][20] = {
    "None",
    "Bronze Donater",
    "Silver Donater",
    "Gold Donater"
};

new vip_coin[4] = {0, 200, 500, 1000};

enum {

	VIP_LEVEL_NONE = 0,
	VIP_LEVEL_BRONZE,
	VIP_LEVEL_SILVER,
	VIP_LEVEL_GOLD

};

enum E_PLAYER_VIP {

    vipLevel,
    vipExpired,
    vipCoin
};
new PlayerVIP[MAX_PLAYERS][E_PLAYER_VIP];

hook OnPlayerConnect(playerid) {

	PlayerVIP[playerid][vipLevel] = 0;
	PlayerVIP[playerid][vipExpired] = 0;
}
hook OnPlayerLogin(playerid) {

    mysql_tquery(sqlcon, sprintf("SELECT * FROM `donation_characters` WHERE `pID` = '%d' LIMIT 1;", PlayerData[playerid][pID]), "OnPlayerVIPChecked", "d", playerid);
}

FUNC::OnPlayerVIPChecked(playerid) {

    new level, expired;

    if(cache_num_rows()) {

        cache_get_value_name_int(0, "Level", level);
        cache_get_value_name_int(0, "Expired", expired);

        if(expired < gettime()) {

			RemovePlayerVIP(playerid);
			SendServerMessage(playerid, "Masa aktif VIP mu telah habis, terimakasih atas dukungannya!");
            CallLocalFunction(#OnPlayerExpireVIP, "d", playerid);
        }
        else {
            SetPlayerVIP(playerid, level, expired);
            SendServerMessage(playerid, "Status VIP "YELLOW"%s"WHITE", masa aktif sampai "LIGHTBLUE"%s.", GetVIPName(PlayerVIP[playerid][vipLevel]), ConvertTimestamp(Timestamp:PlayerVIP[playerid][vipExpired]));
        }
    }
    return 1;
}
stock SetPlayerVIP(playerid, level, expired) {

    PlayerVIP[playerid][vipLevel] = level;
    PlayerVIP[playerid][vipExpired] = expired;
    return 1;
}

stock RemovePlayerVIP(playerid) {

    PlayerVIP[playerid][vipLevel] = 0;
    PlayerVIP[playerid][vipExpired] = 0;
    return mysql_tquery(sqlcon, sprintf("DELETE FROM `donation_characters` WHERE `pID` = '%d';", PlayerData[playerid][pID]));
}


FUNC::OnRedeemCode(playerid, code[]) {

    if(cache_num_rows()) {

        new level, expired;

        cache_get_value_name_int(0, "Level", level);
        cache_get_value_name_int(0, "Duration", expired);

        SetPlayerVIP(playerid, level, expired);
        PlayerData[playerid][pCoin] += vip_coin[level];

        SendCustomMessage(playerid, X11_LIGHTBLUE, "VIP", "Kamu berhasil meredeem VIP dengan Kode "YELLOW"%s", code);
        SendCustomMessage(playerid, X11_LIGHTBLUE, "VIP", "Berisi "YELLOW"%s"WHITE", berakhir pada "YELLOW"%s", GetVIPName(level), ConvertTimestamp(Timestamp:expired));
        SendCustomMessage(playerid, X11_LIGHTBLUE, "VIP", "Gunakan command "YELLOW"/viphelp "WHITE"untuk melihat daftar Donater Commands.");

    
        mysql_tquery(sqlcon, sprintf("DELETE FROM `donation_code` WHERE `Code` = '%s'", code));

        new output[300];
        mysql_format(sqlcon, output, sizeof(output), "INSERT INTO `donation_characters` (`pID`, `Level`, `Expired`) VALUES ('%d','%d','%d') ON DUPLICATE KEY UPDATE `Level`='%d', `Expired`='%d';", PlayerData[playerid][pID], level, expired, level, expired);
        mysql_tquery(sqlcon, output);

        CallLocalFunction(#OnPlayerRedeemVIP, "d", playerid);
        Log_Write("Logs/vip_redeemed.txt", "[%s] %s menggunakan code redeem %s (type: %s, expired: %s).", ReturnDate(), GetName(playerid, false), code, GetVIPName(level), ConvertTimestamp(Timestamp:expired));
    }
    else SendErrorMessage(playerid, "Tidak dapat menemukan Kode Redeem \"%s\"", code);
}


FUNC::OnVIPCheckMask(playerid, maskid) {

    if(cache_num_rows()) {
        return SendErrorMessage(playerid, "Mask dengan ID \"%d\" sudah digunakan!", maskid);
    }

    PlayerData[playerid][pCoin] -= 150;
    SendCustomMessage(playerid, X11_GOLD, "VIP", "Kamu berhasil mengubah Mask ID mu menjadi "LIGHTBLUE"%d", maskid);
    PlayerData[playerid][pMaskID] = maskid;
    return 1;
}
FUNC::OnVIPCheckNumber(playerid, number) {
    if(cache_num_rows()) 
        return SendErrorMessage(playerid, "Nomor handphone \"%d\" sudah digunakan!", number);

    PlayerData[playerid][pCoin] -= 100;
    SendCustomMessage(playerid, X11_GOLD, "VIP", "Kamu berhasil mengubah Nomor Handphone mu menjadi "LIGHTBLUE"%d", number);
    PlayerData[playerid][pPhoneNumber] = number;
    return 1;
}
/* Commands */

CMD:generatevip(playerid, params[]) {

    if(PlayerData[playerid][pAdmin] < 7)
        return PermissionError(playerid);

    new level, duration;

    if(sscanf(params, "dd", level, duration))
        return SendSyntaxMessage(playerid, "/generatevip [vip level] [time in day]");

	if(!(0 < level <= 3))
		return SendErrorMessage(playerid, "Level VIP dibatasi dari 1 - 3.");

	if(!(0 < duration <= 360))
		return SendErrorMessage(playerid, "Durasi dibatasi dari 1 - 360 hari!");

    new expired = gettime() + (duration * 86400), vip_code[24];

    format(vip_code, sizeof(vip_code), "OT-%c%c%c%c%04d", RandomLetter(), RandomLetter(), RandomLetter(), RandomLetter(), RandomEx(1000, 9999));
    SendAdminAction(playerid, "Kamu berhasil membuat Code VIP (%s)", vip_code);
    SendAdminAction(playerid, "Berisi VIP level %s dengan durasi %d hari.", GetVIPName(level), duration);
    mysql_tquery(sqlcon, sprintf("INSERT INTO `donation_code`(`Code`, `Duration`, `Level`) VALUES ('%s','%d','%d');", vip_code, expired, level));
    Log_Write("Logs/vip_generate.txt", "[%s] %s membuat Kode VIP (%s) berisi %s dan durasi %d hari.", ReturnDate(), GetVIPName(level), duration);
    return 1;
}

CMD:redeemvip(playerid, params[]) {

    new code[24];
    if(sscanf(params, "s[24]", code))
        return SendSyntaxMessage(playerid, "/redeemvip [vip code]");

    mysql_tquery(sqlcon, sprintf("SELECT * FROM `donation_code` WHERE `Code` = '%s'", code), "OnRedeemCode", "ds", playerid, code);
    return 1;
}

CMD:usepoint(playerid, params[]) {

	if(!GetPlayerVIPLevel(playerid))
        return SendErrorMessage(playerid, "Hanya donater yang bisa mengakses command ini.");

    ShowPlayerDialog(playerid, DIALOG_VIP_POINT, DIALOG_STYLE_LIST, "Donater Point", "Custom phone number (100 Point)\nCustom mask (150 Point)\nRequest Gate (250 Point)", "Select", "Close");
    return 1;
}

CMD:vip(playerid, params[]) {

	if(!GetPlayerVIPLevel(playerid))
        return SendErrorMessage(playerid, "Hanya donater yang bisa mengakses command ini.");

	if(isnull(params))
		return SendSyntaxMessage(playerid, "/vip [text]");

	if(strlen(params) > 128)
		return SendErrorMessage(playerid, "Text hanya dibatasi sebanyak 128 karakter!");


	foreach (new i : Player) if(GetPlayerVIPLevel(i)) {
		SendClientMessageEx(i, X11_TURQUOISE, "* (%s) %s: "WHITE"%s", GetVIPName(GetPlayerVIPLevel(playerid)), GetName(playerid, false), params);
	}
    return 1;
}
CMD:viphelp(playerid, params[]) {

    if(!GetPlayerVIPLevel(playerid))
        return SendErrorMessage(playerid, "Tidak ada status Donater pada karakter-mu.");

    SendCustomMessage(playerid, X11_LIGHTBLUE, "VIP", "/boombox, /usepoint, /vip, /customooc");
    return 1;
}

/* Timer */

ptask Player_VIPUpdate[10000](playerid)
{
    if(!IsPlayerSpawned(playerid))
        return 0;
		
	if(GetPlayerVIPLevel(playerid) > VIP_LEVEL_NONE && PlayerVIP[playerid][vipExpired] < gettime())
	{
		RemovePlayerVIP(playerid);
		SendServerMessage(playerid, "Masa aktif VIP mu telah habis, terimakasih atas dukungannya!");
        CallLocalFunction(#OnPlayerExpireVIP, "d", playerid);
	}
	return 1;
}
