#include "EnemyShooterCharacter.h"
#include "EnemyShooterGameMode.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AEnemyShooterCharacter::AEnemyShooterCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    MaxHealth = 100.f;
    CurrentHealth = MaxHealth;

    // Camera boom (spring arm)
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 400.f;
    CameraBoom->bUsePawnControlRotation = true;

    // Follow camera
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    // Character rotation follows controller yaw
    bUseControllerRotationYaw = false;
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
    GetCharacterMovement()->MaxWalkSpeed = 500.f;
}

void AEnemyShooterCharacter::BeginPlay()
{
    Super::BeginPlay();
    CurrentHealth = MaxHealth;
}

void AEnemyShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Movement axes
    PlayerInputComponent->BindAxis("MoveForward", this, &AEnemyShooterCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight",   this, &AEnemyShooterCharacter::MoveRight);

    // Camera axes
    PlayerInputComponent->BindAxis("Turn",   this, &AEnemyShooterCharacter::Turn);
    PlayerInputComponent->BindAxis("LookUp", this, &AEnemyShooterCharacter::LookUp);

    // Jump
    PlayerInputComponent->BindAction("Jump", IE_Pressed,  this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
}

void AEnemyShooterCharacter::MoveForward(float Value)
{
    if (Controller && Value != 0.f)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void AEnemyShooterCharacter::MoveRight(float Value)
{
    if (Controller && Value != 0.f)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(Direction, Value);
    }
}

void AEnemyShooterCharacter::Turn(float Value)
{
    AddControllerYawInput(Value);
}

void AEnemyShooterCharacter::LookUp(float Value)
{
    AddControllerPitchInput(Value);
}

float AEnemyShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
    AController* EventInstigator, AActor* DamageCauser)
{
    float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

    if (IsDead()) return 0.f;

    CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.f, MaxHealth);
    UE_LOG(LogTemp, Warning, TEXT("Player Health: %.1f"), CurrentHealth);

    if (IsDead())
    {
        Die();
    }

    return DamageAmount;
}

bool AEnemyShooterCharacter::IsDead() const
{
    return CurrentHealth <= 0.f;
}

float AEnemyShooterCharacter::GetHealthPercent() const
{
    return CurrentHealth / MaxHealth;
}

void AEnemyShooterCharacter::Die()
{
    UE_LOG(LogTemp, Warning, TEXT("Player is dead!"));

    // Disable input
    APlayerController* PC = Cast<APlayerController>(GetController());
    if (PC)
    {
        PC->DisableInput(PC);
    }

    // Notify game mode
    AEnemyShooterGameMode* GM = Cast<AEnemyShooterGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
    if (GM)
    {
        GM->PlayerDied();
    }
}
