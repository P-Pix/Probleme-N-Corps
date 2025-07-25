# Simulateur N-Corps Interactif

![N-Corps Simulation](asset/picture/simulation_screenshot.png)

## 📋 Description

Le **Simulateur N-Corps** est une application interactive développée en C++ qui simule les interactions gravitationnelles entre plusieurs corps célestes. Le projet utilise SDL2 pour le rendu graphique et propose une interface de configuration intuitive permettant de personnaliser les paramètres de simulation.

## ✨ Fonctionnalités

### 🎯 Interface de Configuration
- **Préréglages prédéfinis** : Système Solaire, Étoiles Binaires, Corps Aléatoires, Galaxies
- **Configuration personnalisée** : Nombre de corps, constante gravitationnelle, pas de temps
- **Interface graphique moderne** avec SDL2_ttf pour le rendu de texte

### 🚀 Simulation Physique
- **Intégration de Verlet** pour une simulation stable et précise
- **Calcul des forces gravitationnelles** en temps réel
- **Prévention des collisions** pour maintenir la stabilité
- **Contrôle de vitesse dynamique** (molette de souris, touches +/-)

### 🎮 Contrôles Interactifs
- **Zoom** : Molette de souris
- **Vitesse** : Touches `+` et `-` ou molette avec Ctrl
- **Pause/Reprise** : Barre d'espace
- **Réinitialisation** : Touche `R`

## 🛠️ Architecture

Le projet suit une architecture **MVC (Model-View-Controller)** :

```
src/
├── main.cpp                 # Point d'entrée
├── controller/
│   └── Application.cpp      # Contrôleur principal
├── model/
│   ├── Body.cpp            # Modèle des corps célestes
│   └── Simulation.cpp      # Moteur de simulation
└── view/
    ├── ConfigWindow.cpp    # Interface de configuration
    └── Renderer.cpp        # Rendu graphique
```

## 📦 Dépendances

- **SDL2** (>= 2.0) - Rendu graphique et gestion des événements
- **SDL2_ttf** - Rendu de texte
- **C++11** - Standard minimum requis
- **Make** - Système de build

### Installation des dépendances (Ubuntu/Debian)

```bash
sudo apt-get update
sudo apt-get install libsdl2-dev libsdl2-ttf-dev build-essential
```

## 🔧 Compilation

```bash
# Cloner le projet
git clone https://github.com/P-Pix/Probleme-N-Corps.git
cd Probleme-N-Corps

# Compiler
make all

# Lancer la simulation
./N-Corps
```

### Commandes Make disponibles

```bash
make all        # Compiler et nettoyer
make clean      # Supprimer les fichiers objets
make run        # Compiler et exécuter
make help       # Afficher l'aide
```

## 🎯 Utilisation

### Lancement
1. Exécutez `./N-Corps`
2. Choisissez un préréglage ou configurez manuellement
3. Cliquez sur "Démarrer" pour lancer la simulation

### Préréglages disponibles

| Préréglage | Description | Corps | Gravité |
|------------|-------------|-------|---------|
| **Système Solaire** | Simulation planétaire | 9 | 100.0 |
| **Étoiles Binaires** | Système d'étoiles doubles | 2 | 200.0 |
| **Corps Aléatoires** | Distribution aléatoire | 15 | 50.0 |
| **Galaxies** | Formation galactique | 50 | 25.0 |

### Configuration personnalisée
- **Nombre de corps** : 1-100
- **Constante gravitationnelle** : 0.1-1000.0
- **Pas de temps** : 0.001-0.1

## 🔬 Algorithmes

### Intégration de Verlet
L'algorithme de Verlet assure une simulation stable et conserve l'énergie :

```cpp
// Position
newPosition = 2 * position - oldPosition + acceleration * timeStep²

// Vitesse (pour affichage)
velocity = (newPosition - oldPosition) / (2 * timeStep)
```

### Calcul gravitationnel
Force entre deux corps selon la loi de Newton :

```cpp
F = G * m1 * m2 / r²
```

## 📊 Performance

- **Complexité** : O(n²) pour n corps
- **Optimisations** : 
  - Calcul vectoriel efficace
  - Prévention des divisions par zéro
  - Rendu optimisé avec SDL2

## 🧪 Tests

```bash
make test           # Tests unitaires
make demo          # Démonstration sans graphiques
make test-features # Tests des fonctionnalités
```

## 📁 Structure du projet

```
Probleme-N-Corps/
├── src/                    # Code source
├── include/               # Headers
├── bin/                   # Fichiers objets
├── test/                  # Tests unitaires
├── asset/                 # Ressources
│   ├── picture/          # Images
│   └── video/            # Vidéos de démonstration
├── doc/                   # Documentation
├── Makefile              # Configuration de build
└── README.md             # Ce fichier
```

## 🤝 Contribution

Les contributions sont les bienvenues ! Veuillez :

1. Fork le projet
2. Créer une branche feature (`git checkout -b feature/nouvelle-fonctionnalite`)
3. Commit vos changements (`git commit -m 'Ajouter nouvelle fonctionnalité'`)
4. Push vers la branche (`git push origin feature/nouvelle-fonctionnalite`)
5. Ouvrir une Pull Request

## 📝 Licence

Ce projet est sous licence MIT. Voir le fichier `LICENSE` pour plus de détails.

## 👨‍💻 Auteur

**P-Pix** - [GitHub Profile](https://github.com/P-Pix)

## 🙏 Remerciements

- SDL2 Development Team
- Communauté open-source C++
- Algorithmes de simulation physique classiques

---

⭐ **N'hésitez pas à donner une étoile si ce projet vous plaît !**

- **Simulation physique réaliste** : Calcul des forces gravitationnelles entre tous les corps
- **Rendu visuel en temps réel** : Affichage des corps avec des couleurs différentes selon leur masse
- **Traînées orbitales** : Visualisation des trajectoires des corps
- **Contrôles interactifs** : Navigation avec la souris et le clavier
- **Préréglages de simulation** : Système solaire, systèmes binaires, collision de galaxies
- **Interface de contrôle** : Pause, reset, zoom, panoramique

## Prérequis

- SDL2 development libraries
- g++ compiler with C++11 support
- pkg-config

### Installation des dépendances (Ubuntu/Debian)

```bash
sudo apt-get update
sudo apt-get install libsdl2-dev pkg-config build-essential
```

### Installation des dépendances (Fedora/CentOS)

```bash
sudo dnf install SDL2-devel pkgconf gcc-c++
```

## Compilation

```bash
make init    # Créer les répertoires nécessaires
make all     # Compiler le projet
```

## Utilisation

```bash
make run     # Lancer la simulation
# ou directement
./N-Corps
```

## Contrôles

| Touche/Action | Description |
|---------------|-------------|
| **ESPACE** | Mettre en pause/reprendre la simulation |
| **R** | Réinitialiser la simulation |
| **T** | Activer/désactiver les traînées |
| **C** | Effacer les traînées |
| **1** | Charger le système solaire |
| **2** | Charger un système d'étoiles binaires |
| **3** | Générer des corps aléatoires |
| **4** | Simulation de collision de galaxies |
| **WASD/Flèches** | Déplacer la caméra |
| **Molette souris** | Zoomer/dézoomer |
| **Clic + glisser** | Panoramique de la caméra |

## Architecture du Code

```
src/
├── main.cpp                    # Point d'entrée de l'application
├── controller/
│   └── Application.cpp         # Contrôleur principal de l'application
├── model/
│   ├── Body.cpp               # Classe représentant un corps céleste
│   └── Simulation.cpp         # Moteur de simulation physique
└── view/
    └── Renderer.cpp           # Moteur de rendu SDL2

include/
├── Application.hpp
├── Body.hpp
├── Simulation.hpp
└── Renderer.hpp
```

## Algorithmes Utilisés

### Simulation Physique
- **Loi de la gravitation universelle** : F = G × m₁ × m₂ / r²
- **Intégration de Verlet** : Pour la stabilité numérique
- **Calcul O(n²)** : Toutes les interactions entre corps sont calculées

### Rendu
- **Projection monde-écran** : Transformation des coordonnées
- **Système de caméra** : Zoom et panoramique
- **Traînées avec effet de fondu** : Visualisation des trajectoires

## Préréglages de Simulation

1. **Système Solaire** : Une étoile centrale avec plusieurs planètes en orbite
2. **Système Binaire** : Deux étoiles en orbite mutuelle avec des planètes
3. **Corps Aléatoires** : Distribution aléatoire de corps avec des masses variables
4. **Collision de Galaxies** : Deux galaxies spirales en collision

## Paramètres Physiques

- **Constante gravitationnelle** : Ajustée pour un effet visuel optimal
- **Pas de temps** : 0.01 unité de temps par frame
- **Prévention des singularités** : Distance minimale entre les corps

## Nettoyage

```bash
make clean      # Supprimer les fichiers objets
make mrproper   # Supprimer tout (objets + exécutable)
```

## Développement

Le projet suit une architecture MVC (Modèle-Vue-Contrôleur) :

- **Modèle** : Gestion de la physique et des données (`Body`, `Simulation`)
- **Vue** : Rendu graphique (`Renderer`)
- **Contrôleur** : Logique d'application et gestion des événements (`Application`)

## Améliorations Futures

- [ ] Optimisation avec des algorithmes Barnes-Hut ou Fast Multipole Method
- [ ] Système de particules pour les effets visuels
- [ ] Sauvegarde/chargement de configurations
- [ ] Interface utilisateur avec des menus
- [ ] Support de différents intégrateurs numériques
- [ ] Mode de création interactive de systèmes

## Licence

Ce projet est open source et disponible sous licence MIT.
