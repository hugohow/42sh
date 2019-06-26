env -i SHLVL=-2 echo $SHLVL
echo $?
env -i SHLVL=-1000 echo $SHLVL
echo $SHLVL
env -i SHLVL=10032 ls
exit