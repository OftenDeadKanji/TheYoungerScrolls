// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "Core/HUD/MainPlayerHUD.h"

#include "Blueprint/UserWidget.h"
#include "Core/Characters/Components/InventoryComponent.h"
#include "Core/Characters/Player/MainPlayer.h"
#include "UI/Characters/Player/MainPlayerHUDWidget.h"

AMainPlayerHUD::AMainPlayerHUD()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AMainPlayerHUD::ToggleInventory(const FInputActionValue& Value)
{
	UInventoryComponent* Inventory = MainPlayer->GetComponentByClass<UInventoryComponent>();
	if(IsValid(HUDWidget))
	{
		HUDWidget->ToggleInventoryWidget(Inventory);
	}
}

bool AMainPlayerHUD::IsAnyWidgetBlockingPawnInput() const
{
	bool bBlockPawnInput = false;

	if(IsValid(HUDWidget))
	{
		bBlockPawnInput |= HUDWidget->IsBlockingPawnInput();
	}

	return bBlockPawnInput;
}

void AMainPlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(PlayerOwner) == false)
	{
		return;
	}

	MainPlayer = Cast<AMainPlayer>(GetOwningPawn());
	if(MainPlayer.IsValid() == false)
	{
		return;
	}

	HUDWidget = CreateWidget<UMainPlayerHUDWidget>(PlayerOwner, HUDWidgetClass);
	if(IsValid(HUDWidget) == false)
	{
		return;
	}

	HUDWidget->AddToViewport();
	HUDWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void AMainPlayerHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(IsValid(HUDWidget) && MainPlayer.IsValid())
	{
		const FCharacterStats& Stats = MainPlayer->GetCharacterStats();
		HUDWidget->UpdateCharacterStats(Stats);
	}
}
