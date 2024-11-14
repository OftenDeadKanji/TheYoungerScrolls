// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "UI/Characters/Inventory/ItemsGridWidget.h"

#include "Components/TileView.h"
#include "Inventory/InventoryItemInstanceData.h"

void UItemsGridWidget::Init(const TArray<UInventoryItemInstanceData*>& InItems)
{
	Items = &InItems;

	Clear();

	for(UInventoryItemInstanceData* Item : InItems)
	{
		TileView->AddItem(Item);
	}
}

void UItemsGridWidget::Clear()
{
	TileView->ClearListItems();
}

UInventoryItemInstanceData* UItemsGridWidget::GetHoveredItem() const
{
	return TileView->GetSelectedItem<UInventoryItemInstanceData>();
}

void UItemsGridWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TileView->OnItemIsHoveredChanged().AddUObject(this, &UItemsGridWidget::OnItemHoverChange);
	TileView->OnItemClicked().AddUObject(this, &UItemsGridWidget::OnItemClicked);
}

void UItemsGridWidget::OnItemHoverChange(UObject* Item, bool bHovered)
{
	if (UInventoryItemInstanceData* InventoryItem = Cast<UInventoryItemInstanceData>(Item))
	{
		OnItemHoverChangeEvent.Broadcast(InventoryItem, bHovered);
	}
}

void UItemsGridWidget::OnItemClicked(UObject* Item)
{
	if (UInventoryItemInstanceData* InventoryItem = Cast<UInventoryItemInstanceData>(Item))
	{
		OnItemClickedEvent.Broadcast(InventoryItem);
	}
}
