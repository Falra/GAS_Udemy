// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeSetBase.h"

#include "GameplayEffectExtension.h"
#include "GameplayEffectTypes.h"

UAttributeSetBase::UAttributeSetBase() : Health(200.0f), MaxHealth(200.0f)
{
}

void UAttributeSetBase::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    //Super::PostGameplayEffectExecute(Data);

    static const FName NAME_Health = GET_MEMBER_NAME_CHECKED(UAttributeSetBase, Health);
    
    if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<FProperty>(StaticClass(), NAME_Health))
    {
        UE_LOG(LogTemp, Warning, TEXT("Ouch I took some damage, now my health is %f"), Health.GetCurrentValue());
        OnHealthChanged.Broadcast(Health.GetCurrentValue(), MaxHealth.GetCurrentValue());
    }
}
