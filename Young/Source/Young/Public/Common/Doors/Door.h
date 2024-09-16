// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "DoorMiscTypes.h"
#include "Animation/SkeletalMeshActor.h"
#include "Common/Interactable.h"
#include "Door.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDoorStateChanged, EDoorState, DoorState);

UCLASS()
class YOUNG_API ADoor : public ASkeletalMeshActor, public IInteractable
{
	GENERATED_BODY()

public:
	ADoor();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

#pragma region IInteractable
	virtual void Authority_OnUsePressed_Implementation(AMainPlayerController* PlayerController) override;

	virtual float GetMaxFacingHalfAngle_Implementation() const override;

	virtual bool IsInteractionByServerRequired_Implementation() const override;
#pragma endregion

	EDoorState GetState() const;

	void OpeningAnimationEnded();
	void ClosingAnimationEnded();

	FOnDoorStateChanged OnStateChanged;
protected:
	UFUNCTION()
	virtual void OnRep_State();

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, ReplicatedUsing = "OnRep_State")
	EDoorState State;
};
