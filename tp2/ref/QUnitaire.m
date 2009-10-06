function c=QUnitaire(a)
%
% Normaliser le quaternion ˆ 1
% 
v1=[a(2) a(3) a(4)];
long=a(1)^2+dot(v1,v1);
c=a/long; 
