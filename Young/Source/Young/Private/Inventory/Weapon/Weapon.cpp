// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "Inventory/Weapon/Weapon.h"

#include "Inventory/Weapon/WeaponInstanceData.h"
#include "Inventory/Weapon/WeaponTypeData.h"

AWeapon::AWeapon(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Mesh = CreateDefaultSubobject<UMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	if (IsValid(Mesh))
	{
		Mesh->SetCollisionProfileName(TEXT("Weapon"));
	}
}

void AWeapon::Init(UWeaponInstanceData* Data)
{
	WeaponInstanceData = Data;

	if(WeaponInstanceData.IsValid())
	{
		WeaponTypeData = Cast<UWeaponTypeData>(WeaponInstanceData->GetItemTypeData());
	}

}
