// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Common/Interaction/YN_Interactable.h"
#include "Inventory/YN_InventoryItem.h"
#include "YN_InventoryItemPickup.generated.h"

class UYN_InventoryItem;
class UYN_InventoryItemConstData;

UCLASS()
class YOUNG_API AYN_InventoryItemPickup : public AStaticMeshActor, public IYN_Interactable
{
	GENERATED_BODY()
	
public:
	void OnUsePressed_Implementation(AYN_PlayerController* PlayerController) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(CallInEditor, Category = "Item Config")
	virtual void TryToInitItem();

	virtual void InitItem(bool bDestroyOnFail);

	UPROPERTY(EditInstanceOnly, Category = "Item Config")
	FYN_InventoryItemData ItemData;

	UPROPERTY()
	TObjectPtr<UYN_InventoryItem> Item;
};
