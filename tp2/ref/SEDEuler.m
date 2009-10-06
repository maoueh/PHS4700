function qs=SEDEuler(q0,t0,Deltat,fonctiong)
%
% Solution ED par methode de Euler
% qs        : vecteur final pour vitesse et position
% q0        : vecteur initial pour vitesse et position
% t0        : temps initial
% Deltat    : intervalle de temps
% fonctiong : membre de droite de ED.
%
qs=q0+feval(fonctiong,q0,t0)*Deltat;
