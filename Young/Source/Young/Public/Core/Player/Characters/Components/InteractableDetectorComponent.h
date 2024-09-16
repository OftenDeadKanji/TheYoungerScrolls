// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "InteractableDetectorComponent.generated.h"

class IInteractable;

UCLASS()
class YOUNG_API UInteractableDetectorComponent : public UCapsuleComponent
{
	GENERATED_BODY()

public:
	virtual void PostLoad() override;
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	TScriptInterface<IInteractable> GetFirstInteractable();
protected:
	UFUNCTION()
	void OnAreaOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnAreaOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

	TArray<TScriptInterface<IInteractable>> OverlappedInteractables;

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category = "Config|Debug")
	bool bShowDebugMessages = false;
#endif
};
