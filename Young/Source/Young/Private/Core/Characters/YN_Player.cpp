// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.


#include "Core/Characters/YN_Player.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Core/Characters/Components/YN_SafeSpawnComponent.h"
#include "Core/Characters/YN_CharacterStats.h"
#include "Utilities/DebugMacros.h"
#include "UI/YN_UserInterfaceSubsystem.h"
#include "UI/Widgets/Player/YN_PlayerHUD.h"

AYN_Player::AYN_Player()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	
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
	if (Direction.Size() > 0.0f)
	{
		FVector Movement;
		Movement += GetActorForwardVector() * Direction.Y;
		Movement += GetActorRightVector() * Direction.X;

		Movement.Normalize();
		GetCharacterMovement()->AddInputVector(Movement);
	}
}

void AYN_Player::LookAround(const FVector2D& Direction)
{
	if (Direction.Size() > 0.0f)
	{
		// Turn
		{
			float TurnAngle = Direction.X * LookAroundSpeed;

			FRotator ActorRotation = GetActorRotation();
			ActorRotation.Yaw += TurnAngle;

			SetActorRotation(ActorRotation);
		}

		// Look up
		{
			FRotator CurrentRotation = Camera->GetComponentRotation();

			float NewPitch = FMath::Clamp(CurrentRotation.Pitch + Direction.Y, LookUpRange.X, LookUpRange.Y);
			FRotator NewRotation = FRotator(NewPitch, CurrentRotation.Yaw, CurrentRotation.Roll);

			Camera->SetWorldRotation(NewRotation);
		}
	}
}

void AYN_Player::Jump()
{
	Super::Jump();
}

void AYN_Player::StartCrouch()
{
	Super::Crouch();
}

void AYN_Player::StopCrouch()
{
	Super::UnCrouch();
}

void AYN_Player::BeginPlay()
{
	Super::BeginPlay();

	SafeSpawnComponent->OnSafeSpawned.BindDynamic(this, &AYN_Player::OnSafeSpawn);
	SafeSpawnComponent->StartSafeSpawn(GetCapsuleComponent());
	UE_LOG(LogTemp, Warning, TEXT("NET MODE = %d"), GetNetMode());
	if (IsLocallyControlled())
	{
		if (SafeCheckMsgNoRet(PlayerHUDClass, TEXT("Player HUD class not set. Was that intentional?")))
		{
			APlayerController* PlayerController = Cast<APlayerController>(GetController());
			Check(PlayerController);

			ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
			Check(LocalPlayer);

			UYN_UserInterfaceSubsystem* UISubsystem = LocalPlayer->GetSubsystem<UYN_UserInterfaceSubsystem>();
			Check(UISubsystem);

			PlayerHUD = UISubsystem->CreateAndPushWidget<UYN_PlayerHUD>(PlayerHUDClass);
		}
	}
}

void AYN_Player::OnSafeSpawn()
{
	SafeSpawnComponent->DestroyComponent();
	SafeSpawnComponent = nullptr;
}
