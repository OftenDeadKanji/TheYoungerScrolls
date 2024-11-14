// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "Core/Characters/Components/InventoryComponent.h"

#include "Inventory/Weapon/WeaponInstanceData.h"
#include "Net/UnrealNetwork.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);

	bReplicateUsingRegisteredSubObjectList = true;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetNetMode() != NM_Client)
	{
		InitArrays();
	}
}

void UInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UInventoryComponent, Items, COND_OwnerOnly);

	DOREPLIFETIME_CONDITION(UInventoryComponent, Weapons, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UInventoryComponent, ItemsWeapons, COND_OwnerOnly);
}

const TArray<UInventoryItemInstanceData*>& UInventoryComponent::GetAllItems() const
{
	return Items;
}

void UInventoryComponent::AddWeapon(UWeaponInstanceData* Weapon)
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

const TArray<UWeaponInstanceData*>& UInventoryComponent::GetWeapons() const
{
	return Weapons;
}

const TArray<UInventoryItemInstanceData*>& UInventoryComponent::GetWeaponsAsItems() const
{
	return ItemsWeapons;
}

void UInventoryComponent::InitArrays()
{
	int32 WeaponsCount = Weapons.Num();
	ItemsWeapons.Empty(WeaponsCount);

	int32 ItemsCount = WeaponsCount;
	Items.Empty(ItemsCount);

	for (UWeaponInstanceData* Weapon : Weapons)
	{
		ItemsWeapons.Add(Weapon);
		Items.Add(Weapon);
	}
}

void UInventoryComponent::Server_AddWeapon_Implementation(UWeaponInstanceData* Weapon)
{
	Authority_AddWeapon(Weapon);
}

void UInventoryComponent::Authority_AddWeapon(UWeaponInstanceData* Weapon)
{
	AddReplicatedSubObject(Weapon);

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
