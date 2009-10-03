#include "ode_euler.h"

template <class Real>
OdeEuler<Real>::OdeEuler(Real* initialValue, INT dimension, 
                         typename OdeSolver<Real>::Function function, 
                         Real stepSize, Real startStep = 0.0f) : 
    OdeSolver<Real>(initialValue, dimension, function, stepSize, startStep)
{

}

template <class Real>
OdeEuler<Real>::~OdeEuler()
{

}

template <class Real>
Real* OdeEuler<Real>::step()
{
    Real h = mStepSize;
    Real t = mCurrentStep;

    Real yi;
    for (INT i = 0; i < mDimension; ++i)
    {
        yi = mLastValue[i];
        mLastValue[i] = yi + h * mFunction(t, yi, i);
    }
   
    mCurrentStep += mStepSize;
    return mLastValue;
}

// Explicit Instantiation
template class OdeEuler<FLOAT>;
template class OdeEuler<DOUBLE>;