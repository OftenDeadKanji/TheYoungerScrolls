// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InventoryItemTypeData.generated.h"

class UInventoryItemInstanceData;

UCLASS(BlueprintType)
class YOUNG_API UInventoryItemTypeData : public UDataAsset
{
	GENERATED_BODY()

public:
	const FText& GetShortName() const;
	const FText& GetDescription() const;
	UStaticMesh* GetPickUpMesh() const;
	UTexture2D* GetIcon() const;
	bool IsStackable() const;

	virtual UInventoryItemInstanceData* CreateItem(UObject* Outer = nullptr);
protected:
	UPROPERTY(EditAnywhere)
	FText ShortName;

	UPROPERTY(EditAnywhere)
	FText Description;

	UPROPERTY(EditAnywhere)
	UStaticMesh* PickUpMesh;

	UPROPERTY(EditAnywhere)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere)
	bool bStackable;
};
