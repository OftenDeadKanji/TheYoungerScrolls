// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.


#include "Core/Characters/Components/YN_InventoryComponent.h"
#include "Inventory/YN_InventoryItem.h"
#include "Inventory/YN_Weapon.h"
#include "Inventory/YN_WeaponConstData.h"

UYN_InventoryComponent::UYN_InventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

const TArray<UYN_InventoryItem*>& UYN_InventoryComponent::GetItems() const
{
	return Items;
}

void UYN_InventoryComponent::AddWeapon(UYN_Weapon* Weapon)
{
	if (Weapon->GetConstData()->IsStackable())
	{
		if (UYN_Weapon** ItemPtr = Weapons.FindByPredicate(
			[&] (const UYN_Weapon* WeaponInInventory)
			{
				return WeaponInInventory->GetConstData() == Weapon->GetConstData();
			}))
		{
			(*ItemPtr)->AddCount(Weapon->GetCount());
			return;
		}
	}

	Weapons.Add(Weapon);
	ItemsWeapons.Add(Weapon);
	Items.Add(Weapon);
}

const TArray<UYN_Weapon*>& UYN_InventoryComponent::GetWeapons() const
{
	return Weapons;
}

const TArray<UYN_InventoryItem*>& UYN_InventoryComponent::GetWeaponsAsItems() const
{
	return ItemsWeapons;
}

void UYN_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

