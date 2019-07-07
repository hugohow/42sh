
cd dqdqzdqzd/../../
echo $PWD
cd dqdqzdqzd/../
echo $PWD
mkdir -p 1/2/3
cd 1/2/3
rm -rf ../../../1
echo $PWD
cd ..
echo PWD : $PWD
echo OLDPWD : $OLDPWD
cd ..
echo PWD : $PWD
echo OLDPWD : $OLDPWD