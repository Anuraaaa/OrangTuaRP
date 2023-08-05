new const Crate_Name[][] = {
	"None",
	"Fast Food",
	"24/7",
	"Clothes",
	"Electronic",
	"Equipment",
	"Component",
	"Spareparts"
};

enum {
	CARGO_TYPE_NONE,
	CARGO_TYPE_FASTFOOD,
	CARGO_TYPE_247,
	CARGO_TYPE_CLOTHES,
	CARGO_TYPE_ELECTRO,
	CARGO_TYPE_EQUIPMENT,
	CARGO_TYPE_COMPONENT,
	CARGO_TYPE_SPAREPARTS
};

enum E_CRATE_DATA
{
	crateID,
	bool:crateExists,
	crateType,
	crateVehicle
};
new CrateData[MAX_CRATES][E_CRATE_DATA],
	Iterator:Crate<MAX_CRATES>;

Crate_Delete(id)
{

	new str[156];
	mysql_format(sqlcon, str, sizeof(str), "DELETE FROM `crates` WHERE `ID` = '%d'", CrateData[id][crateID]);
	mysql_tquery(sqlcon, str);

	CrateData[id][crateExists] = false;
	CrateData[id][crateVehicle] = -1;
	CrateData[id][crateID] = 0;

	Iter_Remove(Crate, id);
	return 1;
}

Crate_GetFreeID() {

	return Iter_Free(Crate);
}
Crate_Create(playerid, type)
{
	new id = INVALID_ITERATOR_SLOT;

	if((id = Iter_Alloc(Crate)) != INVALID_ITERATOR_SLOT) {
		CrateData[id][crateExists] = true;
		CrateData[id][crateType] = type;
		CrateData[id][crateVehicle] = -1;

		PlayerData[playerid][pCrate] = id;
		ApplyAnimation(playerid, "CARRY", "liftup", 4.1, 0, 0, 0, 0, 0, 1);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
		SetPlayerAttachedObject(playerid,  9, 1271, 5, 0.044377, 0.029049, 0.161334, 265.922912, 9.904896, 21.765972, 0.500000, 0.500000, 0.500000);			
		mysql_tquery(sqlcon, "INSERT INTO `crates` (`Type`) VALUES(0)", "OnCrateCreated", "d", id);
	}
	return id;
}

function OnCrateCreated(cid)
{
	CrateData[cid][crateID] = cache_insert_id();
	Crate_Save(cid);

	return 1;
}

Crate_Save(cid)
{

	if(!Iter_Contains(Crate, cid))
		return 0;


	new query[352];
	mysql_format(sqlcon, query, sizeof(query), "UPDATE `crates` SET ");
	mysql_format(sqlcon, query, sizeof(query), "%s`Type`='%d', ", query, CrateData[cid][crateType]);
	mysql_format(sqlcon, query, sizeof(query), "%s`Vehicle`='%d' ", query, CrateData[cid][crateVehicle]);
	mysql_format(sqlcon, query, sizeof(query), "%sWHERE `ID` = '%d'", query, CrateData[cid][crateID]);
	mysql_tquery(sqlcon, query);
	return 1;
}