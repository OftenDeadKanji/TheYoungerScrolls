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
class YOUNG_API AYN_InventoryItemPickup : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AYN_InventoryItemPickup();

protected:
	virtual void BeginPlay() override;

	void Interact(AYN_PlayerController* InteractingPlayerController);

	UFUNCTION(CallInEditor, Category = "Item Config")
	virtual void TryToInitItem();

	virtual void InitItem(bool bDestroyOnFail);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UYN_InteractionAreaComponent> InteractionArea;

	UPROPERTY(EditInstanceOnly, Category = "Item Config")
	FYN_InventoryItemData ItemData;

	UPROPERTY()
	TObjectPtr<UYN_InventoryItem> Item;
};
