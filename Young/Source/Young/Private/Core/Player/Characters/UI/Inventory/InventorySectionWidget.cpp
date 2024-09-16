// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "Core/Player/Characters/UI/Inventory/InventorySectionWidget.h"

#include "Components/TileView.h"
#include "Core/Player/Characters/UI/Inventory/ItemInfoWidget.h"
#include "Core/Player/Characters/UI/Inventory/ItemsGridWidget.h"

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
