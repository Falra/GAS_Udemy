// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeSetBase.h"

#include "GameplayEffectExtension.h"
#include "GameplayEffectTypes.h"

UAttributeSetBase::UAttributeSetBase() :
    Health(200.0f), MaxHealth(200.0f),
    Mana(100.0f), MaxMana(150.0f),
    Strength(250.0f), MaxStrength(250.0f)
{
}

void UAttributeSetBase::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    //Super::PostGameplayEffectExecute(Data);

    static const FName NAME_Health = GET_MEMBER_NAME_CHECKED(UAttributeSetBase, Health);
    static const FName NAME_Mana = GET_MEMBER_NAME_CHECKED(UAttributeSetBase, Mana);
    static const FName NAME_Strength = GET_MEMBER_NAME_CHECKED(UAttributeSetBase, Strength);
    
    
    if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<FProperty>(StaticClass(), NAME_Health))
    {
        Health.SetCurrentValue(FMath::Clamp(Health.GetCurrentValue(), 0.0f, MaxHealth.GetCurrentValue()));
        Health.SetBaseValue(FMath::Clamp(Health.GetBaseValue(), 0.0f, MaxHealth.GetCurrentValue()));
        
        OnHealthChanged.Broadcast(Health.GetCurrentValue(), MaxHealth.GetCurrentValue());
    }

    if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<FProperty>(StaticClass(), NAME_Mana))
    {
        Mana.SetCurrentValue(FMath::Clamp(Mana.GetCurrentValue(), 0.0f, MaxMana.GetCurrentValue()));
        Mana.SetBaseValue(FMath::Clamp(Mana.GetBaseValue(), 0.0f, MaxMana.GetCurrentValue()));
        
        OnManaChanged.Broadcast(Mana.GetCurrentValue(), MaxMana.GetCurrentValue());
    }

    if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<FProperty>(StaticClass(), NAME_Strength))
    {
        Strength.SetCurrentValue(FMath::Clamp(Strength.GetCurrentValue(), 0.0f, MaxStrength.GetCurrentValue()));
        Strength.SetBaseValue(FMath::Clamp(Strength.GetBaseValue(), 0.0f, MaxStrength.GetCurrentValue()));
        
        OnStrengthChanged.Broadcast(Strength.GetCurrentValue(), MaxStrength.GetCurrentValue());
    }
}
