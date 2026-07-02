# EnemyShooterGame — Technical Standards

## Engine & Language
- Unreal Engine 5.3
- C++ (no Blueprint-only logic — all gameplay in C++, Blueprints are child classes for assets)
- Visual Studio 2022, Game development with C++ workload

## Build
```
Right-click EnemyShooterGame.uproject → Generate Visual Studio project files
Open EnemyShooterGame.sln → Build (Development Editor | Win64)
```

## Module
- Single runtime module: `EnemyShooterGame`
- Build rules: `Source/EnemyShooterGame/EnemyShooterGame.Build.cs`
- Required public modules: Core, CoreUObject, Engine, InputCore, UMG, Slate, SlateCore

## Coding Rules
- All UCLASS macros must have the module API macro: `ENEMYSHOOTERGAME_API`
- Use `UPROPERTY(EditDefaultsOnly)` for Blueprint-assignable class references (e.g. ProjectileClass)
- Use `UPROPERTY(EditAnywhere)` for tunable values designers change per-instance
- Use `FTimerHandle` + `GetWorldTimerManager().SetTimer(...)` for all recurring game logic
- Never use `UE_LOG` for gameplay state in shipping; use it freely for debugging
- Prefer `Cast<T>()` over `dynamic_cast`
- `TakeDamage` must always call `Super::TakeDamage` first

## Input
- Axis: MoveForward, MoveRight, Turn, LookUp (defined in DefaultInput.ini)
- Action: Jump (SpaceBar)

## Damage
- All damage flows through `UGameplayStatics::ApplyDamage` → `AActor::TakeDamage`
- Damage amount per projectile: 20.f (configurable in Blueprint child)
- Player max HP: 100.f
