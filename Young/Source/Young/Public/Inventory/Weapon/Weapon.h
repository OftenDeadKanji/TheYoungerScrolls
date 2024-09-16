// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/InventoryItem.h"
#include "Weapon.generated.h"

UCLASS()
class YOUNG_API UWeapon : public UInventoryItem
{
	GENERATED_BODY()

public:
	virtual void AddSelfToInventory(UInventoryComponent* Inventory) override;

};
