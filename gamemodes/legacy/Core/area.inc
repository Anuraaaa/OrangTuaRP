enum e_gangzone
{
	gzSafezone,
};

new GangZoneData[e_gangzone];

enum e_area
{
	STREAMER_TAG_AREA:areaMechanic,
	STREAMER_TAG_AREA:areaPershing,
	STREAMER_TAG_AREA:areaNews,
	STREAMER_TAG_AREA:areaHospital,
	STREAMER_TAG_AREA:areaBank,
	STREAMER_TAG_AREA:areaDrug,
	STREAMER_TAG_AREA:areaMechanicBoat
};
new AreaData[e_area];

new Float:arr_MechBoat[] =
{
	-2848.56, 1269.23,
	-2849.30, 1311.78,
	-2887.70, 1311.27,
	-2883.62, 1252.90,
	-2867.62, 1252.90
};

new Float:arr_Mechanic[] =
{
	-1819.54, -102.70,
	-1818.44, -40.28,
	-1864.24, -40.24,
	-1867.21, -100.52
};

new Float:arr_Drug[] = {

	-2065.64, 2752.23,
	-2064.95, 2665.88,
	-2137.67, 2643.38,
	-2143.91, 2715.07
};

stock IsPlayerInArea(playerid, Float:max_x, Float:min_x, Float:max_y, Float:min_y)
{
	new Float:X, Float:Y, Float:Z;
	GetPlayerPos(playerid, X, Y, Z);
	if(X <= max_x && X >= min_x && Y <= max_y && Y >= min_y) return true;
	return false;
}

stock LoadGangZone()
{
	GangZoneData[gzSafezone] = GangZoneCreate(-3000, -3000, 3000, 3000);

}

stock LoadArea()
{
	AreaData[areaDrug] = CreateDynamicPolygon(arr_Drug);

	AreaData[areaPershing] = CreateDynamicRectangle(-1725, 636.5, -1547, 740.5);
	AreaData[areaHospital] = CreateDynamicRectangle(-2754, 558.5, -2520, 712.5);
	AreaData[areaBank] = CreateDynamicRectangle(-2861, 282.5, -2600, 472.5);
	AreaData[areaNews] = CreateDynamicRectangle(-2711, -74.5, -2597, 44.5);

	AreaData[areaMechanic] = CreateDynamicPolygon(arr_Mechanic);
	AreaData[areaMechanicBoat] = CreateDynamicPolygon(arr_MechBoat);
}

stock IsSafeZone(STREAMER_TAG_AREA:areaid)
{
	if(areaid == AreaData[areaPershing] || areaid == AreaData[areaHospital] || areaid == AreaData[areaBank] || areaid == AreaData[areaNews])
		return 1;

	return 0;
}