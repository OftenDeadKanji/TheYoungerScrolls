// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "UI/Characters/Inventory/InventoryWidget.h"

#include "Core/Characters/Components/InventoryComponent.h"
#include "Core/Characters/Player/MainPlayer.h"
#include "Inventory/InventoryItemInstanceData.h"
#include "Inventory/UsableItem.h"
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

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Section->OnItemClickedEvent.AddDynamic(this, &UInventoryWidget::OnItemClicked);
}

void UInventoryWidget::OnItemClicked(UInventoryItemInstanceData* Items)
{
	APlayerController* PlayerController = GetOwningPlayer();

	if(Items->Implements<UUsableItem>())
	{
		IUsableItem::Execute_Use(Items, PlayerController);
	}
}
