// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/YN_InventoryItem.h"
#include "YN_Weapon.generated.h"


UCLASS()
class YOUNG_API UYN_Weapon : public UYN_InventoryItem
{
	GENERATED_BODY()
	
public:
	virtual void AddToInventory(UYN_InventoryComponent* Inventory) override;

};
