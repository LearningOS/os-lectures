rm -rf docs && mkdir docs && cp os-lecs.md docs/index.md && cp -r lec[1-9]* docs
marp --html --input-dir docs/ --output docs/