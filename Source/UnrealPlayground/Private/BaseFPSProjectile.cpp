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

	// Bind OnHit event.
	CollisionComp->OnComponentHit.AddDynamic(this, &ABaseFPSProjectile::OnHit);

	// Set sphere collision radius.
	CollisionComp->InitSphereRadius(5.0f);

	// Setup projectiles collision based on our custom collision profiles.
	CollisionComp->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));

	// Set collision component as root comp.
	RootComponent = CollisionComp;

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Setup static mesh comp.
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	StaticMeshComp->SetupAttachment(CollisionComp);
	StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Use this component to drive projectile's movement.
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComp->UpdatedComponent = CollisionComp; // Assign the component we move and update.

	// These are default in-engine variables and not created manually.
	ProjectileMovementComp->InitialSpeed = 5000.0f;
	ProjectileMovementComp->MaxSpeed = 5000.0f;
	ProjectileMovementComp->bRotationFollowsVelocity = true;
	ProjectileMovementComp->bShouldBounce = true;
	ProjectileMovementComp->ProjectileGravityScale = 0.0f;

	// Destroy after given seconds.
	InitialLifeSpan = 3.0f;

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

// Function that is called when projectile hits something.
void ABaseFPSProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	// TODO the function doesn't get called.
 	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComponent != NULL) && OtherComponent->IsSimulatingPhysics())
 	{
 		OtherComponent->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
 		Destroy();
 	}

}

