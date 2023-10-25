#!/bin/bash

# the script will load the main_page.html file and put it in the ./main/html_page.h file as a string like this:
# const char *index_html = "<html><head>...</head><body>...</body></html>";

output_file="./main/html_page.h"

echo -n "const char *index_html = \"" > $output_file
cat main_page.html | sed -e 's/"/\\"/g' | sed -e 's/$/\\/' >> $output_file
echo "\";" >> $output_file
