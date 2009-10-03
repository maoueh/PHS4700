#ifndef ODE_RUNGE_KUTTA4_H
#define ODE_RUNGE_KUTTA4_H

#include "ode_solver.h"

/// Runge-Kutta Fourth Order
/// Yi+1 = Yi + 1/6(k1 + 2 * k2 + 2 * k3 + k4)
///   with
///  k1 = h * F(Ti, Yi)
///  k2 = h * F(Ti + h/2, Yi + k1/2)
///  k3 = h * F(Ti + h/2, Yi + k2/2)
///  k4 = h * F(Ti + h, Yi + k3)
///   where
/// Y0        = initialValue (from constructor)
/// Yi        = mLastValue
/// h         = mStepSize
/// F(T, Y)   = mFunction(mCurrentStep, mLastValue)

template <class Real>
class OdeRungeKutta4 : public OdeSolver<Real>
{
public:
    OdeRungeKutta4(Real* initialValue, INT dimension, typename OdeSolver<Real>::Function function, 
                   Real stepSize, Real startStep = 0.0f);
    virtual ~OdeRungeKutta4();

    virtual Real* step();

protected:
    using OdeSolver<Real>::mLastValue;
    using OdeSolver<Real>::mDimension;
    using OdeSolver<Real>::mStepSize;
    using OdeSolver<Real>::mCurrentStep;
    using OdeSolver<Real>::mFunction;
};

typedef OdeRungeKutta4<FLOAT>    OdeRungeKutta4f;
typedef OdeRungeKutta4<DOUBLE>   OdeRungeKutta4d;

#endif
