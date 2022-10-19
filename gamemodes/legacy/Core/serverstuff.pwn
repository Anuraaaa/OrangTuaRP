LoadStaticVehicle()
{
	TrashVehicle[0] = Vehicle_Create(408, -1916.6907, -1702.9725, 22.3032, 184.3942, 26, 26, 0, false);
    TrashVehicle[1] = Vehicle_Create(408, -1912.3484, -1702.5702, 22.2899, 183.3604, 26, 26, 0, false);
    TrashVehicle[2] = Vehicle_Create(408, -1908.4242, -1702.2488, 22.3004, 184.5224, 26, 26, 0, false);
	forex(i, sizeof(TrashVehicle))
	{
		VehicleData[TrashVehicle[i]][vFuel] = 100;
		SetVehicleNumberPlate(TrashVehicle[i], "TRASHMASTER-SF");
		Vehicle_SetType(TrashVehicle[i], VEHICLE_TYPE_SIDEJOB);
	}
	MowerVehicle[0] = Vehicle_Create(572,-2288.9854,174.6294,34.8807,90.9118,1, 1, 0, false);
	MowerVehicle[1] = Vehicle_Create(572,-2289.0369,172.4341,34.8758,90.5593,1, 1, 0, false);
	MowerVehicle[2] = Vehicle_Create(572,-2289.1563,170.1806,34.8839,90.9597,1, 1, 0, false);
	MowerVehicle[3] = Vehicle_Create(572,-2288.9021,167.7834,34.8719,92.3754,1, 1, 0, false);
	forex(i, sizeof(MowerVehicle))
	{
		VehicleData[MowerVehicle[i]][vFuel] = 100;
		SetVehicleNumberPlate(MowerVehicle[i], "MOWER-SF");
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
		SetVehicleNumberPlate(RumpoVehicle[i], "RUMPO-SF");
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
		SetVehicleNumberPlate(ForkliftVehicle[i], "FORKLIFT-SF");
		Vehicle_SetType(ForkliftVehicle[i], VEHICLE_TYPE_SIDEJOB);
	}
	SweeperVehicle[0] = Vehicle_Create(574,-2093.7937,-83.2754,34.8914,178.7325,1, 1, 0, false);
	SweeperVehicle[1] = Vehicle_Create(574,-2089.5867,-83.4144,34.8925,177.5521,1, 1, 0, false);
	SweeperVehicle[2] = Vehicle_Create(574,-2085.6165,-83.4752,34.8632,183.9264,1, 1, 0, false);
	forex(i, sizeof(SweeperVehicle))
	{
		VehicleData[SweeperVehicle[i]][vFuel] = 100;
		SetVehicleNumberPlate(SweeperVehicle[i], "SWEEPER-SF");
		Vehicle_SetType(SweeperVehicle[i], VEHICLE_TYPE_SIDEJOB);
	}
	Bus2Vehicle[0] = Vehicle_Create(437,-2511.6821,1205.4083,37.5022,270.0276,1, 1, 0, false);
	Bus2Vehicle[1] = Vehicle_Create(437,-2511.6414,1209.5726,37.5030,270.8899,1, 1, 0, false);
	forex(i, sizeof(Bus2Vehicle))
	{
		VehicleData[BusVehicle[i]][vFuel] = 100;
		SetVehicleNumberPlate(BusVehicle[i], "BUS-SF");
		Vehicle_SetType(BusVehicle[i], VEHICLE_TYPE_SIDEJOB);
	}
	BusVehicle[0] = Vehicle_Create(431,-2517.0537,-605.2971,132.6685,179.7611,1, 1, 0, false);
	BusVehicle[1] = Vehicle_Create(431,-2524.4326,-605.2515,132.6667,180.0471,1, 1, 0, false);
	BusVehicle[2] = Vehicle_Create(431,-2531.9109,-605.2745,132.6496,179.2747,1, 1, 0, false);
	forex(i, sizeof(BusVehicle))
	{
		VehicleData[BusVehicle[i]][vFuel] = 100;
		SetVehicleNumberPlate(BusVehicle[i], "BUS-SF");
		Vehicle_SetType(BusVehicle[i], VEHICLE_TYPE_SIDEJOB);
	}
	/*
	PizzaVehicle[0] = Vehicle_Create(586, -2315.0833,-121.8533,34.9109,180.8729, 2, 2, 0, false);
	PizzaVehicle[1] = Vehicle_Create(586, -2318.7058,-121.8589,34.9109,182.1402, 2, 2, 0, false);
	PizzaVehicle[2] = Vehicle_Create(586, -2322.5537,-121.8266,34.9109,182.1128, 2, 2, 0, false);
	PizzaVehicle[3] = Vehicle_Create(586, -2326.3721,-121.8904,34.9109,179.1078, 2, 2, 0, false);
	forex(i, sizeof(PizzaVehicle))
	{
		VehicleData[PizzaVehicle[i]][vFuel] = 100;
		SetVehicleNumberPlate(PizzaVehicle[i], "PIZZA-SF");
		Vehicle_SetType(PizzaVehicle[i], VEHICLE_TYPE_SIDEJOB);
	}


	SanNewsVehicles[1] = Vehicle_Create(582, -1874.3662,445.2826,35.2278,0.6498,6,6, 0, false, "SFN");
	SanNewsVehicles[2] = Vehicle_Create(582, -1877.7924,445.4186,35.2242,0.1064,6,6, 0, false, "SFN");
	SanNewsVehicles[3] = Vehicle_Create(582, -1881.1426,445.3790,35.2322,357.8842,6,6, 0, false, "SFN");
	SanNewsVehicles[4] = Vehicle_Create(582, -1884.7002,445.4959,35.2281,359.2859,6,6, 0, false, "SFN");
	SanNewsVehicles[5] = Vehicle_Create(560, -1862.3236,459.4580,34.8784,90.2969,6,6, 0, false, "SFN");
	SanNewsVehicles[6] = Vehicle_Create(560, -1862.3727,455.8022,34.8776,90.6098,6,6, 0, false, "SFN");
	SanNewsVehicles[7] = Vehicle_Create(579, -1862.8317,451.6100,35.1041,89.2307,6,6, 0, false, "SFN");
	SanNewsVehicles[8] = Vehicle_Create(579, -1862.8342,447.6895,35.1031,91.6275,6,6, 0, false, "SFN");
	SanNewsVehicles[9] = Vehicle_Create(579, -1862.5958,443.4810,35.1052,93.7536,6,6, 0, false, "SFN");
	SanNewsVehicles[10] = Vehicle_Create(487,-1878.3439,489.2160,116.1457,76.3573,6,6, 0, false, "SFN"); 
	forex(i, sizeof(SanNewsVehicles))
	{
		VehicleData[SanNewsVehicles[i]][vFuel] = 100;
		Vehicle_SetType(SanNewsVehicles[i], VEHICLE_TYPE_FACTION);
		VehicleData[SanNewsVehicles[i]][vFactionType] = FACTION_NEWS;
	}
	LSMDVehicles[0] = Vehicle_Create(416, -2589.0063,652.8833,14.6312,269.2020,1,3, 0, false, "SFFD");	
	LSMDVehicles[1] = Vehicle_Create(416, -2589.0393,658.1194,14.6312,270.4256,1,3, 0, false, "SFFD");
	LSMDVehicles[2] = Vehicle_Create(490,-2589.3364,622.3182,14.5097,269.6186, 3, 3, 0, false, "SFFD");
	LSMDVehicles[3] = Vehicle_Create(490,-2589.4587,627.3685,14.5086,272.2860, 3, 3, 0, false, "SFFD");
	LSMDVehicles[4] = Vehicle_Create(405,-2545.8884,658.0899,14.3341,89.7227, 3, 3, 1, false, "SFFD");
	LSMDVehicles[5] = Vehicle_Create(442,-2545.9666,652.7462,14.2926,91.8644,3,3, 1, false, "SFFD");
	LSMDVehicles[6] = Vehicle_Create(579,-2546.3721,647.6375,14.6169,88.8405, 3, 3, 1, false, "SFFD");
	LSMDVehicles[7] = Vehicle_Create(407,-2589.7126,647.5717,14.6850,270.7710, 3, 3, 0, false, "SFFD");
	LSMDVehicles[8] = Vehicle_Create(426,-2546.3059,637.7538,14.1966,89.4086, 3, 3, 1, false, "SFFD");
	LSMDVehicles[9] = Vehicle_Create(445,-2546.2749,632.6559,14.3281,90.8614, 3, 3, 1, false, "SFFD");
	forex(i, sizeof(LSMDVehicles))
	{
		VehicleData[LSMDVehicles[i]][vFuel] = 100;
		Vehicle_SetType(LSMDVehicles[i], VEHICLE_TYPE_FACTION);
		VehicleData[LSMDVehicles[i]][vFactionType] = FACTION_MEDIC;
	}
	LSPDVehicles[0] = Vehicle_Create(597,-2413.5515,540.0397,29.6938,268.1397,0,1, 0, false, "SFPD"); // Cruiser HC
	LSPDVehicles[1] = Vehicle_Create(597,-2413.9492,535.8163,29.6766,259.4626,0,1, 0, false, "SFPD"); // Cruiser Command Team
	LSPDVehicles[2] = Vehicle_Create(597,-2414.9912,532.0808,29.6989,247.6113,0,1, 0, false, "SFPD"); // Cruiser Supervisor 1
	LSPDVehicles[3] = Vehicle_Create(523,-2415.6252,529.1201,29.4887,240.3476,0,1, 0, false, "SFPD"); // Cruiser Supervisor 2
	LSPDVehicles[4] = Vehicle_Create(523,-2416.7202,527.0045,29.4949,234.5331,0,1, 0, false, "SFPD"); // Cruiser
	LSPDVehicles[5] = Vehicle_Create(560,-2419.1665,524.9501,29.6368,230.4010,0,0, 0, false, "SFPD"); // Cruiser
	LSPDVehicles[6] = Vehicle_Create(451,-2422.2637,521.6082,29.6372,226.3248,3,1, 0, false, "SFPD"); // Cruiser
	LSPDVehicles[7] = Vehicle_Create(541,-2425.5168,518.0164,29.5548,224.7571,0,1, 0, false, "SFPD"); // Cruiser
	
	LSPDVehicles[8] = Vehicle_Create(597,-1579.8534,749.6013,-5.5198,179.0906, 0, 1, 0, false, "SFPD"); // Cruiser HC
	LSPDVehicles[9] = Vehicle_Create(597,-1572.6299,742.6924,-5.5190,89.0323,0,1, 0, false, "SFPD"); // Cruiser Command Team
	LSPDVehicles[10] = Vehicle_Create(597,-1572.6825,738.6356,-5.5200,89.8512,0,1, 0, false, "SFPD"); // Cruiser Supervisor 1
	LSPDVehicles[11] = Vehicle_Create(597,-1572.7855,734.6165,-5.5196,89.0528,0,1, 0, false, "SFPD"); // Cruiser Supervisor 2
	LSPDVehicles[12] = Vehicle_Create(597,-1572.8948,730.6498,-5.5209,90.5495,0,1, 0, false, "SFPD"); // Cruiser
	LSPDVehicles[13] = Vehicle_Create(597,-1572.7695,726.5457,-5.5194,89.1891,0,1, 0, false, "SFPD"); // Cruiser

	LSPDVehicles[14] = Vehicle_Create(560,-1600.2104,693.9465,-5.5369,180.0330, 0, 0, 1, false, "SFPD"); // Sultan
	LSPDVehicles[15] = Vehicle_Create(560,-1604.2634,693.7793,-5.5372,179.4394, 0, 0, 1, false, "SFPD"); // Sultan
	LSPDVehicles[16] = Vehicle_Create(560,-1608.3971,693.9834,-5.5374,178.8489, 0, 0, 1, false, "SFPD"); // Sultan

	LSPDVehicles[17] = Vehicle_Create(599,-1572.6381,718.2594,-5.1686,89.9223,0,1, 0, false, "SFPD"); // Ranger
	LSPDVehicles[18] = Vehicle_Create(599,-1572.8369,722.3583,-5.1688,90.6290,0,1, 0, false, "SFPD"); // Ranger

	LSPDVehicles[19] = Vehicle_Create(601,-1623.0701,659.8624,-5.4834,88.2852,1,1, 0, false, "SFPD"); // S.W.AT

	LSPDVehicles[20] = Vehicle_Create(427,-1623.1246,653.8961,-4.9952,90.5156,0,1, 1, false, "SFPD"); // Enforcer
	LSPDVehicles[21] = Vehicle_Create(427,-1623.0157,649.8275,-4.9950,89.5976,0,1, 1, false, "SFPD"); // Enforcer

	LSPDVehicles[22] = Vehicle_Create(490,-1639.6564,649.7194,-5.1943,269.8666,0,0, 1, false, "SFPD"); // FBI
	LSPDVehicles[23] = Vehicle_Create(490,-1639.5039,653.6905,-5.1924,268.9561,0,0, 1, false, "SFPD"); // FBI

	LSPDVehicles[24] = Vehicle_Create(411,-1632.8408,693.9875,-5.5151,180.1917,0, 0, 1, false, "SFPD"); // Infernus
	LSPDVehicles[25] = Vehicle_Create(541,-1628.6444,694.0319,-5.6172,178.7400,0,0, 1, false, "SFPD"); // Bullet
	LSPDVehicles[26] = Vehicle_Create(451,-1624.6858,693.7829,-5.5355,180.6099,0,0, 1, false, "SFPD"); // Turismo

	LSPDVehicles[27] = Vehicle_Create(523,-1572.8210,714.5817,-5.6778,89.2428, 0, 0, 1, false, "SFPD"); // HPV
	LSPDVehicles[28] = Vehicle_Create(523,-1573.1056,713.1453,-5.6703,85.7029, 0, 0, 1, false, "SFPD"); // HPV

	LSPDVehicles[29] = Vehicle_Create(468,-1572.9041,711.2983,-5.5733,86.0483, 0, 0, 1, false, "SFPD"); // Sanchez
	LSPDVehicles[30] = Vehicle_Create(468,-1572.9517,709.9579,-5.5733,91.9232, 0, 0, 1, false, "SFPD"); // Sanchez

	LSPDVehicles[31] = Vehicle_Create(426,-1596.0389,676.1673,-5.4989,0.1873,0,0, 1, false, "SFPD"); // Premier
	LSPDVehicles[32] = Vehicle_Create(426,-1600.2365,676.0677,-5.4990,359.2720,0,0, 1, false, "SFPD"); // Premier

	LSPDVehicles[33] = Vehicle_Create(525,-1588.0919,749.5121,-5.3604,179.5525,1,1, 1, false, "SFPD"); // Tow truck
	LSPDVehicles[34] = Vehicle_Create(525,-1592.2413,749.8562,-5.3570,178.3324,0,1, 1, false, "SFPD"); // Tow truck

	LSPDVehicles[35] = Vehicle_Create(472,-1474.1566,696.8568,-0.0161,272.2573,0,1, 1, false, "SFPD"); // Coastguard
	LSPDVehicles[36] = Vehicle_Create(472,-1472.9733,689.9062,0.1532,271.8740,0,1, 1, false, "SFPD"); // Coastguard

	LSPDVehicles[37] = Vehicle_Create(497,-1681.3596,706.0087,30.7765,90.3618,0,1, 1, false, "SFPD"); // Police Maverick
	forex(i, sizeof(LSPDVehicles))
	{
		VehicleData[LSPDVehicles[i]][vFuel] = 100;
		Vehicle_SetType(LSPDVehicles[i], VEHICLE_TYPE_FACTION);
		VehicleData[LSPDVehicles[i]][vFactionType] = FACTION_POLICE;
		SetVehicleHealth(LSPDVehicles[i], 2000.0);
	} */
}

stock LoadActor()
{
	CreateActor(29, -774.2181,2425.2349,157.1011,226.0966); //sell drugs actor
	CreateDynamic3DTextLabel("Drop the {FFFF00}Rolled Weed {FFFFFF}here to sell", -1, -774.2181,2425.2349,157.1011, 5.0);
	CreateDynamicCP(-774.2181,2425.2349,157.1011, 1.3, -1, -1, -1, 3.0);

}

stock LoadPoint()
{
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
	CreateDynamic3DTextLabel("{FFFF00}[Timber Storage]\n{FFFFFF}Type {FFFF00}/selltimber {FFFFFF}to sell all Timber\nPrice: {00FF00}$50.00{FFFFFF} per Timber", -1, -1993.0046,-2388.0107,30.6250, 10.0);

	CreateDynamicPickup(1239, 23, -1772.3304, -2013.1531, 1500.7853, -1);
	CreateDynamic3DTextLabel("{86C6F4}[Medical]\n{FFFFFF}/autotreatment\nPrice: {00FF00}$150.0", -1, -1772.3304, -2013.1531, 1500.7853, 10.0);

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

	CreateDynamicPickup(1239, 23, 1384.4253,1532.2789,1510.9011, -1, -1);
	CreateDynamic3DTextLabel("{0000FF}[SAPD Desk]\n{FFFFFF}/buyplate - for buy plate\n/payticket - for pay ticket", -1, 1384.4253,1532.2789,1510.9011, 5.0);

	CreateDynamicPickup(1239, 23, 1382.0933,1532.1388,1510.9011, -1, -1);
	CreateDynamic3DTextLabel("{0000FF}[SAPD Desk]\n{FFFFFF}/unimpound - for release vehicle", -1, 1382.0933,1532.1388,1510.9011, 5.0);

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
