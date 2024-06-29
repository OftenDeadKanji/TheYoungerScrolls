// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.


#include "Core/Characters/Components/YN_InteractionDetectorComponent.h"

#include "Common/Interaction/YN_Interactable.h"
#include "Common/Interaction/YN_InteractionAreaComponent.h"

TScriptInterface<IYN_Interactable> UYN_InteractionDetectorComponent::GetFirstInteractable()
{
	return OverlappedInteractables.IsEmpty() ? TScriptInterface<IYN_Interactable>() : OverlappedInteractables[0];
}

void UYN_InteractionDetectorComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UYN_InteractionDetectorComponent::OnAreaOverlapBegin);
	OnComponentEndOverlap.AddDynamic(this, &UYN_InteractionDetectorComponent::OnAreaOverlapEnd);
}

void UYN_InteractionDetectorComponent::OnAreaOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TScriptInterface<IYN_Interactable> Interactable;
	if(IsValid(OtherActor) && OtherActor->Implements<UYN_Interactable>())
	{
		Interactable = OtherActor;
	}
	else if(IsValid(OtherComponent) && OtherComponent->Implements<UYN_Interactable>())
	{
		Interactable = OtherComponent;
	}

	if (Interactable)
	{
		OverlappedInteractables.Add(Interactable);
		GEngine->AddOnScreenDebugMessage(0, 2.0f, FColor::Yellow, FString::Printf(TEXT("Overlapped interactable %s"), *Interactable.GetObject()->GetName()));
	}
}

void UYN_InteractionDetectorComponent::OnAreaOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	TScriptInterface<IYN_Interactable> Interactable;
	if(IsValid(OtherActor) && OtherActor->Implements<UYN_Interactable>())
	{
		Interactable = OtherActor;
	}
	else if(IsValid(OtherComponent) && OtherComponent->Implements<UYN_Interactable>())
	{
		Interactable = OtherComponent;
	}

	if (Interactable)
	{
		for (int i = OverlappedInteractables.Num() - 1; i >= 0; i--)
		{
			if (OverlappedInteractables[i].GetObject() == Interactable.GetObject())
			{
				OverlappedInteractables.RemoveAt(i);
				GEngine->AddOnScreenDebugMessage(0, 2.0f, FColor::Yellow, FString::Printf(TEXT("Ended Overlap with interactable %s"), *Interactable.GetObject()->GetName()));
			}
		}
	}
}
