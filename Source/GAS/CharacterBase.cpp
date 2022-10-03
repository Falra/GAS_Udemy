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
    AttributeSet->OnManaChanged.AddDynamic(this, &ACharacterBase::OnManaChanged);
    AttributeSet->OnStrengthChanged.AddDynamic(this, &ACharacterBase::OnStrengthChanged);

    AutoDetermineTeamIDByControllerType();
    AddGameplayTag(FullHealthTag);
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
    if (Health == MaxHealth)
    {
        AddGameplayTag(FullHealthTag);
    }
    else
    {
        RemoveGameplayTag(FullHealthTag);
    }
    
    BlueprintOnHealthChanged(Health, MaxHealth);

    if (Health <= 0.0f && !bIsDead)
    {
        bIsDead = true;
        Dead();
        BlueprintDie();
    }
}

void ACharacterBase::OnManaChanged(float Mana, float MaxMana)
{
    BlueprintOnManaChanged(Mana, MaxMana);
}

void ACharacterBase::OnStrengthChanged(float Strength, float MaxStrength)
{
    BlueprintOnStrengthChanged(Strength, MaxStrength);
}

bool ACharacterBase::IsOtherHostile(ACharacterBase* Other)
{
    return TeamId != Other->TeamId;
}

void ACharacterBase::AddGameplayTag(const FGameplayTag& TagToAdd)
{
    AbilitySystemComponent->AddLooseGameplayTag(TagToAdd);
    AbilitySystemComponent->SetTagMapCount(TagToAdd, 1);
}

void ACharacterBase::RemoveGameplayTag(const FGameplayTag& TagToRemove)
{
    AbilitySystemComponent->RemoveLooseGameplayTag(TagToRemove);
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
    DisableInputControl();
}

void ACharacterBase::HitStun(float StunTime)
{
    DisableInputControl();
    FTimerHandle StunTimerHandle;
    GetWorldTimerManager().SetTimer(StunTimerHandle, this, &ACharacterBase::EnableInputControl, StunTime);
    
}

void ACharacterBase::DisableInputControl()
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

void ACharacterBase::EnableInputControl()
{
    APlayerController* PC = Cast<APlayerController>(GetController());
    if (PC)
    {
        PC->EnableInput(PC);
    }

    const AAIController* AIC = Cast<AAIController>(GetController());
    if (AIC)
    {
        AIC->GetBrainComponent()->RestartLogic();
    }
}
