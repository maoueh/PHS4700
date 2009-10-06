function c=QProduit(a,b)
%
% Produit de 2 quaternion
% 
v1=[a(2) a(3) a(4)];
v2=[b(2) b(3) b(4)];
vp=cross(v1,v2);
vecpc=a(1)*v2+b(1)*v1+vp;
c=horzcat((a(1)*b(1)-(v1*v2')),vecpc); 
