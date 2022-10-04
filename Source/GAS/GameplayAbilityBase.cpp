// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilityBase.h"

FGameplayAbilityInfo UGameplayAbilityBase::GetAbilityInfo() const
{
    float CooldownDuration = 0.0f;
    float Cost = 0.0f;
    EAbilityCostType CostType = EAbilityCostType::None;

    const UGameplayEffect* CooldownEffect = GetCooldownGameplayEffect();
    if (CooldownEffect)
    {
        CooldownEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(1, CooldownDuration);
    }

    const UGameplayEffect* CostEffect = GetCostGameplayEffect();
    if (CostEffect && CostEffect->Modifiers.Num() > 0)
    {
        const FGameplayModifierInfo EffectCostInfo = CostEffect->Modifiers[0];
        EffectCostInfo.ModifierMagnitude.GetStaticMagnitudeIfPossible(1, Cost);
        const FGameplayAttribute CostAttr = EffectCostInfo.Attribute;
        const FString AttributeName = CostAttr.AttributeName;
        if (AttributeName == "Health")
        {
            CostType = EAbilityCostType::Health;
        }
        else if (AttributeName == "Mana")
        {
            CostType = EAbilityCostType::Mana;
        }
        else if (AttributeName == "Strength")
        {
            CostType = EAbilityCostType::Strength;
        }
    }
    return FGameplayAbilityInfo(CooldownDuration, Cost, CostType, UIMaterial, GetClass());
}
