#include <YSI_Coding\y_hooks>

new 
    g_ListedProp[MAX_PLAYERS][10];

CMD:paytax(playerid, params[]) {

    if(!IsPlayerInRangeOfPoint(playerid, 5.0, 361.8309,173.6048,1008.3828))
        return SendErrorMessage(playerid, "Kamu tidak berada di tax office atau paytax point.");

    ShowPlayerDialog(playerid, DIALOG_PAYTAX, DIALOG_STYLE_LIST, "Tax Menu", "Flat\nHouse", "Select", "Close");
    return 1;
}

ShowFlatTax(playerid) {

    if(!Flat_GetCount(playerid))
        return SendErrorMessage(playerid, "Kamu tidak memiliki flat.");

    new string[512],count = 0;
    foreach(new i : Flat) if(Flat_IsOwner(playerid, i)) {

        new price = 0;

        price = FlatData[i][flatPrice] * 5/100;

        format(string, sizeof(string), "%sFlat ID: %d ($%s) %s: %s [%s"WHITE"]\n", string, i, FormatNumber(price), (FlatData[i][flatTaxState] == TAX_STATE_COOLDOWN) ? ("Pay in") : ("Due date"), ConvertTimestamp(Timestamp:FlatData[i][flatTaxDate]), (FlatData[i][flatTaxState] == TAX_STATE_COOLDOWN) ? (""DARKRED"can't be paid") : (""DARKGREEN"can be paid"));
        g_ListedProp[playerid][count++] = i;
    }
    if(count)
        ShowPlayerDialog(playerid, DIALOG_PAYTAX_FLAT, DIALOG_STYLE_LIST, "Tax of Flat", string, "Pay", "Close");

    return 1;

}

ShowHouseTax(playerid) {
    if(!House_GetCount(playerid))
        return SendErrorMessage(playerid, "Kamu tidak memiliki rumah.");

    new string[512],count = 0;
    foreach(new i : House) if(House_IsOwner(playerid, i)) {

        new price = 0;

        price = HouseData[i][housePrice] * 5/100;

        format(string, sizeof(string), "%sHouse ID: %d ($%s) %s: %s [%s"WHITE"]\n", string, i, FormatNumber(price), (HouseData[i][houseTaxState] == TAX_STATE_COOLDOWN) ? ("Pay in") : ("Due date"), ConvertTimestamp(Timestamp:HouseData[i][houseTaxDate]), (HouseData[i][houseTaxState] == TAX_STATE_COOLDOWN) ? (""DARKRED"can't be paid") : (""DARKGREEN"can be paid"));
        g_ListedProp[playerid][count++] = i;
    }
    if(count)
        ShowPlayerDialog(playerid, DIALOG_PAYTAX_HOUSE, DIALOG_STYLE_LIST, "Tax of House", string, "Pay", "Close");

    return 1;
}
hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {
    if(dialogid == DIALOG_PAYTAX) {
        if(response) {
            switch(listitem) {
                case 0: ShowFlatTax(playerid);
                case 1: ShowHouseTax(playerid);
            }
        }   
    }
    if(dialogid == DIALOG_PAYTAX_HOUSE) {
        if(response) {
            new id = -1, price = 0;

            id = g_ListedProp[playerid][listitem], price = 0;

            if(HouseData[id][houseTaxState] == TAX_STATE_COOLDOWN)
                return SendErrorMessage(playerid, "Sekarang belum waktunya membayar pajak untuk rumah ini.");


            price = HouseData[id][housePrice] * 5/100;

            if(GetMoney(playerid) < price)
                return SendErrorMessage(playerid, "Kamu tidak memiliki cukup uang untuk membayar pajak.");

            GiveMoney(playerid, -price, "Bayar pajak");
            HouseData[id][houseTaxDate] = gettime() + (14 * 86400);
            HouseData[id][houseTaxState] = TAX_STATE_COOLDOWN;
            HouseData[id][houseTaxPaid] = true;

            SendClientMessageEx(playerid, X11_LIGHTBLUE, "TAX: "WHITE"Kamu berhasil membayar pajak untuk rumah-mu dengan harga "GREEN"$%s", FormatNumber(price));
            SendClientMessageEx(playerid, X11_LIGHTBLUE, "TAX: "WHITE"Terimakasih telah membayar pajak! bayar lagi dalam 14 hari.");

            serverVault += price;
            SaveEconomyData();
        }
    }
    if(dialogid == DIALOG_PAYTAX_FLAT) {
        if(response) {
            new id = -1, price = 0;

            id = g_ListedProp[playerid][listitem], price = 0;

            if(FlatData[id][flatTaxState] == TAX_STATE_COOLDOWN)
                return SendErrorMessage(playerid, "Sekarang belum waktunya membayar pajak untuk flat ini.");


            price = FlatData[id][flatPrice] * 5/100;

            if(GetMoney(playerid) < price)
                return SendErrorMessage(playerid, "Kamu tidak memiliki cukup uang untuk membayar pajak.");

            GiveMoney(playerid, -price, "Bayar pajak");
            FlatData[id][flatTaxDate] = gettime() + (14 * 86400);
            FlatData[id][flatTaxState] = TAX_STATE_COOLDOWN;
            FlatData[id][flatTaxPaid] = true;

            SendClientMessageEx(playerid, X11_LIGHTBLUE, "TAX: "WHITE"Kamu berhasil membayar pajak untuk flat-mu dengan harga "GREEN"$%s", FormatNumber(price));
            SendClientMessageEx(playerid, X11_LIGHTBLUE, "TAX: "WHITE"Terimakasih telah membayar pajak! bayar lagi dalam 14 hari.");
            serverVault += price;
            SaveEconomyData();
        }
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}

task house_OnTaxUpdate[60000]() {
    foreach(new i : Flat) if(HouseData[i][houseTaxDate] != 0 && HouseData[i][houseOwner] != 0) {
        if(HouseData[i][houseTaxDate] <= gettime()) {
            if(HouseData[i][houseTaxState] == TAX_STATE_COOLDOWN) {
                HouseData[i][houseTaxState] = TAX_STATE_DEADLINE;
                HouseData[i][houseTaxDate] = gettime() + (3 * 86400);
                HouseData[i][houseTaxPaid] = false;
            }
            else {
                SendAdminMessage(X11_TOMATO, "HouseWarn: House ID %d telah di asell karena tidak membayar pajak.", i);

                new string[256], msge[128];
                format(msge, 128, "Rumahmu (ID:%d) telah otomatis dijual oleh pemerintah karena tidak membayar pajak.", i);

                mysql_format(sqlcon, string, 256, "INSERT INTO `house_queue` (`Username`, `HouseID`, `Message`) VALUES('%e','%d','%e')", HouseData[i][houseOwnerName], i, msge);
                mysql_tquery(sqlcon,string);

                foreach(new id : Player) if(PlayerData[id][pID] == HouseData[i][houseOwner]) {
                    SendClientMessageEx(id, X11_LIGHTBLUE, "TAX: "WHITE"Rumahmu (ID:%d) telah otomatis dijual oleh pemerintah karena tidak membayar pajak.", i);
                    break;
                }
                HouseData[i][houseLastLogin] = 0;
            
                HouseData[i][houseOwner] = -1;
                format(HouseData[i][houseOwnerName], MAX_PLAYER_NAME, "No Owner");

                House_Save(i);
                House_Refresh(i);
            }
        }
    }
    return 1;
}
task flat_OnTaxUpdate[60000]() {

    foreach(new i : Flat) if(FlatData[i][flatTaxDate] != 0 && FlatData[i][flatOwner] != -1) {
        if(FlatData[i][flatTaxDate] <= gettime()) {
            if(FlatData[i][flatTaxState] == TAX_STATE_COOLDOWN) {
                FlatData[i][flatTaxState] = TAX_STATE_DEADLINE;
                FlatData[i][flatTaxDate] = gettime() + (3 * 86400);
                FlatData[i][flatTaxPaid] = false;
            }
            else {
                SendAdminMessage(X11_TOMATO, "FlatWarn: Flat ID %d telah di asell karena tidak membayar pajak.", i);

                new string[256], msge[128];
                format(msge, 128, "Flat mu (ID:%d) telah otomatis dijual oleh pemerintah karena tidak membayar pajak.", i);

                mysql_format(sqlcon, string, 256, "INSERT INTO `flat_queue` (`Username`, `FlatID`, `Message`) VALUES('%e','%d','%e')", FlatData[i][flatOwnerName], i, msge);
                mysql_tquery(sqlcon,string);
                FlatData[i][flatLastLogin] = 0;
            
                FlatData[i][flatOwner] = -1;
                format(FlatData[i][flatOwnerName], MAX_PLAYER_NAME, "No Owner");

                Flat_Save(i);
                Flat_Sync(i);
            }
        }
    }
    return 1;
}

CMD:taxinited(playerid, params[]) {
    foreach(new index : Flat) {
		FlatData[index][flatTaxDate] = gettime() + (14 * 86400);
		FlatData[index][flatTaxState] = TAX_STATE_COOLDOWN;
		FlatData[index][flatTaxPaid] = true;
        Flat_Save(index);
    }

    foreach(new i : House) {
        HouseData[i][houseTaxDate] = gettime() + (14 * 86400);
        HouseData[i][houseTaxPaid] = true;
        HouseData[i][houseTaxState] = TAX_STATE_COOLDOWN;

        House_Save(i);
    }
    return 1;
}