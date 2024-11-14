// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/Weapon/Weapon.h"
#include "WeaponSkeletal.generated.h"

/**
 * 
 */
UCLASS()
class YOUNG_API AWeaponSkeletal : public AWeapon
{
	GENERATED_BODY()

public:
	AWeaponSkeletal(const FObjectInitializer& ObjectInitializer);

	virtual void Init(UWeaponInstanceData* Data) override;

protected:
	TWeakObjectPtr<USkeletalMeshComponent> SkeletalMesh;
};
