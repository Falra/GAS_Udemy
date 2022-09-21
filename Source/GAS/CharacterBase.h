// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
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

    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; };

    UFUNCTION(BlueprintCallable, Category = AbilitySystem)
    void AcquireAbility(TSubclassOf<class UGameplayAbility> AbilityToAcquire);
};
