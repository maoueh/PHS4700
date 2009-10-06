clear;
clf;
% 
% 
%
global r;
global vvitesse ;
global qomega ;
r=11./100;
itrace=1;
cm0=[0,0,0]; 
qrot0=[1,0,0,0];
BallonGeo=BallonDefinition(r);
ok=BallonTrace(BallonGeo,cm0,itrace);
itrace=2;
Theta0=0.0;
vvitesse=[1.0,1.0,1.0];
vomega=[0.0,0.0,-2*pi];
qomega=horzcat(0,vomega);
velocite=norm(vvitesse);
velomega=norm(vomega);
uvitesse=vvitesse/velocite;
uomega=vomega/velomega;
pause;
% %
% % Solution exacte
% %
% for i=2:11
%   cm=cm0+vvitesse*0.2*(i-1); 
%   Theta=Theta0+velomega*0.2*(i-1);
%   qrot=horzcat(cos(Theta/2),sin(Theta/2)*uomega);
%   BallonRot=BallonTourne(qrot,BallonGeo);
%   ok=BallonTrace(BallonRot,cm,itrace);
% end;
% pause;
% %
% %  Solution Euler sans renormalization
% %
% cm=cm0+[0.2,0.0,0.0];
% qrot=qrot0;
% t=0.0;
% ok=BallonTrace(BallonGeo,cm,itrace);
% for i=2:11
%   cm=SEDEuler(cm,t,0.2,'TrajectoireLineaire'); 
%   qrot=SEDEuler(qrot,t,0.2,'TrajectoireAngulaire'); 
%   BallonRot=BallonTourne(qrot,BallonGeo);
%   ok=BallonTrace(BallonRot,cm,itrace);
% end;
% pause;
%
%  Solution Euler avec renormalization
%
cm=cm0+[0.4,0.0,0.0];
qrot=qrot0;
t=0.0;
ok=BallonTrace(BallonGeo,cm,itrace);
fprintf('QRot   [%d,%d,%d,%d]\n', qrot(1), qrot(2), qrot(3), qrot(4)); 
fprintf('QOmega [%d,%d,%d,%d]\n', qomega(1), qomega(2), qomega(3), qomega(4));
for i=2:11
  cm=SEDEuler(cm,t,0.2,'TrajectoireLineaire'); 
  qrot=SEDEuler(qrot,t,0.2,'TrajectoireAngulaire'); 
  fprintf('QRot   %i [%d,%d,%d,%d]\n', i - 1, qrot(1), qrot(2), qrot(3), qrot(4));
  qrot=QUnitaire(qrot);
  fprintf('|QRot| %i [%d,%d,%d,%d]\n', i - 1, qrot(1), qrot(2), qrot(3), qrot(4));
  BallonRot=BallonTourne(qrot,BallonGeo);
  ok=BallonTrace(BallonRot,cm,itrace);
end;
hold;
