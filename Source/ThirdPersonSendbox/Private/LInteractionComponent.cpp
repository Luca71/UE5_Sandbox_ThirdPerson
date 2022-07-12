// Fill out your copyright notice in the Description page of Project Settings.


#include "LInteractionComponent.h"
#include "LGameplayInterface.h"
#include <DrawDebugHelpers.h>
#include <Camera/CameraComponent.h>
#include "LCharacter.h"


// Sets default values for this component's properties
ULInteractionComponent::ULInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner = GetOwner();

	// Ray initialization
	FVector EyeLocation;
	FRotator EyeRotation;
	ALCharacter* Player = Cast<ALCharacter>(MyOwner);
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	float Radius = 30.0f;
	FCollisionShape Shape;
	Shape.SetSphere(Radius);

	FVector TraceStart = Player->GetCameraLocation(); //CameraComp->GetComponentLocation();
	FVector TraceEnd = TraceStart + (Player->GetCameraRotation().Vector() * 5000);

	FCollisionObjectQueryParams ObjParams;
	ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
	ObjParams.AddObjectTypesToQuery(ECC_Pawn);

	FHitResult Hit;
	// returns true if we got to a blocking hit
	if (GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjParams, Shape))
	{
		TraceEnd = Hit.ImpactPoint;

		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			if (HitActor->Implements<ULGameplayInterface>())
			{
				APawn* MyPawn = Cast<APawn>(MyOwner);
				ILGameplayInterface::Execute_Interact(HitActor, MyPawn);
			}
		}
	}

	DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, FColor::Green, false, 0.5f, 0, 1.0f);

}
