#include "ode_runge_kutta4.h"

template <class Real>
OdeRungeKutta4<Real>::OdeRungeKutta4(Real* initialValue, INT dimension, 
                                     typename OdeSolver<Real>::Function function, 
                                     Real stepSize, Real startStep = 0.0f) : 
    OdeSolver<Real>(initialValue, dimension, function, stepSize, startStep),
    mK1(new Real[dimension]), mK2(new Real[dimension]),
    mK3(new Real[dimension]), mK4(new Real[dimension]),
    mHalfStepSize(stepSize * 0.5f)
{
}

template <class Real>
OdeRungeKutta4<Real>::~OdeRungeKutta4()
{
    delete [] mK1;
    delete [] mK2;
    delete [] mK3;
    delete [] mK4;
}

template <class Real>
Real* OdeRungeKutta4<Real>::step()
{
    Real h      = mStepSize;
    Real t      = mCurrentStep;
    Real half_h = mHalfStepSize;
    INT i       = 0;

    // Step #1
    mFunction(t, mLastValue, mK1);
    for (i = 0; i < mDimension; ++i)
    {
        mK1[i] = h * mK1[i];
        mK2[i] = mLastValue[i] + mK1[i] * 0.5f;
    }

    // Step #2
    mFunction(t + half_h, mK2, mK2);
    for (i = 0; i < mDimension; ++i)
    {
        mK2[i] = h * mK2[i];
        mK3[i] = mLastValue[i] + mK2[i] * 0.5f;
    }

    // Step #3
    mFunction(t + half_h, mK3, mK3);
    for (i = 0; i < mDimension; ++i)
    {
        mK3[i] = h * mK3[i];
        mK4[i] = mLastValue[i] + mK3[i];
    }

    // Step #4 and final calculation
    mFunction(t, mK4, mK4);
    for (i = 0; i < mDimension; ++i)
    {
        mK4[i] = h * mK4[i];
        mLastValue[i] = mLastValue[i] + (1 / 6.0f) * (mK1[i] + 2.0f * mK2[i] + 2.0f * mK3[i] + mK4[i]);
    }

    mCurrentStep += h;
    return mLastValue;
}

// Explicit Instantiation
template class OdeRungeKutta4<FLOAT>;
template class OdeRungeKutta4<DOUBLE>;