// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

UCLASS()
class GAS_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
    ACharacterBase();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AbilitySystem)
    class UAbilitySystemComponent* AbilitySystemComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AbilitySystem)
    class UAttributeSetBase* AttributeSet;
    
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; };

    UFUNCTION(BlueprintCallable, Category = AbilitySystem)
    void AcquireAbility(TSubclassOf<class UGameplayAbility> AbilityToAcquire);

    UPROPERTY(EditAnywhere, Category = AbilitySystem)
    TArray<TSubclassOf<UGameplayAbility>> AbilitiesToAcquire;
        
    UFUNCTION(BlueprintCallable, Category = AbilitySystem)
    void AcquireAbilities();
    
    UFUNCTION()
    void OnHealthChanged(float Health, float MaxHealth);

    UFUNCTION(BlueprintImplementableEvent, Category = AbilitySystem, meta = (DisplayName="OnHealthChanged"))
    void BlueprintOnHealthChanged(float Health, float MaxHealth);

    UFUNCTION()
    void OnManaChanged(float Mana, float MaxMana);

    UFUNCTION(BlueprintImplementableEvent, Category = AbilitySystem, meta = (DisplayName="OnManaChanged"))
    void BlueprintOnManaChanged(float Mana, float MaxMana);

    UFUNCTION()
    void OnStrengthChanged(float Strength, float MaxStrength);

    UFUNCTION(BlueprintImplementableEvent, Category = AbilitySystem, meta = (DisplayName="OnStrengthChanged"))
    void BlueprintOnStrengthChanged(float Strength, float MaxStrength);

    UFUNCTION(BlueprintImplementableEvent, Category = AbilitySystem, meta = (DisplayName="Die"))
    void BlueprintDie();

    UFUNCTION(BlueprintCallable, Category = AbilitySystem)
    bool IsOtherHostile(ACharacterBase* Other);

    UFUNCTION(BlueprintCallable, Category = AbilitySystem)
    void AddGameplayTag(const FGameplayTag& TagToAdd);
    
    UFUNCTION(BlueprintCallable, Category = AbilitySystem)
    void RemoveGameplayTag(const FGameplayTag& TagToRemove);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilitySystem)
    FGameplayTag FullHealthTag;

    UFUNCTION(BlueprintCallable, Category = AbilitySystem)
    void HitStun(float StunTime);
protected:
    bool bIsDead = false;
    uint8 TeamId;
    void AutoDetermineTeamIDByControllerType();
    void Dead();
    void DisableInputControl();
    void EnableInputControl();
    void AddAbilityToUI(TSubclassOf<class UGameplayAbilityBase> AbilityClass);
};
