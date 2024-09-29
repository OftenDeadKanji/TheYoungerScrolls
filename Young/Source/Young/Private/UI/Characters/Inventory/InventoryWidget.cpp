// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "UI/Characters/Inventory/InventoryWidget.h"

#include "Core/Characters/Components/InventoryComponent.h"
#include "UI/Characters/Inventory/InventorySectionWidget.h"

void UInventoryWidget::Init(UInventoryComponent* Inventory)
{
	PlayerInventory = Inventory;

	Section->SetVisibility(ESlateVisibility::Visible);
	Section->Init(Inventory->GetWeaponsAsItems());
}

void UInventoryWidget::Clear()
{
	Section->Clear();
}
