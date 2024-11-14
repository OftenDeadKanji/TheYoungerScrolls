// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "Inventory/Weapon/WeaponStatic.h"

#include "Inventory/Weapon/WeaponInstanceData.h"
#include "Inventory/Weapon/WeaponTypeData.h"

AWeaponStatic::AWeaponStatic(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer.SetDefaultSubobjectClass(TEXT("Mesh"), UStaticMeshComponent::StaticClass()))
{
	StaticMesh = Cast<UStaticMeshComponent>(Mesh);
}

void AWeaponStatic::Init(UWeaponInstanceData* Data)
{
	Super::Init(Data);

	if(WeaponTypeData.IsValid())
	{
		StaticMesh->SetStaticMesh(WeaponTypeData->GetStaticMesh());
	}
}
