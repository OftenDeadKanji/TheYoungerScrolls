// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.


#include "UI/Widgets/Player/Inventory/YN_InventoryWidget.h"

#include "Components/Button.h"
#include "Core/Characters/Components/YN_InventoryComponent.h"
#include "UI/Widgets/Player/Inventory/YN_InventorySectionWidget.h"
#include "Inventory/YN_Weapon.h"

void UYN_InventoryWidget::Init(UYN_InventoryComponent* Inventory)
{
	PlayerInventory = Inventory;

	Section->SetVisibility(ESlateVisibility::Visible);
	Section->Init(Inventory->GetWeaponsAsItems());


}

void UYN_InventoryWidget::Clear()
{
	Section->Clear();
}
