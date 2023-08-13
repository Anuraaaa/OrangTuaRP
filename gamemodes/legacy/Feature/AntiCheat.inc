#include <YSI_Coding\y_hooks>

#define 	MAX_CHEAT_WARNING		2

#define     BulletCrasher -5.5
#define     InvalidSeat1 -1000000.0
#define     InvalidSeat2 1000000.0

new WarningCode[MAX_PLAYERS][53],
    tele_warn[MAX_PLAYERS]= {0, ...},
    slapper_warn[MAX_PLAYERS]= {0, ...},
    engine_hack_warn[MAX_PLAYERS]= {0, ...},
    speed_hack[MAX_PLAYERS]= {0, ...},
    airbreak_hack[MAX_PLAYERS]= {0, ...},
    ping_warning[MAX_PLAYERS]= {0, ...},
    ac_weapon_h[MAX_PLAYERS]= {0, ...},
    ac_ammo_h[MAX_PLAYERS]= {0, ...},
    ac_ammo_inf_h[MAX_PLAYERS]= {0, ...};

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

hook OnGameModeInit()
{
    EnableAntiCheat(4, 0); // disable Teleport Hack: Into/Between Vehicle
    EnableAntiCheat(5, 0); // disable Teleport Hack: Vehicle to Player
    EnableAntiCheat(6, 0); // disable Teleport Hack: Pickups
    EnableAntiCheat(9, 0); // disable SpeedHack: On Foot
    EnableAntiCheat(23, 0); // disable Tunning Hack
    EnableAntiCheat(24, 0); // disable Parkour Mod
    // EnableAntiCheat(26, 0); // disable Rapid Fire
    EnableAntiCheat(27, 0); // disable Fake Spawn
    // EnableAntiCheat(29, 0); // disable Aimbot
    EnableAntiCheat(31, 0); // disable Car Shot
    EnableAntiCheat(33, 0); // disable Unfreeze
    EnableAntiCheat(34, 0); // disable AFK Ghost
    EnableAntiCheat(35, 0); // disable Full Aiming
    EnableAntiCheat(36, 0); // disable Fake NPC
    EnableAntiCheat(37, 0); // disable Reconnect
    EnableAntiCheat(38, 0); // disable High Ping
    EnableAntiCheat(39, 0); // disable Dialog Hack
    EnableAntiCheat(40, 0); // disable Protection from sandbox
    EnableAntiCheat(41, 0); // disable Protection from invalid version
    EnableAntiCheat(42, 0); // disable Rcon Hack
    EnableAntiCheat(43, 0); // disable Tuning Crasher
    EnableAntiCheat(45, 0); // disable Dialog Crasher
    EnableAntiCheat(46, 0); // disable Attached Object Crasher
    EnableAntiCheat(47, 0); // disable Weapon Crasher
    EnableAntiCheat(48, 0); // disable Protection from connection flood in one slot
    EnableAntiCheat(49, 0); // disable Callback functions flood
    EnableAntiCheat(50, 0); // disable DoS
    EnableAntiCheat(51, 0); // disable NOPs
}

static GetCodeAC(code)
{    
    new string[128];
    switch(code)
    {
		case 0: string = "AirBreak: On Foot";
		case 1: string = "AirBreak: Inside Vehicle";
		case 2: string = "Teleport Hack: On Foot";
		case 3: string = "Teleport Hack: Inside Vehicle";
		case 4: string = "Teleport Hack: Into/Between Vehicle";
		case 5: string = "Teleport Hack: Vehicle to Player";
		case 6: string = "Teleport Hack: Pickups";
		case 7: string = "FlyHack: On Foot";
		case 8: string = "FlyHack: Inside Vehicle";
		case 9: string = "SpeedHack: On Foot";
		case 10: string = "SpeedHack: Inside Vehicle";
		case 11: string = "Health Hack: Inside Vehicle";
		case 12: string = "Health Hack: On Foot";
		case 13: string = "Armour Hack";
		case 14: string = "Money Hack";
		case 15: string = "Weapon Hack";
		case 16: string = "Ammo Hack: Spawning";
		case 17: string = "Ammo Hack: Infinite";
		case 18: string = "Special Actions Hack";
		case 19: string = "GodMode from a bullets: On Foot";
		case 20: string = "GodMode from a bullets: Inside Vehicle";
		case 21: string = "Invisible Hack";
		case 22: string = "Lagcomp-Spoof";
		case 23: string = "Tuning Hack";
		case 24: string = "Parkour Mod";
		case 25: string = "Quick Turn";
		case 26: string = "Rapid Fire";
		case 27: string = "Fake Spawn";
		case 28: string = "Fake Kill";
		case 29: string = "Aimbot";
		case 30: string = "CJ Run";
		case 31: string = "Car Shot";
		case 32: string = "Car Jacking";
		case 33: string = "UnFreeze";
		case 34: string = "AFK Ghost";
		case 35: string = "Full Aiming";
		case 36: string = "Fake NPC";
		case 37: string = "Reconnect";
		case 38: string = "High Ping";
		case 39: string = "Dialog Hack";
		case 40: string = "Protection from Sandbox";
		case 41: string = "Protection from Invalid Version";
		case 42: string = "Rcon Hack";
		case 43: string = "Tuning Crasher";
		case 44: string = "Invalid Seat Crasher";
		case 45: string = "Dialog Crasher";
		case 46: string = "Attached Object Crasher";
		case 47: string = "Weapon Crasher";
		case 48: string = "Protection from connection flood in one slot";
		case 49: string = "Callback functions flood";
		case 50: string = "Flood by seat changing";
		case 51: string = "DoS";
        case 52: string = "NOPs";
    }
    return string;
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
    if (!IsPlayerConnected(playerid))
        return 0;

    switch(code)
    {
        //Onfoot airbreak
        case 0: {
            if(++hack_airbreak[playerid] >= 3)
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
            if(++hack_airbreak[playerid] >= 3)
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
                if(++hack_teleport[playerid] >= 3)
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
            if(++hack_vehtele[playerid] >= 3) 
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
            if(++hack_fly[playerid] >= 3)
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
            if(++hack_fly[playerid] >= 3)
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
            if(++speed_hack[playerid] >= 5) {
                SendAdminMessage(X11_TOMATO, "AntiCheat: "GREY"Cheat detected on {FFFF00}%s {FF6347}(Vehicle Speedhack)", GetName(playerid));
                SendClientMessageEx(playerid, X11_YELLOW, "(AntiCheat) "GREY"You have been kicked from the server because of using some suspicious programs (SpeedHack)");
                speed_hack[playerid] = 0;   
                KickEx(playerid);  
            }
        }
        
        //Vehicle health hack
        case 11: {
            new Float:health;
            new vehicleid = GetPlayerVehicleID(playerid);

            if (vehicleid == INVALID_VEHICLE_ID) {
                return 0;
            }

            AntiCheatGetVehicleHealth(vehicleid, health);
            defer AC_SetVehicleHealthBack[1000](vehicleid, health);
            if(++hack_vehiclehealth[playerid] >= 3)
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
            defer AC_SetHealthBack[1000](playerid, health);

            if(++hack_health[playerid] >= 3)
            {
                SendClientMessageEx(playerid, X11_YELLOW, "(AntiCheat) "GREY"You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));
                hack_health[playerid] = 0;
                KickEx(playerid);
                return 1;
            }
            SendAdminMessage(X11_TOMATO, "Anticheat: %s possible health hack.", GetName(playerid));
        }
        //Armour Hack
        case 13: {
            new Float:armour;
            AntiCheatGetArmour(playerid, armour);
            defer AC_SetArmorBack[1000](playerid, armour);

            if(++hack_armour[playerid] >= 3)
            {
                SendClientMessageEx(playerid, X11_YELLOW, "(AntiCheat) "GREY"You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));

                hack_armour[playerid] = 0;

                KickEx(playerid);
                return 1;
            }
            SendAdminMessage(X11_TOMATO, "Anticheat: %s possible armour hack.", GetName(playerid));
        }
        //Weapon hack
        case 15: {
            defer AC_SetWeaponBack[1000](playerid);

            if (++ac_weapon_h[playerid] >= 3) {

                SendClientMessageEx(playerid, X11_YELLOW, "(AntiCheat) "GREY"You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));
                ac_weapon_h[playerid] = 0;
                KickEx(playerid);
            }
            SendAdminMessage(X11_TOMATO, "Anticheat: %s possible weapon hack.", GetName(playerid));
        }

        //Ammo hack
        case 16: {
            defer AC_SetWeaponBack[1000](playerid);

            if (++ac_ammo_h[playerid] >= 3) {

                SendClientMessageEx(playerid, X11_YELLOW, "(AntiCheat) "GREY"You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));
                ac_ammo_h[playerid] = 0;
                KickEx(playerid);
            }
            SendAdminMessage(X11_TOMATO, "Anticheat: %s possible add ammo hack.", GetName(playerid));
        }

        //Ammo hack infinite
        case 17: {
            defer AC_SetWeaponBack[1000](playerid);

            if (++ac_ammo_inf_h[playerid] >= 3) {

                SendClientMessageEx(playerid, X11_YELLOW, "(AntiCheat) "GREY"You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));
                ac_ammo_inf_h[playerid] = 0;
                KickEx(playerid);
            }
            SendAdminMessage(X11_TOMATO, "Anticheat: %s possible infinite ammo hack.", GetName(playerid)); 
        }

        case 18: {
            SendAdminMessage(X11_TOMATO, "Anticheat: %s is using special animations hack.", GetName(playerid));
            SendClientMessageEx(playerid, X11_YELLOW, "(AntiCheat) "GREY"You have been kicked from the server because of using some suspicious programs (%s)", GetCodeAC(code));
            KickEx(playerid);
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
    SendAdminMessage(X11_TOMATO, "Anticheat: %s (%s) possible %s", GetName(playerid), ReturnIP(playerid), GetCodeAC(code));
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

hook OnPlayerConnect(playerid) {

	ResetPlayerWarningCode(playerid);

    slapper_warn[playerid] = 0;
    engine_hack_warn[playerid] = 0;
    speed_hack[playerid] = 0;
    airbreak_hack[playerid] = 0;
    hack_health[playerid] = 0;
    hack_armour[playerid] = 0;
    hack_teleport[playerid] = 0;
    hack_airbreak[playerid] = 0;
    hack_vehiclehealth[playerid] = 0;
    hack_vehtele[playerid] = 0;
    hack_fly[playerid] = 0;
    ac_weapon_h[playerid] = 0;
    ac_ammo_h[playerid] = 0;
    ac_ammo_inf_h[playerid] = 0;

    for(new i = 0; i < 9; i++) {
        UsingMods[playerid][i] = false;
    }
}

hook OnPlayerDisconnect(playerid, reason) {

	ResetPlayerWarningCode(playerid);

    slapper_warn[playerid] = 0;
    engine_hack_warn[playerid] = 0;
    speed_hack[playerid] = 0;
    airbreak_hack[playerid] = 0;
    hack_health[playerid] = 0;
    hack_armour[playerid] = 0;
    hack_teleport[playerid] = 0;
    hack_airbreak[playerid] = 0;
    hack_vehiclehealth[playerid] = 0;
    hack_vehtele[playerid] = 0;
    hack_fly[playerid] = 0;
    ac_weapon_h[playerid] = 0;
    ac_ammo_h[playerid] = 0;
    ac_ammo_inf_h[playerid] = 0;


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

public OnPlayerUseVending(playerid, type) {

    new Float:health;
    AntiCheatGetHealth(playerid, health);
    defer AC_SetHealthBack[1000](playerid, health);

    SendAdminMessage(X11_TOMATO, "AdmWarning: %s terdeteksi menggunakan vending machines.", GetName(playerid, false));
    SendClientMessage(playerid, X11_RED, "Kamu terdeteksi melakukan abuse dengan vending machines! (notif ini akan muncul ke administrator & log server)");
    return 1;
}

timer AC_SetWeaponBack[1000](playerid) {

    new
        ac_weapon[13],
        ac_ammo[13];

    for (new i = 0; i < 12; i++) {
        AntiCheatGetWeaponData(playerid, i, ac_weapon[i], ac_ammo[i]);

        ResetWeapon(playerid, ac_weapon[i]);
        PlayerData[playerid][pGuns][i] = ac_weapon[i];
        PlayerData[playerid][pAmmo][i] = ac_ammo[i];
        SetWeapons(playerid);
    }
}

timer AC_SetHealthBack[1000](playerid, Float:health) {
    SetPlayerHealth(playerid, health);
}

timer AC_SetArmorBack[1000](playerid, Float:armour) {    
    SetPlayerArmour(playerid, armour);
}

timer AC_SetVehicleHealthBack[1000](vehicleid, Float:health) {
    SetVehicleHealth(vehicleid, health);
}