// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "UI/Characters/Inventory/InventorySectionWidget.h"

#include "UI/Characters/Inventory/ItemInfoWidget.h"
#include "UI/Characters/Inventory/ItemsGridWidget.h"

void UInventorySectionWidget::Init(const TArray<UInventoryItem*>& Items)
{
	ItemsGrid->Init(Items);
	//ItemsGrid->OnItemHovered.AddDynamic(this, &UInventorySectionWidget::OnNewItemHovered);

	//ItemsTileView->Add

	ItemInfo->SetNewItem(nullptr);
}

void UInventorySectionWidget::Clear()
{
	ItemsGrid->Clear();
	//ItemsGrid->OnItemHovered.RemoveDynamic(this, &UInventorySectionWidget::OnNewItemHovered);
}

void UInventorySectionWidget::OnNewItemHovered(UInventoryItem* Item)
{
	ItemInfo->SetNewItem(Item);
}
