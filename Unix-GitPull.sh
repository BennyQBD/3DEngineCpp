#Clean up any files that aren't part of the repository
#because they will need to be regenerated after a pull.
./Unix-Clean.sh

#Pull any commits from the remote branch
git pull origin master
