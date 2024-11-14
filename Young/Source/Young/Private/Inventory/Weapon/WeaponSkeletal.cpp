// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "Inventory/Weapon/WeaponSkeletal.h"

#include "Inventory/Weapon/WeaponTypeData.h"

AWeaponSkeletal::AWeaponSkeletal(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass(TEXT("Mesh"), USkeletalMeshComponent::StaticClass()))
{
	SkeletalMesh = Cast<USkeletalMeshComponent>(Mesh);
}

void AWeaponSkeletal::Init(UWeaponInstanceData* Data)
{
	Super::Init(Data);

	if(WeaponTypeData.IsValid())
	{
		SkeletalMesh->SetSkeletalMesh(WeaponTypeData->GetSkeletalMesh());
	}
}
