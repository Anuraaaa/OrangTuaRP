#include <YSI_Coding\y_hooks>

#define KEY_VEHICLE_FORWARD 0b001000
#define KEY_VEHICLE_BACKWARD 0b100000

new VMUpgrades[MAX_VEHICLES];

hook OnGameModeInit() {
    SetTimer("SpeedUpTimer", 300, true);
}
SetVehicleMaxSpeed(vehicleid,prct){
    if(prct < 0)prct = 0;
    VMUpgrades[vehicleid]=prct;
}


CMD:vms(playerid, params[]){
    
    if(GetPlayerVehicleSeat(playerid) != 0)
        return SendClientMessage(playerid ,-1,"You have to be in a drivers seat");

    new prct;
    if(sscanf(params,"i",prct))
        return SendClientMessage(playerid,-1,"Usage : /vehiclemaxspeed [percentage]");
    if(prct < 0)
        return SendClientMessage(playerid,-1,"Speed upgrade percentage cannot be less than 0");

	SetVehicleMaxSpeed(GetPlayerVehicleID(playerid),prct);

    new msg[144];
    format(msg,sizeof(msg),"Vehicle max speed successfully set to +%i percent | Topspeed: %.2f",prct, Vehicle_TopSpeed(GetPlayerVehicleID(playerid)));
	SendClientMessage(playerid,-1,msg);
	return 1;
}

function SpeedUpTimer() {

    foreach(new playerid : Player) {
        new vehicleid,Float:speed,Float:vX,Float:vY,Float:vZ,Float:maxSpeed,Float:newMaxSpeed,keys;

        vehicleid = GetPlayerVehicleID(playerid);

        maxSpeed = Vehicle_TopSpeed(vehicleid); // get the max speed of vehicle 

        if(maxSpeed > 0) {
            GetPlayerKeys(playerid, keys, _:vX, _:vX);
            if ((keys & (KEY_VEHICLE_FORWARD | KEY_VEHICLE_BACKWARD | KEY_HANDBRAKE)) == KEY_VEHICLE_FORWARD) 
            { // modify the speed only if player is pressing the forward key without the brake or handbrake.
                GetVehicleVelocity(vehicleid, vX, vY, vZ);
                speed = floatmul( floatsqroot( floatadd( floatadd( floatpower( vX, 2 ), floatpower( vY, 2 ) ),  floatpower( vZ, 2 ) ) ), 180.0 ); // get the current vehicle speed

                newMaxSpeed = maxSpeed+maxSpeed/100*VMUpgrades[vehicleid]; // calculate the new max speed based on percentage added

                if(speed > maxSpeed-1 && speed < newMaxSpeed+1) // if the vehicle speed is more than the maxspeed (-1, for less precision) and less than the new max speed
                    SetVehicleVelocity(vehicleid, vX*1.03, vY*1.03, vZ*1.03); // add velocity to the vehicle overriding the max speed - it will keep accelerating even tho it reached its max speed.
            }
        }
    }
    return 1;
}
