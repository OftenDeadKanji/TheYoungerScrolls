// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/YN_UserWidget.h"
#include "YN_InventorySectionWidget.generated.h"

class UTextBlock;

class UYN_ItemDescriptionWidget;
class UYN_ItemsGridWidget;
class UYN_InventoryItem;

UCLASS()
class YOUNG_API UYN_InventorySectionWidget : public UYN_UserWidget
{
	GENERATED_BODY()
	
public:
	void Init(const TArray<UYN_InventoryItem*>& Items);
	void Clear();

protected:
	UFUNCTION()
	void OnNewItemHovered(UYN_InventoryItem* Item);

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UYN_ItemsGridWidget> ItemsGrid;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UYN_ItemDescriptionWidget> ItemDescription;
};
