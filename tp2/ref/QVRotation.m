function c=QVRotation(a,b)
%
% Rotation du vecteur b par le quaternion a
%
qb=[0 b(1) b(2) b(3)];
v1=QProduit(a,qb);
v2=QConjugue(a);
qc=QProduit(v1,v2); 
c=[qc(2) qc(3) qc(4)];

