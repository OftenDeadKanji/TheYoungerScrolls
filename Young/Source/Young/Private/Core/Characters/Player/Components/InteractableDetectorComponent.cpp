// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "Core/Characters/Player/Components/InteractableDetectorComponent.h"

#include "Common/Interactable.h"

void UInteractableDetectorComponent::PostLoad()
{
	Super::PostLoad();

	SetCollisionProfileName(TEXT("OverlapDetector"));
}

void UInteractableDetectorComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UInteractableDetectorComponent::OnAreaOverlapBegin);
	OnComponentEndOverlap.AddDynamic(this, &UInteractableDetectorComponent::OnAreaOverlapEnd);
}

TScriptInterface<IInteractable> UInteractableDetectorComponent::GetFirstInteractable()
{
	return OverlappedInteractables.IsEmpty() ? TScriptInterface<IInteractable>() : OverlappedInteractables[0];
}

void UInteractableDetectorComponent::OnAreaOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TScriptInterface<IInteractable> Interactable;
	if(IsValid(OtherActor) && OtherActor->Implements<UInteractable>())
	{
		Interactable = OtherActor;
	}
	else if(IsValid(OtherComponent) && OtherComponent->Implements<UInteractable>())
	{
		Interactable = OtherComponent;
	}

	if(Interactable)
	{
		OverlappedInteractables.Add(Interactable);

#if WITH_EDITORONLY_DATA
		GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Blue, FString::Printf(TEXT("Overlapped interactable %s"), *Interactable.GetObject()->GetName()));
#endif
	}
}

void UInteractableDetectorComponent::OnAreaOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	TScriptInterface<IInteractable> Interactable;
	if(IsValid(OtherActor) && OtherActor->Implements<UInteractable>())
	{
		Interactable = OtherActor;
	}
	else if(IsValid(OtherComponent) && OtherComponent->Implements<UInteractable>())
	{
		Interactable = OtherComponent;
	}

	if(Interactable)
	{
		for(int i = OverlappedInteractables.Num() - 1; i >= 0; i--)
		{
			if(OverlappedInteractables[i].GetObject() == Interactable.GetObject())
			{
				OverlappedInteractables.RemoveAt(i);

			#if WITH_EDITORONLY_DATA
				GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Blue, FString::Printf(TEXT("Ended overlap with interactable %s"), *Interactable.GetObject()->GetName()));
			#endif

				return;
			}
		}
	}
}
