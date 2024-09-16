// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItemData.generated.h"

class UInventoryItemTypeData;

USTRUCT(BlueprintType)
struct YOUNG_API FInventoryItemData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInventoryItemTypeData* TypeData = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Count = 1;
};
