#a script to batch submit the code of project
#param $1 the name of the code file or directory
#author ygh
#data 2017.6.3
for name in $(ls ./)
do
	git add $name &&
	git commit -m "commit_$name"
done
git push -u origin master
