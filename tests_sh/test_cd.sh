cd ./directory
echo $?
echo $PWD
echo $OLDPWD
cd ./tests
echo $?
echo $PWD
echo $OLDPWD
cd ..
echo $?
echo $PWD
echo $OLDPWD
cd tests
echo $?
echo $PWD
echo $OLDPWD
cd /
echo $?
echo $PWD
echo $OLDPWD
cd 
echo $?
echo $PWD
echo $OLDPWD
mkdir perm
chmod 000 perm
cd perm
echo $?
echo $PWD
echo $OLDPWD
cd ..
echo $?
echo $PWD
echo $OLDPWD
rm -rf perm
cd /~
echo $?
cd /-
echo $?
exit