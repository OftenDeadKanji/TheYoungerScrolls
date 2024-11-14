// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItemTypeData.h"
#include "InventoryItemInstanceData.generated.h"

class UInventoryComponent;

UCLASS(EditInlineNew, DefaultToInstanced)
class YOUNG_API UInventoryItemInstanceData : public UObject
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual bool IsSupportedForNetworking() const override;

	UFUNCTION(BlueprintCallable)
	virtual void AddSelfToInventory(UInventoryComponent* Inventory);

	const UInventoryItemTypeData* GetItemTypeData() const;
	UInventoryItemTypeData* GetItemTypeData();
	void SetItemTypeData(UInventoryItemTypeData* InData);

	int32 GetCount() const;
	void SetCount(int32 InCount);

	UFUNCTION(BlueprintCallable)
	void AddCount(int32 InCount);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated)
	UInventoryItemTypeData* Data;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated)
	int32 Count;
};
