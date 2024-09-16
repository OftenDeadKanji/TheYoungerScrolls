// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "Core/Player/Characters/UI/Inventory/InventoryWidget.h"

#include "Core/General/Characters/Components/InventoryComponent.h"
#include "Core/Player/Characters/UI/Inventory/InventorySectionWidget.h"

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
