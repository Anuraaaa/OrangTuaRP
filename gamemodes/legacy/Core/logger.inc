#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_timers>

new DCC_Channel:cheatLog;
new DCC_Channel:propertyLog;
new DCC_Channel:payLog;
new DCC_Channel:killLog;
new DCC_Channel:pmLog;
new DCC_Channel:assistLog;
new DCC_Channel:adsLog;
new DCC_Channel:bankLog;
new DCC_Channel:salaryLog;
new DCC_Channel:itemLog;
new DCC_Channel:vehDeathLog;

hook OnGameModeInit()
{
    cheatLog = DCC_FindChannelById("1142329351912837151");
    killLog = DCC_FindChannelById("1142329401606950922");
    pmLog = DCC_FindChannelById("1142330548480655360");
    payLog = DCC_FindChannelById("1142329499896270938");
    bankLog = DCC_FindChannelById("1142330178232647750");
    salaryLog = DCC_FindChannelById("1142330127821312090");
    itemLog = DCC_FindChannelById("1142329628837560370");
    assistLog = DCC_FindChannelById("1142329715517046865");
    propertyLog = DCC_FindChannelById("1142329782261006407");
    adsLog = DCC_FindChannelById("1000014125503627294");
	vehDeathLog = DCC_FindChannelById("1143359718287482973");
}

hook OnPlayerDeath(playerid, killerid, reason) {

	if (1 <= reason <= 46)
	{
		if (killerid != INVALID_PLAYER_ID)
		{
			LogKill_DCChannel(Str_Format("[%s]\nKILLLOG: %s (%s) has killed %s (%s) (Reason: %s)", ReturnDate(), GetName(killerid), GetUsername(killerid), GetName(playerid), GetUsername(playerid), ReturnWeaponName(reason)));
		}
		else
		{
			LogKill_DCChannel(Str_Format("[%s]\nKILLLOG: %s (%s) is dead (Reason: %s)", ReturnDate(), GetName(playerid), GetUsername(playerid), ReturnWeaponName(reason)));
		}
	}
	else if (reason == 49)
	{
		if (killerid != INVALID_PLAYER_ID)
		{			
			LogKill_DCChannel(Str_Format("[%s]\nKILLLOG: %s (%s) has killed %s (%s) (Reason: Weapon Vehicle)", ReturnDate(), GetName(killerid), GetUsername(killerid), GetName(playerid), GetUsername(playerid)));
		}
		else
		{
			LogKill_DCChannel(Str_Format("[%s]\nKILLLOG: %s (%s) is dead (Reason: Weapon Vehicle)", ReturnDate(), GetName(playerid), GetUsername(playerid)));
		}
	}
	else if (reason == 50)
	{
		if (killerid != INVALID_PLAYER_ID)
		{
			LogKill_DCChannel(Str_Format("[%s]\nKILLLOG: %s (%s) has killed %s (%s) (Reason: Helicopter Blade)", ReturnDate(), GetName(killerid), GetUsername(killerid), GetName(playerid), GetUsername(playerid)));
		}
		else
		{
			LogKill_DCChannel(Str_Format("[%s]\nKILLLOG: %s (%s) is dead (Reason: Helicopter Blade)", ReturnDate(), GetName(playerid), GetUsername(playerid)));
		}
	}
	else if (reason == 51)
	{
		if (killerid != INVALID_PLAYER_ID)
		{
			LogKill_DCChannel(Str_Format("[%s]\nKILLLOG: %s (%s) has killed %s (%s) (Reason: Explosion)", ReturnDate(), GetName(killerid), GetUsername(killerid), GetName(playerid), GetUsername(playerid)));
		}
		else
		{
			LogKill_DCChannel(Str_Format("[%s]\nKILLLOG: %s (%s) is dead (Reason: Explosion)", ReturnDate(), GetName(playerid), GetUsername(playerid)));
		}
	}
	else if (reason == 53)
	{
		if (killerid != INVALID_PLAYER_ID)
		{
			LogKill_DCChannel(Str_Format("[%s]\nKILLLOG: %s (%s) has killed %s (%s) (Reason: Drowned)", ReturnDate(), GetName(killerid), GetUsername(killerid), GetName(playerid), GetUsername(playerid)));
		}
		else
		{
			LogKill_DCChannel(Str_Format("[%s]\nKILLLOG: %s (%s) is dead (Reason: Drowned)", ReturnDate(), GetName(playerid), GetUsername(playerid)));
		}
	}
	else if (reason == 54)
	{
		if (killerid != INVALID_PLAYER_ID)
		{
			LogKill_DCChannel(Str_Format("[%s]\nKILLLOG: %s (%s) has killed %s (%s) (Reason: Splat)", ReturnDate(), GetName(killerid), GetUsername(killerid), GetName(playerid), GetUsername(playerid)));
		}
		else
		{
			LogKill_DCChannel(Str_Format("[%s]\nKILLLOG: %s (%s) is dead (Reason: Splat)", ReturnDate(), GetName(playerid), GetUsername(playerid)));
		}
	}
	else if (reason == 255)
	{
		if (killerid != INVALID_PLAYER_ID)
		{
			LogKill_DCChannel(Str_Format("[%s]\nKILLLOG: %s (%s) has killed %s (%s) (Reason: Suicide)", ReturnDate(), GetName(killerid), GetUsername(killerid), GetName(playerid), GetUsername(playerid)));
		}
		else
		{
			LogKill_DCChannel(Str_Format("[%s]\nKILLLOG: %s (%s) is dead (Reason: Suicide)", ReturnDate(), GetName(playerid), GetUsername(playerid)));
		}
	}
}

stock LogPM_DCChannel(msg[])
{
    new 
        str[MAX_PLAYER_NAME + 5064];

    format(str, sizeof(str), "```\n%s\n```", msg);
    return DCC_SendChannelMessage(pmLog, str);
}

stock LogCheat_DCChannel(msg[])
{
    new 
        str[MAX_PLAYER_NAME + 5064];

    format(str, sizeof(str), "```\n%s\n```", msg);
    return DCC_SendChannelMessage(cheatLog, str);
}

stock LogProperty_DCChannel(msg[])
{
    new 
        str[MAX_PLAYER_NAME + 5064];

    format(str, sizeof(str), "```\n%s\n```", msg);
    return DCC_SendChannelMessage(propertyLog, str);
}

stock LogPay_DCChannel(msg[])
{
    new 
        str[MAX_PLAYER_NAME + 5064];

    format(str, sizeof(str), "```\n%s\n```", msg);
    return DCC_SendChannelMessage(payLog, str);
}

stock LogKill_DCChannel(msg[])
{
    new 
        str[MAX_PLAYER_NAME + 5064];

    format(str, sizeof(str), "```\n%s\n```", msg);
    return DCC_SendChannelMessage(killLog, str);
}

stock LogAssist_DCChannel(msg[])
{
    new 
        str[MAX_PLAYER_NAME + 5064];

    format(str, sizeof(str), "```\n%s\n```", msg);
    return DCC_SendChannelMessage(assistLog, str);
}

stock LogAds_DCChannel(msg[])
{
    new 
        str[MAX_PLAYER_NAME + 5064];

    format(str, sizeof(str), "```\n%s\n```", msg);
    return DCC_SendChannelMessage(adsLog, str);
}

stock LogSalary_DCChannel(msg[])
{
    new 
        str[MAX_PLAYER_NAME + 5064];

    format(str, sizeof(str), "```\n%s\n```", msg);
    return DCC_SendChannelMessage(salaryLog, str);
}

stock LogBank_DCChannel(msg[])
{
    new 
        str[MAX_PLAYER_NAME + 5064];

    format(str, sizeof(str), "```\n%s\n```", msg);
    return DCC_SendChannelMessage(bankLog, str);
}

stock LogItem_DCChannel(msg[])
{
    new 
        str[MAX_PLAYER_NAME + 5064];

    format(str, sizeof(str), "```\n%s\n```", msg);
    return DCC_SendChannelMessage(itemLog, str);
}

stock LogVehicleDeath_DCChannel(msg[])
{
    new 
        str[MAX_PLAYER_NAME + 5064];

    format(str, sizeof(str), "```\n%s\n```", msg);
    return DCC_SendChannelMessage(vehDeathLog, str);
}

task UpdateBotPresence[2000]()
{
	new 
		str[164],
		count = 0;

	foreach (new i : Player)
	{
		if (IsPlayerConnected(i))
			count++;
	}

    format(str, sizeof(str), "SA-MP with %d/%d players", count, GetMaxPlayers());
	DCC_SetBotActivity(str);
	return 1;
}
