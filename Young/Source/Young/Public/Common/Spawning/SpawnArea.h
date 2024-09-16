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

	FVector GetRandomPointInArea() const;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> Area;
};
