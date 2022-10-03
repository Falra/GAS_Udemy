#pragma once

#include "CoreMinimal.h"
#include "AbilityTypes.generated.h"

UENUM(BlueprintType)
enum class EAbilityCostType : uint8
{
    Health,
    Mana,
    Strength
};

USTRUCT(BlueprintType)
struct FGameplayAbilityInfo
{
    GENERATED_BODY();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilitySystem")
    float CooldownDuration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilitySystem")
    float Cost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilitySystem")
    EAbilityCostType CostType;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilitySystem")
    UMaterialInstance* UIMaterial;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilitySystem")
    TSubclassOf<class UGameplayAbilityBase> AbilityClass;

    FGameplayAbilityInfo()
    : CooldownDuration(0.0f),
          Cost(0.0f),
          CostType(EAbilityCostType::Mana),
          UIMaterial(nullptr),
          AbilityClass(nullptr)
    {
        
    }

    FGameplayAbilityInfo(float CooldownDuration, float Cost, EAbilityCostType CostType, UMaterialInstance* UIMaterial,
        const TSubclassOf<UGameplayAbilityBase>& AbilityClass)
        : CooldownDuration(CooldownDuration),
          Cost(Cost),
          CostType(CostType),
          UIMaterial(UIMaterial),
          AbilityClass(AbilityClass)
    {
    }
};
