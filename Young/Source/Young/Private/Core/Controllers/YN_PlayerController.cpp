// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.


#include "Core/Controllers/YN_PlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

#include "Common/YN_SpawnPoint.h"
#include "Core/Characters/YN_Player.h"
#include "Utilities/DebugMacros.h"
#include "Utilities/YN_InputMappingContext.h"

void AYN_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	bReplicates = true;

	SafeCheckMsgNoRet(PlayerInputMapping, "PlayerInputMapping is not set in %s", *GetName());

	ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	Check(LocalPlayer);

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	Check(InputSubsystem);

	InputSubsystem->ClearAllMappings();
	InputSubsystem->AddMappingContext(PlayerInputMapping, 0);

	UEnhancedInputComponent* InputCmp = Cast<UEnhancedInputComponent>(InputComponent);
	Check(InputCmp);

	InputCmp->BindAction(PlayerInputMapping->GetAction(TEXT("IA_PlayerMove")), ETriggerEvent::Triggered, this, &AYN_PlayerController::CallMove);
	InputCmp->BindAction(PlayerInputMapping->GetAction(TEXT("IA_PlayerMove")), ETriggerEvent::Completed, this, &AYN_PlayerController::CallMove);

	InputCmp->BindAction(PlayerInputMapping->GetAction(TEXT("IA_PlayerLookAround")), ETriggerEvent::Triggered, this, &AYN_PlayerController::CallLookAround);
	InputCmp->BindAction(PlayerInputMapping->GetAction(TEXT("IA_PlayerLookAround")), ETriggerEvent::Completed, this, &AYN_PlayerController::CallLookAround);

	InputCmp->BindAction(PlayerInputMapping->GetAction(TEXT("IA_PlayerJump")), ETriggerEvent::Started, this, &AYN_PlayerController::CallJump);

	InputCmp->BindAction(PlayerInputMapping->GetAction(TEXT("IA_PlayerCrouch")), ETriggerEvent::Triggered, this, &AYN_PlayerController::CallStartCrouch);
	InputCmp->BindAction(PlayerInputMapping->GetAction(TEXT("IA_PlayerCrouch")), ETriggerEvent::Completed, this, &AYN_PlayerController::CallStopCrouch);

	InputCmp->BindAction(PlayerInputMapping->GetAction(TEXT("IA_InteractPrimary")), ETriggerEvent::Started, this, &AYN_PlayerController::CallInteractPrimary);

	InputCmp->BindAction(PlayerInputMapping->GetAction(TEXT("IA_PlayerInventory")), ETriggerEvent::Started, this, &AYN_PlayerController::CallToggleInventory);
}

void AYN_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		CheckMsg(PossessedPlayer == nullptr, TEXT("Player is not supposed to be already spawned!"));

		UWorld* World = GetWorld();
		Check(World);

		AActor* SpawnPoint = UGameplayStatics::GetActorOfClass(World, AYN_SpawnPoint::StaticClass());
		CheckMsg(SpawnPoint, TEXT("Spawn place not found!"));

		FTransform SpawnTransform = SpawnPoint->GetActorTransform();

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		
		AYN_Player* SpawnedPlayer = GetWorld()->SpawnActorDeferred<AYN_Player>(PlayerClass, SpawnTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		Possess(SpawnedPlayer);
		PossessedPlayer = SpawnedPlayer;

		UGameplayStatics::FinishSpawningActor(SpawnedPlayer, SpawnTransform, ESpawnActorScaleMethod::MultiplyWithRoot);
	}
}

void AYN_PlayerController::CallMove(const FInputActionValue& Value)
{
	FVector2D Direction = Value.Get<FVector2D>();
	if (PossessedPlayer.IsValid())
	{
		PossessedPlayer->Move(Direction);
	}
}

void AYN_PlayerController::CallLookAround(const FInputActionValue& Value)
{
	FVector2D Direction = Value.Get<FVector2D>();
	if (PossessedPlayer.IsValid())
	{
		PossessedPlayer->LookAround(Direction);
	}
}

void AYN_PlayerController::CallJump(const FInputActionValue& Value)
{
	if (PossessedPlayer.IsValid())
	{
		PossessedPlayer->Jump();
	}
}

void AYN_PlayerController::CallStartCrouch(const FInputActionValue& Value)
{
	if (PossessedPlayer.IsValid())
	{
		PossessedPlayer->StartCrouch();
	}
}

void AYN_PlayerController::CallStopCrouch(const FInputActionValue& Value)
{
	if (PossessedPlayer.IsValid())
	{
		PossessedPlayer->StopCrouch();
	}
}

void AYN_PlayerController::CallInteractPrimary(const FInputActionValue& Value)
{
	if (PossessedPlayer.IsValid())
	{
		PossessedPlayer->InteractPrimary();
	}
}

void AYN_PlayerController::CallInteractSecondary(const FInputActionValue& Value)
{
	if (PossessedPlayer.IsValid())
	{
		PossessedPlayer->InteractSecondary();
	}
}

void AYN_PlayerController::CallToggleInventory(const FInputActionValue& Value)
{
	if(PossessedPlayer.IsValid())
	{
		PossessedPlayer->ToggleInventory();
	}
}

void AYN_PlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AYN_PlayerController, PossessedPlayer);
}
