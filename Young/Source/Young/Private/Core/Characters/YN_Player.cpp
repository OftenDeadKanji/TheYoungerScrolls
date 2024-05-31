// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.


#include "Core/Characters/YN_Player.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Core/Characters/Components/YN_SafeSpawnComponent.h"
#include "Core/Characters/Components/YN_PlayerLineTraceComponent.h"
#include "Core/Characters/YN_CharacterStats.h"
#include "Core/Controllers/YN_PlayerController.h"
#include "Utilities/DebugMacros.h"
#include "UI/YN_UserInterfaceSubsystem.h"
#include "UI/Widgets/Player/YN_PlayerHUD.h"
#include "Common/Interaction/YN_Interactable.h"
#include "UI/Widgets/Player/Inventory/YN_InventoryWidget.h"

AYN_Player::AYN_Player()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	
	LineTraceComponent = CreateDefaultSubobject<UYN_PlayerLineTraceComponent>(TEXT("LineTraceComponent"));

	SafeSpawnComponent = CreateDefaultSubobject<UYN_SafeSpawnComponent>(TEXT("SafeSpawnComponent"));
	SafeSpawnComponent->SetupAttachment(RootComponent);

	bUseControllerRotationYaw = false;
	
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
	SetReplicatingMovement(true);
}

void AYN_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerHUD)
	{
		PlayerHUD->UpdateHealth(Stats.CurrentHealth, Stats.MaxHealth);
		PlayerHUD->UpdateStamina(Stats.CurrentStamina, Stats.MaxStamina);
		PlayerHUD->UpdateMana(Stats.CurrentMana, Stats.MaxMana);
	}
}

void AYN_Player::Move(const FVector2D& Direction)
{
	if(UISubsystem->GetTopWidget()->IsBlockingMovementAndCameraInput())
	{
		return;
	}

	if (Direction.Size() > 0.0f)
	{
		FVector Forward = Camera->GetForwardVector();
		Forward.Z = 0.0;
		Forward.Normalize();

		FVector Right = Camera->GetRightVector();
		Right.Z = 0.0;
		Right.Normalize();

		FVector Movement(0.0f, 0.0f, 0.0f);
		Movement += Forward * Direction.Y;
		Movement += Right * Direction.X;

		Movement.Normalize();
		GetCharacterMovement()->AddInputVector(Movement);

		SetActorRotation(Movement.Rotation());
	}
}

void AYN_Player::LookAround(const FVector2D& Direction)
{
	if(UISubsystem->GetTopWidget()->IsBlockingMovementAndCameraInput())
	{
		return;
	}

	if (Direction.Size() > 0.0f)
	{
		UWorld* World = GetWorld();
		Check(World);

		FRotator SpringArmRotation = SpringArm->GetRelativeRotation();
		FVector2D LookAroundAngle = Direction * LookAroundSpeed * World->GetDeltaSeconds();

		// Turn
		SpringArmRotation.Yaw += LookAroundAngle.X;

		// Look up
		SpringArmRotation.Pitch += LookAroundAngle.Y;
		SpringArmRotation.Pitch = FMath::Clamp(SpringArmRotation.Pitch, LookUpRange.X, LookUpRange.Y);

		SpringArm->SetRelativeRotation(SpringArmRotation);
	}
}

void AYN_Player::Jump()
{
	if(UISubsystem->GetTopWidget()->IsBlockingMovementAndCameraInput())
	{
		return;
	}

	Super::Jump();
}

void AYN_Player::StartCrouch()
{
	if(UISubsystem->GetTopWidget()->IsBlockingMovementAndCameraInput())
	{
		return;
	}

	Super::Crouch();
}

void AYN_Player::StopCrouch()
{
	if(UISubsystem->GetTopWidget()->IsBlockingMovementAndCameraInput())
	{
		return;
	}

	Super::UnCrouch();
}

void AYN_Player::InteractPrimary()
{
	Check(LineTraceComponent);

	if (TScriptInterface<IYN_Interactable> Interactable = LineTraceComponent->GetHitInteractable())
	{
		if (IsValid(Interactable.GetObject()))
		{
			Interactable->Execute_OnUsePressed(Interactable.GetObject(), Cast<AYN_PlayerController>(GetController()));
		}
	}
}

void AYN_Player::InteractSecondary()
{}

void AYN_Player::ToggleInventory()
{
	Check(Inventory);
	Check(InventoryWidget);

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	Check(PlayerController);

	if(InventoryWidget->GetVisibility() == ESlateVisibility::Collapsed)
	{
		InventoryWidget->Init(Inventory);
		InventoryWidget->SetVisibility(ESlateVisibility::Visible);

		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PlayerController);
		PlayerController->SetShowMouseCursor(true);
	}
	else
	{
		InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);

		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
		PlayerController->SetShowMouseCursor(false);
	}
}

void AYN_Player::BeginPlay()
{
	Super::BeginPlay();

	SafeSpawnComponent->OnSafeSpawned.BindDynamic(this, &AYN_Player::OnSafeSpawn);
	SafeSpawnComponent->StartSafeSpawn(GetCapsuleComponent());

	if (IsLocallyControlled())
	{
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		Check(PlayerController);

		ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
		Check(LocalPlayer);

		UISubsystem = LocalPlayer->GetSubsystem<UYN_UserInterfaceSubsystem>();
		Check(UISubsystem);

		Check(PlayerHUDClass);
		PlayerHUD = UISubsystem->CreateAndPushWidget<UYN_PlayerHUD>(PlayerHUDClass);
		Check(PlayerHUD);

		PlayerHUD->SetVisibility(ESlateVisibility::HitTestInvisible);

		Check(InventoryWidgetClass);
		InventoryWidget = Cast<UYN_InventoryWidget>(UISubsystem->CreateAndPushWidget(InventoryWidgetClass));
		Check(InventoryWidget);

		InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AYN_Player::OnSafeSpawn()
{
	SafeSpawnComponent->DestroyComponent();
	SafeSpawnComponent = nullptr;
}
