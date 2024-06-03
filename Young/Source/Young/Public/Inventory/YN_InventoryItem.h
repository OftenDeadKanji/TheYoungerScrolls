// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "YN_InventoryItem.generated.h"

class UYN_InventoryComponent;
class UYN_InventoryItemConstData;

USTRUCT(BlueprintType)
struct FYN_InventoryItemData
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	TObjectPtr<UYN_InventoryItemConstData> ConstData;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	int Count;
};

UCLASS()
class YOUNG_API UYN_InventoryItem : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void Init();
	
	UFUNCTION(BlueprintCallable)
	virtual void AddToInventory(UYN_InventoryComponent* Inventory);

	const UYN_InventoryItemConstData* GetConstData() const;
	void SetConstData(UYN_InventoryItemConstData* NewConstData);

	int GetCount() const;
	void SetCount(int NewCount);

	void AddCount(int NewCount);
	void IncrementCount();
	void DecrementCount();

protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	FYN_InventoryItemData Data;
};
