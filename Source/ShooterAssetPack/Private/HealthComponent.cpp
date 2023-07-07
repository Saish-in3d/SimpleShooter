// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	
	GetWorld()->GetTimerManager().SetTimer(WallTimer, this, &UHealthComponent::ReduceTimeHealth, 2.f, true);

	GetOwner();
}

void UHealthComponent::CheckHealth()
{
	//GetOwner()->ChangeColor
	if (Health <= 0.f)
	{
		GetOwner()->Destroy();
	}
}

void UHealthComponent::ReduceTimeHealth()
{
	Health -= 10.f;
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CheckHealth();
	
}

void UHealthComponent::ReduceHealth(float Damage)
{
	Health -= Damage;
}

float UHealthComponent::GetAlpha()
{
	return 1.f - (Health / MaxHealth);
}

