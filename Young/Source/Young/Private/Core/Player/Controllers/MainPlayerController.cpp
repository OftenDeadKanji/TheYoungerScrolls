// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "Core/Player/Controllers/MainPlayerController.h"

#include "Common/Spawning/SpawnArea.h"
#include "Core/Player/Characters/MainPlayer.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

AMainPlayerController::AMainPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	bReplicates = true;
}

void AMainPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AMainPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMainPlayerController, SpawnedPlayer);
}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(HasAuthority())
	{
		Authority_SpawnPlayer();
	}
}

void AMainPlayerController::Authority_SpawnPlayer()
{
	UWorld* World = GetWorld();

	ASpawnArea* SpawnArea = Cast<ASpawnArea>(UGameplayStatics::GetActorOfClass(World, ASpawnArea::StaticClass()));
	if(SpawnArea == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Red, FString::Printf(TEXT("SpawnArea not found!")));
		return;
	}

	FTransform SpawnTransform(SpawnArea->GetRandomPointInArea());
	SpawnedPlayer = World->SpawnActorDeferred<AMainPlayer>(PlayerClass, SpawnTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	Possess(SpawnedPlayer.Get());
	SpawnedPlayer->SetOwner(this);

	UGameplayStatics::FinishSpawningActor(SpawnedPlayer.Get(), SpawnTransform);
}
