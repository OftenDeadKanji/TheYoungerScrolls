// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.


#include "Inventory/YN_Weapon.h"
#include "Core/Characters/Components/YN_InventoryComponent.h"

void UYN_Weapon::AddToInventory(UYN_InventoryComponent* Inventory)
{
	Inventory->AddWeapon(this);
}
