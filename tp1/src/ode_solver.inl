
template <class Real>
OdeSolver<Real>::OdeSolver(Real* initialValue, INT dimension, Function function, 
                           Real stepSize, Real startStep /* = 0.0f */) : 
     mDimension(dimension),       mLastValue(NULL),
     mStepSize(stepSize),         mFunction(function), 
     mCurrentStep(startStep) 
{ 
    assert(dimension > 0 && "OdeSolver: dimension invalid");
    mLastValue = new Real[dimension];
    for (INT i = 0; i < dimension; ++i)
        mLastValue[i] = initialValue[i];
}

template <class Real>
OdeSolver<Real>::~OdeSolver()
{ 
    delete[] mLastValue;
}

template <class Real>
inline void OdeSolver<Real>::resetCurrentStep(Real startStep = 0.0) 
{ 
    mCurrentStep = startStep; 
}

template <class Real>
inline void OdeSolver<Real>::reset(Real* initialValue, Real startStep = 0.0) 
{ 
    setInitialValue(initialValue); 
    resetCurrentStep(startStep); 
}

template <class Real>
inline void OdeSolver<Real>::setInitialValue(Real* initialValue) 
{ 
    for (INT i = 0; i < mDimension; ++i)
        mLastValue[i] = initialValue[i]; 
}

template <class Real>
inline void OdeSolver<Real>::setStepSize(Real stepSize) 
{ 
    mStepSize = stepSize; 
}

template <class Real>
inline Real OdeSolver<Real>::getStepSize() const
{ 
    return mStepSize; 
}