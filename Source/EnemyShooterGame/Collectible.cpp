#include "Collectible.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EnemyShooterCharacter.h"
#include "EnemyShooterGameMode.h"
#include "Kismet/GameplayStatics.h"

ACollectible::ACollectible()
{
    PrimaryActorTick.bCanEverTick = true;

    ScoreValue = 1;
    SpinSpeed  = 90.f;

    // Overlap sphere
    CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
    CollisionComp->InitSphereRadius(50.f);
    CollisionComp->SetCollisionProfileName("OverlapAllDynamic");
    RootComponent = CollisionComp;

    // Visible mesh
    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    MeshComp->SetupAttachment(RootComponent);
    MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACollectible::BeginPlay()
{
    Super::BeginPlay();

    CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ACollectible::OnPlayerOverlap);
}

void ACollectible::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Spin in place so it's easy to spot
    AddActorLocalRotation(FRotator(0.f, SpinSpeed * DeltaTime, 0.f));
}

void ACollectible::OnPlayerOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    AEnemyShooterCharacter* Player = Cast<AEnemyShooterCharacter>(OtherActor);
    if (!Player) return;
    if (Player->IsDead()) return;

    // Award score
    AEnemyShooterGameMode* GM = Cast<AEnemyShooterGameMode>(
        UGameplayStatics::GetGameMode(GetWorld()));
    if (GM)
    {
        GM->AddScore(ScoreValue);
    }

    // Destroy the collectible
    Destroy();
}
