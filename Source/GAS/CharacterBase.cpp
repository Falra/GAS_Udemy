// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"

#include "AbilitySystemComponent.h"
#include "AttributeSetBase.h"

ACharacterBase::ACharacterBase()
{
    PrimaryActorTick.bCanEverTick = true;

    AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
    AttributeSet = CreateDefaultSubobject<UAttributeSetBase>("AttributeSet");
}

void ACharacterBase::BeginPlay()
{
    Super::BeginPlay();

    check(AttributeSet);
    AttributeSet->OnHealthChanged.AddDynamic(this, &ACharacterBase::OnHealthChanged);
}

void ACharacterBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACharacterBase::AcquireAbility(TSubclassOf<UGameplayAbility> AbilityToAcquire)
{
    if (!AbilitySystemComponent) return;

    if (HasAuthority() && AbilityToAcquire)
    {
        AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(AbilityToAcquire));
    }
    AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void ACharacterBase::OnHealthChanged(float Health, float MaxHealth)
{
    BlueprintOnHealthChanged(Health, MaxHealth);
}
