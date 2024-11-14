// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/UserWidgetEx.h"
#include "ItemsGridWidget.generated.h"

class UTileView;
class UInventoryItemInstanceData;
class UGridPanel;
class UImageButtonWidget;


UCLASS()
class YOUNG_API UItemsGridWidget : public UUserWidgetEx
{
	GENERATED_BODY()

public:
	void Init(const TArray<UInventoryItemInstanceData*>& InItems);
	void Clear();

	UInventoryItemInstanceData* GetHoveredItem() const;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemHoverChange, UInventoryItemInstanceData*, Item, bool, bHovered);

	UPROPERTY(BlueprintAssignable)
	FOnItemHoverChange OnItemHoverChangeEvent;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemClicked, UInventoryItemInstanceData*, Item);
	UPROPERTY(BlueprintAssignable)
	FOnItemClicked OnItemClickedEvent;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnItemHoverChange(UObject* Item, bool bHovered);
	UFUNCTION()
	void OnItemClicked(UObject* Item);

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTileView> TileView;

	FIntVector2 GridSize;

	const TArray<UInventoryItemInstanceData*>* Items;
};
