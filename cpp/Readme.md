# TP C++ - Questions

## 4e étape

Comment appelle-t'on ce type de méthode et comment faut-il les déclarer ?

```
    C'est une méthode pûrement virtuelle (ou abstraite) que l'on déclare avec le mot clé "virtual" dans la classe parent et en ajoutant un "= 0" à la fin.
```

Si vous avez fait ce qui précède comme demandé, il ne sera plus possible d'instancer des objets de la classe de base. Pourquoi ?

```
    Une classe ayant une fonction pûrement virtuelle ne peut pas être instancié, il s'agit d'une interface, un concept servant au polymorphisme. Cette classe devient abstraite.
```

## 5e étape

Quelle est la propriété caractéristique de l'orienté objet qui permet de faire cela ?

```
C'est le polymorphisme.
```

Qu'est-il spécifiquement nécessaire de faire dans le cas du C++ ?

```
Pour avoir un polymorphisme dynamique, il faut utiliser le mot clé `virtual` dans la méthode de la classe parent.
```

Quel est le type des éléments du tableau : le tableau doit-il contenir des objets ou des pointeurs vers ces objets ? Pourquoi ? Comparer à Java.

```
Le tableau doit contenir des pointeurs vers ces objets pour permettre le polymorphisme.
```

## 7e étape

Parmi les classes précédemment écrites quelles sont celles qu'il faut modifier afin qu'il n'y ait pas de fuite mémoire quand on détruit les objets ?

```
Seule la classe `Film` a besoin d'être modifiée pour libérer la mémoire occuppée par le tableau.
```

La copie d'objet peut également poser problème quand ils ont des variables d'instance qui sont des pointeurs. Quel est le problème et quelles sont les solutions ?

```
Une solution peut être de faire une `deep-copy` du contenu des pointeurs.
```

# TP C++ - Remarks

## 4e étape

To use the "play" method from the multimedia, you'll need the following:

- `xdg-open` for the photos
- `mpv` for the videos

## 6e étape

Tested with valgrind to check the memory leak.

```
==3996== Memcheck, a memory error detector
==3996== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==3996== Using Valgrind-3.21.0 and LibVEX; rerun with -h for copyright info
==3996== Command: ./myprog
==3996== 
Name: lavaSimulation, Path: media/lavaSimulation.mp4
Length: 600
nbChapters: 3, chapters: [1, 1, 3]
Name: lavaSimulation, Path: media/lavaSimulation.mp4
Length: 600
nbChapters: 3, chapters: [1, 1, 3]
Name: lavaSimulation, Path: media/lavaSimulation.mp4
Length: 600
nbChapters: 3, chapters: [1, 1, 3]
==3996== 
==3996== HEAP SUMMARY:
==3996==     in use at exit: 0 bytes in 0 blocks
==3996==   total heap usage: 11 allocs, 11 frees, 83,655 bytes allocated
==3996== 
==3996== All heap blocks were freed -- no leaks are possible
==3996== 
==3996== For lists of detected and suppressed errors, rerun with: -s
==3996== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

## 9e étape

Tested with valgrind to check the memory leak.

```
==3759== Memcheck, a memory error detector
==3759== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==3759== Using Valgrind-3.21.0 and LibVEX; rerun with -h for copyright info
==3759== Command: ./myprog
==3759== 
Group: G1
Name: Film, Path: media/lavaSimulation.mp4
Length: 600
nbChapters: 3, chapters: [1, 1, 3]
Name: Photo, Path: media/profilPicture.jpg
Latitude: 640, Longitude: 720

Group: G2
Name: Photo, Path: media/profilPicture.jpg
Latitude: 640, Longitude: 720
Name: Video, Path: media/lavaSimulation.mp4
Length: 600

Group: G1
Name: Film, Path: media/lavaSimulation.mp4
Length: 600
nbChapters: 3, chapters: [1, 1, 3]
Name: Photo, Path: media/profilPicture.jpg
Latitude: 640, Longitude: 720

Name: Photo, Path: media/profilPicture.jpg
Latitude: 640, Longitude: 720
==3759== 
==3759== HEAP SUMMARY:
==3759==     in use at exit: 0 bytes in 0 blocks
==3759==   total heap usage: 34 allocs, 34 frees, 101,664 bytes allocated
==3759== 
==3759== All heap blocks were freed -- no leaks are possible
==3759== 
==3759== For lists of detected and suppressed errors, rerun with: -s
==3759== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

## 10e étape

Pour empécher le `new` on peut rendre les constructeurs `private` et ajouter la classe `MultimediaManager` en tant que `friend` pour toute les autres classes pour qu'il soit le seul à avoir l'accès au constructeur.

Question bonus implémentée

## 11e étape

Décommenter le `#define __VERSION_PRE_SOCKET__` et commenter `#define __VERSION_POST_SOCKET__` pour avoir la version du `main` des questions précédentes et inversement pour les version du `main` des questions suivantes.

Ajout de la map de functions pour représenter les commandes. Ajout d'une commande pour lire la base de donnée.

## 12e étape

Pour que MultimediaManager soit la seule classe capable de sérialiser des multimédias, je la met en tant que `friend` de Multimedia.
De plus je transforme mon manager en singleton pour être sûr que l'utilisateur ne puisse pas l'hériter ou en créer d'autres.

Une manière de contourner cette restriction serait d'hériter de Multimedia et de redéfinir la méthode write mais dans ce cas, étant donné que cette méthode est vide dans la classe Multimedia, cela ne servirait pas à grand chose.

Pour faciliter les choses, j'utilise une `Factory` qui crée les multimedias en prenant en paramètre le fichier à lire. Je rend également les fonctions de cette classe privés pour que le manager soit le seul à pouvoir l'utiliser.