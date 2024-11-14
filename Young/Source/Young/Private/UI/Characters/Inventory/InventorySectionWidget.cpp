// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "UI/Characters/Inventory/InventorySectionWidget.h"

#include "UI/Characters/Inventory/ItemInfoWidget.h"
#include "UI/Characters/Inventory/ItemsGridWidget.h"

void UInventorySectionWidget::Init(const TArray<UInventoryItemInstanceData*>& Items)
{
	ItemsGrid->Init(Items);

	ItemsGrid->OnItemHoverChangeEvent.AddDynamic(this, &UInventorySectionWidget::OnItemHoverChange);
	ItemsGrid->OnItemClickedEvent.AddDynamic(this, &UInventorySectionWidget::OnItemClicked);

	ItemInfo->SetNewItem(nullptr);
}

void UInventorySectionWidget::Clear()
{
	ItemsGrid->Clear();

	ItemsGrid->OnItemClickedEvent.RemoveDynamic(this, &UInventorySectionWidget::OnItemClicked);
	ItemsGrid->OnItemHoverChangeEvent.RemoveDynamic(this, &UInventorySectionWidget::OnItemHoverChange);
}

void UInventorySectionWidget::OnItemHoverChange(UInventoryItemInstanceData* Item, bool bHovered)
{
	ItemInfo->SetNewItem(bHovered ? Item : nullptr);
}

void UInventorySectionWidget::OnItemClicked(UInventoryItemInstanceData* Item)
{
	OnItemClickedEvent.Broadcast(Item);
}
