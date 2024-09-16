// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "Core/General/Characters/Components/InventoryComponent.h"

#include "Inventory/Weapon/Weapon.h"
#include "Net/UnrealNetwork.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

const TArray<UInventoryItem*>& UInventoryComponent::GetAllItems() const
{
	return Items;
}

void UInventoryComponent::AddWeapon(UWeapon* Weapon)
{
	if(IsValid(Weapon) == false)
	{
		return;
	}

	if(GetNetMode() == NM_Client)
	{
		Server_AddWeapon(Weapon);
	}
	else
	{
		Authority_AddWeapon(Weapon);
	}
}

const TArray<UWeapon*>& UInventoryComponent::GetWeapons() const
{
	return Weapons;
}

const TArray<UInventoryItem*>& UInventoryComponent::GetWeaponsAsItems() const
{
	return ItemsWeapons;
}

void UInventoryComponent::Server_AddWeapon_Implementation(UWeapon* Weapon)
{
	Authority_AddWeapon(Weapon);
}

void UInventoryComponent::Authority_AddWeapon(UWeapon* Weapon)
{
	if(Weapon->GetItemTypeData()->IsStackable())
	{
		for(int i = 0; i < Weapons.Num(); i++)
		{
			if(Weapons[i]->GetItemTypeData() == Weapon->GetItemTypeData())
			{
				Weapons[i]->AddCount(Weapon->GetCount());

				return;
			}
		}
	}

	Weapons.Add(Weapon);
	ItemsWeapons.Add(Weapon);
	Items.Add(Weapon);
}

void UInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UInventoryComponent, Items, COND_OwnerOnly);

	DOREPLIFETIME_CONDITION(UInventoryComponent, Weapons, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UInventoryComponent, ItemsWeapons, COND_OwnerOnly);
}
