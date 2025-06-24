Tout à été compilé avec MS Visual C++ Build Tools 2019

Version de CoinUtils
https://projects.coin-or.org/svn/CoinUtils/stable/2.10/CoinUtils 
libCoinUtils.dll
libCoinUtils.lib

Version de Osi
https://projects.coin-or.org/svn/Osi/stable/0.107/Osi
libOsi.dll
libOsi.lib

Version de Cgl
https://projects.coin-or.org/svn/Cgl/stable/0.59/Cgl

Version de Clp
https://projects.coin-or.org/svn/Clp/stable/1.16/Clp

Version de Cbc
https://projects.coin-or.org/svn/Cbc/stable/2.9/Cbc

* Ordre des dépendances

CoinUtils  
    <- Osi
    <- Clp
        <- OsiClp
            <- Cgl
                <- Cbc
                    <- CbcSolver
			<- OsiCbc



* Compilation 
Les .lib ont été obtenus en ajoutant l'option CONFIG += staticlib
Les .dll sont obtenus sans cette option