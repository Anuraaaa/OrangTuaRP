	#include <a_samp>
	#include <streamer>

	new Area;
	new Float:Array[] =
{
	-1429.82, -1524.52,
	-1433.42, -1451.37,
	-1467.88, -1453.18,
	-1466.70, -1472.83,
	-1470.86, -1494.25,
	-1472.03, -1511.06,
	-1471.12, -1525.99,
	-1467.40, -1526.38
};

	public OnFilterScriptInit()
	{
	Area = CreateDynamicPolygon(Array);
}

		public OnPlayerEnterDynamicArea(playerid, areaid)
	{
	if(areaid == Area)	
	{	
		SendClientMessage(playerid, -1, "Welcome to farmer Area");	
	}
	}

		public OnPlayerLeaveDynamicArea(playerid, areaid)
	{
	if(areaid == Area)	
	{	
		SendClientMessage(playerid, -1, "Goodbye from farmer Area");	
	}
	}
	
// Total Array Point: 8											  
// Output File: Polygon_Editor - farmer.pwn											  
// Exported Date: 18/8/2023 ~ 21:47:1											  
// Polygon Editor by Abyss (GvC.VN)											  
// Version 1.0