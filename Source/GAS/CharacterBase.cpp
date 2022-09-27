// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"

#include "AbilitySystemComponent.h"
#include "AIController.h"
#include "AttributeSetBase.h"
#include "BrainComponent.h"

ACharacterBase::ACharacterBase()
{
    PrimaryActorTick.bCanEverTick = true;

    AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
    AttributeSet = CreateDefaultSubobject<UAttributeSetBase>("AttributeSet");
    TeamId = 255;
}

void ACharacterBase::BeginPlay()
{
    Super::BeginPlay();

    check(AttributeSet);
    AttributeSet->OnHealthChanged.AddDynamic(this, &ACharacterBase::OnHealthChanged);

    AutoDetermineTeamIDByControllerType();
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

    if (Health <= 0.0f && !bIsDead)
    {
        bIsDead = true;
        Dead();
        BlueprintDie();
    }
}

bool ACharacterBase::IsOtherHostile(ACharacterBase* Other)
{
    return TeamId != Other->TeamId;
}

void ACharacterBase::AutoDetermineTeamIDByControllerType()
{
    if (GetController() && GetController()->IsPlayerController())
    {
        TeamId = 0;
    }
}

void ACharacterBase::Dead()
{
    APlayerController* PC = Cast<APlayerController>(GetController());
    if (PC)
    {
        PC->DisableInput(PC);
    }

    const AAIController* AIC = Cast<AAIController>(GetController());
    if (AIC)
    {
        AIC->GetBrainComponent()->StopLogic("Dead");
    }
}
