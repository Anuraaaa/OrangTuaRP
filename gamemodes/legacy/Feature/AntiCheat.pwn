#include <YSI_Coding\y_hooks>

#define 	MAX_CHEAT_WARNING		2

new WarningCode[MAX_PLAYERS][53],
    tele_warn[MAX_PLAYERS],
    slapper_warn[MAX_PLAYERS],
    engine_hack_warn[MAX_PLAYERS],
    g_ArmourHack[MAX_PLAYERS];

static GetCodeAC(code)
{
    new str[128];
    switch(code)
    {
        case 0: str =  "Onfoot airbreak";
        case 1: str =  "Vehicle airbreak";
        case 2: str =  "Onfoot teleport";
        case 3: str =  "Vehicle teleport";
        case 7: str =  "Onfoot Flyhack";
        case 8: str =  "Vehicle Flyhack";
        case 9: str =  "Onfoot speedhack";
        case 10: str =  "Vehicle speedhack";
        case 11: str = "Health Hack";
        case 12: str = "Health Hack";
        case 13: str = "Armour Hack";
        case 15: str =  "Weapon hack";
        case 16: str =  "Ammo hack";
        case 17: str =  "Infinite ammo";
        case 26: str =  "Rapid fire";
        case 29: str =  "Aimhack";
        case 35: str =  "Full aiming";
        default: format(str, sizeof(str), "Code %d", code);
    }
    return str;
}

static ResetPlayerWarningCode(playerid) {

	for(new i = 0; i < 52; i++) {
		WarningCode[playerid][i] = 0;
	}
	return 1;
}

public OnPlayerTeleport(playerid, Float:distance) {

    if(!PlayerData[playerid][pAdmin] && !PlayerData[playerid][pKicked]) {

        if(++tele_warn[playerid] >= 3) {
            SendAdminMessage(COLOR_LIGHTRED, "AdmWarning: Cheat detected on {FFFF00}%s (%s) {FF6347}(Teleport Hack)", GetName(playerid), PlayerData[playerid][pUCP]);
            SendClientMessageEx(playerid, X11_TOMATO_1, "AntiCheat: "GREY"Kamu dikick dari server karena dicurigai menggunakan program ilegal (Teleport Hack).");
            KickEx(playerid);
        }
    }
    return 1;
}

forward OnCheatDetected(playerid, ip_address[], type, code);
public OnCheatDetected(playerid, ip_address[], type, code)
{
    if(!type)
    {
		if(!PlayerData[playerid][pAdmin] && !PlayerData[playerid][pKicked]) {

            if(code == 6)
                return 0;
                
            if(code == 15) {

                if(GetPlayerWeapon(playerid) > 0)
                    SendAdminMessage(COLOR_LIGHTRED, "AdmWarning: Cheat detected on {FFFF00}%s (%s) {FF6347}(Weapon hack %s)", GetName(playerid), PlayerData[playerid][pUCP], ReturnWeaponName(GetPlayerWeapon(playerid)));
                
                SendClientMessageEx(playerid, X11_TOMATO_1, "AntiCheat: "GREY"Kamu dikick dari server karena dicurigai menggunakan program ilegal (%s).", GetCodeAC(code));
                ResetWeapons(playerid);
                SQL_SaveCharacter(playerid);
                AntiCheatKickWithDesync(playerid, code);         
            }
            else if(code == 13) {

                SendAdminMessage(COLOR_LIGHTRED, "AdmWarning: Cheat detected on {FFFF00}%s (%s) {FF6347}(Armour hack)", GetName(playerid, false), GetUsername(playerid));
                SetPlayerArmour(playerid, 0.0);
                if(++g_ArmourHack[playerid] >= 3) {
                    SendClientMessageEx(playerid, X11_TOMATO_1, "AntiCheat: "GREY"Kamu dikick dari server karena dicurigai menggunakan program ilegal (%s).", GetCodeAC(code));
                    SQL_SaveCharacter(playerid);
                    AntiCheatKickWithDesync(playerid, code);     
                }
            }
            else {

                if(WarningCode[playerid][code] < MAX_CHEAT_WARNING)
                {
                    WarningCode[playerid][code]++;
                }
                else
                {       
                    SendClientMessageEx(playerid, X11_TOMATO_1, "AntiCheat: "GREY"Kamu dikick dari server karena dicurigai menggunakan program ilegal (%s).", GetCodeAC(code));
                    SQL_SaveCharacter(playerid);
                    AntiCheatKickWithDesync(playerid, code);

                }
            }
		}
    }
    return 1;
}

hook OnPlayerConnect(playerid) {
	ResetPlayerWarningCode(playerid);

    slapper_warn[playerid] = 0;
    engine_hack_warn[playerid] = 0;
    g_ArmourHack[playerid] = 0;
}

/* Funcs */

Float:AC_GetPlayerSpeed(playerid)
{
	static Float:velocity[3];

	if (IsPlayerInAnyVehicle(playerid))
	    GetVehicleVelocity(GetPlayerVehicleID(playerid), velocity[0], velocity[1], velocity[2]);
	else
	    GetPlayerVelocity(playerid, velocity[0], velocity[1], velocity[2]);

	return floatsqroot((velocity[0] * velocity[0]) + (velocity[1] * velocity[1]) + (velocity[2] * velocity[2])) * 136.666667;
}

/* Anti Slapper */

ptask OnCheckAntiCheat[1000](playerid) {

    if(IsPlayerSpawned(playerid)) {
        if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
		{
		    new Float: ghX, Float: ghY, Float: ghZ;
			GetPlayerVelocity(playerid, ghX, ghY, ghZ);
		    if((ghX == -0.0 && ghY == -20.0) || (ghX == -20.0 && ghY == 0.0) || (ghX == 0.0 && ghY == 20.0)) {
                
                if(++slapper_warn[playerid] >= 3) {
                    SendAdminMessage(X11_TOMATO, "AdmWarning: "YELLOW"%s(%s) "TOMATO"is possibly using "RED"Slapper "YELLOW"go check!", GetName(playerid, false), GetUsername(playerid) );
                    slapper_warn[playerid] = 0;
                }
            }
		}
		if (AC_GetPlayerSpeed(playerid) > 200.0 && PlayerData[playerid][pAdmin] < 1)
		{
            SendAdminMessage(X11_TOMATO, "AdmWarning: Cheat detected on {FFFF00}%s (%s) {FF6347}(%s)", GetName(playerid, false), GetUsername(playerid), (IsPlayerInAnyVehicle(playerid)) ? ("Vehicle Speedhack") : ("Onfoot Speedhack"));
		    SendClientMessageEx(playerid, X11_TOMATO_1, "AntiCheat: "GREY"Kamu dikick dari server karena dicurigai menggunakan program ilegal (Speedhack).");
            KickEx(playerid);
		}
        if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && !GetEngineStatus(GetPlayerVehicleID(playerid)) && GetVehicleSpeedKMH(GetPlayerVehicleID(playerid)) > 15.0) {
            if(++engine_hack_warn[playerid] >= 5) {
                SendClientMessageEx(playerid, X11_TOMATO_1, "AntiCheat: "GREY"Kamu dikick dari server karena dicurigai menggunakan program ilegal (Engine Hack).");
                KickEx(playerid);
            }
        }
    }
    return 1;
}