FIND_PATH(OPENGM_INCLUDE_DIR
  opengm/graphicalmodel/graphicalmodel.hxx
  HINTS "~/usr/local/include/" 
   "~/usr/include"
)

#FIND_LIBRARY(LIBDAI_LIBRARY
#   opengmimpl
#   HINTS "~/usr/local/lib/" 
#   "~/usr/lib/"
#)


INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(OPENGM 
   DEFAULT_MSG 
#   OPENGM_LIBRARY 
   OPENGM_INCLUDE_DIR 
)
	
IF(OPENGM_FOUND)

ELSE()
   SET(OPENGM_INCLUDE_DIR OPENGM_INCLUDE_DIR-NOTFOUND)
#   SET(LIBDAI_LIBRARY   LIBDAI_LIBRARY-NOTFOUND)
ENDIF(OPENGM_FOUND)
