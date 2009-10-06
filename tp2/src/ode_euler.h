#ifndef ODE_EULER_H
#define ODE_EULER_H

#include "ode_solver.h"

/// Explicit Euler's Method
/// Y0   = Y0 + h * F(T0, Y0)
/// Yi+1 = Yi + h * F(Ti, Yi)
///   where
/// Y0        = initialValue (from constructor)
/// Yi        = mLastValue
/// h         = mStepSize
/// F(T, Y)   = mFunction(mCurrentStep, mLastValue);

template <class Real>
class OdeEuler : public OdeSolver<Real>
{
public:
    OdeEuler(Real* initialValue, INT dimension, typename OdeSolver<Real>::Function function, 
             Real stepSize, Real startStep = 0.0f);
    virtual ~OdeEuler();

    virtual Real* step();

protected:
    using OdeSolver<Real>::mLastValue;
    using OdeSolver<Real>::mDimension;
    using OdeSolver<Real>::mStepSize;
    using OdeSolver<Real>::mCurrentStep;
    using OdeSolver<Real>::mFunction;

private:
    Real* mFunctionResult;

};

typedef OdeEuler<FLOAT>    OdeEulerf;
typedef OdeEuler<DOUBLE>   OdeEulerd;

#endif
