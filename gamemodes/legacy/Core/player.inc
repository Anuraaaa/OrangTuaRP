stock CheckAccount(playerid)
{
	new query[256];
	mysql_format(sqlcon, query, sizeof(query), "SELECT * FROM `playerucp` WHERE `UCP` = '%e' LIMIT 1;", GetName(playerid));
	mysql_tquery(sqlcon, query, "CheckPlayerUCP", "d", playerid);
	return 1;
}

function PlayerCheck(playerid, rcc)
{
	if(rcc != g_RaceCheck{playerid})
	    return Kick(playerid);

	TogglePlayerSpectating(playerid, true);

	new itrpt_rnd = random(2);

	SendClientMessage(playerid, X11_RED, "(Info) "WHITE"Jika panel register/login belum muncul, "YELLOW"Harap tunggu!");
	if(itrpt_rnd == 0) {
	
		InterpolateCameraPos(playerid, -3077.4265, 431.7690, 69.0493, -2442.3191, 496.1073, 125.3368, 25000, CAMERA_MOVE);
		InterpolateCameraLookAt(playerid, -3076.4797, 432.0866, 68.5543, -2443.1770, 496.6155, 124.8367, 25000, CAMERA_MOVE);
	}
	else {
		InterpolateCameraPos(playerid, -2397.553710, 1436.038452, 140.798019, -2876.055175, 1382.189697, 159.150161, 17000);
		InterpolateCameraLookAt(playerid, -2401.776855, 1438.431640, 139.599197, -2872.188964, 1384.818359, 157.377395, 17000);
	}
	SetPlayerColor(playerid, COLOR_GREY);
	SyncPlayerTime(playerid);

	new query[256];
	mysql_format(sqlcon, query, sizeof(query), "SELECT * FROM `banip` WHERE `IP` = '%e' LIMIT 1;", ReturnIP(playerid));
	mysql_tquery(sqlcon, query, "OnBanIPCheck", "d", playerid);

	return true;
}

function OnBanIPCheck(playerid) {

	if(cache_num_rows()) {

		new admin[24], ip[24], reason[64];
		cache_get_value_name(0, "IP", ip, 24);
		cache_get_value_name(0, "Admin", admin, 24);
		cache_get_value_name(0, "Reason", reason, 64);

		SendClientMessageEx(playerid, X11_ORANGE, "IP Address mu "YELLOW"\"%s\" "ORANGE"telah diblokir dari server.", ip);
		SendClientMessageEx(playerid, X11_ORANGE, "Diblokir oleh: "YELLOW"%s", admin);
		SendClientMessageEx(playerid, X11_ORANGE, "Alasan: "YELLOW"%s", reason);

		KickEx(playerid);
	}
	else CheckAccount(playerid);

	return 1;
}
function CheckPlayerUCP(playerid)
{
	new rows = cache_num_rows();
	new banned, banby[24], banreason[32], bantime;
	new date[6], active;
	new string[364];

	if (rows)
	{
	    cache_get_value_name(0, "UCP", tempUCP[playerid]);
	    cache_get_value_name_int(0, "Banned", banned);
	    cache_get_value_name(0, "BannedBy", banby);
	    cache_get_value_name(0, "BannedReason", banreason);
	    cache_get_value_name_int(0, "BannedTime", bantime);
	    cache_get_value_name_int(0, "Registered", UcpData[playerid][ucpTime]);
	    cache_get_value_name_int(0, "pID", UcpData[playerid][ucpID]);
	    cache_get_value_name_int(0, "Admin", UcpData[playerid][ucpAdmin]);
	    cache_get_value_name(0, "UCP",PlayerData[playerid][pUCP]);
	    cache_get_value_name_int(0, "Active", active);
	    cache_get_value_name_int(0, "code", tempCode[playerid]);
	    cache_get_value_name(0, "email", UcpData[playerid][ucpEmail]);
		cache_get_value_name(0, "Password", UcpData[playerid][uPassword], 128);
		cache_get_value_name_int(0, "DiscordCode", UcpData[playerid][uVerifyCode]);
	    if(banned)
	    {
	    	TimestampToDate(bantime, date[2], date[1], date[0], date[3], date[4], date[5]);

			new zstr[425];
			format(zstr, sizeof(zstr),"{FFFFFF}Your UCP has been Banned from this server\n{FF0000}Reason: {FFFFFF}%s\n{FF0000}Banned By: {FFFFFF}%s\n{FF0000}Banned Date: {FFFFFF}%i/%02d/%02d %02d:%02d\n{FF0000}IP Address: {FFFFFF}%s\n{FFFFFF}Ingin melakukan unbanned? kunjungi "YELLOW"https://discord.gg/EZxPE4Q8Uf", banreason, banby, date[2], date[0], date[1], date[3], date[4],ReturnIP(playerid));
			ShowPlayerDialog(playerid, DIALOG_NONE, DIALOG_STYLE_MSGBOX, "{FFFFFF}Banned Alert - UCP Ban", zstr, "Close", "");	 
			KickEx(playerid);   	
	    }
		else {

			if(active == 0) {
				ShowVerifyMenu(playerid);
			}
			else 
			{
				ShowLoginMenu(playerid);
				LoginTimer[playerid] = SetTimerEx("KickLogin", 30000, false, "d", playerid);
				SendClientMessage(playerid, X11_RED, "(Security) "WHITE"Kamu diberikan waktu "YELLOW"30 detik "WHITE"untuk memasukkan password.");
			}
		}
	}
	else
	{
		format(string,sizeof(string),"{FF0000}Username ini belum terverifikasi!\n{FFFFFF}Silahkan verifikasi di: https://discord.io/orangtuarp");
	    ShowPlayerDialog(playerid, DIALOG_NONE, DIALOG_STYLE_MSGBOX, "Unregistered Username",string,"Close","");
		KickEx(playerid);
	}
	return 1;
}

function KickLogin(playerid) {

	if(IsPlayerSpawned(playerid))
		return 0;

	Kick(playerid);
	return 1;
}
stock SetupPlayerData(playerid)
{
	Inventory_Clear(playerid);
	PlayerData[playerid][pHealth] = 100.0;
	SetSpawnInfo(playerid, 0, PlayerData[playerid][pSkin], -1415.9169,-300.1727,14.1484,134.7111, 0, 0, 0, 0, 0, 0);
	TogglePlayerSpectating(playerid, false);
	SetPlayerPos(playerid, -1425.2041,-291.0014,14.1484);
	SetPlayerFacingAngle(playerid, 135.9490);
	SetPlayerVirtualWorld(playerid, 0);
	SetPlayerInterior(playerid, 0);
	GiveMoney(playerid, 10000, "First Spawn");
	PlayerData[playerid][pBank] = 15000;
	TogglePlayerControllable(playerid, 1);
	SendClientMessageEx(playerid, -1, "Halo "YELLOW"%s"WHITE", Selamat datang di "LIGHTGREEN"Orang Tua Roleplay"WHITE"!", ReturnName(playerid));
	SendClientMessageEx(playerid, -1, "Kamu mendapatkan "GREEN"$100.00 "WHITE"ditangan dan "GREEN"$150.00 "WHITE"pada akun bank-mu.");
	ValidSpawn[playerid] = true;
	
	SetPlayerName(playerid, PlayerData[playerid][pName]);
	SetPlayerLogged(playerid);
    return 1;
}

SQL_SavePlayerPos(playerid) {
	if(IsPlayerSpawned(playerid)) {
		GetPlayerHealth(playerid, PlayerData[playerid][pHealth]);
		GetPlayerArmour(playerid, PlayerData[playerid][pArmor]);

		GetPlayerPos(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);

		new query[1012];
		mysql_format(sqlcon, query, sizeof(query), "UPDATE `characters` SET `PosX` = '%.4f', `PosY` = '%.4f', `PosZ` = '%.4f', `Health` = '%.4f', `Armor` = '%.4f'",
			PlayerData[playerid][pPos][0],
			PlayerData[playerid][pPos][1],
			PlayerData[playerid][pPos][2],
			PlayerData[playerid][pHealth],
			PlayerData[playerid][pArmor]
		);
		mysql_format(sqlcon, query,  sizeof(query), "%s, `Interior` = '%d', `World` = '%d' WHERE `pID` = '%d'",
			query,
			GetPlayerInterior(playerid),
			GetPlayerVirtualWorld(playerid),
			PlayerData[playerid][pID]
		);
		mysql_tquery(sqlcon, query);	
	}
	return 1;
}
SQL_SaveCharacter(playerid)
{
	new query[3612];
	if(IsPlayerSpawned(playerid))
	{
		GetPlayerHealth(playerid, PlayerData[playerid][pHealth]);
		GetPlayerArmour(playerid, PlayerData[playerid][pArmor]);

		GetPlayerPos(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);

		mysql_format(sqlcon, query, sizeof(query), "UPDATE `characters` SET ");
		mysql_format(sqlcon, query, sizeof(query), "%s`PosX`='%f', ", query, PlayerData[playerid][pPos][0]);
        mysql_format(sqlcon, query, sizeof(query), "%s`PosY`='%f', ", query, PlayerData[playerid][pPos][1]);
        mysql_format(sqlcon, query, sizeof(query), "%s`PosZ`='%f', ", query, PlayerData[playerid][pPos][2]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`Health`='%f', ", query, PlayerData[playerid][pHealth]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`World`='%d', ", query, GetPlayerVirtualWorld(playerid));
	    mysql_format(sqlcon, query, sizeof(query), "%s`Interior`='%d', ", query, GetPlayerInterior(playerid));
	    mysql_format(sqlcon, query, sizeof(query), "%s`Age`='%d', ", query, PlayerData[playerid][pAge]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`Origin`='%s', ", query, PlayerData[playerid][pOrigin]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`Gender`='%d', ", query, PlayerData[playerid][pGender]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`Skin`='%d', ", query, PlayerData[playerid][pSkin]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`Accent`='%s', ", query, PlayerData[playerid][pAccent]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`Hunger`='%f', ", query, PlayerData[playerid][pHunger]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`Thirst`='%f', ", query, PlayerData[playerid][pThirst]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`AdminLevel`='%d', ", query, PlayerData[playerid][pAdmin]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`InBiz`='%d', ", query, PlayerData[playerid][pInBiz]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`InHouse`='%d', ", query, PlayerData[playerid][pInHouse]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`Money`='%d', ", query, PlayerData[playerid][pMoney]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`Family`='%d', ", query, PlayerData[playerid][pFamily]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`FamilyRank`='%d', ", query, PlayerData[playerid][pFamilyRank]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`Faction`='%d', ", query, PlayerData[playerid][pFaction]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`FactionRank`='%d', ", query, PlayerData[playerid][pFactionRank]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`FactionID`='%d', ", query, PlayerData[playerid][pFactionID]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`Job`='%d', ", query, PlayerData[playerid][pJob]);
		mysql_format(sqlcon, query, sizeof(query), "%s`Job2`='%d', ", query, PlayerData[playerid][pJob2]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`FactionSkin`='%d', ", query, PlayerData[playerid][pFactionSkin]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`Onduty`='%d', ", query, PlayerData[playerid][pOnDuty]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`Number`='%d', ", query, PlayerData[playerid][pPhoneNumber]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`Armor`='%f', ", query, PlayerData[playerid][pArmor]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`Salary`='%d', ", query, PlayerData[playerid][pSalary]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`Bank`='%d', ", query, PlayerData[playerid][pBank]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`Arrest`='%d', ", query, PlayerData[playerid][pArrest]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`JailTime`='%d', ", query, PlayerData[playerid][pJailTime]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`JailReason`='%s', ", query, PlayerData[playerid][pJailReason]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`JailBy`='%s', ", query, PlayerData[playerid][pJailBy]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`InDoor`='%d', ", query, PlayerData[playerid][pInDoor]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`Injured`='%d', ", query, PlayerData[playerid][pInjured]);
		mysql_format(sqlcon, query, sizeof(query), "%s`Coin`='%d', ", query, PlayerData[playerid][pCoin]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`Credit`='%d', ", query, PlayerData[playerid][pCredit]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`BusDelay`='%d', ", query, PlayerData[playerid][pBusDelay]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`Head`='%f', ", query, PlayerData[playerid][pDamages][0]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`Torso`='%f', ", query, PlayerData[playerid][pDamages][1]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`RightArm`='%f', ", query, PlayerData[playerid][pDamages][2]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`LeftArm`='%f', ", query, PlayerData[playerid][pDamages][3]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`RightLeg`='%f', ", query, PlayerData[playerid][pDamages][4]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`LeftLeg`='%f', ", query, PlayerData[playerid][pDamages][5]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`Groin`='%f', ", query, PlayerData[playerid][pDamages][6]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`Healthy`='%f', ", query, PlayerData[playerid][pHealthy]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`SweeperDelay`='%d', ", query, PlayerData[playerid][pSweeperDelay]);
		mysql_format(sqlcon, query, sizeof(query), "%s`MowerDelay`='%d', ", query, PlayerData[playerid][pMowerDelay]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`TrashmasterDelay`='%d', ", query, PlayerData[playerid][pTrashmasterDelay]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`MaskID`='%d', ", query, PlayerData[playerid][pMaskID]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`Birthdate`='%s', ", query, PlayerData[playerid][pBirthdate]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`Exp`='%d', ", query, PlayerData[playerid][pExp]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`Level`='%d', ", query, PlayerData[playerid][pLevel]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`Hour`='%d', ", query, PlayerData[playerid][pHour]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`Second`='%d', ", query, PlayerData[playerid][pSecond]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`Paycheck`='%d', ", query, PlayerData[playerid][pPaycheck]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`Minute`='%d', ", query, PlayerData[playerid][pMinute]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`Channel`='%d', ", query, PlayerData[playerid][pChannel]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`FishDelay`='%d', ", query, PlayerData[playerid][pFishDelay]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`Funds`='%d', ", query, PlayerData[playerid][pFunds]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`Quitjob`='%d', ", query, PlayerData[playerid][pQuitjob]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`DrivingLicense`='%d', ", query, PlayerData[playerid][pLicense][0]);
		mysql_format(sqlcon, query, sizeof(query), "%s`LumberLicense`='%d', ", query, PlayerData[playerid][pLicense][2]);
		mysql_format(sqlcon, query, sizeof(query), "%s`HaulingLicense`='%d', ", query, PlayerData[playerid][pLicense][3]);
	    mysql_format(sqlcon, query, sizeof(query), "%s`LastLogin`='%d', ", query, gettime());
		mysql_format(sqlcon, query, sizeof(query), "%s`InFlat`='%d', ", query, PlayerData[playerid][pInFlat]);
		mysql_format(sqlcon, query, sizeof(query), "%s`IDCard`='%d', ", query, PlayerData[playerid][pIDCard]);
		mysql_format(sqlcon, query, sizeof(query), "%s`IDCardExpired`='%d', ", query, PlayerData[playerid][pIDCardExpired]);
		mysql_format(sqlcon, query, sizeof(query), "%s`MineDelay`='%d', ", query, PlayerData[playerid][pMineDelay]);
		mysql_format(sqlcon, query, sizeof(query), "%s`FactionHour`='%d', ", query, PlayerData[playerid][pFactionHour]);
		mysql_format(sqlcon, query, sizeof(query), "%s`FactionMinute`='%d', ", query, PlayerData[playerid][pFactionMinute]);
		mysql_format(sqlcon, query, sizeof(query), "%s`FactionSecond`='%d', ", query, PlayerData[playerid][pFactionSecond]);
		mysql_format(sqlcon, query, sizeof(query), "%s`HaulingDelay`='%d', ", query, PlayerData[playerid][pHaulingDelay]);
		mysql_format(sqlcon, query, sizeof(query), "%s`MarryWith`='%s', ", query, MarryWith[playerid]);
		mysql_format(sqlcon, query, sizeof(query), "%s`MarryDate`='%s', ", query, MarryDate[playerid]);
		mysql_format(sqlcon,  query, sizeof(query), "%s`Masked`='%d', ", query, PlayerData[playerid][pMasked]);
		mysql_format(sqlcon, query, sizeof(query), "%s`HudType`='%d', ", query, PlayerData[playerid][pHudType]);
		mysql_format(sqlcon, query, sizeof(query), "%s`AdminPoint`='%d', ", query, PlayerData[playerid][pAdminPoint]);
		forex(i, 10)
		{
			mysql_format(sqlcon, query, sizeof(query), "%s`Fish%d` = '%.1f', `FishName%d` = '%s', ", query, i + 1, FishWeight[playerid][i], i + 1, FishName[playerid][i]);
		}
		forex(i, 13)
		{
			mysql_format(sqlcon, query, sizeof(query), "%s`Gun%d` = '%d', `Ammo%d` = '%d', `Durability%d` = '%d', `HighVelocity%d` = '%d', ", query, i + 1, PlayerData[playerid][pGuns][i], i + 1, PlayerData[playerid][pAmmo][i], i + 1, PlayerData[playerid][pDurability][i], i + 1, PlayerData[playerid][pHighVelocity][i], i + 1);
		}
		forex(i, 7)
		{
			mysql_format(sqlcon, query, sizeof(query), "%s`Bullet%d` = '%d', ", query, i + 1, PlayerData[playerid][pBullets][i]);
		}
		mysql_format(sqlcon, query, sizeof(query), "%s`CourierDelay`='%d', ", query, PlayerData[playerid][pCourierDelay]);
		mysql_format(sqlcon, query, sizeof(query), "%s`TogLogin`='%d', ", query, PlayerData[playerid][pTogLogin]);
		mysql_format(sqlcon, query, sizeof(query), "%s`AutoPaycheck`='%d', ", query, PlayerData[playerid][pAutoPaycheck]);
		mysql_format(sqlcon, query, sizeof(query), "%s`InWorkshop`='%d', ", query, PlayerData[playerid][pInWorkshop]);
		mysql_format(sqlcon, query, sizeof(query), "%s`Fever`='%d', ", query, PlayerData[playerid][pFever]);
		mysql_format(sqlcon, query, sizeof(query), "%s`Cough`='%d', ", query, PlayerData[playerid][pCough]);
		mysql_format(sqlcon, query, sizeof(query), "%s`Badge`='%d', ", query, PlayerData[playerid][pFactionBadge]);
		mysql_format(sqlcon, query, sizeof(query), "%s`Quitjob`='%d', `DriverDelay`='%d', `LumberDelay` = '%d' ", query, PlayerData[playerid][pQuitjob], PlayerData[playerid][pDriverDelay], PlayerData[playerid][pLumberDelay]);
	    mysql_format(sqlcon, query, sizeof(query), "%sWHERE `pID` = %d", query, PlayerData[playerid][pID]);
		mysql_tquery(sqlcon, query);
		SQL_SavePlayerPos(playerid);
	}
	return 1;
}

function LoadCharacterData(playerid)
{

	if(!IsPlayerConnected(playerid))
		return 0;

	cache_get_value_name_int(0, "pID", PlayerData[playerid][pID]);
	cache_get_value_name(0, "Name", PlayerData[playerid][pName]);
	cache_get_value_name_float(0, "PosX", PlayerData[playerid][pPos][0]);
	cache_get_value_name_float(0, "PosY", PlayerData[playerid][pPos][1]);
	cache_get_value_name_float(0, "PosZ", PlayerData[playerid][pPos][2]);
	cache_get_value_name_float(0, "Health", PlayerData[playerid][pHealth]);
	cache_get_value_name_int(0, "Interior", PlayerData[playerid][pInterior]);
	cache_get_value_name_int(0, "World", PlayerData[playerid][pWorld]);
	cache_get_value_name_int(0, "Age", PlayerData[playerid][pAge]);
	cache_get_value_name(0, "Origin", PlayerData[playerid][pOrigin]);
	cache_get_value_name_int(0, "Gender", PlayerData[playerid][pGender]);
	cache_get_value_name_int(0, "Skin", PlayerData[playerid][pSkin]);
	//cache_get_value_name(0, "UCP", PlayerData[playerid][pUCP]);
	cache_get_value_name(0, "Accent", PlayerData[playerid][pAccent]);
	cache_get_value_name_float(0, "Hunger", PlayerData[playerid][pHunger]);
	cache_get_value_name_float(0, "Thirst", PlayerData[playerid][pThirst]);
	cache_get_value_name_int(0, "AdminLevel", PlayerData[playerid][pAdmin]);
	cache_get_value_name_int(0, "InBiz", PlayerData[playerid][pInBiz]);
	cache_get_value_name_int(0, "InHouse", PlayerData[playerid][pInHouse]);
	cache_get_value_name_int(0, "Money", PlayerData[playerid][pMoney]);
	cache_get_value_name_int(0, "Job", PlayerData[playerid][pJob]);
	cache_get_value_name_int(0, "Job2", PlayerData[playerid][pJob2]);
	cache_get_value_name_int(0, "Number", PlayerData[playerid][pPhoneNumber]);
	cache_get_value_name_int(0, "Faction", PlayerData[playerid][pFaction]);
	cache_get_value_name_int(0, "FactionRank", PlayerData[playerid][pFactionRank]);
	cache_get_value_name_int(0, "FactionID", PlayerData[playerid][pFactionID]);
	cache_get_value_name_int(0, "FactionSkin", PlayerData[playerid][pFactionSkin]);
	cache_get_value_name_int(0, "Family", PlayerData[playerid][pFamily]);
	cache_get_value_name_int(0, "FamilyRank", PlayerData[playerid][pFamilyRank]);
	cache_get_value_name_int(0, "Onduty", PlayerData[playerid][pOnDuty]);
	cache_get_value_name(0, "Birthdate", PlayerData[playerid][pBirthdate], 24);
	cache_get_value_name_float(0, "Armor", PlayerData[playerid][pArmor]);
	cache_get_value_name_int(0, "Coin", PlayerData[playerid][pCoin]);
	cache_get_value_name_int(0, "Salary", PlayerData[playerid][pSalary]);
	cache_get_value_name_int(0, "Bank", PlayerData[playerid][pBank]);
	cache_get_value_name_int(0, "Credit", PlayerData[playerid][pCredit]);
	cache_get_value_name_int(0, "InDoor", PlayerData[playerid][pInDoor]);
	cache_get_value_name_int(0, "Arrest", PlayerData[playerid][pArrest]);
	cache_get_value_name_int(0, "JailTime", PlayerData[playerid][pJailTime]);
	cache_get_value_name(0, "JailReason", PlayerData[playerid][pJailReason]);
	cache_get_value_name(0, "JailBy", PlayerData[playerid][pJailBy]);
	cache_get_value_name_int(0, "Injured", PlayerData[playerid][pInjured]);
	cache_get_value_name_int(0, "TrashmasterDelay", PlayerData[playerid][pTrashmasterDelay]);
	cache_get_value_name_int(0, "SweeperDelay", PlayerData[playerid][pSweeperDelay]);
	cache_get_value_name_int(0, "DriverDelay", PlayerData[playerid][pDriverDelay]);
	cache_get_value_name_int(0, "MowerDelay", PlayerData[playerid][pMowerDelay]);
	cache_get_value_name_int(0, "BusDelay", PlayerData[playerid][pBusDelay]);
	cache_get_value_name_int(0, "MaskID", PlayerData[playerid][pMaskID]);
	cache_get_value_name_int(0, "HaulingDelay", PlayerData[playerid][pHaulingDelay]);
	cache_get_value_name_int(0, "Masked",  PlayerData[playerid][pMasked]);
	cache_get_value_name_float(0, "Head", PlayerData[playerid][pDamages][0]);
	cache_get_value_name_float(0, "Torso", PlayerData[playerid][pDamages][1]);
	cache_get_value_name_float(0, "RightArm", PlayerData[playerid][pDamages][2]);
	cache_get_value_name_float(0, "LeftArm", PlayerData[playerid][pDamages][3]);
	cache_get_value_name_float(0, "RightLeg", PlayerData[playerid][pDamages][4]);
	cache_get_value_name_float(0, "LeftLeg", PlayerData[playerid][pDamages][5]);
	cache_get_value_name_float(0, "Groin", PlayerData[playerid][pDamages][6]);
	cache_get_value_name_float(0, "Healthy", PlayerData[playerid][pHealthy]);
	cache_get_value_name_int(0, "Level", PlayerData[playerid][pLevel]);
	cache_get_value_name_int(0, "Exp", PlayerData[playerid][pExp]);
	cache_get_value_name_int(0, "Second", PlayerData[playerid][pSecond]);
	cache_get_value_name_int(0, "Hour", PlayerData[playerid][pHour]);
	cache_get_value_name_int(0, "Minute", PlayerData[playerid][pMinute]);
	cache_get_value_name_int(0, "Paycheck", PlayerData[playerid][pPaycheck]);
	cache_get_value_name_int(0, "Quitjob", PlayerData[playerid][pQuitjob]);
	cache_get_value_name_int(0, "Channel", PlayerData[playerid][pChannel]);
	cache_get_value_name_int(0, "Funds", PlayerData[playerid][pFunds]);
	cache_get_value_name_int(0, "DrivingLicense", PlayerData[playerid][pLicense][0]);
	cache_get_value_name_int(0, "LumberLicense", PlayerData[playerid][pLicense][2]);
	cache_get_value_name_int(0, "HaulingLicense", PlayerData[playerid][pLicense][3]);
	cache_get_value_name_int(0, "FishDelay", PlayerData[playerid][pFishDelay]);
	cache_get_value_name_int(0, "InFlat", PlayerData[playerid][pInFlat]);
	cache_get_value_name_int(0, "AutoPaycheck", PlayerData[playerid][pAutoPaycheck]);
	cache_get_value_name_int(0, "LumberDelay", PlayerData[playerid][pLumberDelay]);
	cache_get_value_name_int(0, "IDCard", PlayerData[playerid][pIDCard]);
	cache_get_value_name_int(0, "IDCardExpired", PlayerData[playerid][pIDCardExpired]);
	cache_get_value_name_int(0, "Fever", PlayerData[playerid][pFever]);
	cache_get_value_name_int(0, "Cough", PlayerData[playerid][pCough]);
	cache_get_value_name_int(0, "InWorkshop", PlayerData[playerid][pInWorkshop]);
	cache_get_value_name_int(0, "TogLogin", PlayerData[playerid][pTogLogin]);
	cache_get_value_name_int(0, "Badge", PlayerData[playerid][pFactionBadge]);
	cache_get_value_name_int(0, "MineDelay", PlayerData[playerid][pMineDelay]);
	cache_get_value_name_int(0, "FactionHour", PlayerData[playerid][pFactionHour]);
	cache_get_value_name_int(0, "FactionMinute", PlayerData[playerid][pFactionMinute]);
	cache_get_value_name_int(0, "FactionSecond", PlayerData[playerid][pFactionSecond]);
	cache_get_value_name_int(0, "CourierDelay", PlayerData[playerid][pCourierDelay]);
	cache_get_value_name(0, "MarryWith", MarryWith[playerid], 24);
	cache_get_value_name(0, "MarryDate", MarryDate[playerid], 28);
	cache_get_value_name_int(0, "HudType", PlayerData[playerid][pHudType]);
	cache_get_value_name_int(0, "AdminPoint", PlayerData[playerid][pAdminPoint]);

	SetPlayerName(playerid, PlayerData[playerid][pName]);
	forex(i, 7)
	{
		new lquery[128];
		format(lquery, sizeof(lquery), "Bullet%d", i + 1);
		cache_get_value_name_int(0, lquery, PlayerData[playerid][pBullets][i]);
	}
	forex(i, 13)
	{
	    new zquery[256];
	    format(zquery, sizeof(zquery), "Gun%d", i + 1);
	    cache_get_value_name_int(0,zquery,PlayerData[playerid][pGuns][i]);

	    format(zquery, sizeof(zquery), "Ammo%d", i + 1);
	    cache_get_value_name_int(0,zquery,PlayerData[playerid][pAmmo][i]);

	    format(zquery, sizeof(zquery), "Durability%d", i + 1);
	    cache_get_value_name_int(0,zquery,PlayerData[playerid][pDurability][i]);

	    format(zquery, sizeof(zquery), "HighVelocity%d", i + 1);
	    cache_get_value_name_int(0,zquery,PlayerData[playerid][pHighVelocity][i]);
	}
    for(new i = 0; i < 10; i++)
    {
		new zquery[256];
		format(zquery, sizeof(zquery), "Fish%d", i + 1);
		cache_get_value_name_float(0, zquery, FishWeight[playerid][i]);

		format(zquery, sizeof(zquery), "FishName%d", i + 1);
		cache_get_value_name(0, zquery, FishName[playerid][i]);
	}
	new invQuery[256];
	new contactQuery[256];

	new ticketQuery[256];


	new string[128];
	mysql_format(sqlcon, string, sizeof(string), "SELECT * FROM weaponsettings WHERE Owner = '%d'", PlayerData[playerid][pID]);
	mysql_tquery(sqlcon, string, "OnWeaponsLoaded", "d", playerid);

	mysql_format(sqlcon, ticketQuery, sizeof(ticketQuery), "SELECT * FROM `tickets` WHERE `ID` = '%d'", PlayerData[playerid][pID]);
	mysql_tquery(sqlcon, ticketQuery, "LoadPlayerTicket", "d", playerid);

    mysql_format(sqlcon,invQuery, sizeof(invQuery), "SELECT * FROM `inventory` WHERE `ID` = '%d'", PlayerData[playerid][pID]);
	mysql_tquery(sqlcon, invQuery, "LoadPlayerItems", "d", playerid);

	mysql_format(sqlcon, contactQuery, sizeof(contactQuery), "SELECT * FROM `contacts` WHERE `ID` = %d", PlayerData[playerid][pID]);
	mysql_tquery(sqlcon, contactQuery, "LoadPlayerContact", "d", playerid);

	mysql_tquery(sqlcon, sprintf("SELECT * FROM `aksesoris` WHERE `accID` = '%d' ORDER BY `accID` DESC LIMIT %d", PlayerData[playerid][pID], MAX_ACC), "Aksesoris_Load", "d", playerid);

    SetSpawnInfo(playerid, 0, PlayerData[playerid][pSkin], PlayerData[playerid][pPos][0] + 0.3, PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2], 0.0, 0, 0, 0, 0, 0, 0);
    TogglePlayerSpectating(playerid, false);

	mysql_tquery(sqlcon, sprintf("UPDATE `characters` SET `LastIP` = '%s' WHERE `Name` = '%s'", ReturnIP(playerid), GetName(playerid)));
	mysql_tquery(sqlcon, sprintf("UPDATE `playerucp` SET `LastIP` = '%s' WHERE `UCP` = '%s'", ReturnIP(playerid), GetUsername(playerid)));
	
    LoadPlayerVehicle(playerid);
	LoadRentalVehicle(playerid);

	PlayerData[playerid][pLogged] = true;

	CallLocalFunction("OnPlayerLogin", "d", playerid);
	ValidSpawn[playerid] = true;
    return 1;
}

function OnPlayerPasswordChange(playerid, hashid)
{
	new
		query[256],
		hash[BCRYPT_HASH_LENGTH];

    bcrypt_get_hash(hash, sizeof(hash));

	mysql_format(sqlcon,query,sizeof(query),"UPDATE `playerucp` SET `password` = '%e' WHERE `UCP` = '%e'",hash, GetUsername(playerid));
	mysql_tquery(sqlcon,query);

	SendServerMessage(playerid, "Password akunmu berhasil diubah!");
	return 1;
}
function HashPlayerPassword(playerid, hashid)
{
	new
		query[356],
		hash[BCRYPT_HASH_LENGTH];

    bcrypt_get_hash(hash, sizeof(hash));

	GetPlayerName(playerid, tempUCP[playerid], MAX_PLAYER_NAME + 1);

	mysql_format(sqlcon, query,sizeof(query),"UPDATE `playerucp` SET `password` = '%e', `Registered` = '%d', `Active` = '%d' WHERE `UCP` = '%e'", hash, gettime(), 1, tempUCP[playerid]);
	mysql_tquery(sqlcon,query, #OnPasswordCreated, "d", playerid);

	return 1;
}

function OnPasswordCreated(playerid) {
	UcpData[playerid][ucpID] = cache_insert_id();


    SendServerMessage(playerid, "Akunmu berhasil terdaftar pada server!");
    CheckAccount(playerid);

	return 1;
}
stock HideCharacter(playerid)
{
	forex(i, 5)
	{
		PlayerTextDrawHide(playerid, UCPTD[playerid][i]);
	}
	forex(i, 3)
	{
		PlayerTextDrawHide(playerid, CHARTD[playerid][i]);
	}
	CancelSelectTextDraw(playerid);
	return 1;
}
//----- [ Textdraw Login ]
/*stock ShowCharacterList(playerid)
{
	SelectTextDraw(playerid, COLOR_YELLOW);
	//new name[256], count, sgstr[128];
	forex(i, 5)
	{
		PlayerTextDrawShow(playerid, UCPTD[playerid][i]);
	}
	forex(i, MAX_CHARS)
	{
		PlayerTextDrawShow(playerid, CHARTD[playerid][i]);
		PlayerTextDrawSetString(playerid, CHARTD[playerid][i], sprintf("%s", (PlayerChar[playerid][i][0] == EOS) ? ("Empty_Slot") : (PlayerChar[playerid][i])));
	}
	return 1;
}

function LoadCharacter(playerid)
{
	for (new i = 0; i < MAX_CHARS; i ++)
	{
		PlayerChar[playerid][i][0] = EOS;
	}
	for (new i = 0; i < cache_num_rows(); i ++)
	{
		cache_get_value_name(i, "Name", PlayerChar[playerid][i]);
	}
  	ShowCharacterList(playerid);
  	return 1;
}*/
stock ShowCharacterList(playerid)
{
	new name[256], count, sgstr[128];	
	
	forex(i, MAX_CHARS) if(PlayerChar[playerid][i][0] != EOS)
	{
	    format(sgstr, sizeof(sgstr), "{ffffff}%s\t%d\t%s\n", PlayerChar[playerid][i], PlayerLevel[playerid][i], ConvertTimestamp(Timestamp:PlayerLastLogin[playerid][i]));
		strcat(name, sgstr);
		count++;
	}
	if(count < MAX_CHARS)
		strcat(name, ""RED"(buat karakter baru)");
	strins(name, "Character\tLevel\tLast Played\n", 0);
	ShowPlayerDialog(playerid, DIALOG_CHARACTER_LIST, DIALOG_STYLE_TABLIST_HEADERS, "Character List", name, "Select", "Quit");
	return 1;
}

function LoadCharacter(playerid)
{
	for (new i = 0; i < MAX_CHARS; i ++)
	{
		PlayerChar[playerid][i][0] = EOS;
	}
	for (new i = 0; i < cache_num_rows(); i ++)
	{
		cache_get_value_name(i, "Name", PlayerChar[playerid][i]);
		cache_get_value_name_int(i, "Level", PlayerLevel[playerid][i]);
		cache_get_value_name_int(i, "LastLogin", PlayerLastLogin[playerid][i]);
	}
  	ShowCharacterList(playerid);
  	return 1;
}

stock ShowVerifyMenu(playerid) {
	new str[256];
	format(str, sizeof(str), "Akun-mu belum terverifikasi! masukkan kode PIN untuk me-verifikasi akunmu:\n\n(note) kode pin bisa dilihat dari Bot Orang Tua Roleplay.");
	return ShowPlayerDialog(playerid, DIALOG_VERIFY, DIALOG_STYLE_INPUT, "Account Verification", str, "Confirm", "Close");
}
stock ShowRegisterMenu(playerid) {

	new str[256];
	format(str, sizeof(str), ""WHITE"Selamat datang di "LIGHTBLUE"%s\n\n"WHITE"Akun-mu belum terdaftar di server, masukkan password-mu dibawah untuk membuat akun.\n"GREY"Untuk keamanan akun, masukkan "TOMATO"password unik "GREY"yang belum pernah kamu gunakan:", SERVER_NAME);
	ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD, "OT:RP - Register", str, "Confirm", "Exit");
	return 1;
}

stock ShowLoginMenu(playerid) {

	new str[256];
	format(str, sizeof(str), ""WHITE"Selamat datang kembali di "LIGHTBLUE"%s\n\n"WHITE"Akun-mu telah terdaftar di server.\nMasukkan password akun-mu untuk login:", SERVER_NAME);
	return ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "OT:RP - Login", str, "Login", "Exit");
}
function OnPlayerPasswordChecked(playerid, bool:success)
{

	if(!success)
	{
	    if(PlayerData[playerid][pAttempt] < 5)
	    {
		    PlayerData[playerid][pAttempt]++;
	        ShowLoginMenu(playerid);
		}
		else
		{
		    SendServerMessage(playerid, "Kamu telah salah memasukan password sebanyak {FFFF00}3 kali!");
		    KickEx(playerid);
		}
	}
	else
	{
		new query[256];
		mysql_format(sqlcon, query, sizeof(query), "SELECT `Name`, `Level`, `LastLogin` FROM `characters` WHERE `UCP` = '%s' LIMIT %d;", GetName(playerid), MAX_CHARS);
		mysql_tquery(sqlcon, query, "LoadCharacter", "d", playerid);
		KillTimer(LoginTimer[playerid]);

	}
	return 1;
}

stock IsNameUsed(playerid, name[]) {

	new bool:ada = false;

	foreach(new i : Player) if(IsPlayerSpawned(i) && !strcmp(GetUsername(i), name, true) && i != playerid) {
		ada = true;
		break;
	}
	return ada;
}
//-----[Textdraw Login]
/*function InsertPlayerName(playerid, name[])
{
	new count = cache_num_rows();
	if(count > 0)
	{
        ShowPlayerDialog(playerid, DIALOG_MAKECHAR, DIALOG_STYLE_INPUT, "Character Name", "ERROR: This name is already used by the other player!\nInsert your Character Name\n\nExample: Finn_Xanderz, Javier_Cooper etc.", "Submit", "Cancel");
	}
	else
	{
		format(PlayerData[playerid][pTempName], MAX_PLAYER_NAME, name);
		PlayerTextDrawSetString(playerid, NAMETD[playerid], sprintf("%s", PlayerData[playerid][pTempName]));
		SelectTextDraw(playerid, COLOR_YELLOW);
	}
	return 1;
}*/

function InsertPlayerName(playerid, name[])
{
	if(cache_num_rows())
	{
        ShowPlayerDialog(playerid, DIALOG_MAKECHAR, DIALOG_STYLE_INPUT, "Character Name", "(error) nama ini sudah digunakan!\n\nSilahkan masukan nama karaktermu:\n(note) nama karakter harus nama Roleplay!", "Submit", "Cancel");
	}
	else
	{
		format(PlayerData[playerid][pTempName], MAX_PLAYER_NAME, name);
		ShowCharacterSetup(playerid);
	}
	return 1;
}

stock ReturnName(playerid)
{
    static
        name[MAX_PLAYER_NAME + 1];

    GetPlayerName(playerid, name, sizeof(name));
    if(PlayerData[playerid][pMasked])
    {
        format(name, sizeof(name), "Unknown_#%d", PlayerData[playerid][pMaskID]);
	}
	else
	{
	    for (new i = 0, len = strlen(name); i < len; i ++)
		{
	        if (name[i] == '_') name[i] = ' ';
		}
	}
    return name;
}

stock ReturnIP(playerid)
{
	static
	    ip[16];

	GetPlayerIp(playerid, ip, sizeof(ip));
	return ip;
}

stock GetName(playerid, bool:underscore = true)
{
	new name[MAX_PLAYER_NAME];
	GetPlayerName(playerid,name,sizeof(name));

	if(!underscore) {

		for (new i = 0, len = strlen(name); i < len; i ++)
		{
	        if (name[i] == '_') name[i] = ' ';
		}
	}
	return name;
}

stock CheckPlayerJob(playerid, job = JOB_NONE) {
	if(PlayerData[playerid][pJob] != job && PlayerData[playerid][pJob2] != job)
		return 0;

	return 1;
}

stock IsHungerOrThirst(playerid) {

	if(PlayerData[playerid][pHunger] < 20)
		return 1;

	if(PlayerData[playerid][pThirst] < 20)
		return 1;
	
	return 0;
}
stock ResetPlayerStatistics(playerid)
{

	PlayerData[playerid][pLastNumber] = 0;
	PlayerData[playerid][pCourierDelay] = 0;
	PlayerData[playerid][pHudType] = 1;

	format(MarryWith[playerid], 24, "Unknown");
	format(MarryDate[playerid], 28, "None");
	format(PlayerData[playerid][pUCP], 24, "None");

	HasRubberBullet[playerid] = false;
	PlayerRubbed[playerid] = false;
	PlayerData[playerid][pID] = -1;
	ResetPlayerOutsideInfo(playerid);
	Helmet[playerid] = 0;
	
	PlayerData[playerid][pCallNews] = false;
	PlayerData[playerid][pCoin] = 0;
	chat_floodProtect[playerid]  = 0;
	cmd_floodProtect[playerid] = 0;
	
	g_EngineHack[playerid] = 0;
	
	PlayerData[playerid][pAdoLabel] = Text3D:INVALID_3DTEXT_ID;
	PlayerData[playerid][pMaskLabel] = Text3D:INVALID_3DTEXT_ID;
	PlayerData[playerid][pToggleSpeed] = true;
	
	PlayerData[playerid][pAhide] = false;
	PlayerData[playerid][pMineDelay] = 0;
	PlayerData[playerid][pMicrophone] = false;
	PlayerData[playerid][pFactionBadge] = 0;
	PlayerData[playerid][pDoorDelay] = 0;
	PlayerData[playerid][pInWorkshop] = -1;
	PlayerData[playerid][pUsePill] = 0;
	PlayerData[playerid][pFeverTime] = 0;
	PlayerData[playerid][pCoughTime] = 0;
	PlayerData[playerid][pFeverRate] = 0;
	PlayerData[playerid][pCoughRate] = 0;
	PlayerData[playerid][pFever] = 0;
	PlayerData[playerid][pCough] = 0;
	PlayerData[playerid][pAksesoris] = -1;
	PlayerData[playerid][pDriverDelay] = 0;
	askDelay[playerid] = 0;
	reportDelay[playerid] = 0;
	PlayerData[playerid][pJob2] = JOB_NONE;
	PlayerData[playerid][pBandage] = false;
	PlayerData[playerid][pAutoPaycheck] = false;
	liveMode[playerid] = false;
	PlayerData[playerid][pLumberDelay] = 0;
	PlayerData[playerid][pDrugTime] = 0;
	PlayerData[playerid][pDrugCondition] = false;
	PlayerData[playerid][pRumpoVehicle] = INVALID_VEHICLE_ID;
	PlayerData[playerid][pForkliftVehicle] = INVALID_VEHICLE_ID;
	PlayerData[playerid][pPMLog] = false;
	PlayerData[playerid][pMowerDelay] = 0;
	LewatConnect[playerid] = true;
	ValidSpawn[playerid] = false;
	PlayerData[playerid][pVynMode] = false;
	PlayerData[playerid][pIDCard] = 0;
	PlayerData[playerid][pIDCardExpired] = 0;
	PlayerData[playerid][pKicked] = false;
	PlayerData[playerid][pLastWeapon] = 0;
	PlayerData[playerid][pIsDrunk] = false;
	PlayerData[playerid][pTaxiVehicleID] = INVALID_VEHICLE_ID;
	PlayerData[playerid][pLastVehicleID] = INVALID_VEHICLE_ID;
	PlayerData[playerid][pAMSG] = true;
	PlayerData[playerid][pVehicleOffer] = -1;
	PlayerData[playerid][pVehicleOfferID] = INVALID_PLAYER_ID;
	PlayerData[playerid][pFlatOffer] = -1;
	PlayerData[playerid][pFlatOfferID] = INVALID_PLAYER_ID;
	PlayerData[playerid][pHouseOffer] = -1;
	PlayerData[playerid][pHouseOfferID] = INVALID_PLAYER_ID;
	PlayerData[playerid][pNewsGuest] = INVALID_PLAYER_ID;
	PlayerData[playerid][pBroadcast] = false;
	PlayerData[playerid][pInFlat] = -1;
	InHospital[playerid] = false;
	format(TagFont[playerid], 24, "Arial");
	TagSize[playerid] = 24;
	TagBold[playerid] = 0;
	TagColor[playerid] = 0xFFFFFFFF;
	PlayerData[playerid][pTogBuy] = true;
	PlayerData[playerid][pTogHud] = false;
	PlayerData[playerid][pTogAnim] = true;
	PlayerData[playerid][pTogPM] = false;
	PlayerData[playerid][pTogLogin] = false;
	PlayerData[playerid][pTogGlobal] = false;
	PlayerData[playerid][pDutyTime] = 3600;
	PlayerData[playerid][pDragOffer] = INVALID_PLAYER_ID;
	PlayerData[playerid][pFishing] = false;
	PlayerData[playerid][pFishDelay] = 0;
	PlayerData[playerid][pLogged] = false;
	PlayerData[playerid][pTaxiCalled] = false;
	PlayerData[playerid][pInterior] = 0;
	PlayerData[playerid][pInTuning] = false;
	PlayerData[playerid][pSeatbelt] = false;
	PlayerData[playerid][pEditGate] = 0;
	PlayerData[playerid][pAdmin] = 0;
	PlayerMedia[playerid][samLogged] = false;
	format(PlayerMedia[playerid][samName], MAX_PLAYER_NAME, "");
	PlayerData[playerid][pHaveDrivingLicense] = false;
	PlayerData[playerid][pOnTest] = false;
	PlayerData[playerid][pIndexTest] = 0;
	PlayerData[playerid][pVehicleDMV] = INVALID_VEHICLE_ID;
	PlayerData[playerid][pOnDMV] = false;
	PlayerData[playerid][pAFK] = 0;
	PlayerData[playerid][pIndexDMV] = -1;
	PlayerData[playerid][pWeapon] = 0;
	PlayerData[playerid][pFunds] = false;
	PlayerData[playerid][pTazed] = false;
	PlayerData[playerid][pTazer] = false;
	g_EquipItem[playerid] = EQUIP_ITEM_NONE;
	WeaponTick[playerid] = 0;
	EditingWeapon[playerid] = 0;
	PlayerData[playerid][pCutting] = -1;
	PlayerData[playerid][pEditing] = -1;
	PlayerData[playerid][pEditType] = -1;
	PlayerData[playerid][pFirstAid] = false;
	PlayerData[playerid][pAduty] = false;
	PlayerData[playerid][pVendor] = -1;
	PlayerData[playerid][pChannel] = 0;
	PlayerData[playerid][pArmor] = 0.0;
	PlayerData[playerid][pQuitjob] = 0;
	PlayerData[playerid][pMinutes] = 0;
	PlayerData[playerid][pDutySecond] = 0;
	PlayerData[playerid][pDutyMinute] = 0;
	PlayerData[playerid][pDutyHour] = 0;
	PlayerData[playerid][pFrisked] = INVALID_PLAYER_ID;
	IsDragging[playerid] = INVALID_PLAYER_ID;
	PlayerData[playerid][pSpectator] = INVALID_PLAYER_ID;
	PlayerData[playerid][pInHouse] = -1;
	Falling[playerid] = false;
	PlayerData[playerid][pHour] = 0;
	PlayerData[playerid][pPaycheck] = 0;
	PlayerData[playerid][pMinute] = 0;
	PlayerData[playerid][pSecond] = 0;
	LoginTimer[playerid] = 0;

	PlayerData[playerid][pLevel] = 1;
	PlayerData[playerid][pExp] = 0;
	PlayerData[playerid][pMasked] = false;
	PlayerData[playerid][pSelecting] = -1;
	PlayerData[playerid][pEditingItem] = -1;
	PlayerPressedJump[playerid] = 0;
	PlayerData[playerid][pMaskID] = 0;
	PlayerData[playerid][pHealthy] = 100.0;
	PlayerData[playerid][pTargetid] = INVALID_PLAYER_ID;
	PlayerData[playerid][pCallLine] = INVALID_PLAYER_ID;
	PlayerData[playerid][pIncomingCall] = 0;
	PlayerData[playerid][pCredit] = 0;
	PlayerData[playerid][pPhoneNumber] = 0;
	tempCode[playerid] = 0;
	ServiceIndex[playerid] = 0;
	PlayerData[playerid][pCuffed] = false;
	SweeperIndex[playerid] = -1;
	PlayerData[playerid][pInjuredTime] = 600;
	OnSweeping[playerid] = false;
	PlayerData[playerid][pBusDelay] = 0;
	PlayerData[playerid][pSweeperDelay] = 0;
	PlayerData[playerid][pTrashmasterDelay] = 0;
	PlayerData[playerid][pDead] = false;
	PlayerData[playerid][pInjured] = false;
	PlayerData[playerid][pArrest] = false;
	PlayerData[playerid][pJailTime] = 0;
	PlayerData[playerid][pMarkActive] = false;
	PlayerData[playerid][pAsking] = false;
	PlayerData[playerid][pFreeze] = 0;
	PlayerData[playerid][pInDoor] = -1;
	PlayerData[playerid][pSalary] = 0;
	BusIndex[playerid] = 0;
	PlayerData[playerid][pBank] = 0;
	OnBus[playerid] = false;
	format(PlayerData[playerid][pTempName], MAX_PLAYER_NAME, "");
	format(PlayerData[playerid][pBirthdate], 24, "");
	PlayerData[playerid][pGender] = 0;
	format(PlayerData[playerid][pOrigin], 32, "");
	PlayerData[playerid][pFactionOffered] = -1;
	PlayerData[playerid][pFactionOffer] = INVALID_PLAYER_ID;
	PlayerData[playerid][pOnDuty] = false;
	PlayerData[playerid][pFactionSkin] = 0;
	PlayerData[playerid][pFactionID] = -1;
	PlayerData[playerid][pFactionRank] = 0;
	PlayerData[playerid][pSelectedSlot] = -1;
	PlayerData[playerid][pFaction] = -1;
	PlayerData[playerid][pSpraying] = false;
	PlayerData[playerid][pSprayStart] = false;
	PlayerData[playerid][pColor] = 0;
	PlayerData[playerid][pColoring] = 0;
	PlayerData[playerid][pMechPrice][0] = 0;
	PlayerData[playerid][pMechPrice][1] = 0;
	PlayerData[playerid][pTotalFare] = 0;
	PlayerData[playerid][pInTaxi] = false;
	PlayerData[playerid][pJobduty] = false;
	PlayerData[playerid][pFare] = 0;
	PlayerData[playerid][pWP] = false;
	PlayerData[playerid][pHunger] = 100;
	PlayerData[playerid][pThirst] = 100;
	PlayerData[playerid][pTracking] = false;
	PlayerData[playerid][pMoney] = 0;
	PlayerData[playerid][pInBiz] = -1;
	PlayerData[playerid][pListitem] = -1;
	PlayerData[playerid][pAttempt] = 0;
	PlayerData[playerid][pCalling] = INVALID_PLAYER_ID;
	PlayerData[playerid][pSpawned] = false;
	PlayerData[playerid][pCrate] = -1;
	PlayerData[playerid][pVehicle] = -1;
	PlayerData[playerid][pBusiness] = -1;
	PlayerData[playerid][pJob] = JOB_NONE;
	PlayerData[playerid][pJobSelect] = JOB_NONE;
	PlayerData[playerid][pWS] = -1;
    PlayerData[playerid][pBoomboxPlaced] = 0;
	PlayerData[playerid][pBoomboxListen] = INVALID_PLAYER_ID;
    PlayerData[playerid][pStreamType] = MUSIC_NONE;
	PlayerData[playerid][pTogMusic] = false;
	PlayerData[playerid][pFamily] = -1;
	PlayerData[playerid][pFamilyRank] = 0;
	PlayerData[playerid][pFamilyOffered] = -1;
	PlayerData[playerid][pFamilyOffer] = INVALID_PLAYER_ID;
	PlayerData[playerid][pACWarning] = 0;
	PlayerData[playerid][pACTime] = 0;
	PlayerData[playerid][pACJetpack] = 0;
	format(PlayerData[playerid][pAccent], 24, "None");
	PlayerData[playerid][pPizza] = 0;
	PlayerData[playerid][pCarryPizza] = 0;
	PlayerData[playerid][pCarryingPizza] = false;
	OnTrash[playerid] = 0;
	FactoryIcons[playerid] = -1;
		
	Trash_InitPlayer(playerid);
	
	forex(i, MAX_TRASH)
	{
		if(IsValidDynamicMapIcon(TrashIcons[playerid][i]))
		{
			DestroyDynamicMapIcon(TrashIcons[playerid][i]);
			TrashIcons[playerid][i] = -1;
		}	
	}
	forex(i, 13)
	{
		PlayerData[playerid][pGuns][i] = 0;
		PlayerData[playerid][pAmmo][i] = 0;
		PlayerData[playerid][pDurability][i] = 0;
		PlayerData[playerid][pHighVelocity][i] = 0;
	}
	forex(i, MAX_INVENTORY)
	{
	    InventoryData[playerid][i][invExists] = false;
	    InventoryData[playerid][i][invModel] = 0;
	    InventoryData[playerid][i][invQuantity] = 0;
	}
	forex(i, 7)
	{
		PlayerData[playerid][pDamages][i] = 100.0;
		PlayerData[playerid][pBullets][i] = 0;
	}
	forex(i, MAX_CHARS)
	{
		PlayerChar[playerid][i][0] = EOS;
	}
	forex(i, 17)
	{
		WeaponSettings[playerid][i][Position][0] = -0.116;
		WeaponSettings[playerid][i][Position][1] = 0.189;
		WeaponSettings[playerid][i][Position][2] = 0.088;
		WeaponSettings[playerid][i][Position][3] = 0.0;
		WeaponSettings[playerid][i][Position][4] = 44.5;
		WeaponSettings[playerid][i][Position][5] = 0.0;
		WeaponSettings[playerid][i][Bone] = 1;
		WeaponSettings[playerid][i][Hidden] = false;
	}
	forex(i, 4)
	{
		PlayerData[playerid][pLicense][i] = false;
	}

    for (new i = 0; i != MAX_ACC; i ++) {
        AccData[playerid][i][accExists] = false;
        AccData[playerid][i][accID] = 0;
        AccData[playerid][i][accModel] = 0;
        AccData[playerid][i][accBone] = 0;
        AccData[playerid][i][accShow] = 0;

        AccData[playerid][i][accColor1][0] = AccData[playerid][i][accColor1][1] = AccData[playerid][i][accColor1][2] = 0;
        AccData[playerid][i][accColor2][0] = AccData[playerid][i][accColor2][1] = AccData[playerid][i][accColor2][2] = 0;

        AccData[playerid][i][accOffset][0] = AccData[playerid][i][accOffset][1] = AccData[playerid][i][accOffset][2] = 0.0;
        AccData[playerid][i][accRot][0] = AccData[playerid][i][accRot][1] = AccData[playerid][i][accRot][2] = 0.0;
        AccData[playerid][i][accScale][0] = AccData[playerid][i][accScale][1] = AccData[playerid][i][accScale][2] = 1.0;
    }

	for(new i = 0; i < MAX_CONTACTS; i++) {
		ContactData[playerid][i][contactExists] = false;
	}
	forex(i, 10)
	{
	    FishWeight[playerid][i] = 0;
	    format(FishName[playerid][i], 32, "Empty");
	}
	SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL, 0);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL_SILENCED, 999);

	Damage_Reset(playerid);
	return 1;
}

stock HideWaypoint(playerid)
{
	PlayerTextDrawHide(playerid, GPSTD[playerid]);
	PlayerData[playerid][pWP] = false;
	DisablePlayerCheckpoint(playerid);
}

stock SetWaypoint(playerid, Float:x, Float:y, Float:z, Float:rad)
{
	Destination[playerid][0] = x;
	Destination[playerid][1] = y;
	Destination[playerid][2] = z;
	SetPlayerCheckpoint(playerid, x, y, z, rad);
	PlayerData[playerid][pWP] = true;
	PlayerTextDrawShow(playerid, GPSTD[playerid]);
	ShowMessage(playerid, "Type_~r~/disablecp_~w~to_remove_checkpoints",3);

}

stock GetWeapon(playerid)
{
	new weaponid = GetPlayerWeapon(playerid);

	if (1 <= weaponid <= 46 && PlayerData[playerid][pGuns][g_aWeaponSlots[weaponid]] == weaponid)
 		return weaponid;

	return 0;
}

stock ShowWeapon(playerid, targetid)
{
	new mstr[512], lstr[1024];
	format(mstr, sizeof(mstr), "%s Weapon List", ReturnName(targetid));
	strcat(lstr, "Weapon\tAmmo\tDurability\n");
	for(new i = 0; i < 13; i ++)
    {
        if(PlayerData[targetid][pGuns][i] > 0) {
			if(PlayerData[targetid][pHighVelocity][i]) {
				format(lstr, sizeof(lstr), "%s\n%s (High Velocity)\t%d\t%d", lstr, ReturnWeaponName(PlayerData[targetid][pGuns][i]), PlayerData[targetid][pAmmo][i], PlayerData[targetid][pDurability][i]);
			}
			else {
				format(lstr, sizeof(lstr), "%s\n%s\t%d\t%d", lstr, ReturnWeaponName(PlayerData[targetid][pGuns][i]), PlayerData[targetid][pAmmo][i], PlayerData[targetid][pDurability][i]);
			}
		}
    }
    ShowPlayerDialog(playerid, DIALOG_NONE, DIALOG_STYLE_TABLIST_HEADERS, mstr, lstr,"Close","");
    return 1;
}

stock UpdateWeapons(playerid)
{
	forex(i, 13) if (PlayerData[playerid][pGuns][i])
    {
		if ((i == 2))
		    continue;

        GetPlayerWeaponData(playerid, i, PlayerData[playerid][pGuns][i], PlayerData[playerid][pAmmo][i]);

        if (PlayerData[playerid][pGuns][i] != 0 && !PlayerData[playerid][pAmmo][i])
		{
            PlayerData[playerid][pGuns][i] = 0;
		}
	}
	return 1;
}

stock PlayerHasWeapon(playerid, weaponid)
{
	new
	    weapon,
	    ammo;

	forex(i, 13) if (PlayerData[playerid][pGuns][i] == weaponid) {
	    GetPlayerWeaponData(playerid, i, weapon, ammo);

	    if (weapon == weaponid && ammo > 0) return 1;
	}
	return 0;
}

stock IsWeaponHaveRound(weaponid) {
	if(weaponid == 25 || weaponid == 33 || weaponid == 34)
		return  0;

	return 1;
}
stock GetWeaponRound(weaponid) {

	new round = 0;
	switch(weaponid) {
		case WEAPON_COLT45: round = 34;
		case WEAPON_SILENCED: round = 17;
		case WEAPON_DEAGLE: round = 7;
		case WEAPON_SAWEDOFF: round = 4;
		case WEAPON_SHOTGSPA: round = 7;
		case WEAPON_UZI: round = 100;
		case WEAPON_MP5: round = 30;
		case WEAPON_AK47: round = 30;
		case WEAPON_M4: round = 50;
		case WEAPON_TEC9: round = 100;
	}
	return round;
}
stock SetWeapons(playerid)
{
	ResetPlayerWeapons(playerid);

	forex(i, 13) if (PlayerData[playerid][pGuns][i] > 0)
	{
		if(IsWeaponHaveRound(PlayerData[playerid][pGuns][i])) {
			PlayerData[playerid][pWeaponRound][g_aWeaponSlots[PlayerData[playerid][pGuns][i]]] = GetWeaponRound(PlayerData[playerid][pGuns][i]);
			PlayerData[playerid][pTempAmmo][g_aWeaponSlots[PlayerData[playerid][pGuns][i]]] = PlayerData[playerid][pAmmo][g_aWeaponSlots[PlayerData[playerid][pGuns][i]]] - GetWeaponRound(PlayerData[playerid][pGuns][i]);
		
			if(PlayerData[playerid][pAmmo][g_aWeaponSlots[PlayerData[playerid][pGuns][i]]] <= GetWeaponRound(PlayerData[playerid][pGuns][i])) {
				PlayerData[playerid][pWeaponRound][g_aWeaponSlots[PlayerData[playerid][pGuns][i]]] = PlayerData[playerid][pAmmo][g_aWeaponSlots[PlayerData[playerid][pGuns][i]]];
				PlayerData[playerid][pTempAmmo][g_aWeaponSlots[PlayerData[playerid][pGuns][i]]] = 0;
			}
		}
	    GivePlayerWeapon(playerid, PlayerData[playerid][pGuns][i], 99999);
	}
	return 1;
}

stock ResetWeapons(playerid)
{
	ResetPlayerWeapons(playerid);

	forex(i, 13)
	{
		PlayerData[playerid][pGuns][i] = 0;
		PlayerData[playerid][pAmmo][i] = 0;
		PlayerData[playerid][pDurability][i] = 0;
		PlayerData[playerid][pHighVelocity][i] = 0;
	}
	return 1;
}

stock ResetWeapon(playerid, weaponid)
{
	ResetPlayerWeapons(playerid);

	forex(i, 13)
	{
	    if (PlayerData[playerid][pGuns][i] != weaponid)
		{
			if(IsWeaponHaveRound(PlayerData[playerid][pGuns][i])) {
				PlayerData[playerid][pWeaponRound][g_aWeaponSlots[PlayerData[playerid][pGuns][i]]] = GetWeaponRound(PlayerData[playerid][pGuns][i]);
				PlayerData[playerid][pTempAmmo][g_aWeaponSlots[PlayerData[playerid][pGuns][i]]] = PlayerData[playerid][pAmmo][g_aWeaponSlots[PlayerData[playerid][pGuns][i]]] - GetWeaponRound(PlayerData[playerid][pGuns][i]);

				if(PlayerData[playerid][pAmmo][g_aWeaponSlots[PlayerData[playerid][pGuns][i]]] <= GetWeaponRound(PlayerData[playerid][pGuns][i])) {
					PlayerData[playerid][pWeaponRound][g_aWeaponSlots[PlayerData[playerid][pGuns][i]]] = PlayerData[playerid][pAmmo][g_aWeaponSlots[PlayerData[playerid][pGuns][i]]];
					PlayerData[playerid][pTempAmmo][g_aWeaponSlots[PlayerData[playerid][pGuns][i]]] = 0;
				}
			}
	        GivePlayerWeapon(playerid, PlayerData[playerid][pGuns][i], 99999);
		}
		else
		{
            PlayerData[playerid][pGuns][i] = 0;
            PlayerData[playerid][pAmmo][i] = 0;
            PlayerData[playerid][pDurability][i] = 0;
			PlayerData[playerid][pHighVelocity][i] = 0;

	    }
	}
	return 1;
}

stock PassWeaponToPlayer(playerid, weaponid, ammo, dura, highvelo = 0)
{
	if (weaponid < 0 || weaponid > 46)
	    return 0;

	PlayerData[playerid][pGuns][g_aWeaponSlots[weaponid]] = weaponid;
	PlayerData[playerid][pAmmo][g_aWeaponSlots[weaponid]] = ammo;
	PlayerData[playerid][pDurability][g_aWeaponSlots[weaponid]] = dura;
	PlayerData[playerid][pHighVelocity][g_aWeaponSlots[weaponid]] = highvelo;

	if(IsWeaponHaveRound(weaponid)) {
		PlayerData[playerid][pWeaponRound][g_aWeaponSlots[weaponid]] = GetWeaponRound(weaponid);
		PlayerData[playerid][pTempAmmo][g_aWeaponSlots[weaponid]] = PlayerData[playerid][pAmmo][g_aWeaponSlots[weaponid]] - GetWeaponRound(weaponid);
	
		if(PlayerData[playerid][pAmmo][g_aWeaponSlots[weaponid]] <= GetWeaponRound(weaponid)) {
			PlayerData[playerid][pWeaponRound][g_aWeaponSlots[weaponid]] = PlayerData[playerid][pAmmo][g_aWeaponSlots[weaponid]];
			PlayerData[playerid][pTempAmmo][g_aWeaponSlots[weaponid]] = 0;
		}
	}
	return GivePlayerWeapon(playerid, weaponid, 999999);
}

stock GiveWeaponToPlayer(playerid, weaponid, ammo = 100, dura = 500, highvelo = 0)
{
	if (weaponid < 0 || weaponid > 46)
	    return 0;

	PlayerData[playerid][pGuns][g_aWeaponSlots[weaponid]] = weaponid;
	PlayerData[playerid][pAmmo][g_aWeaponSlots[weaponid]] = ammo;
	PlayerData[playerid][pDurability][g_aWeaponSlots[weaponid]] = dura;
	PlayerData[playerid][pHighVelocity][g_aWeaponSlots[weaponid]] = highvelo;

	if(IsWeaponHaveRound(weaponid)) {
		PlayerData[playerid][pWeaponRound][g_aWeaponSlots[weaponid]] = GetWeaponRound(weaponid);
		PlayerData[playerid][pTempAmmo][g_aWeaponSlots[weaponid]] = PlayerData[playerid][pAmmo][g_aWeaponSlots[weaponid]] - GetWeaponRound(weaponid);

		if(PlayerData[playerid][pAmmo][g_aWeaponSlots[weaponid]] <= GetWeaponRound(weaponid)) {
			PlayerData[playerid][pWeaponRound][g_aWeaponSlots[weaponid]] = PlayerData[playerid][pAmmo][g_aWeaponSlots[weaponid]];
			PlayerData[playerid][pTempAmmo][g_aWeaponSlots[weaponid]] = 0;
		}
	}
	return GivePlayerWeapon(playerid, weaponid, 999999);
}

SendAdminDutyMessage(color, const str[], {Float,_}:...)
{
	static
	    args,
	    start,
	    end,
	    string[144]
	;
	#emit LOAD.S.pri 8
	#emit STOR.pri args

	if (args > 8)
	{
		#emit ADDR.pri str
		#emit STOR.pri start

	    for (end = start + (args - 8); end > start; end -= 4)
		{
	        #emit LREF.pri end
	        #emit PUSH.pri
		}
		#emit PUSH.S str
		#emit PUSH.C 144
		#emit PUSH.C string

		#emit LOAD.S.pri 8
		#emit ADD.C 4
		#emit PUSH.pri

		#emit SYSREQ.C format
		#emit LCTRL 5
		#emit SCTRL 4

        foreach (new i : Player) if(PlayerData[i][pSpawned])
		{
			if(PlayerData[i][pAdmin] >= 1 && PlayerData[i][pAduty])
			{
  				SendClientMessage(i, color, string);
			}
		}
		return 1;
	}
	foreach (new i : Player) if(PlayerData[i][pSpawned])
	{
		if (PlayerData[i][pAdmin] >= 1 && PlayerData[i][pAduty])
		{
			SendClientMessage(i, color, str);
		}
	}
	return 1;
}

SendAdminMessage(color, const str[], {Float,_}:...)
{
	static
	    args,
	    start,
	    end,
	    string[144]
	;
	#emit LOAD.S.pri 8
	#emit STOR.pri args

	if (args > 8)
	{
		#emit ADDR.pri str
		#emit STOR.pri start

	    for (end = start + (args - 8); end > start; end -= 4)
		{
	        #emit LREF.pri end
	        #emit PUSH.pri
		}
		#emit PUSH.S str
		#emit PUSH.C 144
		#emit PUSH.C string

		#emit LOAD.S.pri 8
		#emit ADD.C 4
		#emit PUSH.pri

		#emit SYSREQ.C format
		#emit LCTRL 5
		#emit SCTRL 4

        foreach (new i : Player) if(PlayerData[i][pSpawned])
		{
			if(PlayerData[i][pAdmin] >= 1 && PlayerData[i][pAMSG] && !PlayerData[i][pVynMode])
			{
  				SendClientMessage(i, color, string);
			}
		}
		return 1;
	}
	foreach (new i : Player) if(PlayerData[i][pSpawned])
	{
		if (PlayerData[i][pAdmin] >= 1 && PlayerData[i][pAMSG] && !PlayerData[i][pVynMode])
		{
			SendClientMessage(i, color, str);
		}
	}
	return 1;
}

UpdateHBE(playerid)
{
	new Float:lapar, Float:haus, Float:divided;

	if(PlayerData[playerid][pSpawned] && !PlayerData[playerid][pTogHud])
	{
		if(PlayerData[playerid][pHudType] == 1) {
			
			divided = floatdiv(59.5,100);
			lapar = floatmul(PlayerData[playerid][pHunger], divided);
			PlayerTextDrawTextSize(playerid, HUNGERTD[playerid], lapar, 6.5);
			PlayerTextDrawShow(playerid, HUNGERTD[playerid]);


			divided = floatdiv(59.5,100);
			haus = floatmul(PlayerData[playerid][pThirst], divided);
			PlayerTextDrawTextSize(playerid,THIRSTTD[playerid], haus, 6.5);
			PlayerTextDrawShow(playerid,THIRSTTD[playerid]);
		}
		else if(PlayerData[playerid][pHudType] == 2) {

			
			divided = floatdiv(23.399999,100);
			lapar = floatmul(PlayerData[playerid][pHunger], divided);
			PlayerTextDrawTextSize(playerid, HUNGERBAR_2[playerid], lapar, 3.5);
			PlayerTextDrawColor(playerid, HUNGERBAR_2[playerid], ConvertHBEColor(PlayerData[playerid][pHunger]));
			PlayerTextDrawShow(playerid, HUNGERBAR_2[playerid]);

			divided = floatdiv( 23.899999,100);
			haus = floatmul(PlayerData[playerid][pThirst], divided);
			
			PlayerTextDrawTextSize(playerid, THIRSTBAR_2[playerid], haus, 3.5);
			PlayerTextDrawColor(playerid, THIRSTBAR_2[playerid], ConvertHBEColor(PlayerData[playerid][pThirst]));
			PlayerTextDrawShow(playerid, THIRSTBAR_2[playerid]);		
		}
		else {
			SetPlayerProgressBarValue(playerid, PROGRESS_HUNGER[playerid], PlayerData[playerid][pHunger]);
			SetPlayerProgressBarValue(playerid, PROGRESS_THIRST[playerid], PlayerData[playerid][pThirst]);
			SetPlayerProgressBarColour(playerid, PROGRESS_HUNGER[playerid], ConvertHBEColor(PlayerData[playerid][pHunger]));
			SetPlayerProgressBarColour(playerid, PROGRESS_THIRST[playerid], ConvertHBEColor(PlayerData[playerid][pThirst]));
		}
	}
	return 1;
}

ShowPlayerHUD(playerid) {

	if(PlayerData[playerid][pTogHud])
		return 0;

	PlayerTextDrawShow(playerid, TIMEGUI[playerid][0]);
	PlayerTextDrawShow(playerid, TIMEGUI[playerid][1]);
	PlayerTextDrawShow(playerid, AMMOTD[playerid]);

	if(PlayerData[playerid][pHudType] == 1) {
		for(new i = 0; i < 4; i++) 
			PlayerTextDrawShow(playerid, HUDTD[playerid][i]);

		PlayerTextDrawShow(playerid, HBEBOX[playerid]);
		PlayerTextDrawShow(playerid, MONEYTD[playerid]);
		PlayerTextDrawShow(playerid, HUNGERTD[playerid]);
		PlayerTextDrawShow(playerid, THIRSTTD[playerid]);

		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {

			for(new i = 4; i < 11; i++) 
				PlayerTextDrawShow(playerid, HUDTD[playerid][i]);

			PlayerTextDrawShow(playerid, VHPTD[playerid]);
			PlayerTextDrawShow(playerid, FUELTD[playerid]);
			PlayerTextDrawShow(playerid, ENGINETD[playerid]);
			PlayerTextDrawShow(playerid, KMHTD[playerid]);
			PlayerTextDrawShow(playerid, VEHNAMETD[playerid]);
			PlayerTextDrawShow(playerid, LOCATIONTD[playerid]);
		}
	}
	else if(PlayerData[playerid][pHudType] == 2) {
		
		for(new i = 0; i < 13; i++) {
			TextDrawShowForPlayer(playerid, HUD2_TD[i]);
		}

		PlayerTextDrawShow(playerid, HUNGERBAR_2[playerid]);
		PlayerTextDrawShow(playerid, THIRSTBAR_2[playerid]);

		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
			PlayerTextDrawShow(playerid, SPEEDO_2[playerid]);
		}
	}
	else {
		PlayerTextDrawShow(playerid, HBE3_BOX[playerid]);
		PlayerTextDrawShow(playerid, HBE3_FOODICO[playerid]);
		PlayerTextDrawShow(playerid, HBE3_DRINKICO[playerid]);

		PROGRESS_HUNGER[playerid] = CreatePlayerProgressBar(playerid, 552.000000, 416.000000, 71.000000, 6.500000, 852308735, 100.000000, 0);
		PROGRESS_THIRST[playerid] = CreatePlayerProgressBar(playerid, 552.000000, 431.000000, 71.000000, 6.500000, 852308735, 100.000000, 0);

		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
			for(new i = 0; i < 6; i++) {
				PlayerTextDrawShow(playerid, HBE3_SPEEDO[playerid][i]);
			}
			PROGRESS_FUEL[playerid] = CreatePlayerProgressBar(playerid, 534.000000, 396.000000, 100.000000, 4.000000, -2016478465, 100.000000, 0);
		}
	}
	return 1;
}

HidePlayerHUD(playerid) {

	for(new i = 0; i < 4; i++) 
		PlayerTextDrawHide(playerid, HUDTD[playerid][i]);

	PlayerTextDrawHide(playerid, HBEBOX[playerid]);
	PlayerTextDrawHide(playerid, MONEYTD[playerid]);
	PlayerTextDrawHide(playerid, HUNGERTD[playerid]);
	PlayerTextDrawHide(playerid, THIRSTTD[playerid]);
	PlayerTextDrawHide(playerid, TIMEGUI[playerid][0]);
	PlayerTextDrawHide(playerid, TIMEGUI[playerid][1]);
	PlayerTextDrawHide(playerid, AMMOTD[playerid]);

	// Type 2
	for(new i = 0; i < 13; i++) {
		TextDrawHideForPlayer(playerid, HUD2_TD[i]);
	}

	PlayerTextDrawHide(playerid, HUNGERBAR_2[playerid]);
	PlayerTextDrawHide(playerid, THIRSTBAR_2[playerid]);

	// == //

	// Type 3

	PlayerTextDrawHide(playerid, HBE3_BOX[playerid]);
	PlayerTextDrawHide(playerid, HBE3_FOODICO[playerid]);
	PlayerTextDrawHide(playerid, HBE3_DRINKICO[playerid]);

	if(IsValidPlayerProgressBar(playerid, PROGRESS_HUNGER[playerid]))
		DestroyPlayerProgressBar(playerid, PROGRESS_HUNGER[playerid]);

	if(IsValidPlayerProgressBar(playerid, PROGRESS_THIRST[playerid]))
		DestroyPlayerProgressBar(playerid, PROGRESS_THIRST[playerid]);

	

	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
		for(new i = 0; i < 6; i++) {
			PlayerTextDrawShow(playerid, HBE3_SPEEDO[playerid][i]);
		}
		PROGRESS_FUEL[playerid] = CreatePlayerProgressBar(playerid, 534.000000, 396.000000, 100.000000, 4.000000, -2016478465, 100.000000, 0);
	}
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {

		for(new i = 4; i < 11; i++) 
			PlayerTextDrawHide(playerid, HUDTD[playerid][i]);

		PlayerTextDrawHide(playerid, VHPTD[playerid]);
		PlayerTextDrawHide(playerid, FUELTD[playerid]);
		PlayerTextDrawHide(playerid, ENGINETD[playerid]);
		PlayerTextDrawHide(playerid, KMHTD[playerid]);
		PlayerTextDrawHide(playerid, VEHNAMETD[playerid]);
		PlayerTextDrawHide(playerid, LOCATIONTD[playerid]);

		// Type 2
		PlayerTextDrawHide(playerid, SPEEDO_2[playerid]);

		// Type 3
		for(new i = 0; i < 6; i++) {
			PlayerTextDrawHide(playerid, HBE3_SPEEDO[playerid][i]);
		}

		if(IsValidPlayerProgressBar(playerid, PROGRESS_FUEL[playerid]))
			DestroyPlayerProgressBar(playerid, PROGRESS_FUEL[playerid]);
	}


	return 1;
}

stock UpdatePlayerSkin(playerid, skinid)
{
	SetPlayerSkin(playerid, skinid);
	PlayerData[playerid][pSkin] = skinid;
}

function BandageUpdate(playerid)
{

	if(!PlayerData[playerid][pBandage])
		return 0;

	static
	    Float:health;

	GetPlayerHealth(playerid, health);
	PlayerData[playerid][pBandage] = false;
	SendServerMessage(playerid, "Your bandage has been used up.");
	ClearAnimations(playerid, 1);

	if(health + 10.0 > 100.0)
		SetPlayerHealth(playerid, 100.0);
	else SetPlayerHealth(playerid, health + 10.0);


	return 1;
}

function FirstAidUpdate(playerid)
{
	static
	    Float:health;

	GetPlayerHealth(playerid, health);

    if (!IsPlayerInAnyVehicle(playerid) && GetPlayerAnimationIndex(playerid) != 1508)
    	ApplyAnimation(playerid, "SWAT", "gnstwall_injurd", 4.0, 1, 0, 0, 0, 0);

	if (health >= 95.0)
	{
	    SetPlayerHealth(playerid, 100.0);
	    SendServerMessage(playerid, "Your medkit has been used up.");

	    ClearAnimations(playerid, 1);

		PlayerData[playerid][pFirstAid] = false;
		KillTimer(PlayerData[playerid][pAidTimer]);
	}
	else {
	    SetPlayerHealth(playerid, floatadd(health, 4.0));
	}
	return 1;
}

stock GiveMoney(playerid, amount, string:reason[] = "")
{
	if(strlen(reason) > 0) {
		printf("[CASH UPDATE] %s(%s) | Before: $%s | After: $%s | Reason: %s", GetName(playerid), GetUsername(playerid), FormatNumber(GetMoney(playerid)), FormatNumber(GetMoney(playerid) + amount), reason);
	}
	PlayerData[playerid][pMoney] += amount;
	GivePlayerMoney(playerid, amount);
	PlayerTextDrawSetString(playerid, MONEYTD[playerid], sprintf("$%s", FormatNumber(PlayerData[playerid][pMoney])));

	new string[128]; 
	
	if(amount < 0) {
		format(string, sizeof(string), "~r~$%s", FormatNumber(amount));
		GameTextForPlayer(playerid, string, 2000, 1);
	}
	else{
		format(string, sizeof(string), "~g~$%s", FormatNumber(amount));
		GameTextForPlayer(playerid, string, 2000, 1);
	}
	return 1;
}
	
stock GetMoney(playerid)
{
	return PlayerData[playerid][pMoney];
}

stock SendNearbyMessage(playerid, Float:radius, color, const str[], {Float,_}:...)
{
	static
	    args,
	    start,
	    end,
	    string[144]
	;
	#emit LOAD.S.pri 8
	#emit STOR.pri args

	if (args > 16)
	{
		#emit ADDR.pri str
		#emit STOR.pri start

	    for (end = start + (args - 16); end > start; end -= 4)
		{
	        #emit LREF.pri end
	        #emit PUSH.pri
		}
		#emit PUSH.S str
		#emit PUSH.C 144
		#emit PUSH.C string

		#emit LOAD.S.pri 8
		#emit CONST.alt 4
		#emit SUB
		#emit PUSH.pri

		#emit SYSREQ.C format
		#emit LCTRL 5
		#emit SCTRL 4

        foreach (new i : Player)
		{
			if (IsPlayerNearPlayer(i, playerid, radius) && PlayerData[i][pSpawned])
			{
  				SendClientMessage(i, color, string);
			}
		}
		return 1;
	}
	foreach (new i : Player)
	{
		if (IsPlayerNearPlayer(i, playerid, radius) && PlayerData[i][pSpawned])
		{
			SendClientMessage(i, color, str);
		}
	}
	return 1;
}

function OnUCPBanned(playerid, name[], reason[])
{
	new rows = cache_num_rows();
	if(rows)
	{
		new query[256];
		mysql_format(sqlcon, query,sizeof(query),"UPDATE `playerucp` SET `Banned` = 1, `BannedBy` = '%s', `BannedReason` = '%s', `BannedTime` = '%d' WHERE `UCP` = '%s'", PlayerData[playerid][pUCP], reason, gettime(),name);
		mysql_tquery(sqlcon, query);	

		SendClientMessageToAllEx(COLOR_LIGHTRED, "AdmCmd: Account %s has been offline banned by %s", name, PlayerData[playerid][pUCP]);
		SendClientMessageToAllEx(COLOR_LIGHTRED, "Reason: %s", reason);		
	}
	else
	{
		SendErrorMessage(playerid, "Account with name '%s' is not registered on database!", name);
	}
	return 1;
}

function OnUCPUnban(playerid, name[])
{
	new rows = cache_num_rows();
	new ban;
	if(rows)
	{
		cache_get_value_name_int(0, "Banned", ban);
		if(!ban)
			return SendErrorMessage(playerid, "The specified player is not in banned!");

		new query[256];
		mysql_format(sqlcon, query,sizeof(query),"UPDATE `playerucp` SET `Banned` = 0  WHERE `UCP` = '%s'", name);
		mysql_tquery(sqlcon, query);			

		SendClientMessageToAllEx(COLOR_LIGHTRED, "AdmCmd: Account %s has been unbanned by %s", name, PlayerData[playerid][pUCP]);
	}
	else
	{
		SendErrorMessage(playerid, "Account with name '%s' is not registered on database!", name);
	}
	return 1;
}

stock SendPlayerToPlayer(playerid, targetid)
{
	new
	    Float:x,
	    Float:y,
	    Float:z;

	GetPlayerPos(targetid, x, y, z);

	SetPlayerInterior(playerid, GetPlayerInterior(targetid));
	SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(targetid));
	
	if (IsPlayerInAnyVehicle(playerid))
	{
	    SetVehiclePos(GetPlayerVehicleID(playerid), x, y + 2, z);
		LinkVehicleToInterior(GetPlayerVehicleID(playerid), GetPlayerInterior(targetid));
	}
	else {

		Streamer_UpdateEx(playerid, x, y, z, GetPlayerVirtualWorld(targetid), GetPlayerInterior(targetid), STREAMER_TYPE_OBJECT, 1000, 1);
		SetPlayerPos(playerid, x + 1, y, z);
	}
	PlayerData[playerid][pInBiz] = PlayerData[targetid][pInBiz];
	PlayerData[playerid][pInDoor] = PlayerData[targetid][pInDoor];
	PlayerData[playerid][pInFlat] = PlayerData[targetid][pInFlat];
	PlayerData[playerid][pInWorkshop] = PlayerData[targetid][pInWorkshop];
	return 1;
}
stock GetAdminRank(playerid)
{
 	new astring[28];
 	if(PlayerData[playerid][pAdmin] == 0) format(astring, sizeof(astring), "None");
	else if (PlayerData[playerid][pAdmin] == 1)format(astring, sizeof(astring), "Helper");
	else if (PlayerData[playerid][pAdmin] == 2)format(astring, sizeof(astring), "Senior Helper");
	else if (PlayerData[playerid][pAdmin] == 3)format(astring, sizeof(astring), "Admin Level 1");
	else if (PlayerData[playerid][pAdmin] == 4)format(astring, sizeof(astring), "Admin Level 2");
	else if (PlayerData[playerid][pAdmin] == 5)format(astring, sizeof(astring), "Senior Admin");
	else if (PlayerData[playerid][pAdmin] == 6)format(astring, sizeof(astring), "High Administrator");
	else if (PlayerData[playerid][pAdmin] == 7)format(astring, sizeof(astring), "Management");
	return astring;
}

stock SetPlayerSeatbelt(playerid)
{
	if(!PlayerData[playerid][pSeatbelt])
	{
        SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "* %s reaches for their seatbelt, and buckles it up.", ReturnName(playerid));
		SendClientMessage(playerid, 0x33CC33FF, "* You have put on your seatbelt.");
		PlayerData[playerid][pSeatbelt] = true;
	}
	else
	{
		PlayerData[playerid][pSeatbelt] = false;
        SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "* %s reaches for their seatbelt, and unbuckles it.", ReturnName(playerid));
		SendClientMessage(playerid,  0x33CC33FF, "* You have taken off your seatbelt.");
	}
	return 1;
}

GetEquipedItem(playerid) {
	return g_EquipItem[playerid];
}

EquipItem(playerid, equip) {

	g_EquipItem[playerid] = equip;

	switch(equip) {
		case EQUIP_ITEM_NONE: {
			RemovePlayerAttachedObject(playerid, 9);
		}
		case EQUIP_ITEM_AXE: {
			SetPlayerAttachedObject(playerid, 9, 19631, 6, 0.0659, 0.0180, 0.0000, -93.7999, -80.1999, -2.4000, 1.0000, 1.0000, 1.0000, 0xFFFFFFFF, 0xFFFFFFFF);
		}
		case EQUIP_ITEM_ROD: {
			SetPlayerAttachedObject(playerid, 9, 18632, 6, 0.1, 0.05, 0, 0, 180, 180, 0);
		}
	}
	return 1;
}

stock DisplayHealth(playerid, userid)
{
    new string[1351];
    strcat(string, ""LIGHTBLUE"============== "LIGHTGREEN"DAMAGE STATUS   "LIGHTBLUE"==============\n");
	strcat(string, sprintf(""WHITE"Head: "YELLOW"%.2f\n", PlayerData[userid][pDamages][0]));
	strcat(string, sprintf(""WHITE"Torso: "YELLOW"%.2f\n", PlayerData[userid][pDamages][1]));
	strcat(string, sprintf(""WHITE"Right Arm: "YELLOW"%.2f\n", PlayerData[userid][pDamages][2]));
	strcat(string, sprintf(""WHITE"Left Arm: "YELLOW"%.2f\n", PlayerData[userid][pDamages][3]));
	strcat(string, sprintf( ""WHITE"Groin: "YELLOW"%.2f\n", PlayerData[userid][pDamages][4]));
	strcat(string, sprintf(""WHITE"Right Leg: "YELLOW"%.2f\n", PlayerData[userid][pDamages][5]));
	strcat(string, sprintf(""WHITE"Left Leg: "YELLOW"%.2f\n\n\n", PlayerData[userid][pDamages][6]));
    if(PlayerData[userid][pCough])
    {
        new rate[15];

        switch(PlayerData[userid][pCough])
        {
            case 1, 2, 3: rate= "LOW";
            case 4, 5, 6: rate= "MEDIUM";
            case 7, 8, 9: rate= "HIGH";
			case 10: rate = "EXTREME";
        }
        strcat(string, ""LIGHTBLUE"============== "LIGHTGREEN"SICKNESS STATUS "LIGHTBLUE"==============\n");
        strcat(string, ""WHITE"Condition: "YELLOW"SICK (Cough)\n");
		if(GetFactionType(playerid) == FACTION_MEDIC)
        	strcat(string, ""WHITE"How to cure: "YELLOW"Promethazine\n");

        strcat(string, sprintf(""WHITE"Sickness rate: "YELLOW"%s\n", rate));
		if(GetFactionType(playerid) == FACTION_MEDIC)
        	strcat(string, sprintf(""WHITE"Medicine Needed: "YELLOW"%d\n\n\n", PlayerData[userid][pCough]));
    }
    if(PlayerData[userid][pFever])
    {
        new rate[15];

        switch(PlayerData[userid][pFever])
        {
            case 1: rate = "LOW";
            case 2: rate = "MEDIUM";
            case 3: rate = "HIGH";
            case 4: rate = "EXTREME";
        }

        strcat(string, ""WHITE"Condition: "YELLOW"SICK (Fever)\n");

		if(GetFactionType(playerid) == FACTION_MEDIC)
        	strcat(string, ""WHITE"How to cure: "YELLOW"Acetaminophen\n");
			
        strcat(string, sprintf(""WHITE"Sickness rate: "YELLOW"%s\n", rate));
		if(GetFactionType(playerid) == FACTION_MEDIC)
        	strcat(string, sprintf(""WHITE"Medicine Needed: "YELLOW"%d\n", PlayerData[userid][pFever]));
    }

    ShowPlayerDialog(playerid, DIALOG_NONE, DIALOG_STYLE_MSGBOX, sprintf("%s Condition", ReturnName(userid)), string, "Close", "");
	return 1;
}

function UnTazer(playerid)
{
	if(!PlayerData[playerid][pTazed])
		return 0;

	TogglePlayerControllable(playerid, 1);
	ClearAnimations(playerid, 1);
	PlayerData[playerid][pTazed] = false;
	return 1;
}

stock GetNumberOwner(number)
{
	foreach (new i : Player) if (PlayerData[i][pPhoneNumber] == number && PlayerHasItem(i, "Cellphone"))
	{
		return i;
	}
	return INVALID_PLAYER_ID;
}

function SetPlayerToUnfreeze(playerid)
{
    TogglePlayerControllable(playerid, 1);
    PlayerData[playerid][pFreeze] = 0;
}

SetPlayerPositionEx(playerid, Float:x, Float:y, Float:z, time = 2000, interior = -1, world = -1)
{
    if(PlayerData[playerid][pFreeze])
    {
        KillTimer(PlayerData[playerid][pFreezeTimer]);
        PlayerData[playerid][pFreeze] = 0;
        TogglePlayerControllable(playerid, 1);
    }
	GameTextForPlayer(playerid, "~w~Rendering objects...", time, 3);
    TogglePlayerControllable(playerid, 0);
	Streamer_UpdateEx(playerid, x, y, z, world, interior, STREAMER_TYPE_OBJECT, time, 0);
    SetCameraBehindPlayer(playerid);
    PlayerData[playerid][pFreeze] = 1;
    PlayerData[playerid][pFreezeTimer] = SetTimerEx("SetPlayerToUnfreeze", time, false, "d", playerid);

	if(interior != -1) SetPlayerInterior(playerid,interior);
	if(world != -1) SetPlayerVirtualWorld(playerid,world);
	return SetPlayerPos(playerid, x, y, z + 1);
}