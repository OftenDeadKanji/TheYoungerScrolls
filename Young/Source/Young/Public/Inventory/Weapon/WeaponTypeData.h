// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/InventoryItemTypeData.h"
#include "WeaponTypeData.generated.h"

UCLASS()
class YOUNG_API UWeaponTypeData : public UInventoryItemTypeData
{
	GENERATED_BODY()

public:
	float GetDamage() const;

	virtual UInventoryItem* CreateItem(UObject* Outer) override;
protected:
	UPROPERTY(EditAnywhere)
	float Damage;
};
