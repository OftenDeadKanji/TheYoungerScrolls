// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "Common/Spawning/SpawnArea.h"

#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

ASpawnArea::ASpawnArea()
{
	Area = CreateDefaultSubobject<UBoxComponent>(TEXT("Area"));
	RootComponent = Area;
}

void ASpawnArea::BeginPlay()
{
	Super::BeginPlay();

	FRotator Rotation = GetActorRotation();
	if(Rotation.IsNearlyZero() == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("Rotation of %s must be Zero!"), *GetName());

		SetActorRotation(FRotator::ZeroRotator);
	}
}

FVector ASpawnArea::GetRandomSpawnLocation(float PawnHalfHeight, bool bTryToAdjustLocation) const
{
	if (IsValid(Area))
	{
		FVector SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(), Area->GetScaledBoxExtent());

		if(bTryToAdjustLocation == false)
		{
			return SpawnLocation;
		}

		FVector TopPoint = Area->GetComponentLocation() + FVector(0.0f, 0.0f, Area->GetScaledBoxExtent().Z);
		FVector TraceStart = FVector(SpawnLocation.X, SpawnLocation.Y, TopPoint.Z);

		FVector BottomPoint = Area->GetComponentLocation() - FVector(0.0f, 0.0f, Area->GetScaledBoxExtent().Z);
		FVector TraceEnd = FVector(SpawnLocation.X, SpawnLocation.Y, BottomPoint.Z);

		UWorld* World = GetWorld();
		check(World);

		FHitResult Hit;
		if(World->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility))
		{
			return Hit.Location + FVector(0.0f, 0.0f, PawnHalfHeight);
		}

		return TraceEnd + FVector(0.0f, 0.0f, PawnHalfHeight);
	}

	return GetActorLocation();
}
