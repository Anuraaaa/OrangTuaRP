#include <YSI_Coding\y_hooks>

enum tree_data
{
	treeID,
	bool:treeExists,
	Float:treePos[6],
	treeTime,
	bool:treeCutted,
	STREAMER_TAG_OBJECT:treeObject,
	STREAMER_TAG_AREA:treeArea,
	treeProgress,
	treeCutTime,
	bool:treeCut,
};

new TreeData[MAX_TREE][tree_data];

Tree_Save(id)
{
	new query[512];
	mysql_format(sqlcon, query, sizeof(query), "UPDATE `tree` SET ");
	mysql_format(sqlcon, query, sizeof(query), "%s`PosX`='%f', ", query, TreeData[id][treePos][0]);
	mysql_format(sqlcon, query, sizeof(query), "%s`PosY`='%f', ", query, TreeData[id][treePos][1]);
	mysql_format(sqlcon, query, sizeof(query), "%s`PosZ`='%f', ", query, TreeData[id][treePos][2]);
	mysql_format(sqlcon, query, sizeof(query), "%s`PosRX`='%f', ", query, TreeData[id][treePos][3]);
	mysql_format(sqlcon, query, sizeof(query), "%s`PosRY`='%f', ", query, TreeData[id][treePos][4]);
	mysql_format(sqlcon, query, sizeof(query), "%s`PosRZ`='%f', ", query, TreeData[id][treePos][5]);
	mysql_format(sqlcon, query, sizeof(query), "%s`Time`='%d' ", query, TreeData[id][treeTime]);
	mysql_format(sqlcon, query, sizeof(query), "%sWHERE `ID` = '%d'", query, TreeData[id][treeID]);
	mysql_tquery(sqlcon, query);
}
Tree_Create(playerid)
{
	new Float:x, Float:y, Float:z, Float:a;
	if(GetPlayerPos(playerid, x, y, z) && GetPlayerFacingAngle(playerid, a))
	{
		forex(i, MAX_TREE) if(!TreeData[i][treeExists])
		{
			TreeData[i][treeExists] = true;

			TreeData[i][treePos][0] = x;
			TreeData[i][treePos][1] = y;
			TreeData[i][treePos][2] = z;
			TreeData[i][treePos][3] = 0.0;
			TreeData[i][treePos][4] = 0.0;
			TreeData[i][treePos][5] = a;
			TreeData[i][treeTime] = 0;
			TreeData[i][treeCutted] = false;
			TreeData[i][treeCutTime] = 0;
			TreeData[i][treeProgress] = 0;

			Tree_Spawn(i);
			mysql_tquery(sqlcon, "INSERT INTO `tree` (`Time`) VALUES(0)", "OnTreeCreated", "d", i);
			return i;
		}
	}
	return -1;
}

function Tree_Load()
{
	new rows = cache_num_rows();
	if(rows)
	{
		forex(i, rows)
		{
			TreeData[i][treeExists] = true;
			TreeData[i][treeCutted] = false;
			cache_get_value_name_int(i, "ID", TreeData[i][treeID]);
			cache_get_value_name_float(i, "PosX", TreeData[i][treePos][0]);
			cache_get_value_name_float(i, "PosY", TreeData[i][treePos][1]);
			cache_get_value_name_float(i, "PosZ", TreeData[i][treePos][2]);
			cache_get_value_name_float(i, "PosRX", TreeData[i][treePos][3]);
			cache_get_value_name_float(i, "PosRY", TreeData[i][treePos][4]);
			cache_get_value_name_float(i, "PosRZ", TreeData[i][treePos][5]);
			cache_get_value_name_int(i, "Time", TreeData[i][treeTime]);
			Tree_Spawn(i);
		}
		printf("[TREE] Loaded %d tree from database", rows);
	}
	return 1;
}

Tree_Nearest(playerid)
{
	forex(i, MAX_TREE) if(TreeData[i][treeExists]) if(IsPlayerInDynamicArea(playerid, TreeData[i][treeArea]))
		return i;

	return -1;
}

Tree_Refresh(id)
{
	if(TreeData[id][treeExists])
	{
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, TreeData[id][treeObject], E_STREAMER_X, TreeData[id][treePos][0]);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, TreeData[id][treeObject], E_STREAMER_Y, TreeData[id][treePos][1]);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, TreeData[id][treeObject], E_STREAMER_Z, TreeData[id][treePos][2]);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, TreeData[id][treeObject], E_STREAMER_R_X, TreeData[id][treePos][3]);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, TreeData[id][treeObject], E_STREAMER_R_Y, TreeData[id][treePos][4]);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, TreeData[id][treeObject], E_STREAMER_R_Z, TreeData[id][treePos][5]);

		Streamer_SetFloatData(STREAMER_TYPE_AREA, TreeData[id][treeArea], E_STREAMER_X, TreeData[id][treePos][0]);
		Streamer_SetFloatData(STREAMER_TYPE_AREA, TreeData[id][treeArea], E_STREAMER_Y, TreeData[id][treePos][1]);
		Streamer_SetFloatData(STREAMER_TYPE_AREA, TreeData[id][treeArea], E_STREAMER_Z, TreeData[id][treePos][2]);
	}
	return 1;
}


function OnTreeCreated(id)
{
	TreeData[id][treeID] = cache_insert_id();
	Tree_Save(id);
}
Tree_Spawn(id)
{
	if(TreeData[id][treeExists])
	{
		TreeData[id][treeArea] = CreateDynamicSphere(TreeData[id][treePos][0], TreeData[id][treePos][1], TreeData[id][treePos][2], 2.5);

		if(TreeData[id][treeTime] < 1)
			TreeData[id][treeObject] = CreateDynamicObject(657, TreeData[id][treePos][0], TreeData[id][treePos][1], TreeData[id][treePos][2], TreeData[id][treePos][3], TreeData[id][treePos][4], TreeData[id][treePos][5], -1, -1, -1, 500.0, 500.0);	

		Streamer_SetIntData(STREAMER_TYPE_AREA, TreeData[id][treeArea], E_STREAMER_EXTRA_ID, AREA_TYPE_TREE);
	}
	return 1;
}

Tree_Delete(id)
{
	if(!TreeData[id][treeExists])
		return 0;

	if(IsValidDynamicObject(TreeData[id][treeObject]))
		DestroyDynamicObject(TreeData[id][treeObject]);

	if(IsValidDynamicArea(TreeData[id][treeArea]))
		DestroyDynamicArea(TreeData[id][treeArea]);

	new str[64];
	mysql_format(sqlcon, str, sizeof(str), "DELETE FROM `tree`  WHERE `ID` = '%d'", TreeData[id][treeID]);
	mysql_tquery(sqlcon, str);

	TreeData[id][treeObject] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
	TreeData[id][treeID] = 0;
	TreeData[id][treeExists] = false;
	return 1;
}

CMD:createtree(playerid, params[])
{
	if(PlayerData[playerid][pAdmin] < 6)
		return SendErrorMessage(playerid, NO_PERMISSION);

	new id;

	id = Tree_Create(playerid);

	if(id == -1)
		return SendErrorMessage(playerid, "The server cannot creating more tree's!");

	PlayerData[playerid][pEditing] = id;
	PlayerData[playerid][pEditType] = EDIT_TREE;
	EditDynamicObject(playerid, TreeData[id][treeObject]);
	SendServerMessage(playerid, "You have created Tree ID %d", id);
	return 1;
}

CMD:destroytree(playerid, params[])
{
	if(PlayerData[playerid][pAdmin] < 6)
		return SendErrorMessage(playerid, NO_PERMISSION);

	new id;
	if(sscanf(params, "d", id))
		return SendSyntaxMessage(playerid, "/destroytree [Tree ID]");

	if(id > MAX_TREE || !TreeData[id][treeExists])
		return SendErrorMessage(playerid, "Invalid Tree ID");

	Tree_Delete(id);
	SendServerMessage(playerid, "You have deleted Tree ID %d", id);
	return 1;	
}

hook OnGameModeInit() {

	if (IsSQLConnected()) {
		mysql_tquery(sqlcon, "SELECT * FROM `tree`", "Tree_Load", "");
	}
}

hook OnGameModeExit() {

	if (IsSQLConnected()) {
		
		new time = GetTickCount();

		forex(i, MAX_TREE) if(TreeData[i][treeExists])
		{
			Tree_Save(i);
		}
		printf("** Saved tree data in %dms.", GetTickCount() - time);		
	}
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA:areaid) {

	for(new i = 0; i < MAX_TREE; i++) if(TreeData[i][treeExists]) {

		if(areaid == TreeData[i][treeArea] && Streamer_GetIntData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID) == AREA_TYPE_TREE) {
			if(CheckPlayerJob(playerid, JOB_LUMBERJACK))
			{
				new str[152], hours, minutes, seconds;
				if(TreeData[i][treeCutted])
					format(str, sizeof(str), "~w~Press ~r~H ~w~to load the timber.");
				else
				{
					if(TreeData[i][treeTime] < 1)
						format(str, sizeof(str), "~y~Available to cut~n~~w~Press ~r~H ~w~to begin.");
					else
					{
						GetElapsedTime(TreeData[i][treeTime], hours, minutes, seconds);
						format(str, sizeof(str), "~y~Available in: ~r~%02d:%02d:%02d", hours, minutes, seconds);
					}
				}
				ShowText(playerid, str, 3);
			}
		}
	}
/*
	new treeid = Streamer_GetIntData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID);

	if(TreeData[treeid][treeExists] && areaid == TreeData[treeid][treeArea] && IsPlayerInRangeOfPoint(playerid, 5.0, TreeData[treeid][treePos][0], TreeData[treeid][treePos][1], TreeData[treeid][treePos][2])) {

		if(PlayerData[playerid][pJob] == JOB_LUMBERJACK)
		{
			new str[152], hours, minutes, seconds;
			if(TreeData[treeid][treeCutted])
				format(str, sizeof(str), "~w~Press ~r~H ~w~to load the timber.");
			else
			{
				if(TreeData[treeid][treeTime] < 1)
					format(str, sizeof(str), "~y~Available to cut~n~~w~Press ~r~H ~w~to begin.");
				else
				{
					GetElapsedTime(TreeData[treeid][treeTime], hours, minutes, seconds);
					format(str, sizeof(str), "~y~Available in: ~r~%02d:%02d:%02d", hours, minutes, seconds);
				}
			}
			ShowText(playerid, str, 3);
		}
	}*/
}