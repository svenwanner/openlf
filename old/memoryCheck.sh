cd build/test_release
valgrind --tool=memcheck --leak-check=yes -v ./OpenLF_test_imgproc
valgrind --tool=memcheck --leak-check=yes -v ./OpenLF_test_image
valgrind --tool=memcheck --leak-check=yes -v ./OpenLF_test_lightfield_IO
valgrind --tool=memcheck --leak-check=yes -v ./OpenLF_test_lightfield
