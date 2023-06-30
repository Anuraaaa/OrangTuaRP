#define forex(%0,%1) for(new %0 = 0; %0 < %1; %0++)

#define function%0(%1) forward %0(%1); public %0(%1)

#define IsNull(%1) \
((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))

#define COLOR_YELLOW 			0xFFFF00FF
#define COLOR_ORANGE       		0xFF9900FF
#define COLOR_SERVER      		0xC6E2FFFF
#define COLOR_GREY   			0xAFAFAFFF
#define COLOR_PURPLE 			X11_PLUM
#define COLOR_CLIENT 			0xC6E2FFFF
#define COLOR_WHITE  			0xFFFFFFFF
#define COLOR_LIGHTRED    		0xFF6347FF
#define COLOR_LIGHTGREEN  		0x9ACD32FF
#define COLOR_RADIO 			0x8D8DFFFF
#define COLOR_DEPARTMENT		0xF0CC00FF
#define COLOR_GREEN       		0x33CC33FF
#define COLOR_RED 				0xFF0000FF
#define COLOR_LIGHTORANGE   	0xF7A763FF
#define COLOR_JOB				0xC6E2FFFF

#define DATABASE_ADDRESS 			"103.55.39.44"
#define DATABASE_USERNAME 			"independ_otrpuser"
#define DATABASE_NAME 				"independ_otrp"
#define DATABASE_PASSWORD 			"BG6tW@VPc7xYy2Z"

#define SERVER_NAME 			"Orang Tua Roleplay"
#define SERVER_VERSION 			"v12.13.9"

#if !defined BCRYPT_HASH_LENGTH
	#define BCRYPT_HASH_LENGTH 250
#endif

#if !defined BCRYPT_COST
	#define BCRYPT_COST 12
#endif

#define NO_PERMISSION "You don't have permission to use this command."
#define ERROR_INVALID_PLAYER "You have specified invalid player."
#define ERROR_INVALID_VEHICLE "You have specified invalid vehicle."
#define COOL_GREEN "{00D900}"
#define GREY_SAMP  "{A9C4E4}"
#define IsPlayerSpawned(%0) PlayerData[%0][pSpawned]

#define PermissionError(%0) SendErrorMessage(%0, "You don't have permission to use this command.")

#define MDC_ERROR               (21001)
#define MDC_SELECT              (21000)
#define MDC_OPEN                (45400)

#define PRESSED(%0) (((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))

#define PRESSING(%0,%1) \
	(%0 & (%1))

#define RELEASE(%0) (((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0)))

#define GetUsername(%0) PlayerData[%0][pUCP]

#define SendCustomMessage(%0,%1,%2,%3) \
    SendClientMessageEx(%0, %1, "("%2") ""{FFFFFF}"%3)

#define SendAdminAction(%0,%1) \
	SendClientMessageEx(%0, X11_TOMATO, "(Admin){FFFFFF} "%1)

#define SendServerMessage(%0,%1) \
	SendClientMessageEx(%0, X11_LIGHTGREEN, "(Server){FFFFFF} "%1)

#define SendSyntaxMessage(%0,%1) \
	SendClientMessageEx(%0, COLOR_GREY, "(Usage){FFFFFF} "%1)
	
#define SendErrorMessage(%0,%1) \
	SendClientMessageEx(%0, COLOR_GREY, "(Error) "%1)

#define GetVehicleName(%0) ReturnVehicleModelName(GetVehicleModel(%0))
#define SetPlayerLogged(%0) PlayerData[%0][pLogged]=true

#define BODY_PART_TORSO (3)
#define BODY_PART_GROIN (4)
#define BODY_PART_LEFT_ARM (5)
#define BODY_PART_RIGHT_ARM (6)
#define BODY_PART_LEFT_LEG (7)
#define BODY_PART_RIGHT_LEG (8)
#define BODY_PART_HEAD (9)

#define MAX_HOUSE_STORAGE			10
#define MAX_WHEAT					1000
#define MAX_TAGS					100
#define MAX_ACTOR 					200
#define MAX_WEAPONS 				55
#define MAX_BODY_PARTS 				7
#define MAX_HOUSE_FURNITURE			30
#define MAX_FURNITURE 				10000
#define MAX_PLAYER_TICKETS			15
#define MAX_PLAYER_VEHICLE 			1000
#define MAX_INVENTORY 				15
#define MAX_BUSINESS                100
#define MAX_DROPPED_ITEMS  			1000
#define MAX_RENTAL                  20
#define MAX_CRATES 					1000
#define MAX_WEED					1000
#define MAX_GROW                    20
#define MAX_LISTED_ITEMS 			10
#define MAX_FACTIONS				10
#define MAX_DDOORS					100
#define MAX_REPORTS					25
#define MAX_EMERGENCY				300
#define MAX_SPEEDCAM 				50
#define MAX_CONTACTS				15
#define MAX_CHARS					3
#define MAX_DEALER 					20
#define MAX_ATM 					50
#define MAX_ADVERT					50
#define MAX_HOUSES					300
#define MAX_VENDOR					3
#define MAX_TREE					200
#define MAX_GATES 					100
#define MAX_FACTION_VEHICLE			200
#define	MAX_DOOR					100
#define MAX_WORKSHOP    			30
#define MAX_PARKPOINT				50		
#define MAX_MAPOBJECTS				1000
#define MAX_FAMILY					20
#define MAX_FAMILY_STORAGE 			10
#define MAX_CHEAT					3
#define MAX_TRASH					100
#define MAX_PUBLIC_GARAGE			50
#define MAX_CAR_STORAGE				5

#define SOUND_FIREALARM_START   (3401)
#define SOUND_FIREALARM_END     (3402)