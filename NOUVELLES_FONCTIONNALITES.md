# 🚀 Nouvelles Fonctionnalités Interactives

## Interface de Configuration au Démarrage

### Fenêtre de Configuration
Au lancement de la simulation, une fenêtre de configuration s'ouvre automatiquement permettant de :

#### 📊 **Préréglages Rapides**
- **Système Solaire** - Configuration classique avec une étoile et des planètes
- **Étoiles Binaires** - Deux étoiles en orbite mutuelle avec planètes
- **Corps Aléatoires** - Distribution aléatoire pour observer le chaos gravitationnel
- **Galaxies** - Collision de deux galaxies spirales

#### ⚙️ **Configuration Personnalisée**
- **Nombre de corps** : De 1 à 100 corps (recommandé : 5-25 pour de bonnes performances)
- **Constante gravitationnelle** : Contrôle l'intensité de l'attraction (0.1 à 1000)
- **Pas de temps** : Précision de la simulation (0.001 à 0.1)

### 🎮 **Utilisation de l'Interface**
1. **Cliquez sur un préréglage** pour une configuration rapide
2. **Ou saisissez vos valeurs** dans les champs personnalisés
3. **Cliquez sur "Démarrer"** pour lancer la simulation
4. **"Quitter"** pour fermer l'application

## Contrôles de Vitesse Avancés

### 🏃 **Ajustement en Temps Réel**
- **Touches +/-** : Augmenter/diminuer la vitesse par incréments
- **Touche 0** : Remettre la vitesse normale (x1.0)
- **Molette souris** : Ajustement fluide de la vitesse
- **Ctrl + Molette** : Zoom (comme avant)

### 📈 **Plages de Vitesse**
- **Vitesse minimale** : x0.1 (ralenti extrême pour l'observation)
- **Vitesse normale** : x1.0 (vitesse de base)
- **Vitesse maximale** : x10.0 (accélération pour l'évolution rapide)

### 🔄 **Indicateur de Vitesse**
La vitesse actuelle s'affiche dans la console en temps réel :
```
Vitesse: x2.5
Vitesse réinitialisée: x1.0
```

## Impact des Paramètres

### 👥 **Nombre de Corps**
- **1-5 corps** : Orbites stables, facile à suivre
- **6-15 corps** : Interactions complexes, bon équilibre
- **16-25 corps** : Chaos gravitationnel intéressant
- **26-50 corps** : Formations de clusters
- **50+ corps** : Simulations de type galactique (plus lent)

### 🌍 **Constante Gravitationnelle**
- **G < 10** : Interactions faibles, orbites larges
- **G = 50** : Équilibre recommandé (valeur par défaut)
- **G > 100** : Attractions fortes, orbites serrées
- **G > 500** : Systèmes très compacts, risque d'instabilité

### ⏱️ **Pas de Temps**
- **dt = 0.001** : Très précis mais plus lent
- **dt = 0.01** : Bon équilibre (recommandé)
- **dt = 0.05** : Rapide mais moins précis
- **dt > 0.1** : Risque d'instabilité numérique

## Exemples de Configurations Intéressantes

### 🌟 **Système Planétaire Stable**
- **Corps** : 5-7
- **G** : 80-120
- **dt** : 0.01
- **Résultat** : Orbites elliptiques stables

### 🌪️ **Chaos Gravitationnel**
- **Corps** : 15-20
- **G** : 30-50
- **dt** : 0.01
- **Résultat** : Interactions chaotiques, éjections

### 🌌 **Formation de Structures**
- **Corps** : 25-40
- **G** : 20-40
- **dt** : 0.005
- **Résultat** : Clustering, formation de groupes

### ⚡ **Système Dynamique Rapide**
- **Corps** : 8-12
- **G** : 150-300
- **dt** : 0.008
- **Vitesse** : x3-5
- **Résultat** : Évolution rapide, collisions

## Conseils d'Utilisation

### 🎯 **Pour l'Observation Scientifique**
1. Commencez avec un préréglage
2. Utilisez une vitesse x0.5-1.0
3. Activez les traînées (T)
4. Observez plusieurs orbites complètes

### 🚀 **Pour l'Exploration Rapide**
1. Configuration personnalisée avec 15-20 corps
2. Vitesse x3-5
3. Changez les paramètres et observez les différences
4. Utilisez Reset (R) pour tester plusieurs configurations

### 🔬 **Pour l'Analyse Détaillée**
1. Peu de corps (3-8)
2. Vitesse lente (x0.2-0.5)
3. Pas de temps petit (0.005-0.01)
4. Zoom sur les interactions

## Performance et Optimisation

### 📊 **Recommandations de Performance**
| Nombre de Corps | Vitesse Recommandée | Performance |
|----------------|-------------------|-------------|
| 1-10           | x1-10             | Excellente  |
| 11-20          | x1-5              | Bonne       |
| 21-35          | x1-3              | Moyenne     |
| 36-50          | x1-2              | Acceptable  |
| 50+            | x1                | Lente       |

### ⚡ **Optimisations Automatiques**
- La vitesse ajuste automatiquement le nombre d'étapes par frame
- Les traînées sont limitées pour maintenir la performance
- Les calculs sont optimisés pour les grandes vitesses

### 🛠️ **Dépannage**
- **Simulation trop lente** : Réduisez le nombre de corps ou la vitesse
- **Orbites instables** : Diminuez le pas de temps
- **Pas d'interaction** : Augmentez la constante gravitationnelle
- **Explosion du système** : Réduisez G ou dt

## Interface Utilisateur Détaillée

### 📱 **Champs de Saisie**
- **Clic** pour sélectionner un champ
- **Saisie numérique** filtrée automatiquement
- **Entrée** pour valider
- **Échap** pour annuler

### 🎨 **Codes Couleurs**
- **Bleu clair** : Bouton sélectionné/actif
- **Gris foncé** : Bouton normal
- **Blanc** : Champ de saisie actif
- **Gris** : Champ de saisie inactif

### ⌨️ **Raccourcis Clavier**
- **Entrée** : Valider et passer au champ suivant
- **Tab** : Passer au champ suivant (futur)
- **Échap** : Annuler la saisie
- **Clic** : Sélection directe

Ces nouvelles fonctionnalités rendent la simulation beaucoup plus interactive et permettent une exploration approfondie des phénomènes gravitationnels !
