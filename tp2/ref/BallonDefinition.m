function Ballon=BallonDefinition(r)
%
%  Geometrie du ballon de rayon r centre a (0,0,0)
%
ielem=0;
DeltaAngle=pi/4;
xyzcentral=r/sqrt(3);
xycentral=r/sqrt(2);
%
% Chaque quartier du ballon est compose de 6 faces triangulaire identiques
% (a une rotation pres)
% 
% Premier quartier (+x, +y, +z)
for iface=1:6
  for idir=1:3
    Ballon(1,idir,iface,1)=xyzcentral;
    Ballon(4,idir,iface,1)=xyzcentral;
  end;
end;
Ballon(2,1,1,1)=r;
Ballon(2,2,1,1)=0;
Ballon(2,3,1,1)=0;
Ballon(3,1,1,1)=xycentral;
Ballon(3,2,1,1)=xycentral;
Ballon(3,3,1,1)=0;
for iface=2:6
  xyzt(1)=Ballon(2,3,iface-1,1);
  xyzt(2)=Ballon(2,1,iface-1,1);
  xyzt(3)=Ballon(2,2,iface-1,1);
  for idir=1:3
    Ballon(2,idir,iface,1)=Ballon(3,idir,iface-1,1);
    Ballon(3,idir,iface,1)=xyzt(idir);
  end
end
% Quatier en -z symetrique au premier quartier
for iface=1:6
  for isface=1:4
    Ballon(isface,1,iface,2)= Ballon(isface,1,iface,1);
    Ballon(isface,2,iface,2)= Ballon(isface,2,iface,1);
    Ballon(isface,3,iface,2)=-Ballon(isface,3,iface,1);
  end;
end;
% Quatier en -x symetrique au second quartier
for iface=1:6
  for isface=1:4
    Ballon(isface,1,iface,3)=-Ballon(isface,1,iface,2);
    Ballon(isface,2,iface,3)= Ballon(isface,2,iface,2);
    Ballon(isface,3,iface,3)= Ballon(isface,3,iface,2);
  end;
end;
% Quatier en -z symetrique au second quartier
for iface=1:6
  for isface=1:4
    Ballon(isface,1,iface,4)= Ballon(isface,1,iface,3);
    Ballon(isface,2,iface,4)= Ballon(isface,2,iface,3);
    Ballon(isface,3,iface,4)=-Ballon(isface,3,iface,3);
  end;
end;
% Quatier en -x -y symetrique au premier quartier
for iface=1:6
  for isface=1:4
    Ballon(isface,1,iface,5)=-Ballon(isface,2,iface,4);
    Ballon(isface,2,iface,5)= Ballon(isface,1,iface,4);
    Ballon(isface,3,iface,5)= Ballon(isface,3,iface,4);
  end;
end;
% Quatier en -z symetrique au troisieme quartier
for iface=1:6
  for isface=1:4
    Ballon(isface,1,iface,6)= Ballon(isface,1,iface,5);
    Ballon(isface,2,iface,6)= Ballon(isface,2,iface,5);
    Ballon(isface,3,iface,6)=-Ballon(isface,3,iface,5);
  end;
end;
% Quatier en -x symetrique au troisieme quartier
for iface=1:6
  for isface=1:4
    Ballon(isface,1,iface,7)=-Ballon(isface,1,iface,6);
    Ballon(isface,2,iface,7)= Ballon(isface,2,iface,6);
    Ballon(isface,3,iface,7)= Ballon(isface,3,iface,6);
  end;
end;
% Quatier en -z symetrique au quatrieme quartier
for iface=1:6
  for isface=1:4
    Ballon(isface,1,iface,8)= Ballon(isface,1,iface,7);
    Ballon(isface,2,iface,8)= Ballon(isface,2,iface,7);
    Ballon(isface,3,iface,8)=-Ballon(isface,3,iface,7);
  end;
end;
