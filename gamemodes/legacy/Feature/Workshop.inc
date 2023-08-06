#include <YSI_Coding\y_hooks>

enum E_WORKSHOP_DATA {
    wsID,
    wsOwner,
    wsOwnerName[MAX_PLAYER_NAME],
    wsPrice,
    wsVault,
    wsWorld,
    wsName[24],
    wsLocked,
    Float:wsVehPos[4],
    Float:wsFootPos[3],
    Text3D:wsVehLabel,
    Text3D:wsFootLabel,
    STREAMER_TAG_PICKUP:wsVehPickup,
    STREAMER_TAG_PICKUP:wsFootPickup
};
new
    WorkshopData[MAX_WORKSHOP][E_WORKSHOP_DATA],
    Iterator:Workshop<MAX_WORKSHOP>;


Workshop_Create(Float:x, Float:y, Float:z, price) {

    new index = INVALID_ITERATOR_SLOT;

    if((index = Iter_Free(Workshop)) != INVALID_ITERATOR_SLOT) {

        Iter_Add(Workshop, index);

        format(WorkshopData[index][wsOwnerName], MAX_PLAYER_NAME, "-");
        format(WorkshopData[index][wsName], 24, "-");

        WorkshopData[index][wsOwner] = -1;
        WorkshopData[index][wsPrice] = price;
        WorkshopData[index][wsVault] = 0;
        WorkshopData[index][wsFootPos][0] = x;
        WorkshopData[index][wsFootPos][1] = y;
        WorkshopData[index][wsFootPos][2] = z;
        WorkshopData[index][wsLocked] = false;

        for(new i = 0; i < 4; i++) {
            WorkshopData[index][wsVehPos][i] = 0.0;
        }

        Workshop_Sync(index);

        mysql_tquery(sqlcon, "INSERT INTO `workshop` (`Price`) VALUES(0)", "OnWorkshopCreated", "d", index);
        return index;
    }
    return INVALID_ITERATOR_SLOT;
}

function OnWorkshopCreated(id) {
    if(!Iter_Contains(Workshop, id))
        return 0;

    WorkshopData[id][wsID] = cache_insert_id();
    WorkshopData[id][wsWorld] = WorkshopData[id][wsID] + 100;
    Workshop_Save(id);
    
    return 1;
}

Workshop_Save(id) {
    if(!Iter_Contains(Workshop, id))
        return 0;

    
    new query[1712];
    mysql_format(sqlcon, query, sizeof(query), "UPDATE `workshop` SET `Owner` = '%d', `OwnerName` = '%e', `Name` = '%e', `Price` = '%d', `Vault` = '%d', `Locked` = '%d', `World` = '%d'",
        WorkshopData[id][wsOwner],
        WorkshopData[id][wsOwnerName],
        WorkshopData[id][wsName],
        WorkshopData[id][wsPrice],
        WorkshopData[id][wsVault],
        WorkshopData[id][wsLocked],
        WorkshopData[id][wsWorld]
    );
    mysql_format(sqlcon, query, sizeof(query), "%s, `FootX` = '%.4f', `FootY` = '%.4f', `FootZ` = '%.4f', `VehX` = '%.4f', `VehY` = '%.4f', `VehZ` = '%.4f', `VehA` = '%.4f'",
        query,
        WorkshopData[id][wsFootPos][0],
        WorkshopData[id][wsFootPos][1],
        WorkshopData[id][wsFootPos][2],
        WorkshopData[id][wsVehPos][0],
        WorkshopData[id][wsVehPos][1],
        WorkshopData[id][wsVehPos][2],
        WorkshopData[id][wsVehPos][3]
    );
    mysql_format(sqlcon, query, sizeof(query), "%s WHERE `ID` = '%d'",
        query,
        WorkshopData[id][wsID]
    );
    mysql_tquery(sqlcon, query);
    return 1;
}

function Workshop_Load() {
    new 
        rows = cache_num_rows();

    if(rows) {
        for(new i = 0; i < rows; i++) {
            Iter_Add(Workshop, i);

            cache_get_value_name_int(i, "ID", WorkshopData[i][wsID]);
            cache_get_value_name_int(i, "Owner", WorkshopData[i][wsOwner]);
            cache_get_value_name(i, "OwnerName", WorkshopData[i][wsOwnerName], MAX_PLAYER_NAME);
            cache_get_value_name(i, "Name", WorkshopData[i][wsName], 24);
            cache_get_value_name_int(i, "Locked", WorkshopData[i][wsLocked]);
            cache_get_value_name_int(i, "Price", WorkshopData[i][wsPrice]);
            cache_get_value_name_int(i, "Vault", WorkshopData[i][wsVault]);
            cache_get_value_name_float(i, "FootX", WorkshopData[i][wsFootPos][0]);
            cache_get_value_name_float(i, "FootY", WorkshopData[i][wsFootPos][1]);
            cache_get_value_name_float(i, "FootZ", WorkshopData[i][wsFootPos][2]);
            cache_get_value_name_float(i, "VehX", WorkshopData[i][wsVehPos][0]);
            cache_get_value_name_float(i, "VehY", WorkshopData[i][wsVehPos][1]);
            cache_get_value_name_float(i, "VehZ", WorkshopData[i][wsVehPos][2]);
            cache_get_value_name_float(i, "VehA", WorkshopData[i][wsVehPos][3]);
            cache_get_value_name_int(i, "World", WorkshopData[i][wsWorld]);

            Workshop_Sync(i);
        }
    }
    printf("[WORKSHOP] Loaded %d workshop from database.", rows);
    return 1;
}

Workshop_IsOwner(playerid, id) {
    if(Iter_Contains(Workshop, id)) {
        if(WorkshopData[id][wsOwner] == PlayerData[playerid][pID]) {
            return 1;
        }
    }
    return 0;
}

Workshop_Sync(id) {

    if(!Iter_Contains(Workshop, id))
        return 0;

    new str[144];

    if(WorkshopData[id][wsOwner] == -1) {
        format(str, sizeof(str), "[Workshop %d]\nWorkshop price: $%s\nType /workshop buy to purchase.", id, FormatNumber(WorkshopData[id][wsPrice]));
    }
    else format(str, sizeof(str), "[Workshop %d]\n%s\nOwned by %s", id, WorkshopData[id][wsName], WorkshopData[id][wsOwnerName]);

    if(IsValidDynamic3DTextLabel(WorkshopData[id][wsFootLabel]))
        Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, WorkshopData[id][wsFootLabel], WorkshopData[id][wsFootPos][0], WorkshopData[id][wsFootPos][1], WorkshopData[id][wsFootPos][2]);
    else WorkshopData[id][wsFootLabel] = CreateDynamic3DTextLabel(str, -1, WorkshopData[id][wsFootPos][0], WorkshopData[id][wsFootPos][1], WorkshopData[id][wsFootPos][2], 10.0);
    
    if(IsValidDynamicPickup(WorkshopData[id][wsFootPickup]))
        Streamer_SetItemPos(STREAMER_TYPE_PICKUP, WorkshopData[id][wsFootPickup], WorkshopData[id][wsFootPos][0], WorkshopData[id][wsFootPos][1], WorkshopData[id][wsFootPos][2]);
    else WorkshopData[id][wsFootPickup] = CreateDynamicPickup(1239, 23, WorkshopData[id][wsFootPos][0], WorkshopData[id][wsFootPos][1], WorkshopData[id][wsFootPos][2], -1, -1, -1, 15.0);

    UpdateDynamic3DTextLabelText(WorkshopData[id][wsFootLabel], -1, str);
    return 1;
}

Workshop_AddEmployee(playerid, id) {
    if(Iter_Contains(Workshop, id)) {
        new query[144];
        mysql_format(sqlcon, query, sizeof(query), "INSERT INTO `workshop_employee` (`Name`, `WorkshopID`) VALUES('%e','%d')", GetName(playerid), WorkshopData[id][wsID]);
        mysql_tquery(sqlcon, query);
    }
    return 1;
}
Workshop_IsEmployee(playerid, id) {
    new Cache:cache, result, query[144];
    
    mysql_format(sqlcon, query, sizeof(query), "SELECT * FROM `workshop_employee` WHERE `Name` = '%e' AND `WorkshopID` = '%d'", GetName(playerid), WorkshopData[id][wsID]);
    cache = mysql_query(sqlcon, query);
    result = cache_num_rows();
    cache_delete(cache);
    return result;
}

Workshop_HaveAccess(playerid, id) {
    if(Workshop_IsOwner(playerid, id))
        return 1;

    if(Workshop_IsEmployee(playerid, id))
        return 1;
    
    return 0;
}

Workshop_Nearest(playerid, Float:range = 5.0) {
    new index = -1;
    foreach(new i : Workshop) if(IsPlayerInRangeOfPoint(playerid, range, WorkshopData[i][wsFootPos][0], WorkshopData[i][wsFootPos][1], WorkshopData[i][wsFootPos][2])) {
        index = i;
        break;
    }
    return index;
}

Workshop_Delete(id) {
    if(!Iter_Contains(Workshop, id))
        return 0;

    if(IsValidDynamic3DTextLabel(WorkshopData[id][wsFootLabel]))
        DestroyDynamic3DTextLabel(WorkshopData[id][wsFootLabel]);

    if(IsValidDynamic3DTextLabel(WorkshopData[id][wsVehLabel]))
        DestroyDynamic3DTextLabel(WorkshopData[id][wsVehLabel]);

    if(IsValidDynamicPickup(WorkshopData[id][wsFootPickup]))
        DestroyDynamicPickup(WorkshopData[id][wsFootPickup]);

    if(IsValidDynamicPickup(WorkshopData[id][wsVehPickup]))
        DestroyDynamicPickup(WorkshopData[id][wsVehPickup]);

    mysql_tquery(sqlcon, sprintf("DELETE FROM `workshop_employee` WHERE `WorkshopID` = '%d'", WorkshopData[id][wsID]));
    mysql_tquery(sqlcon, sprintf("DELETE FROM `workshop` WHERE `ID` = '%d'", WorkshopData[id][wsID]));
    WorkshopData[id][wsID] = 0;
    WorkshopData[id][wsOwner] = -1;
    Iter_Remove(Workshop, id);
    return 1;
}

/* Commands */

CMD:createworkshop(playerid, params[]) {
    if(PlayerData[playerid][pAdmin] < 6)
        return PermissionError(playerid);

    new price[32], index = INVALID_ITERATOR_SLOT;
    if(sscanf(params, "s[32]", price))
        return SendSyntaxMessage(playerid, "/createworkshop [price]");

    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);

    index = Workshop_Create(x, y, z, strcash(price));

    if(index == INVALID_ITERATOR_SLOT)
        return SendErrorMessage(playerid, "Server ini tidak dapat membuat lebih banyak workshop.");

    SendAdminAction(playerid, "Kamu telah membuat workshop %d dengan harga $%s.", index, FormatNumber(strcash(price)));
    return 1;
}

CMD:editworkshop(playerid, params[]) {
    new str[24], string[128], index;

    if(PlayerData[playerid][pAdmin] < 6)
        return PermissionError(playerid);
        
    if(sscanf(params, "ds[24]S()[128]", index, str, string))
        return SendSyntaxMessage(playerid, "/editworkshop [wsid] [pos/price/asell/delete]");

    if(!Iter_Contains(Workshop, index))
        return SendErrorMessage(playerid, "Workshop ID %d is doesnt exists!", index);

    if(!strcmp(str, "delete", true)) {

        Workshop_Delete(index);
        SendAdminAction(playerid, "Kamu telah menghapus workshop %d.", index);
    }
    else if(!strcmp(str, "pos", true)) {
        GetPlayerPos(playerid, WorkshopData[index][wsFootPos][0],WorkshopData[index][wsFootPos][1], WorkshopData[index][wsFootPos][2]);
        Workshop_Save(index);
        Workshop_Sync(index);


        SendAdminAction(playerid, "Kamu telah mengubah foot position workshop %d.", index);

        Streamer_Update(playerid, STREAMER_TYPE_PICKUP);
    }
    else if(!strcmp(str, "price", true)) {
        new
            harga[32];

        if(sscanf(string, "s[32]", harga))
            return SendSyntaxMessage(playerid, "/editworkshop [wsid] [price] [new price]");

        WorkshopData[index][wsPrice] = strcash(harga);
        Workshop_Sync(index);
        Workshop_Save(index);

        SendAdminAction(playerid, "Kamu telah mengubah harga workshop %d menjadi $%s.", index, FormatNumber(strcash(harga)));
    }
    else if(!strcmp(str, "asell", true)) {


        if(WorkshopData[index][wsOwner] == -1)
            return SendErrorMessage(playerid, "This workshop  is already selled!");

        WorkshopData[index][wsOwner] = -1;
        format(WorkshopData[index][wsOwnerName], MAX_PLAYER_NAME, "-");
        format(WorkshopData[index][wsName], 24, "-");

        Workshop_Sync(index);
        Workshop_Save(index);

        SendAdminAction(playerid, "Kamu telah menjual workshop %d.", index);
    }
    return 1;

}
CMD:workshop(playerid, params[]) {

    new str[24], string[128], index, cash[32], amount;

    if(sscanf(params, "s[24]S()[128]", str, string))
        return SendSyntaxMessage(playerid, "/workshop [buy/deposit/withdraw/employee/name]");

    if(!strcmp(str, "buy", true)) {

        index = Workshop_Nearest(playerid);

        if(index == -1)
            return SendErrorMessage(playerid, "Kamu tidak berada pada point workshop manapun.");

        if(WorkshopData[index][wsOwner] != -1)
            return SendErrorMessage(playerid, "Workshop ini sudah dimiliki orang lain.");

        if(GetMoney(playerid) < WorkshopData[index][wsPrice])
            return SendErrorMessage(playerid, "Kamu tidak memiliki cukup uang.");

        WorkshopData[index][wsOwner] = PlayerData[playerid][pID];
        format(WorkshopData[index][wsOwnerName], MAX_PLAYER_NAME, GetName(playerid));
        Workshop_Save(index);
        Workshop_Sync(index);
        SendServerMessage(playerid, "Kamu berhasil membeli workshop dengan harga "GREEN"$%s", FormatNumber(WorkshopData[index][wsPrice]));
    }
    else if(!strcmp(str, "employee", true)) {

        index = Workshop_Nearest(playerid);

        if(index == -1)
            return SendErrorMessage(playerid, "Kamu tidak berada didalam workshop milikmu.");

        if(!Workshop_IsOwner(playerid, index))
            return SendErrorMessage(playerid, "Kamu bukan pemilik workshop ini.");

        ShowPlayerDialog(playerid, DIALOG_WS_EMPLOYEE, DIALOG_STYLE_LIST, "Workshop Employee", "Hire\nRemove\nListed employee", "Select", "Close");
    }
    else if(!strcmp(str, "name", true)) {
        index = Workshop_Nearest(playerid);
        new ws_new_name[24];

        if(index == -1)
            return SendErrorMessage(playerid, "Kamu tidak berada didalam workshop manapun.");

        if(!Workshop_IsOwner(playerid, index))
            return SendErrorMessage(playerid, "Kamu bukan pemilik workshop ini.");

        if(sscanf(string, "s[24]", ws_new_name))
            return SendSyntaxMessage(playerid, "/workshop [name] [new workshop name]");

        if(strlen(ws_new_name) > 24)
            return SendErrorMessage(playerid, "Tidak bisa lebih dari 24 huruf.");

        format(WorkshopData[index][wsName], 24, ws_new_name);
        Workshop_Save(index);
        Workshop_Sync(index);
        SendServerMessage(playerid, "Kamu telah mengubah nama workshop menjadi %s.", ws_new_name);

    }
    else if(!strcmp(str, "deposit", true)) {
        index = Workshop_Nearest(playerid);
        if(index == -1)
            return SendErrorMessage(playerid, "Kamu tidak berada didalam workshop manapun.");

        if(!Workshop_HaveAccess(playerid, index))
            return SendErrorMessage(playerid, "Kamu tidak memiliki akses workshop ini.");

        if(sscanf(string, "s[32]", cash))
            return SendSyntaxMessage(playerid, "/workshop [deposit] [amount]");

        amount = strcash(cash);

        if(!amount)
            return SendErrorMessage(playerid, "Tidak bisa memasukkan jumlah yang invalid.");

        if(amount < 0 || amount > 5000000)
            return SendErrorMessage(playerid, "You have input invalid amount.");

        if(GetMoney(playerid) < amount)
            return SendErrorMessage(playerid, "Kamu tidak memiliki uang sebanyak itu.");

        WorkshopData[index][wsVault] += amount;
        GiveMoney(playerid, -amount, "Deposit WS");
        SendServerMessage(playerid, "Kamu memasukkan "GREEN"$%s "WHITE"kedalam cash vault, total vault adalah "GREEN"$%s", FormatNumber(amount), FormatNumber(WorkshopData[index][wsVault]));
        Workshop_Save(index);
    }
    else if(!strcmp(str, "balance", true)) {

        index = Workshop_Nearest(playerid);

        if(index == -1)
            return SendErrorMessage(playerid, "Kamu tidak berada didalam workshop manapun.");

        if(!Workshop_HaveAccess(playerid, index))
            return SendErrorMessage(playerid, "Kamu tidak memiliki akses workshop ini.");

        SendServerMessage(playerid, "Total vault dalam workshop ini adalah "GREEN"$%s", FormatNumber(WorkshopData[index][wsVault]));
    }
    else if(!strcmp(str, "withdraw", true)) {

        index = Workshop_Nearest(playerid);

        if(index == -1)
            return SendErrorMessage(playerid, "Kamu tidak berada didalam workshop manapun.");

        if(!Workshop_IsOwner(playerid, index))
            return SendErrorMessage(playerid, "Kamu tidak memiliki akses workshop ini.");

        if(sscanf(string, "s[32]", cash))
            return SendSyntaxMessage(playerid, "/witdraw [deposit] [amount]");     

        amount = strcash(cash);

        if(!amount)
            return SendErrorMessage(playerid, "Tidak bisa memasukkan jumlah yang invalid.");

        if(amount < 0 || amount > 5000000)
            return SendErrorMessage(playerid, "You have input invalid amount.");


        if(WorkshopData[index][wsVault] < amount)
            return SendErrorMessage(playerid, "Workshop ini tidak memiliki uang sebanyak itu.");

        WorkshopData[index][wsVault] -= amount;
        GiveMoney(playerid, amount, "Withdraw WS");
        SendServerMessage(playerid, "Kamu mengambil "GREEN"$%s "WHITE"dari cash vault, total vault adalah "GREEN"$%s", FormatNumber(amount), FormatNumber(WorkshopData[index][wsVault]));
        Workshop_Save(index);
    }
    return 1;

}

function ShowWorkshopEmployee(playerid) {
    if(cache_num_rows()) {

        new str[312];

        for(new i = 0; i < cache_num_rows(); i++) {

            new
                char_name[MAX_PLAYER_NAME];

            cache_get_value_name(i, "Name", char_name, MAX_PLAYER_NAME);

            strcat(str, sprintf("%d) %s\n", i + 1, char_name));
        }
        ShowPlayerDialog(playerid, DIALOG_NONE, DIALOG_STYLE_LIST, "Listed Employee", str, "Close", "");
    }
    else SendErrorMessage(playerid, "Workshop ini tidak memiliki pekerja satupun.");
    return 1;
}
function OnRemoveEmployee(playerid, id, inputtext[]) {
    if(cache_num_rows()) {

        new query[256];
        mysql_format(sqlcon, query, sizeof(query), sprintf("DELETE FROM `workshop_employee` WHERE `Name` = '%e' AND `WorkshopID` = '%d'", inputtext, WorkshopData[id][wsID]));
        mysql_tquery(sqlcon, query);

        SendServerMessage(playerid, "Pekerja %s berhasil dihapus dari daftar.", inputtext);
    }
    else SendErrorMessage(playerid, "Tidak ada pekerjamu dengan nama tersebut.");
    return 1;
}