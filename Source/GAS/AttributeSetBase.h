// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AttributeSetBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAttributeChangedDelegate, float, Value, float, MaxValue);

/**
 * 
 */
UCLASS()
class GAS_API UAttributeSetBase : public UAttributeSet
{
    GENERATED_BODY()
public:
    UAttributeSetBase();
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)
    FGameplayAttributeData Health;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)
    FGameplayAttributeData MaxHealth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)
    FGameplayAttributeData Mana;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)
    FGameplayAttributeData MaxMana;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)
    FGameplayAttributeData Strength;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)
    FGameplayAttributeData MaxStrength;
    
    FOnAttributeChangedDelegate OnHealthChanged;
    FOnAttributeChangedDelegate OnManaChanged;
    FOnAttributeChangedDelegate OnStrengthChanged;
        
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
};
