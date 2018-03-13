#!/bin/bash
git config --global user.email "davidsiaw@gmail.com"
git config --global user.name "David Siaw (via Circle CI)"

git clone -b gh-pages git@github.com:davidsiaw/s2 build
cp -r build/.git ./gittemp
bundle install
bundle exec weaver build -r https://davidsiaw.github.io/s2
cp -r ./gittemp build/.git

pushd build
git add .
git add -u
git commit -m "update `date`"
ssh-agent bash -c 'ssh-add ~/.ssh/id_github.com; git push'
popd
