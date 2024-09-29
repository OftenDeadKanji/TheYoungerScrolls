// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/UserWidgetEx.h"
#include "ItemsGridWidget.generated.h"

class UTileView;
class UInventoryItem;
class UGridPanel;
class UImageButtonWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemHovered, UInventoryItem*, Item);

UCLASS()
class YOUNG_API UItemsGridWidget : public UUserWidgetEx
{
	GENERATED_BODY()

public:
	void Init(const TArray<UInventoryItem*>& InItems);
	void Clear();

	UInventoryItem* GetHoveredItem() const;

	FOnItemHovered OnItemHovered;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnNewItemHovered();

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTileView> TileView;

	FIntVector2 GridSize;

	const TArray<UInventoryItem*>* Items;
};
