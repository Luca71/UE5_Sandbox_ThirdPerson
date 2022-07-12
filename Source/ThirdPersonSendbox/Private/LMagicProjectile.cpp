// Fill out your copyright notice in the Description page of Project Settings.


#include "LMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "LAttributeComponent.h"

// Sets default values
ALMagicProjectile::ALMagicProjectile() : DamageAmount(20.0f), Velocity(1000.0f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ALMagicProjectile::OnActorOverlap);
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = Velocity;
	MovementComp->ProjectileGravityScale = 0;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
}

void ALMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		ULAttributeComponent* AttributeComp = Cast<ULAttributeComponent>(OtherActor->GetComponentByClass(ULAttributeComponent::StaticClass()));
		if (AttributeComp)
		{
			AttributeComp->ApplyHealthChange(-DamageAmount);
			Destroy();
		}
	}
}

// Called when the game starts or when spawned
void ALMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

