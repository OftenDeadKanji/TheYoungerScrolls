// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.


#include "Inventory/YN_WeaponConstData.h"
#include "Inventory/YN_InventoryItem.h"
#include "Inventory/YN_Weapon.h"

float UYN_WeaponConstData::GetDamage() const
{
    return Damage;
}

const FName& UYN_WeaponConstData::GetMaterial() const
{
    return Material;
}

UYN_InventoryItem* UYN_WeaponConstData::CreateItem(UObject* Outer)
{
    UObject* ItemOuter = Outer ? Outer : GetTransientPackage();

    UYN_InventoryItem* Item = NewObject<UYN_Weapon>(ItemOuter);

    return Item;
}
