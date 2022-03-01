rm -rf html-docs && mkdir html-docs && cp os-lecs.md html-docs/index.md && cp -r lec[1-9]* html-docs/
marp --html --input-dir html-docs/ --output html-docs/