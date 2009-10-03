#include "ode_runge_kutta4.h"

template <class Real>
OdeRungeKutta4<Real>::OdeRungeKutta4(Real* initialValue, INT dimension, 
                                     typename OdeSolver<Real>::Function function, 
                                     Real stepSize, Real startStep = 0.0f) : 
    OdeSolver<Real>(initialValue, dimension, function, stepSize, startStep)
{

}

template <class Real>
OdeRungeKutta4<Real>::~OdeRungeKutta4()
{

}

template <class Real>
Real* OdeRungeKutta4<Real>::step()
{
    Real h      = mStepSize;
    Real t      = mCurrentStep;
    Real half_h = h / 2.0f;

    Real k1, k2, k3, k4, yi;
    for (INT i = 0; i < mDimension; ++i)
    {
        yi = mLastValue[i];
        k1 = h * mFunction(t,          yi,             i);
        k2 = h * mFunction(t + half_h, yi + k1 / 2.0f, i);
        k3 = h * mFunction(t + half_h, yi + k2 / 2.0f, i);
        k4 = h * mFunction(t + h,      yi + k3,        i);

        mLastValue[i] = yi + (1 / 6.0f) * (k1 + 2.0f * k2 + 2.0f * k3 + k4);
    }

    mCurrentStep += h;
    return mLastValue;
}

// Explicit Instantiation
template class OdeRungeKutta4<FLOAT>;
template class OdeRungeKutta4<DOUBLE>;