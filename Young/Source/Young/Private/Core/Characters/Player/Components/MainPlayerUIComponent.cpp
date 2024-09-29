// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "Core/Characters/Player/Components/MainPlayerUIComponent.h"

#include "Core/Characters/Components/InventoryComponent.h"
#include "Core/Characters/Player/MainPlayer.h"
#include "UI/Characters/Player/MainPlayerHUDWidget.h"
#include "Core/Controllers/MainPlayerController.h"
#include "UI/UserInterfaceSubsystem.h"

UMainPlayerUIComponent::UMainPlayerUIComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UMainPlayerUIComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerMainPlayer = Cast<AMainPlayer>(GetOwner());
	if(OwnerMainPlayer->IsLocallyControlled() == false)
	{
		return;
	}

	AMainPlayerController* MainPlayerController = Cast<AMainPlayerController>(OwnerMainPlayer->GetController());

	ULocalPlayer* LocalPlayer = MainPlayerController->GetLocalPlayer();

	UUserInterfaceSubsystem* UISubsystem = LocalPlayer->GetSubsystem<UUserInterfaceSubsystem>();

	HUDWidget = UISubsystem->CreateAndPushWidget<UMainPlayerHUDWidget>(HUDWidgetClass);

	HUDWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UMainPlayerUIComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(IsValid(HUDWidget) && OwnerMainPlayer.IsValid())
	{
		const FCharacterStats& Stats = OwnerMainPlayer->GetCharacterStats();
		HUDWidget->UpdateCharacterStats(Stats);
	}
}

void UMainPlayerUIComponent::ToggleInventory(const FInputActionValue& Value)
{
	UInventoryComponent* Inventory = OwnerMainPlayer->GetComponentByClass<UInventoryComponent>();
	HUDWidget->ToggleInventoryWidget(Inventory);
}

bool UMainPlayerUIComponent::IsAnyWidgetBlockingPawnInput() const
{
	bool bBlock = false;

	if(IsValid(HUDWidget))
	{
		bBlock |= HUDWidget->IsAnyWidgetBlockingPawnInput();
	}

	return bBlock;
}
