<pre>
 *   Author           : Dr. Yacine GAOUA (yacine.gaoua@cea.fr)
 *   Version          : 1.0.0
 *   Description      : MIPModeler (Algebraic Modeling Language for optimisation)
</pre>

# Introduction

MIPModeler (Mixed Integer Progamming Modeler) is a C++ library designed to build linear optimization problems using native C++ algebraic expressions as CPLEX, GUROBI modelers. 

MIPModeler allows us to build optimization problems using expressions close to the original mathematical description.

MIPModeler has several solver interfaces which allow it to be easily connected to the most MILP solvers (CPLEX, GUROBI, XPRESS, MOSEK, CBC, CLP, GLPK, SOPLEX, ...).

MIPModeler offers also the possibility to declare SOS variables and to use helpfull efficient generic methods (piecewise linearisation, 2d interpolation, ...).<br/><br/>