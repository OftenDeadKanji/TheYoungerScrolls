// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/YN_UserWidget.h"
#include "YN_TextButtonWidget.generated.h"

class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class YOUNG_API UYN_TextButtonWidget : public UYN_UserWidget
{
	GENERATED_BODY()
	
public:

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> Button;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> Text;

};
