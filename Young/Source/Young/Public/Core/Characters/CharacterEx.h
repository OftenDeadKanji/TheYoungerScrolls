// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterMiscTypes.h"
#include "GameFramework/Character.h"
#include "CharacterEx.generated.h"

class AWeapon;
class UWeaponInstanceData;
class UInventoryComponent;

UCLASS()
class YOUNG_API ACharacterEx : public ACharacter
{
	GENERATED_BODY()

	friend class UKanjiklubAN_EnteredCombat;
	friend class UKanjiklubAN_DrawWeapon;

public:
	ACharacterEx();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual ELifetimeCondition AllowActorComponentToReplicate(const UActorComponent* ComponentToReplicate) const override;

	const FCharacterStats& GetCharacterStats() const;

	UFUNCTION(BlueprintCallable)
	void ToggleWeapon_RightHand(UWeaponInstanceData* WeaponData);
	//void EquipWeapon_LeftHand(UWeaponInstanceData* WeaponData);
	//void EquipWeapon_BothHands(UWeaponInstanceData* WeaponData);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnteredCombat);
	UPROPERTY(BlueprintAssignable)
	FOnEnteredCombat OnEnteredCombatDelegate;
protected:
	virtual void BeginPlay() override;
	virtual void Authority_StatsUpdateCallback();

	UFUNCTION(Server, Reliable)
	void Server_ToggleWeapon_RightHand(UWeaponInstanceData* WeaponData);
	void Authority_ToggleWeapon_RightHand(UWeaponInstanceData* WeaponData);

	void DrawnWeapon();
	void EnteredCombat();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UInventoryComponent> Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats", Replicated)
	FCharacterStats Stats;
	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float StatsUpdateRate = 0.3f;

	FTimerHandle StatsUpdateTimer;

	UPROPERTY(VisibleAnywhere)
	TWeakObjectPtr<AWeapon> EquippedWeaponRightHand;

	UPROPERTY(Replicated)
	EActionMode ActionMode;

	UPROPERTY(EditAnywhere)
	UAnimMontage* DrawSwordMontage;
};
