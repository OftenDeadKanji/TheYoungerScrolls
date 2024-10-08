// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "UI/Characters/Player/MainPlayerHUDWidget.h"

#include "Components/BackgroundBlur.h"
#include "Components/Overlay.h"
#include "Core/Characters/Components/InventoryComponent.h"
#include "UI/Characters/CharacterStatsWidget.h"
#include "UI/Characters/Inventory/InventoryWidget.h"

void UMainPlayerHUDWidget::ToggleInventoryWidget(UInventoryComponent* Inventory)
{
	check(IsValid(GameBlur));

	if(IsValid(InventoryWidget))
	{
		InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
		InventoryWidget->RemoveFromParent();
		InventoryWidget = nullptr;

		GameBlur->SetVisibility(ESlateVisibility::Collapsed);
	}
	else if(Inventory && InventoryWidgetClass)
	{
		InventoryWidget = CreateWidget<UInventoryWidget>(this, InventoryWidgetClass);
		InventoryPanel->AddChild(InventoryWidget);
		InventoryWidget->SetVisibility(ESlateVisibility::Visible);

		InventoryWidget->Init(Inventory);

		GameBlur->SetVisibility(ESlateVisibility::Visible);
	}

	UpdateCachedChildrenData({ CharacterStats, InventoryWidget });
	UpdateInputMode();
}

void UMainPlayerHUDWidget::UpdateCharacterStats(const FCharacterStats& Stats)
{
	check(IsValid(GameBlur));

	CharacterStats->Update(Stats);
}
