# EnemyShooterGame — Project Structure

```
EnemyShooterGame/
├── EnemyShooterGame.uproject          # UE project descriptor (Engine 5.3)
├── Config/
│   ├── DefaultEngine.ini
│   ├── DefaultGame.ini                # Sets GameMode, DefaultPawn, HUD class
│   └── DefaultInput.ini               # WASD + mouse + jump bindings
├── Content/                           # UE assets (meshes, materials, maps, BPs)
│   └── (create Blueprint child classes here — see below)
└── Source/
    ├── EnemyShooterGame.Target.cs     # Game target
    ├── EnemyShooterGameEditor.Target.cs
    └── EnemyShooterGame/
        ├── EnemyShooterGame.Build.cs  # Module build rules
        ├── EnemyShooterGame.h/.cpp    # Module entry point
        │
        ├── EnemyShooterCharacter.h/.cpp   # Player: movement, health, TakeDamage
        ├── EnemyShooterGameMode.h/.cpp    # Score, win/lose logic
        ├── ShooterHUD.h/.cpp              # On-screen score + health bar
        │
        ├── EnemyCharacter.h/.cpp          # Enemy: faces player, fires on timer
        ├── EnemyProjectile.h/.cpp         # Projectile: moves straight, damages on hit
        │
        ├── Collectible.h/.cpp             # Pickup: spins, awards score on overlap
        └── CollectibleSpawner.h/.cpp      # Spawns collectibles at random positions
```

## Blueprint Child Classes to Create in Editor
After compiling, create these Blueprint children in Content/Blueprints/:

| Blueprint Name       | Parent C++ Class        | What to assign                          |
|----------------------|-------------------------|-----------------------------------------|
| BP_Player            | AEnemyShooterCharacter  | Skeletal mesh, anim blueprint           |
| BP_Enemy             | AEnemyCharacter         | ProjectileClass = BP_Projectile, mesh   |
| BP_Projectile        | AEnemyProjectile        | Static mesh (sphere), material          |
| BP_Collectible       | ACollectible            | Static mesh (star/gem), material        |
| BP_CollectibleSpawner| ACollectibleSpawner     | CollectibleClass = BP_Collectible       |
| BP_GameMode          | AEnemyShooterGameMode   | (optional) override ScoreToWin          |

## Level Setup (in editor)
1. Place **BP_Player** as the default pawn (or set in GameMode)
2. Place **BP_Enemy** somewhere in the level
3. Place **BP_CollectibleSpawner** at the center of the play area
4. Set World Settings → GameMode Override → **BP_GameMode**
