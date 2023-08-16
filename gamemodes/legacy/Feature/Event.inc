#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_timers>


/*==============================================================================
	Dearby Mode Enumemators.
==============================================================================*/
enum e_eventDearby {
	Float:evPos[4],
	evEntry,
	evLimit,
	evModel,
	evTime,
	evPrice,
	evWorld,
	evInterior,
	STREAMER_TAG_AREA:evArea,
	evCountdown[MAX_PLAYERS],
};
new dearby_EventData[e_eventDearby];

/*==============================================================================
	Race Mode Enumemators.
==============================================================================*/
enum e_eventRace {
	Float:evPos[4],
	evEntry,
	evLimit,
	evModel,
	evTime,
	evPrice,
	evWorld,
	evWinner,
	evCP[MAX_PLAYERS],
	evCountdown[MAX_PLAYERS],
};
new race_EventData[e_eventRace];

enum e_eventRaceCP {

	cpIndex,
	cpName[64],
	cpLastUsed[32],
	cpPublisher[MAX_PLAYER_NAME],
	Float:cpDistance,
};
new race_CPData[20][e_eventRaceCP];
new Iterator:RacesMap<20>;

new SelectedRaceMap = -1;
new SelectedRaceMapEx = -1;

enum e_eventRaceCPEx {

	cpIndex,
	Float:cpRace[3],
};
new race_CPInfo[20][20][e_eventRaceCPEx];
new Iterator:RacesCP<400,20>;
new HighestEXP;
new PlayerHighestEXP;

/*==============================================================================
	TDM Mode Enumemators.
==============================================================================*/
enum e_TDM_Event {

	eventEntry,
	eventLimit,
	eventPrice,
	eventSkin[2],
	eventTeamScore[2],
	eventMaxScore,
	eventSelection,
	eventWorld,
	eventInterior,
	eventWinner,
	eventWeapons[3],
	eventAmmo[3],
	eventCD[MAX_PLAYERS],
	Float:eventPosX[2],
	Float:eventPosY[2],
	Float:eventPosZ[2],
	Float:eventPosA[2],

	STREAMER_TAG_AREA:eventArea,
};
new tdm_EventData[e_TDM_Event];
static PlayerText:TDM_TD[MAX_PLAYERS][5];


new arrWeap[27][] = {

	"Brassknuckle", "Golfclub",
	"Nitestick", "Knife",
	"Baseball Bat", "Shovel",
	"Pool cue", "Katana",
	"Chainsaw", "Dildo",
	"Dildo 2", "Vibrator",
	"Vibrator 2", "Colt45",
	"Silenced Pistol", "Desert Eagle",
	"Shotgun", "Sawnoff",
	"Spass-12", "UZI",
	"MP5", "AK47", "M4", "Tec9",
	"Rifle", "Sniper", "Rocket Launcher"
};
new arrWeapData[] = {

	WEAPON_BRASSKNUCKLE, WEAPON_GOLFCLUB,
	WEAPON_NITESTICK, WEAPON_KNIFE,
	WEAPON_BAT, WEAPON_SHOVEL, WEAPON_POOLSTICK,
	WEAPON_KATANA, WEAPON_CHAINSAW, WEAPON_DILDO,
	WEAPON_DILDO2, WEAPON_VIBRATOR, WEAPON_VIBRATOR2,
	WEAPON_COLT45, WEAPON_SILENCED, WEAPON_DEAGLE,
	WEAPON_SHOTGUN, WEAPON_SAWEDOFF, WEAPON_SHOTGSPA,
	WEAPON_UZI, WEAPON_MP5, WEAPON_AK47, WEAPON_M4,
	WEAPON_TEC9, WEAPON_RIFLE, WEAPON_SNIPER,
	WEAPON_ROCKETLAUNCHER
};
new arrAmmoData[] = {

	50, 100, 150,
	250, 350, 500
};
/*==============================================================================
	DM Mode Enumemators.
==============================================================================*/

enum e_DM_Event {

	eventEntry,
	eventLimit,
	eventPrice,
	//eventSkin,
	eventMaxScore,
	eventWorld,
	eventInterior,
	eventWinner,
	eventWeapons[3],
	eventAmmo[3],
	eventCD[MAX_PLAYERS],
	eventExp[MAX_PLAYERS],
	Float:eventPosX,
	Float:eventPosY,
	Float:eventPosZ,
	Float:eventPosA,

	STREAMER_TAG_AREA:eventArea,
};
new dm_EventData[e_DM_Event];
static PlayerText:DM_TD[MAX_PLAYERS][6];


/*==============================================================================
	Parachute Mode Enumemators.
==============================================================================*/

enum e_PARA_EventData {

	eventEntry,
	eventLimit,
	eventPrice,
	eventWorld,
	eventInterior,
	eventWinner,
	eventWinnerPrice,
	eventSelectPos,
	eventCD[MAX_PLAYERS],
	Float:eventLandingX,
	Float:eventLandingY,
	Float:eventLandingZ,
};
new parachute_EventData[e_PARA_EventData];

new Float:arrFlyFrom[6][4] = {

	{0.0,0.0,0.0,0.0}, // As default
	{1481.4126,-1789.1826,156.7533,178.2234},
	{1545.8698,-1352.7760,329.4735,107.3143},
	{-1790.8743,567.6440,332.8019,207.8202},
	{1971.9750,1913.9811,130.9375,96.3839},
	{36.3416,2262.7424,124.2270,320.8591}
};

new const arrFlyData[6][] = {

	"Not selected",
	"LS City Hall Tower",
	"Downtown LS Building Rooftop",
	"San Fierro Office Rooftop",
	"Caligula's Palace Rooftop",
	"Tebing Bandara Bekas LV"
};
/*==============================================================================
	Parachute Mode Enumemators.
==============================================================================*/
enum e_Zombie_Event {

	eventEntry,
	eventLimit,
	eventPrice,
	eventAlive,
	eventTimer,
	eventWorld,
	eventInterior,
	eventWinner,
	eventWeapons[3],
	eventAmmo[3],
	eventCD[MAX_PLAYERS],
	Float:eventPosX[2],
	Float:eventPosY[2],
	Float:eventPosZ[2],
	Float:eventPosA[2],

	STREAMER_TAG_AREA:eventArea,
};
new zombie_EventData[e_Zombie_Event];
static PlayerText:ZombieTD[MAX_PLAYERS][4];


/*==============================================================================
	Global Variable.
==============================================================================
enum eventMap {
	evID,
	evName[32],
	evDate[24],
	evAuthor[MAX_PLAYER_NAME],
	evType,
	Float:evPos[4],
};
new EventMap[MAX_EVENT_MAP+1][eventMap];
new Iterator:evMap<MAX_EVENT_MAP>;*/

new EventCreated,
	EventStarted,
	EventType,
	EventHost[24];

new evTeam[MAX_PLAYERS] = {0 , ...},
	evRaceCP[MAX_PLAYERS] = {-1 , ...},
	evCar[MAX_PLAYERS] = {INVALID_VEHICLE_ID , ...};

hook OnGameModeInit()
{
	EventCreated = 0;
	EventStarted = 0;

	EventType = 0;
	format(EventHost, sizeof(EventHost), "null");

	Iter_Init(RacesMap);
	// mysql_tquery(sqlcon, "SELECT * FROM `racemap`", "Race_Event_Load", "");
}

hook OnGameModeExit()
{
	if (EventStarted)
		Event_ForceEnd();

	foreach (new cp : RacesMap) if (Iter_Contains(RacesMap, cp)) {

		Race_EventCP_Save(cp);
		Race_Event_Save(cp);

		Iter_SafeRemove(RacesMap, cp, cp);
	}
	SelectedRaceMap = -1;
	SelectedRaceMapEx = -1;
}

CMD:event(playerid, params[])
{
	if (!strcmp(params, "join", true))
	{
		if (!EventCreated)
			return SendErrorMessage(playerid, "Tidak ada event yang sedang berlangsung!");

		if (EventStarted)
			return SendErrorMessage(playerid, "Event telah dimulai!");

		if (OnMower[playerid] || OnSweeping[playerid] || IsPlayerWorkInBus(playerid))
			return SendErrorMessage(playerid, "Harap selesaikan sidejobmu terlebih dahulu!");

		if (PlayerData[playerid][pOnDMV])
			return SendErrorMessage(playerid, "Harap selesaikan driving testmu terlebih dahulu!");

		if (PlayerData[playerid][pAduty])
			return SendErrorMessage(playerid, "Harap matikan admin duty terlebih dahulu sebelum bergabung kedalam event!");

		if (PlayerData[playerid][pMaskOn])
			return SendErrorMessage(playerid, "Harap lepaskan masker milikmu terlebih dahulu sebelum bergabung kedalam event!");

		if (PlayerData[playerid][pJailTime] > 0 || PlayerData[playerid][pArrest])
			return SendErrorMessage(playerid, "Kamu tidak dapat bergabung kedalam event ketika sedang didalam penjara apapun!");

		if (PlayerData[playerid][pAFK] > 0)
			return SendErrorMessage(playerid, "Harap keluar dari AFK-Mode terlebih dahulu sebelum bergabung kedalam event!");

		if (PlayerData[playerid][pLoopAnim] && !AnimationCheck(playerid))
			return SendErrorMessage(playerid, "Kamu tidak dapat bergabung kedalam event saat ini!");

		if (GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
			return SendErrorMessage(playerid, "You must be on foot before join an event!");

		if (EventType == 1)
		{
			new rand = RandomEx(1, 100);

			if ((race_EventData[evEntry] >= race_EventData[evLimit]) && !PlayerVIP[playerid][vipLevel])
				return SendErrorMessage(playerid, "Event saat ini telah penuh!");

			if (GetPVarInt(playerid, "IsAtEvent") > 0)
				return SendErrorMessage(playerid, "Kamu sudah masuk kedalam event saat ini!");

			if (race_EventData[evCountdown] > 0)
				return SendErrorMessage(playerid, "Admin telah memulai mode ini, tidak dapat bergabung!");

			SetPVarInt(playerid, "IsAtEvent", EventType);

			SetPlayerColor(playerid, X11_GREEN);
			ResetPlayerWeapons(playerid);

			race_EventData[evEntry] ++;
			race_EventData[evCountdown][playerid] = 20;

			GetPlayerHealth(playerid, PlayerData[playerid][pHealth]);
			GetPlayerArmour(playerid, PlayerData[playerid][pArmor]);

			GetPlayerPos(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);

			PlayerData[playerid][pWorld] = GetPlayerVirtualWorld(playerid);
			PlayerData[playerid][pInterior] = GetPlayerInterior(playerid);

			SetPlayerHealth(playerid, 100.0);
			SetPlayerArmour(playerid, 0.0);

			SetPlayerPositionEx(playerid, race_EventData[evPos][0], race_EventData[evPos][1], race_EventData[evPos][2]);
			SetPlayerFacingAngle(playerid, race_EventData[evPos][3]);

			evCar[playerid] = Vehicle_Create(race_EventData[evModel], race_EventData[evPos][0], race_EventData[evPos][1], race_EventData[evPos][2], race_EventData[evPos][3], rand, rand);
			Vehicle_SetType(evCar[playerid], VEHICLE_TYPE_EVENT);
			SetVehicleNumberPlate(evCar[playerid], "EVENT");

			SetPlayerVirtualWorld(playerid, race_EventData[evEntry] + 20);
			SetVehicleVirtualWorld(evCar[playerid], GetPlayerVirtualWorld(playerid));

			PutPlayerInVehicle(playerid, evCar[playerid], 0);
			SwitchVehicleEngine(evCar[playerid], true);

			DisableRemoteVehicleCollisions(playerid, 1);
			TogglePlayerControllable(playerid, 0);

			SendClientMessageEx(playerid, COLOR_SERVER, "EVENT: "WHITE"Kamu sudah memasuki event "YELLOW"%s "WHITE"mode.", ReturnEventMode(EventType));
			SendClientMessage(playerid, COLOR_SERVER, "EVENT: "WHITE"Harap tunggu beberapa waktu hingga Admin memulai event ini!");
		
			SendEventMessage(EventType, COLOR_SERVER, "EVENT: "GREEN"%s "YELLOW"telah bergabung kedalam event ini.", GetName(playerid));
		}
		else if (EventType == 2)
		{
			new rand = RandomEx(1, 100);

			if ((dearby_EventData[evEntry] >= dearby_EventData[evLimit]) && !PlayerVIP[playerid][vipLevel])
				return SendErrorMessage(playerid, "Event saat ini telah penuh!");

			if (GetPVarInt(playerid, "IsAtEvent") > 0)
				return SendErrorMessage(playerid, "Kamu sudah masuk kedalam event saat ini!");

			if (dearby_EventData[evCountdown] > 0)
				return SendErrorMessage(playerid, "Admin telah memulai mode ini, tidak dapat bergabung!");

			SetPVarInt(playerid, "IsAtEvent", EventType);

			SetPlayerColor(playerid, X11_CYAN1);
			ResetPlayerWeapons(playerid);

			dearby_EventData[evEntry] ++;

			GetPlayerHealth(playerid, PlayerData[playerid][pHealth]);
			GetPlayerArmour(playerid, PlayerData[playerid][pArmor]);

			GetPlayerPos(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);

			PlayerData[playerid][pWorld] = GetPlayerVirtualWorld(playerid);
			PlayerData[playerid][pInterior] = GetPlayerInterior(playerid);

			SetPlayerHealth(playerid, 100.0);
			SetPlayerArmour(playerid, 0.0);

			SetPlayerPositionEx(playerid, dearby_EventData[evPos][0], dearby_EventData[evPos][1], dearby_EventData[evPos][2]);
			SetPlayerFacingAngle(playerid, dearby_EventData[evPos][3]);

			evCar[playerid] = Vehicle_Create(race_EventData[evModel], race_EventData[evPos][0], race_EventData[evPos][1], race_EventData[evPos][2], race_EventData[evPos][3], rand, rand);
			Vehicle_SetType(evCar[playerid], VEHICLE_TYPE_EVENT);
			SetVehicleNumberPlate(evCar[playerid], "EVENT");
			
			SetPlayerVirtualWorld(playerid, dearby_EventData[evEntry] + 20);
			SetVehicleVirtualWorld(evCar[playerid], GetPlayerVirtualWorld(playerid));

			SetPlayerInterior(playerid, dearby_EventData[evInterior]);
			LinkVehicleToInterior(evCar[playerid], GetPlayerInterior(playerid));

			PutPlayerInVehicle(playerid, evCar[playerid], 0);
			SwitchVehicleEngine(evCar[playerid], true);

			TogglePlayerControllable(playerid, 0);

			SendClientMessageEx(playerid, COLOR_SERVER, "EVENT: "WHITE"Kamu sudah memasuki event "YELLOW"%s "WHITE"mode.", ReturnEventMode(EventType));
			SendClientMessage(playerid, COLOR_SERVER, "EVENT: "WHITE"Harap tunggu beberapa waktu hingga Admin memulai event ini!");
		
			SendEventMessage(EventType, COLOR_SERVER, "EVENT: "CYAN1"%s "YELLOW"telah bergabung kedalam event ini.", GetName(playerid));
		}
		else if (EventType == 3) {

			if ((tdm_EventData[eventEntry] >= tdm_EventData[eventLimit]) && !PlayerVIP[playerid][vipLevel])
				return SendErrorMessage(playerid, "Event saat ini telah penuh!");

			if (GetPVarInt(playerid, "IsAtEvent") > 0)
				return SendErrorMessage(playerid, "Kamu sudah masuk kedalam event saat ini!");

			if (PlayerData[playerid][pTazer])
				cmd_tazer(playerid, "\0");

			SetPVarInt(playerid, "IsAtEvent", EventType);
			ResetPlayerWeapons(playerid);

			tdm_EventData[eventEntry] ++;
			tdm_EventData[eventCD][playerid] = 30;

			GetPlayerHealth(playerid, PlayerData[playerid][pHealth]);
			GetPlayerArmour(playerid, PlayerData[playerid][pArmor]);

			GetPlayerPos(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);

			PlayerData[playerid][pWorld] = GetPlayerVirtualWorld(playerid);
			PlayerData[playerid][pInterior] = GetPlayerInterior(playerid);

			if (tdm_EventData[eventSelection]) {

				tdm_EventData[eventSelection] = 0;
				evTeam[playerid] = 1;

				SetPlayerHealth(playerid, 999.0);
				SetPlayerArmour(playerid, 0.0);

				SetPlayerColor(playerid, RemoveAlpha(X11_RED));
				SetPlayerSkin(playerid, tdm_EventData[eventSkin][0]);

				SetPlayerPositionEx(playerid, tdm_EventData[eventPosX][0], tdm_EventData[eventPosY][0], tdm_EventData[eventPosZ][0]);
				SetPlayerFacingAngle(playerid, tdm_EventData[eventPosA][0]);

				SetPlayerVirtualWorld(playerid, tdm_EventData[eventWorld]+5);
				SetPlayerInterior(playerid, tdm_EventData[eventInterior]);
			}
			else {

				tdm_EventData[eventSelection] = 1;
				evTeam[playerid] = 2;

				SetPlayerHealth(playerid, 999.0);
				SetPlayerArmour(playerid, 0.0);

				SetPlayerColor(playerid, RemoveAlpha(X11_BLUE));
				SetPlayerSkin(playerid, tdm_EventData[eventSkin][1]);

				SetPlayerPositionEx(playerid, tdm_EventData[eventPosX][1], tdm_EventData[eventPosY][1], tdm_EventData[eventPosZ][1]);
				SetPlayerFacingAngle(playerid, tdm_EventData[eventPosA][1]);

				SetPlayerVirtualWorld(playerid, tdm_EventData[eventWorld]+10);
				SetPlayerInterior(playerid, tdm_EventData[eventInterior]);				
			}
			SetPlayerTeam(playerid, evTeam[playerid]);
			SetCameraBehindPlayer(playerid);

			foreach (new id : Player) {

				if (GetPVarInt(id, "IsAtEvent") == EventType) {

					tdm_EventData[eventCD][id] = tdm_EventData[eventCD][playerid];
				}
			}
			static getTeam[][] = { ""RED"Team A", ""BLUE"Team B" };

			SendClientMessageEx(playerid, COLOR_SERVER, "EVENT: "WHITE"Kamu sudah memasuki event "YELLOW"%s "WHITE"mode.", ReturnEventMode(EventType));
			SendClientMessageEx(playerid, COLOR_SERVER, "EVENT: "YELLOW"You're now on %s", getTeam[GetPlayerTeam(playerid)-1]);

			switch (GetPlayerTeam(playerid)) {

				case 1: SendEventMessage(EventType, COLOR_SERVER, "EVENT: "RED"%s "YELLOW"telah bergabung kedalam event ini.", GetName(playerid));
				case 2: SendEventMessage(EventType, COLOR_SERVER, "EVENT: "BLUE"%s "YELLOW"telah bergabung kedalam event ini.", GetName(playerid));
			}
			TDM_ToggleAntiCheat(playerid);
		}
		else if (EventType == 4) {

			if ((dm_EventData[eventEntry] >= dm_EventData[eventLimit]) && !PlayerVIP[playerid][vipLevel])
				return SendErrorMessage(playerid, "Event saat ini telah penuh!");

			if (GetPVarInt(playerid, "IsAtEvent") > 0)
				return SendErrorMessage(playerid, "Kamu sudah masuk kedalam event saat ini!");

			if (PlayerData[playerid][pTazer])
				cmd_tazer(playerid, "\0");

			SetPVarInt(playerid, "IsAtEvent", EventType);
			ResetPlayerWeapons(playerid);

			dm_EventData[eventEntry] ++;
			dm_EventData[eventCD][playerid] = 30;

			GetPlayerHealth(playerid, PlayerData[playerid][pHealth]);
			GetPlayerArmour(playerid, PlayerData[playerid][pArmor]);

			GetPlayerPos(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);

			PlayerData[playerid][pWorld] = GetPlayerVirtualWorld(playerid);
			PlayerData[playerid][pInterior] = GetPlayerInterior(playerid);

			SetPlayerHealth(playerid, 200.0);
			SetPlayerArmour(playerid, 0.0);

			SetPlayerColor(playerid, RemoveAlpha(X11_RED));
			SetCameraBehindPlayer(playerid);

			SetPlayerPositionEx(playerid, dm_EventData[eventPosX], dm_EventData[eventPosY], dm_EventData[eventPosZ]);
			SetPlayerFacingAngle(playerid, dm_EventData[eventPosA]);

			SetPlayerVirtualWorld(playerid, (playerid+1357));
			SetPlayerInterior(playerid, dm_EventData[eventInterior]);

			foreach (new id : Player) {

				if (GetPVarInt(id, "IsAtEvent") == EventType) {

					dm_EventData[eventCD][id] = dm_EventData[eventCD][playerid];
				}
			}
			SendClientMessageEx(playerid, COLOR_SERVER, "EVENT: "WHITE"Kamu sudah memasuki event "YELLOW"%s "WHITE"mode.", ReturnEventMode(EventType));
			SendEventMessage(EventType, COLOR_SERVER, "EVENT: "RED"%s "YELLOW"telah bergabung kedalam event ini.", GetName(playerid));
		
			DM_ToggleAntiCheat(playerid);
		}
		else if (EventType == 5) {

			if ((parachute_EventData[eventEntry] >= parachute_EventData[eventLimit]) && !PlayerVIP[playerid][vipLevel])
				return SendErrorMessage(playerid, "Event saat ini telah penuh!");

			if (GetPVarInt(playerid, "IsAtEvent") > 0)
				return SendErrorMessage(playerid, "Kamu sudah masuk kedalam event saat ini!");

			if (PlayerData[playerid][pTazer])
				cmd_tazer(playerid, "\0");

			SetPVarInt(playerid, "IsAtEvent", EventType);
			ResetPlayerWeapons(playerid);

			parachute_EventData[eventEntry] ++;
			parachute_EventData[eventCD][playerid] = 15;

			GetPlayerHealth(playerid, PlayerData[playerid][pHealth]);
			GetPlayerArmour(playerid, PlayerData[playerid][pArmor]);

			GetPlayerPos(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);

			PlayerData[playerid][pWorld] = GetPlayerVirtualWorld(playerid);
			PlayerData[playerid][pInterior] = GetPlayerInterior(playerid);

			SetPlayerHealth(playerid, 100.0);
			SetPlayerArmour(playerid, 0.0);

			SetPlayerColor(playerid, RemoveAlpha(X11_PURPLE));
			SetCameraBehindPlayer(playerid);

			SetPlayerPositionEx(playerid, arrFlyFrom[parachute_EventData[eventSelectPos]][0], arrFlyFrom[parachute_EventData[eventSelectPos]][1], arrFlyFrom[parachute_EventData[eventSelectPos]][2]);
			SetPlayerFacingAngle(playerid, arrFlyFrom[parachute_EventData[eventSelectPos]][3]);

			SetPlayerVirtualWorld(playerid, (playerid+1357));
			SetPlayerInterior(playerid, parachute_EventData[eventInterior]);

			Parachute_Attach(playerid);
			TogglePlayerControllable(playerid, 0);

			foreach (new id : Player) {

				if (GetPVarInt(id, "IsAtEvent") == EventType) {

					parachute_EventData[eventCD][id] = parachute_EventData[eventCD][playerid];
				}
			}
			SendClientMessageEx(playerid, COLOR_SERVER, "EVENT: "WHITE"Kamu sudah memasuki event "YELLOW"%s "WHITE"mode.", ReturnEventMode(EventType));
			SendEventMessage(EventType, COLOR_SERVER, "EVENT: "PURPLE"%s "YELLOW"telah bergabung kedalam event ini.", GetName(playerid));			
		}
		else if (EventType == 6) {

			if ((zombie_EventData[eventEntry] >= zombie_EventData[eventLimit]) && !PlayerVIP[playerid][vipLevel])
				return SendErrorMessage(playerid, "Event saat ini telah penuh!");

			if (GetPVarInt(playerid, "IsAtEvent") > 0)
				return SendErrorMessage(playerid, "Kamu sudah masuk kedalam event saat ini!");

			if (PlayerData[playerid][pTazer])
				cmd_tazer(playerid, "\0");

			SetPVarInt(playerid, "IsAtEvent", EventType);
			ResetPlayerWeapons(playerid);

			zombie_EventData[eventEntry] ++;
			zombie_EventData[eventCD][playerid] = 20;

			GetPlayerHealth(playerid, PlayerData[playerid][pHealth]);
			GetPlayerArmour(playerid, PlayerData[playerid][pArmor]);

			GetPlayerPos(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);

			PlayerData[playerid][pWorld] = GetPlayerVirtualWorld(playerid);
			PlayerData[playerid][pInterior] = GetPlayerInterior(playerid);

			if (zombie_EventData[eventEntry] <= zombie_EventData[eventAlive]) {

				evTeam[playerid] = 1;

				SetPlayerHealth(playerid, 999.0);
				SetPlayerArmour(playerid, 0.0);

				SetPlayerPositionEx(playerid, zombie_EventData[eventPosX][0], zombie_EventData[eventPosY][0], zombie_EventData[eventPosZ][0]);
				SetPlayerFacingAngle(playerid, zombie_EventData[eventPosA][0]);

				SetPlayerVirtualWorld(playerid, zombie_EventData[eventWorld]+5);
				SetPlayerInterior(playerid, zombie_EventData[eventInterior]);

				SetPlayerColor(playerid, RemoveAlpha(X11_GREEN));
				SendClientMessage(playerid, COLOR_SERVER, "EVENT: "WHITE"You're now as a "GREEN"Defender");
			}
			else {

				evTeam[playerid] = 2;

				SetPlayerHealth(playerid, 999.0);
				SetPlayerArmour(playerid, 0.0);

				SetPlayerPositionEx(playerid, zombie_EventData[eventPosX][1], zombie_EventData[eventPosY][1], zombie_EventData[eventPosZ][1]);
				SetPlayerFacingAngle(playerid, zombie_EventData[eventPosA][1]);

				SetPlayerVirtualWorld(playerid, zombie_EventData[eventWorld]+10);
				SetPlayerInterior(playerid, zombie_EventData[eventInterior]);

				SetPlayerSkin(playerid, 162);
				SetPlayerColor(playerid, RemoveAlpha(X11_RED));

				SendClientMessage(playerid, COLOR_SERVER, "EVENT: "WHITE"You're now as a "RED"Zombie");
			}
			SetPlayerTeam(playerid, evTeam[playerid]);
			SetCameraBehindPlayer(playerid);

			foreach (new id : Player) {

				if (GetPVarInt(id, "IsAtEvent") == EventType) {

					zombie_EventData[eventCD][id] = zombie_EventData[eventCD][playerid];
				}
			}
			SendClientMessageEx(playerid, COLOR_SERVER, "EVENT: "WHITE"Kamu sudah memasuki event "YELLOW"%s "WHITE"mode.", ReturnEventMode(EventType));
			SendEventMessage(EventType, COLOR_SERVER, "EVENT: "GREEN"%s "YELLOW"telah bergabung kedalam event ini.", GetName(playerid));

			Zombie_ToggleAntiCheat(playerid);				
		}
	}
	else if (!strcmp(params, "mode", true))
	{
		if (PlayerData[playerid][pAdmin] < 6)
			return SendErrorMessage(playerid, "You don't have permission to use this command!");

		if(EventCreated)
			return SendErrorMessage(playerid, "There is an event has created!");

		if(EventStarted)
			return SendErrorMessage(playerid, "Event is already started, wait until event is ended!");

		Dialog_Show(playerid, EventMode, DIALOG_STYLE_LIST,
			"Event Mode",
			""GREEN"Race\n\
			"CYAN1"Dearby (maintenace)\n\
			"BLUE"Team Deathmatch\n\
			"RED"Deathmatch\n\
			"PURPLE"Parachute\n\
			{009000}Zombie Survival",
			"Set", "Close"
		);
	}
	else if (!strcmp(params, "info", true))
	{
		if (PlayerData[playerid][pAdmin] < 6)
			return SendErrorMessage(playerid, "You don't have permission to use this command!");

		if ((strcmp(EventHost, PlayerData[playerid][pUCP], true)) && PlayerData[playerid][pAdmin] < 7)
			return SendErrorMessage(playerid, "Event telah dimulai oleh "RED"%s", EventHost);

		static str[1024];

		if (EventType == 1)
		{
			format(str, sizeof(str), "Options\tValue\nEvent Slot\t%d participants\nEvent Price\t$%s ($%s if won)\nEvent Vehicles Model\t%d (%s)\nEvent Position\t%.1f\nEvent Time\t%d minutes\n%s\nTeleport to checkpoint\nAnnounce Event\nForce End",
				race_EventData[evLimit],
				FormatNumber(race_EventData[evPrice]), FormatNumber(race_EventData[evPrice]+1000000),
				race_EventData[evModel], ReturnVehicleModelName(race_EventData[evModel]),
				race_EventData[evPos][0],
				(race_EventData[evTime] / 60),
				((!Iter_Count(RacesMap)) ? ("Create Map") : ("Load Map"))
			);
			Dialog_Show(playerid, EventInfo, DIALOG_STYLE_TABLIST_HEADERS, sprintf("Event Info: %s Mode", ReturnEventMode(EventType)), str, "Select", "Close");
		}
		else if (EventType == 2)
		{
			format(str, sizeof(str), "Options\tValue\nEvent Slot\t%d participants\nEvent Price\t$%s\nEvent Vehicles Model\t%d (%s)\nEvent Position\t%.1f\nEvent Time\t%d minutes\nLoad Map\nAnnounce Event\nForce End",
				dearby_EventData[evLimit],
				FormatNumber(dearby_EventData[evPrice]),
				dearby_EventData[evModel],
				dearby_EventData[evPos][0],
				(dearby_EventData[evTime] / 60)
			);
			Dialog_Show(playerid, EventInfo, DIALOG_STYLE_TABLIST_HEADERS, sprintf("Event Info: %s Mode", ReturnEventMode(EventType)), str, "Select", "Close");
		}
		else if (EventType == 3) {

			format (str, sizeof(str),
				
				"Options\tValues\n\
				Max participants\t%d players\n\
				Max Team Score\t%d points\n\
				Participants Prize\t$%s ($%s if won)\n\
				Participants Team A Skin\t%d\n\
				Participants Team B Skin\t%d\n\
				Participants Team A Spawn\t%.2f near you\n\
				Participants Team B Spawn\t%.2f near you\n\
				Participants Equips\t%s, %s, %s\n\
				Participants Ammo\t%d, %d, %d\n\
				Announce Event\n\
				Force End",

				tdm_EventData[eventLimit],
				tdm_EventData[eventMaxScore],
				FormatNumber(tdm_EventData[eventPrice]),
				FormatNumber(tdm_EventData[eventPrice]*2),
				tdm_EventData[eventSkin][0],
				tdm_EventData[eventSkin][1],
				GetPlayerDistanceFromPoint(playerid, tdm_EventData[eventPosX][0], tdm_EventData[eventPosY][0], tdm_EventData[eventPosZ][0]),
				GetPlayerDistanceFromPoint(playerid, tdm_EventData[eventPosX][1], tdm_EventData[eventPosY][1], tdm_EventData[eventPosZ][1]),
				ReturnWeaponName(tdm_EventData[eventWeapons][0]), ReturnWeaponName(tdm_EventData[eventWeapons][1]), ReturnWeaponName(tdm_EventData[eventWeapons][2]),
				tdm_EventData[eventAmmo][0], tdm_EventData[eventAmmo][1], tdm_EventData[eventAmmo][2]
			);
			Dialog_Show(playerid, EventInfo, DIALOG_STYLE_TABLIST_HEADERS, sprintf("Event Info: %s Mode", ReturnEventMode(EventType)), str, "Select", "Close");
		}
		else if (EventType == 4) {

			format (str, sizeof(str),

				"Options\tValues\n\
				Max participants\t%d players\n\
				Max mode score\t%d points\n\
				Participants prize\t$%s ($%s if won)\n\
				Participants spawn\t%.2f near you\n\
				Participants equips\t%s, %s, %s\n\
				Participants ammo\t%d, %d, %d\n\
				Announce Event\n\
				Force End",

				dm_EventData[eventLimit],
				dm_EventData[eventMaxScore],
				FormatNumber(dm_EventData[eventPrice]),
				FormatNumber(dm_EventData[eventPrice]+10000),
				GetPlayerDistanceFromPoint(playerid, dm_EventData[eventPosX], dm_EventData[eventPosY], dm_EventData[eventPosZ]),
				ReturnWeaponName(dm_EventData[eventWeapons][0]), ReturnWeaponName(dm_EventData[eventWeapons][1]), ReturnWeaponName(dm_EventData[eventWeapons][2]),
				dm_EventData[eventAmmo][0], dm_EventData[eventAmmo][1], dm_EventData[eventAmmo][2]				
			);
			Dialog_Show(playerid, EventInfo, DIALOG_STYLE_TABLIST_HEADERS, sprintf("Event Info: %s Mode", ReturnEventMode(EventType)), str, "Select", "Close");
		}
		else if (EventType == 5) {

			format (str, sizeof(str),

				"Options\tValues\n\
				Max participants\t%d players\n\
				Participants prize\t$%s\n\
				Participants winner prize\t($%s 1st, $%s 2nd, $%s 3rd)\n\
				Flying departure\tAt %s\n\
				Flying arrival\t%.2f near you\n\
				Announce Event\n\
				Force End",

				parachute_EventData[eventLimit],
				FormatNumber(parachute_EventData[eventPrice]),
				FormatNumber(parachute_EventData[eventWinnerPrice]),
				FormatNumber(parachute_EventData[eventWinnerPrice]-2500),
				FormatNumber(parachute_EventData[eventWinnerPrice]-5000),
				arrFlyData[parachute_EventData[eventSelectPos]],
				GetPlayerDistanceFromPoint(playerid, parachute_EventData[eventLandingX], parachute_EventData[eventLandingY], parachute_EventData[eventLandingZ])
			);
			Dialog_Show(playerid, EventInfo, DIALOG_STYLE_TABLIST_HEADERS, sprintf("Event Info: %s Mode", ReturnEventMode(EventType)), str, "Select", "Close");
		}
		else if (EventType == 6) {

			format (str, sizeof(str),
			
				"Options\tValue\n\
				Max participants\t%d players\n\
				Max human participants\t%d players\n\
				Participants winner prize\t$%s ($%s if won)\n\
				Surviving time\t%d minutes\n\
				Human spawn position\t%.2f near you\n\
				Zombie spawn position\t%.2f near you\n\
				Participants equip (human only)\t%s, %s, %s\n\
				Participants ammo (human only)\t%d, %d, %d\n\
				Announce Event\n\
				Force End",

				zombie_EventData[eventLimit],
				zombie_EventData[eventAlive],
				FormatNumber(zombie_EventData[eventPrice]), FormatNumber(zombie_EventData[eventPrice]+10000),
				zombie_EventData[eventTimer],
				GetPlayerDistanceFromPoint(playerid, zombie_EventData[eventPosX][0], zombie_EventData[eventPosY][0], zombie_EventData[eventPosZ][0]),
				GetPlayerDistanceFromPoint(playerid, zombie_EventData[eventPosX][1], zombie_EventData[eventPosY][1], zombie_EventData[eventPosZ][1]),
				ReturnWeaponName(zombie_EventData[eventWeapons][0]), ReturnWeaponName(zombie_EventData[eventWeapons][1]), ReturnWeaponName(zombie_EventData[eventWeapons][2]),
				zombie_EventData[eventAmmo][0], zombie_EventData[eventAmmo][1], zombie_EventData[eventAmmo][2]
			);
			Dialog_Show(playerid, EventInfo, DIALOG_STYLE_TABLIST_HEADERS, sprintf("Event Info: %s Mode", ReturnEventMode(EventType)), str, "Select", "Close");
		}
		else SendErrorMessage(playerid, "Kamu tidak memilih event mode yang dituju, gunakan '/event mode'.");
	}
	else cmd_event(playerid, "join");

	return 1;
}

Dialog:EventMode(playerid, response, listitem, inputtext[])
{
	if(!response)
		return 1;

	switch (listitem) {
		case 1: SendErrorMessage(playerid, "Mode tidak tersedia saat ini!");
		default: {

			EventType = listitem + 1;
			format(EventHost, sizeof(EventHost), PlayerData[playerid][pUCP]);

			SendClientMessageEx(playerid, COLOR_SERVER, "EVENT: "WHITE"Kamu telah memilih mode "GREEN"'%s'", inputtext);
		}
	}
	return 1;
}

Dialog:EventInfo(playerid, response, listitem, inputtext[])
{
	if (!response)
		return 1;

	if (EventType == 1)
	{
		switch(listitem)
		{
			case 0:
			{
				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				Dialog_Show(playerid, Race_EventLimit, DIALOG_STYLE_INPUT, sprintf("Event Info: %s Mode", ReturnEventMode(EventType)), "Masukkan nilai batas partisipan untuk mode ini: (10-50)", "Confirm", "Back");
			}
			case 1:
			{
				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");
				
				Dialog_Show(playerid, Race_EventPrice, DIALOG_STYLE_INPUT, sprintf("Event Info: %s Mode", ReturnEventMode(EventType)), "Masukkan nilai hadiah partisipan untuk mode ini: ($0.50-$4.00)", "Confirm", "Back");
			}
			case 2:
			{
				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				Dialog_Show(playerid, Race_EventModel, DIALOG_STYLE_INPUT, sprintf("Event Info: %s Mode", ReturnEventMode(EventType)), "Masukkan nilai model kendaraan untuk mode ini: (400-611)", "Confirm", "Back");
			}
			case 3:
			{
				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				if (SelectedRaceMap == -1)
					return SendErrorMessage(playerid, "Pilih map sebelum menentukan spawn point pada mode ini!"), cmd_event(playerid, "info");

				if (!GetPlayerVirtualWorld(playerid))
					return SendErrorMessage(playerid, "Tidak dapat mengatur posisi spawn ketika virtual world mu adalah 0."), cmd_event(playerid, "info");

				if (!IsPlayerInRangeOfPoint(playerid, 50, race_CPInfo[SelectedRaceMap][0][cpRace][0], race_CPInfo[SelectedRaceMap][0][cpRace][1], race_CPInfo[SelectedRaceMap][0][cpRace][2]))
					return SendErrorMessage(playerid, "Kamu tidak dekat dengan posisi awal map pada mode ini!"), cmd_event(playerid, "info");

				if (IsPlayerInRangeOfPoint(playerid, 20, race_CPInfo[SelectedRaceMap][0][cpRace][0], race_CPInfo[SelectedRaceMap][0][cpRace][1], race_CPInfo[SelectedRaceMap][0][cpRace][2]))
					return SendErrorMessage(playerid, "Kamu terlalu dekat dengan posisi awal map pada mode ini!"), cmd_event(playerid, "info");

				GetPlayerPos(playerid, race_EventData[evPos][0], race_EventData[evPos][1], race_EventData[evPos][2]);
				GetPlayerFacingAngle(playerid, race_EventData[evPos][3]);

				race_EventData[evWorld] = GetPlayerVirtualWorld(playerid);

				cmd_event(playerid, "info");
				SendClientMessage(playerid, COLOR_SERVER, "EVENT: "WHITE"Event spawn has been moved to your position!");
			}
			case 4:
			{
				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				Dialog_Show(playerid, Race_EventTime, DIALOG_STYLE_INPUT, sprintf("Event Info: %s Mode", ReturnEventMode(EventType)), "Masukkan waktu event untuk mode ini: (5-20 [menit])", "Confirm", "Back");
			}
			case 5:
			{
				new str[1024];

				if (!Iter_Count(RacesMap)) {

					Dialog_Show(playerid, Race_CreateMap, DIALOG_STYLE_INPUT, "Create Race Map", "Fill a name on your map creation: (input below)", "Next", "Back");
				}
				else {

					if (EventStarted)
						return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");
					
					if (race_EventData[evModel] < 400)
						return SendErrorMessage(playerid, "Harap atur terlebih dahulu model kendaraan event ini!"), cmd_event(playerid, "info");				

					format (str, sizeof(str), "Map Name\tDistance\tLast used\tPublisher");

					foreach (new id : RacesMap) if (Iter_Contains(RacesMap, id)) {

						format (str, sizeof(str), "%s\n%s\t%.2f\t%s\t%s", str, race_CPData[id][cpName], race_CPData[id][cpDistance], race_CPData[id][cpLastUsed], race_CPData[id][cpPublisher]);
					}
					if (Iter_Count(RacesMap) < 20) {

						format (str, sizeof(str), "%s\n<< Upload Map >>\t-\t-\tN/A", str);
					}
					Dialog_Show(playerid, Race_LoadMap, DIALOG_STYLE_TABLIST_HEADERS, "Load Race Map", str, "Load", "Back");
				}
			}
			case 6: {

				if (SelectedRaceMap == -1)
					return SendErrorMessage(playerid, "Pilih map sebelum melakukan teleportasi!"), cmd_event(playerid, "info");

				static str[128];

				format (str, sizeof(str),
					
					"Options\tDistance\n\
					Teleport to start point\t%.2f\n\
					Teleport to finish point\t%.2f",
					GetPlayerDistanceFromPoint(playerid, race_CPInfo[SelectedRaceMap][0][cpRace][0], race_CPInfo[SelectedRaceMap][0][cpRace][1], race_CPInfo[SelectedRaceMap][0][cpRace][2]),
					GetPlayerDistanceFromPoint(playerid, race_CPInfo[SelectedRaceMap][19][cpRace][0], race_CPInfo[SelectedRaceMap][19][cpRace][1], race_CPInfo[SelectedRaceMap][19][cpRace][2])
				);
				Dialog_Show(playerid, Race_TeleOption, DIALOG_STYLE_TABLIST_HEADERS, "Event Map: Teleport Options", str, "Pilih", "Kembali");
			}
			case 7:
			{
				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				if (race_EventData[evPos][0] == 0.0 && race_EventData[evPos][1] == 0.0 && race_EventData[evPos][2] == 0.0)
					return SendErrorMessage(playerid, "Harap atur terlebih dahulu posisi spawn event sebelum mengumumkan event ini!"), cmd_event(playerid, "info");

				if (race_EventData[evModel] < 400)
					return SendErrorMessage(playerid, "Harap atur terlebih dahulu model kendaraan event ini!"), cmd_event(playerid, "info");

				if (race_EventData[evTime] < 2)
					return SendErrorMessage(playerid, "Harap atur terlebih dahulu waktu pada event ini!"), cmd_event(playerid, "info");

				if (EventCreated)
					return SendErrorMessage(playerid, "This event is already announced by "RED"%s", EventHost), cmd_event(playerid, "info");

				EventCreated = 1;

				SendClientMessageToAllEx(COLOR_SERVER, "EVENT: "RED"%s "WHITE"telah memulai event "YELLOW"%s Mode", PlayerData[playerid][pUCP], ReturnEventMode(EventType));
				SendClientMessageToAllEx(COLOR_SERVER, "EVENT: "WHITE"Gunakan '"YELLOW"/event join"WHITE"' untuk bergabung kedalam mode!");
			}
			case 8:
			{
				if (!EventStarted)
					return SendErrorMessage(playerid, "Tidak ada event yang sedang berlangsung!"), cmd_event(playerid, "info");				
			
				foreach (new i : Player) if (GetPVarInt(i, "IsAtEvent") == EventType)
				{
					TogglePlayerSpectating(i, 1);
					SetTimerEx("Event_RespawnPlayer", 4000, false, "d", i);

					evRaceCP[i] = -1;
					if (IsValidVehicle(evCar[i]))
						Vehicle_Delete(evCar[i], false);

					SetPlayerColor(i, COLOR_DEFAULT);
					SetCameraBehindPlayer(i);
					SetPlayerPositionEx(i, PlayerData[i][pPos][0], PlayerData[i][pPos][1], PlayerData[i][pPos][2]);
					SetPlayerHealth(i, PlayerData[i][pHealth]);
					SetPlayerArmour(i, PlayerData[i][pArmor]);
					SetPlayerVirtualWorld(i, PlayerData[i][pWorld]);
					SetPlayerInterior(i, PlayerData[i][pInterior]);
					SetPlayerSkin(i, PlayerData[i][pSkin]);

					if (PlayerData[i][pOnDuty]) {

						SetFactionColor(i);
						SetPlayerSkin(playerid, PlayerData[i][pFactionSkin]);
					}

					ResetPlayerMoney(i);
					GivePlayerMoney(i, GetMoney(i));
					ResetPlayerWeapons(i);
					SetWeapons(i);
					DisableRemoteVehicleCollisions(i, 0);
					DisablePlayerRaceCheckpoint(i);

					SendClientMessage(i, COLOR_SERVER, "EVENT: "YELLOW"An Admin has force-ended this event mode!");
					SetPVarInt(i, "IsAtEvent", -1);
				}
				Event_ForceEnd();			
			}
		}
	}
	else if (EventType == 2)
	{
		switch(listitem)
		{
			case 0:
			{
				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				Dialog_Show(playerid, Dearby_EventLimit, DIALOG_STYLE_INPUT, sprintf("Event Info: %s Mode", ReturnEventMode(EventType)), "Masukkan nilai batas partisipan untuk mode ini: (10-50)", "Confirm", "Back");
			}
			case 1:
			{
				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");
				
				Dialog_Show(playerid, Dearby_EventPrice, DIALOG_STYLE_INPUT, sprintf("Event Info: %s Mode", ReturnEventMode(EventType)), "Masukkan nilai hadiah partisipan untuk mode ini: ($0.50-$4.00)", "Confirm", "Back");
			}
			case 2:
			{
				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				Dialog_Show(playerid, Dearby_EventModel, DIALOG_STYLE_INPUT, sprintf("Event Info: %s Mode", ReturnEventMode(EventType)), "Masukkan nilai model kendaraan untuk mode ini: (400-611)", "Confirm", "Back");
			}
			case 3:
			{
				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				if (!GetPlayerVirtualWorld(playerid))
					return SendErrorMessage(playerid, "Tidak dapat mengatur posisi spawn ketika virtual world mu adalah 0."), cmd_event(playerid, "info");

				GetPlayerPos(playerid, dearby_EventData[evPos][0], dearby_EventData[evPos][1], dearby_EventData[evPos][2]);
				GetPlayerFacingAngle(playerid, dearby_EventData[evPos][3]);

				dearby_EventData[evWorld] = GetPlayerVirtualWorld(playerid);
				dearby_EventData[evInterior] = GetPlayerInterior(playerid);

				cmd_event(playerid, "info");
				SendClientMessage(playerid, COLOR_SERVER, "EVENT: "WHITE"Event spawn has been moved to your position!");
			}
			case 4:
			{
				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				Dialog_Show(playerid, Dearby_EventTime, DIALOG_STYLE_INPUT, sprintf("Event Info: %s Mode", ReturnEventMode(EventType)), "Masukkan waktu event untuk mode ini: (5-20 [menit])", "Confirm", "Back");
			}
			case 5:
			{
				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				if (dearby_EventData[evPos][0] == 0.0 && dearby_EventData[evPos][1] == 0.0 && dearby_EventData[evPos][2] == 0.0)
					return SendErrorMessage(playerid, "Harap atur terlebih dahulu posisi spawn event sebelum mengumumkan event ini!"), cmd_event(playerid, "info");

				if (dearby_EventData[evModel] < 400)
					return SendErrorMessage(playerid, "Harap atur terlebih dahulu model kendaraan event ini!"), cmd_event(playerid, "info");
			
				if (EventCreated)
					return SendErrorMessage(playerid, "This event is already announced by "RED"%s", EventHost), cmd_event(playerid, "info");

				EventCreated = 1;

				SendClientMessageToAllEx(COLOR_SERVER, "EVENT: "RED"%s "WHITE"telah memulai event "YELLOW"%s Mode", PlayerData[playerid][pUCP], ReturnEventMode(EventType));
				SendClientMessageToAllEx(COLOR_SERVER, "EVENT: "WHITE"Gunakan '"YELLOW"/event join"WHITE"' untuk bergabung kedalam mode!");
			}
			case 6:
			{
				if (!EventCreated)
					return SendErrorMessage(playerid, "Please announce the event first before start this mode!"), cmd_event(playerid, "info");

				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");
				
				if (dearby_EventData[evModel] < 400)
					return SendErrorMessage(playerid, "Harap atur terlebih dahulu model kendaraan event ini!"), cmd_event(playerid, "info");				
			
				foreach (new i : Player) if (GetPVarInt(i, "IsAtEvent") == EventType)
				{
					dearby_EventData[evCountdown][i] = 20;
					SendClientMessageEx(i, COLOR_SERVER, "EVENT: "YELLOW"Event akan dimulai dalam {33aa33}%d detik!", dearby_EventData[evCountdown][i]);
				}
			}
			case 7:
			{
				if (!EventStarted)
					return SendErrorMessage(playerid, "Tidak ada event yang sedang berlangsung!"), cmd_event(playerid, "info");				
			
				foreach (new i : Player) if (GetPVarInt(i, "IsAtEvent") == EventType)
				{
					SetPlayerColor(i, COLOR_DEFAULT);

					if (PlayerData[i][pOnDuty])
						SetFactionColor(i);

					if (IsValidVehicle(evCar[i]))
						Vehicle_Delete(evCar[i], false);

					SetPlayerPositionEx(i, PlayerData[i][pPos][0], PlayerData[i][pPos][1], PlayerData[i][pPos][2]);

					SetPlayerHealth(i, PlayerData[i][pHealth]);
					SetPlayerArmour(i, PlayerData[i][pArmor]);

					SetPlayerVirtualWorld(i, PlayerData[i][pWorld]);
					SetPlayerInterior(i, PlayerData[i][pInterior]);

					SetCameraBehindPlayer(i);
					DisableRemoteVehicleCollisions(i, 0);

					ResetPlayerMoney(i);
					GivePlayerMoney(i, PlayerData[i][pMoney]);

					ResetPlayerWeapons(i);
					DisablePlayerRaceCheckpoint(i);

					SendClientMessage(i, COLOR_SERVER, "EVENT: "YELLOW"An Admin has force-ended this event mode!");
					SetPVarInt(i, "IsAtEvent", -1);
				}
				Event_ForceEnd();
			}
		}
	}
	else if (EventType == 3) {

		switch (listitem) {

			case 0: {

				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				Dialog_Show(playerid, TDM_EventLimit, DIALOG_STYLE_INPUT, "Set mode limit", "Masukkan berapa jumlah maksimal slot untuk bisa memasuki mode ini:", "Limit", "Back");
			}
			case 1: {

				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				Dialog_Show(playerid, TDM_EventScore, DIALOG_STYLE_INPUT, "Set max score", "Masukkan berapa maksimal skor untuk menyelesaikan mode ini:", "Set", "Back");
			}
			case 2: {

				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				Dialog_Show(playerid, TDM_EventPrize, DIALOG_STYLE_INPUT, "Set mode prize", "Masukkan berapa nominal uang untuk hadiah para partisipan:", "Set", "Back");
			}
			case 3: {

				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				Dialog_Show(playerid, TDM_EventSkinA, DIALOG_STYLE_INPUT, "Set Skin A", "Masukkan nilai skin yang akan digunakan oleh Tim A: (1-311)", "Set", "Back");
			}
			case 4: {

				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				Dialog_Show(playerid, TDM_EventSkinB, DIALOG_STYLE_INPUT, "Set Skin B", "Masukkan nilai skin yang akan digunakan oleh Tim B: (1-311)", "Set", "Back");
			}
			case 5: {

				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				if (!GetPlayerVirtualWorld(playerid))
					return SendErrorMessage(playerid, "Unable to set spawn event while at default world!");

				GetPlayerPos(playerid, tdm_EventData[eventPosX][0], tdm_EventData[eventPosY][0], tdm_EventData[eventPosZ][0]);
				GetPlayerFacingAngle(playerid, tdm_EventData[eventPosA][0]);

				tdm_EventData[eventWorld] = GetPlayerVirtualWorld(playerid);
				tdm_EventData[eventInterior] = GetPlayerInterior(playerid);

				cmd_event(playerid, "info");
				SendClientMessage(playerid, COLOR_SERVER, "EVENT: "WHITE"Team A spawn point has moved!");
			}
			case 6: {

				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				if (!GetPlayerVirtualWorld(playerid))
					return SendErrorMessage(playerid, "Unable to set spawn event while at default world!");

				GetPlayerPos(playerid, tdm_EventData[eventPosX][1], tdm_EventData[eventPosY][1], tdm_EventData[eventPosZ][1]);
				GetPlayerFacingAngle(playerid, tdm_EventData[eventPosA][1]);

				tdm_EventData[eventWorld] = GetPlayerVirtualWorld(playerid);
				tdm_EventData[eventInterior] = GetPlayerInterior(playerid);

				cmd_event(playerid, "info");
				SendClientMessage(playerid, COLOR_SERVER, "EVENT: "WHITE"Team B spawn point has moved!");
			}
			case 7: {

				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				static str[512];
				format (str, sizeof(str), "Weapon Name");

				forex (id, sizeof(arrWeap))	{

					format (str, sizeof(str), "%s\n%s", str, arrWeap[id]);
				}
				Dialog_Show(playerid, TDM_EventEquip, DIALOG_STYLE_TABLIST_HEADERS, "Select a weapon 1", str, "Pick", "");
			}
			case 8: {

				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				static str[128];
				format (str, sizeof(str), "Ammo Amount");
				format (str, sizeof(str), "%s\n50", str);
				format (str, sizeof(str), "%s\n100", str);
				format (str, sizeof(str), "%s\n150", str);
				format (str, sizeof(str), "%s\n250", str);
				format (str, sizeof(str), "%s\n350", str);
				format (str, sizeof(str), "%s\n500", str);
				Dialog_Show(playerid, TDM_EventAmmo, DIALOG_STYLE_TABLIST_HEADERS, "Select ammo 1 amount", str, "Pick", "");				
			}
			case 9:
			{
				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				if (tdm_EventData[eventPosX][1] == 0.0 && tdm_EventData[eventPosY][1] == 0.0 && tdm_EventData[eventPosZ][1] == 0.0)
					return SendErrorMessage(playerid, "Harap atur terlebih dahulu posisi spawn event sebelum mengumumkan event ini!"), cmd_event(playerid, "info");

				if (tdm_EventData[eventSkin] < 1)
					return SendErrorMessage(playerid, "Harap atur terlebih dahulu skin partisipan mode ini!"), cmd_event(playerid, "info");

				if (tdm_EventData[eventWeapons][2] < 1)
					return SendErrorMessage(playerid, "Harap atur terlebih dahulu equipment partisipan mode ini!"), cmd_event(playerid, "info");

				if (EventCreated)
					return SendErrorMessage(playerid, "This event is already announced by "RED"%s", EventHost), cmd_event(playerid, "info");

				EventCreated = 1;

				SendClientMessageToAllEx(COLOR_SERVER, "EVENT: "RED"%s "WHITE"telah memulai event "YELLOW"%s Mode", PlayerData[playerid][pUCP], ReturnEventMode(EventType));
				SendClientMessageToAllEx(COLOR_SERVER, "EVENT: "WHITE"Gunakan '"YELLOW"/event join"WHITE"' untuk bergabung kedalam mode!");
			}
			case 10:
			{
				if (!EventStarted)
					return SendErrorMessage(playerid, "Tidak ada event yang sedang berlangsung!"), cmd_event(playerid, "info");				

				foreach (new i : Player) if (GetPVarInt(i, "IsAtEvent") == EventType)
				{
					TogglePlayerSpectating(i, 1);
					SetTimerEx("Event_RespawnPlayer", 4000, false, "d", i);

					evTeam[i] = 0;
					TDM_DisplayTD(i, false);
					TDM_ToggleAntiCheat(i, false);

					SetPlayerTeam(i,0);
					SetPlayerColor(i, COLOR_DEFAULT);
					SetCameraBehindPlayer(i);
					SetPlayerPositionEx(i, PlayerData[i][pPos][0], PlayerData[i][pPos][1], PlayerData[i][pPos][2]);
					SetPlayerHealth(i, PlayerData[i][pHealth]);
					SetPlayerArmour(i, PlayerData[i][pArmor]);
					SetPlayerVirtualWorld(i, PlayerData[i][pWorld]);
					SetPlayerInterior(i, PlayerData[i][pInterior]);
					SetPlayerSkin(i, PlayerData[i][pSkin]);

					if (PlayerData[i][pOnDuty]) {

						SetFactionColor(i);
						SetPlayerSkin(playerid, PlayerData[i][pFactionSkin]);
					}

					ResetPlayerMoney(i);
					GivePlayerMoney(i, PlayerData[i][pMoney]);
					ResetPlayerWeapons(i);
					SetWeapons(i);

					SendClientMessage(i, COLOR_SERVER, "EVENT: "YELLOW"An Admin has force-ended this event mode!");
					SetPVarInt(i, "IsAtEvent", -1);
				}
				Event_ForceEnd();			
			}
		}
	}
	else if (EventType == 4) {

		switch (listitem) {

			case 0: {

				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				Dialog_Show(playerid, DM_EventLimit, DIALOG_STYLE_INPUT, "Set mode limit", "Masukkan berapa jumlah maksimal slot untuk bisa memasuki mode ini:", "Limit", "Back");
			}
			case 1: {

				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				Dialog_Show(playerid, DM_EventScore, DIALOG_STYLE_INPUT, "Set max score", "Masukkan berapa maksimal skor untuk menyelesaikan mode ini:", "Set", "Back");
			}
			case 2: {

				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				Dialog_Show(playerid, DM_EventPrize, DIALOG_STYLE_INPUT, "Set mode prize", "Masukkan berapa nominal uang untuk hadiah para partisipan:", "Set", "Back");
			}
			case 3: {

				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				if (!GetPlayerVirtualWorld(playerid))
					return SendErrorMessage(playerid, "Unable to set spawn event while at default world!");

				GetPlayerPos(playerid, dm_EventData[eventPosX], dm_EventData[eventPosY], dm_EventData[eventPosZ]);
				GetPlayerFacingAngle(playerid, dm_EventData[eventPosA]);

				dm_EventData[eventWorld] = GetPlayerVirtualWorld(playerid);
				dm_EventData[eventInterior] = GetPlayerInterior(playerid);

				cmd_event(playerid, "info");
				SendClientMessage(playerid, COLOR_SERVER, "EVENT: "WHITE"Spawn point has moved!");
			}
			case 4: {

				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				static str[512];
				format (str, sizeof(str), "Weapon Name");

				forex (id, sizeof(arrWeap))	{

					format (str, sizeof(str), "%s\n%s", str, arrWeap[id]);
				}
				Dialog_Show(playerid, DM_EventEquip, DIALOG_STYLE_TABLIST_HEADERS, "Select a weapon 1", str, "Pick", "");
			}
			case 5: {

				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				static str[128];
				format (str, sizeof(str), "Ammo Amount");
				format (str, sizeof(str), "%s\n50", str);
				format (str, sizeof(str), "%s\n100", str);
				format (str, sizeof(str), "%s\n150", str);
				format (str, sizeof(str), "%s\n250", str);
				format (str, sizeof(str), "%s\n350", str);
				format (str, sizeof(str), "%s\n500", str);
				Dialog_Show(playerid, DM_EventAmmo, DIALOG_STYLE_TABLIST_HEADERS, "Select ammo 1 amount", str, "Pick", "");				
			}
			case 6:
			{
				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				if (dm_EventData[eventPosX] == 0.0 && dm_EventData[eventPosY] == 0.0 && dm_EventData[eventPosZ] == 0.0)
					return SendErrorMessage(playerid, "Harap atur terlebih dahulu posisi spawn event sebelum mengumumkan event ini!"), cmd_event(playerid, "info");

				if (dm_EventData[eventWeapons][2] < 1)
					return SendErrorMessage(playerid, "Harap atur terlebih dahulu equipment partisipan mode ini!"), cmd_event(playerid, "info");

				if (EventCreated)
					return SendErrorMessage(playerid, "This event is already announced by "RED"%s", EventHost), cmd_event(playerid, "info");

				EventCreated = 1;

				SendClientMessageToAllEx(COLOR_SERVER, "EVENT: "RED"%s "WHITE"telah memulai event "YELLOW"%s Mode", PlayerData[playerid][pUCP], ReturnEventMode(EventType));
				SendClientMessageToAllEx(COLOR_SERVER, "EVENT: "WHITE"Gunakan '"YELLOW"/event join"WHITE"' untuk bergabung kedalam mode!");
			}
			case 7:
			{
				if (!EventStarted)
					return SendErrorMessage(playerid, "Tidak ada event yang sedang berlangsung!"), cmd_event(playerid, "info");				
			
				foreach (new i : Player) if (GetPVarInt(i, "IsAtEvent") == EventType)
				{
					TogglePlayerSpectating(i, 1);
					SetTimerEx("Event_RespawnPlayer", 4000, false, "d", i);

					dm_EventData[eventExp][i] = 0;
					DM_ToggleAntiCheat(playerid,false);
					DM_DisplayTD(i, false);

					SetPlayerColor(i, COLOR_DEFAULT);
					SetCameraBehindPlayer(i);
					SetPlayerPositionEx(i, PlayerData[i][pPos][0], PlayerData[i][pPos][1], PlayerData[i][pPos][2]);
					SetPlayerHealth(i, PlayerData[i][pHealth]);
					SetPlayerArmour(i, PlayerData[i][pArmor]);
					SetPlayerVirtualWorld(i, PlayerData[i][pWorld]);
					SetPlayerInterior(i, PlayerData[i][pInterior]);
					SetPlayerSkin(i, PlayerData[i][pSkin]);

					if (PlayerData[i][pOnDuty]) {

						SetFactionColor(i);
						SetPlayerSkin(playerid, PlayerData[i][pFactionSkin]);
					}

					ResetPlayerMoney(i);
					GivePlayerMoney(i, GetMoney(i));
					ResetPlayerWeapons(i);
					SetWeapons(i);

					SendClientMessage(i, COLOR_SERVER, "EVENT: "YELLOW"An Admin has force-ended this event mode!");
					SetPVarInt(i, "IsAtEvent", -1);
				}
				Event_ForceEnd();			
			}
		}
	}
	else if (EventType == 5) {

		switch (listitem) {

			case 0: {

				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				Dialog_Show(playerid, Parachute_EventLimit, DIALOG_STYLE_INPUT, "Set mode limit", "Masukkan berapa jumlah maksimal slot untuk bisa memasuki mode ini:", "Limit", "Back");
			}
			case 1: {

				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				Dialog_Show(playerid, Parachute_EventPrize, DIALOG_STYLE_INPUT, "Set mode prize", "Masukkan berapa nominal uang untuk hadiah para partisipan:", "Set", "Back");
			}
			case 2: {

				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				Dialog_Show(playerid, Parachute_EvWinnerPrize, DIALOG_STYLE_INPUT, "Set winner prize", "Masukkan berapa nominal uang untuk hadiah para pemenang partisipan:", "Set", "Back");
			}
			case 3: {

				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				static str[168];
				format (str, sizeof(str), "Location Spawn");

				for (new id = 0; id < sizeof(arrFlyData); id ++) {

					format (str, sizeof(str), "%s\n%s", str, arrFlyData[id]);
				}
				Dialog_Show(playerid, Parachute_EventFlyFrom, DIALOG_STYLE_TABLIST_HEADERS, "Select fly departure", str, "Spawn!", "");				
			}
			case 4: {

				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				if (!GetPlayerVirtualWorld(playerid))
					return SendErrorMessage(playerid, "Unable to set spawn event while at default world!");

				GetPlayerPos(playerid, parachute_EventData[eventLandingX], parachute_EventData[eventLandingY], parachute_EventData[eventLandingZ]);

				parachute_EventData[eventWorld] = GetPlayerVirtualWorld(playerid);
				parachute_EventData[eventInterior] = GetPlayerInterior(playerid);

				cmd_event(playerid, "info");
				SendClientMessage(playerid, COLOR_SERVER, "EVENT: "WHITE"Finish point has moved!");
			}
			case 5:
			{
				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				if (parachute_EventData[eventLandingX] == 0.0 && parachute_EventData[eventLandingY] == 0.0 && parachute_EventData[eventLandingZ] == 0.0)
					return SendErrorMessage(playerid, "Harap atur terlebih dahulu posisi spawn event sebelum mengumumkan event ini!"), cmd_event(playerid, "info");

				if (parachute_EventData[eventSelectPos] < 1)
					return SendErrorMessage(playerid, "Harap atur terlebih dahulu posisi awal mode ini!"), cmd_event(playerid, "info");

				if (EventCreated)
					return SendErrorMessage(playerid, "This event is already announced by "RED"%s", EventHost), cmd_event(playerid, "info");

				EventCreated = 1;

				SendClientMessageToAllEx(COLOR_SERVER, "EVENT: "RED"%s "WHITE"telah memulai event "YELLOW"%s Mode", PlayerData[playerid][pUCP], ReturnEventMode(EventType));
				SendClientMessageToAllEx(COLOR_SERVER, "EVENT: "WHITE"Gunakan '"YELLOW"/event join"WHITE"' untuk bergabung kedalam mode!");
			}
			case 6:
			{
				if (!EventStarted)
					return SendErrorMessage(playerid, "Tidak ada event yang sedang berlangsung!"), cmd_event(playerid, "info");				
			
				foreach (new i : Player) if (GetPVarInt(i, "IsAtEvent") == EventType)
				{
					TogglePlayerSpectating(i, 1);
					SetTimerEx("Event_RespawnPlayer", 4000, false, "d", i);

					Parachute_ToggleAntiCheat(playerid, false);

					SetPlayerColor(i, COLOR_DEFAULT);
					SetCameraBehindPlayer(i);
					SetPlayerPositionEx(i, PlayerData[i][pPos][0], PlayerData[i][pPos][1], PlayerData[i][pPos][2]);
					SetPlayerHealth(i, PlayerData[i][pHealth]);
					SetPlayerArmour(i, PlayerData[i][pArmor]);
					SetPlayerVirtualWorld(i, PlayerData[i][pWorld]);
					SetPlayerInterior(i, PlayerData[i][pInterior]);
					SetPlayerSkin(i, PlayerData[i][pSkin]);

					if (PlayerData[i][pOnDuty]) {

						SetFactionColor(i);
						SetPlayerSkin(playerid, PlayerData[i][pFactionSkin]);
					}

					ResetPlayerMoney(i);
					GivePlayerMoney(i, GetMoney(i));
					ResetPlayerWeapons(i);
					DisablePlayerRaceCheckpoint(i);
					SetWeapons(i);

					SendClientMessage(i, COLOR_SERVER, "EVENT: "YELLOW"An Admin has force-ended this event mode!");
					SetPVarInt(i, "IsAtEvent", -1);
				}
				Event_ForceEnd();			
			}
		}
	}
	else if (EventType == 6) {

		switch (listitem) {

			case 0: {

				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				Dialog_Show(playerid, Zombie_EventLimit, DIALOG_STYLE_INPUT, "Set mode limit", "Masukkan berapa jumlah maksimal slot untuk bisa memasuki mode ini:", "Limit", "Back");				
			}
			case 1: {

				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				Dialog_Show(playerid, Zombie_EventAlive, DIALOG_STYLE_INPUT, "Set mode limit", "Masukkan berapa jumlah maksimal human slot untuk bisa memasuki mode ini:", "Limit", "Back");
			}
			case 2: {

				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				Dialog_Show(playerid, Zombie_EventPrize, DIALOG_STYLE_INPUT, "Set mode prize", "Masukkan berapa jumlah nominal hadiah untuk tim pemenang:", "Set", "Back");
			}
			case 3: {

				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				Dialog_Show(playerid, Zombie_EventTimer, DIALOG_STYLE_INPUT, "Set mode timer", "Masukkan berapa lama waktu mode ini akan berlangsung:", "Set", "Back");
			}
			case 4: {

				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				if (!GetPlayerVirtualWorld(playerid))
					return SendErrorMessage(playerid, "Unable to set spawn event while at default world!");

				GetPlayerPos(playerid, zombie_EventData[eventPosX][0], zombie_EventData[eventPosY][0], zombie_EventData[eventPosZ][0]);
				GetPlayerFacingAngle(playerid, zombie_EventData[eventPosA][0]);

				zombie_EventData[eventWorld] = GetPlayerVirtualWorld(playerid);
				zombie_EventData[eventInterior] = GetPlayerInterior(playerid);

				cmd_event(playerid, "info");
				SendClientMessage(playerid, COLOR_SERVER, "EVENT: "WHITE"Defender spawn point has moved!");
			}
			case 5: {

				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				if (!GetPlayerVirtualWorld(playerid))
					return SendErrorMessage(playerid, "Unable to set spawn event while at default world!");

				GetPlayerPos(playerid, zombie_EventData[eventPosX][1], zombie_EventData[eventPosY][1], zombie_EventData[eventPosZ][1]);
				GetPlayerFacingAngle(playerid, zombie_EventData[eventPosA][1]);

				zombie_EventData[eventWorld] = GetPlayerVirtualWorld(playerid);
				zombie_EventData[eventInterior] = GetPlayerInterior(playerid);

				cmd_event(playerid, "info");
				SendClientMessage(playerid, COLOR_SERVER, "EVENT: "WHITE"Attacker spawn point has moved!");
			}
			case 6: {

				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				static str[512];
				format (str, sizeof(str), "Weapon Name");

				forex (id, sizeof(arrWeap))	{

					format (str, sizeof(str), "%s\n%s", str, arrWeap[id]);
				}
				Dialog_Show(playerid, Zombie_EventEquip, DIALOG_STYLE_TABLIST_HEADERS, "Select a weapon 1", str, "Pick", "");
			}
			case 7: {

				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				static str[128];
				format (str, sizeof(str), "Ammo Amount");
				format (str, sizeof(str), "%s\n50", str);
				format (str, sizeof(str), "%s\n100", str);
				format (str, sizeof(str), "%s\n150", str);
				format (str, sizeof(str), "%s\n250", str);
				format (str, sizeof(str), "%s\n350", str);
				format (str, sizeof(str), "%s\n500", str);
				Dialog_Show(playerid, Zombie_EventAmmo, DIALOG_STYLE_TABLIST_HEADERS, "Select ammo 1 amount", str, "Pick", "");				
			}
			case 8:
			{
				if (EventStarted)
					return SendErrorMessage(playerid, "Tidak dapat mengubah informasi ketika event sedang berlangsung!"), cmd_event(playerid, "info");

				if (zombie_EventData[eventPosX][1] == 0.0 && zombie_EventData[eventPosY][1] == 0.0 && zombie_EventData[eventPosZ][1] == 0.0)
					return SendErrorMessage(playerid, "Harap atur terlebih dahulu posisi spawn event sebelum mengumumkan event ini!"), cmd_event(playerid, "info");

				if (zombie_EventData[eventAlive] < 1 || zombie_EventData[eventTimer] < 1)
					return SendErrorMessage(playerid, "Harap atur terlebih dahulu skin atau waktu partisipan mode ini!"), cmd_event(playerid, "info");

				if (zombie_EventData[eventWeapons][2] < 1)
					return SendErrorMessage(playerid, "Harap atur terlebih dahulu equipment partisipan mode ini!"), cmd_event(playerid, "info");

				if (EventCreated)
					return SendErrorMessage(playerid, "This event is already announced by "RED"%s", EventHost), cmd_event(playerid, "info");

				EventCreated = 1;

				SendClientMessageToAllEx(COLOR_SERVER, "EVENT: "RED"%s "WHITE"telah memulai event "YELLOW"%s Mode", PlayerData[playerid][pUCP], ReturnEventMode(EventType));
				SendClientMessageToAllEx(COLOR_SERVER, "EVENT: "WHITE"Gunakan '"YELLOW"/event join"WHITE"' untuk bergabung kedalam mode!");
			}
			case 9:
			{
				if (!EventStarted)
					return SendErrorMessage(playerid, "Tidak ada event yang sedang berlangsung!"), cmd_event(playerid, "info");				
			
				foreach (new i : Player) if (GetPVarInt(i, "IsAtEvent") == EventType)
				{
					TogglePlayerSpectating(i, 1);
					SetTimerEx("Event_RespawnPlayer", 4000, false, "d", i);

					evTeam[i] = 0;
					Zombie_DisplayTD(i, false);
					Zombie_ToggleAntiCheat(i, false);

					SetPlayerTeam(i,0);
					SetPlayerColor(i, COLOR_DEFAULT);
					SetCameraBehindPlayer(i);
					SetPlayerPositionEx(i, PlayerData[i][pPos][0], PlayerData[i][pPos][1], PlayerData[i][pPos][2]);
					SetPlayerHealth(i, PlayerData[i][pHealth]);
					SetPlayerArmour(i, PlayerData[i][pArmor]);
					SetPlayerVirtualWorld(i, PlayerData[i][pWorld]);
					SetPlayerInterior(i, PlayerData[i][pInterior]);
					SetPlayerSkin(i, PlayerData[i][pSkin]);

					if (PlayerData[i][pOnDuty]) {

						SetFactionColor(i);
						SetPlayerSkin(playerid, PlayerData[i][pFactionSkin]);
					}

					ResetPlayerMoney(i);
					GivePlayerMoney(i, GetMoney(i));
					ResetPlayerWeapons(i);
					SetWeapons(i);

					SendClientMessage(i, COLOR_SERVER, "EVENT: "YELLOW"An Admin has force-ended this event mode!");
					SetPVarInt(i, "IsAtEvent", -1);
				}
				Event_ForceEnd();			
			}
		}
	}
	return 1;
}

ReturnEventMode(type)
{
	new str[16];

	switch(type)
	{
		case 1: str = "Race";
		case 2: str = "Dearby";
		case 3: str = "Team Deathmatch";
		case 4: str = "Deathmatch";
		case 5: str = "Parachute";
		case 6: str = "Zombie Survival";
	}
	return str;
}

SendEventMessage(eventid, color, const str[], {Float,_}:...)
{
    static
        args,
        start,
        end,
        string[144]
    ;
    #emit LOAD.S.pri 8
    #emit STOR.pri args

    if(args > 12)
    {
        #emit ADDR.pri str
        #emit STOR.pri start

        for (end = start + (args - 12); end > start; end -= 4)
        {
            #emit LREF.pri end
            #emit PUSH.pri
        }
        #emit PUSH.S str
        #emit PUSH.C 144
        #emit PUSH.C string
        #emit PUSH.C args

        #emit SYSREQ.C format
        #emit LCTRL 5
        #emit SCTRL 4

        foreach (new i : Player) if(GetPVarInt(i, "IsAtEvent") == eventid && EventType == eventid /*&& !pData[i][pDisableFaction]*/) {
                SendClientMessage(i, color, string);
        }
        return 1;
    }
    foreach (new i : Player) if(GetPVarInt(i, "IsAtEvent") == eventid && EventType == eventid /*&& !pData[i][pDisableFaction]*/) {
        SendClientMessage(i, color, str);
    }
    return 1;
}

Event_ForceEnd(all = 1)
{
	if (all) {

		switch(EventType)
		{
			case 1:
			{
				race_EventData[evPos][0] = 0.0;
				race_EventData[evPos][1] = 0.0;
				race_EventData[evPos][2] = 0.0;
				race_EventData[evPos][3] = 0.0;

				race_EventData[evEntry] = 0;
				race_EventData[evLimit] = 0;

				race_EventData[evModel] = 0;
				race_EventData[evTime] = 0;

				race_EventData[evPrice] = 0;
				race_EventData[evWorld] = 0;

				race_EventData[evWinner] = 0;
			}
			case 2: {

				dearby_EventData[evPos][0] = 0.0;
				dearby_EventData[evPos][1] = 0.0;
				dearby_EventData[evPos][2] = 0.0;
				dearby_EventData[evPos][3] = 0.0;

				dearby_EventData[evEntry] = 0;
				dearby_EventData[evLimit] = 0;

				dearby_EventData[evModel] = 0;
				dearby_EventData[evTime] = 0;

				dearby_EventData[evPrice] = 0;
				dearby_EventData[evWorld] = 0;

				dearby_EventData[evInterior] = 0;

				if (IsValidDynamicArea(dearby_EventData[evArea]))
					DestroyDynamicArea(dearby_EventData[evArea]);
			}
			case 3: {

				tdm_EventData[eventPosX][0] = 0.0;
				tdm_EventData[eventPosY][0] = 0.0;
				tdm_EventData[eventPosZ][0] = 0.0;
				tdm_EventData[eventPosA][0] = 0.0;

				tdm_EventData[eventPosX][1] = 0.0;
				tdm_EventData[eventPosY][1] = 0.0;
				tdm_EventData[eventPosZ][1] = 0.0;
				tdm_EventData[eventPosA][1] = 0.0;

				tdm_EventData[eventEntry] = 0;
				tdm_EventData[eventLimit] = 0;

				tdm_EventData[eventPrice] = 0;
				tdm_EventData[eventMaxScore] = 0;

				tdm_EventData[eventSkin][0] = 0;
				tdm_EventData[eventSkin][1] = 0;

				tdm_EventData[eventSelection] = 0;
				tdm_EventData[eventWinner] = 0;

				tdm_EventData[eventWorld] = 0;
				tdm_EventData[eventInterior] = 0;

				tdm_EventData[eventWeapons][0] = 0;
				tdm_EventData[eventWeapons][1] = 0;
				tdm_EventData[eventWeapons][2] = 0;

				tdm_EventData[eventAmmo][0] = 0;
				tdm_EventData[eventAmmo][1] = 0;
				tdm_EventData[eventAmmo][2] = 0;
			
				if (IsValidDynamicArea(tdm_EventData[eventArea]))
					DestroyDynamicArea(tdm_EventData[eventArea]);
			}
			case 4: {

				dm_EventData[eventPosX] = 0.0;
				dm_EventData[eventPosY] = 0.0;
				dm_EventData[eventPosZ] = 0.0;
				dm_EventData[eventPosA] = 0.0;

				dm_EventData[eventEntry] = 0;
				dm_EventData[eventLimit] = 0;

				dm_EventData[eventPrice] = 0;
				dm_EventData[eventMaxScore] = 0;

				dm_EventData[eventWinner] = 0;

				dm_EventData[eventWorld] = 0;
				dm_EventData[eventInterior] = 0;

				dm_EventData[eventWeapons][0] = 0;
				dm_EventData[eventWeapons][1] = 0;
				dm_EventData[eventWeapons][2] = 0;

				dm_EventData[eventAmmo][0] = 0;
				dm_EventData[eventAmmo][1] = 0;
				dm_EventData[eventAmmo][2] = 0;
			
				if (IsValidDynamicArea(dm_EventData[eventArea]))
					DestroyDynamicArea(dm_EventData[eventArea]);
			}
			case 5: {

				parachute_EventData[eventLandingX] = 0.0;
				parachute_EventData[eventLandingY] = 0.0;
				parachute_EventData[eventLandingZ] = 0.0;

				parachute_EventData[eventEntry] = 0;
				parachute_EventData[eventLimit] = 0;

				parachute_EventData[eventPrice] = 0;
				parachute_EventData[eventWorld] = 0;

				parachute_EventData[eventInterior] = 0;
				parachute_EventData[eventWinner] = 0;

				parachute_EventData[eventWinnerPrice] = 0;
				parachute_EventData[eventSelectPos] = 0;
			}
			case 6: {

				zombie_EventData[eventEntry] = 0;
				zombie_EventData[eventLimit] = 0;

				zombie_EventData[eventPrice] = 0;
				zombie_EventData[eventAlive] = 0;

				zombie_EventData[eventTimer] = 0;
				zombie_EventData[eventWorld] = 0;

				zombie_EventData[eventInterior] = 0;
				zombie_EventData[eventWinner] = 0;

				forex (id, 3) {

					if (id < 2) {

						zombie_EventData[eventPosX][id] = 0.0;
						zombie_EventData[eventPosY][id] = 0.0;
						zombie_EventData[eventPosZ][id] = 0.0;
						zombie_EventData[eventPosA][id] = 0.0;
					}
					zombie_EventData[eventWeapons][id] = 0;
					zombie_EventData[eventAmmo][id] = 0;
				}
			}
		}
	}
	tdm_EventData[eventTeamScore][0] = 0;
	tdm_EventData[eventTeamScore][1] = 0;

	EventCreated = 0;
	EventStarted = 0;

    HighestEXP = 0;
    PlayerHighestEXP = 0;

	EventType = 0;
	format(EventHost, sizeof(EventHost), "null");

	return 1;
}

function Event_RespawnPlayer(playerid) {

	TogglePlayerSpectating(playerid, 0);
	return 1;
}

function Dearby_EventCollisions(playerid)
{
	SetVehicleVirtualWorld(evCar[playerid], dearby_EventData[evWorld]);
	SetPlayerVirtualWorld(playerid, dearby_EventData[evWorld]);

	DisableRemoteVehicleCollisions(playerid, 0);

	return 1;
}

Dialog:Dearby_EventLimit(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		new input = strval(inputtext);

		if (!IsNumeric(inputtext))
			return SendErrorMessage(playerid, "Hanya karakter angka yang diperbolehkan!"), dialog_EventInfo(playerid, 1, 0, "\1");
	
		if ((input < 10 || input > 50) && PlayerData[playerid][pAdmin] < 7)
			return SendErrorMessage(playerid, "Tidak dapat mengubah nilai. (10-50)"), dialog_EventInfo(playerid, 1, 0, "\1");

		dearby_EventData[evLimit] = input;
		cmd_event(playerid, "info");
	}
	else cmd_event(playerid, "info");

	return 1;
}

Dialog:Dearby_EventPrice(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		new
			dollar, 
			cent, 
			totalamount[32];

		if (strfind(inputtext, ".", true) != -1)
		{
			sscanf(inputtext, "p<.>dd", dollar, cent);
			format(totalamount, sizeof(totalamount), "%d%02d", dollar, cent);

			if ((strval(totalamount) < 0 || strval(totalamount) > 50000) && PlayerData[playerid][pAdmin] < 7)
				return SendErrorMessage(playerid, "Tidak dapat mengubah nilai. ($0.00-$500.00)"), dialog_EventInfo(playerid, 1, 1, "\1");

			dearby_EventData[evPrice] = strval(totalamount);
			cmd_event(playerid, "info");
		}
		else
		{
			sscanf(inputtext, "d", dollar);
			format(totalamount, sizeof(totalamount), "%d00", dollar);

			if ((strval(totalamount) < 0 || strval(totalamount) > 50000) && PlayerData[playerid][pAdmin] < 7)
				return SendErrorMessage(playerid, "Tidak dapat mengubah nilai. ($0.00-$500.00)"), dialog_EventInfo(playerid, 1, 1, "\1");

			dearby_EventData[evPrice] = strval(totalamount);
			cmd_event(playerid, "info");
		}	
	}
	else cmd_event(playerid, "info");

	return 1;
}

Dialog:Dearby_EventModel(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		new input = strval(inputtext);

		if (!IsNumeric(inputtext))
			return SendErrorMessage(playerid, "Hanya karakter angka yang diperbolehkan!"), dialog_EventInfo(playerid, 1, 2, "\1");
	
		if ((input < 400 || input > 611))
			return SendErrorMessage(playerid, "Tidak dapat mengubah nilai. (400-611)"), dialog_EventInfo(playerid, 1, 2, "\1");

		dearby_EventData[evModel] = input;
		cmd_event(playerid, "info");
	}
	else cmd_event(playerid, "info");

	return 1;
}

Dialog:Dearby_EventTime(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		new input = strval(inputtext);

		if (!IsNumeric(inputtext))
			return SendErrorMessage(playerid, "Hanya karakter angka yang diperbolehkan!"), dialog_EventInfo(playerid, 1, 4, "\1");
	
		if ((input < 5 || input > 20) && PlayerData[playerid][pAdmin] < 7)
			return SendErrorMessage(playerid, "Tidak dapat mengubah nilai. (5-20 [menit])"), dialog_EventInfo(playerid, 1, 4, "\1");

		dearby_EventData[evTime] = (input * 60);
		cmd_event(playerid, "info");
	}
	else cmd_event(playerid, "info");

	return 1;
}

task Dearby_EventTimer[1000]() 
{
	if ((dearby_EventData[evTime] > 0) && (EventType == 2) && EventStarted)
	{
		dearby_EventData[evTime] --;

		if (dearby_EventData[evTime] == 60)
			SendEventMessage(2, COLOR_SERVER, "EVENT: "WHITE"Event akan berakhir dalam {33aa33}%d detik!", dearby_EventData[evTime]);

		else if (dearby_EventData[evTime] <= 30 && dearby_EventData[evTime] > 0)
		{
			if (dearby_EventData[evTime] == 30)
				SendEventMessage(2, COLOR_SERVER, "EVENT: "WHITE"Tidak ada pemenang sejauh ini, event akan berakhir dalam {33aa33}%d detik!", dearby_EventData[evTime]);

			foreach (new i : Player)  if (GetPVarInt(i, "IsAtEvent") == EventType)
			{
				GameTextForPlayer(i, sprintf("~w~Event berakhir dalam~n~%d detik", dearby_EventData[evTime]), 1000, 6);
				PlayerPlaySound(i, 1056, 0, 0, 0);
			}
		}
		else if (!dearby_EventData[evTime])
		{
			foreach (new i : Player) if (GetPVarInt(i, "IsAtEvent") == EventType)
			{
				SetPlayerColor(i, COLOR_DEFAULT);
				GameTextForPlayer(i, " ", 0, 6);

				if (PlayerData[i][pOnDuty])
					SetFactionColor(i);

				if (IsValidVehicle(evCar[i]))
					Vehicle_Delete(evCar[i], false);

				SetPlayerPositionEx(i, PlayerData[i][pPos][0], PlayerData[i][pPos][1], PlayerData[i][pPos][2]);

				SetPlayerHealth(i, PlayerData[i][pHealth]);
				SetPlayerArmour(i, PlayerData[i][pArmor]);

				SetPlayerVirtualWorld(i, PlayerData[i][pWorld]);
				SetPlayerInterior(i, PlayerData[i][pInterior]);

				SetCameraBehindPlayer(i);
				DisableRemoteVehicleCollisions(i, 0);

				ResetPlayerMoney(i);
				GivePlayerMoney(i, PlayerData[i][pMoney]);

				GiveMoney(i, dearby_EventData[evPrice]);
				SetWeapons(i);

				SendClientMessageEx(i, COLOR_SERVER, "EVENT: "YELLOW"Tidak ada pemenang, kamu mendapatkan {33aa33}$%s "YELLOW"karena sudah mengikuti mode ini.", FormatNumber(dearby_EventData[evPrice]));
				SetPVarInt(i, "IsAtEvent", -1);
			}
			Event_ForceEnd();
		}
	}
}

ptask Dearby_EventCountdown[1000](playerid) 
{
	if (GetPVarInt(playerid, "IsAtEvent") > 0 && (EventType == 2))
	{
		if (dearby_EventData[evCountdown][playerid] > 0)
		{
			dearby_EventData[evCountdown][playerid] --;

			GameTextForPlayer(playerid, sprintf("~w~event dimulai dalam~n~%d detik", dearby_EventData[evCountdown][playerid]), 1000, 6);
			PlayerPlaySound(playerid, 1056, 0, 0, 0);

			if (!dearby_EventData[evCountdown][playerid])
			{
				EventStarted = 1;
				dearby_EventData[evArea] = CreateDynamicSphere(dearby_EventData[evPos][0], dearby_EventData[evPos][1], dearby_EventData[evPos][2], 300, dearby_EventData[evWorld], dearby_EventData[evInterior], playerid);

				SendClientMessage(playerid, COLOR_SERVER, "EVENT: "YELLOW"Event dimulai!");
				DisableRemoteVehicleCollisions(playerid, 1);

				GameTextForPlayer(playerid, " ", 0, 6);
				TogglePlayerControllable(playerid, 1);

				SetTimerEx("Dearby_EventCollisions", 1000, false, "d", playerid);
			}
		}
		else
		{
			new Float:health;
			GetVehicleHealth(evCar[playerid], health);

			if (health < 400.0)
			{
				dearby_EventData[evEntry] --;

				SetPlayerColor(playerid, COLOR_DEFAULT);
				GameTextForPlayer(playerid, " ", 0, 6);

				if (PlayerData[playerid][pOnDuty])
					SetFactionColor(playerid);

				if (IsValidVehicle(evCar[playerid]))
					Vehicle_Delete(evCar[playerid], false);

				SetPlayerPositionEx(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);

				SetPlayerHealth(playerid, PlayerData[playerid][pHealth]);
				SetPlayerArmour(playerid, PlayerData[playerid][pArmor]);

				SetPlayerVirtualWorld(playerid, PlayerData[playerid][pWorld]);
				SetPlayerInterior(playerid, PlayerData[playerid][pInterior]);

				ResetPlayerMoney(playerid);
				GivePlayerMoney(playerid, PlayerData[playerid][pMoney]);

				GiveMoney(playerid, dearby_EventData[evPrice]);
				SetWeapons(playerid);

				SendEventMessage(EventType, COLOR_SERVER, "EVENT: "RED"%s "YELLOW"has been eliminated. (Blow up engine)", GetName(playerid));
				SendClientMessageEx(playerid, COLOR_SERVER, "EVENT: "YELLOW"Kamu tereliminasi (blow up engine), kamu mendapatkan {33aa33}$%s "YELLOW"karena sudah berpartisipasi dalam event ini.", FormatNumber(dearby_EventData[evPrice]));

				SetCameraBehindPlayer(playerid);
				SetPVarInt(playerid, "IsAtEvent", -1);
			}
		}
	}
}

hook OnPlayerConnect(playerid) {

	DM_TD[playerid][0] = CreatePlayerTextDraw(playerid, 551.000000, 119.000000, "_");
	PlayerTextDrawFont(playerid, DM_TD[playerid][0], 1);
	PlayerTextDrawLetterSize(playerid, DM_TD[playerid][0], 0.600000, 7.699993);
	PlayerTextDrawTextSize(playerid, DM_TD[playerid][0], 338.500000, 136.500000);
	PlayerTextDrawSetOutline(playerid, DM_TD[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, DM_TD[playerid][0], 0);
	PlayerTextDrawAlignment(playerid, DM_TD[playerid][0], 2);
	PlayerTextDrawColor(playerid, DM_TD[playerid][0], -1);
	PlayerTextDrawBackgroundColor(playerid, DM_TD[playerid][0], 255);
	PlayerTextDrawBoxColor(playerid, DM_TD[playerid][0], -16777081);
	PlayerTextDrawUseBox(playerid, DM_TD[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, DM_TD[playerid][0], 1);
	PlayerTextDrawSetSelectable(playerid, DM_TD[playerid][0], 0);

	DM_TD[playerid][1] = CreatePlayerTextDraw(playerid, 509.000000, 123.000000, "placement");
	PlayerTextDrawFont(playerid, DM_TD[playerid][1], 3);
	PlayerTextDrawLetterSize(playerid, DM_TD[playerid][1], 0.479166, 1.600000);
	PlayerTextDrawTextSize(playerid, DM_TD[playerid][1], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, DM_TD[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, DM_TD[playerid][1], 0);
	PlayerTextDrawAlignment(playerid, DM_TD[playerid][1], 1);
	PlayerTextDrawColor(playerid, DM_TD[playerid][1], -1);
	PlayerTextDrawBackgroundColor(playerid, DM_TD[playerid][1], 255);
	PlayerTextDrawBoxColor(playerid, DM_TD[playerid][1], 50);
	PlayerTextDrawUseBox(playerid, DM_TD[playerid][1], 0);
	PlayerTextDrawSetProportional(playerid, DM_TD[playerid][1], 1);
	PlayerTextDrawSetSelectable(playerid, DM_TD[playerid][1], 0);

	DM_TD[playerid][2] = CreatePlayerTextDraw(playerid, 491.000000, 144.000000, "carl_johnson");
	PlayerTextDrawFont(playerid, DM_TD[playerid][2], 3);
	PlayerTextDrawLetterSize(playerid, DM_TD[playerid][2], 0.329166, 1.500000);
	PlayerTextDrawTextSize(playerid, DM_TD[playerid][2], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, DM_TD[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, DM_TD[playerid][2], 0);
	PlayerTextDrawAlignment(playerid, DM_TD[playerid][2], 1);
	PlayerTextDrawColor(playerid, DM_TD[playerid][2], -65281);
	PlayerTextDrawBackgroundColor(playerid, DM_TD[playerid][2], 255);
	PlayerTextDrawBoxColor(playerid, DM_TD[playerid][2], 50);
	PlayerTextDrawUseBox(playerid, DM_TD[playerid][2], 0);
	PlayerTextDrawSetProportional(playerid, DM_TD[playerid][2], 1);
	PlayerTextDrawSetSelectable(playerid, DM_TD[playerid][2], 0);

	DM_TD[playerid][3] = CreatePlayerTextDraw(playerid, 597.000000, 144.000000, "99");
	PlayerTextDrawFont(playerid, DM_TD[playerid][3], 3);
	PlayerTextDrawLetterSize(playerid, DM_TD[playerid][3], 0.329166, 1.500000);
	PlayerTextDrawTextSize(playerid, DM_TD[playerid][3], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, DM_TD[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, DM_TD[playerid][3], 0);
	PlayerTextDrawAlignment(playerid, DM_TD[playerid][3], 1);
	PlayerTextDrawColor(playerid, DM_TD[playerid][3], -16776961);
	PlayerTextDrawBackgroundColor(playerid, DM_TD[playerid][3], 255);
	PlayerTextDrawBoxColor(playerid, DM_TD[playerid][3], 50);
	PlayerTextDrawUseBox(playerid, DM_TD[playerid][3], 0);
	PlayerTextDrawSetProportional(playerid, DM_TD[playerid][3], 1);
	PlayerTextDrawSetSelectable(playerid, DM_TD[playerid][3], 0);

	DM_TD[playerid][4] = CreatePlayerTextDraw(playerid, 510.000000, 163.000000, "Target:");
	PlayerTextDrawFont(playerid, DM_TD[playerid][4], 3);
	PlayerTextDrawLetterSize(playerid, DM_TD[playerid][4], 0.391666, 1.650000);
	PlayerTextDrawTextSize(playerid, DM_TD[playerid][4], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, DM_TD[playerid][4], 1);
	PlayerTextDrawSetShadow(playerid, DM_TD[playerid][4], 0);
	PlayerTextDrawAlignment(playerid, DM_TD[playerid][4], 1);
	PlayerTextDrawColor(playerid, DM_TD[playerid][4], -1061109505);
	PlayerTextDrawBackgroundColor(playerid, DM_TD[playerid][4], 255);
	PlayerTextDrawBoxColor(playerid, DM_TD[playerid][4], 50);
	PlayerTextDrawUseBox(playerid, DM_TD[playerid][4], 0);
	PlayerTextDrawSetProportional(playerid, DM_TD[playerid][4], 1);
	PlayerTextDrawSetSelectable(playerid, DM_TD[playerid][4], 0);

	DM_TD[playerid][5] = CreatePlayerTextDraw(playerid, 596.000000, 163.000000, "99");
	PlayerTextDrawFont(playerid, DM_TD[playerid][5], 3);
	PlayerTextDrawLetterSize(playerid, DM_TD[playerid][5], 0.391666, 1.650000);
	PlayerTextDrawTextSize(playerid, DM_TD[playerid][5], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, DM_TD[playerid][5], 1);
	PlayerTextDrawSetShadow(playerid, DM_TD[playerid][5], 0);
	PlayerTextDrawAlignment(playerid, DM_TD[playerid][5], 1);
	PlayerTextDrawColor(playerid, DM_TD[playerid][5], -1);
	PlayerTextDrawBackgroundColor(playerid, DM_TD[playerid][5], 255);
	PlayerTextDrawBoxColor(playerid, DM_TD[playerid][5], 50);
	PlayerTextDrawUseBox(playerid, DM_TD[playerid][5], 0);
	PlayerTextDrawSetProportional(playerid, DM_TD[playerid][5], 1);
	PlayerTextDrawSetSelectable(playerid, DM_TD[playerid][5], 0);


	TDM_TD[playerid][0] = CreatePlayerTextDraw(playerid, 559.000000, 132.000000, "_");
	PlayerTextDrawFont(playerid, TDM_TD[playerid][0], 1);
	PlayerTextDrawLetterSize(playerid, TDM_TD[playerid][0], 0.600000, 10.600004);
	PlayerTextDrawTextSize(playerid, TDM_TD[playerid][0], 293.000000, 124.000000);
	PlayerTextDrawSetOutline(playerid, TDM_TD[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, TDM_TD[playerid][0], 0);
	PlayerTextDrawAlignment(playerid, TDM_TD[playerid][0], 2);
	PlayerTextDrawColor(playerid, TDM_TD[playerid][0], -1);
	PlayerTextDrawBackgroundColor(playerid, TDM_TD[playerid][0], 255);
	PlayerTextDrawBoxColor(playerid, TDM_TD[playerid][0], -1378294137);
	PlayerTextDrawUseBox(playerid, TDM_TD[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, TDM_TD[playerid][0], 1);
	PlayerTextDrawSetSelectable(playerid, TDM_TD[playerid][0], 0);

	TDM_TD[playerid][1] = CreatePlayerTextDraw(playerid, 514.000000, 138.000000, "Scoreboard");
	PlayerTextDrawFont(playerid, TDM_TD[playerid][1], 3);
	PlayerTextDrawLetterSize(playerid, TDM_TD[playerid][1], 0.462500, 1.650000);
	PlayerTextDrawTextSize(playerid, TDM_TD[playerid][1], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, TDM_TD[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, TDM_TD[playerid][1], 0);
	PlayerTextDrawAlignment(playerid, TDM_TD[playerid][1], 1);
	PlayerTextDrawColor(playerid, TDM_TD[playerid][1], -1);
	PlayerTextDrawBackgroundColor(playerid, TDM_TD[playerid][1], 255);
	PlayerTextDrawBoxColor(playerid, TDM_TD[playerid][1], 50);
	PlayerTextDrawUseBox(playerid, TDM_TD[playerid][1], 0);
	PlayerTextDrawSetProportional(playerid, TDM_TD[playerid][1], 1);
	PlayerTextDrawSetSelectable(playerid, TDM_TD[playerid][1], 0);

	TDM_TD[playerid][2] = CreatePlayerTextDraw(playerid, 506.000000, 163.000000, "Team A: 123");
	PlayerTextDrawFont(playerid, TDM_TD[playerid][2], 3);
	PlayerTextDrawLetterSize(playerid, TDM_TD[playerid][2], 0.462500, 1.650000);
	PlayerTextDrawTextSize(playerid, TDM_TD[playerid][2], 636.500000, 17.000000);
	PlayerTextDrawSetOutline(playerid, TDM_TD[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, TDM_TD[playerid][2], 0);
	PlayerTextDrawAlignment(playerid, TDM_TD[playerid][2], 1);
	PlayerTextDrawColor(playerid, TDM_TD[playerid][2], -16776961);
	PlayerTextDrawBackgroundColor(playerid, TDM_TD[playerid][2], 255);
	PlayerTextDrawBoxColor(playerid, TDM_TD[playerid][2], 50);
	PlayerTextDrawUseBox(playerid, TDM_TD[playerid][2], 0);
	PlayerTextDrawSetProportional(playerid, TDM_TD[playerid][2], 1);
	PlayerTextDrawSetSelectable(playerid, TDM_TD[playerid][2], 0);

	TDM_TD[playerid][3] = CreatePlayerTextDraw(playerid, 506.000000, 183.000000, "Team B: 234");
	PlayerTextDrawFont(playerid, TDM_TD[playerid][3], 3);
	PlayerTextDrawLetterSize(playerid, TDM_TD[playerid][3], 0.462500, 1.650000);
	PlayerTextDrawTextSize(playerid, TDM_TD[playerid][3], 636.500000, 17.000000);
	PlayerTextDrawSetOutline(playerid, TDM_TD[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, TDM_TD[playerid][3], 0);
	PlayerTextDrawAlignment(playerid, TDM_TD[playerid][3], 1);
	PlayerTextDrawColor(playerid, TDM_TD[playerid][3], 65535);
	PlayerTextDrawBackgroundColor(playerid, TDM_TD[playerid][3], 255);
	PlayerTextDrawBoxColor(playerid, TDM_TD[playerid][3], 50);
	PlayerTextDrawUseBox(playerid, TDM_TD[playerid][3], 0);
	PlayerTextDrawSetProportional(playerid, TDM_TD[playerid][3], 1);
	PlayerTextDrawSetSelectable(playerid, TDM_TD[playerid][3], 0);

	TDM_TD[playerid][4] = CreatePlayerTextDraw(playerid, 506.000000, 204.000000, "~y~Target: ~g~234");
	PlayerTextDrawFont(playerid, TDM_TD[playerid][4], 3);
	PlayerTextDrawLetterSize(playerid, TDM_TD[playerid][4], 0.462500, 1.650000);
	PlayerTextDrawTextSize(playerid, TDM_TD[playerid][4], 636.500000, 17.000000);
	PlayerTextDrawSetOutline(playerid, TDM_TD[playerid][4], 1);
	PlayerTextDrawSetShadow(playerid, TDM_TD[playerid][4], 0);
	PlayerTextDrawAlignment(playerid, TDM_TD[playerid][4], 1);
	PlayerTextDrawColor(playerid, TDM_TD[playerid][4], 65535);
	PlayerTextDrawBackgroundColor(playerid, TDM_TD[playerid][4], 255);
	PlayerTextDrawBoxColor(playerid, TDM_TD[playerid][4], 50);
	PlayerTextDrawUseBox(playerid, TDM_TD[playerid][4], 0);
	PlayerTextDrawSetProportional(playerid, TDM_TD[playerid][4], 1);
	PlayerTextDrawSetSelectable(playerid, TDM_TD[playerid][4], 0);

	ZombieTD[playerid][0] = CreatePlayerTextDraw(playerid, 560.000000, 148.000000, "_");
    PlayerTextDrawFont(playerid, ZombieTD[playerid][0], 1);
    PlayerTextDrawLetterSize(playerid, ZombieTD[playerid][0], 0.591666, 8.949997);
    PlayerTextDrawTextSize(playerid, ZombieTD[playerid][0], 299.500000, 105.000000);
    PlayerTextDrawSetOutline(playerid, ZombieTD[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, ZombieTD[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, ZombieTD[playerid][0], 2);
    PlayerTextDrawColor(playerid, ZombieTD[playerid][0], -1);
    PlayerTextDrawBackgroundColor(playerid, ZombieTD[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, ZombieTD[playerid][0], 852308680);
    PlayerTextDrawUseBox(playerid, ZombieTD[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, ZombieTD[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, ZombieTD[playerid][0], 0);

    ZombieTD[playerid][1] = CreatePlayerTextDraw(playerid, 509.000000, 155.000000, "~y~Human Alive: ~r~99");
    PlayerTextDrawFont(playerid, ZombieTD[playerid][1], 3);
    PlayerTextDrawLetterSize(playerid, ZombieTD[playerid][1], 0.375000, 1.900000);
    PlayerTextDrawTextSize(playerid, ZombieTD[playerid][1], 740.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, ZombieTD[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, ZombieTD[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, ZombieTD[playerid][1], 1);
    PlayerTextDrawColor(playerid, ZombieTD[playerid][1], -1);
    PlayerTextDrawBackgroundColor(playerid, ZombieTD[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, ZombieTD[playerid][1], 50);
    PlayerTextDrawUseBox(playerid, ZombieTD[playerid][1], 0);
    PlayerTextDrawSetProportional(playerid, ZombieTD[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, ZombieTD[playerid][1], 0);

    ZombieTD[playerid][2] = CreatePlayerTextDraw(playerid, 518.000000, 185.000000, "Event end in:");
    PlayerTextDrawFont(playerid, ZombieTD[playerid][2], 3);
    PlayerTextDrawLetterSize(playerid, ZombieTD[playerid][2], 0.375000, 1.900000);
    PlayerTextDrawTextSize(playerid, ZombieTD[playerid][2], 740.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, ZombieTD[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, ZombieTD[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, ZombieTD[playerid][2], 1);
    PlayerTextDrawColor(playerid, ZombieTD[playerid][2], -1);
    PlayerTextDrawBackgroundColor(playerid, ZombieTD[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, ZombieTD[playerid][2], 50);
    PlayerTextDrawUseBox(playerid, ZombieTD[playerid][2], 0);
    PlayerTextDrawSetProportional(playerid, ZombieTD[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, ZombieTD[playerid][2], 0);

    ZombieTD[playerid][3] = CreatePlayerTextDraw(playerid, 524.000000, 206.000000, "99 minutes");
    PlayerTextDrawFont(playerid, ZombieTD[playerid][3], 3);
    PlayerTextDrawLetterSize(playerid, ZombieTD[playerid][3], 0.375000, 1.950000);
    PlayerTextDrawTextSize(playerid, ZombieTD[playerid][3], 740.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, ZombieTD[playerid][3], 1);
    PlayerTextDrawSetShadow(playerid, ZombieTD[playerid][3], 0);
    PlayerTextDrawAlignment(playerid, ZombieTD[playerid][3], 1);
    PlayerTextDrawColor(playerid, ZombieTD[playerid][3], 852308735);
    PlayerTextDrawBackgroundColor(playerid, ZombieTD[playerid][3], 255);
    PlayerTextDrawBoxColor(playerid, ZombieTD[playerid][3], 50);
    PlayerTextDrawUseBox(playerid, ZombieTD[playerid][3], 0);
    PlayerTextDrawSetProportional(playerid, ZombieTD[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, ZombieTD[playerid][3], 0);

	DeletePVar(playerid, "IsAtEvent");
	DeletePVar(playerid, "EditRaceCP");

	return 1;
}

hook OnPlayerDeath(playerid, killerid, reason) {

	if (GetPVarInt(playerid, "IsAtEvent") == 1) {

		TogglePlayerSpectating(playerid, 1);
		SetTimerEx("Event_RespawnPlayer", 4000, false, "d", playerid);

		evRaceCP[playerid] = -1;
		if (IsValidVehicle(evCar[playerid]))
			Vehicle_Delete(evCar[playerid], false);

		SetPlayerColor(playerid, COLOR_DEFAULT);
		SetCameraBehindPlayer(playerid);
		SetPlayerPositionEx(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);
		SetPlayerHealth(playerid, PlayerData[playerid][pHealth]);
		SetPlayerArmour(playerid, PlayerData[playerid][pArmor]);
		SetPlayerVirtualWorld(playerid, PlayerData[playerid][pWorld]);
		SetPlayerInterior(playerid, PlayerData[playerid][pInterior]);
		SetPlayerSkin(playerid, PlayerData[playerid][pSkin]);

		if (PlayerData[playerid][pOnDuty]) {

			SetFactionColor(playerid);
			SetPlayerSkin(playerid, PlayerData[playerid][pFactionSkin]);
		}

		ResetPlayerMoney(playerid);
		GivePlayerMoney(playerid, GetMoney(playerid));
		ResetPlayerWeapons(playerid);
		SetWeapons(playerid);
		DisableRemoteVehicleCollisions(playerid, 0);
		DisablePlayerRaceCheckpoint(playerid);

		SendEventMessage(EventType, COLOR_SERVER, "EVENT: "RED"%s "YELLOW"has been disqualified.", GetName(playerid));
		SetPVarInt(playerid, "IsAtEvent", -1);
	}
	if (GetPVarInt(playerid, "IsAtEvent") == 3 || GetPVarInt(killerid, "IsAtEvent") == 3) {

		ClearAnimations(playerid);
		ResetPlayerWeapons(playerid);

		if (killerid != INVALID_PLAYER_ID) {

			if (EventType == 3) {

				tdm_EventData[eventTeamScore][evTeam[killerid]-1] ++;

				switch (evTeam[killerid]) {

					case 1: SendEventMessage(EventType, COLOR_SERVER, "EVENT: "RED"%s "YELLOW"has killed "BLUE"%s "YELLOW"with %s. Team A Score: {33aa33}%d", GetName(killerid), GetName(playerid), ReturnWeaponName(GetPlayerWeapon(killerid)), tdm_EventData[eventTeamScore][0]);
					case 2: SendEventMessage(EventType, COLOR_SERVER, "EVENT: "BLUE"%s "YELLOW"has killed "RED"%s "YELLOW"with %s. Team B Score: {33aa33}%d", GetName(killerid), GetName(playerid), ReturnWeaponName(GetPlayerWeapon(killerid)), tdm_EventData[eventTeamScore][1]);
				}
				TDM_UpdateTD(evTeam[killerid]);
				GameTextForPlayer(killerid, "~g~Perfect!", 3500, 3);

				if (tdm_EventData[eventTeamScore][evTeam[killerid]-1] >= tdm_EventData[eventMaxScore]) {

					static getTeam[][] = { ""RED"Team A", ""BLUE"Team B" };
					tdm_EventData[eventWinner] = evTeam[killerid];

					SendEventMessage(EventType, COLOR_SERVER, "EVENT: "YELLOW"Event telah selesai dan dimenangkan oleh %s", getTeam[tdm_EventData[eventWinner]-1]);
				
					foreach (new id : Player) {

						if (EventType == 3 && GetPVarInt(id, "IsAtEvent") == EventType && tdm_EventData[eventWinner] > 0) {

							if (evTeam[id] == tdm_EventData[eventWinner]) {

								GiveMoney(id, tdm_EventData[eventPrice]*2);
								SendClientMessageEx(id, COLOR_SERVER, "EVENT: "YELLOW"Tim kamu telah memenangkan mode ini dan mendapatkan hadiah sebesar {33aa33}$%s!", FormatNumber(tdm_EventData[eventPrice]*2));
							}
							else {

								GiveMoney(id, tdm_EventData[eventPrice]);
								SendClientMessageEx(id, COLOR_SERVER, "EVENT: "YELLOW"Kamu telah berpartisipasi dalam mode ini dan mendapatkan {33aa33}$%s", FormatNumber(tdm_EventData[eventPrice]));
							}

							TogglePlayerSpectating(id, 1);
							SetTimerEx("Event_RespawnPlayer", 4000, false, "d", id);

							evTeam[id] = 0;
							TDM_DisplayTD(id, false);
							TDM_ToggleAntiCheat(id, false);

							SetPlayerTeam(id,0);
							SetPlayerColor(id, COLOR_DEFAULT);
							SetCameraBehindPlayer(id);
							SetPlayerPositionEx(id, PlayerData[id][pPos][0], PlayerData[id][pPos][1], PlayerData[id][pPos][2]);
							SetPlayerHealth(id, PlayerData[id][pHealth]);
							SetPlayerArmour(id, PlayerData[id][pArmor]);
							SetPlayerVirtualWorld(id, PlayerData[id][pWorld]);
							SetPlayerInterior(id, PlayerData[id][pInterior]);
							SetPlayerSkin(id, PlayerData[id][pSkin]);

							if (PlayerData[id][pOnDuty]) {

								SetFactionColor(id);
								SetPlayerSkin(id, PlayerData[id][pFactionSkin]);
							}

							ResetPlayerMoney(id);
							GivePlayerMoney(id, PlayerData[id][pMoney]);
							ResetPlayerWeapons(id);
							SetWeapons(id);
							SetPVarInt(id, "IsAtEvent", -1);
						}
					}
					Event_ForceEnd();
				}
				else {

					if (GetPlayerState(playerid) == PLAYER_STATE_WASTED) {

						SetSpawnInfo(playerid, evTeam[playerid], tdm_EventData[eventSkin][evTeam[playerid]-1], tdm_EventData[eventPosX][evTeam[playerid]-1], tdm_EventData[eventPosY][evTeam[playerid]-1], tdm_EventData[eventPosZ][evTeam[playerid]-1], tdm_EventData[eventPosA][evTeam[playerid]-1], 0, 0, 0, 0, 0, 0);
						GameTextForPlayer(playerid, "~y~Nice Try!", 3500, 3);

						TogglePlayerSpectating(playerid, 1);
						SetTimerEx("Event_RespawnPlayer", 3500, false, "d", playerid);
					}
					SetPlayerVirtualWorld(playerid, 0);
				}
			}
		}
		else {

			GameTextForPlayer(playerid, "~r~Disqualified!", 3500, 3);
			SendEventMessage(EventType, COLOR_SERVER, "EVENT: "YELLOW"%s has been disqualified due suicide.", GetName(playerid));

			TogglePlayerSpectating(playerid, 1);
			SetTimerEx("Event_RespawnPlayer", 4000, false, "d", playerid);

			evTeam[playerid] = 0;
			TDM_DisplayTD(playerid, false);
			TDM_ToggleAntiCheat(playerid, false);

			SetPlayerTeam(playerid,0);
			SetPlayerColor(playerid, COLOR_DEFAULT);
			SetCameraBehindPlayer(playerid);
			SetPlayerPositionEx(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);
			SetPlayerHealth(playerid, PlayerData[playerid][pHealth]);
			SetPlayerArmour(playerid, PlayerData[playerid][pArmor]);
			SetPlayerVirtualWorld(playerid, PlayerData[playerid][pWorld]);
			SetPlayerInterior(playerid, PlayerData[playerid][pInterior]);
			SetPlayerSkin(playerid, PlayerData[playerid][pSkin]);

			if (PlayerData[playerid][pOnDuty]) {

				SetFactionColor(playerid);
				SetPlayerSkin(playerid, PlayerData[playerid][pFactionSkin]);
			}

			ResetPlayerMoney(playerid);
			GivePlayerMoney(playerid, PlayerData[playerid][pMoney]);
			ResetPlayerWeapons(playerid);
			SetWeapons(playerid);
			SetPVarInt(playerid, "IsAtEvent", -1);
		}
	}
	if (GetPVarInt(playerid, "IsAtEvent") == 4 || GetPVarInt(killerid, "IsAtEvent") == 4) {

		ClearAnimations(playerid);
		ResetPlayerWeapons(playerid);

		if (killerid != INVALID_PLAYER_ID) {

			dm_EventData[eventExp][killerid] ++;

			foreach (new id : Player) if (GetPVarInt(id, "IsAtEvent") == EventType && EventType == 4) {

				if (dm_EventData[eventExp][killerid] > dm_EventData[eventExp][id]) {

					HighestEXP = dm_EventData[eventExp][killerid];
					PlayerHighestEXP = killerid;

					DM_UpdateTD();
				}
			}
			SendEventMessage(EventType, COLOR_SERVER, "EVENT: "RED"%s "YELLOW"has killed "ORANGE"%s"YELLOW". Exp: {009000}%d", GetName(killerid), GetName(playerid), dm_EventData[eventExp][killerid]);
			GameTextForPlayer(killerid, "~g~Perfect!", 3500, 3);

			if (dm_EventData[eventExp][killerid] >= dm_EventData[eventMaxScore]) {

				dm_EventData[eventWinner] = killerid;
				SendEventMessage(EventType, COLOR_SERVER, "EVENT: "RED"%s "YELLOW"telah memenangkan mode ini dan mendapatkan hadiah sebesar {009000}$%s", GetName(dm_EventData[eventWinner]), FormatNumber(dm_EventData[eventPrice]+10000));
			
				foreach (new id : Player) if (GetPVarInt(id, "IsAtEvent") == EventType && EventType == 4) {

					if (id != dm_EventData[eventWinner]) {

						GiveMoney(id, dm_EventData[eventPrice]);
						SendClientMessageEx(id, COLOR_SERVER, "EVENT: "YELLOW"Kamu telah berpartisipasi dalam mode ini dan mendapatkan {009000}$%s", FormatNumber(dm_EventData[eventPrice]));
					}
					else GiveMoney(id, dm_EventData[eventPrice]+10000);
				
					TogglePlayerSpectating(id, 1);
					SetTimerEx("Event_RespawnPlayer", 4000, false, "d", id);

					dm_EventData[eventExp][id] = 0;
					DM_DisplayTD(id, false);
					DM_ToggleAntiCheat(id, false);

					SetPlayerColor(id, COLOR_DEFAULT);
					SetCameraBehindPlayer(id);
					SetPlayerPositionEx(id, PlayerData[id][pPos][0], PlayerData[id][pPos][1], PlayerData[id][pPos][2]);
					SetPlayerHealth(id, PlayerData[id][pHealth]);
					SetPlayerArmour(id, PlayerData[id][pArmor]);
					SetPlayerVirtualWorld(id, PlayerData[id][pWorld]);
					SetPlayerInterior(id, PlayerData[id][pInterior]);
					SetPlayerSkin(id, PlayerData[id][pSkin]);

					if (PlayerData[id][pOnDuty]) {

						SetFactionColor(id);
						SetPlayerSkin(id, PlayerData[id][pFactionSkin]);
					}

					ResetPlayerMoney(id);
					GivePlayerMoney(id, PlayerData[id][pMoney]);
					ResetPlayerWeapons(id);
					SetWeapons(id);
					SetPVarInt(id, "IsAtEvent", -1);
				}
				Event_ForceEnd();
			}
			else {

				if (GetPlayerState(playerid) == PLAYER_STATE_WASTED) {

					SetSpawnInfo(playerid, 0, PlayerData[playerid][pSkin], dm_EventData[eventPosX], dm_EventData[eventPosY], dm_EventData[eventPosZ], dm_EventData[eventPosA], 0, 0, 0, 0, 0, 0);
					GameTextForPlayer(playerid, "~r~Nice Try!", 3000, 3);

					TogglePlayerSpectating(playerid, 1);
					SetTimerEx("Event_RespawnPlayer", 3000, false, "d", playerid);
				}
				SetPlayerVirtualWorld(playerid, 0);
			}
		}
		else {

			GameTextForPlayer(playerid, "~r~Disqualified!", 3500, 3);
			SendEventMessage(EventType, COLOR_SERVER, "EVENT: "ORANGE"%s "YELLOW"has been disqualified due suicide.", GetName(playerid));

			TogglePlayerSpectating(playerid, 1);
			SetTimerEx("Event_RespawnPlayer", 4000, false, "d", playerid);

			dm_EventData[eventExp][playerid] = 0;
			DM_DisplayTD(playerid, false);
			DM_ToggleAntiCheat(playerid, false);

			SetPlayerColor(playerid, COLOR_DEFAULT);
			SetCameraBehindPlayer(playerid);
			SetPlayerPositionEx(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);
			SetPlayerHealth(playerid, PlayerData[playerid][pHealth]);
			SetPlayerArmour(playerid, PlayerData[playerid][pArmor]);
			SetPlayerVirtualWorld(playerid, PlayerData[playerid][pWorld]);
			SetPlayerInterior(playerid, PlayerData[playerid][pInterior]);
			SetPlayerSkin(playerid, PlayerData[playerid][pSkin]);

			if (PlayerData[playerid][pOnDuty]) {

				SetFactionColor(playerid);
				SetPlayerSkin(playerid, PlayerData[playerid][pFactionSkin]);
			}

			ResetPlayerMoney(playerid);
			GivePlayerMoney(playerid, PlayerData[playerid][pMoney]);
			ResetPlayerWeapons(playerid);
			SetWeapons(playerid);
			SetPVarInt(playerid, "IsAtEvent", -1);
		}
	}
	if (GetPVarInt(playerid, "IsAtEvent") == 5) {

		ClearAnimations(playerid);
		ResetPlayerWeapons(playerid);

		if (killerid != INVALID_PLAYER_ID) {

			SendEventMessage(EventType, COLOR_SERVER, "EVENT: "PURPLE"%s "YELLOW"has been eliminated due killing a participant", GetName(killerid));

			TogglePlayerSpectating(playerid, 1);
			SetTimerEx("Event_RespawnPlayer", 4000, false, "d", playerid);

			Parachute_ToggleAntiCheat(playerid, false);

			SetPlayerColor(playerid, COLOR_DEFAULT);
			SetCameraBehindPlayer(playerid);
			SetPlayerPositionEx(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);
			SetPlayerHealth(playerid, PlayerData[playerid][pHealth]);
			SetPlayerArmour(playerid, PlayerData[playerid][pArmor]);
			SetPlayerVirtualWorld(playerid, PlayerData[playerid][pWorld]);
			SetPlayerInterior(playerid, PlayerData[playerid][pInterior]);
			SetPlayerSkin(playerid, PlayerData[playerid][pSkin]);

			if (PlayerData[playerid][pOnDuty]) {

				SetFactionColor(playerid);
				SetPlayerSkin(playerid, PlayerData[playerid][pFactionSkin]);
			}

			ResetPlayerMoney(playerid);
			GivePlayerMoney(playerid, PlayerData[playerid][pMoney]);
			ResetPlayerWeapons(playerid);
			DisablePlayerRaceCheckpoint(playerid);
			SetWeapons(playerid);
			SetPVarInt(playerid, "IsAtEvent", -1);
		}
		else {

			SendEventMessage(EventType, COLOR_SERVER, "EVENT: "PURPLE"%s "YELLOW"has been disqualified due suicide.", GetName(playerid));

			TogglePlayerSpectating(playerid, 1);
			SetTimerEx("Event_RespawnPlayer", 4000, false, "d", playerid);

			Parachute_ToggleAntiCheat(playerid, false);

			SetPlayerColor(playerid, COLOR_DEFAULT);
			SetCameraBehindPlayer(playerid);
			SetPlayerPositionEx(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);
			SetPlayerHealth(playerid, PlayerData[playerid][pHealth]);
			SetPlayerArmour(playerid, PlayerData[playerid][pArmor]);
			SetPlayerVirtualWorld(playerid, PlayerData[playerid][pWorld]);
			SetPlayerInterior(playerid, PlayerData[playerid][pInterior]);
			SetPlayerSkin(playerid, PlayerData[playerid][pSkin]);

			if (PlayerData[playerid][pOnDuty]) {

				SetFactionColor(playerid);
				SetPlayerSkin(playerid, PlayerData[playerid][pFactionSkin]);
			}

			ResetPlayerMoney(playerid);
			GivePlayerMoney(playerid, PlayerData[playerid][pMoney]);
			ResetPlayerWeapons(playerid);
			SetWeapons(playerid);
			DisablePlayerRaceCheckpoint(playerid);
			SetPVarInt(playerid, "IsAtEvent", -1);
		}
		parachute_EventData[eventEntry] --;
		if (parachute_EventData[eventEntry] == 1) {

			foreach (new i : Player) if (GetPVarInt(i, "IsAtEvent") == 5)
			{
				TogglePlayerSpectating(i, 1);
				SetTimerEx("Event_RespawnPlayer", 4000, false, "d", i);

				Parachute_ToggleAntiCheat(playerid, false);

				SetPlayerColor(i, COLOR_DEFAULT);
				SetCameraBehindPlayer(i);
				SetPlayerPositionEx(i, PlayerData[i][pPos][0], PlayerData[i][pPos][1], PlayerData[i][pPos][2]);
				SetPlayerHealth(i, PlayerData[i][pHealth]);
				SetPlayerArmour(i, PlayerData[i][pArmor]);
				SetPlayerVirtualWorld(i, PlayerData[i][pWorld]);
				SetPlayerInterior(i, PlayerData[i][pInterior]);
				SetPlayerSkin(i, PlayerData[i][pSkin]);

				if (PlayerData[i][pOnDuty]) {

					SetFactionColor(i);
					SetPlayerSkin(playerid, PlayerData[i][pFactionSkin]);
				}

				ResetPlayerMoney(i);
				GivePlayerMoney(i, GetMoney(i));
				ResetPlayerWeapons(i);
				SetWeapons(i);
				DisablePlayerRaceCheckpoint(i);

				GiveMoney(i, parachute_EventData[eventPrice]),
				SendEventMessage(EventType, COLOR_SERVER, "EVENT: Server has force end event, there is only you in this event, you won "GREEN"$%s", FormatNumber(parachute_EventData[eventPrice]));
				SetPVarInt(i, "IsAtEvent", -1);
			}
			Event_ForceEnd();			
		}
	}
    if (GetPVarInt(playerid, "IsAtEvent") == 6 || GetPVarInt(killerid, "IsAtEvent") == 6) {

        ClearAnimations(playerid);
        ResetPlayerWeapons(playerid);

        if (killerid != INVALID_PLAYER_ID) {

            switch (GetPlayerTeam(killerid)) {

                case 1: {

                    static Float:armorData[MAX_PLAYERS];
                    GetPlayerArmour(playerid, armorData[killerid]);

                    if (armorData[killerid] < 90) {

                        GameTextForPlayer(killerid, "~g~Immune +15", 3000, 3);
                        SetPlayerArmour(killerid, (armorData[killerid]+15));
                    }
                    else {

                        GameTextForPlayer(killerid, "~g~Killer!", 3000, 3);
                    }
                    SendEventMessage(EventType, COLOR_SERVER, "EVENT: "GREEN"%s "YELLOW"has killed "RED"%s "YELLOW"with %s.", GetName(killerid), GetName(playerid), ReturnWeaponName(GetPlayerWeapon(killerid)));
                }
                case 2: {

                    evTeam[playerid] = 2;
                    zombie_EventData[eventAlive] --;

                    foreach (new id : Player) if (IsPlayerSpawned(id) && GetPVarInt(id, "IsAtEvent") == 6) {
                        
                        Zombie_UpdateTD(id);
                        SendClientMessageEx(id, COLOR_SERVER, "EVENT: "RED"%s "YELLOW"has killed "GREEN"%s "YELLOW"with %s.", GetName(killerid), GetName(playerid), ReturnWeaponName(GetPlayerWeapon(killerid)));
                    }
                    SetPlayerTeam(playerid, evTeam[playerid]);
					SetPlayerColor(playerid, RemoveAlpha(X11_RED));

                    GameTextForPlayer(playerid, "~r~Infected!", 3000, 3);
                    GameTextForPlayer(killerid, "~g~Injected!", 3000, 3);
                }
            }
            if (!zombie_EventData[eventAlive]) {

				static getTeam[][] = { ""GREEN"Human", ""RED"Zombie" };
				zombie_EventData[eventWinner] = evTeam[killerid];

                SendEventMessage(EventType, COLOR_SERVER, "EVENT: %s "YELLOW"is won!", getTeam[zombie_EventData[eventWinner]-1]);

                foreach (new id : Player) if (GetPVarInt(id, "IsAtEvent") == 6 && zombie_EventData[eventWinner] > 0) {

                    if (evTeam[id] == zombie_EventData[eventWinner]) {
						GiveMoney(id, zombie_EventData[eventPrice]+10000);
						SendClientMessageEx(id, COLOR_SERVER, "EVENT: "YELLOW"Kamu telah memenangkan mode ini dan mendapatkan hadiah sebesar {009000}$%s", FormatNumber(dm_EventData[eventPrice]+10000));
					}
                    else {
						GiveMoney(id, zombie_EventData[eventPrice]);
						SendClientMessageEx(id, COLOR_SERVER, "EVENT: "YELLOW"Kamu telah berpartisipasi dalam mode ini dan mendapatkan {009000}$%s", FormatNumber(dm_EventData[eventPrice]));
					}
                    
					TogglePlayerSpectating(id, 1);
					SetTimerEx("Event_RespawnPlayer", 4000, false, "d", id);

					evTeam[id] = 0;
					Zombie_DisplayTD(id, false);
					Zombie_ToggleAntiCheat(id, false);

					SetPlayerTeam(id,0);
					SetPlayerColor(id, COLOR_DEFAULT);
					SetCameraBehindPlayer(id);
					SetPlayerPositionEx(id, PlayerData[id][pPos][0], PlayerData[id][pPos][1], PlayerData[id][pPos][2]);
					SetPlayerHealth(id, PlayerData[id][pHealth]);
					SetPlayerArmour(id, PlayerData[id][pArmor]);
					SetPlayerVirtualWorld(id, PlayerData[id][pWorld]);
					SetPlayerInterior(id, PlayerData[id][pInterior]);
					SetPlayerSkin(id, PlayerData[id][pSkin]);

					if (PlayerData[id][pOnDuty]) {

						SetFactionColor(id);
						SetPlayerSkin(id, PlayerData[id][pFactionSkin]);
					}

					ResetPlayerMoney(id);
					GivePlayerMoney(id, PlayerData[id][pMoney]);
					ResetPlayerWeapons(id);
					SetWeapons(id);
					SetPVarInt(id, "IsAtEvent", -1);
                }
                Event_ForceEnd();
            }
            else {

				if (GetPlayerState(playerid) == PLAYER_STATE_WASTED) {

					SetSpawnInfo(playerid, evTeam[playerid], PlayerData[playerid][pSkin], zombie_EventData[eventPosX][evTeam[playerid]-1], zombie_EventData[eventPosY][evTeam[playerid]-1], zombie_EventData[eventPosZ][evTeam[playerid]-1], zombie_EventData[eventPosA][evTeam[playerid]-1], 0, 0, 0, 0, 0, 0);
					TogglePlayerSpectating(playerid, 1);

                    SetPlayerVirtualWorld(playerid, (playerid+evTeam[playerid]));
					SetTimerEx("Event_RespawnPlayer", 3000, false, "d", playerid);
				}
            }
        }
		else {

			GameTextForPlayer(playerid, "~r~Disqualified!", 4000, 3);
			SendEventMessage(EventType, COLOR_SERVER, "EVENT: "YELLOW"%s has been disqualified due suicide.", GetName(playerid));

			TogglePlayerSpectating(playerid, 1);
			SetTimerEx("Event_RespawnPlayer", 4000, false, "d", playerid);

			evTeam[playerid] = 0;
			Zombie_DisplayTD(playerid, false);
			Zombie_ToggleAntiCheat(playerid, false);

			SetPlayerTeam(playerid,0);
			SetPlayerColor(playerid, COLOR_DEFAULT);
			SetCameraBehindPlayer(playerid);
			SetPlayerPositionEx(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);
			SetPlayerHealth(playerid, PlayerData[playerid][pHealth]);
			SetPlayerArmour(playerid, PlayerData[playerid][pArmor]);
			SetPlayerVirtualWorld(playerid, PlayerData[playerid][pWorld]);
			SetPlayerInterior(playerid, PlayerData[playerid][pInterior]);
			SetPlayerSkin(playerid, PlayerData[playerid][pSkin]);

			if (PlayerData[playerid][pOnDuty]) {

				SetFactionColor(playerid);
				SetPlayerSkin(playerid, PlayerData[playerid][pFactionSkin]);
			}

			ResetPlayerMoney(playerid);
			GivePlayerMoney(playerid, PlayerData[playerid][pMoney]);
			ResetPlayerWeapons(playerid);
			SetWeapons(playerid);
			SetPVarInt(playerid, "IsAtEvent", -1);
		}
    }
}

hook OnPlayerSpawn(playerid) {

	if (GetPVarInt(playerid, "IsAtEvent") == 1 && EventType == 1) {

		evRaceCP[playerid] = -1;
		race_EventData[evEntry]--;

		if (race_EventData[evEntry] == 1) {

			foreach (new i : Player) if (GetPVarInt(i, "IsAtEvent") == 1)
			{
				TogglePlayerSpectating(i, 1);
				SetTimerEx("Event_RespawnPlayer", 4000, false, "d", i);

				evRaceCP[i] = -1;
				if (IsValidVehicle(evCar[i]))
					Vehicle_Delete(evCar[i], false);

				SetPlayerColor(i, COLOR_DEFAULT);
				SetCameraBehindPlayer(i);
				SetPlayerPositionEx(i, PlayerData[i][pPos][0], PlayerData[i][pPos][1], PlayerData[i][pPos][2]);
				SetPlayerHealth(i, PlayerData[i][pHealth]);
				SetPlayerArmour(i, PlayerData[i][pArmor]);
				SetPlayerVirtualWorld(i, PlayerData[i][pWorld]);
				SetPlayerInterior(i, PlayerData[i][pInterior]);
				SetPlayerSkin(i, PlayerData[i][pSkin]);

				if (PlayerData[i][pOnDuty]) {

					SetFactionColor(i);
					SetPlayerSkin(playerid, PlayerData[i][pFactionSkin]);
				}

				ResetPlayerMoney(i);
				GivePlayerMoney(i, GetMoney(i));
				ResetPlayerWeapons(i);
				SetWeapons(i);
				DisableRemoteVehicleCollisions(i, 0);
				DisablePlayerRaceCheckpoint(i);

				GiveMoney(i, race_EventData[evPrice]),
				SendEventMessage(EventType, COLOR_SERVER, "EVENT: Server has force end event, there is only you in this event, you won "GREEN"$%s", FormatNumber(race_EventData[evPrice]));
				SetPVarInt(i, "IsAtEvent", -1);
			}
			Event_ForceEnd();			
		}

		if (IsValidVehicle(evCar[playerid]))
			Vehicle_Delete(evCar[playerid], false);

		SetPlayerColor(playerid, COLOR_DEFAULT);
		SetCameraBehindPlayer(playerid);
		SetPlayerPositionEx(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);
		SetPlayerHealth(playerid, PlayerData[playerid][pHealth]);
		SetPlayerArmour(playerid, PlayerData[playerid][pArmor]);
		SetPlayerVirtualWorld(playerid, PlayerData[playerid][pWorld]);
		SetPlayerInterior(playerid, PlayerData[playerid][pInterior]);
		SetPlayerSkin(playerid, PlayerData[playerid][pSkin]);

		if (PlayerData[playerid][pOnDuty]) {

			SetFactionColor(playerid);
			SetPlayerSkin(playerid, PlayerData[playerid][pFactionSkin]);
		}

		ResetPlayerMoney(playerid);
		GivePlayerMoney(playerid, GetMoney(playerid));
		ResetPlayerWeapons(playerid);
		SetWeapons(playerid);
		DisableRemoteVehicleCollisions(playerid, 0);
		DisablePlayerRaceCheckpoint(playerid);
		SetPVarInt(playerid, "IsAtEvent", -1);
	}
	else if (GetPVarInt(playerid, "IsAtEvent") == 3 && EventType == 3) {

		TDM_ToggleAntiCheat(playerid, false);
		GameTextForPlayer(playerid, "~w~Kembali dalam~n~5 detik", 5000, 6);

		ResetPlayerMoney(playerid);
		GivePlayerMoney(playerid, GetMoney(playerid));

		SetPlayerPos(playerid, tdm_EventData[eventPosX][evTeam[playerid]-1], tdm_EventData[eventPosY][evTeam[playerid]-1], tdm_EventData[eventPosZ][evTeam[playerid]-1]);
		SetPlayerFacingAngle(playerid, tdm_EventData[eventPosA][evTeam[playerid]-1]);

		SetCameraBehindPlayer(playerid);
		SetPlayerSkin(playerid, tdm_EventData[eventSkin][evTeam[playerid]-1]);

		SetPlayerVirtualWorld(playerid, (playerid+666));
		SetPlayerInterior(playerid, tdm_EventData[eventInterior]);

		SetTimerEx("TDM_Spawning", 5000, false, "d", playerid);
	}
	else if (GetPVarInt(playerid, "IsAtEvent") == 4 && EventType == 4) {

		DM_ToggleAntiCheat(playerid, false);
		GameTextForPlayer(playerid, "~w~Kembali dalam~n~5 detik", 5000, 6);

		ResetPlayerMoney(playerid);
		GivePlayerMoney(playerid, GetMoney(playerid));

		SetCameraBehindPlayer(playerid);
		SetPlayerSkin(playerid, PlayerData[playerid][pSkin]);

		SetPlayerPos(playerid, dm_EventData[eventPosX], dm_EventData[eventPosY], dm_EventData[eventPosZ]);
		SetPlayerFacingAngle(playerid, dm_EventData[eventPosA]);

		SetPlayerVirtualWorld(playerid, (playerid+666));
		SetPlayerInterior(playerid, dm_EventData[eventInterior]);

		SetTimerEx("DM_Spawning", 5000, false, "d", playerid);
	}
	else if (GetPVarInt(playerid, "IsAtEvent") == 5 && EventType == 5) {

		SetPlayerPositionEx(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);

		SetPlayerHealth(playerid, PlayerData[playerid][pHealth]);
		SetPlayerArmour(playerid, PlayerData[playerid][pArmor]);

		SetPlayerVirtualWorld(playerid, PlayerData[playerid][pWorld]);
		SetPlayerInterior(playerid, PlayerData[playerid][pInterior]);

		SetCameraBehindPlayer(playerid);
		Parachute_ToggleAntiCheat(playerid, false);
		
		ResetPlayerWeapons(playerid);
		SetWeapons(playerid);

		DisablePlayerRaceCheckpoint(playerid);

		parachute_EventData[eventEntry] --;
	}
	else if (GetPVarInt(playerid, "IsAtEvent") == 6 && EventType == 6) {

		Zombie_ToggleAntiCheat(playerid, false);
		GameTextForPlayer(playerid, "~w~Kembali dalam~n~5 detik", 5000, 6);

		ResetPlayerMoney(playerid);
		GivePlayerMoney(playerid, GetMoney(playerid));

		SetPlayerPos(playerid, zombie_EventData[eventPosX][evTeam[playerid]-1], zombie_EventData[eventPosY][evTeam[playerid]-1], zombie_EventData[eventPosZ][evTeam[playerid]-1]);
		SetPlayerFacingAngle(playerid, zombie_EventData[eventPosA][evTeam[playerid]-1]);

		SetPlayerVirtualWorld(playerid, (playerid+666));
		SetPlayerInterior(playerid, zombie_EventData[eventInterior]);

		switch (evTeam[playerid]) {

			case 1: SetPlayerSkin(playerid, PlayerData[playerid][pSkin]);
			case 2: SetPlayerSkin(playerid, 162);
		}
		SetTimerEx("Zombie_Spawning", 5000, false, "d", playerid);
	}
	else if (GetPVarInt(playerid, "IsAtEvent") == -1) {

		dm_EventData[eventExp][playerid] = 0;
		evTeam[playerid] = 0;
		evRaceCP[playerid] = -1;
		if (IsValidVehicle(evCar[playerid]))
			Vehicle_Delete(evCar[playerid], false);

		Parachute_ToggleAntiCheat(playerid, false);
		Zombie_ToggleAntiCheat(playerid, false);
		TDM_ToggleAntiCheat(playerid, false);
		DM_ToggleAntiCheat(playerid, false);
				
		SetCameraBehindPlayer(playerid);
		SetPlayerPositionEx(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);
		SetPlayerHealth(playerid, PlayerData[playerid][pHealth]);
		SetPlayerArmour(playerid, PlayerData[playerid][pArmor]);
		SetPlayerVirtualWorld(playerid, PlayerData[playerid][pWorld]);
		SetPlayerInterior(playerid, PlayerData[playerid][pInterior]);
		SetPlayerSkin(playerid, PlayerData[playerid][pSkin]);

		if (PlayerData[playerid][pOnDuty]) {

			SetFactionColor(playerid);
			SetPlayerSkin(playerid, PlayerData[playerid][pFactionSkin]);
		}

		ResetPlayerMoney(playerid);
		GivePlayerMoney(playerid, GetMoney(playerid));
		ResetPlayerWeapons(playerid);
		SetWeapons(playerid);
		DisableRemoteVehicleCollisions(playerid, 0);
		DisablePlayerRaceCheckpoint(playerid);
		SetPVarInt(playerid, "IsAtEvent", 0);
	}
}

hook OnPlayerText(playerid, text[]) {

	if (GetPVarInt(playerid, "IsAtEvent") == 1) {

        text[0] = toupper(text[0]);

		SendEventMessage(EventType, GetPlayerColor(playerid), "%s: "WHITE"%s", GetName(playerid), text);
	}
	else if (GetPVarInt(playerid, "IsAtEvent") == 3) {

		if (GetPlayerVirtualWorld(playerid) != tdm_EventData[eventWorld] && EventStarted) {

			SendErrorMessage(playerid, "You must be spawned first into world!");
			return 0;
		}
        text[0] = toupper(text[0]);

		foreach (new id : Player) {

			if (GetPVarInt(id, "IsAtEvent") == 3 && GetPlayerTeam(playerid) == GetPlayerTeam(id) && GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(id)) {

				SendClientMessageEx(id, GetPlayerColor(playerid), "%s: "WHITE"%s", GetName(playerid), text);
			}
		}
	}
	else if (GetPVarInt(playerid, "IsAtEvent") == 4) {

		if (GetPlayerVirtualWorld(playerid) != dm_EventData[eventWorld] && EventStarted) {

			SendErrorMessage(playerid, "You must be spawned first into world!");
			return 0;
		}
        text[0] = toupper(text[0]);

		foreach (new id : Player) {

			if (GetPVarInt(id, "IsAtEvent") > 0 && GetPVarInt(playerid, "IsAtEvent") == GetPVarInt(id, "IsAtEvent")) {

				SendClientMessageEx(id, GetPlayerColor(playerid), "%s: "WHITE"%s", GetName(playerid), text);
			}
		}
	}
	else if (GetPVarInt(playerid, "IsAtEvent") == 5) {

        text[0] = toupper(text[0]);

		foreach (new id : Player) {

		if (GetPVarInt(id, "IsAtEvent") > 0 && GetPVarInt(id, "IsAtEvent") == 5) {

				SendClientMessage(id, GetPlayerColor(playerid), sprintf("%s: "WHITE"%s", GetName(playerid), text));
			}
		}		
	}		
	else if (GetPVarInt(playerid, "IsAtEvent") == 6) {

		if (GetPlayerVirtualWorld(playerid) != zombie_EventData[eventWorld] && EventStarted) {

			SendErrorMessage(playerid, "You must be spawned first into world!");
			return 0;
		}
        text[0] = toupper(text[0]);

		SendEventMessage(EventType, GetPlayerColor(playerid), "%s: "WHITE"%s", GetName(playerid), text);
	}	
	return 0;	
}

hook OnPlayerDisconnectEx(playerid) {

    if (GetPVarInt(playerid, "IsAtEvent") == 1) {

		evRaceCP[playerid] = -1;
		race_EventData[evEntry] --;
		
		if (race_EventData[evEntry] == 1) {

			foreach (new i : Player) if (GetPVarInt(i, "IsAtEvent") == 1)
			{
				TogglePlayerSpectating(i, 1);
				SetTimerEx("Event_RespawnPlayer", 4000, false, "d", i);

				evRaceCP[i] = -1;
				if (IsValidVehicle(evCar[i]))
					Vehicle_Delete(evCar[i], false);

				SetPlayerColor(i, COLOR_DEFAULT);
				SetCameraBehindPlayer(i);
				SetPlayerPositionEx(i, PlayerData[i][pPos][0], PlayerData[i][pPos][1], PlayerData[i][pPos][2]);
				SetPlayerHealth(i, PlayerData[i][pHealth]);
				SetPlayerArmour(i, PlayerData[i][pArmor]);
				SetPlayerVirtualWorld(i, PlayerData[i][pWorld]);
				SetPlayerInterior(i, PlayerData[i][pInterior]);
				SetPlayerSkin(i, PlayerData[i][pSkin]);

				if (PlayerData[i][pOnDuty]) {

					SetFactionColor(i);
					SetPlayerSkin(playerid, PlayerData[i][pFactionSkin]);
				}

				ResetPlayerMoney(i);
				GivePlayerMoney(i, GetMoney(i));
				ResetPlayerWeapons(i);
				SetWeapons(i);
				DisableRemoteVehicleCollisions(i, 0);
				DisablePlayerRaceCheckpoint(i);

				GiveMoney(i, race_EventData[evPrice]),
				SendEventMessage(EventType, COLOR_SERVER, "EVENT: Server has force end event, there is only you in this event, you won "GREEN"$%s", FormatNumber(race_EventData[evPrice]));
				SetPVarInt(i, "IsAtEvent", -1);
			}
			Event_ForceEnd();			
		}

		DisableRemoteVehicleCollisions(playerid, 0);
		DisablePlayerRaceCheckpoint(playerid);

		ResetPlayerStatistics(playerid);
		ResetPlayerWeapons(playerid);

		if (IsValidVehicle(evCar[playerid]))
			Vehicle_Delete(evCar[playerid], false);

		SendEventMessage(EventType, COLOR_SERVER, "EVENT: "GREEN"%s "YELLOW"has leave from event. (Disconnected/Timeout)", GetName(playerid));
		DeletePVar(playerid, "IsAtEvent");
    }
	else if (GetPVarInt(playerid, "IsAtEvent") == 3) {

		forex (td, 5) PlayerTextDrawDestroy(playerid, TDM_TD[playerid][td]);

		ResetPlayerStatistics(playerid);
		ResetPlayerWeapons(playerid);

		SetPlayerTeam(playerid,0);
		TDM_ToggleAntiCheat(playerid,false);

		SendEventMessage(EventType, COLOR_SERVER, "EVENT: "RED"%s "YELLOW"has leave from event. (Disconnected/FC)", GetName(playerid));
		tdm_EventData[eventEntry]--;		
		if (tdm_EventData[eventEntry] == 1) {

			foreach (new i : Player) if (GetPVarInt(i, "IsAtEvent") == 3)
			{
				TogglePlayerSpectating(i, 1);
				SetTimerEx("Event_RespawnPlayer", 4000, false, "d", i);

				evTeam[i] = 0;
				TDM_DisplayTD(i, false);
				TDM_ToggleAntiCheat(i, false);

				SetPlayerTeam(i,0);
				SetPlayerColor(i, COLOR_DEFAULT);
				SetCameraBehindPlayer(i);
				SetPlayerPositionEx(i, PlayerData[i][pPos][0], PlayerData[i][pPos][1], PlayerData[i][pPos][2]);
				SetPlayerHealth(i, PlayerData[i][pHealth]);
				SetPlayerArmour(i, PlayerData[i][pArmor]);
				SetPlayerVirtualWorld(i, PlayerData[i][pWorld]);
				SetPlayerInterior(i, PlayerData[i][pInterior]);
				SetPlayerSkin(i, PlayerData[i][pSkin]);

				if (PlayerData[i][pOnDuty]) {

					SetFactionColor(i);
					SetPlayerSkin(playerid, PlayerData[i][pFactionSkin]);
				}

				ResetPlayerMoney(i);
				GivePlayerMoney(i, PlayerData[i][pMoney]);
				ResetPlayerWeapons(i);
				SetWeapons(i);

				GiveMoney(i, tdm_EventData[eventPrice]),
				SendEventMessage(EventType, COLOR_SERVER, "EVENT: Server has force end event, there is only you in this event, you won "GREEN"$%s", FormatNumber(tdm_EventData[eventPrice]));
				SetPVarInt(i, "IsAtEvent", -1);
			}
			Event_ForceEnd();			
		}
		DeletePVar(playerid, "IsAtEvent");
	}
	else if (GetPVarInt(playerid, "IsAtEvent") == 4) {

		forex (td, 6) PlayerTextDrawDestroy(playerid, DM_TD[playerid][td]);

		ResetPlayerStatistics(playerid);
		ResetPlayerWeapons(playerid);

		dm_EventData[eventExp][playerid] = 0;
		dm_EventData[eventEntry]--;		
		if (dm_EventData[eventEntry] == 1) {

			foreach (new i : Player) if (GetPVarInt(i, "IsAtEvent") == 4)
			{
				TogglePlayerSpectating(i, 1);
				SetTimerEx("Event_RespawnPlayer", 4000, false, "d", i);

				dm_EventData[eventExp][i] = 0;
				DM_ToggleAntiCheat(playerid,false);
				DM_DisplayTD(i, false);

				SetPlayerColor(i, COLOR_DEFAULT);
				SetCameraBehindPlayer(i);
				SetPlayerPositionEx(i, PlayerData[i][pPos][0], PlayerData[i][pPos][1], PlayerData[i][pPos][2]);
				SetPlayerHealth(i, PlayerData[i][pHealth]);
				SetPlayerArmour(i, PlayerData[i][pArmor]);
				SetPlayerVirtualWorld(i, PlayerData[i][pWorld]);
				SetPlayerInterior(i, PlayerData[i][pInterior]);
				SetPlayerSkin(i, PlayerData[i][pSkin]);

				if (PlayerData[i][pOnDuty]) {

					SetFactionColor(i);
					SetPlayerSkin(playerid, PlayerData[i][pFactionSkin]);
				}

				ResetPlayerMoney(i);
				GivePlayerMoney(i, GetMoney(i));
				ResetPlayerWeapons(i);
				SetWeapons(i);

				GiveMoney(i, dm_EventData[eventPrice]),
				SendEventMessage(EventType, COLOR_SERVER, "EVENT: Server has force end event, there is only you in this event, you won "GREEN"$%s", FormatNumber(dm_EventData[eventPrice]));
				SetPVarInt(i, "IsAtEvent", -1);
			}
			Event_ForceEnd();			
		}
		DM_ToggleAntiCheat(playerid,false);

		SendEventMessage(EventType, COLOR_SERVER, "EVENT: "RED"%s "YELLOW"has leave from event. (Disconnected/FC)", GetName(playerid));
		DeletePVar(playerid, "IsAtEvent");
	}
	else if (GetPVarInt(playerid, "IsAtEvent") == 5) {

		ResetPlayerStatistics(playerid);
		ResetPlayerWeapons(playerid);

		parachute_EventData[eventEntry] --;
		if (parachute_EventData[eventEntry] == 1) {

			foreach (new i : Player) if (GetPVarInt(i, "IsAtEvent") == 5)
			{
				TogglePlayerSpectating(i, 1);
				SetTimerEx("Event_RespawnPlayer", 4000, false, "d", i);

				Parachute_ToggleAntiCheat(playerid, false);

				SetPlayerColor(i, COLOR_DEFAULT);
				SetCameraBehindPlayer(i);
				SetPlayerPositionEx(i, PlayerData[i][pPos][0], PlayerData[i][pPos][1], PlayerData[i][pPos][2]);
				SetPlayerHealth(i, PlayerData[i][pHealth]);
				SetPlayerArmour(i, PlayerData[i][pArmor]);
				SetPlayerVirtualWorld(i, PlayerData[i][pWorld]);
				SetPlayerInterior(i, PlayerData[i][pInterior]);
				SetPlayerSkin(i, PlayerData[i][pSkin]);

				if (PlayerData[i][pOnDuty]) {

					SetFactionColor(i);
					SetPlayerSkin(playerid, PlayerData[i][pFactionSkin]);
				}

				ResetPlayerMoney(i);
				GivePlayerMoney(i, GetMoney(i));
				ResetPlayerWeapons(i);
				SetWeapons(i);
				DisablePlayerRaceCheckpoint(i);

				GiveMoney(i, parachute_EventData[eventPrice]),
				SendEventMessage(EventType, COLOR_SERVER, "EVENT: Server has force end event, there is only you in this event, you won "GREEN"$%s", FormatNumber(parachute_EventData[eventPrice]));
				SetPVarInt(i, "IsAtEvent", -1);
			}
			Event_ForceEnd();			
		}

		DeletePVar(playerid, "IsAtEvent");
		SendEventMessage(EventType, COLOR_SERVER, "EVENT: "PURPLE"%s "YELLOW"has leave from event. (Disconnected/Timeout)", GetName(playerid));
	}
    else if (GetPVarInt(playerid, "IsAtEvent") == 6) {

        forex (td, 4) PlayerTextDrawDestroy(playerid, ZombieTD[playerid][td]);

        if (evTeam[playerid] == 1)
            zombie_EventData[eventAlive] --, evTeam[playerid] = 0;

		if (zombie_EventData[eventAlive] == 1) {

			foreach (new i : Player) if (GetPVarInt(i, "IsAtEvent") == 6)
			{
				TogglePlayerSpectating(i, 1);
				SetTimerEx("Event_RespawnPlayer", 4000, false, "d", i);

				evTeam[i] = 0;
				Zombie_DisplayTD(i, false);
				Zombie_ToggleAntiCheat(i, false);

				SetPlayerTeam(i,0);
				SetPlayerColor(i, COLOR_DEFAULT);
				SetCameraBehindPlayer(i);
				SetPlayerPositionEx(i, PlayerData[i][pPos][0], PlayerData[i][pPos][1], PlayerData[i][pPos][2]);
				SetPlayerHealth(i, PlayerData[i][pHealth]);
				SetPlayerArmour(i, PlayerData[i][pArmor]);
				SetPlayerVirtualWorld(i, PlayerData[i][pWorld]);
				SetPlayerInterior(i, PlayerData[i][pInterior]);
				SetPlayerSkin(i, PlayerData[i][pSkin]);

				if (PlayerData[i][pOnDuty]) {

					SetFactionColor(i);
					SetPlayerSkin(playerid, PlayerData[i][pFactionSkin]);
				}

				ResetPlayerMoney(i);
				GivePlayerMoney(i, GetMoney(i));
				ResetPlayerWeapons(i);
				SetWeapons(i);

				GiveMoney(i, zombie_EventData[eventPrice]),
				SendEventMessage(EventType, COLOR_SERVER, "EVENT: Server has force end event, there is only you in this event, you won "GREEN"$%s", FormatNumber(zombie_EventData[eventPrice]));
				SetPVarInt(i, "IsAtEvent", -1);
			}
			Event_ForceEnd();			
		}

		ResetPlayerStatistics(playerid);
		ResetPlayerWeapons(playerid);

		SetPlayerTeam(playerid,0);
		Zombie_ToggleAntiCheat(playerid,false);

		SendEventMessage(EventType, COLOR_SERVER, "EVENT: "GREEN"%s "YELLOW"has leave from event. (Disconnected/Timeout)", GetName(playerid));
		DeletePVar(playerid, "IsAtEvent");
    }
	else {
		if (GetPVarInt(playerid, "EditRaceCP") > 0)
			DeletePVar(playerid, "EditRaceCP");
	}
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA:areaid) {

	if (GetPVarInt(playerid, "IsAtEvent") == 3) {

		if (areaid == tdm_EventData[eventArea] && GetPlayerVirtualWorld(playerid) == tdm_EventData[eventWorld]) {

			SetPlayerPositionEx(playerid, tdm_EventData[eventPosX][evTeam[playerid]-1], tdm_EventData[eventPosY][evTeam[playerid]-1], tdm_EventData[eventPosZ][evTeam[playerid]-1]);
			SetPlayerFacingAngle(playerid, tdm_EventData[eventPosA][evTeam[playerid]-1]);

			SetCameraBehindPlayer(playerid);
			SendClientMessage(playerid, COLOR_SERVER, "WARNING: "TOMATO_1"Please don't escaping from event mode!");

			/*static Float:angle;
			GetPlayerFacingAngle(playerid, angle); // NGACO

			if (angle >= 0.0 && angle <= 45.0) {

				SetPlayerWorldBounds(playerid, 0.0, 0.0, 0.0, 20.0);
			}
			else if (angle >= 45.0 && angle <= 90.0) {

				SetPlayerWorldBounds(playerid, 20.0, 0.0, 0.0, 20.0);
			}
			else if (angle >= 90.0 && angle <= 135.0) {

				SetPlayerWorldBounds(playerid, 20.0, 0.0, 0.0, 0.0);
			}
			else if (angle >= 135.0 && angle <= 180.0) {

				SetPlayerWorldBounds(playerid, 20.0, 0.0, 20.0, 0.0);
			}
			else if (angle >= 180.0 && angle <= 225.0) {

				SetPlayerWorldBounds(playerid, 0.0, 0.0, 20.0, 0.0);
			}
			else if (angle >= 225.0 && angle <= 270.0) {

				SetPlayerWorldBounds(playerid, 0.0, 20.0, 20.0, 0.0);
			}
			else if (angle >= 270.0 && angle <= 315.0) {

				SetPlayerWorldBounds(playerid, 0.0, 20.0, 0.0, 0.0);
			}
			else if (angle >= 315.0 && angle <= 360.0) {

				SetPlayerWorldBounds(playerid, 0.0, 20.0, 0.0, 20.0);
			}*/
		}
	}
	else if (GetPVarInt(playerid, "IsAtEvent") == 4) {

		if (areaid == dm_EventData[eventArea] && GetPlayerVirtualWorld(playerid) == dm_EventData[eventWorld]) {

			SetPlayerPositionEx(playerid, dm_EventData[eventPosX], dm_EventData[eventPosY], dm_EventData[eventPosZ]);
			SetPlayerFacingAngle(playerid, dm_EventData[eventPosA]);

			SetCameraBehindPlayer(playerid);
			SendClientMessage(playerid, COLOR_SERVER, "WARNING: "TOMATO_1"Please don't escaping from event mode!");
		}
	}
    else if (GetPVarInt(playerid, "IsAtEvent") == 6) {

        if (areaid == zombie_EventData[eventArea] && GetPlayerVirtualWorld(playerid) == zombie_EventData[eventWorld]) {

			SetPlayerPositionEx(playerid, zombie_EventData[eventPosX][evTeam[playerid]-1], zombie_EventData[eventPosY][evTeam[playerid]-1], zombie_EventData[eventPosZ][evTeam[playerid]-1]);
			SetPlayerFacingAngle(playerid, zombie_EventData[eventPosA][evTeam[playerid]-1]);

			SetCameraBehindPlayer(playerid);
			SendClientMessage(playerid, COLOR_SERVER, "WARNING: "TOMATO_1"Please don't escaping from event mode!");
        }
    }
}

stock DM_ToggleAntiCheat(playerid, bool:nyala = true) {

    if (!IsPlayerConnected(playerid))
    {
        return 0;
    }
	EnableAntiCheatForPlayer(playerid, 2, nyala);
	EnableAntiCheatForPlayer(playerid, 3, nyala);
	EnableAntiCheatForPlayer(playerid, 4, nyala);
	EnableAntiCheatForPlayer(playerid, 5, nyala);
	EnableAntiCheatForPlayer(playerid, 6, nyala);
	EnableAntiCheatForPlayer(playerid, 15, nyala);
	EnableAntiCheatForPlayer(playerid, 16, false); // Android suka ke kick
	EnableAntiCheatForPlayer(playerid, 17, false); // Android suka ke kick
	EnableAntiCheatForPlayer(playerid, 18, nyala);
	EnableAntiCheatForPlayer(playerid, 19, nyala);
	EnableAntiCheatForPlayer(playerid, 20, nyala);
	EnableAntiCheatForPlayer(playerid, 21, nyala);
	EnableAntiCheatForPlayer(playerid, 27, nyala);
	EnableAntiCheatForPlayer(playerid, 28, nyala);
	EnableAntiCheatForPlayer(playerid, 29, nyala);
	EnableAntiCheatForPlayer(playerid, 30, nyala);
	EnableAntiCheatForPlayer(playerid, 35, nyala);
	//EnableAntiCheatForPlayer(playerid, 47, nyala); // Android suka ke kick

	return 1;
}

stock DM_UpdateTD() {

	foreach (new playerid : Player) {

		if (IsPlayerConnected(playerid) && GetPVarInt(playerid, "IsAtEvent") == 4) {

			PlayerTextDrawSetString(playerid, DM_TD[playerid][2], sprintf("%s", GetName(PlayerHighestEXP))); // 2, 3, 5
			PlayerTextDrawSetString(playerid, DM_TD[playerid][3], sprintf("%d", HighestEXP)); // 2, 3, 5
			PlayerTextDrawSetString(playerid, DM_TD[playerid][5], sprintf("%d", dm_EventData[eventMaxScore])); // 2, 3, 5
		}
	}
	return 1;
}

stock DM_DisplayTD(playerid, bool:buka = true) {

	if (buka) {

		forex (td, 6) PlayerTextDrawShow(playerid, DM_TD[playerid][td]);
	}
	else {

		forex (td, 6) PlayerTextDrawHide(playerid, DM_TD[playerid][td]);
	}
	return 1;
}

stock DM_GiveWeapon(playerid, weaponid, ammo) {

	if (GetPVarInt(playerid, "IsAtEvent") == 4) {

		GivePlayerWeapon(playerid, weaponid, ammo);
	}
	return 1;
}

function DM_Spawning(playerid) {

	if (GetPVarInt(playerid, "IsAtEvent") == 4) {

		if (GetPlayerVirtualWorld(playerid) != dm_EventData[eventWorld]) {

			forex (weaps, 3) DM_GiveWeapon(playerid, dm_EventData[eventWeapons][weaps], dm_EventData[eventAmmo][weaps]);
			DM_ToggleAntiCheat(playerid);

			SetPlayerVirtualWorld(playerid, dm_EventData[eventWorld]);
			SetPlayerInterior(playerid, dm_EventData[eventInterior]);
		}
	}
	return 1;
}

Dialog:DM_EventLimit(playerid, response, listitem, inputtext[]) {

	if (!response)
		return cmd_event(playerid, "info");

	if (!IsNumeric(inputtext) || IsOdd(strval(inputtext)))
		return SendErrorMessage(playerid, "Hanya karakter angka genap yang diperbolehkan!"), dialog_EventInfo(playerid, 1, 0, inputtext);
	
	if ((strval(inputtext) < 5 || strval(inputtext) > MAX_PLAYERS/2) && PlayerData[playerid][pAdmin] < 7)
		return SendErrorMessage(playerid, "Tidak dapat mengubah nilai. (5-%d)", MAX_PLAYERS/2), dialog_EventInfo(playerid, 1, 0, inputtext);

	dm_EventData[eventLimit] = strval(inputtext);
	cmd_event(playerid, "info");

	return 1;
}

Dialog:DM_EventScore(playerid, response, listitem, inputtext[]) {

	if (!response)
		return cmd_event(playerid, "info");

	if (!IsNumeric(inputtext))
		return SendErrorMessage(playerid, "Hanya karakter angka yang diperbolehkan!"), dialog_EventInfo(playerid, 1, 1, inputtext);
	
	if ((strval(inputtext) < 20 || strval(inputtext) > 100) && PlayerData[playerid][pAdmin] < 7)
		return SendErrorMessage(playerid, "Tidak dapat mengubah nilai. (20-100)"), dialog_EventInfo(playerid, 1, 1, inputtext);

	dm_EventData[eventMaxScore] = strval(inputtext);
	cmd_event(playerid, "info");

	return 1;
}

Dialog:DM_EventPrize(playerid, response, listitem, inputtext[]) {

	if (!response)
		return cmd_event(playerid, "info");

	new
		dollar, 
		cent, 
		totalamount[32];
	
	if (strfind(inputtext, ".", true) != -1)
	{
		sscanf(inputtext, "p<.>dd", dollar, cent);
		format(totalamount, sizeof(totalamount), "%d%02d", dollar, cent);

		if ((strval(totalamount) < 0 || strval(totalamount) > 50000) && PlayerData[playerid][pAdmin] < 7)
			return SendErrorMessage(playerid, "Tidak dapat mengubah nilai. ($0.00-$500.00)"), dialog_EventInfo(playerid, 1, 2, inputtext);

		dm_EventData[eventPrice] = strval(totalamount);
		cmd_event(playerid, "info");
	}
	else
	{
		sscanf(inputtext, "d", dollar);
		format(totalamount, sizeof(totalamount), "%d00", dollar);

		if ((strval(totalamount) < 0 || strval(totalamount) > 50000) && PlayerData[playerid][pAdmin] < 7)
			return SendErrorMessage(playerid, "Tidak dapat mengubah nilai. ($0.00-$500.00)"), dialog_EventInfo(playerid, 1, 2, inputtext);

		dm_EventData[eventPrice] = strval(totalamount);
		cmd_event(playerid, "info");
	}
	return 1;
}

Dialog:DM_EventEquip(playerid, response, listitem, inputtext[]) {

	if (!response)
		return SendErrorMessage(playerid, "Please select a weapon!"), cmd_event(playerid, "info");

	dm_EventData[eventWeapons][0] = arrWeapData[listitem];

	static str[512];
	format (str, sizeof(str), "Weapon Name");

	forex (id, sizeof(arrWeap))	{

		format (str, sizeof(str), "%s\n%s", str, arrWeap[id]);
	}
	Dialog_Show(playerid, DM_EventEquip1, DIALOG_STYLE_TABLIST_HEADERS, "Select a weapon 2", str, "Pick", "");

	return 1;
}

Dialog:DM_EventEquip1(playerid, response, listitem, inputtext[]) {

	if (!response)
		return SendErrorMessage(playerid, "Please select a weapon!"), cmd_event(playerid, "info");

	dm_EventData[eventWeapons][1] = arrWeapData[listitem];

	static str[512];
	format (str, sizeof(str), "Weapon Name");

	forex (id, sizeof(arrWeap))	{

		format (str, sizeof(str), "%s\n%s", str, arrWeap[id]);
	}
	Dialog_Show(playerid, DM_EventEquip2, DIALOG_STYLE_TABLIST_HEADERS, "Select a weapon 3", str, "Pick", "");

	return 1;
}

Dialog:DM_EventEquip2(playerid, response, listitem, inputtext[]) {

	if (!response)
		return SendErrorMessage(playerid, "Please select a weapon!"), cmd_event(playerid, "info");

	dm_EventData[eventWeapons][2] = arrWeapData[listitem];
	cmd_event(playerid, "info");

	return 1;
}

Dialog:DM_EventAmmo(playerid, response, listitem, inputtext[]) {

	if (!response)
		return SendErrorMessage(playerid, "Please select an amount!"), cmd_event(playerid, "info");

	dm_EventData[eventAmmo][0] = arrAmmoData[listitem];

	static str[128];
	format (str, sizeof(str), "Ammo Amount");
	format (str, sizeof(str), "%s\n50", str);
	format (str, sizeof(str), "%s\n100", str);
	format (str, sizeof(str), "%s\n150", str);
	format (str, sizeof(str), "%s\n250", str);
	format (str, sizeof(str), "%s\n350", str);
	format (str, sizeof(str), "%s\n500", str);
	Dialog_Show(playerid, DM_EventAmmo1, DIALOG_STYLE_TABLIST_HEADERS, "Select ammo 2 amount", str, "Pick", "");	

	return 1;
}

Dialog:DM_EventAmmo1(playerid, response, listitem, inputtext[]) {

	if (!response)
		return SendErrorMessage(playerid, "Please select an amount!"), cmd_event(playerid, "info");

	dm_EventData[eventAmmo][1] = arrAmmoData[listitem];

	static str[128];
	format (str, sizeof(str), "Ammo Amount");
	format (str, sizeof(str), "%s\n50", str);
	format (str, sizeof(str), "%s\n100", str);
	format (str, sizeof(str), "%s\n150", str);
	format (str, sizeof(str), "%s\n250", str);
	format (str, sizeof(str), "%s\n350", str);
	format (str, sizeof(str), "%s\n500", str);
	Dialog_Show(playerid, DM_EventAmmo2, DIALOG_STYLE_TABLIST_HEADERS, "Select ammo 3 amount", str, "Pick", "");	

	return 1;
}

Dialog:DM_EventAmmo2(playerid, response, listitem, inputtext[]) {

	if (!response)
		return SendErrorMessage(playerid, "Please select an amount!"), cmd_event(playerid, "info");

	dm_EventData[eventAmmo][2] = arrAmmoData[listitem];
	cmd_event(playerid, "info");

	return 1;
}

ptask DM_EventCountdown[1000](playerid) {

	if (GetPVarInt(playerid, "IsAtEvent") == 4) {

		if (dm_EventData[eventCD][playerid] > 0) {

			dm_EventData[eventCD][playerid] --;

			GameTextForPlayer(playerid, sprintf("~w~event dimulai dalam~n~%d detik", dm_EventData[eventCD][playerid]), 1000, 6);
			PlayerPlaySound(playerid, 1056, 0, 0, 0);

			if (!dm_EventData[eventCD][playerid]) {

				EventStarted = 1;
				dm_EventData[eventArea] = CreateDynamicSphere(dm_EventData[eventPosX], dm_EventData[eventPosY], dm_EventData[eventPosZ], 200, dm_EventData[eventWorld], dm_EventData[eventInterior], -1);

				GameTextForPlayer(playerid, "", 0, 6);
				SendClientMessage(playerid, COLOR_SERVER, "EVENT: "YELLOW"Event dimulai!");

				PlayerTextDrawSetString(playerid, DM_TD[playerid][2], "");
				PlayerTextDrawSetString(playerid, DM_TD[playerid][3], "");
				PlayerTextDrawSetString(playerid, DM_TD[playerid][5], sprintf("%d", dm_EventData[eventMaxScore]));

				forex (weaps, 3) DM_GiveWeapon(playerid, dm_EventData[eventWeapons][weaps], dm_EventData[eventAmmo][weaps]);
				SetPlayerVirtualWorld(playerid, dm_EventData[eventWorld]);

				SetPlayerHealth(playerid, 100.0);
				DM_DisplayTD(playerid);
			}
		}
	}
}

// Event Parachute

hook OnPlayerEnterRaceCP(playerid) {

	if (GetPVarInt(playerid, "IsAtEvent") == 1 && EventType == 1) {

		evRaceCP[playerid] ++;

		switch (evRaceCP[playerid]) {

			case 19: {

				PlayerPlaySound(playerid, 1058, 0, 0, 0);
				SetPlayerRaceCheckpoint(playerid, 1, race_CPInfo[SelectedRaceMap][evRaceCP[playerid]][cpRace][0], race_CPInfo[SelectedRaceMap][evRaceCP[playerid]][cpRace][1], race_CPInfo[SelectedRaceMap][evRaceCP[playerid]][cpRace][2], 0, 0, 0, 10.0);
			}
			case 20: {

				race_EventData[evWinner] ++;

				switch (race_EventData[evWinner]) {

					case 1: {

						GiveMoney(playerid, race_EventData[evPrice]+1000000),
						SendEventMessage(EventType, COLOR_SERVER, "EVENT: "GREEN"%s "YELLOW"telah mencapai garis finish "RED"1st | {009000}$%s", GetName(playerid), FormatNumber(race_EventData[evPrice]+1000000));
					}
					case 2: {

						GiveMoney(playerid, race_EventData[evPrice]+5000),
						SendEventMessage(EventType, COLOR_SERVER, "EVENT: "GREEN"%s "YELLOW"telah mencapai garis finish "RED"2nd | {009000}$%s", GetName(playerid), FormatNumber(race_EventData[evPrice]+5000));
					}
					case 3: {

						race_EventData[evTime] = 30;

						GiveMoney(playerid, race_EventData[evPrice]+3000),
						SendEventMessage(EventType, COLOR_SERVER, "EVENT: "GREEN"%s "YELLOW"telah mencapai garis finish "RED"3rd | {009000}$%s", GetName(playerid), FormatNumber(race_EventData[evPrice]+3000));
					}
					case 4: {

						GiveMoney(playerid, race_EventData[evPrice]+2000),
						SendEventMessage(EventType, COLOR_SERVER, "EVENT: "GREEN"%s "YELLOW"telah mencapai garis finish "RED"4th | {009000}$%s", GetName(playerid), FormatNumber(race_EventData[evPrice]+2000));
					}
					case 5: {

						GiveMoney(playerid, race_EventData[evPrice]+1000),
						SendEventMessage(EventType, COLOR_SERVER, "EVENT: "GREEN"%s "YELLOW"telah mencapai garis finish "RED"5th | {009000}$%s", GetName(playerid), FormatNumber(race_EventData[evPrice]+1000));
					}
					default: {

						GiveMoney(playerid, race_EventData[evPrice]),
						SendEventMessage(EventType, COLOR_SERVER, "EVENT: "GREEN"%s "YELLOW"telah mencapai garis finish!", GetName(playerid));
					}
				}
				TogglePlayerSpectating(playerid, 1);
				SetTimerEx("Event_RespawnPlayer", 4000, false, "d", playerid);

				evRaceCP[playerid] = -1;
				if (IsValidVehicle(evCar[playerid]))
					Vehicle_Delete(evCar[playerid], false);

				SetPlayerColor(playerid, COLOR_DEFAULT);
				SetCameraBehindPlayer(playerid);
				SetPlayerPositionEx(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);
				SetPlayerHealth(playerid, PlayerData[playerid][pHealth]);
				SetPlayerArmour(playerid, PlayerData[playerid][pArmor]);
				SetPlayerVirtualWorld(playerid, PlayerData[playerid][pWorld]);
				SetPlayerInterior(playerid, PlayerData[playerid][pInterior]);
				SetPlayerSkin(playerid, PlayerData[playerid][pSkin]);

				if (PlayerData[playerid][pOnDuty]) {

					SetFactionColor(playerid);
					SetPlayerSkin(playerid, PlayerData[playerid][pFactionSkin]);
				}

				ResetPlayerMoney(playerid);
				GivePlayerMoney(playerid, GetMoney(playerid));
				ResetPlayerWeapons(playerid);
				SetWeapons(playerid);
				DisableRemoteVehicleCollisions(playerid, 0);
				DisablePlayerRaceCheckpoint(playerid);
				SetPVarInt(playerid, "IsAtEvent", -1);
			}
			default: {

				PlayerPlaySound(playerid, 1058, 0, 0, 0);
				SetPlayerRaceCheckpoint(playerid, 0, race_CPInfo[SelectedRaceMap][evRaceCP[playerid]][cpRace][0], race_CPInfo[SelectedRaceMap][evRaceCP[playerid]][cpRace][1], race_CPInfo[SelectedRaceMap][evRaceCP[playerid]][cpRace][2], race_CPInfo[SelectedRaceMap][evRaceCP[playerid]+1][cpRace][0], race_CPInfo[SelectedRaceMap][evRaceCP[playerid]+1][cpRace][1], race_CPInfo[SelectedRaceMap][evRaceCP[playerid]+1][cpRace][2], 10.0);
			}
		}
	}
	else if (GetPVarInt(playerid, "IsAtEvent") == 5 && EventType == 5) {

		parachute_EventData[eventWinner] ++;

		foreach (new id : Player) {

			if (GetPVarInt(id, "IsAtEvent") == 5) {

				parachute_EventData[eventCD][id] = 35;
			}
		}
		switch (parachute_EventData[eventWinner]) {

			case 1: {

				GiveMoney(playerid, parachute_EventData[eventWinnerPrice]);
				SendClientMessageEx(playerid, COLOR_SERVER, "EVENT: "YELLOW"You have earned {009000}$%s "YELLOW"for participate this mode!", FormatNumber(parachute_EventData[eventWinnerPrice]));
				SendEventMessage(EventType, COLOR_SERVER, "EVENT: "PURPLE"%s "YELLOW"has finish at {009000}%dst "YELLOW"on checkpoint destination.", GetName(playerid), parachute_EventData[eventWinner]);
			}
			case 2: {

				GiveMoney(playerid, parachute_EventData[eventWinnerPrice]-2500);
				SendClientMessageEx(playerid, COLOR_SERVER, "EVENT: "YELLOW"You have earned {009000}$%s "YELLOW"for participate this mode!", FormatNumber(parachute_EventData[eventWinnerPrice]-2500));
				SendEventMessage(EventType, COLOR_SERVER, "EVENT: "PURPLE"%s "YELLOW"has finish at {009000}%dnd "YELLOW"on checkpoint destination.", GetName(playerid), parachute_EventData[eventWinner]);
			}
			case 3: {

				GiveMoney(playerid, parachute_EventData[eventWinnerPrice]-5000);
				SendClientMessageEx(playerid, COLOR_SERVER, "EVENT: "YELLOW"You have earned {009000}$%s "YELLOW"for participate this mode!", FormatNumber(parachute_EventData[eventWinnerPrice]-5000));
				SendEventMessage(EventType, COLOR_SERVER, "EVENT: "PURPLE"%s "YELLOW"has finish at {009000}%drd "YELLOW"on checkpoint destination.", GetName(playerid), parachute_EventData[eventWinner]);
			}
			default: {

				GiveMoney(playerid, parachute_EventData[eventPrice]);
				SendClientMessageEx(playerid, COLOR_SERVER, "EVENT: "YELLOW"You have earned {009000}$%s "YELLOW"for participate this mode!", FormatNumber(parachute_EventData[eventPrice]));
				SendEventMessage(EventType, COLOR_SERVER, "EVENT: "PURPLE"%s "YELLOW"has finish at {009000}%dth "YELLOW"on checkpoint destination.", GetName(playerid), parachute_EventData[eventWinner]);
			}
		}
		TogglePlayerSpectating(playerid, 1);
		SetTimerEx("Event_RespawnPlayer", 4000, false, "d", playerid);

		Parachute_ToggleAntiCheat(playerid, false);

		SetPlayerColor(playerid, COLOR_DEFAULT);
		SetCameraBehindPlayer(playerid);
		SetPlayerPositionEx(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);
		SetPlayerHealth(playerid, PlayerData[playerid][pHealth]);
		SetPlayerArmour(playerid, PlayerData[playerid][pArmor]);
		SetPlayerVirtualWorld(playerid, PlayerData[playerid][pWorld]);
		SetPlayerInterior(playerid, PlayerData[playerid][pInterior]);
		SetPlayerSkin(playerid, PlayerData[playerid][pSkin]);

		if (PlayerData[playerid][pOnDuty]) {

			SetFactionColor(playerid);
			SetPlayerSkin(playerid, PlayerData[playerid][pFactionSkin]);
		}

		ResetPlayerMoney(playerid);
		GivePlayerMoney(playerid, PlayerData[playerid][pMoney]);
		ResetPlayerWeapons(playerid);
		SetWeapons(playerid);
		SetPVarInt(playerid, "IsAtEvent", -1);
	}
}

stock Parachute_Attach(playerid) {

	if (GetPVarInt(playerid, "IsAtEvent") == 5) {

		GivePlayerWeapon(playerid, WEAPON_PARACHUTE, 1);
	}
	return 1;
}

stock Parachute_ToggleAntiCheat(playerid, bool:nyala = true) {

    if (!IsPlayerConnected(playerid))
    {
        return 0;
    }
    forex (ac, 13) {

    	EnableAntiCheatForPlayer(playerid, ac, nyala);
    }
	return 1;
}

Dialog:Parachute_EventLimit(playerid, response, listitem, inputtext[]) {

	if (!response)
		return cmd_event(playerid, "info");

	if (!IsNumeric(inputtext))
		return SendErrorMessage(playerid, "Hanya karakter angka yang diperbolehkan!"), dialog_EventInfo(playerid, 1, 0, inputtext);
	
	if ((strval(inputtext) < 5 || strval(inputtext) > MAX_PLAYERS/2) && PlayerData[playerid][pAdmin] < 7)
		return SendErrorMessage(playerid, "Tidak dapat mengubah nilai. (5-%d)", MAX_PLAYERS/2), dialog_EventInfo(playerid, 1, 0, inputtext);

	parachute_EventData[eventLimit] = strval(inputtext);
	cmd_event(playerid, "info");

	return 1;
}

Dialog:Parachute_EventPrize(playerid, response, listitem, inputtext[]) {

	if (!response)
		return cmd_event(playerid, "info");

	new
		dollar, 
		cent, 
		totalamount[32];


	if (!IsNumeric(inputtext))
		return SendErrorMessage(playerid, "Hanya karakter angka yang diperbolehkan!"), dialog_EventInfo(playerid, 1, 1, inputtext);
	
	if (strfind(inputtext, ".", true) != -1)
	{
		sscanf(inputtext, "p<.>dd", dollar, cent);
		format(totalamount, sizeof(totalamount), "%d%02d", dollar, cent);

		if ((strval(totalamount) < 5000 || strval(totalamount) > 50000) && PlayerData[playerid][pAdmin] < 7)
			return SendErrorMessage(playerid, "Tidak dapat mengubah nilai. ($50.00-$500.00)"), dialog_EventInfo(playerid, 1, 1, inputtext);

		parachute_EventData[eventPrice] = strval(totalamount);
		cmd_event(playerid, "info");
	}
	else
	{
		sscanf(inputtext, "d", dollar);
		format(totalamount, sizeof(totalamount), "%d00", dollar);

		if ((strval(totalamount) < 5000 || strval(totalamount) > 50000) && PlayerData[playerid][pAdmin] < 7)
			return SendErrorMessage(playerid, "Tidak dapat mengubah nilai. ($50.00-$500.00)"), dialog_EventInfo(playerid, 1, 1, inputtext);

		parachute_EventData[eventPrice] = strval(totalamount);
		cmd_event(playerid, "info");
	}
	return 1;
}

Dialog:Parachute_EvWinnerPrize(playerid, response, listitem, inputtext[]) {

	if (!response)
		return cmd_event(playerid, "info");

	new
		dollar, 
		cent, 
		totalamount[32];
	
	if (strfind(inputtext, ".", true) != -1)
	{
		sscanf(inputtext, "p<.>dd", dollar, cent);
		format(totalamount, sizeof(totalamount), "%d%02d", dollar, cent);

		if ((strval(totalamount) < 5000 || strval(totalamount) > parachute_EventData[eventPrice]))
			return SendErrorMessage(playerid, "Tidak dapat mengubah nilai. ($50.00-$%s)", FormatNumber(parachute_EventData[eventPrice])), dialog_EventInfo(playerid, 1, 2, inputtext);

		parachute_EventData[eventWinnerPrice] = strval(totalamount);
		cmd_event(playerid, "info");
	}
	else
	{
		sscanf(inputtext, "d", dollar);
		format(totalamount, sizeof(totalamount), "%d00", dollar);

		if ((strval(totalamount) < 5000 || strval(totalamount) > parachute_EventData[eventPrice]))
			return SendErrorMessage(playerid, "Tidak dapat mengubah nilai. ($50.00-$%s)", FormatNumber(parachute_EventData[eventPrice])), dialog_EventInfo(playerid, 1, 2, inputtext);

		parachute_EventData[eventWinnerPrice] = strval(totalamount);
		cmd_event(playerid, "info");
	}
	return 1;
}

Dialog:Parachute_EventFlyFrom(playerid, response, listitem, inputtext[]) {

	if (!response)
		return cmd_event(playerid, "info");

	if (!listitem)
		return SendErrorMessage(playerid, "Please select a valid fly spawn point!"), dialog_EventInfo(playerid, 1, 3, inputtext);

	parachute_EventData[eventSelectPos] = listitem;

	SetPlayerPositionEx(playerid, arrFlyFrom[parachute_EventData[eventSelectPos]][0], arrFlyFrom[parachute_EventData[eventSelectPos]][1], arrFlyFrom[parachute_EventData[eventSelectPos]][2]);
	SetPlayerFacingAngle(playerid, arrFlyFrom[parachute_EventData[eventSelectPos]][3]);

	SendClientMessageEx(playerid, COLOR_SERVER, "EVENT: "WHITE"Teleported to "CYAN1"%s", arrFlyData[parachute_EventData[eventSelectPos]]);
	cmd_event(playerid, "info");

	return 1;
}

ptask Parachute_EventCountdown[1000](playerid) 
{
	if (GetPVarInt(playerid, "IsAtEvent") == 5) {

		if (parachute_EventData[eventCD][playerid] > 0 && (!parachute_EventData[eventWinner])) {

			parachute_EventData[eventCD][playerid] --;

			GameTextForPlayer(playerid, sprintf("~w~event dimulai dalam~n~%d detik", parachute_EventData[eventCD][playerid]), 1000, 6);
			PlayerPlaySound(playerid, 1056, 0, 0, 0);

			if (!parachute_EventData[eventCD][playerid]) {

				EventStarted = 1;
				PlayerPlaySound(playerid, 1057, 0, 0, 0);

				GameTextForPlayer(playerid, "Go!", 500, 6);
				SendClientMessage(playerid, COLOR_SERVER, "EVENT: "YELLOW"Event dimulai!");

				TogglePlayerControllable(playerid, 1);
				Parachute_ToggleAntiCheat(playerid);

				SetPlayerVirtualWorld(playerid, parachute_EventData[eventWorld]);
				SetPlayerInterior(playerid, parachute_EventData[eventInterior]);

				SendClientMessage(playerid, COLOR_SERVER, "HINT: "WHITE"Lompat kearah landing checkpoint yang sudah disediakan untuk menjadi pemenang!");
				SetPlayerRaceCheckpoint(playerid, 1, parachute_EventData[eventLandingX], parachute_EventData[eventLandingY], parachute_EventData[eventLandingZ], 0, 0, 0, 50);
			}
		}
		else if (parachute_EventData[eventWinner] > 0) {

			parachute_EventData[eventCD][playerid] --;

			GameTextForPlayer(playerid, sprintf("~w~event berakhir dalam~n~%d detik", parachute_EventData[eventCD][playerid]), 1000, 6);
			PlayerPlaySound(playerid, 1056, 0, 0, 0);

			if (!parachute_EventData[eventCD][playerid]) {

				GameTextForPlayer(playerid, "", 0, 6);
				SendClientMessageEx(playerid, COLOR_SERVER, "EVENT: "WHITE"Event telah berakhir dan kamu mendapatkan hadiah sebesar {009000}$%s", FormatNumber(parachute_EventData[eventPrice]));

				TogglePlayerSpectating(playerid, 1);
				SetTimerEx("Event_RespawnPlayer", 3000, false, "d", playerid);

				SetPlayerColor(playerid, COLOR_DEFAULT);
				SetPVarInt(playerid, "IsAtEvent", -1);

				if (PlayerData[playerid][pOnDuty])
					SetFactionColor(playerid);

				ResetPlayerMoney(playerid);
				GivePlayerMoney(playerid, GetMoney(playerid));
			}
		}
	}
}

task Parachute_EventTimerCheck[1000]() 
{
	if (EventStarted && (EventType == 5)) {

		if (!parachute_EventData[eventEntry]) {

			Event_ForceEnd();
		}
	}
}

// Event Race

hook OnPlayerStateChange(playerid, newstate, oldstate) {

	if ((GetPVarInt(playerid, "IsAtEvent") > 0) && (oldstate == PLAYER_STATE_DRIVER)) {

		if (GetPVarInt(playerid, "IsAtEvent") == 1) {

			SendEventMessage(EventType, COLOR_SERVER, "EVENT: "RED"%s "YELLOW"has been disqualified.", GetName(playerid));

			TogglePlayerSpectating(playerid, 1);
			SetTimerEx("Event_RespawnPlayer", 4000, false, "d", playerid);

			evRaceCP[playerid] = -1;
			if (IsValidVehicle(evCar[playerid]))
				Vehicle_Delete(evCar[playerid], false);

			SetPlayerColor(playerid, COLOR_DEFAULT);
			SetCameraBehindPlayer(playerid);
			SetPlayerPositionEx(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);
			SetPlayerHealth(playerid, PlayerData[playerid][pHealth]);
			SetPlayerArmour(playerid, PlayerData[playerid][pArmor]);
			SetPlayerVirtualWorld(playerid, PlayerData[playerid][pWorld]);
			SetPlayerInterior(playerid, PlayerData[playerid][pInterior]);
			SetPlayerSkin(playerid, PlayerData[playerid][pSkin]);

			if (PlayerData[playerid][pOnDuty]) {

				SetFactionColor(playerid);
				SetPlayerSkin(playerid, PlayerData[playerid][pFactionSkin]);
			}

			ResetPlayerMoney(playerid);
			GivePlayerMoney(playerid, GetMoney(playerid));
			ResetPlayerWeapons(playerid);
			SetWeapons(playerid);
			DisableRemoteVehicleCollisions(playerid, 0);
			DisablePlayerRaceCheckpoint(playerid);
			SetPVarInt(playerid, "IsAtEvent", -1);
		}
	}
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {

	if (strcmp(EventHost, "null", true) && (EventType == 1)) {

		if (newkeys & KEY_FIRE) {

			new Float:x, Float:y, Float:z, str[1024];
			GetPlayerPos(playerid, x, y, z);

			if (GetPVarInt(playerid, "EditRaceCP") > 0) {

				new id = SelectedRaceMapEx;
				Race_EventCP_Add(x, y, z, id);

				format (str, sizeof(str), "#\tCoordinates\tLocation");

				foreach (new idx : RacesCP<id>) if (Iter_Contains(RacesCP<id>, idx)) {

					format (str, sizeof(str), "%s\nCP:%d\t%.2f, %.2f, %.2f\t%s", str, idx+1, race_CPInfo[id][idx][cpRace][0], race_CPInfo[id][idx][cpRace][1], race_CPInfo[id][idx][cpRace][2], GetLocation(race_CPInfo[id][idx][cpRace][0], race_CPInfo[id][idx][cpRace][1], race_CPInfo[id][idx][cpRace][2]));
				}
				if (Iter_Count(RacesCP<id>) < 20) {

					format (str, sizeof(str), "%s\nCP:-\t<< New checkpoint >>\tSan ANdreas", str);
				}
				Dialog_Show(playerid, Race_CreateCP, DIALOG_STYLE_TABLIST_HEADERS, "Create Race Map", str, "Move", "Save");

				DeletePVar(playerid, "EditRaceCP");
				SendClientMessage(playerid, COLOR_SERVER, "EVENT: "WHITE"Posisi checkpoint telah ditambahkan ke dalam posisi mu saat ini!");
			}
			else if (GetPVarInt(playerid, "EditRaceCP") == -1) {

				new listitem = GetPVarInt(playerid, "EditRaceListitem");

				race_CPInfo[SelectedRaceMapEx][listitem][cpRace] = x;
				race_CPInfo[SelectedRaceMapEx][listitem][cpRace] = y;
				race_CPInfo[SelectedRaceMapEx][listitem][cpRace] = z;

				format (str, sizeof(str), "#\tCoordinates\tLocation");

				foreach (new idx : RacesCP<SelectedRaceMapEx>) if (Iter_Contains(RacesCP<SelectedRaceMapEx>, idx)) {

					format (str, sizeof(str), "%s\nCP:%d\t%.2f, %.2f, %.2f\t%s", str, idx+1, race_CPInfo[SelectedRaceMapEx][idx][cpRace][0], race_CPInfo[SelectedRaceMapEx][idx][cpRace][1], race_CPInfo[SelectedRaceMapEx][idx][cpRace][2], GetLocation(race_CPInfo[SelectedRaceMapEx][idx][cpRace][0], race_CPInfo[SelectedRaceMapEx][idx][cpRace][1], race_CPInfo[SelectedRaceMapEx][idx][cpRace][2]));
				}
				if (Iter_Count(RacesCP<SelectedRaceMapEx>) < 20) {

					format (str, sizeof(str), "%s\nCP:-\t<< New checkpoint >>\tSan ANdreas", str);
				}
				Dialog_Show(playerid, Race_CreateCP, DIALOG_STYLE_TABLIST_HEADERS, "Create Race Map", str, "Move", "Save");

				DeletePVar(playerid, "EditRaceCP");
				DeletePVar(playerid, "EditRaceListitem");

				SendClientMessage(playerid, COLOR_SERVER, "EVENT: "WHITE"Posisi checkpoint telah diganti ke posisi mu saat ini!");
			}
		}
	}
    else if (GetPVarInt(playerid, "IsAtEvent") == 3) {

        if ((newkeys & KEY_FIRE || newkeys & KEY_SECONDARY_ATTACK) && tdm_EventData[eventCD][playerid] > 0 && !EventStarted) {

			ClearAnimations(playerid, 1);
            TogglePlayerControllable(playerid, 1);

            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
			SendErrorMessage(playerid, "Please don't punching your teammate until event is started!");
        }
    }
    else if (GetPVarInt(playerid, "IsAtEvent") == 6) {

        if ((newkeys & KEY_FIRE || newkeys & KEY_SECONDARY_ATTACK) && zombie_EventData[eventCD][playerid] > 0 && !EventStarted) {

			ClearAnimations(playerid, 1);
            TogglePlayerControllable(playerid, 1);

            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
			SendErrorMessage(playerid, "Please don't punching your teammate until event is started!");
        }
    }
}

Race_Event_Add(const name[], const publisher[])
{
	new index = Iter_Free(RacesMap);

	if (index != cellmin)
	{
		Iter_Add(RacesMap, index);

		format (race_CPData[index][cpName], 64, name);
		format (race_CPData[index][cpPublisher], MAX_PLAYER_NAME, publisher);
		format (race_CPData[index][cpLastUsed], 32, "N/A");

		race_CPData[index][cpDistance] = 0.0;
		mysql_tquery(sqlcon, "INSERT INTO racemap (Distance) VALUES (0.0)", "Race_Event_Executed", "d", index);

		return index;
	}
	return cellmin;
}

Race_Event_Delete(index) {

	if (Iter_Contains(RacesMap, index)) {

		mysql_tquery(sqlcon, sprintf("DELETE FROM racemap WHERE MapIndex = '%d'", race_CPData[index][cpIndex]));

		race_CPData[index][cpDistance] = 0;
		Iter_Remove(RacesMap, index);
	}
	return 0;
}

Race_Event_Save(id) {

	static query[128];

	mysql_format (sqlcon, query, sizeof(query),
	
		"UPDATE racemap SET Name = '%e', LastUsed = '%e', Publisher = '%e', Distance = '%.2f' WHERE MapIndex = '%d'",
		race_CPData[id][cpName],
		race_CPData[id][cpLastUsed],
		race_CPData[id][cpPublisher],
		race_CPData[id][cpDistance],
		race_CPData[id][cpIndex]
	);
	return mysql_tquery(sqlcon, query);
}

function Race_Event_Executed(id) {

	if (Iter_Contains(RacesMap, id)) {

		race_CPData[id][cpIndex] = cache_insert_id();
		Race_Event_Save(id);
	}
	return 1;
}

function Race_Event_Load() {

	if (cache_num_rows()) {

		forex (id, cache_num_rows()) {

			Iter_Add(RacesMap, id);

			race_CPData[id][cpIndex] = cache_get_field_int(id, "MapIndex");
			race_CPData[id][cpDistance] = cache_get_field_float(id, "Distance");

			cache_get_field_content(id, "Name", race_CPData[id][cpName], 64);
			cache_get_field_content(id, "LastUsed", race_CPData[id][cpLastUsed], 32);
			cache_get_field_content(id, "Publisher", race_CPData[id][cpPublisher], MAX_PLAYER_NAME);

			Iter_Init(RacesCP<id>);
			mysql_tquery(sqlcon, sprintf("SELECT * FROM `racecp` WHERE `MapIndex` = '%d'", race_CPData[id][cpIndex]), "Race_EventCP_Load", "d", id);
		}
		printf("[EventMode] Loaded %d race mode maps.", Iter_Count(RacesMap));
	}
	return 1;
}

Race_EventCP_Add(Float:x, Float:y, Float:z, id) {

	new idx = Iter_Free(RacesCP<id>);

	if (idx != cellmin) {

		Iter_Add(RacesCP<id>, idx);

		race_CPInfo[id][idx][cpRace][0] = x;
		race_CPInfo[id][idx][cpRace][1] = y;
		race_CPInfo[id][idx][cpRace][2] = z;

		mysql_tquery(sqlcon, sprintf("INSERT INTO racecp (MapIndex) VALUES (%d)", race_CPData[id][cpIndex]), "Race_EventCP_Executed", "dd", id, idx);

		return idx;
	}
	return cellmin;
}

Race_EventCP_Save(id) {

	new str[512];
	foreach (new cp : RacesCP<id>) if (Iter_Contains(RacesCP<id>, cp)) {

		mysql_format(sqlcon, str, sizeof(str), "UPDATE racecp SET");
		mysql_format(sqlcon, str, sizeof(str), "%s cpRaceX = '%.2f',", str, race_CPInfo[id][cp][cpRace][0]);
		mysql_format(sqlcon, str, sizeof(str), "%s cpRaceY = '%.2f',", str, race_CPInfo[id][cp][cpRace][1]);
		mysql_format(sqlcon, str, sizeof(str), "%s cpRaceZ = '%.2f'", str, race_CPInfo[id][cp][cpRace][2]);
		mysql_format(sqlcon, str, sizeof(str), "%s WHERE MapIndex = '%d'", str, race_CPData[id][cpIndex]);
		mysql_format(sqlcon, str, sizeof(str), "%s AND ID = '%d'", str, race_CPInfo[id][cp][cpIndex]);
	}
	return mysql_tquery(sqlcon, str);
}

function Race_EventCP_Load(id) {

	if (cache_num_rows()) {

		forex (cp, cache_num_rows()) {

			Iter_Add(RacesCP<id>, cp);

			race_CPInfo[id][cp][cpIndex] = cache_get_field_int(cp, "ID");
			race_CPInfo[id][cp][cpRace][0] = cache_get_field_float(cp, "cpRaceX");
			race_CPInfo[id][cp][cpRace][1] = cache_get_field_float(cp, "cpRaceY");
			race_CPInfo[id][cp][cpRace][2] = cache_get_field_float(cp, "cpRaceZ");
		}
	}
	return 1;
}

function Race_EventCP_Executed(id, idx) {

	if (Iter_Contains(RacesCP<id>, idx)) {

		race_CPInfo[id][idx][cpIndex] = cache_insert_id();
		Race_EventCP_Save(id);
	}
	return 1;
}

CMD:flipback(playerid, params[])
{
	if(!GetPVarInt(playerid, "IsAtEvent"))
		return 1;

	FlipVehicle(GetPlayerVehicleID(playerid));

	return 1;
}

Dialog:Race_EventLimit(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		new input = strval(inputtext);

		if (!IsNumeric(inputtext))
			return SendErrorMessage(playerid, "Hanya karakter angka yang diperbolehkan!"), dialog_EventInfo(playerid, 1, 0, "\1");
	
		if ((input < 2 || input > 50) && PlayerData[playerid][pAdmin] < 7)
			return SendErrorMessage(playerid, "Tidak dapat mengubah nilai. (2-50)"), dialog_EventInfo(playerid, 1, 0, "\1");

		race_EventData[evLimit] = input;
		cmd_event(playerid, "info");
	}
	else cmd_event(playerid, "info");

	return 1;
}

Dialog:Race_EventPrice(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		new
			dollar, 
			cent, 
			totalamount[32];

		if (strfind(inputtext, ".", true) != -1)
		{
			sscanf(inputtext, "p<.>dd", dollar, cent);
			format(totalamount, sizeof(totalamount), "%d%02d", dollar, cent);

			if ((strval(totalamount) < 0 || strval(totalamount) > 50000) && PlayerData[playerid][pAdmin] < 7)
				return SendErrorMessage(playerid, "Tidak dapat mengubah nilai. ($0.00-$500.00)"), dialog_EventInfo(playerid, 1, 1, "\1");

			race_EventData[evPrice] = strval(totalamount);
			cmd_event(playerid, "info");
		}
		else
		{
			sscanf(inputtext, "d", dollar);
			format(totalamount, sizeof(totalamount), "%d00", dollar);

			if ((strval(totalamount) < 0 || strval(totalamount) > 50000) && PlayerData[playerid][pAdmin] < 7)
				return SendErrorMessage(playerid, "Tidak dapat mengubah nilai. ($0.00-$500.00)"), dialog_EventInfo(playerid, 1, 1, "\1");

			race_EventData[evPrice] = strval(totalamount);
			cmd_event(playerid, "info");
		}	
	}
	else cmd_event(playerid, "info");

	return 1;
}

Dialog:Race_EventModel(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		new input = strval(inputtext);

		if (!IsNumeric(inputtext))
			return SendErrorMessage(playerid, "Hanya karakter angka yang diperbolehkan!"), dialog_EventInfo(playerid, 1, 2, "\1");
	
		if ((input < 400 || input > 611))
			return SendErrorMessage(playerid, "Tidak dapat mengubah nilai. (400-611)"), dialog_EventInfo(playerid, 1, 2, "\1");

		race_EventData[evModel] = input;
		cmd_event(playerid, "info");
	}
	else cmd_event(playerid, "info");

	return 1;
}

Dialog:Race_EventTime(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		new input = strval(inputtext);

		if (!IsNumeric(inputtext))
			return SendErrorMessage(playerid, "Hanya karakter angka yang diperbolehkan!"), dialog_EventInfo(playerid, 1, 4, "\1");
	
		if ((input < 5 || input > 20) && PlayerData[playerid][pAdmin] < 7)
			return SendErrorMessage(playerid, "Tidak dapat mengubah nilai. (5-20 [menit])"), dialog_EventInfo(playerid, 1, 4, "\1");

		race_EventData[evTime] = (input * 60);
		cmd_event(playerid, "info");
	}
	else cmd_event(playerid, "info");

	return 1;
}
/*
Dialog:Race_EventCP(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		new count = 0;

		forex (i, 20)
		{
			if (count == listitem)
			{
				new Float:x, Float:y, Float:z;

				if (!race_CPData[i][cpExists])
				{
					GetPlayerPos(playerid, x, y, z);
					Race_EventCP_Add(x, y, z);

					dialog_EventInfo(playerid, 1, 5, "\1");
					SendClientMessage(playerid, COLOR_SERVER, "EVENT: "WHITE"Posisi checkpoint telah ditambahkan ke dalam posisi mu saat ini!");
				}
				else
				{
					GetPlayerPos(playerid, x, y, z);

					race_CPData[i][cpRace][0] = x;
					race_CPData[i][cpRace][1] = y;
					race_CPData[i][cpRace][2] = z;

					dialog_EventInfo(playerid, 1, 5, "\1");
					SendClientMessage(playerid, COLOR_SERVER, "EVENT: "WHITE"Posisi checkpoint telah diganti ke posisi mu saat ini!");
				}
				break;
			}
			else count ++;
		}
	}
	else cmd_event(playerid, "info");

	return 1;
}*/

Dialog:Race_CreateMap(playerid, response, listitem, inputtext[]) {

	if (!response)
		return cmd_event(playerid, "info");

	if (isnull(inputtext) || strlen(inputtext) > 64)
		return dialog_EventInfo(playerid, 1, 5, "\0");

	static id = cellmin, str[1024];
	id = Race_Event_Add(inputtext, PlayerData[playerid][pUCP]);

	if (id != cellmin) {

		format (str, sizeof(str), "#\tCoordinates\tLocation");

		foreach (new idx : RacesCP<id>) if (Iter_Contains(RacesCP<id>, idx)) {

			format (str, sizeof(str), "%s\nCP:%d\t%.2f, %.2f, %.2f\t%s", str, idx+1, race_CPInfo[id][idx][cpRace][0], race_CPInfo[id][idx][cpRace][1], race_CPInfo[id][idx][cpRace][2], GetLocation(race_CPInfo[id][idx][cpRace][0], race_CPInfo[id][idx][cpRace][1], race_CPInfo[id][idx][cpRace][2]));
		}
		if (Iter_Count(RacesCP<id>) < 20) {

			format (str, sizeof(str), "%s\nCP:-\t<< New checkpoint >>\tSan ANdreas", str);
		}
		SelectedRaceMapEx = id;

		Dialog_Show(playerid, Race_CreateCP, DIALOG_STYLE_TABLIST_HEADERS, "Create Race Map", str, "Move", "Save");
		SendClientMessage(playerid, COLOR_SERVER, "WARNING: "YELLOW"Checkpoint harus 20 baris untuk melakukan saving!");
	}
	else SendErrorMessage(playerid, "Unable to create a map, an error has occured!"), cmd_event(playerid, "info");

	return 1;
}

Dialog:Race_CreateCP(playerid, response, listitem, inputtext[]) {

	if (!response) {

		new id = SelectedRaceMapEx;

		if (Iter_Count(RacesCP<id>) < 20)
			return SendErrorMessage(playerid, "Checkpoint harus diatas 20 sebelum membuat map!"), Race_Event_Delete(id), cmd_event(playerid, "info");

		Race_EventCP_Save(id);
		race_CPData[id][cpDistance] = GetPlayerDistanceFromPoint(playerid, race_CPInfo[id][0][cpRace][0], race_CPInfo[id][0][cpRace][1], race_CPInfo[id][0][cpRace][2]);

		cmd_event(playerid, "info");
		SendClientMessage(playerid, COLOR_SERVER, "EVENT: "YELLOW"Map created!");

		SelectedRaceMapEx = -1;
	}
	else {

		new Float:x, Float:y, Float:z;
		GetPlayerPos(playerid, x, y, z);

		if (Iter_Contains(RacesCP<SelectedRaceMapEx>, listitem)) {

			SetPVarInt(playerid, "EditRaceCP", -1);
			SetPVarInt(playerid, "EditRaceListitem", listitem);

			SendServerMessage(playerid, "Press "YELLOW"LMB "WHITE"to apply modify checkpoint of the map!");
		}
		else {

			SetPVarInt(playerid, "EditRaceCP", SelectedRaceMapEx+1);
			SendServerMessage(playerid, "Press "YELLOW"LMB "WHITE"to apply new checkpoint of the map!");
		}
	}
	return 1;
}

Dialog:Race_LoadMap(playerid, response, listitem, inputtext[]) {

	if (!response)
		return cmd_event(playerid, "info");

	new index = 0;

	foreach (new map : RacesMap) {

		if (index == listitem) {

			if (Iter_Contains(RacesMap, map)) {

				cmd_event(playerid, "info");
				SendClientMessage(playerid, COLOR_SERVER, "EVENT: "YELLOW"Map selected!");

				return SelectedRaceMap = map;
			}
			break;
		}
		else index ++;
	}
	Dialog_Show(playerid, Race_CreateMap, DIALOG_STYLE_INPUT, "Create Race Map", "Fill a name on your map creation: (input below)", "Next", "Back");

	return 1;
}

Dialog:Race_TeleOption(playerid, response, listitem, inputtext[]) {

	if (!response)
		return cmd_event(playerid, "info");

	switch (listitem) {

		case 0: {

			SetCameraBehindPlayer(playerid);
			SendClientMessage(playerid, COLOR_SERVER, "EVENTMAP: "WHITE"Teleported to event map start point");

			SetPlayerPositionEx(playerid, race_CPInfo[SelectedRaceMap][0][cpRace][0], race_CPInfo[SelectedRaceMap][0][cpRace][1], race_CPInfo[SelectedRaceMap][0][cpRace][2], 1000);
		}
		case 1: {

			SetCameraBehindPlayer(playerid);
			SendClientMessage(playerid, COLOR_SERVER, "EVENTMAP: "WHITE"Teleported to event map finish point");

			SetPlayerPositionEx(playerid, race_CPInfo[SelectedRaceMap][19][cpRace][0], race_CPInfo[SelectedRaceMap][19][cpRace][1], race_CPInfo[SelectedRaceMap][19][cpRace][2], 1000);
		}
	}
	return 1;
}

ptask Race_EventCountdown[1000](playerid) 
{
    if (GetPVarInt(playerid, "IsAtEvent") == 1) {

        if (race_EventData[evCountdown][playerid] > 0 && (race_EventData[evTime] > 120)) {

            race_EventData[evCountdown][playerid] --;

			GameTextForPlayer(playerid, sprintf("~w~event dimulai dalam~n~%d detik", race_EventData[evCountdown][playerid]), 1000, 6);
			PlayerPlaySound(playerid, 1056, 0, 0, 0);

            if (!race_EventData[evCountdown][playerid]) {

                EventStarted = 1;
				evRaceCP[playerid] = 0;

                TogglePlayerControllable(playerid, 1);
                GameTextForPlayer(playerid, " ", 0, 6);

                SetPlayerVirtualWorld(playerid, race_EventData[evWorld]);
				SetVehicleVirtualWorld(evCar[playerid], GetPlayerVirtualWorld(playerid));

				PlayerPlaySound(playerid, 1057, 0, 0, 0);
                SendClientMessage(playerid, COLOR_SERVER, "EVENT: "YELLOW"Event dimulai!");

				format (race_CPData[SelectedRaceMap][cpLastUsed], 36, ReturnDate());
				SendClientMessage(playerid, COLOR_SERVER, "HINT: "WHITE"Gunakan '"YELLOW"/flipback"WHITE"' untuk respawn kendaraan milikmu!");

				Race_Event_Save(SelectedRaceMap);
				SetPlayerRaceCheckpoint(playerid, 0, race_CPInfo[SelectedRaceMap][evRaceCP[playerid]][cpRace][0], race_CPInfo[SelectedRaceMap][evRaceCP[playerid]][cpRace][1], race_CPInfo[SelectedRaceMap][evRaceCP[playerid]][cpRace][2], race_CPInfo[SelectedRaceMap][evRaceCP[playerid]+1][cpRace][0], race_CPInfo[SelectedRaceMap][evRaceCP[playerid]+1][cpRace][1], race_CPInfo[SelectedRaceMap][evRaceCP[playerid]+1][cpRace][2], 10.0);
            }
        }
		else if (race_EventData[evTime] <= 30) {

            race_EventData[evCountdown][playerid] --;
			SendEventMessage(EventType, COLOR_SERVER, "EVENT: "WHITE"Tidak ada pemenang sejauh ini, event akan berakhir dalam %d detik!", race_EventData[evTime]);

			GameTextForPlayer(playerid, sprintf("~w~event berakhir dalam~n~%d detik", race_EventData[evCountdown][playerid]), 1000, 6);
			PlayerPlaySound(playerid, 1056, 0, 0, 0);

            if (!race_EventData[evCountdown][playerid]) {

				DisableRemoteVehicleCollisions(playerid, 0);
				DisablePlayerRaceCheckpoint(playerid);

				SendEventMessage(EventType, COLOR_SERVER, "EVENT: "YELLOW"Kamu mendapatkan hadiah sebesar {009000}$%s "YELLOW"karena telah menjadi partisipan event ini!", FormatNumber(race_EventData[evPrice]));

				if (IsValidVehicle(evCar[playerid]))
					Vehicle_Delete(evCar[playerid], false);

				TogglePlayerSpectating(playerid, 1);
				SetTimerEx("Event_RespawnPlayer", 5000, false, "d", playerid);

				SetPlayerColor(playerid, COLOR_DEFAULT);
				SetPVarInt(playerid, "IsAtEvent", -1);

				if (PlayerData[playerid][pOnDuty])
					SetFactionColor(playerid);

				race_EventData[evEntry] --;

				ResetPlayerMoney(playerid);
				GivePlayerMoney(playerid, GetMoney(playerid));
            }			
		}
    }
}

task Race_EventTimer[1000]() 
{
	if ((EventType == 1) && EventStarted) {

		if (race_EventData[evTime] > 0) {

			race_EventData[evTime] --;

			if (race_EventData[evTime] == 60) {

				foreach (new id : Player) if (PlayerData[id][pLogged]) {

					if (GetPVarInt(id, "IsAtEvent") == 1) PlayerPlaySound(id, 1057, 0, 0, 0);
				}
				SendEventMessage(EventType, COLOR_SERVER, "EVENT: "WHITE"Event akan berakhir dalam %d detik!", race_EventData[evTime]);
			}
			else if (race_EventData[evTime] == 30) {

				foreach (new id : Player) if (PlayerData[id][pLogged]) {

					if (GetPVarInt(id, "IsAtEvent") == 1) race_EventData[evCountdown][id] = race_EventData[evTime];
				}				
			}
		}
		if (!race_EventData[evEntry]) {
			
			Event_ForceEnd();
			Race_Event_Save(SelectedRaceMap);

			SelectedRaceMap = -1;
		}
	}
}

// Event TDM

function TDM_Spawning(playerid) {

	if (GetPVarInt(playerid, "IsAtEvent") == 3) {

		if (GetPlayerVirtualWorld(playerid) != tdm_EventData[eventWorld]) {

			forex (weaps, 3) TDM_GiveWeapon(playerid, tdm_EventData[eventWeapons][weaps], tdm_EventData[eventAmmo][weaps]);
			TDM_ToggleAntiCheat(playerid);

			SetPlayerVirtualWorld(playerid, tdm_EventData[eventWorld]);
			SetPlayerInterior(playerid, tdm_EventData[eventInterior]);
		}
	}
	return 1;
}

stock TDM_ToggleAntiCheat(playerid, bool:nyala = true) {

    if (!IsPlayerConnected(playerid))
    {
        return 0;
    }
	EnableAntiCheatForPlayer(playerid, 2, nyala);
	EnableAntiCheatForPlayer(playerid, 3, nyala);
	EnableAntiCheatForPlayer(playerid, 4, nyala);
	EnableAntiCheatForPlayer(playerid, 5, nyala);
	EnableAntiCheatForPlayer(playerid, 6, nyala);
	EnableAntiCheatForPlayer(playerid, 15, nyala);
	EnableAntiCheatForPlayer(playerid, 16, false); // Android suka ke kick
	EnableAntiCheatForPlayer(playerid, 17, false); // Android suka ke kick
	EnableAntiCheatForPlayer(playerid, 18, nyala);
	EnableAntiCheatForPlayer(playerid, 19, nyala);
	EnableAntiCheatForPlayer(playerid, 20, nyala);
	EnableAntiCheatForPlayer(playerid, 21, nyala);
	EnableAntiCheatForPlayer(playerid, 27, nyala);
	EnableAntiCheatForPlayer(playerid, 28, nyala);
	EnableAntiCheatForPlayer(playerid, 29, nyala);
	EnableAntiCheatForPlayer(playerid, 30, nyala);
	EnableAntiCheatForPlayer(playerid, 35, nyala);
	//EnableAntiCheatForPlayer(playerid, 47, nyala); // Android suka ke kick

	return 1;
}

stock TDM_UpdateTD(teamid) {

	foreach (new playerid : Player) {

		if (GetPVarInt(playerid, "IsAtEvent") == 3) {

			switch (teamid) {

				case 1: PlayerTextDrawSetString(playerid, TDM_TD[playerid][2], sprintf("Team A: %d", tdm_EventData[eventTeamScore][teamid-1]));
				case 2: PlayerTextDrawSetString(playerid, TDM_TD[playerid][3], sprintf("Team B: %d", tdm_EventData[eventTeamScore][teamid-1]));
			}
		}
	}
	return 1;
}

stock TDM_DisplayTD(playerid, bool:muncul = true) {

	if (muncul) {

		forex (td, 5) PlayerTextDrawShow(playerid, TDM_TD[playerid][td]);
	}
	else {

		forex (td, 5) PlayerTextDrawHide(playerid, TDM_TD[playerid][td]);
	}
	return 1;
}

stock TDM_GiveWeapon(playerid, weaponid, ammo) {

	if (GetPVarInt(playerid, "IsAtEvent") == 3) {

		GivePlayerWeapon(playerid, weaponid, ammo);
	}
	return 1;
}

Dialog:TDM_EventLimit(playerid, response, listitem, inputtext[]) {

	if (!response)
		return cmd_event(playerid, "info");

	if (!IsNumeric(inputtext) || IsOdd(strval(inputtext)))
		return SendErrorMessage(playerid, "Hanya karakter angka genap yang diperbolehkan!"), dialog_EventInfo(playerid, 1, 0, inputtext);
	
	if ((strval(inputtext) < 5 || strval(inputtext) > MAX_PLAYERS/2) && PlayerData[playerid][pAdmin] < 7)
		return SendErrorMessage(playerid, "Tidak dapat mengubah nilai. (5-%d)", MAX_PLAYERS/2), dialog_EventInfo(playerid, 1, 0, inputtext);

	tdm_EventData[eventLimit] = strval(inputtext);
	cmd_event(playerid, "info");

	return 1;
}

Dialog:TDM_EventScore(playerid, response, listitem, inputtext[]) {

	if (!response)
		return cmd_event(playerid, "info");

	if (!IsNumeric(inputtext))
		return SendErrorMessage(playerid, "Hanya karakter angka yang diperbolehkan!"), dialog_EventInfo(playerid, 1, 1, inputtext);
	
	if ((strval(inputtext) < 20 || strval(inputtext) > 100) && PlayerData[playerid][pAdmin] < 7)
		return SendErrorMessage(playerid, "Tidak dapat mengubah nilai. (20-100)"), dialog_EventInfo(playerid, 1, 1, inputtext);

	tdm_EventData[eventMaxScore] = strval(inputtext);
	cmd_event(playerid, "info");

	return 1;
}

Dialog:TDM_EventPrize(playerid, response, listitem, inputtext[]) {

	if (!response)
		return cmd_event(playerid, "info");

	new
		dollar, 
		cent, 
		totalamount[32];
	
	if (strfind(inputtext, ".", true) != -1)
	{
		sscanf(inputtext, "p<.>dd", dollar, cent);
		format(totalamount, sizeof(totalamount), "%d%02d", dollar, cent);

		if ((strval(totalamount) < 0 || strval(totalamount) > 50000) && PlayerData[playerid][pAdmin] < 7)
			return SendErrorMessage(playerid, "Tidak dapat mengubah nilai. ($0.00-$500.00)"), dialog_EventInfo(playerid, 1, 2, inputtext);

		tdm_EventData[eventPrice] = strval(totalamount);
		cmd_event(playerid, "info");
	}
	else
	{
		sscanf(inputtext, "d", dollar);
		format(totalamount, sizeof(totalamount), "%d00", dollar);

		if ((strval(totalamount) < 0 || strval(totalamount) > 50000) && PlayerData[playerid][pAdmin] < 7)
			return SendErrorMessage(playerid, "Tidak dapat mengubah nilai. ($0.00-$500.00)"), dialog_EventInfo(playerid, 1, 2, inputtext);

		tdm_EventData[eventPrice] = strval(totalamount);
		cmd_event(playerid, "info");
	}
	return 1;
}

Dialog:TDM_EventSkinA(playerid, response, listitem, inputtext[]) {

	if (!response)
		return cmd_event(playerid, "info");

	if (!IsNumeric(inputtext))
		return SendErrorMessage(playerid, "Hanya karakter angka yang diperbolehkan!"), dialog_EventInfo(playerid, 1, 3, inputtext);
	
	if (!IsValidSkin(strval(inputtext)))
		return SendErrorMessage(playerid, "Tidak dapat mengubah nilai. (1-311)"), dialog_EventInfo(playerid, 1, 3, inputtext);

	tdm_EventData[eventSkin][0] = strval(inputtext);
	cmd_event(playerid, "info");

	return 1;
}

Dialog:TDM_EventSkinB(playerid, response, listitem, inputtext[]) {

	if (!response)
		return cmd_event(playerid, "info");

	if (!IsNumeric(inputtext))
		return SendErrorMessage(playerid, "Hanya karakter angka yang diperbolehkan!"), dialog_EventInfo(playerid, 1, 4, inputtext);
	
	if (!IsValidSkin(strval(inputtext)))
		return SendErrorMessage(playerid, "Tidak dapat mengubah nilai. (1-311)"), dialog_EventInfo(playerid, 1, 4, inputtext);

	tdm_EventData[eventSkin][1] = strval(inputtext);
	cmd_event(playerid, "info");

	return 1;
}

Dialog:TDM_EventEquip(playerid, response, listitem, inputtext[]) {

	if (!response)
		return SendErrorMessage(playerid, "Please select a weapon!"), cmd_event(playerid, "info");

	tdm_EventData[eventWeapons][0] = arrWeapData[listitem];

	static str[512];
	format (str, sizeof(str), "Weapon Name");

	forex (id, sizeof(arrWeap))	{

		format (str, sizeof(str), "%s\n%s", str, arrWeap[id]);
	}
	Dialog_Show(playerid, TDM_EventEquip1, DIALOG_STYLE_TABLIST_HEADERS, "Select a weapon 2", str, "Pick", "");

	return 1;
}

Dialog:TDM_EventEquip1(playerid, response, listitem, inputtext[]) {

	if (!response)
		return SendErrorMessage(playerid, "Please select a weapon!"), cmd_event(playerid, "info");

	tdm_EventData[eventWeapons][1] = arrWeapData[listitem];

	static str[512];
	format (str, sizeof(str), "Weapon Name");

	forex (id, sizeof(arrWeap))	{

		format (str, sizeof(str), "%s\n%s", str, arrWeap[id]);
	}
	Dialog_Show(playerid, TDM_EventEquip2, DIALOG_STYLE_TABLIST_HEADERS, "Select a weapon 3", str, "Pick", "");

	return 1;
}

Dialog:TDM_EventEquip2(playerid, response, listitem, inputtext[]) {

	if (!response)
		return SendErrorMessage(playerid, "Please select a weapon!"), cmd_event(playerid, "info");

	tdm_EventData[eventWeapons][2] = arrWeapData[listitem];
	cmd_event(playerid, "info");

	return 1;
}

Dialog:TDM_EventAmmo(playerid, response, listitem, inputtext[]) {

	if (!response)
		return SendErrorMessage(playerid, "Please select an amount!"), cmd_event(playerid, "info");

	tdm_EventData[eventAmmo][0] = arrAmmoData[listitem];

	static str[128];
	format (str, sizeof(str), "Ammo Amount");
	format (str, sizeof(str), "%s\n50", str);
	format (str, sizeof(str), "%s\n100", str);
	format (str, sizeof(str), "%s\n150", str);
	format (str, sizeof(str), "%s\n250", str);
	format (str, sizeof(str), "%s\n350", str);
	format (str, sizeof(str), "%s\n500", str);
	Dialog_Show(playerid, TDM_EventAmmo1, DIALOG_STYLE_TABLIST_HEADERS, "Select ammo 2 amount", str, "Pick", "");	

	return 1;
}

Dialog:TDM_EventAmmo1(playerid, response, listitem, inputtext[]) {

	if (!response)
		return SendErrorMessage(playerid, "Please select an amount!"), cmd_event(playerid, "info");

	tdm_EventData[eventAmmo][1] = arrAmmoData[listitem];

	static str[128];
	format (str, sizeof(str), "Ammo Amount");
	format (str, sizeof(str), "%s\n50", str);
	format (str, sizeof(str), "%s\n100", str);
	format (str, sizeof(str), "%s\n150", str);
	format (str, sizeof(str), "%s\n250", str);
	format (str, sizeof(str), "%s\n350", str);
	format (str, sizeof(str), "%s\n500", str);
	Dialog_Show(playerid, TDM_EventAmmo2, DIALOG_STYLE_TABLIST_HEADERS, "Select ammo 3 amount", str, "Pick", "");	

	return 1;
}

Dialog:TDM_EventAmmo2(playerid, response, listitem, inputtext[]) {

	if (!response)
		return SendErrorMessage(playerid, "Please select an amount!"), cmd_event(playerid, "info");

	tdm_EventData[eventAmmo][2] = arrAmmoData[listitem];
	cmd_event(playerid, "info");

	return 1;
}

ptask TDM_EventCountdown[1000](playerid) {

	if (GetPVarInt(playerid, "IsAtEvent") == EventType && (EventType == 3)) {

		if (tdm_EventData[eventCD][playerid] > 0) {

			tdm_EventData[eventCD][playerid] --;

			GameTextForPlayer(playerid, sprintf("~w~event dimulai dalam~n~%d detik", tdm_EventData[eventCD][playerid]), 1000, 6);
			PlayerPlaySound(playerid, 1056, 0, 0, 0);

			if (!tdm_EventData[eventCD][playerid]) {

				EventStarted = 1;
				tdm_EventData[eventArea] = CreateDynamicSphere(tdm_EventData[eventPosX][0], tdm_EventData[eventPosY][0], tdm_EventData[eventPosZ][0], 300, tdm_EventData[eventWorld], tdm_EventData[eventInterior], -1);

				TDM_UpdateTD(1);
				TDM_UpdateTD(2);

				PlayerTextDrawSetString(playerid, TDM_TD[playerid][4], sprintf("~y~Target: ~g~%d", tdm_EventData[eventMaxScore]));

				TDM_DisplayTD(playerid);
				SetPlayerHealth(playerid, 100.0);

				GameTextForPlayer(playerid, "", 0, 6);
				SendClientMessage(playerid, COLOR_SERVER, "EVENT: "YELLOW"Event dimulai!");

				forex (weaps, 3) TDM_GiveWeapon(playerid, tdm_EventData[eventWeapons][weaps], tdm_EventData[eventAmmo][weaps]);
				SetPlayerVirtualWorld(playerid, tdm_EventData[eventWorld]);
			}
		}
	}
}

hook OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid) {

	if (damagedid != INVALID_PLAYER_ID && (EventType == 3)) {

		if (GetPVarInt(damagedid, "IsAtEvent") == 3 && evTeam[damagedid] == evTeam[playerid]) {

			static Float:health;
			GetPlayerHealth(damagedid,health);
			SetPlayerHealth(damagedid,(health+amount)); // Mencegah Friendly Fire.
			print("Callback GiveDamage terpanggil cuy,");
		}
	}
	if ((GetPVarInt(playerid, "IsAtEvent") == 6 && GetPVarInt(damagedid, "IsAtEvent") == 6)) {

		if (damagedid != INVALID_PLAYER_ID && GetPlayerTeam(playerid) > 0 && GetPlayerTeam(damagedid) == GetPlayerTeam(playerid)) {

			static Float:health;
			GetPlayerHealth(damagedid,health);
			SetPlayerHealth(damagedid,(health+amount)); // Mencegah Friendly Fire.
		}
	}
}

forward Zombie_Spawning(playerid);
public Zombie_Spawning(playerid) {

	if (GetPVarInt(playerid, "IsAtEvent") == 6) {

		if (GetPlayerVirtualWorld(playerid) != zombie_EventData[eventWorld]) {

			switch (evTeam[playerid]) {

                case 1: forex (weaps, 3) Zombie_GiveWeapon(playerid, zombie_EventData[eventWeapons][weaps], zombie_EventData[eventAmmo][weaps]);
                case 2: Zombie_GiveWeapon(playerid, WEAPON_CHAINSAW);
            }
			Zombie_ToggleAntiCheat(playerid);

			SetPlayerVirtualWorld(playerid, zombie_EventData[eventWorld]);
			SetPlayerInterior(playerid, zombie_EventData[eventInterior]);
		}
	}
    return 1;
}

stock Zombie_DisplayTD(playerid, bool:status) {

    if (status) forex (td, 4) PlayerTextDrawShow(playerid, ZombieTD[playerid][td]);
    else forex (td, 4) PlayerTextDrawHide(playerid, ZombieTD[playerid][td]);

    return 1;
}

stock Zombie_UpdateTD(playerid) {

    PlayerTextDrawSetString(playerid, ZombieTD[playerid][1], sprintf("~y~Human Alive: ~r~%d", zombie_EventData[eventAlive]));
    PlayerTextDrawSetString(playerid, ZombieTD[playerid][3], sprintf("%d minutes", zombie_EventData[eventTimer]));

    return 1;
}

stock Zombie_ToggleAntiCheat(playerid, bool:nyala = true) {

    if (!IsPlayerConnected(playerid))
    {
        return 0;
    }
	EnableAntiCheatForPlayer(playerid, 2, nyala);
	EnableAntiCheatForPlayer(playerid, 3, nyala);
	EnableAntiCheatForPlayer(playerid, 4, nyala);
	EnableAntiCheatForPlayer(playerid, 5, nyala);
	EnableAntiCheatForPlayer(playerid, 6, nyala);
	EnableAntiCheatForPlayer(playerid, 15, nyala);
	EnableAntiCheatForPlayer(playerid, 16, false); // Android suka ke kick
	EnableAntiCheatForPlayer(playerid, 17, false); // Android suka ke kick
	EnableAntiCheatForPlayer(playerid, 18, nyala);
	EnableAntiCheatForPlayer(playerid, 19, nyala);
	EnableAntiCheatForPlayer(playerid, 20, nyala);
	EnableAntiCheatForPlayer(playerid, 21, nyala);
	EnableAntiCheatForPlayer(playerid, 27, nyala);
	EnableAntiCheatForPlayer(playerid, 28, nyala);
	EnableAntiCheatForPlayer(playerid, 29, nyala);
	EnableAntiCheatForPlayer(playerid, 30, nyala);
	EnableAntiCheatForPlayer(playerid, 35, nyala);
	//EnableAntiCheatForPlayer(playerid, 47, nyala); // Android suka ke kick

	return 1;
}

stock Zombie_GiveWeapon(playerid, weaponid, ammo = 1) {

	if (GetPVarInt(playerid, "IsAtEvent") == 6) {

		GivePlayerWeapon(playerid, weaponid, ammo);
	}
	return 1;
}

Dialog:Zombie_EventLimit(playerid, response, listitem, inputtext[]) {

	if (!response)
		return cmd_event(playerid, "info");

	if (!IsNumeric(inputtext) || IsOdd(strval(inputtext)))
		return SendErrorMessage(playerid, "Hanya karakter angka genap yang diperbolehkan!"), dialog_EventInfo(playerid, 1, 0, inputtext);
	
	if ((strval(inputtext) < 6 || strval(inputtext) > MAX_PLAYERS/2) && PlayerData[playerid][pAdmin] < 7)
		return SendErrorMessage(playerid, "Tidak dapat mengubah nilai. (6-%d)", MAX_PLAYERS/2), dialog_EventInfo(playerid, 1, 0, inputtext);

	zombie_EventData[eventLimit] = strval(inputtext);

    if (zombie_EventData[eventAlive] > zombie_EventData[eventLimit]) {

        zombie_EventData[eventAlive] = 0;
        SendErrorMessage(playerid, "An option has been reset to default due an unlogical has occured!");
    }
	cmd_event(playerid, "info");

	return 1;
}

Dialog:Zombie_EventAlive(playerid, response, listitem, inputtext[]) {

	if (!response)
		return cmd_event(playerid, "info");

	if (!IsNumeric(inputtext))
		return SendErrorMessage(playerid, "Hanya karakter angka yang diperbolehkan!"), dialog_EventInfo(playerid, 1, 1, inputtext);
	
	if (strval(inputtext) < 1 || strval(inputtext) > zombie_EventData[eventLimit]/2)
		return SendErrorMessage(playerid, "Tidak dapat mengubah nilai. (1-%d)", zombie_EventData[eventLimit]/2), dialog_EventInfo(playerid, 1, 1, inputtext);

	zombie_EventData[eventAlive] = strval(inputtext);
	cmd_event(playerid, "info");

	return 1;
}

Dialog:Zombie_EventPrize(playerid, response, listitem, inputtext[]) {

	if (!response)
		return cmd_event(playerid, "info");

	new
		dollar, 
		cent, 
		totalamount[32];
	
	if (strfind(inputtext, ".", true) != -1)
	{
		sscanf(inputtext, "p<.>dd", dollar, cent);
		format(totalamount, sizeof(totalamount), "%d%02d", dollar, cent);

		if ((strval(totalamount) < 0 || strval(totalamount) > 50000) && PlayerData[playerid][pAdmin] < 7)
			return SendErrorMessage(playerid, "Tidak dapat mengubah nilai. ($0.00-$500.00)"), dialog_EventInfo(playerid, 1, 2, inputtext);

		zombie_EventData[eventPrice] = strval(totalamount);
		cmd_event(playerid, "info");
	}
	else
	{
		sscanf(inputtext, "d", dollar);
		format(totalamount, sizeof(totalamount), "%d00", dollar);

		if ((strval(totalamount) < 0 || strval(totalamount) > 50000) && PlayerData[playerid][pAdmin] < 7)
			return SendErrorMessage(playerid, "Tidak dapat mengubah nilai. ($0.00-$500.00)"), dialog_EventInfo(playerid, 1, 2, inputtext);

		zombie_EventData[eventPrice] = strval(totalamount);
		cmd_event(playerid, "info");
	}
	return 1;
}

Dialog:Zombie_EventTimer(playerid, response, listitem, inputtext[]) {

	if (!response)
		return cmd_event(playerid, "info");

	if (!IsNumeric(inputtext))
		return SendErrorMessage(playerid, "Hanya karakter angka yang diperbolehkan!"), dialog_EventInfo(playerid, 1, 3, inputtext);
	
	if ((strval(inputtext) < 5 || strval(inputtext) > 30) && PlayerData[playerid][pAdmin] < 11)
		return SendErrorMessage(playerid, "Tidak dapat mengubah nilai. (5-30)"), dialog_EventInfo(playerid, 1, 3, inputtext);

	zombie_EventData[eventTimer] = strval(inputtext);
	cmd_event(playerid, "info");

	return 1;
}

Dialog:Zombie_EventEquip(playerid, response, listitem, inputtext[]) {

	if (!response)
		return SendErrorMessage(playerid, "Please select a weapon!"), cmd_event(playerid, "info");

	zombie_EventData[eventWeapons][0] = arrWeapData[listitem];

	static str[512];
	format (str, sizeof(str), "Weapon Name");

	forex (id, sizeof(arrWeap))	{

		format (str, sizeof(str), "%s\n%s", str, arrWeap[id]);
	}
	Dialog_Show(playerid, Zombie_EventEquip1, DIALOG_STYLE_TABLIST_HEADERS, "Select a weapon 2", str, "Pick", "");

	return 1;
}

Dialog:Zombie_EventEquip1(playerid, response, listitem, inputtext[]) {

	if (!response)
		return SendErrorMessage(playerid, "Please select a weapon!"), cmd_event(playerid, "info");

	zombie_EventData[eventWeapons][1] = arrWeapData[listitem];

	static str[512];
	format (str, sizeof(str), "Weapon Name");

	forex (id, sizeof(arrWeap))	{

		format (str, sizeof(str), "%s\n%s", str, arrWeap[id]);
	}
	Dialog_Show(playerid, Zombie_EventEquip2, DIALOG_STYLE_TABLIST_HEADERS, "Select a weapon 3", str, "Pick", "");

	return 1;
}

Dialog:Zombie_EventEquip2(playerid, response, listitem, inputtext[]) {

	if (!response)
		return SendErrorMessage(playerid, "Please select a weapon!"), cmd_event(playerid, "info");

	zombie_EventData[eventWeapons][2] = arrWeapData[listitem];
	cmd_event(playerid, "info");

	return 1;
}

Dialog:Zombie_EventAmmo(playerid, response, listitem, inputtext[]) {

	if (!response)
		return SendErrorMessage(playerid, "Please select an amount!"), cmd_event(playerid, "info");

	zombie_EventData[eventAmmo][0] = arrAmmoData[listitem];

	static str[128];
	format (str, sizeof(str), "Ammo Amount");
	format (str, sizeof(str), "%s\n50", str);
	format (str, sizeof(str), "%s\n100", str);
	format (str, sizeof(str), "%s\n150", str);
	format (str, sizeof(str), "%s\n250", str);
	format (str, sizeof(str), "%s\n350", str);
	format (str, sizeof(str), "%s\n500", str);
	Dialog_Show(playerid, Zombie_EventAmmo1, DIALOG_STYLE_TABLIST_HEADERS, "Select ammo 2 amount", str, "Pick", "");	

	return 1;
}

Dialog:Zombie_EventAmmo1(playerid, response, listitem, inputtext[]) {

	if (!response)
		return SendErrorMessage(playerid, "Please select an amount!"), cmd_event(playerid, "info");

	zombie_EventData[eventAmmo][1] = arrAmmoData[listitem];

	static str[128];
	format (str, sizeof(str), "Ammo Amount");
	format (str, sizeof(str), "%s\n50", str);
	format (str, sizeof(str), "%s\n100", str);
	format (str, sizeof(str), "%s\n150", str);
	format (str, sizeof(str), "%s\n250", str);
	format (str, sizeof(str), "%s\n350", str);
	format (str, sizeof(str), "%s\n500", str);
	Dialog_Show(playerid, Zombie_EventAmmo2, DIALOG_STYLE_TABLIST_HEADERS, "Select ammo 3 amount", str, "Pick", "");	

	return 1;
}

Dialog:Zombie_EventAmmo2(playerid, response, listitem, inputtext[]) {

	if (!response)
		return SendErrorMessage(playerid, "Please select an amount!"), cmd_event(playerid, "info");

	zombie_EventData[eventAmmo][2] = arrAmmoData[listitem];
	cmd_event(playerid, "info");

	return 1;
}

ptask Zombie_EventCountdown[1000](playerid) 
{
    if (GetPVarInt(playerid, "IsAtEvent") == 6) {

        if (zombie_EventData[eventCD][playerid] > 0) {

            zombie_EventData[eventCD][playerid] --;

			GameTextForPlayer(playerid, sprintf("~w~event dimulai dalam~n~%d detik", zombie_EventData[eventCD][playerid]), 1000, 6);
			PlayerPlaySound(playerid, 1056, 0, 0, 0);

            if (!zombie_EventData[eventCD][playerid]) {

                EventStarted = 1;
                zombie_EventData[eventArea] = CreateDynamicSphere(zombie_EventData[eventPosX][0], zombie_EventData[eventPosY][0], zombie_EventData[eventPosZ][0], 200, zombie_EventData[eventWorld], zombie_EventData[eventInterior], -1);

                switch (GetPlayerTeam(playerid)) {

                    case 1: forex (weaps, 3) Zombie_GiveWeapon(playerid, zombie_EventData[eventWeapons][weaps], zombie_EventData[eventAmmo][weaps]);
                    case 2: Zombie_GiveWeapon(playerid, WEAPON_CHAINSAW);
                }
                PlayerPlaySound(playerid, 1057, 0, 0, 0);
            
                Zombie_DisplayTD(playerid, true);
                Zombie_UpdateTD(playerid);

                SetPlayerHealth(playerid, 100.0);
                GameTextForPlayer(playerid, "", 0, 6);

                SetPlayerVirtualWorld(playerid, zombie_EventData[eventWorld]);
                SendClientMessage(playerid, COLOR_SERVER, "EVENT: "YELLOW"Event dimulai!");
            }
        }
    }
}

task Zombie_EventTimer[60000]() 
{
    if (EventStarted && EventType == 6) {

        if (zombie_EventData[eventTimer] > 0) {

            if (!zombie_EventData[eventAlive] && !zombie_EventData[eventWinner]) {

                foreach (new id : Player) if (GetPVarInt(id, "IsAtEvent") == 6) {

                    GiveMoney(id, zombie_EventData[eventPrice]);
                    SendClientMessage(id, COLOR_SERVER, "EVENT: "WHITE"Event was ended premature, not equal participant");
                    
                    TogglePlayerSpectating(id, 1);
        			SetTimerEx("Event_RespawnPlayer", 3000, false, "d", id);

					SetPlayerColor(id, COLOR_DEFAULT);
					SetPlayerTeam(id,0);

					if (PlayerData[id][pOnDuty])
						SetFactionColor(id);

					ResetPlayerMoney(id);
					GivePlayerMoney(id, GetMoney(id));

					Zombie_DisplayTD(id, false);
					SetPVarInt(id, "IsAtEvent", -1);
                }
                return Event_ForceEnd(); 
            }
            zombie_EventData[eventTimer]--;

            foreach (new playerid : Player) if (GetPVarInt(playerid, "IsAtEvent") == 6 && (EventStarted)) {

                Zombie_UpdateTD(playerid);
            }
        }
        else {

            if (zombie_EventData[eventAlive] > 0) {

                zombie_EventData[eventWinner] = 1;
                SendEventMessage(EventType, COLOR_SERVER, "EVENT: "GREEN"Human "YELLOW"is won!");

                foreach (new id : Player) if (GetPVarInt(id, "IsAtEvent") == 6 && zombie_EventData[eventWinner] > 0) {

                    if (evTeam[id] == zombie_EventData[eventWinner]) {
						GiveMoney(id, zombie_EventData[eventPrice]+10000);
						SendClientMessageEx(id, COLOR_SERVER, "EVENT: "YELLOW"Kamu telah memenangkan mode ini dan mendapatkan hadiah sebesar {009000}$%s", FormatNumber(dm_EventData[eventPrice]+10000));
					}
                    else {
						GiveMoney(id, zombie_EventData[eventPrice]);
						SendClientMessageEx(id, COLOR_SERVER, "EVENT: "YELLOW"Kamu telah berpartisipasi dalam mode ini dan mendapatkan {009000}$%s", FormatNumber(dm_EventData[eventPrice]));
					}
                    
                    TogglePlayerSpectating(id, 1);
        			SetTimerEx("Event_RespawnPlayer", 3000, false, "d", id);

					SetPlayerColor(id, COLOR_DEFAULT);
					SetPlayerTeam(id,0);

					if (PlayerData[id][pOnDuty])
						SetFactionColor(id);

					ResetPlayerMoney(id);
					GivePlayerMoney(id, GetMoney(id));

					Zombie_DisplayTD(id, false);
					SetPVarInt(id, "IsAtEvent", -1);
                }
                Event_ForceEnd();                
            }
        }
    }
    return 1;
}