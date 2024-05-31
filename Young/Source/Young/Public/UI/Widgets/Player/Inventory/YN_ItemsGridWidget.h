// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/YN_UserWidget.h"
#include "YN_ItemsGridWidget.generated.h"

class UYN_ImageButtonWidget;
class UGridPanel;

class UYN_InventoryItem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemHovered, UYN_InventoryItem*, Item);

UCLASS()
class YOUNG_API UYN_ItemsGridWidget : public UYN_UserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void Init(const TArray<UYN_InventoryItem*>& Items);
	void Clear();

	UYN_InventoryItem* GetSelectedItem() const;

	FOnItemHovered OnItemHovered;
protected:
	UFUNCTION()
	void ItemHovered(UYN_ImageButtonWidget* Widget);

	UPROPERTY(EditAnywhere)
	TSubclassOf<UYN_ImageButtonWidget> ImageButtonWidgetClass;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UGridPanel> Grid;

	UPROPERTY(EditAnywhere)
	int32 ColumnsCount;

	UPROPERTY(EditAnywhere)
	int32 RowsCount;

	TArray<UYN_ImageButtonWidget*> ItemImageButtons;

	int32 SelectedItemIndex = 0;

	const TArray<UYN_InventoryItem*>* Items;
};
