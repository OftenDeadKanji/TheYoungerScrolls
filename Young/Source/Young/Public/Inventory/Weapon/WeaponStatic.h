// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/Weapon/Weapon.h"
#include "WeaponStatic.generated.h"

/**
 * 
 */
UCLASS()
class YOUNG_API AWeaponStatic : public AWeapon
{
	GENERATED_BODY()

public:
	AWeaponStatic(const FObjectInitializer& ObjectInitializer);

	virtual void Init(UWeaponInstanceData* Data) override;

protected:
	TWeakObjectPtr<UStaticMeshComponent> StaticMesh;
};
