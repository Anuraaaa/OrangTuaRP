#include <YSI_Coding\y_hooks>

enum E_ACTOR_DATA
{
	actorID,
	Float:actorPos[4],
	actorInterior,
	actorWorld,
	actorSkin,
	actorAnim,
	actorName[MAX_PLAYER_NAME],
	STREAMER_TAG_ACTOR:actorModel,
	Text3D:actorLabel,
	actorBusiness,
	bool:actorBeingRob,
	bool:actorRobbed,
	actorCooldown,
	actorGettingRob
};

new ActorData[MAX_ACTOR][E_ACTOR_DATA];
new Iterator:DynamicActor<MAX_ACTOR>,
	g_PlayerRobbingActor[MAX_PLAYERS],
	Timer:g_PlayerRobbingActorTimer[MAX_PLAYERS];

hook OnPlayerConnect(playerid) {
	g_PlayerRobbingActor[playerid] = -1;
	g_PlayerRobbingActorTimer[playerid] = Timer:-1;
}

hook OnPlayerDisconnect(playerid, reason) {
	g_PlayerRobbingActor[playerid] = -1;
	g_PlayerRobbingActorTimer[playerid] = Timer:-1;
}
Actor_Create(skin, Float:x, Float:y, Float:z, Float:a, world, interior, anim = 0, name[] = "")
{
	new id = Iter_Free(DynamicActor);
	if(id != INVALID_ITERATOR_SLOT)
	{
		ActorData[id][actorPos][0] = x;
		ActorData[id][actorPos][1] = y;
		ActorData[id][actorPos][2] = z;
		ActorData[id][actorPos][3] = a;
		ActorData[id][actorSkin] = skin;
		ActorData[id][actorInterior] = interior;
		ActorData[id][actorWorld] = world;
		ActorData[id][actorAnim] = anim;
		ActorData[id][actorCooldown] = 0;
		ActorData[id][actorGettingRob] = 0;
		ActorData[id][actorBusiness] = -1;

		format(ActorData[id][actorName], MAX_PLAYER_NAME, name);

		Iter_Add(DynamicActor, id);
		Actor_Spawn(id);
		mysql_tquery(sqlcon, "INSERT INTO `actors` (`Skin`) VALUES(0)", "OnActorCreated", "d", id);
		return id;
	}
	return INVALID_ITERATOR_SLOT;
}

function OnActorCreated(id)
{
	ActorData[id][actorID] = cache_insert_id();
	Actor_Save(id);
}

Actor_StopRobbery(actorid) {

	if(ActorData[actorid][actorBeingRob]) {
		ApplyDynamicActorAnimation(ActorData[actorid][actorModel], "PED", "cower", 4.1,0,0,0,1,0);
		ActorData[actorid][actorCooldown] = 10800;
		ActorData[actorid][actorBeingRob] = false;
		ActorData[actorid][actorRobbed] = true;
		ActorData[actorid][actorGettingRob] = 0;
	}
	return 1;
}
Actor_ReturnBusinessID(actorid) {

	new index = -1;
	for(new i = 0; i < MAX_BUSINESS; i++) if(BizData[i][bizExists] && BizData[i][bizID] == ActorData[actorid][actorBusiness]) {
		index = i;
		break;
	}
	return index;
}

Actor_Spawn(id)
{
	new animlib[32], animname[32];

	if(!IsValidDynamicActor(ActorData[id][actorModel]))
	{
		ActorData[id][actorModel] = CreateDynamicActor(ActorData[id][actorSkin], ActorData[id][actorPos][0], ActorData[id][actorPos][1], ActorData[id][actorPos][2], ActorData[id][actorPos][3], 1, 100.0, ActorData[id][actorWorld], ActorData[id][actorInterior], -1, 20.0);
		ActorData[id][actorLabel] = CreateDynamic3DTextLabel(sprintf("[ID:%d]\n{FFFFFF}%s", id, ActorData[id][actorName]), COLOR_SERVER, ActorData[id][actorPos][0], ActorData[id][actorPos][1], ActorData[id][actorPos][2] + 1.0, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, ActorData[id][actorWorld], ActorData[id][actorInterior]);
		if(ActorData[id][actorAnim] != 0)
		{
			GetAnimationName(ActorData[id][actorAnim], animlib, 32, animname, 32);
			ApplyDynamicActorAnimation(ActorData[id][actorModel], animlib, animname, 4.1, 1, 0, 0, 1, 0);
		}

		Streamer_SetIntData(STREAMER_TYPE_ACTOR, ActorData[id][actorModel], E_STREAMER_EXTRA_ID, id);
	}
	return 1;
}

Actor_Save(id)
{
	if(!Iter_Contains(DynamicActor, id))
		return 1;

	new query[1012];
	mysql_format(sqlcon, query, sizeof(query), "UPDATE `actors` SET ");
	mysql_format(sqlcon, query, sizeof(query), "%s`Skin` = '%d', ", query, ActorData[id][actorSkin]);
	mysql_format(sqlcon, query, sizeof(query), "%s`PosX` = '%f', ", query, ActorData[id][actorPos][0]);
	mysql_format(sqlcon, query, sizeof(query), "%s`PosY` = '%f', ", query, ActorData[id][actorPos][1]);
	mysql_format(sqlcon, query, sizeof(query), "%s`PosZ` = '%f', ", query, ActorData[id][actorPos][2]);
	mysql_format(sqlcon, query, sizeof(query), "%s`PosA` = '%f', ", query, ActorData[id][actorPos][3]);
	mysql_format(sqlcon, query, sizeof(query), "%s`Anim` = '%d', ", query, ActorData[id][actorAnim]);
	mysql_format(sqlcon, query, sizeof(query), "%s`World` = '%d', ", query, ActorData[id][actorWorld]);
	mysql_format(sqlcon, query, sizeof(query), "%s`Interior` = '%d', ", query, ActorData[id][actorInterior]);
	mysql_format(sqlcon, query, sizeof(query), "%s`Business` = '%d', ", query, ActorData[id][actorBusiness]);
	mysql_format(sqlcon, query, sizeof(query), "%s`Name` = '%s' ", query, ActorData[id][actorName]);
	mysql_format(sqlcon, query, sizeof(query), "%sWHERE `ID` = '%d'", query, ActorData[id][actorID]);
	mysql_tquery(sqlcon, query);
	return 1;
}

Actor_Delete(id)
{
	if(Iter_Contains(DynamicActor, id))
	{
		new query[128];
		mysql_format(sqlcon, query, 128, "DELETE FROM `actors` WHERE `ID` = '%d'", ActorData[id][actorID]);
		mysql_tquery(sqlcon, query);

		if(IsValidDynamicActor(ActorData[id][actorModel]))
			DestroyDynamicActor(ActorData[id][actorModel]);

		if(IsValidDynamic3DTextLabel(ActorData[id][actorLabel]))
			DestroyDynamic3DTextLabel(ActorData[id][actorLabel]);

		ActorData[id][actorID] = 0;
		ActorData[id][actorCooldown] = 0;
		Iter_Remove(DynamicActor, id);
	}
	return 1;
}

Actor_Refresh(id)
{
	if(Iter_Contains(DynamicActor, id))
	{
		SetDynamicActorPos(ActorData[id][actorModel], ActorData[id][actorPos][0], ActorData[id][actorPos][1], ActorData[id][actorPos][2]);
		SetDynamicActorFacingAngle(ActorData[id][actorModel], ActorData[id][actorPos][3]);

		Streamer_SetPosition(STREAMER_TYPE_3D_TEXT_LABEL, ActorData[id][actorLabel], ActorData[id][actorPos][0], ActorData[id][actorPos][1], ActorData[id][actorPos][2] + 1.0);
		UpdateDynamic3DTextLabelText(ActorData[id][actorLabel], COLOR_SERVER, sprintf("[ID:%d]\n{FFFFFF}%s", id, ActorData[id][actorName]));

		Streamer_SetIntData(STREAMER_TYPE_ACTOR, ActorData[id][actorModel], E_STREAMER_MODEL_ID, ActorData[id][actorSkin]);
		if(ActorData[id][actorAnim] != 0 && !ActorData[id][actorBeingRob] && !ActorData[id][actorRobbed])
		{
			new animlib[32], animname[32];
			GetAnimationName(ActorData[id][actorAnim], animlib, 32, animname, 32);
			ApplyDynamicActorAnimation(ActorData[id][actorModel], animlib, animname, 4.1, 1, 0, 0, 1, 0);
		}
	}
	return 1;
}

function Actor_Load()
{
	if(cache_num_rows())
	{
		for(new i = 0; i < cache_num_rows(); i++)
		{
			cache_get_value_name_int(i, "ID", ActorData[i][actorID]);
			cache_get_value_name(i, "Name", ActorData[i][actorName]);
			cache_get_value_name_int(i, "Anim", ActorData[i][actorAnim]);
			cache_get_value_name_int(i, "Skin", ActorData[i][actorSkin]);
			cache_get_value_name_int(i, "World", ActorData[i][actorWorld]);
			cache_get_value_name_int(i, "Interior", ActorData[i][actorInterior]);
			cache_get_value_name_float(i, "PosX", ActorData[i][actorPos][0]);
			cache_get_value_name_float(i, "PosY", ActorData[i][actorPos][1]);
			cache_get_value_name_float(i, "PosZ", ActorData[i][actorPos][2]);
			cache_get_value_name_float(i, "PosA", ActorData[i][actorPos][3]);
			cache_get_value_name_int(i, "Business", ActorData[i][actorBusiness]);

			Iter_Add(DynamicActor, i);

			Actor_Spawn(i);

			ActorData[i][actorBeingRob] = false;
			ActorData[i][actorRobbed] = false;

			ActorData[i][actorCooldown] = 0;
		}
		printf("[ACTOR] Loaded %d Dynamic Actor from database", cache_num_rows());
	}
	return 1;
}

CMD:createactor(playerid, params[])
{
	if(PlayerData[playerid][pAdmin] < 6)
		return SendErrorMessage(playerid, NO_PERMISSION);

	new name[MAX_PLAYER_NAME], skinid, Float:x, Float:y, Float:z, Float:a;
	if(sscanf(params, "ds[24]", skinid, name))
		return SendSyntaxMessage(playerid, "/createactor [skinid] [name]");

	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, a);

	new id = Actor_Create(skinid, x, y, z, a, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), 0, name);

	if(id == INVALID_ITERATOR_SLOT)
		return SendErrorMessage(playerid, "You cannot create more actor's!");

	SendAdminMessage(COLOR_LIGHTRED, "AdmCmd: %s has created actorid %d with name %s", GetUsername(playerid), id, name);
	SetPlayerPos(playerid, x + 1, y, z);
	return 1;
}

CMD:destroyactor(playerid, params[])
{
	if(PlayerData[playerid][pAdmin] < 6)
		return SendErrorMessage(playerid, NO_PERMISSION);

	if(isnull(params))
		return SendSyntaxMessage(playerid, "/destroyactor [actorid]");

	if(!IsNumeric(params))
		return SendSyntaxMessage(playerid, "/destroyactor [actorid]");

	if(!Iter_Contains(DynamicActor, strval(params)))
		return SendErrorMessage(playerid, "Invalid actor specified id!");

	Actor_Delete(strval(params));
	SendAdminMessage(COLOR_LIGHTRED, "AdmCmd: %s has destroyed actorid %d", PlayerData[playerid][pUCP], strval(params));
	return 1;
}
CMD:editactor(playerid, params[])
{
	new
	    id,
	    type[24],
	    string[128];

	if (PlayerData[playerid][pAdmin] < 6)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "ds[24]S()[128]", id, type, string))
 	{
	 	SendSyntaxMessage(playerid, "/editactor [id] [name]");
	    SendClientMessage(playerid, COLOR_YELLOW, "(Names){FFFFFF} pos, model, name, anim, biz");
		return 1;
	}
	if(!Iter_Contains(DynamicActor, id))
		return SendErrorMessage(playerid, "You have specified invalid actor!");

	if(!strcmp(type, "pos", true))
	{

		GetPlayerPos(playerid, ActorData[id][actorPos][0], ActorData[id][actorPos][1], ActorData[id][actorPos][2]);
		GetPlayerFacingAngle(playerid, ActorData[id][actorPos][3]);	

		Actor_Refresh(id);
		Actor_Save(id);

		SetPlayerPos(playerid, ActorData[id][actorPos][0] + 1, ActorData[id][actorPos][1], ActorData[id][actorPos][2]);

		SendAdminMessage(COLOR_LIGHTRED, "AdmCmd: %s has adjusted location actorid %d", PlayerData[playerid][pUCP], id);

	}
	else if(!strcmp(type, "biz", true)) {
		if(isnull(string))
			return SendSyntaxMessage(playerid, "/editactor [id] [biz] [business id]");

		if(!IsNumeric(string))
			return SendSyntaxMessage(playerid, "/editactor [id] [biz] [business id]");

		if(strval(string) != -1 && !BizData[strval(string)][bizExists])
			return SendErrorMessage(playerid, "Business %d is doesn't exists!", strval(string));

		ActorData[id][actorBusiness] = BizData[strval(string)][bizID];
		Actor_Save(id);
		SendAdminMessage(X11_TOMATO, "AdmCmd: %s has adjusted business id of actor %d to %d.", GetUsername(playerid), id, strval(string));
	}
	else if(!strcmp(type, "model", true))
	{
		if(isnull(string))
			return SendSyntaxMessage(playerid, "/editactor [id] [model] [new skin model]");

		if(!IsNumeric(string))
			return SendSyntaxMessage(playerid, "/editactor [id] [model] [new skin model]");

		ActorData[id][actorSkin] = strval(string);
		Actor_Refresh(id);
		Actor_Save(id);
		SendAdminMessage(COLOR_LIGHTRED, "AdmCmd: %s has adjusted model of actorid %d to %d", PlayerData[playerid][pUCP], id, strval(string));
	}
	else if(!strcmp(type, "name", true))
	{
		if(isnull(string))
			return SendSyntaxMessage(playerid, "/editactor [id] [name] [new actor name]");

		format(ActorData[id][actorName], MAX_PLAYER_NAME, string);
		Actor_Refresh(id);
		Actor_Save(id);

		SendAdminMessage(COLOR_LIGHTRED, "AdmCmd: %s has adjusted name of actorid %d to %s", PlayerData[playerid][pUCP], id, string);
	}
	else if(!strcmp(type, "anim", true))
	{
		if(isnull(string))
			return SendSyntaxMessage(playerid, "/editactor [id] [anim] [animation index]");

		if(!IsNumeric(string))
			return SendSyntaxMessage(playerid, "/editactor [id] [anim] [animation index]");

		if(strval(string) < 1 || strval(string) > 1812)
			return SendErrorMessage(playerid, "Invalid animation index!");

		ClearDynamicActorAnimations(ActorData[id][actorModel]);

		new animlib[32], animname[32];
		ActorData[id][actorAnim] = strval(string);
		GetAnimationName(ActorData[id][actorAnim], animlib, 32, animname, 32);
		ApplyDynamicActorAnimation(ActorData[id][actorModel], animlib, animname, 4.1, 1, 0, 0, 1, 0);

		Actor_Save(id);

		SendAdminMessage(COLOR_LIGHTRED, "AdmCmd: %s has adjusted animation index of actorid %d to %d", PlayerData[playerid][pUCP], id, strval(string));
	}
	return 1;
}

public OnPlayerTargetActor(playerid, actorid, weaponid) {

	new idx = -1, bizid;

	idx = Streamer_GetIntData(STREAMER_TYPE_ACTOR, actorid, E_STREAMER_EXTRA_ID);

	if(Iter_Contains(DynamicActor, idx) && IsValidDynamicActor(ActorData[idx][actorModel])) {

		if(!ActorData[idx][actorBeingRob] && !ActorData[idx][actorRobbed] && ActorData[idx][actorBusiness] != -1) {

			if(rob_biz_delay)
				return SendErrorMessage(playerid, "Tidak dapat melakukan perampokan (delay server %d detik)", rob_biz_delay);

			if(Faction_CountDuty(FACTION_POLICE) < 4)
				return SendErrorMessage(playerid, "Harus ada 4 SAPD OnDuty untuk melakukan perampokan.");

			if(weaponid >= 22 && weaponid <= 38) {
				
				if(ActorData[idx][actorCooldown] > 0) {
					return SendErrorMessage(playerid, "NPC ini masih cooldown untuk dirampok! harap tunggu %d menit.", ActorData[idx][actorCooldown]/60);
				}
				ApplyDynamicActorAnimation(ActorData[idx][actorModel], "ROB_BANK", "SHP_HandsUp_Scr", 4.1, 0, 0, 0, 1, 0);

				SendClientMessage(playerid, X11_RED, "(Info) "WHITE"Kamu memulai perampokan bisnis!");
				SendClientMessage(playerid, X11_RED, "(Info) "WHITE"Bidik NPC "YELLOW"selama mungkin "WHITE"untuk mendapatkan uang dari perampokan!");
				SendClientMessage(playerid, X11_RED, "(Info) "WHITE"Jika berhenti membidik atau menembak NPC maka perampokan akan selesai.");

				ActorData[idx][actorBeingRob] = true;
				g_PlayerRobbingActor[playerid] = idx;
				g_PlayerRobbingActorTimer[playerid] = repeat Actor_GiveRobberCash[15000](playerid, idx);
				defer Actor_ApplyRobberyAnim[4000](idx);

				bizid = Actor_ReturnBusinessID(idx);
				SendFactionMessageEx(FACTION_POLICE, -1, ""LIGHTBLUE"[ALARM] "YELLOW"%s "WHITE"Business alarm is triggered, business is under robbery.", BizData[bizid][bizName]);
			
			}
		}
	}
	return 1;
}

public OnPlayerStopTargetActor(playerid, actorid, weaponid) {
	new idx = -1;

	idx = Streamer_GetIntData(STREAMER_TYPE_ACTOR, actorid, E_STREAMER_EXTRA_ID);

	if(Iter_Contains(DynamicActor, idx) && IsValidDynamicActor(ActorData[idx][actorModel])) {

		if(g_PlayerRobbingActor[playerid] == idx) {
			if(ActorData[idx][actorBeingRob]) {
				Actor_StopRobbery(idx);
				stop g_PlayerRobbingActorTimer[playerid];

				rob_biz_delay = 3600;
			}
		}
	}

	return 1;
}


public OnPlayerShotActor(playerid, actorid, weaponid, bool:IsDynamicActor)
{
	new idx = -1;

	idx = Streamer_GetIntData(STREAMER_TYPE_ACTOR, actorid, E_STREAMER_EXTRA_ID);

	if(Iter_Contains(DynamicActor, idx) && IsValidDynamicActor(ActorData[idx][actorModel])) {

		if(g_PlayerRobbingActor[playerid] == idx) {
			if(ActorData[idx][actorBeingRob]) {
				Actor_StopRobbery(idx);
				stop g_PlayerRobbingActorTimer[playerid];
				SendClientMessage(playerid, X11_RED, "(Info) "WHITE"Perampokan diberhentikan karena NPC terkena tembakan.");

				rob_biz_delay = 3600;
			}		
		}
	}
	return 1;
}
timer Actor_ApplyRobberyAnim[4000](actorid) {
	ApplyDynamicActorAnimation(ActorData[actorid][actorModel], "SHOP", "SHP_Rob_GiveCash", 4.1,1,0,0,1,0);
	return 1;
}

timer Actor_GiveRobberCash[4000](playerid, actorid) {

	if(!IsPlayerInRangeOfPoint(playerid, 10.0, ActorData[actorid][actorPos][0], ActorData[actorid][actorPos][1], ActorData[actorid][actorPos][2])) {

		Actor_StopRobbery(actorid);
		stop g_PlayerRobbingActorTimer[playerid];
		SendClientMessage(playerid, X11_RED, "(Info) "WHITE"Perampokan diberhentikan karena kamu terlalu jauh dari NPC!");
		return 1;
	}
	if(GetPlayerTargetDynamicActor(playerid) == ActorData[actorid][actorModel]) {

		new rob_cash = RandomEx(1000, 5000), msg[144];
		format(msg, sizeof(msg), "Uang perampokan diterima! (+$%s)", FormatNumber(rob_cash));
		notification.Show(playerid, "Robbery Update", msg, "hud:radar_cash");

		GiveMoney(playerid, rob_cash);
		if(++ActorData[actorid][actorGettingRob] >= 10) {
			Actor_StopRobbery(actorid);
			stop g_PlayerRobbingActorTimer[playerid];
			SendClientMessage(playerid, X11_RED, "(Info) "WHITE"Perampokan telah selesai! semua uang telah diberikan.");

			rob_biz_delay = 3600;
		}
	}
	return 1;
}

task Actor_RemDelay[1000]() {
	foreach(new i : DynamicActor) if(ActorData[i][actorCooldown]) {
		if(--ActorData[i][actorCooldown] <= 0) {

			ActorData[i][actorRobbed] = false;
			ActorData[i][actorCooldown] = 0;
			ActorData[i][actorBeingRob] = false;

			ClearActorAnimations(ActorData[i][actorModel]);

			if(ActorData[i][actorAnim] != 0 && !ActorData[i][actorBeingRob] && !ActorData[i][actorRobbed])
			{
				new animlib[32], animname[32];
				GetAnimationName(ActorData[i][actorAnim], animlib, 32, animname, 32);
				ApplyDynamicActorAnimation(ActorData[i][actorModel], animlib, animname, 4.1, 1, 0, 0, 1, 0);
			}
		}
	}
	return 1;
}