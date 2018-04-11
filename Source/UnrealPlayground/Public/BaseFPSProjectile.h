// Copyright C 2018 Tomasz Figas

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseFPSProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UStaticMeshComponent;

UCLASS()
class UNREALPLAYGROUND_API ABaseFPSProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseFPSProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Function that initializes the projectile's velocity in the shoot direction.
	void FireInDirection(const FVector& ShootDirection);

	// Function that is called when the projectile hits something.
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Sphere collision component.
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
		USphereComponent* CollisionComp;

	// Projectile movement comp.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
		UProjectileMovementComponent* ProjectileMovementComp;

	// Projectile's static mesh component.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* StaticMeshComp;

};
