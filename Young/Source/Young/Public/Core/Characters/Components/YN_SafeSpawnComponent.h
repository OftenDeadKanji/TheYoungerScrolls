// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "YN_SafeSpawnComponent.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnSafeSpawned);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class YOUNG_API UYN_SafeSpawnComponent : public UCapsuleComponent
{
	GENERATED_BODY()

public:
	UYN_SafeSpawnComponent();

	FOnSafeSpawned OnSafeSpawned;

	void StartSafeSpawn(UPrimitiveComponent* UpdatedComponent);
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSafeAreaEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void EndSafeSpawn();

	TWeakObjectPtr<UPrimitiveComponent> OwnerUpdatedComponent;

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere)
	bool bLogOverlappingActors = true;
#endif
};
