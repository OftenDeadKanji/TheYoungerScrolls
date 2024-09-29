// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

class UInputMappingContextEx;
class AMainPlayer;

UCLASS()
class YOUNG_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMainPlayerController();

	virtual void Tick(float DeltaSeconds) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
protected:
	virtual void BeginPlay() override;
	void Authority_SpawnPlayer();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMainPlayer> PlayerClass;

	UPROPERTY(Replicated)
	TWeakObjectPtr<AMainPlayer> SpawnedPlayer;
};
