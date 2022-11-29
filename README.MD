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