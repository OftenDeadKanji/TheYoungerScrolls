// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "YN_InteractionDetectorComponent.generated.h"

class UYN_InteractionAreaComponent;
class IYN_Interactable;

UCLASS()
class YOUNG_API UYN_InteractionDetectorComponent : public UCapsuleComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	UYN_InteractionAreaComponent* GetFirstInteractableArea() const;
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnAreaOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnAreaOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

	TArray<UYN_InteractionAreaComponent*> OverlappedInteractableAreas;
};
