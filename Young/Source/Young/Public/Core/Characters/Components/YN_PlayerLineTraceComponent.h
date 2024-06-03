// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "YN_PlayerLineTraceComponent.generated.h"

class UCameraComponent;
class UPrimitiveComponent;

class IYN_Interactable;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class YOUNG_API UYN_PlayerLineTraceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UYN_PlayerLineTraceComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	const TWeakObjectPtr<AActor>& GetHitActor() const;

	const TWeakObjectPtr<UPrimitiveComponent>& GetHitComponent() const;

	const TScriptInterface<IYN_Interactable>& GetHitInteractable() const;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line trace settings")
	float Range = 200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line trace settings")
	TEnumAsByte<ECollisionChannel> TraceChannel;

	TWeakObjectPtr<UCameraComponent> PlayerCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hit actor data")
	TWeakObjectPtr<AActor> HitActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hit actor data")
	TWeakObjectPtr<UPrimitiveComponent> HitComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hit actor data")
	TScriptInterface<IYN_Interactable> HitInteractable;

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere)
	bool bLogOnScreen = false;
	UPROPERTY(EditAnywhere)
	bool bDebugDraw = false;
#endif
};
