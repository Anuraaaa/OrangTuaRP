LoadStaticVehicle()
{
	TrashVehicle[0] = Vehicle_Create(408, -1916.6907, -1702.9725, 22.3032, 184.3942, 26, 26, 0, false);
    TrashVehicle[1] = Vehicle_Create(408, -1912.3484, -1702.5702, 22.2899, 183.3604, 26, 26, 0, false);
    TrashVehicle[2] = Vehicle_Create(408, -1908.4242, -1702.2488, 22.3004, 184.5224, 26, 26, 0, false);
	forex(i, sizeof(TrashVehicle))
	{
		VehicleData[TrashVehicle[i]][vFuel] = 100;
		SetVehicleNumberPlate(TrashVehicle[i], "TRASHMASTER-SIDEJOB");
		Vehicle_SetType(TrashVehicle[i], VEHICLE_TYPE_SIDEJOB);
	}
	MowerVehicle[0] = Vehicle_Create(572,-2288.9854,174.6294,34.8807,90.9118,1, 1, 0, false);
	MowerVehicle[1] = Vehicle_Create(572,-2289.0369,172.4341,34.8758,90.5593,1, 1, 0, false);
	MowerVehicle[2] = Vehicle_Create(572,-2289.1563,170.1806,34.8839,90.9597,1, 1, 0, false);
	MowerVehicle[3] = Vehicle_Create(572,-2288.9021,167.7834,34.8719,92.3754,1, 1, 0, false);
	forex(i, sizeof(MowerVehicle))
	{
		VehicleData[MowerVehicle[i]][vFuel] = 100;
		SetVehicleNumberPlate(MowerVehicle[i], "MOWER-SIDEJOB");
		Vehicle_SetType(MowerVehicle[i], VEHICLE_TYPE_SIDEJOB);
	}
	RumpoVehicle[0] = Vehicle_Create(440,-1728.6257,81.1566,3.6649,227.6105, 6, 6, 0, false);
	RumpoVehicle[1] = Vehicle_Create(440,-1726.3901,83.8279,3.6613,228.0577,6, 6, 0, false);
	RumpoVehicle[2] = Vehicle_Create(440,-1724.2279,86.0643,3.6666,226.7363,6, 6, 0, false);
	RumpoVehicle[3] = Vehicle_Create(440,-1722.1833,88.2215,3.6613,225.4247,6, 6, 0, false);
	RumpoVehicle[4] = Vehicle_Create(440,-1720.2440,90.4035,3.6726,228.3086,6, 6, 0, false);
	RumpoVehicle[5] = Vehicle_Create(440,-1718.0669,92.5779,3.6678,224.4250,6, 6, 0, false);
	forex(i, sizeof(RumpoVehicle))
	{
		VehicleData[RumpoVehicle[i]][vFuel] = 100;
		SetVehicleNumberPlate(RumpoVehicle[i], "RUMPO-SIDEJOB");
		Vehicle_SetType(RumpoVehicle[i], VEHICLE_TYPE_SIDEJOB);
	}
	ForkliftVehicle[0] = Vehicle_Create(530,-1707.3604,29.3464,3.3180,226.0739, 6, 6, 0, false);
	ForkliftVehicle[1] = Vehicle_Create(530,-1708.5570,27.9553,3.3198,225.0886,6, 6, 0, false);
	ForkliftVehicle[2] = Vehicle_Create(530,-1709.9226,26.6131,3.3192,227.7379,6, 6, 0, false);
	ForkliftVehicle[3] = Vehicle_Create(530,-1711.2915,25.3742,3.3183,226.9580,6, 6, 0, false);
	ForkliftVehicle[4] = Vehicle_Create(530,-1712.6451,24.0886,3.3177,225.4359,6, 6, 0, false);
	ForkliftVehicle[5] = Vehicle_Create(530,-1713.9181,23.0443,3.3232,225.7067,6, 6, 0, false);
	forex(i, sizeof(ForkliftVehicle))
	{
		VehicleData[ForkliftVehicle[i]][vFuel] = 100;
		SetVehicleNumberPlate(ForkliftVehicle[i], "FORKLIFT-SIDEJOB");
		Vehicle_SetType(ForkliftVehicle[i], VEHICLE_TYPE_SIDEJOB);
	}
	SweeperVehicle[0] = Vehicle_Create(574,-2093.7937,-83.2754,34.8914,178.7325,1, 1, 0, false);
	SweeperVehicle[1] = Vehicle_Create(574,-2089.5867,-83.4144,34.8925,177.5521,1, 1, 0, false);
	SweeperVehicle[2] = Vehicle_Create(574,-2085.6165,-83.4752,34.8632,183.9264,1, 1, 0, false);
	forex(i, sizeof(SweeperVehicle))
	{
		VehicleData[SweeperVehicle[i]][vFuel] = 100;
		SetVehicleNumberPlate(SweeperVehicle[i], "SWEEPER-SIDEJOB");
		Vehicle_SetType(SweeperVehicle[i], VEHICLE_TYPE_SIDEJOB);
	}
	Bus2Vehicle[0] = Vehicle_Create(437,-2511.6821,1205.4083,37.5022,270.0276,1, 1, 0, false);
	Bus2Vehicle[1] = Vehicle_Create(437,-2511.6414,1209.5726,37.5030,270.8899,1, 1, 0, false);
	forex(i, sizeof(Bus2Vehicle))
	{
		VehicleData[BusVehicle[i]][vFuel] = 100;
		SetVehicleNumberPlate(BusVehicle[i], "BUS-SIDEJOB");
		Vehicle_SetType(BusVehicle[i], VEHICLE_TYPE_SIDEJOB);
	}
	BusVehicle[0] = Vehicle_Create(431,-2517.0537,-605.2971,132.6685,179.7611,1, 1, 0, false);
	BusVehicle[1] = Vehicle_Create(431,-2524.4326,-605.2515,132.6667,180.0471,1, 1, 0, false);
	BusVehicle[2] = Vehicle_Create(431,-2531.9109,-605.2745,132.6496,179.2747,1, 1, 0, false);
	forex(i, sizeof(BusVehicle))
	{
		VehicleData[BusVehicle[i]][vFuel] = 100;
		SetVehicleNumberPlate(BusVehicle[i], "BUS-SIDEJOB");
		Vehicle_SetType(BusVehicle[i], VEHICLE_TYPE_SIDEJOB);
	}
	CourierVehicle[0] = Vehicle_Create(413,-1950.9191,-1049.4563,32.2526,272.3899,6,6, 0, false);
	CourierVehicle[1] = Vehicle_Create(413,-1951.1714,-1045.5385,32.2551,275.0669,6,6, 0, false);
	CourierVehicle[2] = Vehicle_Create(413,-1951.3318,-1041.8508,32.2665,275.0267,6,6, 0, false);
	CourierVehicle[3] = Vehicle_Create(413,-1951.3264,-1038.1987,32.2469,271.8810,6,6, 0, false);
	CourierVehicle[4] = Vehicle_Create(413,-1951.2974,-1034.4664,32.2503,270.9728,6,6, 0, false);
	forex(i, sizeof(CourierVehicle))
	{
		VehicleData[CourierVehicle[i]][vFuel] = 100;
		SetVehicleNumberPlate(CourierVehicle[i], "COURIER-SIDEJOB");
		Vehicle_SetType(CourierVehicle[i], VEHICLE_TYPE_SIDEJOB);
	}
}

stock LoadActor()
{
	CreateActor(29, -774.2181,2425.2349,157.1011,226.0966); //sell drugs actor
	CreateDynamic3DTextLabel("Drop the {FFFF00}Rolled Weed {FFFFFF}here to sell", -1, -774.2181,2425.2349,157.1011, 5.0);
	CreateDynamicCP(-774.2181,2425.2349,157.1011, 1.3, -1, -1, -1, 3.0);

}

stock LoadPoint()
{
	CreateDynamic3DTextLabel(""YELLOW"/propose "WHITE"here.", -1, 2214.3958,-1332.6309,252.4141, 3.0);

	CreateDynamicPickup(1239, 23, 361.8309,173.6048,1008.3828, -1);
	CreateDynamic3DTextLabel(""LIGHTBLUE"[Tax Office]\n{FFFF00}/paytax\n"WHITE"Untuk membayar pajak.", -1, 361.8309,173.6048,1008.3828, 10.0);

	CreateDynamicPickup(1239, 23, -2095.2434,95.1803,35.3203, -1);
	CreateDynamic3DTextLabel(""LIGHTBLUE"[Sell Vehicle]\n{FFFF00}/selltostate\n"WHITE"Untuk menjual kendaraan ke state.", -1, -2095.2434,95.1803,35.3203, 10.0);

	CreateDynamicPickup(1239, 23, 1077.6029, -960.2651, 1338.3207, -1);
	CreateDynamic3DTextLabel(""LIGHTBLUE"[Job Center]\n{FFFFFF}/takejob", -1, 1077.6029, -960.2651, 1338.3207, 10.0);
	
	FactoryLabel = CreateDynamic3DTextLabel("Recycling Factory\n\n{FFFFFF}Current Trash Bags: {F39C12}0\n{FFFFFF}Bring trash here to earn money!", 0x2ECC71FF, -1864.8846, -1668.9028, 22.3015 + 0.5, 15.0, .testlos = 1);
	FactoryCP = CreateDynamicCP(-1864.8846, -1668.9028, 22.3015, 5.0); 

	CreateDynamicPickup(1581, 23, -2578.5625, -1383.2179, 1500.7570, -1);
	CreateDynamic3DTextLabel("{0000FF}[Departement of Motorvehicle]\n{FFFFFF}Gunakan {FFFF00}/drivingtest {FFFFFF}untuk memulai tes mengemudi\nPrice: {00FF00}$25.00", -1, -2578.5625, -1383.2179, 1500.7570, 10.0);

	CreateDynamicPickup(1239, 23, 1331.9070,1575.5684,3001.0859, -1);
	CreateDynamic3DTextLabel("{FFFF00}[Fishing Factory]\n{FFFFFF}/buybait", -1, 1331.9070,1575.5684,3001.0859, 10.0);

	CreateDynamicPickup(1239, 23, 1333.7576,1582.0439,3001.0859, -1);
	CreateDynamic3DTextLabel("{FFFF00}[Fishing Factory]\n{FFFFFF}/sellfish", -1, 1333.7576,1582.0439,3001.0859, 10.0);

	CreateDynamicPickup(1239, 23, -1993.0046,-2388.0107,30.6250, -1);
	CreateDynamic3DTextLabel("{FFFF00}[Timber Storage]\n{FFFFFF}Type {FFFF00}/selltimber {FFFFFF}to sell all Timber", -1, -1993.0046,-2388.0107,30.6250, 10.0);

	CreateDynamicPickup(1239, 23, -1436.1725,-1528.6896,3001.5059, -1);
	CreateDynamic3DTextLabel("{86C6F4}[Medical]\n{FFFFFF}/autotreatment\nPrice: {00FF00}$150.0", -1, -1436.1725,-1528.6896,3001.5059, 10.0);

	CreateDynamicPickup(1239, 23, -1862.1053,-145.7666,11.8984, -1);
	LabelData[labelComponent] = CreateDynamic3DTextLabel(sprintf(""LIGHTBLUE"[Component]\n"WHITE"Stock: "YELLOW"%d/10000\n"WHITE"Price: "GREEN"$0.50", StockData[stockComponent]), -1, -1862.1053,-145.7666,11.8984, 10.0);

	CreateDynamicPickup(1239, 23, -1304.1875,2491.8530,87.1437, -1);
	LabelData[labelRock] = CreateDynamic3DTextLabel(sprintf(""LIGHTBLUE"[Rock]\n"WHITE"Stock: "YELLOW"%d/500", StockData[stockRock]), -1, -1304.1875,2491.8530,87.1437, 10.0);


	CreateDynamicPickup(1239, 23, -1702.7526,33.5595,3.5547, -1);
	CreateDynamic3DTextLabel("{86C6F4}[Delivery Driver]\n{FFFF00}/startdeliver "WHITE"To start working.\n{FFFF00}/stopdeliver "WHITE"To stop working.", -1, -1702.7526,33.5595,3.5547, 10.0);

	CreateDynamicPickup(1239, 23, -1699.6128,6.0661,3.5547, -1);
	CreateDynamic3DTextLabel("{86C6F4}[Crate Loading]\n{FFFF00}/pickupcrate\n"WHITE"To pickup crate.", -1, -1699.6128,6.0661,3.5547, 10.0);

	CreateDynamicPickup(1239, 23, -2750.7354,203.6906,7.0267, -1);
	CreateDynamic3DTextLabel("{86C6F4}[Crate Unloading]\n{FFFF00}/unloadcrate\n"WHITE"To unloading crate.", -1, -2750.7354,203.6906,7.0267, 10.0);

	CreateDynamicPickup(1241, 23, -1437.7163,-1517.8572,3001.5059, -1);
	CreateDynamic3DTextLabel("[PHARMACY]\n/getpills here", -1, -1437.7163,-1517.8572,3001.5059, 10.0);

	CreateDynamicPickup(1239, 23, -192.3483, 1338.7361, 1500.9823, -1);
	CreateDynamic3DTextLabel("{86C6F4}[Advertisement]\n{FFFFFF}/ad", -1, -192.3483, 1338.7361, 1500.9823, 10.0);

	CreateDynamicPickup(1247, 23, 1360.5981,1575.5034,1468.7885, -1);
	CreateDynamic3DTextLabel("{0000FF}[Arrest Point]\n{FFFFFF}/arrest", COLOR_SERVER, 1360.5981,1575.5034,1468.7885, 4.0);

	CreateDynamic3DTextLabel("{FFFF00}Bank Point\n{FFFFFF}/help > Bank Commands", COLOR_WHITE,-2217.8130,287.6309,35.9590,3.0);
	CreateDynamicPickup(1274, 23, -2217.8130,287.6309,35.9590);

	CreateDynamic3DTextLabel("{FFFF00}Bank Point\n{FFFFFF}/help > Bank Commands", COLOR_WHITE,-2217.9900,296.9721,35.9590,3.0);
	CreateDynamicPickup(1274, 23, -2217.9900,296.9721,35.9590);

	CreateDynamic3DTextLabel("{FFFF00}Bank Point\n{FFFFFF}/help > Bank Commands", COLOR_WHITE,-2217.7244,278.7101,35.9590,3.0);
	CreateDynamicPickup(1274, 23, -2217.7244,278.7101,35.9590);

	CreateDynamicPickup(1239, 23, -1875.0437, 1419.0042, 7.1797, -1, -1);
	CreateDynamic3DTextLabel("Electronic Cargo\n{FFFFFF}Price: {009000}$15.0", COLOR_SERVER, -1875.0437, 1419.0042, 7.1797, 20.0);

	CreateDynamicPickup(1239, 23, -1835.1539, 1429.7806, 7.1841, -1, -1);
	CreateDynamic3DTextLabel("24/7 Cargo\n{FFFFFF}Price: {009000}$20.0", COLOR_SERVER, -1835.1539, 1429.7806, 7.1841, 20.0);

	CreateDynamicPickup(1239, 23, -1790.5422, 1429.7609, 7.1841, -1, -1);
	CreateDynamic3DTextLabel("Clothes Cargo\n{FFFFFF}Price: {009000}$15.0", COLOR_SERVER, -1790.5422, 1429.7609, 7.1841, 20.0);

	CreateDynamicPickup(1239, 23, -1886.6575,1444.1444,7.1842, -1, -1);
	CreateDynamic3DTextLabel("Equipment Cargo\n{FFFFFF}Price: {009000}$20.0", COLOR_SERVER, -1886.6575,1444.1444,7.1842, 20.0);

	CreateDynamicPickup(1239, 23, -1741.8209, 1429.7811, 7.1875, -1, -1);
	CreateDynamic3DTextLabel("Fast Food Cargo\n{FFFFFF}Price: {009000}$20.0", COLOR_SERVER, -1741.8209, 1429.7811, 7.1875, 20.0);

	CreateDynamicPickup(1239, 23, 2846.3269,2882.9648,320.1620, -1, -1);
	CreateDynamic3DTextLabel("Identification Card\n"YELLOW"/getidcard "WHITE"- untuk mendapatkan ID Card.\n"YELLOW"/extendidcard "WHITE"- untuk memperpanjang ID Card.", COLOR_SERVER, 2846.3269,2882.9648,320.1620, 20.0);

	CreateDynamicPickup(1239, 23, -1634.1038,653.5013,7.1875, -1, -1);
	CreateDynamic3DTextLabel("{0000FF}[Impound Point]\n{FFFFFF}/impound for impound vehicle.", -1, -1634.1038,653.5013,7.1875, 10.0);

	CreateDynamicPickup(1239, 23, 1380.9594,1557.6090,3001.0859, -1, -1);
	CreateDynamic3DTextLabel("{0000FF}[SAPD Desk]\n{FFFFFF}/buyplate - for buy plate\n/payticket - for pay ticket", -1, 1380.9594,1557.6090,3001.0859, 5.0);

	CreateDynamicPickup(1239, 23, 1378.8019,1557.6079,3001.0859, -1, -1);
	CreateDynamic3DTextLabel("{0000FF}[SAPD Desk]\n{FFFFFF}/unimpound - for release vehicle", -1, 1378.8019,1557.6079,3001.0859, 5.0);

	CreateDynamicPickup(1239, 23, -1939.4851,555.0747,35.1719, -1, -1);
	CreateDynamic3DTextLabel("{FFFF00}[Insurance Center]\n{FFFF00}/insu buy {FFFFFF}- to purchase insurance\n{FFFF00}/insu claim {FFFFFF}- to claim vehicle", -1, -1939.4851,555.0747,35.1719, 20.0);
}

stock UpdateServerStock(SERVER_STOCK) {
	switch(SERVER_STOCK) {
		case SERVER_STOCK_COMPONENT: UpdateDynamic3DTextLabelText(LabelData[labelComponent], -1, sprintf(""LIGHTBLUE"[Component]\n"WHITE"Stock: "YELLOW"%d/10000\n"WHITE"Price: "GREEN"$0.50", StockData[stockComponent]));
		case SERVER_STOCK_ROCK: UpdateDynamic3DTextLabelText(LabelData[labelRock], -1, sprintf(""LIGHTBLUE"[Rock]\n"WHITE"Stock: "YELLOW"%d/500", StockData[stockRock]));
	}
	return 1;
}
stock SaveServerData()
{
	new coordsString[128];
	format(coordsString, sizeof(coordsString), "%s,%s,%d,%d,%d,%d", MotdData[motdPlayer], MotdData[motdAdmin], GovData[govVault], GovData[govTax], StockData[stockComponent], StockData[stockRock]);
	new File: file2 = fopen("server.ini", io_write);
	fwrite(file2, coordsString);
	fclose(file2);
	return 1;	
}

stock LoadServerData()
{
	new arrCoords[20][64];
	new strFromFile2[256];
	new File: file = fopen("server.ini", io_read);
	if (file)
	{
		fread(file, strFromFile2);
		splits(strFromFile2, arrCoords, ',');
		strmid(MotdData[motdPlayer], arrCoords[0], 0, strlen(arrCoords[0]), 255);
		strmid(MotdData[motdAdmin], arrCoords[1], 0, strlen(arrCoords[1]), 255);
		GovData[govVault] = strval(arrCoords[2]);
		GovData[govTax] = strval(arrCoords[3]);
		StockData[stockComponent] = strval(arrCoords[4]);
		StockData[stockRock] = strval(arrCoords[5]);
		fclose(file);

		UpdateServerStock(SERVER_STOCK_COMPONENT);
		UpdateServerStock(SERVER_STOCK_ROCK);
	}
	return 1;
}
