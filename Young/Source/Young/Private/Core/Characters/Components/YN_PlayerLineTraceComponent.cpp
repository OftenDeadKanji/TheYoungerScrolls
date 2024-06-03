// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.

#include "Core/Characters/Components/YN_PlayerLineTraceComponent.h"

#include "Camera/CameraComponent.h"

#include "Common/Interaction/YN_Interactable.h"
#include "Utilities/DebugMacros.h"

UYN_PlayerLineTraceComponent::UYN_PlayerLineTraceComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UYN_PlayerLineTraceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UWorld* World = GetWorld();
	Check(World);

	FHitResult Hit;

	FVector Start = PlayerCamera->GetComponentLocation();
	FVector End = Start + PlayerCamera->GetForwardVector() * Range;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());

	FCollisionResponseParams ResponseParams = FCollisionResponseParams::DefaultResponseParam;

	World->LineTraceSingleByChannel(Hit, Start, End, TraceChannel, QueryParams, ResponseParams);

	HitActor = Hit.GetActor();
	HitComponent = Hit.GetComponent();

	if (HitActor.IsValid() && HitActor->Implements<UYN_Interactable>())
	{
		HitInteractable = TScriptInterface<IYN_Interactable>(HitActor.Get());
	}

#if WITH_EDITORONLY_DATA
	if (bLogOnScreen)
	{
		if (HitActor.IsValid())
		{
			FString Message;
			
			if (HitInteractable)
			{
				Message = FString::Printf(TEXT("Hit interactable: %s."), *HitActor->GetName());
			}
			else
			{
				Message = FString::Printf(TEXT("Hit: %s."), *HitActor->GetName());
			}

			GEngine->AddOnScreenDebugMessage(0, 0.1f, FColor::Green, Message);
		}
	}

	if (bDebugDraw)
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, -1.0f, 0, 1.5f);
		if (HitActor.IsValid())
		{
			DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 2.0f, 16, FColor::Green);
		}
	}
#endif 
}

const TWeakObjectPtr<AActor>& UYN_PlayerLineTraceComponent::GetHitActor() const
{
	return HitActor;
}

const TWeakObjectPtr<UPrimitiveComponent>& UYN_PlayerLineTraceComponent::GetHitComponent() const
{
	return HitComponent;
}

const TScriptInterface<IYN_Interactable>& UYN_PlayerLineTraceComponent::GetHitInteractable() const
{
	return HitInteractable;
}

void UYN_PlayerLineTraceComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	Check(Owner);

	PlayerCamera = Owner->GetComponentByClass<UCameraComponent>();
	CheckMsg(PlayerCamera.IsValid(), TEXT("Player doesn't have camera component that is required for LineTraceComponent!"));
}

