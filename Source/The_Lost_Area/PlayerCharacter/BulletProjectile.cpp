// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletProjectile.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"

void ABulletProjectile::BeginPlay()
{
	Super::BeginPlay();
	CapsuleComp->OnComponentHit.AddDynamic(this, &ABulletProjectile::OnHit);
}

// Sets default values
ABulletProjectile::ABulletProjectile()
{
	CapsuleComp = CreateDefaultSubobject <UCapsuleComponent>(TEXT("CapsuleComp"));
	CapsuleComp->InitCapsuleSize(15.f,15.f);
	CapsuleComp->BodyInstance.SetCollisionProfileName("Projectile");

	CapsuleComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CapsuleComp->CanCharacterStepUpOn = ECB_No;

	RootComponent = CapsuleComp;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	Mesh->SetupAttachment(CapsuleComp);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CapsuleComp;
	ProjectileMovement->InitialSpeed = 5000.f;
	ProjectileMovement->MaxSpeed = 5000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

	InitialLifeSpan = 3.0f;

}

void ABulletProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("OnHit Check"));
	if (OtherActor != nullptr && OtherActor != this && OtherComp != nullptr && OtherComp->IsSimulatingPhysics())
	{

	}
}
