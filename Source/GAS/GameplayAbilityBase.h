// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityTypes.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbilityBase.generated.h"

/**
 * 
 */
UCLASS()
class GAS_API UGameplayAbilityBase : public UGameplayAbility
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilitySystem)
    UMaterialInstance* UIMaterial;

    UFUNCTION(BlueprintCallable, Category = AbilitySystem)
    FGameplayAbilityInfo GetAbilityInfo() const;
};
