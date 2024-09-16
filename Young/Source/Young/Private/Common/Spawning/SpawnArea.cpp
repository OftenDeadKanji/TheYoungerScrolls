// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "Common/Spawning/SpawnArea.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ASpawnArea::ASpawnArea()
{
	Area = CreateDefaultSubobject<UBoxComponent>(TEXT("Area"));
	RootComponent = Area;
}

FVector ASpawnArea::GetRandomPointInArea() const
{
	if (IsValid(Area))
	{
		return UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(), Area->GetScaledBoxExtent());
	}

	return GetActorLocation();
}
