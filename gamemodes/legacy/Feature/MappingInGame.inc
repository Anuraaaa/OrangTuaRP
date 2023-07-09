enum objectData {
	mobjID,
	mobjExists,
	mobjModel,
	Float:mobjPos[6],
	mobjInterior,
	mobjWorld,
	//Text3D:mobj3DText,
	mobjObject
};
new ObjectData[MAX_MAPOBJECTS][objectData];

function Object_Load()
{
	new rows = cache_num_rows();
	if(rows)
	{
		forex(i, rows)
		{
            ObjectData[i][mobjExists] = true;
            cache_get_value_name_int(i, "mobjID", ObjectData[i][mobjID]);
            cache_get_value_name_int(i, "mobjModel", ObjectData[i][mobjModel]);
            cache_get_value_name_int(i, "mobjInterior", ObjectData[i][mobjInterior]);
            cache_get_value_name_int(i, "mobjWorld", ObjectData[i][mobjWorld]);
            cache_get_value_name_float(i, "mobjX", ObjectData[i][mobjPos][0]);
            cache_get_value_name_float(i, "mobjY", ObjectData[i][mobjPos][1]);
            cache_get_value_name_float(i, "mobjZ", ObjectData[i][mobjPos][2]);
            cache_get_value_name_float(i, "mobjRX", ObjectData[i][mobjPos][3]);
            cache_get_value_name_float(i, "mobjRY", ObjectData[i][mobjPos][4]);
            cache_get_value_name_float(i, "mobjRZ", ObjectData[i][mobjPos][5]);

            Object_Refresh(i);
        }
        printf("[OBJECT] Loaded %d Object from database", rows);
    }
    return 1;
}        
            
function OnObjectCreated(id)
{
	if (id == -1 || !ObjectData[id][mobjExists])
	    return 0;

	ObjectData[id][mobjID] = cache_insert_id();
	Object_Save(id);

	return 1;
}

Object_Create(playerid, idx)
{
	new
	    Float:x,
	    Float:y,
	    Float:z,
	    Float:angle;

	if (GetPlayerPos(playerid, x, y, z) && GetPlayerFacingAngle(playerid, angle))
	{
		for (new i = 0; i < MAX_MAPOBJECTS; i ++) if (!ObjectData[i][mobjExists])
		{
		    ObjectData[i][mobjExists] = true;
			ObjectData[i][mobjModel] = idx;

			ObjectData[i][mobjPos][0] = x + (3.0 * floatsin(-angle, degrees));
			ObjectData[i][mobjPos][1] = y + (3.0 * floatcos(-angle, degrees));
			ObjectData[i][mobjPos][2] = z;
			ObjectData[i][mobjPos][3] = 0.0;
			ObjectData[i][mobjPos][4] = 0.0;
			ObjectData[i][mobjPos][5] = angle;

            ObjectData[i][mobjInterior] = GetPlayerInterior(playerid);
            ObjectData[i][mobjWorld] = GetPlayerVirtualWorld(playerid);

            Object_Refresh(i);
			mysql_tquery(sqlcon, "INSERT INTO `object` (`mobjModel`) VALUES(980)", "OnObjectCreated", "d", i);

			PlayerData[playerid][pEditing] = -1;
			EditDynamicObject(playerid, ObjectData[i][mobjObject]);
			PlayerData[playerid][pEditing] = i;
			PlayerData[playerid][pEditType] = EDIT_OBJECT;
			SendServerMessage(playerid, "Kamu membuat Object ID: %d.", i);
			return i;
		}
	}
	return -1;
}

Object_Save(id)
{
	new
	    query[768];

	format(query, sizeof(query), "UPDATE `object` SET `mobjModel` = '%d', `mobjX` = '%.4f', `mobjY` = '%.4f', `mobjZ` = '%.4f', `mobjRX` = '%.4f', `mobjRY` = '%.4f', `mobjRZ` = '%.4f', `mobjInterior` = '%d', `mobjWorld` = '%d' WHERE `mobjID` = '%d'",
	    ObjectData[id][mobjModel],
	    ObjectData[id][mobjPos][0],
	    ObjectData[id][mobjPos][1],
	    ObjectData[id][mobjPos][2],
	    ObjectData[id][mobjPos][3],
	    ObjectData[id][mobjPos][4],
	    ObjectData[id][mobjPos][5],
	    ObjectData[id][mobjInterior],
	    ObjectData[id][mobjWorld],
	    ObjectData[id][mobjID]
	);
	return mysql_tquery(sqlcon, query);
}

Object_Duplicate(playerid, idx)
{
	for (new i = 0; i < MAX_MAPOBJECTS; i ++) if (!ObjectData[i][mobjExists])
	{
		ObjectData[i][mobjExists] = true;
		ObjectData[i][mobjModel] = ObjectData[idx][mobjModel];

		ObjectData[i][mobjPos][0] = ObjectData[idx][mobjPos][0];
		ObjectData[i][mobjPos][1] = ObjectData[idx][mobjPos][1];
		ObjectData[i][mobjPos][2] = ObjectData[idx][mobjPos][2];
		ObjectData[i][mobjPos][3] = ObjectData[idx][mobjPos][3];
		ObjectData[i][mobjPos][4] = ObjectData[idx][mobjPos][4];
		ObjectData[i][mobjPos][5] = ObjectData[idx][mobjPos][5];

		ObjectData[i][mobjInterior] = ObjectData[idx][mobjInterior];
		ObjectData[i][mobjWorld] = ObjectData[idx][mobjInterior];

		Object_Refresh(i);
		mysql_tquery(sqlcon, "INSERT INTO `object` (`mobjModel`) VALUES(980)", "OnObjectCreated", "d", i);

		PlayerData[playerid][pEditing] = -1;
		EditDynamicObject(playerid, ObjectData[i][mobjObject]);
		PlayerData[playerid][pEditing] = i;
		PlayerData[playerid][pEditType] = EDIT_OBJECT;
		SendServerMessage(playerid, "Kamu mengubah posisi Object ID: %d.", i);
		return i;
	}
	return -1;
}

Object_Refresh(id)
{
    if(id != 1 && ObjectData[id][mobjExists])
    {
        if(IsValidDynamicObject(ObjectData[id][mobjObject])) {

			Streamer_SetItemPos(STREAMER_TYPE_OBJECT, ObjectData[id][mobjObject], ObjectData[id][mobjPos][0], ObjectData[id][mobjPos][1], ObjectData[id][mobjPos][2]);
			Streamer_SetItemOffset(STREAMER_TYPE_OBJECT, ObjectData[id][mobjObject], ObjectData[id][mobjPos][3], ObjectData[id][mobjPos][4], ObjectData[id][mobjPos][5]);
			Streamer_SetIntData(STREAMER_TYPE_OBJECT, ObjectData[id][mobjObject], E_STREAMER_WORLD_ID, ObjectData[id][mobjWorld]);
			Streamer_SetIntData(STREAMER_TYPE_OBJECT, ObjectData[id][mobjObject], E_STREAMER_INTERIOR_ID, ObjectData[id][mobjInterior]);
		}
		else ObjectData[id][mobjObject] = CreateDynamicObject(ObjectData[id][mobjModel], ObjectData[id][mobjPos][0], ObjectData[id][mobjPos][1], ObjectData[id][mobjPos][2], ObjectData[id][mobjPos][3], ObjectData[id][mobjPos][4], ObjectData[id][mobjPos][5], ObjectData[id][mobjWorld], ObjectData[id][mobjInterior]);
    }
    return 1;
}

Object_Delete(id)
{
	if (id != -1 && ObjectData[id][mobjExists])
	{
		new
		    query[64];

		format(query, sizeof(query), "DELETE FROM `object` WHERE `mobjID` = '%d'", ObjectData[id][mobjID]);
		mysql_tquery(sqlcon, query);

		if (IsValidDynamicObject(ObjectData[id][mobjObject]))
		    DestroyDynamicObject(ObjectData[id][mobjObject]);

		/*if (IsValidDynamic3DTextLabel(ObjectData[id][mobjName]))
			DestroyDynamic3DTextLabel(ObjectData[id][mobjName]);*/

	    ObjectData[id][mobjExists] = false;
	    ObjectData[id][mobjID] = 0;
	}
	return 1;
}
CMD:maphelp(playerid)
{
	if(PlayerData[playerid][pAdmin] < 5) return SendErrorMessage(playerid, NO_PERMISSION);
	SendServerMessage(playerid, "/createobj, /dupobj, /nearobj, /editobj, /delobj ");
	return 1;
}

CMD:nearobj(playerid, params[])
{
	new count = 0;

    if(PlayerData[playerid][pAdmin] < 5) return SendErrorMessage(playerid, NO_PERMISSION);

	SendClientMessageEx(playerid, -1, "========= [ Object Near ] =========");
	for(new i = 0; i < MAX_MAPOBJECTS; i++) if(ObjectData[i][mobjExists] && IsPlayerInRangeOfPoint(playerid, 20.0, ObjectData[i][mobjPos][0], ObjectData[i][mobjPos][1], ObjectData[i][mobjPos][2])) 
	{
		SendClientMessageEx(playerid, -1, "- ID: %d [ Range: %.2f ]", i, GetPlayerDistanceFromPoint(playerid, ObjectData[i][mobjPos][0], ObjectData[i][mobjPos][1], ObjectData[i][mobjPos][2]));
		count++;
	}

	if(!count)
		SendClientMessageEx(playerid, -1, "- Tidak ada object didekatmu");
	return 1;
}

CMD:dupobj(playerid, params[])
{
	static id = -1, idx;
    if(PlayerData[playerid][pAdmin] < 5) return SendErrorMessage(playerid, NO_PERMISSION);
	if (sscanf(params, "d", idx)) return SendSyntaxMessage(playerid, "/dupobj [id]");

	id = Object_Duplicate(playerid, idx);
	if (id == -1) return SendErrorMessage(playerid, "Server telah mencapai batas untuk objek.");
	SendServerMessage(playerid, "Kamu telah menduplikasi Object ID: %d.", id);
	return 1;
}

CMD:createobj(playerid, params[])
{
	static id = -1, idx;
    if(PlayerData[playerid][pAdmin] < 5) return SendErrorMessage(playerid, NO_PERMISSION);
	if (sscanf(params, "d", idx)) return SendSyntaxMessage(playerid, "/createobj [objid]");

	id = Object_Create(playerid, idx);
	if (id == -1) return SendErrorMessage(playerid, "Server telah mencapai batas untuk objek.");
	SendServerMessage(playerid, "Kamu telah membuat Object ID: %d.", id);
	return 1;
}

CMD:editobj(playerid, params[])
{
	static id;
    if(PlayerData[playerid][pAdmin] < 5) return SendErrorMessage(playerid, NO_PERMISSION);
	if (sscanf(params, "d", id)) return SendSyntaxMessage(playerid, "/editobj [id]");
	if ((id < 0 || id >= MAX_MAPOBJECTS) || !ObjectData[id][mobjExists]) return SendErrorMessage(playerid, "Object ID tidak valid!");

	PlayerData[playerid][pEditing] = -1;
	EditDynamicObject(playerid, ObjectData[id][mobjObject]);
	PlayerData[playerid][pEditing] = id;
	PlayerData[playerid][pEditType] = EDIT_OBJECT;
	SendServerMessage(playerid, "Kamu sekarang mengubah posisi Object ID: %d.", id);
	return 1;
}

CMD:delobj(playerid, params[])
{
	static id = 0;
    if(PlayerData[playerid][pAdmin] < 5) return SendErrorMessage(playerid, NO_PERMISSION);
	if (sscanf(params, "d", id)) return SendSyntaxMessage(playerid, "/delobj [id]");
	if ((id < 0 || id >= MAX_MAPOBJECTS) || !ObjectData[id][mobjExists]) return SendErrorMessage(playerid, "Object ID tidak valid!");

	Object_Delete(id);
	SendServerMessage(playerid, "Kamu telah menghapus Object ID: %d.", id);
	return 1;
}