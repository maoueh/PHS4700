function g=TrajectoireLineaire(q0,t0)
%
%  Ballon avec trajectoire angulaire de vitesse constante
%
global qomega;
qproduit = QProduit(q0,qomega);
fprintf('Prod     [%d,%d,%d,%d]\n', qproduit(1), qproduit(2), qproduit(3), qproduit(4));
g=QProduit(q0,qomega) / 2;
fprintf('Prod/2   [%d,%d,%d,%d]\n', g(1), g(2), g(3), g(4));
