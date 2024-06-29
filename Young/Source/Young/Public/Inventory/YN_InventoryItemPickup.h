// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Common/Interaction/YN_Interactable.h"
#include "Inventory/YN_InventoryItem.h"
#include "YN_InventoryItemPickup.generated.h"

class UYN_InteractionAreaComponent;
class UYN_InventoryItem;
class UYN_InventoryItemConstData;

UCLASS()
class YOUNG_API AYN_InventoryItemPickup : public AStaticMeshActor, public IYN_Interactable
{
	GENERATED_BODY()

public:
	AYN_InventoryItemPickup();

	virtual void Authority_OnUsePressed_Implementation(AYN_PlayerController* PlayerController) override;
	virtual bool RequiresInteractionByServer_Implementation() const;
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
