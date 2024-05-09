// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "YN_GameStateGame.generated.h"

/**
 * 
 */
UCLASS()
class YOUNG_API AYN_GameStateGame : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UDataTable* GetInventoryItemsDataTable() const;
	UDataTable* GetWeaponsDataTable() const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data Tables")
	TObjectPtr<UDataTable> InventoryItemsDataTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data Tables")
	TObjectPtr<UDataTable> WeaponsDataTable;
};
