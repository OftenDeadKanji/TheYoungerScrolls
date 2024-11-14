// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/UserWidgetEx.h"
#include "InventorySectionWidget.generated.h"

class UTileView;
class UItemInfoWidget;
class UItemsGridWidget;
class UInventoryItemInstanceData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemClicked, UInventoryItemInstanceData*, Item);

UCLASS()
class YOUNG_API UInventorySectionWidget : public UUserWidgetEx
{
	GENERATED_BODY()

public:
	void Init(const TArray<UInventoryItemInstanceData*>& Items);
	void Clear();

	FOnItemClicked OnItemClickedEvent;

protected:
	UFUNCTION()
	void OnItemHoverChange(UInventoryItemInstanceData* Item, bool bHovered);

	UFUNCTION()
	void OnItemClicked(UInventoryItemInstanceData* Item);

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UItemsGridWidget> ItemsGrid;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UItemInfoWidget> ItemInfo;
};
