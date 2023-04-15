#!/usr/bin/env nu

let browser = 'chromium'
# let browser = 'firefox'
# let browser = 'opera'

# let files = [
# ]

# let files_arg = ( $files | each {|$it| $"'($it)'"} | str join ' ' )
run-external $browser '1/bigger-image.html' '1/bigger-text.html' '2/index.html' '3/answer.html' '4/answer.html' '5/answer.html' '6/answer.html' '7/answer.html'
