#Clean up files that aren't wanted in the commit
./Unix-Clean.sh

#Copy README.md to build directory so github includes it
cp README.md ./build

#Add everything to a new commit and push it to github
git add -A
git commit
git push origin master
