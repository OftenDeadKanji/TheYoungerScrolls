// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "YN_InventoryItemConfigData.generated.h"

UCLASS()
class YOUNG_API UYN_InventoryItemConfigData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	const FText& GetName() const;
	const FText& GetDescription() const;
	UStaticMesh* GetMesh() const;
	UTexture2D* GetIcon() const;
	bool IsStackable() const;
	float GetMass() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMesh* Mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bStackable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MassInKg;
};
