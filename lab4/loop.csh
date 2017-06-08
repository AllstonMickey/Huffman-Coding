#!/bin/csh
touch increment
foreach i (`seq 100`)
./increment -n 10 > noMutex.txt
./increment -n 10 -m > yesMutex.txt
diff noMutex.txt yesMutex.txt
echo '\n'
end
