// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.

#include "UI/Widgets/Player/Inventory/YN_ItemDescriptionWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "Inventory/YN_InventoryItem.h"
#include "Inventory/YN_InventoryItemConstData.h"

void UYN_ItemDescriptionWidget::SetNewItem(UYN_InventoryItem* Item)
{
	if (Item)
	{
		ItemIcon->SetBrushFromTexture(Item->GetConstData()->GetIcon());
		ItemIcon->SetVisibility(ESlateVisibility::HitTestInvisible);

		ItemTextDescription->SetText(Item->GetConstData()->GetDescription());
		ItemTextDescription->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
	{
		ItemIcon->SetVisibility(ESlateVisibility::Collapsed);
		ItemTextDescription->SetVisibility(ESlateVisibility::Collapsed);
	}
}
