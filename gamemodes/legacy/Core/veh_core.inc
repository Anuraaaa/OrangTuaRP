#define MAX_VEHICLE_OBJECT	5

#define MAX_COLOR_MATERIAL	5

#define OBJECT_TYPE_BODY	1
#define OBJECT_TYPE_TEXT	2

enum E_VEHICLE_DATA
{
	vID,
	vExtraID,
	vColor[2],
	vModel,
	vLocked,
	vInsuranced,
	vInsurance,
	vInsuTime,
	vPlate[16],
	Float:vHealth,
	Float:vPos[4],
	vWorld,
	vInterior,
	Float:vFuel,
	vVehicle,
	vDamage[4],
	bool:vExists,
	vRental,
	vRentTime,
	vHouse,
	vPark,
	vWood,
	vPizza,
	vState,
	vMod[17],
	STREAMER_TAG_OBJECT:vToy[5],
	vToyID[5],
	cAttachedToy[5],
	Float:vToyPosX[5],
	Float:vToyPosY[5],
	Float:vToyPosZ[5],
	Float:vToyRotX[5],
	Float:vToyRotY[5],
	Float:vToyRotZ[5],
	vToyType[5],
	vToySize[5],
	vToyColor[5],
	bool:vHandbrake,
	Float:vHandbrakePos[4],
	vType,
	bool:vRepair,
	bool:vHood,
	vFactionType,
	vFaction,
	vKillerID,
	vPrice,
	STREAMER_TAG_OBJECT:vCrateObject,
	vLoadedCrate,
	bool:vHaveCrate,
	vGarage,
	vImpound,
	vImpoundPrice,
	vWeapon[3],
	vAmmo[3],
	vDurability[3],
	vHighVelocity[3],
	vPaintjob,
	vNeonColor,
	vTireLock,
	Timer:vTireLockTimer,
	Text3D:vTireLockText,
	vEngineUpgrade,
	vBodyUpgrade,
	vGarageID,
	bool:vNeonStatus,
	vDeathTime,
	bool:vELM,
	vOctaneSaver
};

enum carStorage {
	cItemID,
	cItemExists,
	cItemName[32 char],
	cItemModel,
	cItemQuantity
};

new VehicleData[MAX_VEHICLES][E_VEHICLE_DATA],
	CarStorage[MAX_VEHICLES][MAX_CAR_STORAGE][carStorage],
	STREAMER_TAG_OBJECT:NeonObject[MAX_VEHICLES][3][2];

#define Vehicle_GetType(%0) VehicleData[%0][vType]
#define Vehicle_GetState(%0) VehicleData[%0][vState]

#define VEHICLE_NEON_NONE 0
#define VEHICLE_NEON_RED 18647
#define VEHICLE_NEON_BLUE 18648
#define VEHICLE_NEON_GREEN 18649
#define VEHICLE_NEON_YELLOW 18650
#define VEHICLE_NEON_PINK 18651
#define VEHICLE_NEON_WHITE 18652

enum {
	VEHICLE_TOY_OBJECT = 0,
	VEHICLE_TOY_TEXT
};

enum E_NEON_OFFSET {
	Float:NeonX,
	Float:NeonY,
	Float:NeonZ
};

new const NeonOffsetData[212][E_NEON_OFFSET] = {
	{-0.924999,0.009999,-0.674999},
	{-0.979999,0.074999,-0.489999},
	{-1.034999,-0.029999,-0.579999},
	{-0.884999,1.834998,-1.099999},
	{-0.839999,-0.064999,-0.419999},
	{-0.914999,0.000000,-0.534999},
	{-1.129999,0.354999,-1.219999},
	{-1.214999,0.125000,-0.759999},
	{-0.664999,0.709999,-0.889999},
	{-0.914999,-0.294999,-0.474999},
	{-0.879999,0.000000,-0.389999},
	{-0.969999,0.004999,-0.559999},
	{-0.994999,-0.154999,-0.569999},
	{-0.919999,-0.069999,-0.719999},
	{-0.759999,-0.469999,-0.524999},
	{-0.949999,-0.009999,-0.524999},
	{-1.259999,-0.604999,-0.664999},
	{-2.255004,0.859999,-0.124999},
	{-1.004999,0.089999,-0.829999},
	{-0.934999,-0.009999,-0.584999},
	{-0.954999,-0.009999,-0.444999},
	{-0.929999,-0.029999,-0.589999},
	{-0.889999,0.009999,-0.609999},
	{-0.999999,0.164999,-0.714999},
	{-0.739999,0.039999,-0.234999},
	{-0.639999,2.475009,-0.789999},
	{-0.969999,0.000000,-0.464999},
	{-1.124999,-0.714999,-0.734999},
	{-1.124999,0.054999,-0.759999},
	{-0.844999,0.004999,-0.474999},
	{0.0,0.0,0.0},
	{-1.304998,2.300005,-0.714999},
	{0.0,0.0,0.0},
	{-0.579999,0.994999,-0.874999},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{-0.859999,-0.024999,-0.489999},
	{-1.314998,2.245003,-0.724999},
	{-0.969999,-0.034999,-0.674999},
	{-0.884999,0.034999,-0.644999},
	{-0.914999,-0.045000,-0.899999},
	{0.0,0.0,0.0},
	{-1.004999,-0.074999,-0.604999},
	{-0.809999,2.770015,-1.174999},
	{-1.064999,0.000000,0.135000},
	{-0.949999,0.000000,-0.519999},
	{0.0,0.0,0.0},
	{-1.004999,0.259999,-0.769999},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{-0.984999,-0.194999,-0.519999},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{-0.579999,0.979999,-0.859999},
	{-0.764999,-0.179999,-0.464999},
	{0.0,0.0,0.0},
	{-0.959999,-0.039999,-0.594999},
	{-0.919999,-0.069999,-0.719999},
	{-1.399998,0.554999,-1.819998},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{-0.989999,-0.064999,-0.489999},
	{-0.989999,-0.044999,-0.484999},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{-1.119999,-0.149999,-0.359999},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{-0.994999,-0.064999,-0.544999},
	{-0.904999,-0.054999,-0.549999},
	{0.0,0.0,0.0},
	{-0.979999,0.019999,-0.514999},
	{-0.804999,0.064999,-0.519999},
	{-0.854999,0.090000,-0.454999},
	{-0.879999,0.000000,-0.489999},
	{0.0,0.0,0.0},
	{-0.989999,0.000000,-0.759999},
	{-0.834999,-0.149999,-0.744999},
	{0.0,0.0,0.0},
	{-0.629999,0.164999,-0.374999},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{-1.019999,0.110000,-0.679999},
	{-1.054999,0.125000,-0.604999},
	{-0.874999,-0.009999,-0.569999},
	{-0.909999,0.000000,-0.459999},
	{0.0,0.0,0.0},
	{-0.909999,-0.199999,-0.639999},
	{-1.024999,0.184999,-0.809999},
	{-0.854999,0.029999,-0.469999},
	{0.0,0.0,0.0},
	{-1.149999,0.269999,-0.654999},
	{-0.969999,-1.404998,-0.199999},
	{-0.969999,0.189999,-0.574999},
	{0.0,0.0,0.0},
	{-0.909999,0.029999,-0.639999},
	{-0.909999,-0.184999,-0.639999},
	{-0.989999,-0.059999,-0.494999},
	{-1.019999,0.110000,-0.679999},
	{-0.904999,-0.249999,-0.509999},
	{-1.084999,-0.024999,-0.589999},
	{-1.334998,-0.424999,-0.979999},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{-0.969999,1.669998,-1.174999},
	{-1.454998,0.439999,-1.854998},
	{-0.989999,0.024999,-0.584999},
	{-0.959999,0.004999,-0.554999},
	{-1.049999,0.110000,-0.439999},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{-0.689999,1.489998,-1.319998},
	{-1.054999,0.499999,-0.329999},
	{-0.899999,0.000000,-0.564999},
	{-0.944999,0.154999,-0.419999},
	{-0.924999,0.059999,-0.529999},
	{-0.934999,-0.110000,-0.429999},
	{0.0,0.0,0.0},
	{-0.144999,0.314999,-0.444999},
	{0.0,0.0,0.0},
	{-0.924999,-0.034999,-0.479999},
	{-0.984999,0.164999,-0.564999},
	{-1.069999,-0.034999,-0.569999},
	{-0.954999,-0.019999,-0.579999},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{-1.004999,-0.049999,-0.019999},
	{-1.024999,-0.090000,-0.639999},
	{-0.904999,0.000000,-0.414999},
	{-0.894999,0.014999,-0.539999},
	{-0.904999,0.009999,-0.409999},
	{-1.089999,0.000000,-0.709999},
	{-0.939999,-0.029999,-0.564999},
	{-1.039999,-0.100000,-0.474999},
	{-0.884999,0.059999,-0.479999},
	{-1.769998,1.484998,-1.774998},
	{-0.949999,0.105000,-0.439999},
	{-1.089999,-0.059999,-0.554999},
	{-0.964999,0.004999,-0.564999},
	{-1.034999,0.749999,-0.254999},
	{0.0,0.0,0.0},
	{-1.109999,0.009999,-0.534999},
	{-0.754999,0.000000,-0.464999},
	{-1.119999,0.000000,0.184999},
	{-1.129999,0.044999,0.074999},
	{-0.894999,-0.089999,-0.374999},
	{-0.964999,0.000000,-0.444999},
	{-1.004999,0.054999,-0.414999},
	{-0.919999,0.130000,-0.574999},
	{-0.909999,0.120000,-0.404999},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{-0.824999,0.000000,-0.414999},
	{-0.989999,-0.049999,-0.479999},
	{-1.089999,0.309999,-0.609999},
	{-0.334999,0.100000,-0.374999},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{-0.924999,0.004999,-0.334999},
	{-1.019999,-0.140000,-0.419999},
	{0.0,0.0,0.0},
	{-1.429998,-0.649999,-0.879999},
	{-1.014999,0.000000,-0.484999},
	{-1.089999,0.014999,-0.474999},
	{0.0,0.0,0.0},
	{-0.984999,-0.194999,-0.709999},
	{-0.674999,0.259999,0.130000},
	{0.0,0.0,0.0},
	{-1.019999,-0.009999,-0.354999},
	{0.0,0.0,0.0},
	{-1.009999,-0.064999,-0.534999},
	{-1.374998,0.000000,-0.664999},
	{-0.909999,0.000000,-0.359999},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{-0.974999,0.000000,-0.469999},
	{-0.969999,0.000000,-0.464999},
	{-1.004999,-0.014999,-0.414999},
	{-1.019999,0.115000,-0.684999},
	{-0.959999,0.204999,-0.499999},
	{0.0,0.0,0.0},
	{-1.024999,0.000000,-0.549999},
	{-0.954999,0.034999,-0.629999},
	{-0.989999,-0.064999,-0.489999},
	{-0.904999,0.009999,-0.409999},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{-1.149999,0.269999,-0.654999},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0}
};


enum {
	VEHICLE_STATE_SPAWNED,
	VEHICLE_STATE_DEATH,
	VEHICLE_STATE_INSURANCE,
	VEHICLE_STATE_HOUSEPARK,
	VEHICLE_STATE_GARAGE,
    VEHICLE_STATE_IMPOUNDED,
	VEHICLE_STATE_STUCK
}

enum {
	VEHICLE_TYPE_NONE,
	VEHICLE_TYPE_PLAYER,
	VEHICLE_TYPE_RENTAL,
	VEHICLE_TYPE_ADMIN,
	VEHICLE_TYPE_SIDEJOB,
	VEHICLE_TYPE_FACTION,
	VEHICLE_TYPE_EVENT
}

enum bodyEnums {
    Model,
    Name[37]
};

new BodyWork[][bodyEnums] = {
    {1000,"Generic Spoiler"},
    {1001,"Generic Spoiler"},
    {1002,"Generic Spoiler"},
    {1003,"Generic Spoiler"},
    {1004,"Bonnet Scoop"},
    {1005,"Bonnet Scoop"},
    {1006,"Generic Vehicle Roof-Scoop"},
    {1007,"Generic Vehicle Side Skirt (L)"},
    {1011,"Bonnet Scoop"},
    {1012,"Bonnet Scoop"},
    {1013,"Round Fog Lamps"},
    {1014,"Generic Spoiler"},
    {1015,"Generic Spoiler"},
    {1016,"Generic Spoiler"},
    {1017,"Generic Vehicle Side Skirt (R)"},
    {1018,"Curved Twin Cylinder Generic Exhaust"},
    {1019,"Twin Cylinder Generic Exhaust"},
    {1020,"Large Generic Exhaust"},
    {1021,"Medium Generic Exhaust"},
    {1022,"Small Generic Exhaust"},
    {1023,"Generic Spoiler"},
    {1024,"Square Fog Lamps"},
    {1026,"Sultan Side Skirt Type 1 (L)"},
    {1027,"Sultan Side Skirt Type 1 (R)"},
    {1028,"Sultan Exhaust Type 1"},
    {1029,"Sultan Exhaust Type 2"},
    {1030,"Sultan Side Skirt Type 2 (R)"},
    {1031,"Sultan Side Skirt Type 1 (L)"},
    {1032,"Sultan Roof Scoop type 1"},
    {1033,"Sultan Roof Scoop type 2"},
    {1034,"Elegy Exhaust type 1"},
    {1035,"Elegy Roof Scoop Type 1"},
    {1036,"Elegy Side Skirt type 1 (L)"},
    {1037,"Elegy Exhaust Type 2"},
    {1038,"Elegy Roof Scoop type 2"},
    {1039,"Elegy Side Skirt type 2 (L)"},
    {1040,"Elegy Side Skirt type 1 (R)"},
    {1041,"Elegy Side Skirt type 2 (R)"},
    {1042,"Broadway Side Skirt (L)"},
    {1043,"Broadway Exhaust type 2"},
    {1044,"Broadway Exhaust type 1"},
    {1045,"Flash Exhaust type 2"},
    {1046,"Flash Exhaust type 1"},
    {1047,"Flash Side Skirt type 1 (L)"},
    {1048,"Flash Side Skirt type 2 (L)"},
    {1049,"Flash Spoiler type 1"},
    {1050,"Flash Spoiler type 2"},
    {1051,"Flash Side Skirt type 1 (R)"},
    {1052,"Flash Side Skirt type 2 (R)"},
    {1053,"Flash Roof Scoop type 2"},
    {1054,"Flash Roof Scoop type 1"},
    {1055,"Stratum Roof Scoop type 1"},
    {1056,"Stratum Side Skirt type 1 (L)"},
    {1057,"Stratum Side Skirt type 2 (L)"},
    {1058,"Stratum Spoiler type 1"},
    {1059,"Stratum Exhaust type 2"},
    {1060,"Stratum Spoiler type 2"},
    {1061,"Stratum Roof Scoop type 2"},
    {1062,"Stratum Side Skirt type 1 (R)"},
    {1063,"Stratum Side Skirt type 2 (R)"},
    {1064,"Stratum Exhaust type 1"},
    {1065,"Jester Exhaust type 1"},
    {1066,"Jester Exhaust type 2"},
    {1067,"Jester Roof Scoop type 1"},
    {1068,"Jester Roof Scoop type 2"},
    {1069,"Jester Side Skirt type 1 (L)"},
    {1070,"Jester Side Skirt type 2 (L)"},
    {1071,"Jester Side Skirt type 1 (R)"},
    {1072,"Jester Side Skirt type 2 (R)"},
    {1088,"Uranus Roof Scoop 1"},
    {1089,"Uranus Exhaust Type 1"},
    {1090,"Uranus Side Skirt type 1 (L)"},
    {1091,"Uranus Roof Scoop 2"},
    {1092,"Uranus Exhaust Type 2"},
    {1093,"Uranus Side Skirt type 2 (L)"},
    {1094,"Uranus Side Skirt type 1 (R)"},
    {1095,"Uranus Side Skirt type 2 (R)"},
    {1099,"Broadway Side Skirt (R)"},
    {1100,"Remington Misc. Part 1"},
    {1101,"Remington Side Skirt type 1 (R)"},
    {1102,"Savanna Side Skirt (R)"},
    {1103,"Blade Roof type 2"},
    {1104,"Blade Exhaust type 1"},
    {1105,"Blade Exhaust type 2"},
    {1106,"Remington Side Skirt type 2 (L)"},
    {1107,"Blade Side Skirt (R)"},
    {1108,"Blade Side Skirt (L)"},
    {1109,"Slamvan Rear Bullbars type 1"},
    {1110,"Slamvan Rear Bullbars type 2"},
    {1111,"Slamvan hood ornament 1 (not used)"},
    {1112,"Slamvan hood ornament 2 (not used)"},
    {1113,"Slamvan Exhaust type 1"},
    {1114,"Slamvan Exhaust type 2"},
    {1115,"Slamvan Front Bullbars type 1"},
    {1116,"Slamvan Front Bullbars type 2"},
    {1117,"Slamvan Front Bumper"},
    {1118,"Slamvan Side Skirt type 1 (L)"},
    {1119,"Slamvan Side Skirt type 2 (L)"},
    {1120,"Slamvan Side Skirt type 1 (R)"},
    {1121,"Slamvan Side Skirt type 2 (R)"},
    {1122,"Remington Side Skirt type 1 (L)"},
    {1123,"Remington Misc. Part 2"},
    {1124,"Remington Side Skirt type 2 (R)"},
    {1125,"Remington Misc. Part 3"},
    {1126,"Remington Exhaust type 1"},
    {1127,"Remington Exhaust type 2"},
    {1128,"Blade Roof Type 1"},
    {1129,"Savanna Exhaust type 1"},
    {1130,"Savanna Roof type 1"},
    {1131,"Savanna Roof type 2"},
    {1132,"Savanna Exhaust type 2"},
    {1133,"Savanna Side Skirt (L)"},
    {1134,"Tornado Side Skirt (L)"},
    {1135,"Tornado Exhaust type 2"},
    {1136,"Tornado Exhaust type 1"},
    {1137,"Tornado Side Skirt (R)"},
    {1138,"Sultan Spoiler type 1"},
    {1139,"Sultan Spoiler type 2"},
    {1140,"Sultan Rear Bumper type 2"},
    {1141,"Sultan Rear Bumper type 1"},
    {1142,"Oval Bonnet Vents (R)"},
    {1143,"Oval Bonnet Vents (L)"},
    {1144,"Square Bonnet Vents (R)"},
    {1145,"Square Bonnet Vents (L)"},
    {1146,"Elegy Spoiler type 2"},
    {1147,"Elegy Spoiler type 1"},
    {1148,"Elegy Rear Bumper type 2"},
    {1149,"Elegy Rear Bumper type 1"},
    {1150,"Flash Rear Bumper type 1"},
    {1151,"Flash Rear Bumper type 2"},
    {1152,"Flash Front Bumper type 2"},
    {1153,"Flash Front Bumper type 1"},
    {1154,"Stratum Rear Bumper type 1"},
    {1155,"Stratum Front Bumper type 1"},
    {1156,"Stratum Rear Bumper type 2"},
    {1157,"Stratum Front Bumper type 2"},
    {1158,"Jester Spoiler type 2"},
    {1159,"Jester Rear Bumper type 1"},
    {1160,"Jester Front bumper type 1"},
    {1161,"Jester Rear bumper type2"},
    {1162,"Jester Spoiler type 1"},
    {1163,"Uranus Spoiler type 2"},
    {1164,"Uranus Spoiler type 1"},
    {1165,"Uranus Front Bumper type 2"},
    {1166,"Uranus Rear Bumper type 2"},
    {1167,"Uranus Front Bumper type 1"},
    {1168,"Uranus Rear Bumper type 1"},
    {1169,"Sultan Front Bumper type 1"},
    {1170,"Sultan Front Bumper type 2"},
    {1171,"Elegy Front Bumper type 1"},
    {1172,"Elegy Front Bumper type 2"},
    {1173,"Jester Front Bumper type 2"},
    {1174,"Broadway Front Bumper type 1"},
    {1175,"Broadway Front Bumper type 2"},
    {1176,"Broadway Rear Bumper type 1"},
    {1178,"Remington Rear Bumper type 2"},
    {1179,"Remington Front Bumper type 1"},
    {1180,"Remington Rear Bumper type 2"},
    {1181,"Blade Front Bumper type 2"},
    {1182,"Blade Front Bumper type 1"},
    {1183,"Blade Rear Bumper type 2"},
    {1184,"Blade Rear Bumper type 1"},
    {1185,"Remington Front Bumper type 2"},
    {1186,"Savanna Rear Bumper type 2"},
    {1187,"Savanna Rear Bumper type 1"},
    {1188,"Savanna Front Bumper type 2"},
    {1189,"Savanna Front Bumper type 1"},
    {1190,"Tornado Rear Bumper type 1"},
    {1191,"Tornado Rear Bumper type 2"},
    {1192,"Tornado Front Bumper type 1"},
    {1193,"Tornado Front Bumper type 2"},
    {19308, "Taxi Sign"}
};

enum E_VEHICLE_OBJECT {
    vehObjectID,
    vehObjectVehicleIndex,
    vehObjectType,
    vehObjectModel,
    vehObjectColor,

    vehObjectText[32],
    vehObjectFont[24],
    vehObjectFontSize,
    vehObjectFontColor,

    vehObject,
    
    bool:vehObjectExists,

    Float:vehObjectPosX,
    Float:vehObjectPosY,
    Float:vehObjectPosZ,
    Float:vehObjectPosRX,
    Float:vehObjectPosRY,
    Float:vehObjectPosRZ
};
new VehicleObjects[MAX_VEHICLES][MAX_VEHICLE_OBJECT][E_VEHICLE_OBJECT];

SwitchVehicleBoot(vehicleid,bool:boot_status){
	new engine,lights,alarm,doors,bonnet,boot,objective;
	GetVehicleParamsEx(vehicleid,engine,lights,alarm,doors,bonnet,boot,objective);
	SetVehicleParamsEx(vehicleid,engine,lights,alarm,doors,bonnet,_:boot_status,objective);
}

SwitchVehicleLight(vehicleid,bool:light_status){

	if(light_status) {
        new panels, doors, lights, tires;

        KillTimer(FlashTime[vehicleid]);

        GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
    	UpdateVehicleDamageStatus(vehicleid, panels, doors, 0, tires);
	}
	new engine,lights,alarm,doors,bonnet,boot,objective;
	GetVehicleParamsEx(vehicleid,engine,lights,alarm,doors,bonnet,boot,objective);
	SetVehicleParamsEx(vehicleid,engine,_:light_status,alarm,doors,bonnet,boot,objective);
}

SwitchVehicleEngine(vehicleid,bool:engine_status){
	new engine,lights,alarm,doors,bonnet,boot,objective;
	GetVehicleParamsEx(vehicleid,engine,lights,alarm,doors,bonnet,boot,objective);
	SetVehicleParamsEx(vehicleid,_:engine_status,lights,alarm,doors,bonnet,boot,objective);
}

GetInsideVehicle(vehicleid) {

	new total = 0;
	foreach(new i : Player) if(IsPlayerInVehicle(i, vehicleid)) {
		total++;
	}
	return total;
}

Float:GetVehicleFuelMax(modelid) {
	new Float:fuel;
	switch(Model_GetCategory(modelid)) 
	{
		case CATEGORY_AIRPLANE: fuel = 50.0;
		case CATEGORY_BIKE: fuel = 5.0;
		case CATEGORY_BOAT: fuel = 15.0;
		case CATEGORY_CONVERTIBLE: fuel = 25.0;
		case CATEGORY_HELICOPTER: fuel = 50.0;
		case CATEGORY_INDUSTRIAL: fuel = 20.0;
		case CATEGORY_LOWRIDER: fuel = 20.0;
		case CATEGORY_OFFROAD: fuel = 30.0;
		case CATEGORY_PUBLIC: fuel = 25.0;
		case CATEGORY_SALOONS: fuel = 15.0;
		case CATEGORY_SPORT: fuel = 15.0;
		case CATEGORY_STATION_WAGON: fuel = 20.0;
		case CATEGORY_UNIQUE: fuel = 20.0;
		default: fuel = 10.0;
	}
	return fuel;
}


Float:Vehicle_GetFuel(vehicleid)
{
	return VehicleData[vehicleid][vFuel];
}
