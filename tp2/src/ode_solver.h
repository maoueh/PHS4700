#ifndef ODE_SOLVER_H
#define ODE_SOLVER_H

#include "common.h"

// Ode Solver
// We try to solve the following differential equation :
//
//   dy/dt = F(t, y) where y can have more than one dimension i.e be a vector for example
//
// The solver numerically solve the equation by doing small step size (h) and approximate the value
// of the equation by evaluating F(t, y) with the previoulsy known result. Almost every method
// are of the form :
//
//   Yi+1 = Yi + f(t, y) where f(t, y) is a compound function where the evaluation of F(t, y)
//                             occurs one or more times. Results of the evaluation of F(t, y)
//                             are usually multiplied by h or a value derivated from h.
//
// For example, the explicit Euler's Method looks like this :
//
//   Yi+1 = Yi + h * F(t, y) where f(t, y) = h * F(t, y)
// 
// The function F(t, y) is represented in the OdeSolver class by the mFunction member with type
// typedef void (*Function)(Real, Real*, Real*) where the first Real* is Yi and the second Real* 
// is a memory location where to put the result of the evaluation of F(t, y).
// 
// When solving for Y0,   y = Y0 = mLastValue   = initialValue (from constructor)
//                        t = T0 = mCurrentStep = 0            (or startStep from constructor)
// When solving for Yi+1, y = Yi = mLastValue                  (previous result of the step function)
//                        t = Ti = mCurrentStep

template <class Real>
class OdeSolver
{
public:
    virtual ~OdeSolver();

    // F(t, y, y+1) where t and y are the in parameter see above, and y+1 is the 
    // location in memory where to put the result of the evaluation of F. The location
    // of y and y+1 could be the same so be warned.
    typedef void (*Function)(Real, Real*, Real*); 

    virtual Real* step() = 0;

    inline void resetCurrentStep(Real startStep = 0.0);
    inline void reset(Real* initialValue, Real startStep = 0.0);

    inline void setInitialValue(Real* initialValue);

    inline void setStepSize(Real stepSize);
    inline Real getStepSize() const;

protected:
    OdeSolver(Real* initialValue, INT dimension, Function function, Real stepSize, Real startStep = 0.0f);

    Real* mLastValue;
    INT mDimension;
    Real mStepSize;
    Real mCurrentStep;
    Function mFunction;
};

#include "ode_solver.inl"

typedef OdeSolver<FLOAT>    OdeSolverf;
typedef OdeSolver<DOUBLE>   OdeSolverd;

#endif
