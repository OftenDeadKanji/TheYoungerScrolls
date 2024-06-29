// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.


#include "Core/Characters/Components/YN_InventoryComponent.h"

#include "../../../../../../../../../../../../Programy/Programowanie/UE/UE_5.3/Engine/Source/Runtime/Engine/Public/Net/UnrealNetwork.h"
#include "Inventory/YN_InventoryItem.h"
#include "Inventory/YN_Weapon.h"
#include "Inventory/YN_WeaponConstData.h"
#include "Utilities/DebugMacros.h"

UYN_InventoryComponent::UYN_InventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

const TArray<UYN_InventoryItem*>& UYN_InventoryComponent::GetItems() const
{
	return Items;
}

void UYN_InventoryComponent::AddWeapon(UYN_Weapon* Weapon)
{
	AActor* OwnerActor = GetOwner();
	if(IsValid(OwnerActor) && GetNetMode() == NM_Client)
	{
		Server_AddWeapon(Weapon);
	}
	else
	{
		Authority_AddWeapon(Weapon);
	}
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

void UYN_InventoryComponent::Server_AddWeapon_Implementation(UYN_Weapon* Weapon)
{
	Authority_AddWeapon(Weapon);
}

void UYN_InventoryComponent::Authority_AddWeapon(UYN_Weapon* Weapon)
{
	CheckOwnerHasAuthority();

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

void UYN_InventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UYN_InventoryComponent, Items, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UYN_InventoryComponent, ItemsWeapons, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UYN_InventoryComponent, Weapons, COND_OwnerOnly);
}

