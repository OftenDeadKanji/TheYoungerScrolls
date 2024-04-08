// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.


#include "Core/YN_Player.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"

AYN_Player::AYN_Player()
{
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	
	bUseControllerRotationYaw = false;
	
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
}

void AYN_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

}
