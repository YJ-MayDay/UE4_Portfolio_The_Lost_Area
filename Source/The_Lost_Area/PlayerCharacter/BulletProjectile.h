// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletProjectile.generated.h"

UCLASS()
class THE_LOST_AREA_API ABulletProjectile : public AActor
{
	GENERATED_BODY()
	

		UPROPERTY(VisibleAnywhere, Category = Projectile)
		class UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* Mesh;

	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	ABulletProjectile();

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	FORCEINLINE class UCapsuleComponent* GetCollisionComp() const { return CapsuleComp; }
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};
