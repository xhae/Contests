set ai
set hlsearch
set ts=4
set sw=4
syntax on
set nu
set smartindent
set autoindent
set ci
set si

colo desert

set guifont=Monaco:h13

filetype plugin indent on

map <F9> :!clang++ % -std=c++1y -O2 -o %<.out<CR>
map <C-F9> :!./%<.out<CR>
map <C-F10> :!./%<.out < input.txt<CR>
map <F11> :!python %<CR>
map <F12> :!python % < input.txt<CR>
