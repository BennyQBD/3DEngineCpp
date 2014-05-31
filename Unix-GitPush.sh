#Move the res directory back to it's inital position
mv ./build/res/ ./

#Add everything to a new commit and push it to github
git add -A
git commit
git push origin master

#Move the res directory back to the working "build" directory
mv ./res/ ./build/
