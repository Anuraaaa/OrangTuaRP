// Default Move Speed
#define MOVE_SPEED              100.0
#define ACCEL_RATE              0.03
#define ACCEL_MODE              true

// Players Mode
#define CAMERA_MODE_NONE    	0
#define CAMERA_MODE_FLY     	1

// Key state definitions
#define MOVE_FORWARD    		1
#define MOVE_BACK       		2
#define MOVE_LEFT       		3
#define MOVE_RIGHT      		4
#define MOVE_FORWARD_LEFT       5
#define MOVE_FORWARD_RIGHT      6
#define MOVE_BACK_LEFT          7
#define MOVE_BACK_RIGHT         8

enum noclipenum
{
	cameramode,
	flyobject,
	flmode,
	lrold,
	udold,
	lastmove,
	Float:accelmul,
    
    Float:accelrate,
    Float:maxspeed,
    bool:accel
}
new noclipdata[MAX_PLAYERS][noclipenum];

new bool:FlyMode[MAX_PLAYERS];

#define InFlyMode(%0) FlyMode[%0]

CMD:flymode(playerid, params[])
{
    if(PlayerData[playerid][pAdmin] < 4)
        return SendErrorMessage(playerid, "You don't have permission to use this command!");

	if(FlyMode[playerid]) CancelFlyMode(playerid);
	else StartFlyMode(playerid);
	return 1;
}

ResetFlyModeData(playerid) {
	noclipdata[playerid][cameramode] 	= CAMERA_MODE_NONE;
	noclipdata[playerid][lrold]	   	 	= 0;
	noclipdata[playerid][udold]   		= 0;
	noclipdata[playerid][flmode]   		= 0;
	noclipdata[playerid][lastmove]   	= 0;
	noclipdata[playerid][accelmul]   	= 0.0;
	noclipdata[playerid][accel]   	    = ACCEL_MODE;
	noclipdata[playerid][accelrate]   	= ACCEL_RATE;
	noclipdata[playerid][maxspeed]   	= MOVE_SPEED;
	FlyMode[playerid] = false;
}
GetMoveDirectionFromKeys(ud, lr)
{
	new direction = 0;
	
    if(lr < 0)
	{
		if(ud < 0) 		direction = MOVE_FORWARD_LEFT; 	// Up & Left key pressed
		else if(ud > 0) direction = MOVE_BACK_LEFT; 	// Back & Left key pressed
		else            direction = MOVE_LEFT;          // Left key pressed
	}
	else if(lr > 0) 	// Right pressed
	{
		if(ud < 0)      direction = MOVE_FORWARD_RIGHT;  // Up & Right key pressed
		else if(ud > 0) direction = MOVE_BACK_RIGHT;     // Back & Right key pressed
		else			direction = MOVE_RIGHT;          // Right key pressed
	}
	else if(ud < 0) 	direction = MOVE_FORWARD; 	// Up key pressed
	else if(ud > 0) 	direction = MOVE_BACK;		// Down key pressed
	
	return direction;
}

MoveCamera(playerid)
{
	new Float:FV[3], Float:CP[3];
	//GetPlayerCameraPos(playerid, CP[0], CP[1], CP[2]);          // 	Cameras position in space
	GetDynamicObjectPos(noclipdata[playerid][flyobject], CP[0], CP[1], CP[2]);          // 	Cameras position in space
    GetPlayerCameraFrontVector(playerid, FV[0], FV[1], FV[2]);  //  Where the camera is looking at

	// Increases the acceleration multiplier the longer the key is held
	if(noclipdata[playerid][accelmul] <= 1.0) noclipdata[playerid][accelmul] += noclipdata[playerid][accelrate];

	// Determine the speed to move the camera based on the acceleration multiplier
	new Float:speed = noclipdata[playerid][maxspeed] * (noclipdata[playerid][accel] ? noclipdata[playerid][accelmul] : 1.0);

	// Calculate the cameras next position based on their current position and the direction their camera is facing
	new Float:X, Float:Y, Float:Z;
	GetNextCameraPosition(noclipdata[playerid][flmode], CP, FV, X, Y, Z);
	MoveDynamicObject(noclipdata[playerid][flyobject], X, Y, Z, speed, 0.0, 0.0, 0.0);

    //SendClientMessage(playerid, -1, sprintf("(%0.1f, %0.1f, %0.1f) - (%0.1f, %0.1f, %0.1f) - (%0.1f, %0.1f, %0.1f)", CP[0], CP[1], CP[2], FV[0], FV[1], FV[2], X, Y, Z));
    
	// Store the last time the camera was moved as now
	noclipdata[playerid][lastmove] = GetTickCount();
	return 1;
}

SetFlyModePos(playerid, Float:x, Float:y, Float:z)
{
	if(FlyMode[playerid])
	{
		SetDynamicObjectPos(noclipdata[playerid][flyobject], x, y, z);
		noclipdata[playerid][lastmove] = GetTickCount();
		return 1;
	}
	return 0;
}

GetFlyModePos(playerid, &Float:x, &Float:y, &Float:z)
{
	if(FlyMode[playerid])
	{
		GetDynamicObjectPos(noclipdata[playerid][flyobject], x, y, z);
		return 1;
	}
	return 0;
}

GetNextCameraPosition(move_mode, Float:CP[3], Float:FV[3], &Float:X, &Float:Y, &Float:Z)
{
    // Calculate the cameras next position based on their current position and the direction their camera is facing
    #define OFFSET_X (FV[0]*6000.0)
	#define OFFSET_Y (FV[1]*6000.0)
	#define OFFSET_Z (FV[2]*6000.0)
	switch(move_mode)
	{
		case MOVE_FORWARD:
		{
			X = CP[0]+OFFSET_X;
			Y = CP[1]+OFFSET_Y;
			Z = CP[2]+OFFSET_Z;
		}
		case MOVE_BACK:
		{
			X = CP[0]-OFFSET_X;
			Y = CP[1]-OFFSET_Y;
			Z = CP[2]-OFFSET_Z;
		}
		case MOVE_LEFT:
		{
			X = CP[0]-OFFSET_Y;
			Y = CP[1]+OFFSET_X;
			Z = CP[2];
		}
		case MOVE_RIGHT:
		{
			X = CP[0]+OFFSET_Y;
			Y = CP[1]-OFFSET_X;
			Z = CP[2];
		}
		case MOVE_BACK_LEFT:
		{
			X = CP[0]+(-OFFSET_X - OFFSET_Y);
 			Y = CP[1]+(-OFFSET_Y + OFFSET_X);
		 	Z = CP[2]-OFFSET_Z;
		}
		case MOVE_BACK_RIGHT:
		{
			X = CP[0]+(-OFFSET_X + OFFSET_Y);
 			Y = CP[1]+(-OFFSET_Y - OFFSET_X);
		 	Z = CP[2]-OFFSET_Z;
		}
		case MOVE_FORWARD_LEFT:
		{
			X = CP[0]+(OFFSET_X  - OFFSET_Y);
			Y = CP[1]+(OFFSET_Y  + OFFSET_X);
			Z = CP[2]+OFFSET_Z;
		}
		case MOVE_FORWARD_RIGHT:
		{
			X = CP[0]+(OFFSET_X  + OFFSET_Y);
			Y = CP[1]+(OFFSET_Y  - OFFSET_X);
			Z = CP[2]+OFFSET_Z;
		}
	}
}

forward DelaySetPos(playerid, Float:x, Float:y, Float:z);
public DelaySetPos(playerid, Float:x, Float:y, Float:z) { SetPlayerPos(playerid, x, y, z); }

FUNC::CancelFlyMode(playerid)
{
	new Float:x, Float:y, Float:z;
	GetPlayerCameraPos(playerid, x, y, z);

	SetTimerEx("DelaySetPos", 2000, false, "ifff", playerid, x, y, z);

	FlyMode[playerid] = false;
	TogglePlayerSpectating(playerid, false);

	DestroyDynamicObject(noclipdata[playerid][flyobject]);
	noclipdata[playerid][cameramode] = CAMERA_MODE_NONE;

    SendAdminAction(playerid, "You are "RED"disabled "WHITE"admin fly mode");
	return 1;
}

FUNC::StartFlyMode(playerid)
{
	// Create an invisible object for the players camera to be attached to
	new Float:X, Float:Y, Float:Z;
	GetPlayerPos(playerid, X, Y, Z);
	noclipdata[playerid][flyobject] = CreateDynamicObject(19300, X, Y, Z, 0.0, 0.0, 0.0, .playerid = playerid, .streamdistance = 300.0, .drawdistance = 300.0);

	// Place the player in spectating mode so objects will be streamed based on camera location
	TogglePlayerSpectating(playerid, true);
	// Attach the players camera to the created object
	AttachCameraToDynamicObject(playerid, noclipdata[playerid][flyobject]);

	FlyMode[playerid] = true;
	noclipdata[playerid][cameramode] = CAMERA_MODE_FLY;
    SendAdminAction(playerid, "You are "GREEN"enabled "WHITE"admin fly mode");
	return 1;
}