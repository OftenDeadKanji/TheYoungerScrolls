// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "YN_Player.generated.h"

class UCameraComponent;

class UYN_SafeSpawnComponent;

UCLASS()
class YOUNG_API AYN_Player : public ACharacter
{
	GENERATED_BODY()

public:
	AYN_Player();

	virtual void Tick(float DeltaTime) override;

#pragma region Inputs
	UFUNCTION(BlueprintCallable)
	void Move(const FVector2D& Direction);
	UFUNCTION(BlueprintCallable)
	void LookAround(const FVector2D& Direction);
	
	void Jump() override;
	
	UFUNCTION(BlueprintCallable)
	void StartCrouch();
	UFUNCTION(BlueprintCallable)
	void StopCrouch();
#pragma endregion
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSafeSpawn();

	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<UCameraComponent> Camera;
	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<UYN_SafeSpawnComponent> SafeSpawnComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings")
	FVector2D LookUpRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings")
	float LookAroundSpeed = 1.0f;
};
