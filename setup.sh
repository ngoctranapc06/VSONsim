#source /usr/local/sklib_gcc4.8.5/geant4.10.03.p01/bin/geant4.sh
cd /Users/ngocha/Geant4/install/bin
source geant4.sh
#source /usr/local/sklib_gcc4.8.5/geant4.10.03.p01/share/Geant4-10.3.1/geant4make/geant4make.sh
cd /Users/ngocha/Geant4/install/share/Geant4-10.5.1/geant4make
source geant4make.sh

cd /Users/ngocha/VSONsim
export G4WORKDIR=`pwd`
export G4BIN=$G4WORKDIR/bin
export G4TMP=$G4WORKDIR/tmp

#source /usr/local/sklib_gcc4.8.5/root_v5.34.36/bin/thisroot.sh
source ~/root/bin/thisroot.sh
alias root='root -l'
