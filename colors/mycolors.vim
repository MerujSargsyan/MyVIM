hi clear
if exists("syntax_on")
    syntax reset
endif

let g:colors_name = "mycolors"

highlight Normal ctermfg=255 ctermbg=235
highlight Type   ctermfg=226 cterm=bold
highlight String ctermfg=76
highlight Conditional ctermfg=226 cterm=bold
highlight Label  ctermfg=226
highlight Function ctermfg=255
highlight Statement ctermfg=226 cterm=bold
highlight Constant ctermfg=255 cterm=bold
highlight PreProc ctermfg=226 cterm=bold
highlight Comment ctermfg=245

highlight link Define Statement
highlight link Include Statement

highlight Cursor ctermfg=yellow
highlight LineNr ctermfg=gray
highlight StatusLine ctermfg=white ctermbg=black
