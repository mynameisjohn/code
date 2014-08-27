syntax enable
set shiftwidth=3 softtabstop=3 tabstop=3
hi Comment ctermfg=DarkMagenta
hi Statement ctermfg=LightGrey
hi PreProc ctermfg=DarkYellow
autocmd FileType c,cpp source ~/.vim/syntax/opengl.vim
autocmd FileType glsl source ~/.vim/syntax/glsl.vim
