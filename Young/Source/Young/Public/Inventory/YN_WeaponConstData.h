// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/YN_InventoryItemConstData.h"
#include "YN_WeaponConstData.generated.h"

UCLASS(BlueprintType)
class UYN_WeaponConstData : public UYN_InventoryItemConstData
{
	GENERATED_BODY()

public:
	float GetDamage() const;

	const FName& GetMaterial() const;

	virtual UYN_InventoryItem* CreateItem(UObject* Outer = nullptr) override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Material;
};
