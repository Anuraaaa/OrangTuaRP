#include <YSI_Coding\y_hooks>

new salarySweeper = 1500,
    salaryBus = 5000,
    salaryTrashmaster = 1000,
	salaryMower = 3000,
	serverVault = 0;


SaveEconomyData()
{
	new coordsString[128];
	format(coordsString, sizeof(coordsString), "%d, %d, %d, %d, %d", salarySweeper, salaryBus, salaryTrashmaster, salaryMower, serverVault);
	new File: file2 = fopen("economy.ini", io_write);
	fwrite(file2, coordsString);
	fclose(file2);
	return 1;	
}

LoadEconomyData()
{
	new arrCoords[20][64];
	new strFromFile2[256];
	new File: file = fopen("economy.ini", io_read);
	if (file)
	{
		fread(file, strFromFile2);
		splits(strFromFile2, arrCoords, ',');
		salarySweeper = strval(arrCoords[0]);
		salaryBus = strval(arrCoords[1]);
        salaryTrashmaster = strval(arrCoords[2]);
		salaryMower = strval(arrCoords[3]);
		serverVault = strval(arrCoords[4]);
		
		fclose(file);
        print("Economy Data Loaded.");
	}
	return 1;
}

ShowMowerEconomy(playerid) {
	return ShowPlayerDialog(playerid, DIALOG_ECONOMY_MOWER, DIALOG_STYLE_INPUT, "Mower Economy", sprintf("Masukkan salary baru untuk sidejob mower:\n(current: $%s)", FormatNumber(salaryMower)), "Set", "Close");

}

ShowSweeperEconomy(playerid) {
	return ShowPlayerDialog(playerid, DIALOG_ECONOMY_SWEEPER, DIALOG_STYLE_INPUT, "Sweeper Economy", sprintf("Masukkan salary baru untuk sidejob sweeper:\n(current: $%s)", FormatNumber(salarySweeper)), "Set", "Close");

}

ShowBusEconomy(playerid) {
	return ShowPlayerDialog(playerid, DIALOG_ECONOMY_BUS, DIALOG_STYLE_INPUT, "Bus Economy", sprintf("Masukkan salary baru untuk sidejob bus:\n(current: $%s)", FormatNumber(salaryBus)), "Set", "Close");

}

ShowTrashmasterEconomy(playerid) {
	return ShowPlayerDialog(playerid, DIALOG_ECONOMY_TRASHMASTER, DIALOG_STYLE_INPUT, "Sweeper Economy", sprintf("Masukkan salary baru untuk sidejob trashmaster (per-trashbag):\n(current: $%s)", FormatNumber(salaryTrashmaster)), "Set", "Close");

}
CMD:seteconomy(playerid, params[]) {
	if(PlayerData[playerid][pAdmin] < 6)
	    return SendErrorMessage(playerid, NO_PERMISSION);

    new str[512];
    strcat(str, sprintf("Sweeper salary: $%s\n", FormatNumber(salarySweeper)));
    strcat(str, sprintf("Bus salary: $%s\n", FormatNumber(salaryBus)));
    strcat(str, sprintf("Trashmaster salary (per-loadedbag): $%s\n", FormatNumber(salaryTrashmaster)));
	strcat(str, sprintf("Mower: $%s\n", FormatNumber(salaryMower)));
    ShowPlayerDialog(playerid, DIALOG_ECONOMY, DIALOG_STYLE_LIST, "Economy Menu", str, "Set", "Close");
    return 1;
}



hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {
	if(dialogid == DIALOG_ECONOMY) {

		if(!response)
			return 0;

		if(listitem == 0) ShowSweeperEconomy(playerid);
		if(listitem == 1) ShowBusEconomy(playerid);
		if(listitem == 2) ShowTrashmasterEconomy(playerid);
		if(listitem == 3) ShowMowerEconomy(playerid);
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}