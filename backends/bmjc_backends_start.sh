currentPath=$(cd "$(dirname "$0")"; pwd)
export LD_LIBRARY_PATH=$currentPath/lib:$currentPath/src/apollo/trojanCheck/clamav/lib:$LD_LIBRARY_PATH
cd $currentPath/src/startup
python bootStrap.py

