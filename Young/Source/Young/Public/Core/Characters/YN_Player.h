// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/Characters/YN_Character.h"
#include "YN_Player.generated.h"

class UYN_InteractionDetectorComponent;
class UCameraComponent;
class USpringArmComponent;

class UYN_InventoryWidget;
class UYN_PlayerHUD;
class UYN_PlayerLineTraceComponent;
class UYN_SafeSpawnComponent;
class UYN_UserInterfaceSubsystem;

UCLASS()
class YOUNG_API AYN_Player : public AYN_Character
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

	UFUNCTION(BlueprintCallable)
	void InteractPrimary();
	UFUNCTION(BlueprintCallable)
	void InteractSecondary();

	UFUNCTION(BlueprintCallable)
	void ToggleInventory();
#pragma endregion

protected:
	virtual void BeginPlay() override;

	UFUNCTION(Server, Reliable)
	void Server_InteractPrimary(UObject* InteractableObject);
	void Server_InteractPrimary_Implementation(UObject* InteractableObject);

	UFUNCTION()
	void OnSafeSpawn();

	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArm;
	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<UCameraComponent> Camera;
	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<UYN_InteractionDetectorComponent> InteractionDetector;
	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<UYN_SafeSpawnComponent> SafeSpawnComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings")
	FVector2D LookUpRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings")
	FVector2D LookAroundSpeed = { 1.0, 1.0 };

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UYN_PlayerHUD> PlayerHUDClass;
	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UYN_PlayerHUD> PlayerHUD;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UYN_InventoryWidget> InventoryWidgetClass;
	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UYN_InventoryWidget> InventoryWidget;

	TWeakObjectPtr<UYN_UserInterfaceSubsystem> UISubsystem;
};
