// Fill out your copyright notice in the Description page of Project Settings.


#include "LAttributeComponent.h"

// Sets default values for this component's properties
ULAttributeComponent::ULAttributeComponent() : HealthMax(100)
{
	Health = HealthMax;
}


bool ULAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;

	OnHealthChange.Broadcast(nullptr, this, Health, Delta);

	return true;
}


