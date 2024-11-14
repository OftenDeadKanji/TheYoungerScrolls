// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/InventoryItemInstanceData.h"
#include "Inventory/UsableItem.h"
#include "WeaponInstanceData.generated.h"

UCLASS()
class YOUNG_API UWeaponInstanceData : public UInventoryItemInstanceData, public IUsableItem
{
	GENERATED_BODY()

public:
#pragma region UInventoryItemInstanceData overrides
	virtual void AddSelfToInventory(UInventoryComponent* Inventory) override;
#pragma endregion

#pragma region IUsableItem
	virtual void Use_Implementation(APlayerController* Player) override;
#pragma endregion
};
