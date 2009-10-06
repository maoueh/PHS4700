#include "ode_euler.h"

template <class Real>
OdeEuler<Real>::OdeEuler(Real* initialValue, INT dimension, 
                         typename OdeSolver<Real>::Function function, 
                         Real stepSize, Real startStep = 0.0f) : 
    OdeSolver<Real>(initialValue, dimension, function, stepSize, startStep),
    mFunctionResult(new Real[dimension])
{
}

template <class Real>
OdeEuler<Real>::~OdeEuler()
{
    delete [] mFunctionResult;
}

template <class Real>
Real* OdeEuler<Real>::step()
{
    Real h = mStepSize;
    Real t = mCurrentStep;

    mFunction(t, mLastValue, mFunctionResult);
    for (INT i = 0; i < mDimension; ++i)
        mLastValue[i] = mLastValue[i] + h * mFunctionResult[i];
   
    mCurrentStep += mStepSize;
    return mLastValue;
}

// Explicit Instantiation
template class OdeEuler<FLOAT>;
template class OdeEuler<DOUBLE>;