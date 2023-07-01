#include <YSI_Coding\y_hooks>

#define TP_WAIT_TIME 5000

new Float:TP_AwaitingPos[MAX_PLAYERS][3];

stock Float:TP_GetDistanceFromAwaiting(playerid)
{
	new Float:pX, Float:pY, Float:pZ;
	GetPlayerPos(playerid, pX, pY, pZ);
	return (floatsqroot(floatpower(pX - TP_AwaitingPos[playerid][0], 2.0) + floatpower(pY - TP_AwaitingPos[playerid][1], 2.0) + floatpower(pZ - TP_AwaitingPos[playerid][2], 2.0)));
}

hook OnPlayerConnect(playerid) {
    TP_AwaitingPos[playerid][0] = -1.0;
}

stock SetPlayerCompensatedPos(playerid, Float:X, Float:Y, Float:Z, wait_time = TP_WAIT_TIME, world = -1, interior = -1)
{
	if (!IsPlayerConnected(playerid)) return 0;
	
	TP_AwaitingPos[playerid][0] = X;
	TP_AwaitingPos[playerid][1] = Y;
	TP_AwaitingPos[playerid][2] = Z;
	
	Streamer_UpdateEx(playerid, X, Y, Z, world, interior, STREAMER_TYPE_OBJECT, wait_time, 1);
	if(interior != -1) SetPlayerInterior(playerid,interior);
	if(world != -1) SetPlayerVirtualWorld(playerid,world);
	return SetPlayerPos(playerid, X, Y, Z - 0.3);
}