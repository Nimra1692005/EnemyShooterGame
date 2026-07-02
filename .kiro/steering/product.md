# EnemyShooterGame — Product Overview

## Goal
A third-person survival/arcade game built in Unreal Engine 5 using C++.
The player collects objects to score points while avoiding projectiles fired by an enemy.

## Core Gameplay Loop
1. Collectibles spawn randomly around the level every few seconds.
2. The player runs around collecting them — each gives +1 score.
3. An enemy rotates to always face the player and fires projectiles on a timer.
4. The player must dodge projectiles while collecting.
5. Collect 10 items to win. Take 5 hits (20 damage each, 100 HP total) to lose.

## Assignment Requirements Checklist
- [x] Random object spawning (CollectibleSpawner)
- [x] Collectibles increase score (Collectible + GameMode.AddScore)
- [x] Score displayed on screen (ShooterHUD)
- [x] Enemy faces player every Tick (EnemyCharacter.FacePlayer)
- [x] Enemy shoots projectiles (EnemyCharacter.ShootAtPlayer + EnemyProjectile)
- [x] Player takes damage from projectiles (TakeDamage override)
- [x] Game ends on death / win on score target (GameMode.PlayerDied / WinGame)
