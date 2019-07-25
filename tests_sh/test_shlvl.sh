env -i SHLVL=-2 echo $SHLVL
echo $?
env -i SHLVL=-1000 echo $SHLVL
echo $SHLVL
env -i SHLVL=10032 ls
echo a
exit
# env -i SHLVL=10032 ./21sh ; echo $SHLVL
# env -i SHLVL=999 ./21sh ; echo $SHLVL
# env -i SHLVL=998 ./21sh ; echo $SHLVL