// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "Inventory/Weapon/WeaponTypeData.h"

#include "Inventory/Weapon/Weapon.h"

float UWeaponTypeData::GetDamage() const
{
	return Damage;
}

UInventoryItem* UWeaponTypeData::CreateItem(UObject* Outer)
{
	UWeapon* NewItem = NewObject<UWeapon>(Outer);
	NewItem->SetItemTypeData(this);

	return NewItem;
}
