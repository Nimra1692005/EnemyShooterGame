# 🎮 Epic Shooter 3D

A browser-based 3D third-person shooter game built with HTML5 + Three.js.
No installation required — just open in Chrome!

---

## 🌐 Play Online
👉 **[Click Here to Play](https://nimra1692005.github.io/EnemyShooterGame/index.html)**

```
https://nimra1692005.github.io/EnemyShooterGame/index.html
```

---

## 🎯 Assignment Features

| Feature | Status |
|---|---|
| Random Object Spawning | ✅ Gems spawn at random locations |
| Collectibles + Score System | ✅ Collect gems to increase score |
| Score Display on Screen | ✅ HUD shows score, HP, progress bar |
| Enemy Faces Player | ✅ Enemy always rotates toward player |
| Enemy Shoots Projectiles | ✅ Enemy fires fireballs at player |
| Player Survival / Health | ✅ Player has 200 HP, takes damage |
| Win / Lose Condition | ✅ Collect 10 gems = WIN, HP = 0 = LOSE |

---

## 🕹️ How to Play

### Controls
| Key | Action |
|---|---|
| **W A S D** / Arrow Keys | Move player |
| **Space** | Shoot (after gun unlock) / Dodge roll |
| **Q** | Sword swing |
| **G** | Gun shoot |
| **F** | Use current weapon |
| **1** | Select Sword |
| **2** | Select Gun |
| **3** | Speed Boost |
| **4** | Shield |
| **5 / B** | Build Mode |
| **E** | Remove nearby block |
| **Mouse Click** | Attack / Place block |

### Game Rules
1. Collect **3 yellow gems** → Gun unlocks automatically
2. Press **Space** to shoot enemy (auto-aim!)
3. Collect **10 gems** to win
4. Avoid enemy fireballs — you have **200 HP (10 hits)**
5. Enemy respawns after death — harder each time!

---

## ⚔️ Weapons & Power-ups

| Item | How to Get | Effect |
|---|---|---|
| 🗡️ Sword | Default | Swing with Q — 5 unit range |
| 🔫 Gun | Collect 3 gems | Auto-aim shoot with Space |
| ⚡ Speed Boost | Press 3 | 2x speed for 10 seconds |
| 🛡️ Shield | Press 4 | Block damage for 10 seconds |

---

## 📋 Quests / Missions

| Quest | Goal |
|---|---|
| Gem Collector | Collect 5 gems |
| Enemy Slayer | Kill 3 enemies |
| Builder | Place 2 blocks |
| Survivor | Survive 60 seconds |

Complete all 4 quests → **BOSS spawns!**

---

## 🧱 Building System (Minecraft Style)

1. Press **B** or **5** to enter Build Mode
2. Select block type (Wood / Grass / Stone)
3. **Click on ground** to place block
4. Press **E** to remove nearby block

---

## 👹 Boss Fight

- Complete all 4 quests to unlock the Boss
- Boss has **20 HP** and 2 phases:
  - **Phase 1:** Normal shooting
  - **Phase 2 (50% HP):** Enraged — faster + 3-way special attack
- Defeat the Boss to **WIN the game!**

---

## 🛠️ Technical Details

| | |
|---|---|
| **Engine** | Three.js r128 (WebGL) |
| **Language** | HTML5 + JavaScript |
| **3D Camera** | Third Person (follows player) |
| **Platform** | Any browser (Chrome recommended) |
| **Install** | None required |

---

## 📁 Project Structure

```
EnemyShooterGame/
├── index.html          ← Main game file (open this!)
├── game.html           ← Backup copy
├── README.md           ← This file
├── EnemyShooterGame.uproject
├── Config/
│   ├── DefaultInput.ini
│   ├── DefaultGame.ini
│   └── DefaultEngine.ini
└── Source/
    └── EnemyShooterGame/
        ├── EnemyShooterCharacter.h/.cpp
        ├── EnemyShooterGameMode.h/.cpp
        ├── EnemyCharacter.h/.cpp
        ├── EnemyProjectile.h/.cpp
        ├── Collectible.h/.cpp
        ├── CollectibleSpawner.h/.cpp
        └── ShooterHUD.h/.cpp
```

---

## 👩‍💻 Developer

**Nimra** — Computer Science Student
GitHub: [@Nimra1692005](https://github.com/Nimra1692005)
