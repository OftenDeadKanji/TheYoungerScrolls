// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.


#include "Core/YN_PlayerController.h"
#include "Core/YN_Player.h"
#include "Utilities/YN_InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include <EnhancedInputComponent.h>

void AYN_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (PlayerInputMapping == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerInputMapping is not set in %s"), *GetName());
		return;
	}

	ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	check(LocalPlayer);

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(InputSubsystem);

	InputSubsystem->ClearAllMappings();
	InputSubsystem->AddMappingContext(PlayerInputMapping, 0);

	UEnhancedInputComponent* InputCmp = Cast<UEnhancedInputComponent>(InputComponent);
	check(InputCmp);

	InputCmp->BindAction(PlayerInputMapping->GetAction(TEXT("IA_PlayerMove")), ETriggerEvent::Triggered, this, &AYN_PlayerController::CallMove);
	InputCmp->BindAction(PlayerInputMapping->GetAction(TEXT("IA_PlayerMove")), ETriggerEvent::Completed, this, &AYN_PlayerController::CallMove);

	InputCmp->BindAction(PlayerInputMapping->GetAction(TEXT("IA_PlayerLookAround")), ETriggerEvent::Triggered, this, &AYN_PlayerController::CallLookAround);
	InputCmp->BindAction(PlayerInputMapping->GetAction(TEXT("IA_PlayerLookAround")), ETriggerEvent::Completed, this, &AYN_PlayerController::CallLookAround);

	InputCmp->BindAction(PlayerInputMapping->GetAction(TEXT("IA_PlayerJump")), ETriggerEvent::Triggered, this, &AYN_PlayerController::CallJump);

	InputCmp->BindAction(PlayerInputMapping->GetAction(TEXT("IA_PlayerCrouch")), ETriggerEvent::Triggered, this, &AYN_PlayerController::CallStartCrouch);
	InputCmp->BindAction(PlayerInputMapping->GetAction(TEXT("IA_PlayerCrouch")), ETriggerEvent::Completed, this, &AYN_PlayerController::CallStopCrouch);
}

void AYN_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	PossessedPlayer = Cast<AYN_Player>(GetPawn());
	checkf(PossessedPlayer, TEXT("PlayerController %s is not possessing a player"), *GetName());
}

void AYN_PlayerController::CallMove(const FInputActionValue& Value)
{
	FVector2D Direction = Value.Get<FVector2D>();
	if (PossessedPlayer)
	{
		PossessedPlayer->Move(Direction);
	}
}

void AYN_PlayerController::CallLookAround(const FInputActionValue& Value)
{
	FVector2D Direction = Value.Get<FVector2D>();
	if (PossessedPlayer)
	{
		PossessedPlayer->LookAround(Direction);
	}
}

void AYN_PlayerController::CallJump(const FInputActionValue& Value)
{
	if (PossessedPlayer)
	{
		PossessedPlayer->Jump();
	}
}

void AYN_PlayerController::CallStartCrouch(const FInputActionValue& Value)
{
	if (PossessedPlayer)
	{
		PossessedPlayer->StartCrouch();
	}
}

void AYN_PlayerController::CallStopCrouch(const FInputActionValue& Value)
{
	if (PossessedPlayer)
	{
		PossessedPlayer->StopCrouch();
	}
}
