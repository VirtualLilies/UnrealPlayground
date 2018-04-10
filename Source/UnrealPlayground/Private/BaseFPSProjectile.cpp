// Copyright C 2018 Tomasz Figas

#include "BaseFPSProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABaseFPSProjectile::ABaseFPSProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Use sphere as simple collision representation.
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

	// Set sphere collision radius.
	CollisionComp->InitSphereRadius(15.0f);

	// Set collision component as root comp.
	RootComponent = CollisionComp;

	// Setup static mesh comp.
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	StaticMeshComp->SetupAttachment(CollisionComp);

	// Use this component to drive projectile's movement.
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComp->SetUpdatedComponent(CollisionComp); // Assign the component we move and update.

	// These are default in-engine variables and not created manually.
	ProjectileMovementComp->InitialSpeed = 3000.0f;
	ProjectileMovementComp->MaxSpeed = 3000.0f;
	ProjectileMovementComp->bRotationFollowsVelocity = true;
	ProjectileMovementComp->bShouldBounce = false;

}

// Called when the game starts or when spawned
void ABaseFPSProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseFPSProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Function that initializes the projectile's velocity in the shoot direction.
void ABaseFPSProjectile::FireInDirection(const FVector & ShootDirection)
{
	ProjectileMovementComp->Velocity = ShootDirection * ProjectileMovementComp->InitialSpeed; // You only needed to supply a launch direction because the projectile's speed is defined by ProjectileMovementComponent.
}

