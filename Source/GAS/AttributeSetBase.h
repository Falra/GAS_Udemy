// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AttributeSetBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedDelegate, float, Health, float, MaxHealth);

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

    FOnHealthChangedDelegate OnHealthChanged;
    
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
};
