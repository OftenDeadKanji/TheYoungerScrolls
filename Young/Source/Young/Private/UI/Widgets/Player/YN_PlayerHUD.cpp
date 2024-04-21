// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.


#include "UI/Widgets/Player/YN_PlayerHUD.h"
#include "Components/TextBlock.h"

void UYN_PlayerHUD::UpdateHealth(float CurrentHealth, float MaxHealth)
{
	FFormatOrderedArguments Args;
	Args.Add(CurrentHealth);
	Args.Add(MaxHealth);

	FText Text = FText::Format(INVTEXT("{0} / {1}"), Args);
	TextHealth->SetText(Text);
}

void UYN_PlayerHUD::UpdateStamina(float CurrentStamina, float MaxStamina)
{
	FFormatOrderedArguments Args;
	Args.Add(CurrentStamina);
	Args.Add(MaxStamina);

	FText Text = FText::Format(INVTEXT("{0} / {1}"), Args);
	TextStamina->SetText(Text);
}

void UYN_PlayerHUD::UpdateMana(float CurrentMana, float MaxMana)
{
	FFormatOrderedArguments Args;
	Args.Add(CurrentMana);
	Args.Add(MaxMana);

	FText Text = FText::Format(INVTEXT("{0} / {1}"), Args);
	TextMana->SetText(Text);
}
