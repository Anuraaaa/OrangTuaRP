#include <YSI_Coding\y_hooks>

#define 	MAX_CHEAT_WARNING		2

#define     BulletCrasher -5.5
#define     InvalidSeat1 -1000000.0
#define     InvalidSeat2 1000000.0

new WarningCode[MAX_PLAYERS][53],
    tele_warn[MAX_PLAYERS]= {0, ...},
    slapper_warn[MAX_PLAYERS]= {0, ...},
    engine_hack_warn[MAX_PLAYERS]= {0, ...},
    g_ArmourHack[MAX_PLAYERS]= {0, ...},
    speed_hack[MAX_PLAYERS]= {0, ...},
    airbreak_hack[MAX_PLAYERS]= {0, ...},
    ping_warning[MAX_PLAYERS]= {0, ...},
    ac_weapon_h[MAX_PLAYERS]= {0, ...};

enum {
    MOD_OLD_VERSION = 0,
    MOD_IMPROVED_DEAGLE,
    MOD_EXTRAWS,
    MOD_SOBEIT,
    MOD_SAMPFUNCS,
    MOD_SPRINTHOOK,
    MOD_CLEO_MODLOADER,
    MOD_BYPASS,
    MOD_SILENTAIM
}

static
    hack_health[MAX_PLAYERS] = {0, ...},
    hack_armour[MAX_PLAYERS] = {0, ...},
    hack_teleport[MAX_PLAYERS] = {0, ...},
    hack_airbreak[MAX_PLAYERS] = {0, ...},
    hack_vehiclehealth[MAX_PLAYERS] = {0, ...},
    hack_vehtele[MAX_PLAYERS] = {0, ...},
    hack_fly[MAX_PLAYERS] = {0, ...},
    UsingMods[MAX_PLAYERS][9];

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

AC_PlayerHasWeapon(playerid, weaponid)
{
	new
	    weapon,
	    ammo;

	for(new i = 0; i < 13; i++) {
	    GetPlayerWeaponData(playerid, i, weapon, ammo);

	    if (weapon == weaponid) return 1;
	}
	return 0;
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
            SendAdminMessage(COLOR_LIGHTRED, "AdmWarning: Cheat detected on {FFFF00}%s (%s) [%s] {FF6347}(Teleport Hack)", GetName(playerid), PlayerData[playerid][pUCP], ReturnIP(playerid));
            SendClientMessageEx(playerid, X11_TOMATO_1, "AntiCheat: "GREY"Kamu dikick dari server karena dicurigai menggunakan program ilegal (Teleport Hack).");
            KickEx(playerid);
        }
    }
    return 1;
}

forward OnCheatDetected(playerid, ip_address[], type, code);
public OnCheatDetected(playerid, ip_address[], type, code)
{

    if(type) {
        return 1;
    }

    switch(code)
    {
        //Onfoot airbreak
        case 0: {
            if(++hack_airbreak[playerid] == 3)
            {
                SendClientMessageEx(playerid, X11_YELLOW, "(AntiCheat) "GREY"You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));

                hack_airbreak[playerid] = 0;

                KickEx(playerid);
                return 1;
            }
            SendAdminMessage(X11_TOMATO, "Anticheat: %s possible onfoot airbreak hack.", GetName(playerid));
        }
        //Vehicle airbreak
        case 1: {
            if(++hack_airbreak[playerid] == 3)
            {
                SendClientMessageEx(playerid, X11_YELLOW, "(AntiCheat) "GREY"You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));

                hack_airbreak[playerid] = 0;

                KickEx(playerid);
                return 1;
            }
            SendAdminMessage(X11_TOMATO, "Anticheat: %s possible vehicle airbreak hack.", GetName(playerid));
        }
        //Teleport hack
        case 2:
        {
            new Float:x, Float:y, Float:z;
            new vw, int;
            int = GetPlayerInterior(playerid);
            vw = GetPlayerVirtualWorld(playerid);
            AntiCheatGetPos(playerid, x, y, z);
            SetPlayerInterior(playerid, int);
            SetPlayerVirtualWorld(playerid, vw);
            SetPlayerPos(playerid, x, y, z);

            if(!IsPlayerPaused(playerid))
            {
                if(++hack_teleport[playerid] == 3)
                {
                    SendClientMessageEx(playerid, X11_YELLOW, "(AntiCheat) "GREY"You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));

                    hack_teleport[playerid] = 0;

                    KickEx(playerid);
                    return 1;
                }
                SendAdminMessage(X11_TOMATO, "Anticheat: %s possible teleport hack.", GetName(playerid));
            }
        }

        //Vehicle teleport hack
        case 3: 
        {
            if(++hack_vehtele[playerid] == 3) 
            {
                SendAdminMessage(X11_TOMATO, "Anticheat: %s possible vehicle teleport hack.", GetName(playerid));
                SendClientMessageEx(playerid, X11_YELLOW, "(AntiCheat) "GREY"You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));
                KickEx(playerid);
                return 1;
            }
            SendAdminMessage(X11_TOMATO, "Anticheat: %s possible vehicle teleport hack.", GetName(playerid));
        }

        //Wrap vehicle hack
        case 4: {
            SendAdminMessage(X11_TOMATO, "Anticheat: %s possible wrap vehicle hack.", GetName(playerid));
            SendClientMessageEx(playerid, X11_YELLOW, "(AntiCheat) "GREY"You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));
            KickEx(playerid);
        }

        //Vehicle teleport to player hack
        case 5: {
            SendAdminMessage(X11_TOMATO, "Anticheat: %s possible vehicle teleport to player hack.", GetName(playerid)); 
            SendClientMessageEx(playerid, X11_YELLOW, "(AntiCheat) "GREY"You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));
            KickEx(playerid);
        }
        
        //Flyhack on foot
        case 7: {
            if(++hack_fly[playerid] == 3)
            {
                SendClientMessageEx(playerid, X11_YELLOW, "(AntiCheat) "GREY"You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));

                hack_fly[playerid] = 0;

                KickEx(playerid);
                return 1;
            }
            SendAdminMessage(X11_TOMATO, "Anticheat: %s possible on foot flyhack hack.", GetName(playerid));
        }    
        //Flyhack in vehicle
        case 8: {
            if(++hack_fly[playerid] == 3)
            {
                SendClientMessageEx(playerid, X11_YELLOW, "(AntiCheat) "GREY"You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));

                hack_fly[playerid] = 0;

                KickEx(playerid);
                return 1;
            }
            SendAdminMessage(X11_TOMATO, "Anticheat: %s possible vehicle fly hack.", GetName(playerid));
        }
        //Speedhack in vehicle
        case 10: {
            if(++speed_hack[playerid] > 5) {
                SendAdminMessage(X11_TOMATO, "AntiCheat: "GREY"Cheat detected on {FFFF00}%s {FF6347}(Vehicle Speedhack)", GetName(playerid));
                SendClientMessageEx(playerid, X11_YELLOW, "(AntiCheat) "GREY"You have been kicked from the server because of using some suspicious programs (SpeedHack)");
                speed_hack[playerid] = 0;   
                KickEx(playerid);  
            }
        }
        
        //Vehicle speed hack
        case 11: {
            if(++hack_vehiclehealth[playerid] == 3)
            {
                SendClientMessageEx(playerid, X11_YELLOW, "(AntiCheat) "GREY"You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));
                hack_vehiclehealth[playerid] = 0;
                KickEx(playerid);
                return 1;
            }
            SendAdminMessage(X11_TOMATO, "Anticheat: %s possible vehicle health hack.", GetName(playerid));
        }
        //Health hack
        case 12: {
            new Float:health;
            AntiCheatGetHealth(playerid, health);
            SetPlayerHealth(playerid, health);
            if(++hack_health[playerid] == 3)
            {
                SendClientMessageEx(playerid, X11_YELLOW, "(AntiCheat) "GREY"You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));
                hack_health[playerid] = 0;
                KickEx(playerid);
                return 1;
            }
            SendAdminMessage(X11_TOMATO, "Anticheat: %s possible health hack.", GetName(playerid));
        }
        //Weapon hack
        case 15: {
            SendAdminMessage(X11_TOMATO, "Anticheat: %s possible weapon hack.", GetName(playerid));
            SendClientMessageEx(playerid, X11_YELLOW, "(AntiCheat) "GREY"You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));
            KickEx(playerid);
        }

        //Ammo hack
        case 16: {
            SendAdminMessage(X11_TOMATO, "Anticheat: %s possible add ammo hack.", GetName(playerid));
            SendClientMessageEx(playerid, X11_YELLOW, "(AntiCheat) "GREY"You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));
            KickEx(playerid);
        }

        //Ammo hack infinite
        case 17: {
            SendAdminMessage(X11_TOMATO, "Anticheat: %s possible infinite ammo hack.", GetName(playerid)); 
            SendClientMessageEx(playerid, X11_YELLOW, "(AntiCheat) "GREY"You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));
            KickEx(playerid);
        }

        case 18: {
            SendAdminMessage(X11_TOMATO, "Anticheat: %s is using special animations hack.", GetName(playerid));
            SendClientMessageEx(playerid, X11_YELLOW, "(AntiCheat) "GREY"You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));
            KickEx(playerid);
        }
        //Vehicle health hack
        case 13: {
            new Float:armour;
            AntiCheatGetArmour(playerid, armour);
            SetPlayerArmour(playerid, armour);

            if(++hack_armour[playerid] == 3)
            {
                SendClientMessageEx(playerid, X11_YELLOW, "(AntiCheat) "GREY"You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));

                hack_armour[playerid] = 0;

                KickEx(playerid);
                return 1;
            }
            SendAdminMessage(X11_TOMATO, "Anticheat: %s possible armour hack.", GetName(playerid));
        }
        //Rapid fire hack
        case 26: {

            if(IsPlayerUsingAndroid(playerid)) {
                return 0;
            }
            SendAdminMessage(X11_TOMATO, "Anticheat: %s possible rapid fire hack.", GetName(playerid)); 
            SendClientMessageEx(playerid, X11_YELLOW, "(AntiCheat) "GREY"You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));
            KickEx(playerid);   
        }
        case 40: {
            SendAdminMessage(X11_TOMATO, "Anticheat: %s is using sandboxie.", GetName(playerid));
            SendClientMessageEx(playerid, X11_YELLOW, "(AntiCheat) "GREY"You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));
            KickEx(playerid);
        }
    }
    SendAdminDutyMessage(X11_TOMATO, "Anticheat: %s (%s) type: %d code %d", GetName(playerid), ReturnIP(playerid), type, code);
    return 1;
}

timer OnCheckFile[5000](playerid) {
    if(IsPlayerSpawned(playerid)) {

        new string[352];

        if(IsUsingMods(playerid, MOD_SAMPFUNCS)) {
            strcat(string, "Kamu telah terdeteksi menggunakan SAMPFUNCS\nSilahkan keluar dari server lalu hapus SAMPFUNCS sebelum kembali bermain di OT:RP");
            ShowPlayerDialog(playerid, DIALOG_NONE, DIALOG_STYLE_MSGBOX, "AntiCheat", string, "Close", "");
            KickEx(playerid);
            return 1;
        }

        if(IsUsingMods(playerid, MOD_SPRINTHOOK)) {
            strcat(string, "Kamu telah terdeteksi menggunakan SPRINTHOOK\nSilahkan keluar dari server lalu hapus SPRINTHOOK sebelum kembali bermain di OT:RP");
            ShowPlayerDialog(playerid, DIALOG_NONE, DIALOG_STYLE_MSGBOX, "AntiCheat", string, "Close", "");
            KickEx(playerid);
            return 1;
        }

        if(IsUsingMods(playerid, MOD_BYPASS)) {
            strcat(string, "Kamu telah terdeteksi menggunakan BYPASS\nSilahkan keluar dari server lalu hapus BYPASS sebelum kembali bermain di OT:RP");
            ShowPlayerDialog(playerid, DIALOG_NONE, DIALOG_STYLE_MSGBOX, "AntiCheat", string, "Close", "");
            KickEx(playerid);
            return 1;
        }

    }
    return 1;
}

hook OnPlayerFirstSpawn(playerid) {
    if(!IsPlayerUsingAndroid(playerid)) {

        if(IsUsingMods(playerid, MOD_CLEO_MODLOADER)) 
            SendClientMessage(playerid, X11_GREY, "(SA:MP File) "WHITE"GTA Mu terdeteksi menggunakan cleo/modloader.");
    }
}
hook OnPlayerConnect(playerid) {

    new string[156];

	ResetPlayerWarningCode(playerid);

    slapper_warn[playerid] = 0;
    engine_hack_warn[playerid] = 0;
    g_ArmourHack[playerid] = 0;
    speed_hack[playerid] = 0;
    airbreak_hack[playerid] = 0;

    for(new i = 0; i < 9; i++) {
        UsingMods[playerid][i] = false;
    }



}

IsUsingMods(playerid, mods) {
    if(UsingMods[playerid][mods]) {
        return 1;
    }
    return 0;
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

        new
            ac_weapon[13],
            ac_ammo[13]
            ;

        for(new i = 0; i < 12; i++) {
            GetPlayerWeaponData(playerid, i, ac_weapon[i], ac_ammo[i]);

            if(ac_weapon[i] && PlayerData[playerid][pGuns][g_aWeaponSlots[ac_weapon[i]]] != ac_weapon[i]) {
                SendAdminMessage(X11_TOMATO, "Anticheat: %s is possible using weapon hack", GetName(playerid));
                ResetWeapon(playerid, ac_weapon[i]);
                ac_weapon_h[playerid]++;

                if(ac_weapon_h[playerid] > 3) {
                    SendAdminMessage(X11_TOMATO, "Anticheat: %s is possible using weapon hack (has been kicked)", GetName(playerid));
                    ResetWeapons(playerid);
                    ac_weapon_h[playerid] = 0;
                    SendClientMessageEx(playerid, X11_YELLOW, "(AntiCheat) "GREY"You have been kicked from the server because of using some suspicious programs (Weapon Hack)");
                    KickEx(playerid);
                }
            }
        }
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
		if (AC_GetPlayerSpeed(playerid) > 350.0 && PlayerData[playerid][pAdmin] < 1)
		{
            SendAdminMessage(X11_TOMATO, "AdmWarning: Cheat detected on {FFFF00}%s (%s) [%s] {FF6347}(%s)", GetName(playerid, false), GetUsername(playerid), ReturnIP(playerid), (IsPlayerInAnyVehicle(playerid)) ? ("Vehicle Speedhack") : ("Onfoot Speedhack"));
		    SendClientMessageEx(playerid, X11_YELLOW, "(AntiCheat) "GREY"You have been kicked from the server because of using some suspicious programs (SpeedHack)");
            KickEx(playerid);
		}
        if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && !GetEngineStatus(GetPlayerVehicleID(playerid)) && GetVehicleSpeed(GetPlayerVehicleID(playerid)) > 15.0) {
            if(++engine_hack_warn[playerid] >= 5) {
                SendClientMessageEx(playerid, X11_YELLOW, "(AntiCheat) "GREY"You have been kicked from the server because of using some suspicious programs (Engine Hack)");
                KickEx(playerid);
            }
        }

        new vehicleid = GetPlayerVehicleID(playerid);

        if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && !IsAPlane(vehicleid) && GetVehicleSpeed(vehicleid) > 300) {
            if(++speed_hack[playerid] > 5) {
                SendAdminMessage(X11_TOMATO, "AntiCheat: "GREY"Cheat detected on {FFFF00}%s {FF6347}(Vehicle Speedhack)", GetName(playerid));
                SendClientMessageEx(playerid, X11_YELLOW, "(AntiCheat) "GREY"You have been kicked from the server because of using some suspicious programs (SpeedHack)");
                speed_hack[playerid] = 0;   
                KickEx(playerid);  
            }
        }
        new Float:X,Float:Y,Float:Z;
        GetPlayerPos(playerid,X,Y,Z);
        if(Z == BulletCrasher || !(InvalidSeat1 <= Z <= InvalidSeat2)) {
            new tipcrasher[56];
            tipcrasher= "Bad Vehicle Crasher";
            if(Z == BulletCrasher)
                tipcrasher= "Bullet Crasher";

            SendAdminMessage(X11_TOMATO, "AntiCheat: "GREY"Cheat detected on {FFFF00}%s {FF6347}(%s)", GetName(playerid), tipcrasher);
            SendClientMessageEx(playerid, X11_YELLOW, "(AntiCheat) "GREY"You have been kicked from the server because of using some suspicious programs (Crasher)");
            KickEx(playerid);
        }
        if(AC_PlayerHasWeapon(playerid, WEAPON_BOMB) && !PlayerData[playerid][pAdmin]) {
            CallLocalFunction("OnPlayerCrasher", "d", playerid);
        }
		new Float:x,Float:y,Float:z;
		GetPlayerCameraFrontVector(playerid,x,y,z);
		if(floatcmp(1.0,floatabs(x))==-1 || floatcmp(1.0,floatabs(y))==-1 || floatcmp(1.0,floatabs(z))==-1)
		{
            if(AOFCT[playerid] < GetTickCount())
                AOFCW[playerid] = 0;
            else 
                AOFCW[playerid]++;
                
            if(AOFCW[playerid] < 2) 
                AOFCT[playerid]= GetTickCount()+1000; 
            else {
                CallLocalFunction("OnPlayerCrasher", "d", playerid);
            }
		}
		if(GetPlayerPing(playerid) > 800) {
			ping_warning[playerid]++;
            SendClientMessageEx(playerid, X11_YELLOW, "(Ping) "GREY"High ping detected on your account (%d/3)", ping_warning[playerid]);
            if(ping_warning[playerid] > 3) {
                ping_warning[playerid] = 0;
                SendClientMessageToAllEx(X11_TOMATO, "BotCmd: %s has been kicked from the server due to high ping (%d/800)", GetName(playerid), GetPlayerPing(playerid));
                KickEx(playerid);
            }
		}
    }
    else {
        if(AC_GetPlayerSpeed(playerid) > 1.0) {
            SendClientMessageEx(playerid, X11_YELLOW, "(AntiCheat) "GREY"You have been kicked from the server because of using some suspicious programs (Fake Spawn)");
            KickEx(playerid);
        }
    }
    return 1;
}

function OnPlayerCrasher(playerid) {
    SendAdminMessage(X11_TOMATO, "AntiCheat: "GREY"Cheat detected on {FFFF00}%s {FF6347}(Crasher)", GetName(playerid));
    SendClientMessageEx(playerid, X11_YELLOW, "(AntiCheat) "GREY"You have been kicked from the server because of using some suspicious programs (Crasher)");
    KickEx(playerid);
    return 1;
}

function CheckWeaponHack(playerid, weaponid) {
    if(weaponid != PlayerData[playerid][pWeapon] && !PlayerData[playerid][pAdmin])
    {
        PlayerData[playerid][pWeapon] = weaponid;

        if(PlayerData[playerid][pWeapon] >= 1 && PlayerData[playerid][pWeapon] <= 45 && PlayerData[playerid][pWeapon] != 40 && PlayerData[playerid][pWeapon] != 2 && PlayerData[playerid][pGuns][g_aWeaponSlots[PlayerData[playerid][pWeapon]]] != weaponid && !PlayerData[playerid][pKicked])
        {
            SendAdminMessage(COLOR_LIGHTRED, "AntiCheat: Cheat detected on {FFFF00}%s (%s) {FF6347}(Weapon hack %s)", GetName(playerid), PlayerData[playerid][pUCP], ReturnWeaponName(PlayerData[playerid][pWeapon]));
            ResetWeapons(playerid);
            KickEx(playerid);
        }
    }
    return 1;
}

public OnPlayerAirbreak(playerid) {

    if(++airbreak_hack[playerid] >= 5) {
        SendAdminMessage(X11_TOMATO, "AntiCheat: "GREY"Cheat detected on {FFFF00}%s {FF6347}(Airbreak)", GetName(playerid));
        SendClientMessageEx(playerid, X11_TOMATO, "AntiCheat: "GREY"You have been kicked for using illegal programs (Airbreak)");
        KickEx(playerid);  
    }
    return 1;
}

forward OnDetectedOldversion(playerid);
public OnDetectedOldversion(playerid)
{
    UsingMods[playerid][MOD_OLD_VERSION] = true;
    return 1;
}
forward OnDetectedImprovedDeagle(playerid);
public OnDetectedImprovedDeagle(playerid)
{
    UsingMods[playerid][MOD_IMPROVED_DEAGLE] = true;
    return 1;
}
forward OnDetectedExtraWS(playerid);
public OnDetectedExtraWS(playerid)
{
    UsingMods[playerid][MOD_EXTRAWS] = true;
    return 1;
}
forward OnDetecteds0beit(playerid);
public OnDetecteds0beit(playerid)
{
    UsingMods[playerid][MOD_SOBEIT] = true;
    return 1;
}
forward OnDetectedSAMPFUNCS(playerid);
public OnDetectedSAMPFUNCS(playerid)
{
    UsingMods[playerid][MOD_SAMPFUNCS] = true;
    return 1;
}
forward OnDetectedSprintHook(playerid);
public OnDetectedSprintHook(playerid)
{
    UsingMods[playerid][MOD_SPRINTHOOK] = true;
    return 1;
}
forward OnDetectedMods(playerid);
public OnDetectedMods(playerid)
{
	UsingMods[playerid][MOD_CLEO_MODLOADER] = true;
    return 1;
}
forward OnDetectedbypass(playerid);
public OnDetectedbypass(playerid)
{
    UsingMods[playerid][MOD_BYPASS] = true;
    return 1;
}
forward OnDetectedSilentaim(playerid);
public OnDetectedSilentaim(playerid)
{
    UsingMods[playerid][MOD_SILENTAIM] = true;
    return 1;
}
