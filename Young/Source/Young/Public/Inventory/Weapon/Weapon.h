// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class UWeaponTypeData;
class UWeaponInstanceData;

UCLASS(Abstract, NotBlueprintable)
class YOUNG_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	AWeapon(const FObjectInitializer& ObjectInitializer);

	virtual void Init(UWeaponInstanceData* Data);

	UWeaponInstanceData* GetInstanceData() const;
	UWeaponTypeData* GetTypeData() const;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UMeshComponent> Mesh;

	UPROPERTY(VisibleInstanceOnly, Category = "Young")
	TWeakObjectPtr<UWeaponInstanceData> WeaponInstanceData;
	TWeakObjectPtr<UWeaponTypeData> WeaponTypeData;

};
