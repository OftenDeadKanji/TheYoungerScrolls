// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItemData.h"
#include "InventoryItemTypeData.h"
#include "Common/Interactable.h"
#include "Engine/StaticMeshActor.h"
#include "InventoryItemPickup.generated.h"

class UInventoryItem;

UCLASS()
class YOUNG_API AInventoryItemPickup : public AStaticMeshActor, public IInteractable
{
	GENERATED_BODY()

public:
	AInventoryItemPickup();

#pragma region IInteractable 
	virtual void Authority_OnUsePressed_Implementation(AMainPlayerController* PlayerController) override;

	virtual bool IsInteractionByServerRequired_Implementation() const override;
#pragma endregion

protected:
	virtual void BeginPlay() override;

	UFUNCTION(CallInEditor, Category = "Item Config")
	virtual void TryToInitItem();
	virtual void InitItem(bool bDestroyOnFail);

	UPROPERTY(EditInstanceOnly, Category = "Item Config")
	FInventoryItemData ItemData;

	UPROPERTY()
	UInventoryItem* Item;
};
