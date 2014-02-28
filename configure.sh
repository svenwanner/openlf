#!/bin/bash 
# Absolute path to this script, e.g. /home/user/bin/foo.sh
SCRIPT=$(readlink -f "$0")
# Absolute path this script is in, thus /home/user/bin
SCRIPTPATH=$(dirname "$SCRIPT")
TESTDATAPATH=$(dirname "$SCRIPT")
TESTOUTPUTPATH=$(dirname "$SCRIPT")
SETTINGSPATH=$(dirname "$SCRIPT")

SETTINGSPATH+="/tests/settings.h"
TESTDATAPATH+="/tests/data/input/"
TESTOUTPUTPATH+="/tests/data/output/"

echo "create settings file: $SETTINGSPATH"
touch $SETTINGSPATH

/bin/cat <<EOM >$SETTINGSPATH
#include <string>
using namespace std;
#ifndef TEST_SETTINGS_H
#define	TEST_SETTINGS_H
const string test_data_dir = "$TESTDATAPATH";
const string test_result_dir = "$TESTOUTPUTPATH";
#endif	/* TEST_SETTINGS_H */
EOM
