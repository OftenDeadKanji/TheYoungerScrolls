// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidgetEx.generated.h"

UCLASS()
class YOUNG_API UUserWidgetEx : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	bool IsBlockingPawnInput() const;

protected:
	UPROPERTY(EditAnywhere)
	bool bBlockPawnInput = false;
};
