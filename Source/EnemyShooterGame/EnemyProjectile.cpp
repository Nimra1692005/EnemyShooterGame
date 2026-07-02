#include "EnemyProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyShooterCharacter.h"

AEnemyProjectile::AEnemyProjectile()
{
    PrimaryActorTick.bCanEverTick = false;
    DamageAmount = 20.f;

    // Collision sphere
    CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
    CollisionComp->InitSphereRadius(15.f);
    CollisionComp->SetCollisionProfileName("Projectile");
    CollisionComp->OnComponentHit.AddDynamic(this, &AEnemyProjectile::OnHit);
    RootComponent = CollisionComp;

    // Visual mesh
    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    MeshComp->SetupAttachment(RootComponent);
    MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    // Movement
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->UpdatedComponent = CollisionComp;
    ProjectileMovement->InitialSpeed      = 1200.f;
    ProjectileMovement->MaxSpeed          = 1200.f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->bShouldBounce     = false;
    ProjectileMovement->ProjectileGravityScale = 0.f; // no arc — straight shot

    // Auto-destroy after 5 seconds
    InitialLifeSpan = 5.f;
}

void AEnemyProjectile::BeginPlay()
{
    Super::BeginPlay();
}

void AEnemyProjectile::FireInDirection(const FVector& ShootDirection)
{
    ProjectileMovement->Velocity = ShootDirection * ProjectileMovement->InitialSpeed;
}

void AEnemyProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    // Ignore the enemy that fired this
    AActor* MyOwner = GetOwner();
    if (OtherActor && OtherActor != this && OtherActor != MyOwner)
    {
        // Apply damage
        UGameplayStatics::ApplyDamage(OtherActor, DamageAmount,
            MyOwner ? MyOwner->GetInstigatorController() : nullptr,
            this, UDamageType::StaticClass());

        Destroy();
    }
}
