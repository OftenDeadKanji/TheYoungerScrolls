// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnArea.generated.h"

class UBoxComponent;

UCLASS()
class YOUNG_API ASpawnArea : public AActor
{
	GENERATED_BODY()

public:
	ASpawnArea();
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	FVector GetRandomSpawnLocation(float PawnHalfHeight, bool bTryToAdjustLocation = false) const;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> Area;
};
