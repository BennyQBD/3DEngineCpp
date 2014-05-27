#Clean up files that aren't wanted in the commit
./Unix-Clean.sh

#Add .gitkeep so github includes build directory
touch ./build/.gitkeep

#Add everything to a new commit and push it to github
git add -A
git commit
git push origin master
