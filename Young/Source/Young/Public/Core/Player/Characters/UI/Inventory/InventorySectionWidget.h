// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/UserWidgetEx.h"
#include "InventorySectionWidget.generated.h"

class UTileView;
class UItemInfoWidget;
class UItemsGridWidget;
class UInventoryItem;

UCLASS()
class YOUNG_API UInventorySectionWidget : public UUserWidgetEx
{
	GENERATED_BODY()

public:
	void Init(const TArray<UInventoryItem*>& Items);
	void Clear();

protected:
	UFUNCTION()
	void OnNewItemHovered(UInventoryItem* Item);

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UItemsGridWidget> ItemsGrid;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UItemInfoWidget> ItemInfo;
};
