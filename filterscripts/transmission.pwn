/*MANUAL TRANSMISSION CAR SYSTEM
[2] - CLUTCH
[Y] - INCREASE GEAR
[N] - DECREASE GEAR
[R] [N] [1] [2] [3] [4] [5] - GEARS AVAILABLE
 
HOW TO USE:
1: TYPE /MANUAL TO ENTER MANUAL MODE
2: UPON ENTERING A CAR, YOU SHOULD BE ON NEUTRAL MODE.
3: HOLD ONTO 2 + TAP Y TO GO INTO FIRST GEAR.
4: HOLD ONTO 2 + W AND THE CAR WILL START MOVING.
5: AFTER A SECOND, RELEASE 2 AND CONTINUE TO USE W.
6: TO INCREASE GEAR, RELEASE W, HOLD ONTO 2 + TAP Y THEN RELEASE 2.
7: TO DECREASE GEAR, RELEASE W, HOLD ONTO 2 + TAP N THEN RELEASE 2.
 
MECHANICS:
1: IF YOU ACCELERATE IN NEUTRAL, CAR WILL STALL. (this wouldn't really happen, but it's just a way to prevent movment of the car)
2: IF YOU DO NOT HOLD CLUTCH WHILST UNDER 3MPH, CAR WILL STALL.
3: IF YOU ACCELERATE IN A GEAR WHICH IS TOO HIGH, CAR WILL STALL.
4: USING THE CLUTCH AND ACCELERATOR AT THE SAME TIME WILL DECREASE THE CAR'S HEALTH. (except when you are initally moving away in first gear)
5: IF YOU DON'T CHANGE GEARS WHEN NECESSARY, CAR HEALTH WILL DECREASE.
6: STALLING DECREASES THE CAR'S HEALTH.
 
KNOWN BUGS:
1: Holding onto the clutch + accelerator whilst falling in mid-air within a vehicle will reduce the speed in which you fall. Although, the vehicle will lose significant health.
 
Created by LEOTorres (Tester101)*/
 
#include <a_samp>
 
#define HOLDING(%0) \
    ((newkeys & (%0)) == (%0))
    
#define ACC KEY_SPRINT
#define REV KEY_JUMP
 
//↓↓ FOLLOWING VALUES CAN BE ADJUSTED TO CHANGE THE SYSTEM TO YOUR SUITING ↓↓//
#define CLUTCH KEY_LOOK_BEHIND
#define GUP KEY_YES
#define GDOWN KEY_NO
 
#define GEAR_1_MAX_SPEED 20
#define GEAR_2_MAX_SPEED 50
#define GEAR_2_MIN_SPEED 10
#define GEAR_3_MAX_SPEED 80
#define GEAR_3_MIN_SPEED 30
#define GEAR_4_MAX_SPEED 120
#define GEAR_4_MIN_SPEED 50
#define GEAR_5_MIN_SPEED 70
 
#define HEAVY_SPEED_REDUCTION 1.5
#define LIGHT_SPEED_REDUCTION 1.1
#define STALL_PUNISHMENT 10
#define GEAR_PUNISHMENT 1
//^^ FOLLOWING VALUES CAN BE ADJUSTED TO CHANGE THE SYSTEM TO YOUR SUITING ^^//
 
new gear[MAX_PLAYERS];
new clutch[MAX_PLAYERS];
new acc[MAX_PLAYERS];
new rev[MAX_PLAYERS];
new stallstate[MAX_PLAYERS];
new transmission[MAX_PLAYERS];
new Text:geartext[MAX_PLAYERS];

new Float:VEHICLE_TOP_SPEEDS[] =
{
    157.0, 147.0, 186.0, 110.0, 133.0, 164.0, 110.0, 148.0, 100.0, 158.0, 129.0, 221.0, 168.0, 110.0, 105.0, 192.0, 154.0, 270.0, 115.0, 149.0,
    145.0, 154.0, 140.0, 99.0,  135.0, 270.0, 173.0, 165.0, 157.0, 201.0, 190.0, 130.0, 94.0,  110.0, 167.0, 0.0,   149.0, 158.0, 142.0, 168.0,
    136.0, 145.0, 139.0, 126.0, 110.0, 164.0, 270.0, 270.0, 111.0, 0.0,   0.0,   193.0, 270.0, 60.0,  135.0, 157.0, 106.0, 95.0,  157.0, 136.0,
    270.0, 160.0, 111.0, 142.0, 145.0, 145.0, 147.0, 140.0, 144.0, 270.0, 157.0, 110.0, 190.0, 190.0, 149.0, 173.0, 270.0, 186.0, 117.0, 140.0,
    184.0, 73.0,  156.0, 122.0, 190.0, 99.0,  64.0,  270.0, 270.0, 139.0, 157.0, 149.0, 140.0, 270.0, 214.0, 176.0, 162.0, 270.0, 108.0, 123.0,
    140.0, 145.0, 216.0, 216.0, 173.0, 140.0, 179.0, 166.0, 108.0, 79.0,  101.0, 270.0, 270.0, 270.0, 120.0, 142.0, 157.0, 157.0, 164.0, 270.0,
    270.0, 160.0, 176.0, 151.0, 130.0, 160.0, 158.0, 149.0, 176.0, 149.0, 60.0,  70.0,  110.0, 167.0, 168.0, 158.0, 173.0, 0.0,   0.0,   270.0,
    149.0, 203.0, 164.0, 151.0, 150.0, 147.0, 149.0, 142.0, 270.0, 153.0, 145.0, 157.0, 121.0, 270.0, 144.0, 158.0, 113.0, 113.0, 156.0, 178.0,
    169.0, 154.0, 178.0, 270.0, 145.0, 165.0, 160.0, 173.0, 146.0, 0.0,   0.0,   93.0,  60.0,  110.0, 60.0,  158.0, 158.0, 270.0, 130.0, 158.0,
    153.0, 151.0, 136.0, 85.0,  0.0,   153.0, 142.0, 165.0, 108.0, 162.0, 0.0,   0.0,   270.0, 270.0, 130.0, 190.0, 175.0, 175.0, 175.0, 158.0,
    151.0, 110.0, 169.0, 171.0, 148.0, 152.0, 0.0,   0.0,   0.0,   108.0, 0.0,   0.0
};

forward EnableEngine(playerid);
forward StallEngine(playerid);
forward ReduceSpeed (playerid, status);
forward OnPlayerSpeeding(playerid);
 
public OnFilterScriptInit()
{
    print("\n--------------------------------------");
    print(" Manual Transmission - LEOTorres (Tester101)");
    print("--------------------------------------\n");
    
    for (new x = 0; x < MAX_PLAYERS; x++)
    {
        geartext[x] = TextDrawCreate(500.0, 100.0, "");
        TextDrawColor(geartext[x], 0x0000BBAA);
        TextDrawFont(geartext[x], 3);
        TextDrawSetShadow(geartext[x], 0);
    }
    return 1;
}
 
public OnFilterScriptExit()
{
    for (new x = 0; x < MAX_PLAYERS; x++)
    {
        TextDrawDestroy (geartext[x]);
    }
    return 1;
}

stock Float:GetVehicleSpeed(vehicleid) //credits to whoever made this.
{
    new
        Float:x,
        Float:y,
        Float:z,
        Float:speed;
        
    GetVehicleVelocity(vehicleid, x, y, z);
    speed = VectorSize(x, y, z);
    
    return floatround(speed * 195.12); 
}
 

public EnableEngine (playerid)
{
    new vehicleid = GetPlayerVehicleID(playerid);
    new engine, lights, alarm, doors, bonnet, boot, objective;
    GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
    
    if (engine == 0)
    {
        SetVehicleParamsEx(vehicleid, 1, lights, alarm, doors, bonnet, boot, objective);
        stallstate[playerid] = 0;
    }
}
 
public StallEngine (playerid)
{
    if (stallstate[playerid] == 0)
    {
        stallstate[playerid] = 1;
        new vehicleid = GetPlayerVehicleID(playerid);
        new engine, lights, alarm, doors, bonnet, boot, objective;
        new Float:health;
        GetVehicleHealth (vehicleid, health);
        GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
        SetVehicleParamsEx(vehicleid, 0, lights, alarm, doors, bonnet, boot, objective);
        if (gear[playerid] != 0)
        {
            SetVehicleHealth (vehicleid, health - STALL_PUNISHMENT);
        }
    }
}
 

Float:GetVehicleModelTopSpeed(modelid) 
    return VEHICLE_TOP_SPEEDS[modelid - 400];

public ReduceSpeed (playerid, status)
{
    new vehicleid = GetPlayerVehicleID(playerid);
    new Float:Velocity[3];
    new Float:health;
    GetVehicleHealth (vehicleid, health);
    GetVehicleVelocity(vehicleid, Velocity[0], Velocity[1], Velocity[2]);
 
    if (status == 0)
    {
        SetVehicleHealth(vehicleid, health - GEAR_PUNISHMENT);
        SetVehicleVelocity(GetPlayerVehicleID(playerid), Velocity[0] / LIGHT_SPEED_REDUCTION, Velocity[1] / LIGHT_SPEED_REDUCTION, Velocity[2] / LIGHT_SPEED_REDUCTION);
    }
    
    if (status == 1)
    {
        SetVehicleHealth(vehicleid, health - GEAR_PUNISHMENT); 
        SetVehicleVelocity(GetPlayerVehicleID(playerid), Velocity[0] / HEAVY_SPEED_REDUCTION, Velocity[1] / HEAVY_SPEED_REDUCTION, Velocity[2] / HEAVY_SPEED_REDUCTION);
    }
    
    if (status == 2)
    {
        SetVehicleVelocity(GetPlayerVehicleID(playerid), Velocity[0] / HEAVY_SPEED_REDUCTION, Velocity[1] / HEAVY_SPEED_REDUCTION, Velocity[2] / HEAVY_SPEED_REDUCTION);
    }
}
 
public OnPlayerDisconnect(playerid)
{
    gear[playerid] = 0;
    clutch[playerid] = 0;
    acc[playerid] = 0;
    rev[playerid] = 0;
    stallstate[playerid] = 0;
    transmission[playerid] = 0;
    
    return 1;
}
 
public OnPlayerStateChange(playerid, newstate, oldstate)
{
    if (transmission[playerid] == 0)    {   return 1;   }
    if(oldstate == PLAYER_STATE_ONFOOT && newstate == PLAYER_STATE_DRIVER)
    {
        TextDrawShowForPlayer(playerid, geartext[playerid]);
        gear[playerid] = 0;
        EnableEngine (playerid);
        stallstate[playerid] = 0;
    }
    return 1;
}
 
public OnPlayerExitVehicle(playerid, vehicleid)
{
    TextDrawHideForPlayer(playerid, geartext[playerid]);
    stallstate[playerid] = 0;
    return 1;
}
 
public OnPlayerKeyStateChange (playerid, newkeys, oldkeys)
{
    if (newkeys & ACC && gear[playerid] == 0 || clutch[playerid] == 1 && acc[playerid] == 1)    {   EnableEngine (playerid);    }
    if (transmission[playerid] == 0)    {   return 1;   }
    if (HOLDING(ACC))   {   acc[playerid] = 1;  }
    else    {   acc[playerid] = 0;  }
    if (HOLDING(REV))   {   rev[playerid] = 1;  }
    else    {   rev[playerid] = 0;  }
    if (HOLDING(CLUTCH))    {   clutch[playerid] = 1;   }
    else    {   clutch[playerid] = 0;   }
    if (HOLDING( CLUTCH | GUP ) && gear[playerid] < 5)  {   gear[playerid]++;   }
    if (HOLDING( CLUTCH | GDOWN ) && gear[playerid] > -1)   {   gear[playerid]--;   }
    return 1;
}

public OnPlayerConnect(playerid) {
    transmission[playerid] = 1;
    return 1;
}
public OnPlayerUpdate (playerid)
{
    if (transmission[playerid] == 0)    {   return 1;   }
    if (IsPlayerInAnyVehicle(playerid) == 0)    {   return 1;   }
    new vehicleid = GetPlayerVehicleID(playerid);
    new model = GetVehicleModel(vehicleid);
    TextDrawSetString(geartext[playerid], "");
    TextDrawShowForPlayer(playerid, geartext[playerid]);
    if (model == 417 || model == 425 || model == 447 || model == 460 || model == 469 || model == 476 || model == 487 || model == 488 || model == 460 || model == 497 || model == 511 || model == 512 || model == 513 || model == 519 || model == 520 || model == 548 || model == 553 || model == 563 || model == 577 || model == 592 || model == 593)   {   return 1;   }
    
    //HANDLES THE TEXTDRAW//
    new gearstring[256];
    format (gearstring, sizeof (gearstring), "", gear[playerid]);
    if (gear[playerid] == 0)    {   format (gearstring, sizeof (gearstring), "~r~R ~g~N ~r~1 2 3 4 5");     }
    if (gear[playerid] == -1)   {   format (gearstring, sizeof (gearstring), "~g~R ~r~N 1 2 3 4 5");        }
    if (gear[playerid] == 1)    {   format (gearstring, sizeof (gearstring), "~r~R N ~g~1 ~r~2 3 4 5");     }
    if (gear[playerid] == 2)    {   format (gearstring, sizeof (gearstring), "~r~R N 1 ~g~2 ~r~3 4 5");     }
    if (gear[playerid] == 3)    {   format (gearstring, sizeof (gearstring), "~r~R N 1 2 ~g~3~r~ 4 5");     }
    if (gear[playerid] == 4)    {   format (gearstring, sizeof (gearstring), "~r~R N 1 2 3 ~g~4~r~ 5");     }
    if (gear[playerid] == 5)    {   format (gearstring, sizeof (gearstring), "~r~R N 1 2 3 4 ~g~5");        }
    TextDrawSetString(geartext[playerid], gearstring);
    TextDrawShowForPlayer(playerid, geartext[playerid]);
    
    //HANDLES VEHICLE MECHANICS//
    
    new Float:speed = GetVehicleSpeed(vehicleid);
    
    new Float:gear_1 = floatdiv(GetVehicleModelTopSpeed(model), 5),
        Float:gear_2 = floatdiv(GetVehicleModelTopSpeed(model), 4)
        Float:gear_3 = floatdiv(GetVehicleModelTopSpeed(model), 3)
        Float:gear_4 = floatdiv(GetVehicleModelTopSpeed(model), 2)
        Float:gear_5 = GetVehicleModelTopSpeed(model);

    if (gear[playerid] > 0)
    {
        if (speed < 3)
        {
            if (clutch[playerid] == 0)
            {
                StallEngine(playerid);
            }
        }
 
        else
        {
            if (acc[playerid] == 1 && clutch[playerid] == 1)
            {
                ReduceSpeed (playerid, 0);
            }
        }
 
        if (speed > 0 && speed < 10)
        {
            if (rev[playerid] == 1)
            {
                StallEngine(playerid);
            }
        }
    }
 
    if (gear[playerid] > 1 && (speed < 10))
    {
        if (clutch[playerid] == 1)
        {
            ReduceSpeed (playerid, 2);
        }
 
        else
        {
            StallEngine(playerid);
        }
    }
 
    switch (gear[playerid])
    {
        case -1:
        {
            if (acc[playerid] == 1)
            {
                StallEngine(playerid);
            }
        }
        
        case 0:
        {
            if ((speed > 0) && acc[playerid] == 1 || rev[playerid] == 1)
            {       
                StallEngine(playerid);      
            }
            
            return 1;
        }
        
        case 1:
        {
            if (speed > gear_1)
            {   
                ReduceSpeed (playerid, 1);
            }
        }
        
        case 2:
        {
            if (speed > gear_2)
            {
                ReduceSpeed (playerid, 0);
            }
            
            if (clutch[playerid] == 1 || acc[playerid] == 0)
            {
                return 1;
            }
            
            if (speed < float(gear_2 - 20.0))
            {
                StallEngine(playerid);
            }
        }
        
        case 3:
        {
            if (speed > GEAR_3_MAX_SPEED)
            {
                ReduceSpeed (playerid, 0);
            }
            
            if (clutch[playerid] == 1 || acc[playerid] == 0)
            {
                return 1;
            }
            
            if (speed < GEAR_3_MIN_SPEED)
            {
                StallEngine(playerid);
            }
        }
        
        case 4:
        {
            if (speed > GEAR_4_MAX_SPEED)
            {
                ReduceSpeed (playerid, 0);
            }
            
            if (clutch[playerid] == 1 || acc[playerid] == 0)
            {
                return 1;
            }
            
            if (speed < GEAR_4_MIN_SPEED)
            {
                StallEngine(playerid);
            }
        }
        
        case 5:
        {
            if (clutch[playerid] == 1 || acc[playerid] == 0)
            {
                return 1;
            }
            
            if (speed < GEAR_5_MIN_SPEED)
            {
                StallEngine(playerid);
            }
        }
    }
    return 1;
}