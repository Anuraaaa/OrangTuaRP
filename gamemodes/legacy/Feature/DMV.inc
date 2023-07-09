new Float:DMVPoint[][] = 
{
	{-2057.8127,-96.3769,34.9102},
	{-2064.7207,-117.0676,34.3122},
	{-2064.9783,-154.2921,34.1923},
	{-2031.9739,-163.8334,34.2027},
	{-2032.4044,-231.7445,34.2006},
	{-2044.8323,-256.8224,34.2024},
	{-2052.7510,-233.9230,34.2026},
	{-2054.0171,-215.5846,34.2027},
	{-2049.0571,-203.7322,34.2026},
	{-2056.3154,-196.1402,34.2029},
	{-2049.7163,-189.3536,34.2022},
	{-2056.6992,-182.7685,34.2024},
	{-2049.0161,-173.8895,34.2021},
	{-2079.4441,-159.2975,34.2028},
	{-2081.5964,-186.9651,36.1048},
	{-2081.5713,-203.5148,34.2022},
	{-2081.5198,-233.1192,34.2018},
	{-2075.5803,-242.8604,34.2027},
	{-2067.2861,-251.1513,34.2025},
	{-2066.8625,-269.5647,34.2021}
};

CheckPlayerTest(playerid)
{
	if(PlayerData[playerid][pIndexTest] < 6)
	{
		SendClientMessageEx(playerid, COLOR_SERVER, "(DMV) {FFFFFF}Kamu dinyatakan {FF0000}gagal {FFFFFF}dalam test teori");
		SendClientMessageEx(playerid, COLOR_SERVER, "(DMV) {FFFFFF}Kamu hanya menjawab {FFFF00}%d {FFFFFF}pertanyaan benar dari {FFFF00}7 {FFFFFF}pertanyaan", PlayerData[playerid][pIndexTest]);
		PlayerData[playerid][pIndexTest] = 0;
		PlayerData[playerid][pOnTest] = false;
	}
	else
	{
		PlayerData[playerid][pVehicleDMV] = Vehicle_Create(410,-2041.9152,-98.6198,34.9071,359.8441,2, 2);
		VehicleData[PlayerData[playerid][pVehicleDMV]][vFuel] = 20;
		
		SetPlayerVirtualWorld(playerid, 0);
		PlayerData[playerid][pInDoor] = -1;
		SetPlayerInterior(playerid, 0);
		PutPlayerInVehicle(playerid, PlayerData[playerid][pVehicleDMV], 0);
		PlayerData[playerid][pOnDMV] = true;
		PlayerData[playerid][pIndexDMV] = 0;
		SetPlayerCheckpoint(playerid, DMVPoint[PlayerData[playerid][pIndexDMV]][0], DMVPoint[PlayerData[playerid][pIndexDMV]][1], DMVPoint[PlayerData[playerid][pIndexDMV]][2], 3.4);
		SendClientMessage(playerid, COLOR_SERVER, "(DMV) {FFFFFF}Kamu dinyatakan {00FF00}lulus {FFFFFF}dalam test teori!");
		SendClientMessage(playerid, COLOR_SERVER, "(DMV) {FFFFFF}Langkah selanjutnya adalah test mengemudi, silahkan ikuti semua Marker yang ada di radar!");
		SendClientMessage(playerid, COLOR_SERVER, "(DMV) "WHITE"Gunakan "YELLOW"/v engine "WHITE"untuk menyalakan mesin kendaraan.");
	}
	return 1;
}

CMD:drivingtest(playerid, params[])
{
	if(!IsPlayerInRangeOfPoint(playerid, 3.0, -2578.5625, -1383.2179, 1500.7570))
		return SendErrorMessage(playerid, "You are not inside Departement of Motorvehicle!");

	if(PlayerData[playerid][pLicense][0])
		return SendErrorMessage(playerid, "You already have Driving License!");

	if(PlayerData[playerid][pOnTest])
		return SendErrorMessage(playerid, "Kamu sedang memulai Driving Test!");

	if(GetMoney(playerid) < 2500)
		return SendErrorMessage(playerid, "Kamu tidak memiliki cukup uang!");

	new str[412];
	strcat(str, "Selamat datang di Departement of Motorvehicle\n");
	strcat(str, "Silahkan perhatikan hal-hal dibawah ini:\n\n");
	strcat(str, "I. Sebelum melanjutkan ke test mengemudi, akan ada test teori terlebih dahulu.\n");
	strcat(str, "II. Tersedia 7 soal untuk dijawab dan minimal memperoleh 6 jawaban benar untuk ke step selanjutnya.\n");
	strcat(str, "III. Jika sengaja keluar pada saat test, maka akan dinyatakan GAGAL.\n\n");

	strcat(str, "Silahkan klik 'Next' untuk memulai test teori.");
	ShowPlayerDialog(playerid, DIALOG_TEST_MAIN, DIALOG_STYLE_MSGBOX, "Theory Test | DMV", str, "Next", "Close");
	return 1;
}
