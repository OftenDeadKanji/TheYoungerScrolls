// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.


#include "UI/Widgets/Player/Inventory/YN_InventorySectionWidget.h"

#include "UI/Widgets/Player/Inventory/YN_ItemDescriptionWidget.h"
#include "UI/Widgets/Player/Inventory/YN_ItemsGridWidget.h"


void UYN_InventorySectionWidget::Init(const TArray<UYN_InventoryItem*>& Items)
{
	ItemsGrid->Init(Items);
	ItemsGrid->OnItemHovered.AddDynamic(this, &UYN_InventorySectionWidget::OnNewItemHovered);

	ItemDescription->SetNewItem(ItemsGrid->GetSelectedItem());
}

void UYN_InventorySectionWidget::Clear()
{
	ItemsGrid->Clear();
}

void UYN_InventorySectionWidget::OnNewItemHovered(UYN_InventoryItem* Item)
{
	ItemDescription->SetNewItem(Item);
}
