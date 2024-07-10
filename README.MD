<pre>
 *   Author           : Yacine GAOUA (yacine.gaoua@cea.fr)
 *   Version          : 1.0.0
 *   Description      : MIPModeler (Algebraic Modeling Language for optimisation)
</pre>

# Introduction

MIPModeler (Mixed Integer Progamming MODELER) is a C++ library designed to build linear optimization problems using native C++ algebraic expressions as CPLEX, GUROBI modelers. 

MIPModeler allows us to build optimization problems using expressions close to the original mathematical description.

MIPModeler has several solver interfaces which allow it to be easily connected to the most MILP solvers (CPLEX, GUROBI, XPRESS, MOSEK, CBC, CLP, GLPK, SOPLEX, ...).

MIPModeler supports SOS variables and includes helpfull generic methods as piecewise linearisation, 2d interpolation, ...

GAMS interface is available on MIPModeler to build an optimization problem under GAMS formalism. This interface gives access to a nonlinear modeling and solvers. <br/><br/>


# Installation pour le développement

### Prérequis pour le développement:
- Qt 5.15
- CMake >= 3.23
- MSVC C++ >=2019 (C++, CMake, Python, et avec l'extension pour Qt)
- Solvers : Cplex, Cbc, Clp, ...
- GAMS 

- Cloner le dépot MIPModeler -> ```<mipmodelerPath>```
Pour une compilation CMake, il faut aussi récupérer le dépot CMakeTools
https://codev-tuleap.intra.cea.fr/plugins/git/pegase/CMakeTools.git

Le poser dans ```<mipmodelerPath>/lib/import``` 
sinon il faudra modifier le fichier de configuration par défaut ```<mipmodelerPath>/CMakeLists.txt```, ligne 8

### Paramétrer Visual Studio 2022

- Installer les extensions Qt Visual Studio Tools et Qt Vs Cmake Tools (non installé sur les serveurs)
Sur les serveurs, le fichier pour installer l'extension se trouve dans D:\B_VERSION_PERSEE_INTEGRATION, fichier qt-vsaddin-msvc2022-2.9.1-rev.06.vsix
ou sinon aller dans (Menu Extensions -> Gérer les extensions) pour télécharger l'extension.
	- Installation: Fermer Visual Studio, double-cliquer sur le fichier vsix pour installer l'extension.
une fois l'extension installée, relancer Visual Sudio, elle doit se trouver dans Menu Extension -> Qt VS Tools

- Paramétrer Qt Visual Studio Tools : 
  - Menu Extension -> Qt VS Tools -> Qt Versions
  - Ajouter la version de Qt: mettre le chemin de Qmake.bat pour msvc2019_x64 dans la colonne "Path" 
  - Mettre 5.15.0 dans la colonne "Version"

L'extension Qt Visual Studio Tools sert uniquement pour le debuggage afin d’afficher les QString, QList, … correctement dans le debugger. L’extension ne sert plus pour la compilation.
  

### Paramétrer Cmake
Possibilité de créer un fichier d'options, à mettre dans <mipmodelerPath>/cmake  (on peut s'inspirer du fichier <mipmodelerPath>/cmake/default_options.cmake)
Sinon par défaut c'est le fichier <mipmodelerPath>/cmake/default_options.cmake qui est utilisé

Ce fichier d'options permet entre autres de spécifier les chemins pour Qt5, Cplex, Python, ... et de choisir les modules à compiler ou non.

Par exemple
- Chemin pour Cplex (variable CPLEX_ROOT) : mettre le chemin du dossier d'installation cplex si cela ne correspond pas avec la version du serveur 

  ```
  set(CPLEX_ROOT "C:/Program Files/IBM/ILOG/CPLEX_Studio201/cplex" CACHE INTERNAL "CPLEX installation path (if exists use CPLEX)")
  ```

- Chemins pour Python

  ```
  set(PYTHON_HOME C:/PythonPegase/3_10_9/python CACHE INTERNAL "Python installation path")
  set(PYTHON_VENV C:/PythonPegase/3_10_9/envPegase CACHE INTERNAL "Python virtual environment")

  ```

### Build en lignes de commande
Utiliser la commande BuildAll.bat (un paramètre release/debug permet de définir le type de compilation, par défaut release)

- Pour le BuildAll.bat, il prend par défaut le chemin de CMake de VisualStudio 2022, voir les 1ieres lignes du BuildAll.bat:
```
set CMAKEPATH=C:/PROGRAM FILES/MICROSOFT VISUAL STUDIO/2022/COMMUNITY/COMMON7/IDE/COMMONEXTENSIONS/MICROSOFT/CMAKE/CMake/bin/
if exist "cmakepath.bat" (           
              call cmakepath.bat
)
echo %CMAKEPATH%
```

Pour surcharger ce chemin par défaut, il faut créer un fichier cmakepath.bat indiquant le CMAKEPATH pour utiliser son propre cmake (seule solution avec MSVC2019 car le cmake est trop ancien): 

```
set CMAKEPATH=C:/Program Files/CMake/bin
```

### Build avec Visual Studio 

Ouvrir Visual Studio, choisir 'Ouvrir un dossier local', prendre <mipmodelerPath>

Le menu Projet -> 'Configurer mipmodeler' permet de réaliser la commande cmake : configuration de la compilation/installation dans le répertoire out/<configuration>

Le menu Générer -> 'Tout générer' permet de réaliser la commande cmake --build : compilation dans le répertoire out/<configuration> (génération des fichiers binaires)

Le menu Générer -> 'Installer mipmodeler' permet de réaliser la commande cmake --install : copie les fichiers utiles de out/<configuration> vers bin/<configuration>

#### Eléments de démarrage en Debug
Tous les outils de debugage Visual Studio sont disponibles.

Le fichier <mipmodelerPath>/.vs/launch.vs.json permet de configurer les éléments de démarrage avec des paramètres de lancement pour le debugage. 
(menu Deboguer->Paramètres de debugage)
- Dans le menu déroulant avec la flèche verte (Selectionner un élément de démarrage)
- Le mode Debug se lance en cliquant sur la flèche Verte

#### Configurations (Release, Debug, ...)
Le fichier <mipmodelerPath>/CMakePresets.json définit les différentes configurations pour la configuration, compilation, installation, test, ...

Pour ajouter ces propres configurations, il faut créer un fichier <mipmodelerPath>/CMakeUserPresets.json, 
par exemple pour définir une configuration qui permet l'utilisation d'un fichier d'options particulières (cmake/my_options.cmake):
```
{
  "version": 3,
  "configurePresets": [    
    {
      "name": "mydebug",
      "displayName": "Debug (my options)",
      "inherits": "windows-base",
      "architecture": {
        "value": "x64",
        "strategy": "external"
      },
      "cacheVariables": {
        "CMAKE_BUILD_TYPE": "Debug",		
        "USER_OPTIONS_FILE": "cmake/my_options.cmake"        
      }
    }
  ]
}
```


