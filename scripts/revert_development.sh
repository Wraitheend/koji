#!/bin/bash

git switch development &&
git fetch origin &&
git rebase origin/main &&
git push --force-with-lease origin development &&
git switch development
