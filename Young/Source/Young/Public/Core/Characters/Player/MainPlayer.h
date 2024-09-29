// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/Characters/CharacterEx.h"
#include "MainPlayer.generated.h"

class UMainPlayerUIComponent;
class UInteractableDetectorComponent;
class UInputMappingContextEx;
class UCameraComponent;
class USpringArmComponent;
struct FInputActionValue;

UCLASS()
class YOUNG_API AMainPlayer : public ACharacterEx
{
	GENERATED_BODY()

public:
	AMainPlayer();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaSeconds) override;
protected:
	virtual void BeginPlay() override;

#pragma region Inputs
	UFUNCTION(BlueprintCallable)
	void Move(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void LookAround(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void Use(const FInputActionValue& Value);

#pragma endregion

	UFUNCTION(Server, Reliable)
	void Server_Use();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCameraComponent> Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UInteractableDetectorComponent> InteractableDetector;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UMainPlayerUIComponent> UIComponent;

	TWeakObjectPtr<UCharacterMovementComponent> Movement;

	FVector CurrentMovementDirection;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float CharacterMovementChangeSpeed = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float LookAroundSpeed = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FVector2D LookUpRange;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContextEx> MainPlayerInputMappingContext;
};
