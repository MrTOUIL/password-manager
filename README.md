# 🔐 Gestionnaire de mots de passe interactif en C (avec <curses.h>)

Bienvenue dans ce petit projet de **gestionnaire de mots de passe**, codé en C, utilisant la bibliothèque `<curses.h>` pour un affichage **coloré**, **animé**, et **interactif** en console.

## ✨ Fonctionnalités principales

- Interface interactive avec couleurs et encadrements grâce à `ncurses`
- Système **mono-utilisateur** pour plus de simplicité
- Chaque mot de passe est associé à une **plateforme (site/app)**
- Cryptage simple des mots de passe pour éviter le stockage brut
- Possibilité de :
  - Ajouter un mot de passe
  - Afficher les mots de passe
  - Modifier un mot de passe existant
  - Supprimer un mot de passe
  - Rechercher un mot de passe par identifiant ou plateforme
  - Quitter avec une **animation élégante**

## 🔒 Cryptage

Ce gestionnaire utilise un algorithme de chiffrement **basique** (type XOR ou César modifié) pour masquer les mots de passe stockés dans un fichier texte local. Le but ici est **pédagogique**, pas sécurisé pour une utilisation réelle.

## 📁 Fichiers utilisés

- `passwords.txt` : stockage local des identifiants et mots de passe cryptés.
- Les entrées sont sauvegardées sous forme :
  
  ```plaintext
  plateforme:id:motdepasse_crypte

## 💖 Credits
“رحلة ألف ميل تبدأ بخطوة” – (The journey of a thousand miles begins with a single step)

This project wouldn’t have reached its current level of elegance and functionality without the valuable collaboration and support of my binôme:

💫 Hamidi Selma
Étudiante à l'USTHB, brillante, engagée et toujours pleine d’idées.
Chaque ligne de ce code porte un peu de sa vision et de sa bienveillance. Merci Selma 💜
À travers ce gestionnaire, se cache plus qu’un code... un clin d'œil discret à une collaboration spéciale .

