// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "Core/Player/Characters/UI/Inventory/ItemInfoWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Inventory/InventoryItem.h"

void UItemInfoWidget::SetNewItem(UInventoryItem* Item)
{
	if(IsValid(Item))
	{
		ImageItemIcon->SetBrushFromTexture(Item->GetItemTypeData()->GetIcon());
		ImageItemIcon->SetVisibility(ESlateVisibility::HitTestInvisible);

		TextItemDescription->SetText(Item->GetItemTypeData()->GetDescription());
		TextItemDescription->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
	{
		ImageItemIcon->SetVisibility(ESlateVisibility::Collapsed);
		TextItemDescription->SetVisibility(ESlateVisibility::Collapsed);
	}
}
