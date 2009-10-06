function BallonRot=BallonTourne(qrot,Ballon)
%
%  Tourner un ballon par un quaternion de rotation 
%  qrot    : Quaternion de rotation.
%  Ballon  : Definition du ballon (Voir BallonDefinition.m). 
%
%  Deplacer les secteurs pour centre de masse
%
for isecteur=1:8
  for iface=1:6
    for isface=1:4
      VBallonR=[Ballon(isface,1,iface,isecteur),...
                Ballon(isface,2,iface,isecteur),...
                Ballon(isface,3,iface,isecteur)];
      BallonR=QVRotation(qrot,VBallonR);
      for idir=1:3
        BallonRot(isface,idir,iface,isecteur)=BallonR(idir);
      end;
    end;
  end;
end;
