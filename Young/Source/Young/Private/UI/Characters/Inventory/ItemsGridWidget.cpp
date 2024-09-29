// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "UI/Characters/Inventory/ItemsGridWidget.h"

#include "Components/TileView.h"
#include "Inventory/InventoryItem.h"

void UItemsGridWidget::Init(const TArray<UInventoryItem*>& InItems)
{
	Items = &InItems;

	Clear();

	for(UInventoryItem* Item : InItems)
	{
		TileView->AddItem(Item);
	}
}

void UItemsGridWidget::Clear()
{
	TileView->ClearListItems();
}

UInventoryItem* UItemsGridWidget::GetHoveredItem() const
{
	return TileView->GetSelectedItem<UInventoryItem>();
}

void UItemsGridWidget::NativeConstruct()
{
	Super::NativeConstruct();

	
}

void UItemsGridWidget::OnNewItemHovered()
{
}
