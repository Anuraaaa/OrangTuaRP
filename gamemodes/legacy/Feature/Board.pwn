#include <YSI_Coding\y_hooks>

#define MAX_BOARD 200

enum objectData {
    oID,
    oExists,
    oModel,
    oText[255],
    oFontNames[24],
    Float:oPos[6],
    oFontColor,
    oBackColor,
    oVw,
    oInt,
    objectText,
    oFontSize
};
new ObjectData[MAX_BOARD][objectData];

ObjectText_Create(playerid, name[], Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, fontcolor = 0xFFFFFFFF, backcolor = 0x000000FF)
{
    static
        string[128];

    for (new i = 0; i != MAX_TEXTOBJECT; i ++) if(!ObjectData[i][oExists])
    {
        ObjectData[i][oExists] = true;
        FixText(name);
        format(ObjectData[i][oText], 255, "%s", name);
        format(ObjectData[i][oFontNames], 24, "Arial");

        ObjectData[i][oPos][0] = x;
        ObjectData[i][oPos][1] = y;
        ObjectData[i][oPos][2] = z;
        ObjectData[i][oPos][3] = rx;
        ObjectData[i][oPos][4] = ry;
        ObjectData[i][oPos][5] = rz;

        ObjectData[i][oModel] = 18244;

        ObjectData[i][oFontColor] = fontcolor;
        ObjectData[i][oBackColor] = backcolor;

        ObjectData[i][oFontSize] = 130;

        ObjectData[i][oInt] = GetPlayerInterior(playerid);
        ObjectData[i][oVw] = GetPlayerVirtualWorld(playerid);

        format(string,sizeof(string),"INSERT INTO `objecttext` (`Vw`) VALUES(%d)",ObjectData[i][oVw]);
        mysql_tquery(sqlcon, string, "OnObjectCreated", "d", i);

        ObjectText_Refresh(i);
        return i;
    }
    return 1;
}

ObjectText_Save(objectid)
{
    new query[2048];
    format(query, sizeof(query), "UPDATE `objecttext` SET `Text`='%q',`PosX`='%.4f',`PosY`='%.4f',`PosZ`='%.4f',`posRX`='%.4f',`posRY`='%.4f',`posRZ`='%.4f',`Vw`='%d',`Int`='%d',`FontColor`='%d',`BackColor`='%d',`FontSize`='%d',`FontNames`='%s',`Model`='%d' WHERE `ID` = '%d'",
        ObjectData[objectid][oText],
        ObjectData[objectid][oPos][0],
        ObjectData[objectid][oPos][1],
        ObjectData[objectid][oPos][2],
        ObjectData[objectid][oPos][3],
        ObjectData[objectid][oPos][4],
        ObjectData[objectid][oPos][5],
        ObjectData[objectid][oVw],
        ObjectData[objectid][oInt],
        ObjectData[objectid][oFontColor],
        ObjectData[objectid][oBackColor],
        ObjectData[objectid][oFontSize],
        ObjectData[objectid][oFontNames],
        ObjectData[objectid][oModel],
        ObjectData[objectid][oID]
    );
    return mysql_tquery(sqlcon, query);
}

ObjectText_Refresh(id)
{
    if(id != -1 && ObjectData[id][oExists])
    {
        if(IsValidDynamicObject(ObjectData[id][objectText]))
            DestroyDynamicObject(ObjectData[id][objectText]);

        ObjectData[id][objectText] = CreateDynamicObject(ObjectData[id][oModel], ObjectData[id][oPos][0], ObjectData[id][oPos][1], ObjectData[id][oPos][2], ObjectData[id][oPos][3], ObjectData[id][oPos][4], ObjectData[id][oPos][5], ObjectData[id][oVw], ObjectData[id][oInt], -1, 300, 300);
        SetDynamicObjectMaterialText(ObjectData[id][objectText], 0, ObjectData[id][oText], ObjectData[id][oFontSize], ObjectData[id][oFontNames], 32, 1, ObjectData[id][oFontColor], ObjectData[id][oBackColor], 1);
        ObjectText_Save(id);
    }
    return 1;
}

ObjectText_Delete(id)
{
    if(id != -1 && ObjectData[id][oExists])
    {
        if(IsValidDynamicObject(ObjectData[id][objectText]))
            DestroyDynamicObject(ObjectData[id][objectText]);

        mysql_tquery(sqlcon, sprintf("DELETE FROM `objecttext` WHERE `ID` = '%d'", ObjectData[id][oID]));

        ObjectData[id][oExists] = false;
        ObjectData[id][oText][0] = EOS;
        ObjectData[id][objectText] = INVALID_STREAMER_ID;
        ObjectData[id][oID] = 0;
    }
    return 1;
}

function ObjectText_Load()
{
    static
        rows,
        fields;

    cache_get_data(rows, fields);

    for (new i = 0; i < rows; i ++) if(i < MAX_TEXTOBJECT)
    {
        ObjectData[i][oExists] = true;
        ObjectData[i][oID] = cache_get_field_int(i, "ID");

        cache_get_field_content(i, "Text", ObjectData[i][oText], 255);
        cache_get_field_content(i, "FontNames", ObjectData[i][oFontNames]);

        ObjectData[i][oVw] = cache_get_field_int(i, "Vw");
        ObjectData[i][oInt] = cache_get_field_int(i, "Int");
        ObjectData[i][oFontColor] = cache_get_field_int(i, "FontColor");
        ObjectData[i][oBackColor] = cache_get_field_int(i, "BackColor");
        ObjectData[i][oFontSize] = cache_get_field_int(i, "FontSize");
        ObjectData[i][oModel] = cache_get_field_int(i, "Model");

        ObjectData[i][oPos][0] = cache_get_field_float(i, "PosX");
        ObjectData[i][oPos][1] = cache_get_field_float(i, "PosY");
        ObjectData[i][oPos][2] = cache_get_field_float(i, "PosZ");
        ObjectData[i][oPos][3] = cache_get_field_float(i, "posRX");
        ObjectData[i][oPos][4] = cache_get_field_float(i, "posRY");
        ObjectData[i][oPos][5] = cache_get_field_float(i, "posRZ");

        ObjectText_Refresh(i);
    }
    printf("[BOARD] Loaded %d board from database", rows);
    return 1;
}

ObjectText_Nearest(playerid)
{
    for (new i = 0; i != MAX_TEXTOBJECT; i ++) if(ObjectData[i][oExists] && IsPlayerInRangeOfPoint(playerid, 5, ObjectData[i][oPos][0], ObjectData[i][oPos][1], ObjectData[i][oPos][2]))
    {
        return i;
    }
    return -1;
}

CMD:createobjecttext(playerid, params[])
{
    static
        text[128],
        backcolor,
        fontcolor,
        Float:x,
        Float:y,
        Float:z,
        Float:angle,
        id;

    if (PlayerData[playerid][pAdmin] < 3)
        return PermissionError(playerid);

    if(sscanf(params,"hhs[128]", fontcolor, backcolor,text))
    {
        SendSyntaxMessage(playerid, "/createobjecttext [font color (0xFFFFFFFF)] [back color (0xFFFFFFFF)] [name]");
        SendSyntaxMessage(playerid, "For name you can use format '\n' (new line) '\t' (new tab)");
        return 1;
    }

    GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid, angle);

    x += 1.5 * floatsin(-angle, degrees);
    y += 1.5 * floatcos(-angle, degrees);

    if(strlen(text) > 128)
        return SendErrorMessage(playerid, "The name to long, maximum character is 128.");

    id = ObjectText_Create(playerid, ColouredText(text), x, y, z, 0, 0, 0, fontcolor, backcolor);

    if(id == -1)
        return SendErrorMessage(playerid, "The server has reached the limit for object.");

    EditDynamicObject(playerid, ObjectData[id][objectText]);
    PlayerData[playerid][pEditTextObject] = id;
    PlayerData[playerid][pEditingMode] = OBJECTTEXT;
    SendServerMessage(playerid, "You have successfully created object ID: %d", id);
    return 1;
}

CMD:destroyobjecttext(playerid, params[])
{
    static
        id = 0;

    if (PlayerData[playerid][pAdmin] < 3)
        return PermissionError(playerid);

    if(sscanf(params, "d", id))
        return SendSyntaxMessage(playerid, "/destroyobjecttext [object id]");

    if((id < 0 || id >= MAX_TEXTOBJECT) || !ObjectData[id][oExists])
        return SendErrorMessage(playerid, "You have specified an invalid object ID.");

    ObjectText_Delete(id);
    SendServerMessage(playerid, "You have successfully destroyed object ID: %d.", id);
    return 1;
}

CMD:editobjecttext(playerid, params[])
{
    static
        id,
        type[24],
        string[128];

    if (PlayerData[playerid][pAdmin] < 3)
        return PermissionError(playerid);

    if(sscanf(params, "ds[24]S()[128]", id, type, string))
    {
        SendSyntaxMessage(playerid, "/editobjecttext [id] [name]");
        SendClientMessage(playerid, X11_YELLOW_2, "[NAMES]:"WHITE" position, name, fontcolor, backcolor, duplicate, fontsize, font, model");
        return 1;
    }
    if((id < 0 || id >= MAX_TEXTOBJECT) || !ObjectData[id][oExists])
        return SendErrorMessage(playerid, "You have specified an invalid object text ID.");

    if(!strcmp(type, "position", true))
    {
        EditDynamicObject(playerid, ObjectData[id][objectText]);
        PlayerData[playerid][pEditingMode] = OBJECTTEXT;
        PlayerData[playerid][pEditTextObject] = id;
        SendAdminMessage(X11_TOMATO_1, "AdmCmd: %s now edit object text ID: %d.", ReturnName(playerid, 0), id);
    }
    else if(!strcmp(type, "name", true))
    {
        new name[128];
        if(sscanf(string,"s[128]", name))
            return SendSyntaxMessage(playerid, "/editobjecttext [id] [name] [text]");

        FixText(name);
        format(ObjectData[id][oText], 255, ColouredText(name));
        SendAdminMessage(X11_TOMATO_1, "AdmCmd: %s has edited name of object text ID: %d.", ReturnName(playerid, 0), id);
        ObjectText_Refresh(id);
    }
    else if(!strcmp(type, "fontcolor", true))
    {
        new hax;
        if(sscanf(string,"h", hax))
            return SendSyntaxMessage(playerid, "/editobjecttext [id] [fontcolor] [hax color]");

        ObjectData[id][oFontColor] = hax;
        ObjectText_Refresh(id);
    }
    else if(!strcmp(type, "fontsize", true))
    {
        SetPVarInt(playerid, "FontSizes",id);

        for (new i = 0, j = sizeof(FontSizes); i < j; i++)
        {
            format(string,sizeof(string),"%s%s\n",string,FontSizes[i][1]);
        }
        Dialog_Show(playerid, FontSizes, DIALOG_STYLE_LIST, "FontSize", string, "Select","Close");
    }
    else if(!strcmp(type, "font", true))
    {
        SetPVarInt(playerid, "FontNames",id);
        Dialog_Show(playerid, FontNames, DIALOG_STYLE_LIST, "Font Name's", object_font, "Select","Close");
    }
    else if(!strcmp(type, "model", true))
    {
        new textModel[256];

        SetPVarInt(playerid, "ObjectList",id);

        for (new i = 0, j = sizeof(ObjectList); i < j; i++)
        {
            strcat(textModel, sprintf("%d\t%s\n", ObjectList[i][0], ObjectList[i][1]));
        }
        Dialog_Show(playerid, ObjectList, DIALOG_STYLE_LIST, "Object's Model", textModel, "Select","Close");
    }
    else if(!strcmp(type, "backcolor", true))
    {
        SetPVarInt(playerid, "BackColor",id);
        Dialog_Show(playerid, WarnaBelakang, DIALOG_STYLE_LIST,"BackColor","Custom Color\nAvailable Color\nTransparant","Next","Close");
    }
    else if(!strcmp(type, "duplicate", true))
    {
        new name[128], ids;
        if(sscanf(string,"s[128]", name))
            return SendSyntaxMessage(playerid, "/editobjecttext [id] [duplicate] [name]");

        if(strlen(name) > 128)
            return SendErrorMessage(playerid, "The name to long, maximum character is 128.");

        ids = ObjectText_Create(playerid, ColouredText(name), ObjectData[id][oPos][0], ObjectData[id][oPos][1], ObjectData[id][oPos][2], ObjectData[id][oPos][3], ObjectData[id][oPos][4], ObjectData[id][oPos][5], ObjectData[id][oFontColor], ObjectData[id][oBackColor]);

        if(ids == -1)
            return SendErrorMessage(playerid, "The server has reached the limit for object.");

        EditDynamicObject(playerid, ObjectData[ids][objectText]);
        PlayerData[playerid][pEditTextObject] = ids;
        PlayerData[playerid][pEditingMode] = OBJECTTEXT;
        SendServerMessage(playerid, "You have successfully created object ID: %d.", ids);
        SendAdminMessage(X11_TOMATO_1, "AdmCmd: %s has duplicate object text ID: %d, new object text (id %d).", GetUsername(playerid), id, ids);
    }
    return 1;
}

CMD:objecttextid(playerid, params[])
{
    if (PlayerData[playerid][pAdmin] < 3)
        return PermissionError(playerid);


    static
        id;
        
    if((id = ObjectText_Nearest(playerid)) != -1)

    {
        SendServerMessage(playerid, "You are standing near Object Text ID: %d.", id);
    }
    return 1;
}