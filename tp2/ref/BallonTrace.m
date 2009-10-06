function ok=BallonTrace(Ballon,cm,itrace)
%
%  Dessiner un ballon coloré
%  Ballon  = Description du ballon (voir Ballon.m)
%  cm      = position du centre de masse du ballon
%  itrace  = numero du trace
%
%  Deplacer les secteurs pour centre de masse
%
for isecteur=1:8
  for iface=1:6
    for isface=1:4
      for idir=1:3
        BallonDep(isface,idir,iface,isecteur)=Ballon(isface,idir,iface,isecteur)+cm(idir);
      end;
    end;
  end;
end;
fill3(BallonDep(:,1,1,1),BallonDep(:,2,1,1),BallonDep(:,3,1,1),'r');
if itrace == 1
  hold;
end
for iface=2:6
  fill3(BallonDep(:,1,iface,1),BallonDep(:,2,iface,1),BallonDep(:,3,iface,1),'r');
end
for iface=1:6
  fill3(BallonDep(:,1,iface,2),BallonDep(:,2,iface,2),BallonDep(:,3,iface,2),'b');
end
for iface=1:6
  fill3(BallonDep(:,1,iface,3),BallonDep(:,2,iface,3),BallonDep(:,3,iface,3),'y');
end
for iface=1:6
  fill3(BallonDep(:,1,iface,4),BallonDep(:,2,iface,4),BallonDep(:,3,iface,4),'g');
end
for iface=1:6
  fill3(BallonDep(:,1,iface,5),BallonDep(:,2,iface,5),BallonDep(:,3,iface,5),'b');
end
for iface=1:6
  fill3(BallonDep(:,1,iface,6),BallonDep(:,2,iface,6),BallonDep(:,3,iface,6),'r');
end
for iface=1:6
  fill3(BallonDep(:,1,iface,7),BallonDep(:,2,iface,7),BallonDep(:,3,iface,7),'g');
end
for iface=1:6
  fill3(BallonDep(:,1,iface,8),BallonDep(:,2,iface,8),BallonDep(:,3,iface,8),'y');
end
ok=0;
