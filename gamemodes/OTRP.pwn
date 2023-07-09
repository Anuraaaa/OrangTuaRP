/*	

					░█████╗░██████╗░░█████╗░███╗░░██╗░██████╗░  ████████╗██╗░░░██╗░█████╗░
					██╔══██╗██╔══██╗██╔══██╗████╗░██║██╔════╝░  ╚══██╔══╝██║░░░██║██╔══██╗
					██║░░██║██████╔╝███████║██╔██╗██║██║░░██╗░  ░░░██║░░░██║░░░██║███████║
					██║░░██║██╔══██╗██╔══██║██║╚████║██║░░╚██╗  ░░░██║░░░██║░░░██║██╔══██║
					╚█████╔╝██║░░██║██║░░██║██║░╚███║╚██████╔╝  ░░░██║░░░╚██████╔╝██║░░██║
					░╚════╝░╚═╝░░╚═╝╚═╝░░╚═╝╚═╝░░╚══╝░╚═════╝░  ░░░╚═╝░░░░╚═════╝░╚═╝░░╚═╝

					██████╗░░█████╗░██╗░░░░░███████╗██████╗░██╗░░░░░░█████╗░██╗░░░██╗
					██╔══██╗██╔══██╗██║░░░░░██╔════╝██╔══██╗██║░░░░░██╔══██╗╚██╗░██╔╝
					██████╔╝██║░░██║██║░░░░░█████╗░░██████╔╝██║░░░░░███████║░╚████╔╝░
					██╔══██╗██║░░██║██║░░░░░██╔══╝░░██╔═══╝░██║░░░░░██╔══██║░░╚██╔╝░░
					██║░░██║╚█████╔╝███████╗███████╗██║░░░░░███████╗██║░░██║░░░██║░░░
					╚═╝░░╚═╝░╚════╝░╚══════╝╚══════╝╚═╝░░░░░╚══════╝╚═╝░░╚═╝░░░╚═╝░░░


Un-noted changelog:

- Fix /damages tidak clear ketika di operate
- Menambahkan SA-PD command "/seal" untuk seal property (biz/house/flat)

*/

/* Includes */

#define CGEN_MEMORY 50000
#define YSI_NO_HEAP_MALLOC
#define YSI_NO_OPTIMISATION_MESSAGE

#define DEBUG
#define NO_SUSPICION_LOGS

#include <a_samp>

#undef MAX_PLAYERS
#define MAX_PLAYERS 199 + 1

#pragma warning disable 239, 214

#define KEY_VEHICLE_FORWARD 0b001000
#define KEY_VEHICLE_BACKWARD 0b100000

enum E_LOGLEVEL
{
	NONE = 0,
	DEBUGGING = 1,
	INFO = 2,
	WARNING = 4,
	ERROR = 8,
	
	ALL = ERROR | WARNING | INFO | DEBUGGING
};

#include <a_zones>

#include <strlib>

#include <a_mysql>

#include <YSI_Coding\y_va>
#include <YSI_Coding\y_timers>
#include <YSI_Server\y_colours>
#include <YSI_Data\y_foreach>
#include <YSI_Game\y_vehicledata>
#include <YSI_Extra\y_inline_mysql>

#include <sscanf2>
#include <nex-ac_en.lang>
#include <nex-ac>

#include <samp_bcrypt>
#include <izcmd>
#include <progress2>

#include <distance>
#include <streamer>
#include <samp-loadingbar>
#include <garageblock>
#include <wep-config>
#include <callbacks>
#include <compat>
#include <crashdetect>
#include <lookup>
#include <chrono>
#include <multicp>
#include <eSelection>
#include <eSelectionv2>
#include <components>
#include <tp>

#include <android-check>
#include <mobile>
#include <mapandreas>
#include <notify>
#include <actor_plus>
#include <LiveCam>
#include <progress2>
#include <PreviewModelDialog2>

#if !defined OnClientCheckResponse
	forward OnClientCheckResponse(playerid, actionid, memaddr, retndata);
#endif

#if !defined SendClientCheck~
	native SendClientCheck(playerid, actionid, memaddr, memOffset, bytesCount);
#endif              

#if !defined IsValidVehicle 
	native IsValidVehicle(vehicleid);
#endif

#include ".\legacy\Core\define"
#include ".\legacy\Core\textdraw"
#include ".\legacy\Core\generalvar"

enum(<<= 1)
{
	CHECK_NULL = 0,
	SOBEIT = 0x5E8606
};

enum E_PLAYER_DATA
{
	pID,
	pUCP[22],
	pName[MAX_PLAYER_NAME],
	Float:pPos[3],
	pWorld,
	pInterior,
	pSkin,
	pAge,
	pAttempt,
	pOrigin[32],
	pGender,
	bool:pMaskOn,
	pMaskID,
	bool:pSpawned,
	pChar,
	Float:pHealth,
	Float:pHunger,
	Float:pThirst,
	pMoney,
	pInBiz,
	pStorageSelect,
	pAdmin,
	pAduty,
	pPhoneNumber,
	pCallLine,
	pCredit,
	pCalling,
	pTarget,
	pSkinPrice,
	pVehKey,
	pFaction,
	pRenting,
	pJob,
	pJob2,
	pJobSelect,
	pStorageItem,
	pCrate,
	pVehicle,
	pBusiness,
	pHudType,
	pWeaponRound[13],
	pLastVehicleID,
	pTrashVehicleID,
	pGuns[13],
	pDurability[13],
	pAmmo[13],
	pHighVelocity[13],
	pTempAmmo[13],
	bool:pTracking,
	pLevel,
	pExp,
	bool:pWP,
	bool:pJobduty,
	pFareTimer,
	pFare,
	bool:pInTaxi,
	pTotalFare,
	pMechPrice[2],
	bool:pSpraying,
	pSprayStart,
	pColor,
	pColoring,
	pSprayTime,
	pDutySecond,
	pDutyMinute,
	pDutyHour,
	pFactionEdit,
	pFactionID,
	pFactionRank,
	pOnDuty,
	pSelectedSlot,
	pFactionSkin,
	pFactionOffer,
	pFactionOffered,
	pBirthdate[24],
	pTempName[MAX_PLAYER_NAME],
	Float:pArmor,
	pSalary,
	pBank,
	pInFlat,
	pInDoor,
	pFreeze,
	pFreezeTimer,
	Float:pMark[3],
	pMarkWorld,
	pMarkInterior,
	bool:pMarkActive,
	bool:pAsking,
	pAsk[128],
	pJailTime,
	pJailReason[128],
	pJailBy[MAX_PLAYER_NAME],
	pArrest,
	pInjured,
	pInjuredTime,
	bool:pDead,
	pBusDelay,
	pSweeperDelay,
	pTrashmasterDelay,
	bool:pCuffed,
	pListitem,
	bool:pPhoneOff,
	pIncomingCall,
	pTargetid,
	Float:pHealthy,
	Float:pDamages[7],
	pBullets[7],
	pContact,
	pEditingItem,
	pSelecting,
	bool:pMasked,
	pPaycheck,
	pMinute,
	pSecond,
	pHour,
	pInHouse,
	Float:sPos[3],
	pSpectator,
	pFrisked,
	pMinutes,
	pDutyTime,
	pQuitjob,
	pChannel,
	pVendor,
	bool:pFirstAid,
	pAidTimer,
	pEditing,
	pEditType,
	pCutting,
	bool:pAxe,
	bool:pTazer,
	bool:pTazed,
	pFunds,
	pTempContact[32],
	pWeapon,
	bool:pEditAcc,
	pTempModel,
	bool:pOnDMV,
	pVehicleDMV,
	pIndexDMV,
	pIndexTest,
	bool:pOnTest,
	pLicense[4],
	pHaveDrivingLicense,
	Float:pAFKPos[6],
	pAFK,
	pAFKTime,
	bool:pLoopAnim,
	pEditGate,
	bool:pSeatbelt,
	bool:pInTuning,
	pTuningCategoryID,
	pTaxiCalled,
	bool:pLogged,
	pFishDelay,
	bool:pBandage,
	pFishing,
	pDragOffer,
	bool:pAhide,
	pTogLogin,
	bool:pTogGlobal,
	bool:pTogAnim,
	bool:pTogPM,
	bool:pTogHud,
	bool:pTogBuy,
	bool:pTogMusic,	
	pWS,
	pPark,
	pBoomboxPlaced,
	pBoomboxObject,
	Text3D:pBoomboxText,
	pBoomboxURL[128],
	pBoomboxListen,
	pMusicType,
	pStreamType,
	pFamily,
	pFamilyRank,
	pFamilyOffer,
	pFamilyOffered,
	pACWarning,
	pACTime,
	pACJetpack,
	pAccent[24],
	pSmugglers,
	bool:pTakePacket,
	pTrackPacket,
	pPizza,
	pPizzas,
	pCarryPizza,
	bool:pCarryingPizza,
	pPizzaTime,
	pPizzaDelay,
	pTrash,
	pCoin,
	pHouseLights,
	pIDCard,
	pIDCardExpired,
	pGasPump,
	bool:pKicked,
	pLastWeapon,
	bool:pIsDrunk,
	pTaxiVehicleID,
	bool:pAMSG,
	pForkliftVehicle,
	pHouseOffer,
	pHouseOfferID,
	pFlatOffer,
	pFlatOfferID,
	pVehicleOffer,
	pVehicleOfferID,
	bool:pVynMode,
	pLeaveTime,
	pMowerDelay,
	bool:pPMLog,
	pRumpoVehicle,
	pDriverDelay,
	pDrugCondition,
	pDrugTime,
	pLumberDelay,
	pAutoPaycheck,
	pAksesoris,
	bool:pTracing,
	pCough,
	pFever,
	pCoughRate,
	pFeverRate,
	pFeverTime,
	pCoughTime,
	pUsePill,
	pInWorkshop,
	pDoorDelay,
	pBroadcast,
	pMicrophone,
	pNewsGuest,
	Text3D:pMaskLabel,
	Text3D:pAdoLabel,
	pMessageTimer,
	pShowMessage,
	pBoxTimer,
	pShowBox,
	pPlayingHours,
	pFactionBadge,
	pMineDelay,
	Float:pLastPos[3],
	pLastWorld,
	pLastInterior,
	pFactionHour,
	pFactionMinute,
	pFactionSecond,
	pHaulingDelay,
	bool:pCallNews,
	pColor1,
	pColor2,
	pLastNumber,
	bool:pToggleSpeed,
	pCourierDelay,
	pAdminPoint
};

new PlayerData[MAX_PLAYERS][E_PLAYER_DATA];
new LoginTimer[MAX_PLAYERS],
	bool:liveMode[MAX_PLAYERS],
	reportDelay[MAX_PLAYERS],
	askDelay[MAX_PLAYERS],
	Helmet[MAX_PLAYERS],
	g_EngineHack[MAX_PLAYERS],
	cmd_floodProtect[MAX_PLAYERS],
	chat_floodProtect[MAX_PLAYERS],
	bool:HasRubberBullet[MAX_PLAYERS],
	bool:PlayerRubbed[MAX_PLAYERS],
	g_ListedTenant[MAX_PLAYERS][10];

new AOFCT[MAX_PLAYERS];
new AOFCW[MAX_PLAYERS];

new
    MarryWith[MAX_PLAYERS][24],
    MarryDate[MAX_PLAYERS][28];
new MarryOffer[MAX_PLAYERS],
	DivorceOffer[MAX_PLAYERS];

new EnterVehicle[MAX_PLAYERS];
new Float:Destination[MAX_PLAYERS][3];
new bool:OnBus[MAX_PLAYERS];
new BusIndex[MAX_PLAYERS];
//new BusTime[MAX_PLAYERS];
new SweeperIndex[MAX_PLAYERS];
new bool:OnSweeping[MAX_PLAYERS];
new NumberIndex[MAX_PLAYERS][5];
new PlayerPressedJump[MAX_PLAYERS];
new bool:Falling[MAX_PLAYERS];
new IsDragging[MAX_PLAYERS];
new tempCode[MAX_PLAYERS];
new bool:ValidSpawn[MAX_PLAYERS],
	bool:LewatConnect[MAX_PLAYERS],
	bool:LewatClass[MAX_PLAYERS];


new color_string[3256];
enum E_UCP_DATA
{
	ucpTime,
	ucpAdmin,
	ucpID,
	ucpEmail[48],
	uVerifyCode,
	uPassword[128],
	uDiscord,
	uLeaveIP[16],
};
new UcpData[MAX_PLAYERS][E_UCP_DATA];

/* Load Modules */
#include ".\legacy\modules"

forward OnPlayerDisconnectEx(playerid);
forward OnPlayerLogin(playerid);
forward OnPlayerFirstSpawn(playerid);
forward OnPlayerDamage(playerid, issuerid, Float:amount, weaponid, bodypart);
forward OnPlayerInjured(playerid);
forward OnVehicleCreated(vehicleid);
forward OnVehicleDeleted(vehicleid);

/* Gamemode Start! */

main()
{

}

public OnGameModeInit()
{

	if(Database_Connect()) {

		MapAndreas_Init(MAP_ANDREAS_MODE_FULL, "scriptfiles/SAFull.hmap");
		CreateGlobalTextDraw();
		CreatePublicHUD();
		DisableInteriorEnterExits();
		EnableStuntBonusForAll(0);
		ManualVehicleEngineAndLights();
		StreamerConfig();
		LoadPoint();
		LoadArea();
		LoadStaticVehicle();
		LoadServerMap();
		LoadActor();
		LoadDynamicDoors();
		LoadGangZone();
		ShowPlayerMarkers(PLAYER_MARKERS_MODE_OFF);
		BlockGarages(true, GARAGE_TYPE_ALL, "");
		VariableConfig();
		SetNameTagDrawDistance(10.0);
		SetupVendor();
		SetGameModeText("OTRP "SERVER_VERSION"");
		SendRconCommand(sprintf("hostname %s", SERVER_NAME));

		Iter_Init(House);
		//Iter_Init(PlayerVehicle);
		Iter_Init(Furniture);
		Iter_Init(DynamicActor);
		Iter_Init(SprayTag);
		/* Load from Database */
		mysql_tquery(sqlcon, "SELECT * FROM `911calls`", "Emergency_Load", "");
		mysql_tquery(sqlcon, "SELECT * FROM `actors`", "Actor_Load", "");
		mysql_tquery(sqlcon, "SELECT * FROM `atm`", "ATM_Load", "");
		mysql_tquery(sqlcon, "SELECT * FROM `fuelpump`", "Pump_Load", "");
		mysql_tquery(sqlcon, "SELECT * FROM `business`", "Business_Load");
		mysql_tquery(sqlcon, "SELECT * FROM `dealer`", "SQL_LoadDealership", "");
		mysql_tquery(sqlcon, "SELECT * FROM `dropped`", "Dropped_Load", "");
		mysql_tquery(sqlcon, "SELECT * FROM `doors`", "Doors_Load", "");
		mysql_tquery(sqlcon, "SELECT * FROM `factions`", "Faction_Load", "");
		mysql_tquery(sqlcon, "SELECT * FROM `familys`", "Family_Load", "");
		mysql_tquery(sqlcon, "SELECT * FROM `flat`", "Flat_Load", "");
		mysql_tquery(sqlcon, "SELECT * FROM `gates`", "Gate_Load", "");
		mysql_tquery(sqlcon, "SELECT * FROM `garage`", "Garage_Load", "");
		mysql_tquery(sqlcon, "SELECT * FROM `houses`", "House_Load", "");
		mysql_tquery(sqlcon, "SELECT * FROM `object`", "Object_Load");
		mysql_tquery(sqlcon, "SELECT * FROM `rental`", "Rental_Load", "");
		mysql_tquery(sqlcon, "SELECT * FROM `speedcameras`", "Speed_Load", "");
		mysql_tquery(sqlcon, "SELECT * FROM `tags`", "Tag_Load", "");
		mysql_tquery(sqlcon, "SELECT * FROM `trash`", "Trash_Load", "");
		mysql_tquery(sqlcon, "SELECT * FROM `tree`", "Tree_Load", "");
		mysql_tquery(sqlcon, "SELECT * FROM `weed`", "Weed_Load", "");
		mysql_tquery(sqlcon, "SELECT * FROM `workshop`", "Workshop_Load");
		mysql_tquery(sqlcon, "SELECT * FROM `rock`", "Rock_Load", "");
		mysql_tquery(sqlcon, "SELECT * FROM `factiongarage`", "FactionGarage_Load", "");
		mysql_tquery(sqlcon, "UPDATE `factiongaragevehs` SET `Spawned` = '0'");
		mysql_tquery(sqlcon, "SELECT * FROM `furniture`", "OnLoadFurniture", "");
		/* Load from Files */

		LoadServerData();
		LoadEconomyData();

		repeat WeatherRotator[1800000]();

		for (new i; i < sizeof(ColorList); i++) {
			format(color_string, sizeof(color_string), "%s{%06x}%03d %s", color_string, ColorList[i] >>> 8, i, ((i+1) % 16 == 0) ? ("\n") : (""));
		}
	}
	return 1;
}

public OnDynamicActorStreamIn(STREAMER_TAG_ACTOR:actorid, forplayerid)
{
	return 1;
}


public OnPlayerRequestSpawn(playerid)
{
    if (!IsPlayerAdmin(playerid))
    {
        KickEx(playerid);
        return 0;
    }
    return 1;
}

public OnPlayerRequestClass(playerid, classid) {

	if(!PlayerData[playerid][pLogged])
	{
		SetPlayerVirtualWorld(playerid, 99);
		PlayerCheck(playerid, g_RaceCheck{playerid});
		LewatClass[playerid] = true;
	}
	return 1;
}

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	if(PlayerData[playerid][pAdmin] > 0 && IsPlayerSpawned(clickedplayerid))
	{
		ShowPlayerStats(clickedplayerid, playerid);
	}
	return 1;
}
public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{

	new fid = PlayerData[playerid][pEditing], vid = PlayerData[playerid][pVehicle], slot = PlayerData[playerid][pListitem];
	if(playertextid == PLUSX[playerid])
	{
		if(IsPlayerInAnyVehicle(playerid))
		{
			VehicleObjects[vid][slot][vehObjectPosX] = VehicleObjects[vid][slot][vehObjectPosX] + 0.2;
			Streamer_SetFloatData(STREAMER_TYPE_OBJECT, VehicleObjects[vid][slot][vehObject], E_STREAMER_ATTACH_OFFSET_X, VehicleObjects[vid][slot][vehObjectPosX]);
		}
		else
		{
			if(PlayerData[playerid][pEditType] == EDIT_TAG)
			{
				TagData[fid][tagPos][0] = TagData[fid][tagPos][0]+0.2;
				Streamer_SetFloatData(STREAMER_TYPE_OBJECT, TagData[fid][tagObject], E_STREAMER_X, TagData[fid][tagPos][0]);
			}
			else
			{

				FurnitureData[fid][furniturePos][0] = FurnitureData[fid][furniturePos][0] + 0.2;

				Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FurnitureData[fid][furnitureObject], E_STREAMER_X, FurnitureData[fid][furniturePos][0]);
			}
		}
	}
	if(playertextid == MINX[playerid])
	{
		if(IsPlayerInAnyVehicle(playerid))
		{
			VehicleObjects[vid][slot][vehObjectPosX] = VehicleObjects[vid][slot][vehObjectPosX] - 0.2;
			Streamer_SetFloatData(STREAMER_TYPE_OBJECT,VehicleObjects[vid][slot][vehObject], E_STREAMER_ATTACH_OFFSET_X, VehicleObjects[vid][slot][vehObjectPosX]);
		}
		else
		{
			if(PlayerData[playerid][pEditType] == EDIT_TAG)
			{
				TagData[fid][tagPos][0] = TagData[fid][tagPos][0]-0.2;
				Streamer_SetFloatData(STREAMER_TYPE_OBJECT, TagData[fid][tagObject], E_STREAMER_X, TagData[fid][tagPos][0]);
			}
			else
			{

				FurnitureData[fid][furniturePos][0] = FurnitureData[fid][furniturePos][0] - 0.2;

				Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FurnitureData[fid][furnitureObject], E_STREAMER_X, FurnitureData[fid][furniturePos][0]);
			}
		}
	}
	if(playertextid == PLUSY[playerid])
	{
		if(IsPlayerInAnyVehicle(playerid))
		{
			VehicleObjects[vid][slot][vehObjectPosY] = VehicleObjects[vid][slot][vehObjectPosY] + 0.2;
			Streamer_SetFloatData(STREAMER_TYPE_OBJECT, VehicleObjects[vid][slot][vehObject], E_STREAMER_ATTACH_OFFSET_Y, VehicleObjects[vid][slot][vehObjectPosY]);
		}
		else
		{
			if(PlayerData[playerid][pEditType] == EDIT_TAG)
			{
				TagData[fid][tagPos][1] = TagData[fid][tagPos][1]+0.2;
				Streamer_SetFloatData(STREAMER_TYPE_OBJECT, TagData[fid][tagObject], E_STREAMER_Y, TagData[fid][tagPos][1]);
			}
			else
			{

				FurnitureData[fid][furniturePos][1] = FurnitureData[fid][furniturePos][1] + 0.2;

				Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FurnitureData[fid][furnitureObject], E_STREAMER_Y, FurnitureData[fid][furniturePos][1]);
			}
		}
	}
	if(playertextid == MINY[playerid])
	{
		if(IsPlayerInAnyVehicle(playerid))
		{
			VehicleObjects[vid][slot][vehObjectPosY] = VehicleObjects[vid][slot][vehObjectPosY] - 0.2;
			Streamer_SetFloatData(STREAMER_TYPE_OBJECT, VehicleObjects[vid][slot][vehObject], E_STREAMER_ATTACH_OFFSET_Y, VehicleObjects[vid][slot][vehObjectPosY]);

		}
		else
		{
			if(PlayerData[playerid][pEditType] == EDIT_TAG)
			{
				TagData[fid][tagPos][1] = TagData[fid][tagPos][1]-0.2;
				Streamer_SetFloatData(STREAMER_TYPE_OBJECT, TagData[fid][tagObject], E_STREAMER_Y, TagData[fid][tagPos][1]);
			}
			else
			{

				FurnitureData[fid][furniturePos][1] = FurnitureData[fid][furniturePos][1] - 0.2;

				Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FurnitureData[fid][furnitureObject], E_STREAMER_Y, FurnitureData[fid][furniturePos][1]);
			}
		}
	}
	if(playertextid == PLUSZ[playerid])
	{
		if(IsPlayerInAnyVehicle(playerid))
		{
			VehicleObjects[vid][slot][vehObjectPosZ] = VehicleObjects[vid][slot][vehObjectPosZ] + 0.2;
			Streamer_SetFloatData(STREAMER_TYPE_OBJECT, VehicleObjects[vid][slot][vehObject], E_STREAMER_ATTACH_OFFSET_Z, VehicleObjects[vid][slot][vehObjectPosZ]);

		}
		else
		{
			if(PlayerData[playerid][pEditType] == EDIT_TAG)
			{ 
				TagData[fid][tagPos][2] = TagData[fid][tagPos][2]+0.2;
				Streamer_SetFloatData(STREAMER_TYPE_OBJECT, TagData[fid][tagObject], E_STREAMER_Z, TagData[fid][tagPos][2]);
			}
			else
			{

				FurnitureData[fid][furniturePos][2] = FurnitureData[fid][furniturePos][2] + 0.2;

				Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FurnitureData[fid][furnitureObject], E_STREAMER_Z, FurnitureData[fid][furniturePos][2]);
			}
		}
	}
	if(playertextid == MINZ[playerid])
	{
		if(IsPlayerInAnyVehicle(playerid))
		{
			VehicleObjects[vid][slot][vehObjectPosZ] = VehicleObjects[vid][slot][vehObjectPosZ] - 0.2;
			Streamer_SetFloatData(STREAMER_TYPE_OBJECT, VehicleObjects[vid][slot][vehObject], E_STREAMER_ATTACH_OFFSET_Z, VehicleObjects[vid][slot][vehObjectPosZ]);
		}
		else
		{
			if(PlayerData[playerid][pEditType] == EDIT_TAG)
			{
				TagData[fid][tagPos][2] = TagData[fid][tagPos][2]-0.2;
				Streamer_SetFloatData(STREAMER_TYPE_OBJECT, TagData[fid][tagObject], E_STREAMER_Z, TagData[fid][tagPos][2]);
			}
			else
			{

				FurnitureData[fid][furniturePos][2] = FurnitureData[fid][furniturePos][2] - 0.2;

				Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FurnitureData[fid][furnitureObject], E_STREAMER_Z, FurnitureData[fid][furniturePos][2]);
			}
		}
	}
	if(playertextid == PLUSRX[playerid])
	{
		if(IsPlayerInAnyVehicle(playerid))
		{
			VehicleObjects[vid][slot][vehObjectPosRX] = VehicleObjects[vid][slot][vehObjectPosRX] + 0.2;
			Streamer_SetFloatData(STREAMER_TYPE_OBJECT, VehicleObjects[vid][slot][vehObject], E_STREAMER_ATTACH_R_X, VehicleObjects[vid][slot][vehObjectPosRX]);
		}
		else
		{
			if(PlayerData[playerid][pEditType] == EDIT_TAG)
			{
				TagData[fid][tagPos][3] = TagData[fid][tagPos][3]+0.2;
				Streamer_SetFloatData(STREAMER_TYPE_OBJECT, TagData[fid][tagObject], E_STREAMER_R_X, TagData[fid][tagPos][3]);
			}
			else
			{

				FurnitureData[fid][furnitureRot][0] = FurnitureData[fid][furnitureRot][0] + 0.2;

				Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FurnitureData[fid][furnitureObject], E_STREAMER_R_X, FurnitureData[fid][furnitureRot][0]);
			}
		}
	}
	if(playertextid == MINRX[playerid])
	{
		if(IsPlayerInAnyVehicle(playerid))
		{
			VehicleObjects[vid][slot][vehObjectPosRX] = VehicleObjects[vid][slot][vehObjectPosRX] - 0.2;
			Streamer_SetFloatData(STREAMER_TYPE_OBJECT, VehicleObjects[vid][slot][vehObject], E_STREAMER_ATTACH_R_X, VehicleObjects[vid][slot][vehObjectPosRX]);
		}
		else
		{
			if(PlayerData[playerid][pEditType] == EDIT_TAG)
			{
				TagData[fid][tagPos][3] = TagData[fid][tagPos][3]-0.2;
				Streamer_SetFloatData(STREAMER_TYPE_OBJECT, TagData[fid][tagObject], E_STREAMER_R_X, TagData[fid][tagPos][3]);
			}
			else
			{

				FurnitureData[fid][furnitureRot][0] = FurnitureData[fid][furnitureRot][0] - 0.2;

				Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FurnitureData[fid][furnitureObject], E_STREAMER_R_X, FurnitureData[fid][furnitureRot][0]);
			}
		}
	}
	if(playertextid == PLUSRY[playerid])
	{
		if(IsPlayerInAnyVehicle(playerid))
		{
			VehicleObjects[vid][slot][vehObjectPosRY] = VehicleObjects[vid][slot][vehObjectPosRY] + 0.2;
			Streamer_SetFloatData(STREAMER_TYPE_OBJECT, VehicleObjects[vid][slot][vehObject], E_STREAMER_ATTACH_R_Y, VehicleObjects[vid][slot][vehObjectPosRY]);
		}
		else
		{
			if(PlayerData[playerid][pEditType] == EDIT_TAG)
			{
				TagData[fid][tagPos][4] = TagData[fid][tagPos][4]+0.2;
				Streamer_SetFloatData(STREAMER_TYPE_OBJECT, TagData[fid][tagObject], E_STREAMER_R_Y, TagData[fid][tagPos][4]);
			}
			else
			{

				FurnitureData[fid][furnitureRot][1] = FurnitureData[fid][furnitureRot][1] + 0.2;

				Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FurnitureData[fid][furnitureObject], E_STREAMER_R_Y, FurnitureData[fid][furnitureRot][1]);
			}
		}
	}
	if(playertextid == MINRY[playerid])
	{
		if(IsPlayerInAnyVehicle(playerid))
		{
			VehicleObjects[vid][slot][vehObjectPosRY] = VehicleObjects[vid][slot][vehObjectPosRY] - 0.2;
			Streamer_SetFloatData(STREAMER_TYPE_OBJECT, VehicleObjects[vid][slot][vehObject], E_STREAMER_ATTACH_R_Y, VehicleObjects[vid][slot][vehObjectPosRY]);
		}
		else
		{
			if(PlayerData[playerid][pEditType] == EDIT_TAG)
			{
				TagData[fid][tagPos][4] = TagData[fid][tagPos][4]-0.2;
				Streamer_SetFloatData(STREAMER_TYPE_OBJECT, TagData[fid][tagObject], E_STREAMER_R_Y, TagData[fid][tagPos][4]);
			}
			else
			{

				FurnitureData[fid][furnitureRot][1] = FurnitureData[fid][furnitureRot][1] - 0.2;

				Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FurnitureData[fid][furnitureObject], E_STREAMER_R_Y, FurnitureData[fid][furnitureRot][1]);
			}
		}
	}
	if(playertextid == PLUSRZ[playerid])
	{
		if(IsPlayerInAnyVehicle(playerid))
		{
			VehicleObjects[vid][slot][vehObjectPosRZ] = VehicleObjects[vid][slot][vehObjectPosRZ] + 0.2;
			Streamer_SetFloatData(STREAMER_TYPE_OBJECT, VehicleObjects[vid][slot][vehObject], E_STREAMER_ATTACH_R_Z, VehicleObjects[vid][slot][vehObjectPosRZ]);
		}
		else
		{
			if(PlayerData[playerid][pEditType] == EDIT_TAG)
			{
				TagData[fid][tagPos][5] = TagData[fid][tagPos][5]+0.2;
				Streamer_SetFloatData(STREAMER_TYPE_OBJECT, TagData[fid][tagObject], E_STREAMER_R_Z, TagData[fid][tagPos][5]);
			}
			else
			{

				FurnitureData[fid][furnitureRot][2] = FurnitureData[fid][furnitureRot][2] + 0.2;

				Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FurnitureData[fid][furnitureObject], E_STREAMER_R_Z, FurnitureData[fid][furnitureRot][2]);
			}
		}
	}
	if(playertextid == MINRZ[playerid])
	{
		if(IsPlayerInAnyVehicle(playerid))
		{
			VehicleObjects[vid][slot][vehObjectPosRZ] = VehicleObjects[vid][slot][vehObjectPosRZ] - 0.2;
			Streamer_SetFloatData(STREAMER_TYPE_OBJECT, VehicleObjects[vid][slot][vehObject], E_STREAMER_ATTACH_R_Z, VehicleObjects[vid][slot][vehObjectPosRZ]);
		}
		else
		{
			if(PlayerData[playerid][pEditType] == EDIT_TAG)
			{
				TagData[fid][tagPos][5] = TagData[fid][tagPos][5]-0.2;
				Streamer_SetFloatData(STREAMER_TYPE_OBJECT, TagData[fid][tagObject], E_STREAMER_R_Z, TagData[fid][tagPos][5]);
			}
			else
			{

				FurnitureData[fid][furnitureRot][2] = FurnitureData[fid][furnitureRot][2] - 0.2;

				Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FurnitureData[fid][furnitureObject], E_STREAMER_R_Z, FurnitureData[fid][furnitureRot][2]);
			}
		}
	}
	if(playertextid == FINISHEDIT[playerid])
	{
		if(PlayerData[playerid][pEditing] != -1)
		{
			if(PlayerData[playerid][pEditType] == EDIT_TAG)
			{
				Tag_Save(fid);
			}
			else
			{
				Furniture_Save(fid);
			}
		}
		PlayerData[playerid][pEditing] = -1;
		PlayerData[playerid][pEditType] = EDIT_NONE;
		HideEditTextDraw(playerid);
	}
	return 1;
}


public OnGameModeExit()
{
	SaveServerStatistics();

	mysql_close(sqlcon);
	return 1;
}

public OnPlayerCommandReceived(playerid, cmdtext[])
{
	if(!IsPlayerSpawned(playerid))
		return 0;

	if(gettime() < cmd_floodProtect[playerid] && !PlayerData[playerid][pAdmin]) {
		ShowMessage(playerid, "~r~ERROR: ~w~Dilarang spam command!", 3, 1);
		return 0;
	}

	return 1;
}

public OnPlayerCommandPerformed(playerid, cmdtext[], success)
{
	printf("[CMD] %s: %s", GetName(playerid, false), cmdtext);
	
	if(!IsPlayerSpawned(playerid))
		return 0;

	if(gettime() < cmd_floodProtect[playerid] && !PlayerData[playerid][pAdmin]) {
		ShowMessage(playerid, "~r~ERROR: ~w~Dilarang spam command!", 3, 1);
		return 0;
	}

    if (!success) 
        return SendClientMessageEx(playerid, COLOR_GREY, "ERROR: Command \"%s\" is not found, check on \"/help\" please.", cmdtext);

	cmd_floodProtect[playerid] = gettime() + 2;
    return 1;
}
public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
	if(PlayerData[playerid][pAdmin] > 0 && PlayerData[playerid][pAduty])
	{
		if(PlayerData[playerid][pAdmin] >= 5)
		{
			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
				SetVehiclePos(GetPlayerVehicleID(playerid), fX, fY, fZ);

			else
				SetPlayerPosFindZ(playerid, fX, fY, fZ);
		}
		else if(PlayerData[playerid][pAdmin] > 0 && PlayerData[playerid][pAduty])
		{
			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
				SetVehiclePos(GetPlayerVehicleID(playerid), fX, fY, fZ);

			else
				SetPlayerPosFindZ(playerid, fX, fY, fZ);
		}
		
	}
	return 1;
}
public OnPlayerConnect(playerid)
{
	LewatClass[playerid] = false;

    if((GetTickCount() - PlayerData[playerid][pLeaveTime]) < 3000 && !strcmp(ReturnIP(playerid), UcpData[playerid][uLeaveIP]))
    {
        SendAdminMessage(X11_TOMATO_1, "AdmWarn: %s (%s) was kicked for possible rejoin hacks.", ReturnName(playerid), ReturnIP(playerid));
        KickEx(playerid);
        return 1;
    }

	ResetPlayerStatistics(playerid);
	PreloadAnimations(playerid);
	ResetFlyModeData(playerid);

	if(!IsNameUsed(playerid, GetName(playerid))) {

		g_RaceCheck{playerid} ++;
		CreatePlayerHUD(playerid);
		LoadRemoveBuilding(playerid);
		Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, 1000, playerid);
		LewatConnect[playerid] = true;
	}
	else Kick(playerid);
	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
    if(killerid != INVALID_PLAYER_ID)
    {
        if(1 <= reason <= 46)
            Log_Write("Logs/death_log.txt", sprintf("[%s] %s has killed %s (%s).", ReturnDate(), ReturnName(killerid), ReturnName(playerid), ReturnWeaponName(reason)));

        else
            Log_Write("Logs/death_log.txt", sprintf("[%s] %s has killed %s (reason %d).", ReturnDate(), ReturnName(killerid), ReturnName(playerid), reason));

        if(reason == 50 && killerid != INVALID_PLAYER_ID)
            SendAdminMessage(X11_TOMATO_1, "AdmWarn: %s has killed %s by heli-blading.", ReturnName(killerid), ReturnName(playerid));

        if(reason == 29 && killerid != INVALID_PLAYER_ID && GetPlayerState(killerid) == PLAYER_STATE_DRIVER)
            SendAdminMessage(X11_TOMATO_1, "AdmWarn: %s has killed %s by driver shooting.", ReturnName(killerid), ReturnName(playerid));
    }

	if(killerid != INVALID_PLAYER_ID && !IsPlayerSpawned(killerid)) {
		Kick(killerid);
		return 1;
	}

    if(IsPlayerSpawned(playerid))
    {
		if(PlayerData[playerid][pVendor] != -1)
		{
			if(IsValidDynamicActor(VendorData[PlayerData[playerid][pVendor]][vendorActor]))
				DestroyDynamicActor(VendorData[PlayerData[playerid][pVendor]][vendorActor]);

			VendorData[PlayerData[playerid][pVendor]][vendorReqFood] = FOOD_NONE;
			VendorData[PlayerData[playerid][pVendor]][vendorReqDrink] = DRINK_NONE;
			VendorData[PlayerData[playerid][pVendor]][vendorFood] = FOOD_NONE;
			VendorData[PlayerData[playerid][pVendor]][vendorDrink] = DRINK_NONE;
			PlayerData[playerid][pVendor] = -1;
		}
		if(IsValidDynamicObject(StretcherEquipped[playerid]))
		{
			DestroyDynamicObject(StretcherEquipped[playerid]);
			StretcherEquipped[playerid] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
			StretcherHolding[playerid] = 0;
			if(StretcherPlayerID[playerid] != INVALID_PLAYER_ID)
			{
				TogglePlayerControllable(StretcherPlayerID[playerid], 1);
				ClearAnimations(StretcherPlayerID[playerid], 1);
				
				StretcherPlayerID[playerid] = INVALID_PLAYER_ID;
			}
		}
		if(PlayerData[playerid][pInTaxi]) {

			new vehicleid = PlayerData[playerid][pTaxiVehicleID];

			new 
				driverid = GetVehicleDriver(vehicleid);

			if(driverid != INVALID_PLAYER_ID) {
				
				GiveMoney(driverid, PlayerData[playerid][pTotalFare], "Dari penumpang taxi.");
				GiveMoney(playerid, -PlayerData[playerid][pTotalFare], "Membayar taxi.");
				SendClientMessageEx(playerid, COLOR_SERVER, "(Taxi) {FFFFFF}Kamu membayar {00FF00}$%s {FFFFFF}kepada pengemudi taxi.", FormatNumber(PlayerData[playerid][pTotalFare]));
				SendClientMessageEx(driverid, COLOR_SERVER, "(Taxi) {FFFFFF}Kamu mendapatkan {00FF00}$%s {FFFFFF}dari penumpang taxi.", FormatNumber(PlayerData[playerid][pTotalFare]));
				PlayerData[driverid][pTotalFare] = 0;
				PlayerTextDrawSetString(driverid, FARETOTALTD[driverid], "Trip_Fare:_~g~$0");
			}
			KillTimer(PlayerData[playerid][pFareTimer]);
			PlayerData[playerid][pTotalFare] = 0;
			PlayerData[playerid][pInTaxi] = false;
			HideTaxi(playerid);
		}
    }
	foreach(new i : Player) if(PlayerData[i][pAdmin] > 0)
    {
        SendDeathMessageToPlayer(i, killerid, playerid, reason);
    }
    return 1;
}

public OnPlayerDisconnectEx(playerid) {

	if(Biz_GetCount(playerid)) {
		for(new i = 0; i < MAX_BUSINESS; i++) if(BizData[i][bizExists] && Biz_IsOwner(playerid, i)) {

			BizData[i][bizLastLogin] = gettime() + (10 * 86400);

			Business_Save(i);
		}
	}

	if(House_GetCount(playerid)) {
		foreach(new i : House) if(House_IsOwner(playerid, i)) {
			HouseData[i][houseLastLogin] = gettime() + (10 * 86400);
			House_Save(i);
		}
	}

	if(Flat_GetCount(playerid)) {
		foreach(new i : Flat) if(Flat_IsOwner(playerid, i)) {
			FlatData[i][flatLastLogin] = gettime() + (10 * 86400);
			Flat_Save(i);
		}
	}

    foreach(new id : Player) if(PlayerData[id][pSpectator] == playerid && GetPlayerState(id) == PLAYER_STATE_SPECTATING)
    {
		SendServerMessage(id, "User %s(%s) is disconnected from server.", GetName(playerid, false), GetUsername(playerid));
        cmd_unspec(id, "\0");
    }
	if(OnTrash[playerid] > 0)
	{
		new vehicleid = PlayerData[playerid][pTrashVehicleID];
	
		LoadedTrash[vehicleid] = 0;
		VehicleData[vehicleid][vFuel] = 100;

		if(IsTrashmasterVehicle(vehicleid) && GetPlayerVehicleID(playerid) == vehicleid)
			SetVehicleToRespawn(vehicleid);
	
		for(new i = 0 ; i < MAX_TRASH; i++) if(IsValidDynamicMapIcon(TrashIcons[playerid][i]))
		{
			DestroyDynamicMapIcon(TrashIcons[playerid][i]);
			TrashIcons[playerid][i] = STREAMER_TAG_MAP_ICON:INVALID_STREAMER_ID;
		}
	} 
	if(HasTrash[playerid])
		Trash_ResetPlayer(playerid);

	if(PlayerData[playerid][pInTaxi])
		KillTimer(PlayerData[playerid][pFareTimer]);

	if(PlayerData[playerid][pCrate] != -1)
	{
		Crate_Delete(PlayerData[playerid][pCrate]);
	}
	if (PlayerData[playerid][pCallLine] != INVALID_PLAYER_ID)
    	CancelCall(playerid);

	if(IsValidDynamic3DTextLabel(PlayerData[playerid][pMaskLabel]))
		DestroyDynamic3DTextLabel(PlayerData[playerid][pMaskLabel]);

	if(PlayerData[playerid][pVendor] != -1)
	{
		if(IsValidDynamicActor(VendorData[PlayerData[playerid][pVendor]][vendorActor]))
			DestroyDynamicActor(VendorData[PlayerData[playerid][pVendor]][vendorActor]);

		VendorData[PlayerData[playerid][pVendor]][vendorReqFood] = FOOD_NONE;
		VendorData[PlayerData[playerid][pVendor]][vendorReqDrink] = DRINK_NONE;
		VendorData[PlayerData[playerid][pVendor]][vendorFood] = FOOD_NONE;
		VendorData[PlayerData[playerid][pVendor]][vendorDrink] = DRINK_NONE;
		PlayerData[playerid][pVendor] = -1;
	}
	if(PlayerData[playerid][pOnDMV])
	{
		PlayerData[playerid][pOnDMV] = false;
		PlayerData[playerid][pIndexDMV] = -1;

		if(IsValidVehicle(PlayerData[playerid][pVehicleDMV]))
			DestroyVehicleEx(PlayerData[playerid][pVehicleDMV]);

	}

	foreach(new i : Player) if(IsDragging[i] == playerid)
	{
		IsDragging[i] = INVALID_PLAYER_ID;
		break;
	}

	if(IsDragging[playerid] != INVALID_PLAYER_ID && IsPlayerConnected(IsDragging[playerid]))
	{
		TogglePlayerControllable(IsDragging[playerid], 1);
	}

	if(IsValidDynamic3DTextLabel(PlayerData[playerid][pAdoLabel]))
		DestroyDynamic3DTextLabel(PlayerData[playerid][pAdoLabel]);

	DestroyBoombox(playerid);
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{	

	SQL_SaveCharacter(playerid);
	
	if(LoginTimer[playerid] != 0) {
		KillTimer(LoginTimer[playerid]);
	}

	new const reason_text[][] = {
		"Timeout/Crash",
		"Leaving",
		"Kicked/Banned"
	};
	SendNearbyMessage(playerid, 15.0, COLOR_GREY, "* %s has disconnected from server (%s)", ReturnName(playerid), reason_text[reason]);

	CallLocalFunction("OnPlayerDisconnectEx", "d", playerid);

    PlayerData[playerid][pLeaveTime] = GetTickCount();
    format(UcpData[playerid][uLeaveIP], 16, ReturnIP(playerid));
	return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(oldstate == PLAYER_STATE_DRIVER)
	{
		if(IsValidDynamicMapIcon(FactoryIcons[playerid]))
		{
			DestroyDynamicMapIcon(FactoryIcons[playerid]);
			FactoryIcons[playerid] = -1;
		}		
				
		for(new i = 0; i < MAX_TRASH; i++) if(IsValidDynamicMapIcon(TrashIcons[playerid][i]))
		{
			DestroyDynamicMapIcon(TrashIcons[playerid][i]);
			TrashIcons[playerid][i] = STREAMER_TAG_MAP_ICON:INVALID_STREAMER_ID;
		}

		TogglePlayerDynamicCP(playerid, FactoryCP, 0);

		PlayerTextDrawHide(playerid, CapacityText[playerid]);
		HidePlayerProgressBar(playerid, CapacityBar[playerid]);

		Trash_ResetPlayer(playerid);
		new vehicleid = PlayerData[playerid][pLastVehicleID];
		if(OnMower[playerid] && IsMowerVehicle(vehicleid))
		{
			SetVehicleToRespawn(vehicleid);
			VehicleData[vehicleid][vFuel] = 100;
			SendClientMessage(playerid, COLOR_SERVER, "(Sidejob) {FFFFFF}Kamu gagal bekerja sebagai {FFFF00}Mower {FFFFFF}karena mencoba keluar dari kendaraan!");
			OnMower[playerid] = false;
			MowerIndex[playerid] = 0;
			DisablePlayerCheckpoint(playerid);
		}

		if(OnSweeping[playerid] && IsSweeperVehicle(vehicleid))
		{
			SetVehicleToRespawn(vehicleid);
			VehicleData[vehicleid][vFuel] = 100;
			SendClientMessage(playerid, COLOR_SERVER, "(Sidejob) {FFFFFF}Kamu gagal bekerja sebagai {FFFF00}Street Sweeper {FFFFFF}karena mencoba keluar dari kendaraan!");
			OnSweeping[playerid] = false;
			SweeperIndex[playerid] = 0;
			DisablePlayerCheckpoint(playerid);
		}
		if(IsPlayerWorkInBus(playerid) && (IsBusVehicle(vehicleid) || IsBus2Vehicle(vehicleid)))
		{
			RespawnPlayerBusVehicle(playerid);
			SendClientMessage(playerid, COLOR_SERVER, "(Sidejob) {FFFFFF}Kamu gagal bekerja sebagai {FFFF00}Bus Driver {FFFFFF}karena mencoba keluar dari kendaraan!");
			OnBus[playerid] = false;
			BusIndex[playerid] = 0;
			DisablePlayerRaceCheckpoint(playerid);
		}
		if(PlayerData[playerid][pOnDMV] && vehicleid == PlayerData[playerid][pVehicleDMV])
		{
			PlayerData[playerid][pOnDMV] = false;
			PlayerData[playerid][pIndexDMV] = -1;
			DestroyVehicleEx(PlayerData[playerid][pVehicleDMV]);
			SendClientMessage(playerid, COLOR_SERVER, "(DMV) {FFFFFF}Kamu gagal dalam tes mengemudi karena mencoba keluar dari kendaraan!");
		}
	}
	if(newstate == PLAYER_STATE_DRIVER)
	{
	    new vehicleid = GetPlayerVehicleID(playerid);
	    SetPlayerArmedWeapon(playerid, 0);
		EnterVehicle[playerid]++;
		PlayerTextDrawSetString(playerid, AMMOTD[playerid], "_");

		if(!PlayerData[playerid][pLicense][0])
			SendClientMessage(playerid, X11_TOMATO, "(Warning) "YELLOW"Kamu tidak memiliki "CYAN"lisensi mengemudi! "YELLOW"kamu bisa saja terkena tilang oleh SA-PD.");
	    
		if(IsEngineVehicle(vehicleid) && IsSpeedoVehicle(vehicleid) && !PlayerData[playerid][pTogHud])
	    {
			ShowPlayerHUD(playerid);
		}
		if(!IsEngineVehicle(vehicleid))
		{
		    SwitchVehicleEngine(vehicleid, true);
		}
		if(EnterVehicle[playerid] > 3 && !PlayerData[playerid][pKicked]) {
			SendAdminMessage(X11_TOMATO, "AntiCheat: Cheat detected on {FFFF00}%s (%s) {FF6347}(Vehicle Spam)", GetName(playerid), PlayerData[playerid][pUCP]);
			KickEx(playerid);
		}
		if(Iter_Contains(Vehicle, vehicleid) && Vehicle_GetType(vehicleid) == VEHICLE_TYPE_PLAYER && VehicleData[vehicleid][vLocked]) {
			RemovePlayerFromVehicle(playerid);
			SendErrorMessage(playerid, "Kendaraan ini masih dikunci!");
		}
		if(Iter_Contains(Vehicle, vehicleid) && Vehicle_GetType(vehicleid) == VEHICLE_TYPE_PLAYER && VehicleData[vehicleid][vTireLock]) {
			RemovePlayerFromVehicle(playerid);
			SendErrorMessage(playerid, "Kendaraan ini sedang di tire-locked!");
		}
		if(IsSweeperVehicle(vehicleid))
		{
			if(!OnSweeping[playerid])
			{	
				if(PlayerData[playerid][pMasked])
					return SendErrorMessage(playerid, "Buka maskermu terlebih dahulu!"), RemovePlayerFromVehicle(playerid);

				if(PlayerData[playerid][pSweeperDelay] > 0)
					return SendErrorMessage(playerid, "Kamu harus menunggu %d menit sebelum bekerja kembali!", PlayerData[playerid][pSweeperDelay]/60), RemovePlayerFromVehicle(playerid);

				if(IsHungerOrThirst(playerid))
					return SendErrorMessage(playerid, "Kamu terlalu lelah untuk bekerja.");

				ShowPlayerDialog(playerid, DIALOG_SWEEPER, DIALOG_STYLE_MSGBOX, "{FFFFFF}Sweeper Sidejob", "{FFFFFF}Pekerjaan ini mengharuskan kamu untuk mengikuti semua petunjuk(Checkpoint)\nSelalu gunakan RP Drive & jangan abuse kendaraan jika tidak ingin\nDi beri punishment oleh {FF0000}Administrator","Start", "Cancel");
			}
		}		
		if(IsMowerVehicle(vehicleid))
		{
			if(!OnMower[playerid])
			{	

				if(PlayerData[playerid][pMasked])
					return SendErrorMessage(playerid, "Buka maskermu terlebih dahulu!"), RemovePlayerFromVehicle(playerid);

				if(PlayerData[playerid][pMowerDelay] > 0)
					return SendErrorMessage(playerid, "Kamu harus menunggu %d menit sebelum bekerja kembali!", PlayerData[playerid][pMowerDelay]/60), RemovePlayerFromVehicle(playerid);


				if(IsHungerOrThirst(playerid))
					return SendErrorMessage(playerid, "Kamu terlalu lelah untuk bekerja.");

				ShowPlayerDialog(playerid, DIALOG_MOWER, DIALOG_STYLE_MSGBOX, "{FFFFFF}Mower Sidejob", "{FFFFFF}Pekerjaan ini mengharuskan kamu untuk mengikuti semua petunjuk(Checkpoint)\nSelalu gunakan RP Drive & jangan abuse kendaraan jika tidak ingin\nDi beri punishment oleh {FF0000}Administrator","Start", "Cancel");
			}
		}		
		if(IsTrashmasterVehicle(vehicleid))
		{
			if(OnTrash[playerid] < 1)
			{
				if(PlayerData[playerid][pMasked])
					return SendErrorMessage(playerid, "Buka maskermu terlebih dahulu!"), RemovePlayerFromVehicle(playerid);

				if(PlayerData[playerid][pTrashmasterDelay] > 0)
					return SendErrorMessage(playerid, "Kamu harus menunggu %d menit sebelum bekerja kembali!", PlayerData[playerid][pTrashmasterDelay]/60), RemovePlayerFromVehicle(playerid);

				if(IsHungerOrThirst(playerid))
					return SendErrorMessage(playerid, "Kamu terlalu lelah untuk bekerja.");

				ShowPlayerDialog(playerid, DIALOG_TRASH, DIALOG_STYLE_MSGBOX, "Trashmaster Sidejob", "Pekerjaan ini mengharuskan kamu untuk mengambil sampah dan mengirimnya ke pengelolahan sampah kota!", "Start", "Cancel");
			}
		}
	    if(IsTrashmasterVehicle(vehicleid) && OnTrash[playerid] > 0)
	    {
		    if(LoadedTrash[vehicleid] > 9)
		    {
				SendClientMessage(playerid, COLOR_JOB, "(Trashmaster) {FFFFFF}Kamu dapat menjual semua kantong sampah pada tanda truk di-peta.");
				
				for(new i = 0; i < MAX_TRASH; i++) if(IsValidDynamicMapIcon(TrashIcons[playerid][i]))
				{
					DestroyDynamicMapIcon(TrashIcons[playerid][i]);
					TrashIcons[playerid][i] = -1;
				}

				FactoryIcons[playerid] = CreateDynamicMapIcon(-1864.8846, -1668.9028, 22.3015 + 0.5, 51, 0, _, _, playerid, 8000.0, MAPICON_GLOBAL);
				TogglePlayerDynamicCP(playerid, FactoryCP, 1);
				OnTrash[playerid] = 2;
		    }
		    else
		    {
		        SendClientMessage(playerid, COLOR_JOB, "(Trashmaster) {FFFFFF}Kamu dapat mengumpulkan kantong sampah lalu menjualnya ke pabrik daur ulang.");
		        SendClientMessage(playerid, COLOR_JOB, "(Trashmaster) {FFFFFF}Cari tempat sampah lalu ambil kantong sampah dengan "YELLOW"/pickup");
		    	
				for(new i = 0; i < MAX_TRASH; i++) if(TrashData[i][TrashExists] && TrashData[i][TrashLevel] > 0)
				{					
					TrashIcons[playerid][i] = CreateDynamicMapIcon(TrashData[i][TrashX], TrashData[i][TrashY], TrashData[i][TrashZ] + 0.5, 56, 0, _, _, playerid, 8000.0, MAPICON_GLOBAL);
				}	

				PlayerData[playerid][pTrashVehicleID] = GetPlayerVehicleID(playerid);		
			}
						
			Trash_ShowCapacity(playerid);
		}
		if(Vehicle_GetType(vehicleid) == VEHICLE_TYPE_FACTION && VehicleData[vehicleid][vFactionType] != GetFactionType(playerid)) {
			if(PlayerData[playerid][pAdmin] && PlayerData[playerid][pAduty]) {
				SendAdminAction(playerid, "Ini adalah kendaraan faction, anda tetap bisa mengemudikannya karena sedang admin duty.");
			}
			else {
				RemovePlayerFromVehicle(playerid);
				SendErrorMessage(playerid, "Kamu tidak dapat mengendarai ini (kendaraan faction)");
			}
		}
	    foreach (new i : Player) if (PlayerData[i][pSpectator] == playerid) 
	    {
     		PlayerSpectateVehicle(i, GetPlayerVehicleID(playerid));
		}
	}
	if(newstate == PLAYER_STATE_PASSENGER)
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		new driverid = INVALID_PLAYER_ID;
  		SetPlayerArmedWeapon(playerid, 0);
		PlayerTextDrawSetString(playerid, AMMOTD[playerid], "_");

		if((driverid = GetVehicleDriver(vehicleid)) != INVALID_PLAYER_ID) {

			if((PlayerData[driverid][pJob] == JOB_TAXI || PlayerData[driverid][pJob2] == JOB_TAXI) && PlayerData[driverid][pJobduty])
			{
				CreateTaxi(playerid);
				PlayerData[playerid][pFareTimer] = SetTimerEx("UpdateFare", 7000, true, "ii", playerid, driverid);
				SendClientMessageEx(driverid, COLOR_SERVER, "(Taxi) "YELLOW"%s "WHITE"telah memasuki taksimu.", ReturnName(playerid));
				PlayerData[playerid][pInTaxi] = true;
				PlayerData[playerid][pTaxiVehicleID] = vehicleid;
			}
			if((IsBusVehicle(vehicleid) || IsBus2Vehicle(vehicleid))) {
				GiveMoney(playerid, -100, "Bayar bus");
				GiveMoney(driverid, 100, "Dari penumpang bus");

				SendServerMessage(driverid, ""YELLOW"%s "WHITE"telah menjadi penumpang di Bus-mu dan membayar "GREEN"$1.00", ReturnName(playerid));
				SendServerMessage(playerid, "Uang-mu dikurangi "GREEN"$1.00 "WHITE"karena menjadi penumpang di Bus.");
			}
		}
	    foreach (new i : Player) if (PlayerData[i][pSpectator] == playerid) 
	    {
     		PlayerSpectateVehicle(i, GetPlayerVehicleID(playerid));
		}
	}
	if (oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER)
	{
	    foreach (new i : Player) if (PlayerData[i][pSpectator] == playerid)
		{
     		PlayerSpectatePlayer(i, playerid);
		}
		if(StretcherHolding[playerid] == 1)
		{
			AttachDynamicObjectToPlayer(StretcherEquipped[playerid], playerid, 0.0, 1.5, -1.0, 0.0, 0.0, 180.0);
			StretcherHolding[playerid] = 2;
		}
	}
	if(oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER && newstate == PLAYER_STATE_ONFOOT)
	{
		new vehicleid = INVALID_VEHICLE_ID;

		if(StretcherHolding[playerid]) {

 			SpawnStretcher(playerid);
		}

		if(PlayerData[playerid][pInTaxi]) {

			vehicleid = PlayerData[playerid][pTaxiVehicleID];

			new 
				driverid = GetVehicleDriver(vehicleid);

			if(driverid != INVALID_PLAYER_ID) {
				
				GiveMoney(driverid, PlayerData[playerid][pTotalFare], "Dari penumpang taxi.");
				GiveMoney(playerid, -PlayerData[playerid][pTotalFare], "Membayar taxi.");
				SendClientMessageEx(playerid, COLOR_SERVER, "(Taxi) {FFFFFF}Kamu membayar {00FF00}$%s {FFFFFF}kepada pengemudi taxi.", FormatNumber(PlayerData[playerid][pTotalFare]));
				SendClientMessageEx(driverid, COLOR_SERVER, "(Taxi) {FFFFFF}Kamu mendapatkan {00FF00}$%s {FFFFFF}dari penumpang taxi.", FormatNumber(PlayerData[playerid][pTotalFare]));
				PlayerData[driverid][pTotalFare] = 0;
				PlayerTextDrawSetString(driverid, FARETOTALTD[driverid], "Trip_Fare:_~g~$0");
			}
			KillTimer(PlayerData[playerid][pFareTimer]);
			PlayerData[playerid][pTotalFare] = 0;
			PlayerData[playerid][pInTaxi] = false;
			HideTaxi(playerid);
		}
		Aksesoris_Sync(playerid);

	}
	if (newstate == PLAYER_STATE_WASTED && PlayerData[playerid][pJailTime] < 1)
	{
		if(PlayerData[playerid][pInjured])
		{
			PlayerData[playerid][pDead] = true;
			PlayerData[playerid][pInjured] = false;
		}
		else 
		{
			PlayerData[playerid][pInterior] = GetPlayerInterior(playerid);
			PlayerData[playerid][pWorld] =  GetPlayerVirtualWorld(playerid);
			PlayerData[playerid][pInjured] = true;
			GetPlayerPos(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);
			SetSpawnInfo(playerid, 0, PlayerData[playerid][pSkin], PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2], 0.0, 0, 0, 0, 0, 0, 0);
			SQL_SaveCharacter(playerid);
		
		}
	}
	if(oldstate == PLAYER_STATE_DRIVER)
	{
		for(new i = 4; i < 11; i++) 
			PlayerTextDrawHide(playerid, HUDTD[playerid][i]);

		PlayerTextDrawHide(playerid, VHPTD[playerid]);
		PlayerTextDrawHide(playerid, FUELTD[playerid]);
		PlayerTextDrawHide(playerid, ENGINETD[playerid]);
		PlayerTextDrawHide(playerid, KMHTD[playerid]);
		PlayerTextDrawHide(playerid, VEHNAMETD[playerid]);
		PlayerTextDrawHide(playerid, LOCATIONTD[playerid]);
		PlayerTextDrawHide(playerid, SPEEDO_2[playerid]);

		for(new i = 0; i < 6; i++) {
			PlayerTextDrawHide(playerid, HBE3_SPEEDO[playerid][i]);
		}

		if(IsValidPlayerProgressBar(playerid, PROGRESS_FUEL[playerid]))
			DestroyPlayerProgressBar(playerid, PROGRESS_FUEL[playerid]);
			
		if(PlayerData[playerid][pJobduty] && (PlayerData[playerid][pJob] == JOB_TAXI || PlayerData[playerid][pJob2] == JOB_TAXI))
		{
			HideTaxi(playerid);
			PlayerData[playerid][pJobduty] = false;
			SetPlayerColor(playerid, COLOR_WHITE);
		}
	}
	if(newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER)
	{
	    new vehicleid = GetPlayerVehicleID(playerid);

		if(!isnull(vehicleStream[vehicleid]) && PlayerData[playerid][pStreamType] == MUSIC_NONE && !PlayerData[playerid][pTogMusic])
  		{
  		    PlayerData[playerid][pStreamType] = MUSIC_VEHICLE;
    		PlayAudioStreamForPlayer(playerid, vehicleStream[vehicleid]);
      		SendServerMessage(playerid, "Kamu sekarang menyetel ke radio kendaraan ini. '/stopmusic' untuk berhenti mendengarkan.");
	    }
		PlayerData[playerid][pLastVehicleID] = vehicleid;
		PlayerTextDrawSetString(playerid, AMMOTD[playerid], "_");
		Aksesoris_Sync(playerid);

	}
	return 1;
}

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid) {

	foreach (new i : Player) if (PlayerData[i][pSpectator] == playerid) 
	{
		PlayerSpectatePlayer(i, playerid);
	}
	return 1;
}

public CustomSelectionResponse(playerid, extraid, modelid, response) 
{
	if((response) && (extraid == MODEL_SELECTION_FURNITURE)) 
	{
		new furniture;

		new
		    Float:x,
		    Float:y,
		    Float:z,
		    Float:angle;

        GetPlayerPos(playerid, x, y, z);
        GetPlayerFacingAngle(playerid, angle);

        x += 3.0 * floatsin(-angle, degrees);
        y += 3.0 * floatcos(-angle, degrees);

		new price = Furniture_ReturnPrice(PlayerData[playerid][pListitem]);

		if (GetMoney(playerid) < price)
			return SendErrorMessage(playerid, "You have insufficient funds for the purchase.");

		if(House_Inside(playerid) != -1)
			furniture = Furniture_Add(HouseData[House_Inside(playerid)][houseID], GetFurnitureNameByModel(modelid), GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), modelid, FURNITURE_TYPE_HOUSE, x, y, z, 0.0, 0.0, angle);
		else
			furniture = Furniture_Add(FlatData[Flat_Inside(playerid)][flatID], GetFurnitureNameByModel(modelid), GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), modelid, FURNITURE_TYPE_FLAT, x, y, z, 0.0, 0.0, angle);
		
		if(furniture == INVALID_ITERATOR_SLOT)
			return SendErrorMessage(playerid, "Server tidak dapat membuat lebih banyak furniture! (Laporkan kepada developer untuk meningkatkan limit)");

		GiveMoney(playerid, -price, "Membeli furniture");
		SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Furniture) "WHITE"Kamu berhasil membeli "YELLOW"%s "WHITE"dengan harga "GREEN"$%s", GetFurnitureNameByModel(modelid), FormatNumber(price));
		Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
	}
	if ((response) && (extraid == MODEL_SELECTION_MODSHOP))
	{
		if(IsValidVehicle(PlayerData[playerid][pVehicle])) {
			new 
				price = 8000,
				vehicleid
			;

			if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
				return SendErrorMessage(playerid, "You need to be inside vehicle as driver");

			vehicleid = PlayerData[playerid][pVehicle];

			if(GetMoney(playerid) < 8000)
				return SendErrorMessage(playerid, "Kamu membutuhkan $80,00 untuk membeli vehicle attachments.");

			if(Vehicle_ObjectAdd(playerid, vehicleid, modelid, OBJECT_TYPE_BODY)) SendClientMessageEx(playerid, X11_LIGHTBLUE, "(V-Attachment) "WHITE"Berhasil membeli attachment kendaraan "YELLOW"(%s)", GetVehObjectNameByModel(modelid));
			else SendErrorMessage(playerid, "Tidak ada slot attachment untuk kendaraan ini lagi.");

			new str[96];
			format(str, sizeof(str), "bought vehicle attachment \"%s\"", GetVehObjectNameByModel(modelid));

			GiveMoney(playerid, -price, str);
			SendClientMessage(playerid, X11_LIGHTBLUE, "(V-Attachment) "WHITE"Gunakan "GREEN"/v attachment "WHITE"untuk mengatur!");
		}
	}
	return 1;
}
public OnModelSelectionResponse(playerid, extraid, index, modelid, response)
{
	if((response) && (extraid == MODEL_SELECTION_ROADBLOCK)) {
		
			static
				Float:fX,Float:fY,Float:fZ;
			
			new bindex;
			if((bindex = Barricade_Create(playerid, 2, modelid, "-")) != -1) 
			{
				SendFactionMessage(PlayerData[playerid][pFaction], COLOR_RADIO, "[RADIO] %s has dropped a roadblock at %s. (( ID %d ))", ReturnName(playerid), GetLocation(fX, fY, fZ), bindex);
				PlayerData[playerid][pEditType] = EDIT_ROADBLOCK;
				PlayerData[playerid][pEditing] = bindex;
				EditDynamicObject(playerid, BarricadeData[bindex][cadeObject]);
			}
			else 
			{
				SendErrorMessage(playerid, "Roadblock sudah mencapai batas maksimal ("#MAX_DYNAMIC_ROADBLOCK" roadblock).");
			}
	}
	if ((response) && (extraid == MODEL_SELECTION_FACTION_SKINS))
	{
	    ShowPlayerDialog(playerid, DIALOG_EDITLOCKER_SKIN, DIALOG_STYLE_LIST, "Edit Skin", "Add by Model ID\nAdd by Thumbnail\nClear Slot", "Select", "Cancel");
	    PlayerData[playerid][pSelectedSlot] = index;
	}
	if(extraid == MODEL_SELECTION_BUYSKIN)
	{
		if(response)
		{
	        GiveMoney(playerid, -PlayerData[playerid][pSkinPrice], "Membeli skin");
			cmd_ame(playerid, sprintf("* %s has paid $%s and purchased a %s.", ReturnName(playerid), FormatNumber(PlayerData[playerid][pSkinPrice]), ProductName[PlayerData[playerid][pInBiz]][0]));
			BizData[PlayerData[playerid][pInBiz]][bizStock]--;		
			BizData[PlayerData[playerid][pInBiz]][bizVault] += PlayerData[playerid][pSkinPrice];
			UpdatePlayerSkin(playerid, modelid);	
		}
	}
	if((response) && (extraid == MODEL_SELECTION_ACC))
	{
		if(response)
		{
			Aksesoris_Create(playerid, modelid, GetAksesorisNameByModel(modelid));

			GiveMoney(playerid, -PlayerData[playerid][pSkinPrice]);
			cmd_ame(playerid, sprintf("* %s has paid $%s and purchased a %s.", ReturnName(playerid), FormatNumber(PlayerData[playerid][pSkinPrice]), ProductName[PlayerData[playerid][pInBiz]][1]));
			BizData[PlayerData[playerid][pInBiz]][bizStock]--;		
			BizData[PlayerData[playerid][pInBiz]][bizVault] += PlayerData[playerid][pSkinPrice];
		}
	}
	if ((response) && (extraid == MODEL_SELECTION_FACTION_SKIN))
	{
	    new factionid = PlayerData[playerid][pFaction];

		if (factionid == -1 || !IsNearFactionLocker(playerid))
	    	return 0;

		if (modelid == 19300)
		    return SendErrorMessage(playerid, "There is no model in the selected slot.");

  		SetFactionSkin(playerid, modelid);
		SendNearbyMessage(playerid, 10.0,X11_PLUM, "** %s has changed their uniform.", ReturnName(playerid));
	}

	if ((response) && (extraid == MODEL_SELECTION_COLOR_1))
	{
		PlayerData[playerid][pColor1] = modelid;

		static
			colors[256];

		for (new i = 0; i < sizeof(colors); i ++)
		{
			colors[i] = i;
		}
		ShowColorSelectionMenu(playerid, MODEL_SELECTION_COLOR_2, colors);

		SendClientMessage(playerid, X11_LIGHTBLUE, "(Mechanic) "WHITE"Silahkan pilih warna kedua untuk dicat ke kendaraan.");
	}
	if((response) && (extraid == MODEL_SELECTION_COLOR_2)) {

        if (PlayerData[playerid][pVehicle] == INVALID_VEHICLE_ID)
		    return SendErrorMessage(playerid, "You are not standing near any vehicle.");

        PlayerData[playerid][pColor2] = modelid;

		GiveWeaponToPlayer(playerid, 41, 3000, 3000);
        SendServerMessage(playerid, "Semprot kendaraan menggunakan "RED"kaleng cat "WHITE"yang telah diberikan!");
		PlayerData[playerid][pSpraying] = true;
	}
	if ((response) && (extraid == MODEL_SELECTION_ADD_SKIN))
	{
	    FactionData[PlayerData[playerid][pFactionEdit]][factionSkins][PlayerData[playerid][pSelectedSlot]] = modelid;
		Faction_Save(PlayerData[playerid][pFactionEdit]);

		SendServerMessage(playerid, "You have set the skin ID in slot %d to %d.", PlayerData[playerid][pSelectedSlot], modelid);
	}
	if(extraid == MODEL_SELECTION_SPAWN)
	{
		if(response)
		{
			PlayerData[playerid][pSkin] = modelid;	
			ShowCharacterSetup(playerid);
		}
	}
	return 1;
}

public OnPlayerShootDynamicObject(playerid, weaponid, STREAMER_TAG_OBJECT:objectid, Float:x, Float:y, Float:z) {

    if(GetWeapon(playerid) == weaponid && weaponid >= 22  && weaponid <= 38)
    {
		if(PlayerData[playerid][pAmmo][g_aWeaponSlots[weaponid]]) {
			if(--PlayerData[playerid][pAmmo][g_aWeaponSlots[weaponid]] == 0) {
				PlayerData[playerid][pAmmo][g_aWeaponSlots[weaponid]] = 0;
				SetPlayerArmedWeapon(playerid, 0);
				SendServerMessage(playerid, "Peluru pada senjata "RED"(%s) "WHITE"sudah habis.", ReturnWeaponName(weaponid));

				return 1;		
			}
		}	
		if(PlayerData[playerid][pDurability][g_aWeaponSlots[weaponid]]) {
			if(--PlayerData[playerid][pDurability][g_aWeaponSlots[weaponid]] == 0) {
				PlayerData[playerid][pDurability][g_aWeaponSlots[weaponid]] = 0;
				ResetWeapon(playerid, weaponid);
				SendServerMessage(playerid, "Kondisi pada senjata "RED"(%s) "WHITE"telah rusak.", ReturnWeaponName(weaponid));
			}
		}
	}
	return 1;
}

public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
    if(GetWeapon(playerid) == weaponid && weaponid >= 22  && weaponid <= 38)
    {
		if(PlayerData[playerid][pAmmo][g_aWeaponSlots[weaponid]]) {
			if(--PlayerData[playerid][pAmmo][g_aWeaponSlots[weaponid]] == 0) {
				PlayerData[playerid][pAmmo][g_aWeaponSlots[weaponid]] = 0;
				SetPlayerArmedWeapon(playerid, 0);
				SendServerMessage(playerid, "Peluru pada senjata "RED"(%s) "WHITE"sudah habis.", ReturnWeaponName(weaponid));

				return 1;		
			}
		}	
		if(PlayerData[playerid][pDurability][g_aWeaponSlots[weaponid]]) {
			if(--PlayerData[playerid][pDurability][g_aWeaponSlots[weaponid]] == 0) {
				PlayerData[playerid][pDurability][g_aWeaponSlots[weaponid]] = 0;
				ResetWeapon(playerid, weaponid);
				SendServerMessage(playerid, "Kondisi pada senjata "RED"(%s) "WHITE"telah rusak.", ReturnWeaponName(weaponid));
			}
		}
	}
	return 1;
}
public OnPlayerCrashVehicle(playerid, vehicleid, Float:damage)
{
	if(IsDoorVehicle(vehicleid))
	{
		if(!PlayerData[playerid][pSeatbelt])
		{
			new Float:hp, amount = RandomEx(1, 3);
			GetPlayerHealth(playerid, hp);
			SetPlayerHealth(playerid, hp-amount);
		}
	}
	return 1;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if(StretcherHolding[playerid] == 1)
	{
		SetPlayerCurrentPos(playerid);
		SendErrorMessage(playerid, "Kamu tidak dapat memasuki kendaraan ketika membawa stretcher.");
		return true;
	}
	if(OnTrash[playerid] > 0 && !IsTrashmasterVehicle(vehicleid)) {
		SetPlayerCurrentPos(playerid);
		SendErrorMessage(playerid, "Tidak bisa menaiki kendaraan lain saat bekerja Trashmaster.");
		return true;
	}
	return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
	if(PlayerData[playerid][pSeatbelt] && IsDoorVehicle(vehicleid))
	{
		SetPlayerSeatbelt(playerid);
	}
    if(Helmet[playerid] == 1)
    {
        Helmet[playerid] = 0;
        SendClientMessage(playerid, COLOR_GREEN, "Helm-mu berhasil dilepas.");
        if(IsPlayerAttachedObjectSlotUsed(playerid, 9)) RemovePlayerAttachedObject(playerid, 9);
    }
	return 1;
}

public OnPlayerLeaveRaceCheckpoint(playerid)
{
	return 1;
}
public OnPlayerEnterRaceCheckpoint(playerid)
{
	return 1;
}

public OnPlayerEnterDynamicArea(playerid, STREAMER_TAG_AREA:areaid)
{
	return 1;
}

public OnPlayerEnterDynamicCP(playerid, STREAMER_TAG_CP:checkpointid)
{
	for(new i = 0; i < MAX_VENDOR; i++) if(checkpointid == VendorData[i][vendorCP])
	{
		ShowMessage(playerid, "~g~(Info) ~w~Tekan ~y~H ~w~untuk bekerja food vendor.", 2);
	}
	if(checkpointid == TrashCP[playerid])
	{
		new vehicleid = PlayerData[playerid][pTrashVehicleID];

	    if(!HasTrash[playerid]) 
			return SendErrorMessage(playerid, "Kamu sedang tidak membawa kantong sampah.");

	    if(LoadedTrash[vehicleid] >= TRASH_LIMIT) 
			return SendErrorMessage(playerid, "Trashmaster ini tidak dapat menampung lebih banyak kantong sampah.");

	    LoadedTrash[vehicleid]++;
		ApplyAnimation(playerid, "GRENADE", "WEAPON_throwu", 4.1, 0, 0, 0, 0, 0);
		SendClientMessage(playerid, COLOR_JOB, "(Trashmaster) {FFFFFF}Kamu berhasil memasukkan "RED"kantong sampah "WHITE"pada trashmaster.");

		if(TRASH_LIMIT - LoadedTrash[vehicleid] > 0)
		{
			new string[96];
			format(string, sizeof(string), "(Trashmaster) {FFFFFF}Kamu dapat memasukkan {F39C12}%d {FFFFFF}kantong sampah lagi pada trashmaster.", TRASH_LIMIT - LoadedTrash[vehicleid]);
			SendClientMessage(playerid, COLOR_JOB, string);
		}

		new driver = GetVehicleDriver(vehicleid);
		if(IsPlayerConnected(driver)) 
			Trash_ShowCapacity(driver);
			
		Trash_ResetPlayer(playerid);
		return 1;
	}
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		if(checkpointid == FactoryCP)
		{
			if(OnTrash[playerid] == 2)
			{
				TogglePlayerControllable(playerid, 0);
				StartPlayerLoadingBar(playerid, 100, "Unloading_Trash", 50, "TrashDone");
			}
		}
	}
	return 1;
}

public OnPlayerEnterCheckpoint(playerid)
{
	if(PlayerData[playerid][pOnDMV] && GetPlayerVehicleID(playerid) == PlayerData[playerid][pVehicleDMV])
	{
		PlayerData[playerid][pIndexDMV]++;

		if(PlayerData[playerid][pIndexDMV] == sizeof(DMVPoint))
		{
			if(IsValidVehicle(PlayerData[playerid][pVehicleDMV]))
				DestroyVehicleEx(PlayerData[playerid][pVehicleDMV]);

			PlayerData[playerid][pLicense][0] = true;
			
			SendClientMessage(playerid, COLOR_SERVER, "(DMV) {FFFFFF}Kamu berhasil menyelesaikan Driving Test! selamat kamu mendapatkan lisensi mengemudimu.");
			DisablePlayerCheckpoint(playerid);

			PlayerData[playerid][pOnTest] = false;
			PlayerData[playerid][pIndexTest] = 0;
			PlayerData[playerid][pOnDMV] = false;
			PlayerData[playerid][pIndexDMV] = -1;
			PlayerData[playerid][pHaveDrivingLicense] = true;
		}
		else 
		{
			DisablePlayerCheckpoint(playerid);
			SetPlayerCheckpoint(playerid, DMVPoint[PlayerData[playerid][pIndexDMV]][0], DMVPoint[PlayerData[playerid][pIndexDMV]][1], DMVPoint[PlayerData[playerid][pIndexDMV]][2], 3.4);
		}
	}
	if(OnSweeping[playerid] && IsSweeperVehicle(GetPlayerVehicleID(playerid)))
	{
		SetSweeperPoint(playerid);
	}
	if(PlayerData[playerid][pTracing])
	{
		PlayerData[playerid][pTracing] = false;
		DisablePlayerCheckpoint(playerid);
	}
	if(PlayerData[playerid][pTracking])
	{
		PlayerData[playerid][pTracking] = false;
		DisablePlayerCheckpoint(playerid);
	}
	if(PlayerData[playerid][pPizzas])
	{
		if(PlayerData[playerid][pCarryPizza] != 2)
			return SendErrorMessage(playerid, "Kamu ambil makanan dari Wayfarer menggunakan {ffffff}/graborder'{ffff00} sebelum memasuki checkpoint ini.");

		new payment = 1500 + random(600);
		SendClientMessageEx(playerid, COLOR_SERVER, "(Sidejob) {FFFFFF}Kamu berhasil menyelesaikan pekerjaan dan mendapatkan {00FF00}$%s {FFFFFF}di {FFFF00}/salary", FormatNumber(payment));
		AddSalary(playerid, "Pizza Delivery", payment);
			
		PlayerData[playerid][pPizzas] = false;
		PlayerData[playerid][pCarryingPizza] = false;
		PlayerData[playerid][pCarryPizza] = 0;
		PlayerData[playerid][pPizza] = 0;
		PlayerData[playerid][pPizzaTime] = 0;

		RemovePlayerAttachedObject(playerid, 1);
		HideWaypoint(playerid);
	}
	if(PlayerData[playerid][pWP])
	{
		HideWaypoint(playerid);
	}
	return 1;
}

public OnPlayerEditDynamicObject(playerid, STREAMER_TAG_OBJECT:objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	new id = PlayerData[playerid][pEditing];
	if(response == EDIT_RESPONSE_FINAL)
	{
		if(PlayerData[playerid][pEditing] != -1)
		{
			if(PlayerData[playerid][pEditType] == EDIT_TREE)
			{
				TreeData[id][treePos][0] = x;
				TreeData[id][treePos][1] = y;
				TreeData[id][treePos][2] = z;
				TreeData[id][treePos][3] = rx;
				TreeData[id][treePos][4] = ry;
				TreeData[id][treePos][5] = rz;

				Tree_Save(id);
				Tree_Refresh(id);
				SendServerMessage(playerid, "Kamu berhasil mengedit Tree ID: %d", id);
			}
			else if(PlayerData[playerid][pEditType] == EDIT_FURNITURE)
			{
				FurnitureData[id][furniturePos][0] = x;
				FurnitureData[id][furniturePos][1] = y;
				FurnitureData[id][furniturePos][2] = z;

				FurnitureData[id][furnitureRot][0] = rx;
				FurnitureData[id][furnitureRot][1] = ry;
				FurnitureData[id][furnitureRot][2] = rz;

				Furniture_Save(id);
				Furniture_Refresh(id);

				SendServerMessage(playerid, "Kamu berhasil mengedit furniture ID: %d", id);

				ShowFurnitureEditMenu(playerid);
			}
			else if(PlayerData[playerid][pEditType] == EDIT_PUMP) 
			{
				PumpData[id][pumpPos][0] = x;
				PumpData[id][pumpPos][1] = y;
				PumpData[id][pumpPos][2] = z;
				PumpData[id][pumpPos][3] = rz;

				Pump_Sync(id);
				Pump_Save(id);

				SendServerMessage(playerid, "Kamu berhasil mengedit Fuel Pump ID %d.", id);
			}
			else if(PlayerData[playerid][pEditType] == EDIT_ROCK) {
				RockData[id][rockX] = x;
				RockData[id][rockY] = y;
				RockData[id][rockZ] = z;

				Rock_Sync(id);
				Rock_Save(id);

				SendServerMessage(playerid, "Kamu berhasil mengedit Rock ID: %d.", id);
			}
			else if(PlayerData[playerid][pEditType] == EDIT_ROADBLOCK) {
				
                BarricadeData[id][cadePos][0] = x;
                BarricadeData[id][cadePos][1] = y;
                BarricadeData[id][cadePos][2] = z;
                BarricadeData[id][cadePos][3] = rx;
                BarricadeData[id][cadePos][4] = ry;
                BarricadeData[id][cadePos][5] = rz;
                Barricade_Sync(id);
            }
			else if(PlayerData[playerid][pEditType] == EDIT_VEHICLE) {

                new 
                    vehicleid = PlayerData[playerid][pEditing],
                    slot = PlayerData[playerid][pListitem],
                    Float:vx,
                    Float:vy,
                    Float:vz,
                    Float:va,
                    Float:real_x,
                    Float:real_y,
                    Float:real_z,
                    Float:real_a
                ;

                GetVehiclePos(vehicleid, vx, vy, vz);
                GetVehicleZAngle(vehicleid, va);

                real_x = x - vx;
                real_y = y - vy;
                real_z = z - vz;
                real_a = rz - va;

				new Float:v_size[3];
				GetVehicleModelInfo(GetVehicleModel(vehicleid), VEHICLE_MODEL_INFO_SIZE, v_size[0], v_size[1], v_size[2]);
				if(	(real_x >= v_size[0] || -v_size[0] >= real_x) || 
					(real_y >= v_size[1] || -v_size[1] >= real_y) ||
					(real_z >= v_size[2] || -v_size[2] >= real_z))
				{
					ShowMessage(playerid, "Posisi ~y~object ~w~terlalu jauh dari kendaraan!", 4, 1);
                    return 1;
				}

                VehicleObjects[vehicleid][slot][vehObjectPosX] = real_x;                
                VehicleObjects[vehicleid][slot][vehObjectPosY] = real_y;
                VehicleObjects[vehicleid][slot][vehObjectPosZ] = real_z;
                VehicleObjects[vehicleid][slot][vehObjectPosRX] = rx;
                VehicleObjects[vehicleid][slot][vehObjectPosRY] = ry;
                VehicleObjects[vehicleid][slot][vehObjectPosRZ] = real_a;

                Vehicle_ObjectUpdate(vehicleid, slot);
                Vehicle_AttachObject(vehicleid, slot);
                Vehicle_ObjectSave(vehicleid, slot);
			}
			else if(PlayerData[playerid][pEditType] == EDIT_TAG)
			{
				TagData[id][tagPos][0] = x;
				TagData[id][tagPos][1] = y;
				TagData[id][tagPos][2] = z;
				TagData[id][tagPos][3] = rx;
				TagData[id][tagPos][4] = ry;
				TagData[id][tagPos][5] = rz;

				SendServerMessage(playerid, "Posisi "GREY"SprayTag "WHITE"berhasil diedit!");

				Tag_Save(id);
			}
		    else if (PlayerData[playerid][pEditType] == EDIT_GATE)
		    {
		        switch (PlayerData[playerid][pEditGate])
		        {
		            case 1:
		            {

		                GateData[id][gatePos][0] = x;
		                GateData[id][gatePos][1] = y;
		                GateData[id][gatePos][2] = z;
		                GateData[id][gatePos][3] = rx;
		                GateData[id][gatePos][4] = ry;
		                GateData[id][gatePos][5] = rz;

		                Streamer_SetPosition(STREAMER_TYPE_OBJECT, GateData[id][gateObject], GateData[id][gatePos][0], GateData[id][gatePos][1], GateData[id][gatePos][2]);
		                Streamer_SetRotation(STREAMER_TYPE_OBJECT, GateData[id][gateObject], GateData[id][gatePos][3], GateData[id][gatePos][4], GateData[id][gatePos][5]);
		                Streamer_SetIntData(STREAMER_TYPE_OBJECT, GateData[id][gateObject], E_STREAMER_INTERIOR_ID, GateData[id][gateInterior]);
		                Streamer_SetIntData(STREAMER_TYPE_OBJECT, GateData[id][gateObject], E_STREAMER_WORLD_ID, GateData[id][gateWorld]);


						Gate_Save(id);
	                    SendServerMessage(playerid, "Kamu berhasil mengedit posisi gate ID: %d.", id);
					}
					case 2:
		            {

		                GateData[id][gateMove][0] = x;
		                GateData[id][gateMove][1] = y;
		                GateData[id][gateMove][2] = z;
		                GateData[id][gateMove][3] = rx;
		                GateData[id][gateMove][4] = ry;
		                GateData[id][gateMove][5] = rz;

		                Streamer_SetPosition(STREAMER_TYPE_OBJECT, GateData[id][gateObject], GateData[id][gatePos][0], GateData[id][gatePos][1], GateData[id][gatePos][2]);
		                Streamer_SetRotation(STREAMER_TYPE_OBJECT, GateData[id][gateObject], GateData[id][gatePos][3], GateData[id][gatePos][4], GateData[id][gatePos][5]);
		                Streamer_SetIntData(STREAMER_TYPE_OBJECT, GateData[id][gateObject], E_STREAMER_INTERIOR_ID, GateData[id][gateInterior]);
		                Streamer_SetIntData(STREAMER_TYPE_OBJECT, GateData[id][gateObject], E_STREAMER_WORLD_ID, GateData[id][gateWorld]);

						Gate_Save(id);
	                    SendServerMessage(playerid, "Kamu berhasil mengedit posisi bergerak gate ID: %d.", id);
					}
				}
			}
			else if(PlayerData[playerid][pEditType] == EDIT_OBJECT)
			{
				ObjectData[id][mobjPos][0] = x;
				ObjectData[id][mobjPos][1] = y;
				ObjectData[id][mobjPos][2] = z;
				ObjectData[id][mobjPos][3] = rx;
				ObjectData[id][mobjPos][4] = ry;
				ObjectData[id][mobjPos][5] = rz;

				Object_Refresh(id);
				Object_Save(id);

				SendServerMessage(playerid, "Kamu berhasil mengedit Object ID: %d", id);
			}
			else if(PlayerData[playerid][pEditType] == EDIT_TRASH)
			{
				TrashData[id][TrashX] = x;
				TrashData[id][TrashY] = y;
				TrashData[id][TrashZ] = z;
				TrashData[id][TrashRotX] = rx;
				TrashData[id][TrashRotY] = ry;
				TrashData[id][TrashRotZ] = rz;

				Trash_Refresh(id);
				Trash_Save(id);

				SendServerMessage(playerid, "Kamu berhasil mengedit Trash ID: %d", id);
			}
		}

		PlayerData[playerid][pEditing] = -1;
		PlayerData[playerid][pEditType] = EDIT_NONE;
		PlayerData[playerid][pEditGate] = 0;
	}
	if(response == EDIT_RESPONSE_CANCEL)
	{
		if(PlayerData[playerid][pEditType] == EDIT_TREE)
			Tree_Refresh(id);

		if(PlayerData[playerid][pEditType] == EDIT_FURNITURE)
			Furniture_Refresh(id);

		if(PlayerData[playerid][pEditType] == EDIT_PUMP)
			Pump_Sync(id);

		if(PlayerData[playerid][pEditType] == EDIT_VEHICLE)
			Vehicle_SyncObject(id,PlayerData[playerid][pListitem]);

		if(PlayerData[playerid][pEditType] == EDIT_ROCK) 
			Rock_Sync(id);

		if(PlayerData[playerid][pEditType] == EDIT_ROADBLOCK)
			Barricade_Sync(id);

		PlayerData[playerid][pEditType] = EDIT_NONE;
		PlayerData[playerid][pEditing] = -1;
		PlayerData[playerid][pEditGate] = 0;

	}
	return 1;
}

public OnPlayerEditAttachedObject(playerid, response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ,Float:fScaleX, Float:fScaleY, Float:fScaleZ)
{
	new weaponid = EditingWeapon[playerid];
	if(response)
	{
        if(weaponid)
        {
            new enum_index = weaponid - 22, weaponname[18], string[340];

            GetWeaponName(weaponid, weaponname, sizeof(weaponname));

            WeaponSettings[playerid][enum_index][Position][0] = fOffsetX;
            WeaponSettings[playerid][enum_index][Position][1] = fOffsetY;
            WeaponSettings[playerid][enum_index][Position][2] = fOffsetZ;
            WeaponSettings[playerid][enum_index][Position][3] = fRotX;
            WeaponSettings[playerid][enum_index][Position][4] = fRotY;
            WeaponSettings[playerid][enum_index][Position][5] = fRotZ;

            RemovePlayerAttachedObject(playerid, GetWeaponObjectSlot(weaponid));
            SetPlayerAttachedObject(playerid, GetWeaponObjectSlot(weaponid), GetWeaponModel(weaponid), WeaponSettings[playerid][enum_index][Bone], fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, 1.0, 1.0, 1.0);

            SendServerMessage(playerid, "Attachment weapon {FF0000}%s {FFFFFF}berhasil diupdate.", weaponname);

            mysql_format(sqlcon, string, sizeof(string), "INSERT INTO weaponsettings (Owner, WeaponID, PosX, PosY, PosZ, RotX, RotY, RotZ) VALUES ('%d', %d, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f) ON DUPLICATE KEY UPDATE PosX = VALUES(PosX), PosY = VALUES(PosY), PosZ = VALUES(PosZ), RotX = VALUES(RotX), RotY = VALUES(RotY), RotZ = VALUES(RotZ)", PlayerData[playerid][pID], weaponid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ);
            mysql_tquery(sqlcon, string);
        }
        if(PlayerData[playerid][pAksesoris] != -1)
        {
            new id = PlayerData[playerid][pAksesoris];
            AccData[playerid][id][accOffset][0] = fOffsetX;
            AccData[playerid][id][accOffset][1] = fOffsetY;
            AccData[playerid][id][accOffset][2] = fOffsetZ;
            AccData[playerid][id][accRot][0] = fRotX;
            AccData[playerid][id][accRot][1] = fRotY;
            AccData[playerid][id][accRot][2] = fRotZ;
            AccData[playerid][id][accScale][0] = (fScaleX > 3.0) ? (3.0) : (fScaleX);
            AccData[playerid][id][accScale][1] = (fScaleY > 3.0) ? (3.0) : (fScaleY);
            AccData[playerid][id][accScale][2] = (fScaleZ > 3.0) ? (3.0) : (fScaleZ);
            Aksesoris_Attach(playerid, id);
            PlayerData[playerid][pAksesoris] = -1;
            SendCustomMessage(playerid, X11_LIGHTBLUE, "Acessory","Aksesoris pada slot "YELLOW"%d "WHITE"berhasil disimpan.", id);
        }
		EditingWeapon[playerid] = 0;
    }
	else
	{
		if(weaponid) 
		{
			new enum_index = weaponid - 22;
			SetPlayerAttachedObject(playerid, GetWeaponObjectSlot(weaponid), GetWeaponModel(weaponid), WeaponSettings[playerid][enum_index][Bone], fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, 1.0, 1.0, 1.0);
		}
        if(PlayerData[playerid][pAksesoris] != -1)
        {
            Aksesoris_Attach(playerid, PlayerData[playerid][pAksesoris]);
            PlayerData[playerid][pAksesoris] = -1;
        }
		EditingWeapon[playerid] = 0;
	}
    return 1;
}

public OnPlayerUpdate(playerid)
{
	if(IsPlayerSpawned(playerid)) {
		
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
					SendAdminMessage(COLOR_LIGHTRED, "AntiCheat: Cheat detected on {FFFF00}%s (%s) {FF6347}(SA:MP Crasher)", GetName(playerid), PlayerData[playerid][pUCP]);
					KickEx(playerid);
				}
		}
		if(GetPlayerWeapon(playerid) != PlayerData[playerid][pWeapon])
		{
			PlayerData[playerid][pWeapon] = GetPlayerWeapon(playerid);

			if(PlayerData[playerid][pWeapon] >= 1 && PlayerData[playerid][pWeapon] <= 45 && PlayerData[playerid][pWeapon] != 40 && PlayerData[playerid][pWeapon] != 2 && PlayerData[playerid][pGuns][g_aWeaponSlots[PlayerData[playerid][pWeapon]]] != GetPlayerWeapon(playerid) && !PlayerData[playerid][pKicked])
			{
				SendAdminMessage(COLOR_LIGHTRED, "AntiCheat: Cheat detected on {FFFF00}%s (%s) {FF6347}(Weapon hack %s)", GetName(playerid), PlayerData[playerid][pUCP], ReturnWeaponName(PlayerData[playerid][pWeapon]));
				ResetWeapons(playerid);
				KickEx(playerid);
			}
		}
		if(noclipdata[playerid][cameramode] == CAMERA_MODE_FLY && PlayerData[playerid][pAdmin])
		{
			new keys,ud,lr;
			GetPlayerKeys(playerid,keys,ud,lr);
			

			if(noclipdata[playerid][flmode] && (GetTickCount() - noclipdata[playerid][lastmove] > 100))
			{
				// If the last move was > 100ms ago, process moving the object the players camera is attached to
				MoveCamera(playerid);
			}

			// Is the players current key state different than their last keystate?
			if(noclipdata[playerid][udold] != ud || noclipdata[playerid][lrold] != lr)
			{
				if((noclipdata[playerid][udold] != 0 || noclipdata[playerid][lrold] != 0) && ud == 0 && lr == 0)
				{   // All keys have been released, stop the object the camera is attached to and reset the acceleration multiplier
					StopDynamicObject(noclipdata[playerid][flyobject]);
					noclipdata[playerid][flmode]      = 0;
					noclipdata[playerid][accelmul]  = 0.0;
				}
				else
				{   // Indicates a new key has been pressed

					// Get the direction the player wants to move as indicated by the keys
					noclipdata[playerid][flmode] = GetMoveDirectionFromKeys(ud, lr);

					// Process moving the object the players camera is attached to
					MoveCamera(playerid);
				}
			}
			noclipdata[playerid][udold] = ud; noclipdata[playerid][lrold] = lr; // Store current keys pressed for comparison next update
		}
		if(StretcherHolding[playerid])
		{
			new Float:zX, Float:zY, Float:zZ, Float:Ang;
			GetPlayerPos(playerid, zX, zY, zZ);
			GetXYInFrontOfPlayer(playerid, zX, zY, 1.6);
			GetPlayerFacingAngle(playerid, Ang);

			if(IsValidDynamicObject(StretcherEquipped[playerid])) {

				SetDynamicObjectPos(StretcherEquipped[playerid], zX, zY, zZ - 1.0);
				SetDynamicObjectRot(StretcherEquipped[playerid], 0.0, 0.0, Ang-180.0);
			}
		}
		if(IsValidDynamicObject(StretcherEquipped[playerid]) && StretcherPlayerID[playerid] != INVALID_PLAYER_ID)
		{
			if(IsPlayerConnected(StretcherPlayerID[playerid]))
			{
				new Float:playerpos[4];
				TogglePlayerControllable(StretcherPlayerID[playerid], 0);
				GetPlayerFacingAngle(playerid, playerpos[3]);
				SetPlayerFacingAngle(StretcherPlayerID[playerid], playerpos[3]);
				GetPlayerPos(playerid, playerpos[0], playerpos[1], playerpos[2]);
				GetXYInFrontOfPlayer(playerid, playerpos[0], playerpos[1], 2.0);
				SetPlayerPos(StretcherPlayerID[playerid], playerpos[0], playerpos[1], playerpos[2] + 0.5);
				SetCameraBehindPlayer(StretcherPlayerID[playerid]);
				SetPlayerVirtualWorld(StretcherPlayerID[playerid], GetPlayerVirtualWorld(playerid));
				SetPlayerInterior(StretcherPlayerID[playerid], GetPlayerInterior(playerid));

				ApplyAnimation(StretcherPlayerID[playerid],"BEACH", "bather", 4.0, 1, 0, 0, 1, -1, 1);
			}
			else StretcherPlayerID[playerid] = INVALID_PLAYER_ID;
		}
		if(Iter_Count(Spike) > 0) {
			foreach(new i : Spike) if(IsPlayerInRangeOfPoint(playerid, 3.0, SpikeData[i][spikePos][0], SpikeData[i][spikePos][1], SpikeData[i][spikePos][2]) && GetPlayerVirtualWorld(playerid) == SpikeData[i][spikeWorld])
			{
				new
					tires[4],
					vehicleid = GetPlayerVehicleID(playerid);

				GetVehicleDamageStatus(vehicleid, tires[0], tires[1], tires[2], tires[3]);

				if (tires[3] != 1111) {
					UpdateVehicleDamageStatus(vehicleid, tires[0], tires[1], tires[2], 1111);
				}
				break;
			}
		}
		if (NetStats_GetConnectedTime(playerid) - WeaponTick[playerid] >= 250)
		{
			new weaponid, ammo, objectslot, count, index; 
			for (new i = 2; i <= 7; i++)
			{
				GetPlayerWeaponData(playerid, i, weaponid, ammo);
				index = weaponid - 22;           
				if (weaponid && ammo && !WeaponSettings[playerid][index][Hidden] && IsWeaponWearable(weaponid) && EditingWeapon[playerid] != weaponid)
				{
					objectslot = GetWeaponObjectSlot(weaponid);
	
					if(GetPlayerWeapon(playerid) != weaponid)
					{
						SetPlayerAttachedObject(playerid, objectslot, GetWeaponModel(weaponid), WeaponSettings[playerid][index][Bone], WeaponSettings[playerid][index][Position][0], WeaponSettings[playerid][index][Position][1], WeaponSettings[playerid][index][Position][2], WeaponSettings[playerid][index][Position][3], WeaponSettings[playerid][index][Position][4], WeaponSettings[playerid][index][Position][5], 1.0, 1.0, 1.0);
					}
					else if (IsPlayerAttachedObjectSlotUsed(playerid, objectslot)) 
					{
						RemovePlayerAttachedObject(playerid, objectslot);
					}
				}
			}
			for (new i= 5; i < 8; i++)
			{ 
				if(IsPlayerAttachedObjectSlotUsed(playerid, i))
				{
					count = 0;    
					for (new j = 22; j <= 32; j++) 
					{
						if(PlayerHasWeaponAttachment(playerid, j) && GetWeaponObjectSlot(j) == i)
						{
							count++;
						}
					}
					if(!count) 
					{
						RemovePlayerAttachedObject(playerid, i);
					}
				}
			}
			WeaponTick[playerid] = NetStats_GetConnectedTime(playerid);
		}

		new weaponid = GetWeapon(playerid);
		if(weaponid >= 22 && weaponid <= 38) {
			if(PlayerData[playerid][pGuns][g_aWeaponSlots[weaponid]] > 0) {
				if(PlayerData[playerid][pHighVelocity][g_aWeaponSlots[weaponid]]) {
					PlayerTextDrawSetString(playerid, AMMOTD[playerid], sprintf("%d~n~high_velocity", PlayerData[playerid][pAmmo][g_aWeaponSlots[weaponid]]));
				}
				else {
					PlayerTextDrawSetString(playerid, AMMOTD[playerid], sprintf("%d", PlayerData[playerid][pAmmo][g_aWeaponSlots[weaponid]]));
				}
			}
		}
		else
			PlayerTextDrawSetString(playerid,  AMMOTD[playerid], "_");
	}
	return 1;
}
public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid == DIALOG_HUD_TYPE) {
		if(response) {

			HidePlayerHUD(playerid);

			PlayerData[playerid][pHudType] = listitem + 1;

			ShowPlayerHUD(playerid);
		}
	}
	if(dialogid == DIALOG_CRIMERECORD) {
		if(!response) {
			ShowPlayerDialog(playerid, DIALOG_MDC_CITIZEN_MENU, DIALOG_STYLE_LIST, "MDC > Lookup Menu", "Summary\nArrest history\nUnpaid tickets\nCrime record", "Select", "Close");
		}
		else {
			new sql_id = ListedItems[playerid][listitem], Cache:result;

			result = mysql_query(sqlcon, sprintf("SELECT * FROM `crime_record` WHERE `ID` = '%d' LIMIT 1;", sql_id));

			if(cache_num_rows()) {
				new status;

				cache_get_value_name_int(0, "Status", status);

				status = !(status);

				mysql_tquery(sqlcon, sprintf("UPDATE `crime_record` SET `Status` = '%d' WHERE `ID` = '%d'", status, sql_id));
				ShowPlayerDialog(playerid, DIALOG_MDC_CITIZEN_MENU, DIALOG_STYLE_LIST, "MDC > Lookup Menu", "Summary\nArrest history\nUnpaid tickets\nCrime record", "Select", "Close");
			}
			else SendErrorMessage(playerid, "Terjadi kesalahan saat melakukan query.");

			cache_delete(result);
		}
	}
	if(dialogid == DIALOG_ADS_POST) {

		new targetid = PlayerData[playerid][pTarget], time;
		if(response) {

			if(!IsPlayerNearPlayer(playerid, targetid, 10.0) || targetid == INVALID_PLAYER_ID)
				return SendErrorMessage(playerid, "The advertisement poster is no longer near you.");

			Advert_Create(PlayerData[targetid][pPhoneNumber], AdvertText[targetid], PlayerData[targetid][pID], GetName(targetid, false), time);

			SendClientMessageEx(targetid, X11_LIGHTBLUE, "(Post-Ad) "WHITE"Your advertisement has been "GREEN"approved "WHITE"and will be posted in %d minute.", time);
			SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Post-Ad) "WHITE"You have "GREEN"approved "WHITE"the advertisement.");
		}
		else {
			SendClientMessageEx(targetid, X11_LIGHTBLUE, "(Post-Ad) "WHITE"Your advertisement has been "RED"denied");
			SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Post-Ad) "WHITE"You have "RED"denied "WHITE"the advertisement.");
		}
	}
	if(dialogid == DIALOG_ADS_TEXT) {
		if(response) {
			if(strlen(inputtext) > 128)
				return ShowPlayerDialog(playerid, DIALOG_ADS_TEXT, DIALOG_STYLE_INPUT, "Advertisement", "Silahkan masukkan apa yang akan kamu iklankan:\n(maksimal 128 karakter)", ">>>", "Close");

			new targetid = PlayerData[playerid][pTarget];

			if(!IsPlayerNearPlayer(playerid, targetid, 10.0) || targetid == INVALID_PLAYER_ID)
				return SendErrorMessage(playerid, "The SFN Staff is no longer near you.");

			format(AdvertText[playerid], 128, "%s", inputtext);

			new string[256];
			format(string, sizeof(string), ""GREEN"Waiting for approval..\n\n"WHITE"Advertisement:\n%s\nPhNumber: %d\n\n\nDid you approve this advertisement to be published?", inputtext, PlayerData[playerid][pPhoneNumber]);
			ShowPlayerDialog(targetid, DIALOG_ADS_POST, DIALOG_STYLE_MSGBOX, "Advertisement Post", string, "Approve", "Denied");

			PlayerData[targetid][pTarget] = playerid;

			SendClientMessage(playerid, X11_LIGHTBLUE, "(Post-Ad) "WHITE"You have written the advertisement, waiting for approval.");
		}
	}
	if(dialogid == DIALOG_VEHMENU) {
		if(response) {
			if(listitem == 0) {
				cmd_v(playerid, "engine");
			}
			if(listitem == 1) {
				cmd_v(playerid, "lock");
			}
			if(listitem == 2) {
				cmd_v(playerid, "light");
			}
			if(listitem == 3) {
				cmd_v(playerid, "neon");
			}
		}
	}
	if(dialogid == DIALOG_FURNITURE_MENU)
	{
		new id = PlayerData[playerid][pEditing];

		if(response)
		{
			if(listitem == 0)
			{
				if(Iter_Contains(Furniture, id))
				{
					PlayerData[playerid][pEditType] = EDIT_FURNITURE;

					EditDynamicObject(playerid, FurnitureData[id][furnitureObject]);

					SendServerMessage(playerid, "You are now in editing mode of furniture index id: %d", id);
				}
			}
			if(listitem == 1)
			{
				ShowEditTextDraw(playerid);

				SendServerMessage(playerid, "You are now in editing mode of furniture index id: %d", id);
			}

			if(listitem == 2) {

				if(GetComponent(playerid) < 10)
					return SendErrorMessage(playerid, "Kamu membutuhkan 10 component untuk re-texture.");

				ShowPlayerDialog(playerid, DIALOG_FURNITURE_TEXTURE, DIALOG_STYLE_INPUT, "Custom Texture", ""LIGHTBLUE"Masukkan texture object dengan format berikut: [modelid] [TXD Name] [texture]\n(contoh): "YELLOW"10101 2notherbuildsfe Bow_Abpave_Gen\n\n"WHITE"Kamu dapat mencari texture pada beberapa link berikut ini:\n"GREEN"- https://samp-textures.iamaul.me/\n- https://textures.xyin.ws/\n- https://www.gtxd.net/", "Set", "Cancel");
			}
			if(listitem == 3)
			{
				Furniture_Delete(id);

				SendServerMessage(playerid, "You have successfully removed the furniture!");
			}
		}
	}
	if(dialogid == DIALOG_FURNITURE_TEXTURE) {
		if(response) {
			new id = PlayerData[playerid][pEditing],
				modelid, txdname[24], txtname[24];

			if(sscanf(inputtext, "ds[24]s[24]", modelid, txdname, txtname)) {
				return ShowPlayerDialog(playerid, DIALOG_FURNITURE_TEXTURE, DIALOG_STYLE_INPUT, "Custom Texture", ""LIGHTBLUE"Masukkan texture object dengan format berikut: [modelid] [TXD Name] [texture]\n(contoh): "YELLOW"10101 2notherbuildsfe Bow_Abpave_Gen\n\n"WHITE"Kamu dapat mencari texture pada beberapa link berikut ini:\n"GREEN"- https://samp-textures.iamaul.me/\n- https://textures.xyin.ws/\n- https://www.gtxd.net/", "Set", "Cancel");
			}

			Inventory_Remove(playerid, "Component", 10);

			FurnitureData[id][furnitureTextureModelid] = modelid;
			format(FurnitureData[id][furnitureTextureName], 24, txtname);
			format(FurnitureData[id][furnitureTextureTXDName], 24, txdname);

			SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Furniture) "WHITE"Used "YELLOW"10 "WHITE"Component for re-texturing the %s.", FurnitureData[id][furnitureName], id);

			Furniture_Sync(id);

			Furniture_Save(id);

			ShowFurnitureEditMenu(playerid);
		}
	}
	if(dialogid == DIALOG_CHANGEPASS)
	{
	    if(response)
	    {
	        if(strlen(inputtext) < 8)
				return SendErrorMessage(playerid, "You must specify more than 7 characters.");

	        if(strlen(inputtext) > 32)
				return SendErrorMessage(playerid, "You can't specify more than 32 characters.");

            bcrypt_hash(playerid, "OnPlayerPasswordChange", inputtext, BCRYPT_COST);
		}
	}
	if(dialogid == DIALOG_WS_EMPLOYEE_HIRE) {
		if(response) {
			new id = Workshop_Nearest(playerid),
				targetid;

			if(id != -1 && Workshop_IsOwner(playerid, id)) {

				if(sscanf(inputtext, "u", targetid))
					return ShowPlayerDialog(playerid, DIALOG_WS_EMPLOYEE_HIRE, DIALOG_STYLE_INPUT, "Hire Employee", "(error): Invalid player!\nMasukkan playerid/PartOfName dari player yang akan di-hire:", "Hire", "Close");
			
				if(!IsPlayerNearPlayer(playerid, targetid, 5.0))
					return ShowPlayerDialog(playerid, DIALOG_WS_EMPLOYEE_HIRE, DIALOG_STYLE_INPUT, "Hire Employee", "(error): Player tersebut tidak didekatmu!\nMasukkan playerid/PartOfName dari player yang akan di-hire:", "Hire", "Close");
			
				if(Workshop_IsEmployee(targetid, id))
					return ShowPlayerDialog(playerid, DIALOG_WS_EMPLOYEE_HIRE, DIALOG_STYLE_INPUT, "Hire Employee", "(error): Player tersebut sudah bekerja di workshop ini!\nMasukkan playerid/PartOfName dari player yang akan di-hire:", "Hire", "Close");
			
				Workshop_AddEmployee(targetid, id);
				SendServerMessage(targetid, "Kamu telah menjadi pekerja dari workshop milik %s.", ReturnName(playerid));
				SendServerMessage(playerid, "Kamu telah menjadikan %s pekerja dari workshop milikmu.", ReturnName(targetid));
				cmd_workshop(playerid, "employee");
			}
		}
	}
	if(dialogid == DIALOG_WS_EMPLOYEE_REMOVE) {
		if(response) {
			new query[182], Cache:execute, id = Workshop_Nearest(playerid);

			if(id != -1 && Workshop_IsOwner(playerid, id)) {
				mysql_format(sqlcon, query, sizeof(query), "SELECT * FROM `workshop_employee` WHERE `Name` = '%e' AND `WorkshopID` = '%d'", inputtext, WorkshopData[id][wsID]);
				execute = mysql_query(sqlcon, query);

				if(cache_num_rows()) {
					mysql_format(sqlcon, query, sizeof(query), sprintf("DELETE FROM `workshop_employee` WHERE `Name` = '%e' AND `WorkshopID` = '%d'", inputtext, WorkshopData[id][wsID]));
					mysql_tquery(sqlcon, query);

					SendServerMessage(playerid, "Pekerja %s berhasil dihapus dari daftar.", inputtext);
				}
				else SendErrorMessage(playerid, "Tidak ada pekerjamu dengan nama tersebut.");

				cmd_workshop(playerid, "employee");
				cache_delete(execute);
			}
		}
	}
	if(dialogid == DIALOG_WS_EMPLOYEE) {
		if(response) {
			new id = Workshop_Nearest(playerid);

			if(id != -1 && Workshop_IsOwner(playerid, id)) {
				if(listitem == 0) {
					ShowPlayerDialog(playerid, DIALOG_WS_EMPLOYEE_HIRE, DIALOG_STYLE_INPUT, "Hire Employee", "Masukkan playerid/PartOfName dari player yang akan di-hire:", "Hire", "Close");
				}
				if(listitem == 1) {
					ShowPlayerDialog(playerid, DIALOG_WS_EMPLOYEE_REMOVE, DIALOG_STYLE_INPUT, "Remove Employee", "Masukkan nama karakter yang akan dihapus dari list employee:", "Remove", "Close");
				}
				if(listitem == 2) {
					new Cache:execute, str[312];

					execute = mysql_query(sqlcon,  sprintf("SELECT * FROM `workshop_employee` WHERE `WorkshopID` = '%d'", WorkshopData[id][wsID]));

					if(cache_num_rows()) {
						for(new i = 0; i < cache_num_rows(); i++) {

							new
								char_name[MAX_PLAYER_NAME];

							cache_get_value_name(i, "Name", char_name, MAX_PLAYER_NAME);

							strcat(str, sprintf("%d) %s\n", i + 1, char_name));
						}
						ShowPlayerDialog(playerid, DIALOG_NONE, DIALOG_STYLE_LIST, "Listed Employee", str, "Close", "");
					}
					else SendErrorMessage(playerid, "Workshop ini tidak memiliki pekerja satupun.");

					cache_delete(execute);
				}
			}
		}
	}
	if(dialogid == DIALOG_BACKUP) {
		if(response) {
			if(listitem == 0) {
				new
					Float:x, Float:y, Float:z;

				GetPlayerPos(playerid, x, y, z);

				foreach(new i : Player) if(GetFactionType(i) == FACTION_POLICE && PlayerData[i][pOnDuty]) {

					if(i == playerid)
						continue;

					SetPlayerMultiCP(i, x, y, z, true, X11_YELLOW);
				}
				SendFactionMessageEx(FACTION_POLICE, COLOR_RADIO, "BACKUP: %s %s needs backup at "TOMATO"%s {8D8DFF}yellow beacon marked on radar.", Faction_GetRank(playerid), GetName(playerid, false), GetLocation(x, y, z));
				SendServerMessage(playerid, "Berhasil mengirim sinyal bantuan.");
			}
			if(listitem == 1) {
				new
					Float:x, Float:y, Float:z;

				GetPlayerPos(playerid, x, y, z);

				foreach(new i : Player) if(GetFactionType(i) == FACTION_MEDIC && PlayerData[i][pOnDuty]) {

					if(i == playerid)
						continue;

					SetPlayerMultiCP(i, x, y, z, true, X11_YELLOW);
				}
				SendFactionMessageEx(FACTION_MEDIC, COLOR_RADIO, "BACKUP: %s %s needs backup at "TOMATO"%s {8D8DFF}yellow beacon markedon radar.", Faction_GetRank(playerid), GetName(playerid, false), GetLocation(x, y, z));
				SendServerMessage(playerid, "Berhasil mengirim sinyal bantuan.");
			}
		}
	}
	if(dialogid == DIALOG_TRUNKWEAPON)
	{
	    new carid = PlayerData[playerid][pVehicle];
		if (response)
		{
			if(GetNearestVehicle(playerid, 5.0) != carid)
				return SendErrorMessage(playerid, "Vehicle no longer valid.");

			if(!IsValidVehicle(carid))
				return SendErrorMessage(playerid, "Vehicle no longer valid.");
			
			if(!GetTrunkStatus(carid))
				return SendErrorMessage(playerid, "Buka trunk terlebih dahulu!");

			if(PlayerData[playerid][pOnDuty])
				return SendErrorMessage(playerid, "You can't store a weapon since faction duty.");

			new weaponid = GetWeapon(playerid);
			
			if (!VehicleData[carid][vWeapon][listitem])
			{
			    if (!GetWeapon(playerid))
			        return SendErrorMessage(playerid, "You aren't holding any weapon.");

	   			VehicleData[carid][vWeapon][listitem] = GetWeapon(playerid);
	            VehicleData[carid][vAmmo][listitem] = PlayerData[playerid][pAmmo][g_aWeaponSlots[weaponid]];
				VehicleData[carid][vDurability][listitem] = PlayerData[playerid][pDurability][g_aWeaponSlots[weaponid]];
				VehicleData[carid][vHighVelocity][listitem] = PlayerData[playerid][pHighVelocity][g_aWeaponSlots[weaponid]];

          		ResetWeapon(playerid, VehicleData[carid][vWeapon][listitem]);
	            SendNearbyMessage(playerid, 30.0,X11_PLUM, "** %s stored a %s into the trunk.", ReturnName(playerid), ReturnWeaponName(VehicleData[carid][vWeapon][listitem]));

	            Vehicle_Save(carid);
				Vehicle_WeaponStorage(playerid, carid);

				Log_Write("Logs/veh_storage_log.txt", "[%s] %s has stored a \"%s\" to Vehicle ID: %d.", ReturnDate(), GetName(playerid, false), ReturnWeaponName(VehicleData[carid][vWeapon][listitem]), VehicleData[carid][vID]);
			}
			else
			{

				if(PlayerData[playerid][pLevel] < 3)
					return SendErrorMessage(playerid, "You must level 3 first to holding weapon.");

					
				if(PlayerHasWeapon(playerid, VehicleData[carid][vWeapon][listitem]))
				    return SendErrorMessage(playerid, "You already have this weapon.");
				    
				if (PlayerData[playerid][pGuns][g_aWeaponSlots[weaponid]] != 0)
					return SendErrorMessage(playerid, "You already have weapon on the same slot.");

			    GiveWeaponToPlayer(playerid, VehicleData[carid][vWeapon][listitem], VehicleData[carid][vAmmo][listitem], VehicleData[carid][vDurability][listitem], VehicleData[carid][vHighVelocity][listitem]);
	            SendNearbyMessage(playerid, 30.0,X11_PLUM, "** %s takes a %s from the trunk.", ReturnName(playerid), ReturnWeaponName(VehicleData[carid][vWeapon][listitem]));
				Log_Write("Logs/veh_storage_log.txt", "[%s] %s has taken a \"%s\" from Vehicle ID: %d.", ReturnDate(), ReturnName(playerid), ReturnWeaponName(VehicleData[carid][vWeapon][listitem]), VehicleData[carid][vID]);

	            VehicleData[carid][vWeapon][listitem] = 0;
	            VehicleData[carid][vAmmo][listitem] = 0;
	            VehicleData[carid][vDurability][listitem] = 0;
				VehicleData[carid][vHighVelocity][listitem] = 0;
	            Vehicle_Save(carid);
				Vehicle_WeaponStorage(playerid, carid);
			}
		}
	}
	if(dialogid == DIALOG_TRUNK_OPTION) {

		if(response) 
		{
			static
				carid = -1,
				itemid = -1,
				string[32];

			if ((carid = Vehicle_Nearest(playerid)) != -1)
			{
				itemid = PlayerData[playerid][pStorageItem];

				strunpack(string, CarStorage[carid][itemid][cItemName]);

				if (response)
				{
					switch (listitem)
					{
						case 0:
						{
							if (CarStorage[carid][itemid][cItemQuantity] == 1)
							{
								new id = Inventory_Add(playerid, string, CarStorage[carid][itemid][cItemModel], 1);

								if (id == -1)
									return SendErrorMessage(playerid, "You don't have any inventory slots left.");

								Car_RemoveItem(carid, string);

								SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "* %s has taken a \"%s\" from the trunk.", ReturnName(playerid), string);
								SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Trunk) "WHITE"Kamu mengambil "YELLOW"%s "WHITE"dari bagasi "CYAN"%s", string, GetVehicleName(carid));
								Vehicle_ShowTrunk(playerid, carid);
							}
							else
							{
								new txtstr[256];
								format(txtstr, sizeof(txtstr), "Item: %s (Quantity: %d)\n\nPlease enter the quantity that you wish to take for this item:", string, CarStorage[carid][itemid][cItemQuantity]);
								ShowPlayerDialog(playerid, DIALOG_TRUNK_TAKE, DIALOG_STYLE_INPUT, "Vehicle Take", txtstr, "Take", "Back");
							}
						}
						case 1:
						{
							new id = Inventory_GetItemID(playerid, string);

							if (id == -1) {
								Vehicle_ShowTrunk(playerid, carid);

								return SendErrorMessage(playerid, "You don't have anymore of this item to store!");
							}
							else if (InventoryData[playerid][id][invQuantity] == 1)
							{
								Car_AddItem(carid, string, InventoryData[playerid][id][invModel], 1);
								Inventory_Remove(playerid, string);

								SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "* %s has stored a \"%s\" into the trunk.", ReturnName(playerid), string);
								SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Trunk) "WHITE"Kamu menyimpan "YELLOW"%s "WHITE"kedalam bagasi "CYAN"%s", string, GetVehicleName(carid));
								
								Vehicle_ShowTrunk(playerid, carid);
							}
							else if (InventoryData[playerid][id][invQuantity] > 1) {
								PlayerData[playerid][pListitem] = id;

								new txtstr[256];
								format(txtstr, sizeof(txtstr), "Item: %s (Quantity: %d)\n\nPlease enter the quantity that you wish to store for this item:", string, InventoryData[playerid][id][invQuantity]);
								ShowPlayerDialog(playerid, DIALOG_TRUNK_DEPOSIT, DIALOG_STYLE_INPUT, "Vehicle Deposit", txtstr, "Store", "Back");
							}
						}
					}
				}
				else
				{
					Vehicle_ShowTrunk(playerid, carid);
				}
			}
		}
	}
	if(dialogid == DIALOG_TRUNK)
	{
	    new carid = PlayerData[playerid][pVehicle], string[64];
	    if(response)
	    {
		    if (listitem == MAX_CAR_STORAGE) {
    			Vehicle_WeaponStorage(playerid, carid);
		    }
		    else if (CarStorage[carid][listitem][cItemExists])
			{
   				PlayerData[playerid][pStorageItem] = listitem;
   				PlayerData[playerid][pListitem] = listitem;

				strunpack(string, CarStorage[carid][listitem][cItemName]);

				format(string, sizeof(string), "%s (Quantity: %d)", string, CarStorage[carid][listitem][cItemQuantity]);
				ShowPlayerDialog(playerid, DIALOG_TRUNK_OPTION, DIALOG_STYLE_LIST, string, "Take Item\nStore Item", "Select", "Back");
			}//jire
			else {
   				OpenInventory(playerid);
				PlayerData[playerid][pStorageSelect] = 3;
			}
		}
	}
	if(dialogid == DIALOG_VEHSPAWN) {
		if(response) {
			new sql_id = g_Selected_Vehicle_ID[playerid][listitem], Cache:result, bool:thereis = false;

			result = mysql_query(sqlcon, sprintf("SELECT * FROM `vehicle` WHERE `vehID`='%d';", sql_id));
			

			if(cache_num_rows()) {

				new Float:x, Float:y, Float:z;
				cache_get_value_name_float(0, "vehX", x);
				cache_get_value_name_float(0, "vehY", y);
				cache_get_value_name_float(0, "vehZ", z);

				foreach(new i : Vehicle) if(IsVehicleInRangeOfPoint3D(i, 3.0,  x, y, z)) {
					thereis  = true;
					break;
				}

				if(thereis) {
					SendErrorMessage(playerid, "Sedang ada kendaraan lain ditempat terakhir kendaraan yang akan kamu spawn.");
				}
				else {
					mysql_tquery(sqlcon, sprintf("UPDATE `vehicle` SET `vehState` = %d WHERE `vehID` = %d", VEHICLE_STATE_SPAWNED, sql_id));

					mysql_tquery(sqlcon, sprintf("SELECT * FROM `vehicle` WHERE `vehID`='%d';", sql_id), "OnVehicleLoaded", "");

					SendServerMessage(playerid, "You have spawned your vehicle back :)");
				}
				cache_delete(result);
			}
		}
	}
	if(dialogid == DIALOG_UNIMPOUND) {
		if(response) {
			new sql_id = g_Selected_Vehicle_ID[playerid][listitem],
				price = g_Selected_Vehicle_Price[playerid][listitem];

			if(GetMoney(playerid) < price)
				return SendErrorMessage(playerid, "Kamu tidak memiliki cukup uang!");

			GiveMoney(playerid, -price);
			SendServerMessage(playerid, "Kamu telah mengeluarkan kendaraan mu dari impound lot.");

			new str[256];
			mysql_format(sqlcon, str, sizeof(str), "UPDATE `vehicle` SET `vehState` = %d, `vehImpoundPrice` = 0, `vehInterior` = 0, `vehWorld` = 0 WHERE `vehID` = %d", VEHICLE_STATE_SPAWNED, sql_id);
			mysql_tquery(sqlcon, str);

			mysql_tquery(sqlcon, sprintf("SELECT * FROM `vehicle` WHERE `vehID`='%d';", sql_id), "OnVehicleLoaded", "");
		}
	}
	if(dialogid == DIALOG_ANDROID) {
		if(response) switch(listitem)
		{
			case 0: ShowPlayerDialog(playerid, DIALOG_EDITTOYSPX, DIALOG_STYLE_INPUT, "Accessory Coordinate", "Input an X Offset from -100 to 100 (Ex: 55, or 33.4)", "Enter", "Cancel");
			case 1: ShowPlayerDialog(playerid, DIALOG_EDITTOYSPY, DIALOG_STYLE_INPUT, "Accessory Coordinate", "Input a Y Offset from -100 to 100 (Ex: 55, or 33.4)", "Enter", "Cancel");
			case 2: ShowPlayerDialog(playerid, DIALOG_EDITTOYSPZ, DIALOG_STYLE_INPUT, "Accessory Coordinate", "Input a Z Offset from -100 to 100 (Ex: 55, or 33.4)", "Enter", "Cancel");
			case 3: ShowPlayerDialog(playerid, DIALOG_EDITTOYSRX, DIALOG_STYLE_INPUT, "Accessory Coordinate", "Input an X Rotation from 0 to 360 (Ex: 90, or 270.4)", "Enter", "Cancel");
			case 4: ShowPlayerDialog(playerid, DIALOG_EDITTOYSRY, DIALOG_STYLE_INPUT, "Accessory Coordinate", "Input a Y Rotation from 0 to 360 (Ex: 90, or 270.4)", "Enter", "Cancel");
			case 5: ShowPlayerDialog(playerid, DIALOG_EDITTOYSRZ, DIALOG_STYLE_INPUT, "Accessory Coordinate", "Input a Z Rotation from 0 to 360 (Ex: 90, or 270.4)", "Enter", "Cancel");
			case 6: ShowPlayerDialog(playerid, DIALOG_EDITTOYSSX, DIALOG_STYLE_INPUT, "Accessory Coordinate", "Input an X Scale from 0.1 to 1.5 (Ex: 1, or 0.93)", "Enter", "Cancel");
			case 7: ShowPlayerDialog(playerid, DIALOG_EDITTOYSSY, DIALOG_STYLE_INPUT, "Accessory Coordinate", "Input a Y Scale from 0.1 to 1.5 (Ex: 1, or 0.93)", "Enter", "Cancel");
			case 8: ShowPlayerDialog(playerid, DIALOG_EDITTOYSSZ, DIALOG_STYLE_INPUT, "Accessory Coordinate", "Input a Z Scale from 0.1 to 1.5 (Ex: 1, or 0.93)", "Enter", "Cancel");
		}
	}
	if(dialogid == DIALOG_EDITTOYSSX)
	{
		if(response)
		{
			new Float:offset = floatstr(inputtext);
			if(offset < 0.1) offset = 0.1;
			else if(offset > 1.5) offset = 1.5;
			AccData[playerid][PlayerData[playerid][pAksesoris]][accScale][0] = offset;
			Aksesoris_ShowAndroid(playerid);
		}
		RemovePlayerAttachedObject(playerid, PlayerData[playerid][pAksesoris]), Aksesoris_Attach(playerid, PlayerData[playerid][pAksesoris]);
	}
	if(dialogid == DIALOG_EDITTOYSSY)
	{
		if(response)
		{
			new Float:offset = floatstr(inputtext);
			if(offset < 0.1) offset = 0.1;
			else if(offset > 1.5) offset = 1.5;
			AccData[playerid][PlayerData[playerid][pAksesoris]][accScale][1] = offset;
			Aksesoris_ShowAndroid(playerid);
		}
		RemovePlayerAttachedObject(playerid, PlayerData[playerid][pAksesoris]), Aksesoris_Attach(playerid, PlayerData[playerid][pAksesoris]);
	}
	if(dialogid == DIALOG_EDITTOYSSZ)
	{
		if(response)
		{
			new Float:offset = floatstr(inputtext);
			if(offset < 0.1) offset = 0.1;
			else if(offset > 1.5) offset = 1.5;
			AccData[playerid][PlayerData[playerid][pAksesoris]][accScale][2] = offset;
			Aksesoris_ShowAndroid(playerid);
		}
		RemovePlayerAttachedObject(playerid, PlayerData[playerid][pAksesoris]), Aksesoris_Attach(playerid, PlayerData[playerid][pAksesoris]);
	}
	if(dialogid == DIALOG_EDITTOYSPX)
	{
		if(response)
		{
			new Float:offset = floatstr(inputtext);
			if(offset < -100) offset = 0;
			else if(offset > 100) offset = 100;
			
			AccData[playerid][PlayerData[playerid][pAksesoris]][accOffset][0] = offset;
			Aksesoris_ShowAndroid(playerid);
		}
		RemovePlayerAttachedObject(playerid, PlayerData[playerid][pAksesoris]), Aksesoris_Attach(playerid, PlayerData[playerid][pAksesoris]);
	}
	if(dialogid == DIALOG_EDITTOYSPY)
	{
		if(response)
		{
			new Float:offset = floatstr(inputtext);
			if(offset < -100) offset = 0;
			else if(offset > 100) offset = 100;
			
			AccData[playerid][PlayerData[playerid][pAksesoris]][accOffset][1] = offset;
			Aksesoris_ShowAndroid(playerid);
		}
		RemovePlayerAttachedObject(playerid, PlayerData[playerid][pAksesoris]), Aksesoris_Attach(playerid, PlayerData[playerid][pAksesoris]);
	}
	if(dialogid == DIALOG_EDITTOYSPZ)
	{
		if(response)
		{
			new Float:offset = floatstr(inputtext);
			if(offset < -100) offset = 0;
			else if(offset > 100) offset = 100;
			
			AccData[playerid][PlayerData[playerid][pAksesoris]][accOffset][2] = offset;
			Aksesoris_ShowAndroid(playerid);
			
		}
		RemovePlayerAttachedObject(playerid, PlayerData[playerid][pAksesoris]), Aksesoris_Attach(playerid, PlayerData[playerid][pAksesoris]);
	}
	if(dialogid == DIALOG_EDITTOYSRX)
	{
		if(response)
		{
			new Float:offset = floatstr(inputtext);
			if(offset < -100) offset = 0;
			else if(offset > 360) offset = 360;
			AccData[playerid][PlayerData[playerid][pAksesoris]][accRot][0] = offset;
			Aksesoris_ShowAndroid(playerid);
		}
		RemovePlayerAttachedObject(playerid, PlayerData[playerid][pAksesoris]), Aksesoris_Attach(playerid, PlayerData[playerid][pAksesoris]);
	}
	if(dialogid == DIALOG_EDITTOYSRY)
	{
		if(response)
		{
			new Float:offset = floatstr(inputtext);
			if(offset < -100) offset = 0;
			else if(offset > 360) offset = 360;
			AccData[playerid][PlayerData[playerid][pAksesoris]][accRot][1] = offset;
			Aksesoris_ShowAndroid(playerid);
			
		}
		RemovePlayerAttachedObject(playerid, PlayerData[playerid][pAksesoris]), Aksesoris_Attach(playerid, PlayerData[playerid][pAksesoris]);
	}
	if(dialogid == DIALOG_EDITTOYSRZ)
	{
		if(response)
		{
			new Float:offset = floatstr(inputtext);
			if(offset < -100) offset = 0;
			else if(offset > 360) offset = 360;
			AccData[playerid][PlayerData[playerid][pAksesoris]][accRot][2] = offset;
			Aksesoris_ShowAndroid(playerid);
		}
		RemovePlayerAttachedObject(playerid, PlayerData[playerid][pAksesoris]), Aksesoris_Attach(playerid, PlayerData[playerid][pAksesoris]);
	}
	if(dialogid == DIALOG_ACCESSORY) {
		if(response)
		{
			new id = PlayerData[playerid][pAksesoris];
			switch(listitem)
			{
				case 0:
				{
					if(IsPlayerAttachedObjectSlotUsed(playerid, id))
					{
						RemovePlayerAttachedObject(playerid, id);
						AccData[playerid][id][accShow] = 0;
						Aksesoris_Save(playerid, id);
					}
					else 
					{
						AccData[playerid][id][accShow] = 1;
						Aksesoris_Attach(playerid, id);
						Aksesoris_Save(playerid, id);
					}
				}
				case 1:
				{
					new string[256+1];
					for(new i; i < sizeof(accBones); i++)
					{
						format(string,sizeof(string),"%s%s\n",string,accBones[i]);
					}
					ShowPlayerDialog(playerid, DIALOG_TOYBONE, DIALOG_STYLE_LIST, "Edit Bone",string,"Select","Close");
				}
				case 2:
				{
					if(IsPlayerAttachedObjectSlotUsed(playerid, id))
					{
						SendServerMessage(playerid, "Use "YELLOW"~k~~PED_SPRINT~"WHITE" to look around.");
						EditAttachedObject(playerid, id);
					}
					else return SendCustomMessage(playerid, X11_LIGHTBLUE, "Acessory",""WHITE"You must attach this accessory first!");
				}
				case 3:
				{
					if(!AccData[playerid][id][accShow])
						return SendCustomMessage(playerid, X11_LIGHTBLUE, "Acessory",""WHITE"You must attach this accessory  first!");

					new stringg[512];
					format(stringg, sizeof(stringg), "Offset X (%.2f)\nOffset Y (%.2f)\nOffset Z (%.2f)\nRotation X (%.2f)\nRotation Y (%.2f)\nRotation Z (%.2f)\nScale X (%.2f)\nScale Y (%.2f)\nScale Z (%.2f)",
					AccData[playerid][id][accOffset][0],//pPosX
					AccData[playerid][id][accOffset][1],//pPosY
					AccData[playerid][id][accOffset][2],//pPosZ
					AccData[playerid][id][accRot][0],//pRotX
					AccData[playerid][id][accRot][1],//pRotY
					AccData[playerid][id][accRot][2],//pRotZ
					AccData[playerid][id][accScale][0],//pScaleX
					AccData[playerid][id][accScale][1],//pScaleY
					AccData[playerid][id][accScale][2]);//pScaleZ
					ShowPlayerDialog(playerid, DIALOG_ANDROID, DIALOG_STYLE_LIST, "Accessory Coordinate", stringg, "Select", "Cancel");
				}
				case 4:
				{
					new string[128];
					AccData[playerid][id][accExists] = 0;
					AccData[playerid][id][accModel] = 0;

					if(IsPlayerAttachedObjectSlotUsed(playerid, id))
					{
						RemovePlayerAttachedObject(playerid, id);
						AccData[playerid][id][accShow] = 0;
						Aksesoris_Save(playerid, id);
					}
					mysql_format(sqlcon, string,sizeof(string),"DELETE FROM `aksesoris` WHERE `ID`='%d'", AccData[playerid][id][accID]);
					mysql_tquery(sqlcon, string);

					SendCustomMessage(playerid, X11_LIGHTBLUE, "Acessory",""WHITE"You have removed accessory index #%d.", id);
				}
				case 5: {
					ShowPlayerDialog(playerid, DIALOG_ACC_PRESET, DIALOG_STYLE_LIST, sprintf("Accessory #%d Preset", id), "Search preset (by name)\nSearch preset (by used model)\nCreate preset\n"YELLOW"My preset", "Select", "Close");
				}
			}
		}
	}
	if(dialogid == DIALOG_ACC_PRESET_SEARCH) {
		if(response) {
			if(isnull(inputtext)) {
				ShowPlayerDialog(playerid, DIALOG_ACC_PRESET_SEARCH, DIALOG_STYLE_INPUT, "Search preset", "Silahkan masukkan nama preset yang ingin kamu cari:", "Search", "Close");
				return 1;

			}

			new Cache:query = mysql_query(sqlcon, sprintf("SELECT * FROM `acc_preset` WHERE `PresetName` = '%s' LIMIT 1;", inputtext)), string[712];

			if(cache_num_rows()) {

				new Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, Float:sx, Float:sy, Float:sz, bone, model, sql_id;

				cache_get_value_name_int(0, "ID", sql_id);
				SetPVarInt(playerid, "AccID", sql_id);

				cache_get_value_name_float(0, "X", x);
				cache_get_value_name_float(0, "Y", y);
				cache_get_value_name_float(0, "Z", z);
				cache_get_value_name_float(0, "RX", rx);
				cache_get_value_name_float(0, "RY", ry);
				cache_get_value_name_float(0, "RZ", rz);
				cache_get_value_name_float(0, "SX", sx);
				cache_get_value_name_float(0, "SY", sy);
				cache_get_value_name_float(0, "SZ", sz);
				cache_get_value_name_int(0, "Bone", bone);
				cache_get_value_name_int(0, "Model", model);
				strcat(string, sprintf(""GREEN"========== [ Preset %s ] ==========\n\n\n", inputtext));
				strcat(string, sprintf(""WHITE"Model aksesoris yang digunakan: %d\n", model));
				strcat(string, sprintf("Bone: %s\n", accBones[bone - 1]));
				strcat(string, sprintf(""WHITE"X: %.2f\n", x));
				strcat(string, sprintf(""WHITE"Y: %.2f\n", y));
				strcat(string, sprintf(""WHITE"Z: %.2f\n", z));
				strcat(string, sprintf(""WHITE"RX: %.2f\n", rx));
				strcat(string, sprintf(""WHITE"RY: %.2f\n", ry));
				strcat(string, sprintf(""WHITE"RZ: %.2f\n", rz));
				strcat(string, sprintf(""WHITE"SX: %.2f\n", sx));
				strcat(string, sprintf(""WHITE"SY: %.2f\n", sy));
				strcat(string, sprintf(""WHITE"SZ: %.2f\n", sz));

				strcat(string, "Silahkan pilih "YELLOW"YES "WHITE"jika anda ingin menggunakan preset ini.");
				ShowPlayerDialog(playerid, DIALOG_ACC_PRESET_FOUND, DIALOG_STYLE_MSGBOX, "Preset found!", string, "Yes", "No");
			}
			else {
				ShowPlayerDialog(playerid, DIALOG_ACC_PRESET_SEARCH, DIALOG_STYLE_INPUT, "Search preset", "(error) preset tidak ditemukan!\n\nSilahkan masukkan nama preset yang ingin kamu cari:", "Search", "Close");
			}
			cache_delete(query);
		}
		else {
			ShowPlayerDialog(playerid, DIALOG_ACC_PRESET, DIALOG_STYLE_LIST, sprintf("Accessory #%d Preset", PlayerData[playerid][pAksesoris]), "Search preset (by name)\nSearch preset (by used model)\nCreate preset\n"YELLOW"My preset", "Select", "Close");
		}
	}
	if(dialogid == DIALOG_ACC_PRESET_FOUND) {
		if(response) {
			new Cache:result = mysql_query(sqlcon, sprintf("SELECT * FROM `acc_preset` WHERE `ID` = '%d' LIMIT 1;", GetPVarInt(playerid, "AccID")));

			if(cache_num_rows()) {

				new id = PlayerData[playerid][pAksesoris], name[24];

				cache_get_value_name(0, "PresetName", name, sizeof(name));
				cache_get_value_name_float(0, "X", AccData[playerid][id][accOffset][0]);
				cache_get_value_name_float(0, "Y", AccData[playerid][id][accOffset][1]);
				cache_get_value_name_float(0, "Z", AccData[playerid][id][accOffset][2]);
				cache_get_value_name_float(0, "RX", AccData[playerid][id][accRot][0]);
				cache_get_value_name_float(0, "RY", AccData[playerid][id][accRot][1]);
				cache_get_value_name_float(0, "RZ", AccData[playerid][id][accRot][2]);
				cache_get_value_name_float(0, "SX", AccData[playerid][id][accScale][0]);
				cache_get_value_name_float(0, "SY", AccData[playerid][id][accScale][1]);
				cache_get_value_name_float(0, "SZ", AccData[playerid][id][accScale][2]);
				cache_get_value_name_int(0, "Bone", AccData[playerid][id][accBone]);

				RemovePlayerAttachedObject(playerid, id);
				Aksesoris_Attach(playerid, id);

				SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Acc-Preset) "WHITE"Preset "YELLOW"\"%s\" "WHITE"berhasil digunakan pada aksesoris index #%d", name, id);
			}
			cache_delete(result);
		}
		else {
			ShowPlayerDialog(playerid, DIALOG_ACC_PRESET, DIALOG_STYLE_LIST, sprintf("Accessory #%d Preset", PlayerData[playerid][pAksesoris]), "Search preset (by name)\nSearch preset (by used model)\nCreate preset\n"YELLOW"My preset", "Select", "Close");
		}
	}
	if(dialogid == DIALOG_ACC_PRESET) {
		if(response) {
			if(listitem == 0) {
				ShowPlayerDialog(playerid, DIALOG_ACC_PRESET_SEARCH, DIALOG_STYLE_INPUT, "Search preset", "Silahkan masukkan nama preset yang ingin kamu cari:", "Search", "Close");
			} 
			if(listitem == 1) {
				new Cache:result = mysql_query(sqlcon, sprintf("SELECT * FROM `acc_preset` WHERE `Model` = '%d' LIMIT 15;", AccData[playerid][PlayerData[playerid][pAksesoris]][accModel]));

				if(cache_num_rows()) {

					new string[15 * 24], count = 0;

					for(new i = 0; i < cache_num_rows(); i++) {
						new preset_name[24], sqlid;
						cache_get_value_name(i, "PresetName", preset_name, 24);
						cache_get_value_name_int(i, "ID", sqlid);

						strcat(string, sprintf("%d) %s\n", i + 1, preset_name));
						ListedPreset[playerid][count++] = sqlid;
					}
					ShowPlayerDialog(playerid, DIALOG_ACC_PRESET_LISTED, DIALOG_STYLE_LIST, "Preset found!", string, "Use", "Close");
				}
				else {
					SendErrorMessage(playerid, "Tidak ada preset dengan model yang kamu gunakan!");
					ShowPlayerDialog(playerid, DIALOG_ACC_PRESET, DIALOG_STYLE_LIST, sprintf("Accessory #%d Preset", PlayerData[playerid][pAksesoris]), "Search preset (by name)\nSearch preset (by used model)\nCreate preset\n"YELLOW"My preset", "Select", "Close");
				}
				cache_delete(result);
			}
			if(listitem == 2) {
				ShowPlayerDialog(playerid, DIALOG_ACC_PRESET_CREATE, DIALOG_STYLE_INPUT, "Create preset", "Silahkan masukkan nama preset yang akan kamu buat: (tidak bisa lebih dari 24 huruf!)", "Create", "Close");
			}
			if(listitem == 3) {

				inline const ShowMyPreset() {
					if(cache_num_rows()) {

						new string[15 * 24], count = 0;

						for(new i = 0; i < cache_num_rows(); i++) {
							
							new sqlid, presetname[24];

							cache_get_value_name_int(i, "ID", sqlid);
							cache_get_value_name(i, "PresetName", presetname, 24);

							ListedPreset[playerid][count++] = sqlid;

							strcat(string, sprintf("%d) %s\n", i + 1, presetname));
						}
						ShowPlayerDialog(playerid, DIALOG_ACC_PRESET_LISTED, DIALOG_STYLE_LIST, "My Preset", string, "Use", "Close");
					}
				}
				MySQL_TQueryInline(sqlcon, using inline ShowMyPreset, "SELECT * FROM `acc_preset` WHERE `OwnerID` = '%d' ORDER BY `ID` ASC LIMIT 15;", PlayerData[playerid][pID]);
			}
		}
	}
	if(dialogid == DIALOG_ACC_PRESET_LISTED) {
		if(response) {
			new Cache:result = mysql_query(sqlcon, sprintf("SELECT * FROM `acc_preset` WHERE `ID` = '%d'", ListedPreset[playerid][listitem]));

			if(cache_num_rows()) {

				new name[24], id = PlayerData[playerid][pAksesoris];
				cache_get_value_name(0, "PresetName", name, 24);
				cache_get_value_name_float(0, "X", AccData[playerid][id][accOffset][0]);
				cache_get_value_name_float(0, "Y", AccData[playerid][id][accOffset][1]);
				cache_get_value_name_float(0, "Z", AccData[playerid][id][accOffset][2]);
				cache_get_value_name_float(0, "RX", AccData[playerid][id][accRot][0]);
				cache_get_value_name_float(0, "RY", AccData[playerid][id][accRot][1]);
				cache_get_value_name_float(0, "RZ", AccData[playerid][id][accRot][2]);
				cache_get_value_name_float(0, "SX", AccData[playerid][id][accScale][0]);
				cache_get_value_name_float(0, "SY", AccData[playerid][id][accScale][1]);
				cache_get_value_name_float(0, "SZ", AccData[playerid][id][accScale][2]);
				cache_get_value_name_int(0, "Bone", AccData[playerid][id][accBone]);

				RemovePlayerAttachedObject(playerid, id);
				Aksesoris_Attach(playerid, id);

				SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Acc-Preset) "WHITE"Preset "YELLOW"\"%s\" "WHITE"berhasil digunakan pada aksesoris index #%d", name, id);
			}
			cache_delete(result);
		}
		else {
			ShowPlayerDialog(playerid, DIALOG_ACC_PRESET, DIALOG_STYLE_LIST, sprintf("Accessory #%d Preset", PlayerData[playerid][pAksesoris]), "Search preset (by name)\nSearch preset (by used model)\nCreate preset\n"YELLOW"My preset", "Select", "Close");
		}
	}
	if(dialogid == DIALOG_ACC_PRESET_CREATE) {
		if(response) {
			if(strlen(inputtext) < 1 || strlen(inputtext) > 24) {
				ShowPlayerDialog(playerid, DIALOG_ACC_PRESET_CREATE, DIALOG_STYLE_INPUT, "Create preset", "Silahkan masukkan nama preset yang akan kamu buat: (tidak bisa lebih dari 24 huruf!)", "Create", "Close");
				return 1;
			}

			new query[1356];
			mysql_format(sqlcon, query, sizeof(query), "SELECT * FROM `acc_preset` WHERE `PresetName` = '%e'", inputtext);
			new Cache:result = mysql_query(sqlcon, query);

			if(!cache_num_rows()) {
				new id = PlayerData[playerid][pAksesoris];

				mysql_format(sqlcon, query, sizeof(query), "INSERT INTO `acc_preset` (`OwnerID`,`PresetName`,`Model`,`Bone`,`X`,`Y`,`Z`,`RX`,`RY`,`RZ`,`SX`,`SY`,`SZ`) VALUES('%d','%e','%d','%d','%f','%f','%f','%f','%f','%f','%f','%f','%f')",
					PlayerData[playerid][pID], inputtext,  AccData[playerid][id][accModel], AccData[playerid][id][accBone], AccData[playerid][id][accOffset][0], AccData[playerid][id][accOffset][1],AccData[playerid][id][accOffset][2], AccData[playerid][id][accRot][0], AccData[playerid][id][accRot][1], AccData[playerid][id][accRot][2], AccData[playerid][id][accScale][0], AccData[playerid][id][accScale][1], AccData[playerid][id][accScale][2]);
				mysql_tquery(sqlcon, query);

				SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Acc-Preset) "WHITE"Preset aksesoris dengan nama "YELLOW"\"%s\" "WHITE"berhasil dibuat!", inputtext);
			}
			else {
				ShowPlayerDialog(playerid, DIALOG_ACC_PRESET_CREATE, DIALOG_STYLE_INPUT, "Create preset", "(error) nama preset tersebut telah digunakan!\n\nSilahkan masukkan nama preset yang akan kamu buat: (tidak bisa lebih dari 24 huruf!)", "Create", "Close");
			}
			cache_delete(result);
		}
		else {
			ShowPlayerDialog(playerid, DIALOG_ACC_PRESET, DIALOG_STYLE_LIST, sprintf("Accessory #%d Preset", PlayerData[playerid][pAksesoris]), "Search preset (by name)\nSearch preset (by used model)\nCreate preset\n"YELLOW"My preset", "Select", "Close");
		}
	}
	if(dialogid == DIALOG_ACC_MENU) {
		if(response)
		{
			new string[24], gstr[256];
			PlayerData[playerid][pAksesoris] = listitem;

			if(!AccData[playerid][listitem][accExists])
				return SendErrorMessage(playerid, "Tidak ada aksesoris pada slot ini.");
				
			format(string,sizeof(string),"Edit Accessory (#%d)",PlayerData[playerid][pAksesoris]);
			format(gstr, sizeof(gstr), "Place %s\nChange Bone\nChange Placement\nChange Coordinate\nRemove from list\n"ORANGE"Preset menu", IsPlayerAttachedObjectSlotUsed(playerid, PlayerData[playerid][pAksesoris]) ? ("Off") : ("On"));
			ShowPlayerDialog(playerid, DIALOG_ACCESSORY, DIALOG_STYLE_LIST, string, gstr, "Select", "Exit");
		}
	}
	if(dialogid == DIALOG_BONE) {
		if(response)
		{
			new id = PlayerData[playerid][pAksesoris];
			AccData[playerid][id][accBone] = listitem+1;
			if(IsPlayerAttachedObjectSlotUsed(playerid, id))
			{
				RemovePlayerAttachedObject(playerid, id);
				AccData[playerid][id][accScale][0] = AccData[playerid][id][accScale][1] = AccData[playerid][id][accScale][2] = 1.0;
				AccData[playerid][id][accOffset][0] = AccData[playerid][id][accOffset][1] = AccData[playerid][id][accOffset][2] = 0.0;
				AccData[playerid][id][accRot][0] = AccData[playerid][id][accRot][1] = AccData[playerid][id][accRot][2] = 0.0;

				Aksesoris_Attach(playerid, id);

				if(!IsPlayerUsingAndroid(playerid))
					EditAttachedObject(playerid, id);
			}
			SendCustomMessage(playerid, X11_LIGHTBLUE, "Acessory",""WHITE"You have been changed accessory bone index #%d to %s", id, accBones[listitem]);
		}
	}
	if(dialogid == DIALOG_GIVETICKET) {

		if(!response) {
			DeletePVar(playerid, "TicketReason");
		}
		else {

			new userid = GetPVarInt(playerid, "TargetID"),
				price = strcash(inputtext),
				reason[64];

			GetPVarString(playerid, "TicketReason", reason, sizeof(reason));

			new id = Ticket_Add(userid, price, reason);

			if (id != -1) {
				SendServerMessage(playerid, "You have written %s a ticket for $%s, reason: %s", ReturnName(userid), FormatNumber(price), reason);
				SendServerMessage(userid, "%s has written you a ticket for $%s, reason: %s", ReturnName(playerid), FormatNumber(price), reason);

				SendNearbyMessage(playerid, 30.0,X11_PLUM, "** %s has written up a ticket for %s.", ReturnName(playerid), ReturnName(userid));
				Log_Write("Logs/ticket_log.txt", "[%s] %s has written a %s ticket to %s, reason: %s", ReturnDate(), ReturnName(playerid), FormatNumber(price), ReturnName(userid), reason);
			}
			else {
				SendErrorMessage(playerid, "That player already has %d outstanding tickets.", MAX_PLAYER_TICKETS);
			}

			DeletePVar(playerid, "TicketReason");
		}
	}
	if(dialogid == DIALOG_ARREST_CHARGE) {
		if(!response) {

			DeletePVar(playerid, "ArrestTime");
			DeletePVar(playerid, "TargetID");
			DeletePVar(playerid, "ArrestPrice");
		}
		else {

			if(strlen(inputtext) > 128) {
				new price, str[256],
					targetid = GetPVarInt(playerid, "TargetID");

				price = GetPVarInt(playerid, "ArrestPrice");

				format(str, sizeof(str), "Suspect: %s\nFine: $%s\n\nMasukkan arrest charge:", ReturnName(targetid), FormatNumber(price));
				ShowPlayerDialog(playerid, DIALOG_ARREST_CHARGE, DIALOG_STYLE_INPUT, "Arrest Charge", str, "Arrest", "Close");

				return 1;
			}
			new price = GetPVarInt(playerid, "ArrestPrice"),
				userid = GetPVarInt(playerid, "TargetID"),
				time = GetPVarInt(playerid, "ArrestTime");

			SetPlayerArrest(userid);

			GiveMoney(userid, -price);

			PlayerData[userid][pArrest] = 1;
			PlayerData[userid][pJailTime] = time * 60;
			format(PlayerData[userid][pJailBy], MAX_PLAYER_NAME, GetName(playerid));
			format(PlayerData[userid][pJailReason], 128, inputtext);

			SendClientMessageEx(userid, X11_RED, "(Arrest) {FFFFFF}You've been arrested by {FFFF00}%s {FFFFFF}For {FF0000}%d Minutes.", GetName(playerid), time);
			SendClientMessageEx(userid, X11_RED, "(Fine) {FFFFFF}$%s", FormatNumber(price));
			SendFactionMessage(PlayerData[playerid][pFaction], COLOR_RADIO, "ARREST: %s was arrested by %s %s", GetName(userid), Faction_GetRank(playerid), GetName(playerid));
			SendFactionMessage(PlayerData[playerid][pFaction], COLOR_RADIO, "REASON: %s", inputtext);
			
			new query[312];
			mysql_format(sqlcon, query, sizeof(query), "INSERT INTO arrest(owner, fine, reason, date) VALUES ('%d', '%d', '%s', CURRENT_TIMESTAMP())", PlayerData[userid][pID], price, inputtext);
			mysql_tquery(sqlcon, query);

			DeletePVar(playerid, "ArrestTime");
			DeletePVar(playerid, "TargetID");
			DeletePVar(playerid, "ArrestPrice");
		}
	}
	if(dialogid == DIALOG_ARREST) {
		if(!response) {
			DeletePVar(playerid, "ArrestTime");
			DeletePVar(playerid, "TargetID");
		}
		else {

			new price, str[256],
				targetid = GetPVarInt(playerid, "TargetID");

			price = strcash(inputtext);

			SetPVarInt(playerid, "ArrestPrice", price);
			format(str, sizeof(str), "Suspect: %s\nFine: $%s\n\nMasukkan arrest charge:", ReturnName(targetid), FormatNumber(price));
			ShowPlayerDialog(playerid, DIALOG_ARREST_CHARGE, DIALOG_STYLE_INPUT, "Arrest Charge", str, "Arrest", "Close");
		}
	}
	if(dialogid == DIALOG_TAKE) {

		if(GetFactionType(playerid) != FACTION_POLICE || PlayerData[playerid][pTarget] == INVALID_PLAYER_ID)
			return 0;

		if(response)
		{
			new
				userid = PlayerData[playerid][pTarget]
			;
			if(!strcmp(inputtext, "Take Weapons")) {
				ResetWeapons(userid);

				SendNearbyMessage(playerid, 15.0, X11_PLUM, "** %s has confiscated %s's weapons.", ReturnName(playerid), ReturnName(userid));
			}
			else if(!strcmp(inputtext, "Take Drugs")) {
				Inventory_Remove(userid, "Rolled Weed", -1);
				Inventory_Remove(userid, "Weed", -1);
				Inventory_Remove(userid, "Weed Seed", -1);

				SendNearbyMessage(playerid, 15.0, X11_PLUM, "** %s has confiscated %s's drugs.", ReturnName(playerid), ReturnName(userid));
			}
			else if(!strcmp(inputtext, "Take weapon parts")) {
				Inventory_Remove(userid, "9mm Luger", -1);
				Inventory_Remove(userid, "12 Gauge", -1);
				Inventory_Remove(userid, "9mm Silenced Schematic", -1);
				Inventory_Remove(userid, "Shotgun Schematic", -1);
				Inventory_Remove(userid, "9mm Silenced Material", -1);
				Inventory_Remove(userid, "Shotgun Material", -1);
				Inventory_Remove(userid, "9mm Silenced HV Schematic", -1);
				Inventory_Remove(userid, "Shotgun HV Schematic", -1);
				Inventory_Remove(userid, "Desert Eagle HV Schematic", -1);
				Inventory_Remove(userid, "Rifle HV Schematic", -1);
				Inventory_Remove(userid, "Rifle Schematic");
				Inventory_Remove(userid, "Desert Eagle Schematic");
				Inventory_Remove(userid, "7.62mm Caliber", -1);
				Inventory_Remove(userid, ".44 Magnum", -1);

				SendNearbyMessage(playerid, 15.0, X11_PLUM, "** %s has confiscated %s's weapon parts.", ReturnName(playerid), ReturnName(userid));
			}
		}
	}
	if(dialogid == DIALOG_EXECUTE) {
		if(response)
		{
			if(isnull(inputtext))
				return ShowPlayerDialog(playerid, DIALOG_EXECUTE, DIALOG_STYLE_INPUT, "Execute Query", "Please specify the MySQL query to execute below:", "Execute", "Back");

			if(strfind(inputtext, "DROP", true) != -1)
				return ShowPlayerDialog(playerid, DIALOG_EXECUTE, DIALOG_STYLE_INPUT, "Execute Query", "Error: You can't execute \"DROP\" queries.\n\nPlease specify the MySQL query to execute below:", "Execute", "Back");

			mysql_tquery(sqlcon, inputtext, "OnQueryExecute", "ds", playerid, inputtext);
		}
	}
	if(dialogid == DIALOG_GARAGE_TAKE) {
		if(response) {
			new
				id = g_Selected_Vehicle_ID[playerid][listitem];

			mysql_tquery(sqlcon, sprintf("UPDATE `vehicle` SET `vehState` = '%d', `vehGarage` = '%d' WHERE `vehID` = '%d'", VEHICLE_STATE_SPAWNED, -1, id));
			mysql_tquery(sqlcon, sprintf("SELECT * FROM `vehicle` WHERE `vehID`='%d';", id), "OnVehicleLoaded", "");

			SendServerMessage(playerid, "Kamu telah mengeluarkan kendaraan-mu dari garasi.");
		}
	}
	if(dialogid == DIALOG_GARAGE) {
		if(!response)
			return 0;

		new garage_index = g_NearGarage[playerid],
			vehicleid = GetPlayerVehicleID(playerid);

		if(listitem == 0) {
			if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
				return SendErrorMessage(playerid, "Kamu harus mengemudikan kendaraanmu!");

			if(!Vehicle_IsOwner(playerid, vehicleid))	
				return SendErrorMessage(playerid, "Ini bukan kendaraan milikmu!");

			if(Vehicle_GetType(vehicleid) != VEHICLE_TYPE_PLAYER)
				return SendErrorMessage(playerid, "Tidak bisa memasukan kendaraan rental!");

			VehicleData[vehicleid][vGarage] = GarageData[garage_index][garageID];
			VehicleData[vehicleid][vState] = VEHICLE_STATE_GARAGE;
			Vehicle_Save(vehicleid);

			SendServerMessage(playerid, "Kamu berhasil memasukan kendaraan %s-mu ke garasi.", GetVehicleName(vehicleid));
			Vehicle_Delete(vehicleid, false);
		}
		if(listitem == 1) {
			mysql_tquery(sqlcon, sprintf("SELECT * FROM `vehicle` WHERE `vehGarage` = '%d' AND `vehState` = '%d' AND `vehExtraID` = '%d'", GarageData[garage_index][garageID], VEHICLE_STATE_GARAGE, PlayerData[playerid][pID]), "OnTakeVehicleGarage", "d", playerid);
		}
	}
	if(dialogid == DIALOG_BIZINFO) {
		if(response) {
			new str[712];
			for(new i = 0; i < MAX_BUSINESS; i++) if(BizData[i][bizExists] && BizData[i][bizType] == listitem + 1 && Business_IsOpen(i)) {
				strcat(str, sprintf("%s, Stock: %d/100\n", BizData[i][bizName], BizData[i][bizStock]));
			}
			ShowPlayerDialog(playerid, DIALOG_NONE, DIALOG_STYLE_LIST, "Business Info", str, "Close", "");
		}
	}
	if(dialogid == DIALOG_VIP_NUMBER) {
		if(response) {

			if(!IsNumeric(inputtext))	
				return ShowPlayerDialog(playerid, DIALOG_VIP_NUMBER, DIALOG_STYLE_INPUT, "Custom Number", "Masukkan custom nomor handphone mu:", "Set", "Close");

			if(!strlen(inputtext))
				return ShowPlayerDialog(playerid, DIALOG_VIP_NUMBER, DIALOG_STYLE_INPUT, "Custom Number", "Masukkan custom nomor handphone mu:", "Set", "Close");

			if(strlen(inputtext) > 8)
				return ShowPlayerDialog(playerid, DIALOG_VIP_NUMBER, DIALOG_STYLE_INPUT, "Custom Number", "(error) panjang nomor tidak bisa lebih dari 8!\nMasukkan custom nomor handphone mu:", "Set", "Close");
		
			new number = strval(inputtext);
			mysql_tquery(sqlcon, sprintf("SELECT * FROM `characters` WHERE `Number` = '%d'", number), "OnVIPCheckNumber", "dd", playerid, number);
		}
	}
	if(dialogid == DIALOG_VIP_MASK) {
		if(response) {
			new maskid = strval(inputtext);

			if(!IsNumeric(inputtext))	
				return ShowPlayerDialog(playerid, DIALOG_VIP_MASK, DIALOG_STYLE_INPUT, "Custom Number", "Masukkan custom nomor handphone mu:", "Set", "Close");

			if(!maskid)
				return ShowPlayerDialog(playerid, DIALOG_VIP_MASK, DIALOG_STYLE_INPUT, "Custom Number", "Masukkan custom nomor handphone mu:", "Set", "Close");

			if(strlen(inputtext) > 8)
				return ShowPlayerDialog(playerid, DIALOG_VIP_MASK, DIALOG_STYLE_INPUT, "Custom Number", "(error) panjang mask id tidak bisa lebih dari 8!\nMasukkan custom nomor handphone mu:", "Set", "Close");
		
			mysql_tquery(sqlcon, sprintf("SELECT * FROM `characters` WHERE `MaskID` = '%d'", maskid), "OnVIPCheckMask", "dd", playerid, maskid);
		}
	}
	if(dialogid == DIALOG_VIP_POINT) {
		if(response) {
			switch(listitem) {
				case 0: {

					if(PlayerData[playerid][pCoin] < 100)
						return SendErrorMessage(playerid, "Kamu tidak memiliki cukup Donater Point.");

					ShowPlayerDialog(playerid, DIALOG_VIP_NUMBER, DIALOG_STYLE_INPUT, "Custom Number", "Masukkan custom nomor handphone mu:", "Set", "Close");
				}
				case 1: {

					if(PlayerData[playerid][pCoin] < 150)
						return SendErrorMessage(playerid, "Kamu tidak memiliki cukup Donater Point.");

					ShowPlayerDialog(playerid, DIALOG_VIP_MASK, DIALOG_STYLE_INPUT, "Custom Mask", "Masukkan custom mask id mu:", "Set", "Close");
				}
				case 2: {

					if(PlayerData[playerid][pCoin] < 250)
						return SendErrorMessage(playerid, "Kamu tidak memiliki cukup Donater Point.");

					SendAdminMessage(X11_TOMATO, "DonaterInfo: %s(%s) has requested \"Custom Gate\" (costs 250 point) please check /gaterequests", GetName(playerid, false), GetUsername(playerid));
					SendServerMessage(playerid, "Kamu telah memasuki pending request "CYAN"Custom Gate, "WHITE"silahkan tunggu admin level 6+ untuk merespon.");
					SendServerMessage(playerid, "Orang Tua Coins mu telah dikurangi sebesar "YELLOW"250 coin");
					PlayerData[playerid][pCoin] -= 250;
					mysql_tquery(sqlcon, sprintf("INSERT INTO `gaterequests` (`Name`, `Date`) VALUES('%s', '%s')", GetName(playerid), ReturnDate(true)));
				}
			}
		}
	}
	if(dialogid == DIALOG_FLAT_TENANT_REMOVE) {
		if(response) {
			new sqlid = g_ListedTenant[playerid][listitem], id = Flat_Inside(playerid);

			new query[256];

			mysql_format(sqlcon, query, 256, "DELETE FROM `flatkeys` WHERE `PlayerID` = '%d' AND `FlatID` = '%d' LIMIT 1;", sqlid, FlatData[id][flatID]);
			mysql_tquery(sqlcon, query);

			SendServerMessage(playerid, "Kamu berhasil menghapus tenant pada slot %d.", listitem + 1);
		}
	}
	if(dialogid == DIALOG_HOUSE_TENANT_REMOVE) {
		if(response) {
			new sqlid = g_ListedTenant[playerid][listitem], id = House_Inside(playerid);

			new query[256];

			mysql_format(sqlcon, query, 256, "DELETE FROM `housekeys` WHERE `PlayerID` = '%d' AND `HouseID` = '%d' LIMIT 1;", sqlid, HouseData[id][houseID]);
			mysql_tquery(sqlcon, query);

			SendServerMessage(playerid, "Kamu berhasil menghapus tenant pada slot %d.", listitem + 1);
		}
	}
	if(dialogid == DIALOG_HOUSE_KEY) {
		if(!response)
			return ShowHouseMenu(playerid);

		new id = House_Inside(playerid);

		switch(listitem) {
			case 0: 
			{

				if(!House_IsOwner(playerid, id))
					return 0;

				new Cache:execute = mysql_query(sqlcon, sprintf("SELECT * FROM `housekeys` WHERE `HouseID` = %d", HouseData[id][houseID]));

				if(cache_num_rows() >= House_TenantLimit(HouseData[id][houseType])) {
					
					SendErrorMessage(playerid, "Kunci pada rumah tidak bisa diberikan lebih dari %d orang.", House_TenantLimit(HouseData[id][houseType]));
				}
				else {
					ShowPlayerDialog(playerid, DIALOG_HOUSE_KEY_SHARE, DIALOG_STYLE_INPUT, "House Share Key", "Masukkan ID/Nama player yang akan diberikan kunci Rumah.", "Share", "Close");
				}
				cache_delete(execute);
			}
			case 1: 
			{
				new str[156];
				mysql_format(sqlcon, str, 156, "SELECT * FROM `housekeys` WHERE `HouseID` = '%d' ORDER BY `ID` ASC", HouseData[id][houseID]);
				new Cache:result = mysql_query(sqlcon, str);

				if(cache_num_rows()) {

					new count = 0, string[512];
					for(new i = 0; i < cache_num_rows(); i++) {
						new sqlid, name[24];
						cache_get_value_name(i, "Name", name, 24);
						cache_get_value_name_int(i, "PlayerID", sqlid);
						g_ListedTenant[playerid][count++] = sqlid;

						strcat(string, sprintf("%d) Name: %s\n", i + 1, name));

					}

					if(count)
						ShowPlayerDialog(playerid, DIALOG_HOUSE_TENANT_REMOVE, DIALOG_STYLE_LIST, "Remove Tenant", string, "Remove", "Close");
				}
				else {
					SendServerMessage(playerid, "Tidak ada tenant pada rumah ini.");
				}
				cache_delete(result);
			}
			case 2: 
			{

				mysql_tquery(sqlcon, sprintf("SELECT * FROM `housekeys` WHERE `HouseID` = %d ORDER BY `ID` ASC", HouseData[id][houseID]), "House_CheckSharedKey", "dd", playerid, id);
			}
		}
	}
	if(dialogid == DIALOG_HOUSE_KEY_SHARE) {
		if(!response)
			return 0;

		new id = House_Inside(playerid), targetid = INVALID_PLAYER_ID;

		if(!House_IsOwner(playerid, id))
			return 0;

		if(sscanf(inputtext, "u", targetid))
			return ShowPlayerDialog(playerid, DIALOG_HOUSE_KEY_SHARE, DIALOG_STYLE_INPUT, "House Share Key", "Masukkan ID/Nama player yang akan diberikan kunci Rumah.", "Share", "Close");

		if(targetid == INVALID_PLAYER_ID)
			return ShowPlayerDialog(playerid, DIALOG_HOUSE_KEY_SHARE, DIALOG_STYLE_INPUT, "House Share Key", "(error) Player tersebut tidak berada didekatmu!\nMasukkan ID/Nama player yang akan diberikan kunci Rumah.", "Share", "Close");
	
		if(!IsPlayerNearPlayer(playerid, targetid, 5.0))
			return ShowPlayerDialog(playerid, DIALOG_HOUSE_KEY_SHARE, DIALOG_STYLE_INPUT, "House Share Key", "(error) Player tersebut tidak berada didekatmu!\nMasukkan ID/Nama player yang akan diberikan kunci Rumah.", "Share", "Close");
	
		if(House_GetCount(targetid) > 0)
			return ShowPlayerDialog(playerid, DIALOG_HOUSE_KEY_SHARE, DIALOG_STYLE_INPUT, "House Share Key", "(error) Player tersebut sudah memiliki rumah!\nMasukkan ID/Nama player yang akan diberikan kunci Rumah.", "Share", "Close");
		SendServerMessage(playerid, "Kamu telah memberikan kunci rumah kepada %s.", ReturnName(targetid));
		SendServerMessage(targetid, "Kamu telah diberikan %s kunci rumah miliknya.", ReturnName(playerid));

		mysql_tquery(sqlcon, sprintf("INSERT INTO `housekeys` (`HouseID`, `PlayerID`, `Name`) VALUES('%d','%d','%s')", HouseData[id][houseID], PlayerData[targetid][pID], GetName(targetid)));
	}
	if(dialogid == DIALOG_FLAT_KEY_SHARE) {
		if(!response)
			return 0;

		new flatid = Flat_Inside(playerid), targetid = INVALID_PLAYER_ID;

		if(!Flat_IsOwner(playerid, flatid))
			return 0;

		if(sscanf(inputtext, "u", targetid))
			return ShowPlayerDialog(playerid, DIALOG_FLAT_KEY_SHARE, DIALOG_STYLE_INPUT, "Flat Share Key", "Masukkan ID/Nama player yang akan diberikan kunci Flat.", "Share", "Close");

		if(targetid == INVALID_PLAYER_ID)
			return ShowPlayerDialog(playerid, DIALOG_FLAT_KEY_SHARE, DIALOG_STYLE_INPUT, "Flat Share Key", "(error) Player tersebut tidak berada didekatmu!\nMasukkan ID/Nama player yang akan diberikan kunci Flat.", "Share", "Close");
	
		if(!IsPlayerNearPlayer(playerid, targetid, 5.0))
			return ShowPlayerDialog(playerid, DIALOG_FLAT_KEY_SHARE, DIALOG_STYLE_INPUT, "Flat Share Key", "(error) Player tersebut tidak berada didekatmu!\nMasukkan ID/Nama player yang akan diberikan kunci Flat.", "Share", "Close");
	
		if(Flat_GetCount(targetid) > 0)
			return ShowPlayerDialog(playerid, DIALOG_FLAT_KEY_SHARE, DIALOG_STYLE_INPUT, "Flat Share Key", "(error) Player tersebut sudah memiliki rumah!\nMasukkan ID/Nama player yang akan diberikan kunci Flat.", "Share", "Close");
		
		SendServerMessage(playerid, "Kamu telah memberikan kunci flat kepada %s.", ReturnName(targetid));
		SendServerMessage(targetid, "Kamu telah diberikan %s kunci flat miliknya.", ReturnName(playerid));

		mysql_tquery(sqlcon, sprintf("INSERT INTO `flatkeys` (`FlatID`, `PlayerID`, `Name`) VALUES('%d','%d','%s')", FlatData[flatid][flatID], PlayerData[targetid][pID], GetName(targetid)));
	}
	if(dialogid == DIALOG_FLAT_KEY) {
		if(!response)
			return cmd_flat(playerid, "menu");

		new flatid = Flat_Inside(playerid);


		switch(listitem) {
			case 0: 
			{

				if(!Flat_IsOwner(playerid, flatid))
					return 0;

				new Cache:execute = mysql_query(sqlcon, sprintf("SELECT * FROM `flatkeys` WHERE `FlatID` = %d", FlatData[flatid][flatID]));

				if(cache_num_rows()) {
					
					SendErrorMessage(playerid, "Kunci pada Flat tidak bisa diberikan lebih dari 1 orang.");
				}
				else {
					ShowPlayerDialog(playerid, DIALOG_FLAT_KEY_SHARE, DIALOG_STYLE_INPUT, "Flat Share Key", "Masukkan ID/Nama player yang akan diberikan kunci Flat.", "Share", "Close");
				}
				cache_delete(execute);
			}
			case 1: 
			{
				new str[156];
				mysql_format(sqlcon, str, 156, "SELECT * FROM `flatkeys` WHERE `FlatID` = '%d' ORDER BY `ID` ASC", FlatData[flatid][flatID]);
				new Cache:result = mysql_query(sqlcon, str);

				if(cache_num_rows()) {

					new count = 0, string[512];
					for(new i = 0; i < cache_num_rows(); i++) {
						new sqlid, name[24];
						cache_get_value_name(i, "Name", name, 24);
						cache_get_value_name_int(i, "PlayerID", sqlid);
						g_ListedTenant[playerid][count++] = sqlid;

						strcat(string, sprintf("%d) Name: %s\n", i + 1, name));

					}

					if(count)
						ShowPlayerDialog(playerid, DIALOG_FLAT_TENANT_REMOVE, DIALOG_STYLE_LIST, "Remove Tenant", string, "Remove", "Close");
				}
				else {
					SendServerMessage(playerid, "Tidak ada tenant pada flat ini.");
				}
				cache_delete(result);
			}
			case 2: 
			{

				mysql_tquery(sqlcon, sprintf("SELECT * FROM `flatkeys` WHERE `FlatID` = %d ORDER BY `ID` ASC", FlatData[flatid][flatID]), "Flat_CheckSharedKey", "dd", playerid, flatid);
			}
		}
	}
	if(dialogid == DIALOG_FLAT_MENU) {
		if(!response)
			return 0;

		switch(listitem) {
			case 0: {

				if(!Flat_IsOwner(playerid, Flat_Inside(playerid)))
					return SendErrorMessage(playerid, "Only owner can access this option.");

				Flat_ShowKeyMenu(playerid, Flat_Inside(playerid));
			}
			case 1: 
			{

				if(!Flat_IsOwner(playerid, Flat_Inside(playerid)))
					return SendErrorMessage(playerid, "Only owner can access this option.");

				Flat_OpenStorage(playerid, Flat_Inside(playerid));
			}
			case 2: {
				ShowPlayerDialog(playerid, DIALOG_FLAT_FURNITURE, DIALOG_STYLE_LIST, "House Furniture", "Listed Furniture\nAdd Furniture\n"RED"Reset all furniture\n"YELLOW"Upgrade furniture slot ", "Select", "Close");
			}
			case 3: {
				new string[256], price = 0,
					id = Flat_Inside(playerid);

				price = FlatData[id][flatPrice] * 5/100;
				strcat(string, sprintf("Harga Pajak: $%s\n", FormatNumber(price)));
				strcat(string, sprintf("Status: %s\n", (FlatData[id][flatTaxState] == TAX_STATE_COOLDOWN) ? ("belum bisa dibayar") : ("sudah bisa dibayar")));
				strcat(string, sprintf("%s: %s\n", (FlatData[id][flatTaxState] == TAX_STATE_COOLDOWN) ? ("Bayar dalam") : ("Jatuh tempo"), ConvertTimestamp(Timestamp:FlatData[id][flatTaxDate])));
				ShowPlayerDialog(playerid, DIALOG_NONE, DIALOG_STYLE_MSGBOX, "Tax Detail", string, "Close", "");
			}
		}
	}
	if(dialogid == DIALOG_ECONOMY_MOWER) {
		if(!response)
			return 0;

		new new_salary = strcash(inputtext);
		if(!new_salary)
			return ShowMowerEconomy(playerid);

		salaryMower = new_salary;
		SendServerMessage(playerid, "Berhasil mengubah salary mower menjadi $%s.", FormatNumber(salaryMower));
		SaveEconomyData();
	}
	if(dialogid == DIALOG_ECONOMY_TRASHMASTER) {
		if(!response)
			return 0;

		new new_salary = strcash(inputtext);
		if(!new_salary)
			return ShowTrashmasterEconomy(playerid);

		salaryTrashmaster = new_salary;
		SendServerMessage(playerid, "Berhasil mengubah salary trashmaster menjadi $%s.", FormatNumber(salaryTrashmaster));
		SaveEconomyData();
	}
	if(dialogid == DIALOG_ECONOMY_BUS) {
		if(!response)
			return 0;

		new new_salary = strcash(inputtext);
		if(!new_salary)
			return ShowBusEconomy(playerid);

		salaryBus = new_salary;
		SendServerMessage(playerid, "Berhasil mengubah salary bus menjadi $%s.", FormatNumber(salaryBus));
		SaveEconomyData();
	}
	if(dialogid == DIALOG_ECONOMY_SWEEPER) {
		if(!response)
			return 0;

		new new_salary = strcash(inputtext);
		if(!new_salary)
			return ShowSweeperEconomy(playerid);

		salarySweeper = new_salary;
		SendServerMessage(playerid, "Berhasil mengubah salary sweeper menjadi $%s.", FormatNumber(salarySweeper));
		SaveEconomyData();
	}
	if(dialogid == DIALOG_ECONOMY) {

		if(!response)
			return 0;

		if(listitem == 0) ShowSweeperEconomy(playerid);
		if(listitem == 1) ShowBusEconomy(playerid);
		if(listitem == 2) ShowTrashmasterEconomy(playerid);
		if(listitem == 3) ShowMowerEconomy(playerid);
	}
	if(dialogid == DIALOG_REPORTS)
	{
		if(!response)
			return 0;

		new index = ListedReport[playerid][listitem];
		
		if(!Iter_Contains(Report, index))
			return SendErrorMessage(playerid, "Report yang dipilih tidak lagi valid.");

		selectReport[playerid] = index;
		ShowPlayerDialog(playerid, DIALOG_REPORTS_ACTION, DIALOG_STYLE_LIST, sprintf("Report - %s", GetName(ReportData[index][reportOwner])), "Accept Report\nDenied Report\nIgnore Report", "Select", "Close");
	}
	if(dialogid == DIALOG_REPORTS_ACTION) {
		if(!response)
			return 0;

		new index = selectReport[playerid];

		if(!Iter_Contains(Report, index))
			return SendErrorMessage(playerid, "Report yang dipilih tidak lagi valid.");

		if(listitem == 0) {
			SendAdminMessage(COLOR_CLIENT, "[REPORT] {FFFFFF}%s telah {00FF00}menerima {FFFFFF}report dari {FFFF00}%s(%d)", GetUsername(playerid), GetName(ReportData[index][reportOwner]), ReportData[index][reportOwner]);
			SendServerMessage(ReportData[index][reportOwner], "Laporanmu telah {00FF00}diterima {FFFFFF}oleh %s.", GetUsername(playerid));
			PlayerData[playerid][pAdminPoint]++;
		}
		if(listitem == 1) {
			SendAdminMessage(COLOR_CLIENT, "[REPORT] {FFFFFF}%s telah {FF0000}menolak {FFFFFF}report dari {FFFF00}%s(%d)", GetUsername(playerid), GetName(ReportData[index][reportOwner]), ReportData[index][reportOwner]);
			SendServerMessage(ReportData[index][reportOwner], "Laporanmu telah {00FF00}ditolak {FFFFFF}oleh %s.", GetUsername(playerid));
		}
		if(listitem == 2) {
			SendAdminMessage(COLOR_CLIENT, "[REPORT] {FFFFFF}%s telah {FF0000}mengabaikan {FFFFFF}report dari {FFFF00}%s(%d)", GetUsername(playerid), GetName(ReportData[index][reportOwner]), ReportData[index][reportOwner]);
		}
		Report_Remove(index, false);
	}
	if(dialogid == DIALOG_SPRAYTAG_MODE)
	{
		if(!response)
			return ShowTagSetup(playerid);

		new id = Tag_Create(playerid);

		if(id == INVALID_ITERATOR_SLOT)
			return SendErrorMessage(playerid, "This server cannot create more tags!");


		PlayerData[playerid][pEditing] = id;
		PlayerData[playerid][pEditType] = EDIT_TAG;
		Streamer_Update(playerid, STREAMER_TYPE_OBJECT);

		if(listitem == 0)
		{
			ShowEditTextDraw(playerid);
		}
		if(listitem == 1)
		{
			EditDynamicObject(playerid, TagData[id][tagObject]);
		}
	}
	if(dialogid == DIALOG_SPRAYTAG_TEXT)
	{
		if(response)
		{
			if(isnull(inputtext))
				return cmd_tag(playerid, "create");

			if(strlen(inputtext) > 64)
				return SendErrorMessage(playerid, "Text characters cannot more than 64 chars!"), cmd_tag(playerid, "create");

			format(TagText[playerid], 64, inputtext);
			ShowTagSetup(playerid);

		}
	}
	if(dialogid == DIALOG_SPRAYTAG_FONT)
	{
		if(!response)
			return ShowTagSetup(playerid);

		if(isnull(inputtext))
			return ShowPlayerDialog(playerid, DIALOG_SPRAYTAG_FONT, DIALOG_STYLE_INPUT, "Tag - Font", "Please input the fontface name:", "Set", "Return");

		if(strlen(inputtext) > 24)
			return ShowPlayerDialog(playerid, DIALOG_SPRAYTAG_FONT, DIALOG_STYLE_INPUT, "Tag - Font", "Please input the fontface name:", "Set", "Return");

		format(TagFont[playerid], 24, inputtext);
		ShowTagSetup(playerid);
	}
	if(dialogid == DIALOG_SPRAYTAG_SIZE)
	{
		if(!response)
			return ShowTagSetup(playerid);

		if(isnull(inputtext))
			return ShowPlayerDialog(playerid, DIALOG_SPRAYTAG_SIZE, DIALOG_STYLE_INPUT, "Tag - Font Size", "Please input the fontsize:\nNote: min 24 max 255!", "Set", "Return");

		if(!IsNumeric(inputtext))
			return ShowPlayerDialog(playerid, DIALOG_SPRAYTAG_SIZE, DIALOG_STYLE_INPUT, "Tag - Font Size", "Please input the fontsize:\nNote: min 24 max 255!", "Set", "Return");

		if(strval(inputtext) < 24 || strval(inputtext) > 255)
			return ShowPlayerDialog(playerid, DIALOG_SPRAYTAG_SIZE, DIALOG_STYLE_INPUT, "Tag - Font Size", "Please input the fontsize:\nNote: min 24 max 255!", "Set", "Return");

		TagSize[playerid] = strval(inputtext);
		ShowTagSetup(playerid);
	}
	if(dialogid == DIALOG_SPRAYTAG_COLOR)
	{
		if(!response)
			return 1;

		if(isnull(inputtext))
			return ShowPlayerDialog(playerid, DIALOG_SPRAYTAG_COLOR, DIALOG_STYLE_INPUT, "Tag - Color", "Please input the color for the tag:\nExample: 0xFFFFFFFF (white)", "Set", "Return");

		TagColor[playerid] = HexToInt(inputtext);
		ShowTagSetup(playerid);
	}
	if(dialogid == DIALOG_SPRAYTAG)
	{
		if(!response)
			return 1;

		if(listitem == 0)
		{
			ShowPlayerDialog(playerid, DIALOG_SPRAYTAG_FONT, DIALOG_STYLE_INPUT, "Tag - Font", "Please input the fontface name:", "Set", "Return");
		}
		if(listitem == 1)
		{
			ShowPlayerDialog(playerid, DIALOG_SPRAYTAG_SIZE, DIALOG_STYLE_INPUT, "Tag - Font Size", "Please input the fontsize:\nNote: min 24 max 255!", "Set", "Return");
		}
		if(listitem == 2)
		{
			TagBold[playerid] = !(TagBold[playerid]);
			ShowTagSetup(playerid);
		}
		if(listitem == 3)
		{
			ShowPlayerDialog(playerid, DIALOG_SPRAYTAG_COLOR, DIALOG_STYLE_INPUT, "Tag - Color", "Please input the color for the tag:\nExample: 0xFFFFFFFF (white)", "Set", "Return");
		}
		if(listitem == 4)
		{
			ShowPlayerDialog(playerid, DIALOG_SPRAYTAG_MODE, DIALOG_STYLE_LIST, "Tag - Edit Mode", "TextDraw Click\nClick n Drag", "Select", "Close");
		}
	}
	if(dialogid == DIALOG_SELLFISH)
	{
	    if(response)
	    {
	        new total = GetPVarInt(playerid, "FishPrice");

			PlayerData[playerid][pFishDelay] = 600;
			AddSalary(playerid, "Sell Fish", total);
			SendClientMessageEx(playerid, COLOR_SERVER, "(Fish) {FFFFFF}You have sold all the fish and earn {009000}$%s {FFFFFF}on your {FFFF00}/salary", FormatNumber(total));
			DeletePVar(playerid, "FishPrice");

	        for(new i = 0; i < MAX_FISH; i++)
	        {
				format(FishName[playerid][i], 12, "Empty");
				FishWeight[playerid][i] = 0.0;
			}
		}
	}
	if(dialogid == DIALOG_TAXI)
	{
		if (response)
		{
		    new targetid = strval(inputtext);

		    if (!IsPlayerConnected(targetid))
		        return SendErrorMessage(playerid, "The specified player has disconnected.");

			if (!PlayerData[targetid][pTaxiCalled])
			    return SendErrorMessage(playerid, "Player tersebut tidak lagi memesan taxi.");

			new
				Float:x,
				Float:y,
				Float:z;


			PlayerData[targetid][pTaxiCalled] = false;
			GetPlayerPos(targetid, x, y, z);
			SetPlayerCheckpoint(playerid, x, y, z, 3.5);
			PlayerData[playerid][pTracking] = true;

	        SendServerMessage(playerid, "You have accepted %s's taxi call.", ReturnName(targetid));
	        SendServerMessage(targetid, "%s has accepted your taxi call and is on their way.", ReturnName(playerid));
		}
	}
	if(dialogid == DIALOG_FLAT_WEAPON)
	{
	    if(response)
	    {
			static
			    flatid = -1;

		    if ((flatid = Flat_Inside(playerid)) != -1 && (Flat_IsHaveAccess(playerid, flatid)))
			{
				if (response)
				{
				    if (FlatData[flatid][flatWeapons][listitem] != 0)
				    {
				        if(PlayerData[playerid][pLevel] < 3)
				            return SendErrorMessage(playerid, "You must level 3 first to holding weapon.");
				            
				        if(PlayerHasWeapon(playerid, FlatData[flatid][flatWeapons][listitem]))
				            return SendErrorMessage(playerid, "You already have this type of weapon!");
				           
						GiveWeaponToPlayer(playerid, FlatData[flatid][flatWeapons][listitem], FlatData[flatid][flatAmmo][listitem],FlatData[flatid][flatDurability][listitem], FlatData[flatid][flatHighVelocity][listitem]);

						SendNearbyMessage(playerid, 30.0,X11_PLUM, "** %s has taken a \"%s\" from their weapon storage.", ReturnName(playerid), ReturnWeaponName(FlatData[flatid][flatWeapons][listitem]));
		                Log_Write("Logs/storage_log.txt", "[%s] %s has taken a \"%s\" from Flat ID: %d (owner: %s).", ReturnDate(), ReturnName(playerid), ReturnWeaponName(FlatData[flatid][flatWeapons][listitem]), FlatData[flatid][flatID], (Flat_IsOwner(playerid, flatid)) ? ("Yes") : ("No"));

						FlatData[flatid][flatWeapons][listitem] = 0;
						FlatData[flatid][flatAmmo][listitem] = 0;
						FlatData[flatid][flatDurability][listitem] = 0;
						FlatData[flatid][flatHighVelocity][listitem] = 0;

						Flat_Save(flatid);
						Flat_WeaponStorage(playerid, flatid);
					}
					else
					{
					    new
							weaponid = GetWeapon(playerid),
							ammo = PlayerData[playerid][pAmmo][g_aWeaponSlots[weaponid]];

					    if (!weaponid)
					        return SendErrorMessage(playerid, "You are not holding any weapon!");

						if(PlayerData[playerid][pOnDuty])
							return SendErrorMessage(playerid, "You can't store a weapon since faction duty.");
							
						FlatData[flatid][flatWeapons][listitem] = weaponid;
						FlatData[flatid][flatAmmo][listitem] = ammo;
						FlatData[flatid][flatDurability][listitem] = PlayerData[playerid][pDurability][g_aWeaponSlots[weaponid]];
						FlatData[flatid][flatHighVelocity][listitem] = PlayerData[playerid][pHighVelocity][g_aWeaponSlots[weaponid]];

						Flat_Save(flatid);
						Flat_WeaponStorage(playerid, flatid);

		                ResetWeapon(playerid, weaponid);
						SendNearbyMessage(playerid, 30.0,X11_PLUM, "** %s has stored a \"%s\" into their weapon storage.", ReturnName(playerid), ReturnWeaponName(weaponid));

						Log_Write("Logs/storage_log.txt", "[%s] %s has stored a \"%s\" to Flat ID: %d (owner: %s).", ReturnDate(), ReturnName(playerid), ReturnWeaponName(FlatData[flatid][flatWeapons][listitem]), FlatData[flatid][flatID], (Flat_IsOwner(playerid, flatid)) ? ("Yes") : ("No"));
					}
				}
			}
		}
	}
	if(dialogid == DIALOG_HOUSEWEAPON)
	{
	    if(response)
	    {
			static
			    houseid = -1;

		    if ((houseid = House_Inside(playerid)) != -1 && (House_HaveAccess(playerid, houseid)))
			{
				if (response)
				{
				    if (HouseData[houseid][houseWeapons][listitem] != 0)
				    {
				        if(PlayerData[playerid][pLevel] < 3)
				            return SendErrorMessage(playerid, "You must level 3 first to holding weapon.");
				            
				        if(PlayerHasWeapon(playerid, HouseData[houseid][houseWeapons][listitem]))
				            return SendErrorMessage(playerid, "You already have this type of weapon!");
				           
						GiveWeaponToPlayer(playerid, HouseData[houseid][houseWeapons][listitem], HouseData[houseid][houseAmmo][listitem],HouseData[houseid][houseDurability][listitem], HouseData[houseid][houseHighVelocity][listitem]);

						SendNearbyMessage(playerid, 30.0,X11_PLUM, "** %s has taken a \"%s\" from their weapon storage.", ReturnName(playerid), ReturnWeaponName(HouseData[houseid][houseWeapons][listitem]));
		                Log_Write("Logs/storage_log.txt", "[%s] %s has taken a \"%s\" from house ID: %d (owner: %s).", ReturnDate(), ReturnName(playerid), ReturnWeaponName(HouseData[houseid][houseWeapons][listitem]), HouseData[houseid][houseID], (House_IsOwner(playerid, houseid)) ? ("Yes") : ("No"));

						HouseData[houseid][houseWeapons][listitem] = 0;
						HouseData[houseid][houseAmmo][listitem] = 0;
						HouseData[houseid][houseDurability][listitem] = 0;
						HouseData[houseid][houseHighVelocity][listitem] = 0;

						House_Save(houseid);
						House_WeaponStorage(playerid, houseid);
					}
					else
					{
					    new
							weaponid = GetWeapon(playerid),
							ammo = PlayerData[playerid][pAmmo][g_aWeaponSlots[weaponid]];

					    if (!weaponid)
					        return SendErrorMessage(playerid, "You are not holding any weapon!");

						if(PlayerData[playerid][pOnDuty])
							return SendErrorMessage(playerid, "You can't store a weapon since faction duty.");

						HouseData[houseid][houseWeapons][listitem] = weaponid;
						HouseData[houseid][houseAmmo][listitem] = ammo;
						HouseData[houseid][houseDurability][listitem] = PlayerData[playerid][pDurability][g_aWeaponSlots[weaponid]];
						HouseData[houseid][houseHighVelocity][listitem] = PlayerData[playerid][pHighVelocity][g_aWeaponSlots[weaponid]];
						
						House_Save(houseid);
						House_WeaponStorage(playerid, houseid);

		                ResetWeapon(playerid, weaponid);
						SendNearbyMessage(playerid, 30.0,X11_PLUM, "** %s has stored a \"%s\" into their weapon storage.", ReturnName(playerid), ReturnWeaponName(weaponid));

						Log_Write("Logs/storage_log.txt", "[%s] %s has stored a \"%s\" to house ID: %d (owner: %s).", ReturnDate(), ReturnName(playerid), ReturnWeaponName(HouseData[houseid][houseWeapons][listitem]), HouseData[houseid][houseID], (House_IsOwner(playerid, houseid)) ? ("Yes") : ("No"));
					}
				}
			}
		}
	}
	if(dialogid == DIALOG_FLAT_OPTION)
	{
	    new
		    flatid = Flat_Inside(playerid),
			itemid = -1,
			string[32];
			
	    if(response)
	    {
		    itemid = PlayerData[playerid][pListitem];

		    strunpack(string, FlatStorage[flatid][itemid][fItemName]);
			if (response)
			{
				switch (listitem)
				{
				    case 0:
				    {
				        if (FlatStorage[flatid][itemid][fItemQuantity] == 1)
				        {
				            new id = Inventory_Add(playerid, string, FlatStorage[flatid][itemid][fItemModel], 1);

							if (id == -1)
	        					return SendErrorMessage(playerid, "You don't have any inventory slots left.");

				            Flat_RemoveItem(flatid, string);
				            SendNearbyMessage(playerid, 30.0,X11_PLUM, "** %s has taken a \"%s\" from their house storage.", ReturnName(playerid), string);

							Flat_ShowItems(playerid, flatid);
							Log_Write("Logs/storage_log.txt", "[%s] %s has taken \"%s\" from Flat ID: %d (owner: %s).", ReturnDate(), ReturnName(playerid), string, FlatData[flatid][flatID], (Flat_IsOwner(playerid, flatid)) ? ("Yes") : ("No"));
				        }
				        else
				        {
				            new str[128];
				            format(str, sizeof(str), "Item: %s (Amount: %d)\n\nPlease enter the amount that you wish to take for this item:", string, FlatStorage[flatid][itemid][fItemQuantity]);
				            ShowPlayerDialog(playerid, DIALOG_FLAT_WITHDRAW, DIALOG_STYLE_INPUT, "Flat Take", str, "Take", "Back");
				        }
				    }
					case 1:
					{
						new id = Inventory_GetItemID(playerid, string);

						if(id == -1)
						{
							Flat_ShowItems(playerid, flatid);

							return SendErrorMessage(playerid, "You don't have anymore of this item to store!");
						}
						else if (InventoryData[playerid][id][invQuantity] == 1)
						{
						    if(!strcmp(string, "Cellphone"))
						        return SendErrorMessage(playerid, "You can't do that on this item! (%s)", string);

						    if(!strcmp(string, "Mask"))
						        return SendErrorMessage(playerid, "You can't do that on this item! (%s)", string);
						        
						    if(!strcmp(string, "GPS"))
						        return SendErrorMessage(playerid, "You can't do that on this item! (%s)", string);

						    if(!strcmp(string, "Portable Radio"))
						        return SendErrorMessage(playerid, "You can't do that on this item! (%s)", string);
						        
						    Flat_AddItem(flatid, string, InventoryData[playerid][id][invModel]);
							Inventory_Remove(playerid, string);

							SendNearbyMessage(playerid, 30.0,X11_PLUM, "** %s has stored a \"%s\" into their house storage.", ReturnName(playerid), string);
							Flat_ShowItems(playerid, flatid);
						}
						else if (InventoryData[playerid][id][invQuantity] > 1)
						{
						    if(!strcmp(string, "Cellphone"))
						        return SendErrorMessage(playerid, "You can't do that on this item! (%s)", string);

						    if(!strcmp(string, "Mask"))
						        return SendErrorMessage(playerid, "You can't do that on this item! (%s)", string);
						        
						    if(!strcmp(string, "GPS"))
						        return SendErrorMessage(playerid, "You can't do that on this item! (%s)", string);

						    if(!strcmp(string, "Portable Radio"))
						        return SendErrorMessage(playerid, "You can't do that on this item! (%s)", string);
						        
							PlayerData[playerid][pListitem] = id;
							new str[128];
							format(str, sizeof(str), "Item: %s (Amount: %d)\n\nPlease enter the quantity that you wish to store for this item:" , string, InventoryData[playerid][PlayerData[playerid][pListitem]][invQuantity]);
	                        ShowPlayerDialog(playerid, DIALOG_FLAT_DEPOSIT, DIALOG_STYLE_INPUT, "Flat Deposit", str, "Store", "Back");
						}
					}
				}
			}
		}
		else
		{
		    Flat_ShowItems(playerid, flatid);
		}
	}
	if(dialogid == DIALOG_HOUSEOPTION)
	{
	    new
		    houseid = House_Inside(playerid),
			itemid = -1,
			string[32];
			
	    if(response)
	    {
		    itemid = PlayerData[playerid][pListitem];

		    strunpack(string, HouseStorage[houseid][itemid][hItemName]);
			if (response)
			{
				switch (listitem)
				{
				    case 0:
				    {
				        if (HouseStorage[houseid][itemid][hItemQuantity] == 1)
				        {
				            new id = Inventory_Add(playerid, string, HouseStorage[houseid][itemid][hItemModel], 1);

							if (id == -1)
	        					return SendErrorMessage(playerid, "You don't have any inventory slots left.");

				            House_RemoveItem(houseid, string);
				            SendNearbyMessage(playerid, 30.0,X11_PLUM, "** %s has taken a \"%s\" from their house storage.", ReturnName(playerid), string);

							House_ShowItems(playerid, houseid);
							Log_Write("Logs/storage_log.txt", "[%s] %s has taken \"%s\" from house ID: %d (owner: %s).", ReturnDate(), ReturnName(playerid), string, HouseData[houseid][houseID], (House_IsOwner(playerid, houseid)) ? ("Yes") : ("No"));
				        }
				        else
				        {
				            new str[128];
				            format(str, sizeof(str), "Item: %s (Amount: %d)\n\nPlease enter the amount that you wish to take for this item:", string, HouseStorage[houseid][itemid][hItemQuantity]);
				            ShowPlayerDialog(playerid, DIALOG_HOUSEWITHDRAW, DIALOG_STYLE_INPUT, "House Take", str, "Take", "Back");
				        }
				    }
					case 1:
					{
						new id = Inventory_GetItemID(playerid, string);

						if(id == -1)
						{
							House_ShowItems(playerid, houseid);

							return SendErrorMessage(playerid, "You don't have anymore of this item to store!");
						}
						else if (InventoryData[playerid][id][invQuantity] == 1)
						{
						    if(!strcmp(string, "Cellphone"))
						        return SendErrorMessage(playerid, "You can't do that on this item! (%s)", string);

						    if(!strcmp(string, "Mask"))
						        return SendErrorMessage(playerid, "You can't do that on this item! (%s)", string);
						        
						    if(!strcmp(string, "GPS"))
						        return SendErrorMessage(playerid, "You can't do that on this item! (%s)", string);

						    if(!strcmp(string, "Portable Radio"))
						        return SendErrorMessage(playerid, "You can't do that on this item! (%s)", string);
						        

						    House_AddItem(houseid, string, InventoryData[playerid][id][invModel]);
							Inventory_Remove(playerid, string);

							SendNearbyMessage(playerid, 30.0,X11_PLUM, "** %s has stored a \"%s\" into their house storage.", ReturnName(playerid), string);
							House_ShowItems(playerid, houseid);
						}
						else if (InventoryData[playerid][id][invQuantity] > 1)
						{
						    if(!strcmp(string, "Cellphone"))
						        return SendErrorMessage(playerid, "You can't do that on this item! (%s)", string);

						    if(!strcmp(string, "Mask"))
						        return SendErrorMessage(playerid, "You can't do that on this item! (%s)", string);
						        
						    if(!strcmp(string, "GPS"))
						        return SendErrorMessage(playerid, "You can't do that on this item! (%s)", string);

						    if(!strcmp(string, "Portable Radio"))
						        return SendErrorMessage(playerid, "You can't do that on this item! (%s)", string);
						        
							PlayerData[playerid][pListitem] = id;
							new str[128];
							format(str, sizeof(str), "Item: %s (Amount: %d)\n\nPlease enter the quantity that you wish to store for this item:" , string, InventoryData[playerid][PlayerData[playerid][pListitem]][invQuantity]);
	                        ShowPlayerDialog(playerid, DIALOG_HOUSEDEPOSIT, DIALOG_STYLE_INPUT, "House Deposit", str, "Store", "Back");
						}
					}
				}
			}
		}
		else
		{
		    House_ShowItems(playerid, houseid);
		}
	}
	if(dialogid == DIALOG_FLAT_ITEM)
	{
	    new flatid = Flat_Inside(playerid), string[156];
		if (response)
		{
    		if (FlatStorage[flatid][listitem][fItemExists])
			{
   				PlayerData[playerid][pListitem] = listitem;
   				PlayerData[playerid][pListitem] = listitem;

				strunpack(string, FlatStorage[flatid][PlayerData[playerid][pListitem]][fItemName]);

				format(string, sizeof(string), "%s (Amount: %d)", string, FlatStorage[flatid][listitem][fItemQuantity]);
				ShowPlayerDialog(playerid, DIALOG_FLAT_OPTION, DIALOG_STYLE_LIST, string, "Take Item\nStore Item", "Select", "Back");
			}
			else
			{
			    PlayerData[playerid][pStorageSelect] = 2;
			    
   				OpenInventory(playerid);
			}
		}
		else Flat_OpenStorage(playerid, flatid);
	}
	if(dialogid == DIALOG_HOUSEITEM)
	{
	    new houseid = House_Inside(playerid), string[156];
		if (response)
		{
    		if (HouseStorage[houseid][listitem][hItemExists])
			{
   				PlayerData[playerid][pListitem] = listitem;
   				PlayerData[playerid][pListitem] = listitem;

				strunpack(string, HouseStorage[houseid][PlayerData[playerid][pListitem]][hItemName]);

				format(string, sizeof(string), "%s (Amount: %d)", string, HouseStorage[houseid][listitem][hItemQuantity]);
				ShowPlayerDialog(playerid, DIALOG_HOUSEOPTION, DIALOG_STYLE_LIST, string, "Take Item\nStore Item", "Select", "Back");
			}
			else
			{
			    PlayerData[playerid][pStorageSelect] = 1;
			    
   				OpenInventory(playerid);
			}
		}
		else House_OpenStorage(playerid, houseid);
	}
	if(dialogid == DIALOG_FLAT_STORAGE)
	{
	    if(response)
	    {
			new
			    flatid = -1;

			if ((flatid = Flat_Inside(playerid)) != -1 && (Flat_IsHaveAccess(playerid, flatid)))
			{
			    if (listitem == 0)
				{
			        Flat_ShowItems(playerid, flatid);
			    }
	      		else if (listitem == 1)
				 {
					Flat_WeaponStorage(playerid, flatid);
			    }
			}
		}
	}
	if(dialogid == DIALOG_HOUSESTORAGE)
	{
	    if(response)
	    {
			new
			    houseid = -1;

			if ((houseid = House_Inside(playerid)) != -1 && (House_HaveAccess(playerid, houseid)))
			{
			    if (listitem == 0)
				{
			        House_ShowItems(playerid, houseid);
			    }
	      		else if (listitem == 1)
				 {
					House_WeaponStorage(playerid, houseid);
			    }
			}
		}
	}
	if(dialogid == DIALOG_FLAT_DEPOSIT)
	{
	    new
	        flatid = Flat_Inside(playerid),
	        string[32];

        strunpack(string, InventoryData[playerid][PlayerData[playerid][pListitem]][invItem]);

		if (response)
		{
			new amount = strval(inputtext);

			if (amount < 1 || amount > InventoryData[playerid][PlayerData[playerid][pListitem]][invQuantity])
			{
			    new str[152];
			    format(str, sizeof(str), "Item: %s (Amount: %d)\n\nPlease enter the quantity that you wish to store for this item:", string, InventoryData[playerid][PlayerData[playerid][pListitem]][invQuantity]);
				ShowPlayerDialog(playerid, DIALOG_FLAT_DEPOSIT, DIALOG_STYLE_INPUT, "Flat Deposit", str, "Store", "Back");
				return 1;
			}
			Flat_AddItem(flatid, string, InventoryData[playerid][PlayerData[playerid][pListitem]][invModel], amount);
			Inventory_Remove(playerid, string, amount);

			SendNearbyMessage(playerid, 30.0,X11_PLUM, "** %s has stored a \"%s\" into their flat storage.", ReturnName(playerid), string);
			Flat_ShowItems(playerid, flatid);
		}
		else Flat_OpenStorage(playerid, flatid);
	}
	if(dialogid == DIALOG_FLAT_WITHDRAW)
	{
		new
		    flatid = Flat_Inside(playerid),
		    string[32];

        strunpack(string, FlatStorage[flatid][PlayerData[playerid][pListitem]][fItemName]);
        
	    if(response)
	    {
			new amount = strval(inputtext);

			if (amount < 1 || amount > FlatStorage[flatid][PlayerData[playerid][pListitem]][fItemQuantity])
			{
			    new str[152];
			    format(str, sizeof(str), "Item: %s (Amount: %d)\n\nPlease enter the quantity that you wish to take for this item:", string, FlatStorage[flatid][PlayerData[playerid][pListitem]][fItemQuantity]);
				ShowPlayerDialog(playerid, DIALOG_FLAT_WITHDRAW, DIALOG_STYLE_INPUT, "Flat Take", str, "Take", "Back");
				return 1;
			}
			new id = Inventory_Add(playerid, string, FlatStorage[flatid][PlayerData[playerid][pListitem]][fItemModel], amount);

			if (id == -1)
				return SendErrorMessage(playerid, "You don't have any inventory slots left.");

			if (id == -1)
				return SendErrorMessage(playerid, "You don't have any inventory slots left.");


			Flat_RemoveItem(flatid, string, amount);
			SendNearbyMessage(playerid, 30.0,X11_PLUM, "** %s has taken a \"%s\" from their flat storage.", ReturnName(playerid), string);

			Flat_ShowItems(playerid, flatid);
		}
		else Flat_OpenStorage(playerid, flatid);
	}
	if(dialogid == DIALOG_HOUSEDEPOSIT)
	{
	    new
	        houseid = House_Inside(playerid),
	        string[32];

        strunpack(string, InventoryData[playerid][PlayerData[playerid][pListitem]][invItem]);
        
		if (response)
		{
			new amount = strval(inputtext);

			if (amount < 1 || amount > InventoryData[playerid][PlayerData[playerid][pListitem]][invQuantity])
			{
			    new str[152];
			    format(str, sizeof(str), "Item: %s (Amount: %d)\n\nPlease enter the quantity that you wish to store for this item:", string, InventoryData[playerid][PlayerData[playerid][pListitem]][invQuantity]);
				ShowPlayerDialog(playerid, DIALOG_HOUSEDEPOSIT, DIALOG_STYLE_INPUT, "House Deposit", str, "Store", "Back");
				return 1;
			}
			House_AddItem(houseid, string, InventoryData[playerid][PlayerData[playerid][pListitem]][invModel], amount);
			Inventory_Remove(playerid, string, amount);

			SendNearbyMessage(playerid, 30.0,X11_PLUM, "** %s has stored a \"%s\" into their house storage.", ReturnName(playerid), string);
			House_ShowItems(playerid, houseid);
		}
		else House_OpenStorage(playerid, houseid);
	}
	if(dialogid == DIALOG_HOUSEWITHDRAW)
	{
		new
		    houseid = House_Inside(playerid),
		    string[32];

        strunpack(string, HouseStorage[houseid][PlayerData[playerid][pListitem]][hItemName]);
        
	    if(response)
	    {
			new amount = strval(inputtext);

			if (amount < 1 || amount > HouseStorage[houseid][PlayerData[playerid][pListitem]][hItemQuantity])
			{
			    new str[152];
			    format(str, sizeof(str), "Item: %s (Amount: %d)\n\nPlease enter the quantity that you wish to take for this item:", string, HouseStorage[houseid][PlayerData[playerid][pListitem]][hItemQuantity]);
				ShowPlayerDialog(playerid, DIALOG_HOUSEWITHDRAW, DIALOG_STYLE_INPUT, "House Take", str, "Take", "Back");
				return 1;
			}
			new id = Inventory_Add(playerid, string, HouseStorage[houseid][PlayerData[playerid][pListitem]][hItemModel], amount);

			if (id == -1)
				return SendErrorMessage(playerid, "You don't have any inventory slots left.");

			if (id == -1)
				return SendErrorMessage(playerid, "You don't have any inventory slots left.");

			House_RemoveItem(houseid, string, amount);
			SendNearbyMessage(playerid, 30.0,X11_PLUM, "** %s has taken a \"%s\" from their house storage.", ReturnName(playerid), string);

			House_ShowItems(playerid, houseid);
		//	Log_Write("logs/storage_log.txt", "[%s] %s has taken %d \"%s\" from house ID: %d (owner: %s).", ReturnDate(), ReturnName(playerid), amount, string, HouseData[houseid][houseID], (House_IsOwner(playerid, houseid)) ? ("Yes") : ("No"));
		}
		else House_OpenStorage(playerid, houseid);
	}
	if(dialogid == DIALOG_INTERIOR)
	{
		if (response)
		{
		    SetPlayerInterior(playerid, g_arrInteriorData[listitem][e_InteriorID]);
		    SetPlayerPos(playerid, g_arrInteriorData[listitem][e_InteriorX], g_arrInteriorData[listitem][e_InteriorY], g_arrInteriorData[listitem][e_InteriorZ]);
		}
	}

	if(dialogid == DIALOG_MODSHOP_SELECT) {
		if(response) {
			if(listitem == 0) 
			{
				if(!GetPlayerVIPLevel(playerid))
					return SendErrorMessage(playerid, "Hanya donatur yang dapat mengakses attachment sticker.");

				if(Vehicle_ObjectAdd(playerid, PlayerData[playerid][pVehicle], 18661, OBJECT_TYPE_TEXT)) SendClientMessageEx(playerid, X11_LIGHTBLUE, "(V-Attachment) "WHITE"Attachment "YELLOW"sticker "WHITE"ditambahkan! gunakan "GREEN"/v attachment "WHITE"untuk mengatur.");
				else SendErrorMessage(playerid, "Tidak ada slot attachment untuk kendaraan ini lagi!");
			}
			if(listitem == 1) {

				new models[175] = {-1, ...},
					count =  0;

				for (new i; i < sizeof(BodyWork); i++)
				{
					models[count++] = BodyWork[i][Model];
				}
				ShowCustomSelection(playerid, "Purchase Modification", MODEL_SELECTION_MODSHOP, models, count);
			}
		}
	}
	if(dialogid == DIALOG_MODSHOP)
	{
		if(response)
		{
	        if(!IsPlayerInAnyVehicle(playerid))
	            return SendErrorMessage(playerid, "Kamu harus mengemudikan kendaraan terlebih dahulu.");
	            
			PlayerData[playerid][pListitem] = listitem;
			new vehicleid = PlayerData[playerid][pVehicle];

			if(VehicleObjects[vehicleid][listitem][vehObjectExists]) {
				ShowPlayerDialog(playerid, DIALOG_MODEDIT, DIALOG_STYLE_LIST, "Attachment > Edit", "Adjust Position "YELLOW"(clickable textdraw)\n"WHITE"Adjust Position "YELLOW"(click n drag)\n"WHITE"Change text >> (text only)\nChange font >> (text only)\nChange color >> (text only)\nChange size >> (text only)\n"RED"Delete attachment", "Select", "Close");
			}
			else {
				ShowPlayerDialog(playerid, DIALOG_MODSHOP_SELECT, DIALOG_STYLE_LIST, "Attachment > Add", "Sticker >> "GOLD"(donater only)\n"WHITE"Object [ price: $80,00 ]", "Select", "Close");
			}
		}
	}
	if(dialogid == DIALOG_MODSHOP_SET_TEXT) {

		if(!response)
			return 0;

		if(isnull(inputtext))
			return ShowPlayerDialog(playerid, DIALOG_MODSHOP_SET_TEXT, DIALOG_STYLE_INPUT, "Edit attachment > Text", "Masukkan text untuk modshop text:\n\nNote: Max 24 character!", "Set", "Close");
		
		if(strlen(inputtext) > 24)
			return ShowPlayerDialog(playerid, DIALOG_MODSHOP_SET_TEXT, DIALOG_STYLE_INPUT, "Edit attachment > Text", "Masukkan text untuk modshop text:\n\nNote: Max 24 character!", "Set", "Close");

		format(VehicleObjects[PlayerData[playerid][pVehicle]][PlayerData[playerid][pListitem]][vehObjectText], 32, "%s", inputtext);
		Vehicle_ObjectTextSync(PlayerData[playerid][pVehicle], PlayerData[playerid][pListitem]);
		SendClientMessageEx(playerid, X11_LIGHTBLUE, "(V-Attachment) "WHITE"Text diubah menjadi: \"%s"WHITE"\"", inputtext);
	}	
	if(dialogid == DIALOG_MODSHOP_SET_FONT) {

		if(!response)
			return 0;

		if(isnull(inputtext))
			return ShowPlayerDialog(playerid, DIALOG_MODSHOP_SET_FONT, DIALOG_STYLE_INPUT, "Edit attachment > Font", "Masukkan font face untuk modshop text:\n\nDefault: Arial", "Set", "Close");

		format(VehicleObjects[PlayerData[playerid][pVehicle]][PlayerData[playerid][pListitem]][vehObjectFont], 32, "%s", inputtext);
		Vehicle_ObjectTextSync(PlayerData[playerid][pVehicle], PlayerData[playerid][pListitem]);
		SendClientMessageEx(playerid, X11_LIGHTBLUE, "(V-Attachment) "WHITE"Font diubah menjadi: \"%s\"", inputtext);
	}
	if(dialogid == DIALOG_MODSHOP_SET_COLOR) {
		if(response) {

			if(!(0 <= strval(inputtext) <= sizeof(ColorList)-1))
				return ShowPlayerDialog(playerid, DIALOG_MODSHOP_SET_COLOR, DIALOG_STYLE_INPUT, "Edit attachment > Color", color_string, "Update", "Close");
			
			VehicleObjects[PlayerData[playerid][pVehicle]][PlayerData[playerid][pListitem]][vehObjectFontColor] = strval(inputtext);
			Vehicle_ObjectTextSync(PlayerData[playerid][pVehicle], PlayerData[playerid][pListitem]);
			SendClientMessageEx(playerid, X11_LIGHTBLUE, "(V-Attachment) "WHITE"Warna diubah menjadi: \"%d\"", strval(inputtext));

		}
	}
	if(dialogid == DIALOG_MODSHOP_SET_SIZE) {
		if(response) {

			if(!(0 < strval(inputtext) <= 200))
				return ShowPlayerDialog(playerid, DIALOG_MODSHOP_SET_SIZE, DIALOG_STYLE_INPUT, "Edit attachment > Size", "Masukkan ukuran text untuk modshop text:\n\nNote: min 24 max 200", "Set", "Close");

			VehicleObjects[PlayerData[playerid][pVehicle]][PlayerData[playerid][pListitem]][vehObjectFontSize] = strval(inputtext);
			Vehicle_ObjectTextSync(PlayerData[playerid][pVehicle], PlayerData[playerid][pListitem]);
			SendClientMessageEx(playerid, X11_LIGHTBLUE, "(V-Attachment) "WHITE"Size diubah  menjadi: \"%d\"", strval(inputtext));
		}
	}
	if(dialogid == DIALOG_MODEDIT)
	{
	    if(response)
	    {
	        if(!IsPlayerInAnyVehicle(playerid))
	            return SendErrorMessage(playerid, "You're no longer inside a Valid Player Vehicle.");
	            
			new
				vehicleid = PlayerData[playerid][pVehicle],
				slot = PlayerData[playerid][pListitem];

			switch(listitem)
			{
			    case 0:
			    {
			        ShowEditTextDraw(playerid);
				}
				case 1:
				{
					if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_BODY) {
						Vehicle_ObjectEdit(playerid, vehicleid, slot, false);
					}
					else {
						Vehicle_ObjectEdit(playerid, vehicleid, slot, true);
					}

				}
				case 2:
				{
					if(VehicleObjects[PlayerData[playerid][pVehicle]][PlayerData[playerid][pListitem]][vehObjectType] != OBJECT_TYPE_TEXT)
						return SendErrorMessage(playerid, "Tipe attachment harus sticker!");

					ShowPlayerDialog(playerid, DIALOG_MODSHOP_SET_TEXT, DIALOG_STYLE_INPUT, "Edit attachment > Text", "Masukkan text untuk modshop text:\n\nNote: Max 24 character!", "Set", "Close");
				}
				case 3: {

					if(VehicleObjects[PlayerData[playerid][pVehicle]][PlayerData[playerid][pListitem]][vehObjectType]!= OBJECT_TYPE_TEXT)
						return SendErrorMessage(playerid, "Tipe attachment harus sticker!");

					ShowPlayerDialog(playerid, DIALOG_MODSHOP_SET_FONT, DIALOG_STYLE_INPUT, "Edit attachment > Font", "Masukkan font face untuk modshop text:\n\nDefault: Arial", "Set", "Close");
				}
				case 4: {

					if(VehicleObjects[PlayerData[playerid][pVehicle]][PlayerData[playerid][pListitem]][vehObjectType] != OBJECT_TYPE_TEXT)
						return SendErrorMessage(playerid, "Tipe attachment harus sticker!");

					ShowPlayerDialog(playerid, DIALOG_MODSHOP_SET_COLOR, DIALOG_STYLE_INPUT, "Edit attachment > Color", color_string, "Update", "Close");
				}
				case 5: {

					if(VehicleObjects[PlayerData[playerid][pVehicle]][PlayerData[playerid][pListitem]][vehObjectType] != OBJECT_TYPE_TEXT)
						return SendErrorMessage(playerid, "Tipe attachment harus sticker!");

					ShowPlayerDialog(playerid, DIALOG_MODSHOP_SET_SIZE, DIALOG_STYLE_INPUT, "Edit attachment > Size", "Masukkan ukuran text untuk modshop text:\n\nNote: min 24 max 200", "Set", "Close");
				}
				case 6:
				{
				    new veh = PlayerData[playerid][pVehicle];

					if(!IsValidVehicle(veh))
						return SendErrorMessage(playerid, "Kendaraan tidak lagi valid.");

					Vehicle_ObjectDelete(veh, PlayerData[playerid][pListitem]);
					SendClientMessageEx(playerid, X11_LIGHTBLUE, "(V-Attachment) "WHITE"Attachment pada slot %d berhasil dihapus.", PlayerData[playerid][pListitem]);
				}
			}
		}
	}
	if(dialogid == DIALOG_GATE_PASS)
	{
		if (response)
		{
		    new id = Gate_Nearest(playerid);

		    if (id == -1)
		        return 0;

	        if (isnull(inputtext))
	        	return ShowPlayerDialog(playerid, DIALOG_GATE_PASS, DIALOG_STYLE_INPUT, "Enter Password", "Please enter the password for this gate below:", "Submit", "Cancel");

			if (strcmp(inputtext, GateData[id][gatePass]) != 0)
	  			return ShowPlayerDialog(playerid, DIALOG_GATE_PASS, DIALOG_STYLE_INPUT, "Enter Password", "Error: Incorrect password specified.\n\nPlease enter the password for this gate below:", "Submit", "Cancel");

			Gate_Operate(id, playerid);
		}
	}
	if(dialogid == DIALOG_STREAMER_CONFIG)
	{
		if(response)
		{
			new config[] = {1000, 700, 500, 300};
			new const confignames[][24] = {"High", "Medium", "Low", "Potato"};

			Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, config[listitem], playerid);
			SendServerMessage(playerid, "You have adjusted maximum streamed object configuration to {FFFF00}%s", confignames[listitem]);
			Streamer_Update(playerid, STREAMER_TYPE_OBJECT);

		}
	}
	if(dialogid == DIALOG_FURNITURE_BUY)
	{
		if(response)
		{
		    new
				items[80] = {-1, ...},
				count;

		    for (new i = 0; i < sizeof(g_aFurnitureData); i ++) if (g_aFurnitureData[i][e_FurnitureType] == listitem + 1) {
				items[count++] = g_aFurnitureData[i][e_FurnitureModel];
		    }
		    PlayerData[playerid][pListitem] = listitem;

			ShowCustomSelection(playerid, "Purchase Furniture", MODEL_SELECTION_FURNITURE, items, count);
			/*if (listitem == 3) {
				
				ShowModelSelectionMenu(playerid, "Furniture", MODEL_SELECTION_FURNITURE, items, count, -12.0, 0.0, 0.0);
			}
			else {
			    ShowModelSelectionMenu(playerid, "Furniture", MODEL_SELECTION_FURNITURE, items, count);
			}*/
		}
	}
	if(dialogid == DIALOG_FURNITURE_LIST)
	{
		if(response)
		{
			PlayerData[playerid][pEditing] = ListedFurniture[playerid][listitem];

			ShowFurnitureEditMenu(playerid);
		}
	}
	if(dialogid == DIALOG_FLAT_FURNITURE)
	{
		if(response)
		{
			if(listitem == 0)
			{
			    new count = 0, string[4512], flatid = Flat_Inside(playerid), real_count;
				foreach(new i : Furniture) if (FurnitureData[i][furnitureProperty] == FlatData[flatid][flatID] && FurnitureData[i][furniturePropertyType] == FURNITURE_TYPE_FLAT)
				{
					if(real_count >= Flat_LimitFurniture(flatid))
						break;
						
					ListedFurniture[playerid][count++] = i;
					format(string, sizeof(string), "%s%s (%.2f meters)\n", string, FurnitureData[i][furnitureName], GetPlayerDistanceFromPoint(playerid, FurnitureData[i][furniturePos][0], FurnitureData[i][furniturePos][1], FurnitureData[i][furniturePos][2]));
				
					real_count++;
				}
				if (count)
				{
					ShowPlayerDialog(playerid, DIALOG_FURNITURE_LIST, DIALOG_STYLE_LIST, sprintf("Furniture List (%d/%d)", Flat_FurnitureCount(flatid), Flat_LimitFurniture(flatid)), string, "Select", "Cancel");
			 	}
			 	else SendErrorMessage(playerid, "There is no furniture on this flat!"), cmd_flat(playerid, "menu");
			}
			if(listitem == 1)
			{
				if(Flat_FurnitureCount(Flat_Inside(playerid)) >= Flat_LimitFurniture(Flat_Inside(playerid)))
					return SendErrorMessage(playerid, "You only can place %d furniture per flat!", Flat_LimitFurniture(Flat_Inside(playerid))), cmd_flat(playerid, "menu");

				new str[312];

		        str[0] = 0;

		        for (new i = 0; i < sizeof(g_aFurnitureTypes); i ++) {
		            format(str, sizeof(str), "%s%s - $%s\n", str, g_aFurnitureTypes[i], FormatNumber(Furniture_ReturnPrice(i)));
				}
				ShowPlayerDialog(playerid, DIALOG_FURNITURE_BUY, DIALOG_STYLE_LIST, "Purchase Furniture", str, "Select", "Close");
			}
			if(listitem == 2)
			{
				if(Flat_FurnitureCount(Flat_Inside(playerid)) < 1)
					return SendErrorMessage(playerid, "There is no furniture on your flat!"), cmd_flat(playerid, "menu");


				new string[156];
				foreach(new i : Furniture) if(FurnitureData[i][furnitureProperty] == FlatData[Flat_Inside(playerid)][flatID] && FurnitureData[i][furniturePropertyType] == FURNITURE_TYPE_FLAT)
				{
					mysql_format(sqlcon, string, sizeof(string), "DELETE FROM `furniture` WHERE `furnitureID` = '%d'", FurnitureData[i][furnitureID]);
					mysql_tquery(sqlcon, string);

					FurnitureData[i][furnitureExists] = false;
					FurnitureData[i][furnitureModel] = 0;
					FurnitureData[i][furniturePropertyType] = -1;
					FurnitureData[i][furnitureProperty] = -1;
					
					if(IsValidDynamicObject(FurnitureData[i][furnitureObject]))
						DestroyDynamicObject(FurnitureData[i][furnitureObject]);

					new next = i;
					Iter_SafeRemove(Furniture, next, i);
				}
				SendServerMessage(playerid, "You have removed all furniture on this flat!");
				cmd_flat(playerid, "menu");
			}
			if(listitem == 3) {

				new flat_id = Flat_Inside(playerid);

				if(!Flat_IsOwner(playerid, flat_id))
					return SendErrorMessage(playerid, "Hanya owner yang dapat mengakses opsi ini.");

				if(FlatData[flat_id][flatFurnitureLevel] >= 10) {
					return SendErrorMessage(playerid, "Furniture slot sudah tidak bisa di-upgrade lagi.");
				}

				new price = FlatData[flat_id][flatFurnitureLevel] * 15000;

				if(GetMoney(playerid) < price)
					return SendErrorMessage(playerid, "Kamu membutuhkan $%s untuk upgrade.", FormatNumber(price));

				GiveMoney(playerid, -price);
				FlatData[flat_id][flatFurnitureLevel] ++;

				SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Furniture) "WHITE"Slot furniture berhasil di-upgrade ke level "YELLOW"%d "WHITE"dengan harga "GREEN"$%s", FlatData[flat_id][flatFurnitureLevel], FormatNumber(price));
				Flat_Save(flat_id);
			}
		}
	}
	if(dialogid == DIALOG_FURNITURE)
	{
		if(response)
		{
			if(listitem == 0)
			{
			    new count = 0, string[4512], houseid = House_Inside(playerid), real_count = 0;
				foreach(new i : Furniture) if (FurnitureData[i][furnitureProperty] == HouseData[houseid][houseID] && FurnitureData[i][furniturePropertyType] == FURNITURE_TYPE_HOUSE)
				{

					if(real_count >= House_LimitFurniture(houseid))
						break;

					ListedFurniture[playerid][count++] = i;
					format(string, sizeof(string), "%s%s (%.2f meters)\n", string, FurnitureData[i][furnitureName], GetPlayerDistanceFromPoint(playerid, FurnitureData[i][furniturePos][0], FurnitureData[i][furniturePos][1], FurnitureData[i][furniturePos][2]));
				
					real_count++;
				}
				if (count)
				{
					ShowPlayerDialog(playerid, DIALOG_FURNITURE_LIST, DIALOG_STYLE_LIST, sprintf("Furniture List (%d/%d)", House_FurnitureCount(houseid), House_LimitFurniture(houseid)), string, "Select", "Cancel");
			 	}
			 	else SendErrorMessage(playerid, "There is no furniture on this house!"), cmd_house(playerid, "menu");
			}
			if(listitem == 1)
			{
				if(House_FurnitureCount(House_Inside(playerid)) >= House_LimitFurniture(House_Inside(playerid)))
					return SendErrorMessage(playerid, "You only can place %d furniture per house!", House_LimitFurniture(House_Inside(playerid))), cmd_house(playerid, "menu");

				new str[312];

		        str[0] = 0;

		        for (new i = 0; i < sizeof(g_aFurnitureTypes); i ++) {
		            format(str, sizeof(str), "%s%s - $%s\n", str, g_aFurnitureTypes[i], FormatNumber(Furniture_ReturnPrice(i)));
				}
				ShowPlayerDialog(playerid, DIALOG_FURNITURE_BUY, DIALOG_STYLE_LIST, "Purchase Furniture", str, "Select", "Close");
			}
			if(listitem == 2)
			{
				if(House_FurnitureCount(House_Inside(playerid)) < 1)
					return SendErrorMessage(playerid, "There is no furniture on your house!"), cmd_house(playerid, "menu");

				new string[156];
				foreach(new i : Furniture) if(FurnitureData[i][furnitureProperty] == HouseData[House_Inside(playerid)][houseID] && FurnitureData[i][furniturePropertyType] == FURNITURE_TYPE_HOUSE)
				{
					mysql_format(sqlcon, string, sizeof(string), "DELETE FROM `furniture` WHERE `furnitureID` = '%d'", FurnitureData[i][furnitureID]);
					mysql_tquery(sqlcon, string);

					FurnitureData[i][furnitureExists] = false;
					FurnitureData[i][furnitureModel] = 0;
					FurnitureData[i][furniturePropertyType] = -1;
					FurnitureData[i][furnitureProperty] = -1;

					if(IsValidDynamicObject(FurnitureData[i][furnitureObject]))
						DestroyDynamicObject(FurnitureData[i][furnitureObject]);

					new next = i;
					Iter_SafeRemove(Furniture, next, i);
				}
				SendServerMessage(playerid, "You have removed all furniture on this house!");
				ShowHouseMenu(playerid);
			}
			if(listitem == 3) {
				new id = House_Inside(playerid);

				if(!House_IsOwner(playerid, id))
					return SendErrorMessage(playerid, "Hanya owner yang dapat mengakses opsi ini.");

				if(HouseData[id][houseFurnitureLevel] >= 10) {
					return SendErrorMessage(playerid, "Furniture slot sudah tidak bisa di-upgrade lagi.");
				}

				new price = HouseData[id][houseFurnitureLevel] * 20000;

				if(GetMoney(playerid) < price)
					return SendErrorMessage(playerid, "Kamu membutuhkan $%s untuk upgrade.", FormatNumber(price));

				GiveMoney(playerid, -price);
				HouseData[id][houseFurnitureLevel] ++;

				SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Furniture) "WHITE"Slot furniture berhasil di-upgrade ke level "YELLOW"%d "WHITE"dengan harga "GREEN"$%s", HouseData[id][houseFurnitureLevel], FormatNumber(price));
				House_Save(id);
			}
		}
	}
	if(dialogid == DIALOG_HOUSE_MENU)
	{
		if(response)
		{
			if(listitem == 0)
			{
				ShowPlayerDialog(playerid, DIALOG_FURNITURE, DIALOG_STYLE_LIST, "House Furniture", "Listed Furniture\nAdd Furniture\n"RED"Reset all furniture\n"YELLOW"Upgrade furniture slot ", "Select", "Close");
			}
			if(listitem == 1)
			{
				if(!House_IsOwner(playerid, House_Inside(playerid)))
					return SendErrorMessage(playerid, "Only owner can access this option.");

				House_OpenStorage(playerid, House_Inside(playerid));
			}
			if(listitem == 2) {

				if(!House_IsOwner(playerid, House_Inside(playerid)))
					return SendErrorMessage(playerid, "Only owner can access this option.");

				House_ShowKeyMenu(playerid, House_Inside(playerid));
			}
			if(listitem == 3) {
				new string[256], price = 0,
					id = House_Inside(playerid);

				price = HouseData[id][housePrice] * 5/100;
				strcat(string, sprintf("Harga Pajak: $%s\n", FormatNumber(price)));
				strcat(string, sprintf("Status: %s\n", (HouseData[id][houseTaxState] == TAX_STATE_COOLDOWN) ? ("belum bisa dibayar") : ("sudah bisa dibayar")));
				strcat(string, sprintf("%s: %s\n", (HouseData[id][houseTaxState] == TAX_STATE_COOLDOWN) ? ("Bayar dalam") : ("Jatuh tempo"), ConvertTimestamp(Timestamp:HouseData[id][houseTaxDate])));
				ShowPlayerDialog(playerid, DIALOG_NONE, DIALOG_STYLE_MSGBOX, "Tax Detail", string, "Close", "");
			}
		}
	}
	if(dialogid == DIALOG_TEST_STAGE_7)
	{
		if(response)
		{
			if(listitem == 1)
			{
				PlayerData[playerid][pIndexTest]++;
			}
			CheckPlayerTest(playerid);
		}
		else
		{
			PlayerData[playerid][pOnTest] = false;
			PlayerData[playerid][pIndexTest] = 0;
			SendServerMessage(playerid, "Kamu gagal mengambil Driving Test karena membatalkan test teori!");					
		}
	}
	if(dialogid == DIALOG_TEST_STAGE_6)
	{
		if(response)
		{
			if(listitem == 2)
			{
				PlayerData[playerid][pIndexTest]++;
			}
			ShowPlayerDialog(playerid, DIALOG_TEST_STAGE_7, DIALOG_STYLE_TABLIST_HEADERS, "Question 7 of 7",
			"Apa yang harus dilakukan jika ingin mengubah arah kendaraan ?\
			\nA. Berhenti ditengah jalan\
			\nB. Memberikan isyarat dengan lampu sein\
			\nC. Langsung berbelok tanpa isyarat",
			"Next", "Close");
		}
		else
		{
			PlayerData[playerid][pOnTest] = false;
			PlayerData[playerid][pIndexTest] = 0;
			SendServerMessage(playerid, "Kamu gagal mengambil Driving Test karena membatalkan test teori!");					
		}
	}
	if(dialogid == DIALOG_TEST_STAGE_5)
	{
		if(response)
		{
			if(listitem == 0)
			{
				PlayerData[playerid][pIndexTest]++;
			}
			ShowPlayerDialog(playerid, DIALOG_TEST_STAGE_6, DIALOG_STYLE_TABLIST_HEADERS, "Question 6 of 7",
			"Pengemudi harus memberi isyarat dengan petunjuk arah yang berkedip pada saat ?\
			\nA. Akan berjalan atau mengubah arah ke kanan\
			\nB. Pada saat akan berhenti\
			\nC. Akan berubah arah ke kiri ataupun kanan",
			"Next", "Close");
		}
		else
		{
			PlayerData[playerid][pOnTest] = false;
			PlayerData[playerid][pIndexTest] = 0;
			SendServerMessage(playerid, "Kamu gagal mengambil Driving Test karena membatalkan test teori!");				
		}
	}
	if(dialogid == DIALOG_TEST_STAGE_4)
	{
		if(response)
		{
			if(listitem == 1)
			{
				PlayerData[playerid][pIndexTest]++;
			}
			ShowPlayerDialog(playerid, DIALOG_TEST_STAGE_5, DIALOG_STYLE_TABLIST_HEADERS, "Question 5 of 7",
			"Dilarang melewati kendaraan lain walau tidak ada rambu yang melarangnya pada ?\
			\nA. Jalan tikungan\
			\nB. Jalan turunan\
			\nC. Jalan berlubang",
			"Next", "Close");
		}
		else
		{
			PlayerData[playerid][pOnTest] = false;
			PlayerData[playerid][pIndexTest] = 0;
			SendServerMessage(playerid, "Kamu gagal mengambil Driving Test karena membatalkan test teori!");			
		}

	}
	if(dialogid == DIALOG_TEST_STAGE_3)
	{
		if(response)
		{
			if(listitem == 1)
			{
				PlayerData[playerid][pIndexTest]++;
			}
			ShowPlayerDialog(playerid, DIALOG_TEST_STAGE_4, DIALOG_STYLE_TABLIST_HEADERS, "Question 4 of 7",
			"Apa yang anda lakukan jika mendengar sirine darurat dari arah belakang ?\
			\nA. Pelan-pelan dan terus maju\
			\nB. Menepi ke bahu jalan lalu berhenti\
			\nC. Mempertahankan kecepatan",
			"Next", "Close");
		}
		else
		{
			PlayerData[playerid][pOnTest] = false;
			PlayerData[playerid][pIndexTest] = 0;
			SendServerMessage(playerid, "Kamu gagal mengambil Driving Test karena membatalkan test teori!");			
		}
	}
	if(dialogid == DIALOG_TEST_STAGE_2)
	{
		if(response)
		{
			if(listitem == 1)
			{
				PlayerData[playerid][pIndexTest]++;
			}
			ShowPlayerDialog(playerid, DIALOG_TEST_STAGE_3, DIALOG_STYLE_TABLIST_HEADERS, "Question 3 of 7",
			"Dimanakah posisi parkir yang baik dan benar ?\
			\nA. Atas trotoar\
			\nB. Setengah trotoar dan setengah bahu jalan\
			\nC. Atas bahu jalan",
			"Next", "Close");
		}
		else
		{
			PlayerData[playerid][pOnTest] = false;
			PlayerData[playerid][pIndexTest] = 0;
			SendServerMessage(playerid, "Kamu gagal mengambil Driving Test karena membatalkan test teori!");			
		}
	}
	if(dialogid == DIALOG_TEST_STAGE_1)
	{
		if(response)
		{
			if(listitem == 2)
			{
				PlayerData[playerid][pIndexTest]++;
			}
			ShowPlayerDialog(playerid, DIALOG_TEST_STAGE_2, DIALOG_STYLE_TABLIST_HEADERS, "Question 2 of 7",
			"Berapakah jarak minimum parkir jika kamu parkir didekat Hydrant ?\
			\nA. 10 Meter\
			\nB. 15 Meter\
			\nC. 25 Meter",
			"Next", "Close");
		}
		else
		{
			PlayerData[playerid][pOnTest] = false;
			PlayerData[playerid][pIndexTest] = 0;
			SendServerMessage(playerid, "Kamu gagal mengambil Driving Test karena membatalkan test teori!");
		}
	}
	if(dialogid == DIALOG_TEST_MAIN)
	{
		if(response)
		{
			GiveMoney(playerid, -2500);
			ShowPlayerDialog(playerid, DIALOG_TEST_STAGE_1, DIALOG_STYLE_TABLIST_HEADERS, "Question 1 of 7",
			"Mengapa kita saat mengemudi harus memperlambat kendaraan saat tikungan ?\
			\nA. Untuk menghemat ke-ausan pada Ban\
			\nB. Untuk dapat melihat pemandangan\
			\nC. Untuk dapat berhenti jika ada seseorang dijalan",
			 "Next", "Close");
		}
		else
		{
			SendServerMessage(playerid, "Kamu batal mengambil Driving Test.");
		}
	}
	if(dialogid == DIALOG_CODE)
	{
		if(response)
		{
			if(isnull(inputtext)) {
				SendServerMessage(playerid, "Kamu memasukkan kode Verifikasi yang salah!");
				return ShowVerifyMenu(playerid);
			}
			if(!IsNumeric(inputtext)) {
				SendServerMessage(playerid, "Kamu memasukkan kode Verifikasi yang salah!");
				return ShowVerifyMenu(playerid);
			}
			if(tempCode[playerid] != strval(inputtext)) {
				SendServerMessage(playerid, "Kamu memasukkan kode Verifikasi yang salah!");
				return ShowVerifyMenu(playerid);
			}


	    	new query[128];
	    	mysql_format(sqlcon, query, sizeof(query), "UPDATE `playerucp` SET `Active` = 1, `Registered` = '%d' WHERE `UCP` = '%s'", gettime(), GetName(playerid));
	    	mysql_tquery(sqlcon, query);

	    	CheckAccount(playerid);

	    	SendServerMessage(playerid, "Account verified successfully.");

		}
		else
		{
			Kick(playerid);
		}
	}
	if(dialogid == DIALOG_GPS_GARAGE)
	{
		if(response)
		{
			SetWaypoint(playerid, GarageData[listitem][garageX], GarageData[listitem][garageY], GarageData[listitem][garageZ], 3.0);
			SendClientMessageEx(playerid, X11_LIGHTBLUE, "(GPS) {FFFFFF}Garage at "RED"%s {FFFFFF}located at your radar.", GetLocation(GarageData[listitem][garageX], GarageData[listitem][garageY], GarageData[listitem][garageZ]));
		}
	}
	if(dialogid == DIALOG_GPS_WORKSHOP)
	{
		if(response)
		{
			SetWaypoint(playerid, WorkshopData[listitem][wsFootPos][0],WorkshopData[listitem][wsFootPos][1], WorkshopData[listitem][wsFootPos][2] , 3.0);
			SendClientMessageEx(playerid, X11_LIGHTBLUE, "(GPS) {FFFFFF}Workshop at "RED"%s {FFFFFF}located at your radar.", GetLocation(WorkshopData[listitem][wsFootPos][0],WorkshopData[listitem][wsFootPos][1], WorkshopData[listitem][wsFootPos][2]));
		}
	}
	if(dialogid == DIALOG_GPS_TREE)
	{
		if(response)
		{
			SetWaypoint(playerid, TreeData[listitem][treePos][0], TreeData[listitem][treePos][1], TreeData[listitem][treePos][2], 3.0);
			SendClientMessageEx(playerid, X11_LIGHTBLUE, "(GPS) {FFFFFF}Tree at "RED"%s {FFFFFF}located at your radar.", GetLocation(TreeData[listitem][treePos][0], TreeData[listitem][treePos][1], TreeData[listitem][treePos][2]));
		}
	}
	if(dialogid == DIALOG_EDITBONE)
	{
		if(response)
		{
			new weaponid = EditingWeapon[playerid], weaponname[18], string[150];

			GetWeaponName(weaponid, weaponname, sizeof(weaponname));

			WeaponSettings[playerid][weaponid - 22][Bone] = listitem + 1;

			SendServerMessage(playerid, "You have successfully changed bone for %s attachment.", weaponname);

			mysql_format(sqlcon, string, sizeof(string), "INSERT INTO weaponsettings (Owner, WeaponID, Bone) VALUES ('%d', %d, %d) ON DUPLICATE KEY UPDATE Bone = VALUES(Bone)", PlayerData[playerid][pID], weaponid, listitem + 1);
			mysql_tquery(sqlcon, string);
		}
		EditingWeapon[playerid] = 0;
	}
	if(dialogid == DIALOG_HIDEGUN)
	{
		new weaponid = GetWeapon(playerid), index = weaponid - 22;
		if(response)
		{
			if(!weaponid)
				return SendErrorMessage(playerid, "You are not holding any weapon.");

			if (EditingWeapon[playerid] != 0)
				return SendErrorMessage(playerid, "You are already editing a weapon attachment");

			if (!IsWeaponWearable(weaponid))
				return SendErrorMessage(playerid, "You can't edit this weapon attachment!");

			if(listitem == 0)
			{
				if (WeaponSettings[playerid][weaponid - 22][Hidden])
					return SendErrorMessage(playerid, "This weapon is still Hidden! you must unhide this weapon.");

				EditingWeapon[playerid] = weaponid;
				SetPlayerArmedWeapon(playerid, 0);
			   
				SetPlayerAttachedObject(playerid, GetWeaponObjectSlot(weaponid), GetWeaponModel(weaponid), WeaponSettings[playerid][index][Bone], WeaponSettings[playerid][index][Position][0], WeaponSettings[playerid][index][Position][1], WeaponSettings[playerid][index][Position][2], WeaponSettings[playerid][index][Position][3], WeaponSettings[playerid][index][Position][4], WeaponSettings[playerid][index][Position][5], 1.0, 1.0, 1.0);
				EditAttachedObject(playerid, GetWeaponObjectSlot(weaponid));
			}
			if(listitem == 1)
			{
				ShowPlayerDialog(playerid, DIALOG_EDITBONE, DIALOG_STYLE_LIST, "Bone", "Spine\nHead\nLeft upper arm\nRight upper arm\nLeft hand\nRight hand\nLeft thigh\nRight thigh\nLeft foot\nRight foot\nRight calf\nLeft calf\nLeft forearm\nRight forearm\nLeft shoulder\nRight shoulder\nNeck\nJaw", "Choose", "Cancel");
				EditingWeapon[playerid] = weaponid;				
			}
			if(listitem == 2)
			{
				if (!IsWeaponHideable(weaponid))
					return SendErrorMessage(playerid, "You can't hide this weapon!");

				new weaponname[18], string[150];

				GetWeaponName(weaponid, weaponname, sizeof(weaponname));
			   
				if (WeaponSettings[playerid][index][Hidden])
				{
					format(string, sizeof(string), "{FFFF00}(Info) {FFFFFF}You have {00FF00}unhide {FFFFFF}attachment for weapon {FFFF00}%s", weaponname);
					WeaponSettings[playerid][index][Hidden] = false;
				}
				else
				{
					if (IsPlayerAttachedObjectSlotUsed(playerid, GetWeaponObjectSlot(weaponid)))
						RemovePlayerAttachedObject(playerid, GetWeaponObjectSlot(weaponid));

					format(string, sizeof(string), "{FFFF00}(Info) {FFFFFF}You have {FF0000}hide {FFFFFF}attachment for weapon {FFFF00}%s", weaponname);
					WeaponSettings[playerid][index][Hidden] = true;
				}
				SendClientMessage(playerid, -1, string);
			   
				mysql_format(sqlcon, string, sizeof(string), "INSERT INTO weaponsettings (Owner, WeaponID, Hidden) VALUES ('%d', %d, %d) ON DUPLICATE KEY UPDATE Hidden = VALUES(Hidden)", PlayerData[playerid][pID], weaponid, WeaponSettings[playerid][index][Hidden]);
				mysql_tquery(sqlcon, string);
			}
		}
	}
	if(dialogid == DIALOG_HOUSE_PARK_TAKE) 
	{
		if(!response) 
			return 0;

		if(IsPlayerInAnyVehicle(playerid))
			return SendErrorMessage(playerid, "Turun dari kendaraan terlebih dahulu.");

		new hid = HousePark_Nearest(playerid), id = g_Selected_Vehicle_ID[playerid][listitem];

		mysql_tquery(sqlcon, sprintf("UPDATE `vehicle` SET `vehHouse` = %d, `vehState` = %d WHERE `vehID` = %d", hid, VEHICLE_STATE_SPAWNED, id));
		mysql_tquery(sqlcon, sprintf("SELECT * FROM `vehicle` WHERE `vehID` = %d", id), "OnVehicleLoaded", "");

		SendServerMessage(playerid, "Berhasil mengeluarkan kendaraanmu dari garasi rumah.");

		HouseData[hid][houseVehInside]--;
		House_Save(hid);
	}
	if(dialogid == DIALOG_HOUSE_PARK)
	{
		if(response)
		{
			if(listitem == 0)
			{
				new str[256], gstr[352], count = 0;
				mysql_format(sqlcon, str, sizeof(str), "SELECT * FROM `vehicle` WHERE `vehState` = %d AND `vehHouse` = %d AND `vehExtraID` = %d", VEHICLE_STATE_HOUSEPARK, HouseData[HousePark_Nearest(playerid)][houseID], PlayerData[playerid][pID]);
				new Cache:execute = mysql_query(sqlcon, str, true);

				if(!cache_num_rows())
					return SendErrorMessage(playerid, "Tidak ada kendaraanmu pada garasi ini."), cache_delete(execute);

				for(new i = 0; i < cache_num_rows(); i++) {
					new modelid, plate[16], vehid;
					cache_get_value_name_int(i, "vehModel", modelid);
					cache_get_value_name(i, "vehPlate", plate, sizeof(plate));
					cache_get_value_name_int(i, "vehID", vehid);

					strcat(gstr, sprintf("%d) %s, Plate: %s\n", i + 1, ReturnVehicleModelName(modelid), plate));
					g_Selected_Vehicle_ID[playerid][count++] = vehid;
				}
				ShowPlayerDialog(playerid, DIALOG_HOUSE_PARK_TAKE, DIALOG_STYLE_LIST, "Parked Vehicle", gstr, "Take", "Close");
				cache_delete(execute);
			}
			if(listitem == 1)
			{
				new id = GetPlayerVehicleID(playerid), hid = HousePark_Nearest(playerid);

				if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
					return SendErrorMessage(playerid, "You must driving a vehicle.");

				if(!Vehicle_IsOwner(playerid, id))
					return SendErrorMessage(playerid, "You only can park your own vehicle!");

				if(Vehicle_GetType(id) != VEHICLE_TYPE_PLAYER)
					return SendErrorMessage(playerid, "You can't park rented vehicle!");

				if(House_CountVehicle(hid) >= HouseData[hid][housePark])
					return SendErrorMessage(playerid, "This house already have full slot of parked vehicle!");

				HouseData[hid][houseVehInside]++;
				House_Save(hid);

				VehicleData[id][vHouse] = HouseData[hid][houseID];
				Vehicle_SetState(id, VEHICLE_STATE_HOUSEPARK);
				
				Vehicle_Save(id);

				mysql_tquery(sqlcon, sprintf("UPDATE `vehicle` SET `vehHouse` = '%d' WHERE `vehID` = '%d'", HouseData[hid][houseID], VehicleData[id][vID]));
				Vehicle_Delete(id, false);
				SendServerMessage(playerid, "You have successfully parked your {FFFF00}%s", ReturnVehicleModelName(VehicleData[id][vModel]));
			}
		}
	}
	if(dialogid == DIALOG_BM_MATERIAL)
	{
		if(response)
		{
			if(listitem == 0)
			{
				if(GetMoney(playerid) < 20000)
					return SendErrorMessage(playerid, "You don't have enough money!");

				if(Inventory_Add(playerid, "9mm Silenced Material", 3052, 1) == -1)	
					return 1;

				GiveMoney(playerid, -20000, "Membeli 9mm material");
				SendServerMessage(playerid, "Kamu berhasil membeli {FF0000}9mm Silenced Material");
			}
			if(listitem == 1)
			{
				if(GetMoney(playerid) < 45000)
					return SendErrorMessage(playerid, "You don't have enough money!");

				if(Inventory_Add(playerid, "Shotgun Material", 3052, 1) == -1)
					return 1;

				GiveMoney(playerid, -45000, "Membeli Shotgun material");
				SendServerMessage(playerid, "Kamu berhasil membeli {FF0000}Shotgun Material");				
			}
			if(listitem == 2) {

				if(GetMoney(playerid) < 35000)
					return SendErrorMessage(playerid, "You don't have enough money!");

				if(Inventory_Add(playerid, "Desert Eagle Material", 3052, 1) == -1)
					return 1;

				GiveMoney(playerid, -35000, "Membeli DE Material");
				SendServerMessage(playerid, "Kamu berhasil membeli {FF0000}Desert Eagle Material");		

			}
			if(listitem == 3) {

				if(GetMoney(playerid) < 90000)
					return SendErrorMessage(playerid, "You don't have enough money!");

				if(Inventory_Add(playerid, "Rifle Material", 3052, 1) == -1)
					return 1;

				GiveMoney(playerid, -90000, "Membeli Rifle Material");
				SendServerMessage(playerid, "Kamu berhasil membeli {FF0000}Rifle Material");		

			}
			if(listitem == 4) {

				if(GetMoney(playerid) < 250000)
					return SendErrorMessage(playerid, "You don't have enough money!");

				if(Inventory_Add(playerid, "AK-47 Material", 3052, 1) == -1)
					return 1;

				GiveMoney(playerid, -250000, "Membeli AK Material");
				SendServerMessage(playerid, "Kamu berhasil membeli {FF0000}AK-47 Material");		
			}
		}
	}
	if(dialogid == DIALOG_BM_CLIP)
	{
		if(response)
		{
			PlayerData[playerid][pListitem] = listitem;
			if(listitem == 0)
			{
				ShowPlayerDialog(playerid, DIALOG_BM_CLIP_AMOUNT, DIALOG_STYLE_INPUT, "9mm Luger", "Silahkan masukan jumlah clip yang ingin dibeli:\nPrice: $47.00 / 1 Clip", "Buy", "Close");
			}
			if(listitem == 1)
			{
				ShowPlayerDialog(playerid, DIALOG_BM_CLIP_AMOUNT, DIALOG_STYLE_INPUT, "12 Gauge", "Silahkan masukan jumlah clip yang ingin dibeli:\nPrice: $69.00 / 1 Clip", "Buy", "Close");
			}
			if(listitem == 2)
			{
				ShowPlayerDialog(playerid, DIALOG_BM_CLIP_AMOUNT, DIALOG_STYLE_INPUT, ".44 Magnum", "Silahkan masukan jumlah clip yang ingin dibeli:\nPrice: $55.00 / 1 Clip", "Buy", "Close");
			}
			if(listitem == 3)
			{
				ShowPlayerDialog(playerid, DIALOG_BM_CLIP_AMOUNT, DIALOG_STYLE_INPUT, "7.62mm Caliber", "Silahkan masukan jumlah clip yang ingin dibeli:\nPrice: $120.00 / 1 Clip", "Buy", "Close");
			}
		}
	}
	if(dialogid == DIALOG_BM_CLIP_AMOUNT)
	{
		if(response)
		{
			new wep = PlayerData[playerid][pListitem];
			if(wep == 0)
			{
				if(strval(inputtext) < 1)
					return ShowPlayerDialog(playerid, DIALOG_BM_CLIP_AMOUNT, DIALOG_STYLE_INPUT, "9mm Luger", "ERROR: Invalid amount!\nSilahkan masukan jumlah clip yang ingin dibeli:\nPrice: $47.00 / 1 Clip", "Buy", "Close");

				if(strval(inputtext) > 20)
					return  ShowPlayerDialog(playerid, DIALOG_BM_CLIP_AMOUNT, DIALOG_STYLE_INPUT, "9mm Luger", "ERROR: Invalid amount!\nSilahkan masukan jumlah clip yang ingin dibeli:\nPrice: $47.00 / 1 Clip", "Buy", "Close");
			
				if(GetMoney(playerid) < strval(inputtext)*4700)
					return ShowPlayerDialog(playerid, DIALOG_BM_CLIP_AMOUNT, DIALOG_STYLE_INPUT, "9mm Luger", "ERROR: You don't have enough money!\nSilahkan masukan jumlah clip yang ingin dibeli:\nPrice: $47.00 / 1 Clip", "Buy", "Close");
			
				if(Inventory_Add(playerid, "9mm Luger", 19995, strval(inputtext)) == -1)
					return 1;

				GiveMoney(playerid, -strval(inputtext)*4700, "Membeli 9mm clip");
				SendServerMessage(playerid, "Kamu berhasil membeli {FF0000}%d Clip {FFFFFF}dengan harga {FFFF00}$%s", strval(inputtext), FormatNumber(strval(inputtext)*4700));
			}
			else if(wep == 1)
			{
				if(strval(inputtext) < 1)
					return ShowPlayerDialog(playerid, DIALOG_BM_CLIP_AMOUNT, DIALOG_STYLE_INPUT, "12 Gauge", "ERROR: Invalid amount!\nSilahkan masukan jumlah clip yang ingin dibeli:\nPrice: $69.00 / 1 Clip", "Buy", "Close");

				if(strval(inputtext) > 20)
					return ShowPlayerDialog(playerid, DIALOG_BM_CLIP_AMOUNT, DIALOG_STYLE_INPUT, "12 Gauge", "ERROR: Invalid amount!\nSilahkan masukan jumlah clip yang ingin dibeli:\nPrice: $69.00 / 1 Clip", "Buy", "Close");
			
				if(GetMoney(playerid) < strval(inputtext)*6900)
					return ShowPlayerDialog(playerid, DIALOG_BM_CLIP_AMOUNT, DIALOG_STYLE_INPUT, "12 Gauge", "ERROR: You don't have enough money!\nSilahkan masukan jumlah clip yang ingin dibeli:\nPrice: $69.00 / 1 Clip", "Buy", "Close");
			
				if(Inventory_Add(playerid, "12 Gauge", 19995, strval(inputtext)) == -1)
					return 1;
					
				GiveMoney(playerid, -strval(inputtext)*6900, "Membeli shotgun clip");
				SendServerMessage(playerid, "Kamu berhasil membeli {FF0000}%d Clip {FFFFFF}dengan harga {FFFF00}$%s", strval(inputtext), FormatNumber(strval(inputtext)*6900));
			}
			else if(wep == 2) {

				if(strval(inputtext) < 1)
					return ShowPlayerDialog(playerid, DIALOG_BM_CLIP_AMOUNT, DIALOG_STYLE_INPUT, ".44 Magnum", "ERROR: Invalid amount!\nSilahkan masukan jumlah clip yang ingin dibeli:\nPrice: $55.00 / 1 Clip", "Buy", "Close");

				if(strval(inputtext) > 20)
					return ShowPlayerDialog(playerid, DIALOG_BM_CLIP_AMOUNT, DIALOG_STYLE_INPUT, ".44 Magnum", "ERROR: Invalid amount!\nSilahkan masukan jumlah clip yang ingin dibeli:\nPrice: $55.00 / 1 Clip", "Buy", "Close");
			
				if(GetMoney(playerid) < strval(inputtext)*5500)
					return ShowPlayerDialog(playerid, DIALOG_BM_CLIP_AMOUNT, DIALOG_STYLE_INPUT, ".44 Magnum", "ERROR: You don't have enough money!\nSilahkan masukan jumlah clip yang ingin dibeli:\nPrice: $55.00 / 1 Clip", "Buy", "Close");
			
				if(Inventory_Add(playerid, ".44 Magnum", 19995, strval(inputtext)) == -1)
					return 1;
					
				GiveMoney(playerid, -strval(inputtext)*5500, "Membeli DE clip");
				SendServerMessage(playerid, "Kamu berhasil membeli {FF0000}%d Clip {FFFFFF}dengan harga {FFFF00}$%s", strval(inputtext), FormatNumber(strval(inputtext)*5500));
			}
			else if(wep == 3) {

				if(strval(inputtext) < 1)
					return ShowPlayerDialog(playerid, DIALOG_BM_CLIP_AMOUNT, DIALOG_STYLE_INPUT, "7.62mm Caliber", "ERROR: Invalid amount!\nSilahkan masukan jumlah clip yang ingin dibeli:\nPrice: $120.00 / 1 Clip", "Buy", "Close");

				if(strval(inputtext) > 20)
					return ShowPlayerDialog(playerid, DIALOG_BM_CLIP_AMOUNT, DIALOG_STYLE_INPUT, "7.62mm Caliber", "ERROR: Invalid amount!\nSilahkan masukan jumlah clip yang ingin dibeli:\nPrice: $120.00 / 1 Clip", "Buy", "Close");
			
				if(GetMoney(playerid) < strval(inputtext)*15000)
					return ShowPlayerDialog(playerid, DIALOG_BM_CLIP_AMOUNT, DIALOG_STYLE_INPUT, "7.62mm Caliber", "ERROR: You don't have enough money!\nSilahkan masukan jumlah clip yang ingin dibeli:\nPrice: $120.00 / 1 Clip", "Buy", "Close");
			
				if(Inventory_Add(playerid, "7.62mm Caliber", 19995, strval(inputtext)) == -1)
					return 1;
					
				GiveMoney(playerid, -strval(inputtext)*15000, "Membeli AK/Rifle clip");
				SendServerMessage(playerid, "Kamu berhasil membeli {FF0000}%d Clip {FFFFFF}dengan harga {FFFF00}$%s", strval(inputtext), FormatNumber(strval(inputtext)*15000));
			}
		}
	} 
	if(dialogid == DIALOG_BM_HV_SCHEMATIC)
	{
		if(response)
		{
			if(listitem == 0)
			{
				if(GetMoney(playerid) < 230000)
					return SendErrorMessage(playerid, "You don't have enough money!");

				if(Inventory_Add(playerid, "9mm Silenced HV Schematic", 3111, 1) == -1)
					return 1;

				SendServerMessage(playerid, "Kamu berhasil membeli {FF0000}9mm Silenced High Velocity Schematic");
				GiveMoney(playerid, -230000, "Membeli 9mm schematic");
			}
			if(listitem == 1)
			{
				if(GetMoney(playerid) < 420000)
					return SendErrorMessage(playerid, "You don't have enough money!");

				if(Inventory_Add(playerid, "Shotgun HV Schematic", 3111, 1) == -1)
					return 1;

				SendServerMessage(playerid, "Kamu berhasil membeli {FF0000}Shotgun High Velocity Schematic");		
				GiveMoney(playerid, -420000, "Membeli shotgun schematic");		
			}
			if(listitem == 2)
			{
				if(GetMoney(playerid) < 290000)
					return SendErrorMessage(playerid, "You don't have enough money!");

				if(Inventory_Add(playerid, "Desert Eagle HV Schematic", 3111, 1) == -1)
					return 1;

				SendServerMessage(playerid, "Kamu berhasil membeli {FF0000}Desert Eagle High Velocity Schematic");		
				GiveMoney(playerid, -290000, "Membeli DE schematic");		
			}
			if(listitem == 3)
			{
				if(GetMoney(playerid) < 610000)
					return SendErrorMessage(playerid, "You don't have enough money!");

				if(Inventory_Add(playerid, "Rifle HV Schematic", 3111, 1) == -1)
					return 1;

				SendServerMessage(playerid, "Kamu berhasil membeli {FF0000}Rifle High Velocity Schematic");		
				GiveMoney(playerid, -610000, "Membeli Rifle schematic");		
			}
			if(listitem == 4)
			{
				if(GetMoney(playerid) < 1430000)
					return SendErrorMessage(playerid, "You don't have enough money!");

				if(Inventory_Add(playerid, "AK-47 HV Schematic", 3111, 1) == -1)
					return 1;

				SendServerMessage(playerid, "Kamu berhasil membeli {FF0000}AK-47 High Velocity Schematic");		
				GiveMoney(playerid, -1430000, "Membeli AK schematic");		
			}
		}
	}
	if(dialogid == DIALOG_BM_SCHEMATIC)
	{
		if(response)
		{
			if(listitem == 0)
			{
				if(GetMoney(playerid) < 170000)
					return SendErrorMessage(playerid, "You don't have enough money!");

				if(Inventory_Add(playerid, "9mm Silenced Schematic", 3111, 1) == -1)
					return 1;

				SendServerMessage(playerid, "Kamu berhasil membeli {FF0000}9mm Silenced Schematic");
				GiveMoney(playerid, -170000, "Membeli 9mm schematic");
			}
			if(listitem == 1)
			{
				if(GetMoney(playerid) < 300000)
					return SendErrorMessage(playerid, "You don't have enough money!");

				if(Inventory_Add(playerid, "Shotgun Schematic", 3111, 1) == -1)
					return 1;

				SendServerMessage(playerid, "Kamu berhasil membeli {FF0000}Shotgun Schematic");		
				GiveMoney(playerid, -300000, "Membeli shotgun schematic");		
			}
			if(listitem == 2)
			{
				if(GetMoney(playerid) < 200000)
					return SendErrorMessage(playerid, "You don't have enough money!");

				if(Inventory_Add(playerid, "Desert Eagle Schematic", 3111, 1) == -1)
					return 1;

				SendServerMessage(playerid, "Kamu berhasil membeli {FF0000}Desert Eagle Schematic");		
				GiveMoney(playerid, -200000, "Membeli DE schematic");		
			}
			if(listitem == 3)
			{
				if(GetMoney(playerid) < 460000)
					return SendErrorMessage(playerid, "You don't have enough money!");

				if(Inventory_Add(playerid, "Rifle Schematic", 3111, 1) == -1)
					return 1;

				SendServerMessage(playerid, "Kamu berhasil membeli {FF0000}Rifle Schematic");		
				GiveMoney(playerid, -460000, "Membeli Rifle schematic");		
			}
			if(listitem == 4)
			{
				if(GetMoney(playerid) < 980000)
					return SendErrorMessage(playerid, "You don't have enough money!");

				if(Inventory_Add(playerid, "AK-47 Schematic", 3111, 1) == -1)
					return 1;

				SendServerMessage(playerid, "Kamu berhasil membeli {FF0000}AK-47 Schematic");		
				GiveMoney(playerid, -980000, "Membeli AK schematic");		
			}
		}
	}
	if(dialogid == DIALOG_TICKET)
	{
		if (response)
		{
		    if (!TicketData[playerid][listitem][ticketExists])
		        return SendErrorMessage(playerid, "There is no ticket in the selected slot.");

			if (GetMoney(playerid) < TicketData[playerid][listitem][ticketFee])
			    return SendErrorMessage(playerid, "You can't afford to pay this ticket.");

			GiveMoney(playerid, -TicketData[playerid][listitem][ticketFee], "Bayar ticket");
			GovData[govVault] += TicketData[playerid][listitem][ticketFee];
			SendServerMessage(playerid, "You have paid off a %s ticket for \"$%s\".", FormatNumber(TicketData[playerid][listitem][ticketFee]), TicketData[playerid][listitem][ticketReason]);
			Ticket_Remove(playerid, listitem);
		}
	}
	if(dialogid == DIALOG_FACTION_RETURN)
	{
		cmd_faction(playerid, "menu");
	}
	if(dialogid == DIALOG_FACTION_MENU)
	{
		if(response)
		{
			new str[1012];
			if(listitem == 0)
			{
				if(GetFactionType(playerid) == FACTION_FAMILY)
				{
					format(str, sizeof(str), "Name(ID)\tRank\n");
				}
				else
				{
					format(str, sizeof(str), "Name(ID)\tStatus\tRank\tDuty Time\n");
				}
				foreach(new i : Player) if(PlayerData[i][pFaction] == PlayerData[playerid][pFaction])
				{
					if(GetFactionType(playerid) == FACTION_FAMILY)
					{
						format(str, sizeof(str), "%s%s(%d)\t%s\n", str, GetName(i), i, Faction_GetRank(i));
					}
					else
					{
						format(str, sizeof(str), "%s%s(%d)\t%s\t%s\t%dh %dm %ds\n", str, GetName(i), i, (!PlayerData[i][pOnDuty]) ? ("Off Duty") : ("On Duty"), Faction_GetRank(i), PlayerData[i][pDutyHour], PlayerData[i][pDutyMinute], PlayerData[i][pDutySecond]);
					}
				}
				ShowPlayerDialog(playerid, DIALOG_FACTION_RETURN, DIALOG_STYLE_TABLIST_HEADERS, "Online Member(s)", str, "Return", "");
			}
			if(listitem == 1)
			{
				new query[167];
				mysql_format(sqlcon, query, sizeof(query), "SELECT * FROM characters WHERE Faction = '%d'", PlayerData[playerid][pFaction]);
				mysql_tquery(sqlcon, query, "FactionMemberCheck", "d", playerid);
			}
		}
	}
	if(dialogid == DIALOG_GOTOLOC_HOUSEINT) {

		if(response)
		{
			SetPlayerPos(playerid, arrHouseInteriors[listitem][eHouseX], arrHouseInteriors[listitem][eHouseY], arrHouseInteriors[listitem][eHouseZ]);
			SetPlayerFacingAngle(playerid, arrHouseInteriors[listitem][eHouseAngle]);
			SetPlayerInterior(playerid, arrHouseInteriors[listitem][eHouseInterior]);
			Streamer_Update(playerid, STREAMER_TAG_OBJECT);
		}
	}

	if(dialogid == DIALOG_GOTOLOC_HOUSE)
	{
		if(response)
		{
			SetPlayerPos(playerid, HouseData[listitem][housePos][0], HouseData[listitem][housePos][1], HouseData[listitem][housePos][2]);
		}
	}
	if(dialogid == DIALOG_GOTOLOC_BUSINESS)
	{
		if(response)
		{
			SetPlayerPos(playerid, BizData[listitem][bizExt][0], BizData[listitem][bizExt][1], BizData[listitem][bizExt][2]);
		}
	}
	if(dialogid == DIALOG_GOTOLOC_DEALER)
	{
		if(response)
		{
			SetPlayerPos(playerid, DealerData[listitem][dealerPos][0], DealerData[listitem][dealerPos][1], DealerData[listitem][dealerPos][2]);
		}
	}
	if(dialogid == DIALOG_GOTOLOC_DOOR)
	{
		if(response)
		{
			SetPlayerPos(playerid, drData[listitem][dExtposX], drData[listitem][dExtposY], drData[listitem][dExtposZ]);
		}
	}

	if(dialogid == DIALOG_GOTOLOC_FLAT)
	{
		if(response)
		{
			SetPlayerPos(playerid, FlatData[listitem][flatPos][0], FlatData[listitem][flatPos][1], FlatData[listitem][flatPos][2]);
		}
	}
	if(dialogid == DIALOG_PAYCHECK)
	{
		if(response)
		{
			PayCheck(playerid);
		}
	}
	if(dialogid == DIALOG_GPS_PUBLIC)
	{
		if(response)
		{
			SetWaypoint(playerid, PublicPoint[listitem][0], PublicPoint[listitem][1], PublicPoint[listitem][2], 4.0);
			SendClientMessageEx(playerid, X11_LIGHTBLUE, "(GPS) {FFFFFF}Lokasi "RED"%s {FFFFFF}berhasil ditandai pada radarmu!", PublicName[listitem]);
		}
	}
	if(dialogid == DIALOG_GPS_JOB)
	{
		if(response)
		{
			SetWaypoint(playerid, JobPoint[listitem][0], JobPoint[listitem][1], JobPoint[listitem][2], 4.0);
			SendClientMessageEx(playerid, X11_LIGHTBLUE, "(GPS) {FFFFFF}Lokasi "RED"%s {FFFFFF}berhasil ditandai pada radarmu!", JobLocName[listitem]);			
		}
	}
	if(dialogid == DIALOG_GPS_DEALER)
	{
		if(response)
		{
			SetWaypoint(playerid, DealerData[listitem][dealerPos][0], DealerData[listitem][dealerPos][1], DealerData[listitem][dealerPos][2], 4.0);
			SendClientMessageEx(playerid, X11_LIGHTBLUE, "(GPS) {FFFFFF}Dealership "RED"%s {FFFFFF}berhasil ditandai pada radarmu!", DealerData[listitem][dealerName]);				
		}
	}
	if(dialogid == DIALOG_GPS_BUSINESS)
	{
		if(response)
		{
			if(listitem == 0) ShowBizTypeLocation(playerid, TYPE_247);
			if(listitem == 1) ShowBizTypeLocation(playerid, TYPE_FASTFOOD);
			if(listitem == 2) ShowBizTypeLocation(playerid, TYPE_CLOTHES);
			if(listitem == 3) ShowBizTypeLocation(playerid, TYPE_ELECTRO);
			if(listitem == 4) ShowBizTypeLocation(playerid, TYPE_EQUIPMENT);
		}
	}
	if(dialogid == DIALOG_GPS_BUSINESS_LISTED) {

		if(response) {

			new idx = ListedBusiness[playerid][listitem];

			SetWaypoint(playerid, BizData[idx][bizExt][0], BizData[idx][bizExt][1], BizData[idx][bizExt][2], 4.0);
			SendClientMessageEx(playerid, X11_LIGHTBLUE, "(GPS) {FFFFFF}Business "RED"%s {FFFFFF}berhasil ditandai pada radarmu!", BizData[idx][bizName]);	
		}
	}
	if(dialogid == DIALOG_ATM_WITHDRAW)
	{
		if(response)
		{
			new cash[32], totalcash;
			if(sscanf(inputtext, "s[32]", cash))
				return ShowPlayerDialog(playerid, DIALOG_ATM_TRANSFER_ID, DIALOG_STYLE_INPUT, "Transfer", "Please input playerid/PartOfName the player you want to transfer:\nFormat: [amount (opt:dollar.cents)]", "Next", "Close");

			totalcash = strcash(cash);

			if(totalcash < 1)
				return ShowPlayerDialog(playerid, DIALOG_ATM_WITHDRAW, DIALOG_STYLE_INPUT, sprintf("Balance: $%s", FormatNumber(PlayerData[playerid][pBank])), "ERROR: Invalid amount!\nPlease input the amount of cash you want to withdraw:", "Get", "Close");

			if(PlayerData[playerid][pBank] < totalcash)
				return ShowPlayerDialog(playerid, DIALOG_ATM_WITHDRAW, DIALOG_STYLE_INPUT, sprintf("Balance: $%s", FormatNumber(PlayerData[playerid][pBank])), "ERROR: There is no enough money on your bank!\nPlease input the amount of cash you want to withdraw:", "Get", "Close");

			if(totalcash > 100000)
				return SendErrorMessage(playerid, "Tidak bisa withdraw lebih dari $1000.00 per-withdraw.");
				
			GiveMoney(playerid, totalcash, "Withdraw ATM");
			PlayerData[playerid][pBank] -= totalcash;
			SendClientMessageEx(playerid, COLOR_SERVER, "(ATM) {FFFFFF}You have successfully withdrawn {00FF00}$%s {FFFFFF}from ATM!", FormatNumber(totalcash));
		}
	}
	if(dialogid == DIALOG_ATM_TRANSFER_AMOUNT)
	{
		if(response)
		{
			new dollars, cents, totalcash[25], cash[32], targetid = PlayerData[playerid][pTarget];

			if(targetid == INVALID_PLAYER_ID)
				return SendErrorMessage(playerid, "Transfer target is no longer valid (disconnected)"), cmd_atm(playerid, "");

			if(sscanf(inputtext, "s[32]", cash))
				return ShowPlayerDialog(playerid, DIALOG_ATM_TRANSFER_AMOUNT, DIALOG_STYLE_INPUT, "Transfer", "Please input amount of cash you want to transfer:\nFormat: [amount (opt:dollar.cents)]", "Transfer", "Close");

			if(strfind(cash, ".", true) != -1)
			{
				sscanf(cash, "p<.>dd", dollars, cents);
				format(totalcash, sizeof(totalcash), "%d%02d", dollars, cents);
				if(strval(totalcash) < 0)
					return ShowPlayerDialog(playerid, DIALOG_ATM_TRANSFER_AMOUNT, DIALOG_STYLE_INPUT, "Transfer", "Please input amount of cash you want to transfer:\nFormat: [amount (opt:dollar.cents)]", "Transfer", "Close");

				if(PlayerData[playerid][pBank] < strval(totalcash))
					return ShowPlayerDialog(playerid, DIALOG_ATM_TRANSFER_AMOUNT, DIALOG_STYLE_INPUT, "Transfer", "Please input amount of cash you want to transfer:\nFormat: [amount (opt:dollar.cents)]", "Transfer", "Close");

				PlayerData[targetid][pBank] += strval(totalcash);
				PlayerData[playerid][pBank] -= strval(totalcash);
				SendClientMessageEx(playerid, COLOR_SERVER, "(ATM) {FFFFFF}You have successfully transfer {00FF00}$%s {FFFFFF}to {FFFF00}%s", FormatNumber(strval(totalcash)), GetName(targetid));
				SendClientMessageEx(targetid, COLOR_SERVER, "(ATM) {FFFFFF}You've received {00FF00}$%s {FFFFFF}from {FFFF00}%s", FormatNumber(strval(totalcash)), GetName(playerid));
			}
			else
			{
				sscanf(cash, "d", dollars);
				format(totalcash, sizeof(totalcash), "%d00", dollars);

				if(strval(totalcash) < 0)
					return ShowPlayerDialog(playerid, DIALOG_ATM_TRANSFER_AMOUNT, DIALOG_STYLE_INPUT, "Transfer", "Please input amount of cash you want to transfer:\nFormat: [amount (opt:dollar.cents)]", "Transfer", "Close");

				if(PlayerData[playerid][pBank] < strval(totalcash))
					return ShowPlayerDialog(playerid, DIALOG_ATM_TRANSFER_AMOUNT, DIALOG_STYLE_INPUT, "Transfer", "Please input amount of cash you want to transfer:\nFormat: [amount (opt:dollar.cents)]", "Transfer", "Close");

				PlayerData[targetid][pBank] += strval(totalcash);
				PlayerData[playerid][pBank] -= strval(totalcash);
				SendClientMessageEx(playerid, COLOR_SERVER, "(ATM) {FFFFFF}You have successfully transfer {00FF00}$%s {FFFFFF}to {FFFF00}%s", FormatNumber(strval(totalcash)), GetName(targetid));
				SendClientMessageEx(targetid, COLOR_SERVER, "(ATM) {FFFFFF}You've received {00FF00}$%s {FFFFFF}from {FFFF00}%s", FormatNumber(strval(totalcash)), GetName(playerid));
			}			
		}
		else
		{
			cmd_atm(playerid, "");
		}
	}
	if(dialogid == DIALOG_ATM_TRANSFER_ID)
	{
		if(response)
		{
			new id;
			if(sscanf(inputtext, "u", id))
				return ShowPlayerDialog(playerid, DIALOG_ATM_TRANSFER_ID, DIALOG_STYLE_INPUT, "Transfer", "Please input playerid/PartOfName the player you want to transfer:\n", "Next", "Close");

			if(id == INVALID_PLAYER_ID)
				return ShowPlayerDialog(playerid, DIALOG_ATM_TRANSFER_ID, DIALOG_STYLE_INPUT, "Transfer", "ERROR: Invalid player specified!\nPlease input playerid/PartOfName the player you want to transfer:", "Next", "Close");
		

			PlayerData[playerid][pTarget] = id;
			ShowPlayerDialog(playerid, DIALOG_ATM_TRANSFER_AMOUNT, DIALOG_STYLE_INPUT, "Transfer", "Please input amount of cash you want to transfer:\nFormat: [amount (opt:dollar.cents)]", "Transfer", "Close");
			SendServerMessage(playerid, "Transfer target is {FFFF00}%s", GetName(id));
		}
		else
		{
			cmd_atm(playerid, "");
		}
	}
	if(dialogid == DIALOG_ATM)
	{
		if(response)
		{
			if(listitem == 0)
			{
				cmd_atm(playerid, "");
			}
			if(listitem == 1)
			{
				ShowPlayerDialog(playerid, DIALOG_ATM_WITHDRAW, DIALOG_STYLE_INPUT, sprintf("Balance: $%s", FormatNumber(PlayerData[playerid][pBank])), "Please input the amount of cash you want to withdraw:", "Get", "Close");
			}
			if(listitem == 2)
			{
				if(PlayerData[playerid][pHour] < 2)
					return SendErrorMessage(playerid, "Minimal bermain 2 jam untuk melakukan ini.");

				ShowPlayerDialog(playerid, DIALOG_ATM_TRANSFER_ID, DIALOG_STYLE_INPUT, "Transfer", "Please input playerid/PartOfName the player you want to transfer:", "Next", "Close");
			}
			if(listitem == 3)
			{
				if(PlayerData[playerid][pPaycheck] > 0 && !PlayerData[playerid][pAduty])
					return SendErrorMessage(playerid, "Kamu harus menunggu %d menit untuk Paycheck!", PlayerData[playerid][pPaycheck]/60);

				new str[256];
				new taxval = PlayerData[playerid][pSalary]/100*GovData[govTax];
				format(str, sizeof(str), "{FFFFFF}Salary: {009000}$%s\n{FFFFFF}Tax: {FFFF00}-$%s {FF0000}(%d percent)\n{FFFFFF}Total Interest: {00FF00}$%s", FormatNumber(PlayerData[playerid][pSalary]), FormatNumber(taxval), GovData[govTax], FormatNumber(PlayerData[playerid][pSalary]-taxval));
				ShowPlayerDialog(playerid, DIALOG_PAYCHECK, DIALOG_STYLE_MSGBOX, "Paycheck", str, "Get", "Close");
			}
		}
	}/*
	if(dialogid == DIALOG_DEALER_RESTOCK_AMOUNT)
	{
		if(response)
		{
			new amount = strval(inputtext), id = PlayerData[playerid][pSelecting], list = PlayerData[playerid][pListitem];
			if(amount < 1)
				return ShowPlayerDialog(playerid, DIALOG_DEALER_RESTOCK_AMOUNT, DIALOG_STYLE_INPUT, sprintf("%s", ReturnDealerVehicle(DealerData[id][dealerVehicle][list])), "ERROR: Invalid amount!\nPlease input amount for rethe selected (Vehicle)\nNote: Min 1.", "Restock", "Close");

			DealerData[id][dealerStock][list] += amount;
			SQL_SaveDealership(id);
			SendServerMessage(playerid, "Kamu telah merestock {FFFF00}%d {FFFFFF}kendaraan dealer.", amount);
		}
	}
	if(dialogid == DIALOG_DEALER_RESTOCK_LIST)
	{
		if(response)
		{
			new id = PlayerData[playerid][pSelecting];
			if(DealerData[id][dealerVehicle][listitem] == 19300)
				return SendErrorMessage(playerid, "There is no vehicle on selected list!");

			ShowPlayerDialog(playerid, DIALOG_DEALER_RESTOCK_AMOUNT, DIALOG_STYLE_INPUT, sprintf("%s", ReturnDealerVehicle(DealerData[id][dealerVehicle][listitem])), "Please input amount for rethe selected (Vehicle)\nNote: Min 1.", "Restock", "Close");
			PlayerData[playerid][pListitem] = listitem;
		}
	}
	if(dialogid == DIALOG_EDITDEALER_MODEL)
	{
		if(response)
		{
			if(isnull(inputtext))
				return ShowPlayerDialog(playerid, DIALOG_EDITDEALER_MODEL, DIALOG_STYLE_INPUT, "Vehicle Model", "Silahkan masukan model id atau nama kendaraan:", "Next", "Close");

			new model = GetVehicleModelByName(inputtext), id = PlayerData[playerid][pSelecting], list = PlayerData[playerid][pListitem];

			if(!model)
				return ShowPlayerDialog(playerid, DIALOG_EDITDEALER_MODEL, DIALOG_STYLE_INPUT, "Vehicle Model", "ERROR: Invalid vehicle model!\nSilahkan masukan model id atau nama kendaraan:", "Next", "Close");
		
			for(new i = 0; i < 6; i++)
			{
				if(DealerData[id][dealerVehicle][i] == model)
					return ShowPlayerDialog(playerid, DIALOG_EDITDEALER_MODEL, DIALOG_STYLE_INPUT, "Vehicle Model", "ERROR: Sudah ada kendaraan dengan model ini pada dealership ini!\nSilahkan masukan model id atau nama kendaraan:", "Next", "Close");
			}
			DealerData[id][dealerVehicle][list] = model;
			ShowPlayerDialog(playerid, DIALOG_EDITDEALER_COST, DIALOG_STYLE_INPUT, "Vehicle Cost", sprintf("Silahkan masukan harga kendaraan untuk '%s'", ReturnVehicleModelName(DealerData[id][dealerVehicle][list])), "Confirm", "Close");
		}
	}
	if(dialogid == DIALOG_EDITDEALER_COST)
	{
		new id = PlayerData[playerid][pSelecting], list = PlayerData[playerid][pListitem];
		if(response)
		{
			if(isnull(inputtext))
				return ShowPlayerDialog(playerid, DIALOG_EDITDEALER_COST, DIALOG_STYLE_INPUT, "Vehicle Cost", sprintf("Silahkan masukan harga kendaraan untuk '%s'", ReturnVehicleModelName(DealerData[id][dealerVehicle][list])), "Confirm", "Close");

			if(strval(inputtext) < 0)
				return ShowPlayerDialog(playerid, DIALOG_EDITDEALER_COST, DIALOG_STYLE_INPUT, "Vehicle Cost", sprintf("Silahkan masukan harga kendaraan untuk '%s'", ReturnVehicleModelName(DealerData[id][dealerVehicle][list])), "Confirm", "Close");

			DealerData[id][dealerCost][list] = strcash(inputtext);
			SendClientMessageEx(playerid, COLOR_SERVER, "AdmCmd: {FFFFFF}Kamu telah mengubah kendaraan menjadi {FFFF00}%s {FFFFFF}dengan harga {00FF00}$%s", ReturnVehicleModelName(DealerData[id][dealerVehicle][list]), FormatNumber(DealerData[id][dealerCost][list]));
			SQL_SaveDealership(id);
		}
		else
		{
			DealerData[id][dealerVehicle] = 19300;
			DealerData[id][dealerCost] = 0;
			SQL_SaveDealership(id);
		}
	}
	if(dialogid == DIALOG_EDITDEALER_SELECT)
	{
		if(response)
		{
			PlayerData[playerid][pListitem] = listitem;
			ShowPlayerDialog(playerid, DIALOG_EDITDEALER_MODEL, DIALOG_STYLE_INPUT, "Vehicle Model", "Silahkan masukan model id atau nama kendaraan:", "Next", "Close");
		}
	}*/
	if(dialogid == DIALOG_CONTACTNUM)
	{
		if (response)
		{
			new
			    cn[156];
			format(cn, sizeof(cn), "Contact Name: %s\n\nPlease enter the phone number for this contact:", PlayerData[playerid][pTempContact]);
		    if (isnull(inputtext) || !IsNumeric(inputtext))
		        return ShowPlayerDialog(playerid, DIALOG_CONTACTNUM, DIALOG_STYLE_INPUT, "Contact Number", cn, "Submit", "Back");

			new contactid = Contact_Add(playerid, strval(inputtext), PlayerData[playerid][pTempContact]);

			if(contactid == -1)
				return SendErrorMessage(playerid, "There is no room left for anymore contacts.");

			SendClientMessageEx(playerid, X11_LIGHTBLUE, "CONTACT (Info) "WHITE"Kamu telah menambahkan "YELLOW"\"%s\" "WHITE"ke kontakmu.", PlayerData[playerid][pTempContact]);
		}
		else
		{
			ShowContacts(playerid);
		}
	}
	if(dialogid == DIALOG_NEWCONTACT)
	{
		if (response)
		{
		    if (isnull(inputtext))
				return ShowPlayerDialog(playerid, DIALOG_NEWCONTACT, DIALOG_STYLE_INPUT, "New Contact", "Please enter the name of the contact below:", "Submit", "Back");

		    if (strlen(inputtext) > 32)
		        return ShowPlayerDialog(playerid, DIALOG_NEWCONTACT, DIALOG_STYLE_INPUT, "New Contact", "Please enter the name of the contact below:", "Submit", "Back");

			format(PlayerData[playerid][pTempContact], 32, inputtext);
			new cn[128];
            format(cn, sizeof(cn), "Contact Name: %s\n\nPlease enter the phone number for this contact:", inputtext);
		    ShowPlayerDialog(playerid, DIALOG_CONTACTNUM, DIALOG_STYLE_INPUT, "Contact Number", cn, "Submit", "Back");
		}
		else
		{
			ShowContacts(playerid);
		}
	}
	if(dialogid == DIALOG_CONTACTINFO)
	{
		if (response)
		{
		    new
				id = PlayerData[playerid][pContact],
				string[72];

			switch (listitem)
			{
			    case 0:
			    {
			        format(string, 16, "%d", ContactData[playerid][id][contactNumber]);
					cmd_call(playerid, string);
			    }
			    case 1:
			    {
			        mysql_format(sqlcon, string, sizeof(string), "DELETE FROM `contacts` WHERE `ID` = '%d' AND `contactID` = '%d'", PlayerData[playerid][pID], ContactData[playerid][id][contactID]);
			        mysql_tquery(sqlcon, string);

			        SendServerMessage(playerid, "You have deleted \"%s\" from your contacts.", ContactData[playerid][id][contactName]);

			        ContactData[playerid][id][contactExists] = false;
			        ContactData[playerid][id][contactNumber] = 0;
			        ContactData[playerid][id][contactID] = 0;
			        ShowContacts(playerid);
			    }
				case 2: {

					new targetid = GetNumberOwner(ContactData[playerid][id][contactNumber]);

					if(targetid == INVALID_PLAYER_ID)
						return SendErrorMessage(playerid, "Nomor tersebut tidak dapat diakses!");

					if(PlayerData[targetid][pPhoneOff])
						return SendErrorMessage(playerid, "Nomor tersebut sedang tidak aktif!");

					new Float:x, Float:y, Float:z;
					GetPlayerPos(playerid, x, y, z);
					SetWaypoint(targetid, x, y, z, 4.0);
					SendServerMessage(targetid, "Nomor "LIGHTBLUE"%s(%d) "WHITE"telah membagikan lokasinya kepadamu!", IsNumberKnown(targetid, PlayerData[playerid][pPhoneNumber]), PlayerData[playerid][pPhoneNumber]);
					SendServerMessage(playerid, "Kamu telah membagikan lokasi kepada Nomor "LIGHTBLUE"%s(%d)", IsNumberKnown(playerid, ContactData[playerid][id][contactNumber]), ContactData[playerid][id][contactNumber]);
					
				}
			}
		}
	}
	if(dialogid == DIALOG_CONTACT)
	{
		if (response)
		{
		    if (!listitem)
			{
		        ShowPlayerDialog(playerid, DIALOG_NEWCONTACT, DIALOG_STYLE_INPUT, "New Contact", "Please enter the name of the contact below:", "Submit", "Back");
		    }
		    else
			{
			    PlayerData[playerid][pContact] = ListedContacts[playerid][listitem - 1];

		        ShowPlayerDialog(playerid, DIALOG_CONTACTINFO, DIALOG_STYLE_LIST, ContactData[playerid][PlayerData[playerid][pContact]][contactName], "Call Contact\nDelete Contact\nShare Location", "Select", "Back");
		    }
		}
		for (new i = 0; i != MAX_CONTACTS; i ++)
		{
		    ListedContacts[playerid][i] = -1;
		}
	}
	if(dialogid == DIALOG_DIAL)
	{
		if (response)
		{
		    new
		        string[16];

		    if (isnull(inputtext) || !IsNumeric(inputtext))
		        return ShowPlayerDialog(playerid, DIALOG_DIAL, DIALOG_STYLE_INPUT, "Dial Number", "Please enter the number that you wish to dial below:", "Dial", "Back");

	        format(string, 16, "%d", strval(inputtext));
			cmd_call(playerid, string);
		}
	}
	if(dialogid == DIALOG_SMS)
	{
		if (response)
		{

			if(!PlayerData[playerid][pCredit])
				return SendErrorMessage(playerid, "Kamu tidak memiliki phone credit!");

		    new number = strval(inputtext);

		    if (isnull(inputtext) || !IsNumeric(inputtext))
		        return ShowPlayerDialog(playerid, DIALOG_SMS, DIALOG_STYLE_INPUT, "Send Text Message", "Please enter the number that you wish to send a text message to:", "Dial", "Back");

	        if (GetNumberOwner(number) == INVALID_PLAYER_ID)
	            return ShowPlayerDialog(playerid, DIALOG_SMS, DIALOG_STYLE_INPUT, "Send Text Message", "Error: That number is not online right now.\n\nPlease enter the number that you wish to send a text message to:", "Dial", "Back");

			PlayerData[playerid][pContact] = GetNumberOwner(number);
			ShowPlayerDialog(playerid, DIALOG_SMSNUM, DIALOG_STYLE_INPUT, "Text Message", "Please enter the message to send:", "Send", "Back");
		}
	}
	if(dialogid == DIALOG_REPLY)
	{
		if (response)
		{
			if (isnull(inputtext))
				return cmd_reply(playerid, "\0");

			new targetid = GetNumberOwner(PlayerData[playerid][pLastNumber]);

			if (!IsPlayerConnected(targetid) || !PlayerHasItem(playerid, "Cellphone") || PlayerData[targetid][pPhoneOff])
			    return SendErrorMessage(playerid, "The specified phone number went offline.");
		    
		    if(strlen(inputtext) > 90)
		    	return SendErrorMessage(playerid, "Text tidak bisa lebih dari 90 karakter!");

		    if(PlayerData[playerid][pCredit] < 1)
		    	return SendErrorMessage(playerid, "Kamu tidak memiliki phone credits!");

			PlayerData[playerid][pCredit] -= 3;

			if(PlayerData[playerid][pCredit] < 0)
				PlayerData[playerid][pCredit] = 0;

			SendClientMessageEx(targetid, X11_LIGHTBLUE, "** SMS from %s(%d): "WHITE"%s", IsNumberKnown(targetid, PlayerData[playerid][pPhoneNumber], true), PlayerData[playerid][pPhoneNumber], inputtext);
			SendClientMessageEx(playerid, X11_LIGHTBLUE, "** SMS to %s(%d): "WHITE"%s", IsNumberKnown(playerid, PlayerData[targetid][pPhoneNumber], true), PlayerData[targetid][pPhoneNumber], inputtext);

			PlayerPlaySound(playerid, targetid, 0.0, 0.0, 0.0);
					
			cmd_ame(playerid, "types something on his cellphone.");

			PlayerData[targetid][pLastNumber] = PlayerData[playerid][pPhoneNumber];
		}
	}
	if(dialogid == DIALOG_SMSNUM)
	{
		if (response)
		{
			if (isnull(inputtext))
				return ShowPlayerDialog(playerid, DIALOG_SMSNUM, DIALOG_STYLE_INPUT, "Text Message", "Error: Please enter a message to send.\n\nPlease enter the message to send:", "Send", "Back");

			new targetid = PlayerData[playerid][pContact];

			if (!IsPlayerConnected(targetid) || !PlayerHasItem(playerid, "Cellphone") || PlayerData[targetid][pPhoneOff])
			    return SendErrorMessage(playerid, "The specified phone number went offline.");
		    
		    if(strlen(inputtext) > 90)
		    	return SendErrorMessage(playerid, "Text tidak bisa lebih dari 90 karakter!");

		    if(PlayerData[playerid][pCredit] < 1)
		    	return SendErrorMessage(playerid, "Kamu tidak memiliki phone credits!");

			PlayerData[playerid][pCredit] -= 3;

			if(PlayerData[playerid][pCredit] < 0)
				PlayerData[playerid][pCredit] = 0;

			SendClientMessageEx(targetid, X11_LIGHTBLUE, "** SMS from %s(%d): "WHITE"%s", IsNumberKnown(targetid, PlayerData[playerid][pPhoneNumber], true), PlayerData[playerid][pPhoneNumber], inputtext);
			SendClientMessageEx(playerid, X11_LIGHTBLUE, "** SMS to %s(%d): "WHITE"%s", IsNumberKnown(playerid, PlayerData[targetid][pPhoneNumber], true), PlayerData[targetid][pPhoneNumber], inputtext);

			PlayerPlaySound(playerid, targetid, 0.0, 0.0, 0.0);
					
			cmd_ame(playerid, "types something on his cellphone.");

			PlayerData[targetid][pLastNumber] = PlayerData[playerid][pPhoneNumber];
		}
		else
		{
	        ShowPlayerDialog(playerid, DIALOG_SMS, DIALOG_STYLE_INPUT, "Send Text Message", "Please enter the number that you wish to send a text message to:", "Submit", "Back");
		}
	}
	if(dialogid == DIALOG_SHARE_LOCATION) {
		if(response) {
			new number = strval(inputtext),
				targetid;


			if(PlayerData[playerid][pCredit] < 10)
				return SendErrorMessage(playerid, "Kamu tidak memiliki cukup phone credits.");

			if(isnull(inputtext))
				return ShowPlayerDialog(playerid, DIALOG_SHARE_LOCATION, DIALOG_STYLE_INPUT, "Share Location", "(error) Invalid phone number!\nMasukkan nomor ponsel yang akan kamu bagikan lokasimu saat ini:", "Share", "Close");

			targetid = GetNumberOwner(number);

			if(targetid == INVALID_PLAYER_ID)
				return ShowPlayerDialog(playerid, DIALOG_SHARE_LOCATION, DIALOG_STYLE_INPUT, "Share Location", "(error) Nomor tersebut tidak dapat diakses saat ini\nMasukkan nomor ponsel yang akan kamu bagikan lokasimu saat ini:", "Share", "Close");
		
			if(PlayerData[targetid][pPhoneOff])
				return ShowPlayerDialog(playerid, DIALOG_SHARE_LOCATION, DIALOG_STYLE_INPUT, "Share Location", "(error) Nomor tersebut tidak dapat diakses saat ini\nMasukkan nomor ponsel yang akan kamu bagikan lokasimu saat ini:", "Share", "Close");
		
			new Float:x, Float:y, Float:z;
			GetPlayerPos(playerid, x, y, z);
			SetWaypoint(targetid, x, y, z, 4.0);
			SendServerMessage(targetid, "Nomor "LIGHTBLUE"%s(%d) "WHITE"telah membagikan lokasinya kepadamu!", IsNumberKnown(targetid, PlayerData[playerid][pPhoneNumber]), PlayerData[playerid][pPhoneNumber]);
			SendServerMessage(playerid, "Kamu telah membagikan lokasi kepada Nomor "LIGHTBLUE"%s(%d)", IsNumberKnown(playerid, number), number);

			PlayerData[playerid][pCredit] -= 10;

			if(PlayerData[playerid][pCredit] < 0)
				PlayerData[playerid][pCredit] = 0;
		}
		else cmd_phone(playerid, "");
	}
	if(dialogid == DIALOG_PHONE)
	{
		if(response)
		{
			if(listitem == 0 || listitem == 1)
			{
				cmd_phone(playerid, "");
			}
			if(listitem == 2)
			{
		        if (PlayerData[playerid][pPhoneOff])
		            return SendErrorMessage(playerid, "Your phone must be powered on.");                            

				ShowPlayerDialog(playerid, DIALOG_DIAL, DIALOG_STYLE_INPUT, "Dial Number", "Please enter the number that you wish to dial below:", "Call", "Back");				
			}
			if(listitem == 3)
			{
			    if (PlayerData[playerid][pPhoneOff])
		            return SendErrorMessage(playerid, "Your phone must be powered on.");

			    ShowContacts(playerid);
			}
			if(listitem == 4)
			{
		        if (PlayerData[playerid][pPhoneOff])
		            return SendErrorMessage(playerid, "Your phone must be powered on.");

				if(!HasPhoneSignal(playerid))
					return SendErrorMessage(playerid, "Signal Service is unreachable on your location.");

				ShowPlayerDialog(playerid, DIALOG_SMS, DIALOG_STYLE_INPUT, "Send Text Message", "Please enter the number that you wish to send a text message to:", "Send", "Back");
			}
			if(listitem == 5)
			{
		        if (PlayerData[playerid][pPhoneOff])
		            return SendErrorMessage(playerid, "Your phone must be powered on.");

				Advert_Show(playerid);
			}
			if(listitem == 6) {

		        if (PlayerData[playerid][pPhoneOff])
		            return SendErrorMessage(playerid, "Your phone must be powered on.");


				if(!HasPhoneSignal(playerid))
					return SendErrorMessage(playerid, "Signal Service is unreachable on your location.");

				if(GetPlayerInterior(playerid) > 0 || GetPlayerVirtualWorld(playerid) > 0)
					return SendErrorMessage(playerid, "Hanya bisa membagikan lokasi diluar ruangan!");

				ShowPlayerDialog(playerid, DIALOG_SHARE_LOCATION, DIALOG_STYLE_INPUT, "Share Location", "Masukkan nomor ponsel yang akan kamu bagikan lokasimu saat ini:", "Share", "Close");	
			}
			if(listitem == 7)
			{
				if(g_LiveStatus == LIVE_STATUS_OFF_AIR && g_ReporterPlayerID == INVALID_PLAYER_ID) {
					return SendErrorMessage(playerid, "Tidak ada siaran yang sedang berlangsung.");

				}

				if(IsPlayerRecording(playerid)) {
					return SendErrorMessage(playerid, "Tidak dapat melakukan ini jika sedang merekam.");
				}
				if(IsPlayerWatchingCamera(playerid))
					return SendErrorMessage(playerid, "Kamu sedang menonton siaran langsung saat ini.");
					
				SendClientMessage(playerid, X11_LIGHTBLUE, "(Live) "WHITE"Kamu sekarang menonton televisi.");
				SendClientMessage(playerid, X11_LIGHTBLUE, "(Live) "WHITE"Gunakan "YELLOW"/stopwatchlive "WHITE"untuk berhenti.");

				StartPlayerWatchingCamera(playerid, g_ReporterPlayerID);
				SendNearbyMessage(playerid, 15.0, X11_PLUM, "** %s starts watching live broadcast from their phone", ReturnName(playerid));

				ShowLiveTD(playerid);
			}
			if(listitem == 8) {
			    if (!PlayerData[playerid][pPhoneOff])
			    {
           			if (PlayerData[playerid][pCallLine] != INVALID_PLAYER_ID)
				   	{
			        	CancelCall(playerid);
					}
					PlayerData[playerid][pPhoneOff] = true;
			        SendNearbyMessage(playerid, 15.0,X11_PLUM, "** %s has powered off their cellphone.", ReturnName(playerid));
				}
				else
				{
				    PlayerData[playerid][pPhoneOff] = false;
			        SendNearbyMessage(playerid, 15.0,X11_PLUM, "** %s has powered on their cellphone.", ReturnName(playerid));
				}
			}
		}
	}
	if(dialogid == DIALOG_NUMBERPHONE)
	{
		if(response)
		{
			if(listitem == 5)
			{
				ShowNumberIndex(playerid);
				SendServerMessage(playerid, "Number list refreshed.");
			}
			else
			{
				new bid = PlayerData[playerid][pInBiz];
				new price = BizData[bid][bizProduct][0];
				new prodname[34];
				prodname = ProductName[bid][0];

				PlayerData[playerid][pPhoneNumber] = NumberIndex[playerid][listitem];
				SendServerMessage(playerid, "Your new phone number is {FFFF00}#%d", NumberIndex[playerid][listitem]);
				GiveMoney(playerid, -price);
				BizData[bid][bizStock]--;
				BizData[bid][bizVault] += price;
				if(Inventory_Count(playerid, "Cellphone") < 1)
				{
					Inventory_Add(playerid, "Cellphone", 18867, 1);
					cmd_ame(playerid, sprintf("* %s has paid $%s and purchased a %s.", ReturnName(playerid), FormatNumber(price), prodname));
				}
			}
		}
		else
		{
			cmd_buy(playerid, "");
		}
	}
	if(dialogid == DIALOG_BUYPLATE)
	{
		new i = g_ListedVehicle[playerid][listitem];
		if(response)
		{

			if(GetMoney(playerid) < 15000)
				return SendErrorMessage(playerid, "You don't have enough money!");

			#define randex(%0,%1) (random(%1 - %0 + 1) + %0)
			format(VehicleData[i][vPlate], 16, "%c%c%c%c%c%c%c", randex('1', '9'), randex('A', 'Z'), randex('A', 'Z'), randex('A', 'Z'), randex('1', '9'), randex('1', '9'), randex('1', '9'));
			SendClientMessageEx(playerid, COLOR_SERVER, "(Vehicle) {FFFFFF}You have successfully purchasing plate for your {FFFF00}%s", ReturnVehicleModelName(VehicleData[i][vModel]));
			GiveMoney(playerid, -15000, "Beli plate");

			if(IsValidVehicle(i))
				SetVehicleNumberPlate(i, VehicleData[i][vPlate]);
		}
	}
	if(dialogid == DIALOG_CURE) {
		if(response) {
			new targetid = PlayerData[playerid][pTargetid];

			if(listitem == 0) {
				PlayerData[targetid][pHealthy] = 100.0;
				PlayerData[targetid][pCough] = 0;
				PlayerData[targetid][pCoughRate] = 0;
				SendServerMessage(playerid, "You have cure {FFFF00}%s's "WHITE"sickness (cough)", ReturnName(targetid));
				SendServerMessage(targetid, "Your sickness (cough) has been cured by {FFFF00}%s", ReturnName(playerid));				
			}
			if(listitem == 1) {
				PlayerData[targetid][pHealthy] = 100.0;
				PlayerData[targetid][pFever] = 0;
				PlayerData[targetid][pFeverRate] = 0;
				SendServerMessage(playerid, "You have cure {FFFF00}%s's "WHITE"sickness (fever)", ReturnName(targetid));
				SendServerMessage(targetid, "Your sickness (fever) has been cured by {FFFF00}%s", ReturnName(playerid));	
			}
		}
	}
	if(dialogid == DIALOG_TREATMENT)
	{
		if(response)
		{
			new targetid = PlayerData[playerid][pTargetid];

			if(!IsPlayerNearPlayer(playerid, targetid, 5.0) || targetid == INVALID_PLAYER_ID)
				return SendErrorMessage(playerid, "You must close to that player!");

			if(listitem == 0)
			{
				if(!PlayerData[targetid][pInjured])
					return SendErrorMessage(playerid, "That player is not in injured condition!");

				PlayerData[targetid][pInjured] = false;
				ClearAnimations(targetid, 1);
				SendServerMessage(playerid, "You have been reviving {FFFF00}%s", ReturnName(targetid));
				SendServerMessage(targetid, "You have been revived by {FFFF00}%s", ReturnName(playerid));

				ApplyAnimation(targetid, "PED", "GETUP_FRONT", 4.0, 0, 1, 1, 0, 0);
			}
			if(listitem == 1)
			{
				new Float:hp;
				GetPlayerHealth(targetid, hp);
				if(hp >= 100.0)
					return SendErrorMessage(playerid, "That player already have Max Health!");

				SetPlayerHealth(targetid, 100.0);
				SendServerMessage(playerid, "You have healing {FFFF00}%s", ReturnName(targetid));
				SendServerMessage(targetid, "You have been healed by {FFFF00}%s", ReturnName(playerid));
			}
			if(listitem == 2)
			{
				ShowPlayerDialog(playerid, DIALOG_CURE, DIALOG_STYLE_LIST, "Cure Player", "Cough\nFever", "Cure", "Close");
			}
			if(listitem == 3)
			{
				ResetPlayerDamages(playerid);
				SendServerMessage(playerid, "You have operating {FFFF00}%s", ReturnName(targetid));
				SendServerMessage(targetid, "You have been operated by {FFFF00}%s", ReturnName(playerid));
			}
		}
	}
	if(dialogid == DIALOG_MDC_RETURN)
	{
		PlayerPlayNearbySound(playerid, MDC_SELECT);
		ShowMDC(playerid);
	}
	if(dialogid == DIALOG_MDC_911_MENU)
	{
		if(response)
		{
			new id = PlayerData[playerid][pListitem];
			PlayerPlayNearbySound(playerid, MDC_SELECT);
			if(listitem == 0)
			{
				ShowEmergencyDetails(playerid, id);
			}
			if(listitem == 1)
			{
				SendFactionMessage(PlayerData[playerid][pFaction], COLOR_RADIO, "[911] %s %s is now responding 911 report with problem %s", Faction_GetRank(playerid), ReturnName(playerid), GetProblemType(EmergencyData[id][emgSector], EmergencyData[id][emgType]));
				SendClientMessageEx(playerid, COLOR_RADIO, "[MDC] {FFFFFF}You have respond to emergency call with problem {FFFF00}%s", GetProblemType(EmergencyData[id][emgSector], EmergencyData[id][emgType]));
				SendClientMessageEx(playerid, COLOR_RADIO, "[MDC] {FFFFFF}Location: %s | Name: %s | Number: %d", EmergencyData[id][emgLocation], EmergencyData[id][emgIssuerName], EmergencyData[id][emgNumber]);
				Emergency_Delete(id);
			}
			if(listitem == 2)
			{
				SendClientMessageEx(playerid, COLOR_RADIO, "[MDC] {FFFFFF}Successfully remove selected emergency call.");
				Emergency_Delete(id);
			}
		}
		else
		{
			ShowMDC(playerid);
			PlayerPlayNearbySound(playerid, MDC_SELECT);
		}
	}
	if(dialogid == DIALOG_MDC_911)
	{
		if(response)
		{
			new count;
			PlayerPlayNearbySound(playerid, MDC_SELECT);
			for(new i = 0; i < MAX_EMERGENCY; i++) if(EmergencyData[i][emgExists])
			{
				if(EmergencyData[i][emgSector] == ReturnSector(playerid) && count++ == listitem)
				{
					PlayerData[playerid][pListitem] = i;
					ShowPlayerDialog(playerid, DIALOG_MDC_911_MENU, DIALOG_STYLE_LIST, "MDC > 911 Menu", "Show Details\nRespond Report\nRemove Report", "Select", "Return");
				}		
			}	
		}
		else
		{
			ShowMDC(playerid);
			PlayerPlayNearbySound(playerid, MDC_SELECT);
		}
	}
	if(dialogid == DIALOG_MDC_PLATE)
	{
		if(response)
		{
			if(!strcmp(inputtext, "NONE", true) || !strcmp(inputtext, "RENTAL", true))
				return ShowPlayerDialog(playerid, DIALOG_MDC_PLATE, DIALOG_STYLE_INPUT, "MDC > Plate Search", "ERROR: Can't found vehicle with specified number plate!\nPlease input the full vehicle plate you wish to search:", "Search", "Return");
			
			new found = 0;
			new str[512];
			new date[6];
			format(str, sizeof(str), "Last Location\tTime\n");
			for(new i = 0; i < MAX_SPEEDCAM; i++) if(SpeedData[i][speedExists])
			{
				if(!strcmp(SpeedData[i][speedPlate], inputtext, true))
				{
					found++;
					TimestampToDate(SpeedData[i][speedTime], date[2], date[1], date[0], date[3], date[4], date[5]);
					format(str, sizeof(str), "%s%s\t%i/%02d/%02d %02d:%02d\n", str, GetLocation(SpeedData[i][speedPos][0], SpeedData[i][speedPos][1], SpeedData[i][speedPos][2]), date[2], date[0], date[1], date[3], date[4]);
				}
			}
			if(found)
				ShowPlayerDialog(playerid, DIALOG_MDC_RETURN, DIALOG_STYLE_TABLIST_HEADERS, "MDC > Plate Search", str, "Return", "");
			else
				ShowPlayerDialog(playerid, DIALOG_MDC_RETURN, DIALOG_STYLE_MSGBOX, "MDC > Error", "There is no SpeedTrap last vehicle matching with the plate.", "Return", "Close");
		}
		else
		{
			PlayerPlayNearbySound(playerid, MDC_SELECT);
			ShowMDC(playerid);
		}
	}
	if(dialogid == DIALOG_MDC_CITIZEN_MENU) {
		if(response) {
			new name[MAX_PLAYER_NAME], sql_id = GetPVarInt(playerid, "LookupID");

			GetPVarString(playerid, "LookupName", name, MAX_PLAYER_NAME);
			if(listitem == 0) {
				mysql_tquery(sqlcon, sprintf("SELECT * FROM `characters` WHERE `Name` = '%s' LIMIT 1;", name), "OnLookupInformationMDC", "d", playerid);
			}
			if(listitem == 1) {
				mysql_tquery(sqlcon, sprintf("SELECT * FROM `arrest` WHERE `owner` = '%d' ORDER BY `id` ASC;",sql_id), "OnLookupArrestMDC", "d", playerid); 
			}
			if(listitem == 2) {
				mysql_tquery(sqlcon, sprintf("SELECT * FROM `tickets` WHERE `ID` = '%d' ORDER BY `ticketID` ASC;", sql_id), "OnLookupTicketMDC", "d", playerid);
			}
			if(listitem == 3) {
				mysql_tquery(sqlcon, sprintf("SELECT * FROM `crime_record` WHERE `PlayerID` = '%d' ORDER BY `ID` ASC LIMIT 15;", sql_id), "OnLookupCrimeRecord", "d", playerid);
			}
		}
	}
	if(dialogid == DIALOG_MDC_CITIZEN) {
		if(response) {
			new query[256];
			mysql_format(sqlcon, query, sizeof(query), "SELECT * FROM `characters` WHERE `Name` = '%e' AND `IDCard` = '%d' LIMIT 1;", inputtext, 1);
			mysql_tquery(sqlcon, query, "OnLookupMDC", "ds", playerid, inputtext);
		}
	}
	if(dialogid == DIALOG_MDC_VEHICLE) {
		if(response) {

			if(!strcmp(inputtext, "NONE", true) || !strcmp(inputtext, "RENTAL", true))
				return ShowPlayerDialog(playerid, DIALOG_MDC_VEHICLE, DIALOG_STYLE_INPUT, "MDC > Vehicle Lookup", "Please input the Vehicle Plate you wish to lookup:", "Search", "Close");

			new query[244];
			mysql_format(sqlcon, query, sizeof(query), "SELECT * FROM `vehicle` WHERE `vehPlate` = '%e' ORDER BY `vehID` ASC LIMIT 1;", inputtext);
			mysql_tquery(sqlcon, query, "OnLookupVehicle", "ds", playerid, inputtext);
		}
		else {
			ShowMDC(playerid);
		}
		PlayerPlayNearbySound(playerid, MDC_SELECT);
	}
	if(dialogid == DIALOG_MDC)
	{
		if(response)
		{
			PlayerPlayNearbySound(playerid, MDC_SELECT);
			if(listitem == 0)
			{
				ShowEmergency(playerid);
			}
			if(listitem == 1)
			{
				ShowPlayerDialog(playerid, DIALOG_MDC_PLATE, DIALOG_STYLE_INPUT, "MDC > Plate Search", "Please input the full vehicle plate you wish to search:", "Search", "Return");
			}
			if(listitem == 2) {
				ShowPlayerDialog(playerid, DIALOG_MDC_CITIZEN, DIALOG_STYLE_INPUT, "MDC > Citizen Lookup", "Please input the Citizen Name you wish to lookup:", "Search", "Close");
			}
			if(listitem == 3) {
				ShowPlayerDialog(playerid, DIALOG_MDC_VEHICLE, DIALOG_STYLE_INPUT, "MDC > Vehicle Lookup", "Please input the Vehicle Plate you wish to lookup:", "Search", "Close");
			}
		}
		else
		{
			PlayerPlayNearbySound(playerid, MDC_ERROR);
			SetPlayerChatBubble(playerid, "* logs off of the Mobile Data Computer *",X11_PLUM, 15, 10000);
		}
	}
	if(dialogid == DIALOG_CALL_911)
	{
		if(response)
		{
			ServiceType[playerid] = listitem;
			if(ServiceIndex[playerid] == 1) ServiceIndex[playerid] = 2; SendClientMessage(playerid, 0x1394BFFF, "911 Dispatch: OK, Tell us more about what's going on.");
		}
		else
		{
			ServiceIndex[playerid] = 0;
			ServiceRequest[playerid] = 0;
			SendClientMessage(playerid, 0x1394BFFF, "911 Dispatch: Alright we will cancel our units. Thank you.");
		    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		    RemovePlayerAttachedObject(playerid, 3);
		}
	}
	if(dialogid == DIALOG_MOWER)
	{
		if(response)
		{

			if(PlayerData[playerid][pMasked])
				return SendErrorMessage(playerid, "Buka maskermu terlebih dahulu!"), RemovePlayerFromVehicle(playerid);

	     	OnMower[playerid] = true;
	     	MowerIndex[playerid] = 0;
			SendClientMessage(playerid, COLOR_SERVER, "(Sidejob) {FFFFFF}Ikuti semua checkpoint yang ada di radar.");
			SetPlayerCheckpoint(playerid, arr_MowerCP[MowerIndex[playerid]][mowerX], arr_MowerCP[MowerIndex[playerid]][mowerY], arr_MowerCP[MowerIndex[playerid]][mowerZ], 4.0);
			SwitchVehicleEngine(GetPlayerVehicleID(playerid), true);
		}
		else
		{
			RemovePlayerFromVehicle(playerid);
		}
	}
	if(dialogid == DIALOG_SWEEPER)
	{
		if(response)
		{

			if(PlayerData[playerid][pMasked])
				return SendErrorMessage(playerid, "Buka maskermu terlebih dahulu!"), RemovePlayerFromVehicle(playerid);

	     	OnSweeping[playerid] = true;
	     	SweeperIndex[playerid] = 0;
			SendClientMessage(playerid, COLOR_SERVER, "(Sidejob) {FFFFFF}Ikuti semua checkpoint yang ada di radar.");
			SetPlayerCheckpoint(playerid, SweeperPoint[SweeperIndex[playerid]][0], SweeperPoint[SweeperIndex[playerid]][1], SweeperPoint[SweeperIndex[playerid]][2], 4.0);
			SwitchVehicleEngine(GetPlayerVehicleID(playerid), true);
		}
		else
		{
			RemovePlayerFromVehicle(playerid);
		}
	}
	if(dialogid == DIALOG_HELP_RETURN)
	{
		cmd_help(playerid, "");
	}
	if(dialogid == DIALOG_HELP_JOB)//list, place, buy, sell, remove
	{
		new string[1412];
		if(response)
		{
			if(listitem == 0)
			{
				strcat(string, "\nNote: Hanya mengikuti checkpoint saja :)");
				ShowPlayerDialog(playerid, DIALOG_HELP_RETURN, DIALOG_STYLE_MSGBOX, "Bus", string, "Back", "");
			}
			if(listitem == 1)
			{
				strcat(string, "\nNote: Hanya mengikuti checkpoint saja :)");
				ShowPlayerDialog(playerid, DIALOG_HELP_RETURN, DIALOG_STYLE_MSGBOX, "Sweeper", string, "Back", "");
			}
			if(listitem == 2)
			{
				strcat(string, "/pickup - untuk mengambil sampah\n");
				strcat(string, "\nNote: Command diatas hanya bisa diakses di Trashmaster.");
				ShowPlayerDialog(playerid, DIALOG_HELP_RETURN, DIALOG_STYLE_MSGBOX, "Trashmaster", string, "Back", "");
			}
			if(listitem == 3)
			{
				strcat(string, "/cargo buy - untuk membeli cargo di Cargo Buypoint\n");
				strcat(string, "/cargo list - untuk melihat list cargo yang ada di Truck\n");
				strcat(string, "/cargo place - untuk menyimpan cargo ke Truck\n");
				strcat(string, "/cargo sell - untuk menjual cargo ke Business\n");
				strcat(string, "/cargo remove - untuk membuang cargo\n");
				strcat(string, "\nNote: Hanya truck Benson dan Yankee untuk pekerjaan ini.");
				ShowPlayerDialog(playerid, DIALOG_HELP_RETURN, DIALOG_STYLE_MSGBOX, "Trucker", string, "Back", "");
			}
			if(listitem == 4)
			{
				strcat(string, "/mech duty - untuk Onduty sebagai Mechanic\n");
				strcat(string, "/mech menu - untuk membuka menu kendaraan\n");
				strcat(string, "\nNote: Command diatas hanya bisa diakses di Mechanic Center.");
				ShowPlayerDialog(playerid, DIALOG_HELP_RETURN, DIALOG_STYLE_MSGBOX, "Mechanic", string, "Back", "");
			}
			if(listitem == 5)
			{
				strcat(string, "/taxi duty - untuk Onduty sebagai Taxi Driver\n");
				strcat(string, "/taxi calls - untuk melihat list penelfon taxi.\n");
				strcat(string, "\nNote: Command diatas hanya bisa diakses di dalam Taxi.");
				ShowPlayerDialog(playerid, DIALOG_HELP_RETURN, DIALOG_STYLE_MSGBOX, "Mechanic", string, "Back", "");				
			}
			if(listitem == 6)
			{
				strcat(string, "/selltimber - untuk menjual Timber yang ada di kendaraan\n");
				strcat(string, "- Key 'H' didekat pohon yang belum ditebang untuk mulai menebang\n");
				strcat(string, "- Key 'H' didekat pohon yang sudah ditebang untuk meload timber\n");
				ShowPlayerDialog(playerid, DIALOG_HELP_RETURN, DIALOG_STYLE_MSGBOX, "Lumberjack", string, "Back", "");
			}
			if(listitem == 7)
			{
				strcat(string, "\nNote: Hanya mengikuti checkpoint saja :)");
				ShowPlayerDialog(playerid, DIALOG_HELP_RETURN, DIALOG_STYLE_MSGBOX, "Mower", string, "Back", "");
			}
			if(listitem == 8)
			{
				strcat(string, "/pickupcrate - untuk mengangkut crate ke forklift.\n");
				strcat(string, "/loadcrate - untuk memasukkan crate ke rumpo.\n");
				strcat(string, "/unloadcrate - untuk mengantarkan/menurunkan crate ke unloading point.\n");
				ShowPlayerDialog(playerid, DIALOG_HELP_RETURN, DIALOG_STYLE_MSGBOX, "Delivery Driver", string, "Back", "");
			}
			if(listitem == 9) {
				strcat(string, "/mine - untuk memulai menambang batu.\n");
				ShowPlayerDialog(playerid, DIALOG_HELP_RETURN, DIALOG_STYLE_MSGBOX, "Miner", string, "Back", "");
			}
			if(listitem == 10) {
				strcat(string, "/trackpacket - untuk melacak paket.\n");
				strcat(string, "/takepacket - untuk mengambil paket.\n");
				ShowPlayerDialog(playerid, DIALOG_HELP_RETURN, DIALOG_STYLE_MSGBOX, "Miner", string, "Back", "");
			}
			if(listitem == 11) {
				strcat(string, "/deliverbox - untuk mengantarkan paket kedepan pintu rumah.\n");
				ShowPlayerDialog(playerid, DIALOG_HELP_RETURN, DIALOG_STYLE_MSGBOX, "Box Courier", string, "Back", "");
			}
		}
	}
	if(dialogid == DIALOG_HELP)
	{
		new string[1412];
		if(response)
		{
			if(listitem == 0)
			{
				strcat(string, "/phone | /salary | /insu | /weapon | /takejob | /quitjob | /renthelp | /call | /accept | /animlist\n");
				strcat(string, "/pay | /buy | /refuel | /inventory | /enter | /jobdelay | /report | /ask | /sms | /myproperty \n");
				strcat(string, "/health [opt:playerid/name] | /mask | /atm | /stats | /drag | /undrag | /frisk | /factions\n");
				strcat(string, "/damages [opt:playerid/PartOfName] | /setfreq | /pr | /disablecp | /licenses [opt:playerid/PartOfName]\n");
				strcat(string, "/v(ehicle) | /seatbelt | /isafk | /cc | /fish | /sellfish | /myfish | /buybait | /toggle\n");
				strcat(string, "/tag | /cursor | /tog(gle) | /warnings | /changepassword | /showidcard | /acc | /watchlive | /stopwatchlive\n");
				ShowPlayerDialog(playerid, DIALOG_HELP_RETURN, DIALOG_STYLE_MSGBOX, "General Commands", string, "Back", "");
			}
			if(listitem == 1)
			{
				strcat(string, "/me | /ame | /pr | /do | /l(ow) | /w(hisper) | /o | /c | /pm");
				ShowPlayerDialog(playerid, DIALOG_HELP_RETURN, DIALOG_STYLE_MSGBOX, "Chat Commands", string, "Back", "");
			}
			if(listitem == 2)
			{
				ShowPlayerDialog(playerid, DIALOG_HELP_JOB, DIALOG_STYLE_LIST, "Job Commands", "Bus (Sidejob)\nSweeper (Sidejob)\nTrashmaster (Sidejob)\nTrucker\nMechanic\nTaxi\nLumberjack\nMower (Sidejob)\nDelivery Driver (Sidejob)\nMiner\nSmuggler\nBox Courier(Sidejob)", "Select", "Close");
			}
			if(listitem == 3)
			{
				strcat(string, "/faction [invite/kick/menu/accept/locker/setrank/quit/offkick]\n");
				strcat(string, "/r | /or | /d | /od\n");
				if(GetFactionType(playerid) == FACTION_POLICE)
				{
					strcat(string, "/mdc | /arrest | /detain | /cuff | /uncuff | /impound | /seizeweed | /m(egaphone) | /trace | /roadblock\n");
					strcat(string, "/take | /callsign | /spike | /removespike | /tazer | /backup | /locktire | /impound | /tirelock | /grant\n");
				}
				else if(GetFactionType(playerid) == FACTION_MEDIC)
				{
					strcat(string, "/mdc | /treatment | /m(egaphone) | /stretcher | /getmedkit | /backup | /inspect | /getpills | /roadblock");
				}
				else if(GetFactionType(playerid) == FACTION_NEWS)
				{
					strcat(string, "/live | /inviteguest | /removeguest | /bc | /broadcast | /(give/remove)mic | /postad | /camera");
				}
				else if(GetFactionType(playerid) == FACTION_GOV)
				{
					strcat(string, "/tax [set/withdraw/deposit]");
				}
				ShowPlayerDialog(playerid, DIALOG_HELP_RETURN, DIALOG_STYLE_MSGBOX, "Faction Commands", string, "Back", "");
			}
			if(listitem == 4)
			{
				strcat(string, "/biz buy - untuk membeli Business\n");
				strcat(string, "/biz menu - untuk membuka menu Business (for owner)\n");
				strcat(string, "/biz lock - untuk toggle lock/unlock Business\n");
				strcat(string, "/biz req- untuk meminta rekepada Trucker\n");
				strcat(string, "/biz convertfuel - untuk mereFuel (24/7 only)\n");
				ShowPlayerDialog(playerid, DIALOG_HELP_RETURN, DIALOG_STYLE_MSGBOX, "Business Commands", string, "Back", "");

			}
			if(listitem == 5)
			{
				strcat(string, "/house buy - untuk membeli house\n");
				strcat(string, "/house lock - untuk toggle lock/unlock House\n");
				strcat(string, "/house menu - untuk membuka House Menu\n");
				ShowPlayerDialog(playerid, DIALOG_HELP_RETURN, DIALOG_STYLE_MSGBOX, "House Commands", string, "Back", "");
			}
			if(listitem == 6)
			{
				strcat(string, "/flat buy - untuk membeli flat\n");
				strcat(string, "/flat lock - untuk toggle lock/unlock flat\n");
				strcat(string, "/flat menu - untuk membuka menu flat\n");
				ShowPlayerDialog(playerid, DIALOG_HELP_RETURN, DIALOG_STYLE_MSGBOX, "Flat Commands", string, "Back", "");
			}
			if(listitem == 7)
			{
				strcat(string, "/withdraw - untuk menarik uang dari Bank\n");
				strcat(string, "/deposit - untuk menyimpan uang ke Bank\n");
				strcat(string, "/paycheck - untuk mencairkan salary\n");
				strcat(string, "/balance - untuk melihat total uang di Bank\n");
				strcat(string, "/transfer - untuk men-transfer uang ke player lain\n");
				strcat(string, "\nNote: Command diatas hanya bisa dilakukan di Bank Point.");
				ShowPlayerDialog(playerid, DIALOG_HELP_RETURN, DIALOG_STYLE_MSGBOX, "Bank Commands", string, "Back", "");
			}
			if(listitem == 8)
			{
				strcat(string, "/buyvehicle - untuk membeli kendaraan\n");
				ShowPlayerDialog(playerid, DIALOG_HELP_RETURN, DIALOG_STYLE_MSGBOX, "Dealership Commands", string, "Back", "");
			}
			if(listitem == 9) {
				strcat(string, "/sharekey - untuk memberikan akses kunci kendaraan\n");
				strcat(string, "/removekey - untuk menghapus akses kunci kendaraan\n");
				strcat(string, "/removeallkeys - untuk menghapus semua player yang memiliki akses kunci\n");
				ShowPlayerDialog(playerid, DIALOG_HELP_RETURN, DIALOG_STYLE_MSGBOX, "Vehicle ShareKey Commands", string, "Back", "");
			}
			if(listitem == 10) {
				strcat(string, "/workshop employee - membuka menu pekerja workshop\n");
				strcat(string, "/workshop deposit - memasukkan uang ke workshop\n");
				strcat(string, "/workshop withdraw - mengambil uang dari workshop\n");
				strcat(string, "/workshop buy - membeli workshop\n");
				strcat(string, "/workshop name - mengubah nama workshop\n");
				ShowPlayerDialog(playerid, DIALOG_HELP_RETURN, DIALOG_STYLE_MSGBOX, "Workshop Commands", string, "Back", "");
			}
			if(listitem == 11) {
				strcat(string, "/race scp - untuk mengatur Checkpoint\n");
				strcat(string, "/race start - untuk memulai balapan\n");
				strcat(string, "/race invite - untuk mengundang orang ke balapan\n");
				strcat(string, "/race kick - untuk mengeluarkan orang dari balapan\n");
				strcat(string, "/race finish - untuk mengatur Checkpoint finish\n");
				strcat(string, "/race removefinish - untuk menghapus Checkpoint finish\n");
				strcat(string, "/race leave - untuk keluar dari balapan");
				ShowPlayerDialog(playerid, DIALOG_HELP_RETURN, DIALOG_STYLE_MSGBOX, "Race Commands", string, "Back", "");
			}
			if(listitem == 12) {
				strcat(string, "/propose - untuk mengajukan pernikahan kepada pasangan (digunakan didalam church)\n");
				strcat(string, "/divorce - untuk menghapus married status antar pasangan.\n");
				ShowPlayerDialog(playerid, DIALOG_HELP_RETURN, DIALOG_STYLE_MSGBOX, "Marriage Commands", string, "Back", "");
			}
		}
	}
	//-----[Textdraw Login]
	/*if(dialogid == DIALOG_BIRTHDATE)
	{
		if (response)
		{
		    new
				iDay,
				iMonth,
				iYear;

		    new const
		        arrMonthDays[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

		    if (sscanf(inputtext, "p</>ddd", iDay, iMonth, iYear)) {
		        ShowPlayerDialog(playerid, DIALOG_BIRTHDATE, DIALOG_STYLE_INPUT, "Date of Birth", "Error: Invalid format specified!\n\nPlease enter your date of birth below (DD/MM/YYYY):", "Submit", "Cancel");
			}
			else if (iYear < 1900 || iYear > 2014) {
			    ShowPlayerDialog(playerid, DIALOG_BIRTHDATE, DIALOG_STYLE_INPUT, "Date of Birth", "Error: Invalid year specified!\n\nPlease enter your date of birth below (DD/MM/YYYY):", "Submit", "Cancel");
			}
			else if (iMonth < 1 || iMonth > 12) {
			    ShowPlayerDialog(playerid, DIALOG_BIRTHDATE, DIALOG_STYLE_INPUT, "Date of Birth", "Error: Invalid month specified!\n\nPlease enter your date of birth below (DD/MM/YYYY):", "Submit", "Cancel");
			}
			else if (iDay < 1 || iDay > arrMonthDays[iMonth - 1]) {
			    ShowPlayerDialog(playerid, DIALOG_BIRTHDATE, DIALOG_STYLE_INPUT, "Date of Birth", "Error: Invalid day specified!\n\nPlease enter your date of birth below (DD/MM/YYYY):", "Submit", "Cancel");
			}
			else 
			{
			    format(PlayerData[playerid][pBirthdate], 24, inputtext);


			    PlayerTextDrawSetString(playerid, BIRTHDATETD[playerid], sprintf("%s", PlayerData[playerid][pBirthdate]));
			    SelectTextDraw(playerid, COLOR_YELLOW);
			}
		}
		else
		{
			SelectTextDraw(playerid, COLOR_YELLOW);
		}
	}*/
	if(dialogid == DIALOG_EDITLOCKER_SKIN_MODEL)
	{
		if (response)
		{
		    new skin = strval(inputtext);

		    if (isnull(inputtext))
		        return  ShowPlayerDialog(playerid, DIALOG_EDITLOCKER_SKIN_MODEL, DIALOG_STYLE_INPUT, "Add by Model ID", "Please enter the model ID of the skin below (0-311):", "Add", "Cancel");

			if (skin < 0 || skin > 311)
			    return ShowPlayerDialog(playerid, DIALOG_EDITLOCKER_SKIN_MODEL, DIALOG_STYLE_INPUT, "Add by Model ID", "Please enter the model ID of the skin below (0-311):", "Add", "Cancel");

	        FactionData[PlayerData[playerid][pFactionEdit]][factionSkins][PlayerData[playerid][pSelectedSlot]] = skin;
			Faction_Save(PlayerData[playerid][pFactionEdit]);

			if (skin) {
			    SendServerMessage(playerid, "You have set the skin ID in slot %d to %d.", PlayerData[playerid][pSelectedSlot] + 1, skin);
			}
			else {
			    SendServerMessage(playerid, "You have removed the skin ID in slot %d.", PlayerData[playerid][pSelectedSlot] + 1);
			}
		}
	}
	if(dialogid == DIALOG_EDITLOCKER_SKIN)
	{
		if (response)
		{
		    static
		        skins[299];

			switch (listitem)
			{
			    case 0:
			        ShowPlayerDialog(playerid, DIALOG_EDITLOCKER_SKIN_MODEL, DIALOG_STYLE_INPUT, "Add by Model ID", "Please enter the model ID of the skin below (0-311):", "Add", "Cancel");

				case 1:
				{
				    for (new i = 0; i < sizeof(skins); i ++)
				        skins[i] = i + 1;

					ShowModelSelectionMenu(playerid, "Add Skin", MODEL_SELECTION_ADD_SKIN, skins, sizeof(skins), -16.0, 0.0, -55.0);
				}
				case 2:
				{
				    FactionData[PlayerData[playerid][pFactionEdit]][factionSkins][PlayerData[playerid][pSelectedSlot]] = 0;

				    Faction_Save(PlayerData[playerid][pFactionEdit]);
				    SendServerMessage(playerid, "You have removed the skin ID in slot %d.", PlayerData[playerid][pSelectedSlot] + 1);
				}
			}
		}
	}
	if(dialogid == DIALOG_EDITLOCKER)
	{
		if (response)
		{
		    switch (listitem)
		    {
		        case 0:
		        {
				    new
				        Float:x,
				        Float:y,
				        Float:z;

					GetPlayerPos(playerid, x, y, z);

					FactionData[PlayerData[playerid][pFactionEdit]][factionLockerPos][0] = x;
					FactionData[PlayerData[playerid][pFactionEdit]][factionLockerPos][1] = y;
					FactionData[PlayerData[playerid][pFactionEdit]][factionLockerPos][2] = z;

					FactionData[PlayerData[playerid][pFactionEdit]][factionLockerInt] = GetPlayerInterior(playerid);
					FactionData[PlayerData[playerid][pFactionEdit]][factionLockerWorld] = GetPlayerVirtualWorld(playerid);

					Faction_Refresh(PlayerData[playerid][pFactionEdit]);
					Faction_Save(PlayerData[playerid][pFactionEdit]);
					SendServerMessage(playerid, "You have adjusted the locker position of faction ID: %d.", PlayerData[playerid][pFactionEdit]);
				}
				case 1:
				{
					new
					    string[512];

					string[0] = 0;

				    for (new i = 0; i < 10; i ++)
					{
				        if (FactionData[PlayerData[playerid][pFactionEdit]][factionWeapons][i])
							format(string, sizeof(string), "%sWeapon %d: %s\n", string, i + 1, ReturnWeaponName(FactionData[PlayerData[playerid][pFactionEdit]][factionWeapons][i]));

						else format(string, sizeof(string), "%sEmpty Slot\n", string);
				    }
				    ShowPlayerDialog(playerid, DIALOG_EDITLOCKER_WEAPON, DIALOG_STYLE_LIST, "Locker Weapons", string, "Select", "Cancel");
				}
			}
		}
	}
	if(dialogid == DIALOG_EDITLOCKER_WEAPON_ID)
	{
		if (response)
		{
		    new weaponid = strval(inputtext);

		    if (isnull(inputtext))
		        return ShowPlayerDialog(playerid, DIALOG_EDITLOCKER_WEAPON_ID, DIALOG_STYLE_INPUT, "Set Weapon", sprintf("Current Weapon: %s (%d)\n\nPlease enter the new weapon ID for slot %d:", ReturnWeaponName(FactionData[PlayerData[playerid][pFactionEdit]][factionWeapons][PlayerData[playerid][pSelectedSlot]]), FactionData[PlayerData[playerid][pFactionEdit]][factionWeapons][PlayerData[playerid][pSelectedSlot]], PlayerData[playerid][pSelectedSlot]), "Submit", "Cancel");

			if (weaponid < 0 || weaponid > 46)
			    return ShowPlayerDialog(playerid, DIALOG_EDITLOCKER_WEAPON_ID, DIALOG_STYLE_INPUT, "Set Weapon", sprintf("Current Weapon: %s (%d)\n\nPlease enter the new weapon ID for slot %d:", ReturnWeaponName(FactionData[PlayerData[playerid][pFactionEdit]][factionWeapons][PlayerData[playerid][pSelectedSlot]]), FactionData[PlayerData[playerid][pFactionEdit]][factionWeapons][PlayerData[playerid][pSelectedSlot]], PlayerData[playerid][pSelectedSlot]), "Submit", "Cancel");

	        FactionData[PlayerData[playerid][pFactionEdit]][factionWeapons][PlayerData[playerid][pSelectedSlot]] = weaponid;
	        Faction_Save(PlayerData[playerid][pFactionEdit]);

		    if (weaponid) {
			    SendServerMessage(playerid, "You have set the weapon in slot %d to %s.", PlayerData[playerid][pSelectedSlot] + 1, ReturnWeaponName(weaponid));
			}
			else {
			    SendServerMessage(playerid, "You have removed the weapon in slot %d.", PlayerData[playerid][pSelectedSlot] + 1);
			}
		}
	}
	if(dialogid == DIALOG_EDITLOCKER_WEAPONRANK)
	{
		if (response)
		{
		    new rank = strval(inputtext);

		    if (isnull(inputtext))
		        return ShowPlayerDialog(playerid, DIALOG_EDITLOCKER_WEAPONRANK, DIALOG_STYLE_INPUT, "Set Minimum Rank", sprintf("Current Rank: %d\n\nPlease enter the new minimum rank for the weapon in slot %d:", FactionData[PlayerData[playerid][pFactionEdit]][factionWeaponMinRank][PlayerData[playerid][pSelectedSlot]], PlayerData[playerid][pSelectedSlot]), "Submit", "Cancel");

			if (rank < 1 || rank > FactionData[PlayerData[playerid][pFaction]][factionRanks])
			    return ShowPlayerDialog(playerid, DIALOG_EDITLOCKER_WEAPONRANK, DIALOG_STYLE_INPUT, "Set Minimum Rank", sprintf("Current Rank: %d\n\nPlease enter the new minimum rank for the weapon in slot %d:", FactionData[PlayerData[playerid][pFactionEdit]][factionWeaponMinRank][PlayerData[playerid][pSelectedSlot]], PlayerData[playerid][pSelectedSlot]), "Submit", "Cancel");

	        FactionData[PlayerData[playerid][pFactionEdit]][factionWeaponMinRank][PlayerData[playerid][pSelectedSlot]] = rank;
	        Faction_Save(PlayerData[playerid][pFactionEdit]);

		    if (rank) {
			    SendServerMessage(playerid, "You have set the minimum rank in slot %d to %s.", PlayerData[playerid][pSelectedSlot] + 1, FactionRanks[PlayerData[playerid][pFactionEdit]][PlayerData[playerid][pSelectedSlot]]);
			}
			else {
			    SendServerMessage(playerid, "You have removed the minimum rank in slot %d.", PlayerData[playerid][pSelectedSlot] + 1);
			}
		}
	}
	if(dialogid == DIALOG_EDITLOCKER_WEAPON_AMMO)
	{
		if (response)
		{
		    new ammo = strval(inputtext);

		    if (isnull(inputtext))
		        return ShowPlayerDialog(playerid, DIALOG_EDITLOCKER_WEAPON_AMMO, DIALOG_STYLE_INPUT, "Set Ammunition", sprintf("Current Ammo: %d\n\nPlease enter the new ammunition for the weapon in slot %d:", FactionData[PlayerData[playerid][pFactionEdit]][factionAmmo][PlayerData[playerid][pSelectedSlot]], PlayerData[playerid][pSelectedSlot]), "Submit", "Cancel");

			if (ammo < 1 || ammo > 15000)
			    return ShowPlayerDialog(playerid, DIALOG_EDITLOCKER_WEAPON_AMMO, DIALOG_STYLE_INPUT, "Set Ammunition", sprintf("Current Ammo: %d\n\nPlease enter the new ammunition for the weapon in slot %d:", FactionData[PlayerData[playerid][pFactionEdit]][factionAmmo][PlayerData[playerid][pSelectedSlot]], PlayerData[playerid][pSelectedSlot]), "Submit", "Cancel");

	        FactionData[PlayerData[playerid][pFactionEdit]][factionAmmo][PlayerData[playerid][pSelectedSlot]] = ammo;
	        Faction_Save(PlayerData[playerid][pFactionEdit]);

			SendServerMessage(playerid, "You have set the ammunition in slot %d to %d.", PlayerData[playerid][pSelectedSlot] + 1, ammo);
		}		
	}
	if(dialogid == DIALOG_EDITLOCKER_WEAPON_SET)
	{
		if (response)
		{
		    switch (listitem)
		    {
		        case 0:
		        	ShowPlayerDialog(playerid, DIALOG_EDITLOCKER_WEAPON_ID, DIALOG_STYLE_INPUT, "Set Weapon", sprintf("Current Weapon: %s (%d)\n\nPlease enter the new weapon ID for slot %d:", ReturnWeaponName(FactionData[PlayerData[playerid][pFactionEdit]][factionWeapons][PlayerData[playerid][pSelectedSlot]]), FactionData[PlayerData[playerid][pFactionEdit]][factionWeapons][PlayerData[playerid][pSelectedSlot]], PlayerData[playerid][pSelectedSlot]), "Submit", "Cancel");

				case 1:
		            ShowPlayerDialog(playerid, DIALOG_EDITLOCKER_WEAPON_AMMO, DIALOG_STYLE_INPUT, "Set Ammunition", sprintf("Current Ammo: %d\n\nPlease enter the new ammunition for the weapon in slot %d:", FactionData[PlayerData[playerid][pFactionEdit]][factionAmmo][PlayerData[playerid][pSelectedSlot]], PlayerData[playerid][pSelectedSlot]), "Submit", "Cancel");

				case 2:
					ShowPlayerDialog(playerid, DIALOG_EDITLOCKER_WEAPONRANK, DIALOG_STYLE_INPUT, "Set Minimum Rank", sprintf("Current Rank: %d\n\nPlease enter the new minimum rank for the weapon in slot %d:", FactionData[PlayerData[playerid][pFactionEdit]][factionWeaponMinRank][PlayerData[playerid][pSelectedSlot]], PlayerData[playerid][pSelectedSlot]), "Submit", "Cancel");
				case 3:
				{
				    FactionData[PlayerData[playerid][pFactionEdit]][factionWeapons][PlayerData[playerid][pSelectedSlot]] = 0;
					FactionData[PlayerData[playerid][pFactionEdit]][factionAmmo][PlayerData[playerid][pSelectedSlot]] = 0;

					Faction_Save(PlayerData[playerid][pFactionEdit]);

					SendServerMessage(playerid, "You have removed the weapon in slot %d.", PlayerData[playerid][pSelectedSlot] + 1);
				}
		    }
		}
	}
	if(dialogid == DIALOG_EDITLOCKER_WEAPON)
	{
		if (response)
		{
		    PlayerData[playerid][pSelectedSlot] = listitem;
		    ShowPlayerDialog(playerid, DIALOG_EDITLOCKER_WEAPON_SET, DIALOG_STYLE_LIST, "Edit Weapon", sprintf("Set Weapon (%d)\nSet Ammunition (%d)\nSet Minimum Rank (%d)\nClear", FactionData[PlayerData[playerid][pFactionEdit]][factionWeapons][PlayerData[playerid][pSelectedSlot]], FactionData[PlayerData[playerid][pFactionEdit]][factionAmmo][PlayerData[playerid][pSelectedSlot]], FactionData[PlayerData[playerid][pFactionEdit]][factionWeaponMinRank][PlayerData[playerid][pSelectedSlot]]), "Select", "Cancel");
		}
	}
	if(dialogid == DIALOG_LOCKER_WEAPON)
	{
		new factionid = PlayerData[playerid][pFaction];
		if (response)
		{
		    new
		        weaponid = FactionData[factionid][factionWeapons][listitem],
		        ammo = FactionData[factionid][factionAmmo][listitem],
		        dura = FactionData[factionid][factionDurability][listitem];

		    if (weaponid)
			{
				if(GetFactionType(playerid) == FACTION_FAMILY)
				{
			        if (PlayerHasWeapon(playerid, weaponid))
			            return SendErrorMessage(playerid, "You have this weapon equipped already.");

			        GiveWeaponToPlayer(playerid, weaponid, ammo, dura, FactionData[factionid][factionHighVelocity][listitem]);
			        SendNearbyMessage(playerid, 15.0, X11_PLUM, "** %s reaches inside the locker and equips a %s.", ReturnName(playerid), ReturnWeaponName(weaponid));

			        FactionData[factionid][factionWeapons][listitem] = 0;
			        FactionData[factionid][factionAmmo][listitem] = 0;
					FactionData[factionid][factionHighVelocity][listitem] = 0;
					FactionData[factionid][factionDurability][listitem] = 0;
			        Faction_Save(factionid);
				}
				else
				{
					if(!PlayerData[playerid][pOnDuty])
						return SendErrorMessage(playerid, "You must faction duty!");

					if(PlayerData[playerid][pFactionRank] < FactionData[factionid][factionWeaponMinRank][listitem])
						return SendErrorMessage(playerid, "Kamu harus rank %d+ untuk menggunakan senjata ini.", FactionData[factionid][factionWeaponMinRank][listitem]);
			        if (PlayerHasWeapon(playerid, weaponid))
			            return SendErrorMessage(playerid, "You have this weapon equipped already.");

			        GiveWeaponToPlayer(playerid, weaponid, ammo, 500, 0);
			        SendNearbyMessage(playerid, 15.0,X11_PLUM, "** %s reaches inside the locker and equips a %s.", ReturnName(playerid), ReturnWeaponName(weaponid));
				}
			}
			else
			{
			    if (GetFactionType(playerid) == FACTION_FAMILY)
			    {
			        if ((weaponid = GetWeapon(playerid)) == 0)
			            return SendErrorMessage(playerid, "You are not holding any weapon.");

			        FactionData[factionid][factionWeapons][listitem] = weaponid;
			        FactionData[factionid][factionAmmo][listitem] = PlayerData[playerid][pAmmo][g_aWeaponSlots[weaponid]];
			        FactionData[factionid][factionDurability][listitem] = PlayerData[playerid][pDurability][g_aWeaponSlots[weaponid]];
					FactionData[factionid][factionHighVelocity][listitem] = PlayerData[playerid][pHighVelocity][g_aWeaponSlots[weaponid]];
			        Faction_Save(factionid);

	                ResetWeapon(playerid, weaponid);
			        SendNearbyMessage(playerid, 30.0,X11_PLUM, "** %s takes out a %s and stores it in the locker.", ReturnName(playerid), ReturnWeaponName(weaponid));
				}
				else
				{
				    SendErrorMessage(playerid, "The selected weapon slot is empty.");
				}
		    }
		}
		else {
		    cmd_faction(playerid, "locker");
		}
	}
	if(dialogid == DIALOG_LOCKER)
	{
		if (response)
		{
			new factionid = PlayerData[playerid][pFaction];
		    new
		        skins[10],
		        string[512];

			string[0] = 0;

		    if (FactionData[factionid][factionType] != FACTION_FAMILY)
		    {
		        switch (listitem)
		        {
		            case 0:
		            {
		                if (!PlayerData[playerid][pOnDuty])
		                {
		                    PlayerData[playerid][pOnDuty] = true;
		                    SetPlayerArmour(playerid, 100.0);

		                    SetFactionColor(playerid);
		                    SetPlayerSkin(playerid, PlayerData[playerid][pFactionSkin]);
		                    SendNearbyMessage(playerid, 20.0,X11_PLUM, "** %s has clocked in and is now on duty.", ReturnName(playerid));
							SetPlayerHealth(playerid, 100.0);

		                    PlayerData[playerid][pDutyTime] = 3600;
		                }
		                else
		                {
		                    PlayerData[playerid][pOnDuty] = false;
		                    SetPlayerArmour(playerid, 0.0);

		                    SetPlayerColor(playerid, COLOR_WHITE);
		                    SetPlayerSkin(playerid, PlayerData[playerid][pSkin]);
		                    ResetWeapons(playerid);

		                    SendNearbyMessage(playerid, 20.0,X11_PLUM, "** %s has clocked out and is now off duty.", ReturnName(playerid));

							PlayerData[playerid][pDutySecond] = 0;
							PlayerData[playerid][pDutyMinute] = 0;
							PlayerData[playerid][pDutyHour] = 0;
		                }
					}
					case 1:
					{
					    SetPlayerArmour(playerid, 100.0);
					    SendNearbyMessage(playerid, 30.0,X11_PLUM, "** %s reaches into the locker and takes out a vest.", ReturnName(playerid));
					}
					case 2:
					{
						for (new i = 0; i < sizeof(skins); i ++)
						    skins[i] = (FactionData[factionid][factionSkins][i]) ? (FactionData[factionid][factionSkins][i]) : (19300);

						ShowModelSelectionMenu(playerid, "Choose Skin", MODEL_SELECTION_FACTION_SKIN, skins, sizeof(skins), -16.0, 0.0, -55.0);
					}
					case 3:
					{
					    for (new i = 0; i < 10; i ++)
						{
					        if (FactionData[factionid][factionWeapons][i])
								format(string, sizeof(string), "%sWeapon %d: %s\n", string, i + 1, ReturnWeaponName(FactionData[factionid][factionWeapons][i]));

							else format(string, sizeof(string), "%sEmpty Slot\n", string);
					    }
					    ShowPlayerDialog(playerid, DIALOG_LOCKER_WEAPON, DIALOG_STYLE_LIST, "Locker Weapons", string, "Equip", "Close");
					}
				}
		    }
		    else
		    {
		        switch (listitem)
		        {
					case 0:
					{
					    for (new i = 0; i < 10; i ++)
						{
					        if (FactionData[factionid][factionWeapons][i] && GetFactionType(playerid) != FACTION_FAMILY)
								format(string, sizeof(string), "%sWeapon %d: %s\n", string, i + 1, ReturnWeaponName(FactionData[factionid][factionWeapons][i]));

							else if (FactionData[factionid][factionWeapons][i] && GetFactionType(playerid) == FACTION_FAMILY)
								format(string, sizeof(string), "%s[%d] : %s (%d ammo) (%d durability)\n", string, i + 1, ReturnWeaponName(FactionData[factionid][factionWeapons][i]), FactionData[factionid][factionAmmo][i], FactionData[factionid][factionDurability][i]);

							else format(string, sizeof(string), "%sEmpty Slot\n", string);
					    }
					    ShowPlayerDialog(playerid, DIALOG_LOCKER_WEAPON, DIALOG_STYLE_LIST, "Locker Weapons", string, "Equip", "Close");
					}
					case 1:
					{
						/*new count = false; kelarin 2
						forex(i, MAX_FACTION_VEHICLE) if(FactionVehicle[i][fvFaction] == PlayerData[playerid][pFactionID])
						{
							if(IsValidVehicle(FactionVehicle[i][fvVehicle]))
								SetVehicleToRespawn(FactionVehicle[i][fvVehicle]);

							VehicleData[FactionVehicle[i][fvVehicle]][vFuel] = 100;

							count = true;
						}
						if(count)
							SendFactionMessage(PlayerData[playerid][pFaction], COLOR_SERVER, "FACTION (Vehicle) {FFFFFF}%s faction vehicle has been respawned by {FFFF00}%s", FactionData[factionid][factionName], ReturnName(playerid));
						else
							SendErrorMessage(playerid, "Your faction doesn't have faction vehicle!");*/
					}
				}
		    }
		}
	}
	if(dialogid == DIALOG_EDITRANK_NAME)
	{
		new str[256];
		if (response)
		{
		    if (isnull(inputtext))
				return format(str, sizeof(str), "Rank: %s (%d)\n\nPlease enter a new name for this rank below:", FactionRanks[PlayerData[playerid][pFactionEdit]][PlayerData[playerid][pSelectedSlot]], PlayerData[playerid][pSelectedSlot] + 1), 
						ShowPlayerDialog(playerid, DIALOG_EDITRANK_NAME, DIALOG_STYLE_INPUT, "Set Rank Name", str, "Submit", "Close");

		    if (strlen(inputtext) > 32)
		        return format(str, sizeof(str), "Rank: %s (%d)\n\nPlease enter a new name for this rank below:", FactionRanks[PlayerData[playerid][pFactionEdit]][PlayerData[playerid][pSelectedSlot]], PlayerData[playerid][pSelectedSlot] + 1), 
						ShowPlayerDialog(playerid, DIALOG_EDITRANK_NAME, DIALOG_STYLE_INPUT, "Set Rank Name", str, "Submit", "Close");

			format(FactionRanks[PlayerData[playerid][pFactionEdit]][PlayerData[playerid][pSelectedSlot]], 32, inputtext);
			Faction_SaveRanks(PlayerData[playerid][pFactionEdit]);

			Faction_ShowRanks(playerid, PlayerData[playerid][pFactionEdit]);
			SendServerMessage(playerid, "You have set the name of rank %d to \"%s\".", PlayerData[playerid][pSelectedSlot] + 1, inputtext);
		}
		else Faction_ShowRanks(playerid, PlayerData[playerid][pFactionEdit]);
	}
	if(dialogid == DIALOG_EDITFACTION_SALARY_LIST)
	{
		if (response)
		{
		    if (!FactionData[PlayerData[playerid][pFactionEdit]][factionExists])
				return 0;

			PlayerData[playerid][pListitem] = listitem;
			new str[256];
			format(str, sizeof(str), "Please enter new salary for rank %d below:", PlayerData[playerid][pListitem] + 1);
			ShowPlayerDialog(playerid, DIALOG_EDITFACTION_SALARY_SET, DIALOG_STYLE_INPUT, "Set Rank Salary", str, "Submit", "Close");
		}
	}			
	if(dialogid == DIALOG_EDITFACTION_SALARY_SET)
	{
		if(response)
		{
			new id = PlayerData[playerid][pFactionEdit], slot = PlayerData[playerid][pListitem], str[256];
			if(isnull(inputtext))
				return format(str, sizeof(str), "Please enter new salary for rank %d below:", PlayerData[playerid][pListitem] + 1),
						ShowPlayerDialog(playerid, DIALOG_EDITFACTION_SALARY_SET, DIALOG_STYLE_INPUT, "Set Rank Salary", str, "Submit", "Close");

			FactionData[id][factionSalary][slot] = strcash(inputtext);
			Faction_Save(id);
			SendServerMessage(playerid, "You have set salary for rank %d to $%s", slot + 1, FormatNumber(strcash(inputtext)));
		}
	}
	if(dialogid == DIALOG_EDITRANK)
	{
		if (response)
		{
		    if (!FactionData[PlayerData[playerid][pFactionEdit]][factionExists])
				return 0;

			PlayerData[playerid][pSelectedSlot] = listitem;
			new str[256];
			format(str, sizeof(str), "Rank: %s (%d)\n\nPlease enter a new name for this rank below:", FactionRanks[PlayerData[playerid][pFactionEdit]][PlayerData[playerid][pSelectedSlot]], PlayerData[playerid][pSelectedSlot] + 1);
			ShowPlayerDialog(playerid, DIALOG_EDITRANK_NAME, DIALOG_STYLE_INPUT, "Set Rank Name", str, "Submit", "Close");
		}
	}
	if(dialogid == DIALOG_TUNE) {

		if (response)
		{
			new modelid = GetVehicleModel(PlayerData[playerid][pVehicle]);

			switch (modelid)
			{
				case 534 .. 536, 558 .. 562, 565, 567, 575, 576:
				{
					if (!strcmp(inputtext, "Wheels") || !strcmp(inputtext, "Hydraulics"))
					{
						new Query[99];
						
						mysql_format(sqlcon, Query, sizeof Query, "SELECT componentid,type FROM vehicle_components WHERE part='%e' ORDER BY type", inputtext);
						mysql_tquery(sqlcon, Query, "OnTuneLoad", "ii", playerid, 2);
					}
					else
					{
						new Query[113];
						
						mysql_format(sqlcon, Query, sizeof Query, "SELECT componentid,type FROM vehicle_components WHERE cars=%i AND part='%e' ORDER BY type", modelid, inputtext);
						mysql_tquery(sqlcon, Query, "OnTuneLoad", "ii", playerid, 2);
					}
				}
				default:
				{
					new Query[101];
					
					mysql_format(sqlcon, Query, sizeof Query, "SELECT componentid,type FROM vehicle_components WHERE cars<=0 AND part='%e' ORDER BY type", inputtext);
					mysql_tquery(sqlcon, Query, "OnTuneLoad", "ii", playerid, 2);
				}
			}
		}
	}
	if(dialogid == DIALOG_TUNE_2)
	{
		if(!response)
			return 0;

		new vehicleid = PlayerData[playerid][pVehicle], componentid;
		
		if(!IsValidVehicle(vehicleid))
			return SendErrorMessage(playerid, "Vehicle no longer valid.");
			
		if (!sscanf(inputtext, "i", componentid)) {
			AddVehicleComponent(vehicleid, componentid);
		}
		
		switch (componentid)
		{
			case 1007, 1027, 1030, 1039, 1040, 1051, 1052, 1062, 1063, 1071, 1072, 1094, 1099, 1101, 1102, 1107, 1120, 1121, 1124, 1137, 1142 .. 1145: AddVehicleComponent(vehicleid, componentid);
		}
		SaveVehicleComponent(vehicleid, componentid);
		PlayerPlaySound(playerid,1133,0.0,0.0,0.0);

		if(PlayerData[playerid][pAdmin] <  6 && !PlayerData[playerid][pAduty])
			Inventory_Remove(playerid, "Component", 50);

		ShowMechanicMenuInfo(playerid);
	}
	if(dialogid == DIALOG_PAINTJOB) {
		if (response)
		{
			new paintjobid, vehicleid = PlayerData[playerid][pVehicle];
		
			if(!IsValidVehicle(vehicleid))
				return SendErrorMessage(playerid, "Vehicle no longer valid!");

			if (!sscanf(inputtext, "'Paintjob ID:'i", paintjobid)) {
				ChangeVehiclePaintjob(vehicleid, paintjobid);
				VehicleData[vehicleid][vPaintjob] = paintjobid;
			}
			else {
				ChangeVehiclePaintjob(vehicleid, 3);
				VehicleData[vehicleid][vPaintjob] = -1;
			}

			if(PlayerData[playerid][pAdmin] <  6 && !PlayerData[playerid][pAduty])
				Inventory_Remove(playerid, "Component", 30);

			PlayerPlaySound(playerid, 1133, 0.0,0.0,0.0);
			ShowMechanicMenuInfo(playerid);
		}
	}
	if(dialogid == DIALOG_MM)
	{
		if(response)
		{
		    new vehicleid = PlayerData[playerid][pVehicle];
		    
		    if(listitem == 0)
      		{
		        if(GetComponent(playerid) < PlayerData[playerid][pMechPrice][0])
					return SendErrorMessage(playerid, "Kamu tidak memiliki cukup komponen.");

		        if(VehicleData[vehicleid][vRepair])
		            return SendErrorMessage(playerid, "This vehicle is being repaired!");
		            

				if(PlayerData[playerid][pMechPrice][0] < 1)
				    return SendErrorMessage(playerid, "This Vehicle doesn't need to repaired!");
				    
				if(PlayerData[playerid][pAdmin] <  6 && !PlayerData[playerid][pAduty])
					Inventory_Remove(playerid, "Component", PlayerData[playerid][pMechPrice][0]);

		        SetTimerEx("TimeRepairEngine", 10000, false, "dd", playerid, vehicleid);
		        StartPlayerLoadingBar(playerid, 10, "Repairing_Engine", 1000);
				SendClientMessage(playerid, COLOR_SERVER, "(Info) {FFFFFF}Kamu sedang memperbaiki mesin kendaraan, harap tunggu.");
				VehicleData[vehicleid][vRepair] = true;
			}
 		    if(listitem == 1)
		    {
		        if(GetComponent(playerid) < PlayerData[playerid][pMechPrice][1])
		            return SendErrorMessage(playerid, "Kamu tidak memiliki cukup komponen.");
		            
		        if(VehicleData[vehicleid][vRepair])
		            return SendErrorMessage(playerid, "This vehicle is being repaired!");
		            
				if(PlayerData[playerid][pAdmin] <  6 && !PlayerData[playerid][pAduty])
					Inventory_Remove(playerid, "Component", PlayerData[playerid][pMechPrice][1]);
		        
				SetTimerEx("TimeRepairBody", 10000, false, "dd", playerid, vehicleid);
		        StartPlayerLoadingBar(playerid, 10, "Repairing_Body", 1000);
				SendClientMessage(playerid, COLOR_SERVER, "(Info) {FFFFFF}Kamu sedang memperbaiki body kendaraan, harap tunggu.");
				VehicleData[vehicleid][vRepair] = true;
			}
 		    if(listitem == 2)
			{
		        if(GetComponent(playerid) < 15)
		            return SendErrorMessage(playerid, "Kamu tidak memiliki cukup komponen.");

		        if(VehicleData[vehicleid][vRepair])
		            return SendErrorMessage(playerid, "This vehicle is being repaired!");
		            
				if(PlayerData[playerid][pAdmin] <  6 && !PlayerData[playerid][pAduty])
					Inventory_Remove(playerid, "Component", 15);

		        SetTimerEx("TimeRepairTire", 10000, false, "dd", playerid, vehicleid);
		        StartPlayerLoadingBar(playerid, 10, "Repairing_Tires", 1000);
				SendClientMessage(playerid, COLOR_SERVER, "(Info) {FFFFFF}Kamu sedang memperbaiki ban kendaraan, harap tunggu.");
				VehicleData[vehicleid][vRepair] = true;
			}
			if(listitem == 3)
			{

			    if(GetComponent(playerid) < 30)
			        return SendErrorMessage(playerid, "Kamu tidak memiliki cukup komponen.");

				if(Vehicle_GetType(vehicleid) != VEHICLE_TYPE_PLAYER)
					return SendErrorMessage(playerid, "Hanya kendaraan player yang dapat dimodifikasi!");

				static
			 		colors[256];

				for (new i = 0; i < sizeof(colors); i ++)
				{
					colors[i] = i;
			   	}
			   	ShowColorSelectionMenu(playerid, MODEL_SELECTION_COLOR_1, colors);

				SendClientMessage(playerid, X11_LIGHTBLUE, "(Mechanic) "WHITE"Silahkan pilih warna pertama terlebih dahulu.");
			}
			if(listitem == 4) {
			    if(GetComponent(playerid) < 50)
			        return SendErrorMessage(playerid, "Kamu tidak memiliki cukup komponen.");

	 		    if (!IsDoorVehicle(vehicleid))
			        return SendErrorMessage(playerid, "Kendaraan ini tidak bisa dimodifikasi.");

				if(Vehicle_GetType(vehicleid) != VEHICLE_TYPE_PLAYER)
					return SendErrorMessage(playerid, "Hanya kendaraan player yang dapat dimodifikasi!");

				new
					modelid = GetVehicleModel(vehicleid);

				switch (modelid)
				{
					case 534 .. 536, 558 .. 562, 565, 567, 575, 576:
					{
						new Query[76];
						mysql_format(sqlcon, Query, sizeof Query, "SELECT part FROM vehicle_components WHERE cars=%i OR cars=-1 GROUP BY part", modelid);
						mysql_tquery(sqlcon, Query, "OnTuneLoad", "ii", playerid, 0);
					}
					default:
					{
						static Query[354];
						
						mysql_format(sqlcon, Query, sizeof Query,
						"SELECT " \
						"IF(parts & 1 <> 0,'Exhausts','')," \
						"IF(parts & 2 <> 0,'Hood','')," \
						"IF(parts & 4 <> 0,'Hydraulics','')," \
						"IF(parts & 8 <> 0,'Lights','')," \
						"IF(parts & 16 <> 0,'Roof','')," \
						"IF(parts & 32 <> 0,'Side Skirts','')," \
						"IF(parts & 64 <> 0,'Spoilers','')," \
						"IF(parts & 128 <> 0,'Vents','')," \
						"IF(parts & 256 <> 0,'Wheels','') " \
						"FROM vehicle_model_parts WHERE modelid=%i", modelid);
						mysql_tquery(sqlcon, Query, "OnTuneLoad", "ii", playerid, 1);
					}
				}
			}
			if(listitem == 5) {

			    if(GetComponent(playerid) < 50)
			        return SendErrorMessage(playerid, "Kamu tidak memiliki cukup komponen.");

				if(Vehicle_GetType(vehicleid) != VEHICLE_TYPE_PLAYER)
					return SendErrorMessage(playerid, "Hanya kendaraan player yang dapat dimodifikasi!");

				new modelid = GetVehicleModel(vehicleid);

				switch (modelid)
				{
					case 483: ShowPlayerDialog(playerid, DIALOG_PAINTJOB, DIALOG_STYLE_LIST, "Available Paintjobs", "Paintjob ID: 0\nRemove Paintjob", "Select", "Cancel");
					case 575: ShowPlayerDialog(playerid, DIALOG_PAINTJOB, DIALOG_STYLE_LIST, "Available Paintjobs", "Paintjob ID: 0\nPaintjob ID: 1\nRemove Paintjob", "Select", "Cancel");
					case 534 .. 536, 558 .. 562, 565, 567, 576: ShowPlayerDialog(playerid, DIALOG_PAINTJOB, DIALOG_STYLE_LIST, "Available Paintjobs", "Paintjob ID: 0\nPaintjob ID: 1\nPaintjob ID: 2\nRemove Paintjob", "Select", "Cancel");
					default: SendErrorMessage(playerid, "Kendaraan ini tidak bisa dimodifikasi.");
				}
			}
			if(listitem == 6) {

			    if(GetComponent(playerid) < 150)
			        return SendErrorMessage(playerid, "Kamu tidak memiliki cukup komponen.");

				if(!IsValidVehicle(vehicleid))
					return SendErrorMessage(playerid, "Vehicle no longer valid.");

				if(GetVehicleComponentInSlot(vehicleid, CARMODTYPE_NITRO) == 1010)
					return SendErrorMessage(playerid, "Kendaraan ini sudah terinstall nitro.");

				if(!IsFourWheelVehicle(vehicleid))
					return SendErrorMessage(playerid, "Kendaraan ini tidak bisa dipasangi Nitro.");

				if(Vehicle_GetType(vehicleid) != VEHICLE_TYPE_PLAYER)
					return SendErrorMessage(playerid, "Hanya kendaraan player yang dapat dimodifikasi!");

				AddVehicleComponent(vehicleid, 1010);
				SaveVehicleComponent(vehicleid, 1010);
				PlayerPlaySound(playerid, 1133, 0.0,0.0,0.0);
				SendServerMessage(playerid, "Kamu berhasil menginstall nitro pada kendaraan %s.", GetVehicleName(vehicleid));
				
				if(PlayerData[playerid][pAdmin] <  6 && !PlayerData[playerid][pAduty])
					Inventory_Remove(playerid, "Component", 150);

				ShowMechanicMenuInfo(playerid);
			}
			if(listitem == 7) {


				new comp_count = 0,
					count = 0,
					str[512];

				if(!IsValidVehicle(vehicleid))
					return SendErrorMessage(playerid, "Vehicle no longer valid.");

				if(!IsFourWheelVehicle(vehicleid))
					return SendErrorMessage(playerid, "Tidak ada modifikasi pada kendaraan ini.");

				if(Vehicle_GetType(vehicleid) != VEHICLE_TYPE_PLAYER)
					return SendErrorMessage(playerid, "Hanya kendaraan player yang dapat dimodifikasi!");

				for(new i = 0; i < 17; i++) if(VehicleData[vehicleid][vMod][i] != 0) {
					count++;
				}

				if(!count) 
					return SendErrorMessage(playerid, "Tidak ada modifikasi terpasang pada kendaraan %s ini.", GetVehicleName(vehicleid));

				strcat(str, "Index\tComponent ID\tComponent Name\n");
				for(new i = 0; i < 17; i++) if(VehicleData[vehicleid][vMod][i] != 0) {

					new comp_name[64];
					GetVehicleComponentName(VehicleData[vehicleid][vMod][i], comp_name, 64);
					strcat(str, sprintf(""BLACK"%d\t"WHITE"%d\t%s\n", i, VehicleData[vehicleid][vMod][i], comp_name));
					g_ListedComponent[playerid][comp_count++] = VehicleData[vehicleid][vMod][i];
				}
				ShowPlayerDialog(playerid, DIALOG_REMOVEMOD, DIALOG_STYLE_TABLIST_HEADERS, "Uninstall Modification", str, "Remove", "Close");
			}
			if(listitem == 8) {
			    if(GetComponent(playerid) < 350)
			        return SendErrorMessage(playerid, "Kamu tidak memiliki cukup komponen.");

				if(!IsValidVehicle(vehicleid))
					return SendErrorMessage(playerid, "Vehicle no longer valid.");	

				if(VehicleData[vehicleid][vEngineUpgrade])
					return SendErrorMessage(playerid, "Mesin kendaraan ini sudah ter-upgrade!");

				if(Vehicle_GetType(vehicleid) != VEHICLE_TYPE_PLAYER)
					return SendErrorMessage(playerid, "Hanya kendaraan player yang dapat dimodifikasi!");

				if(PlayerData[playerid][pAdmin] <  6 && !PlayerData[playerid][pAduty])
					Inventory_Remove(playerid, "Component", 350);

				Vehicle_SetEngineLevel(vehicleid, 1);
				SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Mechanic) "WHITE"Mesin kendaraan "YELLOW"%s"WHITE" berhasil di "RED"upgrade"WHITE"!", GetVehicleName(vehicleid));	
				ShowMechanicMenuInfo(playerid);
			}
			if(listitem == 9) {
			    if(GetComponent(playerid) < 350)
			        return SendErrorMessage(playerid, "Kamu tidak memiliki cukup komponen.");

				if(!IsValidVehicle(vehicleid))
					return SendErrorMessage(playerid, "Vehicle no longer valid.");	

				if(VehicleData[vehicleid][vBodyUpgrade])
					return SendErrorMessage(playerid, "Body kendaraan ini sudah ter-upgrade!");

				if(Vehicle_GetType(vehicleid) != VEHICLE_TYPE_PLAYER)
					return SendErrorMessage(playerid, "Hanya kendaraan player yang dapat dimodifikasi!");

				if(PlayerData[playerid][pAdmin] <  6 && !PlayerData[playerid][pAduty])
					Inventory_Remove(playerid, "Component", 350);

				Vehicle_SetBodyLevel(vehicleid, 1);
				SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Mechanic) "WHITE"Body kendaraan "YELLOW"%s"WHITE" berhasil di "RED"upgrade"WHITE"!", GetVehicleName(vehicleid));
				ShowMechanicMenuInfo(playerid);
			}
			if(listitem == 10) {
				
			    if(GetComponent(playerid) < 200)
			        return SendErrorMessage(playerid, "Kamu tidak memiliki cukup komponen.");

				if(!IsValidVehicle(vehicleid))
					return SendErrorMessage(playerid, "Vehicle no longer valid.");

				if(!IsVehicleSupportsNeonLights(GetVehicleModel(vehicleid)))	
					return SendErrorMessage(playerid, "Kendaraan ini tidak bisa dipasangi Neon.");

				if(Vehicle_GetType(vehicleid) != VEHICLE_TYPE_PLAYER)
					return SendErrorMessage(playerid, "Hanya kendaraan player yang dapat dimodifikasi!");

				ShowPlayerDialog(playerid, DIALOG_SELECT_NEON, DIALOG_STYLE_LIST, "Select Neon...", "Red\nBlue\nGreen\nYellow\nPink\n"RED"Remove neon", "Install", "Close");
			}
		}
	}
	if(dialogid == DIALOG_REMOVEMOD) {
		if(response) {
			new component_id = g_ListedComponent[playerid][listitem],
				vehicleid = PlayerData[playerid][pVehicle],
				comp_name[64];

			if(!IsValidVehicle(vehicleid))
				return SendErrorMessage(playerid, "Vehicle is no longer valid.");

			GetVehicleComponentName(component_id, comp_name, 64);
			PlayerPlaySound(playerid, 1133, 0.0,0.0,0.0);
			RemoveVehicleComponent(vehicleid, component_id);
			SendServerMessage(playerid, "Kamu telah menghapus modifikasi %s dari kendaraan %s.", comp_name, GetVehicleName(vehicleid));

			for(new i = 0; i < 17; i++) if(VehicleData[vehicleid][vMod][i] == component_id) {
				VehicleData[vehicleid][vMod][i] = 0;
				break;
			}

			ShowMechanicMenuInfo(playerid);
		}
	}
	if(dialogid == DIALOG_SELECT_NEON) {
		if(response) {
			new neon = VEHICLE_NEON_NONE,
				vehicleid = PlayerData[playerid][pVehicle];

			switch(listitem) {
				case 0: neon = VEHICLE_NEON_RED;
				case 1: neon = VEHICLE_NEON_BLUE;
				case 2: neon = VEHICLE_NEON_GREEN;
				case 3: neon = VEHICLE_NEON_YELLOW;
				case 4: neon = VEHICLE_NEON_PINK;
				case 5: neon = VEHICLE_NEON_NONE;
				default: neon = VEHICLE_NEON_NONE;
			}

			if(neon != VEHICLE_NEON_NONE) {

				VehicleData[vehicleid][vNeonColor] = neon;
				Vehicle_SetNeon(vehicleid, true, VehicleData[vehicleid][vNeonColor], 0);
				Vehicle_SetNeon(vehicleid, true, VehicleData[vehicleid][vNeonColor], 1);
				Vehicle_SetNeon(vehicleid, true, VehicleData[vehicleid][vNeonColor], 2);
				SendServerMessage(playerid, "Neon berhasil dipasang pada kendaraan %s.", GetVehicleName(vehicleid));

				if(PlayerData[playerid][pAdmin] <  6 && !PlayerData[playerid][pAduty])
					Inventory_Remove(playerid, "Component", 200);

				Streamer_Update(playerid, STREAMER_TYPE_OBJECT);

				VehicleData[vehicleid][vNeonStatus] = true;
			}
			else {
				SendServerMessage(playerid, "Kamu berhasil menghapus Neon pada kendaraan %s.", GetVehicleName(vehicleid));
				VehicleData[vehicleid][vNeonColor] = neon;
				Vehicle_SetNeon(vehicleid, false, VehicleData[vehicleid][vNeonColor], 0);
				Vehicle_SetNeon(vehicleid, false, VehicleData[vehicleid][vNeonColor], 1);
				Vehicle_SetNeon(vehicleid, false, VehicleData[vehicleid][vNeonColor], 2);

				Streamer_Update(playerid, STREAMER_TYPE_OBJECT);

				VehicleData[vehicleid][vNeonStatus] = false;
			}

			Vehicle_Save(vehicleid);
			ShowMechanicMenuInfo(playerid);
		}
	}
	if(dialogid == DIALOG_TUNE_RIMS) {
		if(!response)
			return 0;

		new model = g_WheelData[listitem][wheelModel],
			vehicleid = PlayerData[playerid][pVehicle];

		if(!IsValidVehicle(vehicleid))
			return SendErrorMessage(playerid, "Kendaraan tidak lagi valid.");
		
		if(GetNearestVehicle(playerid, 5.0) != vehicleid)
			return SendErrorMessage(playerid, "Kamu tidak lagi dekat dengan kendaraan tersebut.");

		SendServerMessage(playerid, "Berhasil mengubah rims kendaraan %s menjadi "YELLOW"%s", GetVehicleName(vehicleid), g_WheelData[listitem][wheelName]);
		
		if(PlayerData[playerid][pAdmin] <  6 && !PlayerData[playerid][pAduty])
			Inventory_Remove(playerid, "Component", 100);
	    
		ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 0, 0, 0, 0, 0, 1);
	    PlayerPlaySound(playerid, 1133, 0.0,0.0,0.0);
		AddVehicleComponent(vehicleid, model);
		SaveVehicleComponent(vehicleid, model);
		ShowMechanicMenuInfo(playerid);
	}
	if(dialogid == DIALOG_BUYINSU)
	{
		if(response)
		{
			new price, i = g_ListedVehicle[playerid][listitem];

			if(VehicleData[i][vInsurance] >= 3)
				return SendErrorMessage(playerid, "This vehicle already have full of Insurances!");

			price = GetInsuPrice(VehicleData[i][vModel]);
			if(GetMoney(playerid) < price)
				return SendErrorMessage(playerid, "You don't have enough money!");

			VehicleData[i][vInsurance]++;
			GiveMoney(playerid, -price, "Beli insurance");
			SendClientMessageEx(playerid, COLOR_SERVER, "(Insurance) {FFFFFF}You've successfully purchase insurance for {FFFF00}%s", ReturnVehicleModelName(VehicleData[i][vModel]));
		}
	}
	if(dialogid == DIALOG_CLAIMINSU)
	{
		if(response)
		{
			new
				index = random(sizeof(Random_Insu)),
				id = g_Selected_Vehicle_ID[playerid][listitem],
				claim_time = g_Selected_Vehicle_Time[playerid][listitem],
				modelid = g_Selected_Vehicle_Model[playerid][listitem];

			if(gettime() < claim_time)
				return SendErrorMessage(playerid, "Kendaraan ini belum bisa di claim.");

			new str[256];
			mysql_format(sqlcon, str, sizeof(str), "UPDATE `vehicle` SET `vehState` = '%d', `vehHealth` = '1000.0', `vehDamage1` = '0', `vehDamage2` = '0', `vehDamage3` = '0', `vehDamage4` = '0', `vehInsuTime` = 0, `vehInterior` = 0, `vehWorld` = 0 WHERE `vehID` = '%d'", VEHICLE_STATE_SPAWNED, id);
			mysql_tquery(sqlcon, str);

			if(Model_GetCategory(modelid) == CATEGORY_BOAT) mysql_tquery(sqlcon, sprintf("UPDATE `vehicle` SET `vehX`='-2159.7329',`vehY`='1394.8224',`vehZ`='-0.2678',`vehA`='352.7794' WHERE `vehID`='%d';", id));
			else mysql_tquery(sqlcon, sprintf("UPDATE `vehicle` SET `vehX`='%.2f',`vehY`='%.2f',`vehZ`='%.2f',`vehA`='%.2f' WHERE `vehID`='%d';", Random_Insu[index][0], Random_Insu[index][1], Random_Insu[index][2], Random_Insu[index][3], id));
			
			mysql_tquery(sqlcon, sprintf("SELECT * FROM `vehicle` WHERE `vehID`='%d';", id), "OnVehicleLoaded", "");

			SendServerMessage(playerid, "You have claimed your "YELLOW"%s "WHITE"from insurance center.", inputtext);
		}
	}
	if(dialogid == DIALOG_FORCEINSURANCE)
	{
		if(response)
		{
			new
				index = random(sizeof(Random_Insu)),
				id = g_Selected_Vehicle_ID[playerid][listitem],
				targetid = PlayerData[playerid][pTarget],
				modelid = g_Selected_Vehicle_Model[playerid][listitem];

			new str[256];
			mysql_format(sqlcon, str, sizeof(str), "UPDATE `vehicle` SET `vehState` = '%d', `vehHealth` = '1000.0', `vehDamage1` = '0', `vehDamage2` = '0', `vehDamage3` = '0', `vehDamage4` = '0', `vehInsuTime` = 0, `vehInterior` = 0, `vehWorld` = 0 WHERE `vehID` = '%d'", VEHICLE_STATE_SPAWNED, id);
			mysql_tquery(sqlcon, str);

			if(Model_GetCategory(modelid) == CATEGORY_BOAT) mysql_tquery(sqlcon, sprintf("UPDATE `vehicle` SET `vehX`='-2159.7329',`vehY`='1394.8224',`vehZ`='-0.2678',`vehA`='352.7794' WHERE `vehID`='%d';", id));
			else mysql_tquery(sqlcon, sprintf("UPDATE `vehicle` SET `vehX`='%.2f',`vehY`='%.2f',`vehZ`='%.2f',`vehA`='%.2f' WHERE `vehID`='%d';", Random_Insu[index][0], Random_Insu[index][1], Random_Insu[index][2], Random_Insu[index][3], id));

			mysql_tquery(sqlcon, sprintf("SELECT * FROM `vehicle` WHERE `vehID`='%d';", id), "OnVehicleLoaded", "");

			SendAdminMessage(COLOR_LIGHTRED, "AdmCmd: %s has forced insurance %s's vehicle.", GetUsername(playerid), GetName(targetid, false));
			SendServerMessage(targetid, "%s telah mengeluarkan kendaraanmu dari asuransi.", GetUsername(playerid));
		}
	}
	if(dialogid == DIALOG_PICKITEM)
	{
		static
		    string[64];

		if (response)
		{
		    new id = NearestItems[playerid][listitem];

			if (id != -1 && DroppedItems[id][droppedModel])
			{

				if(PickupItem(playerid, id))
				{
					format(string, sizeof(string), "~g~%s~w~ added to inventory!", DroppedItems[id][droppedItem]);
	 				ShowMessage(playerid, string, 2);
					SendNearbyMessage(playerid, 30.0,X11_PLUM, "** %s has picked up a \"%s\".", ReturnName(playerid), DroppedItems[id][droppedItem]);
				}
				else
					SendErrorMessage(playerid, "You don't have any slot in your inventory.");
			}
			else SendErrorMessage(playerid, "This item was already picked up.");
		}
	}
	if(dialogid == DIALOG_GPS_TRACK)
	{
		new Float:pos[3];
		if(response)
		{
			new i = g_ListedVehicle[playerid][listitem];
			
			PlayerData[playerid][pTracking] = true;
			GetVehiclePos(i, pos[0], pos[1], pos[2]);
			SetWaypoint(playerid, pos[0], pos[1], pos[2], 4.0);
			SendClientMessageEx(playerid, COLOR_SERVER, "(GPS) {FFFFFF}Your {FFFF00}%s {FFFFFF}has been marked on radar (%s)", GetVehicleName(i), GetLocation(pos[0], pos[1], pos[2]));
		}
	}
	if(dialogid == DIALOG_GPS_CARGO) {
		if(response) {

			SetWaypoint(playerid, CargoLoc[listitem][cargoX], CargoLoc[listitem][cargoY], CargoLoc[listitem][cargoZ], 3.0);
			SendClientMessageEx(playerid, X11_LIGHTBLUE, "(GPS) {FFFFFF}Cargo "RED"%s {FFFFFF}located at your radar.", CargoLoc[listitem][cargoType]);
		}
	}
	if(dialogid == DIALOG_GPS)
	{
		if(response)
		{
			if(listitem == 0) SendClientMessageEx(playerid, X11_LIGHTBLUE, "(GPS) {FFFFFF}Your current location is now on {00FFFF}%s", GetSpecificLocation(playerid));
			if(listitem == 1) ShowPublicLocation(playerid);
			if(listitem == 2) ShowJobLocation(playerid);
			if(listitem == 3) ShowVehicleLocation(playerid);
			if(listitem == 4) ShowBusinessLocation(playerid);
			if(listitem == 5) ShowDealerLocation(playerid);
			if(listitem == 6)
			{
				if(!CheckPlayerJob(playerid, JOB_LUMBERJACK))
					return SendErrorMessage(playerid, "Kamu bukan seorang Lumberjack!"), cmd_gps(playerid, "");

				ShowTreeLocation(playerid);
			}
			if(listitem == 7) {
				if(!CheckPlayerJob(playerid, JOB_TRUCKER))
					return SendErrorMessage(playerid, "Kamu bukan seorang Trucker!"), cmd_gps(playerid, "");

				new str[156];
				for(new i = 0; i < sizeof(CargoLoc); i++) {
					strcat(str, sprintf("%d). %s\n", i + 1, CargoLoc[i][cargoType]));
				}
				ShowPlayerDialog(playerid, DIALOG_GPS_CARGO, DIALOG_STYLE_LIST, "Cargo Location", str, "Select", "Close");
			}
			if(listitem == 8) ShowGarageLocation(playerid);
			if(listitem == 9) ShowWorkshopLocation(playerid);
		}
	}
	if(dialogid == DIALOG_TAKEJOB2)
	{
		if(response)
		{
			PlayerData[playerid][pJobSelect] = listitem + 1;

			new str[256];
			format(str, sizeof(str), "{FFFFFF}Tekan {00FF00}Confirm {FFFFFF}untuk mengambil job {FFFF00}%s", GetJobName(PlayerData[playerid][pJobSelect]));
			ShowPlayerDialog(playerid, DIALOG_CONFIRMJOB2, DIALOG_STYLE_MSGBOX, "Job Confirmation", str, "Confirm", "Close");
		}
	}
	if(dialogid == DIALOG_TAKEJOB)
	{
		if(response)
		{
			PlayerData[playerid][pJobSelect] = listitem + 1;

			new str[256];
			format(str, sizeof(str), "{FFFFFF}Tekan {00FF00}Confirm {FFFFFF}untuk mengambil job {FFFF00}%s", GetJobName(PlayerData[playerid][pJobSelect]));
			ShowPlayerDialog(playerid, DIALOG_CONFIRMJOB, DIALOG_STYLE_MSGBOX, "Job Confirmation", str, "Confirm", "Close");
		}
	}
	if(dialogid == DIALOG_CONFIRMJOB2)
	{
		if(response)
		{
			PlayerData[playerid][pJob2] = PlayerData[playerid][pJobSelect];
			PlayerData[playerid][pQuitjob] = 2;
			SendServerMessage(playerid, "Kamu sekarang adalah "YELLOW"%s "WHITE"- gunakan "YELLOW"\"/help > Job Commands > %s\" "WHITE"untuk bantuan.", GetJobName(PlayerData[playerid][pJob2]), GetJobName(PlayerData[playerid][pJob2]));

			PlayerData[playerid][pJobSelect] = JOB_NONE;
		}
		else 
		{
			PlayerData[playerid][pJobSelect] = JOB_NONE;
		}
	}
	if(dialogid == DIALOG_CONFIRMJOB)
	{
		if(response)
		{
			PlayerData[playerid][pJob] = PlayerData[playerid][pJobSelect];
			PlayerData[playerid][pQuitjob] = 2;
			SendServerMessage(playerid, "Kamu sekarang adalah "YELLOW"%s "WHITE"- gunakan "YELLOW"\"/help > Job Commands > %s\" "WHITE"untuk bantuan.", GetJobName(PlayerData[playerid][pJob]), GetJobName(PlayerData[playerid][pJob]));

			PlayerData[playerid][pJobSelect] = JOB_NONE;
		}
		else 
		{
			PlayerData[playerid][pJobSelect] = JOB_NONE;
		}
	}
	if(dialogid == DIALOG_REFUEL)
	{

		if(!response) 
			return 0;
			
		new pump_index = PlayerData[playerid][pGasPump];
		new vehicleid = GetPlayerVehicleID(playerid),
			payment = 0,
			bizid = Pump_GetBizID(PumpData[pump_index][pumpBusiness]);

        if(!IsValidVehicle(vehicleid))
            return SendErrorMessage(playerid, "Kendaraan tidak lagi valid.");

        if(!strcmp(inputtext, "FULLTANK", true))
        {
            new total_fuel = 100 - VehicleData[vehicleid][vFuel];

            payment = total_fuel * 50;

            if(PumpData[pump_index][pumpFuel] < total_fuel)
        	    return ShowPlayerDialog(playerid, DIALOG_REFUEL, DIALOG_STYLE_INPUT, "Refuel Vehicle", ""RED"(error) tidak ada stok bahan bakar yang cukup pada fuelpump.\n"WHITE"Masukkan jumlah bahan bakar (liter) untuk mengisi kendaraan ini\nHarga per-liter nya adalah "GREEN"$0.5\n\n"GREY"(ketik \"FULLTANK\" jika ingin mengisi hingga penuh)", "Refuel", "Close");
        
            if(GetMoney(playerid) < payment)
                return ShowPlayerDialog(playerid, DIALOG_REFUEL, DIALOG_STYLE_INPUT, "Refuel Vehicle", ""RED"(error) kamu tidak memiliki cukup uang.\n"WHITE"Masukkan jumlah bahan bakar (liter) untuk mengisi kendaraan ini\nHarga per-liter nya adalah "GREEN"$0.5\n\n"GREY"(ketik \"FULLTANK\" jika ingin mengisi hingga penuh)", "Refuel", "Close");

			VehicleData[vehicleid][vFuel] = 100;
			PumpData[pump_index][pumpFuel] -= total_fuel;	
			BizData[bizid][bizVault] += payment;

			GiveMoney(playerid, -payment, "Beli bensin");
			Pump_Save(pump_index);
			Pump_Sync(pump_index);
			Business_Save(bizid);

			SendServerMessage(playerid, "Berhasil mengisi bahan bakar sebanyak "YELLOW"%d liter "WHITE" dengan harga "GREEN"$%s.", total_fuel, FormatNumber(payment));
        }
        else 
        {
            payment = (strval(inputtext) * 50);

            if(!(0 < strval(inputtext) <= 100))
                return ShowPlayerDialog(playerid, DIALOG_REFUEL, DIALOG_STYLE_INPUT, "Refuel Vehicle", ""RED"(error) jumlah yang anda masukan invalid.\n"WHITE"Masukkan jumlah bahan bakar (liter) untuk mengisi kendaraan ini\nHarga per-liter nya adalah "GREEN"$0.5\n\n"GREY"(ketik \"FULLTANK\" jika ingin mengisi hingga penuh)", "Refuel", "Close");

            if(PumpData[pump_index][pumpFuel] < strval(inputtext))
                return ShowPlayerDialog(playerid, DIALOG_REFUEL, DIALOG_STYLE_INPUT, "Refuel Vehicle", ""RED"(error) tidak ada stok bahan bakar yang cukup pada fuelpump.\n"WHITE"Masukkan jumlah bahan bakar (liter) untuk mengisi kendaraan ini\nHarga per-liter nya adalah "GREEN"$0.5\n\n"GREY"(ketik \"FULLTANK\" jika ingin mengisi hingga penuh)", "Refuel", "Close");

            if(GetMoney(playerid) < payment)
                return ShowPlayerDialog(playerid, DIALOG_REFUEL, DIALOG_STYLE_INPUT, "Refuel Vehicle", ""RED"(error) kamu tidak memiliki cukup uang.\n"WHITE"Masukkan jumlah bahan bakar (liter) untuk mengisi kendaraan ini\nHarga per-liter nya adalah "GREEN"$0.5\n\n"GREY"(ketik \"FULLTANK\" jika ingin mengisi hingga penuh)", "Refuel", "Close");

            if(VehicleData[vehicleid][vFuel] + strval(inputtext) > 100)
                return ShowPlayerDialog(playerid, DIALOG_REFUEL, DIALOG_STYLE_INPUT, "Refuel Vehicle", ""RED"(error) kendaraan tidak bisa menampung sebanyak itu!\n"WHITE"Masukkan jumlah bahan bakar (liter) untuk mengisi kendaraan ini\nHarga per-liter nya adalah "GREEN"$0.5\n\n"GREY"(ketik \"FULLTANK\" jika ingin mengisi hingga penuh)", "Refuel", "Close");

			VehicleData[vehicleid][vFuel] +=  strval(inputtext);
			PumpData[pump_index][pumpFuel] -=  strval(inputtext);	
			BizData[bizid][bizVault] += payment;
			
			GiveMoney(playerid, -payment, "Beli bensin");
			Pump_Save(pump_index);
			Pump_Sync(pump_index);
			Business_Save(bizid);
			SendServerMessage(playerid, "Berhasil mengisi bahan bakar sebanyak "YELLOW"%d liter "WHITE" dengan harga "GREEN"$%s.", strval(inputtext), FormatNumber(payment));
        }     
	}
	if(dialogid == DIALOG_SELLCARGO)
	{
		if(response)
		{
			new id = PlayerData[playerid][pBusiness];
			new cid = PlayerData[playerid][pCrate];

			if(BizData[id][bizVault] < BizData[id][bizCargo])
				return SendErrorMessage(playerid, "Business ini tidak memiliki cukup uang.");

			GiveMoney(playerid, BizData[id][bizCargo], "Sell cargo");
			BizData[id][bizStock] += 20;
			BizData[id][bizVault] -= BizData[id][bizCargo];
			SendClientMessageEx(playerid, COLOR_SERVER, "(Cargo) {FFFFFF}Kamu berhasil menjual {FFFF00}%s Cargo {FFFFFF}dan mendapat {00FF00}$%s", Crate_Name[CrateData[cid][crateType]], FormatNumber(BizData[id][bizCargo]));
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);		
			ApplyAnimation(playerid, "CARRY", "putdwn", 4.1, 0, 0, 0, 0, 0, 1);
			RemovePlayerAttachedObject(playerid, 9);
			Crate_Delete(cid);
			PlayerData[playerid][pCrate] = -1;
			if(BizData[id][bizStock] > 100)
			{
				BizData[id][bizStock] = 100;
			}
			Business_Save(id);
		}
	}
	if(dialogid == DIALOG_CRATE)
	{
		if(response)
		{
			new id = ListedCrate[playerid][listitem];

			SendClientMessageEx(playerid, COLOR_SERVER, "(Cargo) {FFFFFF}Kamu berhasil mengambil Cargo {FFFF00}%s {FFFFFF}dari Truck!", Crate_Name[CrateData[id][crateType]]);
			ApplyAnimation(playerid, "CARRY", "liftup", 4.1, 0, 0, 0, 0, 0, 1);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
			SetPlayerAttachedObject(playerid,  9, 1271, 5, 0.044377, 0.029049, 0.161334, 265.922912, 9.904896, 21.765972, 0.500000, 0.500000, 0.500000);
			PlayerData[playerid][pCrate] = id;	
			CrateData[id][crateVehicle] = -1;
			Crate_Save(id);
		}
	}
	if(dialogid == DIALOG_UNSTUCK) {
		if(response) {

			new vehicleid;

			vehicleid = g_ListedVehicle[playerid][listitem];

			if(vehicleid == INVALID_VEHICLE_ID)
				return SendErrorMessage(playerid, "Kendaraan ini tidak valid!");
			
			if(!IsValidVehicle(vehicleid))
				return SendErrorMessage(playerid, "Kendaraan ini tidak valid.");
				
			if(GetVehicleDriver(vehicleid) != INVALID_VEHICLE_ID)
				return SendErrorMessage(playerid, "Kendaraan tersebut sedang dikendarai!");
				

			for(new slot = 0; slot < MAX_VEHICLE_OBJECT; slot++) if(VehicleObjects[vehicleid][slot][vehObjectExists])
			{
				if(IsValidDynamicObject(VehicleObjects[vehicleid][slot][vehObject]))
					DestroyDynamicObject(VehicleObjects[vehicleid][slot][vehObject]);

				VehicleObjects[vehicleid][slot][vehObject] = INVALID_OBJECT_ID;

			}
			for(new idx = 0; idx < 3; idx++) {

				for(new i = 0; i < 2; i++) {
					if(IsValidDynamicObject(NeonObject[vehicleid][idx][i])) {
						DestroyDynamicObject(NeonObject[vehicleid][idx][i]);
						NeonObject[vehicleid][idx][i] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
					}
				}
			}

			Vehicle_GetStatus(vehicleid);

			defer UnstuckPlayerVehicle[1000](playerid, vehicleid);
		}
	}
	if(dialogid == DIALOG_LOCK)
	{
		new Float:pos[3], i = g_ListedVehicle[playerid][listitem];
		if(response)
		{
			GetVehiclePos(i, pos[0], pos[1], pos[2]);
			if(IsPlayerInRangeOfPoint(playerid, 5.0, pos[0], pos[1], pos[2]))
			{
				PlayerPlaySound(playerid, 24600, 0.0, 0.0, 0.0);
				VehicleData[i][vLocked] = !(VehicleData[i][vLocked]);
				LockVehicle(i, VehicleData[i][vLocked]);

				ShowMessage(playerid, sprintf("%s %s", GetVehicleName(i), (VehicleData[i][vLocked]) ? ("~r~Locked") : ("~g~Unlocked")), 3);
			}
			else SendErrorMessage(playerid, "Kamu tidak berada didekat kendaraan tersebut.");
		}
	}
	if(dialogid == DIALOG_BIZPRICE)
	{
	    if(response)
	    {
			new str[256];
	        PlayerData[playerid][pListitem] = listitem;
	        format(str, sizeof(str), "{FFFFFF}Current Product Price: $%s\n{FFFFFF}Silahkan masukan harga baru untuk product {00FFFF}%s", FormatNumber(BizData[PlayerData[playerid][pInBiz]][bizProduct][listitem]), ProductName[PlayerData[playerid][pInBiz]][listitem]);
	        ShowPlayerDialog(playerid, DIALOG_BIZPRICESET, DIALOG_STYLE_INPUT, "Set Product Price", str, "Set", "Close");
		}
		else
		    cmd_biz(playerid, "menu");
	}
	if(dialogid == DIALOG_BIZPROD)
	{
	    if(response)
	    {
			new str[256];
	        PlayerData[playerid][pListitem] = listitem;
	        format(str, sizeof(str), "{FFFFFF}Current Product Name: %s\n{FFFFFF}Silahkan masukan nama baru untuk product {00FFFF}%s", ProductName[PlayerData[playerid][pInBiz]][listitem], ProductName[PlayerData[playerid][pInBiz]][listitem]);
	        ShowPlayerDialog(playerid, DIALOG_BIZPRODSET, DIALOG_STYLE_INPUT, "Set Product Name", str, "Set", "Close");
		}
		else
		    cmd_biz(playerid, "menu");
	}
	if(dialogid == DIALOG_BIZPRODSET)
	{
	    if(response)
	    {
	        if(strlen(inputtext) < 1 || strlen(inputtext) > 24)
	            return SendErrorMessage(playerid, "Invalid Product name!");

			new id = PlayerData[playerid][pInBiz];
			new slot = PlayerData[playerid][pListitem];
			SendClientMessageEx(playerid, COLOR_SERVER, "(Business) {FFFFFF}Kamu telah mengubah nama product dari {00FFFF}%s {FFFFFF}menjadi {00FFFF}%s", ProductName[id][slot], inputtext);
			format(ProductName[id][slot], 24, inputtext);
			cmd_biz(playerid, "menu");
			Business_Save(id);
		}
	}
	if(dialogid == DIALOG_BIZPRICESET)
	{
	    if(response)
	    {
	        if(strcash(inputtext) < 1)
	            return SendErrorMessage(playerid, "Invalid Product price!");
	            
			new id = PlayerData[playerid][pInBiz];
			new slot = PlayerData[playerid][pListitem];
			SendClientMessageEx(playerid, COLOR_SERVER, "(Business) {FFFFFF}Kamu telah mengubah harga product dari {009000}$%s {FFFFFF}menjadi {009000}$%s", FormatNumber(BizData[id][bizProduct][slot]), FormatNumber(strcash(inputtext)));
			BizData[id][bizProduct][slot] = strcash(inputtext);
			cmd_biz(playerid, "menu");
			Business_Save(id);
		}
	}
	if(dialogid == DIALOG_BIZNAME)
	{
		if(response)
		{
			new id = PlayerData[playerid][pInBiz];

			if(strlen(inputtext) > 32)
				return SendErrorMessage(playerid, "Business name was too long!"), cmd_biz(playerid, "menu");

			format(BizData[id][bizName], 24, inputtext);
			Business_Save(id);
			Business_Refresh(id);
			SendServerMessage(playerid, "Kamu berhasil mengubah nama business menjadi %s", inputtext);
		}
	}
	if(dialogid == DIALOG_BIZMENU)
	{
	    if(response)
	    {
	    	if(listitem == 0)
	    	{
	    		ShowBizStats(playerid);
	    	}
	        if(listitem == 1)
	        {
	            SetProductName(playerid);
			}
			if(listitem == 2)
			{
			    SetProductPrice(playerid);
			}
			if(listitem == 3)
			{
				new str[256];
				format(str, sizeof(str), "{FFFFFF}Current Biz Name: %s\n{FFFFFF}Silahkan masukan nama Business mu yang baru:\n\n{FFFFFF}Note: Max 24 Huruf!", BizData[PlayerData[playerid][pInBiz]][bizName]);
				ShowPlayerDialog(playerid, DIALOG_BIZNAME, DIALOG_STYLE_INPUT, "Business Name", str, "Set", "Close");
			}
			if(listitem == 4)
			{
				new str[256];
				format(str, sizeof(str), "{FFFFFF}Current Cargo Price: {00FF00}$%s\n{FFFFFF}Silahkan masukan harga Cargo yang baru:\n\nNote: Min $30.0 Max $100.0!", FormatNumber(BizData[PlayerData[playerid][pInBiz]][bizCargo]));
				ShowPlayerDialog(playerid, DIALOG_BIZCARGO, DIALOG_STYLE_INPUT, "Business Cargo", str, "Set", "Close");
			}
			if(listitem == 5)
			{
				ShowPlayerDialog(playerid, DIALOG_BIZ_WD, DIALOG_STYLE_INPUT, "Business Withdraw", "Please input amount of vault you want to withdraw:", "Withdraw", "Close");
			}
			if(listitem == 6)
			{
				ShowPlayerDialog(playerid, DIALOG_BIZ_DP, DIALOG_STYLE_INPUT, "Business Deposit", "Please input amount of money you want to deposit:", "Deposit", "Close");
			}
			if(listitem == 7)
			{
				new str[299];
				if(BizData[PlayerData[playerid][pInBiz]][bizType] == 2)
				{
					for(new i = 0; i < 7; i++)
					{
						format(str, sizeof(str), "%s#%d.\t%s\n", str, i + 1, ProductDescription[PlayerData[playerid][pInBiz]][i]);
					}
					ShowPlayerDialog(playerid, DIALOG_BIZDESC, DIALOG_STYLE_LIST, "Description List", str, "Change", "Close");
				}
				else if(BizData[PlayerData[playerid][pInBiz]][bizType] == 4)
				{
					for(new i = 0; i < 4; i++)
					{
						format(str, sizeof(str), "%s#%d.\t%s\n", str, i + 1, ProductDescription[PlayerData[playerid][pInBiz]][i]);
					}
					ShowPlayerDialog(playerid, DIALOG_BIZDESC, DIALOG_STYLE_LIST, "Description List", str, "Change", "Close");
				}
				else
				{
					cmd_biz(playerid, "menu");
					SendErrorMessage(playerid, "This option only for 24/7 and Electronic business!");
				}
			}
		}
	}
	if(dialogid == DIALOG_BIZDESC_SET)
	{
		if(!response)
			return cmd_biz(playerid, "menu");

		if(isnull(inputtext))
			return ShowPlayerDialog(playerid, DIALOG_BIZDESC_SET, DIALOG_STYLE_INPUT, "Set Description", "Please input new product description\nNote: max 40 characters", "Set", "Close");

		if(strlen(inputtext) > 40)
			return ShowPlayerDialog(playerid, DIALOG_BIZDESC_SET, DIALOG_STYLE_INPUT, "Set Description", "Please input new product description\nNote: max 40 characters", "Set", "Close");

		format(ProductDescription[PlayerData[playerid][pInBiz]][PlayerData[playerid][pListitem]], 40, inputtext);	
		Business_Save(PlayerData[playerid][pInBiz]);
		SendServerMessage(playerid, "You have adjusted the product description!");
	}
	if(dialogid == DIALOG_BIZDESC)
	{
		if(response)
		{
			PlayerData[playerid][pListitem] = listitem;
			ShowPlayerDialog(playerid, DIALOG_BIZDESC_SET, DIALOG_STYLE_INPUT, "Set Description", "Please input new product description\nNote: max 40 characters", "Set", "Close");
		}
		else
		{
			cmd_biz(playerid, "menu");
		}
	}
	if(dialogid == DIALOG_BIZ_DP)
	{
		if(response)
		{
			new amount = strcash(inputtext), id = PlayerData[playerid][pInBiz];
			if(amount < 1)
				return ShowPlayerDialog(playerid, DIALOG_BIZ_DP, DIALOG_STYLE_INPUT, "Business Deposit", "ERROR: Invalid amount!\nPlease input amount of money you want to deposit:", "Deposit", "Close");
		
			if(GetMoney(playerid) < amount)
				return ShowPlayerDialog(playerid, DIALOG_BIZ_DP, DIALOG_STYLE_INPUT, "Business Deposit", "ERROR: You dont have enough money!\nPlease input amount of money you want to deposit:", "Deposit", "Close");
		
			BizData[id][bizVault] += amount;
			GiveMoney(playerid, -amount, "Deposit ke biz vault");
			SendServerMessage(playerid, "You have deposit {009000}$%s {FFFFFF}to business vault.", FormatNumber(amount));
			Business_Save(id);
		}
		else
		{
			cmd_biz(playerid, "menu");
		}
	}
	if(dialogid == DIALOG_BIZ_WD)
	{
		if(response)
		{
			new amount = strcash(inputtext), id = PlayerData[playerid][pInBiz];
			if(amount < 1)
				return ShowPlayerDialog(playerid, DIALOG_BIZ_WD, DIALOG_STYLE_INPUT, "Business Withdraw", "ERROR: Invalid amount!\nPlease input amount of vault you want to withdraw:", "Withdraw", "Close");
		
			if(BizData[id][bizVault] < amount)
				return ShowPlayerDialog(playerid, DIALOG_BIZ_WD, DIALOG_STYLE_INPUT, "Business Withdraw", "ERROR: Not enough money on vault!\nPlease input amount of vault you want to withdraw:", "Withdraw", "Close");
		
			BizData[id][bizVault] -= amount;
			GiveMoney(playerid, amount, "Withdraw dari biz vault");
			SendServerMessage(playerid, "You have withdrawn {009000}$%s {FFFFFF}from business vault.", FormatNumber(amount));
			Business_Save(id);
		}
		else
		{
			cmd_biz(playerid, "menu");
		}
	}
	if(dialogid == DIALOG_BIZCARGO)
	{
		if(response)
		{
			new id = PlayerData[playerid][pInBiz], price = strcash(inputtext);
			if(id == -1)
				return SendErrorMessage(playerid, "Business no longer valid.");

			if(price < 3000 || price > 10000)
				return SendErrorMessage(playerid, "Cannot under $50.00 or above $150!"), cmd_biz(playerid, "menu");

			BizData[id][bizCargo] = price;
			SendClientMessageEx(playerid, COLOR_SERVER, "(Business) {FFFFFF}Kamu telah mengubah Cargo price menjadi {00FF00}$%s", FormatNumber(price));
			cmd_biz(playerid, "menu");
		}
	}
	if(dialogid == DIALOG_RENTAL)
	{
	    if(response)
	    {
	        new id = PlayerData[playerid][pRenting], slot = listitem;

	        if(GetMoney(playerid) < RentData[id][rentPrice][listitem])
	            return SendErrorMessage(playerid, "Kamu tidak memiliki cukup uang!");
	            
            new vehicleid = Vehicle_Create(RentData[id][rentModel][slot], RentData[id][rentSpawn][0], RentData[id][rentSpawn][1], RentData[id][rentSpawn][2], RentData[id][rentSpawn][3], random(255), random(255), 0, true, "RENTAL"); 
			
			Vehicle_SetType(vehicleid, VEHICLE_TYPE_RENTAL);
			Vehicle_SetOwner(vehicleid, playerid, true);
			
			VehicleData[vehicleid][vRental] = PlayerData[playerid][pRenting];
			VehicleData[vehicleid][vRentTime] = 3600;

			GiveMoney(playerid, -RentData[id][rentPrice][slot], "Rental kendaraan");
			SendClientMessageEx(playerid, COLOR_SERVER, "(Rental) {FFFFFF}Kamu telah menyewa {00FFFF}%s {FFFFFF}untuk 1 Jam seharga {009000}$%s", ReturnVehicleModelName(RentData[id][rentModel][slot]), FormatNumber(RentData[id][rentPrice][slot]));
			SendClientMessageEx(playerid, COLOR_SERVER, "(Rental) "WHITE"Gunakan "YELLOW"/rentinfo "WHITE"untuk info kendaraan rental.");
		}
	}
	if(dialogid == DIALOG_RENTTIME)
	{
	    if(response)
	    {
	        new id = PlayerData[playerid][pRenting];
	        new slot = PlayerData[playerid][pListitem];
			new time = strval(inputtext), vehicleid;
			if(time < 1 || time > 4)
			{
				new str[256];
				format(str, sizeof(str), "{FFFFFF}Berapa jam kamu ingin menggunakan kendaraan Rental ini ?\n{FFFFFF}Maksimal adalah {FFFF00}4 jam\n\n{FFFFFF}Harga per Jam: {009000}$%s", FormatNumber(RentData[id][rentPrice][listitem]));
				ShowPlayerDialog(playerid, DIALOG_RENTTIME, DIALOG_STYLE_INPUT, "{FFFFFF}Rental Time", str, "Rental", "Close");
				return 1;
			}
			GiveMoney(playerid, -RentData[id][rentPrice][slot] * time, "Rental kendaraan");
			SendClientMessageEx(playerid, COLOR_SERVER, "(Rental) {FFFFFF}Kamu telah menyewa {00FFFF}%s {FFFFFF}untuk %d Jam seharga {009000}$%s", ReturnVehicleModelName(RentData[id][rentModel][slot]), time, FormatNumber(RentData[id][rentPrice][slot] * time));
            vehicleid = Vehicle_Create(RentData[id][rentModel][slot], RentData[id][rentSpawn][0], RentData[id][rentSpawn][1], RentData[id][rentSpawn][2], RentData[id][rentSpawn][3], random(255), random(255), 0, true, "RENTAL");
			Vehicle_SetOwner(vehicleid, playerid, true);
			Vehicle_SetType(vehicleid, VEHICLE_TYPE_RENTAL);
		
			VehicleData[vehicleid][vRental] = PlayerData[playerid][pRenting];
			VehicleData[vehicleid][vRentTime] = 3600;

			Vehicle_Save(vehicleid);
		}
	}
	if(dialogid == DIALOG_BUYSKINS)
	{
	    if(response)
	    {
	        GiveMoney(playerid, -PlayerData[playerid][pSkinPrice]);
			cmd_ame(playerid, sprintf("* %s has paid $%s and purchased a %s.", ReturnName(playerid), FormatNumber(PlayerData[playerid][pSkinPrice]), ProductName[PlayerData[playerid][pInBiz]][0]));
			BizData[PlayerData[playerid][pInBiz]][bizStock]--;

			if(PlayerData[playerid][pGender] == 1)
				UpdatePlayerSkin(playerid, g_aMaleSkins[listitem]);
			else
				UpdatePlayerSkin(playerid, g_aFemaleSpawnSkins[listitem]);
		}
	}
	if(dialogid == DIALOG_DROPITEM)
	{
	    if(response)
	    {
			new
			    itemid = PlayerData[playerid][pListitem],
			    string[32],
				str[356];

			strunpack(string, InventoryData[playerid][itemid][invItem]);

			if (response)
			{
			    if (isnull(inputtext))
			        return format(str, sizeof(str), "Drop Item", "Item: %s - Quantity: %d\n\nPlease specify how much of this item you wish to drop:", string, InventoryData[playerid][itemid][invQuantity]),
					ShowPlayerDialog(playerid, DIALOG_DROPITEM, DIALOG_STYLE_INPUT, "Drop Item", str, "Drop", "Cancel");

				if (strval(inputtext) < 1 || strval(inputtext) > InventoryData[playerid][itemid][invQuantity])
				    return format(str, sizeof(str), "ERROR: Insufficient amount specified.\n\nItem: %s - Quantity: %d\n\nPlease specify how much of this item you wish to drop:", string, InventoryData[playerid][itemid][invQuantity]),
					ShowPlayerDialog(playerid, DIALOG_DROPITEM, DIALOG_STYLE_INPUT, "Drop Item", str, "Drop", "Cancel");

				if(!strcmp(string, "Rolled Weed"))
				{
					if(IsPlayerInRangeOfPoint(playerid, 5.0, -774.2181,2425.2349,157.1011))
					{
						new amount = strval(inputtext);
						GiveMoney(playerid, amount*1500, "Jual rolled weed");
						SendClientMessageEx(playerid, COLOR_SERVER, "(Drugs) {FFFFFF}Kamu telah menjual {FFFF00}%d Rolled Weed {FFFFFF}dan mendapatkan {00FF00}$%s", amount, FormatNumber(amount*1500));
						Inventory_Remove(playerid, "Rolled Weed", strval(inputtext));
					}
					else
					{
						DropPlayerItem(playerid, itemid, strval(inputtext));
					}
				}
				else
				{
					DropPlayerItem(playerid, itemid, strval(inputtext));
				}
			}
		}
	}
	if(dialogid == DIALOG_GIVEITEM)
	{
		if (response)
		{
		    static
		        userid = -1,
				itemid = -1,
				string[32];

			if (sscanf(inputtext, "u", userid))
			    return ShowPlayerDialog(playerid, DIALOG_GIVEITEM, DIALOG_STYLE_INPUT, "Give Item", "Please enter the name or the ID of the player:", "Submit", "Cancel");

			if (userid == INVALID_PLAYER_ID)
			    return ShowPlayerDialog(playerid, DIALOG_GIVEITEM, DIALOG_STYLE_INPUT, "Give Item", "ERROR: Invalid player specified.\n\nPlease enter the name or the ID of the player:", "Submit", "Cancel");

		    if (!IsPlayerNearPlayer(playerid, userid, 6.0))
				return ShowPlayerDialog(playerid, DIALOG_GIVEITEM, DIALOG_STYLE_INPUT, "Give Item", "ERROR: You are not near that player.\n\nPlease enter the name or the ID of the player:", "Submit", "Cancel");

		    if (userid == playerid)
				return ShowPlayerDialog(playerid, DIALOG_GIVEITEM, DIALOG_STYLE_INPUT, "Give Item", "ERROR: You can't give items to yourself.\n\nPlease enter the name or the ID of the player:", "Submit", "Cancel");

			itemid = PlayerData[playerid][pListitem];

			if (itemid == -1)
			    return 0;

			strunpack(string, InventoryData[playerid][itemid][invItem]);

			if (InventoryData[playerid][itemid][invQuantity] == 1)
			{
			    new id = Inventory_Add(userid, string, InventoryData[playerid][itemid][invModel]);

			    if (id == -1)
					return SendErrorMessage(playerid, "That player doesn't have anymore inventory slots.");

			    SendNearbyMessage(playerid, 30.0,X11_PLUM, "** %s takes out a \"%s\" and gives it to %s.", ReturnName(playerid), string, ReturnName(userid));
			    SendServerMessage(userid, "%s has given you \"%s\" (added to inventory).", ReturnName(playerid), string);

				Inventory_Remove(playerid, string);
			    //Log_Write("logs/give_log.txt", "[%s] %s (%s) has given a %s to %s (%s).", ReturnDate(), ReturnName(playerid), PlayerData[playerid][pIP], string, ReturnName(userid, 0), PlayerData[userid][pIP]);
	  		}
			else
			{
				new str[152];
				format(str, sizeof(str), "Item: %s (Amount: %d)\n\nPlease enter the amount of this item you wish to give %s:", string, InventoryData[playerid][itemid][invQuantity], ReturnName(userid));
			    ShowPlayerDialog(playerid, DIALOG_GIVEAMOUNT, DIALOG_STYLE_INPUT, "Give Item", str, "Give", "Cancel");
			    PlayerData[playerid][pTarget] = userid;
			}
		}
	}
	if(dialogid == DIALOG_GIVEAMOUNT)
	{
		if (response && PlayerData[playerid][pTarget] != INVALID_PLAYER_ID)
		{
		    new
		        userid = PlayerData[playerid][pTarget],
		        itemid = PlayerData[playerid][pListitem],
				string[32],
				str[352];

			strunpack(string, InventoryData[playerid][itemid][invItem]);

			if (isnull(inputtext))
				return format(str, sizeof(str), "Item: %s (Amount: %d)\n\nPlease enter the amount of this item you wish to give %s:", string, InventoryData[playerid][itemid][invQuantity], ReturnName(userid)),
				ShowPlayerDialog(playerid, DIALOG_GIVEAMOUNT, DIALOG_STYLE_INPUT, "Give Item", str, "Give", "Cancel");

			if (strval(inputtext) < 1 || strval(inputtext) > InventoryData[playerid][itemid][invQuantity])
			    return format(str, sizeof(str), "ERROR: You don't have that much.\n\nItem: %s (Amount: %d)\n\nPlease enter the amount of this item you wish to give %s:", string, InventoryData[playerid][itemid][invQuantity], ReturnName(userid)),
				ShowPlayerDialog(playerid, DIALOG_GIVEAMOUNT, DIALOG_STYLE_INPUT, "Give Item", str, "Give", "Cancel");

	        new id = Inventory_Add(userid, string, InventoryData[playerid][itemid][invModel], strval(inputtext));

		    if (id == -1)
				return SendErrorMessage(playerid, "That player doesn't have anymore inventory slots.");

		    SendNearbyMessage(playerid, 30.0,X11_PLUM, "** %s takes out a \"%s\" and gives it to %s.", ReturnName(playerid), string, ReturnName(userid));
		    SendServerMessage(userid, "%s has given you \"%s\" (added to inventory).", ReturnName(playerid), string);

			Inventory_Remove(playerid, string, strval(inputtext));
		    Log_Write("Logs/give_log.txt", "[%s] %s (%s) has given %d %s to %s (%s).", ReturnDate(), ReturnName(playerid), ReturnIP(playerid), strval(inputtext), string, ReturnName(userid), ReturnIP(userid));
		}
	}
	if(dialogid == DIALOG_INVACTION)
	{
	    if(response)
	    {
		    new
				itemid = PlayerData[playerid][pListitem],
				string[64],
				str[256];

		    strunpack(string, InventoryData[playerid][itemid][invItem]);

		    switch (listitem)
		    {
		        case 0:
		        {
		            CallLocalFunction("OnPlayerUseItem", "dds", playerid, itemid, string);
		        }
		        case 1:
		        {

					if(PlayerData[playerid][pInjured])
						return SendErrorMessage(playerid, "Tidak bisa memberikan item ketika injured.");


				    if(!strcmp(string, "Fish Rod") && GetEquipedItem(playerid) == EQUIP_ITEM_ROD) {
						return SendErrorMessage(playerid, "Kamu masih menggunakan item ini.");
					}

				    if(!strcmp(string, "Axe") && GetEquipedItem(playerid) == EQUIP_ITEM_AXE) {
						return SendErrorMessage(playerid, "Kamu masih menggunakan item ini.");
					}

					if(!IsInventoryCanGive(string))
						return SendErrorMessage(playerid, "Kamu tidak dapat memberikan item ini!");

					PlayerData[playerid][pListitem] = itemid;
					ShowPlayerDialog(playerid, DIALOG_GIVEITEM, DIALOG_STYLE_INPUT, "Give Item", "Please enter the name or the ID of the player:", "Submit", "Cancel");
		        }
		        case 2:
		        {
		            if (IsPlayerInAnyVehicle(playerid))
		                return SendErrorMessage(playerid, "You can't drop items right now.");

					if(PlayerData[playerid][pInjured])
						return SendErrorMessage(playerid, "Tidak bisa menjatuhkan item ketika injured.");

				    if(!strcmp(string, "Fish Rod") && GetEquipedItem(playerid) == EQUIP_ITEM_ROD) {
						return SendErrorMessage(playerid, "Kamu masih menggunakan item ini.");
					}

				    if(!strcmp(string, "Axe") && GetEquipedItem(playerid) == EQUIP_ITEM_AXE) {
						return SendErrorMessage(playerid, "Kamu masih menggunakan item ini.");
					}

					else if (InventoryData[playerid][itemid][invQuantity] == 1)
					{
						if(!strcmp(string, "Rolled Weed"))
						{
							if(IsPlayerInRangeOfPoint(playerid, 5.0, -774.2181,2425.2349,157.1011))
							{
								new amount = InventoryData[playerid][itemid][invQuantity];
								GiveMoney(playerid, amount*1500, "Jual rolled weed");
								SendClientMessageEx(playerid, COLOR_SERVER, "(Drugs) {FFFFFF}Kamu telah menjual {FFFF00}%d Rolled Weed {FFFFFF}dan mendapatkan {00FF00}$%s", amount, FormatNumber(amount*1500));
								Inventory_Remove(playerid, "Rolled Weed");
							}
							else
							{
								if(!IsInventoryCanDrop(string))
									return SendErrorMessage(playerid, "Kamu tidak dapat menjatuhkan item ini!");

								DropPlayerItem(playerid, itemid);
							}
						}
						else
						{
							if(!IsInventoryCanDrop(string))
								return SendErrorMessage(playerid, "Kamu tidak dapat menjatuhkan item ini!");

							DropPlayerItem(playerid, itemid);
						}
					}
					else
						format(str, sizeof(str), "Item: %s - Quantity: %d\n\nPlease specify how much of this item you wish to drop:", string, InventoryData[playerid][itemid][invQuantity]),
						ShowPlayerDialog(playerid, DIALOG_DROPITEM, DIALOG_STYLE_INPUT, "Drop Item", str, "Drop", "Cancel");
				}
			}
		}
	}
    if(dialogid == DIALOG_INVENTORY)
    {
        if(response)
        {
	
		    new
		        name[48], id, str[156], index = g_ListedInventory[playerid][listitem];

            if(InventoryData[playerid][index][invQuantity] < 1)
            	return SendErrorMessage(playerid, "There is no item on selected slot!");

            strunpack(name, InventoryData[playerid][index][invItem]);
            PlayerData[playerid][pListitem] = index;

			switch (PlayerData[playerid][pStorageSelect])
			{
			    case 0:
			    {
					new options[128];

					strcat(options, "Use Item\n");

					strcat(options, sprintf(""WHITE"Give Item%s\n", !IsInventoryCanGive(name) ? (""RED" X") : ("")));

					strcat(options, sprintf(""WHITE"Drop Item%s\n", !IsInventoryCanDrop(name) ? (""RED" X") : ("")));

		            ShowPlayerDialog(playerid, DIALOG_INVACTION, DIALOG_STYLE_LIST, sprintf("%s (%d)", name, InventoryData[playerid][index][invQuantity]), options, "Select", "Cancel");
				}
				case 1:
				{
					if(!IsInventoryCanStored(name))
						return SendErrorMessage(playerid, "Item ini tidak bisa disimpan dirumah!");

			    	if ((id = House_Inside(playerid)) != -1 && House_HaveAccess(playerid, id))
					{
					        
						if (InventoryData[playerid][index][invQuantity] == 1)
						{
			        		House_AddItem(id, name, InventoryData[playerid][index][invModel], 1);
			        		Inventory_Remove(playerid, name);
			        		
			        		SendNearbyMessage(playerid, 30.0,X11_PLUM, "** %s has stored a \"%s\" into their house storage.", ReturnName(playerid), name);
					 		House_ShowItems(playerid, id);
						}
						else
						{
							format(str, sizeof(str), "Item: %s (Amount: %d)\n\nPlease enter the quantity that you wish to store for this item:", name, InventoryData[playerid][PlayerData[playerid][pListitem]][invQuantity]);
							ShowPlayerDialog(playerid, DIALOG_HOUSEDEPOSIT, DIALOG_STYLE_INPUT, "House Deposit", str, "Deposit", "Close");
						}
					}
				}
				case 2: {

					if(!IsInventoryCanStored(name))
						return SendErrorMessage(playerid, "Item ini tidak bisa disimpan diflat!");

			    	if ((id = Flat_Inside(playerid)) != -1 && Flat_IsHaveAccess(playerid, id))
					{
					        
						if (InventoryData[playerid][index][invQuantity] == 1)
						{
			        		Flat_AddItem(id, name, InventoryData[playerid][index][invModel], 1);
			        		Inventory_Remove(playerid, name);
			        		
			        		SendNearbyMessage(playerid, 30.0,X11_PLUM, "** %s has stored a \"%s\" into their flat storage.", ReturnName(playerid), name);
					 		Flat_ShowItems(playerid, id);
						}
						else
						{
							format(str, sizeof(str), "Item: %s (Amount: %d)\n\nPlease enter the quantity that you wish to store for this item:", name, InventoryData[playerid][PlayerData[playerid][pListitem]][invQuantity]);
							ShowPlayerDialog(playerid, DIALOG_FLAT_DEPOSIT, DIALOG_STYLE_INPUT, "Flat Deposit", str, "Deposit", "Close");
						}
					}	
				}
				case 3: {

					if((id = Vehicle_Nearest(playerid, 5.0)) != -1) {

					    if(!IsInventoryCanStored(name))
							return SendErrorMessage(playerid, "Item ini tidak bisa disimpan dibagasi!");

						if (InventoryData[playerid][index][invQuantity] == 1) {

							Car_AddItem(id, name, InventoryData[playerid][index][invModel], 1);
							Inventory_Remove(playerid, name);

							SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "* %s has stored a \"%s\" into the trunk.", ReturnName(playerid), name);
							SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Trunk) "WHITE"Kamu telah menyimpan "YELLOW"%s "WHITE"kedalam bagasi "CYAN"%s", name, GetVehicleName(id));
							Vehicle_ShowTrunk(playerid, id);
						}
						else {
							new txtstr[256];
							format(txtstr, sizeof(txtstr), "Item: %s (Quantity: %d)\n\nPlease enter the quantity that you wish to store for this item:", name, InventoryData[playerid][PlayerData[playerid][pListitem]][invQuantity]);
							ShowPlayerDialog(playerid, DIALOG_TRUNK_DEPOSIT, DIALOG_STYLE_INPUT, "Vehicle Deposit", txtstr, "Store", "Back");
						}
					}
				}
			}
		}
	}
	if(dialogid == DIALOG_TRUNK_DEPOSIT) {
		if(response) {
			
			static
				carid = -1,
				string[32];

			if ((carid = Vehicle_Nearest(playerid)) != -1)
			{
				strunpack(string, InventoryData[playerid][PlayerData[playerid][pListitem]][invItem]);

				if (response)
				{
					new amount = strval(inputtext);

					if (amount < 1 || amount > InventoryData[playerid][PlayerData[playerid][pListitem]][invQuantity]) {

						new txtstr[256];
						format(txtstr, sizeof(txtstr), "Item: %s (Quantity: %d)\n\nPlease enter the quantity that you wish to store for this item:", "Store", "Back", string, InventoryData[playerid][PlayerData[playerid][pListitem]][invQuantity]);
						return ShowPlayerDialog(playerid, DIALOG_TRUNK_DEPOSIT, DIALOG_STYLE_INPUT, "Vehicle Deposit", txtstr, "Store", "Back");
					}
					Car_AddItem(carid, string, InventoryData[playerid][PlayerData[playerid][pListitem]][invModel], amount);
					Inventory_Remove(playerid, string, amount);

					SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "* %s has stored a \"%s\" into the trunk.", ReturnName(playerid), string);
					SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Trunk) "WHITE"Kamu telah menyimpan "YELLOW"%d %s "WHITE"kedalam bagasi "CYAN"%s", amount, string, GetVehicleName(carid));
					Vehicle_ShowTrunk(playerid, carid);
				}
				else Vehicle_ShowTrunk(playerid, carid);
			}
		}
	}
	if(dialogid == DIALOG_TRUNK_TAKE) {

		if(response) {
			static
				carid = -1,
				string[32];

			if ((carid = Vehicle_Nearest(playerid, 5.0)) != -1)
			{
				strunpack(string, CarStorage[carid][PlayerData[playerid][pStorageItem]][cItemName]);

				if (response)
				{
					new amount = strval(inputtext);

					if (amount < 1 || amount > CarStorage[carid][PlayerData[playerid][pStorageItem]][cItemQuantity]) {

						new txtstr[256];
						format(txtstr, sizeof(txtstr), "Item: %s (Quantity: %d)\n\nPlease enter the quantity that you wish to take for this item:", string, CarStorage[carid][PlayerData[playerid][pListitem]][cItemQuantity]);
						ShowPlayerDialog(playerid, DIALOG_TRUNK_TAKE, DIALOG_STYLE_INPUT, "Vehicle Take", txtstr, "Take", "Back");
						return 1;
					}

					new id = Inventory_Add(playerid, string, CarStorage[carid][PlayerData[playerid][pStorageItem]][cItemModel], amount);

					if (id == -1)
						return SendErrorMessage(playerid, "You don't have any inventory slots left.");

					Car_RemoveItem(carid, string, amount);

					SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "* %s has taken a \"%s\" from the trunk.", ReturnName(playerid), string);
					SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Trunk) "WHITE"Kamu mengambil "YELLOW"%d %s "WHITE"dari bagasi "CYAN"%s", amount, string, GetVehicleName(carid));
					Vehicle_ShowTrunk(playerid, carid);
				}
				else Vehicle_ShowTrunk(playerid, carid);
			}
		}
	}
	if(dialogid == DIALOG_BIZBUY)
	{
	    if(response)
	    {
	        new bid = PlayerData[playerid][pInBiz], price, prodname[34];
	        if(bid != -1)
	        {
	            price = BizData[bid][bizProduct][listitem];
				prodname = ProductName[bid][listitem];
				PlayerData[playerid][pListitem] = listitem;
	            if(GetMoney(playerid) < price)
	                return SendErrorMessage(playerid, "You don't have enough money!");
	                
				if(BizData[bid][bizStock] < 1)
					return SendErrorMessage(playerid, "This business is out of stock.");
					
				switch(BizData[bid][bizType])
				{
				    case 1:
				    {
						if(listitem == 0)
						{
						    if(PlayerData[playerid][pHunger] >= 100)
						        return SendErrorMessage(playerid, "Kamu tidak membutuhkan makanan saat ini.");

							PlayerData[playerid][pHunger] += 20;
							cmd_ame(playerid, sprintf("* %s has paid $%s and purchased a %s.", ReturnName(playerid), FormatNumber(price), prodname));
							GiveMoney(playerid, -price);
							BizData[bid][bizStock]--;
							BizData[bid][bizVault] += price;
							PlayerPlaySound(playerid, 32200, 0.0, 0.0, 0.0);
							ApplyAnimation(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
						}
						if(listitem == 1)
						{
						    if(PlayerData[playerid][pHunger] >= 100)
						        return SendErrorMessage(playerid, "Your energy is already full!");

							PlayerData[playerid][pHunger] += 40;
							cmd_ame(playerid, sprintf("* %s has paid $%s and purchased a %s.", ReturnName(playerid), FormatNumber(price), prodname));
							GiveMoney(playerid, -price);
							BizData[bid][bizStock]--;
							BizData[bid][bizVault] += price;
							PlayerPlaySound(playerid, 32200, 0.0, 0.0, 0.0);
							ApplyAnimation(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
						}
						if(listitem == 2)
						{
						    if(PlayerData[playerid][pThirst] >= 100)
						        return SendErrorMessage(playerid, "Kamu tidak membutuhkan minum saat ini.");

							PlayerData[playerid][pThirst] += 15;
							cmd_ame(playerid, sprintf("* %s has paid $%s and purchased a %s.", ReturnName(playerid), FormatNumber(price), prodname));
							GiveMoney(playerid, -price);
							BizData[bid][bizStock]--;
							BizData[bid][bizVault] += price;
							ApplyAnimation(playerid, "VENDING", "VEND_DRINK2_P", 4.1, 0, 0, 0, 0, 0, 1);
						}
					}
					case 2:
					{
					    if(listitem == 0)
					    {
							if(Inventory_Add(playerid, "Snack", 2768, 1) == -1)
								return 1;

							cmd_ame(playerid, sprintf("* %s has paid $%s and purchased a %s.", ReturnName(playerid), FormatNumber(price), prodname));
							GiveMoney(playerid, -price);
							BizData[bid][bizStock]--;
							BizData[bid][bizVault] += price;
						}
						if(listitem == 1)
						{
							if(Inventory_Add(playerid, "Water", 2958, 1) == -1)
								return 1;

							cmd_ame(playerid, sprintf("* %s has paid $%s and purchased a %s.", ReturnName(playerid), FormatNumber(price), prodname));
							GiveMoney(playerid, -price);
							BizData[bid][bizStock]--;
							BizData[bid][bizVault] += price;
						}
						if(listitem == 2)
						{
							if(Inventory_Add(playerid, "Mask", 19036, 1) == -1)
								return 1;

							PlayerData[playerid][pMaskID] = PlayerData[playerid][pID]+random(90000) + 10000;
							cmd_ame(playerid, sprintf("* %s has paid $%s and purchased a %s.", ReturnName(playerid), FormatNumber(price), prodname));
							GiveMoney(playerid, -price);
							BizData[bid][bizStock]--;
							BizData[bid][bizVault] += price;
							Log_Write("Logs/maskid_log.txt", "[%s] %s(%s) new maskid: %d", ReturnDate(), GetName(playerid, false), GetUsername(playerid), PlayerData[playerid][pMaskID]);
						}
						if(listitem == 3)
						{
							if(Inventory_Add(playerid, "Rolling Paper", 19873, 1) == -1)
								return 1;

							cmd_ame(playerid, sprintf("* %s has paid $%s and purchased a %s.", ReturnName(playerid), FormatNumber(price), prodname));
							GiveMoney(playerid, -price);
							BizData[bid][bizStock]--;
							BizData[bid][bizVault] += price;
						}
						if(listitem == 4)
						{
							if(Inventory_Add(playerid, "Axe", 19631, 1) == -1)
								return 1;

							cmd_ame(playerid, sprintf("* %s has paid $%s and purchased a %s.", ReturnName(playerid), FormatNumber(price), prodname));
							GiveMoney(playerid, -price);
							BizData[bid][bizStock]--;
							BizData[bid][bizVault] += price;							
						}
						if(listitem == 5)
						{
							if(Inventory_Add(playerid, "Fish Rod", 18632, 1) == -1)
								return 1;

							cmd_ame(playerid, sprintf("* %s has paid $%s and purchased a %s.", ReturnName(playerid), FormatNumber(price), prodname));
							GiveMoney(playerid, -price);
							BizData[bid][bizStock]--;
							BizData[bid][bizVault] += price;	
						}
						if(listitem == 6)
						{
							if(Inventory_Add(playerid, "Fuel Can", 1650, 1) == -1)
								return 1;

							cmd_ame(playerid, sprintf("* %s has paid $%s and purchased a %s.", ReturnName(playerid), FormatNumber(price), prodname));
							GiveMoney(playerid, -price);
							BizData[bid][bizStock]--;
							BizData[bid][bizVault] += price;	
						}
						if(listitem == 7)
						{
							if(Inventory_Add(playerid, "Bandage", 1580, 1) == -1)
								return 1;

							cmd_ame(playerid, sprintf("* %s has paid $%s and purchased a %s.", ReturnName(playerid), FormatNumber(price), prodname));
							GiveMoney(playerid, -price);
							BizData[bid][bizStock]--;
							BizData[bid][bizVault] += price;	
						}
					}
					case 3:
					{
						PlayerData[playerid][pSkinPrice] = price;
						if(listitem == 0)
						{
						    if(PlayerData[playerid][pGender] == 1)
						    {
						    	ShowModelSelectionMenu(playerid, "Male Skins", MODEL_SELECTION_BUYSKIN, g_aMaleSkins, sizeof(g_aMaleSkins), -16.0, 0.0, -55.0);
							}
							else
							{
						        ShowModelSelectionMenu(playerid, "Female Skins", MODEL_SELECTION_BUYSKIN, g_aFemaleSkins, sizeof(g_aFemaleSkins), -16.0, 0.0, -55.0);
							}
						}
						if(listitem == 1)
						{

							if(Aksesoris_GetCount(playerid) >= MAX_ACC)
								return SendErrorMessage(playerid, "Kamu tidak bisa memiliki lebih banyak accessory!");

							new models[150] = {-1, ... },
								count;

							for (new id; id < sizeof(accList); id++)
							{
								models[count++] = accList[id][accListModel];
							}
							ShowModelSelectionMenu(playerid, "Purchase Accessory", MODEL_SELECTION_ACC, models, sizeof(models), 0.0, 0.0, 0.0);
						}
					}
					case 4:
					{
					    if(listitem == 0)
						{       
							ShowNumberIndex(playerid);
						}
					    if(listitem == 1)
						{
							if(Inventory_Add(playerid, "GPS", 18875, 1) == -1)
								return 1;

							cmd_ame(playerid, sprintf("* %s has paid $%s and purchased a %s.", ReturnName(playerid), FormatNumber(price), prodname));
							GiveMoney(playerid, -price);
							BizData[bid][bizStock]--;
							BizData[bid][bizVault] += price;
						}
					    if(listitem == 2)
						{
							if(Inventory_Add(playerid, "Portable Radio", 19942, 1) == -1)
								return 1;

							cmd_ame(playerid, sprintf("* %s has paid $%s and purchased a %s.", ReturnName(playerid), FormatNumber(price), prodname));
							GiveMoney(playerid, -price);
							BizData[bid][bizStock]--;
							BizData[bid][bizVault] += price;
						}
						if(listitem == 3)
						{
							PlayerData[playerid][pCredit] += 50;
							cmd_ame(playerid, sprintf("* %s has paid $%s and purchased a %s.", ReturnName(playerid), FormatNumber(price), prodname));
							GiveMoney(playerid, -price);
							BizData[bid][bizStock]--;
							BizData[bid][bizVault] += price;
						}
						if(listitem == 4)
						{
							if(Inventory_Add(playerid, "Boombox", 2103, 1) == -1)
								return 1;

							cmd_ame(playerid, sprintf("* %s has paid $%s and purchased a %s.", ReturnName(playerid), FormatNumber(price), prodname));
							GiveMoney(playerid, -price);
							BizData[bid][bizStock]--;
							BizData[bid][bizVault] += price;
						}
					}
					case 5: {

						if(listitem == 0) {
							if(PlayerHasWeapon(playerid, WEAPON_FLOWER))
								return SendErrorMessage(playerid, "Kamu masih memiliki senjata pada slot yang sama (Flower)");
								
							if(PlayerHasWeapon(playerid, WEAPON_BAT))
								return SendErrorMessage(playerid, "Kamu masih memiliki senjata pada slot yang sama (Bat)");

							if(PlayerHasWeapon(playerid, WEAPON_POOLSTICK))
								return SendErrorMessage(playerid, "Kamu masih memiliki senjata pada slot yang sama (Pool Cue)");

							GiveWeaponToPlayer(playerid, WEAPON_BAT, 1, 500);
							cmd_ame(playerid, sprintf("* %s has paid $%s and purchased a %s.", ReturnName(playerid), FormatNumber(price), prodname));
							GiveMoney(playerid, -price);
							BizData[bid][bizStock]--;
							BizData[bid][bizVault] += price;
						}
						if(listitem == 1) {

							if(PlayerHasWeapon(playerid, WEAPON_FLOWER))
								return SendErrorMessage(playerid, "Kamu masih memiliki senjata pada slot yang sama (Flower)");

							if(PlayerHasWeapon(playerid, WEAPON_BAT))
								return SendErrorMessage(playerid, "Kamu masih memiliki senjata pada slot yang sama (Bat)");

							if(PlayerHasWeapon(playerid, WEAPON_POOLSTICK))
								return SendErrorMessage(playerid, "Kamu masih memiliki senjata pada slot yang sama (Pool Cue)");

							GiveWeaponToPlayer(playerid, WEAPON_FLOWER, 1, 500);
							cmd_ame(playerid, sprintf("* %s has paid $%s and purchased a %s.", ReturnName(playerid), FormatNumber(price), prodname));
							GiveMoney(playerid, -price);
							BizData[bid][bizStock]--;
							BizData[bid][bizVault] += price;		
						}
						if(listitem == 2) {
							if(PlayerHasWeapon(playerid, WEAPON_FLOWER))
								return SendErrorMessage(playerid, "Kamu masih memiliki senjata pada slot yang sama (Flower)");
								
							if(PlayerHasWeapon(playerid, WEAPON_BAT))
								return SendErrorMessage(playerid, "Kamu masih memiliki senjata pada slot yang sama (Bat)");

							if(PlayerHasWeapon(playerid, WEAPON_POOLSTICK))
								return SendErrorMessage(playerid, "Kamu masih memiliki senjata pada slot yang sama (Pool Cue)");

							GiveWeaponToPlayer(playerid, WEAPON_POOLSTICK, 1, 500);
							cmd_ame(playerid, sprintf("* %s has paid $%s and purchased a %s.", ReturnName(playerid), FormatNumber(price), prodname));
							GiveMoney(playerid, -price);
							BizData[bid][bizStock]--;
							BizData[bid][bizVault] += price;	
						}
						if(listitem == 3) {
							
							Inventory_Set(playerid, "Cigarettes", 19896, 20);
							cmd_ame(playerid, sprintf("* %s has paid $%s and purchased a %s.", ReturnName(playerid), FormatNumber(price), prodname));
							GiveMoney(playerid, -price);
							BizData[bid][bizStock]--;
							BizData[bid][bizVault] += price;
						}
					}
				}
			}
		}
	}
	if(dialogid == DIALOG_VERIFY)
	{
		if(response)
		{
			if(isnull(inputtext)) {
				SendServerMessage(playerid, "Kamu memasukkan kode Verifikasi yang salah!");
				return ShowVerifyMenu(playerid);
			}
			if(!IsNumeric(inputtext)) {
				SendServerMessage(playerid, "Kamu memasukkan kode Verifikasi yang salah!");
				return ShowVerifyMenu(playerid);
			}
			if(strval(inputtext) == UcpData[playerid][uVerifyCode]) {
				ShowRegisterMenu(playerid);
			}
			else
				ShowVerifyMenu(playerid);
		}
		else 
		{
			Kick(playerid);
		}
	}
	if(dialogid == DIALOG_REGISTER)
	{
	    if(!response)
	        return Kick(playerid);

        if(strlen(inputtext) < 7)
			return ShowRegisterMenu(playerid);

        if(strlen(inputtext) > 32)
			return ShowRegisterMenu(playerid);

        bcrypt_hash(playerid, "HashPlayerPassword", inputtext, BCRYPT_COST);
	}
	if(dialogid == DIALOG_LOGIN)
	{
	    if(!response)
	        return Kick(playerid);
	        
		new pwQuery[256];
		mysql_format(sqlcon, pwQuery, sizeof(pwQuery), "SELECT Password FROM playerucp WHERE UCP = '%e' LIMIT 1", GetName(playerid));
		mysql_tquery(sqlcon, pwQuery, "LoadPlayerPassword", "ds", playerid, inputtext);


	}
    if(dialogid == DIALOG_CHARLIST)
    {
		if(response)
		{
			if (PlayerChar[playerid][listitem][0] == EOS)
				return ShowPlayerDialog(playerid, DIALOG_MAKECHAR, DIALOG_STYLE_INPUT, "Create Character", "Silahkan masukan nama karaktermu:\n(note) nama karakter harus nama Roleplay!", "Create", "Exit");

			PlayerData[playerid][pChar] = listitem;

			ShowPlayerDialog(playerid, DIALOG_CHAR_OPTION, DIALOG_STYLE_LIST, "OT - Char Menu", "Start playing\nRemove this character", "Select", "Quit");			
		}
	}
	if(dialogid == DIALOG_CHAR_OPTION) {
		if(!response)
			return Kick(playerid);

		switch(listitem) {
			case 0: {
				new cQuery[256];
				mysql_format(sqlcon, cQuery, sizeof(cQuery), "SELECT * FROM `characters` WHERE `Name` = '%e' LIMIT 1;", PlayerChar[playerid][PlayerData[playerid][pChar]]);
				mysql_tquery(sqlcon, cQuery, "LoadCharacterData", "d", playerid);
				//SetPlayerName(playerid, PlayerChar[playerid][listitem]);
			}
			case 1: {
				ShowPlayerDialog(playerid, DIALOG_CHAR_DELETE, DIALOG_STYLE_INPUT, "OT - Remove Character", "Berikan alasan-mu menghapus karakter yang valid:\n\nNote: Saat menekan \"Confirm\" tandanya kamu menyetujui semua wealth/aset yang hilang\nketika karakter dihapus, karakter yang dihapus tidak dapat dikembalikan dalam cara dan bentuk apapun.\nPastikan kamu memikirkan matang-matang untuk penghapusan karakter.", "Confirm", "Back");
			}
		}
	}
	if(dialogid == DIALOG_CHAR_DELETE) {

		if(response) {
			if(isnull(inputtext))
				return ShowPlayerDialog(playerid, DIALOG_CHAR_DELETE, DIALOG_STYLE_INPUT, "OT - Remove Character", "Berikan alasan-mu menghapus karakter yang valid:\n\nNote: Saat menekan \"Confirm\" tandanya kamu menyetujui semua wealth/aset yang hilang\nketika karakter dihapus, karakter yang dihapus tidak dapat dikembalikan dalam cara dan bentuk apapun.\nPastikan kamu memikirkan matang-matang untuk penghapusan karakter.", "Confirm", "Back");

			
			Log_Write("Logs/char_remove_log.txt", "[%s] %s(UCP: %s - LVL: %d) Reason: %s.", ReturnDate(), PlayerChar[playerid][PlayerData[playerid][pChar]], GetName(playerid, false), PlayerLevel[playerid][PlayerData[playerid][pChar]], inputtext);

			new query[256];

			mysql_format(sqlcon, query,sizeof(query),"DELETE FROM `characters` WHERE `Name` = '%e'", PlayerChar[playerid][PlayerData[playerid][pChar]]);
			mysql_tquery(sqlcon, query);
			mysql_format(sqlcon, query, sizeof(query), "DELETE FROM `workshop_employee` WHERE `Name` = '%e'", PlayerChar[playerid][PlayerData[playerid][pChar]]);
			mysql_tquery(sqlcon, query);
			mysql_format(sqlcon, query, sizeof(query), "DELETE FROM `housekeys` WHERE `Name` = '%e'", PlayerChar[playerid][PlayerData[playerid][pChar]]);
			mysql_tquery(sqlcon, query);

			SendClientMessageEx(playerid, X11_RED, "CHARACTER: Karakter "YELLOW"%s "RED"berhasil dihapus secara permanen!", PlayerChar[playerid][PlayerData[playerid][pChar]]);

			mysql_format(sqlcon, query, sizeof(query), "SELECT `Name`, `Level`, `LastLogin` FROM `characters` WHERE `UCP` = '%e' LIMIT %d;", GetName(playerid), MAX_CHARS);
			mysql_tquery(sqlcon, query, "LoadCharacter", "d", playerid);


		}
		else ShowPlayerDialog(playerid, DIALOG_CHAR_OPTION, DIALOG_STYLE_LIST, "OT - Char Menu", "Start playing\nRemove this character", "Select", "Quit");
	}
	// -----[Textdraw Login]
	/*if(dialogid == DIALOG_MAKECHAR)
	{
	    if(response)
	    {
		    if(strlen(inputtext) < 1 || strlen(inputtext) > 24)
				return ShowPlayerDialog(playerid, DIALOG_MAKECHAR, DIALOG_STYLE_INPUT, "Character Name", "Silahkan masukan nama karaktermu:\n(note) nama karakter harus nama Roleplay!", "Submit", "Cancel");

			if(!IsRoleplayName(inputtext))
				return ShowPlayerDialog(playerid, DIALOG_MAKECHAR, DIALOG_STYLE_INPUT, "Character Name", "Silahkan masukan nama karaktermu:\n(note) nama karakter harus nama Roleplay!", "Submit", "Cancel");

			new characterQuery[178];
			mysql_format(sqlcon, characterQuery, sizeof(characterQuery), "SELECT * FROM `characters` WHERE `Name` = '%s'", inputtext);
			mysql_tquery(sqlcon, characterQuery, "InsertPlayerName", "ds", playerid, inputtext);

		    format(PlayerData[playerid][pUCP], 22, GetName(playerid));
		}
		else
		{
			SelectTextDraw(playerid, COLOR_YELLOW);
		}
	}*/
	if(dialogid == DIALOG_AGE)
	{
		if(response)
		{
			if(strval(inputtext) >= 70)
			    return ShowPlayerDialog(playerid, DIALOG_AGE, DIALOG_STYLE_INPUT, "Character Age", "ERROR: Cannot more than 70 years old!", "Continue", "Cancel");

			if(strval(inputtext) < 13)
			    return ShowPlayerDialog(playerid, DIALOG_AGE, DIALOG_STYLE_INPUT, "Character Age", "ERROR: Cannot below 13 Years Old!", "Continue", "Cancel");

			PlayerData[playerid][pAge] = strval(inputtext);
			ShowPlayerDialog(playerid, DIALOG_ORIGIN, DIALOG_STYLE_INPUT, "Character Origin", "Please input your Character Origin:", "Continue", "Quit");
		}
		else
		{
		    ShowPlayerDialog(playerid, DIALOG_AGE, DIALOG_STYLE_INPUT, "Character Age", "Please Insert your Character Age", "Continue", "Cancel");
		}
	}
	// -----[Textdraw Login]
/*	if(dialogid == DIALOG_ORIGIN)
	{
		if (response)
		{
		    if (isnull(inputtext) || strlen(inputtext) > 32) {
		        ShowPlayerDialog(playerid, DIALOG_ORIGIN, DIALOG_STYLE_INPUT, "Origin", "Please enter the geographical origin of your character below:", "Submit", "Cancel");
			}
			else for (new i = 0, len = strlen(inputtext); i != len; i ++) {
			    if ((inputtext[i] >= 'A' && inputtext[i] <= 'Z') || (inputtext[i] >= 'a' && inputtext[i] <= 'z') || (inputtext[i] >= '0' && inputtext[i] <= '9') || (inputtext[i] == ' ') || (inputtext[i] == ',') || (inputtext[i] == '.'))
					continue;

				else return ShowPlayerDialog(playerid, DIALOG_ORIGIN, DIALOG_STYLE_INPUT, "Origin", "Error: Only letters and numbers are accepted in the origin.\n\nPlease enter the geographical origin of your character below:", "Submit", "Cancel");
			}
			format(PlayerData[playerid][pOrigin], 32, inputtext);

	  		PlayerTextDrawSetString(playerid, ORIGINTD[playerid], sprintf("%s", PlayerData[playerid][pOrigin]));
	  		SelectTextDraw(playerid, COLOR_YELLOW);
		}
		else
		{
			SelectTextDraw(playerid, COLOR_YELLOW);
		}
	}
	if(dialogid == DIALOG_ORIGIN)
	{
	    if(!response)
	        return ShowPlayerDialog(playerid, DIALOG_ORIGIN, DIALOG_STYLE_INPUT, "Character Origin", "Please input your Character Origin:", "Continue", "Quit");

		if(strlen(inputtext) < 1)
		    return ShowPlayerDialog(playerid, DIALOG_ORIGIN, DIALOG_STYLE_INPUT, "Character Origin", "Please input your Character Origin:", "Continue", "Quit");

        format(PlayerData[playerid][pOrigin], 32, inputtext);
        ShowPlayerDialog(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, "Character Gender", "Male\nFemale", "Continue", "Cancel");
	}*/
	// -----[Textdraw Login]
	if(dialogid == DIALOG_GENDER)
	{
		if(response)
		{
			if(listitem == 0)
			{
				new rand = random(sizeof(g_aMaleSkins));
				PlayerData[playerid][pGender] = 1;
				PlayerData[playerid][pSkin] = g_aMaleSkins[rand];
				PlayerTextDrawSetString(playerid, GENDERTD[playerid], "Male");
				SelectTextDraw(playerid, COLOR_YELLOW);
			}
			if(listitem == 1)
			{
				new rand = random(sizeof(g_aFemaleSkins));
				PlayerData[playerid][pGender] = 2;
				PlayerData[playerid][pSkin] = g_aFemaleSkins[rand];
				PlayerTextDrawSetString(playerid, GENDERTD[playerid], "Female");
				SelectTextDraw(playerid, COLOR_YELLOW);
			}
		}
		else
		{
			SelectTextDraw(playerid, COLOR_YELLOW);
		}
	}
	if(dialogid == DIALOG_BOOMBOX_URL)
	{
		if(response)
		{
			if(isnull(inputtext))
			 	return ShowPlayerDialog(playerid, DIALOG_BOOMBOX_URL, DIALOG_STYLE_INPUT, "URL Music", "Please enter the URL of the music you want to play:", "Input", "Close");

			switch(PlayerData[playerid][pMusicType])
			{
				case MUSIC_BOOMBOX:
				{
				    SetMusicStream(MUSIC_BOOMBOX, playerid, inputtext);
					SendNearbyMessage(playerid, 10.0,X11_PLUM, "** %s change songs on Boombox", ReturnName(playerid));
				}
				case MUSIC_VEHICLE:
				{
				    if(IsPlayerInAnyVehicle(playerid))
				    {
					    SetMusicStream(MUSIC_VEHICLE, GetPlayerVehicleID(playerid), inputtext);
						SendNearbyMessage(playerid, 10.0,X11_PLUM, "** %s change songs on Vehicle Radio", ReturnName(playerid));
					}
				}
			}
		}
	}
	if(dialogid == DIALOG_BOOMBOX_LIST)
	{
		if(response)
		{
			switch(PlayerData[playerid][pMusicType])
			{
				case MUSIC_BOOMBOX:
				{
				    SetMusicStream(MUSIC_BOOMBOX, playerid, ListURLMusic[listitem][LinkURL]);
					SendNearbyMessage(playerid, 10.0,X11_PLUM, "change songs on Boombox", ReturnName(playerid));
				}
				case MUSIC_VEHICLE:
				{
				    if(IsPlayerInAnyVehicle(playerid))
				    {
					    SetMusicStream(MUSIC_VEHICLE, GetPlayerVehicleID(playerid), ListURLMusic[listitem][LinkURL]);
						SendNearbyMessage(playerid, 10.0,X11_PLUM, "** %s change songs on Vehicle Radio", ReturnName(playerid));
					}
				}
			}
		}
	}
	if(dialogid == DIALOG_ACCENT)
	{
		if(response)
		{
			strcpy(PlayerData[playerid][pAccent], ListAccent[listitem][accName], 24);
			SendServerMessage(playerid, "You changed your accent to a '%s'", PlayerData[playerid][pAccent]);
		}
	}
	if(dialogid == DIALOG_ORIGIN)
	{
		if (response)
		{
		    if (isnull(inputtext) || strlen(inputtext) > 32) {
		        ShowPlayerDialog(playerid, DIALOG_ORIGIN, DIALOG_STYLE_INPUT, "Origin", "Please enter the geographical origin of your character below:", "Submit", "Cancel");
			}
			else for (new i = 0, len = strlen(inputtext); i != len; i ++) {
			    if ((inputtext[i] >= 'A' && inputtext[i] <= 'Z') || (inputtext[i] >= 'a' && inputtext[i] <= 'z') || (inputtext[i] >= '0' && inputtext[i] <= '9') || (inputtext[i] == ' ') || (inputtext[i] == ',') || (inputtext[i] == '.'))
					continue;

				else return ShowPlayerDialog(playerid, DIALOG_ORIGIN, DIALOG_STYLE_INPUT, "Origin", "Error: Only letters and numbers are accepted in the origin.\n\nPlease enter the geographical origin of your character below:", "Submit", "Cancel");
			}

			format(PlayerData[playerid][pOrigin], 32, inputtext);
	  		ShowCharacterSetup(playerid);
		}
		else
		{
			ShowCharacterSetup(playerid);
		}
	}
    if(dialogid == DIALOG_MAKECHAR)
	{
	    if(response)
	    {
		    if(strlen(inputtext) < 1 || strlen(inputtext) > 24)
				return ShowPlayerDialog(playerid, DIALOG_MAKECHAR, DIALOG_STYLE_INPUT, "Character Name", "Silahkan masukan nama karaktermu:\n(note) nama karakter harus nama Roleplay!", "Submit", "Cancel");

			if(!IsRoleplayName(inputtext))
				return ShowPlayerDialog(playerid, DIALOG_MAKECHAR, DIALOG_STYLE_INPUT, "Character Name", "Silahkan masukan nama karaktermu:\n(note) nama karakter harus nama Roleplay!", "Submit", "Cancel");

			new characterQuery[178];
			mysql_format(sqlcon, characterQuery, sizeof(characterQuery), "SELECT * FROM `characters` WHERE `Name` = '%s'", inputtext);
			mysql_tquery(sqlcon, characterQuery, "InsertPlayerName", "ds", playerid, inputtext);

		    format(PlayerData[playerid][pUCP], 22, GetName(playerid));
			ShowCharacterSetup(playerid);
		}
		else
		{
			ShowCharacterSetup(playerid);
		}
	}
    if(dialogid == DIALOG_GENDER)
	{
		if(response)
		{
			if(listitem == 0)
			{
				PlayerData[playerid][pGender] = 1;
				ShowModelSelectionMenu(playerid, "Male Skins", MODEL_SELECTION_SPAWN, g_aMaleSkins, sizeof(g_aMaleSkins), -16.0, 0.0, -55.0);
			}
			if(listitem == 1)
			{
				PlayerData[playerid][pGender] = 2;
				ShowModelSelectionMenu(playerid, "Female Skins", MODEL_SELECTION_SPAWN, g_aFemaleSkins, sizeof(g_aFemaleSkins), -16.0, 0.0, -55.0);
			}
		}
		else
		{
			ShowCharacterSetup(playerid);
		}
	}
    if(dialogid == DIALOG_BIRTHDATE)
	{
		if (response)
		{
		    new
				iDay,
				iMonth,
				iYear;

		    new const
		        arrMonthDays[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

		    if (sscanf(inputtext, "p</>ddd", iDay, iMonth, iYear)) {
		        ShowPlayerDialog(playerid, DIALOG_BIRTHDATE, DIALOG_STYLE_INPUT, "Date of Birth", "Error: Invalid format specified!\n\nPlease enter your date of birth below (DD/MM/YYYY):", "Submit", "Cancel");
			}
			else if (iYear < 1900 || iYear > 2014) {
			    ShowPlayerDialog(playerid, DIALOG_BIRTHDATE, DIALOG_STYLE_INPUT, "Date of Birth", "Error: Invalid year specified!\n\nPlease enter your date of birth below (DD/MM/YYYY):", "Submit", "Cancel");
			}
			else if (iMonth < 1 || iMonth > 12) {
			    ShowPlayerDialog(playerid, DIALOG_BIRTHDATE, DIALOG_STYLE_INPUT, "Date of Birth", "Error: Invalid month specified!\n\nPlease enter your date of birth below (DD/MM/YYYY):", "Submit", "Cancel");
			}
			else if (iDay < 1 || iDay > arrMonthDays[iMonth - 1]) {
			    ShowPlayerDialog(playerid, DIALOG_BIRTHDATE, DIALOG_STYLE_INPUT, "Date of Birth", "Error: Invalid day specified!\n\nPlease enter your date of birth below (DD/MM/YYYY):", "Submit", "Cancel");
			}
			else 
			{
			    format(PlayerData[playerid][pBirthdate], 24, inputtext);
				ShowCharacterSetup(playerid);
			}
		}
		else
		{
			ShowCharacterSetup(playerid);
		}
	}
	if(dialogid == DIALOG_CHARACTER_LIST)
	{
		if(response)
		{
			if (PlayerChar[playerid][listitem][0] == EOS)
				return ShowCharacterSetup(playerid);

			PlayerData[playerid][pChar] = listitem;

			ShowPlayerDialog(playerid, DIALOG_CHAR_OPTION, DIALOG_STYLE_LIST, "OT - Char Menu", "Start playing\nRemove this character", "Select", "Quit");
		}
		else
			KickEx(playerid);
	}
	if(dialogid == DIALOG_CHARACTER_SETUP)
	{
		if(response)
		{
			switch(listitem)
			{
				case 0:
				{
					ShowPlayerDialog(playerid, DIALOG_MAKECHAR, DIALOG_STYLE_INPUT, "Character Name", "Silahkan masukan nama karaktermu:\n(note) nama karakter harus nama Roleplay!", "Submit", "Cancel");
				}
				case 1:
				{
					ShowPlayerDialog(playerid, DIALOG_ORIGIN, DIALOG_STYLE_INPUT, "Origin", "Please enter the geographical origin of your character below:", "Submit", "Cancel");
				}		
				case 2:
				{
					ShowPlayerDialog(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, "Character Gender", "Male\nFemale", "Submit", "Cancel");
				}
				case 3:
				{
					ShowPlayerDialog(playerid, DIALOG_BIRTHDATE, DIALOG_STYLE_INPUT, "Date of Birth", "Please enter your date of birth below (DD/MM/YYYY):", "Submit", "Cancel");
				}
				case 4:
				{
					if(!strlen(PlayerData[playerid][pTempName]))
						return SendErrorMessage(playerid, "You must specify a character name."), ShowCharacterSetup(playerid);	

					if (!strlen(PlayerData[playerid][pOrigin]))
						return SendErrorMessage(playerid, "You must specify an origin."), ShowCharacterSetup(playerid);

					if(!PlayerData[playerid][pGender])
						return SendErrorMessage(playerid, "You must specify a character gender."), ShowCharacterSetup(playerid);

					if (!strlen(PlayerData[playerid][pBirthdate]))
						return SendErrorMessage(playerid, "You must specify a birth date."), ShowCharacterSetup(playerid);

					new query[256];
					mysql_format(sqlcon,query,sizeof(query),"INSERT INTO `characters` (`Name`, `UCP`, `Registered`, `PosX`, `PosY`, `PosZ`, `Skin`) VALUES('%e', '%e', '%d', '%.4f', '%.4f', '%.4f', '%d')", PlayerData[playerid][pTempName], GetName(playerid), gettime(), -1415.9169,-300.1727,14.1484, PlayerData[playerid][pSkin]);
					mysql_tquery(sqlcon, query, "OnPlayerCharacterCreated", "d", playerid);

				}
			}
		}
		else
			ShowCharacterList(playerid);
	}
	if(dialogid == DIALOG_TRASH)
	{
		if(response)
		{
			PlayerData[playerid][pTrashVehicleID] = GetPlayerVehicleID(playerid);
			OnTrash[playerid] = 1;
			SendClientMessage(playerid,COLOR_WHITE, "(Trashmaster) {ffffff}Cari tong sampah dan letakan di kendaraan truck mu, dan hati hati dijalan!.");
		
			for(new i = 0; i < MAX_TRASH; i++) if(TrashData[i][TrashExists] && TrashData[i][TrashLevel] > 0)
			{					
				TrashIcons[playerid][i] = CreateDynamicMapIcon(TrashData[i][TrashX], TrashData[i][TrashY], TrashData[i][TrashZ] + 0.5, 56, 0, _, _, playerid, 8000.0, MAPICON_GLOBAL);
			}	
		}
		else RemovePlayerFromVehicle(playerid);
	}
	return 1;
}

public OnQueryError(errorid, const error[], const callback[], const query[], MySQL:handle)
{
    SendAdminMessage(X11_TOMATO, "MySQL: An error encountered [ ERR_ID:%d / query printed on DB logs ]", errorid);
	Log_Write("Logs/db_err.txt", "[%s] ERROR: %d / Query: %s - Callback: %s", ReturnDate(), errorid, query, callback);
	return 1;
}

public OnVehicleSirenStateChange(playerid, vehicleid, newstate)
{
    return 1;
}

public Streamer_OnPluginError(const error[]) {
	printf("[STREAMER ERROR] %s", error);
	return 1;
}
public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED && newkeys & KEY_JUMP && !(oldkeys & KEY_JUMP))
        ApplyAnimation(playerid, "GYMNASIUM", "gym_jog_falloff", 4.0, 0, 1, 1, 0, 0, 1);

    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED && newkeys & KEY_FIRE && !(oldkeys & KEY_FIRE))
        ApplyAnimation(playerid, "GYMNASIUM", "gym_jog_falloff", 4.0, 0, 1, 1, 0, 0, 1);


	if(PRESSED(KEY_WALK) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		if(!GetEngineStatus(GetPlayerVehicleID(playerid)))
		{
			if(GetVehicleSpeed(GetPlayerVehicleID(playerid)) >= 5 && GetVehicleSpeed(GetPlayerVehicleID(playerid)) <= 40)
			{
				if(++g_EngineHack[playerid] >= 2) {
					SendClientMessageEx(playerid, X11_TOMATO_1, "AntiCheat: "GREY"Kamu dikick dari server karena dicurigai menggunakan program ilegal (Vehicle engine hack).");
					KickEx(playerid);
				}
			}
		}
	}
    if((newkeys & KEY_CROUCH) && !(oldkeys & KEY_CROUCH) && GetPlayerState(playerid) == PLAYER_STATE_PASSENGER && GetPlayerCameraMode(playerid) == 55 && IsDriveByWeapon(playerid))
    {
		PlayerData[playerid][pLastWeapon] = GetWeapon(playerid);
		SetPlayerArmedWeapon(playerid, 0);
		ApplyAnimation(playerid, "PED", "CAR_GETIN_RHS", 4.1, 0, 0, 0, 0, 1, 1);
        defer GiveLastWeapon(playerid);
    }
	if (PRESSED(KEY_FIRE) || PRESSED(KEY_HANDBRAKE))
	{
		new weaponid;

		if((weaponid = GetWeapon(playerid)) != 0 && PlayerData[playerid][pAmmo][g_aWeaponSlots[weaponid]] <= 0&& GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) 
		{
			TogglePlayerControllable(playerid, 0);
			SetPlayerArmedWeapon(playerid, 0);
			TogglePlayerControllable(playerid, 1);
			SetCameraBehindPlayer(playerid);

			ShowMessage(playerid, "~y~~h~ERROR: ~w~Tidak ada peluru pada senjata ini!", 3, 1);
		}
	}
	new animlib[32], animname[32];
 	if (newkeys & KEY_CROUCH && IsPlayerInAnyVehicle(playerid))
	{
		cmd_gate(playerid, "\1");
	}
    if((newkeys & KEY_JUMP) && !IsPlayerInAnyVehicle(playerid) && !PlayerData[playerid][pAdmin] && !PlayerData[playerid][pInjured] && GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_USEJETPACK && !Falling[playerid])
    {
		GetAnimationName(GetPlayerAnimationIndex(playerid),animlib,32,animname,32);
		if(!strcmp(animname,"JUMP_LAND") || !strcmp(animname,"FALL_LAND"))
		{
	        PlayerPressedJump[playerid] ++;
	        SetTimerEx("PressJumpReset", 3000, false, "i", playerid); // Makes it where if they dont spam the jump key, they wont fall

	        if(PlayerPressedJump[playerid] >= 3) // change 3 to how many jump you want before they fall
	        {
	            ApplyAnimation(playerid, "PED", "BIKE_fall_off", 4.1, 0, 1, 1, 1, 0, 1); // applies the fallover animation
	            SetTimerEx("PressJump", 2000, false, "i", playerid); // Timer for how long the animation lasts
	            ShowText(playerid, "~n~~r~Bunny-hop not allowed!", 3);
	            Falling[playerid] = true;
	        }
	    }
    }
	if(newkeys & KEY_CTRL_BACK)
	{
		new wid = -1, id;
		if((wid = Weed_Nearest(playerid)) != -1)
		{
			if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
				return SendErrorMessage(playerid, "You must be on-foot!");

			if(WeedData[wid][weedGrow] < MAX_GROW)
				return SendErrorMessage(playerid, "Tanaman ini belum bisa dipanen (%d menit tersisa)", MAX_GROW-WeedData[wid][weedGrow]);

			if(WeedData[wid][weedHarvested])
				return SendErrorMessage(playerid, "Tanaman ini sedang dipanen.");

			if(IsValidLoadingBar(playerid))
				return SendErrorMessage(playerid, "Kamu tidak dapat melakukan ini sekarang");

			SetPlayerFace(playerid, WeedData[wid][weedPos][0], WeedData[wid][weedPos][1]);

			ApplyAnimation(playerid, "COP_AMBIENT", "Copbrowse_loop", 4.1, 1, 0, 0, 1, 0, 1);
			WeedData[wid][weedHarvested] = true;
			StartPlayerLoadingBar(playerid, 10, "Harvesting_weed", 1000);
			SetTimerEx("HarvestWeed", 10000, false, "dd", playerid, wid);
			SendNearbyMessage(playerid, 15.0, X11_PLUM, "** %s begins to harvest the weed.", ReturnName(playerid));
		}
		if(Tree_Nearest(playerid) != -1)
		{
			id = Tree_Nearest(playerid);

			if(!CheckPlayerJob(playerid, JOB_LUMBERJACK))
				return SendErrorMessage(playerid, "You are not work as Lumberjack!");

			if(TreeData[id][treeTime] > 0)
				return SendErrorMessage(playerid, "This tree still unavailable!");

			if(GetEquipedItem(playerid) != EQUIP_ITEM_AXE)
				return SendErrorMessage(playerid, "You must holding Axe!");

			if(TreeData[id][treeCut])
				return SendErrorMessage(playerid, "Unable to execute this tree! (being interacted with another player)");

			if(IsValidLoadingBar(playerid))
				return SendErrorMessage(playerid, "Can't do this at the moment.");

			if(PlayerData[playerid][pLumberDelay])
				return SendErrorMessage(playerid, "Kamu harus menunggu %d menit untuk bekerja kembali.", PlayerData[playerid][pLumberDelay]/60);
			
			if(IsHungerOrThirst(playerid))
				return SendErrorMessage(playerid, "Kamu terlalu lelah untuk bekerja.");

			if(!TreeData[id][treeCutted])
			{
				if(TreeData[id][treeProgress] < 100)
				{
					SetPlayerFace(playerid, TreeData[id][treePos][0], TreeData[id][treePos][1]);
					SetTimerEx("CutTree", 3000, false, "dd", playerid, id);
					StartPlayerLoadingBar(playerid, 3, "Cutting_down_Tree", 1000);
					TogglePlayerControllable(playerid, 0);
					ApplyAnimation(playerid,"BASEBALL", "Bat_M", 4.1, 1, 0, 0, 1, 0, 1);
					TreeData[id][treeCut] = true;
				}
			}
			else
			{
				new vnear = GetNearestVehicle(playerid, 5.0);
				if(vnear == INVALID_VEHICLE_ID)
					return SendErrorMessage(playerid, "You must close to Lumberjack vehicle!");

				if(!IsLumberVehicle(vnear))
					return SendErrorMessage(playerid, "You must close to Lumberjack vehicle!");

				if(VehicleData[vnear][vWood] >= GetMaxWood(vnear))
					return SendErrorMessage(playerid, "The vehicle is already loaded full of Timber! (%d/%d)", VehicleData[vnear][vWood], GetMaxWood(vnear));

				SetPlayerFace(playerid, TreeData[id][treePos][0], TreeData[id][treePos][1]);
				SetTimerEx("CreateTimber", 10000, false, "ddd", playerid, id, vnear);
				StartPlayerLoadingBar(playerid, 10, "Processing_Timber", 1000);
				TreeData[id][treeCut] = true;
				TogglePlayerControllable(playerid, 0);
				ApplyAnimation(playerid,"BOMBER","BOM_Plant_Loop", 4.1, 1, 0, 0, 1, 0, 1);
			}
		}
		for(new i = 0; i < MAX_VENDOR; i++) if(IsPlayerInDynamicCP(playerid, VendorData[i][vendorCP]) && PlayerData[playerid][pVendor] == -1 && !IsVendorUsed(i))
		{
			if(PlayerData[playerid][pMasked])
				return SendErrorMessage(playerid, "Buka maskermu terlebih dahulu!");

			if(IsHungerOrThirst(playerid))
				return SendErrorMessage(playerid, "Kamu terlalu lelah untuk bekerja.");

			PlayerData[playerid][pVendor] = i;
			SendClientMessage(playerid, COLOR_SERVER, "(Sidejob) {FFFFFF}Kamu mulai bekerja sebagai {FFFF00}Food Vendor");
			SetupPlayerVendor(playerid);
		}
	}
	if (newkeys & KEY_SPRINT && PlayerData[playerid][pSpawned] && PlayerData[playerid][pLoopAnim])
	{
	    ClearAnimations(playerid);

	    PlayerData[playerid][pLoopAnim] = false;
	}
	if(PRESSED(KEY_FIRE))
	{
	    if(PlayerData[playerid][pSpraying] && GetPlayerWeapon(playerid) == 41 && CheckPlayerJob(playerid, JOB_MECHANIC))
	    {     
	        ShowMessage(playerid, sprintf("~g~Spray the (Vehicle) ~y~%d/15", PlayerData[playerid][pColoring]), 1);
	        PlayerData[playerid][pSprayTime] = SetTimerEx("SprayTimer", 1000, true, "dd", playerid,PlayerData[playerid][pVehicle]);
	        PlayerData[playerid][pSpraying] = true;
		}
	}
	if(newkeys & KEY_SUBMISSION)
	{
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			cmd_v(playerid, "lock");
		}
	}
	if((newkeys & KEY_FIRE) && PlayerData[playerid][pTazer] && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		new Float:X, Float:Y, Float:Z;
		foreach(new i : Player)
		{
		    if(IsPlayerStreamedIn(i, playerid) && i != playerid && GetFactionType(i) != FACTION_POLICE)
		    {
			    GetPlayerPos(i, X, Y, Z);
				if(IsPlayerAimingAt(playerid,X,Y,Z,1) && IsPlayerInRangeOfPoint(playerid, 1.0, X, Y, Z) && !PlayerData[i][pTazed] && GetPlayerState(i) == PLAYER_STATE_ONFOOT && (GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(i)))
				{
		    		TogglePlayerControllable(i, 0);
					PlayerPlaySound(i, 6003, 0,0,0);
					PlayerPlaySound(playerid, 6003, 0,0,0);
					PlayerData[i][pTazed] = true;
					ApplyAnimation(i, "CRACK", "crckdeth4", 4.1, 0, 0, 0, 1, 0, 1);
					SetTimerEx("UnTazer", 5000, false, "d", i);
					SetPlayerChatBubble(i, "(( TAZED ))", COLOR_YELLOW, 15.0, 5000);
					break;
				}
			}
		}
	}
	if(RELEASE(KEY_FIRE))
	{
	    if(PlayerData[playerid][pSpraying] && CheckPlayerJob(playerid, JOB_MECHANIC))
	    {
	        KillTimer(PlayerData[playerid][pSprayTime]);
		}
	}
	if(newkeys & KEY_NO)
	{
		if (GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_DUCK)
		{
		    new
				count = 0,
				id = Item_Nearest(playerid),
		        string[320];

		    if (id != -1)
		    {
		        string = "";

		        for (new i = 0; i < MAX_DROPPED_ITEMS; i ++) if (count < MAX_LISTED_ITEMS && DroppedItems[i][droppedModel] && IsPlayerInRangeOfPoint(playerid, 1.5, DroppedItems[i][droppedPos][0], DroppedItems[i][droppedPos][1], DroppedItems[i][droppedPos][2]) && GetPlayerInterior(playerid) == DroppedItems[i][droppedInt] && GetPlayerVirtualWorld(playerid) == DroppedItems[i][droppedWorld]) {
		            NearestItems[playerid][count++] = i;

		            strcat(string, DroppedItems[i][droppedItem]);
		            strcat(string, "\n");
		        }
		        if (count == 1)
		        {
					if (PickupItem(playerid, id))
					{
			    		format(string, sizeof(string), "~g~%s~w~ added to inventory!", DroppedItems[id][droppedItem]);
			    		ShowMessage(playerid, string, 2);
						SendNearbyMessage(playerid, 30.0,X11_PLUM, "** %s has picked up a \"%s\".", ReturnName(playerid), DroppedItems[id][droppedItem]);
					}
					else
						SendErrorMessage(playerid, "You don't have any slot left in your inventory.");
				}
				else ShowPlayerDialog(playerid, DIALOG_PICKITEM, DIALOG_STYLE_LIST, "Pickup Items", string, "Pickup", "Cancel");
			}
		}
		cmd_v(playerid, "engine");
	}
	if(newkeys & KEY_YES)
	{
	    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	    {
			cmd_inventory(playerid, "");
		}
		else {

			if(IsEngineVehicle(GetPlayerVehicleID(playerid)))
				ShowPlayerDialog(playerid, DIALOG_VEHMENU, DIALOG_STYLE_LIST, "Vehicle Control", "Toggle engine\nToggle Lock\nToggle Lights\nToggle Neon", "Select", "Close");
		}
	}
	if((newkeys & KEY_SECONDARY_ATTACK ))
	{
		return cmd_enter(playerid, "");
	}
	return 1;
}

SetValidColor(playerid)
{
	if(!PlayerData[playerid][pOnDuty])
	{
		if(PlayerData[playerid][pJobduty])
		{
			if(CheckPlayerJob(playerid, JOB_MECHANIC))
			{
				SetPlayerColor(playerid, COLOR_LIGHTGREEN);
			}
			else if(CheckPlayerJob(playerid, JOB_TAXI))
			{
				SetPlayerColor(playerid, COLOR_YELLOW);
			}
		}
		else
		{
			SetPlayerColor(playerid, COLOR_WHITE);
		}

		if(!IsPlayerInAnyVehicle(playerid))
			SetPlayerSkin(playerid, PlayerData[playerid][pSkin]);
	}
	else
	{
		SetFactionColor(playerid);

		if(!IsPlayerInAnyVehicle(playerid))
			SetPlayerSkin(playerid, PlayerData[playerid][pFactionSkin]);
	}
	return 1;
}

public OnPlayerFirstSpawn(playerid) {
	if(IsPlayerSpawned(playerid)) {
		mysql_tquery(sqlcon, sprintf("SELECT * FROM `business_queue` WHERE `Username` = '%s'", GetName(playerid)), "OnBusinessQueue", "d", playerid);
		mysql_tquery(sqlcon, sprintf("SELECT * FROM `house_queue` WHERE `Username` = '%s'", GetName(playerid)), "OnHouseQueue", "d", playerid);
		mysql_tquery(sqlcon, sprintf("SELECT * FROM `flat_queue` WHERE `Username` = '%s'", GetName(playerid)), "OnFlatQueue", "d", playerid);

		if(Biz_GetCount(playerid)) {
			for(new i = 0; i < MAX_BUSINESS; i++) if(BizData[i][bizExists] && Biz_IsOwner(playerid, i)) {
				BizData[i][bizLastLogin] = 0;
			}
		}

		if(House_GetCount(playerid)) {
			foreach(new i : House) if(House_IsOwner(playerid, i)) {
				HouseData[i][houseLastLogin] = 0;
			}
		}

		if(Flat_GetCount(playerid)) {
			foreach(new i : Flat) if(Flat_IsOwner(playerid, i)) {
				FlatData[i][flatLastLogin] = 0;
			}
		}

		if(PlayerData[playerid][pMasked]) {

			PlayerData[playerid][pMaskLabel] = CreateDynamic3DTextLabel(sprintf("Mask_%d", PlayerData[playerid][pMaskID]), COLOR_WHITE, 0.0, 0.0, 0.1, 20.0, playerid, INVALID_VEHICLE_ID, 1, -1, -1, -1, 10.0);
			
			foreach(new i : Player)
			{
				ShowPlayerNameTagForPlayer(i, playerid, 0);
			}
		}
	}
	return 1;
}
public OnPlayerLogin(playerid) {

	return 1;
}
public OnPlayerSpawn(playerid)
{
	if(!LewatConnect[playerid])
		return Kick(playerid);

	if(!ValidSpawn[playerid])
		return Kick(playerid);

	if(!LewatClass[playerid])
		return Kick(playerid);
		
	if(!PlayerData[playerid][pSpawned])
	{	
		if(IsPlayerUsingAndroid(playerid)) 
			defer OnAutoAimCheck[2000](playerid);
	
	    PlayerData[playerid][pSpawned] = true;
	    PlayerData[playerid][pAdmin] = UcpData[playerid][ucpAdmin];

	    GivePlayerMoney(playerid, PlayerData[playerid][pMoney]);
	    SetPlayerHealth(playerid, PlayerData[playerid][pHealth]);
	    SetPlayerArmour(playerid, PlayerData[playerid][pArmor]);
	    SetPlayerScore(playerid, PlayerData[playerid][pLevel]);
	    SetPlayerVirtualWorld(playerid, PlayerData[playerid][pWorld]);
		SetPlayerInterior(playerid, PlayerData[playerid][pInterior]);

		PlayerTextDrawSetString(playerid, MONEYTD[playerid], sprintf("$%s", FormatNumber(PlayerData[playerid][pMoney])));
		Streamer_ToggleIdleUpdate(playerid, true);
		Streamer_ToggleItemUpdate(playerid, STREAMER_TYPE_OBJECT, true);

		FreezePlayer(playerid, 3000);
		
		PlayerTextDrawShow(playerid, LOGOTD[playerid]);

		TextDrawShowForPlayer(playerid,sen);
		TextDrawShowForPlayer(playerid,koma2);

		
		SetValidColor(playerid);

		for (new i = 0; i < 100; i ++)
		{
			SendClientMessage(playerid, -1, "");
		}
		SendServerMessage(playerid, "Selamat datang {00FF00}%s.", ReturnName(playerid));
		SendClientMessageEx(playerid, -1, "{00FFFF}(MOTD) {FFFF00}%s", MotdData[motdPlayer]);
		if(PlayerData[playerid][pAdmin] > 0)
			SendClientMessageEx(playerid, -1, "{FF0000}(Admin MOTD) {FFFF00}%s", MotdData[motdAdmin]);

		SendServerMessage(playerid, "Today is {FFFF00}%s", ConvertTimestamp(Timestamp:Now()));		
		CallLocalFunction("OnPlayerFirstSpawn", "d", playerid);

		ShowPlayerHUD(playerid);

		foreach(new i : Player) if(!PlayerData[i][pTogLogin])
		{
			new country[24], city[24], str[144];
			GetPlayerCountry(playerid, country, sizeof(country));
			GetPlayerCity(playerid, city, sizeof(city));

			format(str, sizeof(str), "* "YELLOW"%s "WHITE"is now connected to "SERVER_NAME"%s.", GetName(playerid, false), !strcmp(country, "Unknown", true) ? ("") : sprintf("(%s, %s)", city, country));
			SendClientMessage(i, X11_WHITE, str);
		}


		if(!IsPlayerUsingAndroid(playerid)) {
			SendClientCheck(playerid, 72, 0, 0, 2);
			defer OnSobeitCheck[10000](playerid);
		}


		if(PlayerData[playerid][pPos][0] == 0.0 && PlayerData[playerid][pPos][1] == 0.0 && PlayerData[playerid][pPos][2] == 0.0) {

			SetPlayerPos(playerid, -1415.9169,-300.1727,14.1484);
			SetPlayerFacingAngle(playerid, 134.7111);
			SendServerMessage(playerid, "Spawn-mu dipindahkan karena ada error saat meload posisi terakhir.");
			SetPlayerHealth(playerid, 100);
		}
	}
	if(PlayerData[playerid][pJailTime] > 0)
	{
	    if (PlayerData[playerid][pArrest])
	        SetPlayerArrest(playerid);
	    else
	    {
		    SetPlayerPos(playerid, 197.6346, 175.3765, 1003.0234);

		    SetPlayerInterior(playerid, 3);

		    SetPlayerVirtualWorld(playerid, (playerid + 100));
		    SetPlayerFacingAngle(playerid, 0.0);
		    SetCameraBehindPlayer(playerid);
		}
		PlayerTextDrawShow(playerid, JAILTD[playerid]);
	    SendServerMessage(playerid, "You have %d seconds of remaining jail time.", PlayerData[playerid][pJailTime]);

		Aksesoris_Sync(playerid);
	}
    else
	{
		if(PlayerData[playerid][pDead])
		{
			PlayerData[playerid][pInjured] = false;
			PlayerData[playerid][pDead] = false;
			
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
			Streamer_Update(playerid, STREAMER_TYPE_OBJECT);

			SetPlayerHealth(playerid, 100);
			SetPlayerPos(playerid, -2655.2048,634.7786,14.4531);
			SetPlayerFacingAngle(playerid, 179.1246);
			SetCameraBehindPlayer(playerid);
			ResetWeapons(playerid);
			TogglePlayerControllable(playerid, 1);

			SendServerMessage(playerid, "You have been respawned at {FFFF00}San Fierro Hospital {FFFFFF}and fined {FF0000}$50.00");
			GiveMoney(playerid, -5000, "Bayar hospital");
			ResetPlayerDamages(playerid);

			Aksesoris_Sync(playerid);

			RemoveDrag(playerid);

			DragCheck(playerid);
		}
		else
		{
			SetValidColor(playerid);
			SetPlayerVirtualWorld(playerid, PlayerData[playerid][pWorld]);
			SetPlayerInterior(playerid, PlayerData[playerid][pInterior]);
			SetWeapons(playerid);
		
			SetPlayerArmedWeapon(playerid, 0);

			if(PlayerData[playerid][pInjured] && PlayerData[playerid][pJailTime] < 1)
			{
				SetPlayerPos(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);
				ApplyAnimation(playerid, "WUZI", "CS_DEAD_GUY", 4.1, 0, 0, 0, 1, 0, 1);
				PlayerData[playerid][pInjured] = true;
				SetPlayerHealth(playerid, 100);
				PlayerData[playerid][pInjuredTime] = 300;
				SendClientMessage(playerid, COLOR_LIGHTRED, "(Warning) {FFFFFF}You have been {E20000}downed.{FFFFFF} You may choose to {44C300}/accept death");
				SendClientMessage(playerid, COLOR_WHITE, "...after your death timer expires or wait until you are revived.");
				CallLocalFunction("OnPlayerInjured", "d", playerid);

				SQL_SaveCharacter(playerid);
			}

			if(PlayerData[playerid][pAduty])
				SetPlayerColor(playerid, COLOR_RED);

			Aksesoris_Sync(playerid);
		}
	}
	return 1;
}


public OnClientCheckResponse(playerid, actionid, memaddr, retndata)
{
	if (retndata != 192 && actionid != 72)
	{
		SendAdminMessage(X11_TOMATO, "AntiCheat: Cheat detected on "YELLOW"%s(%s) "WHITE"possibly using "RED"Blue Eclipse/S0beit", GetName(playerid), GetUsername(playerid));
		KickEx(playerid);
	}

	return 1;
}

public OnPlayerShootRightLeg(playerid, targetid, Float:amount, weaponid)
{
	if(weaponid >= 22 && weaponid <= 38) {
		PlayerData[targetid][pBullets][5]++;
		if(PlayerData[targetid][pDamages][5] > 0)
		{
			PlayerData[targetid][pDamages][5] -= amount;
			if(PlayerData[targetid][pDamages][5] <= 0)
			{
				PlayerData[targetid][pDamages][5] = 0.0;
			}
		}
	}
    return 1;
}

public OnPlayerShootLeftLeg(playerid, targetid, Float:amount, weaponid)
{
	if(weaponid >= 22 && weaponid <= 38) {
		PlayerData[targetid][pBullets][6]++;
		if(PlayerData[targetid][pDamages][6] > 0)
		{
			PlayerData[targetid][pDamages][6] -= amount;
			if(PlayerData[targetid][pDamages][6] <= 0)
			{
				PlayerData[targetid][pDamages][6] = 0;
			}
		}
	}
    return 1;
}
public OnPlayerShootHead(playerid, targetid, Float:amount, weaponid)
{
	if(weaponid >= 22 && weaponid <= 38) {
		PlayerData[targetid][pBullets][0]++;
		SetTimerEx("HidePlayerBox", 500, false, "dd", targetid, _:ShowPlayerBox(targetid, 0xFF000066));
		if(PlayerData[targetid][pDamages][0] > 0)
		{
			PlayerData[targetid][pDamages][0] -= amount;
			if(PlayerData[targetid][pDamages][0] <= 0)
			{
				PlayerData[targetid][pDamages][0] = 0;
			}
		}
	}
    return 1;
}
public OnPlayerShootGroin(playerid, targetid, Float:amount, weaponid)
{
	if(weaponid >= 22 && weaponid <= 38) {
		PlayerData[targetid][pBullets][3]++;
		if(PlayerData[targetid][pDamages][4] > 0)
		{
			PlayerData[targetid][pDamages][4] -= amount;
			if(PlayerData[targetid][pDamages][4] <= 0)
			{
				PlayerData[targetid][pDamages][4] = 0;
			}
		}
	}
    return 1;
}
public OnPlayerShootTorso(playerid, targetid, Float:amount, weaponid)
{
	if(weaponid >= 22 && weaponid <= 38) {
		PlayerData[targetid][pBullets][1]++;
		if(PlayerData[targetid][pDamages][1] > 0)
		{
			PlayerData[targetid][pDamages][1] -= amount;
			if(PlayerData[targetid][pDamages][1] <= 0)
			{
				PlayerData[targetid][pDamages][1] = 0;
			}
		}
	}
    return 1;
}

public OnPlayerShootLeftArm(playerid, targetid, Float:amount, weaponid)
{
	if(weaponid >= 22 && weaponid <= 38) {
		PlayerData[targetid][pBullets][3]++;
		if(PlayerData[targetid][pDamages][3] > 0)
		{
			PlayerData[targetid][pDamages][3] -= amount;
			if(PlayerData[targetid][pDamages][3] < 0)
			{
				PlayerData[targetid][pDamages][3] = 0;
			}
		}
	}
    return 1;
}

public OnPlayerShootRightArm(playerid, targetid, Float:amount, weaponid)
{
	if(weaponid >= 22 && weaponid <= 38) {
		PlayerData[targetid][pBullets][2]++;
		if(PlayerData[targetid][pDamages][2] > 0)
		{
			PlayerData[targetid][pDamages][2] -= amount;
			if(PlayerData[targetid][pDamages][2] <= 0)
			{
				PlayerData[targetid][pDamages][2] = 0;
			}
		}
	}
    return 1;
}

public OnPlayerStreamIn(playerid, forplayerid)
{
    if (PlayerData[playerid][pMasked]) {
		ShowPlayerNameTagForPlayer(forplayerid, playerid, 0);
	}
	else
	    ShowPlayerNameTagForPlayer(forplayerid, playerid, 1);
	return 1;
}

public OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart)
{
	if(GetFactionType(playerid) == FACTION_POLICE) {
		if(HasRubberBullet[playerid] && weaponid == 25 && !IsPlayerInAnyVehicle(damagedid) && !IsPlayerInAnyVehicle(playerid))
		{
			if(PlayerData[damagedid][pInjured])
				return 1;

			new Float:pos[3];
			GetPlayerPos(damagedid, pos[0], pos[1], pos[2]);
			if(!PlayerRubbed[damagedid] && GetPlayerDistanceFromPoint(playerid, pos[0], pos[1], pos[2]) < 25.0)
			{
				if(IsPlayerInAnyVehicle(damagedid)) 
					RemovePlayerFromVehicle(damagedid);

				TogglePlayerControllable(damagedid, false);
				ApplyAnimation(damagedid, "CRACK", "crckdeth2", 4.0, 1, 1, 1, -1, 0, 1);
				defer UnfreezeRubber[10000](damagedid);

				PlayerRubbed[damagedid] = true;

				SendNearbyMessage(playerid, 25.0, X11_PLUM, "** %s has been hit with a rubber bullet by %s and has been forced to the ground.", ReturnName(damagedid), ReturnName(playerid));
				return 1;
			}
		}
	}
	return 1;
}

public OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart)
{
	if (PlayerData[playerid][pBandage])
	{
	    SendClientMessage(playerid, COLOR_LIGHTRED, "(Warning){FFFFFF} Your bandage is no longer in effect as you took damage.");

        PlayerData[playerid][pBandage] = false;
		KillTimer(PlayerData[playerid][pAidTimer]);
	}
	if (PlayerData[playerid][pFirstAid])
	{
	    SendClientMessage(playerid, COLOR_LIGHTRED, "(Warning){FFFFFF} Your medkit is no longer in effect as you took damage.");

        PlayerData[playerid][pFirstAid] = false;
		KillTimer(PlayerData[playerid][pAidTimer]);
	}

    new Float:health,
		Float:armour;

	GetPlayerHealth(playerid, health);
	GetPlayerArmour(playerid, armour);
	if(issuerid != INVALID_PLAYER_ID)
	{
		if(weaponid == 25 && HasRubberBullet[issuerid]) {
			SetPlayerHealth(playerid, health);
			return 1;
		}

		new Float:damage, Float:velodamage;
		switch(weaponid)
		{
		    case 0: damage = 2.0; // Fist
			case 1: damage = 5.0; // Brass Knuckles
			case 2: damage = 5.0;   // Golf Club
			case 3: damage = 5.0; // Nightstick
			case 4: damage = 7.0; // Knife
			case 5: damage = 5.0; // Baseball Bat
			case 6: damage = 5.0; // Shovel
			case 7: damage = 5.0; // Pool Cue
			case 8: damage = 8.0; // Katana
			case 9: damage = 10.0; // Chainsaw
			case 14: damage = 2.0; // Flowers
			case 15: damage = 5.0; // Cane
			case 16: damage = 50.0; // Grenade
			case 18: damage = 20.0; // Molotov
			case 22: damage = RandomFloat(13.0, 17.0), velodamage = RandomFloat(1.0, 4.0); // Colt45
			case 23: damage = RandomFloat(15.0, 20.0), velodamage = RandomFloat(2.0, 7.0); // SLC
			case 28, 29, 32: damage = RandomFloat(17.0, 23.0), velodamage = RandomFloat(1.0, 4.0); // UZI, MP5, Tec
			case 24: damage = RandomFloat(25.0, 30.0), velodamage = RandomFloat(5.0, 8.0); // Desert Eagle
			case 25, 26, 27: // Shotgun, Sawnoff Shotgun, CombatShotgun
			{
			    new Float: p_x, Float: p_y, Float: p_z;
			    GetPlayerPos(playerid, p_x, p_y, p_z);
			    new Float: dist = GetPlayerDistanceFromPoint(playerid, p_x, p_y, p_z);

			    if (dist < 5.0)
					damage = RandomFloat(30.0, 35.0), velodamage = RandomFloat(1.0, 7.0);

				else if (dist < 10.0)
					damage = RandomFloat(23.0, 27.0), velodamage = RandomFloat(1.0, 6.0);

				else if (dist < 15.0)
					damage = RandomFloat(15.0, 20.0), velodamage = RandomFloat(1.0, 5.0);

				else if (dist < 20.0)
					damage = RandomFloat(10.0, 14.0), velodamage = RandomFloat(1.0, 4.0);

				else if (dist < 30.0)
					damage = RandomFloat(5.0, 8.0), velodamage = RandomFloat(1.0, 3.0);
			}
			case 30: damage = RandomFloat(16.0, 23.0), RandomFloat(1.0, 5.0); // AK47
			case 31: damage = RandomFloat(16.0, 20.0), RandomFloat(1.0, 7.0); // M4A1
			case 33: damage = RandomFloat(30.0, 50.0), velodamage = RandomFloat(5.0, 10.0); // Country Rifle
			case 34: damage = RandomFloat(70.0, 75.0); // Sniper Rifle
			case 35: damage = 0.0; // RPG
			case 36: damage = 0.0; // HS Rocket
			case 38: damage = 0.0; // Minigun
		}
        if(armour > 0.0 && weaponid >= 22 && weaponid <= 38)
		{
		    if(armour - damage <= 5.0)
				SetPlayerArmour(playerid, 0.0);
	 		else 
			{
			 	if(PlayerData[playerid][pHighVelocity][g_aWeaponSlots[weaponid]]) 
				{
						
					new Float:final_damage = damage + velodamage;
					SetPlayerArmour(playerid, armour - final_damage);
				}
				else 
				{
					SetPlayerArmour(playerid, armour - damage);
				}
			}
		}
		else
		{
 			if(weaponid >= 22 && weaponid <= 38) {
				if(PlayerData[playerid][pHighVelocity][g_aWeaponSlots[weaponid]]) {

					new Float:final_damage = damage + velodamage;

					SetPlayerHealth(playerid, health - final_damage);
				}
				else {
					SetPlayerHealth(playerid, health - damage);
				}
			}
			else {
				SetPlayerHealth(playerid, health - damage);
			}

			if(armour)
			    SetPlayerArmour(playerid, armour);
		}
		CallLocalFunction("OnPlayerDamage", "ddfdd", playerid, issuerid, damage, weaponid, bodypart);
		
	}
	else {
		SetPlayerHealth(playerid, health - amount);
	}
	
	return 1;
}

public OnPlayerText(playerid, text[])
{
	text[0] = toupper(text[0]);
	new lstr[512];

	if(!PlayerData[playerid][pSpawned]) {
		SendErrorMessage(playerid, "Kamu tidak bisa chat sebelum spawn.");
		return 0;
	}


	if(gettime() < chat_floodProtect[playerid] && !PlayerData[playerid][pAdmin]) {
		ShowMessage(playerid, "~r~ERROR: ~w~Dilarang spam text chat!", 3, 1);
		return 0;
	}
	chat_floodProtect[playerid] = gettime() + 2;

	if(PlayerData[playerid][pAduty] && PlayerData[playerid][pAdmin] > 0)
	{
		SendNearbyMessage(playerid, 30.0, COLOR_RED, "{FF0000}%s: {FFFFFF}(( %s ))", PlayerData[playerid][pUCP], text);
		SetPlayerChatBubble(playerid, sprintf("Admin: %s", text), X11_RED_2, 15.0, 5000);
		return 0;
	}
	if(PlayerData[playerid][pCallNews]) {

		SendFactionMessageEx(FACTION_NEWS, X11_LIGHTBLUE, "193 CALL: "WHITE"%s (%s) "YELLOW"(ph: %d)", GetName(playerid, false), GetSpecificLocation(playerid), PlayerData[playerid][pPhoneNumber]);
		SendFactionMessageEx(FACTION_NEWS, X11_LIGHTBLUE, "DESCRIPTION: "WHITE"%s", text);

		SendClientMessage(playerid, X11_LIGHTBLUE, "(News Operator)"WHITE" Your phone call has been forwarded to 123 - San Fierro News");
	    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	    RemovePlayerAttachedObject(playerid, 3);
		PlayerData[playerid][pCallNews] = false;
	}
	if(ServiceIndex[playerid] != 0)
	{
		ProcessServiceCall(playerid, text);
		return 0;
	}
	if(PlayerData[playerid][pCallLine] != INVALID_PLAYER_ID && !PlayerData[playerid][pIncomingCall])
	{

		if(PlayerData[playerid][pDrugCondition]) {

			new
				len = strlen(text);

    		static const charset[] = "qwertyuiopasdfghjklzxcvbnm";

			for(new i = 0; i < len / 2; i++) {

				text[i] = (charset[random(sizeof charset)]);

			}
		}
		format(lstr, sizeof(lstr), "(Phone) %s says: %s", ReturnName(playerid), text);
		ProxDetector(playerid, 20.0, X11_WHITE, lstr);
		SetPlayerChatBubble(playerid, text, COLOR_WHITE, 10.0, 3000);

		SendClientMessageEx(PlayerData[playerid][pCallLine], COLOR_YELLOW, "(Phone) Caller says: %s", text);
		return 0;
	}
	else
	{
		if(PlayerData[playerid][pMicrophone]) {
			SendNearbyMessage(playerid, 50.0, X11_ORANGE_2, "(Mic) %s says: %s", ReturnName(playerid), text);
		}
		else {
			if(!strcmp(PlayerData[playerid][pAccent], "None", true))
			{
				if(PlayerData[playerid][pDrugCondition]) {

					new
						len = strlen(text);

					static const charset[] = "qwertyuiopasdfghjklzxcvbnm";

					for(new i = 0; i < len / 2; i++) {

						text[i] = (charset[random(sizeof charset)]);
					}
				}
				format(lstr, sizeof(lstr), "%s says: %s", ReturnName(playerid), text);
				ProxDetector(playerid, 20.0, X11_WHITE, lstr);
				SetPlayerChatBubble(playerid, text, COLOR_WHITE, 10.0, 3000);
				if(!IsPlayerInAnyVehicle(playerid) && !PlayerData[playerid][pInjured] && !PlayerData[playerid][pLoopAnim] && !PlayerData[playerid][pTogAnim] && GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_DUCK)
				{
					ApplyAnimation(playerid, "GANGS", "prtial_gngtlkA", 4.1, 0, 1, 1, 1, strlen(text) * 100, 1);
					SetTimerEx("StopChatting", strlen(text) * 100, false, "d", playerid);
				}
			}
			else
			{
				if(PlayerData[playerid][pDrugCondition]) {

					new
						len = strlen(text);

					static const charset[] = "qwertyuiopasdfghjklzxcvbnm";

					for(new i = 0; i < len / 2; i++) {

						text[i] = (charset[random(sizeof charset)]);
					}
				}
				format(lstr, sizeof(lstr), "%s (%s) says: %s", ReturnName(playerid), PlayerData[playerid][pAccent], text);
				ProxDetector(playerid, 20.0, X11_WHITE, lstr);
				SetPlayerChatBubble(playerid, text, COLOR_WHITE, 10.0, 3000);
				if(!IsPlayerInAnyVehicle(playerid) && !PlayerData[playerid][pInjured] && !PlayerData[playerid][pLoopAnim] && !PlayerData[playerid][pTogAnim] && GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_DUCK)
				{
					ApplyAnimation(playerid, "GANGS", "prtial_gngtlkA", 4.1, 0, 1, 1, 1, strlen(text) * 100, 1);
					SetTimerEx("StopChatting", strlen(text) * 100, false, "d", playerid);
				}
			}
		}
		return 0;
	}
}

public OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat, Float:new_x, Float:new_y, Float:new_z, Float:vel_x, Float:vel_y, Float:vel_z)
{
	if(VehicleData[vehicleid][vHandbrake])
	{
		if(VehicleData[vehicleid][vHandbrakePos][0] != new_x && VehicleData[vehicleid][vHandbrakePos][1] != new_y && VehicleData[vehicleid][vHandbrakePos][2] != new_z)
		{
			SetVehiclePos(vehicleid, VehicleData[vehicleid][vHandbrakePos][0], VehicleData[vehicleid][vHandbrakePos][1], VehicleData[vehicleid][vHandbrakePos][2]);
			SetVehicleZAngle(vehicleid, VehicleData[vehicleid][vHandbrakePos][3]);
		}
	}
	return 1;
}

public OnVehicleDamageStatusUpdate(vehicleid, playerid) {


	new Float:veh_health, panel, doors, lights, tires;
	GetVehicleHealth(vehicleid, veh_health);

	if(veh_health >= 1000.0 && VehicleData[vehicleid][vBodyUpgrade]) {
		GetVehicleDamageStatus(vehicleid, panel, doors, lights, tires);
		UpdateVehicleDamageStatus(vehicleid, 0, 0, 0, 0);
	}
	else {
		GetVehicleDamageStatus(vehicleid, panel, doors, lights, tires);
		UpdateVehicleDamageStatus(vehicleid, panel, doors, lights, tires);	
	}
	return 1;
}
public OnVehicleDeath(vehicleid, killerid) {

	if(IsRumpoVehicle(vehicleid)) {
		foreach(new i : Player) if(PlayerData[i][pRumpoVehicle] == vehicleid) {
			PlayerData[i][pRumpoVehicle] = INVALID_VEHICLE_ID;
			OnDeliveryWork[i] = false;
			VehicleData[vehicleid][vLoadedCrate] = 0;
			SendServerMessage(i, "Kamu gagal bekerja menjadi Delivery Driver dikarenakan rumpo-mu hancur.");
			break;
		}
	}

	VehicleData[vehicleid][vState] = VEHICLE_STATE_DEATH;
	VehicleData[vehicleid][vKillerID] = killerid;
	VehicleData[vehicleid][vDeathTime] = gettime() + 15;

	return 1;
}

public OnVehicleSpawn(vehicleid)
{

	defer Vehicle_UpdatePosition(vehicleid);

	if(VehicleData[vehicleid][vState] == VEHICLE_STATE_DEATH) {
		if(Vehicle_GetType(vehicleid) == VEHICLE_TYPE_PLAYER)
		{
			if(IsValidVehicle(vehicleid)) {
				new
					killerid = VehicleData[vehicleid][vKillerID];

				if(killerid != INVALID_PLAYER_ID && IsPlayerConnected(killerid))
					SendAdminMessage(X11_TOMATO, "VehicleAction: %s kemungkinan menghancurkan kendaraan %s(ID:%d) milik %s.", GetName(killerid, false), GetVehicleName(vehicleid), vehicleid, Vehicle_GetOwnerName(vehicleid));

				if(VehicleData[vehicleid][vInsurance] > 0)
				{
					VehicleData[vehicleid][vInsurance] --;
					VehicleData[vehicleid][vInsuTime] = gettime() + (1 * 10800);
					Vehicle_SetState(vehicleid, VEHICLE_STATE_INSURANCE);

					Vehicle_Save(vehicleid);

					foreach(new pid : Player) if (VehicleData[vehicleid][vExtraID] == PlayerData[pid][pID])
					{
						SendClientMessageEx(pid, X11_LIGHTBLUE, "(Vehicle) "WHITE"Kendaraan {00FFFF}%s {FFFFFF}milikmu telah hancur, kamu bisa Claim setelah 3 jam dari Insurance.", GetVehicleName(vehicleid));
						break;
					}
					Vehicle_Delete(vehicleid, false);
				}
				else
				{
					foreach(new pid : Player) if (VehicleData[vehicleid][vExtraID] == PlayerData[pid][pID])
					{
						SendClientMessageEx(pid, X11_LIGHTBLUE, "(Vehicle) "WHITE"Kendaraan {00FFFF}%s {FFFFFF}milikmu telah hancur dan tidak akan dan tidak memiliki Insurance lagi.", GetVehicleName(vehicleid));
						break;
					}
					Vehicle_Delete(vehicleid, true);
				}
				VehicleData[vehicleid][vDeathTime] = 0;
			}
			else {
				foreach(new pid : Player) if (VehicleData[vehicleid][vExtraID] == PlayerData[pid][pID])
				{
					SendClientMessageEx(pid, X11_LIGHTBLUE, "(Vehicle) "WHITE"Kendaraan {00FFFF}%s {FFFFFF}milikmu telah hancur karena hal yang invalid.", GetVehicleName(vehicleid));
					SendClientMessageEx(pid,  X11_WHITE, "...Maka dari itu kendaraan akan ter-spawn ditempat yang terakhir.");
					break;
				}		
				for(new slot = 0; slot < MAX_VEHICLE_OBJECT; slot++) if(VehicleObjects[vehicleid][slot][vehObjectExists])
				{
					if(IsValidDynamicObject(VehicleObjects[vehicleid][slot][vehObject]))
						DestroyDynamicObject(VehicleObjects[vehicleid][slot][vehObject]);

					VehicleObjects[vehicleid][slot][vehObject] = INVALID_OBJECT_ID;

				}
				for(new idx = 0; idx < 3; idx++) {

					for(new i = 0; i < 2; i++) {
						if(IsValidDynamicObject(NeonObject[vehicleid][idx][i])) {
							DestroyDynamicObject(NeonObject[vehicleid][idx][i]);
							NeonObject[vehicleid][idx][i] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
						}
					}
				}

				if(IsValidVehicle(vehicleid))
					Vehicle_GetStatus(vehicleid);

				defer SpawnBackPlayerVehicle[1000](vehicleid);	
			}
		}
		else if(Vehicle_GetType(vehicleid) == VEHICLE_TYPE_RENTAL)
		{
			foreach(new pid : Player) if (VehicleData[vehicleid][vExtraID] == PlayerData[pid][pID])
			{
				GiveMoney(pid, -250, "Denda rental");
				SendServerMessage(pid, "Kendaraan Rental milikmu (%s) telah hancur, kamu dikenai denda sebesar {009000}$250,0!", GetVehicleName(vehicleid));
				break;
			}
			Vehicle_Delete(vehicleid, true);
		}
		else if(Vehicle_GetType(vehicleid) == VEHICLE_TYPE_SIDEJOB) {

			VehicleData[vehicleid][vFuel] = 100;
			RepairVehicle(vehicleid);
		}
		else if(Vehicle_GetType(vehicleid) == VEHICLE_TYPE_FACTION) {

			new query[322];
			mysql_format(sqlcon, query, sizeof(query), "UPDATE `factiongaragevehs` SET `Health` = '%.2f', `Spawned` = '0' WHERE `ID` = '%d'", 300.0, VehicleData[vehicleid][vExtraID]);
			mysql_tquery(sqlcon, query);

			Vehicle_Delete(vehicleid, false);
		}
	}
	return 1;
}



/* Main Functions */

GetVehicleCategoryName(modelid) {
	new string[56];
	switch(Model_GetCategory(modelid)) 
	{
		case CATEGORY_AIRPLANE: string = "Airplane";
		case CATEGORY_BIKE: string = "Bike/Motorcycle";
		case CATEGORY_BOAT: string = "Boat";
		case CATEGORY_CONVERTIBLE: string = "Convertible";
		case CATEGORY_HELICOPTER: string = "Helicopter";
		case CATEGORY_INDUSTRIAL: string = "Industrial";
		case CATEGORY_LOWRIDER: string = "Lowrider";
		case CATEGORY_OFFROAD: string = "Offroad";
		case CATEGORY_PUBLIC: string = "Public";
		case CATEGORY_SALOONS: string = "Saloons";
		case CATEGORY_SPORT: string = "Sport";
		case CATEGORY_STATION_WAGON: string = "Station Wagon";
		case CATEGORY_UNIQUE: string = "Unique";
		default: string = "Unknown";
	}
	return string;
}

House_LimitFurniture(id) {
	new limit = 0;
	switch(HouseData[id][houseType]) {
		case 1: limit = 35;
		case 2: limit = 45;
		case 3: limit = 50;
	}

	if(HouseData[id][houseFurnitureLevel] > 1) {
		new total_new_furn = HouseData[id][houseFurnitureLevel] * 5;
		limit += total_new_furn;
	}
	return limit;
}
Flat_LimitFurniture(flatid) {
	new limit = 0;
	switch(FlatData[flatid][flatType]) {
		case FLAT_TYPE_LOW: limit = 30;
		case FLAT_TYPE_MEDIUM: limit = 35;
		case FLAT_TYPE_HIGH: limit = 40;
	}

	if(FlatData[flatid][flatFurnitureLevel] > 1) {
		new total_new_furn = FlatData[flatid][flatFurnitureLevel] * 5;
		limit += total_new_furn;
	}
	return limit;
}
IsPoliceVehicle(vehicleid) {
	return (Vehicle_GetFaction(vehicleid) == FACTION_POLICE ? true : false);
}

IsMedicVehicle(vehicleid) {
	return (Vehicle_GetFaction(vehicleid) == FACTION_MEDIC ? true : false);
}

IsNewsVehicle(vehicleid) {
	return (Vehicle_GetFaction(vehicleid) == FACTION_NEWS ? true : false);
}

GetPlayerOutsideInfo(playerid) {
	GetPlayerPos(playerid, PlayerData[playerid][pLastPos][0],  PlayerData[playerid][pLastPos][1],  PlayerData[playerid][pLastPos][2]);
	PlayerData[playerid][pLastWorld] = GetPlayerVirtualWorld(playerid);
	PlayerData[playerid][pLastInterior] = GetPlayerInterior(playerid);

	return 1;
}

ResetPlayerOutsideInfo(playerid) {
	for(new i = 0; i < 3; i++) {
		PlayerData[playerid][pLastPos][i] = 0.0;
	}
	PlayerData[playerid][pLastInterior] = 0;
	PlayerData[playerid][pLastWorld] = 0;

	return 1;
}
ResetInteriorData(playerid) {
	PlayerData[playerid][pInHouse] = -1;
	PlayerData[playerid][pInBiz] = -1;
	PlayerData[playerid][pInWorkshop] = -1;
	PlayerData[playerid][pInFlat] = -1;
	PlayerData[playerid][pInDoor] = -1;

	return 1;
}

IsPlayerOnJob(playerid) {
	if(OnDeliveryWork[playerid])
		return 1;

	if(IsPlayerWorkInBus(playerid))
		return 1;

	if(OnSweeping[playerid])
		return 1;

	if(OnTrash[playerid])
		return 1;

	if(OnMower[playerid])
		return 1;

	return 0;

	
}
Flat_FurnitureCount(id)
{
	new count = 0;

	foreach(new i : Furniture) if (FurnitureData[i][furnitureProperty] == FlatData[id][flatID] && FurnitureData[i][furniturePropertyType] == FURNITURE_TYPE_FLAT) {
	    count++;
	}
	return count;
}

FixText(text[])
{
    new len = strlen(text);
    if(len > 1)
    {
        for (new i = 0; i < len; i++)
        {
            if(text[i] == 92)
            {
                if(text[i+1] == 'n')
                {
                    text[i] = '\n';
                    for (new j = i+1; j < len; j++) text[j] = text[j+1], text[j+1] = 0;
                    continue;
                }
                if(text[i+1] == 't')
                {
                    text[i] = '\t';
                    for (new j = i+1; j < len-1; j++) text[j] = text[j+1], text[j+1] = 0;
                    continue;
                }

                if(text[i+1] == 92)
                {
                    text[i] = 92;
                    for (new j = i+1; j < len-1; j++) text[j] = text[j+1], text[j+1] = 0;
                }
            }
        }
    }
    return 1;
}

SetHoodStatus(vehicleid, status)
{
    static engine, lights, alarm, doors, bonnet, boot, objective;
    GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
    return SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, status, boot, objective);
}

Character_CanUpdate(playerid) {
	if(!PlayerData[playerid][pAduty] && !PlayerData[playerid][pJailTime])
		return 1;
	
	return 0;
}
Garage_ReturnID(garage_sqlid) {
	new index = -1;
	foreach(new i : Garage) if(GarageData[i][garageID] == garage_sqlid) {
		index = i;
		break;
	}
	return index;
}
ReturnWeaponCount(playerid)
{
	new
		count,
	    weapon,
	    ammo;

	for (new i = 0; i < 12; i ++)
	{
	    GetPlayerWeaponData(playerid, i, weapon, ammo);

	    if (weapon > 0 && ammo > 0) count++;
	}
	return count;
}


function OnQueryExecute(playerid, query[])
{
	new str[221];

    if(strfind(query, "SELECT", true) != -1) {
		format(str, sizeof(str),  "Success: MySQL returned %d rows from your query.\n\nPlease specify the MySQL query to execute below:", cache_num_rows());
        ShowPlayerDialog(playerid, DIALOG_EXECUTE, DIALOG_STYLE_INPUT, "Execute Query",str, "Execute", "Back");
	}
    else {
		format(str, sizeof(str), "Success: Query executed successfully (affected rows: %d).\n\nPlease specify the MySQL query to execute below:", cache_affected_rows());
        ShowPlayerDialog(playerid, DIALOG_EXECUTE, DIALOG_STYLE_INPUT, "Execute Query", str, "Execute", "Back");
	}
    return 1;
}

IsPlayerDrunk(playerid) {
	return PlayerData[playerid][pIsDrunk];
}
SetPlayerDrunkLevelEx(playerid, level = 0, time = 0) {


	if(PlayerData[playerid][pIsDrunk] && level != 0)
		return 0;

	if(!level) {
		SetPlayerDrunkLevel(playerid, 0);
		PlayerData[playerid][pIsDrunk] = false;
	}
	else {
		SetPlayerDrunkLevel(playerid, level);
		PlayerData[playerid][pIsDrunk] = true;
		defer StopDrunkEffect[time](playerid);
	}
	return 1;
}
ResetPlayerDamages(playerid) {

	for(new i = 0; i < 7; i++)
	{
		PlayerData[playerid][pDamages][i] = 100.0;
		PlayerData[playerid][pBullets][i] = 0;
	}

	Damage_Reset(playerid);

	return 1;
}
SaveServerStatistics() {

	new time = GetTickCount();

	SaveServerData();
	printf("** Saved server data in %dms", GetTickCount() - time);

	SaveEconomyData();
	printf("** Saved server economy in %dms", GetTickCount() - time);

	foreach(new i : Vehicle) if(Vehicle_GetType(i) == VEHICLE_TYPE_RENTAL || Vehicle_GetType(i) == VEHICLE_TYPE_PLAYER) {
		Vehicle_Save(i);
	}

	printf("** Saved vehicle data in %dms", GetTickCount() - time);


	foreach(new i : Player) if(IsPlayerSpawned(i)) {
		SQL_SaveCharacter(i);
	}

	printf("** Saved player data in %dms", GetTickCount() - time);

	forex(i, MAX_TREE) if(TreeData[i][treeExists])
	{
		Tree_Save(i);
	}
	printf("** Saved tree data in %dms.", GetTickCount() - time);

	for(new i = 0; i < MAX_WEED; i ++) if(WeedData[i][weedExists]) {
		Weed_Save(i);
	}
	printf("** Saved  weed data  in %dms.", GetTickCount() - time);

	for(new i = 0; i < MAX_SPEEDCAM; i++) if(SpeedData[i][speedExists]) {
		Speed_Save(i);
	}
	printf("** Saved speedcam data in %dms", GetTickCount() - time);

	for(new i = 0; i < MAX_DEALER; i++) if(DealerData[i][dealerExists]) {
		SQL_SaveDealership(i);
	}
	printf("** Saved dealer data in %dms", GetTickCount() - time);

	foreach(new i : House) {
		House_Save(i);
	}
	printf("** Saved house data  in %dms", GetTickCount() - time);

	for(new i = 0; i < MAX_BUSINESS; i++) if(BizData[i][bizExists]) {
		Business_Save(i);
	}
	printf("** Saved business data in %dms", GetTickCount() - time);

	for(new i =  0; i <  MAX_TREE; i++) if(TreeData[i][treeExists]) {
		Tree_Save(i);
	}
	printf("** Saved tree data in %dms", GetTickCount() - time);

	foreach(new i :  Flat) {
		Flat_Save(i);
	}
	printf("** Saved flat data in %dms", GetTickCount() - time);

	foreach(new i : Pump) {
		Pump_Save(i);
	}
	printf("** Saved pump data in %dms", GetTickCount() - time);

	return printf("There is %d player when the server shutdown.", Iter_Count(Player));
}
function OnAdminSetName(playerid, userid, newname[]) {

	new query[256];

	if(cache_num_rows())
		return SendErrorMessage(playerid, "Nama karakter \"%s\" sudah digunakan.", newname);

	foreach(new i : House) if(House_IsOwner(userid, i)) {

		format(HouseData[i][houseOwnerName], MAX_PLAYER_NAME, newname);
		House_Save(i);
		House_Refresh(i);
	}
	foreach(new i : Flat) if(Flat_IsOwner(userid, i)) {
		format(FlatData[i][flatOwnerName], MAX_PLAYER_NAME, newname);
		Flat_Save(i);
		Flat_Sync(i);
	}
	foreach(new i : Workshop) if(Workshop_IsOwner(userid, i)) {
		format(WorkshopData[i][wsOwnerName], MAX_PLAYER_NAME, newname);
		Workshop_Save(i);
		Workshop_Sync(i);
	}
	for(new i = 0; i < MAX_BUSINESS; i++) if(BizData[i][bizExists] && Biz_IsOwner(userid, i)) {
		format(BizData[i][bizOwnerName], MAX_PLAYER_NAME, newname);
		Business_Save(i);
		Business_Refresh(i);
	}

	mysql_format(sqlcon, query,sizeof(query),"UPDATE `characters` SET `Name` = '%e' WHERE `Name` = '%e'", newname, PlayerData[userid][pName]);
	mysql_tquery(sqlcon, query);
	mysql_format(sqlcon, query, sizeof(query), "UPDATE `workshop_employee` SET `Name` = '%e' WHERE `Name` = '%e'", newname, PlayerData[userid][pName]);
	mysql_tquery(sqlcon, query);
	mysql_format(sqlcon, query, sizeof(query), "UPDATE `housekeys` SET `Name` = '%e' WHERE `Name` = '%e'", newname, PlayerData[userid][pName]);
	mysql_tquery(sqlcon, query);

	mysql_format(sqlcon, query, sizeof(query), "UPDATE `flatkeys` SET `Name` = '%e' WHERE `Name` = '%e'", newname, PlayerData[userid][pName]);
	mysql_tquery(sqlcon, query);

	SendServerMessage(userid, "Your name has been changed to "YELLOW"%s", newname);
	SendServerMessage(playerid, "You've been changed %s name to "YELLOW"%s", GetName(userid), newname);

	Log_Write("Logs/changename.txt", "[%s] %s has changed %s name to %s.", ReturnDate(), GetUsername(playerid), GetName(userid, false), newname);
	
	SetPlayerName(userid, newname);
	format(PlayerData[userid][pName], MAX_PLAYER_NAME, newname);
	return 1;
}
CountPlayerShootWound(playerid) {

	new total = 0;

	for(new i = 0; i < 7; i++) if(PlayerData[playerid][pBullets][i] > 0) {
		total++;
	}
	return total;
}
RandomLetter()
    return 65 + random(25);

PayCheck(playerid) {

	mysql_tquery(sqlcon, sprintf("SELECT * FROM `playersalary` WHERE `owner` = '%d'", PlayerData[playerid][pID]), "OnSalaryReceived", "d", playerid);
	return 1;
}

function OnSalaryReceived(playerid) {

	new total_salary = 0;

	for(new i = 0; i < cache_num_rows(); i++) {

		new amount;
		cache_get_value_name_int(i, "amount", amount);
		total_salary += amount;
	}
	new taxval = total_salary/100*GovData[govTax];

	PlayerData[playerid][pBank] += total_salary-taxval;
	PlayerData[playerid][pPaycheck] = 3600;
	PlayerData[playerid][pSalary] = 0;

	SendClientMessage(playerid, X11_LIGHTBLUE, "----------------------------------------------------");

	SendClientMessageEx(playerid, X11_WHITE, "Total salary: "GREEN"$%s", FormatNumber(total_salary));
	SendClientMessageEx(playerid, X11_WHITE, "Bank interest: "GREEN"$%s", FormatNumber(total_salary - taxval));
	SendClientMessageEx(playerid, X11_WHITE, "New balance: "GREEN"$%s", FormatNumber(PlayerData[playerid][pBank]));

	SendClientMessage(playerid, X11_LIGHTBLUE, "----------------------------------------------------");
	notification.Show(playerid, "PAYCHECK", sprintf("Paycheck has been taken! (%s)", ReturnDate()), "hud:radar_cash");

	mysql_tquery(sqlcon, sprintf("DELETE FROM `playersalary` WHERE `owner` = '%d'", PlayerData[playerid][pID]));


	if(PlayerData[playerid][pQuitjob]) {
		if(--PlayerData[playerid][pQuitjob] <= 0) {
			PlayerData[playerid][pQuitjob] = 0;
			SendServerMessage(playerid, "Kamu bisa keluar dari pekerjaanmu sekarang!");
		}
	}

	return 1;

}
function LoadPlayerPassword(playerid, inputtext[]) {

	new hash[BCRYPT_HASH_LENGTH];

	cache_get_value_name(0, "Password", hash, sizeof(hash));
	
	bcrypt_verify(playerid, "OnPlayerPasswordChecked", inputtext, hash);
	return 1;
}
function FactionMemberCheck(playerid) {

	new str[1012];
	if(cache_num_rows())
	{
		format(str, sizeof(str), "Name\tRank\tTotal Duty Time\n");
		for(new i = 0; i < cache_num_rows(); i++)
		{
			new tempname[24], rank, hour, minute, second;
			cache_get_value_name(i, "Name", tempname, 24);
			cache_get_value_name_int(i, "FactionRank", rank);
			cache_get_value_name_int(i, "FactionHour", hour);
			cache_get_value_name_int(i, "FactionMinute", minute);
			cache_get_value_name_int(i, "FactionSecond", second);

			format(str, sizeof(str), "%s%s\t%d\t%02d:%02d:%02d\n", str, tempname, rank, hour, minute, second);
		}
		ShowPlayerDialog(playerid, DIALOG_FACTION_RETURN, DIALOG_STYLE_TABLIST_HEADERS, "Total Member(s)", str, "Return", "");
	}
	return 1;
}
function OnPlayerCharacterCreated(playerid) {

	if(!IsPlayerConnected(playerid))
		return 0;
		
	PlayerData[playerid][pID] = cache_insert_id();
	PlayerData[playerid][pPos][0] = -1415.9169;
	PlayerData[playerid][pPos][1] = -300.1727;
	PlayerData[playerid][pPos][2] = 14.1484;
	format(PlayerData[playerid][pName], MAX_PLAYER_NAME, PlayerData[playerid][pTempName]);
	SetupPlayerData(playerid);
	CancelSelectTextDraw(playerid);
	return 1;
}

bool:IsPlayerHaveProperty(playerid) {

	new bool:index = false;
	foreach(new i : House) if(HouseData[i][houseOwner] == PlayerData[playerid][pID]) {
		index = true;
		break;
	}

	foreach(new i : Flat) if(FlatData[i][flatOwner] == PlayerData[playerid][pID]){
		index = true;
		break;
	}	

	return index;
}

CountPlayerHouseSlot(playerid) {

	new slot = 1;

	if(GetPlayerVIPLevel(playerid) == VIP_LEVEL_SILVER || GetPlayerVIPLevel(playerid) == VIP_LEVEL_GOLD)
		slot += 1;

	return slot;
}

CountPlayerBusinessSlot(playerid) {

	new slot = 1;

	if(GetPlayerVIPLevel(playerid) == VIP_LEVEL_GOLD)
		slot += 1;

	return slot;
}


CountPlayerVehicleSlot(playerid) {

	new slot = 1;

	if(IsPlayerHouseGuest(playerid) || IsPlayerFlatGuest(playerid))
		slot += 1;
		
	if(IsPlayerHaveProperty(playerid))
		slot += 2;

	if(GetPlayerVIPLevel(playerid) == VIP_LEVEL_SILVER) 
		slot += 1;

	else if(GetPlayerVIPLevel(playerid) == VIP_LEVEL_GOLD)
		slot += 2;

	return slot;
}

ShowPlayerStats(playerid, targetid)
{
	new str[2060], header[232], Float:hp, Float:ar, cat[2060];
	GetPlayerHealth(playerid, hp);
	GetPlayerArmour(playerid, ar);
	format(header, sizeof(header), "{AFAFAF}%s", ReturnDate(true));
	format(str, sizeof(str), "{F7FF00}In Character\n");
	strcat(cat, str);
	format(str, sizeof(str), "{FFFFFF}Name: [{C6E2FF}%s{FFFFFF}] ({FF8000}%d{FFFFFF}) | Gender: [{C6E2FF}%s{FFFFFF}] | Birthdate: [{C6E2FF}%s{FFFFFF}] | Money: [{009000}$%s{FFFFFF}] | Bank: [{009000}$%s{FFFFFF}]\n",
	PlayerData[playerid][pName], PlayerData[playerid][pID], Gender_Name[PlayerData[playerid][pGender]], PlayerData[playerid][pBirthdate], FormatNumber(GetMoney(playerid)), FormatNumber(PlayerData[playerid][pBank]));
	strcat(cat, str);
	format(str, sizeof(str), "Origin: [{C6E2FF}%s{FFFFFF}] | Number: [{C6E2FF}%d{FFFFFF}] | Job: [{C6E2FF}%s, %s{FFFFFF}] | Faction: [{C6E2FF}%s{FFFFFF}] | Faction Rank: [{C6E2FF}%s{FFFFFF}] | Married With: [{C6E2FF}%s{FFFFFF}]\n",
	PlayerData[playerid][pOrigin], PlayerData[playerid][pPhoneNumber], GetJobName(PlayerData[playerid][pJob]), GetJobName(PlayerData[playerid][pJob2]), Faction_GetName(playerid), Faction_GetRank(playerid), MarryWith[playerid]);
	strcat(cat, str);
	format(str, sizeof(str), "Vehicle Slot: [{C6E2FF}%d{FFFFFF}] | House Slot: [{C6E2FF}%d{FFFFFF}] | Business Slot: [{C6E2FF}%d{FFFFFF}]\n",
	CountPlayerVehicleSlot(playerid), CountPlayerHouseSlot(playerid), CountPlayerBusinessSlot(playerid));
	strcat(cat, str);
	format(str, sizeof(str), "\n{F7FF00}Out of Character\n");
	strcat(cat, str);
	format(str, sizeof(str), "{FFFFFF}Username: [{C6E2FF}%s{FFFFFF}] ({FF8000}%d{FFFFFF}) | Registration Date: [{C6E2FF}%s %s %s %i, %02d:%02d:%02d{FFFFFF}]\n",
	PlayerData[playerid][pUCP], UcpData[playerid][ucpID], ConvertTimestamp(Timestamp:UcpData[playerid][ucpTime]));
	strcat(cat, str);
	format(str, sizeof(str), "Time Played: [{C6E2FF}%d hours %d minutes %d seconds{FFFFFF}] | Mask ID: [{C6E2FF}Mask_#%d{FFFFFF}] | Last Vehicle ID: [{C6E2FF}%d{FFFFFF}]\n",
	PlayerData[playerid][pHour], PlayerData[playerid][pMinute], PlayerData[playerid][pSecond], PlayerData[playerid][pMaskID], PlayerData[playerid][pLastVehicleID]);
	strcat(cat, str);
	format(str, sizeof(str), "Health: [{FF0000}%.2f/100.0{FFFFFF}] | Armour: [{C6E2FF}%.2f/100.0{FFFFFF}] | Interior: [{C6E2FF}%d{FFFFFF}] | Virtual World: [{C6E2FF}%d{FFFFFF}]\n",
	hp, ar, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));
	strcat(cat, str);
	format(str, sizeof(str), "\nDonater Level: [{C6E2FF}%s{FFFFFF}] | Donater Point [{C6E2FF}%d{FFFFFF}]\n",
	GetVIPName(PlayerVIP[playerid][vipLevel]), PlayerData[playerid][pCoin]);
	strcat(cat, str);
	ShowPlayerDialog(targetid, DIALOG_NONE, DIALOG_STYLE_MSGBOX, header, cat, "Close", "");
	return 1;
}

Furniture_Spawn(furnitureid) {

	if(Iter_Contains(Furniture, furnitureid))
	{
		FurnitureData[furnitureid][furnitureObject] = CreateDynamicObject(
			FurnitureData[furnitureid][furnitureModel],
			FurnitureData[furnitureid][furniturePos][0],
			FurnitureData[furnitureid][furniturePos][1],
			FurnitureData[furnitureid][furniturePos][2],
			FurnitureData[furnitureid][furnitureRot][0],
			FurnitureData[furnitureid][furnitureRot][1],
			FurnitureData[furnitureid][furnitureRot][2],
			FurnitureData[furnitureid][furnitureWorld],
			FurnitureData[furnitureid][furnitureInterior]
		);

		if(FurnitureData[furnitureid][furnitureTextureModelid] != 0) {
			SetDynamicObjectMaterial(FurnitureData[furnitureid][furnitureObject], 0, FurnitureData[furnitureid][furnitureTextureModelid], FurnitureData[furnitureid][furnitureTextureTXDName], FurnitureData[furnitureid][furnitureTextureName]);
		}

		Streamer_AppendArrayData(STREAMER_TYPE_OBJECT, FurnitureData[furnitureid][furnitureObject], E_STREAMER_WORLD_ID, FurnitureData[furnitureid][furnitureWorld]);
	}
	return 1;
}

Furniture_Sync(furnitureid) {

	if(Iter_Contains(Furniture, furnitureid))
	{
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FurnitureData[furnitureid][furnitureObject], E_STREAMER_X, FurnitureData[furnitureid][furniturePos][0]);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FurnitureData[furnitureid][furnitureObject], E_STREAMER_Y, FurnitureData[furnitureid][furniturePos][1]);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FurnitureData[furnitureid][furnitureObject], E_STREAMER_Z, FurnitureData[furnitureid][furniturePos][2]);

		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FurnitureData[furnitureid][furnitureObject], E_STREAMER_R_X, FurnitureData[furnitureid][furnitureRot][0]);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FurnitureData[furnitureid][furnitureObject], E_STREAMER_R_Y, FurnitureData[furnitureid][furnitureRot][1]);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FurnitureData[furnitureid][furnitureObject], E_STREAMER_R_Z, FurnitureData[furnitureid][furnitureRot][2]);
	
		if(FurnitureData[furnitureid][furnitureTextureModelid] != 0) {
			SetDynamicObjectMaterial(FurnitureData[furnitureid][furnitureObject], 0, FurnitureData[furnitureid][furnitureTextureModelid], FurnitureData[furnitureid][furnitureTextureTXDName], FurnitureData[furnitureid][furnitureTextureName]);
		}

		Streamer_AppendArrayData(STREAMER_TYPE_OBJECT, FurnitureData[furnitureid][furnitureObject], E_STREAMER_WORLD_ID, FurnitureData[furnitureid][furnitureWorld]);
	}
	return 1;
}
/* Main Timer */

timer UnfreezeRubber[10000](playerid) {
	ClearAnimations(playerid, 1);
	PlayerRubbed[playerid] = false;
	TogglePlayerControllable(playerid, true);
	return 1;
}
timer OnAutoAimCheck[2000](playerid) {
	if(IsPlayerHaveAutoaim(playerid)) {
		SendClientMessageEx(playerid, X11_TOMATO_1, "AntiCheat: "GREY"Kamu dikick dari server karena dicurigai menggunakan program ilegal (Aimlock)");
		KickEx(playerid);
	}
	return 1;
}
task OnServerDataUpdate[1800000]() {
	fishPrice = RandomFloat(3.8,6.0);
	woodPrice = RandomEx(2500, 5000);
	return 1;
}

timer WeatherRotator[2400000]()
{
	new index = random(sizeof(g_aWeatherRotations));

	SetWeather(g_aWeatherRotations[index]);
}

timer FixVehicleEnterWorkshop[1000](vehicleid) {
	SetVehiclePos(vehicleid, -849.5128,410.4552,997.5434);
	SetVehicleZAngle(vehicleid, 359.6590);
	return 1;
}
timer StopDrunkEffect[5000](playerid) {

	if(!PlayerData[playerid][pIsDrunk])
		return 0;

	SetPlayerDrunkLevel(playerid, 0);
	PlayerData[playerid][pIsDrunk] = false;
	return 1;
}

timer SpawnBackPlayerVehicle[1000](vehicleid) {

	if(IsValidVehicle(vehicleid)) {
		SetVehicleToRespawn(vehicleid);
	}
	else {
		vehicleid = Vehicle_Create(VehicleData[vehicleid][vModel], VehicleData[vehicleid][vPos][0], VehicleData[vehicleid][vPos][1], VehicleData[vehicleid][vPos][2], VehicleData[vehicleid][vPos][3], VehicleData[vehicleid][vColor][0], VehicleData[vehicleid][vColor][1], 0, false, VehicleData[vehicleid][vPlate]);
	}

	UpdateVehicleDamageStatus(vehicleid, VehicleData[vehicleid][vDamage][0], VehicleData[vehicleid][vDamage][1], VehicleData[vehicleid][vDamage][2], VehicleData[vehicleid][vDamage][3]);
	SetVehicleHealth(vehicleid, VehicleData[vehicleid][vHealth]);
	for(new m = 0; m < 17; m++)
	{
		if(VehicleData[vehicleid][vMod][m]) AddVehicleComponent(vehicleid, VehicleData[vehicleid][vMod][m]);
	}
	SetVehiclePos(vehicleid, VehicleData[vehicleid][vPos][0], VehicleData[vehicleid][vPos][1], VehicleData[vehicleid][vPos][2]);
	SetVehicleZAngle(vehicleid, VehicleData[vehicleid][vPos][3]);

	ChangeVehicleColor(vehicleid,  VehicleData[vehicleid][vColor][0], VehicleData[vehicleid][vColor][1]);
	for(new i = 0; i < MAX_VEHICLE_OBJECT; i++) if(VehicleObjects[vehicleid][i][vehObjectExists]) {
		Vehicle_AttachObject(vehicleid, i);
	}

	return 1;
}
timer UnstuckPlayerVehicle[1000](playerid, vehicleid) {

	SetVehicleToRespawn(vehicleid);

	UpdateVehicleDamageStatus(vehicleid, VehicleData[vehicleid][vDamage][0], VehicleData[vehicleid][vDamage][1], VehicleData[vehicleid][vDamage][2], VehicleData[vehicleid][vDamage][3]);
	SetVehicleHealth(vehicleid, VehicleData[vehicleid][vHealth]);
	for(new m = 0; m < 17; m++)
	{
		if(VehicleData[vehicleid][vMod][m]) AddVehicleComponent(vehicleid, VehicleData[vehicleid][vMod][m]);
	}
	SetVehiclePos(vehicleid, VehicleData[vehicleid][vPos][0], VehicleData[vehicleid][vPos][1], VehicleData[vehicleid][vPos][2]);
	SetVehicleZAngle(vehicleid, VehicleData[vehicleid][vPos][3]);
	SendServerMessage(playerid, "Your "YELLOW"%s "WHITE"has been unstucked.", GetVehicleName(vehicleid));

	ChangeVehicleColor(vehicleid,  VehicleData[vehicleid][vColor][0], VehicleData[vehicleid][vColor][1]);
	for(new i = 0; i < MAX_VEHICLE_OBJECT; i++) if(VehicleObjects[vehicleid][i][vehObjectExists]) {
		Vehicle_AttachObject(vehicleid, i);
	}
	Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
	return 1;
}
timer OnSobeitCheck[10000](playerid)
{
    new actionid = 0x5, memaddr = SOBEIT, retndata = 0x4;
    SendClientCheck(playerid, actionid, memaddr, CHECK_NULL, retndata);
    return 1;
}

timer GiveLastWeapon[500](playerid)
{
    SetPlayerArmedWeapon(playerid, PlayerData[playerid][pLastWeapon]);
    PlayerData[playerid][pLastWeapon] = 0;
    return 1;
}

timer Vehicle_UpdatePosition[2000](vehicleid)
{
	new
		Float:x,
		Float:y,
		Float:z,
		Float:a
	;

	GetVehiclePos(vehicleid, x, y, z);
	GetVehicleZAngle(vehicleid, a);

	SetVehiclePos(vehicleid, x, y, z);
	SetVehicleZAngle(vehicleid, a);
}

#include ".\legacy\Core\timer"
