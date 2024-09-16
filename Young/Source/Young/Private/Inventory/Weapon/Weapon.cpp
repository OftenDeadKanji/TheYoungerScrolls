// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "Inventory/Weapon/Weapon.h"

#include "Core/General/Characters/Components/InventoryComponent.h"

void UWeapon::AddSelfToInventory(UInventoryComponent* Inventory)
{
	Super::AddSelfToInventory(Inventory);

	Inventory->AddWeapon(this);
}
