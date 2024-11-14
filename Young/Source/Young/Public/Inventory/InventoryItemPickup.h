// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItemTypeData.h"
#include "Common/Interactable.h"
#include "Engine/StaticMeshActor.h"
#include "InventoryItemPickup.generated.h"

class UInventoryItemInstanceData;

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
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite)
	UInventoryItemInstanceData* Item;

private:

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
