// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#include "Core/Characters/Player/MainPlayer.h"

#include "Utilities/InputMappingContextEx.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "Common/Interactable.h"
#include "Core/Characters/Player/Components/InteractableDetectorComponent.h"
#include "Core/Controllers/MainPlayerController.h"
#include "Core/HUD/MainPlayerHUD.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AMainPlayer::AMainPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	bReplicates = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bInheritYaw = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	InteractableDetector = CreateDefaultSubobject<UInteractableDetectorComponent>(TEXT("InteractableDetector"));
	InteractableDetector->SetupAttachment(RootComponent);

	bUseControllerRotationYaw = false;

	Movement = GetCharacterMovement();
	Movement->NavAgentProps.bCanCrouch = true;
	Movement->bUseControllerDesiredRotation = true;
	Movement->bOrientRotationToMovement = true;
	SetReplicatingMovement(true);
}

void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(MainPlayerInputMappingContext == nullptr)
	{
		return;
	}

	APlayerController* PlayerController = GetController<APlayerController>();

	ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	InputSubsystem->ClearAllMappings();
	InputSubsystem->AddMappingContext(MainPlayerInputMappingContext.Get(), 0);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(MainPlayerInputMappingContext->GetAction(TEXT("IA_MainPlayer_Move")), ETriggerEvent::Triggered, this, &AMainPlayer::Move);
	EnhancedInputComponent->BindAction(MainPlayerInputMappingContext->GetAction(TEXT("IA_MainPlayer_Move")), ETriggerEvent::Completed, this, &AMainPlayer::Move);

	EnhancedInputComponent->BindAction(MainPlayerInputMappingContext->GetAction(TEXT("IA_MainPlayer_LookAround")), ETriggerEvent::Triggered, this, &AMainPlayer::LookAround);
	EnhancedInputComponent->BindAction(MainPlayerInputMappingContext->GetAction(TEXT("IA_MainPlayer_LookAround")), ETriggerEvent::Completed, this, &AMainPlayer::LookAround);

	EnhancedInputComponent->BindAction(MainPlayerInputMappingContext->GetAction(TEXT("IA_MainPlayer_Use")), ETriggerEvent::Started, this, &AMainPlayer::Use);

	EnhancedInputComponent->BindAction(MainPlayerInputMappingContext->GetAction(TEXT("IA_MainPlayer_ToggleInventory")), ETriggerEvent::Started, PlayerController->GetHUD<AMainPlayerHUD>(), &AMainPlayerHUD::ToggleInventory);
}

void AMainPlayer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = GetController<APlayerController>();
	HUD = PlayerController->GetHUD<AMainPlayerHUD>();

	CurrentMovementDirection = GetCapsuleComponent()->GetForwardVector();
}

void AMainPlayer::Move(const FInputActionValue& Value)
{
	if(HUD->IsAnyWidgetBlockingPawnInput())
	{
		return;
	}

	FVector2D Direction = Value.Get<FVector2D>();
	if(Direction.IsNearlyZero() == false)
	{
		UWorld* World = GetWorld();

		FVector Forward = Camera->GetForwardVector();
		FVector Right = Camera->GetRightVector();

		FVector TargetMovement = FVector::ZeroVector;
		TargetMovement += Forward * Direction.Y;
		TargetMovement += Right * Direction.X;
		TargetMovement.Z = 0.0f;
		TargetMovement.Normalize();

		FVector MovementChangeDirection = TargetMovement - CurrentMovementDirection;
		CurrentMovementDirection += MovementChangeDirection * FMath::Min(1.0f, World->GetDeltaSeconds() * CharacterMovementChangeSpeed);

		Movement->AddInputVector(CurrentMovementDirection);
	}
}

void AMainPlayer::LookAround(const FInputActionValue& Value)
{
	if(HUD->IsAnyWidgetBlockingPawnInput())
	{
		return;
	}

	FVector2D Direction = Value.Get<FVector2D>();
	if(Direction.IsNearlyZero() == false)
	{
		UWorld* World = GetWorld();

		FRotator SpringArmRotation = SpringArm->GetRelativeRotation();
		FVector2D LookAroundAngle = Direction * LookAroundSpeed * World->GetDeltaSeconds();

		//Turn
		SpringArmRotation.Yaw += LookAroundAngle.X;

		//Look up
		SpringArmRotation.Pitch = FMath::Clamp(SpringArmRotation.Pitch + LookAroundAngle.Y, LookUpRange.X, LookUpRange.Y);

		SpringArm->SetRelativeRotation(SpringArmRotation);
	}
}

void AMainPlayer::Use(const FInputActionValue& Value)
{
	if(HUD->IsAnyWidgetBlockingPawnInput())
	{
		return;
	}

	if(TScriptInterface<IInteractable> Interactable = InteractableDetector->GetFirstInteractable())
	{
		if(IInteractable::Execute_IsInteractionByServerRequired(Interactable.GetObject()))
		{
			Server_Use();
		}
		else
		{
			IInteractable::Execute_Local_OnUsePressed(Interactable.GetObject(), Cast<AMainPlayerController>(GetController()));
		}
	}
}

void AMainPlayer::Server_Use_Implementation()
{
	if (TScriptInterface<IInteractable> Interactable = InteractableDetector->GetFirstInteractable())
	{
		if (IInteractable::Execute_IsInteractionByServerRequired(Interactable.GetObject()))
		{
			IInteractable::Execute_Authority_OnUsePressed(Interactable.GetObject(), Cast<AMainPlayerController>(GetController()));
		}
	}
}
