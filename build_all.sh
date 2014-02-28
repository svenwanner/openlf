{
cd doc 
rm -r *
cd .. 
}
make clean
make
doxygen Doxyfile
cd doc
cd latex
make
mv refman.pdf ../OpenLF.pdf
cd ..
ln html/index.html OpenLF.html
