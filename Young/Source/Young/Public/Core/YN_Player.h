// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "YN_Player.generated.h"

class UCameraComponent;

UCLASS()
class YOUNG_API AYN_Player : public ACharacter
{
	GENERATED_BODY()

public:
	AYN_Player();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void Move(const FVector2D& Direction);
	UFUNCTION(BlueprintCallable)
	void LookAround(const FVector2D& Direction);
	
	void Jump() override;
	
	UFUNCTION(BlueprintCallable)
	void StartCrouch();
	UFUNCTION(BlueprintCallable)
	void StopCrouch();
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Components")
	UCameraComponent* Camera{};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings")
	FVector2D LookUpRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings")
	float LookAroundSpeed{ 1.0f };
};
