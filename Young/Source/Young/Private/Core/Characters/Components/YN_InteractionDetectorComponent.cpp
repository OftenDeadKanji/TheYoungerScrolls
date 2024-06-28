// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.


#include "Core/Characters/Components/YN_InteractionDetectorComponent.h"

#include "Common/Interaction/YN_InteractionAreaComponent.h"

UYN_InteractionAreaComponent* UYN_InteractionDetectorComponent::GetFirstInteractableArea() const
{
	return OverlappedInteractableAreas.IsEmpty() ? nullptr : OverlappedInteractableAreas[0];
}

void UYN_InteractionDetectorComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UYN_InteractionDetectorComponent::OnAreaOverlapBegin);
	OnComponentEndOverlap.AddDynamic(this, &UYN_InteractionDetectorComponent::OnAreaOverlapEnd);
}

void UYN_InteractionDetectorComponent::OnAreaOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(IsValid(OtherComponent))
	{
		if(UYN_InteractionAreaComponent* InteractionArea = Cast<UYN_InteractionAreaComponent>(OtherComponent))
		{
			OverlappedInteractableAreas.Add(InteractionArea);
			GEngine->AddOnScreenDebugMessage(0, 2.0f, FColor::Yellow, FString::Printf(TEXT("Overlapped interactable component %s"), *OtherComponent->GetName()));
		}
	}
}

void UYN_InteractionDetectorComponent::OnAreaOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	if(IsValid(OtherComponent))
	{
		if (UYN_InteractionAreaComponent* InteractionArea = Cast<UYN_InteractionAreaComponent>(OtherComponent))
		{
			for(int i = OverlappedInteractableAreas.Num() - 1; i >= 0; i--)
			{
				if (OverlappedInteractableAreas[i] == InteractionArea)
				{
					OverlappedInteractableAreas.RemoveAt(i);
					GEngine->AddOnScreenDebugMessage(0, 2.0f, FColor::Yellow, FString::Printf(TEXT("Ended Overlap with interactable component %s"), *OtherComponent->GetName()));
				}
			}
		}
	}
}
