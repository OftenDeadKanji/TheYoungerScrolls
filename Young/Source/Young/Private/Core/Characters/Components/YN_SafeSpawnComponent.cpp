// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.


#include "Core/Characters/Components/YN_SafeSpawnComponent.h"

#include "Core/Characters/YN_Player.h"
#include "Utilities/DebugMacros.h"

UYN_SafeSpawnComponent::UYN_SafeSpawnComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UYN_SafeSpawnComponent::StartSafeSpawn(UPrimitiveComponent* UpdatedComponent)
{
	OwnerUpdatedComponent = UpdatedComponent;
	OwnerUpdatedComponent->SetCollisionProfileName(TEXT("Ghost"));

	OnComponentEndOverlap.AddDynamic(this, &UYN_SafeSpawnComponent::OnSafeAreaEndOverlap);
}

void UYN_SafeSpawnComponent::BeginPlay()
{
	Super::BeginPlay();

	IgnoreActorWhenMoving(GetOwner(), true);
}

void UYN_SafeSpawnComponent::OnSafeAreaEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	TArray<UPrimitiveComponent*> OverlappingComps;
	GetOverlappingComponents(OverlappingComps);

	if (OverlappingComps.Num() == 0)
	{
		EndSafeSpawn();
	}

#if WITH_EDITORONLY_DATA
	if (bLogOverlappingActors && OverlappingComps.Num() != 0)
	{
		FString OverlappingInfo;
		for (auto* Component : OverlappingComps)
		{
			FStringFormatOrderedArguments Args;
			Args.Add(Component->GetOwner()->GetName());
			Args.Add(Component->GetName());

			OverlappingInfo += FString::Format(TEXT("\tActor = {0} Component = {1}\n"), Args);
		}
		UE_LOG(LogTemp, Display, TEXT("Still overlapping with: \n%s"), *OverlappingInfo);
	}
#endif
}

void UYN_SafeSpawnComponent::EndSafeSpawn()
{
	OwnerUpdatedComponent->SetCollisionProfileName(TEXT("Pawn"));
	OnSafeSpawned.ExecuteIfBound();
}
